// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "transactions/ManageBalanceOpFrame.h"
#include "ledger/LedgerDelta.h"
#include "ledger/LedgerHeaderFrame.h"
#include "ledger/AccountHelper.h"
#include "ledger/AssetHelperLegacy.h"
#include "ledger/BalanceHelperLegacy.h"
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
    if (!(getSourceID() == mManageBalance.destination))
    {
        result.emplace_back(AccountRuleResource(LedgerEntryType::BALANCE), "create", mSourceAccount);
    }

    // account can create balance for him self without special rule
    return true;
}

ManageBalanceOpFrame::ManageBalanceOpFrame(Operation const& op,
                                           OperationResult& res,
                                           TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx)
    , mManageBalance(mOperation.body.manageBalanceOp())
{
}

bool
ManageBalanceOpFrame::doApply(Application& app,
                              LedgerDelta& delta, LedgerManager& ledgerManager)
{
    Database& db = ledgerManager.getDatabase();
    if (mManageBalance.action == ManageBalanceAction::CREATE_UNIQUE)
    {
        if (!ledgerManager.shouldUse(LedgerVersion::UNIQUE_BALANCE_CREATION))
        {
            innerResult().code(ManageBalanceResultCode::VERSION_IS_NOT_SUPPORTED_YET);
            return false;
        }

        const auto balance = BalanceHelperLegacy::Instance()->loadBalance(mManageBalance.destination, mManageBalance.asset, db, nullptr);
        if (!!balance)
        {
            innerResult().code(ManageBalanceResultCode::BALANCE_ALREADY_EXISTS);
            return false;
        }
    }

    auto accountHelper = AccountHelper::Instance();
    const AccountFrame::pointer destAccountFrame = accountHelper->
        loadAccount(delta, mManageBalance.destination, db);
    if (!destAccountFrame)
    {
        innerResult().code(ManageBalanceResultCode::DESTINATION_NOT_FOUND);
        return false;
    }

    auto balanceHelper = BalanceHelperLegacy::Instance();
    auto balanceFrame = balanceHelper->loadBalance(mManageBalance.destination,
                                                   mManageBalance.asset, db,
                                                   &delta);

    auto assetHelper = AssetHelperLegacy::Instance();
    const auto assetFrame = assetHelper->loadAsset(mManageBalance.asset, db);
    if (!assetFrame)
    {
        innerResult().code(ManageBalanceResultCode::ASSET_NOT_FOUND);
        return false;
    }

    auto sequentialID =
        delta.getHeaderFrame().generateID(LedgerEntryType ::BALANCE);
    const BalanceID newBalanceID = BalanceKeyUtils::forAccount(mManageBalance.
                                                               destination, sequentialID);
    balanceFrame = BalanceFrame::createNew(newBalanceID,
                                           mManageBalance.destination,
                                mManageBalance.asset, sequentialID);
    EntryHelperProvider::storeAddEntry(delta, db, balanceFrame->mEntry);
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
