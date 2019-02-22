#include "transactions/CreateAccountOpFrame.h"
#include <transactions/manage_asset/ManageAssetHelper.h>
#include <ledger/LedgerHeaderFrame.h>
#include <ledger/StorageHelper.h>
#include <ledger/SignerRuleFrame.h>
#include "ledger/AccountRoleHelper.h"
#include "ledger/AccountHelper.h"
#include "ledger/AssetHelper.h"
#include "ManageSignerOpFrame.h"

namespace stellar
{
using namespace std;
using xdr::operator==;

CreateAccountOpFrame::CreateAccountOpFrame(Operation const &op,
        OperationResult &res, TransactionFrame &parentTx)
        : OperationFrame(op, res, parentTx)
        , mCreateAccount(mOperation.body.createAccountOp())
{
}

bool
CreateAccountOpFrame::tryGetOperationConditions(StorageHelper &storageHelper,
                                    std::vector<OperationCondition> &result) const
{
    result.emplace_back(AccountRuleResource(LedgerEntryType::ACCOUNT),
                        AccountRuleAction::CREATE, mSourceAccount);

    return true;
}

bool
CreateAccountOpFrame::tryGetSignerRequirements(StorageHelper &storageHelper,
                                   std::vector<SignerRequirement> &result) const
{
    result.emplace_back(SignerRuleResource(LedgerEntryType::ACCOUNT),
                        SignerRuleAction::CREATE);

    return true;
}

void
CreateAccountOpFrame::trySetReferrer(Application& app, StorageHelper& storageHelper,
                                     AccountFrame::pointer accountFrame) const
{
    if (!mCreateAccount.referrer)
    {
        return;
    }

    const auto referrer = *mCreateAccount.referrer;
    if (referrer == app.getAdminID())
    {
        return;
    }

    if (!storageHelper.getAccountHelper().exists(referrer))
    {
        return;
    }

    accountFrame->setReferrer(referrer);
}

bool
CreateAccountOpFrame::createAccount(Application &app, StorageHelper& storageHelper)
{
    auto& headerFrame = storageHelper.mustGetLedgerDelta().getHeaderFrame();

    if (!checkRoleExisting(storageHelper))
    {
        return false;
    }

    auto accountFrame = make_shared<AccountFrame>(mCreateAccount.destination);
    auto& accountEntry = accountFrame->getAccount();
    accountEntry.sequentialID = headerFrame.generateID(LedgerEntryType::ACCOUNT);
    accountEntry.roleID = mCreateAccount.roleID;
    trySetReferrer(app, storageHelper, accountFrame);

    storageHelper.getAccountHelper().storeAdd(accountFrame->mEntry);

    innerResult().success().sequentialID = accountEntry.sequentialID;

    return true;
}

void
CreateAccountOpFrame::createBalances(StorageHelper& storageHelper)
{
    auto& assetHelper = storageHelper.getAssetHelper();

    std::vector<AssetFrame::pointer> baseAssets = assetHelper.loadBaseAssets();
    for (const auto &baseAsset : baseAssets)
    {
        ManageAssetHelper::createBalanceForAccount(mCreateAccount.destination,
                                                   baseAsset->getCode(),
                                                   storageHelper.getDatabase(),
                                                   storageHelper.mustGetLedgerDelta());
    }
}

bool
CreateAccountOpFrame::createSigners(Application &app,
                                    StorageHelper& storageHelper)
{
    auto accountFrame = storageHelper.getAccountHelper().mustLoadAccount(
            mCreateAccount.destination);

    Operation op;
    op.sourceAccount.activate() = accountFrame->getID();
    op.body.type(OperationType::MANAGE_SIGNER);
    ManageSignerOp& manageSignerOp = op.body.manageSignerOp();
    manageSignerOp.data.action(ManageSignerAction::CREATE);

    OperationResult opRes;
    opRes.code(OperationResultCode::opINNER);
    opRes.tr().type(OperationType::MANAGE_SIGNER);

    for (auto const& createData : mCreateAccount.signersData)
    {
        manageSignerOp.data.createData() = createData;

        ManageSignerOpFrame manageSignerOpFrame(op, opRes, mParentTx);

        manageSignerOpFrame.setSourceAccountPtr(accountFrame);

        if (!manageSignerOpFrame.doCheckValid(app) ||
            !manageSignerOpFrame.doApply(app, storageHelper, app.getLedgerManager()))
        {
            innerResult().code(CreateAccountResultCode::INVALID_SIGNER_DATA);
            innerResult().createSignerErrorCode() = ManageSignerOpFrame::getInnerCode(opRes);
            return false;
        }
    }

    return true;
}

bool
CreateAccountOpFrame::checkRoleExisting(StorageHelper& storageHelper)
{
    LedgerKey roleKey(LedgerEntryType::ACCOUNT_ROLE);
    roleKey.accountRole().id = mCreateAccount.roleID;

    auto& roleHelper = storageHelper.getAccountRoleHelper();
    if (!roleHelper.exists(roleKey))
    {
        innerResult().code(CreateAccountResultCode::NO_SUCH_ROLE);
        return false;
    }

    return true;
}

bool
CreateAccountOpFrame::doApply(Application &app, StorageHelper& storageHelper,
                              LedgerManager &ledgerManager)
{
    innerResult().code(CreateAccountResultCode::SUCCESS);

    auto& accountHelper = storageHelper.getAccountHelper();

    if (accountHelper.exists(mCreateAccount.destination))
    {
        innerResult().code(CreateAccountResultCode::ALREADY_EXISTS);
        return false;
    }

    if (!createAccount(app, storageHelper))
    {
        return false;
    }

    createBalances(storageHelper);

    return createSigners(app, storageHelper);
}

bool
CreateAccountOpFrame::doCheckValid(Application &app)
{
    if (mCreateAccount.destination == getSourceID())
    {
        innerResult().code(CreateAccountResultCode::INVALID_DESTINATION);
        return false;
    }

    if (mCreateAccount.signersData.empty())
    {
        innerResult().code(CreateAccountResultCode::NO_SIGNER_DATA);
        return false;
    }

    map<uint32_t, uint64_t> identityWeight;

    for (auto const& createData : mCreateAccount.signersData)
    {
        if (identityWeight[createData.identity] < createData.weight)
        {
            identityWeight[createData.identity] = createData.weight;
        }
    }

    uint64_t totalWeight = 0;

    for (auto const& pair : identityWeight)
    {
        totalWeight += pair.second;
    }

    if (totalWeight < SignerRuleFrame::threshold)
    {
        innerResult().code(CreateAccountResultCode::INVALID_WEIGHT);
        return false;
    }

    return true;
}
}
