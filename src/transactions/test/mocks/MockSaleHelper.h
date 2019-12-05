#include "ledger/SaleHelper.h"

namespace stellar
{

class MockSaleHelper : public SaleHelper
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
    MOCK_METHOD1(exists, bool(uint64_t saleID));
    MOCK_METHOD1(exists, bool(AssetCode const& code));
    MOCK_METHOD2(exists, bool(AssetCode const& base, AssetCode const& quote));
    MOCK_METHOD1(loadSale, SaleFrame::pointer(uint64_t saleID));
    MOCK_METHOD2(loadSale, SaleFrame::pointer(uint64_t saleID, AccountID ownerID));
    MOCK_METHOD3(loadSale, SaleFrame::pointer(uint64_t saleID,AssetCode const& base, AssetCode const& quote));
    MOCK_METHOD1(loadSalesForOwner, std::vector<SaleFrame::pointer>(AccountID owner));
    MOCK_METHOD2(storeUpdateHelper, void(bool insert, LedgerEntry const& entry));
    MOCK_METHOD2(loadSales,void(StatementContext & prep, std::function<void(LedgerEntry const&)> requestsProcessor));
};

}  // namespace stellar