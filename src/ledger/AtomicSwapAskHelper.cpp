#include "AtomicSwapAskHelper.h"
#include "AtomicSwapAskQuoteAssetHelper.h"
#include "LedgerDelta.h"
#include "xdrpp/printer.h"

using namespace soci;
using namespace std;

namespace stellar
{
using xdr::operator<;

static const char* atomicSwapAskColumnSelector = "SELECT id, owner_id, "
                                                 "base_asset_code, "
                                                 "base_balance_id, base_amount, "
                                                 "locked_amount, is_cancelled, "
                                                 "details, created_at, "
                                                 "lastmodified, version "
                                                 "FROM atomic_swap_ask";

void
AtomicSwapAskHelper::dropAll(Database &db)
{
    db.getSession() << "DROP TABLE IF EXISTS atomic_swap_ask";
    db.getSession() << "CREATE TABLE atomic_swap_ask"
                       "("
                       "id              BIGINT          NOT NULL,"
                       "owner_id        VARCHAR(56)     NOT NULL,"
                       "base_asset_code VARCHAR(16)     NOT NULL,"
                       "base_balance_id VARCHAR(56)     NOT NULL,"
                       "base_amount     NUMERIC(20,0)   NOT NULL CHECK (base_amount >= 0),"
                       "locked_amount   NUMERIC(20,0)   NOT NULL CHECK (locked_amount >= 0),"
                       "is_cancelled    BOOLEAN         NOT NULL,"
                       "details         TEXT            NOT NULL,"
                       "created_at      BIGINT          NOT NULL,"
                       "lastmodified    INT             NOT NULL,"
                       "version         INT             NOT NULL,"
                       "PRIMARY KEY (id)"
                       ");";

    AtomicSwapAskQuoteAssetHelper::dropAll(db);
}

void
AtomicSwapAskHelper::storeAdd(LedgerDelta &delta, Database &db, LedgerEntry const &entry)
{
    storeUpdateHelper(delta, db, true, entry);
}

void
AtomicSwapAskHelper::storeChange(LedgerDelta &delta, Database &db, LedgerEntry const &entry)
{
    storeUpdateHelper(delta, db, false, entry);
}

void
AtomicSwapAskHelper::storeDelete(LedgerDelta &delta, Database &db, LedgerKey const &key)
{
    flushCachedEntry(key, db);
    uint64_t id = key.atomicSwapAsk().id;

    auto timer = db.getDeleteTimer("atomic-swap-ask");
    auto prep = db.getPreparedStatement("DELETE FROM atomic_swap_ask WHERE id = :id");
    auto& st = prep.statement();
    st.exchange(use(id));
    st.define_and_bind();
    st.execute(true);
    AtomicSwapAskQuoteAssetHelper::deleteAllForAsk(db, id);
    delta.deleteEntry(key);
}

bool
AtomicSwapAskHelper::exists(Database &db, LedgerKey const &key)
{
    int exists = 0;
    auto timer = db.getSelectTimer("atomic-swap-ask-exists");
    auto prep = db.getPreparedStatement("SELECT EXISTS (SELECT NULL FROM atomic_swap_bid "
                                        "WHERE id = :id)");
    auto& st = prep.statement();
    uint64_t id = key.atomicSwapAsk().id;
    st.exchange(use(id, "id"));
    st.exchange(into(exists));
    st.define_and_bind();
    st.execute(true);
    return exists != 0;
}

LedgerKey
AtomicSwapAskHelper::getLedgerKey(LedgerEntry const &from)
{
    LedgerKey ledgerKey;
    ledgerKey.type(from.data.type());
    ledgerKey.atomicSwapAsk().id = from.data.atomicSwapAsk().id;
    return ledgerKey;
}

EntryFrame::pointer
AtomicSwapAskHelper::storeLoad(LedgerKey const &key, Database &db)
{
    return loadAtomicSwapAsk(key.atomicSwapAsk().id, db);
}

EntryFrame::pointer
AtomicSwapAskHelper::fromXDR(LedgerEntry const &from)
{
    return make_shared<AtomicSwapAskFrame>(from);
}

uint64_t
AtomicSwapAskHelper::countObjects(soci::session &sess)
{
    uint64_t count = 0;
    sess << "SELECT COUNT(*) FROM atomic_swap_ask;", into(count);
    return count;
}

AtomicSwapAskFrame::pointer
AtomicSwapAskHelper::loadAtomicSwapAsk(AccountID const &ownerID, uint64_t askID,
                                       Database &db, LedgerDelta *delta)
{
    AtomicSwapAskFrame::pointer result;

    string accIDStrKey = PubKeyUtils::toStrKey(ownerID);

    string sql = atomicSwapAskColumnSelector;
    sql += " WHERE id = :id AND owner_id = :oid";
    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();
    st.exchange(use(askID, "id"));
    st.exchange(use(accIDStrKey, "oid"));

    auto timer = db.getSelectTimer("atomic-swap-ask");
    loadAtomicSwapAsks(db, prep, [&result](LedgerEntry const& atomicSwapAsk)
    {
        result = make_shared<AtomicSwapAskFrame>(atomicSwapAsk);
    });

    if ((delta != nullptr) && (result))
    {
        delta->recordEntry(*result);
    }

    return result;
}

AtomicSwapAskFrame::pointer
AtomicSwapAskHelper::loadAtomicSwapAsk(uint64_t askID, Database &db,
                                       LedgerDelta *delta)
{
    string sql = atomicSwapAskColumnSelector;
    sql += " WHERE id = :id";
    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();
    st.exchange(use(askID, "id"));

    auto timer = db.getSelectTimer("atomic-swap-ask");

    AtomicSwapAskFrame::pointer retAsk;
    loadAtomicSwapAsks(db, prep, [&retAsk](LedgerEntry const& atomicSwapAsk)
    {
        retAsk = make_shared<AtomicSwapAskFrame>(atomicSwapAsk);
    });

    if ((delta != nullptr) && (retAsk))
    {
        delta->recordEntry(*retAsk);
    }

    return retAsk;
}

std::unordered_map<AccountID, std::vector<AtomicSwapAskFrame::pointer>>
AtomicSwapAskHelper::loadAllAtomicSwapAsks(Database &db)
{
    std::unordered_map<AccountID, std::vector<AtomicSwapAskFrame::pointer>> result;
    string sql = atomicSwapAskColumnSelector;
    sql += " ORDER BY owner_id";
    auto prep = db.getPreparedStatement(sql);

    auto timer = db.getSelectTimer("atomic-swap-ask");
    loadAtomicSwapAsks(db, prep, [&result](LedgerEntry const& entry)
    {
        auto& thisUsersAsks = result[entry.data.atomicSwapAsk().ownerID];
        thisUsersAsks.emplace_back(make_shared<AtomicSwapAskFrame>(entry));
    });

    return result;
}

void
AtomicSwapAskHelper::storeUpdateHelper(LedgerDelta &delta, Database &db, bool insert,
                                       LedgerEntry const &entry)
{
    auto askFrame = make_shared<AtomicSwapAskFrame>(entry);
    auto askEntry = askFrame->getAtomicSwapAsk();

    askFrame->touch(delta);

    if (!askFrame->isValid())
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER)
                << "Unexpected state - atomic swap ask is invalid: "
                << xdr::xdr_to_string(askFrame->getAtomicSwapAsk());
        throw std::runtime_error("Unexpected state - atomic swap ask is invalid");
    }

    string sql;

    if (insert)
    {
        sql = "INSERT INTO atomic_swap_ask (id, owner_id, "
              "base_asset_code, base_balance_id, base_amount, locked_amount, "
              "is_cancelled, details, created_at, lastmodified, version) "
              "VALUES "
              "(:id, :oid, :bac, :bbi, :ba, :la, :ic, :d, :ca, :lm, :v)";
    }
    else
    {
        sql = "UPDATE atomic_swap_ask "
              "SET base_asset_code = :bac, "
              "base_balance_id = :bbi, base_amount = :ba, locked_amount = :la, "
              "is_cancelled = :ic, details = :d, created_at = :ca, lastmodified = :lm, "
              "version = :v "
              "WHERE id = :id";
    }

    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();

    auto version = static_cast<int32_t>(askEntry.ext.v());
    auto ownerID = PubKeyUtils::toStrKey(askEntry.ownerID);

    if (insert)
    {
        st.exchange(use(ownerID, "oid"));
    }
    st.exchange(use(askEntry.id, "id"));
    st.exchange(use(askEntry.baseAsset, "bac"));
    auto baseBalanceID = BalanceKeyUtils::toStrKey(askEntry.baseBalance);
    st.exchange(use(baseBalanceID, "bbi"));
    st.exchange(use(askEntry.amount, "ba"));
    st.exchange(use(askEntry.lockedAmount, "la"));
    int isCancelled = askEntry.isCancelled ? 1 : 0;
    st.exchange(use(isCancelled, "ic"));
    st.exchange(use(askEntry.details, "d"));
    st.exchange(use(askEntry.createdAt, "ca"));
    st.exchange(use(askFrame->mEntry.lastModifiedLedgerSeq, "lm"));
    st.exchange(use(version, "v"));
    st.define_and_bind();

    auto timer = insert
                 ? db.getInsertTimer("atomic-swap-ask")
                 : db.getUpdateTimer("atomic-swap-ask");

    st.execute(true);

    if (st.get_affected_rows() != 1)
    {
        throw runtime_error("could not update SQl");
    }

    AtomicSwapAskQuoteAssetHelper::storeUpdate(db, askEntry.id,
            askEntry.quoteAssets, insert);

    if (insert)
    {
        delta.addEntry(*askFrame);
    }
    else
    {
        delta.modEntry(*askFrame);
    }
}

