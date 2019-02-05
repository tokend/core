#include "ManageAccountRuleOpFrame.h"
#include "ledger/AccountRuleHelper.h"
#include "ledger/LedgerDelta.h"
#include "ledger/LedgerHeaderFrame.h"
#include "ledger/StorageHelper.h"
#include "ledger/AccountRoleHelper.h"

namespace stellar
{

using namespace std;
using xdr::operator==;

ManageAccountRuleOpFrame::ManageAccountRuleOpFrame(
    const Operation& op, OperationResult& res, TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx)
    , mManageAccountRule(mOperation.body.manageAccountRuleOp())
{
}

bool
ManageAccountRuleOpFrame::doApply(Application& app,
                                  StorageHelper& storageHelper,
                                  LedgerManager& ledgerManager)
{
    switch (mManageAccountRule.data.action())
    {
    case ManageAccountRuleAction::CREATE:
        return createRule(app, storageHelper);
    case ManageAccountRuleAction::UPDATE:
        return updateRule(app, storageHelper);
    case ManageAccountRuleAction::REMOVE:
        return deleteAccountRule(app, storageHelper);
    default:
        throw std::runtime_error("Unknown action in manage account rule");
    }
}

bool
ManageAccountRuleOpFrame::doCheckValid(Application& app)
{
    std::string details;

    switch (mManageAccountRule.data.action())
    {
        case ManageAccountRuleAction::CREATE:
            details = mManageAccountRule.data.createData().details;
            break;
        case ManageAccountRuleAction::UPDATE:
            details = mManageAccountRule.data.updateData().details;
            break;
        case ManageAccountRuleAction::REMOVE:
            return true;
        default:
            throw std::runtime_error("Unexpected action in manage account rule");
    }

    if (!isValidJson(details))
    {
        innerResult().code(ManageAccountRuleResultCode::INVALID_DETAILS);
        return false;
    }

    return true;
}

bool
ManageAccountRuleOpFrame::tryGetOperationConditions(StorageHelper &storageHelper,
                                    std::vector<OperationCondition> &result) const
{
    result.emplace_back(AccountRuleResource(LedgerEntryType::ACCOUNT_RULE), "manage", mSourceAccount);

    return true;
}

bool
ManageAccountRuleOpFrame::updateRule(Application &app,
                                     StorageHelper &storageHelper)
{
    LedgerKey ruleKey(LedgerEntryType::ACCOUNT_RULE);
    ruleKey.accountRule().id = mManageAccountRule.data.updateData().accountRuleID;

    auto& helper = storageHelper.getAccountRuleHelper();
    if (!helper.exists(ruleKey))
    {
        innerResult().code(ManageAccountRuleResultCode::NOT_FOUND);
        return false;
    }

    LedgerEntry le;
    le.data.type(LedgerEntryType::ACCOUNT_RULE);
    auto& rule = le.data.accountRule();
    rule.id = mManageAccountRule.data.updateData().accountRuleID;
    rule.resource = mManageAccountRule.data.updateData().resource;
    rule.action = mManageAccountRule.data.updateData().action;
    rule.isForbid = mManageAccountRule.data.updateData().isForbid;
    rule.details = mManageAccountRule.data.updateData().details;

    helper.storeChange(le);

    innerResult().code(ManageAccountRuleResultCode::SUCCESS);
    innerResult().success().ruleID = le.data.accountRule().id;

    return true;
}

bool
ManageAccountRuleOpFrame::createRule(Application &app,
                                     StorageHelper &storageHelper)
{
    auto& headerFrame = storageHelper.mustGetLedgerDelta().getHeaderFrame();

    LedgerEntry le;
    le.data.type(LedgerEntryType::ACCOUNT_RULE);
    auto& rule = le.data.accountRule();
    rule.id = headerFrame.generateID(LedgerEntryType::ACCOUNT_RULE);
    rule.resource = mManageAccountRule.data.createData().resource;
    rule.action = mManageAccountRule.data.createData().action;
    rule.isForbid = mManageAccountRule.data.createData().isForbid;
    rule.details = mManageAccountRule.data.createData().details;

    storageHelper.getAccountRuleHelper().storeAdd(le);

    innerResult().code(ManageAccountRuleResultCode::SUCCESS);
    innerResult().success().ruleID = rule.id;

    return true;
}

bool
ManageAccountRuleOpFrame::deleteAccountRule(Application &app,
                                            StorageHelper &storageHelper)
{
    LedgerKey key;
    key.type(LedgerEntryType::ACCOUNT_RULE);
    auto ruleID = mManageAccountRule.data.removeData().accountRuleID;
    key.accountRule().id = ruleID;

    auto frame = storageHelper.getAccountRuleHelper().storeLoad(key);
    if (!frame)
    {
        innerResult().code(ManageAccountRuleResultCode::NOT_FOUND);
        return false;
    }

    if (isRuleUsed(storageHelper, ruleID))
    {
        return false;
    }

    storageHelper.getAccountRuleHelper().storeDelete(frame->getKey());
    innerResult().code(ManageAccountRuleResultCode::SUCCESS);
    innerResult().success().ruleID = key.accountRule().id;
    return true;
}

bool
ManageAccountRuleOpFrame::isRuleUsed(StorageHelper &storageHelper, uint64_t ruleID)
{
    auto& roleHelper = storageHelper.getAccountRoleHelper();

    auto roleIDs = roleHelper.loadRoleIDsByRule(ruleID);

    if (roleIDs.empty())
    {
        return false;
    }

    innerResult().code(ManageAccountRuleResultCode::RULE_IS_USED);
    innerResult().roleIDs().assign(roleIDs.begin(), roleIDs.end());
    return true;
}

} // namespace stellar