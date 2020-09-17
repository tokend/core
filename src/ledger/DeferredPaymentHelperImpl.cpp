#include "DeferredPaymentHelperImpl.h"
#include "LedgerDelta.h"
#include "StorageHelper.h"
#include "database/Database.h"
#include "util/basen.h"
#include "xdrpp/marshal.h"

using namespace soci;

namespace stellar
{

using xdr::operator<;

DeferredPaymentHelperImpl::DeferredPaymentHelperImpl(
    StorageHelper& storageHelper)
    : mStorageHelper(storageHelper)
{
    mDeferredPaymentColumnSelector =
        "select id, amount, fee_data, source, "
        "source_balance, destination, "
        "version, lastmodified from deferred_payments ";
}

/*
 * //: ID of the deferred payment entry
    uint64 id;

    uint64 amount;
    PaymentFeeData feeData;

    //: Creator of the entry
    AccountID source;
    BalanceID sourceBalance;

    AccountID destination;

    longstring reference;

    //: Reserved for future extension
    EmptyExt ext;
 * */

void
DeferredPaymentHelperImpl::dropAll()
{
    Database& db = getDatabase();

    db.getSession() << "DROP TABLE IF EXISTS deferred_payments";
    db.getSession() << "CREATE TABLE deferred_payments"
                       "("
                       "id              BIGINT NOT NULL PRIMARY KEY,"
                       "amount          NUMERIC(20, 0) NOT NULL,"
                       "source          VARCHAR(56) NOT NULL,"
                       "source_balance  VARCHAR(56) NOT NULL,"
                       "destination     VARCHAR(56) NOT NULL,"
                       "fee_data        TEXT NOT NULL,"
                       "version         INT    NOT NULL,"
                       "lastmodified    INT    NOT NULL"
                       ");";
}

void
DeferredPaymentHelperImpl::storeUpdate(LedgerEntry const& entry, bool insert)
{
    auto deferredPaymentFrame = std::make_shared<DeferredPaymentFrame>(entry);
    auto deferredPaymentEntry = deferredPaymentFrame->getDeferredPayment();

    deferredPaymentFrame->touch(mStorageHelper.mustGetLedgerDelta());
    LedgerKey const& key = deferredPaymentFrame->getKey();
    flushCachedEntry(key);

    auto version = static_cast<int32_t>(deferredPaymentEntry.ext.v());

    std::string sql;
    if (insert)
    {
        sql = "INSERT INTO deferred_payments (id, amount, source, "
              "source_balance, destination, fee_data, version, "
              "lastmodified) "
              "VALUES (:id, :am, :src, :srcb, :dst, :fd, :v, :lm)";
    }
    else
    {
        sql = "UPDATE deferred_payments SET amount = :am, source = :src, "
              "source_balance = :srcb, "
              "destination = :dst, fee_data = :fd, version = "
              ":v, "
              "lastmodified = :lm "
              " WHERE id = :id";
    }

    Database& db = getDatabase();
    auto prep = db.getPreparedStatement(sql);
    auto src = PubKeyUtils::toStrKey(deferredPaymentEntry.source);
    auto dst = PubKeyUtils::toStrKey(deferredPaymentEntry.destination);
    auto srcBalance =
        BalanceKeyUtils::toStrKey(deferredPaymentEntry.sourceBalance);
    auto feeDataBytes = xdr::xdr_to_opaque(deferredPaymentEntry.feeData);
    auto feeData = bn::encode_b64(feeDataBytes);

    statement& st = prep.statement();
    st.exchange(use(deferredPaymentEntry.id, "id"));
    st.exchange(use(deferredPaymentEntry.amount, "am"));
    st.exchange(use(src, "src"));
    st.exchange(use(srcBalance, "srcb"));
    st.exchange(use(dst, "dst"));
    st.exchange(use(feeData, "fd"));
    st.exchange(use(version, "v"));
    st.exchange(use(deferredPaymentFrame->mEntry.lastModifiedLedgerSeq, "lm"));

    st.define_and_bind();

    auto timer = insert ? db.getInsertTimer("deferredPayment")
                        : db.getUpdateTimer("deferredPayment");

    st.execute(true);

    if (st.get_affected_rows() != 1)
    {
        throw std::runtime_error("Could not update deferred payment in SQL");
    }
    if (insert)
    {
        mStorageHelper.mustGetLedgerDelta().addEntry(*deferredPaymentFrame);
    }
    else
    {
        mStorageHelper.mustGetLedgerDelta().modEntry(*deferredPaymentFrame);
    }
}

void
DeferredPaymentHelperImpl::storeAdd(LedgerEntry const& entry)
{
    storeUpdate(entry, true);
}

void
DeferredPaymentHelperImpl::storeChange(LedgerEntry const& entry)
{
    storeUpdate(entry, false);
}

void
DeferredPaymentHelperImpl::storeDelete(LedgerKey const& key)
{
    flushCachedEntry(key);
    auto id = key.deferredPayment().id;

    Database& db = getDatabase();
    auto timer = db.getDeleteTimer("deferredPayment");
    auto prep =
        db.getPreparedStatement("DELETE FROM deferred_payments WHERE id = :id");
    auto& st = prep.statement();
    st.exchange(use(id, "id"));
    st.define_and_bind();
    st.execute(true);

    mStorageHelper.mustGetLedgerDelta().deleteEntry(key);
}

bool
DeferredPaymentHelperImpl::exists(LedgerKey const& key)
{
    if (cachedEntryExists(key) && (getCachedEntry(key) != nullptr))
    {
        return true;
    }

    int exists = 0;

    Database& db = getDatabase();
    auto timer = db.getSelectTimer("deferredPayment");
    auto prep = db.getPreparedStatement(
        "SELECT EXISTS "
        "(SELECT NULL FROM deferred_payments WHERE id = :id)");
    auto& st = prep.statement();
    auto id = key.deferredPayment().id;
    st.exchange(use(id, "id"));
    st.exchange(into(exists));
    st.define_and_bind();
    st.execute(true);

    return exists != 0;
}

LedgerKey
DeferredPaymentHelperImpl::getLedgerKey(LedgerEntry const& entry)
{
    auto deferredPaymentFrame = std::make_shared<DeferredPaymentFrame>(entry);
    return deferredPaymentFrame->getKey();
}

EntryFrame::pointer
DeferredPaymentHelperImpl::fromXDR(LedgerEntry const& entry)
{
    return std::make_shared<DeferredPaymentFrame>(entry);
}

uint64_t
DeferredPaymentHelperImpl::countObjects()
{
    session& sess = getDatabase().getSession();
    uint64_t count = 0;
    sess << "SELECT COUNT(*) FROM deferred_payments;", into(count);

    return count;
}

EntryFrame::pointer
DeferredPaymentHelperImpl::storeLoad(LedgerKey const& key)
{
    return loadDeferredPayment(key.deferredPayment().id);
}

DeferredPaymentFrame::pointer
DeferredPaymentHelperImpl::loadDeferredPayment(uint64_t const id)
{
    LedgerKey key(LedgerEntryType::DEFERRED_PAYMENT);
    key.deferredPayment().id = id;

    if (cachedEntryExists(key))
    {
        auto p = getCachedEntry(key);
        if (!p)
        {
            return nullptr;
        }

        auto result = std::make_shared<DeferredPaymentFrame>(*p);
        if (getLedgerDelta() != nullptr)
        {
            mStorageHelper.mustGetLedgerDelta().recordEntry(*result);
        }
        return result;
    }

    std::string sql = mDeferredPaymentColumnSelector;
    sql += " where id = :id";

    Database& db = getDatabase();
    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();

    st.exchange(use(id, "id"));
    DeferredPaymentFrame::pointer result;
    load(prep, [&result](LedgerEntry const& entry) {
        result = std::make_shared<DeferredPaymentFrame>(entry);
    });

    if (!result)
    {
        putCachedEntry(key, nullptr);
        return nullptr;
    }

    if (getLedgerDelta() != nullptr)
    {
        mStorageHelper.mustGetLedgerDelta().recordEntry(*result);
    }

    auto pEntry = std::make_shared<LedgerEntry>(result->mEntry);
    putCachedEntry(key, pEntry);

    return result;
}

void
DeferredPaymentHelperImpl::load(
    StatementContext& prep, std::function<void(LedgerEntry const&)> processor)
{
    try
    {
        LedgerEntry le;
        le.data.type(LedgerEntryType::DEFERRED_PAYMENT);
        auto& deferredPaymentEntry = le.data.deferredPayment();

        int32_t version;
        std::string rawFeeData, rawSrcBalance, rawSrc, rawDst;
        auto& st = prep.statement();
        st.exchange(into(deferredPaymentEntry.id));
        st.exchange(into(deferredPaymentEntry.amount));
        st.exchange(into(rawFeeData));
        st.exchange(into(rawSrc));
        st.exchange(into(rawSrcBalance));
        st.exchange(into(rawDst));
        st.exchange(into(version));
        st.exchange(into(le.lastModifiedLedgerSeq));
        st.define_and_bind();
        st.execute(true);

        while (st.got_data())
        {
            deferredPaymentEntry.ext.v(static_cast<LedgerVersion>(version));

            // unmarshal body
            std::vector<uint8_t> decoded;
            bn::decode_b64(rawFeeData, decoded);
            xdr::xdr_get unmarshaler(&decoded.front(), &decoded.back() + 1);
            xdr::xdr_argpack_archive(unmarshaler, deferredPaymentEntry.feeData);
            unmarshaler.done();

            deferredPaymentEntry.sourceBalance =
                BalanceKeyUtils::fromStrKey(rawSrcBalance);
            deferredPaymentEntry.source = PubKeyUtils::fromStrKey(rawSrc);
            deferredPaymentEntry.destination = PubKeyUtils::fromStrKey(rawDst);

            processor(le);
            st.fetch();
        }
    }
    catch (std::exception& e)
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER) << e.what();
        std::throw_with_nested(
            std::runtime_error("Failed to load deferred payment"));
    }
}

Database&
DeferredPaymentHelperImpl::getDatabase()
{
    return mStorageHelper.getDatabase();
}

LedgerDelta*
DeferredPaymentHelperImpl::getLedgerDelta()
{
    return mStorageHelper.getLedgerDelta();
}
}