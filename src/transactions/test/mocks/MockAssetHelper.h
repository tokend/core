#pragma once

#include <lib/gtest/googlemock/include/gmock/gmock-generated-function-mockers.h>
#include <lib/gtest/googlemock/include/gmock/gmock-more-actions.h>
#include "ledger/AssetHelper.h"

namespace stellar
{

class MockAssetHelper : public AssetHelper
{
public:

    MOCK_METHOD0(dropAll, void());
    MOCK_METHOD1(storeAdd, void(LedgerEntry const& entry));
    MOCK_METHOD1(storeChange, void(LedgerEntry const& entry));
    MOCK_METHOD1(storeDelete, void(LedgerKey const& key));
    MOCK_METHOD1(exists, bool(LedgerKey const& key));
    MOCK_METHOD1(exists, bool(AssetCode const& key));
    MOCK_METHOD1(getLedgerKey, LedgerKey(LedgerEntry const& from));
    MOCK_METHOD1(fromXDR, EntryFrame::pointer(LedgerEntry const& from));
    MOCK_METHOD1(storeLoad, EntryFrame::pointer(LedgerKey const& ledgerKey));
    MOCK_METHOD0(countObjects, uint64_t());
    MOCK_METHOD0(getDatabase, Database&());
    MOCK_METHOD0(getLedgerDelta, LedgerDelta*());
    MOCK_METHOD1(flushCachedEntry, void(LedgerKey const& key));
    MOCK_METHOD1(cachedEntryExists, bool(LedgerKey const& key));
    MOCK_METHOD1(loadAsset,
                 AssetFrame::pointer(AssetCode assetCode));
    MOCK_METHOD1(mustLoadAsset,
                 AssetFrame::pointer(AssetCode assetCode));
    MOCK_METHOD2(loadAsset,
                 AssetFrame::pointer(AssetCode assetCode, AccountID owner));
    MOCK_METHOD2(loadAssets, void(StatementContext& prep,
            std::function<void(LedgerEntry const&)> assetProcessor));
    MOCK_METHOD0(loadStatsAsset, AssetFrame::pointer());
    MOCK_METHOD0(loadBaseAssets, std::vector<AssetFrame::pointer>());
    MOCK_METHOD0(addTrailingDigits, void());
    MOCK_METHOD2(doesAmountFitAssetPrecision, bool(const AssetCode& assetCode, uint64_t amount));
};

}  // namespace stellar
