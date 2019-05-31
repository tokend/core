#include "util/asio.h"
#include "ReviewAssetCreationRequestOpFrame.h"
#include "database/Database.h"
#include "ledger/LedgerDelta.h"
#include "ledger/StorageHelperImpl.h"
#include "ledger/AssetHelperLegacy.h"
#include "ledger/BalanceHelperLegacy.h"
#include "main/Application.h"
#include "transactions/managers/BalanceManager.h"

namespace stellar
{

using namespace std;
using xdr::operator==;

bool ReviewAssetCreationRequestOpFrame::handleApprove(Application & app, LedgerDelta & delta, LedgerManager & ledgerManager, ReviewableRequestFrame::pointer request)
{
	if (request->getRequestType() != ReviewableRequestType::CREATE_ASSET) {
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

	StorageHelperImpl storageHelper(db, &delta);
	BalanceManager balanceManager(app, storageHelper);

    if (assetFrame->isPolicySet(AssetPolicy::BASE_ASSET))
    {
		balanceManager.loadOrCreateBalanceForAdmin(assetFrame->getCode());
    }
    else
    {
        balanceManager.loadOrCreateBalance(assetFrame->getOwner(), assetFrame->getCode());
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
