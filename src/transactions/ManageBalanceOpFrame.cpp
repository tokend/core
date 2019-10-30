// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "transactions/ManageBalanceOpFrame.h"
#include "ledger/LedgerDelta.h"
#include "ledger/LedgerHeaderFrame.h"
#include "ledger/AccountHelper.h"
#include "ledger/AssetHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/StorageHelper.h"
#include "main/Application.h"

namespace stellar
{
using namespace std;
using xdr::operator==;


bool
ManageBalanceOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                                                std::vector<OperationCondition>& result) const
{
    AccountRuleResource resource(LedgerEntryType::BALANCE);

    if (getSourceID() == mManageBalance.destination)
    {
        result.emplace_back(resource, AccountRuleAction::CREATE, mSourceAccount);
        return true;
    }

    result.emplace_back(resource, AccountRuleAction::CREATE_FOR_OTHER, mSourceAccount);
    return true;
}

bool
ManageBalanceOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                               std::vector<SignerRequirement>& result) const
{
    SignerRuleResource resource(LedgerEntryType::BALANCE);

    if (getSourceID() == mManageBalance.destination)
    {
        result.emplace_back(resource, SignerRuleAction::CREATE);
        return true;
    }

    result.emplace_back(resource, SignerRuleAction::CREATE_FOR_OTHER);
    return true;
}

ManageBalanceOpFrame::ManageBalanceOpFrame(Operation const& op,
                                           OperationResult& res,
                                           TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx), mManageBalance(mOperation.body.manageBalanceOp())
{
}

bool
ManageBalanceOpFrame::doApply(Application& app,
                              StorageHelper& storageHelper, LedgerManager& ledgerManager)
{
    auto& balanceHelper = storageHelper.getBalanceHelper();

    if (mManageBalance.action == ManageBalanceAction::CREATE_UNIQUE)
    {
        const auto balance = balanceHelper.loadBalance(mManageBalance.destination, mManageBalance.asset);
        if (!!balance)
        {
            innerResult().code(ManageBalanceResultCode::BALANCE_ALREADY_EXISTS);
            return false;
        }
    }

    auto& accountHelper = storageHelper.getAccountHelper();
    const AccountFrame::pointer destAccountFrame = accountHelper.loadAccount(mManageBalance.destination);
    if (!destAccountFrame)
    {
        innerResult().code(ManageBalanceResultCode::DESTINATION_NOT_FOUND);
        return false;
    }

    auto balanceFrame = balanceHelper.loadBalance(mManageBalance.destination,
                                                  mManageBalance.asset);

    auto& assetHelper = storageHelper.getAssetHelper();
    const auto assetFrame = assetHelper.loadActiveAsset(mManageBalance.asset);
    if (!assetFrame)
    {
        innerResult().code(ManageBalanceResultCode::ASSET_NOT_FOUND);
        return false;
    }
    auto& delta = storageHelper.mustGetLedgerDelta();
    auto sequentialID =
        delta.getHeaderFrame().generateID(LedgerEntryType::BALANCE);
    const BalanceID newBalanceID = BalanceKeyUtils::forAccount(mManageBalance.
        destination, sequentialID);
    balanceFrame = BalanceFrame::createNew(newBalanceID,
                                           mManageBalance.destination,
                                           mManageBalance.asset, sequentialID);
    balanceHelper.storeAdd(balanceFrame->mEntry);
    innerResult().success().balanceID = newBalanceID;
    innerResult().code(ManageBalanceResultCode::SUCCESS);
    return true;
}

bool ManageBalanceOpFrame::doCheckValid(Application& app)
{
    if (mManageBalance.action == ManageBalanceAction::DELETE_BALANCE)
    {
        innerResult().code(ManageBalanceResultCode::MALFORMED);
        return false;
    }

    if (!AssetFrame::isAssetCodeValid(mManageBalance.asset))
    {
        innerResult().code(ManageBalanceResultCode::INVALID_ASSET);
        return false;
    }

    return true;
}
}
