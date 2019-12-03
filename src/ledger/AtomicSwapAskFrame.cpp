#include "AtomicSwapAskFrame.h"
#include "AssetFrame.h"

using namespace std;

namespace stellar
{

AtomicSwapAskFrame::AtomicSwapAskFrame()
        : EntryFrame(LedgerEntryType::ATOMIC_SWAP_ASK),
          mAtomicSwapAsk(mEntry.data.atomicSwapAsk())
{
}

AtomicSwapAskFrame::AtomicSwapAskFrame(LedgerEntry const &from)
        : EntryFrame(from), mAtomicSwapAsk(mEntry.data.atomicSwapAsk())
{
}

AtomicSwapAskFrame::AtomicSwapAskFrame(const stellar::AtomicSwapAskFrame &from)
        : AtomicSwapAskFrame(from.mEntry)
{
}

AtomicSwapAskFrame&
AtomicSwapAskFrame::operator=(AtomicSwapAskFrame const &other)
{
    if (&other != this)
    {
        mAtomicSwapAsk = other.mAtomicSwapAsk;
        mKey = other.mKey;
        mKeyCalculated = other.mKeyCalculated;
    }
    return *this;
}

EntryFrame::pointer
AtomicSwapAskFrame::copy() const
{
    return EntryFrame::pointer(new AtomicSwapAskFrame(*this));
}

AtomicSwapAskEntry&
AtomicSwapAskFrame::getAtomicSwapAsk()
{
    return mAtomicSwapAsk;
}

uint64_t
AtomicSwapAskFrame::getID() const
{
    return mAtomicSwapAsk.id;
}

AccountID
AtomicSwapAskFrame::getOwnerID() const
{
    return mAtomicSwapAsk.ownerID;
}

AssetCode AtomicSwapAskFrame::getBaseAsset() const
{
    return mAtomicSwapAsk.baseAsset;
}

uint64_t
AtomicSwapAskFrame::getAmount() const
{
    return mAtomicSwapAsk.amount;
}

uint64_t
AtomicSwapAskFrame::getLockedAmount() const
{
    return mAtomicSwapAsk.lockedAmount;
}

uint64_t AtomicSwapAskFrame::getTotalAmount() const
{
    uint64_t totalAmount = 0;
    if (!safeSum(mAtomicSwapAsk.amount, mAtomicSwapAsk.lockedAmount, totalAmount))
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER)
                << "Unexpected state: "
                   "total amount of atomic swap ask overflows uint64, ask ID: "
                << mAtomicSwapAsk.id;
        throw runtime_error("Unexpected state: "
                            "total amount of atomic swap ask overflows uint64");
    }
    return totalAmount;
}

bool AtomicSwapAskFrame::isCancelled() const
{
    return mAtomicSwapAsk.isCancelled;
}

void AtomicSwapAskFrame::setIsCancelled(bool isCancelled)
{
    mAtomicSwapAsk.isCancelled = isCancelled;
}

bool
AtomicSwapAskFrame::hasQuoteAsset(AssetCode assetCode) const
{
    for (auto const& quoteAsset : mAtomicSwapAsk.quoteAssets)
    {
        if (quoteAsset.quoteAsset == assetCode)
        {
            return true;
        }
    }

    return false;
}

bool AtomicSwapAskFrame::tryLockAmount(uint64_t amountToLock)
{
    if (mAtomicSwapAsk.amount < amountToLock)
    {
        return false;
    }

    mAtomicSwapAsk.amount -= amountToLock;

    if (!safeSum(mAtomicSwapAsk.lockedAmount, amountToLock,
                 mAtomicSwapAsk.lockedAmount))
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER)
                << "Unexpected state: addition of the locked amount "
                   "to atomic swap ask overflows uint64, atomic swap ask ID: "
                << mAtomicSwapAsk.id;
        throw runtime_error("Unexpected state: addition of the locked amount "
                            "to atomic swap ask overflows uint64");
    }

    return true;
}

bool AtomicSwapAskFrame::tryUnlockAmount(uint64_t amountToUnlock)
{
    if (mAtomicSwapAsk.lockedAmount < amountToUnlock)
    {
        return false;
    }

    mAtomicSwapAsk.lockedAmount -= amountToUnlock;

    if (!safeSum(mAtomicSwapAsk.amount, amountToUnlock, mAtomicSwapAsk.amount))
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER)
                << "Unexpected state: unlock of the amount "
                   "in atomic swap ask overflows uint64, atomic swap ask ID: "
                << mAtomicSwapAsk.id;
        throw runtime_error("Unexpected state: unlock of the amount "
                            "in atomic swap ask overflows uint64");
    }

    return true;
}

bool AtomicSwapAskFrame::tryChargeFromLocked(uint64_t amount)
{
    if (mAtomicSwapAsk.lockedAmount < amount)
    {
        return false;
    }
    mAtomicSwapAsk.lockedAmount -= amount;
    return true;
}

bool
AtomicSwapAskFrame::isValid(AtomicSwapAskEntry const& atomicSwapBidEntry)
{
    for (auto const& quoteAsset : atomicSwapBidEntry.quoteAssets)
    {
        if (!AssetFrame::isAssetCodeValid(quoteAsset.quoteAsset))
        {
            return false;
        }

        if (quoteAsset.price == 0)
        {
            return false;
        }
    }

    return true;
}

bool
AtomicSwapAskFrame::isValid() const
{
    return isValid(mAtomicSwapAsk);
}

uint64_t
AtomicSwapAskFrame::getQuoteAssetPrice(AssetCode const &quoteAssetCode) const
{
    for (auto const& quoteAsset : mAtomicSwapAsk.quoteAssets)
    {
        if (quoteAsset.quoteAsset == quoteAssetCode)
        {
            return quoteAsset.price;
        }
    }

    return 0;
}

LedgerKey const &
AtomicSwapAskFrame::getKey() const
{
    if (!mKeyCalculated) {
        mKey = LedgerKey(LedgerEntryType::ATOMIC_SWAP_ASK);
        mKey.atomicSwapAsk().id = mAtomicSwapAsk.id,
                mKeyCalculated = true;
    }
    return mKey;
}

}