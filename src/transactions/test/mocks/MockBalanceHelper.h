#pragma once

#include "ledger/BalanceHelper.h"

namespace stellar
{

class MockBalanceHelper : public BalanceHelper
{
public:
    MOCK_METHOD0(dropAll, void());
    MOCK_CONST_METHOD0(getTableName, const std::string());
    MOCK_METHOD1(storeAdd, void(LedgerEntry const& entry));
    MOCK_METHOD1(storeChange, void(LedgerEntry const& entry));
    MOCK_METHOD1(storeDelete, void(LedgerKey const& key));
    MOCK_METHOD1(exists, bool(LedgerKey const& key));
    MOCK_METHOD1(exists, bool(BalanceID));
    MOCK_METHOD1(getLedgerKey, LedgerKey(LedgerEntry const& from));
    MOCK_METHOD1(fromXDR, EntryFrame::pointer(LedgerEntry const& from));
    MOCK_METHOD1(storeLoad, EntryFrame::pointer(LedgerKey const& ledgerKey));
    MOCK_METHOD0(countObjects, uint64_t());
    MOCK_METHOD0(getDatabase, Database&());
    MOCK_METHOD0(getLedgerDelta, LedgerDelta*());
    MOCK_METHOD1(flushCachedEntry, void(LedgerKey const& key));
    MOCK_METHOD1(cachedEntryExists, bool(LedgerKey const& key));
    MOCK_METHOD1(mustLoadBalance, BalanceFrame::pointer(BalanceID balanceID));
    MOCK_METHOD1(loadBalance,
            BalanceFrame::pointer(BalanceID balanceID));
    MOCK_METHOD2(loadBalance,
            BalanceFrame::pointer(BalanceID balanceID, AccountID accountID));
    MOCK_METHOD2(loadBalance,
            BalanceFrame::pointer(AccountID accountID, AssetCode assetCode));
    MOCK_METHOD2(loadBalances,
            void(AccountID const& accountID,
                    std::vector<BalanceFrame::pointer>& retBalances));
    MOCK_METHOD2(loadBalances,
            std::vector<BalanceFrame::pointer>(AccountID accountID,
             AssetCode assetCode));
    MOCK_METHOD2(loadBalances,
            std::vector<BalanceFrame::pointer>(
                    std::vector<AccountID> accountIDs, AssetCode assetCode));
    MOCK_METHOD3(loadAssetHolders,
            std::vector<BalanceFrame::pointer>(AssetCode assetCode,
                                   AccountID owner, uint64_t minTotalAmount));
    MOCK_METHOD1(loadBalancesForAsset,
            std::vector<BalanceFrame::pointer>(AssetCode assetCode));
    MOCK_METHOD1(loadTotalAssetAmount, uint64_t(AssetCode assetCode));
};

}  // namespace stellar
