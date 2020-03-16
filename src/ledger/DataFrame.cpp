#include "DataFrame.h"

namespace stellar 
{
DataFrame::DataFrame() 
        : EntryFrame(LedgerEntryType::DATA)
        , mDataEntry(mEntry.data.data()) 
{
}

DataFrame::DataFrame(LedgerEntry const& from)
        : EntryFrame(from), mDataEntry(mEntry.data.data())
{
}

DataFrame::DataFrame(DataFrame const& from) 
        : DataFrame(from.mEntry) 
{
}

LedgerKey const& 
DataFrame::getKey() const 
{
    if (!mKeyCalculated)
    {
        mKey = LedgerKey(LedgerEntryType::DATA);
        mKey.data().id = mDataEntry.id;
        mKeyCalculated = true;
    }

    return mKey;
}

}