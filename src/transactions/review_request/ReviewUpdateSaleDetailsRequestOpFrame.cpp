#include <ledger/SaleHelper.h>
#include <ledger/EntryHelper.h>
#include "ReviewUpdateSaleDetailsRequestOpFrame.h"
#include "transactions/sale/ManageSaleOpFrame.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/StorageHelper.h"

namespace stellar
{
ReviewUpdateSaleDetailsRequestOpFrame::ReviewUpdateSaleDetailsRequestOpFrame(const stellar::Operation& op,
                                                                             stellar::OperationResult& res,
                                                                             stellar::TransactionFrame& parentTx) :
    ReviewRequestOpFrame(op, res, parentTx)
{

}

bool ReviewUpdateSaleDetailsRequestOpFrame::handleApprove(Application& app, StorageHelper& storageHelper,
                                                          LedgerManager& ledgerManager,
                                                          ReviewableRequestFrame::pointer request)
{
    request->checkRequestType(ReviewableRequestType::UPDATE_SALE_DETAILS);

    auto& requestHelper = storageHelper.getReviewableRequestHelper();

    handleTasks(requestHelper, request);

    if (!request->canBeFulfilled(ledgerManager))
    {
        innerResult().code(ReviewRequestResultCode::SUCCESS);
        innerResult().success().fulfilled = false;
        return true;
    }

    auto& updateSaleDetailsRequest = request->getRequestEntry().body.updateSaleDetailsRequest();
    auto saleFrame = storageHelper.getSaleHelper().loadSale(updateSaleDetailsRequest.saleID);

    if (!saleFrame)
    {
        innerResult().code(ReviewRequestResultCode::SALE_NOT_FOUND);
        return false;
    }

    saleFrame->getSaleEntry().details = updateSaleDetailsRequest.creatorDetails;
    storageHelper.getSaleHelper().storeChange(saleFrame->mEntry);
    requestHelper.storeDelete(request->getKey());

    innerResult().code(ReviewRequestResultCode::SUCCESS);
    innerResult().success().fulfilled = true;
    return true;
}
}
