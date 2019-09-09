#pragma once

#include "ledger/AccountFrame.h"

namespace stellar
{

class FeeManager
{
public:
    struct FeeResult {
        uint64_t fixedFee;
        uint64_t percentFee;
        uint64_t calculatedPercentFee;
        bool isOverflow;
    };

    static FeeResult calculateFeeForAccount(const AccountFrame::pointer account, FeeType const feeType,
                                            AssetCode const &asset,
                                            int64_t const subtype, uint64_t const amount, Database &db);

};
}
