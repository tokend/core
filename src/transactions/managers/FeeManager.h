#pragma once

#include "ledger/AccountFrame.h"

namespace stellar
{
class Application;

class FeeManager
{
    Application& mApp;
    Database& mDb;

public:
    struct FeeResult
    {
        uint64_t fixedFee;
        uint64_t percentFee;
        uint64_t calculatedPercentFee;
        bool isOverflow;
    };

    FeeManager(Application& app, Database& db);

    static FeeResult
    calculateFeeForAccount(const AccountFrame::pointer account, FeeType const feeType,
            AssetCode const &asset, int64_t const subtype, uint64_t const amount, Database &db);

    bool
    isFeeMatches(AccountFrame::pointer account, Fee fee, FeeType feeType,
            int64_t subtype, AssetCode assetCode, uint64_t amount) const;

};
}