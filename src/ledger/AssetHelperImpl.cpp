#include "AssetHelperImpl.h"
#include "database/Database.h"
#include "ledger/LedgerDelta.h"
#include "ledger/StorageHelper.h"
#include "ledger/LedgerManager.h"
#include <xdrpp/marshal.h>

using namespace soci;
using namespace std;

namespace stellar
{

using xdr::operator<;

AssetHelperImpl::AssetHelperImpl(StorageHelper& storageHelper)
    : mStorageHelper(storageHelper)
{
    mAssetColumnSelector =
        "SELECT code, owner, preissued_asset_signer, "
        "details, max_issuance_amount, "
        "available_for_issueance, issued, pending_issuance, "
        "policies, type, trailing_digits, lastmodified, version "
        "FROM asset ";
}

void
AssetHelperImpl::dropAll()
{
    Database& db = getDatabase();

    db.getSession() << "DROP TABLE IF EXISTS asset;";
    db.getSession()
        << "CREATE TABLE asset"
           "("
           "code                    VARCHAR(16)   NOT NULL,"
           "owner                   VARCHAR(56)   NOT NULL,"
           "preissued_asset_signer  VARCHAR(56)   NOT NULL,"
           "details                 TEXT          NOT NULL,"
           "max_issuance_amount     NUMERIC(23,0) NOT NULL CHECK "
           "(max_issuance_amount >= 0),"
           "available_for_issueance NUMERIC(23,0) NOT NULL CHECK "
           "(available_for_issueance >= 0),"
           "issued                  NUMERIC(23,0) NOT NULL CHECK (issued >= 0),"
           "pending_issuance        NUMERIC(23,0) NOT NULL CHECK (issued >= 0),"
           "policies                INT           NOT NULL, "
           "type                    BIGINT        NOT NULL, "
           "lastmodified            INT           NOT NULL, "
           "version                 INT           NOT NULL, "
           "PRIMARY KEY (code)"
           ");";
}

void
AssetHelperImpl::addAssetState()
{
    getDatabase().getSession()
        << "ALTER TABLE asset ADD COLUMN state INT NOT NULL DEFAULT "
        << int(AssetFrame::State::ACTIVE) << ";";
}

void
AssetHelperImpl::addTrailingDigits()
{
    getDatabase().getSession()
        << "ALTER TABLE asset ADD COLUMN trailing_digits INT NOT NULL DEFAULT "
        << AssetFrame::kMaximumTrailingDigits << ";";
}

void
AssetHelperImpl::storeAdd(LedgerEntry const& entry)
{
    storeUpdateHelper(true, entry);
}

void
AssetHelperImpl::storeChange(LedgerEntry const& entry)
{
    storeUpdateHelper(false, entry);
}

void
AssetHelperImpl::storeDelete(LedgerKey const& key)
{
    flushCachedEntry(key);

    Database& db = getDatabase();
    auto timer = db.getDeleteTimer("delete-asset");
    auto prep = db.getPreparedStatement("DELETE FROM asset WHERE code=:code");
    auto& st = prep.statement();
    st.exchange(use(key.asset().code, "code"));
    st.define_and_bind();
    st.execute(true);

    if (mStorageHelper.getLedgerDelta())
    {
        mStorageHelper.getLedgerDelta()->deleteEntry(key);
    }
}

void
AssetHelperImpl::markDeleted(LedgerEntry const& entry, LedgerManager& lm)
{

    flushCachedEntry(getLedgerKey(entry));

    Database& db = getDatabase();

    auto assetFrame = make_shared<AssetFrame>(entry);
    std::string assetCode = assetFrame->getCode();

    auto timer = db.getDeleteTimer("delete-asset");
    auto prep = db.getPreparedStatement(
        "UPDATE asset SET state = :state WHERE code = :code");
    auto& st = prep.statement();

    if (lm.shouldUse(LedgerVersion::DELETE_REDEMPTION_ZERO_TASKS_CHECKING)) {
        st.exchange(use(assetCode, "code"));
    } else {
        st.exchange(use(assetFrame->getCode(), "code"));
    }
    
    int deletedState = int(AssetFrame::State::DELETED);
    st.exchange(use(deletedState, "state"));

    st.define_and_bind();
    st.execute(true);
}

bool
AssetHelperImpl::exists(LedgerKey const& key)
{
    return exists(key.asset().code);
}

bool
AssetHelperImpl::existActive(const AssetCode& code)
{
    int exists = 0;
    auto timer = getDatabase().getSelectTimer("asset-exists");
    std::string assetCode = code;
    auto prep = getDatabase().getPreparedStatement(
        "SELECT EXISTS (SELECT NULL FROM asset WHERE code=:code "
        "and state = :state)");
    auto& st = prep.statement();
    st.exchange(use(assetCode, "code"));
    int activeState = int(AssetFrame::State::ACTIVE);
    st.exchange(use(activeState, "state"));
    st.exchange(into(exists));
    st.define_and_bind();
    st.execute(true);

    return exists != 0;
}

bool
AssetHelperImpl::exists(const AssetCode& code)
{
    int exists = 0;
    auto timer = getDatabase().getSelectTimer("asset-exists");
    std::string assetCode = code;
    auto prep = getDatabase().getPreparedStatement(
        "SELECT EXISTS (SELECT NULL FROM asset WHERE code=:code)");
    auto& st = prep.statement();
    st.exchange(use(assetCode, "code"));
    st.exchange(into(exists));
    st.define_and_bind();
    st.execute(true);

    return exists != 0;
}

void
AssetHelperImpl::storeUpdateHelper(bool insert, LedgerEntry const& entry)
{
    Database& db = getDatabase();
    LedgerDelta* delta = mStorageHelper.getLedgerDelta();

    auto assetFrame = make_shared<AssetFrame>(entry);
    auto assetEntry = assetFrame->getAsset();

    if (delta)
    {
        assetFrame->touch(*delta);
    }
    flushCachedEntry(getLedgerKey(entry));

    assetFrame->ensureValid();

    auto owner = PubKeyUtils::toStrKey(assetEntry.owner);
    auto signer = PubKeyUtils::toStrKey(assetEntry.preissuedAssetSigner);
    auto version = static_cast<int32_t>(assetEntry.ext.v());

    string sql;

    if (insert)
    {
        sql = "INSERT INTO asset (code, owner, preissued_asset_signer, details,"
              "                   max_issuance_amount, available_for_issueance,"
              "                   issued, pending_issuance, policies, type, "
              "                   trailing_digits, lastmodified, version) "
              "VALUES (:code, :owner, :signer, :details, :max, :available, "
              "        :issued, :pending, :policies, :t, :td, :lm, :v)";
    }
    else
    {
        sql = "UPDATE asset SET owner = :owner, "
              "preissued_asset_signer = :signer, details = :details, "
              "max_issuance_amount = :max, "
              "available_for_issueance = :available, issued = :issued, "
              "pending_issuance = :pending, policies = :policies, type = :t, "
              "trailing_digits = :td, lastmodified = :lm, version = :v "
              "WHERE code = :code";
    }

    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();

    const uint32 trailingDigits = assetFrame->getTrailingDigitsCount();
    st.exchange(use(assetEntry.code, "code"));
    st.exchange(use(owner, "owner"));
    st.exchange(use(signer, "signer"));
    st.exchange(use(assetEntry.details, "details"));
    st.exchange(use(assetEntry.maxIssuanceAmount, "max"));
    st.exchange(use(assetEntry.availableForIssueance, "available"));
    st.exchange(use(assetEntry.issued, "issued"));
    st.exchange(use(assetEntry.pendingIssuance, "pending"));
    st.exchange(use(assetEntry.policies, "policies"));
    st.exchange(use(assetEntry.type, "t"));
    st.exchange(use(assetFrame->mEntry.lastModifiedLedgerSeq, "lm"));
    st.exchange(use(trailingDigits, "td"));
    st.exchange(use(version, "v"));
    st.define_and_bind();

    auto timer = insert ? db.getInsertTimer("insert-asset")
                        : db.getUpdateTimer("update-asset");

    st.execute(true);
    if (st.get_affected_rows() != 1)
    {
        throw runtime_error("could not update SQL");
    }

    if (delta)
    {
        if (insert)
        {
            delta->addEntry(*assetFrame);
        }
        else
        {
            delta->modEntry(*assetFrame);
        }
    }
}

LedgerKey
AssetHelperImpl::getLedgerKey(LedgerEntry const& from)
{
    LedgerKey ledgerKey;
    ledgerKey.type(from.data.type());
    ledgerKey.asset().code = from.data.asset().code;
    return ledgerKey;
}

EntryFrame::pointer
AssetHelperImpl::storeLoad(LedgerKey const& key)
{
    return loadAsset(key.asset().code);
}

EntryFrame::pointer
AssetHelperImpl::fromXDR(LedgerEntry const& from)
{
    return make_shared<AssetFrame>(from);
}

uint64_t
AssetHelperImpl::countObjects()
{
    uint64_t count = 0;
    getDatabase().getSession() << "SELECT COUNT(*) FROM asset;", into(count);
    return count;
}

AssetFrame::pointer
AssetHelperImpl::loadActiveAsset(AssetCode assetCode)
{
    LedgerKey key;
    key.type(LedgerEntryType::ASSET);
    key.asset().code = assetCode;
    if (cachedEntryExists(key))
    {
        auto asset = getCachedEntry(key);
        auto assetFrame =
            asset ? std::make_shared<AssetFrame>(*asset) : nullptr;
        if (asset && mStorageHelper.getLedgerDelta())
        {
            mStorageHelper.getLedgerDelta()->recordEntry(*assetFrame);
        }

        return assetFrame;
    }

    Database& db = getDatabase();

    string sql = mAssetColumnSelector;
    sql += " WHERE state = :state and code = :code";
    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();
    st.exchange(use(assetCode, "code"));
    int activeState = int(AssetFrame::State::ACTIVE);
    st.exchange(use(activeState, "state"));

    auto timer = db.getSelectTimer("load-asset");
    AssetFrame::pointer retAsset;
    loadAssets(prep, [&retAsset](LedgerEntry const& entry) {
        retAsset = make_shared<AssetFrame>(entry);
    });

    if (!retAsset)
    {
        putCachedEntry(key, nullptr);
        return nullptr;
    }

    if (mStorageHelper.getLedgerDelta())
    {
        mStorageHelper.getLedgerDelta()->recordEntry(*retAsset);
    }
    putCachedEntry(key, make_shared<LedgerEntry>(retAsset->mEntry));

    return retAsset;
}

AssetFrame::pointer
AssetHelperImpl::loadAsset(AssetCode assetCode)
{
    LedgerKey key;
    key.type(LedgerEntryType::ASSET);
    key.asset().code = assetCode;
    if (cachedEntryExists(key))
    {
        auto asset = getCachedEntry(key);
        auto assetFrame =
            asset ? std::make_shared<AssetFrame>(*asset) : nullptr;
        if (asset && mStorageHelper.getLedgerDelta())
        {
            mStorageHelper.getLedgerDelta()->recordEntry(*assetFrame);
        }

        return assetFrame;
    }

    Database& db = getDatabase();

    string sql = mAssetColumnSelector;
    sql += " WHERE state = :state and code = :code";
    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();
    st.exchange(use(assetCode, "code"));
    int activeState = int(AssetFrame::State::ACTIVE);
    st.exchange(use(activeState, "state"));

    auto timer = db.getSelectTimer("load-asset");
    AssetFrame::pointer retAsset;
    loadAssets(prep, [&retAsset](LedgerEntry const& entry) {
        retAsset = make_shared<AssetFrame>(entry);
    });

    if (!retAsset)
    {
        putCachedEntry(key, nullptr);
        return nullptr;
    }

    if (mStorageHelper.getLedgerDelta())
    {
        mStorageHelper.getLedgerDelta()->recordEntry(*retAsset);
    }
    putCachedEntry(key, make_shared<LedgerEntry>(retAsset->mEntry));

    return retAsset;
}

AssetFrame::pointer
AssetHelperImpl::mustLoadAsset(AssetCode assetCode)
{
    auto assetFrame = loadActiveAsset(assetCode);

    if (!assetFrame)
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER)
            << "Unexpected state, "
            << "expected asset to exists, asset code: " << assetCode;
        throw runtime_error("Unexpected state, expected asset to exists");
    }

    return assetFrame;
}

