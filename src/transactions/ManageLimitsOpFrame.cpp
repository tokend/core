#include <ledger/LimitsV2Helper.h>
#include "transactions/ManageLimitsOpFrame.h"
#include "main/Application.h"
#include "ledger/LedgerDelta.h"
#include "ledger/LedgerHeaderFrame.h"

namespace stellar
{
using xdr::operator==;

ManageLimitsOpFrame::ManageLimitsOpFrame(Operation const& op, OperationResult& res,
                                     TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx)
    , mManageLimits(mOperation.body.manageLimitsOp())
{
}

bool
ManageLimitsOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                                std::vector<OperationCondition>& result) const
{
    result.emplace_back(AccountRuleResource(LedgerEntryType::LIMITS_V2), "manage", mSourceAccount);

    return true;
}

std::string
ManageLimitsOpFrame::getInnerResultCodeAsStr()
{
    const auto result = getResult();
    const auto code = getInnerCode(result);
    return xdr::xdr_traits<ManageLimitsResultCode>::enum_name(code);
}

bool
ManageLimitsOpFrame::doApply(Application& app, LedgerDelta& delta,
                             LedgerManager& ledgerManager)
{
    innerResult().code(ManageLimitsResultCode::SUCCESS);

    Database& db = ledgerManager.getDatabase();
    auto limitsV2Helper = LimitsV2Helper::Instance();

    switch (mManageLimits.details.action())
    {
    case ManageLimitsAction::CREATE:
    {
        auto limitsV2Frame = limitsV2Helper->loadLimits(db, mManageLimits.details.limitsCreateDetails().statsOpType,
                                                        mManageLimits.details.limitsCreateDetails().assetCode,
                                                        mManageLimits.details.limitsCreateDetails().accountID,
                                                        mManageLimits.details.limitsCreateDetails().accountType,
                                                        mManageLimits.details.limitsCreateDetails().isConvertNeeded,
                                                        &delta);
        if (!limitsV2Frame) {
            uint64_t id = delta.getHeaderFrame().generateID(LedgerEntryType::LIMITS_V2);
            limitsV2Frame = LimitsV2Frame::createNew(id, mManageLimits);
            limitsV2Helper->storeAdd(delta, db, limitsV2Frame->mEntry);
        }
        else
        {
            limitsV2Frame->changeLimits(mManageLimits);
            limitsV2Helper->storeChange(delta, db, limitsV2Frame->mEntry);
        }

        innerResult().success().details.action(ManageLimitsAction::CREATE);
        innerResult().success().details.id() = limitsV2Frame->getID();
        break;
    }
    case ManageLimitsAction::REMOVE:
    {
        auto limitsV2FrameToRemove = limitsV2Helper->loadLimits(mManageLimits.details.id(), db, &delta);
        if (!limitsV2FrameToRemove) {
            innerResult().code(ManageLimitsResultCode::NOT_FOUND);
            return false;
        }
        limitsV2Helper->storeDelete(delta, db, limitsV2FrameToRemove->getKey());
        innerResult().success().details.action(ManageLimitsAction::REMOVE);
        break;
    }
    default:
        throw std::runtime_error("Unexpected manage limits action in doApply. "
                                 "Expected UPDATE or REMOVE");
    }

    return true;
}

bool
ManageLimitsOpFrame::doCheckValid(Application& app)
{
    if ((mManageLimits.details.action() == ManageLimitsAction::CREATE) &&
        !!mManageLimits.details.limitsCreateDetails().accountID &&
        !!mManageLimits.details.limitsCreateDetails().accountType)
    {
        innerResult().code(ManageLimitsResultCode::CANNOT_CREATE_FOR_ACC_ID_AND_ACC_TYPE);
        return false;
    }
    
    if ((mManageLimits.details.action() == ManageLimitsAction::CREATE) && !isValidLimits())
    {
        innerResult().code(ManageLimitsResultCode::INVALID_LIMITS);
        return false;
    }

    return true;
}

bool ManageLimitsOpFrame::isValidLimits()
{
    if (mManageLimits.details.limitsCreateDetails().dailyOut < 0)
        return false;
    if (mManageLimits.details.limitsCreateDetails().weeklyOut <
        mManageLimits.details.limitsCreateDetails().dailyOut)
        return false;
    if (mManageLimits.details.limitsCreateDetails().monthlyOut <
        mManageLimits.details.limitsCreateDetails().weeklyOut)
        return false;
    return mManageLimits.details.limitsCreateDetails().annualOut >=
           mManageLimits.details.limitsCreateDetails().monthlyOut;
}

}
