#include "SaleHelperImpl.h"
#include "xdrpp/printer.h"
#include "LedgerDelta.h"
#include "SaleQuoteAssetHelper.h"
#include "ledger/AssetHelper.h"
#include "ledger/StorageHelperImpl.h"
#include "database/Database.h"

using namespace soci;
using namespace std;

namespace stellar
{
    using xdr::operator<;

    void SaleHelperImpl::dropAll()
    {
        Database& db = getDatabase();
        db.getSession() << "DROP TABLE IF EXISTS sale CASCADE;";
        db.getSession() << "CREATE TABLE sale"
                           "("
                           "id                  BIGINT        NOT NULL CHECK (id >= 0),"
                           "type                BIGINT        NOT NULL,"
                           "owner_id            VARCHAR(56)   NOT NULL,"
                           "base_asset          VARCHAR(16)   NOT NULL,"
                           "default_quote_asset VARCHAR(16)   NOT NULL,"
                           "start_time          BIGINT        NOT NULL CHECK (start_time >= 0),"
                           "end_time            BIGINT        NOT NULL CHECK (end_time >= 0),"
                           "soft_cap            NUMERIC(20,0) NOT NULL CHECK (soft_cap >= 0),"
                           "hard_cap            NUMERIC(20,0) NOT NULL CHECK (hard_cap >= 0),"
                           "hard_cap_in_base    NUMERIC(20,0) NOT NULL CHECK (hard_cap_in_base >= 0),"
                           "current_cap_in_base NUMERIC(20,0) NOT NULL CHECK (current_cap_in_base >= 0),"
                           "details             TEXT          NOT NULL,"
                           "base_balance        VARCHAR(56)   NOT NULL,"
                           "version             INT           NOT NULL,"
                           "lastmodified        INT           NOT NULL,"
                           "sale_type           INT           NOT NULL DEFAULT 0,"
                           "PRIMARY KEY (id)"
                           ");";

        SaleQuoteAssetHelper::dropAll(db);
    }

    void SaleHelperImpl::storeAdd(LedgerEntry const& entry)
    {
        storeUpdateHelper(true, entry);
    }

    void SaleHelperImpl::storeChange(LedgerEntry const& entry)
    {
        storeUpdateHelper(false, entry);
    }

    void SaleHelperImpl::storeDelete(LedgerKey const& key)
    {
        Database& db = getDatabase();
        LedgerDelta* delta = getLedgerDelta();
        flushCachedEntry(key);
        auto timer = db.getDeleteTimer("sale");
        auto prep = db.getPreparedStatement("DELETE FROM sale WHERE id=:id");
        auto& st = prep.statement();
        st.exchange(use(key.sale().saleID));
        st.define_and_bind();
        st.execute(true);
        SaleQuoteAssetHelper::deleteAllForSale(db, key.sale().saleID);
        delta->deleteEntry(key);
    }

    bool SaleHelperImpl::exists(LedgerKey const& key)
    {
        if (cachedEntryExists(key) && getCachedEntry(key))
        {
            return true;
        }

        Database& db = getDatabase();
        auto timer = db.getSelectTimer("sale_exists");
        auto prep =
                db.getPreparedStatement("SELECT EXISTS (SELECT NULL FROM sale WHERE id=:id)");
        auto& st = prep.statement();
        st.exchange(use(key.sale().saleID));
        auto exists = 0;
        st.exchange(into(exists));
        st.define_and_bind();
        st.execute(true);

        return exists != 0;
    }

    bool SaleHelperImpl::exists(uint64_t saleID)
    {
        Database& db = getDatabase();
        auto timer = db.getSelectTimer("sale_exists");
        auto prep = db.getPreparedStatement("SELECT EXISTS (SELECT NULL FROM sale WHERE id=:id)");
        auto& st = prep.statement();
        st.exchange(use(saleID));
        auto exists = 0;
        st.exchange(into(exists));
        st.define_and_bind();
        st.execute(true);

        return exists != 0;
    }

