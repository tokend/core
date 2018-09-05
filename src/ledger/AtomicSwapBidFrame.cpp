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
    AtomicSwapBidFrame::getOwner() const
    {
        return mAtomicSwapBid.ownerID;
    }

    uint64_t
    AtomicSwapBidFrame::getPrice() const
    {
        return mAtomicSwapBid.price;
    }

    bool
    AtomicSwapBidFrame::isInQuoteAssets(AssetCode assetCode) const
    {
        for (auto quoteAsset : mAtomicSwapBid.quoteAssets)
        {
            if (assetCode == quoteAsset.quoteAsset)
            {
                return true;
            }
        }

        return false;
    }

    uint64_t
    AtomicSwapBidFrame::getAmount() const
    {
        return mAtomicSwapBid.baseAmount;
    }

    uint64_t
    AtomicSwapBidFrame::getFee() const
    {
        return mAtomicSwapBid.fee;
    }

    void
    AtomicSwapBidFrame::setFee(uint64_t fee)
    {
        mAtomicSwapBid.fee = fee;
    }

    void
    AtomicSwapBidFrame::setPercentFee(uint64_t percentFee)
    {
        mAtomicSwapBid.percentFee = percentFee;
    }

    bool
    AtomicSwapBidFrame::isValid(AtomicSwapBidEntry const& atomicSwapBidEntry)
    {
        return AssetFrame::isAssetCodeValid(atomicSwapBidEntry.baseAsset)
               && AssetFrame::isAssetCodeValid(atomicSwapBidEntry.quoteAsset)
               && atomicSwapBidEntry.baseAmount != 0
               && atomicSwapBidEntry.price != 0;
    }

    bool
    AtomicSwapBidFrame::isValid() const
    {
        return isValid(mAtomicSwapBid);
    }

}