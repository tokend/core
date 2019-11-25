#include "AccountKYCHelperImpl.h"
#include "LedgerDelta.h"
#include "database/Database.h"
#include "AccountHelperImpl.h"
#include "StorageHelper.h"
#include <xdrpp/marshal.h>
#include <lib/util/basen.h>

using namespace std;
using namespace soci;


namespace stellar
{

    void AccountKYCHelperImpl::dropAll()
    {
        Database &db = getDatabase();

        db.getSession() << "DROP TABLE IF EXISTS account_kyc;";

        db.getSession() << "CREATE TABLE account_kyc"
                           "("
                           "accountid       VARCHAR(56)     PRIMARY KEY,"
                           "kyc_data        TEXT            NOT NULL,"
                           "lastmodified    INT             NOT NULL,"
                           "version         INT             NOT NULL    DEFAULT 0"
                           ");";
    }

    void AccountKYCHelperImpl::storeUpdate(const LedgerEntry &entry, bool insert)
    {
        Database &db = getDatabase();
        LedgerDelta* delta = getLedgerDelta();
        auto accountKYCFrame = std::make_shared<AccountKYCFrame>(entry);

        accountKYCFrame->touch(*delta);

        auto key = accountKYCFrame->getKey();
        flushCachedEntry(key);

        std::string sqlQuery;
        if (insert)
            sqlQuery = std::string("INSERT INTO account_kyc (accountid, kyc_data, lastmodified, version) "
                                   "VALUES (:id, :data, :lm, :v) ");
        else
            sqlQuery = std::string("UPDATE account_kyc "
                                   "SET    kyc_data=:data, lastmodified=:lm, version=:v "
                                   "WHERE  accountid=:id ");

        auto accountKYCEntry = accountKYCFrame->getAccountKYC();
        std::string accIdStr = PubKeyUtils::toStrKey(accountKYCEntry.accountID);
        uint32_t version = static_cast<uint32_t>(accountKYCEntry.ext.v());

        auto prep = db.getPreparedStatement(sqlQuery);
        auto& st = prep.statement();

        st.exchange(soci::use(accIdStr, "id"));
        st.exchange(soci::use(accountKYCEntry.KYCData, "data"));
        st.exchange(soci::use(accountKYCFrame->mEntry.lastModifiedLedgerSeq, "lm"));
        st.exchange(soci::use(version, "v"));

        st.define_and_bind();

        auto timer = insert ? db.getInsertTimer("account_kyc") : db.getUpdateTimer("account_kyc");
        st.execute(true);

        if (st.get_affected_rows() != 1)
        {
            throw std::runtime_error("Could not update data in SQL");
        }

        if (insert)
            delta->addEntry(*accountKYCFrame);
        else
            delta->modEntry(*accountKYCFrame);

    }

    LedgerKey AccountKYCHelperImpl::getLedgerKey(LedgerEntry const& from)
    {
        LedgerKey key;
        key.type(from.data.type());
        key.accountKYC().accountID = from.data.accountKYC().accountID;
        return key;
    }

    void AccountKYCHelperImpl::storeAdd(LedgerEntry const &entry)
    {
        storeUpdate(entry, true);
    }

    void AccountKYCHelperImpl::storeChange(LedgerEntry const &entry)
    {
        storeUpdate(entry, false);
    }

    void AccountKYCHelperImpl::storeDelete(LedgerKey const &key)
    {
        Database &db = getDatabase();
        LedgerDelta* delta = getLedgerDelta();
        flushCachedEntry(key);
        std::string sqlQuery = std::string("DELETE FROM account_kyc "
                                           "WHERE accountid=:id ");

        auto prep = db.getPreparedStatement(sqlQuery);
        auto& st = prep.statement();

        std::string accIdStr = PubKeyUtils::toStrKey(key.accountKYC().accountID);
        st.exchange(soci::use(accIdStr, "id"));
        st.define_and_bind();

        auto timer = db.getDeleteTimer("account_kyc");
        st.execute(true);

        delta->deleteEntry(key);
    }

