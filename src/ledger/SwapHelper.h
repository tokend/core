#pragma once

#include "SwapFrame.h"
#include "ledger/EntryHelper.h"

namespace stellar
{

class SwapHelper : public EntryHelper
{
  public:
    using EntryHelper::exists;

    virtual bool exists(uint64_t id) = 0;

    virtual SwapFrame::pointer loadSwap(uint64_t swapID) = 0;
    virtual SwapFrame::pointer mustLoadSwap(uint64_t swapID) = 0;
    virtual bool existForAsset(const AssetCode& assetCode) = 0;
};
}