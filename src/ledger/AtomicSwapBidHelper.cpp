#include "AtomicSwapBidHelper.h"
#include "AtomicSwapBidQuoteAssetHelper.h"
#include "LedgerDelta.h"
#include "xdrpp/printer.h"

using namespace soci;
using namespace std;

namespace stellar
{
using xdr::operator<;

static const char* atomicSwapBidColumnSelector = "SELECT bid_id, owner_id, "
                                                 "base_asset_code, "
                                                 "base_balance_id, base_amount, "
                                                 "fee, percent_fee, details, "
                                                 "created_at, "
                                                 "lastmodified, version "
                                                 "FROM atomic_swap_bid";

void
AtomicSwapBidHelper::dropAll(Database &db)
{
    db.getSession() << "DROP TABLE IF EXISTS atomic_swap_bid";
    db.getSession() << "CREATE TABLE atomic_swap_bid"
                       "("
                       "bid_id              BIGINT      NOT NULL CHECK (bid_id >= 0),"
                       "owner_id            VARCHAR(56) NOT NULL,"
                       "base_asset_code     VARCHAR(16) NOT NULL,"
                       "base_balance_id     VARCHAR(56) NOT NULL,"
                       "base_amount         BIGINT      NOT NULL CHECK (base_amount > 0),"
                       "fee                 BIGINT      NOT NULL CHECK (fee >= 0),"
                       "percent_fee         BIGINT      NOT NULL CHECK (percent_fee >= 0),"
                       "details             TEXT        NOT NULL,"
                       "created_at          BIGINT      NOT NULL,"
                       "lastmodified        INT         NOT NULL,"
                       "version             INT         NOT NULL DEFAULT 0,"
                       "PRIMARY KEY (bid_id)"
                       ");";

    ASwapBidQuoteAssetHelper::dropAll(db);
}

void
AtomicSwapBidHelper::storeAdd(LedgerDelta &delta, Database &db, LedgerEntry const &entry)
{
    storeUpdateHelper(delta, db, true, entry);
}

void
AtomicSwapBidHelper::storeChange(LedgerDelta &delta, Database &db, LedgerEntry const &entry)
{
    storeUpdateHelper(delta, db, false, entry);
}

void
AtomicSwapBidHelper::storeDelete(LedgerDelta &delta, Database &db, LedgerKey const &key)
{
    flushCachedEntry(key, db);
    auto timer = db.getDeleteTimer("atomic-swap-bid");
    auto prep = db.getPreparedStatement("DELETE FROM atomic_swap_bid WHERE bid_id = :id");
    auto& st = prep.statement();
    st.exchange(use(key.atomicSwapBid().bidID));
    st.define_and_bind();
    st.execute(true);
    ASwapBidQuoteAssetHelper::deleteAllForBid(db, key.atomicSwapBid().bidID);
    delta.deleteEntry(key);
}

bool
AtomicSwapBidHelper::exists(Database &db, LedgerKey const &key)
{
    string accIDStrKey = PubKeyUtils::toStrKey(key.atomicSwapBid().ownerID);
    int exists = 0;
    auto timer = db.getSelectTimer("atomic-swap-bid-exists");
    auto prep = db.getPreparedStatement("SELECT EXISTS (SELECT NULL FROM atomic_swap_bid "
                                        "WHERE bid_id = :id AND owner_id = :oid)");
    auto& st = prep.statement();
    st.exchange(use(key.atomicSwapBid().bidID, "id"));
    st.exchange(use(accIDStrKey, "oid"));
    st.exchange(into(exists));
    st.define_and_bind();
    st.execute(true);
    return exists != 0;
}

LedgerKey
AtomicSwapBidHelper::getLedgerKey(LedgerEntry const &from)
{
    LedgerKey ledgerKey;
    ledgerKey.type(from.data.type());
    ledgerKey.atomicSwapBid().bidID = from.data.atomicSwapBid().bidID;
    ledgerKey.atomicSwapBid().ownerID = from.data.atomicSwapBid().ownerID;
    return ledgerKey;
}

EntryFrame::pointer
AtomicSwapBidHelper::storeLoad(LedgerKey const &key, Database &db)
{
    return loadAtomicSwapBid(key.atomicSwapBid().ownerID, key.offer().offerID, db);
}

EntryFrame::pointer
AtomicSwapBidHelper::fromXDR(LedgerEntry const &from)
{
    return make_shared<AtomicSwapBidFrame>(from);
}

uint64_t
AtomicSwapBidHelper::countObjects(soci::session &sess)
{
    uint64_t count = 0;
    sess << "SELECT COUNT(*) FROM atomic_swap_bid;", into(count);
    return count;
}

AtomicSwapBidFrame::pointer
AtomicSwapBidHelper::loadAtomicSwapBid(AccountID const &accountID, uint64_t bidID,
                                       Database &db, LedgerDelta *delta)
{
    AtomicSwapBidFrame::pointer retBid;

    string accIDStrKey = PubKeyUtils::toStrKey(accountID);

    string sql = atomicSwapBidColumnSelector;
    sql += " WHERE bid_id = :id AND owner_id = :oid";
    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();
    st.exchange(use(bidID, "id"));
    st.exchange(use(accIDStrKey, "oid"));

    auto timer = db.getSelectTimer("atomic-swap-bid");
    loadAtomicSwapBids(db, prep, [&retBid](LedgerEntry const& atomicSwapBid) {
        retBid = make_shared<AtomicSwapBidFrame>(atomicSwapBid);
    });

    if (delta != nullptr && retBid != nullptr)
    {
        delta->recordEntry(*retBid);
    }

    return retBid;
}

AtomicSwapBidFrame::pointer
AtomicSwapBidHelper::loadAtomicSwapBid(uint64_t bidID, Database &db,
                                       LedgerDelta *delta)
{
    string sql = atomicSwapBidColumnSelector;
    sql += " WHERE bid_id = :id";
    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();
    st.exchange(use(bidID, "id"));

    auto timer = db.getSelectTimer("atomic-swap-bid");

    AtomicSwapBidFrame::pointer retBid;
    loadAtomicSwapBids(db, prep, [&retBid](LedgerEntry const& atomicSwapBid)
    {
        retBid = make_shared<AtomicSwapBidFrame>(atomicSwapBid);
    });

    if (delta != nullptr && retBid != nullptr)
    {
        delta->recordEntry(*retBid);
    }

    return retBid;
}

std::unordered_map<AccountID, std::vector<AtomicSwapBidFrame::pointer>>
AtomicSwapBidHelper::loadAllAtomicSwapBids(Database &db)
{
    std::unordered_map<AccountID, std::vector<AtomicSwapBidFrame::pointer>> retBids;
    string sql = atomicSwapBidColumnSelector;
    sql += " ORDER BY owner_id";
    auto prep = db.getPreparedStatement(sql);

    auto timer = db.getSelectTimer("atomic-swap-bid");
    loadAtomicSwapBids(db, prep, [&retBids](LedgerEntry const& entry) {
        auto& thisUsersBids = retBids[entry.data.atomicSwapBid().ownerID];
        thisUsersBids.emplace_back(make_shared<AtomicSwapBidFrame>(entry));
    });
    return retBids;
}

void
AtomicSwapBidHelper::storeUpdateHelper(LedgerDelta &delta, Database &db, bool insert,
                                       LedgerEntry const &entry)
{
    auto bidFrame = make_shared<AtomicSwapBidFrame>(entry);
    auto bidEntry = bidFrame->getAtomicSwapBid();

    bidFrame->touch(delta);

    if (!bidFrame->isValid())
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER)
                << "Unexpected state - atomic swap bid is invalid: "
                << xdr::xdr_to_string(bidFrame->getAtomicSwapBid());
        throw std::runtime_error("Unexpected state - atomic swap bid is invalid");
    }

    string sql;

    if (insert)
    {
        sql = "INSERT INTO atomic_swap_bid (bid_id, owner_id, "
              "base_asset_code, base_balance_id, base_amount, fee, percent_fee, "
              "details, created_at, lastmodified, version) "
              "VALUES "
              "(:id, :oid, :bac, :bbi, :ba, :f, :pf, :d, :ca, :lm, :v)";
    }
    else
    {
        sql = "UPDATE atomic_swap_bid "
              "SET base_asset_code = :bac, "
              "base_balance_id = :bbi, base_amount = :ba, "
              "fee = :f, percent_fee = :pf, details = :d, "
              "created_at = :ca, lastmodified = :lm, version = :v "
              "WHERE bid_id = :id";
    }

    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();

    auto bidVersion = static_cast<int32_t>(bidEntry.ext.v());
    auto ownerID = PubKeyUtils::toStrKey(bidEntry.ownerID);

    if (insert)
    {
        st.exchange(use(ownerID, "oid"));
    }
    st.exchange(use(bidEntry.bidID, "id"));
    st.exchange(use(bidEntry.baseAsset, "bac"));
    auto baseBalanceID = BalanceKeyUtils::toStrKey(bidEntry.baseBalance);
    st.exchange(use(baseBalanceID, "bbi"));
    st.exchange(use(bidEntry.amount, "ba"));
    st.exchange(use(bidEntry.fee, "f"));
    st.exchange(use(bidEntry.percentFee, "pf"));
    st.exchange(use(bidEntry.details, "d"));
    st.exchange(use(bidEntry.createdAt, "ca"));
    st.exchange(use(bidFrame->mEntry.lastModifiedLedgerSeq, "lm"));
    st.exchange(use(bidVersion, "v"));
    st.define_and_bind();

    auto timer = insert ? db.getInsertTimer("atomic-swap-bid") : db.getUpdateTimer("atomic-swap-bid");
    st.execute(true);

    if (st.get_affected_rows() != 1)
    {
        throw runtime_error("could not update SQl");
    }

    ASwapBidQuoteAssetHelper::storeUpdate(db, bidEntry.bidID, bidEntry.quoteAssets,
                                          insert);

    if (insert)
    {
        delta.addEntry(*bidFrame);
    }
    else
    {
        delta.modEntry(*bidFrame);
    }
}

