#include "RemoveDataRequestOpFrame.h"
#include <ledger/StorageHelper.h>
#include <ledger/LedgerHeaderFrame.h>
#include <ledger/AccountHelper.h>
#include <ledger/LedgerDelta.h>
#include <ledger/DataHelper.h>
#include <ledger/ReviewableRequestHelper.h>
#include <src/main/Application.h>

namespace stellar {

    RemoveDataRequestOpFrame::RemoveDataRequestOpFrame(Operation const &op,
                                                       OperationResult &res,
                                                       TransactionFrame &tx)
            : OperationFrame(op, res, tx), mRemoveDataRequestOp(op.body.removeDataRequestOp()) {}

    bool
    RemoveDataRequestOpFrame::doCheckValid(Application &app) {
        return true;
    }

    bool
    RemoveDataRequestOpFrame::doApply(Application &app, StorageHelper &storageHelper, LedgerManager &ledgerManager) {
        auto& helper = storageHelper.getDataHelper();
        auto dataFrame = helper.loadData(mRemoveDataRequestOp.removeDataRequest.id);
        if (!dataFrame)
        {
            innerResult().code(RemoveDataRequestResultCode::NOT_FOUND);
            return false;
        }

        auto &delta = storageHelper.mustGetLedgerDelta();
        auto request = ReviewableRequestFrame::createNew(delta,
                                                         getSourceID(),
                                                         app.getAdminID(),
                                                         nullptr,
                                                         ledgerManager.getCloseTime());
        auto &requestEntry = request->getRequestEntry();
        requestEntry.body.type(ReviewableRequestType::REMOVE_DATA);

        auto &removeDataRequest = requestEntry.body.removeDataRequest();
        removeDataRequest = mRemoveDataRequestOp.removeDataRequest;
        request->recalculateHashRejectReason();

        storageHelper.getReviewableRequestHelper().storeAdd(request->mEntry);

        pickResultCode(RemoveDataRequestResultCode::SUCCESS);
        innerResult().removeDataRequestResponse().requestID = request->getRequestID();
        return true;
    }

    bool
    RemoveDataRequestOpFrame::tryGetOperationConditions(
            StorageHelper& storageHelper, std::vector<OperationCondition>& result) const
    {
        auto dataFrame = storageHelper.getDataHelper().loadData(mRemoveDataRequestOp.removeDataRequest.id);
        if (!dataFrame)
        {
            mResult.code(OperationResultCode::opNO_ENTRY);
            mResult.entryType() = LedgerEntryType::DATA;
            return false;
        }

        auto action = AccountRuleAction::REMOVE;
        if (!(getSourceID() == dataFrame->getData().owner))
        {
            action = AccountRuleAction::REMOVE_FOR_OTHER;
        }

        AccountRuleResource resource(LedgerEntryType::DATA);
        resource.data().type = dataFrame->getData().type;
        result.emplace_back(resource, action, mSourceAccount);

        return true;
    }

    bool RemoveDataRequestOpFrame::tryGetSignerRequirements(stellar::StorageHelper &storageHelper,
                                                            std::vector<SignerRequirement> &result) const {
        //todo
        return true;
    }

    void
    RemoveDataRequestOpFrame::pickResultCode(RemoveDataRequestResultCode code) {
        innerResult().code(code);
    }

    RemoveDataRequestResult&
    RemoveDataRequestOpFrame::innerResult() {
        return mResult.tr().removeDataRequestResult();
    }
}