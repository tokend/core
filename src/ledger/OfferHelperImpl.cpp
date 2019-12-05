// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "OfferHelperImpl.h"
#include "LedgerDelta.h"
#include "ledger/StorageHelperImpl.h"
#include "ledger/AssetHelper.h"
#include "ledger/BalanceHelper.h"
#include "xdrpp/printer.h"
#include "database/Database.h"

using namespace soci;
using namespace std;

namespace stellar {
    using xdr::operator<;

    static const char* offerColumnSelector =
            "SELECT owner_id, offer_id, order_book_id, base_asset_code, quote_asset_code, base_amount, quote_amount,"
            "price, fee, percent_fee, is_buy, base_balance_id, quote_balance_id, created_at, lastmodified, version "
            "FROM offer";

    void OfferHelperImpl::dropAll() {
        Database& db = getDatabase();
        db.getSession() << "DROP TABLE IF EXISTS offer;";
        db.getSession() << "CREATE TABLE offer"
                           "("
                           "owner_id          	VARCHAR(56)      NOT NULL,"
                           "offer_id           BIGINT           NOT NULL CHECK (offer_id >= 0),"
                           "order_book_id      BIGINT           NOT NULL CHECK (order_book_id >= 0),"
                           "base_asset_code    VARCHAR(16)      NOT NULL,"
                           "quote_asset_code   VARCHAR(16)      NOT NULL,"
                           "is_buy             BOOLEAN          NOT NULL,"
                           "base_amount        BIGINT           NOT NULL CHECK (base_amount > 0),"
                           "quote_amount       BIGINT           NOT NULL CHECK (quote_amount > 0),"
                           "price              BIGINT           NOT NULL CHECK (price > 0),"
                           "fee                BIGINT           NOT NULL CHECK (fee >= 0),"
                           "percent_fee        BIGINT           NOT NULL CHECK (percent_fee >= 0),"
                           "base_balance_id    VARCHAR(56)      NOT NULL,"
                           "quote_balance_id   VARCHAR(56)      NOT NULL,"
                           "created_at         BIGINT           NOT NULL,"
                           "lastmodified       INT              NOT NULL,"
                           "version			INT				 NOT NULL DEFAULT 0,"
                           "PRIMARY KEY      (offer_id)"
                           ");";
        db.getSession() << "CREATE INDEX base_quote_price ON offer"
                           " (order_book_id, base_asset_code, quote_asset_code, is_buy, price);";
    }

    void OfferHelperImpl::storeAdd(LedgerEntry const &entry) {
        storeUpdateHelper(true, entry);
    }

    void OfferHelperImpl::storeChange(LedgerEntry const &entry) {
        storeUpdateHelper(false, entry);
    }

    void OfferHelperImpl::storeDelete(LedgerKey const &key) {
        Database& db = getDatabase();
        LedgerDelta* delta = mStorageHelper.getLedgerDelta();
        auto timer = db.getDeleteTimer("offer");
        auto prep = db.getPreparedStatement("DELETE FROM offer WHERE offer_id=:s");
        auto& st = prep.statement();
        st.exchange(use(key.offer().offerID));
        st.define_and_bind();
        st.execute(true);
        delta->deleteEntry(key);
    }

    bool OfferHelperImpl::exists(LedgerKey const &key) {
        Database& db = getDatabase();
        std::string actIDStrKey = PubKeyUtils::toStrKey(key.offer().ownerID);
        int exists = 0;
        auto timer = db.getSelectTimer("offer-exists");
        auto prep =
                db.getPreparedStatement("SELECT EXISTS (SELECT NULL FROM offer WHERE owner_id=:id AND offer_id=:s)");
        auto& st = prep.statement();
        st.exchange(use(actIDStrKey));
        st.exchange(use(key.offer().offerID));
        st.exchange(into(exists));
        st.define_and_bind();
        st.execute(true);
        return exists != 0;
    }

    LedgerKey OfferHelperImpl::getLedgerKey(LedgerEntry const &from) {
        LedgerKey ledgerKey;
        ledgerKey.type(from.data.type());
        ledgerKey.offer().offerID = from.data.offer().offerID;
        ledgerKey.offer().ownerID = from.data.offer().ownerID;
        return ledgerKey;
    }

