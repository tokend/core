#include "SignerFrame.h"

namespace stellar
{
SignerFrame::SignerFrame() : EntryFrame(LedgerEntryType::SIGNER)
        , mSignerEntry(mEntry.data.signer())
{
}

SignerFrame::SignerFrame(LedgerEntry const& from) : EntryFrame(from)
        , mSignerEntry(mEntry.data.signer())
{
}

SignerFrame::SignerFrame(SignerFrame const& from) : SignerFrame(from.mEntry)
{
}

LedgerKey const&
SignerFrame::getKey() const
{
    if (!mKeyCalculated)
    {
        mKey = LedgerKey(LedgerEntryType::SIGNER);
        mKey.signer().pubKey = mSignerEntry.pubKey;
        mKeyCalculated = true;
    }

    return mKey;
}
}
