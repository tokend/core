#include <ledger/AccountHelperLegacy.h>
#include <transactions/issuance/CreateIssuanceRequestOpFrame.h>
#include <ledger/ReviewableRequestHelper.h>
#include <ledger/PendingStatisticsHelper.h>
#include "ledger/LedgerDeltaImpl.h"
#include "ledger/AssetHelperLegacy.h"
#include "ledger/BalanceHelperLegacy.h"
#include "main/Application.h"
#include "xdrpp/printer.h"
#include "ReviewRequestHelper.h"
#include "ledger/StorageHelper.h"
#include "ledger/AssetHelper.h"

namespace stellar
{

using namespace std;
using xdr::operator==;

bool
ReviewIssuanceCreationRequestOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
											   std::vector<SignerRequirement>& result) const
{
	auto request = ReviewableRequestHelper::Instance()->loadRequest(
			mReviewRequest.requestID, storageHelper.getDatabase());
	if (!request || (request->getType() != ReviewableRequestType::CREATE_ISSUANCE))
	{
		mResult.code(OperationResultCode::opNO_ENTRY);
		mResult.entryType() = LedgerEntryType::REVIEWABLE_REQUEST;
		return false;
	}

	auto asset = storageHelper.getAssetHelper().mustLoadAsset(
			request->getRequestEntry().body.issuanceRequest().asset);

	SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
	resource.reviewableRequest().details.requestType(ReviewableRequestType::CREATE_ISSUANCE);
	resource.reviewableRequest().details.issuance().assetCode = asset->getCode();
	resource.reviewableRequest().details.issuance().assetType = asset->getType();
	resource.reviewableRequest().tasksToAdd = mReviewRequest.reviewDetails.tasksToAdd;
	resource.reviewableRequest().tasksToRemove = mReviewRequest.reviewDetails.tasksToRemove;
	resource.reviewableRequest().allTasks = 0;

	result.emplace_back(resource, SignerRuleAction::REVIEW);

	return true;
}

bool ReviewIssuanceCreationRequestOpFrame::
handleApprove(Application &app, LedgerDelta &delta,
														   LedgerManager &ledgerManager,
														   ReviewableRequestFrame::pointer request)
{
	request->checkRequestType(ReviewableRequestType::CREATE_ISSUANCE);

	auto& issuanceRequest = request->getRequestEntry().body.issuanceRequest();
	Database& db = ledgerManager.getDatabase();

	auto asset = AssetHelperLegacy::Instance()->mustLoadAsset(issuanceRequest.asset, db, &delta);
	if (asset->willExceedMaxIssuanceAmount(issuanceRequest.amount))
	{
		innerResult().code(ReviewRequestResultCode::MAX_ISSUANCE_AMOUNT_EXCEEDED);
		return false;
	}

	auto& requestEntry = request->getRequestEntry();

	auto systemTasksToAdd = getSystemTasksToAdd(app, db, delta, ledgerManager, request);
	int32_t systemTasks = CreateIssuanceRequestOpFrame::INSUFFICIENT_AVAILABLE_FOR_ISSUANCE_AMOUNT |
						  CreateIssuanceRequestOpFrame::ISSUANCE_MANUAL_REVIEW_REQUIRED |
						  CreateIssuanceRequestOpFrame::DEPOSIT_LIMIT_EXCEEDED;
	if ((systemTasksToAdd & ~systemTasks) != 0 ){
		throw std::runtime_error("Expected only system tasks, got more");
	}

    requestEntry.tasks.allTasks |= systemTasksToAdd;
	requestEntry.tasks.pendingTasks |= systemTasksToAdd;

    handleTasks(db, delta, request);

    if (!request->canBeFulfilled(ledgerManager)){
        innerResult().code(ReviewRequestResultCode::SUCCESS);
        innerResult().success().fulfilled = false;
        return true;
    }

	if (!request->canBeFulfilled(ledgerManager))
	{
		innerResult().code(ReviewRequestResultCode::SUCCESS);
        innerResult().success().fulfilled = false;
		return true;
	}

    createReference(delta, db, request->getRequestor(), request->getReference());
	EntryHelperProvider::storeDeleteEntry(delta, db, request->getKey());

	if (!asset->tryIssue(issuanceRequest.amount))
	{
		CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected state. Failed to fulfill request: "
											   << xdr::xdr_to_string(request->getRequestEntry());
		throw std::runtime_error("Unexpected issuance result. Expected to be able to issue");
	}

	EntryHelperProvider::storeChangeEntry(delta, db, asset->mEntry);

	auto receiver = BalanceHelperLegacy::Instance()->mustLoadBalance(issuanceRequest.receiver, db, &delta);

	uint64_t totalFee = 0;
	if (!safeSum(issuanceRequest.fee.fixed, issuanceRequest.fee.percent, totalFee))
	{
		CLOG(ERROR, Logging::OPERATION_LOGGER) << "totalFee overflows uint64 for request: " << request->getRequestID();
		throw std::runtime_error("totalFee overflows uint64");
	}

	if (totalFee >= issuanceRequest.amount)
	{
		CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected state. totalFee exceeds amount for request: "
											   << request->getRequestID();
		throw std::runtime_error("Unexpected state. totalFee exceeds amount");
	}

	//transfer fee
	AccountManager accountManager(app, db, delta, ledgerManager);
	accountManager.transferFee(issuanceRequest.asset, totalFee);

	const uint64_t destinationReceive = issuanceRequest.amount - totalFee;
	const BalanceFrame::Result fundResult = receiver->tryFundAccount(destinationReceive);
	if (fundResult != BalanceFrame::Result::SUCCESS)
	{
		innerResult().code(fundResult == BalanceFrame::Result::LINE_FULL ?
		                   ReviewRequestResultCode::FULL_LINE :
						   ReviewRequestResultCode::INCORRECT_PRECISION);
		return false;
	}

	EntryHelperProvider::storeChangeEntry(delta, db, receiver->mEntry);
	innerResult().code(ReviewRequestResultCode::SUCCESS);
    innerResult().success().fulfilled = true;
	innerResult().success().typeExt.requestType(ReviewableRequestType::NONE);
	return true;
}

