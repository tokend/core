#include "VoteHelperImpl.h"
#include "StorageHelper.h"
#include "LedgerDelta.h"
#include "database/Database.h"
#include <lib/xdrpp/xdrpp/marshal.h>
#include <lib/util/basen.h>

using namespace soci;

namespace stellar
{

VoteHelperImpl::VoteHelperImpl(StorageHelper &storageHelper)
        : mStorageHelper(storageHelper)
{
    mVoteColumnSelector = "SELECT poll_id, voter_id, "
                          "choice, version, lastmodified "
                          "FROM votes ";
}

void
VoteHelperImpl::dropAll()
{
    Database& db = getDatabase();

    db.getSession() << "DROP TABLE IF EXISTS votes;";
    db.getSession() << "CREATE TABLE votes"
                   "("
                   "poll_id             BIGINT      NOT NULL CHECK (poll_id > 0),"
                   "voter_id            VARCHAR(56) NOT NULL,"
                   "choice              TEXT        NOT NULL,"
                   "version             INT         NOT NULL,"
                   "lastmodified        INT         NOT NULL,"
                   "PRIMARY KEY (poll_id, voter_id)"
                   ");";
}

void
VoteHelperImpl::storeAdd(LedgerEntry const &entry)
{
    auto voteFrame = std::make_shared<VoteFrame>(entry);
    auto const& voteEntry = voteFrame->getEntry();

    voteFrame->touch(mStorageHelper.mustGetLedgerDelta());

    LedgerKey const& key = voteFrame->getKey();
    flushCachedEntry(key);

    std::string voterIDStr = PubKeyUtils::toStrKey(voteEntry.voterID);
    auto version = static_cast<int32_t>(voteEntry.ext.v());

    auto choiceBytes = xdr::xdr_to_opaque(voteEntry.data);
    std::string strChoice = bn::encode_b64(choiceBytes);

    std::string sql = "INSERT INTO votes (poll_id, voter_id, "
              "choice, version, lastmodified) "
              "VALUES (:pid, :vid, :ch, :v, :lm)";

    Database& db = getDatabase();
    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();

    st.exchange(use(voteEntry.pollID, "pid"));
    st.exchange(use(voterIDStr, "vid"));
    st.exchange(use(strChoice, "ch"));
    st.exchange(use(version, "v"));
    st.exchange(use(voteFrame->mEntry.lastModifiedLedgerSeq, "lm"));

    st.define_and_bind();

    auto timer = db.getInsertTimer("insert-vote");

    st.execute(true);

    if (st.get_affected_rows() != 1) {
        throw std::runtime_error("could not update SQL");
    }

    mStorageHelper.mustGetLedgerDelta().addEntry(*voteFrame);
}

void VoteHelperImpl::storeChange(LedgerEntry const& entry)
{
    throw std::runtime_error("Cannot change vote");
}

void
VoteHelperImpl::storeDelete(LedgerKey const &key)
{
    Database& db = getDatabase();
    auto prep = db.getPreparedStatement("DELETE FROM votes "
                                        "WHERE poll_id = :pid AND voter_id = :vid ");
    auto& st = prep.statement();
    std::string voterIDStr = PubKeyUtils::toStrKey(key.vote().voterID);
    st.exchange(use(voterIDStr, "vid"));
    const uint64_t pollID =  key.vote().pollID;
    st.exchange(use(pollID, "pid"));
    st.define_and_bind();
    {
        auto timer = db.getDeleteTimer("vote");
        st.execute(true);
    }

    if (st.get_affected_rows() != 1)
    {
        throw std::runtime_error("Could not update data in SQL");
    }

    flushCachedEntry(key);
    mStorageHelper.mustGetLedgerDelta().deleteEntry(key);
}

void
VoteHelperImpl::deleteForPoll(uint64_t pollID)
{
    handleDeletedDelta(pollID);

    Database& db = getDatabase();
    std::string sql = "DELETE from votes WHERE poll_id = :pid";

    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();
    st.exchange(use(pollID, "pid"));
    st.define_and_bind();
    st.execute(true);
}
void
VoteHelperImpl::handleDeletedDelta(uint64_t pollID)
{
    Database& db = getDatabase();
    std::string sql = "SELECT voter_id from votes WHERE poll_id = :pid";

    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();
    std::string voterIDStr;
    st.exchange(into(voterIDStr));
    st.exchange(use(pollID, "pid"));
    st.define_and_bind();
    st.execute(true);

    LedgerDelta& delta = mStorageHelper.mustGetLedgerDelta();

    while (st.got_data())
    {
        LedgerKey key(LedgerEntryType::VOTE);
        key.vote().pollID = pollID;
        key.vote().voterID = PubKeyUtils::fromStrKey(voterIDStr);

        flushCachedEntry(key);
        delta.deleteEntry(key);

        st.fetch();
    }
}

bool
VoteHelperImpl::exists(LedgerKey const& key)
{
    if (cachedEntryExists(key) && (getCachedEntry(key) != nullptr))
    {
        return true;
    }

    return exists(key.vote().pollID, key.vote().voterID);
}

bool
VoteHelperImpl::exists(uint64_t const pollID, AccountID voterID)
{
    int exists = 0;
    {
        Database& db = getDatabase();
        auto timer = db.getSelectTimer("vote-exists");
        auto prep = db.getPreparedStatement("SELECT EXISTS (SELECT NULL "
                                            "FROM votes WHERE poll_id = :pid and voter_id = :vid)");
        std::string voterIDStr = PubKeyUtils::toStrKey(voterID);
        auto& st = prep.statement();
        st.exchange(use(pollID, "pid"));
        st.exchange(use(voterIDStr, "vid"));
        st.exchange(into(exists));
        st.define_and_bind();
        st.execute(true);
    }

    return exists != 0;
}

LedgerKey
VoteHelperImpl::getLedgerKey(LedgerEntry const& from)
{
    return fromXDR(from)->getKey();
}

EntryFrame::pointer
VoteHelperImpl::storeLoad(LedgerKey const& key)
{
    return loadVote(key.vote().pollID, key.vote().voterID);
}

EntryFrame::pointer
VoteHelperImpl::fromXDR(LedgerEntry const& from)
{
    return std::make_shared<VoteFrame>(from);
}

uint64_t
VoteHelperImpl::countObjects()
{
    soci::session& sess = getDatabase().getSession();
    uint64_t count = 0;
    sess << "SELECT COUNT(*) FROM votes;", into(count);

    return count;
}

VoteFrame::pointer
VoteHelperImpl::loadVote(uint64_t pollID, AccountID voterID)
{
    LedgerKey key(LedgerEntryType::VOTE);
    key.vote().pollID = pollID;
    key.vote().voterID = voterID;

    if (cachedEntryExists(key))
    {
        auto p = getCachedEntry(key);
        return p ? std::make_shared<VoteFrame>(*p) : nullptr;
    }

    Database& db = getDatabase();
    std::string sql = mVoteColumnSelector;
    sql += " WHERE poll_id = :pid and voter_id = :vid";

    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();

    std::string voterIDStr = PubKeyUtils::toStrKey(voterID);
    st.exchange(use(voterIDStr, "vid"));
    st.exchange(use(pollID, "pid"));

    VoteFrame::pointer result;
    load(prep, [&result](LedgerEntry const& entry)
    {
        result = std::make_shared<VoteFrame>(entry);
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
VoteHelperImpl::load(StatementContext& prep,
                     std::function<void(LedgerEntry const&)> processor)
{
    try
    {
        LedgerEntry le;
        le.data.type(LedgerEntryType::VOTE);
        auto& voteEntry = le.data.vote();

        std::string voterIDStr;
        int32_t version;
        std::string strChoice;

        auto& st = prep.statement();
        st.exchange(into(voteEntry.pollID));
        st.exchange(into(voterIDStr));
        st.exchange(into(strChoice));
        st.exchange(into(version));
        st.exchange(into(le.lastModifiedLedgerSeq));
        st.define_and_bind();
        st.execute(true);

        while (st.got_data())
        {

            std::vector<uint8_t> decoded;
            bn::decode_b64(strChoice, decoded);
            xdr::xdr_get unmarshaler(&decoded.front(), &decoded.back() + 1);
            xdr::xdr_argpack_archive(unmarshaler, voteEntry.data);
            unmarshaler.done();

            voteEntry.voterID = PubKeyUtils::fromStrKey(voterIDStr);
            voteEntry.ext.v(static_cast<LedgerVersion>(version));
            processor(le);
            st.fetch();
        }
    }
    catch (std::exception& e)
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER) << e.what();
        std::throw_with_nested(std::runtime_error("Failed to load vote"));
    }
}

Database&
VoteHelperImpl::getDatabase()
{
    return mStorageHelper.getDatabase();
}

LedgerDelta*
VoteHelperImpl::getLedgerDelta()
{
    return mStorageHelper.getLedgerDelta();
}

std::string const
VoteHelperImpl::getTableName() const
{
    return "votes";
}
}
