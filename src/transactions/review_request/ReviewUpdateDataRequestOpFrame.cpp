#include "ReviewUpdateDataRequestOpFrame.h"
#include "ledger/StorageHelper.h"
#include "ledger/DataHelper.h"

namespace stellar
{
using namespace std;
using xdr::operator==;

bool
ReviewUpdateDataRequestOpFrame::handleApprove(Application& app, StorageHelper& storageHelper,
                                             LedgerManager& ledgerManager, ReviewableRequestFrame::pointer request)
{
    request->checkRequestType(ReviewableRequestType::UPDATE_DATA);

    auto& requestHelper = storageHelper.getReviewableRequestHelper();

    handleTasks(requestHelper, request);

    if (!request->canBeFulfilled(ledgerManager))
    {
        innerResult().code(ReviewRequestResultCode::SUCCESS);
        innerResult().success().fulfilled = false;
        return true;
    }

    auto& updateDataRequest = request->getRequestEntry().body.updateDataRequest();
    auto dataFrame = storageHelper.getDataHelper().loadData(updateDataRequest.id);

    if (!dataFrame) {
        innerResult().code(ReviewRequestResultCode::DATA_NOT_FOUND);
    }
    dataFrame->getData().value = updateDataRequest.value;
    storageHelper.getDataHelper().storeChange(dataFrame->mEntry);

    innerResult().code(ReviewRequestResultCode::SUCCESS);
    innerResult().success().fulfilled = true;
    return true;
}

bool
ReviewUpdateDataRequestOpFrame::handleReject(Application& app, StorageHelper& storageHelper,
                                             LedgerManager& ledgerManager, ReviewableRequestFrame::pointer request)
{
    innerResult().code(ReviewRequestResultCode::REJECT_NOT_ALLOWED);
    return false;
}

ReviewUpdateDataRequestOpFrame::ReviewUpdateDataRequestOpFrame(Operation const& op,
                                                           OperationResult& res, TransactionFrame& parentTx)
        : ReviewRequestOpFrame(op, res, parentTx)
{
}

}
