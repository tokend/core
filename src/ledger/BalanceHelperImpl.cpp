#include "BalanceHelperImpl.h"
#include "ledger/LedgerDelta.h"
#include "ledger/StorageHelper.h"
#include "database/Database.h"
#include "AssetHelper.h"

using namespace soci;
using namespace std;

namespace stellar
{

using xdr::operator<;

static const char* balanceColumnSelector =
        "SELECT balance.balance_id, balance.asset, balance.amount, balance.locked, "
        "balance.account_id, asset.trailing_digits, balance.lastmodified, "
        "balance.version, asset.version, balance.sequential_id "
        "FROM balance INNER JOIN asset ON asset.code = balance.asset";

BalanceHelperImpl::BalanceHelperImpl(StorageHelper& storageHelper)
        : mStorageHelper(storageHelper)
{
    mTableName = "balance";
}

void
BalanceHelperImpl::dropAll()
{
    Database& db = mStorageHelper.getDatabase();

    db.getSession() << "DROP TABLE IF EXISTS balance;";
    db.getSession() << "CREATE TABLE balance"
           "("
           "balance_id               VARCHAR(56) NOT NULL,"
           "account_id               VARCHAR(56) NOT NULL,"
           "asset                    VARCHAR(16) NOT NULL,"
           "amount                   BIGINT      NOT NULL CHECK (amount >= 0),"
           "locked                   BIGINT      NOT NULL CHECK (locked >= 0),"
           "lastmodified             INT         NOT NULL, "
           "version                  INT         NOT NULL DEFAULT 0,"
           "sequential_id            BIGINT      UNIQUE NOT NULL,"
           "PRIMARY KEY (balance_id)"
           ");";
}

void
BalanceHelperImpl::storeAdd(LedgerEntry const& entry)
{
    storeUpdateHelper(true, entry);
}

void
BalanceHelperImpl::storeChange(LedgerEntry const& entry)
{
    storeUpdateHelper(false, entry);
}

void
BalanceHelperImpl::storeDelete(LedgerKey const& key)
{
    flushCachedEntry(key);

    Database& db = getDatabase();
    auto timer = db.getDeleteTimer("delete-balance");
    auto prep =
            db.getPreparedStatement("DELETE FROM balance WHERE balance_id=:id");
    auto& st = prep.statement();
    auto balanceIDStr = BalanceKeyUtils::toStrKey(key.balance().balanceID);
    st.exchange(use(balanceIDStr, "id"));
    st.define_and_bind();
    st.execute(true);
    mStorageHelper.getLedgerDelta()->deleteEntry(key);
}

bool
BalanceHelperImpl::exists(LedgerKey const& key)
{
    // if (cached entry == nullptr) entry does not exists
    if (cachedEntryExists(key) && getCachedEntry(key))
    {
        return true;
    }
    int exists = 0;

    Database& db = getDatabase();
    auto timer = db.getSelectTimer("balance-exists");
    auto prep = db.getPreparedStatement("SELECT EXISTS "
                        "(SELECT NULL FROM balance WHERE balance_id=:id)");
    auto& st = prep.statement();
    auto balanceIDStr = BalanceKeyUtils::toStrKey(key.balance().balanceID);
    st.exchange(use(balanceIDStr, "id"));
    st.exchange(into(exists));
    st.define_and_bind();
    st.execute(true);

    return exists != 0;
}

bool
BalanceHelperImpl::exists(BalanceID balanceID)
{
    int exists = 0;
    Database& db = getDatabase();
    auto timer = db.getSelectTimer("balance-exists");
    auto prep =
            db.getPreparedStatement("SELECT EXISTS (SELECT NULL FROM balance WHERE balance_id=:id)");
    auto balIDStrKey = BalanceKeyUtils::toStrKey(balanceID);
    auto& st = prep.statement();
    st.exchange(use(balIDStrKey));
    st.exchange(into(exists));
    st.define_and_bind();
    st.execute(true);
    return exists != 0;
}

void
BalanceHelperImpl::storeUpdateHelper(bool insert, LedgerEntry const& entry)
{
    Database& db = getDatabase();
    LedgerDelta* delta = mStorageHelper.getLedgerDelta();

    auto balanceFrame = make_shared<BalanceFrame>(entry);
    auto balanceEntry = balanceFrame->getBalance();

    if (delta)
    {
        balanceFrame->touch(*delta);
    }
    putCachedEntry(getLedgerKey(entry), make_shared<LedgerEntry>(entry));

    if (!balanceFrame->isValid())
    {
        throw std::runtime_error("Invalid balance");
    }
    if (!mStorageHelper.getAssetHelper().doesAmountFitAssetPrecision(
            balanceEntry.asset, balanceEntry.amount))
    {
        throw std::runtime_error("Invalid balance amount");
    }

    std::string accountID = PubKeyUtils::toStrKey(balanceFrame->getAccountID());
    std::string balanceID =
            BalanceKeyUtils::toStrKey(balanceFrame->getBalanceID());
    std::string asset = balanceFrame->getAsset();
    int32_t version = static_cast<int32_t>(balanceEntry.ext.v());

    string sql;

    if (insert)
    {
        sql = "INSERT INTO balance (balance_id, asset, amount, locked, "
              "                     account_id, lastmodified, version, sequential_id) "
              "VALUES (:id, :as, :am, :ld, :aid, :lm, :v, :seqid)";
    }
    else
    {
        sql = "UPDATE balance "
              "SET    asset = :as, amount=:am, locked=:ld, account_id=:aid, "
              "lastmodified=:lm, version=:v, sequential_id = :seqid "
              "WHERE  balance_id = :id";
    }

    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();

    st.exchange(use(balanceID, "id"));
    st.exchange(use(asset, "as"));
    st.exchange(use(balanceEntry.amount, "am"));
    st.exchange(use(balanceEntry.locked, "ld"));
    st.exchange(use(accountID, "aid"));
    st.exchange(use(balanceFrame->mEntry.lastModifiedLedgerSeq, "lm"));
    st.exchange(use(version, "v"));
    st.exchange(use(balanceEntry.sequentialID, "seqid"));
    st.define_and_bind();

    auto timer = insert ? db.getInsertTimer("insert-balance")
                        : db.getUpdateTimer("update-balance");
    st.execute(true);

    if (st.get_affected_rows() != 1)
    {
        throw std::runtime_error("could not update SQL");
    }

    if (delta)
    {
        if (insert)
        {
            delta->addEntry(*balanceFrame);
        }
        else
        {
            delta->modEntry(*balanceFrame);
        }
    }
}

LedgerKey
BalanceHelperImpl::getLedgerKey(LedgerEntry const& from)
{
    LedgerKey ledgerKey;
    ledgerKey.type(from.data.type());
    ledgerKey.balance().balanceID = from.data.balance().balanceID;
    return ledgerKey;
}

EntryFrame::pointer
BalanceHelperImpl::storeLoad(LedgerKey const& key)
{
    return loadBalance(key.balance().balanceID);
}

EntryFrame::pointer
BalanceHelperImpl::fromXDR(LedgerEntry const& from)
{
    return std::make_shared<BalanceFrame>(from);
}

uint64_t
BalanceHelperImpl::countObjects()
{
    uint64_t count = 0;
    getDatabase().getSession() << "SELECT COUNT(*) FROM balance;", into(count);
    return count;
}

BalanceFrame::pointer
BalanceHelperImpl::mustLoadBalance(BalanceID balanceID)
{
    auto result = loadBalance(balanceID);
    if (result)
    {
        return result;
    }

    CLOG(ERROR, Logging::ENTRY_LOGGER) << "Expected balance to exist: "
                                       << BalanceKeyUtils::toStrKey(balanceID);
    throw std::runtime_error("Expected balance to exist");
}

BalanceFrame::pointer
BalanceHelperImpl::loadBalance(BalanceID balanceID)
{
    LedgerKey key;
    key.type(LedgerEntryType::BALANCE);
    key.balance().balanceID = balanceID;
    if (cachedEntryExists(key))
    {
        auto entry = getCachedEntry(key);
        if (!entry)
        {
            return nullptr;
        }
        auto asset = mStorageHelper.getAssetHelper().mustLoadAsset(entry->data.balance().asset);
        auto balanceFrame = std::make_shared<BalanceFrame>(*entry);
        balanceFrame->setPrecisionForAmounts(
                AssetFrame::kMaximumTrailingDigits - asset->getTrailingDigitsCount());
        if (mStorageHelper.getLedgerDelta())
        {
            mStorageHelper.getLedgerDelta()->recordEntry(*balanceFrame);
        }
        return balanceFrame;
    }

    Database& db = getDatabase();

    auto balIDStrKey = BalanceKeyUtils::toStrKey(balanceID);

    std::string sql = balanceColumnSelector;
    sql += " WHERE balance_id = :id";
    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();
    st.exchange(use(balIDStrKey));

    auto timer = db.getSelectTimer("load-balance");
    BalanceFrame::pointer retBalance;
    loadBalances(prep, [&retBalance](BalanceFrame::pointer const& framePtr)
    {
        retBalance = framePtr;
    });

    if (!retBalance)
    {
        putCachedEntry(key, nullptr);
        return nullptr;
    }
    putCachedEntry(key, make_shared<LedgerEntry>(retBalance->mEntry));

    return retBalance;
}

BalanceFrame::pointer
BalanceHelperImpl::loadBalance(BalanceID balanceID, AccountID accountID)
{
    auto balanceFrame = loadBalance(balanceID);
    if (!balanceFrame)
    {
        return nullptr;
    }

    if (balanceFrame->getAccountID() == accountID)
    {
        return balanceFrame;
    }

    return nullptr;
}

BalanceFrame::pointer
BalanceHelperImpl::loadBalance(AccountID accountID, AssetCode assetCode)
{
    Database& db = getDatabase();

    string accountIDStr = PubKeyUtils::toStrKey(accountID);

    string sql = balanceColumnSelector;
    sql += " WHERE asset = :asset AND account_id = :acc_id";

    auto prep = db.getPreparedStatement(sql);
    auto &st = prep.statement();
    st.exchange(use(assetCode, "asset"));
    st.exchange(use(accountIDStr, "acc_id"));

    auto timer = db.getSelectTimer("load-balances");

    BalanceFrame::pointer retBalance;
    loadBalances(prep, [&retBalance](BalanceFrame::pointer const& framePtr)
    {
        retBalance = framePtr;
    });

    if (!retBalance)
    {
        return nullptr;
    }

    putCachedEntry(retBalance->getKey(),
                   make_shared<LedgerEntry>(retBalance->mEntry));

    return retBalance;
}

void
BalanceHelperImpl::loadBalances(AccountID const& accountID,
                                std::vector<BalanceFrame::pointer>& retBalances)
{
    std::string actIDStrKey;
    actIDStrKey = PubKeyUtils::toStrKey(accountID);

    std::string sql = balanceColumnSelector;
    sql += " WHERE account_id = :account_id";
    auto prep = getDatabase().getPreparedStatement(sql);
    auto& st = prep.statement();
    st.exchange(use(actIDStrKey));

    auto timer = getDatabase().getSelectTimer("balance");
    loadBalances(prep, [&retBalances](BalanceFrame::pointer const& balanceFrame)
    {
        retBalances.push_back(balanceFrame);
    });
}

vector<BalanceFrame::pointer>
BalanceHelperImpl::loadBalances(AccountID accountID, AssetCode assetCode)
{
    Database& db = getDatabase();

    string accountIDStr = PubKeyUtils::toStrKey(accountID);

    string sql = balanceColumnSelector;
    sql += " WHERE asset = :asset AND account_id = :acc_id";

    auto prep = db.getPreparedStatement(sql);
    auto &st = prep.statement();
    st.exchange(use(assetCode, "asset"));
    st.exchange(use(accountIDStr, "acc_id"));

    auto timer = db.getSelectTimer("load-balances");

    std::vector<BalanceFrame::pointer> retBalances;
    loadBalances(prep, [&retBalances](BalanceFrame::pointer const& framePtr)
    {
        retBalances.push_back(framePtr);
    });

    return retBalances;
}

vector<BalanceFrame::pointer>
BalanceHelperImpl::loadBalances(vector<AccountID> accountIDs,
                                AssetCode assetCode)
{
    if (accountIDs.empty())
    {
        return vector<BalanceFrame::pointer>{};
    }

    Database& db = getDatabase();

    string sql = "SELECT DISTINCT ON (balance.account_id) "
                 "balance.balance_id, balance.asset, balance.amount, "
                 "balance.locked, balance.account_id, asset.trailing_digits, "
                 "balance.lastmodified, balance.version, asset.version, balance.sequential_id "
                 "FROM balance INNER JOIN asset ON balance.asset = "
                 "asset.code "
                 "WHERE balance.asset = :asset AND balance.account_id IN (" +
                 obtainStrAccountIDs(accountIDs) + ")";

    auto prep = db.getPreparedStatement(sql);
    auto &st = prep.statement();
    st.exchange(use(assetCode, "asset"));

    auto timer = db.getSelectTimer("load-balances");

    vector<BalanceFrame::pointer> result;
    loadBalances(prep, [&result](BalanceFrame::pointer const& framePtr)
    {
        result.push_back(framePtr);
    });

    return result;
}

void
BalanceHelperImpl::loadBalances(StatementContext& prep,
                   function<void(BalanceFrame::pointer const&)> balanceProcessor)
{
    LedgerEntry le;
    le.data.type(LedgerEntryType::BALANCE);
    BalanceEntry& oe = le.data.balance();

    int32 balanceVersion = 0;
    int32 assetVersion = 0;
    int trailingDigits = 0;
    string accountID, balanceID, asset;

    statement& st = prep.statement();
    st.exchange(into(balanceID));
    st.exchange(into(asset));
    st.exchange(into(oe.amount));
    st.exchange(into(oe.locked));
    st.exchange(into(accountID));
    st.exchange(into(trailingDigits));
    st.exchange(into(le.lastModifiedLedgerSeq));
    st.exchange(into(balanceVersion));
    st.exchange(into(assetVersion));
    st.exchange(into(oe.sequentialID));
    st.define_and_bind();
    st.execute(true);
    while (st.got_data())
    {
        oe.accountID = PubKeyUtils::fromStrKey(accountID);
        oe.balanceID = BalanceKeyUtils::fromStrKey(balanceID);
        oe.asset = asset;
        oe.ext.v(static_cast<LedgerVersion>(balanceVersion));

        bool isValid = BalanceFrame::isValid(oe);
        if (!isValid)
        {
            throw std::runtime_error("Invalid balance from database");
        }

        auto balanceFrame = std::make_shared<BalanceFrame>(le);
        balanceFrame->setPrecisionForAmounts(AssetFrame::kMaximumTrailingDigits - trailingDigits);


        if (mStorageHelper.getLedgerDelta())
        {
            mStorageHelper.getLedgerDelta()->recordEntry(*balanceFrame);
        }

        balanceProcessor(balanceFrame);
        st.fetch();
    }
}

vector<BalanceFrame::pointer>
BalanceHelperImpl::loadAssetHolders(AssetCode assetCode, AccountID owner,
                                    uint64_t minTotalAmount)
{
    Database& db = getDatabase();

    std::string ownerIDStr = PubKeyUtils::toStrKey(owner);

    std::string sql = balanceColumnSelector;
    sql += " WHERE asset = :asset AND account_id != :owner AND"
           " amount + locked >= :min_tot";

    auto prep = db.getPreparedStatement(sql);
    auto &st = prep.statement();
    st.exchange(use(assetCode, "asset"));
    st.exchange(use(ownerIDStr, "owner"));
    st.exchange(use(minTotalAmount, "min_tot"));

    auto timer = db.getSelectTimer("balance");

    std::vector<BalanceFrame::pointer> holders;
    loadBalances(prep, [&holders](BalanceFrame::pointer const& framePtr)
    {
        if (framePtr->getTotal() > 0)
        {
            holders.push_back(framePtr);
        }
    });

    return holders;
}

Database&
BalanceHelperImpl::getDatabase()
{
    return mStorageHelper.getDatabase();
}

LedgerDelta*
BalanceHelperImpl::getLedgerDelta()
{
    return mStorageHelper.getLedgerDelta();
}

string
BalanceHelperImpl::obtainStrAccountIDs(vector<AccountID> accountIDs)
{
    string result = "'";

    for (auto accountID : accountIDs)
    {
        result += PubKeyUtils::toStrKey(accountID);
        result += "', '";
    }

    return result.substr(0, result.size() - 3);
}

std::string const
BalanceHelperImpl::getTableName() const
{
    return mTableName;
}
} // namespace stellar

