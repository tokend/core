#include <ledger/SaleHelper.h>
#include "ReviewUpdateSaleDetailsRequestOpFrame.h"
#include "transactions/dex/ManageSaleOpFrame.h"

namespace stellar {
    ReviewUpdateSaleDetailsRequestOpFrame::ReviewUpdateSaleDetailsRequestOpFrame(const stellar::Operation &op,
                                                                                 stellar::OperationResult &res,
                                                                                 stellar::TransactionFrame &parentTx) :
            ReviewRequestOpFrame(op, res, parentTx) {

    }

    bool ReviewUpdateSaleDetailsRequestOpFrame::handleApprove(Application &app, LedgerDelta &delta,
                                                              LedgerManager &ledgerManager,
                                                              ReviewableRequestFrame::pointer request) {
        request->checkRequestType(ReviewableRequestType::UPDATE_SALE_DETAILS);

        Database &db = ledgerManager.getDatabase();

        handleTasks(db, delta, request);

        if (!request->canBeFulfilled(ledgerManager)){
            innerResult().code(ReviewRequestResultCode::SUCCESS);
            innerResult().success().fulfilled = false;
            return true;
        }

        auto &updateSaleDetailsRequest = request->getRequestEntry().body.updateSaleDetailsRequest();

        auto saleFrame = SaleHelper::Instance()->loadSale(updateSaleDetailsRequest.saleID, db, &delta);

        if (!saleFrame) {
            innerResult().code(ReviewRequestResultCode::SALE_NOT_FOUND);
            return false;
        }

        saleFrame->getSaleEntry().details = updateSaleDetailsRequest.newDetails;

        EntryHelperProvider::storeChangeEntry(delta, db, saleFrame->mEntry);
        EntryHelperProvider::storeDeleteEntry(delta, db, request->getKey());

        innerResult().code(ReviewRequestResultCode::SUCCESS);
        innerResult().success().fulfilled = true;
        return true;
    }
}