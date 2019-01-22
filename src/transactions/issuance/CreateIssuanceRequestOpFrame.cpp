// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <transactions/review_request/ReviewRequestHelper.h>
#include <ledger/FeeHelper.h>
#include <transactions/ManageKeyValueOpFrame.h>
#include <ledger/KeyValueHelperLegacy.h>
#include <ledger/BalanceHelper.h>
#include "util/asio.h"
#include "CreateIssuanceRequestOpFrame.h"
#include "ledger/AccountHelper.h"
#include "ledger/AssetHelper.h"
#include "ledger/AssetHelperLegacy.h"
#include "ledger/BalanceHelperLegacy.h"
#include "ledger/ReviewableRequestFrame.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/ReferenceFrame.h"
#include "ledger/StorageHelperImpl.h"
#include "ledger/StorageHelper.h"
#include "util/Logging.h"
#include "util/types.h"
#include "database/Database.h"
#include "ledger/LedgerDelta.h"
#include "main/Application.h"
#include "crypto/SHA.h"
#include "xdrpp/marshal.h"
#include "xdrpp/printer.h"

namespace stellar
{

using namespace std;
using xdr::operator==;

const uint32_t CreateIssuanceRequestOpFrame::INSUFFICIENT_AVAILABLE_FOR_ISSUANCE_AMOUNT;
const uint32_t CreateIssuanceRequestOpFrame::ISSUANCE_MANUAL_REVIEW_REQUIRED;
const uint32_t CreateIssuanceRequestOpFrame::DEPOSIT_LIMIT_EXCEEDED;

CreateIssuanceRequestOpFrame::CreateIssuanceRequestOpFrame(Operation const& op,
                                       OperationResult& res,
                                       TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx)
    , mCreateIssuanceRequest(mOperation.body.createIssuanceRequestOp())
{
    mIsFeeRequired = true;
}

bool
CreateIssuanceRequestOpFrame::tryGetOperationConditions(StorageHelper &storageHelper,
									 	std::vector<OperationCondition>& result) const
{
	auto asset = storageHelper.getAssetHelper().loadAsset(mCreateIssuanceRequest.request.asset);
	if (!asset)
	{
		mResult.code(OperationResultCode::opNO_ASSET);
		return false;
	}

	auto balance = storageHelper.getBalanceHelper().loadBalance(mCreateIssuanceRequest.request.receiver);
	if (!balance)
	{
	    mResult.code(OperationResultCode::opNO_BALANCE);
	    return false;
	}

	auto account = AccountHelper::Instance()->mustLoadAccount(balance->getAccountID(), storageHelper.getDatabase());

	AccountRuleResource resource(LedgerEntryType::ASSET);
	resource.asset().assetCode = asset->getCode();
	resource.asset().assetType = asset->getType();

	result.emplace_back(resource, "receive", account);

	// only asset owner can do issuance, it will be handled in doApply
	return true;
}

bool CreateIssuanceRequestOpFrame::doApply(Application& app, StorageHelper &storageHelper, LedgerManager& ledgerManager)
{
	auto delta = storageHelper.getLedgerDelta();
	auto requestFrame = tryCreateIssuanceRequest(app, *delta, ledgerManager);
	if (!requestFrame)
    {
		return false;
	}

	auto& db = storageHelper.getDatabase();

    uint32_t allTasks = 0;
    if (!loadTasks(storageHelper, allTasks, mCreateIssuanceRequest.allTasks))
    {
        innerResult().code(CreateIssuanceRequestResultCode::ISSUANCE_TASKS_NOT_FOUND);
        return false;
    }

    requestFrame->setTasks(allTasks);
    EntryHelperProvider::storeChangeEntry(*delta, db, requestFrame->mEntry);

    const auto assetFrame = AssetHelperLegacy::Instance()->loadAsset(mCreateIssuanceRequest.request.asset, db);
    if (!assetFrame)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Failed to load asset for issuance request. Asset Code: "
                                               << mCreateIssuanceRequest.request.asset;
        throw runtime_error("Failed to load asset for issuance request");
    }

	if (assetFrame->isPolicySet(AssetPolicy::ISSUANCE_MANUAL_REVIEW_REQUIRED))
	{
		allTasks |= ISSUANCE_MANUAL_REVIEW_REQUIRED;
		requestFrame->setTasks(allTasks);
		EntryHelperProvider::storeChangeEntry(*delta, db, requestFrame->mEntry);
	}

    bool fulfilled = false;
	ReviewRequestResultCode reviewRequestResultCode = ReviewRequestResultCode::SUCCESS;

