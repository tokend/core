#pragma once

// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ledger/SaleFrame.h"
#include "CreateOfferOpFrame.h"

namespace stellar
{
class CreateSaleParticipationOpFrame : public CreateOfferOpFrame
{
    SaleFrame::pointer loadSaleForOffer(Database& db, LedgerDelta& delta);

    bool isPriceValid(SaleFrame::pointer sale, BalanceFrame::pointer balance, Database& db) const;

    void setErrorCode(BalanceFrame::Result lockingResult);

public:

    CreateSaleParticipationOpFrame(Operation const& op, OperationResult& res,
                         TransactionFrame& parentTx);

    bool doCheckValid(Application& app) override;
    bool doApply(Application& app, LedgerDelta& delta,
        LedgerManager& ledgerManager) override;
    bool isSaleActive(Database& db,LedgerManager& ledgerManager, SaleFrame::pointer sale);
    static SaleFrame::State getSaleState(const SaleFrame::pointer sale, Database& db, const uint64_t currentTime);
    static bool getSaleCurrentCap(SaleFrame::pointer const sale, Database& db, uint64_t& currentCapInDefaultQuote);

    static bool tryAddSaleCap(Database& db, uint64_t const& amount, AssetCode const& asset, SaleFrame::pointer sale);
};
}
