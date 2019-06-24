#pragma once

#include "ledger/SignerHelper.h"

namespace stellar
{

class MockSignerHelper : public SignerHelper
{
public:
    MOCK_METHOD0(dropAll, void());
    MOCK_CONST_METHOD0(getTableName, const std::string());
    MOCK_METHOD1(storeAdd, void(LedgerEntry const& entry));
    MOCK_METHOD1(storeChange, void(LedgerEntry const& entry));
    MOCK_METHOD1(storeDelete, void(LedgerKey const& key));
    MOCK_METHOD1(exists, bool(LedgerKey const& key));
    MOCK_METHOD1(getLedgerKey, LedgerKey(LedgerEntry const& from));
    MOCK_METHOD1(fromXDR, EntryFrame::pointer(LedgerEntry const& from));
    MOCK_METHOD1(storeLoad, EntryFrame::pointer(LedgerKey const& ledgerKey));
    MOCK_METHOD0(countObjects, uint64_t());
    MOCK_METHOD0(getDatabase, Database&());
    MOCK_METHOD0(getLedgerDelta, LedgerDelta*());
    MOCK_METHOD1(flushCachedEntry, void(LedgerKey const& key));
    MOCK_METHOD1(cachedEntryExists, bool(LedgerKey const& key));
    MOCK_METHOD2(loadSigner, SignerFrame::pointer(
            PublicKey const& publicKey, AccountID const& accountID));
    MOCK_METHOD1(loadSigners,
                 std::vector<SignerFrame::pointer>(AccountID const& accountID));
    MOCK_METHOD1(isRoleIDUsed, bool(uint64_t roleID));
    MOCK_METHOD2(exists,
                 bool(PublicKey const& publicKey, AccountID const& accountID));



};

}  // namespace stellar
