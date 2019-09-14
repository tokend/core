#pragma once

#include "ledger/EntryFrame.h"

namespace stellar
{

class SwapFrame : public EntryFrame
{
    SwapEntry& mSwapEntry;

    SwapFrame(SwapFrame const& from);

  public:
    typedef std::shared_ptr<SwapFrame> pointer;

    SwapFrame();
    SwapFrame(LedgerEntry const& from);
    SwapFrame(uint64_t id);

    EntryFrame::pointer
    copy() const override
    {
        return EntryFrame::pointer(new SwapFrame(*this));
    }

    uint64_t getID() const;

    SwapEntry const&
    getSwap() const
    {
        return mSwapEntry;
    }

    SwapEntry&
    getSwap()
    {
        clearCached();
        return mSwapEntry;
    }

    LedgerKey const& getKey() const override;
};
} // namespace stellar
