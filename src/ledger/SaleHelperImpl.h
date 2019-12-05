#pragma once

#include "EntryHelper.h"
#include <functional>
#include <unordered_map>
#include "AccountLimitsFrame.h"
#include "AccountFrame.h"
#include "BalanceFrame.h"
#include "StorageHelper.h"
#include "SaleHelper.h"

namespace soci
{
    class session;
}

namespace stellar
{
class StatementContext;


class SaleHelperImpl : public SaleHelper, NonCopyable
{
public:
    explicit SaleHelperImpl(StorageHelper &storageHelper);

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

    bool exists(uint64_t saleID) override;
    bool exists(AssetCode const& base, AssetCode const& quote) override;
    bool exists(AssetCode const& code) override;

    SaleFrame::pointer loadSale(uint64_t saleID, AccountID ownerID) override;
    SaleFrame::pointer loadSale(uint64_t saleID) override;
    SaleFrame::pointer loadSale(uint64_t saleID, AssetCode const& base, AssetCode const& quote) override;

    std::vector<SaleFrame::pointer> loadSalesForOwner(AccountID owner) override;

private:
    StorageHelper& mStorageHelper;
    const char* mSaleColumnSelector;

    void storeUpdateHelper(bool insert, LedgerEntry const& entry);
    void loadSales(StatementContext & prep, std::function<void(LedgerEntry const&)> requestsProcessor) const;
};

}