#pragma once

#include "EntryHelper.h"
#include "StorageHelper.h"
#include "LiquidityPoolHelper.h"

namespace soci
{
    class session;
}

namespace stellar
{
class StatementContext;

class LiquidityPoolHelperImpl : public LiquidityPoolHelper, NonCopyable
{
public:
    explicit LiquidityPoolHelperImpl(StorageHelper &storageHelper);
};
}
