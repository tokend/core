#pragma once

#include "ledger/EntryHelperLegacy.h"
#include "ledger/LedgerManager.h"
#include "ledger/FeeFrame.h"
#include <functional>
#include <unordered_map>
#include "BalanceFrame.h"

namespace soci
{
class session;
}

namespace stellar
{
class StatementContext;

class BalanceHelperLegacy : public EntryHelperLegacy
{
public:

    static BalanceHelperLegacy *Instance() {
        static BalanceHelperLegacy singleton;
        return &singleton;
    }

    void dropAll(Database& db) override;
    void storeAdd(LedgerDelta& delta, Database& db, LedgerEntry const& entry) override;
    void storeChange(LedgerDelta& delta, Database& db, LedgerEntry const& entry) override;
    void storeDelete(LedgerDelta& delta, Database& db, LedgerKey const& key) override;
    bool exists(Database& db, LedgerKey const& key) override;
    LedgerKey getLedgerKey(LedgerEntry const& from) override;
    EntryFrame::pointer storeLoad(LedgerKey const& key, Database& db) override;
    EntryFrame::pointer fromXDR(LedgerEntry const& from) override;
    uint64_t countObjects(soci::session& sess) override;

    void loadBalances(AccountID const& accountID,
                      std::vector<BalanceFrame::pointer>& retBalances,
                      Database& db);

    BalanceFrame::pointer loadBalance(AccountID accountID, BalanceID balanceID,
                                      Database &db, LedgerDelta *delta = nullptr);

    BalanceFrame::pointer loadBalance(BalanceID balanceID,
                                      Database& db, LedgerDelta *delta = nullptr);

    BalanceFrame::pointer loadBalance(AccountID account, AssetCode asset, Database& db,
                                      LedgerDelta *delta = nullptr);

    BalanceFrame::pointer mustLoadBalance(BalanceID balanceID, Database& db, LedgerDelta* delta = nullptr)
    {
        auto result = loadBalance(balanceID, db, delta);
        if (!!result) {
            return result;
        }

        CLOG(ERROR, Logging::ENTRY_LOGGER) << "expected balance " << BalanceKeyUtils::toStrKey(balanceID) << " to exist";
        throw std::runtime_error("expected balance to exist");
    }

    BalanceFrame::pointer mustLoadBalance(AccountID accountID, AssetCode asset,
                                          Database& db, LedgerDelta* delta = nullptr)
    {
        auto result = loadBalance(accountID, asset, db, delta);
        if (!!result) {
            return result;
        }

        CLOG(ERROR, Logging::ENTRY_LOGGER) << "expected balance for account " << PubKeyUtils::toStrKey(accountID)
                                           << " to exist";
        throw std::runtime_error("expected balance for account to exist");
    }

    // load all Balances from the database (very slow)
    std::unordered_map<BalanceID, std::vector<BalanceFrame::pointer>>
    loadAllBalances(Database& db);

    std::unordered_map<std::string, BalanceFrame::pointer>
    loadBalances(AccountID const& accountID, Database& db);

    std::vector<BalanceFrame::pointer> loadBalances(AccountID account,
                                                    AssetCode asset, Database& db);

    std::vector<BalanceFrame::pointer>
    loadAssetHolders(AssetCode assetCode, AccountID ownerID,
                     uint64_t minTotalAmount, Database &db);

    std::vector<BalanceFrame::pointer> loadBalances(
            std::vector<AccountID> accountIDs,
            AssetCode assetCode, Database& db);

    bool exists(Database& db, BalanceID balanceID);

private:
    BalanceHelperLegacy() { ; }
    ~BalanceHelperLegacy() { ; }

    BalanceHelperLegacy(BalanceHelperLegacy const&) = delete;
    BalanceHelperLegacy& operator=(BalanceHelperLegacy const&) = delete;

    std::string obtainStrAccountIDs(std::vector<AccountID> accountIDs);

    static void loadBalances(StatementContext& prep,
                             std::function<void(BalanceFrame::pointer&)> balanceProcessor);

    void storeUpdateHelper(LedgerDelta& delta, Database& db, bool insert, LedgerEntry const& entry);
};
}