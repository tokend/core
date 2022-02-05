#include "LiquidityPoolHelperImpl.h"

#include <database/Database.h>
#include <ledger/LedgerDelta.h>

using namespace soci;

namespace stellar
{
    using xdr::operator<;

    void LiquidityPoolHelperImpl::dropAll()
    {
        Database& db = getDatabase();
        db.getSession() << "DROP TABLE IF EXISTS liquidity_pool;";
        db.getSession() << "CREATE TABLE IF NOT EXISTS liquidity_pool"
                           "("
                           "id             BIGINT NOT NULL PRIMARY KEY CHECK (id >= 0),"
                           "account        CHAR(56) NOT NULL,"
                           "token_asset    VARCHAR(16) NOT NULL,"
                           "first_balance  CHAR(56) NOT NULL,"
                           "second_balance CHAR(56) NOT NULL,"
                           "tokens_amount  NUMERIC(20, 0) NOT NULL,"
                           "first_reserve  NUMERIC(20, 0) NOT NULL,"
                           "second_reserve NUMERIC(20, 0) NOT NULL"
                           ");";
    }

    void LiquidityPoolHelperImpl::storeAdd(const LedgerEntry& entry)
    {
        storeUpdateHelper(true, entry);
    }

    void LiquidityPoolHelperImpl::storeChange(const LedgerEntry& entry)
    {
        storeUpdateHelper(false, entry);
    }

    void LiquidityPoolHelperImpl::storeDelete(const LedgerKey& key)
    {
        Database& db = getDatabase();
        LedgerDelta* delta = getLedgerDelta();
        flushCachedEntry(key);
        auto timer = db.getDeleteTimer("liquidity_pool");
        auto prep = db.getPreparedStatement("DELETE FROM liquidity_pool WHERE id = :id");
        auto& st = prep.statement();
        st.exchange(use(key.liquidityPool().id, "id"));
        st.define_and_bind();
        st.execute(true);
        delta->deleteEntry(key);
    }

    bool LiquidityPoolHelperImpl::exists(uint64_t poolID)
    {
        Database& db = getDatabase();
        int exists = 0;
        auto timer = db.getSelectTimer("liquidity_pool_exists");

        auto prep = db.getPreparedStatement(
            "SELECT EXISTS ( "
            "SELECT NULL FROM liquidity_pool lp "
            "WHERE lp.id = :id"
            ")"
        );
        auto& st = prep.statement();
        st.exchange(use(poolID, "id"));
        st.exchange(into(exists));
        st.define_and_bind();
        st.execute(true);

        return exists != 0;
    }

    bool LiquidityPoolHelperImpl::exists(const LedgerKey& key)
    {
        return exists(key.liquidityPool().id);
    }

    bool LiquidityPoolHelperImpl::exists(const AssetCode& lpTokenAsset)
    {
        Database& db = getDatabase();
        int exists = 0;
        auto timer = db.getSelectTimer("liquidity_pool_exists");

        auto prep = db.getPreparedStatement(
            "SELECT EXISTS ( "
            "SELECT NULL FROM liquidity_pool lp "
            "WHERE lp.token_asset = :token_asset"
            ")"
        );
        auto& st = prep.statement();

        std::string lpTokenAssetCode = lpTokenAsset;
        st.exchange(use(lpTokenAssetCode, "token_asset"));
        st.exchange(into(exists));
        st.define_and_bind();
        st.execute(true);

        return exists != 0;
    }

    bool LiquidityPoolHelperImpl::exists(const AssetCode& firstAsset, const AssetCode& secondAsset)
    {
        auto lpTokenAsset = LiquidityPoolFrame::calculateLPTokenAssetCode(firstAsset, secondAsset);
        return exists(lpTokenAsset);
    }

    LedgerKey LiquidityPoolHelperImpl::getLedgerKey(const LedgerEntry& from)
    {
        LedgerKey ledgerKey;
        ledgerKey.type(from.data.type());
        ledgerKey.liquidityPool().id = from.data.liquidityPool().id;

        return ledgerKey;
    }

    EntryFrame::pointer LiquidityPoolHelperImpl::fromXDR(const LedgerEntry& from)
    {
        return std::make_shared<LiquidityPoolFrame>(from);
    }

    uint64_t LiquidityPoolHelperImpl::countObjects()
    {
        Database& db = getDatabase();
        uint64_t count = 0;

        db.getSession() << "SELECT COUNT(*) FROM liquidity_pool;", into(count);

        return count;
    }

