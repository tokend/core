#pragma once

#include "EntryFrame.h"

namespace stellar
{

class SignerFrame : public EntryFrame
{
    SignerEntry& mSignerEntry;

    SignerFrame(SignerFrame const& from);

public:
    typedef std::shared_ptr<SignerFrame> pointer;

    SignerFrame();
    SignerFrame(LedgerEntry const& from);

    EntryFrame::pointer
    copy() const override
    {
        return EntryFrame::pointer(new SignerFrame(*this));
    }


    SignerEntry const&
    getEntry() const
    {
        return mSignerEntry;
    }

    SignerEntry&
    getEntry()
    {
        clearCached();
        return mSignerEntry;
    }
};

}

