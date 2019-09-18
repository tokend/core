#include "SwapHelperImpl.h"
#include "LedgerDelta.h"
#include "StorageHelper.h"
#include "database/Database.h"
#include <lib/util/basen.h>
#include <xdrpp/marshal.h>

using namespace soci;

namespace stellar
{

SwapHelperImpl::SwapHelperImpl(StorageHelper& storageHelper)
    : mStorageHelper(storageHelper)
{
    mSwapColumnSelector =
        "SELECT id, secret_hash, source, source_balance, destination_balance, "
        "amount, "
        "created_at, lock_time, fee, details, version "
        "FROM  swap";
}

void
SwapHelperImpl::dropAll()
{
    Database& db = getDatabase();

    db.getSession() << "DROP TABLE IF EXISTS swap;";
    db.getSession()
        << "CREATE TABLE swap"
           "("
           "id                    BIGINT          NOT NULL,"
           "secret_hash           VARCHAR(64)     NOT NULL,"
           "source                VARCHAR(56)     NOT NULL,"
           "source_balance        VARCHAR(56)     NOT NULL,"
           "destination_balance   VARCHAR(56)     NOT NULL,"
           "amount                NUMERIC(20, 0)  NOT NULL,"
           "fee                   NUMERIC(20, 0)  NOT NULL,"
           "lock_time             BIGINT          NOT NULL,"
           "created_at            BIGINT          NOT NULL,"
           "details               TEXT            NOT NULL,"
           "version               INT             NOT NULL    DEFAULT 0,"
           "PRIMARY KEY(id)"
           ");";
}
void
SwapHelperImpl::storeAdd(LedgerEntry const& entry)
{
    auto swapFrame = std::make_shared<SwapFrame>(entry);
    auto swapEntry = swapFrame->getSwapEntry();

    LedgerKey const& key = swapFrame->getKey();
    flushCachedEntry(key);

    int32_t swapVersion =
        static_cast<int32_t>(swapFrame->getSwapEntry().ext.v());
    std::string secretHash = binToHex(swapEntry.secretHash);
    std::string source = PubKeyUtils::toStrKey(swapEntry.source);
    std::string destinationBalance =
        BalanceKeyUtils::toStrKey(swapEntry.destinationBalance);
    std::string sourceBalance = BalanceKeyUtils::toStrKey(swapEntry.sourceBalance);

    std::string sql;

    sql = "INSERT INTO swap (id, secret_hash, source, source_balance,  "
          "destination_balance, amount, fee, lock_time, "
          "created_at, details, version) "
          "VALUES "
          "(:id, :sh, :s, :sb, :db, :am, :f, :lt, :ca, :d, :v)";

    Database& db = getDatabase();
    auto prep = db.getPreparedStatement(sql);

    {
        soci::statement& st = prep.statement();
        st.exchange(use(swapEntry.id, "id"));
        st.exchange(use(secretHash, "sh"));
        st.exchange(use(source, "s"));
        st.exchange(use(sourceBalance, "sb"));
        st.exchange(use(destinationBalance, "db"));
        st.exchange(use(swapEntry.amount, "am"));
        st.exchange(use(swapEntry.fee, "f"));
        st.exchange(use(swapEntry.lockTime, "lt"));
        st.exchange(use(swapEntry.createdAt, "ca"));
        st.exchange(use(swapEntry.details, "d"));
        st.exchange(use(swapVersion, "v"));

        st.define_and_bind();
        {
            auto timer = db.getInsertTimer("swap");
            st.execute(true);
        }

        if (st.get_affected_rows() != 1)
        {
            throw std::runtime_error("Could not update data in SQL");
        }
        mStorageHelper.mustGetLedgerDelta().addEntry(*swapFrame);
    }
}

void
SwapHelperImpl::storeChange(LedgerEntry const& entry)
{
    std::throw_with_nested(std::runtime_error("swap update is not supported"));
}

void
SwapHelperImpl::storeDelete(LedgerKey const& key)
{
    flushCachedEntry(key);

    auto id = key.swap().id;

    {
        Database& db = getDatabase();
        auto timer = db.getDeleteTimer("swap");
        auto prep = db.getPreparedStatement("DELETE FROM swap "
                                            "WHERE       id=:id");
        auto& st = prep.statement();
        st.exchange(soci::use(id, "id"));
        st.define_and_bind();
        st.execute(true);
    }

    mStorageHelper.mustGetLedgerDelta().deleteEntry(key);
}

bool
SwapHelperImpl::exists(LedgerKey const& key)
{
    if (cachedEntryExists(key) && getCachedEntry(key) != nullptr)
    {
        return true;
    }

    return exists(key.swap().id);
}

LedgerKey
SwapHelperImpl::getLedgerKey(LedgerEntry const& from)
{
    LedgerKey ledgerKey(from.data.type());
    ledgerKey.swap().id = from.data.swap().id;

    return ledgerKey;
}

EntryFrame::pointer
SwapHelperImpl::storeLoad(LedgerKey const& key)
{
    return loadSwap(key.swap().id);
}

EntryFrame::pointer
SwapHelperImpl::fromXDR(LedgerEntry const& from)
{
    return std::make_shared<SwapFrame>(from);
}

uint64_t
SwapHelperImpl::countObjects()
{
    soci::session& sess = getDatabase().getSession();
    uint64_t count = 0;
    sess << "SELECT COUNT(*) FROM swap;", into(count);

    return count;
}

SwapFrame::pointer
SwapHelperImpl::loadSwap(uint64_t id)
{
    LedgerKey key;
    key.type(LedgerEntryType::SWAP);
    key.swap().id = id;

    if (cachedEntryExists(key))
    {
        auto p = getCachedEntry(key);
        return p ? std::make_shared<SwapFrame>(*p) : nullptr;
    }

    Database& db = getDatabase();
    std::string sql = mSwapColumnSelector;
    sql += " WHERE id = :id";

    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();
    st.exchange(use(id, "id"));

    SwapFrame::pointer result;
    load(prep, [&result](LedgerEntry const& entry) {
        result = std::make_shared<SwapFrame>(entry);
    });

    if (!result)
    {
        putCachedEntry(key, nullptr);
        return nullptr;
    }

    if (mStorageHelper.getLedgerDelta() != nullptr)
    {
        mStorageHelper.mustGetLedgerDelta().recordEntry(*result);
    }

    auto pEntry = std::make_shared<LedgerEntry>(result->mEntry);
    putCachedEntry(key, pEntry);

    return result;
}

void
SwapHelperImpl::load(StatementContext& prep,
                     std::function<void(LedgerEntry const&)> processor)
{
    try
    {
        LedgerEntry le;
        le.data.type(LedgerEntryType::SWAP);
        auto& swapEntry = le.data.swap();

        int32_t version;
        std::string sourceRaw, sourceBalRaw, destBalRaw, secretHash;

        auto& st = prep.statement();
        st.exchange(into(swapEntry.id));
        st.exchange(into(secretHash));
        st.exchange(into(sourceRaw));
        st.exchange(into(sourceBalRaw));
        st.exchange(into(destBalRaw));
        st.exchange(into(swapEntry.amount));
        st.exchange(into(swapEntry.createdAt));
        st.exchange(into(swapEntry.lockTime));
        st.exchange(into(swapEntry.fee));
        st.exchange(into(swapEntry.details));
        st.exchange(into(version));
        st.define_and_bind();
        st.execute(true);

        while (st.got_data())
        {
            swapEntry.source = PubKeyUtils::fromStrKey(sourceRaw);
            swapEntry.sourceBalance = BalanceKeyUtils::fromStrKey(sourceBalRaw);
            swapEntry.destinationBalance =
                BalanceKeyUtils::fromStrKey(destBalRaw);
            swapEntry.secretHash = hexToBin256(secretHash);

            swapEntry.ext.v(static_cast<LedgerVersion>(version));
            processor(le);
            st.fetch();
        }
    }
    catch (std::exception& e)
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER) << e.what();
        std::throw_with_nested(std::runtime_error("Failed to load swap"));
    }
}

bool
SwapHelperImpl::exists(uint64_t id)
{
    int exists = 0;
    {
        Database& db = getDatabase();
        auto timer = db.getSelectTimer("swap-exists");
        auto prep =
            db.getPreparedStatement("SELECT EXISTS (SELECT NULL FROM swap "
                                    "WHERE id=:id)");
        auto& st = prep.statement();
        st.exchange(use(id));
        st.exchange(into(exists));
        st.define_and_bind();
        st.execute(true);
    }
    return exists != 0;
}

SwapFrame::pointer
SwapHelperImpl::mustLoadSwap(uint64_t id)
{
    auto swapFrame = loadSwap(id);

    if (!swapFrame)
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER) << "Expected swap to exist: " << id;
        throw std::runtime_error("Expected swap to exist");
    }

    return swapFrame;
}

Database&
SwapHelperImpl::getDatabase()
{
    return mStorageHelper.getDatabase();
}

LedgerDelta*
SwapHelperImpl::getLedgerDelta()
{
    return mStorageHelper.getLedgerDelta();
}
}
