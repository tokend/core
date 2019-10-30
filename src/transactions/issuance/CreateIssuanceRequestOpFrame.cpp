// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "transactions/review_request/ReviewRequestHelper.h"
#include "ledger/FeeHelper.h"
#include "transactions/ManageKeyValueOpFrame.h"
#include "ledger/KeyValueHelper.h"
#include "CreateIssuanceRequestOpFrame.h"
#include "ledger/AssetHelper.h"
#include "ledger/AccountHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/ReferenceFrame.h"
#include "ledger/StorageHelper.h"
#include "xdrpp/marshal.h"

namespace stellar
{

using namespace std;
using xdr::operator==;

const uint32_t CreateIssuanceRequestOpFrame::INSUFFICIENT_AVAILABLE_FOR_ISSUANCE_AMOUNT;
const uint32_t CreateIssuanceRequestOpFrame::ISSUANCE_MANUAL_REVIEW_REQUIRED;
const uint32_t CreateIssuanceRequestOpFrame::DEPOSIT_LIMIT_EXCEEDED;

CreateIssuanceRequestOpFrame::CreateIssuanceRequestOpFrame(Operation const& op,
                                                           OperationResult& res,
                                                           TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx), mCreateIssuanceRequest(mOperation.body.createIssuanceRequestOp())
{
    mIsFeeRequired = true;
}

bool
CreateIssuanceRequestOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                                                        std::vector<OperationCondition>& result,
                                                        LedgerManager& ledgerManager) const
{
    auto asset = storageHelper.getAssetHelper().loadActiveAsset(
        mCreateIssuanceRequest.request.asset);
    if (!asset)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::ASSET;
        return false;
    }

    auto balance = storageHelper.getBalanceHelper().loadBalance(mCreateIssuanceRequest.request.receiver);
    if (!balance)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::BALANCE;
        return false;
    }

    if (ledgerManager.shouldUse(LedgerVersion::FIX_NOT_CHECKING_SET_TASKS_PERMISSIONS))
    {
        AccountRuleResource issuanceResource(LedgerEntryType::REVIEWABLE_REQUEST);
        issuanceResource.reviewableRequest().details.requestType(ReviewableRequestType::CREATE_ISSUANCE);

        if (mCreateIssuanceRequest.allTasks)
        {
            result.emplace_back(issuanceResource, AccountRuleAction::CREATE_WITH_TASKS, mSourceAccount);
        }
        else
        {
            result.emplace_back(issuanceResource, AccountRuleAction::CREATE, mSourceAccount);
        }
    }

    auto account = storageHelper.getAccountHelper().mustLoadAccount(balance->getAccountID());

    AccountRuleResource resource(LedgerEntryType::ASSET);
    resource.asset().assetCode = asset->getCode();
    resource.asset().assetType = asset->getType();

    result.emplace_back(resource, AccountRuleAction::RECEIVE_ISSUANCE, account);

    // only asset owner can do issuance, it will be handled in doApply
    return true;
}

bool
CreateIssuanceRequestOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                                       std::vector<SignerRequirement>& result) const
{
    auto asset = storageHelper.getAssetHelper().mustLoadAsset(
        mCreateIssuanceRequest.request.asset);

    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::CREATE_ISSUANCE);
    resource.reviewableRequest().details.createIssuance().assetCode = asset->getCode();
    resource.reviewableRequest().details.createIssuance().assetType = asset->getType();
    resource.reviewableRequest().tasksToRemove = 0;
    resource.reviewableRequest().tasksToAdd = 0;
    resource.reviewableRequest().allTasks = 0;
    if (mCreateIssuanceRequest.allTasks)
    {
        resource.reviewableRequest().allTasks = *mCreateIssuanceRequest.allTasks;
    }

    result.emplace_back(resource, SignerRuleAction::CREATE);

    return true;
}

