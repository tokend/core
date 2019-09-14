#include "CreateSaleCreationRequestOpFrame.h"
#include "bucket/BucketApplicator.h"
#include "database/Database.h"
#include "ledger/AccountHelper.h"
#include "ledger/AssetHelper.h"
#include "ledger/AssetHelperLegacy.h"
#include "ledger/AssetPairHelper.h"
#include "ledger/KeyValueHelper.h"
#include "ledger/LedgerDelta.h"
#include "ledger/LedgerHeaderFrame.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/StorageHelper.h"
#include "main/Application.h"
#include "transactions/ManageKeyValueOpFrame.h"
#include "transactions/review_request/ReviewRequestHelper.h"
#include "xdrpp/printer.h"

namespace stellar
{
using xdr::operator==;

bool
CreateSaleCreationRequestOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                                            std::vector<OperationCondition>& result) const
{
    AccountRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::CREATE_SALE);
    resource.reviewableRequest().details.createSale().type = mCreateSaleCreationRequest.request.saleType;

    if (mCreateSaleCreationRequest.allTasks)
    {
        result.emplace_back(resource, AccountRuleAction::CREATE_WITH_TASKS, mSourceAccount);
        return true;
    }

    result.emplace_back(resource, AccountRuleAction::CREATE, mSourceAccount);

    // only asset owner can create sale, but restrict him to create sale - feature
    return true;
}

bool
CreateSaleCreationRequestOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                            std::vector<SignerRequirement>& result) const
{
    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::CREATE_SALE);
    resource.reviewableRequest().details.createSale().type = mCreateSaleCreationRequest.request.saleType;
    resource.reviewableRequest().tasksToRemove = 0;
    resource.reviewableRequest().tasksToAdd = 0;
    resource.reviewableRequest().allTasks = 0;
    if (mCreateSaleCreationRequest.allTasks)
    {
        resource.reviewableRequest().allTasks = *mCreateSaleCreationRequest.allTasks;
    }

    result.emplace_back(resource, SignerRuleAction::CREATE);

    return true;
}

AssetFrame::pointer
CreateSaleCreationRequestOpFrame::tryLoadBaseAssetOrRequest(SaleCreationRequest const& request,
                                                            Database& db, AccountID const& source)
{
    const auto assetFrame = AssetHelperLegacy::Instance()->loadAsset(request.baseAsset, source, db);
    if (!!assetFrame)
    {
        return assetFrame;
    }

    auto assetCreationRequests = ReviewableRequestHelper::Instance()->loadRequests(source, ReviewableRequestType::CREATE_ASSET, db);
    for (auto assetCreationRequestFrame : assetCreationRequests)
    {
        auto& assetCreationRequest = assetCreationRequestFrame->getRequestEntry().body.assetCreationRequest();
        if (assetCreationRequest.code == request.baseAsset)
        {
            return AssetFrame::create(assetCreationRequest, source);
        }
    }

    return nullptr;
}

bool CreateSaleCreationRequestOpFrame::areQuoteAssetsValid(Database& db, xdr::xvector<SaleCreationRequestQuoteAsset, 100> quoteAssets, AssetCode defaultQuoteAsset)
{
    if (!AssetHelperLegacy::Instance()->exists(db, defaultQuoteAsset))
    {
        return false;
    }

    for (auto const& quoteAsset : quoteAssets)
    {
        if (!AssetHelperLegacy::Instance()->exists(db, quoteAsset.quoteAsset))
        {
            return false;
        }

        if (defaultQuoteAsset == quoteAsset.quoteAsset)
            continue;

        const auto assetPair = AssetPairHelper::Instance()->tryLoadAssetPairForAssets(defaultQuoteAsset,
            quoteAsset.quoteAsset,
            db);
        if (!assetPair)
        {
            return false;
        }
    }

    return true;
}

bool CreateSaleCreationRequestOpFrame::isPriceValid(SaleCreationRequestQuoteAsset const& quoteAsset,
                                                    SaleCreationRequest const& saleCreationRequest)
{
    if (quoteAsset.price == 0)
    {
        return false;
    }

    bool isCrowdfunding = saleCreationRequest.saleTypeExt.saleType() == SaleType::CROWD_FUNDING;
    if (isCrowdfunding)
    {
        return quoteAsset.price == ONE;
    }

    // check for overflows
    uint64_t requiredBaseAsset;
    return SaleFrame::convertToBaseAmount(quoteAsset.price, saleCreationRequest.hardCap, 1, requiredBaseAsset) &&
           SaleFrame::convertToBaseAmount(quoteAsset.price, saleCreationRequest.softCap, 1, requiredBaseAsset);
}

