#include "CreateDataRequestOpFrame.h"
#include <ledger/StorageHelper.h>
#include <ledger/LedgerHeaderFrame.h>
#include <ledger/AccountHelper.h>
#include <ledger/LedgerDelta.h>
#include <ledger/ReviewableRequestHelper.h>
#include <src/main/Application.h>

namespace stellar {

    CreateDataRequestOpFrame::CreateDataRequestOpFrame(Operation const &op,
                                                       OperationResult &res,
                                                       TransactionFrame &tx)
            : OperationFrame(op, res, tx), mCreateDataRequestOp(op.body.createDataRequestOp()) {}

    bool
    CreateDataRequestOpFrame::doCheckValid(Application &app) {
        if (mCreateDataRequestOp.createDataRequest.value.empty() ||
            !isValidJson(mCreateDataRequestOp.createDataRequest.value)) {
            pickResultCode(CreateDataRequestResultCode::INVALID_VALUE);
            return false;
        }

        return true;
    }

    bool
    CreateDataRequestOpFrame::doApply(Application &app, StorageHelper &storageHelper, LedgerManager &ledgerManager) {
        if(!storageHelper.getAccountHelper().exists(mCreateDataRequestOp.createDataRequest.owner)) {
            pickResultCode(CreateDataRequestResultCode::OWNER_NOT_EXIST);
            return false;
        }

        auto &delta = storageHelper.mustGetLedgerDelta();
        auto request = ReviewableRequestFrame::createNew(delta,
                                                         getSourceID(),
                                                         app.getAdminID(),
                                                         nullptr,
                                                         ledgerManager.getCloseTime());

        auto &requestEntry = request->getRequestEntry();
        requestEntry.body.type(ReviewableRequestType::CREATE_DATA);
        auto &createDataRequest = requestEntry.body.createDataRequest();
        createDataRequest = mCreateDataRequestOp.createDataRequest;
        request->recalculateHashRejectReason();

        storageHelper.getReviewableRequestHelper().storeAdd(request->mEntry);

        pickResultCode(CreateDataRequestResultCode::SUCCESS);
        innerResult().createDataRequestResponse().requestID = request->getRequestID();
        innerResult().createDataRequestResponse().value = createDataRequest.value;
        innerResult().createDataRequestResponse().type = createDataRequest.type;
        innerResult().createDataRequestResponse().ext.v(LedgerVersion::EMPTY_VERSION);
        return true;
    }

    bool
    CreateDataRequestOpFrame::tryGetOperationConditions(
            StorageHelper& storageHelper, std::vector<OperationCondition>& result) const
    {
        auto action = AccountRuleAction::CREATE;
        if (!(getSourceID() == mCreateDataRequestOp.createDataRequest.owner))
        {
            action = AccountRuleAction::CREATE_FOR_OTHER;
        }

        AccountRuleResource resource(LedgerEntryType::DATA);
        resource.data().type = mCreateDataRequestOp.createDataRequest.type;
        result.emplace_back(resource, action, mSourceAccount);

        return true;
    }

    bool CreateDataRequestOpFrame::tryGetSignerRequirements(stellar::StorageHelper &storageHelper,
                                                                  std::vector<SignerRequirement> &result) const {
        //TODO

        return true;
    }

    void
    CreateDataRequestOpFrame::pickResultCode(CreateDataRequestResultCode code) {
        innerResult().code(code);
    }

    CreateDataRequestResult&
    CreateDataRequestOpFrame::innerResult() {
        return mResult.tr().createDataRequestResult();
    }
}