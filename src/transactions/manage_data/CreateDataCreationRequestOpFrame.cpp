#include "CreateDataCreationRequestOpFrame.h"
#include <ledger/StorageHelper.h>
#include <ledger/LedgerHeaderFrame.h>
#include <ledger/AccountHelper.h>
#include <ledger/LedgerDelta.h>
#include <ledger/ReviewableRequestHelper.h>
#include <src/main/Application.h>

namespace stellar {

    CreateDataCreationRequestOpFrame::CreateDataCreationRequestOpFrame(Operation const &op,
                                                                       OperationResult &res,
                                                                       TransactionFrame &tx)
            : OperationFrame(op, res, tx), mCreateDataCreationRequestOp(op.body.createDataCreationRequestOp()) {}

    bool
    CreateDataCreationRequestOpFrame::tryGetOperationConditions(
            StorageHelper& storageHelper, std::vector<OperationCondition>& result) const
    {
        AccountRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
        resource.reviewableRequest().details.requestType(ReviewableRequestType::DATA_CREATION);
        resource.reviewableRequest().details.dataCreation().type = mCreateDataCreationRequestOp.dataCreationRequest.type;

        if (mCreateDataCreationRequestOp.allTasks)
        {
            result.emplace_back(resource, AccountRuleAction::CREATE_WITH_TASKS, mSourceAccount);
            return true;
        }

        result.emplace_back(resource, AccountRuleAction::CREATE, mSourceAccount);

        return true;
    }

    bool CreateDataCreationRequestOpFrame::tryGetSignerRequirements(stellar::StorageHelper &storageHelper,
                                                                    std::vector<SignerRequirement> &result) const {
        SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
        resource.reviewableRequest().details.requestType(ReviewableRequestType::DATA_CREATION);
        resource.reviewableRequest().details.createSale().type = mCreateDataCreationRequestOp.dataCreationRequest.type;
        resource.reviewableRequest().tasksToRemove = 0;
        resource.reviewableRequest().tasksToAdd = 0;
        resource.reviewableRequest().allTasks = 0;
        if (mCreateDataCreationRequestOp.allTasks)
        {
            resource.reviewableRequest().allTasks = *mCreateSaleCreationRequest.allTasks;
        }

        result.emplace_back(resource, SignerRuleAction::CREATE);

        return true;
    }

    bool
    CreateDataCreationRequestOpFrame::doCheckValid(Application &app) {
        if (mCreateDataCreationRequestOp.createDataCreationRequest.value.empty() ||
            !isValidJson(mCreateDataCreationRequestOp.createDataCreationRequest.value)) {
            pickResultCode(CreateDataCreationRequestResultCode::INVALID_VALUE);
            return false;
        }

        return true;
    }

    bool
    CreateDataCreationRequestOpFrame::doApply(Application &app, StorageHelper &storageHelper, LedgerManager &ledgerManager) {
        if (mCreateDataCreationRequestOp.requestID == 0)
        {
            return createRequest(app, storageHelper, ledgerManager);
        }

        return updateRequest(app, storageHelper, ledgerManager);
    }

    bool
    CreateDataCreationRequestOpFrame::createRequest(Application& app,
                                                    StorageHelper& storageHelper,
                                                    LedgerManager& ledgerManager) {


        auto &delta = storageHelper.mustGetLedgerDelta();
        auto request = ReviewableRequestFrame::createNew(delta,
                                                         getSourceID(),
                                                         app.getAdminID(),
                                                         nullptr,
                                                         ledgerManager.getCloseTime());

        auto &requestEntry = request->getRequestEntry();
        requestEntry.body.type(ReviewableRequestType::DATA_CREATION);
        mCreateDataCreationRequestOp.dataCreationRequest.sequenceNumber = 0;
        requestEntry.body.dataCreationRequest() = mCreateDataCreationRequestOp.dataCreationRequest;
        request->recalculateHashRejectReason();

        auto& keyValueHelper = storageHelper.getKeyValueHelper();
        uint32_t allTasks;
        if (!keyValueHelper.loadTasks(allTasks,
                                      makeTasksKeyVector(),
                                      mCreateDataCreationRequestOp.allTasks.get()))
        {
            pickResultCode(CreateDataCreationRequestResultCode::CREATE_DATA_TASKS_NOT_FOUND);
            return false;
        }

        request->setTasks(allTasks);

        storageHelper.getReviewableRequestHelper().storeAdd(request->mEntry);

        pickResultCode(CreateDataCreationRequestResultCode::SUCCESS);
        innerResult().createDataCreationRequestResponse().requestID = request->getRequestID();
        innerResult().createDataCreationRequestResponse().value = mCreateDataCreationRequestOp.dataCreationRequest.value;
        innerResult().createDataCreationRequestResponse().type = mCreateDataCreationRequestOp.dataCreationRequest.type;
        innerResult().createDataCreationRequestResponse().ext.v(LedgerVersion::EMPTY_VERSION);
        return true;
    }

    bool
    CreateDataCreationRequestOpFrame::updateRequest(Application& app,
                                                    StorageHelper& storageHelper,
                                                    LedgerManager& ledgerManager) {
        auto& requestHelper = storageHelper.getReviewableRequestHelper();
        const auto requestFrame = requestHelper.
                loadRequest(mCreateSaleCreationRequest.requestID, getSourceID());
        if (!requestFrame || requestFrame->getType() != ReviewableRequestType::DATA_CREATION)
        {
            innerResult().code(
                    CreateSaleCreationRequestResultCode::REQUEST_NOT_FOUND);
            return false;
        }

        auto& request = requestFrame->getRequestEntry();
        request.tasks.pendingTasks = request.tasks.allTasks;
        auto sequence = request.body.dataCreationRequest().sequenceNumber;
        request.body.saleCreationRequest() = mCreateSaleCreationRequest.request;
        request.body.saleCreationRequest().sequenceNumber = sequence + 1;
        requestFrame->recalculateHashRejectReason();

        if (!isRequestValid(app, storageHelper, ledgerManager, requestFrame))
        {
            // corresponding result code is set
            return false;
        }

        requestHelper.storeChange(requestFrame->mEntry);

        innerResult().code(CreateSaleCreationRequestResultCode::SUCCESS);
        innerResult().success().requestID = requestFrame->getRequestID();
        innerResult().success().fulfilled = false;
        innerResult().success().saleID = 0;
        return true;
    }


    void
    CreateDataCreationRequestOpFrame::pickResultCode(CreateDataCreationRequestResultCode code) {
        innerResult().code(code);
    }

    CreateDataCreationRequestResult&
    CreateDataCreationRequestOpFrame::innerResult() {
        return mResult.tr().createDataCreationRequestResult();
    }

    std::vector<std::string>
    CreateDataCreationRequestOpFrame::makeTasksKeyVector()
    {
        return
            {
                ManageKeyValueOpFrame::createDataCreationRequestTasks(to_string(mCreateDataCreationRequestOp.dataCreationRequest.type)),
                ManageKeyValueOpFrame::createDataCreationRequestTasks("*")
            };
    }
}
