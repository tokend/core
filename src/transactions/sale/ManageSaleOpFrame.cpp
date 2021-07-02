#include "ManageSaleOpFrame.h"
#include "transactions/dex/OfferManager.h"
#include "transactions/ManageKeyValueOpFrame.h"
#include "ledger/OfferHelper.h"
#include "ledger/AssetHelper.h"
#include "ledger/KeyValueHelper.h"
#include "ledger/SaleHelper.h"
#include "ledger/StorageHelper.h"
#include "transactions/review_request/ReviewRequestHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/AccountSpecificRuleHelper.h"

namespace stellar
{
ManageSaleOpFrame::ManageSaleOpFrame(Operation const& op, OperationResult& opRes, TransactionFrame& parentTx)
    : OperationFrame(op, opRes, parentTx), mManageSaleOp(mOperation.body.manageSaleOp())
{
}

bool
ManageSaleOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                                             std::vector<OperationCondition>& result,
                                             LedgerManager& ledgerManager) const
{
    switch (mManageSaleOp.data.action()) {
    case ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
        if (ledgerManager.shouldUse(LedgerVersion::FIX_NOT_CHECKING_SET_TASKS_PERMISSIONS))
        {
            AccountRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
            resource.reviewableRequest().details.requestType(ReviewableRequestType::UPDATE_SALE_DETAILS);

            if (mManageSaleOp.data.updateSaleDetailsData().allTasks)
            {
                result.emplace_back(resource, AccountRuleAction::CREATE_WITH_TASKS, mSourceAccount);
            }
            else
            {
                result.emplace_back(resource, AccountRuleAction::CREATE, mSourceAccount);
            }
        }
        break;
    case ManageSaleAction::UPDATE_TIME:
        auto sale = storageHelper.getSaleHelper().loadSale(mManageSaleOp.saleID);
        if (!sale)
        {
            mResult.code(OperationResultCode::opNO_ENTRY);
            mResult.entryType() = LedgerEntryType::SALE;
            return false;
        }

        AccountRuleResource resource(LedgerEntryType::SALE);
        resource.sale().saleID = sale->getID();
        resource.sale().saleType = sale->getType();

        result.emplace_back(resource, AccountRuleAction::UPDATE_END_TIME, mSourceAccount);
        break;
    }
    // only sale owner or admin can manage sale
    return true;
}

bool
ManageSaleOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                            std::vector<SignerRequirement>& result) const
{
    auto sale = storageHelper.getSaleHelper().loadSale(mManageSaleOp.saleID);
    if (!sale)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::SALE;
        return false;
    }

    SignerRuleResource resource(LedgerEntryType::SALE);
    resource.sale().saleID = sale->getID();
    resource.sale().saleType = sale->getType();

    switch (mManageSaleOp.data.action())
    {
    case ManageSaleAction::UPDATE_TIME:
        result.emplace_back(resource, SignerRuleAction::UPDATE_END_TIME);
        break;
    default:
        result.emplace_back(resource, SignerRuleAction::MANAGE);
        break;
    }

    return true;
}

