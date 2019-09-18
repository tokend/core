#include "CancelSaleCreationRequestOpFrame.h"
#include <ledger/ReviewableRequestHelper.h>
#include "ledger/StorageHelper.h"

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

bool
CancelSaleCreationRequestOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                                           std::vector<SignerRequirement>& result) const
{
    auto request = storageHelper.
        getReviewableRequestHelper().
        loadRequest(mCancelSaleCreationRequest.requestID);
    if (!request || (request->getType() != ReviewableRequestType::CREATE_SALE))
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::REVIEWABLE_REQUEST;
        return false;
    }

    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::CREATE_SALE);

    resource.reviewableRequest().details.createSale().type =
        request->getRequestEntry().body.saleCreationRequest().saleType;
    resource.reviewableRequest().allTasks = 0;
    resource.reviewableRequest().tasksToAdd = 0;
    resource.reviewableRequest().tasksToRemove = 0;

    result.emplace_back(resource, SignerRuleAction::CANCEL);

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
CancelSaleCreationRequestOpFrame::doApply(Application& app, StorageHelper& storageHelper,
                                          LedgerManager& ledgerManager)
{
    auto const requestID = mCancelSaleCreationRequest.requestID;
    auto& requestHelper = storageHelper.getReviewableRequestHelper();

    auto requestFrame = requestHelper.loadRequest(requestID, getSourceID(),
                                                  ReviewableRequestType::CREATE_SALE);
    if (!requestFrame)
    {
        innerResult().code(CancelSaleCreationRequestResultCode::REQUEST_NOT_FOUND);
        return false;
    }

    requestHelper.storeDelete(requestFrame->getKey());

    innerResult().code(CancelSaleCreationRequestResultCode::SUCCESS);
    return true;
}

bool
CancelSaleCreationRequestOpFrame::doCheckValid(Application& app)
{
    if (mCancelSaleCreationRequest.requestID == 0)
    {
        innerResult().code(CancelSaleCreationRequestResultCode::REQUEST_ID_INVALID);
        return false;
    }

    return true;
}
}

