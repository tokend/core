#include "DataHelperImpl.h"
#include "database/Database.h"
#include "LedgerDelta.h"
#include "StorageHelper.h"

using namespace soci;

namespace stellar
{
DataHelperImpl::DataHelperImpl(StorageHelper& storageHelper)
        : mStorageHelper(storageHelper)
{
    mDataColumnSelector = "select id, type, value, owner, version, lastmodified from data ";
}

void
DataHelperImpl::dropAll()
{
    Database& db = getDatabase();

    db.getSession() << "DROP TABLE IF EXISTS data";

    createIfNotExists();
}

void
DataHelperImpl::createIfNotExists()
{
    Database& db = getDatabase();

    db.getSession() << "CREATE TABLE IF NOT EXISTS data"
                       "("
                       "id           BIGINT NOT NULL PRIMARY KEY,"
                       "type         NUMERIC(20,0) NOT NULL,"
                       "value        text   NOT NULL,"
                       "owner        VARCHAR(56)   NOT NULL,"
                       "version      INT    NOT NULL,"
                       "lastmodified INT    NOT NULL"
                       ");";
}

void
DataHelperImpl::storeUpdate(LedgerEntry const& entry, bool insert)
{
    auto dataFrame = std::make_shared<DataFrame>(entry);
    auto dataEntry = dataFrame->getData();

    dataFrame->touch(mStorageHelper.mustGetLedgerDelta());
    LedgerKey const& key = dataFrame->getKey();
    flushCachedEntry(key);

    auto version = static_cast<int32_t>(dataEntry.ext.v());

    std::string sql;
    if (insert)
    {
        sql = "INSERT INTO data (id, type, value, owner, version, lastmodified) "
              "VALUES (:id, :t, :val, :o, :v, :lm)";
    }
    else
    {
        sql = "UPDATE data SET type = :t, value = :val, owner = :o, version = :v, lastmodified = :lm"
              " WHERE id = :id";
    }

    Database& db = getDatabase();
    auto prep = db.getPreparedStatement(sql);
    auto ownerID = PubKeyUtils::toStrKey(dataEntry.owner);
    statement& st = prep.statement();
    st.exchange(use(dataEntry.id, "id"));
    st.exchange(use(dataEntry.type, "t"));
    st.exchange(use(dataEntry.value, "val"));
    st.exchange(use(ownerID, "o"));
    st.exchange(use(version, "v"));
    st.exchange(use(dataFrame->mEntry.lastModifiedLedgerSeq, "lm"));

    st.define_and_bind();

    auto timer = insert ? db.getInsertTimer("data")
                        : db.getUpdateTimer("data");

    st.execute(true);

    if (st.get_affected_rows() != 1)
    {
        throw std::runtime_error("Could not update data in SQL");
    }
    if (insert)
    {
        mStorageHelper.mustGetLedgerDelta().addEntry(*dataFrame);
    }
    else
    {
        mStorageHelper.mustGetLedgerDelta().modEntry(*dataFrame);
    }
}

void
DataHelperImpl::storeAdd(LedgerEntry const& entry)
{
    storeUpdate(entry, true);
}

void
DataHelperImpl::storeChange(LedgerEntry const& entry)
{
    storeUpdate(entry, false);
}

void
DataHelperImpl::storeDelete(LedgerKey const& key)
{
    flushCachedEntry(key);
    auto id = key.data().id;

    Database& db = getDatabase();
    auto timer = db.getDeleteTimer("data");
    auto prep = db.getPreparedStatement("DELETE FROM data WHERE id = :id");
    auto& st = prep.statement();
    st.exchange(use(id, "id"));
    st.define_and_bind();
    st.execute(true);

    mStorageHelper.mustGetLedgerDelta().deleteEntry(key);
}

bool
DataHelperImpl::exists(LedgerKey const& key)
{
    if (cachedEntryExists(key) && (getCachedEntry(key) != nullptr))
    {
        return true;
    }

    int exists = 0;

    Database& db = getDatabase();
    auto timer = db.getSelectTimer("data");
    auto prep = db.getPreparedStatement("SELECT EXISTS "
                    "(SELECT NULL FROM data WHERE id = :id)");
    auto& st = prep.statement();
    auto id = key.data().id;
    st.exchange(use(id, "id"));
    st.exchange(into(exists));
    st.define_and_bind();
    st.execute(true);

    return exists != 0;
}

LedgerKey
DataHelperImpl::getLedgerKey(LedgerEntry const& entry)
{
    auto dataFrame = std::make_shared<DataFrame>(entry);
    return dataFrame->getKey();
}

EntryFrame::pointer
DataHelperImpl::fromXDR(LedgerEntry const& entry)
{
    return std::make_shared<DataFrame>(entry);
}

uint64_t
DataHelperImpl::countObjects()
{
    session& sess = getDatabase().getSession();
    uint64_t count = 0;
    sess << "SELECT COUNT(*) FROM data;", into(count);

    return count;
}

EntryFrame::pointer
DataHelperImpl::storeLoad(LedgerKey const& key)
{
    return loadData(key.data().id);
}

DataFrame::pointer
DataHelperImpl::loadData(uint64_t const id)
{
    LedgerKey key(LedgerEntryType::DATA);
    key.data().id = id;

    if (cachedEntryExists(key))
    {
        auto p = getCachedEntry(key);
        if (!p)
        {
            return nullptr;
        }

        auto result = std::make_shared<DataFrame>(*p);
        if (getLedgerDelta() != nullptr)
        {
            mStorageHelper.mustGetLedgerDelta().recordEntry(*result);
        }
        return result;
    }

    std::string sql = mDataColumnSelector;
    sql += " where id = :id";

    Database& db = getDatabase();
    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();

    st.exchange(use(id, "id"));
    DataFrame::pointer result;
    load(prep, [&result](LedgerEntry const& entry)
    {
        result = std::make_shared<DataFrame>(entry);
    });

    if (!result)
    {
        putCachedEntry(key, nullptr);
        return nullptr;
    }

    if (getLedgerDelta() != nullptr)
    {
        mStorageHelper.mustGetLedgerDelta().recordEntry(*result);
    }

    auto pEntry = std::make_shared<LedgerEntry>(result->mEntry);
    putCachedEntry(key, pEntry);

    return result;
}

void
DataHelperImpl::load(StatementContext& prep,
                     std::function<void(LedgerEntry const&)> processor)
{
    try
    {
        LedgerEntry le;
        le.data.type(LedgerEntryType::DATA);
        auto& dataEntry = le.data.data();

        int32_t version;

        auto& st = prep.statement();
        st.exchange(into(dataEntry.id));
        st.exchange(into(dataEntry.type));
        st.exchange(into(dataEntry.value));
        st.exchange(into(dataEntry.owner));
        st.exchange(into(version));
        st.exchange(into(le.lastModifiedLedgerSeq));
        st.define_and_bind();
        st.execute(true);

        while (st.got_data())
        {
            dataEntry.ext.v(static_cast<LedgerVersion>(version));

            processor(le);
            st.fetch();
        }
    }
    catch (std::exception& e)
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER) << e.what();
        std::throw_with_nested(std::runtime_error("Failed to load data"));
    }
}

Database&
DataHelperImpl::getDatabase()
{
    return mStorageHelper.getDatabase();
}

LedgerDelta*
DataHelperImpl::getLedgerDelta()
{
    return mStorageHelper.getLedgerDelta();
}
}