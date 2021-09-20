#pragma once

#include "ledger/EntryFrame.h"
#include <iostream>

namespace stellar {
class KeyValueEntryFrame : public EntryFrame {

    KeyValueEntry& mKeyEntry;
    KeyValueEntryFrame(KeyValueEntryFrame const& from);

public:

    typedef std::shared_ptr<KeyValueEntryFrame> pointer;

    KeyValueEntryFrame();
    KeyValueEntryFrame(LedgerEntry const& from);

    KeyValueEntryFrame& operator=(KeyValueEntryFrame const& other);

    EntryFrame::pointer copy() const override
    {
        return EntryFrame::pointer(new KeyValueEntryFrame(*this));
    }

    KeyValueEntry const& getKeyValue() const
    {
        return mKeyEntry;
    }

    KeyValueEntry& getKeyValue()
    {
        return mKeyEntry;
    }

    longstring getEntryKey()
    {
        return mKeyEntry.key;
    }

    KeyValueEntryType const
    getKeyValueEntryType() const
    {
        return mKeyEntry.value.type();
    }

    void setKey(string256 newKey)
    {
        mKeyEntry.key = newKey;
    }

    string256 getPrefix()
    {
        string256 prefix;
        std::istringstream from(mKeyEntry.key);
        std::getline(from,prefix,':');

        return prefix;
    }

    uint32_t const
    mustGetUint32Value() const;

    xdr::xstring<> const
    mustGetStringValue() const;

    LedgerKey const&
    getKey() const override;

};

}