    EntryFrame::pointer OfferHelperImpl::storeLoad(LedgerKey const &key) {
        return loadOffer(key.offer().ownerID, key.offer().offerID);
    }

    EntryFrame::pointer OfferHelperImpl::fromXDR(LedgerEntry const &from) {
        return std::make_shared<OfferFrame>(from);
    }

    uint64_t OfferHelperImpl::countObjects() {
        uint64_t count = 0;
        Database &db = getDatabase();
        db.getSession() << "SELECT COUNT(*) FROM offer;", into(count);
        return count;
    }

    void OfferHelperImpl::storeUpdateHelper(bool insert, LedgerEntry const &entry) {
        Database& db = getDatabase();
        auto& delta = mStorageHelper.mustGetLedgerDelta();
        auto offerFrame = make_shared<OfferFrame>(entry);
        auto offerEntry = offerFrame->getOffer();
        offerFrame->touch(delta);

        if (!offerFrame->isValid())
        {
            CLOG(ERROR, Logging::ENTRY_LOGGER)
                    << "Unexpected state - offer is invalid: "
                    << xdr::xdr_to_string(offerFrame->getOffer());
            throw std::runtime_error("Unexpected state - offer is invalid");
        }
        checkAmounts(offerFrame);

        string sql;

        if (insert)
        {
            sql = "INSERT INTO offer (owner_id, offer_id, order_book_id,"
                  "base_asset_code, quote_asset_code, base_amount, quote_amount,"
                  "price, fee, percent_fee, is_buy, "
                  "base_balance_id, quote_balance_id, created_at, lastmodified, version) "
                  "VALUES "
                  "(:sid, :oid, :order_book_id, :sac, :bac, :ba, :qa, :p, :f, :pf, :ib, :sbi, :bbi, :ca, :l, :v)";
        }
        else
        {
            sql = "UPDATE offer "
                  "SET order_book_id = :order_book_id, base_asset_code=:sac, quote_asset_code=:bac, base_amount=:ba, quote_amount=:qa,"
                  "price=:p, fee=:f, percent_fee=:pf, is_buy=:ib,"
                  "base_balance_id=:sbi, quote_balance_id=:bbi, created_at=:ca,"
                  "lastmodified=:l, version=:v "
                  "WHERE  offer_id=:oid";
        }

        auto prep = db.getPreparedStatement(sql);
        auto& st = prep.statement();

        auto offerVersion = static_cast<int32_t >(offerEntry.ext.v());

        auto ownerID = PubKeyUtils::toStrKey(offerEntry.ownerID);
        if (insert)
        {
            st.exchange(use(ownerID, "sid"));
        }
        st.exchange(use(offerEntry.offerID, "oid"));
        st.exchange(use(offerEntry.orderBookID, "order_book_id"));
        st.exchange(use(offerEntry.base, "sac"));
        st.exchange(use(offerEntry.quote, "bac"));
        st.exchange(use(offerEntry.baseAmount, "ba"));
        st.exchange(use(offerEntry.quoteAmount, "qa"));
        st.exchange(use(offerEntry.price, "p"));
        st.exchange(use(offerEntry.fee, "f"));
        st.exchange(use(offerEntry.percentFee, "pf"));
        int isBuy = offerEntry.isBuy ? 1 : 0;
        st.exchange(use(isBuy, "ib"));
        auto baseBalance = BalanceKeyUtils::toStrKey(offerEntry.baseBalance);
        st.exchange(use(baseBalance, "sbi"));
        auto quoteBalance = BalanceKeyUtils::toStrKey(offerEntry.quoteBalance);
        st.exchange(use(quoteBalance, "bbi"));
        st.exchange(use(offerEntry.createdAt, "ca"));
        st.exchange(use(offerFrame->mEntry.lastModifiedLedgerSeq, "l"));
        st.exchange(use(offerVersion, "v"));
        st.define_and_bind();

        auto timer =
                insert ? db.getInsertTimer("offer") : db.getUpdateTimer("offer");
        st.execute(true);

        if (st.get_affected_rows() != 1)
        {
            throw runtime_error("could not update SQL");
        }

        if (insert)
        {
            delta.addEntry(*offerFrame);
        }
        else
        {
            delta.modEntry(*offerFrame);
        }
    }

