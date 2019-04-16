#include <util/Logging.h>
#include "AtomicSwapBidQuoteAssetHelper.h"

using namespace soci;
using namespace std;

namespace stellar
{
using xdr::operator<;

void
ASwapBidQuoteAssetHelper::dropAll(Database &db)
{
    db.getSession() << "DROP TABLE IF EXISTS atomic_swap_quote_asset;";
    db.getSession() << "CREATE TABLE atomic_swap_quote_asset"
                       "("
                       "bid_id      BIGINT          NOT NULL CHECK (bid_id >= 0),"
                       "quote_asset VARCHAR(16)     NOT NULL,"
                       "price       NUMERIC(20,0)   NOT NULL CHECK (price > 0),"
                       "version     INT             NOT NULL,"
                       "PRIMARY KEY (bid_id, quote_asset)"
                       ");";
}

void
ASwapBidQuoteAssetHelper::deleteAllForBid(Database &db, uint64_t bidID)
{
    auto prep = db.getPreparedStatement("DELETE FROM atomic_swap_quote_asset "
                                        "WHERE bid_id = :id");
    auto& st = prep.statement();
    st.exchange(use(bidID, "id"));
    st.define_and_bind();
    st.execute(true);
}

void
ASwapBidQuoteAssetHelper::storeUpdate(Database &db, uint64_t bidID,
                                      xdr::xvector<ASwapBidQuoteAsset> quoteAssets,
                                      bool insert)
{
    for (auto const& quoteAsset : quoteAssets)
    {
        storeUpdate(db, bidID, quoteAsset, insert);
    }
}

void ASwapBidQuoteAssetHelper::storeUpdate(Database &db, uint64_t bidID,
                                           ASwapBidQuoteAsset const &quoteAsset,
                                           bool insert)
{
    string sql;

    auto version = static_cast<int32_t>(quoteAsset.ext.v());

    if (insert)
    {
        sql = "INSERT INTO atomic_swap_quote_asset (bid_id, quote_asset, price, version) "
              "VALUES (:id, :qa, :p, :v)";
    }
    else
    {
        sql = "UPDATE atomic_swap_quote_asset SET price = :p, version = :v "
              "WHERE bid_id = :id AND quote_asset = :qa";
    }

    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();

    st.exchange(use(bidID, "id"));
    st.exchange(use(quoteAsset.quoteAsset, "qa"));
    st.exchange(use(quoteAsset.price, "p"));
    st.exchange(use(version, "v"));
    st.define_and_bind();
    st.execute(true);

    if (st.get_affected_rows() != 1)
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER) << "Failed to update atomic swap bid quote "
                                              "asset with id: " << bidID
                                           << quoteAsset.quoteAsset;
        throw runtime_error("Failed to update atomic swap bid quote asset");
    }
}

void ASwapBidQuoteAssetHelper::loadASwapQuoteAsset(
        StatementContext &prep, const std::function<void(
                ASwapBidQuoteAsset const &)> saleProcessor)
{
    ASwapBidQuoteAsset quoteAsset;
    int64_t version;

    statement& st = prep.statement();
    st.exchange(into(quoteAsset.quoteAsset));
    st.exchange(into(quoteAsset.price));
    st.exchange(into(version));
    st.define_and_bind();
    st.execute(true);

    while (st.got_data())
    {
        quoteAsset.ext.v(static_cast<LedgerVersion>(version));

        saleProcessor(quoteAsset);
        st.fetch();
    }
}

xdr::xvector<ASwapBidQuoteAsset>
ASwapBidQuoteAssetHelper::loadQuoteAssets(Database &db, uint64_t bidID)
{
    string const sql = "SELECT quote_asset, price, version FROM atomic_swap_quote_asset "
                       "WHERE bid_id = :id";
    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();
    st.exchange(use(bidID, "id"));

    xdr::xvector<ASwapBidQuoteAsset> result;
    auto timer = db.getSelectTimer("atomic-swap-bid");
    loadASwapQuoteAsset(prep, [&result](ASwapBidQuoteAsset const& entry)
    {
        result.push_back(entry);
    });

    return result;
}

}