bool
CreateIssuanceRequestOpFrame::doApply(Application& app, StorageHelper& storageHelper,
                                      LedgerManager& ledgerManager)
{
    auto requestFrame = tryCreateIssuanceRequest(app, storageHelper, ledgerManager);
    if (!requestFrame)
    {
        return false;
    }

    auto& keyValueHelper = storageHelper.getKeyValueHelper();
    uint32_t allTasks = 0;
    if (!keyValueHelper.loadTasks(allTasks, makeTasksKeyVector(),
                                  mCreateIssuanceRequest.allTasks.get()))
    {
        innerResult().code(CreateIssuanceRequestResultCode::ISSUANCE_TASKS_NOT_FOUND);
        return false;
    }

    requestFrame->setTasks(allTasks);
    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    requestHelper.storeChange(requestFrame->mEntry);

    const auto assetFrame = storageHelper.getAssetHelper().loadActiveAsset(
        mCreateIssuanceRequest.request.asset);
    if (!assetFrame)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Failed to load asset for issuance request. Asset Code: "
                                               << mCreateIssuanceRequest.request.asset;
        throw runtime_error("Failed to load asset for issuance request");
    }

    if (assetFrame->isPolicySet(AssetPolicy::ISSUANCE_MANUAL_REVIEW_REQUIRED))
    {
        allTasks |= ISSUANCE_MANUAL_REVIEW_REQUIRED;
        requestFrame->setTasks(allTasks);
        requestHelper.storeChange(requestFrame->mEntry);
    }

    bool fulfilled = false;
    ReviewRequestResultCode reviewRequestResultCode = ReviewRequestResultCode::SUCCESS;

    if (allTasks == 0)
    {
        ReviewRequestResult reviewRequestResult = ReviewRequestHelper::tryApproveRequestWithResult(
            mParentTx, app, ledgerManager, storageHelper, requestFrame);

        reviewRequestResultCode = reviewRequestResult.code();
        fulfilled = reviewRequestResultCode == ReviewRequestResultCode::SUCCESS ?
                    reviewRequestResult.success().fulfilled :
                    false;
    }

    switch (reviewRequestResultCode)
    {
        case ReviewRequestResultCode::SUCCESS:
        {
            break;
        }
        case ReviewRequestResultCode::FULL_LINE:
        {
            innerResult().code(CreateIssuanceRequestResultCode::RECEIVER_FULL_LINE);
            return false;
        }
        default:
        {
            CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected result received on review of just created issuance request: "
                << xdr::xdr_traits<ReviewRequestResultCode>::enum_name(reviewRequestResultCode);
            throw std::runtime_error("Unexpected result received on review of just created issuance request");
        }
    }

    innerResult().code(CreateIssuanceRequestResultCode::SUCCESS);
    innerResult().success().requestID = requestFrame->getRequestID();
    innerResult().success().fulfilled = fulfilled;
    innerResult().success().fee = requestFrame->getRequestEntry().body.issuanceRequest().fee;
    auto receiver = storageHelper.getBalanceHelper().mustLoadBalance(mCreateIssuanceRequest.request.receiver);
    innerResult().success().receiver = receiver->getAccountID();
    return true;
}

bool
CreateIssuanceRequestOpFrame::doCheckValid(Application& app)
{

    if (!AssetFrame::isAssetCodeValid(mCreateIssuanceRequest.request.asset))
    {
        innerResult().code(CreateIssuanceRequestResultCode::ASSET_NOT_FOUND);
        return false;
    }

    if (mCreateIssuanceRequest.request.amount == 0)
    {
        innerResult().code(CreateIssuanceRequestResultCode::INVALID_AMOUNT);
        return false;
    }

    if (mCreateIssuanceRequest.reference.empty())
    {
        innerResult().code(CreateIssuanceRequestResultCode::REFERENCE_DUPLICATION);
        return false;
    }

    if (mCreateIssuanceRequest.request.creatorDetails.size() > app.getIssuanceDetailsMaxLength()
        || !isValidJson(mCreateIssuanceRequest.request.creatorDetails))
    {
        innerResult().code(CreateIssuanceRequestResultCode::INVALID_CREATOR_DETAILS);
        return false;
    }


    int32_t systemTasks = CreateIssuanceRequestOpFrame::INSUFFICIENT_AVAILABLE_FOR_ISSUANCE_AMOUNT |
                          CreateIssuanceRequestOpFrame::ISSUANCE_MANUAL_REVIEW_REQUIRED |
                          CreateIssuanceRequestOpFrame::DEPOSIT_LIMIT_EXCEEDED;

    if (mCreateIssuanceRequest.allTasks && (*mCreateIssuanceRequest.allTasks.get() & systemTasks) != 0)
    {
        innerResult().code(CreateIssuanceRequestResultCode::SYSTEM_TASKS_NOT_ALLOWED);
        return false;
    }

    return true;
}

bool CreateIssuanceRequestOpFrame::isAuthorizedToRequestIssuance(AssetFrame::pointer assetFrame)
{
    return assetFrame->getOwner() == getSourceID();
}

