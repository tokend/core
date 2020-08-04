#include "ReviewRemoveDataRequestOpFrame.h"
#include "ledger/StorageHelper.h"
#include "ledger/DataHelper.h"

namespace stellar
{
using namespace std;
using xdr::operator==;

bool
ReviewRemoveDataRequestOpFrame::handleApprove(Application& app, StorageHelper& storageHelper,
                                             LedgerManager& ledgerManager, ReviewableRequestFrame::pointer request)
{
    request->checkRequestType(ReviewableRequestType::REMOVE_DATA);

    auto& requestHelper = storageHelper.getReviewableRequestHelper();

    handleTasks(requestHelper, request);

    if (!request->canBeFulfilled(ledgerManager))
    {
        innerResult().code(ReviewRequestResultCode::SUCCESS);
        innerResult().success().fulfilled = false;
        return true;
    }

    auto& removeDataRequest = request->getRequestEntry().body.removeDataRequest();
    auto dataFrame = storageHelper.getDataHelper().loadData(removeDataRequest.id);

    if (!dataFrame) {
        innerResult().code(ReviewRequestResultCode::DATA_NOT_FOUND);
    }
    storageHelper.getDataHelper().storeDelete(dataFrame->getKey());

    innerResult().code(ReviewRequestResultCode::SUCCESS);
    innerResult().success().fulfilled = true;
    return true;
}

bool
ReviewRemoveDataRequestOpFrame::handleReject(Application& app, StorageHelper& storageHelper,
                                             LedgerManager& ledgerManager, ReviewableRequestFrame::pointer request)
{
    innerResult().code(ReviewRequestResultCode::REJECT_NOT_ALLOWED);
    return false;
}

ReviewRemoveDataRequestOpFrame::ReviewRemoveDataRequestOpFrame(Operation const& op,
                                                           OperationResult& res, TransactionFrame& parentTx)
     : ReviewRequestOpFrame(op, res, parentTx)
{
}

}
