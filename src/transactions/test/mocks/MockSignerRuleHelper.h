#pragma once

#include <lib/gtest/googlemock/include/gmock/gmock-generated-function-mockers.h>
#include "ledger/SignerRuleHelper.h"

namespace stellar
{

class MockSignerRuleHelper : public SignerRuleHelper
{
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
    MOCK_METHOD0(getLedgerDelta, LedgerDelta*());
    MOCK_METHOD1(flushCachedEntry, void(LedgerKey const& key));
    MOCK_METHOD1(cachedEntryExists, bool(LedgerKey const& key));
    MOCK_METHOD1(exists, bool(uint64_t const ruleID));
    MOCK_METHOD1(loadSignerRule,
                 SignerRuleFrame::pointer(uint64_t const ruleID));
    MOCK_METHOD1(loadSignerRules,
                 std::vector<SignerRuleFrame::pointer>(std::vector<uint64_t> const ruleIDs));
    MOCK_METHOD0(loadDefaultRuleIDs, std::vector<uint64_t>());


};

}  // namespace stellar