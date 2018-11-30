#pragma once

#include <functional>
#include "EntryHelper.h"
#include "AssetFrame.h"

namespace soci
{
class session;
}

namespace stellar
{
class StatementContext;

class AssetHelper : public EntryHelper
{
public:
    using EntryHelper::exists;

	virtual bool
	exists(const AssetCode &code) = 0;

	virtual AssetFrame::pointer
	loadAsset(AssetCode assetCode) = 0;

	virtual AssetFrame::pointer
	mustLoadAsset(AssetCode assetCode) = 0;

	virtual AssetFrame::pointer
	loadAsset(AssetCode assetCode, AccountID owner) = 0;

	virtual AssetFrame::pointer
	loadStatsAsset() = 0;

    virtual void
    loadBaseAssets(std::vector<AssetFrame::pointer>& retAssets) = 0;

	virtual void
	addTrailingDigits() = 0;

	virtual bool
	doesAmountFitAssetPrecision(const AssetCode& assetCode, uint64_t amount) = 0;

private:

	virtual void
	loadAssets(StatementContext& prep,
			   std::function<void(LedgerEntry const&)> assetProcessor) = 0;

};
}