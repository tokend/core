#pragma once

#include <lib/gtest/googlemock/include/gmock/gmock-generated-function-mockers.h>
#include "ledger/LedgerHeaderFrame.h"

namespace stellar
{
class LedgerManager;

class MockLedgerHeaderFrame : public LedgerHeaderFrame
{
public:
    MOCK_CONST_METHOD0(getHash, const Hash&());
    MOCK_CONST_METHOD0(getHeader, const LedgerHeader&());
    MOCK_METHOD0(getHeader, LedgerHeader&());
    MOCK_CONST_METHOD1(getLastGeneratedID, uint64_t(const LedgerEntryType ledgerEntryType));
    MOCK_METHOD1(generateID, uint64_t(const LedgerEntryType ledgerEntryType));
    MOCK_CONST_METHOD1(storeInsert, void(LedgerManager& ledgerManager));
};

}  // namespace stellar
