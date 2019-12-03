#pragma once

// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ledger/EntryFrame.h"
#include "ledger/LedgerManager.h"
#include <functional>

namespace soci
{
class session;
}

namespace stellar
{
class StatementContext;

class StampFrame : public EntryFrame
{

    StampEntry& mStamp;

    StampFrame(StampFrame const& from);


public:
    typedef std::shared_ptr<StampFrame> pointer;

    static pointer createNew(Hash ledgerHash, Hash licenseHash);

    StampFrame();
    StampFrame(LedgerEntry const& from);

    StampFrame& operator=(StampFrame const& other);

    EntryFrame::pointer
    copy() const override
    {
        return EntryFrame::pointer(new StampFrame(*this));
    }
    StampEntry& getStampEntry();

    LedgerKey const&
    getKey() const override;
};
}