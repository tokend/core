#include "ManageSignerRuleOpFrame.h"
#include "database/Database.h"
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

    switch (mManageSignerRule.data.action())
    {
        case ManageSignerRuleAction::CREATE:
            details = mManageSignerRule.data.createData().details;
            break;
        case ManageSignerRuleAction::UPDATE:
            details = mManageSignerRule.data.updateData().details;
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

    return true;
}

bool
ManageSignerRuleOpFrame::tryGetOperationConditions(StorageHelper &storageHelper,
                                   std::vector<OperationCondition> &result) const
{
    result.emplace_back(AccountRuleResource(LedgerEntryType::SIGNER_RULE), "manage", mSourceAccount);

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

    result.emplace_back(resource, "manage");

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
    rule.isForbid = updateData.isForbid;
    rule.details = updateData.details;

    helper.storeChange(signerRuleFrame->mEntry);

    innerResult().code(ManageSignerRuleResultCode::SUCCESS);
    innerResult().success().ruleID = rule.id;

    return true;
}

bool
ManageSignerRuleOpFrame::createRule(Application &app,
                                     StorageHelper &storageHelper)
{
    auto& headerFrame = storageHelper.mustGetLedgerDelta().getHeaderFrame();

    LedgerEntry le;
    le.data.type(LedgerEntryType::SIGNER_RULE);
    auto& rule = le.data.signerRule();
    rule.id = headerFrame.generateID(LedgerEntryType::SIGNER_RULE);
    rule.resource = mManageSignerRule.data.createData().resource;
    rule.action = mManageSignerRule.data.createData().action;
    rule.isForbid = mManageSignerRule.data.createData().isForbid;
    rule.details = mManageSignerRule.data.createData().details;

    storageHelper.getSignerRuleHelper().storeAdd(le);

    innerResult().code(ManageSignerRuleResultCode::SUCCESS);
    innerResult().success().ruleID = rule.id;

    return true;
}

bool
ManageSignerRuleOpFrame::deleteRule(Application &app,
                                    StorageHelper &storageHelper)
{
    LedgerKey key(LedgerEntryType::SIGNER_RULE);
    auto ruleID = mManageSignerRule.data.removeData().ruleID;
    key.accountRule().id = ruleID;

    auto frame = storageHelper.getSignerRuleHelper().storeLoad(key);
    if (!frame)
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
    innerResult().success().ruleID = key.signerRule().id;
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