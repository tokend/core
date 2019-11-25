#pragma once

// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "AssetPairFrame.h"
#include "ledger/EntryHelper.h"
#include "ledger/LedgerManager.h"
#include <functional>
#include <unordered_map>

namespace soci
{
class session;
}

namespace stellar
{
class StatementContext;

class AssetPairHelper : public EntryHelper
{
  public:

    virtual bool existsForAsset(AssetCode code) = 0;
    virtual bool exists(AssetCode base, AssetCode quote) = 0;
    virtual AssetPairFrame::pointer loadAssetPair(AssetCode base, AssetCode quote) = 0;

    virtual AssetPairFrame::pointer
    mustLoadAssetPair(AssetCode base, AssetCode quote) = 0;

    // tryLoadAssetPairForAssets - tries to load code1/code2 asset pair, if not
    // found loads code2/code1
    virtual AssetPairFrame::pointer
    tryLoadAssetPairForAssets(AssetCode code1, AssetCode code2) = 0;

    // convertAmount - converts amount to opposite of asset passed
    // Returns false on overflow or incorrect destination code
    virtual bool convertAmount(const AssetPairFrame::pointer& assetPair,
                       const AssetCode& destCode, uint64_t amount,
                       Rounding rounding, uint64_t& result) = 0;

    virtual void
    loadAssetPairs(StatementContext& prep,
                   std::function<void(LedgerEntry const&)> AssetPairProcessor) = 0;

    virtual void storeUpdateHelper(bool insert, LedgerEntry const& entry) = 0;
};

}
