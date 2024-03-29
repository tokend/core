// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "AssetPairHelperImpl.h"
#include "LedgerDelta.h"
#include "crypto/Hex.h"
#include "crypto/SecretKey.h"
#include "database/Database.h"
#include "ledger/StorageHelperImpl.h"
#include "lib/util/format.h"
#include "util/basen.h"
#include "util/types.h"
#include <algorithm>
#include "ledger/AssetHelper.h"

using namespace soci;
using namespace std;

namespace stellar
{
using xdr::operator<;

static const char* assetPairColumnSelector =
        "SELECT base, quote, current_price, physical_price, "
        "physical_price_correction, max_price_step, policies, "
        "lastmodified, version "
        "FROM asset_pair";

void
AssetPairHelperImpl::dropAll()
{
    Database &db = getDatabase();
    db.getSession() << "DROP TABLE IF EXISTS asset_pair;";
    db.getSession() << "CREATE TABLE asset_pair"
                       "("
                       "base                      VARCHAR(16)       NOT NULL,"
                       "quote                     VARCHAR(16)       NOT NULL,"
                       "current_price             BIGINT            NOT NULL "
                       "CHECK(current_price >= 0), "
                       "physical_price            BIGINT            NOT NULL "
                       "CHECK(physical_price >= 0), "
                       "physical_price_correction BIGINT            NOT NULL "
                       "CHECK(physical_price_correction >= 0), "
                       "max_price_step            BIGINT            NOT NULL "
                       "CHECK(max_price_step >= 0), "
                       "policies                  INT               NOT NULL, "
                       "lastmodified              INT               NOT NULL, "
                       "version				   INT		"
                       "		 NOT NULL DEFAULT 0, "
                       "PRIMARY KEY (base, quote)"
                       ");";
}

void
AssetPairHelperImpl::storeUpdateHelper(bool insert, LedgerEntry const& entry)
{
    Database &db = getDatabase();
    LedgerDelta* delta = getLedgerDelta();
    auto assetPairFrame = make_shared<AssetPairFrame>(entry);
    auto assetPairEntry = assetPairFrame->getAssetPair();

    assetPairFrame->touch(*delta);

    bool isValid = assetPairFrame->isValid();
    if (!isValid)
    {
        throw std::runtime_error("Invalid asset pair");
    }

    auto key = assetPairFrame->getKey();
    flushCachedEntry(key);
    string sql;

    if (insert)
    {
        sql = "INSERT INTO asset_pair (base, quote, current_price, "
              "physical_price, physical_price_correction, "
              "max_price_step, policies, lastmodified, version) "
              "VALUES (:b, :q, :cp, :pp, :ppc, :mps, :p, :lm, :v)";
    }
    else
    {
        sql =
                "UPDATE asset_pair "
                "SET 	  current_price=:cp, physical_price=:pp, "
                "physical_price_correction=:ppc, max_price_step=:mps, policies=:p, "
                "       lastmodified=:lm, version=:v "
                "WHERE  base = :b AND quote=:q";
    }

    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();

    string base = assetPairFrame->getBaseAsset();
    string quote = assetPairFrame->getQuoteAsset();
    int32_t assetPairVersion =
            static_cast<int32_t>(assetPairFrame->getAssetPair().ext.v());

    st.exchange(use(base, "b"));
    st.exchange(use(quote, "q"));
    st.exchange(use(assetPairEntry.currentPrice, "cp"));
    st.exchange(use(assetPairEntry.physicalPrice, "pp"));
    st.exchange(use(assetPairEntry.physicalPriceCorrection, "ppc"));
    st.exchange(use(assetPairEntry.maxPriceStep, "mps"));
    st.exchange(use(assetPairEntry.policies, "p"));
    st.exchange(use(assetPairFrame->mEntry.lastModifiedLedgerSeq, "lm"));
    st.exchange(use(assetPairVersion, "v"));
    st.define_and_bind();

    auto timer = insert ? db.getInsertTimer("assetPair")
                        : db.getUpdateTimer("assetPair");
    st.execute(true);

    if (st.get_affected_rows() != 1)
    {
        throw std::runtime_error("could not update SQL");
    }

    if (insert)
    {
        delta->addEntry(*assetPairFrame);
    }
    else
    {
        delta->modEntry(*assetPairFrame);
    }
}

void
AssetPairHelperImpl::storeAdd(LedgerEntry const& entry)
{
    storeUpdateHelper(true, entry);
}

void
AssetPairHelperImpl::storeChange(LedgerEntry const& entry)
{
    storeUpdateHelper(false, entry);
}

void
AssetPairHelperImpl::storeDelete(LedgerKey const& key)
{
    Database &db = getDatabase();
    LedgerDelta* delta = getLedgerDelta();
    flushCachedEntry(key);
    auto timer = db.getDeleteTimer("AssetPair");
    auto prep = db.getPreparedStatement(
            "DELETE FROM asset_pair WHERE base=:base AND quote=:quote");
    auto& st = prep.statement();
    string base = key.assetPair().base;
    string quote = key.assetPair().quote;
    st.exchange(use(base));
    st.exchange(use(quote));
    st.define_and_bind();
    st.execute(true);
    delta->deleteEntry(key);
}

bool
AssetPairHelperImpl::exists(LedgerKey const& key)
{
    return exists(key.assetPair().base, key.assetPair().quote);
}

bool
AssetPairHelperImpl::exists(AssetCode base, AssetCode quote)
{
    Database &db = getDatabase();
    int exists = 0;
    auto timer = db.getSelectTimer("assetPair-exists");
    auto prep =
            db.getPreparedStatement("SELECT EXISTS (SELECT NULL FROM asset_pair "
                                    "WHERE base=:base AND quote=:quote)");
    auto& st = prep.statement();
    string baseCode = base;
    string quoteCode = quote;
    st.exchange(use(baseCode));
    st.exchange(use(quoteCode));
    st.exchange(into(exists));
    st.define_and_bind();
    st.execute(true);

    return exists != 0;
}

LedgerKey
AssetPairHelperImpl::getLedgerKey(LedgerEntry const& from)
{
    LedgerKey ledgerKey;
    ledgerKey.type(from.data.type());
    ledgerKey.assetPair().base = from.data.assetPair().base;
    ledgerKey.assetPair().quote = from.data.assetPair().quote;
    return ledgerKey;
}

EntryFrame::pointer
AssetPairHelperImpl::storeLoad(LedgerKey const& key)
{
    if (cachedEntryExists(key))
    {
        auto p = getCachedEntry(key);
        return p ? std::make_shared<AssetPairFrame>(*p) : nullptr;
    }

    Database &db = getDatabase();
    string baseCode = key.assetPair().base;
    string quoteCode = key.assetPair().quote;
    std::string sql = assetPairColumnSelector;
    sql += " WHERE base = :base AND quote = :quote";
    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();
    st.exchange(use(baseCode));
    st.exchange(use(quoteCode));

    auto timer = db.getSelectTimer("assetPair");
    AssetPairFrame::pointer retAssetPair;
    loadAssetPairs(prep, [&retAssetPair](LedgerEntry const& assetPair) {
        retAssetPair = make_shared<AssetPairFrame>(assetPair);
    });

    if (!retAssetPair)
    {
        putCachedEntry(key, nullptr);
        return nullptr;
    }
    auto pEntry = std::make_shared<LedgerEntry const>(retAssetPair->mEntry);
    putCachedEntry(key, pEntry);
    return retAssetPair;
}

EntryFrame::pointer
AssetPairHelperImpl::fromXDR(LedgerEntry const& from)
{
    return std::make_shared<AssetPairFrame>(from);
}

uint64_t
AssetPairHelperImpl::countObjects()
{
    uint64_t count = 0;
    Database &db = getDatabase();
    db.getSession() << "SELECT COUNT(*) FROM asset_pair;", into(count);
    return count;
}

AssetPairFrame::pointer
AssetPairHelperImpl::loadAssetPair(AssetCode base, AssetCode quote)
{
    Database &db = getDatabase();
    LedgerDelta* delta = getLedgerDelta();
    LedgerKey key;
    key.type(LedgerEntryType::ASSET_PAIR);
    key.assetPair().base = base;
    key.assetPair().quote = quote;

    if (cachedEntryExists(key))
    {
        auto p = getCachedEntry(key);
        auto result = p ? std::make_shared<AssetPairFrame>(*p) : nullptr;
        tryRecordEntry(result);
        return result;
    }

    string baseCode = base;
    string quoteCode = quote;
    std::string sql = assetPairColumnSelector;
    sql += " WHERE base = :base AND quote = :quote";
    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();
    st.exchange(use(baseCode));
    st.exchange(use(quoteCode));

    auto timer = db.getSelectTimer("assetPair");
    AssetPairFrame::pointer retAssetPair;
    loadAssetPairs(prep, [&retAssetPair](LedgerEntry const& assetPair) {
        retAssetPair = make_shared<AssetPairFrame>(assetPair);
    });

    if (!retAssetPair)
    {
        putCachedEntry(key, nullptr);
        return nullptr;
    }

    if (delta)
    {
        delta->recordEntry(*retAssetPair);
    }
    auto pEntry = std::make_shared<LedgerEntry const>(retAssetPair->mEntry);
    putCachedEntry(key, pEntry);
    return retAssetPair;
}

AssetPairFrame::pointer
AssetPairHelperImpl::tryLoadAssetPairForAssets(const AssetCode code1, const AssetCode code2)
{
    auto assetPair = loadAssetPair(code1, code2);
    if (!!assetPair)
    {
        return assetPair;
    }

    return loadAssetPair(code2, code1);
}

void
AssetPairHelperImpl::loadAssetPairs(
        StatementContext& prep,
        std::function<void(LedgerEntry const&)> assetPairProcessor)
{
    LedgerEntry le;
    le.data.type(LedgerEntryType::ASSET_PAIR);
    AssetPairEntry& oe = le.data.assetPair();
    string baseCode, quoteCode;
    int32_t assetPairVersion = 0;

    statement& st = prep.statement();
    st.exchange(into(baseCode));
    st.exchange(into(quoteCode));
    st.exchange(into(oe.currentPrice));
    st.exchange(into(oe.physicalPrice));
    st.exchange(into(oe.physicalPriceCorrection));
    st.exchange(into(oe.maxPriceStep));
    st.exchange(into(oe.policies));
    st.exchange(into(le.lastModifiedLedgerSeq));
    st.exchange(into(assetPairVersion));
    st.define_and_bind();
    st.execute(true);
    while (st.got_data())
    {
        oe.base = baseCode;
        oe.quote = quoteCode;
        oe.ext.v((LedgerVersion)assetPairVersion);

        bool isValid = AssetPairFrame::isValid(oe);
        if (!isValid)
        {
            throw std::runtime_error("Invalid asset pair");
        }

        assetPairProcessor(le);
        st.fetch();
    }
}

bool
AssetPairHelperImpl::existsForAsset(AssetCode code)
{
    Database &db = getDatabase();
    int exists = 0;
    auto timer = db.getSelectTimer("asset-pair-exists");
    auto prep =
            db.getPreparedStatement("SELECT EXISTS (SELECT NULL FROM asset_pair "
                                    "WHERE base=:code OR quote=:code)");
    auto& st = prep.statement();
    string assetCode = code;
    st.exchange(use(assetCode, "code"));
    st.exchange(into(exists));
    st.define_and_bind();
    st.execute(true);

    return exists != 0;
}

bool
AssetPairHelperImpl::convertAmount(const AssetPairFrame::pointer& assetPair,
                               const AssetCode& destCode, uint64_t amount,
                               const Rounding rounding, uint64_t& result)
{
    if (assetPair->getCurrentPrice() <= 0)
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER)
                << "Unexpected state. Current price is <= 0: " << destCode;
        return false;
    }

    if (destCode != assetPair->getBaseAsset() &&
        destCode != assetPair->getQuoteAsset())
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER)
                << "Unknown asset code: " << destCode;
        return false;
    }

    const int64_t currentPrice = assetPair->getCurrentPrice();
    Database &db = getDatabase();
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, nullptr));
    storageHelper->release();
    auto& assetHelper = storageHelper->getAssetHelper();
    const auto destAsset = assetHelper.mustLoadAsset(destCode);
    const uint64_t destAssetMinimumAmount = destAsset->getMinimumAmount();
    if (destCode == assetPair->getQuoteAsset())
    {
        return bigDivide(result, amount, currentPrice, ONE, rounding,
                         destAssetMinimumAmount);
    }

    return bigDivide(result, amount, ONE, currentPrice, rounding,
                     destAssetMinimumAmount);
}

AssetPairFrame::pointer
AssetPairHelperImpl::mustLoadAssetPair(AssetCode base, AssetCode quote)
{
    auto result = loadAssetPair(base, quote);
    if (!result)
    {
        CLOG(ERROR, "EntryFrame")
                << "Unexpected db state. Expected asset pair to exists. Base "
                << std::string(base) << " Quote " << std::string(quote);
        throw std::runtime_error(
                "Unexpected db state. Expected asset pair to exist");
    }
    return result;
}

    LedgerDelta *AssetPairHelperImpl::getLedgerDelta() {
        return mStorageHelper.getLedgerDelta();
    }

    Database &AssetPairHelperImpl::getDatabase() {
        return mStorageHelper.getDatabase();
    }

    AssetPairHelperImpl::AssetPairHelperImpl(StorageHelper &storageHelper)
            : mStorageHelper(storageHelper)
    {
    }

}