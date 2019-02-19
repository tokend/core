#include "SignerRoleFrame.h"

namespace stellar
{

SignerRoleFrame::SignerRoleFrame() : EntryFrame(LedgerEntryType::SIGNER_ROLE)
        , mSignerRoleEntry(mEntry.data.signerRole())
{
}

SignerRoleFrame::SignerRoleFrame(LedgerEntry const& from) : EntryFrame(from)
        , mSignerRoleEntry(mEntry.data.signerRole())
{
}

SignerRoleFrame::SignerRoleFrame(SignerRoleFrame const& from)
        : SignerRoleFrame(from.mEntry)
{
}

LedgerKey const&
SignerRoleFrame::getKey() const
{
    if (!mKeyCalculated)
    {
        mKey = LedgerKey(LedgerEntryType::SIGNER_ROLE);
        mKey.signerRole().id = mSignerRoleEntry.id;
        mKeyCalculated = true;
    }

    return mKey;
}
}