#include "EntryHelper.h"
#include <functional>
#include <unordered_map>
#include "AccountLimitsFrame.h"
#include "AccountFrame.h"
#include "BalanceFrame.h"
#include "StorageHelper.h"
#include "OfferHelper.h"

namespace soci
{
    class session;
}

namespace stellar
{
class StatementContext;


class OfferHelperImpl : public OfferHelper, NonCopyable
{
public:
    explicit OfferHelperImpl(StorageHelper &storageHelper);

    void dropAll() override;
    void storeAdd(LedgerEntry const& entry) override;
    void storeChange(LedgerEntry const& entry) override;
    void storeDelete(LedgerKey const& key) override;
    bool exists(LedgerKey const& key) override;
    LedgerKey getLedgerKey(LedgerEntry const& from) override;
    EntryFrame::pointer storeLoad(LedgerKey const& ledgerKey) override;
    EntryFrame::pointer fromXDR(LedgerEntry const& from) override;
    uint64_t countObjects() override;
    Database& getDatabase() override;
    LedgerDelta* getLedgerDelta() override;

private:
    StorageHelper& mStorageHelper;
    const char* mOfferColumnSelector;

    bool exists(AssetCode const& base, AssetCode const& quote, uint64_t* orderBookID) override;
    bool exists(AssetCode const &code, uint64_t *orderBookIDPtr) override;

    OfferFrame::pointer loadOffer(AccountID const& accountID, uint64_t offerID) override;

    OfferFrame::pointer loadOffer(AccountID const& accountID, uint64_t offerID, uint64_t orderBookID) override;

    std::vector<OfferFrame::pointer> loadOffersWithFilters(AssetCode const& base, AssetCode const& quote, uint64_t* orderBookID,
                                                                   uint64_t* priceUpperBound) override;

    std::vector<OfferFrame::pointer> loadOffers(AssetCode const& base, AssetCode const& quote, uint64_t const orderBookID,
                                                        int64_t quoteamountUpperBound) override;

    std::vector<OfferFrame::pointer>
    loadOffers(AccountID const& accountID, uint64_t orderBookID) override;

    std::unordered_map<AccountID, std::vector<OfferFrame::pointer>> loadAllOffers() override;

    void loadBestOffers(size_t numOffers, size_t offset,
                                AssetCode const& base, AssetCode const& quote, uint64_t orderBookID,
                                bool isBuy,
                                std::vector<OfferFrame::pointer>& retOffers) override;

    void storeUpdateHelper(bool insert, LedgerEntry const& entry);

    void loadOffers(StatementContext& prep, std::function<void(LedgerEntry const&)> offerProcessor);

    void checkAmounts(const OfferFrame::pointer& frame) const override;

};

}