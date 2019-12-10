#pragma once




// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ledger/EntryFrame.h"
#include <functional>
#include <unordered_map>
#include <stdio.h>
#include "ledger/AccountFrame.h"
#include "util/types.h"

namespace soci
{
    class session;
}

namespace stellar
{
class StatementContext;

class FeeFrame : public EntryFrame{

    FeeEntry& mFee;
    FeeFrame(FeeFrame const& from);

public:

    static const int64_t SUBTYPE_ANY = 0;

    typedef std::shared_ptr<FeeFrame> pointer;

    FeeFrame();
    FeeFrame(LedgerEntry const& from);

    FeeFrame& operator=(FeeFrame const& other);

    static pointer create(FeeType feeType, int64_t fixedFee, int64_t percentFee, AssetCode asset,
        AccountID* accountID = nullptr, uint64_t assetPrecision = 1);

    EntryFrame::pointer
    copy() const override
    {
        return EntryFrame::pointer(new FeeFrame(*this));
    }

    bool calculatePercentFee(uint64_t amount, uint64_t& result, Rounding rounding, uint64_t roundingStep) const;

    FeeEntry const&
    getFee() const
    {
        return mFee;
    }
    FeeEntry&
    getFee()
    {
        return mFee;
    }

    int64_t getPercentFee()
    {
        return mFee.percentFee;
    }

    int64_t getFixedFee()
    {
        return mFee.fixedFee;
    }

    static void checkFeeType(FeeEntry const& feeEntry, FeeType feeType);

    AssetCode getFeeAsset() const;

    static bool isValid(FeeEntry const& oe);
    bool isValid() const;

    static bool isInRange(int64_t a, int64_t b, int64_t point);

    static Hash calcHash(FeeType feeType, AssetCode asset, AccountID* accountID, uint64_t* accountType, int64_t subtype);

    LedgerKey const&
    getKey() const override;

};

}