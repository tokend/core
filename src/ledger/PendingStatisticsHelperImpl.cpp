#include <database/Database.h>
#include "PendingStatisticsHelperImpl.h"
#include "LedgerDelta.h"
#include "PendingStatisticsFrame.h"

using namespace std;
using namespace soci;

namespace stellar
{

    const char* pendingStatisticsSelector = "SELECT statistics_id, request_id, amount, lastmodified, version "
                                            "FROM   pending_statistics ";

    void PendingStatisticsHelperImpl::dropAll()
    {
        Database& db = getDatabase();
        db.getSession() << "DROP TABLE IF EXISTS pending_statistics;";
        db.getSession() << "CREATE TABLE pending_statistics"
                           "("
                           "statistics_id       BIGINT          NOT NULL,"
                           "request_id          BIGINT          NOT NULL,"
                           "amount              NUMERIC(20,0)   NOT NULL,"
                           "lastmodified        INT             NOT NULL,"
                           "version             INT             NOT NULL DEFAULT 0,"
                           "PRIMARY KEY (request_id, statistics_id),"
                           "FOREIGN KEY (statistics_id) REFERENCES statistics_v2(id) on delete cascade on update cascade,"
                           "FOREIGN KEY (request_id) REFERENCES reviewable_request(id) on delete cascade on update cascade"
                           ");";
    }


    void PendingStatisticsHelperImpl::restrictUpdateDelete() {
        Database& db = getDatabase();
        db.getSession() << "ALTER TABLE pending_statistics "
                           "DROP CONSTRAINT pending_statistics_request_id_fkey";
        db.getSession() << "ALTER TABLE pending_statistics "
                           "ADD CONSTRAINT pending_statistics_request_id_fkey FOREIGN KEY (request_id) REFERENCES reviewable_request(id) on delete restrict on update cascade;";
    }


    void PendingStatisticsHelperImpl::storeAdd(LedgerEntry const &entry)
    {
        storeUpdateHelper(true, entry);
    }

    void PendingStatisticsHelperImpl::storeChange(LedgerEntry const &entry)
    {
        storeUpdateHelper(false, entry);
    }

    void PendingStatisticsHelperImpl::storeDelete(LedgerKey const &key)
    {
        Database& db = getDatabase();
        LedgerDelta* delta = getLedgerDelta();
        auto timer = db.getDeleteTimer("delete_pending_statistics");
        auto prep = db.getPreparedStatement("DELETE FROM pending_statistics "
                                            "WHERE statistics_id = :stats_id AND request_id = :req_id");

        auto& st = prep.statement();
        uint64_t statisticsID = key.pendingStatistics().statisticsID;
        uint64_t requestID = key.pendingStatistics().requestID;
        st.exchange(use(statisticsID, "stats_id"));
        st.exchange(use(requestID, "req_id"));
        st.define_and_bind();
        st.execute(true);
        delta->deleteEntry(key);
    }

    bool PendingStatisticsHelperImpl::exists(LedgerKey const &key)
    {
        Database& db = getDatabase();
        int exists = 0;
        auto timer = db.getSelectTimer("pending_statistics_exists");
        auto prep = db.getPreparedStatement("SELECT EXISTS (SELECT NULL FROM pending_statistics "
                                            "WHERE statistics_id = :stats_id AND request_id = :req_id)");
        auto &st = prep.statement();
        uint64_t statisticsID = key.pendingStatistics().statisticsID;
        uint64_t requestID = key.pendingStatistics().requestID;
        st.exchange(use(statisticsID, "stats_id"));
        st.exchange(use(requestID, "req_id"));
        st.exchange(into(exists));
        st.define_and_bind();
        st.execute(true);
        return exists != 0;
    }

    LedgerKey PendingStatisticsHelperImpl::getLedgerKey(LedgerEntry const &from)
    {
        LedgerKey ledgerKey;
        ledgerKey.type(from.data.type());
        ledgerKey.pendingStatistics().statisticsID = from.data.pendingStatistics().statisticsID;
        ledgerKey.pendingStatistics().requestID = from.data.pendingStatistics().requestID;
        return ledgerKey;
    }

    EntryFrame::pointer
    PendingStatisticsHelperImpl::storeLoad(LedgerKey const &key)
    {
        uint64_t statisticsID = key.pendingStatistics().statisticsID;
        uint64_t requestID = key.pendingStatistics().requestID;
        return loadPendingStatistics(requestID, statisticsID);
    }

    EntryFrame::pointer
    PendingStatisticsHelperImpl::fromXDR(LedgerEntry const &from)
    {
        return std::make_shared<PendingStatisticsFrame>(from);
    }

    uint64_t
    PendingStatisticsHelperImpl::countObjects()
    {
        uint64_t count = 0;
        getDatabase().getSession() << "SELECT COUNT(*) FROM pending_statistics;", into(count);
        return count;
    }

