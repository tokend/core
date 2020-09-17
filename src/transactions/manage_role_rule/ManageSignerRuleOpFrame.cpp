#include "ManageSignerRuleOpFrame.h"
#include "ledger/SignerRuleHelper.h"
#include "ledger/LedgerDelta.h"
#include "ledger/LedgerHeaderFrame.h"
#include "main/Application.h"
#include "ledger/AccountRoleHelper.h"
#include "ledger/StorageHelper.h"

namespace stellar
{

using namespace std;
using xdr::operator==;

ManageSignerRuleOpFrame::ManageSignerRuleOpFrame(const Operation& op,
        OperationResult& res, TransactionFrame& parentTx)
        : OperationFrame(op, res, parentTx)
        , mManageSignerRule(mOperation.body.manageSignerRuleOp())
{
}

bool
ManageSignerRuleOpFrame::doApply(Application& app,
                                  StorageHelper& storageHelper,
                                  LedgerManager& ledgerManager)
{
    switch (mManageSignerRule.data.action())
    {
        case ManageSignerRuleAction::CREATE:
            return createRule(app, storageHelper);
        case ManageSignerRuleAction::UPDATE:
            return updateRule(app, storageHelper);
        case ManageSignerRuleAction::REMOVE:
            return deleteRule(app, storageHelper);
        default:
            throw std::runtime_error("Unknown action in manage signer rule");
    }
}

bool
ManageSignerRuleOpFrame::doCheckValid(Application& app)
{
    std::string details;
    SignerRuleAction action;
    SignerRuleResource resource;

    switch (mManageSignerRule.data.action())
    {
        case ManageSignerRuleAction::CREATE:
            details = mManageSignerRule.data.createData().details;
            action = mManageSignerRule.data.createData().action;
            resource = mManageSignerRule.data.createData().resource;
            break;
        case ManageSignerRuleAction::UPDATE:
            details = mManageSignerRule.data.updateData().details;
            action = mManageSignerRule.data.updateData().action;
            resource = mManageSignerRule.data.updateData().resource;
            break;
        case ManageSignerRuleAction::REMOVE:
            return true;
        default:
            throw std::runtime_error("Unexpected action in manage signer rule");
    }

    if (!isValidJson(details))
    {
        innerResult().code(ManageSignerRuleResultCode::INVALID_DETAILS);
        return false;
    }

    if (action == SignerRuleAction::CUSTOM &&
        resource.type() != LedgerEntryType::CUSTOM)
    {
        innerResult().code(ManageSignerRuleResultCode::INVALID_ACTION);
        return false;
    }

    return true;
}

bool
ManageSignerRuleOpFrame::tryGetOperationConditions(StorageHelper &storageHelper,
                                   std::vector<OperationCondition> &result) const
{
    result.emplace_back(AccountRuleResource(LedgerEntryType::SIGNER_RULE),
                        AccountRuleAction::MANAGE, mSourceAccount);

    return true;
}

bool
ManageSignerRuleOpFrame::tryGetSignerRequirements(StorageHelper &storageHelper,
                                  std::vector<SignerRequirement> &result) const
{
    bool isDefault;

    switch (mManageSignerRule.data.action())
    {
        case ManageSignerRuleAction::CREATE:
            isDefault = mManageSignerRule.data.createData().isDefault;
            break;
        case ManageSignerRuleAction::UPDATE:
        {
            auto updateData = mManageSignerRule.data.updateData();
            isDefault = updateData.isDefault;
            auto ruleFrame = storageHelper.getSignerRuleHelper().loadSignerRule(
                    updateData.ruleID);
            if (!ruleFrame)
            {
                mResult.code(OperationResultCode::opNO_ENTRY);
                mResult.entryType() = LedgerEntryType::SIGNER_RULE;
                return false;
            }
            isDefault = isDefault || ruleFrame->isDefault();
            break;
        }
        case ManageSignerRuleAction::REMOVE:
        {
            auto ruleFrame = storageHelper.getSignerRuleHelper().loadSignerRule(
                    mManageSignerRule.data.removeData().ruleID);
            if (!ruleFrame) {
                mResult.code(OperationResultCode::opNO_ENTRY);
                mResult.entryType() = LedgerEntryType::SIGNER_RULE;
                return false;
            }
            isDefault = ruleFrame->isDefault();
            break;
        }
        default:
            throw std::runtime_error("Unexpected action in manage signer rule");
    }

    SignerRuleResource resource(LedgerEntryType::SIGNER_RULE);
    resource.signerRule().isDefault = isDefault;

    result.emplace_back(resource, SignerRuleAction::MANAGE);

    return true;
}

bool
ManageSignerRuleOpFrame::updateRule(Application &app,
                                    StorageHelper &storageHelper)
{
    auto updateData = mManageSignerRule.data.updateData();

    auto& helper = storageHelper.getSignerRuleHelper();
    auto signerRuleFrame = helper.loadSignerRule(updateData.ruleID);
    if (!signerRuleFrame || !(signerRuleFrame->getOwnerID() == getSourceID()))
    {
        innerResult().code(ManageSignerRuleResultCode::NOT_FOUND);
        return false;
    }

    auto& rule = signerRuleFrame->getEntry();
    rule.resource = updateData.resource;
    rule.action = updateData.action;
    rule.forbids = updateData.forbids;
    rule.details = updateData.details;

    helper.storeChange(signerRuleFrame->mEntry);

    innerResult().code(ManageSignerRuleResultCode::SUCCESS);
    innerResult().success().ruleID = rule.id;

    return true;
}

AccountID
ManageSignerRuleOpFrame::getOwnerID(Application& app, CreateSignerRuleData data)
{
    if ((app.getAdminID() == getSourceID()) && data.isReadOnly)
    {
        return app.getLedgerManager().getNotExistingAccountID();
    }

    return getSourceID();
}

bool
ManageSignerRuleOpFrame::createRule(Application &app,
                                     StorageHelper &storageHelper)
{
    auto data = mManageSignerRule.data.createData();

    auto& headerFrame = storageHelper.mustGetLedgerDelta().getHeaderFrame();

    auto signerRuleFrame = std::make_shared<SignerRuleFrame>(
            headerFrame.generateID(LedgerEntryType::SIGNER_RULE),
            getOwnerID(app, data), data);

    storageHelper.getSignerRuleHelper().storeAdd(signerRuleFrame->mEntry);

    innerResult().code(ManageSignerRuleResultCode::SUCCESS);
    innerResult().success().ruleID = signerRuleFrame->getID();

    return true;
}

bool
ManageSignerRuleOpFrame::deleteRule(Application &app,
                                    StorageHelper &storageHelper)
{
    auto ruleID = mManageSignerRule.data.removeData().ruleID;

    auto frame = storageHelper.getSignerRuleHelper().loadSignerRule(ruleID);
    if (!frame || !(frame->getOwnerID() == getSourceID()))
    {
        innerResult().code(ManageSignerRuleResultCode::NOT_FOUND);
        return false;
    }

    if (isRuleUsed(storageHelper, ruleID))
    {
        return false;
    }

    storageHelper.getSignerRuleHelper().storeDelete(frame->getKey());
    innerResult().code(ManageSignerRuleResultCode::SUCCESS);
    innerResult().success().ruleID = ruleID;
    return true;
}

bool
ManageSignerRuleOpFrame::isRuleUsed(StorageHelper &storageHelper, uint64_t ruleID)
{
    auto& roleHelper = storageHelper.getAccountRoleHelper();

    auto roleIDs = roleHelper.loadRoleIDsByRule(ruleID);

    if (roleIDs.empty())
    {
        return false;
    }

    innerResult().code(ManageSignerRuleResultCode::RULE_IS_USED);
    innerResult().roleIDs().assign(roleIDs.begin(), roleIDs.end());
    return true;
}

} // namespace stellar