    bool AccountKYCHelperImpl::exists(LedgerKey const &key)
    {
        Database &db = getDatabase();

        if (cachedEntryExists(key) && getCachedEntry(key) != nullptr)
            return true;

        std::string sqlQuery = std::string("SELECT EXISTS (SELECT NULL "
                                           "FROM   account_kyc "
                                           "WHERE  accountid=:id)");
        auto prep = db.getPreparedStatement(sqlQuery);
        auto& st = prep.statement();

        std::string accIdStr = PubKeyUtils::toStrKey(key.accountKYC().accountID);
        int exists = 0;
        st.exchange(soci::use(accIdStr, "id"));
        st.exchange(soci::into(exists));

        st.define_and_bind();
        st.execute(true);

        return exists != 0;
    }

    uint64_t AccountKYCHelperImpl::countObjects()
    {
        uint32_t count = 0;
        Database &db = getDatabase();
        db.getSession() << "SELECT COUNT(*) FROM account_kyc;", soci::into(count);

        return count;
    }

    EntryFrame::pointer AccountKYCHelperImpl::storeLoad(LedgerKey const &ledgerKey)
    {
        return loadAccountKYC(ledgerKey.accountKYC().accountID);
    }

    AccountKYCFrame::pointer AccountKYCHelperImpl::loadAccountKYC(const AccountID &accountID)
    {
        Database &db = getDatabase();
        LedgerKey key;
        key.type(LedgerEntryType::ACCOUNT_KYC);
        key.accountKYC().accountID = accountID;

        if (cachedEntryExists(key))
        {
            auto accountKYCFrame = getCachedEntry(key);
            auto result = accountKYCFrame ? std::make_shared<AccountKYCFrame>(*accountKYCFrame) : nullptr;
            tryRecordEntry(result);
            return result;
        }

        LedgerEntry ledgerEntry;
        ledgerEntry.data.type(LedgerEntryType::ACCOUNT_KYC);
        auto& accountKYC = ledgerEntry.data.accountKYC();
        accountKYC.accountID = accountID;

        std::string sqlQuery = std::string("SELECT kyc_data, lastmodified, version "
                                           "FROM   account_kyc "
                                           "WHERE  accountid=:id");
        auto prep = db.getPreparedStatement(sqlQuery);
        auto& st = prep.statement();

        uint32_t version(0);
        st.exchange(soci::into(accountKYC.KYCData));
        st.exchange(soci::into(ledgerEntry.lastModifiedLedgerSeq));
        st.exchange(soci::into(version));

        std::string accIdStr = PubKeyUtils::toStrKey(accountID);
        st.exchange(soci::use(accIdStr, "id"));

        st.define_and_bind();
        st.execute(true);

        if (!st.got_data())
        {
            putCachedEntry(key, nullptr);
            return nullptr;
        }

        accountKYC.ext.v((LedgerVersion)version);
        auto accountKYCFrame = std::make_shared<AccountKYCFrame>(ledgerEntry);

        auto pEntry = std::make_shared<const LedgerEntry>(ledgerEntry);
        putCachedEntry(key, pEntry);

        return accountKYCFrame;
    }

    EntryFrame::pointer AccountKYCHelperImpl::fromXDR(LedgerEntry const &from)
    {
        return std::make_shared<AccountKYCFrame>(from);
    }

    LedgerDelta *AccountKYCHelperImpl::getLedgerDelta() {
        return mStorageHelper.getLedgerDelta();
    }

    Database &AccountKYCHelperImpl::getDatabase() {
        return mStorageHelper.getDatabase();
    }

    AccountKYCHelperImpl::AccountKYCHelperImpl(StorageHelper &storageHelper)
            : mStorageHelper(storageHelper)
    {
        mAccountKYCHColumnSelector =
                "SELECT code, owner, preissued_asset_signer, "
                "details, max_issuance_amount, "
                "available_for_issueance, issued, pending_issuance, "
                "policies, type, trailing_digits, lastmodified, version "
                "FROM asset ";
    }

}