CreateSaleCreationRequestOpFrame::CreateSaleCreationRequestOpFrame(
    Operation const& op, OperationResult& res,
    TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx)
    , mCreateSaleCreationRequest(mOperation.body.createSaleCreationRequestOp())
{
}

bool
CreateSaleCreationRequestOpFrame::doApply(Application& app, StorageHelper &storageHelper,
                                        LedgerManager& ledgerManager)
{
    if (mCreateSaleCreationRequest.requestID == 0)
    {
        return createRequest(app, storageHelper, ledgerManager);
    }

    return updateRequest(app, storageHelper, ledgerManager);
}

bool CreateSaleCreationRequestOpFrame::ensureEnoughAvailable(const SaleCreationRequest& saleCreationRequest,
                                                             AssetFrame::pointer baseAsset)
{
    if (saleCreationRequest.saleTypeExt.saleType() != SaleType::FIXED_PRICE ||
    saleCreationRequest.saleTypeExt.saleType() != SaleType::IMMEDIATE)
        return true;

    return baseAsset->getAvailableForIssuance() >= saleCreationRequest.requiredBaseAssetForHardCap;
}

bool CreateSaleCreationRequestOpFrame::doCheckValid(Application& app)
{
    if (mCreateSaleCreationRequest.requestID != 0 && mCreateSaleCreationRequest.allTasks)
    {
        innerResult().code(CreateSaleCreationRequestResultCode::
                               NOT_ALLOWED_TO_SET_TASKS_ON_UPDATE);
        return false;
    }

    auto checkValidResult = doCheckValid(app, mCreateSaleCreationRequest.request, getSourceID());
    if (checkValidResult == CreateSaleCreationRequestResultCode::SUCCESS) {
        return true;
    }

    innerResult().code(checkValidResult);
    return false;
}

CreateSaleCreationRequestResultCode
CreateSaleCreationRequestOpFrame::doCheckValid(Application &app, const SaleCreationRequest &saleCreationRequest,
                                               AccountID const& source)
{
    if (!AssetFrame::isAssetCodeValid(saleCreationRequest.baseAsset) ||
        !AssetFrame::isAssetCodeValid(saleCreationRequest.defaultQuoteAsset)
        || saleCreationRequest.defaultQuoteAsset == saleCreationRequest.baseAsset
        || saleCreationRequest.quoteAssets.empty())
    {
        return CreateSaleCreationRequestResultCode::INVALID_ASSET_PAIR;
    }

    std::set<AssetCode> quoteAssets;
    for (auto const& quoteAsset : saleCreationRequest.quoteAssets)
    {
        if (!AssetFrame::isAssetCodeValid(quoteAsset.quoteAsset) ||
            quoteAsset.quoteAsset == saleCreationRequest.baseAsset)
        {
            return CreateSaleCreationRequestResultCode::INVALID_ASSET_PAIR;
        }

        if (quoteAssets.find(quoteAsset.quoteAsset) != quoteAssets.end())
        {
            return CreateSaleCreationRequestResultCode::INVALID_ASSET_PAIR;
        }
        quoteAssets.insert(quoteAsset.quoteAsset);

        if (!isPriceValid(quoteAsset, saleCreationRequest))
        {
            return CreateSaleCreationRequestResultCode::INVALID_PRICE;
        }
    }

    if (saleCreationRequest.endTime <= saleCreationRequest.startTime)
    {
        return CreateSaleCreationRequestResultCode::START_END_INVALID;
    }

    if (saleCreationRequest.hardCap < saleCreationRequest.softCap
        || saleCreationRequest.requiredBaseAssetForHardCap == 0)
    {
        return CreateSaleCreationRequestResultCode::INVALID_CAP;
    }

    if (!isValidJson(saleCreationRequest.creatorDetails))
    {
        return CreateSaleCreationRequestResultCode::INVALID_CREATOR_DETAILS;
    }

    return CreateSaleCreationRequestResultCode::SUCCESS;
}

