#include "LiquidityPoolFrame.h"

namespace stellar
{
using xdr::operator<;

LiquidityPoolFrame::LiquidityPoolFrame()
    : EntryFrame(LedgerEntryType::LIQUIDITY_POOL),
      mLiquidityPool(mEntry.data.liquidityPool())
{
}

LiquidityPoolFrame::LiquidityPoolFrame(const LedgerEntry& from)
    : EntryFrame(from),
      mLiquidityPool(mEntry.data.liquidityPool())
{
}

LiquidityPoolFrame&
LiquidityPoolFrame::operator=(const LiquidityPoolFrame& other)
{
    if (&other != this)
    {
        mLiquidityPool = other.mLiquidityPool;
        mKey = other.mKey;
        mKeyCalculated = other.mKeyCalculated;
    }

    return *this;
}

void LiquidityPoolFrame::ensureValid(const LiquidityPoolEntry& lpe)
{
    // TODO
}

void LiquidityPoolFrame::ensureValid() const
{
        ensureValid(mLiquidityPool);
}

LiquidityPoolEntry& LiquidityPoolFrame::getLiquidityPoolEntry() const
{
    return mLiquidityPool;
}

const AccountID& LiquidityPoolFrame::getOwnerID() const
{
    return mLiquidityPool.liquidityPoolOwner;
}

const LPAssetPair& LiquidityPoolFrame::getAssetPair() const
{
    return mLiquidityPool.assetPair;
}

LiquidityPoolFrame::pointer LiquidityPoolFrame::createNew()
{
    // TODO
    return LiquidityPoolFrame::pointer();
}

const LedgerKey& LiquidityPoolFrame::getKey() const
{
    if (!mKeyCalculated)
    {
        mKey = LedgerKey(LedgerEntryType::LIQUIDITY_POOL);
        mKey.liquidityPool().id = mLiquidityPool.sequentialID;
        mKeyCalculated = true;
    }

    return mKey;
}

LiquidityPoolFrame::LiquidityPoolFrame(const LiquidityPoolFrame& from)
    : LiquidityPoolFrame(from.mEntry)
{
}
}