    void PendingStatisticsHelperImpl::storeUpdateHelper(bool insert, const LedgerEntry &entry)
    {
        auto pendingStatisticsFrame = make_shared<PendingStatisticsFrame>(entry);
        auto pendingStatisticsEntry = pendingStatisticsFrame->getPendingStatistics();

        pendingStatisticsFrame->touch(mStorageHelper.mustGetLedgerDelta());

        auto pendingStatsVersion = static_cast<int32_t>(pendingStatisticsFrame->getVersion());

        string sql;

        if (insert)
        {
            sql = "INSERT INTO pending_statistics (statistics_id, request_id, amount, lastmodified, version) "
                  "VALUES      (:stats_id, :req_id, :am, :lm, :v)";
        }
        else
        {
            sql = "UPDATE pending_statistics "
                  "SET 	  amount=:am, lastmodified=:lm, version=:v "
                  "WHERE  statistics_id=:stats_id AND request_id=:req_id";
        }
        Database& db = getDatabase();
        LedgerDelta* delta = getLedgerDelta();
        auto prep = db.getPreparedStatement(sql);
        auto &st = prep.statement();

        st.exchange(use(pendingStatisticsEntry.statisticsID, "stats_id"));
        st.exchange(use(pendingStatisticsEntry.requestID, "req_id"));
        st.exchange(use(pendingStatisticsEntry.amount, "am"));
        st.exchange(use(pendingStatisticsFrame->mEntry.lastModifiedLedgerSeq, "lm"));
        st.exchange(use(pendingStatsVersion, "v"));
        st.define_and_bind();

        auto timer = insert ? db.getInsertTimer("pending_stats")
                            : db.getUpdateTimer("pending_stats");
        st.execute(true);

        if (st.get_affected_rows() != 1) {
            throw std::runtime_error("could not update SQL");
        }

        if (insert)
            delta->addEntry(*pendingStatisticsFrame);
        else
            delta->modEntry(*pendingStatisticsFrame);

    }

    PendingStatisticsFrame::pointer
    PendingStatisticsHelperImpl::loadPendingStatistics(uint64_t& requestID, uint64_t& statsID)
    {
        Database& db = getDatabase();
        LedgerDelta* delta = getLedgerDelta();
        string sql = pendingStatisticsSelector;
        sql += " WHERE statistics_id = :stats_id AND request_id = :req_id";

        auto prep = db.getPreparedStatement(sql);
        auto& st = prep.statement();
        st.exchange(use(statsID, "stats_id"));
        st.exchange(use(requestID, "req_id"));

        PendingStatisticsFrame::pointer result;
        auto timer = db.getSelectTimer("pending_stats");
        load(prep, [&result](LedgerEntry const& entry)
        {
            result = make_shared<PendingStatisticsFrame>(entry);
        });

        if (!result)
            return nullptr;

        if (delta)
            delta->recordEntry(*result);

        return result;
    }

    vector<PendingStatisticsFrame::pointer>
    PendingStatisticsHelperImpl::loadPendingStatistics(uint64_t& requestID)
    {
        Database& db = getDatabase();
        string sql = pendingStatisticsSelector;
        sql += " WHERE request_id = :req_id";

        auto prep = db.getPreparedStatement(sql);
        auto& st = prep.statement();
        st.exchange(use(requestID, "req_id"));

        vector<PendingStatisticsFrame::pointer> result;
        auto timer = db.getSelectTimer("pending_stats");
        load(prep, [&result](LedgerEntry const& entry)
        {
            result.emplace_back(make_shared<PendingStatisticsFrame>(entry));
        });

        return result;
    }

    void PendingStatisticsHelperImpl::load(StatementContext &prep, function<void(LedgerEntry const&)> processor)
    {
        try
        {
            LedgerEntry le;
            le.data.type(LedgerEntryType::PENDING_STATISTICS);
            auto& pendingStats = le.data.pendingStatistics();

            int32_t version;

            auto& st = prep.statement();
            st.exchange(into(pendingStats.statisticsID));
            st.exchange(into(pendingStats.requestID));
            st.exchange(into(pendingStats.amount));
            st.exchange(into(le.lastModifiedLedgerSeq));
            st.exchange(into(version));
            st.define_and_bind();
            st.execute(true);

            while (st.got_data())
            {
                pendingStats.ext.v(static_cast<LedgerVersion>(version));

                processor(le);
                st.fetch();
            }
        }
        catch (...)
        {
            throw_with_nested(runtime_error("Failed to load pending statistics"));
        }
    }

    LedgerDelta *PendingStatisticsHelperImpl::getLedgerDelta() {
        return mStorageHelper.getLedgerDelta();
    }

    Database &PendingStatisticsHelperImpl::getDatabase() {
        return mStorageHelper.getDatabase();
    }

    PendingStatisticsHelperImpl::PendingStatisticsHelperImpl(StorageHelper &storageHelper)
            : mStorageHelper(storageHelper)
    {
        mPendingStatisticsColumnSelector =
                "SELECT code, owner, preissued_asset_signer, "
                "details, max_issuance_amount, "
                "available_for_issueance, issued, pending_issuance, "
                "policies, type, trailing_digits, lastmodified, version "
                "FROM asset ";
    }
}