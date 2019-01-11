#include "ManageAccountRuleOpFrame.h"
#include "database/Database.h"
#include "ledger/AccountRuleHelperImpl.h"
#include "ledger/LedgerDelta.h"
#include "ledger/LedgerHeaderFrame.h"
#include "main/Application.h"

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
    case ManageAccountRuleAction::UPDATE:
        return createOrUpdateRule(app, storageHelper);
    case ManageAccountRuleAction::REMOVE:
        return deleteAccountRule(app, storageHelper);
    default:
        throw std::runtime_error("Unknown action.");
    }
}

bool
ManageAccountRuleOpFrame::doCheckValid(Application& app)
{
    return isValidEnumValue(mManageAccountRule.data.action());
}

SourceDetails
ManageAccountRuleOpFrame::getSourceAccountDetails(
    std::unordered_map<AccountID, CounterpartyDetails> counterpartiesDetails,
    int32_t ledgerVersion) const
{
    // allow for any user
    return SourceDetails(
        getAllAccountTypes(), mSourceAccount->getMediumThreshold(),
        static_cast<int32_t>(SignerType::ACCOUNT_ROLE_PERMISSION_MANAGER));
}

std::unordered_map<AccountID, CounterpartyDetails>
ManageAccountRuleOpFrame::getCounterpartyDetails(
    Database& db, LedgerDelta* delta) const
{
    return {};
}

bool
ManageAccountRuleOpFrame::createOrUpdateRule(Application &app,
                                             StorageHelper &storageHelper)
{
    if (!storageHelper.getLedgerDelta())
    {
        throw std::runtime_error("Unable to process policy without ledger.");
    }
    LedgerHeaderFrame& headerFrame =
        storageHelper.getLedgerDelta()->getHeaderFrame();
    auto& helper = storageHelper.getAccountRuleHelper();

    LedgerEntry le;
    le.data.type(LedgerEntryType::ACCOUNT_RULE);

    auto& rule = le.data.accountRule();
    switch (mManageAccountRule.data.action())
    {
    case ManageAccountRuleAction::CREATE:
        rule.id = headerFrame.generateID(LedgerEntryType::ACCOUNT_RULE);
        rule.resource = mManageAccountRule.data.createData().resource;
        rule.action = mManageAccountRule.data.createData().action;
        rule.isForbid = mManageAccountRule.data.createData().isForbid;
        rule.details = mManageAccountRule.data.createData().details;
        break;
    case ManageAccountRuleAction::UPDATE:
        rule.id = mManageAccountRule.data.updateData().accountRuleID;
        rule.resource = mManageAccountRule.data.updateData().resource;
        rule.action = mManageAccountRule.data.updateData().action;
        rule.isForbid = mManageAccountRule.data.updateData().isForbid;
        rule.details = mManageAccountRule.data.updateData().details;
        break;
    default:
        throw std::runtime_error("Unexpected action type.");
    }

    innerResult().code(ManageAccountRuleResultCode::SUCCESS);
    innerResult().success().ruleID = le.data.accountRule().id;

    if (helper.exists(helper.getLedgerKey(le)))
    {
        helper.storeChange(le);
    }
    else
    {
        helper.storeAdd(le);
    }

    return true;
}

bool
ManageAccountRuleOpFrame::deleteAccountRule(Application &app,
                                            StorageHelper &storageHelper)
{
    LedgerKey key;
    key.type(LedgerEntryType::ACCOUNT_RULE);
    key.accountRule().id = mManageAccountRule.data.removeData().accountRuleID;

    auto frame = storageHelper.getAccountRuleHelper().storeLoad(key);
    if (!frame)
    {
        innerResult().code(ManageAccountRuleResultCode::NOT_FOUND);
        return false;
    }

    storageHelper.getAccountRuleHelper().storeDelete(frame->getKey());
    innerResult().code(ManageAccountRuleResultCode::SUCCESS);
    innerResult().success().ruleID = key.accountRule().id;
    return true;
}

} // namespace stellar