    bool SaleHelperImpl::exists(AssetCode const &base, AssetCode const &quote)
    {
        Database& db = getDatabase();
        auto timer = db.getSelectTimer("sale_exists");
        auto prep = db.getPreparedStatement(
                "SELECT EXISTS "
                "(SELECT NULL FROM sale "
                "INNER JOIN sale_quote_asset ON sale.id = sale_quote_asset.sale_id "
                "WHERE sale.base_asset = :base_asset "
                "AND sale_quote_asset.quote_asset = :quote_asset)");
        auto& st = prep.statement();

        string baseAssetCode = base;
        string quoteAssetCode = quote;
        st.exchange(use(baseAssetCode, "base_asset"));
        st.exchange(use(quoteAssetCode, "quote_asset"));

        auto exists = 0;
        st.exchange(into(exists));
        st.define_and_bind();
        st.execute(true);

        return exists != 0;
    }

    bool SaleHelperImpl::exists(AssetCode const &code)
    {
        Database& db = getDatabase();
        auto timer = db.getSelectTimer("sale_exists");
        auto prep = db.getPreparedStatement(
                "SELECT EXISTS "
                "(SELECT NULL FROM sale "
                "INNER JOIN sale_quote_asset ON sale.id = sale_quote_asset.sale_id "
                "WHERE sale.base_asset = :code "
                "or sale_quote_asset.quote_asset = :code)");
        auto& st = prep.statement();

        string assetCode = code;
        st.exchange(use(assetCode, "code"));

        auto exists = 0;
        st.exchange(into(exists));
        st.define_and_bind();
        st.execute(true);

        return exists != 0;
    }

    LedgerKey SaleHelperImpl::getLedgerKey(LedgerEntry const& from)
    {
        LedgerKey ledgerKey;
        ledgerKey.type(from.data.type());
        ledgerKey.sale().saleID = from.data.sale().saleID;
        return ledgerKey;
    }

    EntryFrame::pointer SaleHelperImpl::fromXDR(LedgerEntry const& from)
    {
        return std::make_shared<SaleFrame>(from);
    }

    uint64_t SaleHelperImpl::countObjects()
    {
        uint64_t count = 0;
        Database& db = getDatabase();
        db.getSession() << "SELECT COUNT(*) FROM sale;", into(count);
        return count;
    }

