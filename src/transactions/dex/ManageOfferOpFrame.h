#pragma once

// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ledger/BalanceFrame.h"
#include "ledger/AssetPairFrame.h"
#include "transactions/OperationFrame.h"

namespace stellar
{
class ManageOfferOpFrame : public OperationFrame
{

protected:

    BalanceFrame::pointer mBaseBalance;
    BalanceFrame::pointer mQuoteBalance;
    AssetPairFrame::pointer mAssetPair;

    ManageOfferResult& innerResult() const
    {
        return mResult.tr().manageOfferResult();
    }

    ManageOfferOp const& mManageOffer;

public:
    static const uint64_t SECONDARY_MARKET_ORDER_BOOK_ID = 0;
    ManageOfferOpFrame(Operation const& op, OperationResult& res,
                       TransactionFrame& parentTx);

    static ManageOfferResultCode getInnerCode(OperationResult const& res)
    {
        return res.tr().manageOfferResult().code();
    }

    static ManageOfferOpFrame* make(Operation const& op, OperationResult& res,
        TransactionFrame& parentTx);
    std::string getInnerResultCodeAsStr() override;

    virtual bool
    doCheckValid(Application& app) = 0;

    virtual bool
    doApply(Application& app, LedgerDelta& delta, LedgerManager& lm) = 0;

    ManageOfferResultCode 
    getInnerCode() 
    {
        return getInnerCode(mResult);
    }
};
}
