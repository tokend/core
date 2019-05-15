#include "ManageSaleOpFrame.h"
#include "transactions/dex/OfferManager.h"
#include "transactions/ManageKeyValueOpFrame.h"
#include <ledger/OfferHelper.h>
#include <ledger/KeyValueHelper.h>
#include <ledger/SaleHelper.h>
#include "ledger/StorageHelperImpl.h"
#include <transactions/review_request/ReviewRequestHelper.h>
#include <ledger/ReviewableRequestHelper.h>
#include "ledger/AccountSpecificRuleHelper.h"

namespace stellar
{
    ManageSaleOpFrame::ManageSaleOpFrame(Operation const &op, OperationResult &opRes, TransactionFrame &parentTx)
            : OperationFrame(op, opRes, parentTx), mManageSaleOp(mOperation.body.manageSaleOp()) {
    }

bool
ManageSaleOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                                std::vector<OperationCondition>& result) const
{
    // only sale owner or admin can manage sale
    return true;
}

bool
ManageSaleOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                std::vector<SignerRequirement>& result) const
{
    auto sale = SaleHelper::Instance()->loadSale(mManageSaleOp.saleID,
                                                 storageHelper.getDatabase());
    if (!sale)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::SALE;
        return false;
    }

    SignerRuleResource resource(LedgerEntryType::SALE);
    resource.sale().saleID = sale->getID();
    resource.sale().saleType = sale->getType();

    result.emplace_back(resource, SignerRuleAction::MANAGE);

    return true;
}

    bool ManageSaleOpFrame::amendUpdateSaleDetailsRequest(Application &app, LedgerManager &lm, StorageHelper &storageHelper) {

        auto& db = storageHelper.getDatabase();
        auto delta = storageHelper.getLedgerDelta();

        auto requestFrame = ReviewableRequestHelper::Instance()->loadRequest(
                mManageSaleOp.data.updateSaleDetailsData().requestID, getSourceID(),
                ReviewableRequestType::UPDATE_SALE_DETAILS, db, delta);

        if (!requestFrame) {
            innerResult().code(ManageSaleResultCode::UPDATE_DETAILS_REQUEST_NOT_FOUND);
            return false;
        }

        auto &requestEntry = requestFrame->getRequestEntry();
        if (!ensureSaleUpdateDataValid(requestFrame)) {
            return false;
        }

        requestEntry.body.updateSaleDetailsRequest().creatorDetails = mManageSaleOp.data.updateSaleDetailsData().creatorDetails;
        requestEntry.body.updateSaleDetailsRequest().sequenceNumber++;
        requestFrame->setTasks(requestEntry.tasks.allTasks);

        requestFrame->recalculateHashRejectReason();
        ReviewableRequestHelper::Instance()->storeChange(*delta, db, requestFrame->mEntry);

        bool fulfilled = false;
        if (getSourceID() == app.getAdminID()) {
            auto resultCode = ReviewRequestHelper::tryApproveRequest(mParentTx, app, lm, *delta, requestFrame);

            if (resultCode == ReviewRequestResultCode::SUCCESS) {
                fulfilled = true;
            }
        }

        innerResult().code(ManageSaleResultCode::SUCCESS);
        innerResult().success().response.action(ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST);
        innerResult().success().response.requestID() = requestFrame->getRequestID();
        innerResult().success().fulfilled = fulfilled;

        return true;
    }

    bool
    ManageSaleOpFrame::createUpdateSaleDetailsRequest(Application &app, StorageHelper &storageHelper,
                                                      LedgerManager &ledgerManager) {
        auto& db = storageHelper.getDatabase();
        LedgerDelta& delta = storageHelper.mustGetLedgerDelta();

        auto reference = getUpdateSaleDetailsRequestReference();
        auto const referencePtr = xdr::pointer<string64>(new string64(reference));
        auto requestHelper = ReviewableRequestHelper::Instance();
        if (requestHelper->isReferenceExist(db, getSourceID(), reference)) {
            innerResult().code(ManageSaleResultCode::UPDATE_DETAILS_REQUEST_ALREADY_EXISTS);
            return false;
        }

        auto request = ReviewableRequestFrame::createNew(delta, getSourceID(),
                                                         app.getAdminID(),
                                                         referencePtr, ledgerManager.getCloseTime());
        auto &requestEntry = request->getRequestEntry();
        requestEntry.body.type(ReviewableRequestType::UPDATE_SALE_DETAILS);
        requestEntry.body.updateSaleDetailsRequest().saleID = mManageSaleOp.saleID;
        requestEntry.body.updateSaleDetailsRequest().creatorDetails = mManageSaleOp.data.updateSaleDetailsData().creatorDetails;
        requestEntry.body.updateSaleDetailsRequest().sequenceNumber = 0;

        request->recalculateHashRejectReason();

        requestHelper->storeAdd(delta, db, request->mEntry);

        KeyValueHelper& keyValueHelper = storageHelper.getKeyValueHelper();
        uint32_t allTasks = 0;
        if (!keyValueHelper.loadTasks(allTasks, makeTasksKeyVector(),
                                      mManageSaleOp.data.updateSaleDetailsData().allTasks.get()))
        {
            innerResult().code(ManageSaleResultCode::SALE_UPDATE_DETAILS_TASKS_NOT_FOUND);
            return false;
        }

        request->setTasks(allTasks);
        EntryHelperProvider::storeChangeEntry(delta, db, request->mEntry);

        bool fulfilled = false;

        if (allTasks == 0) {
            auto result = ReviewRequestHelper::tryApproveRequestWithResult(mParentTx, app, ledgerManager, delta, request);
            if (result.code() != ReviewRequestResultCode::SUCCESS) {
                throw std::runtime_error("Failed to review manage sale request");
            }
            fulfilled = result.success().fulfilled;
        }

        innerResult().code(ManageSaleResultCode::SUCCESS);
        innerResult().success().response.action(ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST);
        innerResult().success().response.requestID() = request->getRequestID();
        innerResult().success().fulfilled = fulfilled;

        return true;
    }