    void LiquidityPoolHelperImpl::storeUpdateHelper(bool insert, const LedgerEntry& entry)
    {
        Database& db = getDatabase();
        auto lpFrame = std::make_shared<LiquidityPoolFrame>(entry);
        lpFrame->touch(mStorageHelper.mustGetLedgerDelta());
        lpFrame->ensureValid();

        flushCachedEntry(getLedgerKey(entry));

        std::string sql;

        if (insert)
        {
            sql =
                "INSERT INTO liquidity_pool (id, account, token_asset, first_balance, second_balance, tokens_amount, "
                "   first_reserve, second_reserve) "
                "VALUES (:id, :account, :token_asset, :first_balance, :second_balance, :tokens_amount, :first_reserve, "
                "   :second_reserve)";
        }
        else
        {
            sql =
                "UPDATE liquidity_pool SET id = :id, account = :account, token_asset = :token_asset, "
                "   first_balance = :first_balance, second_balance = :second_balance, tokens_amount = :tokens_amount, "
                "   first_reserve = :first_reserve, second_reserve = :second_reserve "
                "WHERE id = :id";
        }

        auto prep = db.getPreparedStatement(sql);
        auto& st = prep.statement();

        auto lpEntry = lpFrame->getLiquidityPoolEntry();

        std::string accountID = PubKeyUtils::toStrKey(lpFrame->getAccountID());
        std::string lpAsset = lpFrame->getLpTokenAsset();
        std::string firstBalance = BalanceKeyUtils::toStrKey(lpEntry.firstAssetBalance);
        std::string secondBalance = BalanceKeyUtils::toStrKey(lpEntry.secondAssetBalance);

        st.exchange(use(lpEntry.id, "id"));
        st.exchange(use(accountID, "account"));
        st.exchange(use(lpAsset, "token_asset"));
        st.exchange(use(firstBalance, "first_balance"));
        st.exchange(use(secondBalance, "second_balance"));
        st.exchange(use(lpEntry.lpTokensTotalCap, "tokens_amount"));
        st.exchange(use(lpEntry.firstReserve, "first_reserve"));
        st.exchange(use(lpEntry.secondReserve, "second_reserve"));
        st.define_and_bind();

        auto times = insert
                     ? db.getInsertTimer("liquidity_pool")
                     : db.getUpdateTimer("liquidity_pool");
        st.execute(true);

        if (st.get_affected_rows() != 1)
        {
            CLOG(ERROR, Logging::ENTRY_LOGGER) << "Failed to update liquidity_pool with id: " << lpEntry.id;
            throw std::runtime_error("Failed to update liquidity_pool");
        }

        auto delta = getLedgerDelta();

        if (insert)
        {
            delta->addEntry(*lpFrame);
        }
        else
        {
            delta->modEntry(*lpFrame);
        }
    }

    LiquidityPoolFrame::pointer LiquidityPoolHelperImpl::loadPool(uint64_t poolID)
    {
        LedgerKey key;
        LedgerDelta* delta = getLedgerDelta();
        key.type(LedgerEntryType::LIQUIDITY_POOL);
        key.liquidityPool().id = poolID;
        if (cachedEntryExists(key))
        {
            const auto entryPtr = getCachedEntry(key);
            auto res = entryPtr ? std::make_shared<LiquidityPoolFrame>(*entryPtr) : nullptr;

            if (!!delta && !!res)
            {
                delta->recordEntry(*res);
            }

            return res;
        }

        Database& db = getDatabase();

        std::string sql = mLPColumnSelector;
        sql += +" WHERE id = :id";

        auto prep = db.getPreparedStatement(sql);
        auto& st = prep.statement();
        st.exchange(use(poolID, "id"));

        LiquidityPoolFrame::pointer retLP;

        auto timer = db.getSelectTimer("liquidity_pool");
        loadPools(prep, [&retLP](LedgerEntry const& entry) -> void
        {
            retLP = std::make_shared<LiquidityPoolFrame>(entry);
        });

        if (!retLP)
        {
            putCachedEntry(key, nullptr);
            return nullptr;
        }

        if (delta)
        {
            delta->recordEntry(*retLP);
        }

        const auto entryPtr = std::make_shared<LedgerEntry>(retLP->mEntry);
        putCachedEntry(key, entryPtr);

        return retLP;
    }

    LiquidityPoolFrame::pointer LiquidityPoolHelperImpl::loadPool(AssetCode const& lpTokenAsset)
    {
        Database& db = getDatabase();

        std::string sql = mLPColumnSelector;
        sql += +"WHERE lp.token_asset = :tokenAsset";
        auto prep = db.getPreparedStatement(sql);
        auto& st = prep.statement();

        std::string tokenAsset = lpTokenAsset;
        st.exchange(use(tokenAsset, "tokenAsset"));

        LiquidityPoolFrame::pointer retLP;

        auto timer = db.getSelectTimer("liquidity_pool_with_assets");
        loadPools(prep, [&retLP](LedgerEntry const& entry) -> void
        {
            retLP = std::make_shared<LiquidityPoolFrame>(entry);
        });

        return retLP;
    }

    void LiquidityPoolHelperImpl::loadPools(StatementContext& prep,
        const std::function<void(LedgerEntry const&)>& lpProcessor) const
    {
        try
        {
            LedgerEntry le;
            le.data.type(LedgerEntryType::LIQUIDITY_POOL);
            auto& lp = le.data.liquidityPool();

            statement& st = prep.statement();
            st.exchange(into(lp.id));
            st.exchange(into(lp.liquidityPoolAccount));
            st.exchange(into(lp.lpTokenAssetCode));
            st.exchange(into(lp.firstAssetBalance));
            st.exchange(into(lp.secondAssetBalance));
            st.exchange(into(lp.lpTokensTotalCap));
            st.exchange(into(lp.firstReserve));
            st.exchange(into(lp.secondReserve));

            st.define_and_bind();
            st.execute(true);

            while (st.got_data())
            {
                LiquidityPoolFrame::ensureValid(lp);

                lpProcessor(le);

                st.fetch();
            }
        }
        catch (...)
        {
            std::throw_with_nested(std::runtime_error("Failed to load liquidity pool data"));
        }
    }

    EntryFrame::pointer LiquidityPoolHelperImpl::storeLoad(LedgerKey const& ledgerKey)
    {
        return loadPool(ledgerKey.liquidityPool().id);
    }

    LedgerDelta* LiquidityPoolHelperImpl::getLedgerDelta()
    {
        return mStorageHelper.getLedgerDelta();
    }

    Database& LiquidityPoolHelperImpl::getDatabase()
    {
        return mStorageHelper.getDatabase();
    }

    LiquidityPoolHelperImpl::LiquidityPoolHelperImpl(StorageHelper& storageHelper) : mStorageHelper(storageHelper)
    {
        mLPColumnSelector = "SELECT id, account, token_asset, first_balance, second_balance, tokens_amount, "
                            "   first_reserve, second_reserve "
                            "FROM liquidity_pool lp ";
    }

}
