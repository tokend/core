// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "BalanceFrame.h"
#include "AssetFrame.h"

using namespace std;

namespace stellar
{
using xdr::operator<;

static const uint64 kPrecisionBase = 10;

BalanceFrame::BalanceFrame()
    : EntryFrame(LedgerEntryType::BALANCE), mBalance(mEntry.data.balance())
{
}

BalanceFrame::BalanceFrame(LedgerEntry const& from)
    : EntryFrame(from), mBalance(mEntry.data.balance())
{
}

BalanceFrame::BalanceFrame(BalanceFrame const& from) : BalanceFrame(from.mEntry)
{
}

BalanceFrame&
BalanceFrame::operator=(BalanceFrame const& other)
{
    if (&other != this)
    {
        mBalance = other.mBalance;
        mKey = other.mKey;
        mKeyCalculated = other.mKeyCalculated;
    }
    return *this;
}

BalanceFrame::pointer
BalanceFrame::createNew(BalanceID id, AccountID owner, AssetCode asset, uint64 sequentialID)
{
    LedgerEntry le;
    le.data.type(LedgerEntryType::BALANCE);
    BalanceEntry& entry = le.data.balance();

    entry.balanceID = id;
    entry.accountID = owner;
    entry.asset = asset;
    entry.amount = 0;
    entry.locked = 0;
    entry.sequentialID = sequentialID;

    auto framePtr = std::make_shared<BalanceFrame>(le);
    framePtr->setPrecisionForAmounts(0);
    return framePtr;
}

bool
BalanceFrame::isValid(BalanceEntry const& oe)
{
    return AssetFrame::isAssetCodeValid(oe.asset) && oe.locked >= 0 &&
           oe.amount >= 0;
}

bool
BalanceFrame::isValid() const
{
    return isValid(mBalance);
}

uint64_t
BalanceFrame::getTotal() const
{
    uint64_t totalAmount;
    if (!safeSum(mBalance.amount, mBalance.locked, totalAmount))
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER)
            << "Unexpected state: "
            << "total balance amount overflows UINT64_MAX, balance id: "
            << BalanceKeyUtils::toStrKey(mBalance.balanceID);
        throw runtime_error("Unexpected state: "
                            "total balance amount overflows UINT64_MAX");
    }

    return totalAmount;
}

void
BalanceFrame::setPrecisionForAmounts(uint32 precisionExponent)
{
    uint64 precision = 1;
    while (precisionExponent != 0)
    {
        precision *= kPrecisionBase;
        precisionExponent--;
    }
    mPrecisionToUse = std::make_unique<uint64_t>(precision);
}

uint64
BalanceFrame::getMinimumAmount()
{
    return mPrecisionToUse ? *mPrecisionToUse : 1;
}

BalanceFrame::Result
BalanceFrame::tryFundAccount(uint64_t amount)
{
    if (!checkPrecisionForAmount(amount))
    {
        return Result::NONMATCHING_PRECISION;
    }

    uint64_t updatedAmount;
    if (!safeSum(mBalance.amount, amount, updatedAmount))
    {
        return Result::LINE_FULL;
    }

    uint64_t totalFunds;
    if (!safeSum(updatedAmount, mBalance.locked, totalFunds))
    {
        return Result::LINE_FULL;
    }

    mBalance.amount = updatedAmount;
    return Result::SUCCESS;
}

BalanceFrame::Result
BalanceFrame::tryLock(const uint64_t amountToBeLocked)
{
    if (!checkPrecisionForAmount(amountToBeLocked))
    {
        return Result::NONMATCHING_PRECISION;
    }
    if (mBalance.amount < amountToBeLocked)
    {
        return Result::UNDERFUNDED;
    }

    mBalance.amount -= amountToBeLocked;

    uint64_t updatedLockedAmount;
    if (!safeSum(mBalance.locked, amountToBeLocked, updatedLockedAmount))
    {
        return Result::LINE_FULL;
    }

    mBalance.locked = updatedLockedAmount;
    return Result::SUCCESS;
}

BalanceFrame::Result
BalanceFrame::tryChargeFromLocked(uint64_t amountToCharge)
{
    if (!checkPrecisionForAmount(amountToCharge))
    {
        return Result::NONMATCHING_PRECISION;
    }
    if (mBalance.locked < amountToCharge)
    {
        return Result::UNDERFUNDED;
    }

    mBalance.locked -= amountToCharge;
    return Result::SUCCESS;
}

BalanceFrame::Result
BalanceFrame::unlock(const uint64_t amountToUnlock)
{
    if (!checkPrecisionForAmount(amountToUnlock))
    {
        return Result::NONMATCHING_PRECISION;
    }
    if (mBalance.locked < amountToUnlock)
    {
        return Result::UNDERFUNDED;
    }

    mBalance.locked -= amountToUnlock;
    return tryFundAccount(amountToUnlock);
}
BalanceFrame::Result
BalanceFrame::tryCharge(uint64_t amountToCharge)
{
    if (!checkPrecisionForAmount(amountToCharge))
    {
        return Result::NONMATCHING_PRECISION;
    }
    if (mBalance.amount < amountToCharge)
    {
        return Result::UNDERFUNDED;
    }
    mBalance.amount -= amountToCharge;
    return Result::SUCCESS;
}

bool BalanceFrame::checkPrecisionForAmount(stellar::uint64 amount)
{
    if (!mPrecisionToUse)
    {
        throw std::runtime_error("Precision is not set.");
    }

    return amount % *mPrecisionToUse == 0;
}

std::ostream& operator<<(std::ostream& stream, const BalanceFrame::Result& result)
{
    switch (result)
    {
        case BalanceFrame::Result::SUCCESS:
            return stream << "SUCCESS";
        case BalanceFrame::Result::LINE_FULL:
            return stream << "LINE_FULL";
        case BalanceFrame::Result::UNDERFUNDED:
            return stream << "UNDERFUNDED";
        case BalanceFrame::Result::NONMATCHING_PRECISION:
            return stream << "NONMATCHING_PRECISION";
        default:
            throw std::runtime_error("Unknown result type.");
    }
}

LedgerKey const &
BalanceFrame::getKey() const
{
    if (!mKeyCalculated) {
        mKey = LedgerKey(LedgerEntryType::BALANCE);
        mKey.balance().balanceID = mBalance.balanceID;
        mKeyCalculated = true;
    }
    return mKey;
}

} // namespace stellar