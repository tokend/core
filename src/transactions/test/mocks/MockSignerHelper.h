#pragma once

#include "ledger/SignerHelper.h"

namespace stellar {

    class MockSignerHelper : public SignerHelper {
    public:
        MOCK_METHOD0(dropAll, void());
        MOCK_METHOD1(storeAdd, void(LedgerEntry const& entry));
        MOCK_METHOD1(storeChange, void(LedgerEntry const& entry));
        MOCK_METHOD1(storeDelete, void(LedgerKey const& key));
        MOCK_METHOD1(exists, bool(LedgerKey const& key));
        MOCK_METHOD1(exists, bool(AssetCode const& key));
        MOCK_METHOD1(getLedgerKey, LedgerKey(LedgerEntry const& from));
        MOCK_METHOD1(fromXDR, EntryFrame::pointer(LedgerEntry const& from));
        MOCK_METHOD1(storeLoad, EntryFrame::pointer(LedgerKey const& ledgerKey));
        MOCK_METHOD0(countObjects, uint64_t());
        MOCK_METHOD0(getDatabase, Database&());
        MOCK_METHOD1(flushCachedEntry, void(LedgerKey const& key));
        MOCK_METHOD1(cachedEntryExists, bool(LedgerKey const& key));
        MOCK_METHOD1(loadSigners,
                std::vector<SignerFrame::pointer>(AccountID const& accountID));
    };

}  // namespace stellar
