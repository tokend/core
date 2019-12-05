#include "ledger/FeeHelper.h"

namespace stellar
{

class MockFeeHelper : public FeeHelper
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
    MOCK_METHOD7(loadFee, FeeFrame::pointer(FeeType feeType, AssetCode asset, AccountID *accountID,
            uint64_t* accountType, int64_t subtype, int64_t lowerBound,
            int64_t upperBound));
    MOCK_METHOD3(loadFee, FeeFrame::pointer(Hash hash, int64_t lowerBound, int64_t upperBound));
    MOCK_METHOD5(loadForAccount, FeeFrame::pointer(FeeType feeType, AssetCode asset, int64_t subtype,
            AccountFrame::pointer accountFrame, int64_t amount));
    MOCK_METHOD1(loadFees, std::vector<FeeFrame::pointer>(Hash hash));
    MOCK_METHOD2(storeUpdateHelper, void(bool insert, LedgerEntry const &entry));
    MOCK_METHOD2(loadFees, void(StatementContext &prep, std::function<void(LedgerEntry const &)> feeProcessor));
    MOCK_METHOD1(checkAmounts, void(const FeeFrame::pointer &frame));
    MOCK_METHOD3(isBoundariesOverlap, bool(Hash hash, int64_t lowerBound, int64_t upperBound));
    MOCK_METHOD3(exists, bool(Hash hash, int64_t lowerBound, int64_t upperBound));

};

}  // nam