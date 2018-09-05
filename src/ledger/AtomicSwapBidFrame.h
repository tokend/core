#pragma once

#include "EntryFrame.h"

namespace stellar
{

class AtomicSwapBidFrame : public EntryFrame
{
    AtomicSwapBidEntry& mAtomicSwapBid;

    AtomicSwapBidFrame(AtomicSwapBidFrame const& from);

public:
    typedef std::shared_ptr<AtomicSwapBidFrame> pointer;

    AtomicSwapBidFrame();

    explicit AtomicSwapBidFrame(LedgerEntry const& from);

    AtomicSwapBidFrame& operator=(AtomicSwapBidFrame const& other);

    EntryFrame::pointer copy() const override;

    AtomicSwapBidEntry& getAtomicSwapBid();

    uint64_t getBidID() const;

    AccountID getOwner() const;

    uint64_t getPrice() const;

    bool isInQuoteAssets(AssetCode assetCode) const;

    uint64_t getAmount() const;

    uint64_t getFee() const;

    void setFee(uint64_t fee);

    void setPercentFee(uint64_t percentFee);

    bool isValid() const;

    static bool isValid(AtomicSwapBidEntry const& atomicSwapBidEntry);
};

}