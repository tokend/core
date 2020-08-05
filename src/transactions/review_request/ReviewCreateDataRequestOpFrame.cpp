#include "ReviewCreateDataRequestOpFrame.h"
#include "ledger/StorageHelper.h"
#include "ledger/DataHelper.h"

namespace stellar
{
using namespace std;
using xdr::operator==;

bool
ReviewCreateDataRequestOpFrame::handleApprove(Application& app, StorageHelper& storageHelper,
                                             LedgerManager& ledgerManager, ReviewableRequestFrame::pointer request)
{
    request->checkRequestType(ReviewableRequestType::CREATE_DATA);

    auto& requestHelper = storageHelper.getReviewableRequestHelper();

    handleTasks(requestHelper, request);

    if (!request->canBeFulfilled(ledgerManager))
    {
        innerResult().code(ReviewRequestResultCode::SUCCESS);
        innerResult().success().fulfilled = false;
        return true;
    }

    auto& createDataRequest = request->getRequestEntry().body.createDataRequest();
    auto dataFrame = DataFrame::create(createDataRequest); //todo get acc id from request
    storageHelper.getDataHelper().storeAdd(dataFrame->mEntry);

    innerResult().code(ReviewRequestResultCode::SUCCESS);
    innerResult().success().fulfilled = true;
    return true;
}

bool
ReviewCreateDataRequestOpFrame::handleReject(Application& app, StorageHelper& storageHelper,
                                             LedgerManager& ledgerManager, ReviewableRequestFrame::pointer request)
{
    innerResult().code(ReviewRequestResultCode::REJECT_NOT_ALLOWED);
    return false;
}

ReviewCreateDataRequestOpFrame::ReviewCreateDataRequestOpFrame(Operation const& op,
                                                               OperationResult& res, TransactionFrame& parentTx)
     : ReviewRequestOpFrame(op, res, parentTx)
{
}

}
