#pragma once

#include "EntryFrame.h"

namespace stellar
{

class AtomicSwapAskFrame : public EntryFrame
{
    AtomicSwapAskEntry& mAtomicSwapAsk;

    AtomicSwapAskFrame(AtomicSwapAskFrame const& from);

public:
    typedef std::shared_ptr<AtomicSwapAskFrame> pointer;

    AtomicSwapAskFrame();

    explicit AtomicSwapAskFrame(LedgerEntry const& from);

    AtomicSwapAskFrame& operator=(AtomicSwapAskFrame const& other);

    EntryFrame::pointer copy() const override;

    AtomicSwapAskEntry& getAtomicSwapAsk();

    uint64_t getID() const;

    AccountID getOwnerID() const;

    AssetCode getBaseAsset() const;

    uint64_t getAmount() const;

    uint64_t getLockedAmount() const;

    uint64_t getTotalAmount() const;

    bool isCancelled() const;

    void setIsCancelled(bool isCancelled);

    bool hasQuoteAsset(AssetCode assetCode) const;

    uint64_t getQuoteAssetPrice(AssetCode const &quoteAssetCode) const;

    bool tryLockAmount(uint64_t amountToLock);

    bool tryUnlockAmount(uint64_t amountToUnlock);

    bool tryChargeFromLocked(uint64_t amount);

    bool isValid() const;

    static bool isValid(AtomicSwapAskEntry const& atomicSwapBidEntry);

    LedgerKey const&
    getKey() const override;
};

}