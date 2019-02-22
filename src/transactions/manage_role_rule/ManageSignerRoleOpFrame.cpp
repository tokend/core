#include "ManageSignerRoleOpFrame.h"
#include "ledger/LedgerDelta.h"
#include "ledger/LedgerHeaderFrame.h"
#include "ledger/StorageHelper.h"
#include "ledger/SignerRoleHelper.h"
#include "ledger/SignerRuleHelper.h"
#include "ledger/SignerHelper.h"
#include "main/Application.h"

namespace stellar
{
using namespace std;

ManageSignerRoleOpFrame::ManageSignerRoleOpFrame(Operation const& op,
        OperationResult& res, TransactionFrame& parentTx)
        : OperationFrame(op, res, parentTx)
        , mManageSignerRole(mOperation.body.manageSignerRoleOp())
{
}

bool
ManageSignerRoleOpFrame::tryGetOperationConditions(StorageHelper &storageHelper,
                                                   std::vector<OperationCondition> &result) const
{
    result.emplace_back(AccountRuleResource(LedgerEntryType::SIGNER_ROLE),
                        AccountRuleAction::MANAGE, mSourceAccount);

    return true;
}

bool
ManageSignerRoleOpFrame::tryGetSignerRequirements(StorageHelper &storageHelper,
                                                  std::vector<SignerRequirement> &result) const
{
    uint64_t roleID = 0;

    switch (mManageSignerRole.data.action())
    {
        case ManageSignerRoleAction::CREATE:
            break;
        case ManageSignerRoleAction::UPDATE:
            roleID = mManageSignerRole.data.updateData().roleID;
            break;
        case ManageSignerRoleAction::REMOVE:
            roleID = mManageSignerRole.data.removeData().roleID;
            break;
        default:
            throw std::runtime_error("Unexpected action in manage signer rule");
    }

    SignerRuleResource resource(LedgerEntryType::SIGNER_ROLE);
    resource.signerRole().roleID = roleID;

    result.emplace_back(resource, SignerRuleAction::MANAGE);

    return true;
}

bool
ManageSignerRoleOpFrame::checkRulesExisting(StorageHelper &storageHelper,
                                            std::vector<uint64_t> ruleIDs)
{
    auto& ruleHelper = storageHelper.getSignerRuleHelper();

    for (auto const ruleID : ruleIDs)
    {
        if (!ruleHelper.exists(ruleID))
        {
            innerResult().code(ManageSignerRoleResultCode::NO_SUCH_RULE);
            innerResult().ruleID() = ruleID;
            return false;
        }
    }

    return true;
}

AccountID
ManageSignerRoleOpFrame::getOwnerID(Application& app, CreateSignerRoleData data)
{
    if ((app.getAdminID() == getSourceID()) && data.isReadOnly)
    {
        return app.getLedgerManager().getNotExistingAccountID();
    }

    return getSourceID();
}

bool
ManageSignerRoleOpFrame::tryObtainRuleIDs(StorageHelper &storageHelper,
                                          std::vector<uint64_t> incomingIDs,
                                          std::vector<uint64_t> &result)
{
    std::unordered_set<uint64_t> ruleIDs;
    for (auto id : incomingIDs)
    {
        if (ruleIDs.find(id) != ruleIDs.end())
        {
            innerResult().code(ManageSignerRoleResultCode::RULE_ID_DUPLICATION);
            innerResult().ruleID() = id;
            return false;
        }

        ruleIDs.insert(id);
    }

    if (!checkRulesExisting(storageHelper, incomingIDs))
    {
        return false;
    }

    auto defaultRuleIDs = storageHelper.getSignerRuleHelper().loadDefaultRuleIDs();

    for (auto id : defaultRuleIDs)
    {
        if (ruleIDs.find(id) != ruleIDs.end())
        {
            innerResult().code(ManageSignerRoleResultCode::DEFAULT_RULE_ID_DUPLICATION);
            innerResult().ruleID() = id;
            return false;
        }

        ruleIDs.insert(id);
    }

    result.clear();
    for (auto id : ruleIDs)
    {
        result.emplace_back(id);
    }

    return true;
}

bool
ManageSignerRoleOpFrame::createRole(Application& app,
                                    StorageHelper& storageHelper)
{
    auto creationData = mManageSignerRole.data.createData();

    auto& headerFrame = storageHelper.mustGetLedgerDelta().getHeaderFrame();

    LedgerEntry le;
    le.data.type(LedgerEntryType::SIGNER_ROLE);
    auto& roleEntry = le.data.signerRole();
    roleEntry.id = headerFrame.generateID(LedgerEntryType::SIGNER_ROLE);

    if (!tryObtainRuleIDs(storageHelper, creationData.ruleIDs, roleEntry.ruleIDs))
    {
        return false;
    }

    roleEntry.details = creationData.details;
    roleEntry.ownerID = getOwnerID(app, creationData);

    storageHelper.getSignerRoleHelper().storeAdd(le);

    innerResult().code(ManageSignerRoleResultCode::SUCCESS);
    innerResult().success().roleID = roleEntry.id;

    return true;
}

bool
ManageSignerRoleOpFrame::updateRole(Application& app,
                                    StorageHelper& storageHelper)
{
    auto& helper = storageHelper.getSignerRoleHelper();
    auto updateData = mManageSignerRole.data.updateData();

    auto role = helper.loadSignerRole(updateData.roleID);
    if (!role || !(role->getOwnerID() == getSourceID()))
    {
        innerResult().code(ManageSignerRoleResultCode::NOT_FOUND);
        return false;
    }

    auto& roleEntry = role->getEntry();

    if (!tryObtainRuleIDs(storageHelper, updateData.ruleIDs, roleEntry.ruleIDs))
    {
        return false;
    }

    roleEntry.details = updateData.details;

    helper.storeChange(role->mEntry);

    innerResult().code(ManageSignerRoleResultCode::SUCCESS);
    innerResult().success().roleID = updateData.roleID;

    return true;
}

bool
ManageSignerRoleOpFrame::deleteRole(Application& app,
                                    StorageHelper& storageHelper)
{
    auto& data = mManageSignerRole.data.removeData();
    auto& signerHelper = storageHelper.getSignerHelper();

    if (signerHelper.isRoleIDUsed(data.roleID))
    {
        innerResult().code(ManageSignerRoleResultCode::ROLE_IS_USED);
        return false;
    }

    LedgerKey key(LedgerEntryType::SIGNER_ROLE);
    key.signerRole().id = data.roleID;

    auto& signerRoleHelper = storageHelper.getSignerRoleHelper();
    if (!signerRoleHelper.exists(key))
    {
        innerResult().code(ManageSignerRoleResultCode::NOT_FOUND);
        return false;
    }

    signerRoleHelper.storeDelete(key);

    innerResult().code(ManageSignerRoleResultCode::SUCCESS);
    innerResult().success().roleID = data.roleID;

    return true;
}

bool
ManageSignerRoleOpFrame::doApply(Application& app,
                                  StorageHelper& storageHelper,
                                  LedgerManager& ledgerManager)
{
    switch (mManageSignerRole.data.action())
    {
        case ManageSignerRoleAction::CREATE:
            return createRole(app, storageHelper);
        case ManageSignerRoleAction::UPDATE:
            return updateRole(app, storageHelper);
        case ManageSignerRoleAction::REMOVE:
            return deleteRole(app, storageHelper);
        default:
            throw std::runtime_error("Unknown action in manage account role");
    }
}

bool
ManageSignerRoleOpFrame::doCheckValid(Application& app)
{
    std::string details;
    size_t ruleIDsCount;

    switch (mManageSignerRole.data.action())
    {
        case ManageSignerRoleAction::CREATE:
            details = mManageSignerRole.data.createData().details;
            ruleIDsCount = mManageSignerRole.data.createData().ruleIDs.size();
            break;
        case ManageSignerRoleAction::UPDATE:
            details = mManageSignerRole.data.updateData().details;
            ruleIDsCount = mManageSignerRole.data.updateData().ruleIDs.size();
            break;
        case ManageSignerRoleAction::REMOVE:
            return true;
        default:
            throw std::runtime_error("Unexpected action in manage account role");
    }

    if (!isValidJson(details))
    {
        innerResult().code(ManageSignerRoleResultCode::INVALID_DETAILS);
        return false;
    }

    if (ruleIDsCount > app.getSignerRuleIDsMaxCount())
    {
        innerResult().code(ManageSignerRoleResultCode::TOO_MANY_RULE_IDS);
        innerResult().maxRuleIDsCount() = app.getSignerRuleIDsMaxCount();
        return false;
    }

    return true;
}
} // namespace stellar
