#include "KeyValueEntryFrame.h"

namespace stellar{

    KeyValueEntryFrame::KeyValueEntryFrame():EntryFrame(LedgerEntryType::KEY_VALUE),
                                   mKeyEntry(mEntry.data.keyValue())
    {
    }

    KeyValueEntryFrame::KeyValueEntryFrame(LedgerEntry const &from) : EntryFrame(from),
                                                            mKeyEntry(mEntry.data.keyValue())
    {
    }

    KeyValueEntryFrame::KeyValueEntryFrame(KeyValueEntryFrame const &from) : KeyValueEntryFrame(from.mEntry)
    {
    }

    KeyValueEntryFrame &KeyValueEntryFrame::operator=(KeyValueEntryFrame const &other) {
        if(&other != this)
        {
            mKey = other.mKey;
            mKeyCalculated = other.mKeyCalculated;
            mKeyEntry = other.mKeyEntry;
        }
        return *this;
    }

    uint32_t const
    KeyValueEntryFrame::mustGetUint32Value() const
    {
        if (getKeyValueEntryType() == KeyValueEntryType::UINT32)
        {
            return mKeyEntry.value.ui32Value();
        }

        CLOG(ERROR, Logging::ENTRY_LOGGER) << "Unexpected database state. "
                << "Expected " + mKeyEntry.key + " key to be UINT32 type, get:"
                << xdr::xdr_traits<KeyValueEntryType>::enum_name(
                                getKeyValueEntryType());
        throw std::runtime_error("Unexpected database state. Expected " +
                                 mKeyEntry.key + "key to be UINT32 type");
    }

}