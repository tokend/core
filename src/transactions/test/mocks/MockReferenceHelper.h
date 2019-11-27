#include "ledger/ReferenceHelper.h"

namespace stellar
{

class MockReferenceHelper : public ReferenceHelper
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
    MOCK_METHOD0(addVersion, void());
    MOCK_METHOD2(loadReference, ReferenceFrame::pointer(AccountID exchange, std::string reference));
    MOCK_METHOD2(storeUpdateHelper, void(bool insert, const LedgerEntry& entry));
    MOCK_METHOD2(loadReferences, void(StatementContext &prep, std::function<void(LedgerEntry const &)> referenceProcessor));
    MOCK_METHOD2(exists, bool(std::string reference, AccountID exchange));
};

}  // namespace stellar