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

    AccountID const& getOwnerID() const;
    LPAssetPair const& getAssetPair() const;

    static pointer createNew();

    LedgerKey const& getKey() const override;

private:
    LiquidityPoolEntry& mLiquidityPool;

    LiquidityPoolFrame(LiquidityPoolFrame const& from);
};
}
