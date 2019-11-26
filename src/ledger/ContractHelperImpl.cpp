#include "ContractHelperImpl.h"
#include <xdrpp/marshal.h>
#include <lib/util/basen.h>
#include "LedgerDelta.h"
#include "database/Database.h"

using namespace std;
using namespace soci;

namespace stellar
{
    const char* contractSelector = "SELECT id, contractor, customer, escrow,"
                                   "       start_time, end_time, initial_details, invoices,"
                                   "       state, lastmodified, version, customer_details "
                                   "FROM   contracts";

    void ContractHelperImpl::dropAll()
    {
        Database& db = mStorageHelper.getDatabase();

        db.getSession() << "DROP TABLE IF EXISTS contracts;";
        db.getSession() << "CREATE TABLE contracts"
                           "("
                           "id              BIGINT      NOT NULL CHECK (id >= 0) PRIMARY KEY,"
                           "contractor      VARCHAR(56) NOT NULL,"
                           "customer        VARCHAR(56) NOT NULL,"
                           "escrow          VARCHAR(56) NOT NULL,"
                           "start_time      BIGINT      NOT NULL CHECK (start_time >= 0),"
                           "end_time        BIGINT      NOT NULL CHECK (end_time >= 0),"
                           "initial_details TEXT        NOT NULL,"
                           "invoices        TEXT        NOT NULL,"
                           "state           INT         NOT NULL,"
                           "lastmodified    INT         NOT NULL,"
                           "version         INT         NOT NULL DEFAULT 0"
                           ");";
    }

    void ContractHelperImpl::addCustomerDetails()
    {
        Database& db = getDatabase();
        db.getSession() << "ALTER TABLE contracts ADD COLUMN customer_details TEXT NOT NULL DEFAULT '';";
    }

    void
    ContractHelperImpl::storeUpdateHelper(bool insert, LedgerEntry const &entry)
    {
        Database &db = getDatabase();
        auto& delta = mStorageHelper.mustGetLedgerDelta();
        auto contractFrame = make_shared<ContractFrame>(entry);
        auto contractEntry = contractFrame->getContract();

        contractFrame->touch(delta);

        auto key = contractFrame->getKey();
        flushCachedEntry(key);

        string contractorID = PubKeyUtils::toStrKey(contractEntry.contractor);
        string customerID = PubKeyUtils::toStrKey(contractEntry.customer);
        string escrowID = PubKeyUtils::toStrKey(contractEntry.escrow);

        string strDetails = bn::encode_b64(contractEntry.initialDetails);
        auto invoicesBytes = xdr::xdr_to_opaque(contractEntry.invoiceRequestsIDs);
        string strInvoices = bn::encode_b64(invoicesBytes);
        auto state = static_cast<int32_t>(contractEntry.state);
        auto version = static_cast<int32_t>(contractEntry.ext.v());
        string customerDetails = contractFrame->getCustomerDetails();

        string sql;

        if (insert)
        {
            sql = "INSERT INTO contracts (id, contractor, customer, escrow,"
                  "                       start_time, end_time, initial_details, invoices, "
                  "                       state, lastmodified, version, customer_details) "
                  "VALUES (:id, :contractor, :customer, :escrow, :s_t, :e_t,"
                  "        :init_det, :invoices, :state, :lm, :v, :c_d)";
        }
        else
        {
            sql = "UPDATE contracts "
                  "SET    contractor = :contractor, customer = :customer, escrow = :escrow,"
                  "       start_time = :s_t, end_time = :e_t,"
                  "       initial_details = :init_det, invoices = :invoices,"
                  "       state = :state, lastmodified = :lm, version = :v, customer_details = :c_d "
                  "WHERE  id = :id";
        }

        auto prep = db.getPreparedStatement(sql);
        auto& st = prep.statement();

        st.exchange(use(contractEntry.contractID, "id"));
        st.exchange(use(contractorID, "contractor"));
        st.exchange(use(customerID, "customer"));
        st.exchange(use(escrowID, "escrow"));
        st.exchange(use(contractEntry.startTime, "s_t"));
        st.exchange(use(contractEntry.endTime, "e_t"));
        st.exchange(use(strDetails, "init_det"));
        st.exchange(use(strInvoices, "invoices"));
        st.exchange(use(state, "state"));
        st.exchange(use(contractFrame->mEntry.lastModifiedLedgerSeq, "lm"));
        st.exchange(use(version, "v"));
        st.exchange(use(customerDetails, "c_d"));
        st.define_and_bind();

        auto timer = insert ? db.getInsertTimer("contracts")
                            : db.getUpdateTimer("contracts");
        st.execute(true);

        if (st.get_affected_rows() != 1)
            throw runtime_error("could not update SQL");

        if (insert)
            delta.addEntry(*contractFrame);
        else
            delta.modEntry(*contractFrame);
    }

    void
    ContractHelperImpl::storeAdd(LedgerEntry const &entry)
    {
        storeUpdateHelper(true, entry);
    }

    void
    ContractHelperImpl::storeChange(LedgerEntry const &entry)
    {
        storeUpdateHelper(false, entry);
    }

