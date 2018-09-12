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

    AccountID getOwnerID() const;

    AssetCode getBaseAsset() const;

    uint64_t getAmount() const;

    uint64_t getLockedAmount() const;

    uint64_t getTotalAmount() const;

    bool isCancelled() const;

    void setIsCancelled(bool isCancelled);

    bool hasQuoteAsset(AssetCode assetCode) const;

    bool tryLockAmount(uint64_t amountToLock);

    bool tryUnlockAmount(uint64_t amountToUnlock);

    bool tryChargeFromLocked(uint64_t amount);

    bool isValid() const;

    static bool isValid(AtomicSwapBidEntry const& atomicSwapBidEntry);
};

}