    void SaleHelperImpl::storeUpdateHelper(const bool insert,
                                       const LedgerEntry& entry)
    {
        auto saleFrame = make_shared<SaleFrame>(entry);
        saleFrame->normalize();
        saleFrame->touch(mStorageHelper.mustGetLedgerDelta());
        const auto saleEntry = saleFrame->getSaleEntry();
        saleFrame->ensureValid();

        if (!mStorageHelper.getAssetHelper().doesAmountFitAssetPrecision(
                saleFrame->getBaseAsset(), saleFrame->getCurrentCapInBase()))
        {
            throw std::runtime_error("Invalid current cap in base");
        }
        if (!mStorageHelper.getAssetHelper().doesAmountFitAssetPrecision(
                saleFrame->getBaseAsset(), saleFrame->getMaxAmountToBeSold()))
        {
            throw std::runtime_error("Invalid max amount to be sold");
        }
        if (!mStorageHelper.getAssetHelper().doesAmountFitAssetPrecision(
                saleFrame->getDefaultQuoteAsset(), saleFrame->getSoftCap()))
        {
            throw std::runtime_error("Invalid soft cap amount");
        }
        if (!mStorageHelper.getAssetHelper().doesAmountFitAssetPrecision(
                saleFrame->getDefaultQuoteAsset(), saleFrame->getHardCap()))
        {
            throw std::runtime_error("Invalid hard cap amount");
        }

        const auto key = saleFrame->getKey();
        flushCachedEntry(key);
        string sql;

        auto version = static_cast<int32_t>(saleEntry.ext.v());

        if (insert)
        {
            sql =
                    "INSERT INTO sale (id, type, owner_id, base_asset, default_quote_asset, start_time,"
                    " end_time, soft_cap, hard_cap, details, version, lastmodified, base_balance, current_cap_in_base, hard_cap_in_base, sale_type)"
                    " VALUES (:id, :t, :owner_id, :base_asset, :default_quote_asset, :start_time,"
                    " :end_time, :soft_cap, :hard_cap, :details, :v, :lm, :base_balance, :current_cap_in_base, :hard_cap_in_base, :sale_type)";
        }
        else
        {
            sql =
                    "UPDATE sale SET type = :t, owner_id=:owner_id, base_asset = :base_asset, default_quote_asset = :default_quote_asset, start_time = :start_time,"
                    " end_time= :end_time, soft_cap = :soft_cap, hard_cap = :hard_cap, details = :details, version=:v, lastmodified=:lm, "
                    " base_balance = :base_balance, current_cap_in_base = :current_cap_in_base, hard_cap_in_base = :hard_cap_in_base, sale_type = :sale_type "
                    " WHERE id = :id";
        }
        Database& db = getDatabase();
        LedgerDelta* delta = getLedgerDelta();
        auto prep = db.getPreparedStatement(sql);
        auto& st = prep.statement();

        st.exchange(use(saleEntry.saleID, "id"));
        st.exchange(use(saleEntry.saleType, "t"));
        auto ownerID = PubKeyUtils::toStrKey(saleEntry.ownerID);
        st.exchange(use(ownerID, "owner_id"));
        st.exchange(use(saleEntry.baseAsset, "base_asset"));
        st.exchange(use(saleEntry.defaultQuoteAsset, "default_quote_asset"));
        st.exchange(use(saleEntry.startTime, "start_time"));
        st.exchange(use(saleEntry.endTime, "end_time"));
        st.exchange(use(saleEntry.softCap, "soft_cap"));
        st.exchange(use(saleEntry.hardCap, "hard_cap"));
        st.exchange(use(saleEntry.details, "details"));
        st.exchange(use(version, "v"));
        st.exchange(use(saleFrame->mEntry.lastModifiedLedgerSeq, "lm"));
        auto baseBalance = BalanceKeyUtils::toStrKey(saleEntry.baseBalance);
        st.exchange(use(baseBalance, "base_balance"));
        st.exchange(use(saleEntry.currentCapInBase, "current_cap_in_base"));
        st.exchange(use(saleEntry.maxAmountToBeSold, "hard_cap_in_base"));
        auto saleType = static_cast<int>(SaleFrame::getSaleType(saleEntry));
        st.exchange(use(saleType, "sale_type"));
        st.define_and_bind();

        auto timer = insert
                     ? db.getInsertTimer("sale")
                     : db.getUpdateTimer("sale");
        st.execute(true);

        if (st.get_affected_rows() != 1)
        {
            CLOG(ERROR, Logging::ENTRY_LOGGER) << "Failed to update sale with id: " << saleEntry.saleID;
            throw runtime_error("Failed to update sale");
        }

        SaleQuoteAssetHelper::storeUpdate(db, saleEntry.saleID, saleEntry.quoteAssets, insert);

        if (insert)
        {
            delta->addEntry(*saleFrame);
        }
        else
        {
            delta->modEntry(*saleFrame);
        }
    }

    void SaleHelperImpl::loadSales(StatementContext& prep,
                               const function<void(LedgerEntry const&)>
                               saleProcessor) const
    {
        try
        {
            LedgerEntry le;
            le.data.type(LedgerEntryType::SALE);
            auto& oe = le.data.sale();
            int version;

            statement& st = prep.statement();
            st.exchange(into(oe.saleID));
            st.exchange(into(oe.saleType));
            st.exchange(into(oe.ownerID));
            st.exchange(into(oe.baseAsset));
            st.exchange(into(oe.defaultQuoteAsset));
            st.exchange(into(oe.startTime));
            st.exchange(into(oe.endTime));
            st.exchange(into(oe.softCap));
            st.exchange(into(oe.hardCap));
            st.exchange(into(oe.details));
            st.exchange(into(oe.baseBalance));
            st.exchange(into(version));
            st.exchange(into(le.lastModifiedLedgerSeq));
            st.exchange(into(oe.currentCapInBase));
            st.exchange(into(oe.maxAmountToBeSold));
            int rawSaleType = 0;
            st.exchange(into(rawSaleType));

            st.define_and_bind();
            st.execute(true);

            while (st.got_data())
            {
                oe.ext.v(static_cast<LedgerVersion>(version));
                const auto saleType = SaleType(rawSaleType);
                SaleFrame::setSaleType(oe, saleType);
                oe.quoteAssets = SaleQuoteAssetHelper::loadQuoteAssets(mStorageHelper.getDatabase(), oe.saleID);
                SaleFrame::ensureValid(oe);

                saleProcessor(le);
                st.fetch();
            }
        } catch (...)
        {
            throw_with_nested(runtime_error("Failed to load sale"));
        }
    }

