#pragma once

#include "overlay/StellarXDR.h"

namespace stellar
{

class Database;
class StatementContext;

class ASwapBidQuoteAssetHelper
{
public:
    static void dropAll(Database& db);

    static void deleteAllForBid(Database& db, uint64_t bidID);

    static void storeUpdate(Database& db, uint64_t bidID,
                            xdr::xvector<AtomicSwapBidQuoteAsset> quoteAssets,
                            bool insert);

    static void storeUpdate(Database& db, uint64_t bidID,
                            AtomicSwapBidQuoteAsset const& quoteAsset,
                            bool insert);

    static void
    loadASwapQuoteAsset(StatementContext& prep,
            const std::function<void (AtomicSwapBidQuoteAsset const&)> saleProcessor);

    static xdr::xvector<AtomicSwapBidQuoteAsset> loadQuoteAssets(Database& db, uint64_t bidID);
};

}