void
AtomicSwapAskHelper::loadAtomicSwapAsks(Database& db, StatementContext &prep,
                                        std::function<void(LedgerEntry const &)> processor)
{
    int32_t version = 0;
    int isCancelled = 0;

    LedgerEntry le;
    le.data.type(LedgerEntryType::ATOMIC_SWAP_ASK);
    AtomicSwapAskEntry& be = le.data.atomicSwapAsk();

    statement& st = prep.statement();
    st.exchange(into(be.id));
    st.exchange(into(be.ownerID));
    st.exchange(into(be.baseAsset));
    st.exchange(into(be.baseBalance));
    st.exchange(into(be.amount));
    st.exchange(into(be.lockedAmount));
    st.exchange(into(isCancelled));
    st.exchange(into(be.details));
    st.exchange(into(be.createdAt));
    st.exchange(into(le.lastModifiedLedgerSeq));
    st.exchange(into(version));
    st.define_and_bind();
    st.execute(true);
    while (st.got_data())
    {
        be.isCancelled = isCancelled > 0;
        be.ext.v(static_cast<LedgerVersion>(version));
        be.quoteAssets = AtomicSwapAskQuoteAssetHelper::loadQuoteAssets(db, be.id);
        if (!AtomicSwapAskFrame::isValid(be))
        {
            CLOG(ERROR, Logging::ENTRY_LOGGER)
                    << "Unexpected state - atomic swap ask is invalid"
                    << xdr::xdr_to_string(be);
            throw runtime_error("Unexpected state - atomic swap ask is invalid");
        }

        processor(le);
        st.fetch();
    }
}
}