	if (allTasks == 0)
	{
		ReviewRequestResult reviewRequestResult = ReviewRequestHelper::tryApproveRequestWithResult(mParentTx, app,
																								   ledgerManager, *delta,
																								   requestFrame);
		reviewRequestResultCode = reviewRequestResult.code();
		fulfilled = reviewRequestResultCode == ReviewRequestResultCode::SUCCESS ?
					  reviewRequestResult.success().fulfilled:
					  false;
	}

	switch (reviewRequestResultCode) {
		case ReviewRequestResultCode::SUCCESS:
		{
			break;
		}
		case ReviewRequestResultCode::FULL_LINE:
		{
			innerResult().code(CreateIssuanceRequestResultCode::RECEIVER_FULL_LINE);
			return false;
		}
		default:
		{
			CLOG(ERROR, Logging::OPERATION_LOGGER)
					<< "Unexpected result received on review of just created issuance request: "
					<< xdr::xdr_traits<ReviewRequestResultCode>::enum_name(reviewRequestResultCode);
			throw std::runtime_error("Unexpected result received on review of just created issuance request");
		}
	}

	innerResult().code(CreateIssuanceRequestResultCode::SUCCESS);
	innerResult().success().requestID = requestFrame->getRequestID();
	innerResult().success().fulfilled = fulfilled;
	innerResult().success().fee = requestFrame->getRequestEntry().body.issuanceRequest().fee;
	auto balanceHelper = BalanceHelperLegacy::Instance();
	auto receiver = balanceHelper->mustLoadBalance(mCreateIssuanceRequest.request.receiver, db);
	innerResult().success().receiver = receiver->getAccountID();
    return true;
}

bool
CreateIssuanceRequestOpFrame::doCheckValid(Application& app)
{
    
    if (!AssetFrame::isAssetCodeValid(mCreateIssuanceRequest.request.asset)) {
        innerResult().code(CreateIssuanceRequestResultCode::ASSET_NOT_FOUND);
        return false;
    }

	if (mCreateIssuanceRequest.request.amount == 0) {
		innerResult().code(CreateIssuanceRequestResultCode::INVALID_AMOUNT);
		return false;
	}

	if (mCreateIssuanceRequest.reference.empty()) {
		innerResult().code(CreateIssuanceRequestResultCode::REFERENCE_DUPLICATION);
		return false;
	}

	if (mCreateIssuanceRequest.request.externalDetails.size() > app.getIssuanceDetailsMaxLength()
            || !isValidJson(mCreateIssuanceRequest.request.externalDetails))
	{
		innerResult().code(CreateIssuanceRequestResultCode::INVALID_EXTERNAL_DETAILS);
        return false;
	}


	int32_t systemTasks = CreateIssuanceRequestOpFrame::INSUFFICIENT_AVAILABLE_FOR_ISSUANCE_AMOUNT |
						  CreateIssuanceRequestOpFrame::ISSUANCE_MANUAL_REVIEW_REQUIRED |
						  CreateIssuanceRequestOpFrame::DEPOSIT_LIMIT_EXCEEDED;

	if (mCreateIssuanceRequest.allTasks && (*mCreateIssuanceRequest.allTasks.get() & systemTasks) != 0)
	{
		innerResult().code(CreateIssuanceRequestResultCode::SYSTEM_TASKS_NOT_ALLOWED);
		return false;
	}
	
    return true;
}

bool CreateIssuanceRequestOpFrame::isAuthorizedToRequestIssuance(AssetFrame::pointer assetFrame)
{
	return assetFrame->getOwner() == getSourceID();
}

