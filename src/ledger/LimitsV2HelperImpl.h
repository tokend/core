#pragma once

#include "EntryHelper.h"
#include <functional>
#include <unordered_map>
#include "AccountLimitsFrame.h"
#include "LimitsV2Frame.h"
#include "AccountFrame.h"
#include "BalanceFrame.h"
#include "StorageHelper.h"

namespace soci
{
    class session;
}

namespace stellar
{
class StatementContext;


class LimitsV2HelperImpl : public EntryHelper
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

    std::vector<LimitsV2Frame::pointer> loadLimits(Database &db, std::vector<StatsOpType> statsOpTypes,
                                      AssetCode assetCode, xdr::pointer<AccountID> accountID = nullptr,
                                      uint64_t* accountType = nullptr);
    LimitsV2Frame::pointer loadLimits(Database &db, StatsOpType statsOpType, AssetCode assetCode,
                                      xdr::pointer<AccountID> accountID, uint64_t* accountType,
                                      bool isConvertNeeded, LedgerDelta *delta = nullptr);
    LimitsV2Frame::pointer loadLimits(uint64_t id, Database& db, LedgerDelta* delta = nullptr);
    std::vector<LimitsV2Frame::pointer> loadLimitsForAsset(Database& db, AssetCode const& code);

private:
    StorageHelper& mStorageHelper;
    const char* mAssetColumnSelector;


    std::string obtainSqlStatsOpTypesString(std::vector<StatsOpType> stats);
    void load(StatementContext &prep, std::function<void(LedgerEntry const &)> processor);
    void storeUpdateHelper(LedgerDelta& delta, Database& db, bool insert, LedgerEntry const& entry);
};

}