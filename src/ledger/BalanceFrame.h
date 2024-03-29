#pragma once

// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ledger/EntryFrame.h"

namespace stellar
{

class BalanceFrame : public EntryFrame
{
    BalanceEntry& mBalance;

    BalanceFrame(BalanceFrame const& from);

  public:
    typedef std::shared_ptr<BalanceFrame> pointer;

    BalanceFrame();
    BalanceFrame(LedgerEntry const& from);

    LedgerKey const&
    getKey() const override;

    BalanceFrame& operator=(BalanceFrame const& other);

    EntryFrame::pointer
    copy() const override
    {
        return EntryFrame::pointer(new BalanceFrame(*this));
    }

    BalanceEntry const&
    getBalance() const
    {
        return mBalance;
    }

    uint64_t
    getAmount()
    {
        return mBalance.amount;
    }

    uint64_t
    getLocked()
    {
        return mBalance.locked;
    }

    AssetCode
    getAsset()
    {
        return mBalance.asset;
    }

    AccountID
    getAccountID()
    {
        return mBalance.accountID;
    }

    BalanceID
    getBalanceID()
    {
        return mBalance.balanceID;
    }

    uint64_t getTotal() const;

    static bool isValid(BalanceEntry const& oe);
    bool isValid() const;

    enum class Result
    {
        SUCCESS,
        LINE_FULL,
        UNDERFUNDED,
        NONMATCHING_PRECISION
    };

    // Sets the precision to be used in methods that modify amounts as
    // 10 in power precisionExponent.
    // These methods will throw without precision set, but
    // the frame without a precision is still considered valid.
    void setPrecisionForAmounts(uint32 precisionExponent);
    // Returns minimum amount that this balance can be changed according,
    // to precision, or 1 if precision was not set.
    uint64 getMinimumAmount();

    // Adds amount to current account.
    Result tryFundAccount(uint64_t amount);
    // Moves amount from current account to locked account.
    Result tryLock(uint64_t amountToBeLocked);
    // Charges amount from locked account.
    Result tryChargeFromLocked(uint64_t amountToCharge);
    // Moves amount from locked account to current account.
    Result unlock(uint64_t amountToUnlock);
    // Charges amount from current account.
    Result tryCharge(uint64_t amountToCharge);

    static pointer createNew(BalanceID id, AccountID owner, AssetCode asset,
                             uint64 sequentialID);

  private:
    // Returns false if the amount provided is too precise for precision that
    // was previously set by setPrecisionForAmounts().
    // Throws if this precision was not set.
    bool checkPrecisionForAmount(uint64 amount);
    std::unique_ptr<uint64> mPrecisionToUse;
};

std::ostream& operator<<(std::ostream& stream, const BalanceFrame::Result& result);
} // namespace stellar
