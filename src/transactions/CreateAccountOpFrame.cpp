// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <transactions/manage_asset/ManageAssetHelper.h>
#include <ledger/LedgerHeaderFrame.h>
#include <ledger/StorageHelperImpl.h>
#include "transactions/CreateAccountOpFrame.h"
#include "ledger/AccountHelperLegacy.h"
#include "ledger/AssetHelperLegacy.h"
#include "ledger/AccountRoleHelper.h"

namespace stellar {
    using namespace std;
    using xdr::operator==;

    CreateAccountOpFrame::CreateAccountOpFrame(Operation const &op,
                                               OperationResult &res,
                                               TransactionFrame &parentTx)
            : OperationFrame(op, res, parentTx), mCreateAccount(mOperation.body.createAccountOp()) {
    }

    bool
    CreateAccountOpFrame::tryGetOperationConditions(StorageHelper &storageHelper,
                                    std::vector<OperationCondition> &result) const
    {
        result.emplace_back(AccountRuleResource(LedgerEntryType::ACCOUNT), "create", mSourceAccount);

        return true;
    }

    bool CreateAccountOpFrame::createAccount(Application &app, LedgerDelta &delta,
                                             LedgerManager &ledgerManager) {
        auto &db = app.getDatabase();
        StorageHelperImpl storageHelper(db, &delta);

        if (!checkRoleExisting(storageHelper))
        {
            return false;
        }

        auto destAccountFrame = make_shared<AccountFrame>(mCreateAccount.destination);
        auto& accountEntry = destAccountFrame->getAccount();
        accountEntry.sequentialID =
                delta.getHeaderFrame().generateID(LedgerEntryType::ACCOUNT);
        accountEntry.roleID = mCreateAccount.roleID;

        //save recovery accountID
        destAccountFrame->setRecoveryID(mCreateAccount.recoveryKey);

        EntryHelperProvider::storeAddEntry(delta, db, destAccountFrame->mEntry);
        // create balance for all available base assets
        createBalance(delta, db);
        return true;
    }

    void CreateAccountOpFrame::createBalance(LedgerDelta &delta, Database &db) {
        std::vector<AssetFrame::pointer> baseAssets;
        AssetHelperLegacy::Instance()->loadBaseAssets(baseAssets, db);
        for (const auto &baseAsset : baseAssets) {
            ManageAssetHelper::createBalanceForAccount(mCreateAccount.destination, baseAsset->getCode(), db, delta);
        }
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
    CreateAccountOpFrame::doApply(Application &app,
                                  LedgerDelta &delta, LedgerManager &ledgerManager) {
        Database &db = ledgerManager.getDatabase();
        innerResult().code(CreateAccountResultCode::SUCCESS);

        if (!ledgerManager.shouldUse(mCreateAccount.ext.v())) {
            innerResult().code(CreateAccountResultCode::INVALID_ACCOUNT_VERSION);
            return false;
        }

        if (AccountHelperLegacy::Instance()->exists(mCreateAccount.destination, db))
        {
            innerResult().code(CreateAccountResultCode::ALREADY_EXISTS);
            return false;
        }

        return createAccount(app, delta, ledgerManager);
    }

    bool CreateAccountOpFrame::doCheckValid(Application &app) {
        if (mCreateAccount.destination == getSourceID()) {
            innerResult().code(CreateAccountResultCode::MALFORMED);
            return false;
        }

        if (mCreateAccount.recoveryKey == mCreateAccount.destination) {
            innerResult().code(CreateAccountResultCode::MALFORMED);
            return false;
        }

        if (mCreateAccount.accountType == AccountType::NOT_VERIFIED &&
            mCreateAccount.policies != 0) {
            innerResult().code(CreateAccountResultCode::NOT_VERIFIED_CANNOT_HAVE_POLICIES);
            return false;
        }

        if (isSystemAccountType(mCreateAccount.accountType)) {
            innerResult().code(CreateAccountResultCode::TYPE_NOT_ALLOWED);
            return false;
        }

        return true;
    }
}
