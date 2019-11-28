#include "EntryHelper.h"
#include <functional>
#include <unordered_map>
#include "AccountLimitsFrame.h"
#include "AccountFrame.h"
#include "BalanceFrame.h"
#include "StorageHelper.h"
#include "StatisticsV2Helper.h"

namespace soci
{
    class session;
}

namespace stellar
{
class StatementContext;


class StatisticsV2HelperImpl : public StatisticsV2Helper, NonCopyable
{
public:
    explicit StatisticsV2HelperImpl(StorageHelper &storageHelper);

    void dropAll() override;
    void storeAdd(LedgerEntry const& entry) override;
    void storeChange(LedgerEntry const& entry) override;
    void storeDelete(LedgerKey const& key) override;
    bool exists(LedgerKey const& key) override;
    LedgerKey getLedgerKey(LedgerEntry const& from) override;
    EntryFrame::pointer storeLoad(LedgerKey const& ledgerKey) override;
    EntryFrame::pointer fromXDR(LedgerEntry const& from) override;
    uint64_t countObjects() override;
    Database& getDatabase() override;
    LedgerDelta* getLedgerDelta() override;

    StatisticsV2Frame::pointer loadStatistics(uint64_t id) override;
    StatisticsV2Frame::pointer loadStatistics(AccountID& accountID, StatsOpType statsOpType,
                                                      AssetCode const& assetCode, bool isConvertNeeded) override;

    StatisticsV2Frame::pointer mustLoadStatistics(uint64_t id) override;
    StatisticsV2Frame::pointer mustLoadStatistics(AccountID& accountID, StatsOpType statsOpType,
                                                          AssetCode const& assetCode, bool isConvertNeeded) override;

private:
    StorageHelper& mStorageHelper;
    const char* mStatisticsV2ColumnSelector;

    void loadStatistics(StatementContext& prep, std::function<void(LedgerEntry const&)> processor) override;
    void storeUpdateHelper(bool insert, LedgerEntry const& entry) override;
};

}