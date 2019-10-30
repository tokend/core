#include "FeeManager.h"
#include "ledger/FeeHelper.h"
#include "ledger/AssetHelper.h"
#include "ledger/StorageHelperImpl.h"
#include "main/Application.h"

namespace stellar
{

FeeManager::FeeManager(Application &app, StorageHelper& storageHelper)
        : mApp(app) , mSh(sh)
{
}

FeeManager::FeeResult
FeeManager::calculateFeeForAccount(const AccountFrame::pointer account,
                                   FeeType const feeType, AssetCode const &asset,
                                   int64_t const subtype, uint64_t const amount, Database &db)
{
    auto result = FeeResult{ 0, 0, 0, false };
    auto feeFrame = FeeHelper::Instance()->loadForAccount(feeType, asset, subtype, account, amount, db);
    if (!feeFrame)
    {
        return result;
    }

    StorageHelperImpl storageHelper(db, nullptr);
    auto feeAssetFrame = storageHelper.mustLoadAsset(asset);
    const uint64_t feeAssetPrecision = feeAssetFrame->getMinimumAmount();

    result.fixedFee = feeFrame->getFixedFee();
    result.percentFee = feeFrame->getPercentFee();
    result.isOverflow = !feeFrame->calculatePercentFee(amount, result.calculatedPercentFee, ROUND_UP, feeAssetPrecision);
    return result;
}

bool
FeeManager::isFeeMatches(const AccountFrame::pointer account, const Fee fee,
        const FeeType feeType, const int64_t subtype, const AssetCode assetCode,
        const uint64_t amount) const
{
    if (mApp.getAdminID() == account->getID())
    {
        return fee.fixed == 0 && fee.percent == 0;
    }

    auto feeFrame = FeeHelper::Instance()->loadForAccount(feeType, assetCode, subtype, account, amount, mDb);
    if (!feeFrame)
    {
        return fee.fixed == 0 && fee.percent == 0;
    }

    if (feeFrame->getFee().fixedFee != fee.fixed)
    {
        return false;
    }

    auto feeAssetFrame = mSh.getAssetHelper().mustLoadAsset(assetCode);

    // if we have overflow - fee does not match
    uint64_t expectedPercentFee = 0;
    if (!feeFrame->calculatePercentFee(amount, expectedPercentFee, Rounding::ROUND_UP,
                                       feeAssetFrame->getMinimumAmount()))
    {
        return false;
    }

    return fee.percent == expectedPercentFee;
}

}
