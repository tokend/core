#include "ledger/EntryHelper.h"
#include "ledger/LedgerManager.h"
#include <functional>
#include <unordered_map>
#include "OfferFrame.h"

namespace soci
{
    class session;
}

namespace stellar
{

class StatementContext;

class OfferHelper : public EntryHelper {

public:
    virtual bool exists(AssetCode const& base, AssetCode const& quote, uint64_t* orderBookID) = 0;
    virtual bool exists(AssetCode const &code, uint64_t *orderBookIDPtr) = 0;

    virtual OfferFrame::pointer loadOffer(AccountID const& accountID, uint64_t offerID) = 0;

    virtual OfferFrame::pointer loadOffer(AccountID const& accountID, uint64_t offerID, uint64_t orderBookID) = 0;

    virtual std::vector<OfferFrame::pointer> loadOffersWithFilters(AssetCode const& base, AssetCode const& quote, uint64_t* orderBookID,
        uint64_t* priceUpperBound) = 0;

    virtual std::vector<OfferFrame::pointer> loadOffers(AssetCode const& base, AssetCode const& quote, uint64_t const orderBookID,
        int64_t quoteamountUpperBound) = 0;

    virtual std::vector<OfferFrame::pointer>
    loadOffers(AccountID const& accountID, uint64_t orderBookID) = 0;

    virtual std::unordered_map<AccountID, std::vector<OfferFrame::pointer>> loadAllOffers() = 0;

    virtual void loadBestOffers(size_t numOffers, size_t offset,
                        AssetCode const& base, AssetCode const& quote, uint64_t orderBookID,
                        bool isBuy,
                        std::vector<OfferFrame::pointer>& retOffers) = 0;

    virtual void storeUpdateHelper(bool insert, LedgerEntry const& entry) = 0;

    virtual void loadOffers(StatementContext& prep, std::function<void(LedgerEntry const&)> offerProcessor) = 0;

    virtual void checkAmounts(const OfferFrame::pointer& frame) const = 0;
};
}