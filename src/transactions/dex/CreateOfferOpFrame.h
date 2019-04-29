#pragma once

// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <transactions/FeesManager.h>
#include "ledger/OfferFrame.h"
#include "ledger/BalanceFrame.h"
#include "ledger/AssetPairFrame.h"
#include "transactions/OperationFrame.h"
#include "OfferExchange.h"
#include "ManageOfferOpFrame.h"

namespace stellar
{
class CreateOfferOpFrame : public ManageOfferOpFrame
{

    FeeType feeType = FeeType::OFFER_FEE;

    bool checkOfferValid(Database& db, LedgerDelta& delta);

    OfferExchange::OfferFilterResult filterOffer(uint64_t price, OfferFrame const& o);

    AssetPairFrame::pointer loadTradableAssetPair(Database& db, LedgerDelta& delta);

    bool lockSellingAmount(OfferEntry const& offer);

    FeeManager::FeeResult obtainCalculatedFeeForAccount(int64_t amount, LedgerManager& lm, Database& db) const;

protected:

    BalanceFrame::pointer loadBalanceValidForTrading(
        BalanceID const& balanceID,
        Database& db, LedgerDelta& delta);

    bool
    tryGetOperationConditions(StorageHelper &storageHelper,
                              std::vector<OperationCondition> &result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;

public:
    CreateOfferOpFrame(Operation const& op, OperationResult& res,
                       TransactionFrame& parentTx, FeeType feeType);

    bool doApply(Application& app, LedgerDelta& delta,
                 LedgerManager& ledgerManager) override;
    bool doCheckValid(Application& app) override;
};
}
