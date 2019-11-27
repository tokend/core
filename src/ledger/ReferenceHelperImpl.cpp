#include "ReferenceHelperImpl.h"
#include "LedgerDelta.h"
#include "xdrpp/printer.h"
#include "database/Database.h"

using namespace soci;
using namespace std;

namespace stellar {
    using xdr::operator<;

    void ReferenceHelperImpl::dropAll() {
        Database& db = getDatabase();
        db.getSession() << "DROP TABLE IF EXISTS reference;";
        db.getSession() << "CREATE TABLE reference"
                           "("
                           "sender       VARCHAR(64) NOT NULL,"
                           "reference    VARCHAR(64) NOT NULL,"
                           "lastmodified INT         NOT NULL,"
                           "PRIMARY KEY (sender, reference)"
                           ");";
    }

    void ReferenceHelperImpl::storeAdd(LedgerEntry const &entry) {
        storeUpdateHelper(true, entry);
    }

    void ReferenceHelperImpl::storeChange(LedgerEntry const &entry) {
        storeUpdateHelper(false, entry);
    }

    void ReferenceHelperImpl::storeUpdateHelper(bool insert, const LedgerEntry &entry) {
        Database& db = getDatabase();
        auto& delta = mStorageHelper.mustGetLedgerDelta();
        auto referenceFrame = make_shared<ReferenceFrame>(entry);
        auto referenceEntry = referenceFrame->getReference();

        referenceFrame->touch(delta);

        if (!referenceFrame->isValid())
        {
            CLOG(ERROR, Logging::ENTRY_LOGGER) << "Invalid reference: " << xdr::xdr_to_string(entry);
            throw std::runtime_error("Invalid reference");
        }

        auto reference = referenceFrame->getReferenceString();
        auto sender = PubKeyUtils::toStrKey(referenceFrame->getSender());
        auto version = static_cast<uint32_t>(referenceEntry.ext.v());

        std::string sql;
        if (insert)
        {
            sql = "INSERT INTO reference (reference, sender, lastmodified, version) "
                  "VALUES (:r, :se, :lm, :v)";
        } else {
            sql = "UPDATE reference "
                  "SET    lastmodified=:lm, version=:v "
                  "WHERE  reference=:r AND sender=:se ";
        }

        auto prep = db.getPreparedStatement(sql);
        auto& st = prep.statement();

        st.exchange(soci::use(reference, "r"));
        st.exchange(soci::use(sender, "se"));
        st.exchange(soci::use(referenceFrame->mEntry.lastModifiedLedgerSeq, "lm"));
        st.exchange(soci::use(version, "v"));
        st.define_and_bind();

        auto timer =
                insert ? db.getInsertTimer("reference") : db.getUpdateTimer("reference");
        st.execute(true);

        if (st.get_affected_rows() != 1) {
            throw std::runtime_error("could not update SQL");
        }

        if (insert) {
            delta.addEntry(*referenceFrame);
        } else {
            delta.modEntry(*referenceFrame);
        }
    }

    void ReferenceHelperImpl::storeDelete(LedgerKey const &key) {
        Database& db = getDatabase();
        LedgerDelta* delta = getLedgerDelta();
        auto timer = db.getDeleteTimer("reference");
        auto prep = db.getPreparedStatement("DELETE FROM reference WHERE reference=:r AND sender=:se");
        auto& st = prep.statement();
        st.exchange(use(key.reference().reference));
        auto sender = PubKeyUtils::toStrKey(key.reference().sender);
        st.exchange(use(sender));
        st.define_and_bind();
        st.execute(true);
        delta->deleteEntry(key);
    }

    bool ReferenceHelperImpl::exists(LedgerKey const &key) {
        return exists(key.reference().reference, key.reference().sender);
    }

    LedgerKey ReferenceHelperImpl::getLedgerKey(LedgerEntry const &from) {
        LedgerKey ledgerKey;
        ledgerKey.type(from.data.type());
        ledgerKey.reference().reference = from.data.reference().reference;
        ledgerKey.reference().sender = from.data.reference().sender;
        return ledgerKey;
    }

