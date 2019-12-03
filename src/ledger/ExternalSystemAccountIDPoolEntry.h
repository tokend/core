#pragma once

#include "ledger/EntryFrame.h"

namespace stellar
{

class ExternalSystemAccountIDPoolEntryFrame : public EntryFrame
{
    ExternalSystemAccountIDPoolEntry& mExternalSystemAccountIDPoolEntry;

    ExternalSystemAccountIDPoolEntryFrame(ExternalSystemAccountIDPoolEntryFrame const& from);

public:
    typedef std::shared_ptr<ExternalSystemAccountIDPoolEntryFrame> pointer;

    ExternalSystemAccountIDPoolEntryFrame();

    explicit ExternalSystemAccountIDPoolEntryFrame(LedgerEntry const& from);

    ExternalSystemAccountIDPoolEntryFrame& operator=(
            ExternalSystemAccountIDPoolEntryFrame const& other);

    EntryFrame::pointer copy() const override
    {
        return EntryFrame::pointer(new ExternalSystemAccountIDPoolEntryFrame(*this));
    }

    static pointer createNew(uint64 poolEntryID, int32 const externalSystemType,
                                std::string const data, uint64 parent);

    void markAsDeleted();

    ExternalSystemAccountIDPoolEntry const& getExternalSystemAccountIDPoolEntry() const
    {
        return mExternalSystemAccountIDPoolEntry;
    }

    ExternalSystemAccountIDPoolEntry& getExternalSystemAccountIDPoolEntry()
    {
        return mExternalSystemAccountIDPoolEntry;
    }

    static void ensureValid(ExternalSystemAccountIDPoolEntry const& p);
    void ensureValid() const;

    LedgerKey const&
    getKey() const override;
};
}