// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ledger/AssetPairHelper.h"
#include "ledger/LimitsV2Helper.h"
#include "ledger/StatisticsV2Helper.h"
#include "ledger/StorageHelperImpl.h"
#include "WithdrawRequestHelper.h"
#include "ledger/AssetHelper.h"
#include "ledger/BalanceHelper.h"
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
    CreateWithdrawalRequestResultCode expectedResult,
    OperationResultCode expectedOpResultCode)
{
    Database& db = mTestManager->getDB();
    auto& requestHelper = mTestManager->getStorageHelper().getReviewableRequestHelper();
    auto& balanceHelper = mTestManager->getStorageHelper().getBalanceHelper();

    auto reviewableRequestCountBeforeTx = requestHelper.countObjects();
    auto balanceBeforeRequest = balanceHelper.loadBalance(request.balance);

    xdr::pointer<AccountID> accountID = nullptr;
    accountID.activate() = source.key.getPublicKey();
    AssetCode asset;
    if (!!balanceBeforeRequest)
        asset = balanceBeforeRequest->getAsset();

    auto limitsV2Frames = mTestManager->getStorageHelper().getLimitsV2Helper().loadLimits({StatsOpType::WITHDRAW},
                                                                     asset,
                                                                     accountID);
    std::vector<StatisticsV2Frame::pointer> statsBeforeRequestVector;
    for (LimitsV2Frame::pointer limitsV2Frame : limitsV2Frames)
    {
        auto statsBeforeRequest = mTestManager->getStorageHelper().getStatisticsV2Helper().loadStatistics(*accountID, StatsOpType::WITHDRAW,
                                                                                 limitsV2Frame->getAsset(),
                                                                                 limitsV2Frame->getConvertNeeded());
        statsBeforeRequestVector.emplace_back(statsBeforeRequest);
    }

    auto txFrame = createWithdrawalRequestTx(source, request, allTasks);
    mTestManager->applyCheck(txFrame);
    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];

    REQUIRE(opResult.code() == expectedOpResultCode);
    if (expectedOpResultCode != OperationResultCode::opINNER)
    {
        return CreateWithdrawalRequestResult();
    }

    auto actualResultCode = CreateWithdrawalRequestOpFrame::getInnerCode(opResult);
    REQUIRE(actualResultCode == expectedResult);

    uint64 reviewableRequestCountAfterTx = requestHelper.countObjects();
    if (expectedResult != CreateWithdrawalRequestResultCode::SUCCESS)
    {
        REQUIRE(reviewableRequestCountBeforeTx == reviewableRequestCountAfterTx);
        return CreateWithdrawalRequestResult{};
    }

    CreateWithdrawalRequestResult createRequestResult = opResult.tr().createWithdrawalRequestResult();
    auto withdrawRequest = requestHelper.loadRequest(createRequestResult.success().requestID);
    REQUIRE(withdrawRequest);

    REQUIRE(!!balanceBeforeRequest);
    REQUIRE(reviewableRequestCountBeforeTx + 1 == reviewableRequestCountAfterTx);

    auto balanceAfterRequest = balanceHelper.loadBalance(request.balance);
    REQUIRE(!!balanceAfterRequest);
    REQUIRE(balanceBeforeRequest->getAmount()
            == balanceAfterRequest->getAmount() + request.amount + request.fee.fixed + request.fee.percent);
    REQUIRE(balanceAfterRequest->getLocked()
            == balanceBeforeRequest->getLocked() + request.amount + request.fee.fixed + request.fee.percent);

    unsigned long iterator = 0;
    for (LimitsV2Frame::pointer limitsV2Frame : limitsV2Frames)
    {
        asset = balanceAfterRequest->getAsset();
        auto statsAfterRequest = mTestManager->getStorageHelper().getStatisticsV2Helper().mustLoadStatistics(*accountID, StatsOpType::WITHDRAW,
                                                                                    limitsV2Frame->getAsset(),
                                                                                    limitsV2Frame->getConvertNeeded());
        validateStatsChange(statsBeforeRequestVector.at(iterator), statsAfterRequest, withdrawRequest);
        iterator++;
    }


    return opResult.tr().createWithdrawalRequestResult();
}

WithdrawalRequest WithdrawRequestHelper::createWithdrawRequest(
    const BalanceID balance, const uint64_t amount, const Fee fee, std::string creatorDetails)
{
    WithdrawalRequest result;
    result.balance = balance;
    result.amount = amount;
    result.fee = fee;
    result.creatorDetails = creatorDetails;
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
        case ReviewableRequestType::CREATE_WITHDRAW:
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
    auto statsAsset = mTestManager->
        getStorageHelper().
        getAssetHelper().
        loadStatsAsset();
    if (!statsAsset)
        return false;

    auto statsAssetPair = mTestManager->getStorageHelper().getAssetPairHelper().tryLoadAssetPairForAssets(statsAsset->getCode(), baseAsset);

    return !!statsAssetPair;
}

}
}
