#include "SwapFrame.h"

namespace stellar
{
using xdr::operator<;

SwapFrame::SwapFrame()
    : EntryFrame(LedgerEntryType::SWAP), mSwapEntry(mEntry.data.swap())
{
}

SwapFrame::SwapFrame(LedgerEntry const& from)
    : EntryFrame(from), mSwapEntry(mEntry.data.swap())
{
}

SwapFrame::SwapFrame(SwapFrame const& from) : SwapFrame(from.mEntry)
{
}

SwapFrame::SwapFrame(uint64_t id) : SwapFrame()
{
    mSwapEntry.swapID = id;
}


LedgerKey const&
SwapFrame::getKey() const
{
    if (!mKeyCalculated)
    {
        mKey = LedgerKey(LedgerEntryType::SWAP);
        mKey.swap().swapID = getID();
        mKeyCalculated = true;
    }

    return mKey;
}

uint64_t SwapFrame::getID() const
{
    return mSwapEntry.swapID;
}

} // namespace stellar