    void
    ContractHelperImpl::storeDelete(LedgerKey const &key)
    {
        Database& db = getDatabase();
        auto timer = db.getDeleteTimer("contracts");
        auto prep = db.getPreparedStatement("DELETE FROM contracts WHERE id = :id");
        auto& st = prep.statement();
        st.exchange(use(key.contract().contractID));
        st.define_and_bind();
        st.execute(true);
        mStorageHelper.mustGetLedgerDelta().deleteEntry(key);
    }

    bool
    ContractHelperImpl::exists(LedgerKey const &key)
    {
        Database& db = getDatabase();
        int exists = 0;
        auto timer = db.getSelectTimer("contract_exists");
        auto prep = db.getPreparedStatement("SELECT EXISTS (SELECT NULL FROM contracts WHERE id = :id)");
        auto& st = prep.statement();
        st.exchange(use(key.contract().contractID, "id"));
        st.exchange(into(exists));
        st.define_and_bind();
        st.execute(true);

        return exists != 0;
    }

    LedgerKey
    ContractHelperImpl::getLedgerKey(LedgerEntry const &from)
    {
        LedgerKey ledgerKey;
        ledgerKey.type(from.data.type());
        ledgerKey.contract().contractID = from.data.contract().contractID;
        return ledgerKey;
    }

    EntryFrame::pointer
    ContractHelperImpl::storeLoad(LedgerKey const &key)
    {
        auto const &contract = key.contract();
        return loadContract(contract.contractID);
    }

    EntryFrame::pointer
    ContractHelperImpl::fromXDR(LedgerEntry const &from)
    {
        return make_shared<ContractFrame>(from);
    }

    uint64_t
    ContractHelperImpl::countObjects()
    {
        uint64_t count = 0;
        Database &db = getDatabase();
        db.getSession()<< "SELECT COUNT(*) FROM contracts;", into(count);
        return count;
    }

    void
    ContractHelperImpl::load(StatementContext& prep,
                         function<void(LedgerEntry const&)> processor)
    {
        string contractorID, customerID, escrowID;
        string details, invoices, customerDetails;

        LedgerEntry le;
        le.data.type(LedgerEntryType::CONTRACT);
        ContractEntry& oe = le.data.contract();
        int32_t version = 0;

        auto& st = prep.statement();
        st.exchange(into(oe.contractID));
        st.exchange(into(contractorID));
        st.exchange(into(customerID));
        st.exchange(into(escrowID));
        st.exchange(into(oe.startTime));
        st.exchange(into(oe.endTime));
        st.exchange(into(details));
        st.exchange(into(invoices));
        st.exchange(into(oe.state));
        st.exchange(into(le.lastModifiedLedgerSeq));
        st.exchange(into(version));
        st.exchange(into(customerDetails));
        st.define_and_bind();
        st.execute(true);

        while (st.got_data())
        {
            oe.contractor = PubKeyUtils::fromStrKey(contractorID);
            oe.customer = PubKeyUtils::fromStrKey(customerID);
            oe.escrow = PubKeyUtils::fromStrKey(escrowID);

            bn::decode_b64(details, oe.initialDetails);

            std::vector<uint8_t> decodedInv;
            bn::decode_b64(invoices, decodedInv);
            xdr::xdr_get unmarshalerInv(&decodedInv.front(), &decodedInv.back() + 1);
            xdr::xdr_argpack_archive(unmarshalerInv, oe.invoiceRequestsIDs);
            unmarshalerInv.done();

            oe.ext.v(static_cast<LedgerVersion>(version));
            ContractFrame::setCustomerDetails(oe, customerDetails);

            processor(le);
            st.fetch();
        }
    }

    ContractFrame::pointer
    ContractHelperImpl::loadContract(uint64_t id)
    {
        Database& db = getDatabase();
        LedgerDelta* delta = getLedgerDelta();
        ContractFrame::pointer contractFrame;

        string sql = contractSelector;
        sql += " WHERE id = :id";
        auto prep = db.getPreparedStatement(sql);
        auto& st = prep.statement();
        st.exchange(use(id, "id"));

        auto timer = db.getSelectTimer("contract");
        load(prep, [&contractFrame](LedgerEntry const& contract)
        {
            contractFrame = make_shared<ContractFrame>(contract);
        });

        if (delta && contractFrame)
            delta->recordEntry(*contractFrame);

        return contractFrame;
    }

    uint64_t
    ContractHelperImpl::countContracts(AccountID const& contractor)
    {
        Database& db = getDatabase();
        string contractorStr = PubKeyUtils::toStrKey(contractor);

        auto& sess = db.getSession();
        uint64_t count = 0;
        sess << "SELECT COUNT(*) FROM contracts WHERE contractor = :contractor;",
                use(contractorStr, "contractor"), into(count);
        return count;
    }

    LedgerDelta *ContractHelperImpl::getLedgerDelta() {
        return mStorageHelper.getLedgerDelta();
    }

    Database &ContractHelperImpl::getDatabase() {
        return mStorageHelper.getDatabase();
    }

    ContractHelperImpl::ContractHelperImpl(StorageHelper &storageHelper)
            : mStorageHelper(storageHelper)
    {
        mContractColumnSelector =
                "SELECT code, owner, preissued_asset_signer, "
                "details, max_issuance_amount, "
                "available_for_issueance, issued, pending_issuance, "
                "policies, type, trailing_digits, lastmodified, version "
                "FROM asset ";
    }
}