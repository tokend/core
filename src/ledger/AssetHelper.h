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
class LedgerManager;

class AssetHelper : public EntryHelper
{
public:
    using EntryHelper::exists;

        virtual std::map<AssetCode, uint64_t>
        loadIssuedForAssets() = 0;
	virtual bool existActive(const AssetCode &code) = 0;
	virtual bool exists(const AssetCode &code) = 0;

	virtual AssetFrame::pointer loadActiveAsset(AssetCode assetCode) = 0;
	virtual AssetFrame::pointer loadAsset(AssetCode assetCode) = 0;

	virtual AssetFrame::pointer
	mustLoadAsset(AssetCode assetCode) = 0;

	virtual AssetFrame::pointer
	loadAsset(AssetCode assetCode, AccountID owner) = 0;

	virtual AssetFrame::pointer
	loadStatsAsset() = 0;

    virtual std::vector<AssetFrame::pointer>
    loadBaseAssets() = 0;

	virtual void
	addTrailingDigits() = 0;

	virtual bool
	doesAmountFitAssetPrecision(const AssetCode& assetCode, uint64_t amount) = 0;

        virtual void
        addAssetState() = 0;

        virtual void
        markDeleted(LedgerEntry const& entry, LedgerManager& lm) = 0;


};
}