#include <util/Logging.h>
#include "AtomicSwapAskQuoteAssetHelper.h"
#include "database/Database.h"

using namespace soci;
using namespace std;

namespace stellar
{
using xdr::operator<;

void
AtomicSwapAskQuoteAssetHelper::dropAll(Database &db)
{
    db.getSession() << "DROP TABLE IF EXISTS atomic_swap_quote_asset;";
    db.getSession() << "CREATE TABLE atomic_swap_quote_asset"
                       "("
                       "ask_id      BIGINT          NOT NULL CHECK (ask_id >= 0),"
                       "quote_asset VARCHAR(16)     NOT NULL,"
                       "price       NUMERIC(20,0)   NOT NULL CHECK (price > 0),"
                       "version     INT             NOT NULL,"
                       "PRIMARY KEY (ask_id, quote_asset)"
                       ");";
}

void
AtomicSwapAskQuoteAssetHelper::deleteAllForAsk(Database &db, uint64_t askID)
{
    auto prep = db.getPreparedStatement("DELETE FROM atomic_swap_quote_asset "
                                        "WHERE ask_id = :id");
    auto& st = prep.statement();
    st.exchange(use(askID, "id"));
    st.define_and_bind();
    st.execute(true);
}

void
AtomicSwapAskQuoteAssetHelper::storeUpdate(Database &db, uint64_t askID,
        xdr::xvector<AtomicSwapAskQuoteAsset> quoteAssets, bool insert)
{
    for (auto const& quoteAsset : quoteAssets)
    {
        storeUpdate(db, askID, quoteAsset, insert);
    }
}

void
AtomicSwapAskQuoteAssetHelper::storeUpdate(Database &db, uint64_t askID,
        AtomicSwapAskQuoteAsset const &quoteAsset, bool insert)
{
    string sql;

    auto version = static_cast<int32_t>(quoteAsset.ext.v());

    if (insert)
    {
        sql = "INSERT INTO atomic_swap_quote_asset (ask_id, quote_asset, price, version) "
              "VALUES (:id, :qa, :p, :v)";
    }
    else
    {
        sql = "UPDATE atomic_swap_quote_asset SET price = :p, version = :v "
              "WHERE ask_id = :id AND quote_asset = :qa";
    }

    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();

    st.exchange(use(askID, "id"));
    st.exchange(use(quoteAsset.quoteAsset, "qa"));
    st.exchange(use(quoteAsset.price, "p"));
    st.exchange(use(version, "v"));
    st.define_and_bind();
    st.execute(true);

    if (st.get_affected_rows() != 1)
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER) << "Failed to update atomic swap ask quote "
                                              "asset with id: " << askID
                                           << quoteAsset.quoteAsset;
        throw runtime_error("Failed to update atomic swap ask quote asset");
    }
}

void AtomicSwapAskQuoteAssetHelper::loadASwapQuoteAsset(
        StatementContext &prep, const std::function<void(
                AtomicSwapAskQuoteAsset const &)> processor)
{
    AtomicSwapAskQuoteAsset quoteAsset;
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

        processor(quoteAsset);
        st.fetch();
    }
}

xdr::xvector<AtomicSwapAskQuoteAsset>
AtomicSwapAskQuoteAssetHelper::loadQuoteAssets(Database &db, uint64_t askID)
{
    string const sql = "SELECT quote_asset, price, version FROM atomic_swap_quote_asset "
                       "WHERE ask_id = :id";
    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();
    st.exchange(use(askID, "id"));

    xdr::xvector<AtomicSwapAskQuoteAsset> result;
    auto timer = db.getSelectTimer("atomic-swap-ask-quote-asset");
    loadASwapQuoteAsset(prep, [&result](AtomicSwapAskQuoteAsset const& entry)
    {
        result.emplace_back(entry);
    });

    return result;
}

}