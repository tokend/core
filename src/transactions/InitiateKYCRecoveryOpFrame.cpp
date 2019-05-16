#include "InitiateKYCRecoveryOpFrame.h"
#include <ledger/ReviewableRequestHelper.h>
#include "ledger/AccountHelper.h"
#include "ledger/StorageHelper.h"
#include "ledger/SignerHelper.h"
#include "ledger/SignerRoleHelper.h"
#include "ledger/AccountRoleHelper.h"
#include "ledger/KeyValueHelper.h"
#include <lib/xdrpp/xdrpp/marshal.h>
#include <crypto/SHA.h>
#include "xdrpp/printer.h"
#include "ledger/LedgerDelta.h"
#include "ledger/SignerRuleFrame.h"
#include "transactions/review_request/ReviewRequestHelper.h"
#include "ledger/KeyValueHelperLegacy.h"
#include "ManageKeyValueOpFrame.h"
#include "ManageSignerOpFrame.h"
#include "CreateKYCRecoveryRequestOpFrame.h"

namespace stellar
{
using namespace std;
using xdr::operator==;

InitiateKYCRecoveryOpFrame::InitiateKYCRecoveryOpFrame(
    Operation const& op, OperationResult& res, TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx), mInitiateKYCRecoveryOp(mOperation.body.initiateKYCRecoveryOp())
{
}

bool
InitiateKYCRecoveryOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                                                      std::vector<OperationCondition>& result) const
{
    AccountRuleResource resource(LedgerEntryType::INITIATE_KYC_RECOVERY);
    result.emplace_back(resource, AccountRuleAction::CREATE, mSourceAccount);

    return true;
}

bool
InitiateKYCRecoveryOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                                     std::vector<SignerRequirement>& result) const
{
    SignerRuleResource resource(LedgerEntryType::INITIATE_KYC_RECOVERY);
    result.emplace_back(resource, SignerRuleAction::CREATE);

    return true;
}

bool
InitiateKYCRecoveryOpFrame::doCheckValid(Application& app)
{
    return true;
}

bool
InitiateKYCRecoveryOpFrame::doApply(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager)
{
    if (!(mSourceAccount->getID() == app.getAdminID()))
    {
        innerResult().code(InitiateKYCRecoveryResultCode::NOT_AUTHORIZED);
        return false;
    }

    if (!isRecoveryAllowed(storageHelper))
    {
        innerResult().code(InitiateKYCRecoveryResultCode::RECOVERY_NOT_ALLOWED);
        return false;
    }

    uint64_t accountRole;
    if (!getRecoveryAccountRole(storageHelper, accountRole))
    {
        innerResult().code(InitiateKYCRecoveryResultCode::RECOVERY_ACCOUNT_ROLE_NOT_FOUND);
        return false;
    }

    auto& accountHelper = storageHelper.getAccountHelper();
    auto accountFrame = accountHelper.loadAccount(mInitiateKYCRecoveryOp.account);
    if (!accountFrame)
    {
        innerResult().code(InitiateKYCRecoveryResultCode::NOT_FOUND);
        return false;
    }

    handleSigners(app, storageHelper, accountFrame);

    deletePendingRecoveryRequests(app, storageHelper);

    accountFrame->setAccountRole(accountRole);
    accountHelper.storeChange(accountFrame->mEntry);

    innerResult().code(InitiateKYCRecoveryResultCode::SUCCESS);
    return true;
}

bool
InitiateKYCRecoveryOpFrame::isRecoveryAllowed(StorageHelper& storageHelper)
{
    auto& keyValueHelper = storageHelper.getKeyValueHelper();

    auto key = ManageKeyValueOpFrame::makeKYCRecoveryKey();
    auto recoveryEnabled = keyValueHelper.loadKeyValue(key);
    if (!recoveryEnabled)
    {
        return false;
    }

    auto value = recoveryEnabled->mustGetUint32Value();

    return value != 0;

}

