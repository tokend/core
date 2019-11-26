#pragma once

#include "BalanceFrame.h"
#include "EntryHelper.h"
#include <functional>

namespace soci
{
class session;
}

namespace stellar
{
class StatementContext;

class BalanceHelper : public EntryHelper
{
public:
    using EntryHelper::exists;

    virtual bool exists(BalanceID balanceID) = 0;

    virtual BalanceFrame::pointer
    mustLoadBalance(BalanceID balanceID) = 0;

    virtual BalanceFrame::pointer loadBalance(BalanceID balanceID) = 0;

    virtual BalanceFrame::pointer loadBalance(BalanceID balanceID,
                                              AccountID accountID) = 0;

    virtual BalanceFrame::pointer loadBalance(AccountID accountID,
                                              AssetCode assetCode) = 0;

    virtual void loadBalances(AccountID const& accountID,
                              std::vector<BalanceFrame::pointer>& retBalances) = 0;

    virtual std::vector<BalanceFrame::pointer>
    loadBalances(AccountID accountID, AssetCode assetCode) = 0;

    virtual std::vector<BalanceFrame::pointer>
    loadBalances(std::vector<AccountID> accountIDs, AssetCode assetCode) = 0;

    virtual std::vector<BalanceFrame::pointer>
    loadAssetHolders(AssetCode assetCode, AccountID owner,
                     uint64_t minTotalAmount) = 0;
    virtual std::vector<BalanceFrame::pointer>
    loadBalancesForAsset(AssetCode assetCode) = 0;
    virtual uint64_t
    loadTotalAssetAmount(AssetCode assetCode) = 0;
};
} // namespace stellar