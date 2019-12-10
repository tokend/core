#pragma once

#include "EntryHelper.h"
#include <functional>
#include <unordered_map>
#include "AccountLimitsFrame.h"
#include "AccountFrame.h"
#include "BalanceFrame.h"
#include "StorageHelper.h"
#include "LimitsV2Helper.h"

namespace soci
{
    class session;
}

namespace stellar
{
class StatementContext;


class LimitsV2HelperImpl : public LimitsV2Helper
{
public:
    explicit LimitsV2HelperImpl(StorageHelper &storageHelper);

    LimitsV2HelperImpl(LimitsV2HelperImpl const&) = delete;
    LimitsV2HelperImpl& operator=(LimitsV2HelperImpl const&) = delete;

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

    std::vector<LimitsV2Frame::pointer> loadLimits(std::vector<StatsOpType> statsOpTypes,
                                      AssetCode assetCode, xdr::pointer<AccountID> accountID = nullptr,
                                      uint64_t* accountType = nullptr) override;
    LimitsV2Frame::pointer loadLimits(StatsOpType statsOpType, AssetCode assetCode,
                                      xdr::pointer<AccountID> accountID, uint64_t* accountType,
                                      bool isConvertNeeded) override;
    LimitsV2Frame::pointer loadLimits(uint64_t id) override;
    std::vector<LimitsV2Frame::pointer> loadLimitsForAsset(AssetCode const& code);

private:
    StorageHelper& mStorageHelper;
    const char* mLimitsV2ColumnSelector;


    std::string obtainSqlStatsOpTypesString(std::vector<StatsOpType> stats);
    void load(StatementContext &prep, std::function<void(LedgerEntry const &)> processor);
    void storeUpdateHelper(bool insert, LedgerEntry const& entry);
};

}