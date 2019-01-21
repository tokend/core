
#include <ledger/ReviewableRequestHelper.h>
#include "CancelSaleCreationRequestOpFrame.h"

namespace stellar
{
using xdr::operator==;

bool
CancelSaleCreationRequestOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                                            std::vector<OperationCondition>& result) const
{
    // only request creator can remove it
    return true;
}

CancelSaleCreationRequestOpFrame::CancelSaleCreationRequestOpFrame(
        Operation const& op, OperationResult& res,
        TransactionFrame& parentTx)
        : OperationFrame(op, res, parentTx),
        mCancelSaleCreationRequest(mOperation.body.cancelSaleCreationRequestOp())
{
}

bool
CancelSaleCreationRequestOpFrame::doApply(Application& app, LedgerDelta& delta,
                                          LedgerManager& ledgerManager)
{
    auto const requestID = mCancelSaleCreationRequest.requestID;
    auto& db = ledgerManager.getDatabase();
    auto requestHelper = ReviewableRequestHelper::Instance();

    auto requestFrame = requestHelper->loadRequest(requestID, getSourceID(),
            ReviewableRequestType::SALE, db, &delta);
    if (!requestFrame)
    {
        innerResult().code(CancelSaleCreationRequestResultCode::REQUEST_NOT_FOUND);
        return false;
    }

    requestHelper->storeDelete(delta, db, requestFrame->getKey());

    innerResult().code(CancelSaleCreationRequestResultCode::SUCCESS);
    return true;
}

bool
CancelSaleCreationRequestOpFrame::doCheckValid(Application& app)
{
    if (mCancelSaleCreationRequest.requestID == 0) {
        innerResult().code(CancelSaleCreationRequestResultCode::REQUEST_ID_INVALID);
        return false;
    }

    return true;
}
}