    void OfferHelperImpl::loadOffers(StatementContext &prep, function<void(const LedgerEntry &)> offerProcessor) {
        int isBuy;
        int32_t offerVersion = 0;

        LedgerEntry le;
        le.data.type(LedgerEntryType::OFFER_ENTRY);
        OfferEntry& oe = le.data.offer();

        statement& st = prep.statement();
        st.exchange(into(oe.ownerID));
        st.exchange(into(oe.offerID));
        st.exchange(into(oe.orderBookID));
        st.exchange(into(oe.base));
        st.exchange(into(oe.quote));
        st.exchange(into(oe.baseAmount));
        st.exchange(into(oe.quoteAmount));
        st.exchange(into(oe.price));
        st.exchange(into(oe.fee));
        st.exchange(into(oe.percentFee));
        st.exchange(into(isBuy));
        st.exchange(into(oe.baseBalance));
        st.exchange(into(oe.quoteBalance));
        st.exchange(into(oe.createdAt));
        st.exchange(into(le.lastModifiedLedgerSeq));
        st.exchange(into(offerVersion));
        st.define_and_bind();
        st.execute(true);
        while (st.got_data())
        {
            oe.isBuy = isBuy > 0;
            oe.ext.v(static_cast<LedgerVersion>(offerVersion));
            if (!OfferFrame::isValid(oe))
            {
                CLOG(ERROR, Logging::ENTRY_LOGGER)
                        << "Unexpected state - offer is invalid: "
                        << xdr::xdr_to_string(oe);
                throw runtime_error("Unexpected state - offer is invalid");
            }

            offerProcessor(le);
            st.fetch();
        }
    }

    bool OfferHelperImpl::exists(AssetCode const &base, AssetCode const &quote, uint64_t *orderBookIDPtr)
    {
        Database& db = getDatabase();
        auto timer = db.getSelectTimer("offer-exists");
        string sql = "SELECT NULL FROM offer "
                     "WHERE base_asset_code = :base_asset "
                     "AND quote_asset_code = :quote_asset";
        if (orderBookIDPtr != nullptr)
        {
            sql += " AND order_book_id = :order_book_id";
        }
        sql = "SELECT EXISTS (" + sql + ")";
        auto prep = db.getPreparedStatement(sql);
        auto& st = prep.statement();

        string baseAssetCode = base;
        string quoteAssetCode = quote;
        st.exchange(use(baseAssetCode, "base_asset"));
        st.exchange(use(quoteAssetCode, "quote_asset"));
        if (orderBookIDPtr != nullptr)
        {
            uint64_t orderBookID = *orderBookIDPtr;
            st.exchange(use(orderBookID, "order_book_id"));
        }

        auto exists = 0;
        st.exchange(into(exists));
        st.define_and_bind();
        st.execute(true);

        return exists != 0;
    }

    OfferFrame::pointer
    OfferHelperImpl::loadOffer(AccountID const &accountID, uint64_t offerID) {
        Database& db = getDatabase();
        LedgerDelta* delta = getLedgerDelta();
        OfferFrame::pointer retOffer;

        std::string actIDStrKey = PubKeyUtils::toStrKey(accountID);

        std::string sql = offerColumnSelector;
        sql += " WHERE owner_id = :id AND offer_id = :offer_id";
        auto prep = db.getPreparedStatement(sql);
        auto& st = prep.statement();
        st.exchange(use(actIDStrKey));
        st.exchange(use(offerID));

        auto timer = db.getSelectTimer("offer");
        loadOffers(prep, [&retOffer](LedgerEntry const& offer) {
            retOffer = make_shared<OfferFrame>(offer);
        });

        if (delta && retOffer)
        {
            delta->recordEntry(*retOffer);
        }

        return retOffer;
    }

