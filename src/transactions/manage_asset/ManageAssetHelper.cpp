#include <ledger/BalanceHelperLegacy.h>
#include <ledger/LedgerHeaderFrame.h>
#include "ManageAssetHelper.h"
#include "transactions/AccountManager.h"

namespace stellar
{

void ManageAssetHelper::createSystemBalances(AssetCode assetCode, Application &app,
                                            LedgerDelta &delta)
{
    auto& db = app.getDatabase();
    AccountManager::loadOrCreateBalanceForAsset(app.getAdminID(), assetCode, db, delta);
}

void ManageAssetHelper::createBalanceForAccount(AccountID account,
    AssetCode assetCode, Application& app, LedgerDelta& delta)
{
    createBalanceForAccount(
            account,
            assetCode,
            app.getDatabase(),
            delta
    );
}

    void ManageAssetHelper::createBalanceForAccount(AccountID account, AssetCode assetCode, Database &db,
                                                    LedgerDelta &delta) {
        auto balanceFrame = BalanceHelperLegacy::Instance()->loadBalance(account, assetCode, db, &delta);
        if (!!balanceFrame)
            return;
        auto sequentialID =
            delta.getHeaderFrame().generateID(LedgerEntryType::BALANCE);
        const BalanceID balanceID =
            BalanceKeyUtils::forAccount(account, sequentialID);
        balanceFrame = BalanceFrame::createNew(balanceID, account, assetCode,
                                               sequentialID);

        EntryHelperProvider::storeAddEntry(delta, db, balanceFrame->mEntry);
    }
}


