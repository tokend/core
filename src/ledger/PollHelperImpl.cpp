#include "PollHelperImpl.h"
#include "StorageHelper.h"
#include "VoteHelper.h"
#include "LedgerDelta.h"
#include "database/Database.h"
#include <lib/xdrpp/xdrpp/marshal.h>
#include <lib/util/basen.h>

using namespace soci;

namespace stellar
{

PollHelperImpl::PollHelperImpl(StorageHelper &storageHelper)
        : mStorageHelper(storageHelper)
{
    mPollColumnSelector = "SELECT id, permission_type, number_of_choices, "
                                 "type, data, start_time, end_time, owner_id, "
                                 "result_provider_id, vote_confirmation_required, "
                                 "details, version, lastmodified "
                          "FROM polls ";
}

void
PollHelperImpl::dropAll()
{
    Database& db = getDatabase();

    db.getSession() << "DROP TABLE IF EXISTS polls;";
    db.getSession() << "CREATE TABLE polls"
                   "("
                   "id                            BIGINT      NOT NULL,"
                   "permission_type               INT         NOT NULL,"
                   "number_of_choices             INT         NOT NULL CHECK (number_of_choices > 0),"
                   "type                          INT         NOT NULL,"
                   "data                          TEXT        NOT NULL,"
                   "start_time                    BIGINT      NOT NULL,"
                   "end_time                      BIGINT      NOT NULL,"
                   "owner_id                      VARCHAR(56) NOT NULL,"
                   "result_provider_id            VARCHAR(56) NOT NULL,"
                   "vote_confirmation_required    BOOLEAN     NOT NULL,"
                   "details                       TEXT        NOT NULL,"
                   "version                       INT         NOT NULL,"
                   "lastmodified                  INT         NOT NULL,"
                   "PRIMARY KEY (id)"
                   ");";
}

void
PollHelperImpl::permissionTypeMigration()
{
    Database& db = getDatabase();

    db.getSession() << "ALTER TABLE polls ALTER permission_type TYPE NUMERIC(10,0);";
    db.getSession() << "ALTER TABLE polls ALTER number_of_choices TYPE NUMERIC(10,0);";
}

void
PollHelperImpl::storeUpdate(LedgerEntry const &entry, bool insert)
{
    auto pollFrame = std::make_shared<PollFrame>(entry);
    auto const& pollEntry = pollFrame->getEntry();

    pollFrame->touch(mStorageHelper.mustGetLedgerDelta());

    LedgerKey const& key = pollFrame->getKey();
    flushCachedEntry(key);

    std::string ownerIDStr = PubKeyUtils::toStrKey(pollEntry.ownerID);
    std::string resultProviderIDStr = PubKeyUtils::toStrKey(pollEntry.resultProviderID);
    int voteConfirmationRequired = pollEntry.voteConfirmationRequired ? 1 : 0;
    auto version = static_cast<int32_t>(pollEntry.ext.v());
    auto type = static_cast<int32_t>(pollEntry.data.type());
    auto permissionType = static_cast<int64_t>(pollEntry.permissionType);
    auto numberOfChoices = static_cast<int64_t>(pollEntry.numberOfChoices);
    auto specBytes = xdr::xdr_to_opaque(pollEntry.data);
    std::string specStr = bn::encode_b64(specBytes);

    std::string sql;
    if (insert)
    {
        sql = "INSERT INTO polls (id, permission_type, number_of_choices, type,"
              "                   data, start_time, end_time, owner_id, "
              "                   result_provider_id, vote_confirmation_required, "
              "                   details, version, lastmodified) "
              "VALUES (:id, :p_t, :n_c, :t, :data, :s_t, :e_t, :o_i, :r_p_i, :v_v_r, :det, :v, :lm)";
    }
    else
    {
        sql = "UPDATE polls SET permission_type = :p_t, number_of_choices = :n_c, "
              " type = :t, data = :data, start_time = :s_t, end_time = :e_t, "
              " owner_id = :o_i, result_provider_id = :r_p_i, vote_confirmation_required = :v_v_r, "
              "details = :det, version = :v, lastmodified = :lm "
              "WHERE id = :id";
    }

    Database& db = getDatabase();
    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();

    st.exchange(use(pollEntry.id, "id"));
    st.exchange(use(permissionType, "p_t"));
    st.exchange(use(numberOfChoices, "n_c"));
    st.exchange(use(type, "t"));
    st.exchange(use(specStr, "data"));
    st.exchange(use(pollEntry.startTime, "s_t"));
    st.exchange(use(pollEntry.endTime, "e_t"));
    st.exchange(use(ownerIDStr, "o_i"));
    st.exchange(use(resultProviderIDStr, "r_p_i"));
    st.exchange(use(voteConfirmationRequired, "v_v_r"));
    st.exchange(use(pollEntry.details, "det"));
    st.exchange(use(version, "v"));
    st.exchange(use(pollFrame->mEntry.lastModifiedLedgerSeq, "lm"));

    st.define_and_bind();

    auto timer = insert ? db.getInsertTimer("insert-poll")
                        : db.getUpdateTimer("update-poll");

    st.execute(true);

    if (st.get_affected_rows() != 1) {
        throw std::runtime_error("could not update SQL");
    }

    if (insert)
    {
        mStorageHelper.mustGetLedgerDelta().addEntry(*pollFrame);
    }
    else
    {
        mStorageHelper.mustGetLedgerDelta().modEntry(*pollFrame);
    }
}

void
PollHelperImpl::storeAdd(LedgerEntry const &entry)
{
    storeUpdate(entry, true);
}

void
PollHelperImpl::storeChange(LedgerEntry const &entry)
{
    storeUpdate(entry, false);
}

void
PollHelperImpl::storeDelete(LedgerKey const &key)
{
    Database& db = getDatabase();
    auto prep = db.getPreparedStatement("DELETE FROM polls WHERE id = :id ");
    auto& st = prep.statement();
    const uint64_t id = key.poll().id;
    st.exchange(use(id, "id"));
    st.define_and_bind();
    {
        auto timer = db.getDeleteTimer("poll");
        st.execute(true);
    }

    if (st.get_affected_rows() != 1)
    {
        throw std::runtime_error("Could not update data in SQL");
    }

    flushCachedEntry(key);

    mStorageHelper.mustGetLedgerDelta().deleteEntry(key);
    mStorageHelper.getVoteHelper().deleteForPoll(key.poll().id);
}

bool
PollHelperImpl::exists(LedgerKey const& key)
{
    if (cachedEntryExists(key) && (getCachedEntry(key) != nullptr))
    {
        return true;
    }

    return exists(key.poll().id);
}

bool
PollHelperImpl::exists(uint64_t const id)
{
    int exists = 0;
    {
        Database& db = getDatabase();
        auto timer = db.getSelectTimer("poll-exists");
        auto prep = db.getPreparedStatement("SELECT EXISTS (SELECT NULL "
                                            "FROM polls WHERE id = :id)");
        auto& st = prep.statement();
        st.exchange(use(id, "id"));
        st.exchange(into(exists));
        st.define_and_bind();
        st.execute(true);
    }

    return exists != 0;
}

LedgerKey
PollHelperImpl::getLedgerKey(LedgerEntry const& from)
{
    return fromXDR(from)->getKey();
}

EntryFrame::pointer
PollHelperImpl::storeLoad(LedgerKey const& key)
{
    return loadPoll(key.poll().id);
}

EntryFrame::pointer
PollHelperImpl::fromXDR(LedgerEntry const& from)
{
    return std::make_shared<PollFrame>(from);
}

uint64_t
PollHelperImpl::countObjects()
{
    soci::session& sess = getDatabase().getSession();
    uint64_t count = 0;
    sess << "SELECT COUNT(*) FROM polls;", into(count);

    return count;
}

PollFrame::pointer
PollHelperImpl::mustLoadPoll(uint64_t const id)
{
    auto poll = loadPoll(id);
    if (poll)
    {
        return poll;
    }

    throw std::runtime_error("Expected poll to exists");
}

PollFrame::pointer
PollHelperImpl::loadPoll(uint64_t const id)
{
    LedgerKey key(LedgerEntryType::POLL);
    key.poll().id = id;

    if (cachedEntryExists(key))
    {
        auto p = getCachedEntry(key);
        return p ? std::make_shared<PollFrame>(*p) : nullptr;
    }

    Database& db = getDatabase();
    std::string sql = mPollColumnSelector;
    sql += " WHERE id = :id ";

    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();
    st.exchange(use(id, "id"));

    PollFrame::pointer result;
    load(prep, [&result](LedgerEntry const& entry)
    {
        result = std::make_shared<PollFrame>(entry);
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
PollHelperImpl::load(StatementContext& prep,
                     std::function<void(LedgerEntry const&)> processor)
{
    try
    {
        LedgerEntry le;
        le.data.type(LedgerEntryType::POLL);
        auto& pollEntry = le.data.poll();

        std::string ownerIDStr, resultProviderIDStr;
        std::string specStr;
        int32_t version;
        int32_t type;
        int64_t permissionType;
        int64_t numberOfChoices;
        int32_t voteConfirmationRequired;

        auto& st = prep.statement();
        st.exchange(into(pollEntry.id));
        st.exchange(into(permissionType));
        st.exchange(into(numberOfChoices));
        st.exchange(into(type));
        st.exchange(into(specStr));
        st.exchange(into(pollEntry.startTime));
        st.exchange(into(pollEntry.endTime));
        st.exchange(into(ownerIDStr));
        st.exchange(into(resultProviderIDStr));
        st.exchange(into(voteConfirmationRequired));
        st.exchange(into(pollEntry.details));
        st.exchange(into(version));
        st.exchange(into(le.lastModifiedLedgerSeq));
        st.define_and_bind();
        st.execute(true);

        while (st.got_data())
        {
            // unmarshal specification
            std::vector<uint8_t> decoded;
            bn::decode_b64(specStr, decoded);
            xdr::xdr_get unmarshaler(&decoded.front(), &decoded.back() + 1);
            xdr::xdr_argpack_archive(unmarshaler, pollEntry.data);
            unmarshaler.done();

            pollEntry.ownerID = PubKeyUtils::fromStrKey(ownerIDStr);
            pollEntry.permissionType = static_cast<uint32_t>(permissionType);
            pollEntry.numberOfChoices = static_cast<uint32_t>(numberOfChoices);
            pollEntry.resultProviderID = PubKeyUtils::fromStrKey(resultProviderIDStr);
            pollEntry.voteConfirmationRequired = voteConfirmationRequired > 0;
            pollEntry.ext.v(static_cast<LedgerVersion>(version));

            auto specType = static_cast<int32_t>(pollEntry.data.type());
            if (specType != type)
            {
                CLOG(ERROR, Logging::ENTRY_LOGGER) << "Unexpected state, specification poll type: "
                                                   << std::to_string(specType)
                                                   << " , poll type: " << std::to_string(type);
                throw std::runtime_error("Unexpected state, specification poll type not equal poll type");
            }

            processor(le);
            st.fetch();
        }
    }
    catch (std::exception& e)
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER) << e.what();
        std::throw_with_nested(std::runtime_error("Failed to load poll"));
    }
}

Database&
PollHelperImpl::getDatabase()
{
    return mStorageHelper.getDatabase();
}

LedgerDelta*
PollHelperImpl::getLedgerDelta()
{
    return mStorageHelper.getLedgerDelta();
}
}