    EntryFrame::pointer ReferenceHelperImpl::storeLoad(LedgerKey const &key) {
        return loadReference(key.reference().sender,key.reference().reference);
    }

    EntryFrame::pointer ReferenceHelperImpl::fromXDR(LedgerEntry const &from) {
        return std::make_shared<ReferenceFrame>(from);
    }

    uint64_t ReferenceHelperImpl::countObjects() {
        uint64_t count = 0;
        Database &db = getDatabase();
        db.getSession() << "SELECT COUNT(*) FROM reference;", into(count);
        return count;
    }

    void
    ReferenceHelperImpl::loadReferences(StatementContext &prep, function<void(const LedgerEntry &)> referenceProcessor) {
        LedgerEntry le;
        le.data.type(LedgerEntryType::REFERENCE_ENTRY);
        ReferenceEntry& oe = le.data.reference();

        statement& st = prep.statement();
        st.exchange(into(oe.sender));
        st.exchange(into(oe.reference));
        st.exchange(into(le.lastModifiedLedgerSeq));

        uint32_t referenceVersion = 0;
        st.exchange(into(referenceVersion));

        st.define_and_bind();
        st.execute(true);
        while (st.got_data())
        {
            oe.ext.v(LedgerVersion(referenceVersion));
            if (!ReferenceFrame::isValid(oe))
            {
                CLOG(ERROR, Logging::ENTRY_LOGGER)
                        << "Unexpected state - references is invalid: "
                        << xdr::xdr_to_string(oe);
                throw std::runtime_error("Unexpected state - references is invalid");
            }

            referenceProcessor(le);
            st.fetch();
        }
    }

    bool ReferenceHelperImpl::exists(std::string reference, AccountID rawSender) {
        Database& db = getDatabase();
        int exists = 0;
        auto timer = db.getSelectTimer("reference-exists");
        auto prep =
                db.getPreparedStatement("SELECT EXISTS (SELECT NULL FROM reference WHERE reference=:r AND sender=:se)");
        auto& st = prep.statement();
        st.exchange(use(reference, "r"));
        auto sender = PubKeyUtils::toStrKey(rawSender);
        st.exchange(use(sender, "se"));
        st.exchange(into(exists));
        st.define_and_bind();
        st.execute(true);

        return exists != 0;
    }

    ReferenceFrame::pointer
    ReferenceHelperImpl::loadReference(AccountID rawSender, std::string reference) {
        Database& db = getDatabase();
        LedgerDelta* delta = getLedgerDelta();
        std::string sql = "SELECT sender, reference, lastmodified, version FROM reference";
        sql += " WHERE reference = :ref AND sender = :sender";
        auto prep = db.getPreparedStatement(sql);
        auto& st = prep.statement();
        st.exchange(use(reference, "ref"));
        auto sender = PubKeyUtils::toStrKey(rawSender);
        st.exchange(use(sender, "sender"));

        auto timer = db.getSelectTimer("reference");
        ReferenceFrame::pointer retReference;
        loadReferences(prep, [&retReference](LedgerEntry const& Reference)
        {
            retReference = make_shared<ReferenceFrame>(Reference);
        });

        if (delta && retReference)
        {
            delta->recordEntry(*retReference);
        }

        return retReference;
    }

    void ReferenceHelperImpl::addVersion()
    {
       getDatabase().getSession() << "ALTER TABLE reference ADD COLUMN version INT NOT NULL DEFAULT 0";
    }

    LedgerDelta *ReferenceHelperImpl::getLedgerDelta() {
        return mStorageHelper.getLedgerDelta();
    }

    Database &ReferenceHelperImpl::getDatabase() {
        return mStorageHelper.getDatabase();
    }

    ReferenceHelperImpl::ReferenceHelperImpl(StorageHelper &storageHelper)
            : mStorageHelper(storageHelper)
    {
        mReferenceColumnSelector =
                "SELECT code, owner, preissued_asset_signer, "
                "details, max_issuance_amount, "
                "available_for_issueance, issued, pending_issuance, "
                "policies, type, trailing_digits, lastmodified, version "
                "FROM asset ";
    }
}
