#pragma once

// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <transactions/managers/FeeManager.h>
#include "ledger/OfferFrame.h"
#include "ledger/BalanceFrame.h"
#include "ledger/AssetPairFrame.h"
#include "transactions/OperationFrame.h"
#include "OfferExchange.h"
#include "ManageOfferOpFrame.h"

namespace stellar
{
class CreateOfferOpFrame : public ManageOfferOpFrame {

    FeeType feeType;

    bool checkOfferValid(LedgerManager& lm, StorageHelper& storageHelper);

    OfferExchange::OfferFilterResult filterOffer(uint64_t price, OfferFrame const& o);

    AssetPairFrame::pointer loadTradableAssetPair(StorageHelper& storageHelper);

    bool lockSellingAmount(OfferEntry const& offer);

    FeeManager::FeeResult obtainCalculatedFeeForAccount(StorageHelper& storageHelper, int64_t amount, LedgerManager& lm) const;

    bool currentPriceRestrictionsMet(LedgerManager& lm);

    bool physicalPriceRestrictionsMet(LedgerManager& lm);

protected:

    BalanceFrame::pointer loadBalanceValidForTrading(StorageHelper& storageHelper,
                                                     BalanceID const& balanceID);

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;

public:
    CreateOfferOpFrame(Operation const& op, OperationResult& res,
                       TransactionFrame& parentTx, FeeType feeType);

    bool doApply(Application& app, StorageHelper& storageHelper,
                 LedgerManager& ledgerManager) override;
    bool doCheckValid(Application& app) override;
};
}
