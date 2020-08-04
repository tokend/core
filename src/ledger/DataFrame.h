#pragma once

#include "ledger/EntryFrame.h"

namespace stellar 
{
class DataFrame : public EntryFrame 
{
    DataEntry& mDataEntry;

    DataFrame(DataFrame const& from);

public:
    typedef std::shared_ptr<DataFrame> pointer;

    DataFrame();
    DataFrame(LedgerEntry const& from);

    EntryFrame::pointer
    copy() const override
    {
        return EntryFrame::pointer(new DataFrame(*this));
    }

    static pointer create(CreateDataRequest const& request);

    LedgerKey const&
    getKey() const override;

    DataEntry const&
    getData() const 
    {
        return mDataEntry;
    }

    DataEntry&
    getData() 
    {
        clearCached();
        return mDataEntry;
    }
};
}