AssetFrame::pointer
AssetHelperImpl::loadAsset(AssetCode assetCode, AccountID owner)
{
    auto assetFrame = loadActiveAsset(assetCode);
    if (!assetFrame)
    {
        return nullptr;
    }

    if (assetFrame->getOwner() == owner)
    {
        return assetFrame;
    }

    return nullptr;
}

AssetFrame::pointer
AssetHelperImpl::loadStatsAsset()
{
    const uint32 statsAssetPolicy =
        static_cast<uint32>(AssetPolicy::STATS_QUOTE_ASSET);

    AssetFrame::pointer retAsset;
    std::string sql = mAssetColumnSelector;
    sql += " WHERE state = :state and policies & :sp = :sp";
    auto prep = getDatabase().getPreparedStatement(sql);
    auto& st = prep.statement();
    st.exchange(use(statsAssetPolicy, "sp"));
    int activeState = int(AssetFrame::State::ACTIVE);
    st.exchange(use(activeState, "state"));

    auto timer = getDatabase().getSelectTimer("asset");
    loadAssets(prep, [&retAsset](LedgerEntry const& asset) {
        retAsset = make_shared<AssetFrame>(asset);
    });
    return retAsset;
}

void
AssetHelperImpl::loadAssets(StatementContext& prep,
                            function<void(LedgerEntry const&)> assetProcessor)
{
    LedgerEntry le;
    le.data.type(LedgerEntryType::ASSET);
    AssetEntry& oe = le.data.asset();

    int32_t version = 0;
    uint32_t trailingDigits = 0;

    statement& st = prep.statement();
    st.exchange(into(oe.code));
    st.exchange(into(oe.owner));
    st.exchange(into(oe.preissuedAssetSigner));
    st.exchange(into(oe.details));
    st.exchange(into(oe.maxIssuanceAmount));
    st.exchange(into(oe.availableForIssueance));
    st.exchange(into(oe.issued));
    st.exchange(into(oe.pendingIssuance));
    st.exchange(into(oe.policies));
    st.exchange(into(oe.type));
    st.exchange(into(trailingDigits));
    st.exchange(into(le.lastModifiedLedgerSeq));
    st.exchange(into(version));
    st.define_and_bind();
    st.execute(true);

    while (st.got_data())
    {
        oe.ext.v(static_cast<LedgerVersion>(version));
        oe.trailingDigitsCount = trailingDigits;

        AssetFrame::ensureValid(oe);

        assetProcessor(le);
        st.fetch();
    }
}

