#include <ledger/BalanceHelper.h>
#include <ledger/ReviewableRequestHelper.h>
#include <ledger/AccountHelper.h>
#include "ledger/AssetHelper.h"
#include "CreateRedemptionRequestOpFrame.h"
#include "ledger/LedgerDelta.h"
#include "ledger/StorageHelper.h"
#include "ledger/KeyValueHelper.h"
#include "ledger/LedgerHeaderFrame.h"
#include "transactions/ManageKeyValueOpFrame.h"
#include "review_request/ReviewRequestHelper.h"
#include "managers/BalanceManager.h"

namespace stellar {
    using xdr::operator==;

// TODO rm comments on merge
//  as i can see we need to validate all  prerequisites here (src account, dst balance & asset existing)
//  and then add account rule resources to result vector
//  hope im right
    bool CreateRedemptionRequestOpFrame::tryGetOperationConditions(StorageHelper &storageHelper,
                                                                   std::vector<OperationCondition> &result,
                                                                   LedgerManager &ledgerManager) const {
        auto &balanceHelper = storageHelper.getBalanceHelper();
        auto srcBalanceFrame = balanceHelper.loadBalance(mCreateRedemptionRequest.redemptionRequest.sourceBalanceID);
        if (!srcBalanceFrame) {
            mResult.code(OperationResultCode::opNO_ENTRY);
            mResult.entryType() = LedgerEntryType::BALANCE;
            return false;
        }

        auto &accountHelper = storageHelper.getAccountHelper();
        auto dstAccountFrame = accountHelper.loadAccount(mCreateRedemptionRequest.redemptionRequest.destination);
        if (!dstAccountFrame) {
            mResult.code(OperationResultCode::opNO_ENTRY);
            mResult.entryType() = LedgerEntryType::ACCOUNT;
            return false;
        }

        auto &assetHelper = storageHelper.getAssetHelper();
        auto assetFrame = assetHelper.mustLoadAsset(srcBalanceFrame->getAsset());

        AccountRuleResource resource(LedgerEntryType::ASSET);
        resource.asset().assetType = assetFrame->getType();
        resource.asset().assetCode = assetFrame->getCode();
        result.emplace_back(resource, AccountRuleAction::RECEIVE_REDEMPTION, dstAccountFrame);

        resource.type(LedgerEntryType::REVIEWABLE_REQUEST);
        resource.reviewableRequest().details.requestType(ReviewableRequestType::PERFORM_REDEMPTION);

        auto &details = resource.reviewableRequest().details.performRedemption();
        details.assetType = assetFrame->getType();
        details.assetCode = assetFrame->getCode();

        AccountRuleAction action = mCreateRedemptionRequest.allTasks ?
                                   AccountRuleAction::CREATE_WITH_TASKS : AccountRuleAction::CREATE;

        result.emplace_back(resource, action, mSourceAccount);

        return true;
    }

// TODO rm comments on merge
//  as i can see we need to validate all prerequisites here for signer (dst balance & asset existing)
//  and then add signer rule resources to result vector
//  hope im right
    bool CreateRedemptionRequestOpFrame::tryGetSignerRequirements(stellar::StorageHelper &storageHelper,
                                                                  std::vector<SignerRequirement> &result) const {
        auto &balanceHelper = storageHelper.getBalanceHelper();
        auto senderBalanceFrame = balanceHelper.mustLoadBalance(
                mCreateRedemptionRequest.redemptionRequest.sourceBalanceID);

        auto &assetHelper = storageHelper.getAssetHelper();
        auto assetFrame = assetHelper.mustLoadAsset(senderBalanceFrame->getAsset());

        SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
        resource.reviewableRequest().details.requestType(ReviewableRequestType::PERFORM_REDEMPTION);

        auto &details = resource.reviewableRequest().details.performRedemption();
        details.assetType = assetFrame->getType();
        details.assetCode = assetFrame->getCode();

        resource.reviewableRequest().tasksToRemove = 0;
        resource.reviewableRequest().tasksToAdd = 0;
        resource.reviewableRequest().allTasks = 0;

        SignerRuleAction action = SignerRuleAction::CREATE;
        if (mCreateRedemptionRequest.allTasks) {
            action = SignerRuleAction::CREATE_WITH_TASKS;
            resource.reviewableRequest().allTasks = *mCreateRedemptionRequest.allTasks;
        }

        result.emplace_back(resource, action);

        return true;
    }

