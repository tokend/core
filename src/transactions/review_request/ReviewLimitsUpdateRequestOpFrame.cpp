// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "util/asio.h"
#include "ReviewLimitsUpdateRequestOpFrame.h"
#include "database/Database.h"
#include "ledger/LedgerDelta.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/AccountHelper.h"
#include <ledger/StorageHelperImpl.h>
#include "transactions/ManageLimitsOpFrame.h"
#include "main/Application.h"

namespace stellar
{

using namespace std;
using xdr::operator==;

ReviewLimitsUpdateRequestOpFrame::ReviewLimitsUpdateRequestOpFrame(Operation const& op, OperationResult& res,
                                                                   TransactionFrame& parentTx) :
    ReviewRequestOpFrame(op, res, parentTx)
{
}

bool
ReviewLimitsUpdateRequestOpFrame::handleManageLimitsResult(ManageLimitsResultCode manageLimitsResultCode)
{
    switch (manageLimitsResultCode)
    {
        case ManageLimitsResultCode::CANNOT_CREATE_FOR_ACC_ID_AND_ACC_TYPE:
        {
            innerResult().code(ReviewRequestResultCode::CANNOT_CREATE_FOR_ACC_ID_AND_ACC_TYPE);
            return false;
        }
        case ManageLimitsResultCode::INVALID_LIMITS:
        {
            innerResult().code(ReviewRequestResultCode::INVALID_LIMITS);
            return false;
        }
        case ManageLimitsResultCode::ACCOUNT_NOT_FOUND:
        {
            innerResult().code(ReviewRequestResultCode::ACCOUNT_NOT_FOUND);
            return false;
        }
        case ManageLimitsResultCode::ROLE_NOT_FOUND:
        {
            innerResult().code(ReviewRequestResultCode::ROLE_NOT_FOUND);
            return false;
        }
        case ManageLimitsResultCode::ASSET_NOT_FOUND:
        {
            innerResult().code(ReviewRequestResultCode::ASSET_DOES_NOT_EXISTS);
            return false;
        }
        default:
        {
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected result code from manage limits: "
                                                   << xdr::xdr_traits<ManageLimitsResultCode>::enum_name(manageLimitsResultCode);
            throw std::runtime_error("Unexpected result code from manage limits");
        }
    }
}

bool
ReviewLimitsUpdateRequestOpFrame::tryCallManageLimits(Application& app,
                                                      LedgerManager& ledgerManager, StorageHelper& storageHelper,
                                                      ReviewableRequestFrame::pointer request)
{
    auto requestorID = request->getRequestor();

    Operation op;
    op.body.type(OperationType::MANAGE_LIMITS);
    ManageLimitsOp& manageLimitsOp = op.body.manageLimitsOp();
    manageLimitsOp.details.action(ManageLimitsAction::CREATE);
    manageLimitsOp.details.limitsCreateDetails().accountID = mReviewRequest.requestDetails.limitsUpdate().newLimitsV2.accountID;
    manageLimitsOp.details.limitsCreateDetails().accountRole = mReviewRequest.requestDetails.limitsUpdate().newLimitsV2.accountRole;
    manageLimitsOp.details.limitsCreateDetails().statsOpType = mReviewRequest.requestDetails.limitsUpdate().newLimitsV2.statsOpType;
    manageLimitsOp.details.limitsCreateDetails().assetCode = mReviewRequest.requestDetails.limitsUpdate().newLimitsV2.assetCode;
    manageLimitsOp.details.limitsCreateDetails().isConvertNeeded = mReviewRequest.requestDetails.limitsUpdate().newLimitsV2.isConvertNeeded;
    manageLimitsOp.details.limitsCreateDetails().dailyOut = mReviewRequest.requestDetails.limitsUpdate().newLimitsV2.dailyOut;
    manageLimitsOp.details.limitsCreateDetails().weeklyOut = mReviewRequest.requestDetails.limitsUpdate().newLimitsV2.weeklyOut;
    manageLimitsOp.details.limitsCreateDetails().monthlyOut = mReviewRequest.requestDetails.limitsUpdate().newLimitsV2.monthlyOut;
    manageLimitsOp.details.limitsCreateDetails().annualOut = mReviewRequest.requestDetails.limitsUpdate().newLimitsV2.annualOut;

    OperationResult opRes;
    opRes.code(OperationResultCode::opINNER);
    opRes.tr().type(OperationType::MANAGE_LIMITS);
    ManageLimitsOpFrame manageLimitsOpFrame(op, opRes, mParentTx);

    auto& accountHelper = storageHelper.getAccountHelper();
    auto master = accountHelper.mustLoadAccount(app.getAdminID());
    manageLimitsOpFrame.setSourceAccountPtr(master);

    if (!manageLimitsOpFrame.doCheckValid(app) || !manageLimitsOpFrame.doApply(app, storageHelper, ledgerManager))
    {
        OperationResult& manageLimitsResult = manageLimitsOpFrame.getResult();
        auto manageLimitsResultCode = ManageLimitsOpFrame::getInnerCode(manageLimitsResult);
        return handleManageLimitsResult(manageLimitsResultCode);
    }

    auto reference = request->getReference();

    createReference(storageHelper, requestorID, reference);

    innerResult().code(ReviewRequestResultCode::SUCCESS);
    innerResult().success().fulfilled = true;
    return true;
}

bool ReviewLimitsUpdateRequestOpFrame::handleApprove(Application& app, StorageHelper& storageHelper,
                                                     LedgerManager& ledgerManager,
                                                     ReviewableRequestFrame::pointer request)
{
    request->checkRequestType(ReviewableRequestType::UPDATE_LIMITS);

    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    handleTasks(requestHelper, request);

    if (!request->canBeFulfilled(ledgerManager))
    {
        innerResult().code(ReviewRequestResultCode::SUCCESS);
        innerResult().success().fulfilled = false;
        return true;
    }

    requestHelper.storeDelete(request->getKey());

    auto requestorID = request->getRequestor();

    if (!storageHelper.getAccountHelper().exists(requestorID))
    {
        throw std::runtime_error("Expected account to exists");
    }

    return tryCallManageLimits(app, ledgerManager, storageHelper, request);
}

bool ReviewLimitsUpdateRequestOpFrame::handleReject(Application& app, StorageHelper& storageHelper,
                                                    LedgerManager& ledgerManager,
                                                    ReviewableRequestFrame::pointer request)
{
    request->checkRequestType(ReviewableRequestType::UPDATE_LIMITS);
    request->setRejectReason(mReviewRequest.reason);

    auto& requestEntry = request->getRequestEntry();
    const auto newHash = ReviewableRequestFrame::calculateHash(requestEntry.body);
    requestEntry.hash = newHash;

    storageHelper.getReviewableRequestHelper().storeChange(request->mEntry);

    innerResult().code(ReviewRequestResultCode::SUCCESS);
    return true;
}

}