bool
CreateSaleCreationRequestOpFrame::createRequest(Application& app,
                                                StorageHelper& storageHelper,
                                                LedgerManager& ledgerManager)
{
    LedgerDelta& delta = storageHelper.mustGetLedgerDelta();
    auto request = ReviewableRequestFrame::createNew(
        delta.getHeaderFrame().generateID(LedgerEntryType::REVIEWABLE_REQUEST),
        getSourceID(), app.getAdminID(), nullptr, ledgerManager.getCloseTime());

    auto& requestEntry = request->getRequestEntry();
    requestEntry.body.type(ReviewableRequestType::CREATE_SALE);
    requestEntry.body.saleCreationRequest() = mCreateSaleCreationRequest.request;
    requestEntry.body.saleCreationRequest().sequenceNumber = 0;
    request->recalculateHashRejectReason();

    KeyValueHelper& keyValueHelper = storageHelper.getKeyValueHelper();
    uint32_t allTasks = 0;
    if (!keyValueHelper.loadTasks(allTasks, makeTasksKeyVector(),
                                  mCreateSaleCreationRequest.allTasks.get()))
    {
        innerResult().code(
            CreateSaleCreationRequestResultCode::SALE_CREATE_TASKS_NOT_FOUND);
        return false;
    }

    request->setTasks(allTasks);

    if (!isRequestValid(app, storageHelper, ledgerManager, request))
    {
        // corresponding result code is set in the called method
        return false;
    }

    auto& db = storageHelper.getDatabase();
    ReviewableRequestHelper::Instance()->storeAdd(delta, db, request->mEntry);

    bool fulfilled = false;
    uint64 saleID = 0;
    if (allTasks == 0)
    {
        // It's possible for sale creation request to fail on review due to various reasons
        auto result = ReviewRequestHelper::tryApproveRequestWithResult(
            mParentTx, app, ledgerManager, delta, request);
        if (result.code() != ReviewRequestResultCode::SUCCESS)
        {
            innerResult().code(CreateSaleCreationRequestResultCode::AUTO_REVIEW_FAILED);
            innerResult().autoReviewFailed().reviewRequestRequest = result;
            return false;
        }
        fulfilled = result.code() == ReviewRequestResultCode::SUCCESS &&
                    result.success().fulfilled;
        saleID = fulfilled ? result.success().typeExt.saleExtended().saleID : 0;
    }

    innerResult().code(CreateSaleCreationRequestResultCode::SUCCESS);
    innerResult().success().requestID = request->getRequestID();
    innerResult().success().fulfilled = fulfilled;
    innerResult().success().saleID = saleID;
    return true;
}

bool
CreateSaleCreationRequestOpFrame::updateRequest(Application& app,
                                                StorageHelper& storageHelper,
                                                LedgerManager& ledgerManager)
{

    auto& db = storageHelper.getDatabase();
    auto& delta = storageHelper.mustGetLedgerDelta();
    const auto requestFrame = ReviewableRequestHelper::Instance()->loadRequest(mCreateSaleCreationRequest.requestID, getSourceID(), db, &delta);
    if (!requestFrame || requestFrame->getType() != ReviewableRequestType::CREATE_SALE)
    {
        innerResult().code(
            CreateSaleCreationRequestResultCode::REQUEST_NOT_FOUND);
        return false;
    }

    auto& request = requestFrame->getRequestEntry();
    request.tasks.pendingTasks = request.tasks.allTasks;
    auto sequence = request.body.saleCreationRequest().sequenceNumber;
    request.body.saleCreationRequest() = mCreateSaleCreationRequest.request;
    request.body.saleCreationRequest().sequenceNumber = sequence + 1;
    requestFrame->recalculateHashRejectReason();

    if (!isRequestValid(app, storageHelper, ledgerManager, requestFrame))
    {
        // corresponding result code is set
        return false;
    }

    ReviewableRequestHelper::Instance()->storeChange(delta, db, requestFrame->mEntry);

    innerResult().code(CreateSaleCreationRequestResultCode::SUCCESS);
    innerResult().success().requestID = requestFrame->getRequestID();
    innerResult().success().fulfilled = false;
    innerResult().success().saleID = 0;
    return true;
}

bool
CreateSaleCreationRequestOpFrame::checkRulesDuplication(StorageHelper& storageHelper,
        xdr::xvector<CreateAccountSaleRuleData> const& rules)
{
    std::unordered_set<AccountID> accountIDs;
    bool hasGlobal = false;

    for (auto const& rule : rules)
    {
        if (rule.accountID)
        {
            auto isInserted = accountIDs.insert(*rule.accountID).second;
            if (!isInserted)
            {
                innerResult().code(CreateSaleCreationRequestResultCode::ACCOUNT_SPECIFIC_RULE_DUPLICATION);
                return false;
            }

            if (!storageHelper.getAccountHelper().exists(*rule.accountID))
            {
                innerResult().code(CreateSaleCreationRequestResultCode::ACCOUNT_NOT_FOUND);
                return false;
            }
        }
        else
        {
            if (hasGlobal) // only one global is allowed
            {
                innerResult().code(CreateSaleCreationRequestResultCode::GLOBAL_SPECIFIC_RULE_DUPLICATION);
                return false;
            }
            hasGlobal = true;
        }
    }

    if (!hasGlobal)
    {
        innerResult().code(CreateSaleCreationRequestResultCode::GLOBAL_SPECIFIC_RULE_REQUIRED);
        return false;
    }

    return true;
}


