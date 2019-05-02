#include "FeesManager.h"
#include "ledger/FeeHelper.h"
#include "ledger/AssetHelperLegacy.h"

namespace stellar
{
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

    auto feeAssetFrame = AssetHelperLegacy::Instance()->mustLoadAsset(asset, db);
    const uint64_t feeAssetPrecision = feeAssetFrame->getMinimumAmount();

    result.fixedFee = feeFrame->getFixedFee();
    result.percentFee = feeFrame->getPercentFee();
    result.isOverflow = !feeFrame->calculatePercentFee(amount, result.calculatedPercentFee, ROUND_UP, feeAssetPrecision);
    return result;
}
}
