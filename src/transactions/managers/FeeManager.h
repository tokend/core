#pragma once

#include "ledger/AccountFrame.h"
#include "ledger/StorageHelper.h"

namespace stellar
{
class Application;

class FeeManager
{
    Application& mApp;
    StorageHelper& mSh;

public:
    struct FeeResult
    {
        uint64_t fixedFee;
        uint64_t percentFee;
        uint64_t calculatedPercentFee;
        bool isOverflow;
    };

    FeeManager(Application& app, StorageHelper& sh);

    static FeeResult
    calculateFeeForAccount(StorageHelper& storageHelper, const AccountFrame::pointer account, FeeType const feeType,
            AssetCode const &asset, int64_t const subtype, uint64_t const amount);

    bool
    isFeeMatches(StorageHelper& storageHelper, AccountFrame::pointer account, Fee fee, FeeType feeType,
            int64_t subtype, AssetCode assetCode, uint64_t amount) const;

};
}
