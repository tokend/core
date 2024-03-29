#include "transactions/ManageLimitsOpFrame.h"
#include "ledger/AccountHelper.h"
#include "ledger/AccountRoleHelper.h"
#include "ledger/AssetHelper.h"
#include "ledger/LedgerDelta.h"
#include "ledger/LedgerHeaderFrame.h"
#include "ledger/StorageHelperImpl.h"
#include "main/Application.h"
#include <ledger/LimitsV2HelperImpl.h>

namespace stellar
{
using xdr::operator==;

ManageLimitsOpFrame::ManageLimitsOpFrame(Operation const& op,
                                         OperationResult& res,
                                         TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx)
    , mManageLimits(mOperation.body.manageLimitsOp())
{
}

bool
ManageLimitsOpFrame::tryGetOperationConditions(
    StorageHelper& storageHelper, std::vector<OperationCondition>& result) const
{
    result.emplace_back(AccountRuleResource(LedgerEntryType::LIMITS_V2),
                        AccountRuleAction::MANAGE, mSourceAccount);

    return true;
}

bool
ManageLimitsOpFrame::tryGetSignerRequirements(
    StorageHelper& storageHelper, std::vector<SignerRequirement>& result) const
{
    result.emplace_back(SignerRuleResource(LedgerEntryType::LIMITS_V2),
                        SignerRuleAction::MANAGE);

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
ManageLimitsOpFrame::doApply(Application& app, StorageHelper& storageHelper,
                             LedgerManager& ledgerManager)
{
    innerResult().code(ManageLimitsResultCode::SUCCESS);

    if (ledgerManager.shouldUse(LedgerVersion::MARK_ASSET_AS_DELETED))
    {
        if (mManageLimits.details.action() == ManageLimitsAction::CREATE &&
            !storageHelper.getAssetHelper().existActive(
                mManageLimits.details.limitsCreateDetails().assetCode))
        {
            innerResult().code(ManageLimitsResultCode::ASSET_NOT_FOUND);
            return false;
        }
    }

    auto& LimitsV2HelperImpl =  storageHelper.getLimitsV2Helper();
    auto& db = storageHelper.getDatabase();
    auto& delta = storageHelper.mustGetLedgerDelta();
    switch (mManageLimits.details.action())
    {
    case ManageLimitsAction::CREATE:
    {
        if (!checkAccountRoleExisting(storageHelper, ledgerManager))
        {
            return false;
        }

        auto limitsV2Frame = LimitsV2HelperImpl.loadLimits(
            mManageLimits.details.limitsCreateDetails().statsOpType,
            mManageLimits.details.limitsCreateDetails().assetCode,
            mManageLimits.details.limitsCreateDetails().accountID,
            mManageLimits.details.limitsCreateDetails().accountRole.get(),
            mManageLimits.details.limitsCreateDetails().isConvertNeeded);
        if (!limitsV2Frame)
        {
            uint64_t id =
                delta.getHeaderFrame().generateID(LedgerEntryType::LIMITS_V2);
            limitsV2Frame = LimitsV2Frame::createNew(id, mManageLimits);
            LimitsV2HelperImpl.storeAdd(limitsV2Frame->mEntry);
        }
        else
        {
            limitsV2Frame->changeLimits(mManageLimits);
            LimitsV2HelperImpl.storeChange(limitsV2Frame->mEntry);
        }

        innerResult().success().details.action(ManageLimitsAction::CREATE);
        innerResult().success().details.id() = limitsV2Frame->getID();
        break;
    }
    case ManageLimitsAction::REMOVE:
    {
        auto limitsV2FrameToRemove =
            LimitsV2HelperImpl.loadLimits(mManageLimits.details.id());
        if (!limitsV2FrameToRemove)
        {
            innerResult().code(ManageLimitsResultCode::NOT_FOUND);
            return false;
        }
        LimitsV2HelperImpl.storeDelete(limitsV2FrameToRemove->getKey());
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
ManageLimitsOpFrame::checkAccountRoleExisting(StorageHelper& storageHelper,
                                              LedgerManager& ledgerManager)
{
    if (!ledgerManager.shouldUse(LedgerVersion::CHECK_SET_FEE_ACCOUNT_EXISTING))
    {
        return true;
    }

    if (mManageLimits.details.action() != ManageLimitsAction::CREATE)
    {
        throw std::runtime_error("Expected action to be CREATE");
    }

    auto& details = mManageLimits.details.limitsCreateDetails();

    if (details.accountID)
    {
        if (!storageHelper.getAccountHelper().exists(*details.accountID))
        {
            innerResult().code(ManageLimitsResultCode::ACCOUNT_NOT_FOUND);
            return false;
        }
    }

    if (details.accountRole)
    {
        if (!storageHelper.getAccountRoleHelper().exists(*details.accountRole))
        {
            innerResult().code(ManageLimitsResultCode::ROLE_NOT_FOUND);
            return false;
        }
    }

    return true;
}

bool
ManageLimitsOpFrame::doCheckValid(Application& app)
{
    if ((mManageLimits.details.action() == ManageLimitsAction::CREATE) &&
        !!mManageLimits.details.limitsCreateDetails().accountID &&
        !!mManageLimits.details.limitsCreateDetails().accountRole)
    {
        innerResult().code(
            ManageLimitsResultCode::CANNOT_CREATE_FOR_ACC_ID_AND_ACC_TYPE);
        return false;
    }

    if ((mManageLimits.details.action() == ManageLimitsAction::CREATE) &&
        !isValidLimits())
    {
        innerResult().code(ManageLimitsResultCode::INVALID_LIMITS);
        return false;
    }

    return true;
}

bool
ManageLimitsOpFrame::isValidLimits()
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
