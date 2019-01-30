// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <transactions/manage_asset/ManageAssetHelper.h>
#include "util/asio.h"
#include "ReviewAssetCreationRequestOpFrame.h"
#include "database/Database.h"
#include "ledger/LedgerDelta.h"
#include "ledger/AssetHelperLegacy.h"
#include "ledger/BalanceHelperLegacy.h"
#include "main/Application.h"

namespace stellar
{

using namespace std;
using xdr::operator==;

bool ReviewAssetCreationRequestOpFrame::handleApprove(Application & app, LedgerDelta & delta, LedgerManager & ledgerManager, ReviewableRequestFrame::pointer request)
{
	if (request->getRequestType() != ReviewableRequestType::ASSET_CREATE) {
		CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected request type. Expected ASSET_CREATE, but got " << xdr::xdr_traits<ReviewableRequestType>::enum_name(request->getRequestType());
		throw std::invalid_argument("Unexpected request type for review asset creation request");
	}

	auto assetCreationRequest = request->getRequestEntry().body.assetCreationRequest();
	Database& db = ledgerManager.getDatabase();

	auto assetHelper = AssetHelperLegacy::Instance();
	auto isAssetExist = assetHelper->exists(db, assetCreationRequest.code);
	if (isAssetExist) {
		innerResult().code(ReviewRequestResultCode::ASSET_ALREADY_EXISTS);
		return false;
	}


	handleTasks(db, delta, request);

	if (!request->canBeFulfilled(ledgerManager)){
		innerResult().code(ReviewRequestResultCode::SUCCESS);
		innerResult().success().fulfilled = false;
		return true;
	}

	auto assetFrame = AssetFrame::create(assetCreationRequest, request->getRequestor());
	EntryHelperProvider::storeAddEntry(delta, db, assetFrame->mEntry);

    if (assetFrame->isPolicySet(AssetPolicy::BASE_ASSET))
    {
        ManageAssetHelper::createSystemBalances(assetFrame->getCode(), app, delta);
    } else
    {
        AccountManager::loadOrCreateBalanceForAsset(assetFrame->getOwner(), assetFrame->getCode(), db, delta);
    }

	EntryHelperProvider::storeDeleteEntry(delta, db, request->getKey());
	innerResult().code(ReviewRequestResultCode::SUCCESS);
	innerResult().success().fulfilled = true;
	return true;
}

ReviewAssetCreationRequestOpFrame::ReviewAssetCreationRequestOpFrame(Operation const & op, OperationResult & res, TransactionFrame & parentTx) :
	ReviewRequestOpFrame(op, res, parentTx)
{
}

}
