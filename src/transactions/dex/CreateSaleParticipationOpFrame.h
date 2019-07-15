#pragma once

// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ledger/SaleFrame.h"
#include "CreateOfferOpFrame.h"

namespace stellar
{
class CreateSaleParticipationOpFrame : public CreateOfferOpFrame {
    SaleFrame::pointer loadSaleForOffer(StorageHelper& storageHelper);

    bool isPriceValid(StorageHelper& storageHelper, SaleFrame::pointer sale, BalanceFrame::pointer balance) const;

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;

    bool
    checkSaleRules(StorageHelper& storageHelper, SaleFrame::pointer const& sale);

public:

    CreateSaleParticipationOpFrame(Operation const& op, OperationResult& res,
                                   TransactionFrame& parentTx);

    bool doCheckValid(Application& app) override;
    bool doApply(Application& app, StorageHelper& storageHelper,
                 LedgerManager& ledgerManager) override;
    bool isSaleActive(StorageHelper& storageHelper, LedgerManager& ledgerManager, SaleFrame::pointer sale);
    static SaleFrame::State
    getSaleState(StorageHelper& storageHelper, const SaleFrame::pointer sale, const uint64_t currentTime);
    static bool
    getSaleCurrentCap(StorageHelper& storageHelper, SaleFrame::pointer const sale, uint64_t& currentCapInDefaultQuote);

    static bool
    tryAddSaleCap(StorageHelper& storageHelper, uint64_t const& amount, AssetCode const& asset, SaleFrame::pointer sale);
};
}