    bool OfferHelperImpl::exists(AssetCode const &code, uint64_t *orderBookIDPtr)
    {
        Database& db = getDatabase();
        auto timer = db.getSelectTimer("offer-for-asset-exists");
        string sql = "SELECT NULL FROM offer "
                     "WHERE base_asset_code = :code "
                     "OR quote_asset_code = :code";
        if (orderBookIDPtr != nullptr)
        {
            sql += " AND order_book_id = :order_book_id";
        }
        sql = "SELECT EXISTS (" + sql + ")";
        auto prep = db.getPreparedStatement(sql);
        auto& st = prep.statement();

        string assetCode = code;
        st.exchange(use(assetCode, "code"));
        if (orderBookIDPtr != nullptr)
        {
            uint64_t orderBookID = *orderBookIDPtr;
            st.exchange(use(orderBookID, "order_book_id"));
        }

        auto exists = 0;
        st.exchange(into(exists));
        st.define_and_bind();
        st.execute(true);

        return exists != 0;
    }

    OfferFrame::pointer OfferHelperImpl::loadOffer(AccountID const& accountID,
                                               uint64_t offerID, uint64_t orderBookID)
    {
        auto offer = loadOffer(accountID, offerID);
        if (!!offer && offer->getOrderBookID() != orderBookID)
        {
            return nullptr;
        }

        return offer;
    }

    vector<OfferFrame::pointer> OfferHelperImpl::loadOffersWithFilters(
            AssetCode const& base, AssetCode const& quote, uint64_t* orderBookIDPtr,
            uint64_t* priceUpperBoundPtr)
    {
        Database& db = getDatabase();
        string sql = offerColumnSelector;
        sql += " WHERE base_asset_code=:base_asset_code AND quote_asset_code = :quote_asset_code ";
        // do not join declaration and use, will lead to issues as `use` receives reference
        uint64_t orderBookID;
        if (!!orderBookIDPtr)
        {
            sql += " AND order_book_id = :order_book_id";
            orderBookID = *orderBookIDPtr;
        }

        uint64_t priceUpperBound;
        if (!!priceUpperBoundPtr)
        {
            sql += " AND price < :p";
            priceUpperBound = *priceUpperBoundPtr;
        }

        sql += " ORDER BY offer_id ASC";

        auto prep = db.getPreparedStatement(sql);
        auto& st = prep.statement();

        string baseAssetCode = base;
        string quoteAssetCode = quote;

        st.exchange(use(baseAssetCode));
        st.exchange(use(quoteAssetCode));
        if (!!orderBookIDPtr)
        {
            st.exchange(use(orderBookID));
        }

        if (!!priceUpperBoundPtr)
        {
            st.exchange(use(priceUpperBound));
        }

        auto timer = db.getSelectTimer("offer");
        vector<OfferFrame::pointer> results;
        loadOffers(prep, [&results](LedgerEntry const& of) {
            results.emplace_back(make_shared<OfferFrame>(of));
        });

        return results;
    }

    std::vector<OfferFrame::pointer> OfferHelperImpl::loadOffers(AssetCode const& base,
                                                             AssetCode const& quote, uint64_t const orderBookID,
                                                             int64_t quoteamountUpperBound)
    {
        Database& db = getDatabase();
        string sql = offerColumnSelector;
        sql += " WHERE base_asset_code=:base_asset_code AND quote_asset_code = :quote_asset_code AND order_book_id = :order_book_id AND quote_amount < :quote_amount";
        sql += " ORDER BY offer_id ASC";
        auto prep = db.getPreparedStatement(sql);
        auto& st = prep.statement();

        string baseAssetCode = base;
        string quoteAssetCode = quote;

        st.exchange(use(baseAssetCode));
        st.exchange(use(quoteAssetCode));
        st.exchange(use(orderBookID));
        st.exchange(use(quoteamountUpperBound));

        auto timer = db.getSelectTimer("offer");
        vector<OfferFrame::pointer> results;
        loadOffers(prep, [&results](LedgerEntry const& of) {
            results.emplace_back(make_shared<OfferFrame>(of));
        });

        return results;
    }