void
AtomicSwapBidHelper::loadAtomicSwapBids(Database& db, StatementContext &prep,
                                        std::function<void(LedgerEntry const &)> atomicSwapBidProcessor)
{
    int32_t bidVersion = 0;

    LedgerEntry le;
    le.data.type(LedgerEntryType::ATOMIC_SWAP_BID);
    AtomicSwapBidEntry& be = le.data.atomicSwapBid();

    statement& st = prep.statement();
    st.exchange(into(be.bidID));
    st.exchange(into(be.ownerID));
    st.exchange(into(be.baseAsset));
    st.exchange(into(be.baseBalance));
    st.exchange(into(be.amount));
    st.exchange(into(be.fee));
    st.exchange(into(be.percentFee));
    st.exchange(into(be.details));
    st.exchange(into(be.createdAt));
    st.exchange(into(le.lastModifiedLedgerSeq));
    st.exchange(into(bidVersion));
    st.define_and_bind();
    st.execute(true);
    while (st.got_data())
    {
        be.ext.v(static_cast<LedgerVersion>(bidVersion));
        be.quoteAssets = ASwapBidQuoteAssetHelper::loadQuoteAssets(db, be.bidID);
        if (!AtomicSwapBidFrame::isValid(be))
        {
            CLOG(ERROR, Logging::ENTRY_LOGGER)
                    << "Unexpected state - atomic swap bid is invalid"
                    << xdr::xdr_to_string(be);
            throw runtime_error("Unexpected state - atomic swap bid is invalid");
        }

        atomicSwapBidProcessor(le);
        st.fetch();
    }
}

}