bool ReviewIssuanceCreationRequestOpFrame::handleReject(Application & app, LedgerDelta & delta, LedgerManager & ledgerManager,
                                                        ReviewableRequestFrame::pointer request)
{
	innerResult().code(ReviewRequestResultCode::REJECT_NOT_ALLOWED);
	return false;
}

ReviewIssuanceCreationRequestOpFrame::ReviewIssuanceCreationRequestOpFrame(Operation const & op, OperationResult & res,
                                                                           TransactionFrame & parentTx) :
	ReviewRequestOpFrame(op, res, parentTx)
{
}

bool ReviewIssuanceCreationRequestOpFrame::doCheckValid(Application &app)
{
	int32_t systemTasks = CreateIssuanceRequestOpFrame::INSUFFICIENT_AVAILABLE_FOR_ISSUANCE_AMOUNT |
			              CreateIssuanceRequestOpFrame::DEPOSIT_LIMIT_EXCEEDED;

	if ((mReviewRequest.reviewDetails.tasksToAdd & systemTasks) != 0 ||
        (mReviewRequest.reviewDetails.tasksToRemove & systemTasks) != 0)
	{
		innerResult().code(ReviewRequestResultCode::SYSTEM_TASKS_NOT_ALLOWED);
		return false;
	}

	if (!isValidJson(mReviewRequest.reviewDetails.externalDetails))
	{
		innerResult().code(ReviewRequestResultCode::INVALID_EXTERNAL_DETAILS);
		return false;
	}

    return true;
}


bool ReviewIssuanceCreationRequestOpFrame::addStatistics(Database& db,
													   LedgerDelta& delta, LedgerManager& ledgerManager,
													   BalanceFrame::pointer balanceFrame, const uint64_t amountToAdd,
													   uint64_t& universalAmount)
{
	StatisticsV2Processor statisticsV2Processor(db, delta, ledgerManager);
	return tryAddStatsV2(statisticsV2Processor, balanceFrame, amountToAdd, universalAmount);
}
bool ReviewIssuanceCreationRequestOpFrame::tryAddStatsV2(StatisticsV2Processor& statisticsV2Processor,
                                                       const BalanceFrame::pointer balance, const uint64_t amountToAdd,
                                                       uint64_t& universalAmount)
{
	const auto result = statisticsV2Processor.addStatsV2(StatisticsV2Processor::SpendType::DEPOSIT, amountToAdd,
														 universalAmount, mSourceAccount, balance, nullptr);
	switch (result)
	{
		case StatisticsV2Processor::SUCCESS:
			return true;
		case StatisticsV2Processor::STATS_V2_OVERFLOW:
			return false;
		case StatisticsV2Processor::LIMITS_V2_EXCEEDED:
			return false;
		default:
			CLOG(ERROR, Logging::OPERATION_LOGGER)
					<< "Unexpeced result from statisticsV2Processor when updating statsV2:" << result;
			throw std::runtime_error("Unexpected state from statisticsV2Processor when updating statsV2");
	}

}

uint32_t ReviewIssuanceCreationRequestOpFrame::getSystemTasksToAdd( Application &app, Database& db,
		LedgerDelta &delta,
		LedgerManager &ledgerManager,
		ReviewableRequestFrame::pointer request)
	{
        // shield outer scope of any side effects by using
		// a sql transaction for ledger state and LedgerDelta
		soci::transaction localTx(db.getSession());
		LedgerDeltaImpl localDeltaImpl(delta);
		LedgerDelta& localDelta = localDeltaImpl;

		request->checkRequestType(ReviewableRequestType::CREATE_ISSUANCE);
		auto& requestEntry = request->getRequestEntry();
        auto& issuanceRequest = request->getRequestEntry().body.issuanceRequest();
		auto asset = AssetHelperLegacy::Instance()->mustLoadAsset(issuanceRequest.asset, db, &localDelta);

		uint32_t allTasks = 0;

        uint64_t universalAmount = 0;
        auto balanceFrame = AccountManager::loadOrCreateBalanceFrameForAsset(requestEntry.requestor, issuanceRequest.asset, db, localDelta);

		if (!asset->isAvailableForIssuanceAmountSufficient(issuanceRequest.amount))
		{
			allTasks |= CreateIssuanceRequestOpFrame::INSUFFICIENT_AVAILABLE_FOR_ISSUANCE_AMOUNT;
		}
		else
		{
			requestEntry.tasks.pendingTasks &= ~CreateIssuanceRequestOpFrame::INSUFFICIENT_AVAILABLE_FOR_ISSUANCE_AMOUNT;
		}

		if (!addStatistics(db, localDelta, ledgerManager,
							   balanceFrame, issuanceRequest.amount,
							   universalAmount))
		{
			allTasks |= CreateIssuanceRequestOpFrame::DEPOSIT_LIMIT_EXCEEDED;
		}
		else
		{
			requestEntry.tasks.pendingTasks &= ~CreateIssuanceRequestOpFrame::DEPOSIT_LIMIT_EXCEEDED;
		}

		if (allTasks == 0)
        {
		    localTx.commit();
		    localDelta.commit();
            return allTasks;
        }
        return allTasks;
	}

}
