#include "SignerRuleFrame.h"

namespace stellar
{

SignerRuleFrame::SignerRuleFrame() : EntryFrame(LedgerEntryType::SIGNER_RULE)
        , mSignerRuleEntry(mEntry.data.signerRule())
{
}

SignerRuleFrame::SignerRuleFrame(LedgerEntry const& from) : EntryFrame(from)
        , mSignerRuleEntry(mEntry.data.signerRule())
{
}

SignerRuleFrame::SignerRuleFrame(SignerRuleFrame const& from)
        : SignerRuleFrame(from.mEntry)
{
}

LedgerKey const&
SignerRuleFrame::getKey() const
{
    if (!mKeyCalculated)
    {
        mKey = LedgerKey(LedgerEntryType::SIGNER_RULE);
        mKey.signerRule().id = mSignerRuleEntry.id;
        mKeyCalculated = true;
    }

    return mKey;
}
}