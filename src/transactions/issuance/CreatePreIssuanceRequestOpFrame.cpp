// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <transactions/review_request/ReviewRequestHelper.h>
#include "util/asio.h"
#include "CreatePreIssuanceRequestOpFrame.h"
#include "transactions/SignatureValidatorImpl.h"
#include "transactions/ManageKeyValueOpFrame.h"
#include "ledger/AssetHelper.h"
#include "ledger/StorageHelper.h"
#include "ledger/ReviewableRequestFrame.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/ReferenceFrame.h"
#include "util/Logging.h"
#include "util/types.h"
#include "database/Database.h"
#include "ledger/LedgerDelta.h"
#include "main/Application.h"
#include "crypto/SHA.h"

namespace stellar
{

using namespace std;
using xdr::operator==;

CreatePreIssuanceRequestOpFrame::CreatePreIssuanceRequestOpFrame(Operation const& op,
                                       OperationResult& res,
                                       TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx)
    , mCreatePreIssuanceRequest(mOperation.body.createPreIssuanceRequest())
{
}

bool
CreatePreIssuanceRequestOpFrame::doApply(Application& app,
                            StorageHelper &storageHelper, LedgerManager& ledgerManager)
{
    auto& db = storageHelper.getDatabase();
    auto delta = storageHelper.getLedgerDelta();

	auto reviewableRequestHelper = ReviewableRequestHelper::Instance();
	if (reviewableRequestHelper->isReferenceExist(db, getSourceID(), mCreatePreIssuanceRequest.request.reference)) {
		innerResult().code(CreatePreIssuanceRequestResultCode::REFERENCE_DUPLICATION);
		return false;
	}

	auto& assetHelper = storageHelper.getAssetHelper();
	auto asset = assetHelper.loadAsset(mCreatePreIssuanceRequest.request.asset);
	if (!asset) {
		innerResult().code(CreatePreIssuanceRequestResultCode::ASSET_NOT_FOUND);
		return false;
	}

	if (!(asset->getOwner() == getSourceID())) {
		innerResult().code(CreatePreIssuanceRequestResultCode::NOT_AUTHORIZED_UPLOAD);
		return false;
	}

	if (!isSignatureValid(asset, LedgerVersion(ledgerManager.getCurrentLedgerHeader().ledgerVersion))) {
		innerResult().code(CreatePreIssuanceRequestResultCode::INVALID_SIGNATURE);
		return false;
	}

    if (mCreatePreIssuanceRequest.request.amount % asset->getMinimumAmount() != 0) {
        innerResult().code(CreatePreIssuanceRequestResultCode::INCORRECT_AMOUNT_PRECISION);
        return false;
    }

	if (!asset->canAddAvailableForIssuance(mCreatePreIssuanceRequest.request.amount)) {
		innerResult().code(CreatePreIssuanceRequestResultCode::EXCEEDED_MAX_AMOUNT);
		return false;
	}

	auto reference = xdr::pointer<stellar::string64>(new stellar::string64(mCreatePreIssuanceRequest.request.reference));
	ReviewableRequestEntry::_body_t requestBody;
	requestBody.type(ReviewableRequestType::PRE_ISSUANCE_CREATE);
	requestBody.preIssuanceRequest() = mCreatePreIssuanceRequest.request;
	auto request = ReviewableRequestFrame::createNewWithHash(*delta, getSourceID(),
                                                             app.getAdminID(), reference,
                                                             requestBody, ledgerManager.getCloseTime());
	EntryHelperProvider::storeAddEntry(*delta, db, request->mEntry);

	uint32_t allTasks = 0;
	if (!loadTasks(storageHelper, allTasks, mCreatePreIssuanceRequest.allTasks))
	{
		innerResult().code(CreatePreIssuanceRequestResultCode::PREISSUANCE_TASKS_NOT_FOUND);
		return false;
	}

	request->setTasks(allTasks);
	EntryHelperProvider::storeChangeEntry(*delta, db, request->mEntry);

    bool fulfilled = false;
    if (allTasks == 0) {
		auto result = ReviewRequestHelper::tryApproveRequestWithResult(mParentTx, app, ledgerManager, *delta, request);
		if (result.code() != ReviewRequestResultCode::SUCCESS) {
			throw std::runtime_error("Failed to review preissuance request");
		}
		fulfilled = result.success().fulfilled;
    }
	innerResult().code(CreatePreIssuanceRequestResultCode::SUCCESS);
	innerResult().success().requestID = request->getRequestID();
    innerResult().success().fulfilled = fulfilled;
	return true;
}

bool
CreatePreIssuanceRequestOpFrame::doCheckValid(Application& app)
{
    
    if (!AssetFrame::isAssetCodeValid(mCreatePreIssuanceRequest.request.asset)) {
        innerResult().code(CreatePreIssuanceRequestResultCode::ASSET_NOT_FOUND);
        return false;
    }

	if (mCreatePreIssuanceRequest.request.amount == 0) {
		innerResult().code(CreatePreIssuanceRequestResultCode::INVALID_AMOUNT);
		return false;
	}

	if (mCreatePreIssuanceRequest.request.reference.empty()) {
		innerResult().code(CreatePreIssuanceRequestResultCode::INVALID_REFERENCE);
		return false;
	}
	
    return true;
}

Hash CreatePreIssuanceRequestOpFrame::getSignatureData(stellar::string64 const & reference, uint64_t const & amount, AssetCode const & assetCode)
{
	std::string rawSignatureData = reference + ":" + std::to_string(amount) + ":" + assetCode;
	return Hash(sha256(rawSignatureData));
}

bool
CreatePreIssuanceRequestOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
							  			std::vector<OperationCondition>& result) const
{
	// only asset pre issuer can do pre issuance;
	return true;
}

bool CreatePreIssuanceRequestOpFrame::isSignatureValid(AssetFrame::pointer asset, LedgerVersion version)
{
	auto& request = mCreatePreIssuanceRequest.request;
	auto signatureData = getSignatureData(mCreatePreIssuanceRequest.request.reference, request.amount, request.asset);
	auto signatureValidator = SignatureValidatorImpl(signatureData, { request.signature });

	const int VALID_SIGNATURES_REQUIRED = 1;
	SignatureValidator::Result result = signatureValidator.check({ asset->getPreIssuedAssetSigner() }, VALID_SIGNATURES_REQUIRED, version);
	return result == SignatureValidator::Result::SUCCESS;
}

std::vector<longstring> CreatePreIssuanceRequestOpFrame::makeTasksKeyVector(StorageHelper &storageHelper) {
	return std::vector<longstring>{
		ManageKeyValueOpFrame::makePreIssuanceTasksKey(mCreatePreIssuanceRequest.request.asset),
		ManageKeyValueOpFrame::makePreIssuanceTasksKey("*")
	};
}

}
