#include "LiquidityPoolFrame.h"

#include "xdrpp/printer.h"
#include "AssetFrame.h"
#include <crypto/StrKey.h>
#include "util/SecretValue.h"

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
    try
    {
        if (lpe.firstAssetBalance == lpe.secondAssetBalance)
        {
            throw std::runtime_error("balances of asset pair cannot be equal");
        }

        if (!AssetFrame::isAssetCodeValid(lpe.lpTokenAssetCode))
        {
            throw std::runtime_error("invalid LP token asset code");
        }
    } catch(...)
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER) << "Unexpected state liquidity pool entry is invalid: "
            << xdr::xdr_to_string(lpe);
        throw_with_nested(std::runtime_error("Liquidity pool entry is invalid"));
    }
}

void LiquidityPoolFrame::ensureValid() const
{
    ensureValid(mLiquidityPool);
}

LiquidityPoolEntry& LiquidityPoolFrame::getLiquidityPoolEntry() const
{
    return mLiquidityPool;
}

AccountID const& LiquidityPoolFrame::getAccountID() const
{
    return mLiquidityPool.liquidityPoolAcount;
}

AssetCode const& LiquidityPoolFrame::getLpTokenAsset() const
{
    return mLiquidityPool.lpTokenAssetCode;
}

BalanceID const& LiquidityPoolFrame::getFirstAssetBalance() const
{
    return mLiquidityPool.firstAssetBalance;
}

BalanceID const& LiquidityPoolFrame::getSecondAssetBalance() const
{
    return mLiquidityPool.secondAssetBalance;
}

uint64_t const& LiquidityPoolFrame::getLPTokensAmount() const
{
    return mLiquidityPool.lpTokensTotalCap;
}

LiquidityPoolFrame::pointer
LiquidityPoolFrame::createNew(uint64_t const& id, AccountID const& accountID, BalanceID const& firstAssetBalance,
    BalanceID const& secondAssetBalance, AssetCode const& lpTokenAsset, uint64_t const& lpTokensAmount,
    uint64_t const& firstReserve, uint64_t const& secondReserve)
{
    LedgerEntry entry;
    entry.data.type(LedgerEntryType::LIQUIDITY_POOL);

    LiquidityPoolEntry& lp = entry.data.liquidityPool();
    lp.id = id;
    lp.liquidityPoolAcount = accountID;
    lp.firstAssetBalance = firstAssetBalance;
    lp.secondAssetBalance = secondAssetBalance;
    lp.lpTokenAssetCode = lpTokenAsset;
    lp.lpTokensTotalCap = lpTokensAmount;

    return std::make_shared<LiquidityPoolFrame>(entry);
}

const LedgerKey& LiquidityPoolFrame::getKey() const
{
    if (!mKeyCalculated)
    {
        mKey = LedgerKey(LedgerEntryType::LIQUIDITY_POOL);
        mKey.liquidityPool().id = mLiquidityPool.id;
        mKeyCalculated = true;
    }

    return mKey;
}

LiquidityPoolFrame::LiquidityPoolFrame(const LiquidityPoolFrame& from)
    : LiquidityPoolFrame(from.mEntry)
{
}

uint64_t LiquidityPoolFrame::getPoolID() const
{
    return mLiquidityPool.id;
}

uint64_t const& LiquidityPoolFrame::getFirstReserve() const
{
    return mLiquidityPool.firstReserve;
}

uint64_t const& LiquidityPoolFrame::getSecondReserve() const
{
    return mLiquidityPool.secondReserve;
}

AssetCode const LiquidityPoolFrame::calculateLPTokenAssetCode(const AssetCode& first, const AssetCode& second)
{
    AssetCode lFirst = first, lSecond = second;
    if (first > second)
    {
        lFirst.swap(lSecond);
    }

    std::string lpTokenCodeStr = "LP:" + lFirst + ":" + lSecond;
    Hash lpTokenHash = HashUtils::fromStr(lpTokenCodeStr);
    auto key = strKey::toStrKey(strKey::STRKEY_PUBKEY_ED25519, lpTokenHash).value;

    return {std::begin(key), std::begin(key) + 16};
}

}