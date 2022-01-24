#pragma once

#include <ledger/EntryFrame.h>

namespace soci
{
class session;
}

namespace stellar
{
class StatementContext;

class LiquidityPoolFrame : public EntryFrame
{
public:
    typedef std::shared_ptr<LiquidityPoolFrame> pointer;

    LiquidityPoolFrame();
    explicit LiquidityPoolFrame(LedgerEntry const& from);

    LiquidityPoolFrame& operator=(LiquidityPoolFrame const& other);

    EntryFrame::pointer copy() const override
    {
        return EntryFrame::pointer(new LiquidityPoolFrame(*this));
    }

    static void ensureValid(LiquidityPoolEntry const& lpe);
    void ensureValid() const;

    LiquidityPoolEntry& getLiquidityPoolEntry() const;

    uint64_t getPoolID() const;
    AccountID const& getAccountID() const;
    AssetCode const& getLpTokenAsset() const;
    BalanceID const& getFirstAssetBalance() const;
    BalanceID const& getSecondAssetBalance() const;
    uint64_t const& getLPTokensAmount() const;
    uint64_t const& getFirstReserve() const;
    uint64_t const& getSecondReserve() const;

    static pointer createNew(uint64_t const& id, AccountID const& accountID, BalanceID const& firstAssetBalance,
        BalanceID const& secondAssetBalance, AssetCode const& lpTokenAsset, uint64_t const& lpTokensAmount,
        uint64_t const& firstReserve, uint64_t const& secondReserve);

    LedgerKey const& getKey() const override;

    static AssetCode const calculateLPTokenAssetCode(AssetCode const& first, AssetCode const& second);

private:
    LiquidityPoolEntry& mLiquidityPool;

    LiquidityPoolFrame(LiquidityPoolFrame const& from);
};
}