bool
InitiateKYCRecoveryOpFrame::getRecoveryAccountRole(StorageHelper& storageHelper, uint64_t& roleID)
{
    roleID = 0;
    auto& keyValueHelper = storageHelper.getKeyValueHelper();

    auto key = ManageKeyValueOpFrame::makeKYCRecoveryAccountRoleKey();
    auto recoveryRole = keyValueHelper.loadKeyValue(key);
    if (!recoveryRole)
    {
        return false;
    }

    auto value = recoveryRole->getKeyValue().value;
    if (value.type() != KeyValueEntryType::UINT64)
    {
        return false;
    }
    roleID = value.ui64Value();

    LedgerKey ledgerKey;
    ledgerKey.type(LedgerEntryType::ACCOUNT_ROLE);
    ledgerKey.accountRole().id = roleID;

    return storageHelper.getAccountRoleHelper().exists(ledgerKey);
}

void
InitiateKYCRecoveryOpFrame::handleSigners(Application& app, StorageHelper& storageHelper, AccountFrame::pointer accountFrame)
{
    Operation op;
    op.sourceAccount.activate() = accountFrame->getID();
    op.body.type(OperationType::MANAGE_SIGNER);
    ManageSignerOp& manageSignerOp = op.body.manageSignerOp();
    manageSignerOp.data.action(ManageSignerAction::CREATE);

    OperationResult opRes;
    opRes.code(OperationResultCode::opINNER);
    opRes.tr().type(OperationType::MANAGE_SIGNER);

    auto& signerHelper = storageHelper.getSignerHelper();
    auto signers = signerHelper.loadSigners(mInitiateKYCRecoveryOp.account);

    for (auto& s : signers)
    {
        RemoveSignerData removeData;
        removeData.publicKey = s->getEntry().pubKey;
        manageSignerOp.data.removeData() = removeData;

        ManageSignerOpFrame manageSignerOpFrame(op, opRes, mParentTx);

        manageSignerOpFrame.setSourceAccountPtr(accountFrame);

        if (!manageSignerOpFrame.doCheckValid(app) ||
            !manageSignerOpFrame.doApply(app, storageHelper, app.getLedgerManager()))
        {
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected state: Failed to delete existing signers of account";
            throw std::runtime_error("Failed to delete existing signers");
        }
    }
    manageSignerOp.data.action(ManageSignerAction::CREATE);

    UpdateSignerData createData;
    createData.publicKey = mInitiateKYCRecoveryOp.signer;
    createData.weight = 1000;
    createData.identity = 1;
    createData.roleID = 1;

    manageSignerOp.data.createData() = createData;

    ManageSignerOpFrame manageSignerOpFrame(op, opRes, mParentTx);

    manageSignerOpFrame.setSourceAccountPtr(accountFrame);

    if (!manageSignerOpFrame.doCheckValid(app) ||
        !manageSignerOpFrame.doApply(app, storageHelper, app.getLedgerManager()))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected state: Failed to create recovery signer for account";
        throw std::runtime_error("Failed to create recovery signer");
    }
}


// KYC recovery request can be created by either admin or account itself. Thus we need to check for pending requests
// existence and delete them beforehand
void
InitiateKYCRecoveryOpFrame::deletePendingRecoveryRequests(Application& app, StorageHelper& storageHelper)
{
    auto reviewableRequestHelper = ReviewableRequestHelper::Instance();
    auto& db = storageHelper.getDatabase();
    auto& delta = storageHelper.mustGetLedgerDelta();

    auto targetAccRequest =
        reviewableRequestHelper->loadRequest(mInitiateKYCRecoveryOp.account,
            CreateKYCRecoveryRequestOpFrame::getReference(mInitiateKYCRecoveryOp.account), db, &delta);
    if(targetAccRequest){
        reviewableRequestHelper->storeDelete(delta, db, targetAccRequest->getKey());
    }

    auto adminID = app.getAdminID();

    auto adminRequest =
        reviewableRequestHelper->loadRequest(adminID,
            CreateKYCRecoveryRequestOpFrame::getReference(mInitiateKYCRecoveryOp.account), db, &delta);
    if(adminRequest){
        reviewableRequestHelper->storeDelete(delta, db, adminRequest->getKey());
    }
}

}
