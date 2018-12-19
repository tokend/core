// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <ledger/StatisticsHelper.h>
#include <ledger/AssetPairHelper.h>
#include <ledger/LimitsV2Helper.h>
#include <ledger/StatisticsV2Helper.h>
#include "WithdrawRequestHelper.h"
#include "ledger/AssetHelperLegacy.h"
#include "ledger/BalanceHelperLegacy.h"
#include "ledger/ReviewableRequestHelper.h"
#include "transactions/CreateWithdrawalRequestOpFrame.h"
#include "test/test_marshaler.h"

namespace stellar
{
namespace txtest
{
WithdrawRequestHelper::
WithdrawRequestHelper(TestManager::pointer testManager) : TxHelper(testManager)
{
}

CreateWithdrawalRequestResult WithdrawRequestHelper::applyCreateWithdrawRequest(
    Account& source, WithdrawalRequest request,
    uint32_t *allTasks,
    CreateWithdrawalRequestResultCode expectedResult)
{
    Database& db = mTestManager->getDB();
    auto reviewableRequestHelper = ReviewableRequestHelper::Instance();
    auto reviewableRequestCountBeforeTx = reviewableRequestHelper->countObjects(db.getSession());
    auto balanceBeforeRequest = BalanceHelperLegacy::Instance()->loadBalance(request.balance, db);

    xdr::pointer<AccountID> accountID = nullptr;
    accountID.activate() = source.key.getPublicKey();
    AssetCode asset;
    if (!!balanceBeforeRequest)
        asset = balanceBeforeRequest->getAsset();

    auto limitsV2Frames = LimitsV2Helper::Instance()->loadLimits(db, {StatsOpType::WITHDRAW},
                                                                 asset,
                                                                 accountID);
    std::vector<StatisticsV2Frame::pointer> statsBeforeRequestVector;
    for (LimitsV2Frame::pointer limitsV2Frame : limitsV2Frames)
    {
        auto statsBeforeRequest = StatisticsV2Helper::Instance()->loadStatistics(*accountID, StatsOpType::WITHDRAW,
                                                                                 limitsV2Frame->getAsset(),
                                                                                 limitsV2Frame->getConvertNeeded(),
                                                                                 db);
        statsBeforeRequestVector.emplace_back(statsBeforeRequest);
    }

    auto txFrame = createWithdrawalRequestTx(source, request, allTasks);
    mTestManager->applyCheck(txFrame);
    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];
    auto actualResultCode = CreateWithdrawalRequestOpFrame::getInnerCode(opResult);
    REQUIRE(actualResultCode == expectedResult);

    uint64 reviewableRequestCountAfterTx = reviewableRequestHelper->countObjects(db.getSession());
    if (expectedResult != CreateWithdrawalRequestResultCode::SUCCESS)
    {
        REQUIRE(reviewableRequestCountBeforeTx == reviewableRequestCountAfterTx);
        return CreateWithdrawalRequestResult{};
    }

    CreateWithdrawalRequestResult createRequestResult = opResult.tr().createWithdrawalRequestResult();
    auto withdrawRequest = ReviewableRequestHelper::Instance()->loadRequest(createRequestResult.success().requestID, db);
    REQUIRE(withdrawRequest);

    REQUIRE(!!balanceBeforeRequest);
    REQUIRE(reviewableRequestCountBeforeTx + 1 == reviewableRequestCountAfterTx);

    auto balanceAfterRequest = BalanceHelperLegacy::Instance()->loadBalance(request.balance, db);
    REQUIRE(!!balanceAfterRequest);
    REQUIRE(balanceBeforeRequest->getAmount() == balanceAfterRequest->getAmount() + request.amount + request.fee.fixed + request.fee.percent);
    REQUIRE(balanceAfterRequest->getLocked() == balanceBeforeRequest->getLocked() + request.amount + request.fee.fixed + request.fee.percent);

    unsigned long iterator = 0;
    for (LimitsV2Frame::pointer limitsV2Frame : limitsV2Frames)
    {
        asset = balanceAfterRequest->getAsset();
        auto statsAfterRequest = StatisticsV2Helper::Instance()->mustLoadStatistics(*accountID, StatsOpType::WITHDRAW,
                                                                                    limitsV2Frame->getAsset(),
                                                                                    limitsV2Frame->getConvertNeeded(),
                                                                                    db);
        validateStatsChange(statsBeforeRequestVector.at(iterator), statsAfterRequest, withdrawRequest);
        iterator++;
    }


    return opResult.tr().createWithdrawalRequestResult();
}

WithdrawalRequest WithdrawRequestHelper::createWithdrawRequest(
    const BalanceID balance, const uint64_t amount, const Fee fee, std::string externalDetails)
{
    WithdrawalRequest result;
    result.balance = balance;
    result.amount = amount;
    result.fee = fee;
    result.externalDetails = externalDetails;
    result.ext.v(LedgerVersion::EMPTY_VERSION);
    return result;
}

TransactionFramePtr WithdrawRequestHelper::createWithdrawalRequestTx(
    Account& source, const WithdrawalRequest request, uint32_t *allTasks)
{
    Operation baseOp;
    baseOp.body.type(OperationType::CREATE_WITHDRAWAL_REQUEST);
    auto& op = baseOp.body.createWithdrawalRequestOp();
    op.request = request;
    op.ext.v(LedgerVersion::WITHDRAWAL_TASKS);
    if (allTasks != nullptr)
    {
        op.allTasks.activate() = *allTasks;
    }
    return txFromOperation(source, baseOp, nullptr);
}

void WithdrawRequestHelper::validateStatsChange(StatisticsV2Frame::pointer statsBefore,
                                                StatisticsV2Frame::pointer statsAfter,
                                                ReviewableRequestFrame::pointer withdrawRequest)
{
    uint64_t universalAmount = 0;
    switch (withdrawRequest->getRequestType())
    {
    case ReviewableRequestType::WITHDRAW:
        universalAmount = withdrawRequest->getRequestEntry().body.withdrawalRequest().universalAmount;
        break;
    default:
        throw std::runtime_error("Unexpected reviewable request type");
    }
    REQUIRE(universalAmount != 0);

    REQUIRE(statsAfter->getUpdateAt() == withdrawRequest->getCreatedAt());

    if (!!statsBefore)
    {
        REQUIRE(statsAfter->getDailyOutcome() == universalAmount + statsBefore->getDailyOutcome());
        REQUIRE(statsAfter->getWeeklyOutcome() == universalAmount + statsBefore->getWeeklyOutcome());
        REQUIRE(statsAfter->getMonthlyOutcome() == universalAmount + statsBefore->getMonthlyOutcome());
        REQUIRE(statsAfter->getAnnualOutcome() == universalAmount + statsBefore->getAnnualOutcome());
    }
    else
    {
        REQUIRE(statsAfter->getDailyOutcome() == universalAmount);
        REQUIRE(statsAfter->getWeeklyOutcome() == universalAmount);
        REQUIRE(statsAfter->getMonthlyOutcome() == universalAmount);
        REQUIRE(statsAfter->getAnnualOutcome() == universalAmount);
    }
    REQUIRE(statsAfter->isValid());
}

bool WithdrawRequestHelper::canCalculateStats(AssetCode baseAsset)
{
    auto statsAsset = AssetHelperLegacy::Instance()->loadStatsAsset(mTestManager->getDB());
    if (!statsAsset)
        return false;

    auto statsAssetPair = AssetPairHelper::Instance()->tryLoadAssetPairForAssets(statsAsset->getCode(), baseAsset,
                                                                                 mTestManager->getDB());

    return !!statsAssetPair;
}

}
}
