#include "ledger/OfferHelper.h"

namespace stellar
{

class MockOfferHelper : public OfferHelper
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
    MOCK_METHOD3(exists, bool(AssetCode const& base, AssetCode const& quote, uint64_t* orderBookID));
    MOCK_METHOD2(exists, bool(AssetCode const &code, uint64_t *orderBookIDPtr));
    MOCK_METHOD2(loadOffer, OfferFrame::pointer(AccountID const& accountID, uint64_t offerID));
    MOCK_METHOD3(loadOffer, OfferFrame::pointer(AccountID const& accountID, uint64_t offerID, uint64_t orderBookID));
    MOCK_METHOD4(loadOffersWithFilters, std::vector<OfferFrame::pointer>(AssetCode const& base, AssetCode const& quote, uint64_t* orderBookID,
            uint64_t* priceUpperBound));
    MOCK_METHOD4(loadOffers, std::vector<OfferFrame::pointer>(AssetCode const& base, AssetCode const& quote, uint64_t const orderBookID,
            int64_t quoteamountUpperBound));
    MOCK_METHOD2(loadOffers, std::vector<OfferFrame::pointer>(AccountID const& accountID, uint64_t orderBookID));
    MOCK_METHOD0(loadAllOffers, std::unordered_map<AccountID, std::vector<OfferFrame::pointer>>());
    MOCK_METHOD7(loadBestOffers, void(size_t numOffers, size_t offset,
            AssetCode const& base, AssetCode const& quote, uint64_t orderBookID,
            bool isBuy,
            std::vector<OfferFrame::pointer>& retOffers));
    MOCK_METHOD2(storeUpdateHelper, void(bool insert, LedgerEntry const& entry));
    MOCK_METHOD2(loadOffers, void(StatementContext& prep, std::function<void(LedgerEntry const&)> offerProcessor));
    MOCK_METHOD1(checkAmounts, void(const OfferFrame::pointer& frame));
};

}  // namespace stellar