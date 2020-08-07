#include "UpdateDataRequestOpFrame.h"
#include <ledger/StorageHelper.h>
#include <ledger/LedgerHeaderFrame.h>
#include <ledger/AccountHelper.h>
#include <ledger/LedgerDelta.h>
#include <ledger/DataHelper.h>
#include <ledger/ReviewableRequestHelper.h>
#include <src/main/Application.h>

namespace stellar {

    UpdateDataRequestOpFrame::UpdateDataRequestOpFrame(Operation const &op,
                                                       OperationResult &res,
                                                       TransactionFrame &tx)
            : OperationFrame(op, res, tx), mUpdateDataRequestOp(op.body.updateDataRequestOp()) {}

    bool
    UpdateDataRequestOpFrame::doCheckValid(Application &app) {
        if (mUpdateDataRequestOp.updateDataRequest.value.empty() ||
            !isValidJson(mUpdateDataRequestOp.updateDataRequest.value)) {
            pickResultCode(UpdateDataRequestResultCode::INVALID_VALUE);
            return false;
        }

        return true;
    }

    bool
    UpdateDataRequestOpFrame::doApply(Application &app, StorageHelper &storageHelper, LedgerManager &ledgerManager) {

        if(!storageHelper.getAccountHelper().exists(mUpdateDataRequestOp.updateDataRequest.owner)) {
            pickResultCode(UpdateDataRequestResultCode::OWNER_NOT_EXIST);
            return false;
        }

        auto& helper = storageHelper.getDataHelper();
        auto dataFrame = helper.loadData(mUpdateDataRequestOp.updateDataRequest.id);
        if (!dataFrame)
        {
            innerResult().code(UpdateDataRequestResultCode::NOT_FOUND);
            return false;
        }

        auto &delta = storageHelper.mustGetLedgerDelta();
        auto request = ReviewableRequestFrame::createNew(delta,
                                                         getSourceID(),
                                                         app.getAdminID(),
                                                         nullptr,
                                                         ledgerManager.getCloseTime());
        auto &requestEntry = request->getRequestEntry();
        requestEntry.body.type(ReviewableRequestType::UPDATE_DATA);

        auto &updateDataRequest = requestEntry.body.updateDataRequest();
        updateDataRequest = mUpdateDataRequestOp.updateDataRequest;
        request->recalculateHashRejectReason();

        storageHelper.getReviewableRequestHelper().storeAdd(request->mEntry);

        pickResultCode(UpdateDataRequestResultCode::SUCCESS);
        innerResult().updateDataRequestResponse().requestID = request->getRequestID();
        innerResult().updateDataRequestResponse().owner = updateDataRequest.owner;
        innerResult().updateDataRequestResponse().dataID = updateDataRequest.id;
        innerResult().updateDataRequestResponse().value = updateDataRequest.value;
        innerResult().updateDataRequestResponse().type = updateDataRequest.type;
        innerResult().updateDataRequestResponse().ext.v(LedgerVersion::EMPTY_VERSION);
        return true;
    }

    bool
    UpdateDataRequestOpFrame::tryGetOperationConditions(
            StorageHelper& storageHelper, std::vector<OperationCondition>& result) const
    {
        auto dataFrame = storageHelper.getDataHelper().loadData(mUpdateDataRequestOp.updateDataRequest.id);
        if (!dataFrame)
        {
            mResult.code(OperationResultCode::opNO_ENTRY);
            mResult.entryType() = LedgerEntryType::DATA;
            return false;
        }

        auto action = AccountRuleAction::UPDATE;
        if (!(getSourceID() == dataFrame->getData().owner))
        {
            action = AccountRuleAction::UPDATE_FOR_OTHER;
        }

        AccountRuleResource resource(LedgerEntryType::DATA);
        resource.data().type = dataFrame->getData().type;
        result.emplace_back(resource, action, mSourceAccount);

        return true;
    }

    bool UpdateDataRequestOpFrame::tryGetSignerRequirements(stellar::StorageHelper &storageHelper,
                                                            std::vector<SignerRequirement> &result) const {
        //todo
        return true;
    }

    void
    UpdateDataRequestOpFrame::pickResultCode(UpdateDataRequestResultCode code) {
        innerResult().code(code);
    }

    UpdateDataRequestResult&
    UpdateDataRequestOpFrame::innerResult() {
        return mResult.tr().updateDataRequestResult();
    }
}