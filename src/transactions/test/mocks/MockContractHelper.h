#include "ledger/ContractHelper.h"

namespace stellar
{

class MockContractHelper : public ContractHelper
{
public:
    MOCK_METHOD0(dropAll, void());
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
    MOCK_METHOD0(addCustomerDetails, void());
    MOCK_METHOD1(loadContract, ContractFrame::pointer(uint64_t id));
    MOCK_METHOD1(countContracts, uint64_t(AccountID const& contractor));
    MOCK_METHOD2(load, void(StatementContext & prep, std::function<void(LedgerEntry const&)> processor));
    MOCK_METHOD2(storeUpdateHelper, void(bool insert, LedgerEntry const& entry));
};

}  // namespace stellar