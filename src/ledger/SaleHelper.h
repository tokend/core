#pragma once

// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ledger/EntryHelper.h"
#include "ledger/LedgerManager.h"
#include <functional>
#include "SaleFrame.h"

namespace soci
{
    class session;
}

namespace stellar
{
class StatementContext;

class SaleHelper : public EntryHelper {
public:
    virtual bool exists(uint64_t saleID) = 0;
    virtual bool exists(AssetCode const& base, AssetCode const& quote) = 0;
    virtual bool exists(AssetCode const& code) = 0;

    virtual SaleFrame::pointer loadSale(uint64_t saleID, AccountID ownerID) = 0;
    virtual SaleFrame::pointer loadSale(uint64_t saleID) = 0;
    virtual SaleFrame::pointer loadSale(uint64_t saleID, AssetCode const& base, AssetCode const& quote) = 0;

    virtual std::vector<SaleFrame::pointer> loadSalesForOwner(AccountID owner) = 0;

private:

    virtual void storeUpdateHelper(bool insert, LedgerEntry const& entry) = 0;
    virtual void loadSales(StatementContext & prep, std::function<void(LedgerEntry const&)> requestsProcessor) const = 0;
};
}