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

SignerRuleFrame::SignerRuleFrame(uint64_t const ruleID, AccountID ownerID,
        const CreateSignerRuleData data)
        : SignerRuleFrame()

{
    mSignerRuleEntry.id = ruleID;
    mSignerRuleEntry.isForbid = data.isForbid;
    mSignerRuleEntry.isDefault = data.isDefault;
    mSignerRuleEntry.resource = data.resource;
    mSignerRuleEntry.action = data.action;
    mSignerRuleEntry.details = data.details;
    mSignerRuleEntry.ownerID = ownerID;
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