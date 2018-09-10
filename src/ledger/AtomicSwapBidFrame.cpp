#include "AtomicSwapBidFrame.h"
#include "AssetFrame.h"

using namespace std;

namespace stellar
{

    AtomicSwapBidFrame::AtomicSwapBidFrame()
            : EntryFrame(LedgerEntryType::ATOMIC_SWAP_BID),
              mAtomicSwapBid(mEntry.data.atomicSwapBid())
    {
    }

    AtomicSwapBidFrame::AtomicSwapBidFrame(LedgerEntry const &from)
            : EntryFrame(from), mAtomicSwapBid(mEntry.data.atomicSwapBid())
    {
    }

    AtomicSwapBidFrame::AtomicSwapBidFrame(const stellar::AtomicSwapBidFrame &from)
            : AtomicSwapBidFrame(from.mEntry)
    {
    }

    AtomicSwapBidFrame&
    AtomicSwapBidFrame::operator=(AtomicSwapBidFrame const &other)
    {
        if (&other != this)
        {
            mAtomicSwapBid = other.mAtomicSwapBid;
            mKey = other.mKey;
            mKeyCalculated = other.mKeyCalculated;
        }
        return *this;
    }

    EntryFrame::pointer
    AtomicSwapBidFrame::copy() const
    {
        return EntryFrame::pointer(new AtomicSwapBidFrame(*this));
    }

    AtomicSwapBidEntry&
    AtomicSwapBidFrame::getAtomicSwapBid()
    {
        return mAtomicSwapBid;
    }

    uint64_t
    AtomicSwapBidFrame::getBidID() const
    {
        return mAtomicSwapBid.bidID;
    }

    AccountID
    AtomicSwapBidFrame::getOwnerID() const
    {
        return mAtomicSwapBid.ownerID;
    }

    AssetCode AtomicSwapBidFrame::getBaseAsset() const
    {
        return mAtomicSwapBid.baseAsset;
    }

    uint64_t
    AtomicSwapBidFrame::getAmount() const
    {
        return mAtomicSwapBid.amount;
    }

    uint64_t
    AtomicSwapBidFrame::getLockedAmount() const
    {
        return mAtomicSwapBid.lockedAmount;
    }

    bool AtomicSwapBidFrame::isCancelled() const
    {
        return mAtomicSwapBid.isCancelled;
    }

    void AtomicSwapBidFrame::setIsCancelled(bool isCancelled)
    {
        mAtomicSwapBid.isCancelled = isCancelled;
    }

    bool
    AtomicSwapBidFrame::hasQuoteAsset(AssetCode assetCode) const
    {
        for (auto const& quoteAsset : mAtomicSwapBid.quoteAssets)
        {
            if (quoteAsset.quoteAsset == assetCode)
            {
                return true;
            }
        }

        return false;
    }

    bool AtomicSwapBidFrame::tryLockAmount(uint64_t amountToLock)
    {
        if (mAtomicSwapBid.amount < amountToLock)
        {
            return false;
        }

        mAtomicSwapBid.amount -= amountToLock;

        if (!safeSum(mAtomicSwapBid.lockedAmount, amountToLock,
                     mAtomicSwapBid.lockedAmount))
        {
            CLOG(ERROR, Logging::ENTRY_LOGGER)
                    << "Unexpected state: addition of the locked amount "
                       "to atomic swap bid overflows uint64, atomic swap bid ID: "
                    << mAtomicSwapBid.bidID;
            throw runtime_error("Unexpected state: addition of the locked amount "
                                "to atomic swap bid overflows uint64");
        }

        return true;
    }

    bool AtomicSwapBidFrame::tryUnlockAmount(uint64_t amountToUnlock)
    {
        if (mAtomicSwapBid.lockedAmount < amountToUnlock)
        {
            return false;
        }

        mAtomicSwapBid.lockedAmount -= amountToUnlock;

        if (!safeSum(mAtomicSwapBid.amount, amountToUnlock, mAtomicSwapBid.amount))
        {
            CLOG(ERROR, Logging::ENTRY_LOGGER)
                    << "Unexpected state: unlock of the amount "
                       "in atomic swap bid overflows uint64, atomic swap bid ID: "
                    << mAtomicSwapBid.bidID;
            throw runtime_error("Unexpected state: unlock of the amount "
                                "in atomic swap bid overflows uint64");
        }

        return true;
    }

    bool AtomicSwapBidFrame::tryChargeFromLocked(uint64_t amount)
    {
        if (mAtomicSwapBid.lockedAmount < amount)
        {
            return false;
        }
        mAtomicSwapBid.lockedAmount -= amount;
        return true;
    }

    bool
    AtomicSwapBidFrame::isValid(AtomicSwapBidEntry const& atomicSwapBidEntry)
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
    AtomicSwapBidFrame::isValid() const
    {
        return isValid(mAtomicSwapBid);
    }

}