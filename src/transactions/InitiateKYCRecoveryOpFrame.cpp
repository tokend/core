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
    return true;
}

bool
InitiateKYCRecoveryOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                                     std::vector<SignerRequirement>& result) const
{
    //todo
    SignerRuleResource resource(LedgerEntryType::ACCOUNT_KYC);
    result.emplace_back(resource, SignerRuleAction::CREATE_FOR_OTHER);

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

    clearSigners(storageHelper);

    createSigner(storageHelper, *accountFrame);

    //todo: delete all pending KYC Recovery requests

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
InitiateKYCRecoveryOpFrame::clearSigners(StorageHelper& storageHelper)
{
    auto& signerHelper = storageHelper.getSignerHelper();
    auto signers = signerHelper.loadSigners(mInitiateKYCRecoveryOp.account);
    for (auto& s : signers)
    {
        LedgerKey key(LedgerEntryType::SIGNER);
        key.signer().accountID = mInitiateKYCRecoveryOp.account;
        key.signer().pubKey = s->getEntry().pubKey;
        signerHelper.storeDelete(key);
    }
}

void
InitiateKYCRecoveryOpFrame::createSigner(StorageHelper& storageHelper, AccountFrame& accountFrame)
{
    SignerFrame signerFrame;
    signerFrame.getEntry().pubKey = mInitiateKYCRecoveryOp.singer;
    signerFrame.getEntry().weight = 1000;
    signerFrame.getEntry().identity = 1;
    signerFrame.getEntry().roleID = 1;
    signerFrame.getEntry().accountID = accountFrame.getID();

    auto& signerHelper = storageHelper.getSignerHelper();
    signerHelper.storeAdd(signerFrame.mEntry);
}

void
InitiateKYCRecoveryOpFrame::deletePendingRecoveryRequests(Application& app, StorageHelper& storageHelper)
{
    auto reviewableRequestHelper = ReviewableRequestHelper::Instance();
    auto& db = storageHelper.getDatabase();
    auto& delta = storageHelper.mustGetLedgerDelta();
    auto requests = reviewableRequestHelper->loadRequests(app.getAdminID(), ReviewableRequestType::KYC_RECOVERY, db);
    for (auto& rec : requests)
    {
        auto recovery = rec->getRequestEntry().body.kycRecoveryRequest();
        if (recovery.targetAccount == mInitiateKYCRecoveryOp.account)
        {
            reviewableRequestHelper->storeDelete(delta, db, rec->getKey());
        }
    }
}

}