bool ManageSaleOpFrame::amendUpdateSaleDetailsRequest(Application& app, LedgerManager& lm, StorageHelper& storageHelper)
{
    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    auto requestFrame = requestHelper.loadRequest(
        mManageSaleOp.data.updateSaleDetailsData().requestID, getSourceID(),
        ReviewableRequestType::UPDATE_SALE_DETAILS);

    if (!requestFrame)
    {
        innerResult().code(ManageSaleResultCode::UPDATE_DETAILS_REQUEST_NOT_FOUND);
        return false;
    }

    auto& requestEntry = requestFrame->getRequestEntry();
    if (!ensureSaleUpdateDataValid(requestFrame))
    {
        return false;
    }

    requestEntry.body.updateSaleDetailsRequest().creatorDetails = mManageSaleOp.data.updateSaleDetailsData().creatorDetails;
    requestEntry.body.updateSaleDetailsRequest().sequenceNumber++;
    requestFrame->setTasks(requestEntry.tasks.allTasks);

    requestFrame->recalculateHashRejectReason();
    requestHelper.storeChange(requestFrame->mEntry);

    bool fulfilled = false;
    if (getSourceID() == app.getAdminID())
    {
        auto resultCode = ReviewRequestHelper::tryApproveRequest(mParentTx, app, lm, storageHelper, requestFrame);

        if (resultCode == ReviewRequestResultCode::SUCCESS)
        {
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
ManageSaleOpFrame::createUpdateSaleDetailsRequest(Application& app, StorageHelper& storageHelper,
                                                  LedgerManager& ledgerManager)
{
    auto reference = getUpdateSaleDetailsRequestReference();
    auto const referencePtr = xdr::pointer<string64>(new string64(reference));
    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    if (requestHelper.isReferenceExist(getSourceID(), reference, 0))
    {
        innerResult().code(ManageSaleResultCode::UPDATE_DETAILS_REQUEST_ALREADY_EXISTS);
        return false;
    }

    auto request = ReviewableRequestFrame::createNew(storageHelper.mustGetLedgerDelta(), getSourceID(),
                                                     app.getAdminID(),
                                                     referencePtr, ledgerManager.getCloseTime());
    auto& requestEntry = request->getRequestEntry();
    requestEntry.body.type(ReviewableRequestType::UPDATE_SALE_DETAILS);
    requestEntry.body.updateSaleDetailsRequest().saleID = mManageSaleOp.saleID;
    requestEntry.body.updateSaleDetailsRequest().creatorDetails = mManageSaleOp.data.updateSaleDetailsData().creatorDetails;
    requestEntry.body.updateSaleDetailsRequest().sequenceNumber = 0;

    request->recalculateHashRejectReason();

    requestHelper.storeAdd(request->mEntry);

    KeyValueHelper& keyValueHelper = storageHelper.getKeyValueHelper();
    uint32_t allTasks = 0;
    if (!keyValueHelper.loadTasks(allTasks, makeTasksKeyVector(),
                                  mManageSaleOp.data.updateSaleDetailsData().allTasks.get()))
    {
        innerResult().code(ManageSaleResultCode::SALE_UPDATE_DETAILS_TASKS_NOT_FOUND);
        return false;
    }

    request->setTasks(allTasks);
    requestHelper.storeChange(request->mEntry);

    bool fulfilled = false;

    if (allTasks == 0)
    {
        auto result = ReviewRequestHelper::tryApproveRequestWithResult(mParentTx, app, ledgerManager, storageHelper, request);
        if (result.code() != ReviewRequestResultCode::SUCCESS)
        {
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

void ManageSaleOpFrame::cancelSale(SaleFrame::pointer sale, StorageHelper& storageHelper, LedgerManager& lm)
{
    for (auto& saleQuoteAsset : sale->getSaleEntry().quoteAssets)
    {
        cancelAllOffersForQuoteAsset(sale, saleQuoteAsset, storageHelper);
    }

    unlockPendingIssuance(storageHelper, sale->getBaseAsset(), sale->getMaxAmountToBeSold());
    storageHelper.getSaleHelper().storeDelete(sale->getKey());

    removeSaleRules(storageHelper, sale->getKey());
}

void ManageSaleOpFrame::cancelAllOffersForQuoteAsset(SaleFrame::pointer sale, SaleQuoteAsset const& saleQuoteAsset,
                                                     StorageHelper& storageHelper)
{
    auto orderBookID = sale->getID();
    const auto offersToCancel = storageHelper.getOfferHelper().loadOffersWithFilters(sale->getBaseAsset(),
                                                                               saleQuoteAsset.quoteAsset,
                                                                               &orderBookID, nullptr);
    OfferManager::deleteOffers(storageHelper, offersToCancel);
}

bool ManageSaleOpFrame::doApply(Application& app, StorageHelper& storageHelper, LedgerManager& lm)
{
    auto saleFrame = getSourceID() == app.getAdminID()
                     ? storageHelper.getSaleHelper().loadSale(mManageSaleOp.saleID)
                     : storageHelper.getSaleHelper().loadSale(mManageSaleOp.saleID, getSourceID());

    if (!saleFrame)
    {
        innerResult().code(ManageSaleResultCode::SALE_NOT_FOUND);
        return false;
    }

    switch (mManageSaleOp.data.action())
    {
        case ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
        {
            if (mManageSaleOp.data.updateSaleDetailsData().requestID != 0)
            {
                return amendUpdateSaleDetailsRequest(app, lm, storageHelper);
            }
            return createUpdateSaleDetailsRequest(app, storageHelper, lm);
        }
        case ManageSaleAction::CANCEL:
        {
            cancelSale(saleFrame, storageHelper, lm);
            innerResult().code(ManageSaleResultCode::SUCCESS);
            innerResult().success().response.action(ManageSaleAction::CANCEL);
            break;
        }
        case ManageSaleAction::UPDATE_TIME:
            return updateTime(storageHelper, lm, saleFrame);
        default:
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected action from manage sale op: "
                                                   << xdr::xdr_to_string(mManageSaleOp.data.action());
            throw std::runtime_error("Unexpected action from manage sale op");
    }

    return true;
}

bool ManageSaleOpFrame::doCheckValid(Application& app)
{
    if (mManageSaleOp.saleID == 0)
    {
        innerResult().code(ManageSaleResultCode::SALE_NOT_FOUND);
        return false;
    }

    switch (mManageSaleOp.data.action()) {
    case ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
        if (!isValidJson(mManageSaleOp.data.updateSaleDetailsData().creatorDetails))
        {
            innerResult().code(ManageSaleResultCode::INVALID_CREATOR_DETAILS);
            return false;
        }
        break;
    case ManageSaleAction::UPDATE_TIME:
        if ((mManageSaleOp.data.updateTime().newStartTime == 0) && 
            (mManageSaleOp.data.updateTime().newEndTime == 0)) 
        {
            innerResult().code(ManageSaleResultCode::INVALID_UPDATE_TIME_DATA);
            return false;
        }
        break;
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
    auto& updateSaleDetailsRequest = request->getRequestEntry().body.updateSaleDetailsRequest();
    auto updateSaleDetailsRequestData = mManageSaleOp.data.updateSaleDetailsData();

    if (updateSaleDetailsRequestData.allTasks)
    {
        innerResult().code(ManageSaleResultCode::NOT_ALLOWED_TO_SET_TASKS_ON_UPDATE);
        return false;
    }

    return true;
}

void
ManageSaleOpFrame::unlockPendingIssuance(StorageHelper& storageHelper, AssetCode const& code, uint64_t const& amount)
{
    auto& assetHelper = storageHelper.getAssetHelper();
    auto asset = assetHelper.mustLoadAsset(code);
    asset->mustUnlockIssuedAmount(amount);
    assetHelper.storeChange(asset->mEntry);
}

bool
ManageSaleOpFrame::updateTime(StorageHelper& storageHelper, LedgerManager& lm, SaleFrame::pointer sale) {
    uint64 currentTime = lm.getCloseTime();
    uint64 newStartTime = mManageSaleOp.data.updateTime().newStartTime;

    if (newStartTime != 0) 
    {
        if ((currentTime >= sale->getStartTime()) || 
            (lm.getLastClosedLedgerHeader().header.scpValue.closeTime > newStartTime)) 
        {
            innerResult().code(ManageSaleResultCode::INVALID_START_TIME);
            return false;            
        }

        sale->setStartTime(newStartTime);
    }

    uint64 newEndTime = mManageSaleOp.data.updateTime().newEndTime;
    if (newEndTime <= sale->getStartTime()) 
    {
        innerResult().code(ManageSaleResultCode::INVALID_END_TIME);
        return false;     
    }

    sale->setEndTime(newEndTime);

    storageHelper.getSaleHelper().storeChange(sale->mEntry);

    innerResult().code(ManageSaleResultCode::SUCCESS);
    innerResult().success().response.action(ManageSaleAction::UPDATE_TIME);
    return true;
}

}
