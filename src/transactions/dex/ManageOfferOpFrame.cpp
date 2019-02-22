// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <ledger/AssetHelper.h>
#include "ManageOfferOpFrame.h"
#include "OfferExchange.h"
#include "ledger/LedgerDelta.h"
#include "main/Application.h"
#include "DeleteOfferOpFrame.h"
#include "CreateOfferOpFrame.h"
#include "DeleteSaleParticipationOpFrame.h"
#include "CreateSaleParticipationOpFrame.h"
#include "ledger/StorageHelper.h"
#include "ledger/BalanceHelper.h"

namespace stellar
{
using namespace std;
using xdr::operator==;

ManageOfferOpFrame::ManageOfferOpFrame(Operation const& op,
                                       OperationResult& res,
                                       TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx)
    , mManageOffer(mOperation.body.manageOfferOp())
{
}

ManageOfferOpFrame* ManageOfferOpFrame::make(Operation const& op,
                                             OperationResult& res,
                                             TransactionFrame& parentTx)
{
    const auto manageOffer = op.body.manageOfferOp();
    if (manageOffer.orderBookID == SECONDARY_MARKET_ORDER_BOOK_ID)
    {
        if (manageOffer.amount == 0)
        {
            return new DeleteOfferOpFrame(op, res, parentTx);
        }

        return new CreateOfferOpFrame(op, res, parentTx);
    }

    if (manageOffer.amount == 0)
    {
        return new DeleteSaleParticipationOpFrame(op, res, parentTx);
    }

    return new CreateSaleParticipationOpFrame(op, res, parentTx);
}

std::string ManageOfferOpFrame::getInnerResultCodeAsStr()
{
    const auto result = getResult();
    const auto code = getInnerCode(result);
    return xdr::xdr_traits<ManageOfferResultCode>::enum_name(code);
}
}