    CreateRedemptionRequestOpFrame::CreateRedemptionRequestOpFrame(Operation const &op,
                                                                   OperationResult &res,
                                                                   TransactionFrame &tx)
            : OperationFrame(op, res, tx), mCreateRedemptionRequest(op.body.createRedemptionRequestOp()) {}


// TODO rm comments on merge
//  as i can see we need to do all operation's stuff in here
//  hope im right
    bool
    CreateRedemptionRequestOpFrame::doApply(Application &app, StorageHelper &storageHelper,
                                            LedgerManager &ledgerManager) {
        auto &balanceHelper = storageHelper.getBalanceHelper();
        auto sourceBalance = balanceHelper.loadBalance(mCreateRedemptionRequest.redemptionRequest.sourceBalanceID);
        if (!sourceBalance) {
            pickResultCode(CreateRedemptionRequestResultCode::SOURCE_BALANCE_NOT_EXIST);
            return false;
        }

        if (!storageHelper.getAccountHelper().exists(mCreateRedemptionRequest.redemptionRequest.destination)) {
            pickResultCode(CreateRedemptionRequestResultCode::DST_ACCOUNT_NOT_FOUND);
            return false;
        }

        BalanceManager balanceManager(app, storageHelper);
        auto destinationBalance = balanceManager.loadOrCreateBalance(
                mCreateRedemptionRequest.redemptionRequest.destination,
                sourceBalance->getAsset());
        if (!destinationBalance) {
            // not picking result code because there is bad app state if we cannot create balance, not our fault
            return false;
        }

        const auto result = sourceBalance->tryLock(mCreateRedemptionRequest.redemptionRequest.amount);
        if (result != BalanceFrame::Result::SUCCESS) {
            pickResultCode(result == BalanceFrame::Result::NONMATCHING_PRECISION ?
                           CreateRedemptionRequestResultCode::INCORRECT_PRECISION :
                           CreateRedemptionRequestResultCode::UNDERFUNDED);
            return false;
        }

        auto &requestHelper = storageHelper.getReviewableRequestHelper();

        const bool isReferenceExists = requestHelper.isReferenceExist(getSourceID(), mCreateRedemptionRequest.reference,
                                                                      0);
        if (isReferenceExists) {
            pickResultCode(CreateRedemptionRequestResultCode::REFERENCE_DUPLICATION);
            return false;
        }


        auto &delta = storageHelper.mustGetLedgerDelta();
        const uint64 requestID = delta.
                getHeaderFrame().
                generateID(LedgerEntryType::REVIEWABLE_REQUEST);
        const auto referencePtr = xdr::pointer<string64>(new string64(mCreateRedemptionRequest.reference));
        auto request = ReviewableRequestFrame::createNew(requestID,
                                                         getSourceID(),
                                                         app.getAdminID(),
                                                         referencePtr,
                                                         ledgerManager.getCloseTime());

        auto &requestEntry = request->getRequestEntry();
        requestEntry.body.type(ReviewableRequestType::PERFORM_REDEMPTION);
        requestEntry.body.redemptionRequest() = mCreateRedemptionRequest.redemptionRequest;
        request->recalculateHashRejectReason();
        balanceHelper.storeChange(sourceBalance->mEntry);
        requestHelper.storeAdd(request->mEntry);

        auto &kvHelper = storageHelper.getKeyValueHelper();
        uint32_t allTasks;
        if (!kvHelper.loadTasks(allTasks, makeTasksKeyVector(sourceBalance->getAsset()),
                                mCreateRedemptionRequest.allTasks.get())) {
            pickResultCode(CreateRedemptionRequestResultCode::REDEMPTION_TASKS_NOT_FOUND);
            return false;
        }
        if (allTasks == 0) {
            pickResultCode(CreateRedemptionRequestResultCode::REDEMPTION_ZERO_TASKS_NOT_ALLOWED);
            return false;
        }

        request->setTasks(allTasks);
        requestHelper.storeChange(request->mEntry);

        pickResultCode(CreateRedemptionRequestResultCode::SUCCESS);

        innerResult().redemptionResponse().requestID = requestID;
        innerResult().redemptionResponse().asset = sourceBalance->getAsset();
        innerResult().redemptionResponse().fulfilled = false; // approve by admin is mandatory
        innerResult().redemptionResponse().ext.v(LedgerVersion::EMPTY_VERSION);
        return true;
    }

// TODO rm comments on merge
//  as i can see we need to validate operation fields in this method
//  hope im right
    bool
    CreateRedemptionRequestOpFrame::doCheckValid(Application &app) {
        if (mCreateRedemptionRequest.redemptionRequest.creatorDetails.empty() ||
            isValidJson(mCreateRedemptionRequest.redemptionRequest.creatorDetails)) {
            pickResultCode(CreateRedemptionRequestResultCode::INVALID_CREATOR_DETAILS);
            return false;
        }

        if (mCreateRedemptionRequest.redemptionRequest.amount == 0) {
            pickResultCode(CreateRedemptionRequestResultCode::INVALID_AMOUNT);
            return false;
        }

        if (mCreateRedemptionRequest.reference.length() > 64) {
            pickResultCode(CreateRedemptionRequestResultCode::INVALID_REFERENCE);
            return false;
        }

        return true;
    }

    void
    CreateRedemptionRequestOpFrame::pickResultCode(CreateRedemptionRequestResultCode code) {
        innerResult().code(code);
    }

    std::vector<std::string>
    CreateRedemptionRequestOpFrame::makeTasksKeyVector(AssetCode const &code) {
        return {ManageKeyValueOpFrame::makeRedemptionTasksKey()};
    }

}