    std::vector<OfferFrame::pointer>
    OfferHelperImpl::loadOffers(AccountID const &accountID, uint64_t const orderBookID)
    {
        Database& db = getDatabase();
        string sql = offerColumnSelector;
        sql += " WHERE order_book_id = :obi AND owner_id = :oi";
        sql += " ORDER BY offer_id ASC";
        std::string accountIDStr;
        accountIDStr = PubKeyUtils::toStrKey(accountID);

        auto prep = db.getPreparedStatement(sql);
        auto& st = prep.statement();

        st.exchange(use(orderBookID, "obi"));
        st.exchange(use(accountIDStr, "oi"));

        auto timer = db.getSelectTimer("offers");

        std::vector<OfferFrame::pointer> result;
        loadOffers(prep, [&result](LedgerEntry const& of)
        {
            result.emplace_back(make_shared<OfferFrame>(of));
        });
        return result;
    }

    std::unordered_map<AccountID, std::vector<OfferFrame::pointer>> OfferHelperImpl::loadAllOffers() {
        Database& db = getDatabase();
        std::unordered_map<AccountID, std::vector<OfferFrame::pointer>> retOffers;
        std::string sql = offerColumnSelector;
        sql += " ORDER BY owner_id";
        auto prep = db.getPreparedStatement(sql);

        auto timer = db.getSelectTimer("offer");
        loadOffers(prep, [&retOffers](LedgerEntry const& of) {
            auto& thisUserOffers = retOffers[of.data.offer().ownerID];
            thisUserOffers.emplace_back(make_shared<OfferFrame>(of));
        });
        return retOffers;
    }

    void OfferHelperImpl::loadBestOffers(size_t numOffers, size_t offset, AssetCode const &base, AssetCode const &quote, uint64_t orderBookID,
                                     bool isBuy, std::vector<OfferFrame::pointer> &retOffers) {
        Database& db = getDatabase();
        std::string sql = offerColumnSelector;
        sql += " WHERE base_asset_code=:s AND quote_asset_code = :b AND order_book_id = :order_book_id AND is_buy=:ib";

        sql += " ORDER BY price ";
        sql += isBuy ? "DESC" : "ASC";

        sql += ", offer_id ASC LIMIT :n OFFSET :o";

        auto prep = db.getPreparedStatement(sql);
        auto& st = prep.statement();

        int isBuyRaw = isBuy ? 1 : 0;

        st.exchange(use(base));
        st.exchange(use(quote));
        st.exchange(use(orderBookID));
        st.exchange(use(isBuyRaw));
        st.exchange(use(numOffers));
        st.exchange(use(offset));

        auto timer = db.getSelectTimer("offer");
        loadOffers(prep, [&retOffers](LedgerEntry const& of) {
            retOffers.emplace_back(make_shared<OfferFrame>(of));
        });
    }

    void OfferHelperImpl::checkAmounts(const OfferFrame::pointer& frame) const
    {
        const OfferEntry& entry = frame->getOffer();

        auto baseBalance = mStorageHelper.getBalanceHelper().loadBalance(entry.baseBalance);
        auto quoteBalance = mStorageHelper.getBalanceHelper().loadBalance(entry.quoteBalance);
        if (!baseBalance || !quoteBalance)
        {
            throw std::runtime_error("Unexpected state: unable to find offer balances");
        }

        if (!mStorageHelper.getAssetHelper().doesAmountFitAssetPrecision(
                baseBalance->getAsset(), frame->getOffer().baseAmount))
        {
            throw std::runtime_error("Invalid base amount");
        }

        if (!mStorageHelper.getAssetHelper().doesAmountFitAssetPrecision(
                quoteBalance->getAsset(), frame->getOffer().quoteAmount))
        {
            throw std::runtime_error("Invalid quote amount");
        }
    }

    LedgerDelta *OfferHelperImpl::getLedgerDelta() {
        return mStorageHelper.getLedgerDelta();
    }

    Database &OfferHelperImpl::getDatabase() {
        return mStorageHelper.getDatabase();
    }

    OfferHelperImpl::OfferHelperImpl(StorageHelper &storageHelper)
            : mStorageHelper(storageHelper)
    {
    }
}