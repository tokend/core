// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "StampFrame.h"
#include "database/Database.h"
#include "LedgerDelta.h"
#include "xdrpp/printer.h"

using namespace soci;
using namespace std;

namespace stellar
{

StampFrame::StampFrame() : EntryFrame(LedgerEntryType::STAMP), mStamp(mEntry.data.stamp())
{
}

StampFrame::StampFrame(LedgerEntry const& from)
    : EntryFrame(from), mStamp(mEntry.data.stamp())
{
}

StampFrame::StampFrame(StampFrame const& from) : StampFrame(from.mEntry)
{
}

StampFrame& StampFrame::operator=(StampFrame const& other)
{
    if (&other != this)
    {
        mStamp = other.mStamp;
        mKey = other.mKey;
        mKeyCalculated = other.mKeyCalculated;
    }
    return *this;
}

StampEntry& StampFrame::getStampEntry()
{
    return mStamp;
}

StampFrame::pointer StampFrame::createNew(Hash ledgerHash, Hash licenseHash)
{
    try
    {
        LedgerEntry entry;
        entry.data.type(LedgerEntryType::STAMP);
        entry.data.stamp().ledgerHash = ledgerHash;
        entry.data.stamp().licenseHash = licenseHash;
        return std::make_shared<StampFrame>(entry);
    } catch (...)
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER) << "Failed to create stamp";
        throw_with_nested(runtime_error("Failed to create stamp"));
    }
}

LedgerKey const &
StampFrame::getKey() const
{
    if (!mKeyCalculated) {
        mKey = LedgerKey(LedgerEntryType::STAMP);
        mKey.stamp().ledgerHash = mStamp.ledgerHash;
        mKey.stamp().licenseHash = mStamp.licenseHash;
        mKeyCalculated = true;
    }
    return mKey;
}
}