#pragma once

#include <ledger/ReviewableRequestFrame.h>
#include "transactions/OperationFrame.h"

namespace stellar
{

class CreateChangeRoleRequestOpFrame : public OperationFrame
{
    CreateChangeRoleRequestOp mCreateChangeRoleRequestOp;

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;

    CreateChangeRoleRequestResult&
    innerResult()
    {
        return mResult.tr().createChangeRoleRequestResult();
    }

    std::string getReference() const;

    void createRequest(ReviewableRequestEntry &requestEntry, uint32 defaultMask);

    void updateRequest(ReviewableRequestEntry &requestEntry);

    bool updateChangeRoleRequest(Database &db, LedgerDelta &delta,
                                 Application &app);

    void tryAutoApprove(Database &db, LedgerDelta &delta, Application &app,
                        ReviewableRequestFrame::pointer requestFrame);

    bool ensureDestinationNotChanged(ReviewableRequestEntry &requestEntry);

    std::vector<longstring>
    makeTasksKeyVector(StorageHelper &storageHelper) override;

public:
    CreateChangeRoleRequestOpFrame(Operation const &op, OperationResult &res, TransactionFrame &parentTx);

    bool doApply(Application &app, LedgerDelta &delta, LedgerManager &ledgerManager) override;

    bool doCheckValid(Application &app) override;

    static CreateChangeRoleRequestResultCode getInnerCode(OperationResult const &res)
    {
        return res.tr().createChangeRoleRequestResult().code();
    }

    std::string getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<CreateChangeRoleRequestResultCode>::enum_name(innerResult().code());
    }
};
}