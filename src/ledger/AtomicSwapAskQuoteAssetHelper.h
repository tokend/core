#pragma once

#include "overlay/StellarXDR.h"

namespace stellar
{

class Database;
class StatementContext;

class AtomicSwapAskQuoteAssetHelper
{
public:
    static void dropAll(Database& db);

    static void deleteAllForAsk(Database &db, uint64_t bidID);

    static void storeUpdate(Database& db, uint64_t bidID,
                            xdr::xvector<AtomicSwapAskQuoteAsset> quoteAssets,
                            bool insert);

    static void storeUpdate(Database& db, uint64_t bidID,
                            AtomicSwapAskQuoteAsset const& quoteAsset,
                            bool insert);

    static void
    loadASwapQuoteAsset(StatementContext& prep,
            const std::function<void (AtomicSwapAskQuoteAsset const&)> saleProcessor);

    static xdr::xvector<AtomicSwapAskQuoteAsset> loadQuoteAssets(Database& db, uint64_t bidID);
};

}