bool
CreateSaleCreationRequestOpFrame::isSaleRulesValid(Application& app,
        StorageHelper& storageHelper, SaleCreationRequest const& request)
{
    switch (request.ext.v())
    {
        case LedgerVersion::EMPTY_VERSION:
            return true;
        case LedgerVersion::ADD_SALE_WHITELISTS:
        {
            auto const& rules = request.ext.saleRules();

            uint32_t maxRulesLength = app.getMaxSaleRulesLength();
            auto keyValue = storageHelper.getKeyValueHelper().loadKeyValue(
                    ManageKeyValueOpFrame::makeMaxSaleRulesNumberKey());

            if (keyValue)
            {
                maxRulesLength = keyValue->mustGetUint32Value();
            }

            if (rules.size() > maxRulesLength)
            {
                innerResult().code(CreateSaleCreationRequestResultCode::EXCEEDED_MAX_RULES_SIZE);
                return false;
            }

            return checkRulesDuplication(storageHelper, rules);
        }
        default:
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected sale creation request version"
                                                   << static_cast<int32_t>(request.ext.v());
            throw std::runtime_error("Unexpected sale creation request version");
    }
}

bool
CreateSaleCreationRequestOpFrame::isRequestValid(Application& app,
    StorageHelper& storageHelper, LedgerManager& ledgerManager,
    ReviewableRequestFrame::pointer request)
{
    auto& sale = request->getRequestEntry().body.saleCreationRequest();
    auto saleVersion = sale.ext.v();
    if (!ledgerManager.shouldUse(saleVersion))
    {
        innerResult().code(
            CreateSaleCreationRequestResultCode::VERSION_IS_NOT_SUPPORTED_YET);
        return false;
    }

    if (!isSaleRulesValid(app, storageHelper, sale))
    {
        return false;
    }

    if (sale.endTime <= ledgerManager.getCloseTime())
    {
        innerResult().code(CreateSaleCreationRequestResultCode::INVALID_END);
        return false;
    }

    auto& db = ledgerManager.getDatabase();
    if (!areQuoteAssetsValid(
            db, sale.quoteAssets,
            sale.defaultQuoteAsset))
    {
        innerResult().code(
            CreateSaleCreationRequestResultCode::QUOTE_ASSET_NOT_FOUND);
        return false;
    }

    if (ledgerManager.shouldUse(LedgerVersion::FIX_REVERSE_SALE_PAIR))
    {
        for (auto const& quoteAsset : sale.quoteAssets)
        {
            if (AssetPairHelper::Instance()->exists(db, quoteAsset.quoteAsset, sale.baseAsset))
            {
                innerResult().code(CreateSaleCreationRequestResultCode::INVALID_ASSET_PAIR);
                return false;
            }
        }
    }

    const auto baseAsset = tryLoadBaseAssetOrRequest(sale, db, getSourceID());
    if (!baseAsset)
    {
        innerResult().code(CreateSaleCreationRequestResultCode::
                               BASE_ASSET_OR_ASSET_REQUEST_NOT_FOUND);
        return false;
    }
    if (!ensureEnoughAvailable(sale, baseAsset))
    {
        innerResult().code(
            CreateSaleCreationRequestResultCode::INSUFFICIENT_PREISSUED);
        return false;
    }
    if (baseAsset->willExceedMaxIssuanceAmount(sale.requiredBaseAssetForHardCap))
    {
        innerResult().code(CreateSaleCreationRequestResultCode::INSUFFICIENT_MAX_ISSUANCE);
        return false;
    }

   return true;
}

std::vector<std::string>
CreateSaleCreationRequestOpFrame::makeTasksKeyVector()
{
    return
    {
        ManageKeyValueOpFrame::makeSaleCreateTasksKey(mCreateSaleCreationRequest.request.baseAsset),
        ManageKeyValueOpFrame::makeSaleCreateTasksKey("*")
    };
}

}
