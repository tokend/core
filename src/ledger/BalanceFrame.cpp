// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "BalanceFrame.h"
#include "crypto/SecretKey.h"
#include "crypto/Hex.h"
#include "database/Database.h"
#include "LedgerDelta.h"
#include "ledger/LedgerManager.h"
#include "util/basen.h"
#include "util/types.h"
#include "lib/util/format.h"
#include <algorithm>
#include "AssetFrame.h"

using namespace soci;
using namespace std;

namespace stellar
{
using xdr::operator<;

BalanceFrame::BalanceFrame() : EntryFrame(LedgerEntryType::BALANCE), mBalance(mEntry.data.balance())
{
}

BalanceFrame::BalanceFrame(LedgerEntry const& from)
    : EntryFrame(from), mBalance(mEntry.data.balance())
{
}

BalanceFrame::BalanceFrame(BalanceFrame const& from) : BalanceFrame(from.mEntry)
{
}

BalanceFrame& BalanceFrame::operator=(BalanceFrame const& other)
{
    if (&other != this)
    {
        mBalance = other.mBalance;
        mKey = other.mKey;
        mKeyCalculated = other.mKeyCalculated;
    }
    return *this;
}

BalanceFrame::pointer BalanceFrame::createNew(BalanceID id, AccountID owner, AssetCode asset, uint64 ledgerCloseTime,
    uint64 initialAmount)
{
	LedgerEntry le;
	le.data.type(LedgerEntryType::BALANCE);
	BalanceEntry& entry = le.data.balance();

	entry.balanceID = id;
	entry.accountID = owner;
	entry.asset = asset;
	entry.amount = initialAmount;
	entry.locked = 0;
	return std::make_shared<BalanceFrame>(le);
}

bool
BalanceFrame::isValid(BalanceEntry const& oe)
{
    return AssetFrame::isAssetCodeValid(oe.asset) && oe.locked >= 0 && oe.amount >= 0;
}

bool
BalanceFrame::isValid() const
{
    return isValid(mBalance);
}


bool BalanceFrame::addBalance(int64_t delta)
{
	int64_t availableBalance = getAmount();
	if (availableBalance + delta < 0)
		return false;
	if (mBalance.amount + delta < 0)
		return false;
	mBalance.amount += delta;
    int64_t totalFunds = mBalance.amount + mBalance.locked;
    if (totalFunds < 0)
        return false;
	return true;
}

bool BalanceFrame::addLocked(int64_t delta)
{
	if (mBalance.locked + delta < 0)
		return false;
	mBalance.locked += delta;
    int64_t totalFunds = mBalance.amount + mBalance.locked;
    if (totalFunds < 0)
        return false;
	return true;
}

BalanceFrame::Result BalanceFrame::lockBalance(int64_t delta)
{
	int64_t availableBalance = getAmount();
	if (availableBalance - delta < 0)
		return Result::UNDERFUNDED;
    if (mBalance.locked + delta < 0)
		return Result::LINE_FULL;
	mBalance.amount -= delta;
    mBalance.locked += delta;
	return Result::SUCCESS;
}

bool BalanceFrame::tryFundAccount(uint64_t amount)
{
	uint64_t updatedAmount;
	if (!safeSum(mBalance.amount, amount, updatedAmount)) {
		return false;
	}

	uint64_t totalFunds;
	if (!safeSum(updatedAmount, mBalance.locked, totalFunds)) {
		return false;
	}

	mBalance.amount = updatedAmount;
	return true;
}

}

