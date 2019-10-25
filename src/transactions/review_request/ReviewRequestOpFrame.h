#pragma once

// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "transactions/OperationFrame.h"
#include "ledger/ReviewableRequestFrame.h"

namespace stellar
{
class ReviewableRequestHelper;

class ReviewRequestOpFrame : public OperationFrame {
    bool isRejectReasonValid(Application& app);

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;
    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;
    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result,
                             LedgerManager& lm) const override;

protected:
    ReviewRequestResult&
    innerResult()
    {
        return mResult.tr().reviewRequestResult();
    }

    ReviewRequestOp const& mReviewRequest;

    virtual bool
    handleReject(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager, ReviewableRequestFrame::pointer request);
    virtual bool
    handlePermanentReject(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager, ReviewableRequestFrame::pointer request);
    virtual bool
    handleApprove(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager, ReviewableRequestFrame::pointer request)
    {
        throw std::runtime_error("There is no default implementation of handleApprove of Reviewable Request");
    }

    void handleTasks(ReviewableRequestHelper& reviewableRequestHelper, ReviewableRequestFrame::pointer request);

    // ensures that blocking rules are fulfilled, if not sets the error code and returns false
    bool
    areBlockingRulesFulfilled(ReviewableRequestFrame::pointer request, LedgerManager& lm, StorageHelper& storageHelper);

    // creates reference entry, throws excpetion if reference already exist. Throws expception if reference is null
    void
    createReference(StorageHelper& storageHelper, AccountID const& requestor, xdr::pointer<stellar::string64> reference);

public:

    ReviewRequestOpFrame(Operation const& op, OperationResult& res,
                         TransactionFrame& parentTx);

    static ReviewRequestOpFrame *makeHelper(Operation const& op, OperationResult& res, TransactionFrame& parentTx);

    bool doApply(Application& app, StorageHelper& storageHelper,
                 LedgerManager& ledgerManager) override;
    bool doCheckValid(Application& app) override;

    static ReviewRequestResultCode
    getInnerCode(OperationResult const& res)
    {
        return res.tr().reviewRequestResult().code();
    }

    std::string getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<ReviewRequestResultCode>::enum_name(innerResult().code());
    }

    static uint64_t getTotalFee(uint64_t requestID, Fee fee);

    bool removingExistingTasks(ReviewableRequestEntry& requestEntry);

};
}
