#pragma once

#include <ledger/ReviewableRequestFrame.h>
#include "transactions/OperationFrame.h"

namespace stellar
{

class CreateKYCRecoveryRequestOpFrame : public OperationFrame
{
    CreateKYCRecoveryRequestOp mCreateKYCRecoveryRequestOp;

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;

    CreateKYCRecoveryRequestResult&
    innerResult()
    {
        return mResult.tr().createKYCRecoveryRequestResult();
    }

    std::string getReference() const;

    void createRequest(ReviewableRequestEntry &requestEntry, uint32 defaultMask);

    std::vector<longstring>
    makeTasksKeyVector(StorageHelper &storageHelper) override;


    void
    tryAutoApprove(Database &db, LedgerDelta &delta, Application &app,
                    ReviewableRequestFrame::pointer requestFrame);

    bool
    updateRecoveryRequest(StorageHelper& storageHelper,
                    Application &app);
    bool
    ensureTargetNotChanged(ReviewableRequestEntry &requestEntry);

    void
    updateRequest(ReviewableRequestEntry &requestEntry);

public:
    CreateKYCRecoveryRequestOpFrame(Operation const &op, OperationResult &res, TransactionFrame &parentTx);

    bool doApply(Application &app, StorageHelper& storageHelper, LedgerManager &ledgerManager) override;

    bool doCheckValid(Application &app) override;

    static CreateKYCRecoveryRequestResultCode getInnerCode(OperationResult const &res)
    {
        return res.tr().createKYCRecoveryRequestResult().code();
    }

    std::string getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<CreateKYCRecoveryRequestResultCode>::enum_name(innerResult().code());
    }
};
}