ReviewableRequestFrame::pointer CreateIssuanceRequestOpFrame::tryCreateIssuanceRequest(Application & app, LedgerDelta & delta, LedgerManager & ledgerManager)
{
	Database& db = ledgerManager.getDatabase();

	auto reviewableRequestHelper = ReviewableRequestHelper::Instance();
	if (reviewableRequestHelper->isReferenceExist(db, getSourceID(), mCreateIssuanceRequest.reference)) {
		innerResult().code(CreateIssuanceRequestResultCode::REFERENCE_DUPLICATION);
		return nullptr;
	}

	StorageHelperImpl storageHelperImpl(db, &delta);
	StorageHelper& storageHelper = storageHelperImpl;
	auto asset = storageHelper.getAssetHelper().loadAsset(mCreateIssuanceRequest.request.asset);
	if (!asset) {
		innerResult().code(CreateIssuanceRequestResultCode::ASSET_NOT_FOUND);
		return nullptr;
	}

	if (!storageHelper.getAssetHelper().doesAmountFitAssetPrecision(
			mCreateIssuanceRequest.request.asset, mCreateIssuanceRequest.request.amount))
	{
		innerResult().code(CreateIssuanceRequestResultCode::INVALID_AMOUNT_PRECISION);
		return nullptr;
	}

	if (!isAuthorizedToRequestIssuance(asset)) {
		innerResult().code(CreateIssuanceRequestResultCode::NOT_AUTHORIZED);
		return nullptr;
	}

	if (asset->willExceedMaxIssuanceAmount(mCreateIssuanceRequest.request.amount)) {
		innerResult().code(CreateIssuanceRequestResultCode::EXCEEDS_MAX_ISSUANCE_AMOUNT);
		return nullptr;
	}

	auto balanceHelper = BalanceHelperLegacy::Instance();
    auto balance = balanceHelper->loadBalance(mCreateIssuanceRequest.request.receiver, db);
	if (!balance || balance->getAsset() != asset->getCode()) {
		innerResult().code(CreateIssuanceRequestResultCode::NO_COUNTERPARTY);
		return nullptr;
	}

    Fee feeToPay;
    if (!calculateFee(balance->getAccountID(), db, feeToPay)) {
        innerResult().code(CreateIssuanceRequestResultCode::FEE_EXCEEDS_AMOUNT);
        return nullptr;
    }

	auto reference = xdr::pointer<stellar::string64>(new stellar::string64(mCreateIssuanceRequest.reference));
	ReviewableRequestEntry::_body_t body;
	body.type(ReviewableRequestType::ISSUANCE_CREATE);
	body.issuanceRequest() = mCreateIssuanceRequest.request;
    body.issuanceRequest().fee = feeToPay;
	auto request = ReviewableRequestFrame::createNewWithHash(delta, getSourceID(), asset->getOwner(), reference,
                                                             body, ledgerManager.getCloseTime());
	EntryHelperProvider::storeAddEntry(delta, db, request->mEntry);
	return request;
}

bool CreateIssuanceRequestOpFrame::calculateFee(AccountID receiver, Database &db, Fee &fee)
{
    // calculate fee which will be charged from receiver
    fee.percent = 0;
    fee.fixed = 0;

    if (!mIsFeeRequired)
        return true;

    auto receiverFrame = AccountHelper::Instance()->mustLoadAccount(receiver, db);
    if (isSystemAccountType(receiverFrame->getAccountType()))
        return true;

    auto feeFrame = FeeHelper::Instance()->loadForAccount(FeeType::ISSUANCE_FEE, mCreateIssuanceRequest.request.asset,
                                                          FeeFrame::SUBTYPE_ANY, receiverFrame,
                                                          mCreateIssuanceRequest.request.amount, db);
    if (feeFrame) {
        fee.fixed = feeFrame->getFee().fixedFee;
        auto feeAssetFrame = AssetHelperLegacy::Instance()->mustLoadAsset(mCreateIssuanceRequest.request.asset, db);
        feeFrame->calculatePercentFee(mCreateIssuanceRequest.request.amount, fee.percent, ROUND_UP,
                                      feeAssetFrame->getMinimumAmount());
    }

    uint64_t totalFee = 0;
    if (!safeSum(fee.fixed, fee.percent, totalFee))
        throw std::runtime_error("totalFee overflows uint64");

    return totalFee < mCreateIssuanceRequest.request.amount;
}

CreateIssuanceRequestOp CreateIssuanceRequestOpFrame::build(
    AssetCode const& asset, const uint64_t amount, BalanceID const& receiver,
    LedgerManager& lm, uint32_t allTasks)
{
    IssuanceRequest request;
    request.amount = amount;
    request.asset = asset;
    request.externalDetails = "{}";
    request.fee.percent = 0;
    request.fee.fixed = 0;
    request.receiver = receiver;
    CreateIssuanceRequestOp issuanceRequestOp;
    issuanceRequestOp.request = request;
    issuanceRequestOp.reference = binToHex(sha256(xdr_to_opaque(receiver, asset, amount, lm.getCloseTime())));

	issuanceRequestOp.allTasks.activate() = allTasks;

    return issuanceRequestOp;
}

std::vector<longstring> CreateIssuanceRequestOpFrame::makeTasksKeyVector(StorageHelper &storageHelper) {
	return std::vector<longstring> {
		ManageKeyValueOpFrame::makeIssuanceTasksKey(mCreateIssuanceRequest.request.asset),
		ManageKeyValueOpFrame::makeIssuanceTasksKey("*")
	};
}
}