void
ManageSaleOpFrame::removeSaleRules(StorageHelper& sh, LedgerKey const& saleKey)
{
    auto& ruleHelper = sh.getAccountSpecificRuleHelper();

    ruleHelper.deleteRulesForEntry(saleKey);
}

    void ManageSaleOpFrame::cancelSale(SaleFrame::pointer sale, LedgerDelta &delta, Database &db, LedgerManager &lm) {
        for (auto &saleQuoteAsset : sale->getSaleEntry().quoteAssets) {
            cancelAllOffersForQuoteAsset(sale, saleQuoteAsset, delta, db);
        }

        AccountManager::unlockPendingIssuanceForSale(sale, delta, db, lm);
        SaleHelper::Instance()->storeDelete(delta, db, sale->getKey());

        StorageHelperImpl storageHelper(db, &delta);
        removeSaleRules(storageHelper, sale->getKey());
    }

    void ManageSaleOpFrame::cancelAllOffersForQuoteAsset(SaleFrame::pointer sale, SaleQuoteAsset const &saleQuoteAsset,
                                                         LedgerDelta &delta, Database &db) {
        auto orderBookID = sale->getID();
        const auto offersToCancel = OfferHelper::Instance()->loadOffersWithFilters(sale->getBaseAsset(),
                                                                                   saleQuoteAsset.quoteAsset,
                                                                                   &orderBookID, nullptr, db);
        OfferManager::deleteOffers(offersToCancel, db, delta);
    }

    bool ManageSaleOpFrame::doApply(Application &app, StorageHelper &storageHelper, LedgerManager &lm) {
        auto &db = storageHelper.getDatabase();
        auto delta = storageHelper.getLedgerDelta();

        auto saleFrame = getSourceID() == app.getAdminID()
                         ? SaleHelper::Instance()->loadSale(mManageSaleOp.saleID, db, delta)
                         : SaleHelper::Instance()->loadSale(mManageSaleOp.saleID, getSourceID(), db, delta);

        if (!saleFrame) {
            innerResult().code(ManageSaleResultCode::SALE_NOT_FOUND);
            return false;
        }

        switch (mManageSaleOp.data.action()) {
            case ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST: {
                if (mManageSaleOp.data.updateSaleDetailsData().requestID != 0) {
                    return amendUpdateSaleDetailsRequest(app, lm, storageHelper);
                }
                return createUpdateSaleDetailsRequest(app, storageHelper, lm);
            }
            case ManageSaleAction::CANCEL: {
                cancelSale(saleFrame, *delta, db, lm);
                innerResult().code(ManageSaleResultCode::SUCCESS);
                innerResult().success().response.action(ManageSaleAction::CANCEL);
                break;
            }
            default:
                CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected action from manage sale op: "
                                                       << xdr::xdr_to_string(mManageSaleOp.data.action());
                throw std::runtime_error("Unexpected action from manage sale op");
        }

        return true;
    }

    bool ManageSaleOpFrame::doCheckValid(Application &app) {
        if (mManageSaleOp.saleID == 0) {
            innerResult().code(ManageSaleResultCode::SALE_NOT_FOUND);
            return false;
        }

        if (mManageSaleOp.data.action() != ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST) {
            return true;
        }

        if (!isValidJson(mManageSaleOp.data.updateSaleDetailsData().creatorDetails)) {
            innerResult().code(ManageSaleResultCode::INVALID_CREATOR_DETAILS);
            return false;
        }

        return true;
    }

std::vector<std::string>
ManageSaleOpFrame::makeTasksKeyVector()
{
    return
    {
        ManageKeyValueOpFrame::makeSaleUpdateTasksKey(std::to_string(mManageSaleOp.saleID)),
        ManageKeyValueOpFrame::makeSaleUpdateTasksKey("*")
    };
}

    bool ManageSaleOpFrame::ensureSaleUpdateDataValid(ReviewableRequestFrame::pointer request)
    {
        auto &updateSaleDetailsRequest = request->getRequestEntry().body.updateSaleDetailsRequest();
        auto updateSaleDetailsRequestData = mManageSaleOp.data.updateSaleDetailsData();

        if (updateSaleDetailsRequestData.allTasks)
        {
            innerResult().code(ManageSaleResultCode::NOT_ALLOWED_TO_SET_TASKS_ON_UPDATE);
            return false;
        }

        return true;
    }
}
