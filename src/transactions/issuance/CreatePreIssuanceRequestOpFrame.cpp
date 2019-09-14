#include <transactions/review_request/ReviewRequestHelper.h>
#include "CreatePreIssuanceRequestOpFrame.h"
#include "transactions/SignatureValidatorImpl.h"
#include "transactions/ManageKeyValueOpFrame.h"
#include "ledger/AssetHelper.h"
#include "ledger/StorageHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/ReferenceFrame.h"
#include "ledger/KeyValueHelper.h"

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
	auto& requestHelper = storageHelper.getReviewableRequestHelper();
	if (requestHelper.isReferenceExist(getSourceID(), mCreatePreIssuanceRequest.request.reference)) {
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
	requestBody.type(ReviewableRequestType::CREATE_PRE_ISSUANCE);
	requestBody.preIssuanceRequest() = mCreatePreIssuanceRequest.request;

    LedgerDelta& delta = storageHelper.mustGetLedgerDelta();

    auto request = ReviewableRequestFrame::createNewWithHash(delta, getSourceID(),
                                                             app.getAdminID(), reference,
                                                             requestBody, ledgerManager.getCloseTime());

    requestHelper.storeAdd(request->mEntry);

	auto& keyValueHelper = storageHelper.getKeyValueHelper();
	uint32_t allTasks = 0;
	if (!keyValueHelper.loadTasks(allTasks, makeTasksKeyVector(),
								  mCreatePreIssuanceRequest.allTasks.get()))
	{
		innerResult().code(CreatePreIssuanceRequestResultCode::PREISSUANCE_TASKS_NOT_FOUND);
		return false;
	}

	request->setTasks(allTasks);
	requestHelper.storeChange(request->mEntry);

    bool fulfilled = false;
    if (allTasks == 0) {
		auto result = ReviewRequestHelper::tryApproveRequestWithResult(mParentTx, app, ledgerManager, storageHelper, request);
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

	if (!isValidJson(mCreatePreIssuanceRequest.request.creatorDetails))
	{
		innerResult().code(CreatePreIssuanceRequestResultCode::INVALID_CREATOR_DETAILS);
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
							  			std::vector<OperationCondition>& result,
							  			LedgerManager& ledgerManager) const
{
    if (!ledgerManager.shouldUse(LedgerVersion::FIX_NOT_CHECKING_SET_TASKS_PERMISSIONS))
    {
        return true;
    }

    AccountRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::CREATE_PRE_ISSUANCE);

    if (mCreatePreIssuanceRequest.allTasks)
    {
        result.emplace_back(resource, AccountRuleAction::CREATE_WITH_TASKS, mSourceAccount);
    }
    else
    {
        result.emplace_back(resource, AccountRuleAction::CREATE, mSourceAccount);
    }

	// only asset pre issuer can do pre issuance;
	return true;
}

bool
CreatePreIssuanceRequestOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
							 				std::vector<SignerRequirement>& result) const
{
	// only asset owner signer which is specified in asset can do pre issuance
	return true;
}

bool CreatePreIssuanceRequestOpFrame::isSignatureValid(AssetFrame::pointer asset, LedgerVersion version)
{
	auto& request = mCreatePreIssuanceRequest.request;
	auto signatureData = getSignatureData(request.reference, request.amount, request.asset);
	auto signatureValidator = SignatureValidatorImpl(signatureData, { request.signature });

	const int VALID_SIGNATURES_REQUIRED = 1;
	SignatureValidator::Result result = signatureValidator.check({ asset->getPreIssuedAssetSigner() }, VALID_SIGNATURES_REQUIRED, version);
	return result == SignatureValidator::Result::SUCCESS;
}

std::vector<std::string>
CreatePreIssuanceRequestOpFrame::makeTasksKeyVector()
{
	return
	{
		ManageKeyValueOpFrame::makePreIssuanceTasksKey(mCreatePreIssuanceRequest.request.asset),
		ManageKeyValueOpFrame::makePreIssuanceTasksKey("*")
	};
}

}