bool
AssetHelperImpl::doesAmountFitAssetPrecision(const AssetCode& assetCode,
                                             uint64_t amount)
{
    const uint64_t precision = mustLoadAsset(assetCode)->getMinimumAmount();
    return amount % precision == 0;
}

std::vector<AssetFrame::pointer>
AssetHelperImpl::loadBaseAssets()
{
    std::string sql = mAssetColumnSelector;
    sql += " WHERE state = :state and "
           " policies & :bp = :bp "
           " ORDER BY code ";
    uint32 baseAssetPolicy = static_cast<uint32>(AssetPolicy::BASE_ASSET);
    auto prep = getDatabase().getPreparedStatement(sql);
    prep.statement().exchange(use(baseAssetPolicy, "bp"));
    int activeState = int(AssetFrame::State::ACTIVE);
    prep.statement().exchange(use(activeState, "state"));

    auto timer = getDatabase().getSelectTimer("asset");
    std::vector<AssetFrame::pointer> retAssets;
    loadAssets(prep, [&retAssets](LedgerEntry const& asset) {
        retAssets.push_back(make_shared<AssetFrame>(asset));
    });

    return retAssets;
}

Database&
AssetHelperImpl::getDatabase()
{
    return mStorageHelper.getDatabase();
}

LedgerDelta*
AssetHelperImpl::getLedgerDelta()
{
    return mStorageHelper.getLedgerDelta();
}

std::map<AssetCode, uint64_t>
AssetHelperImpl::loadIssuedForAssets()
{
    auto& db = getDatabase();
    uint64_t issued = 0;
    AssetCode assetCode;

    std::map<AssetCode, uint64_t> result;

    auto timer = db.getSelectTimer("issued-for-asset");
    auto prep = db.getPreparedStatement("SELECT code, issued FROM asset "
                                        " WHERE state = :state");
    auto& st = prep.statement();
    st.exchange(use(int(AssetFrame::State::ACTIVE)));
    st.exchange(into(assetCode));
    st.exchange(into(issued));
    st.define_and_bind();
    st.execute(true);
    while (st.got_data())
    {
        result[assetCode] = issued;
        st.fetch();
    }

    return result;
}

} // namespace stellar