ReviewableRequestFrame::pointer
CreateIssuanceRequestOpFrame::tryCreateIssuanceRequest(Application& app, StorageHelper& storageHelper,
                                                       LedgerManager& ledgerManager)
{
    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    if (requestHelper.isReferenceExist(getSourceID(), mCreateIssuanceRequest.reference))
    {
        innerResult().code(CreateIssuanceRequestResultCode::REFERENCE_DUPLICATION);
        return nullptr;
    }

    auto& assetHelper = storageHelper.getAssetHelper();

    auto asset =
        assetHelper.loadActiveAsset(mCreateIssuanceRequest.request.asset);
    if (!asset)
    {
        innerResult().code(CreateIssuanceRequestResultCode::ASSET_NOT_FOUND);
        return nullptr;
    }

    if (!assetHelper.doesAmountFitAssetPrecision(
        mCreateIssuanceRequest.request.asset, mCreateIssuanceRequest.request.amount))
    {
        innerResult().code(CreateIssuanceRequestResultCode::INVALID_AMOUNT_PRECISION);
        return nullptr;
    }

    if (!isAuthorizedToRequestIssuance(asset))
    {
        innerResult().code(CreateIssuanceRequestResultCode::NOT_AUTHORIZED);
        return nullptr;
    }

    if (asset->willExceedMaxIssuanceAmount(mCreateIssuanceRequest.request.amount))
    {
        innerResult().code(CreateIssuanceRequestResultCode::EXCEEDS_MAX_ISSUANCE_AMOUNT);
        return nullptr;
    }

    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto balance = balanceHelper.loadBalance(mCreateIssuanceRequest.request.receiver);
    if (!balance || balance->getAsset() != asset->getCode())
    {
        innerResult().code(CreateIssuanceRequestResultCode::NO_COUNTERPARTY);
        return nullptr;
    }

    Fee feeToPay;
    if (!calculateFee(app, storageHelper, balance->getAccountID(), feeToPay))
    {
        innerResult().code(CreateIssuanceRequestResultCode::FEE_EXCEEDS_AMOUNT);
        return nullptr;
    }

    auto reference = xdr::pointer<stellar::string64>(new stellar::string64(mCreateIssuanceRequest.reference));

    ReviewableRequestEntry::_body_t body;
    body.type(ReviewableRequestType::CREATE_ISSUANCE);
    body.issuanceRequest() = mCreateIssuanceRequest.request;
    body.issuanceRequest().fee = feeToPay;

    AccountID reviewer = app.getAdminID();
    if (!ledgerManager.shouldUse(LedgerVersion::FIX_ISSUANCE_REVIEWER)) 
    {
        reviewer = asset->getOwner();
    }

    auto& delta = storageHelper.mustGetLedgerDelta();
    auto request = ReviewableRequestFrame::createNewWithHash(delta, getSourceID(), reviewer, reference,
                                                             body, ledgerManager.getCloseTime());
    requestHelper.storeAdd(request->mEntry);
    return request;
}

bool
CreateIssuanceRequestOpFrame::calculateFee(Application& app, StorageHelper& storageHelper, AccountID receiver, Fee& fee)
{
    // calculate fee which will be charged from receiver
    fee.percent = 0;
    fee.fixed = 0;

    if (!mIsFeeRequired)
        return true;

    if (app.getAdminID() == receiver)
    {
        return true;
    }

    auto& db = storageHelper.getDatabase();

    auto receiverFrame = storageHelper.
        getAccountHelper().
        mustLoadAccount(receiver);

    auto feeFrame = FeeHelper::Instance()->loadForAccount(FeeType::ISSUANCE_FEE, mCreateIssuanceRequest.request.asset,
                                                          FeeFrame::SUBTYPE_ANY, receiverFrame,
                                                          mCreateIssuanceRequest.request.amount, db);
    if (feeFrame)
    {
        fee.fixed = feeFrame->getFee().fixedFee;
        auto feeAssetFrame = storageHelper.
            getAssetHelper().
            mustLoadAsset(mCreateIssuanceRequest.request.asset);
        feeFrame->calculatePercentFee(mCreateIssuanceRequest.request.amount, fee.percent, ROUND_UP,
                                      feeAssetFrame->getMinimumAmount());
    }

    uint64_t totalFee = 0;
    if (!safeSum(fee.fixed, fee.percent, totalFee))
        throw std::runtime_error("totalFee overflows uint64");

    return totalFee < mCreateIssuanceRequest.request.amount;
}

CreateIssuanceRequestOp CreateIssuanceRequestOpFrame::build(
    AssetCode const& asset, const uint64_t amount, BalanceID const& receiver,
    LedgerManager& lm, uint32_t allTasks, std::string* reference)
{
    IssuanceRequest request;
    request.amount = amount;
    request.asset = asset;
    request.creatorDetails = "{}";
    request.fee.percent = 0;
    request.fee.fixed = 0;
    request.receiver = receiver;
    CreateIssuanceRequestOp issuanceRequestOp;
    issuanceRequestOp.request = request;
    if (reference != nullptr)
    {
        if (reference->size() != 64)
        {
            throw std::runtime_error("Reference length is wrong");
        }
        issuanceRequestOp.reference = *reference;
    }
    else
    {
        issuanceRequestOp.reference = binToHex(
            sha256(xdr_to_opaque(receiver, asset, amount, lm.getCloseTime())));
    }

    issuanceRequestOp.allTasks.activate() = allTasks;

    return issuanceRequestOp;
}

std::vector<std::string>
CreateIssuanceRequestOpFrame::makeTasksKeyVector()
{
    return
        {
            ManageKeyValueOpFrame::makeIssuanceTasksKey(mCreateIssuanceRequest.request.asset),
            ManageKeyValueOpFrame::makeIssuanceTasksKey("*")
        };
}
}
