#pragma once

#include "util/NonCopyable.h"
#include "BalanceHelper.h"

namespace soci
{
class session;
}

namespace stellar
{
class StorageHelper;

class BalanceHelperImpl : public BalanceHelper, NonCopyable
{

public:
    explicit BalanceHelperImpl(StorageHelper& storageHelper);
    uint64_t
    loadTotalAssetAmount(AssetCode assetCode) override;
private:
    void
    dropAll() override;

    void
    storeAdd(LedgerEntry const& entry) override;

    void
    storeChange(LedgerEntry const& entry) override;

    void
    storeDelete(LedgerKey const& key) override;

    bool
    exists(LedgerKey const& key) override;

    bool
    exists(BalanceID balanceID) override;

    LedgerKey
    getLedgerKey(LedgerEntry const& from) override;

    EntryFrame::pointer
    storeLoad(LedgerKey const& key) override;

    EntryFrame::pointer
    fromXDR(LedgerEntry const& from) override;

    uint64_t
    countObjects() override;

    BalanceFrame::pointer
    mustLoadBalance(BalanceID balanceID) override;

    BalanceFrame::pointer
    loadBalance(BalanceID balanceID) override;

    BalanceFrame::pointer
    loadBalance(BalanceID balanceID, AccountID accountID) override;

    BalanceFrame::pointer
    loadBalance(AccountID accountID, AssetCode assetCode) override;

    BalanceFrame::pointer
    loadFirstBalance(AccountID accountID, AssetCode assetCode) override;

    void
    loadBalances(AccountID const& accountID,
                 std::vector<BalanceFrame::pointer>& retBalances) override;

    std::vector<BalanceFrame::pointer>
    loadBalances(AccountID accountID, AssetCode assetCode) override;

    std::vector<BalanceFrame::pointer>
    loadBalances(std::vector<AccountID> accountIDs,
                 AssetCode assetCode) override;

    std::vector<BalanceFrame::pointer>
    loadAssetHolders(AssetCode assetCode, AccountID owner,
                     uint64_t minTotalAmount) override;
    std::vector<BalanceFrame::pointer>
    loadBalancesForAsset(AssetCode assetCode) override;

    void
    loadBalances(StatementContext& prep,
            std::function<void(BalanceFrame::pointer const&)> balanceProcessor);

    void
    storeUpdateHelper(bool insert, LedgerEntry const& entry);

    Database&
    getDatabase() override;

    LedgerDelta*
    getLedgerDelta() override;

    std::string
    obtainStrAccountIDs(std::vector<AccountID> accountIDs);

    StorageHelper& mStorageHelper;
};

} // namespace stellar
