#pragma once

#include <database/Database.h>

namespace soci
{
    class session;
}

namespace stellar
{

class StatementContext;

class ASwapBidQuoteAssetHelper
{
public:
    static void dropAll(Database& db);

    static void
    addAtomicSwapBidForeignKey(Database &db);

    static void deleteAllForBid(Database& db, uint64_t bidID);

    static void storeUpdate(Database& db, uint64_t bidID,
                            xdr::xvector<ASwapBidQuoteAsset> quoteAssets,
                            bool insert);

    static void storeUpdate(Database& db, uint64_t bidID,
                            ASwapBidQuoteAsset const& quoteAsset,
                            bool insert);

    static void loadASwapQuoteAsset(
            StatementContext& prep,
            const std::function<void (ASwapBidQuoteAsset const&)> saleProcessor);

    static xdr::xvector<ASwapBidQuoteAsset> loadQuoteAssets(Database& db, uint64_t bidID);
};

}