#pragma once

#include "EntryHelper.h"
#include "LiquidityPoolFrame.h"

namespace stellar
{
class LiquidityPoolHelper : public EntryHelper
{
public:
    virtual bool exists(uint64_t poolID) = 0;
    virtual bool exists(AssetCode const& lpTokenAsset) = 0;
    virtual bool exists(AssetCode const& firstAsset, AssetCode const& secondAsset) = 0;

    virtual LiquidityPoolFrame::pointer loadPool(uint64_t poolID) = 0;
    virtual LiquidityPoolFrame::pointer loadPool(AssetCode const& lpTokenAsset) = 0;
};
}