#pragma once

#include "EntryHelper.h"
#include "LiquidityPoolFrame.h"

namespace stellar
{
class LiquidityPoolHelper : public EntryHelper
{
public:
    virtual LiquidityPoolFrame::pointer
    loadLiquidityPool(uint64_t id) = 0;

    virtual void createIfNotExists() = 0;
};
}