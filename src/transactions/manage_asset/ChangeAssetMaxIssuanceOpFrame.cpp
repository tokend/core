// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <lib/xdrpp/xdrpp/printer.h>
#include <transactions/review_request/ReviewIssuanceCreationRequestOpFrame.h>
#include <main/Application.h>
#include <transactions/review_request/ReviewRequestHelper.h>
#include <ledger/StorageHelper.h>
#include "ChangeAssetMaxIssuanceOpFrame.h"
#include "ledger/AccountHelperLegacy.h"
#include "ledger/AssetHelper.h"
#include "ledger/AssetHelperLegacy.h"

namespace stellar
{
using namespace std;
using xdr::operator==;

ChangeAssetMaxIssuanceOpFrame::ChangeAssetMaxIssuanceOpFrame(Operation const& op,
                                                         OperationResult& res,
                                                         TransactionFrame&
                                                         parentTx)
    : ManageAssetOpFrame(op, res, parentTx)
{
    mUpdateMaxIssuance = mManageAsset.request.updateMaxIssuance();
}

bool
ChangeAssetMaxIssuanceOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                          std::vector<OperationCondition>& result) const
{
    auto asset = storageHelper.getAssetHelper().loadAsset(mUpdateMaxIssuance.assetCode);
    if (!asset)
    {
        mResult.code(OperationResultCode::opNO_ASSET);
        return false;
    }

    AccountRuleResource resource(LedgerEntryType::ASSET);
    resource.asset().assetCode = asset->getCode();
    resource.asset().assetType = asset->getType();

    result.emplace_back(resource, "update_max_issuance", mSourceAccount);

    // only asset owner can do it, but it is useful to restrict him
    return true;
}

bool ChangeAssetMaxIssuanceOpFrame::doApply(Application& app, LedgerDelta& delta,
                                          LedgerManager& ledgerManager)
{
    Database& db = ledgerManager.getDatabase();
    auto assetFrame = AssetHelperLegacy::Instance()->
        loadAsset(mUpdateMaxIssuance.assetCode, getSourceID(), db, &delta);
    if (!assetFrame)
    {
        innerResult().code(ManageAssetResultCode::ASSET_NOT_FOUND);
        return false;
    }

    auto& assetEntry = assetFrame->getAsset();
    assetEntry.maxIssuanceAmount = mUpdateMaxIssuance.maxIssuanceAmount;
    try {
        assetFrame->ensureValid();
    }
    catch (...) {
        innerResult().code(ManageAssetResultCode::INVALID_MAX_ISSUANCE_AMOUNT);
        return false;
    }
    AssetHelperLegacy::Instance()->storeChange(delta, db, assetFrame->mEntry);
    innerResult().code(ManageAssetResultCode::SUCCESS);
    innerResult().success().requestID = 0;
    innerResult().success().fulfilled = true;
    return true;
}

bool ChangeAssetMaxIssuanceOpFrame::doCheckValid(Application& app)
{
    return true;
}

string ChangeAssetMaxIssuanceOpFrame::getAssetCode() const
{
    return mUpdateMaxIssuance.assetCode;
}
}