    SaleFrame::pointer SaleHelperImpl::loadSale(uint64_t saleID, AccountID ownerID) {
        auto saleFrame = loadSale(saleID);
        if (!saleFrame)
            return nullptr;
        return ownerID == saleFrame->getOwnerID() ? saleFrame : nullptr;
    }

    SaleFrame::pointer SaleHelperImpl::loadSale(uint64_t saleID)
    {
        LedgerKey key;
        Database& db = getDatabase();
        LedgerDelta* delta = getLedgerDelta();
        key.type(LedgerEntryType::SALE);
        key.sale().saleID = saleID;
        if (cachedEntryExists(key))
        {
            const auto p = getCachedEntry(key);
            auto result = p ? std::make_shared<SaleFrame>(*p) : nullptr;
            if (!!delta && !!result)
            {
                delta->recordEntry(*result);
            }
            return result;
        }

        string sql = mSaleColumnSelector;
        sql += +" WHERE id = :id";
        auto prep = db.getPreparedStatement(sql);
        auto& st = prep.statement();
        st.exchange(use(saleID));

        SaleFrame::pointer retSale;
        auto timer = db.getSelectTimer("sale");
        loadSales(prep, [&retSale](LedgerEntry const& entry)
        {
            retSale = make_shared<SaleFrame>(entry);
            retSale->normalize();
        });

        if (!retSale)
        {
            putCachedEntry(key, nullptr);
            return nullptr;
        }

        if (delta)
        {
            delta->recordEntry(*retSale);
        }

        const auto pEntry = std::make_shared<LedgerEntry>(retSale->mEntry);
        putCachedEntry(key, pEntry);
        return retSale;
    }

    SaleFrame::pointer SaleHelperImpl::loadSale(const uint64_t saleID, AssetCode const& base,
                                            AssetCode const& quote)
    {
        auto sale = loadSale(saleID);
        if (!sale)
        {
            return nullptr;
        }

        if (!(sale->getBaseAsset() == base))
        {
            return nullptr;
        }

        for (auto const& quoteAsset : sale->getSaleEntry().quoteAssets)
        {
            if (quoteAsset.quoteAsset == quote)
                return sale;
        }

        return nullptr;
    }

    std::vector<SaleFrame::pointer> SaleHelperImpl::loadSalesForOwner(AccountID owner)
    {
        Database& db = getDatabase();
        string sql = mSaleColumnSelector;
        sql += +" WHERE owner_id = :owner_id";
        auto prep = db.getPreparedStatement(sql);
        auto& st = prep.statement();
        std::string rawOwnerID = PubKeyUtils::toStrKey(owner);
        st.exchange(use(rawOwnerID));

        vector<SaleFrame::pointer> result;
        auto timer = db.getSelectTimer("sale");
        loadSales(prep, [&result](LedgerEntry const& entry)
        {
            SaleFrame::pointer retSale;
            retSale = make_shared<SaleFrame>(entry);
            retSale->normalize();
            result.push_back(retSale);
        });

        return result;
    }

    EntryFrame::pointer SaleHelperImpl::storeLoad(LedgerKey const& key)
    {
        return loadSale(key.sale().saleID);
    }

    LedgerDelta *SaleHelperImpl::getLedgerDelta() {
        return mStorageHelper.getLedgerDelta();
    }

    Database &SaleHelperImpl::getDatabase() {
        return mStorageHelper.getDatabase();
    }

    SaleHelperImpl::SaleHelperImpl(StorageHelper &storageHelper)
            : mStorageHelper(storageHelper)
    {
        mSaleColumnSelector =
                "SELECT id, type, owner_id, base_asset, default_quote_asset, start_time, "
                "end_time, soft_cap, hard_cap, details, base_balance, version, lastmodified, current_cap_in_base, hard_cap_in_base, sale_type FROM sale";
    }


}
