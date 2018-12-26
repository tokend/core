// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <transactions/test/TxTests.h>
#include <cstdint>
#include "ManageAssetTestHelper.h"
#include "ledger/AccountHelper.h"
#include "ledger/AssetHelperLegacy.h"
#include "ledger/AssetHelperImpl.h"
#include "ledger/BalanceHelperLegacy.h"
#include "ledger/ReviewableRequestFrame.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/StorageHelperImpl.h"
#include "transactions/manage_asset/ManageAssetOpFrame.h"
#include "ReviewAssetRequestHelper.h"
#include "test/test_marshaler.h"


namespace stellar
{
namespace txtest
{
ManageAssetTestHelper::
ManageAssetTestHelper(TestManager::pointer testManager) : TxHelper(testManager)
{
}

void ManageAssetTestHelper::createApproveRequest(Account& root, Account& source,
                                                 const ManageAssetOp::_request_t
                                                 request)
{
    auto requestCreationResult = applyManageAssetTx(source, 0, request);
    if (requestCreationResult.success().fulfilled)
        return;
    auto requestFrame = ReviewableRequestHelper::Instance()->
        loadRequest(requestCreationResult.success().requestID,
                    mTestManager->getDB());
    auto reviewHelper = ReviewAssetRequestHelper(mTestManager);
    reviewHelper.applyReviewRequestTx(root, requestCreationResult.success().
                                                                  requestID,
                                      requestFrame->getHash(),
                                      requestFrame->getRequestType(),
                                      ReviewRequestOpAction::APPROVE, "");
}

ManageAssetResult ManageAssetTestHelper::applyManageAssetTx(
    Account& source, uint64_t requestID, ManageAssetOp::_request_t request,
    ManageAssetResultCode expectedResult, OperationResultCode expectedOpCode)
{
    auto reviewableRequestHelper = ReviewableRequestHelper::Instance();
    auto reviewableRequestCountBeforeTx = reviewableRequestHelper->
        countObjects(mTestManager->getDB().getSession());
    auto requestBeforeTx = reviewableRequestHelper->loadRequest(requestID,
                                                                mTestManager->
                                                                getLedgerManager()
                                                                .getDatabase(),
                                                                nullptr);
    auto txFrame = createManageAssetTx(source, requestID, request);

    mTestManager->applyCheck(txFrame);
    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];
    REQUIRE(opResult.code() == expectedOpCode);
    if (opResult.code() != OperationResultCode::opINNER) {
        return ManageAssetResult();
    }
    auto actualResultCode = ManageAssetOpFrame::getInnerCode(opResult);
    REQUIRE(actualResultCode == expectedResult);

    uint64 reviewableRequestCountAfterTx = reviewableRequestHelper->
        countObjects(mTestManager->getDB().getSession());
    if (expectedResult != ManageAssetResultCode::SUCCESS)
    {
        REQUIRE(reviewableRequestCountBeforeTx == reviewableRequestCountAfterTx)
        ;
        return ManageAssetResult{};
    }

    auto accountHelper = AccountHelper::Instance();
    auto sourceFrame = accountHelper->loadAccount(source.key.getPublicKey(),
                                                  mTestManager->getDB());
    auto manageAssetResult = opResult.tr().manageAssetResult();

    auto assetHelper = AssetHelperLegacy::Instance();
    auto balanceHelper = BalanceHelperLegacy::Instance();

    if ((request.action() == ManageAssetAction::CREATE_ASSET_CREATION_REQUEST
        || request.action() == ManageAssetAction::CREATE_ASSET_UPDATE_REQUEST)
        && manageAssetResult.success().fulfilled)
    {
        REQUIRE(reviewableRequestCountAfterTx == reviewableRequestCountBeforeTx);

        validateManageAssetEffect(request);

        return manageAssetResult;
    }


    const bool isUpdatingExistingRequest = requestID != 0;
    if (isUpdatingExistingRequest)
    {
        REQUIRE(!!requestBeforeTx);
    }

    auto requestAfterTx = reviewableRequestHelper->loadRequest(manageAssetResult
                                                               .success().
                                                                requestID,
                                                               mTestManager->
                                                               getDB(),
                                                               nullptr);
    if (request.action() == ManageAssetAction::CANCEL_ASSET_REQUEST)
    {
        REQUIRE(!requestAfterTx);
        return manageAssetResult;
    }

    REQUIRE(requestAfterTx);
    REQUIRE(requestAfterTx->getRequestEntry().rejectReason.empty());

    switch (request.action())
    {
    case ManageAssetAction::CREATE_ASSET_CREATION_REQUEST:
        REQUIRE(requestAfterTx->getRequestEntry().body.assetCreationRequest() ==
            request.createAssetCreationRequest().createAsset);
        break;
    case ManageAssetAction::CREATE_ASSET_UPDATE_REQUEST:
        REQUIRE(requestAfterTx->getRequestEntry().body.assetUpdateRequest() ==
            request.createAssetUpdateRequest().updateAsset);
        break;
    default:
        throw std::runtime_error("Unexpected action for manage asset");
    }

    return manageAssetResult;
}

Operation
ManageAssetTestHelper::createManageAssetOp(Account &source, uint64_t requestID, ManageAssetOp::_request_t request)
{
    Operation op;
    op.body.type(OperationType::MANAGE_ASSET);
    ManageAssetOp& manageAssetOp = op.body.manageAssetOp();
    manageAssetOp.requestID = requestID;
    manageAssetOp.request = request;

    return op;
}

TransactionFramePtr ManageAssetTestHelper::createManageAssetTx(
    Account& source, uint64_t requestID, ManageAssetOp::_request_t request)
{
    Operation op = createManageAssetOp(source, requestID, request);
    return txFromOperation(source, op, nullptr);
}

ManageAssetOp::_request_t ManageAssetTestHelper::createAssetCreationRequest(
    AssetCode code,
    AccountID preissuedAssetSigner,
    std::string details,
    uint64_t maxIssuanceAmount,
    uint32_t policies,
    uint32_t* allTasks,
    uint64_t initialPreissuanceAmount,
    uint32_t trailingDigitsCount
    )
{
    ManageAssetOp::_request_t request;
    request.action(ManageAssetAction::CREATE_ASSET_CREATION_REQUEST);
    AssetCreationRequest& assetCreationRequest = request.createAssetCreationRequest().createAsset;
    assetCreationRequest.code = code;
    assetCreationRequest.details = details;
    assetCreationRequest.maxIssuanceAmount = maxIssuanceAmount;
    assetCreationRequest.policies = policies;
    assetCreationRequest.preissuedAssetSigner = preissuedAssetSigner;
    assetCreationRequest.initialPreissuedAmount = initialPreissuanceAmount;
    if (trailingDigitsCount != AssetFrame::kMaximumTrailingDigits)
    {
        assetCreationRequest.ext.v(LedgerVersion::ADD_ASSET_BALANCE_PRECISION);
        assetCreationRequest.ext.trailingDigitsCount() = trailingDigitsCount;
    }
    if (allTasks){
        request.createAssetCreationRequest().allTasks.activate() = *allTasks;
    }
    return request;
}

ManageAssetOp::_request_t ManageAssetTestHelper::createAssetUpdateRequest(
    AssetCode code,
    std::string details,
    uint32_t policies,
    uint32_t *allTasks
)
{
    ManageAssetOp::_request_t request;
    request.action(ManageAssetAction::CREATE_ASSET_UPDATE_REQUEST);
    AssetUpdateRequest& assetUpdateRequest = request.createAssetUpdateRequest().updateAsset;
    assetUpdateRequest.code = code;
    assetUpdateRequest.details = details;
    assetUpdateRequest.policies = policies;
    if (allTasks){
        request.createAssetUpdateRequest().allTasks.activate() = *allTasks;
    }
    return request;
}

ManageAssetOp::_request_t ManageAssetTestHelper::createCancelRequest()
{
    ManageAssetOp::_request_t request;
    request.action(ManageAssetAction::CANCEL_ASSET_REQUEST);
    return request;
}

ManageAssetOp::_request_t ManageAssetTestHelper::updateMaxAmount(AssetCode asset, uint64 amount)
{
    ManageAssetOp::_request_t request;
    request.action(ManageAssetAction::UPDATE_MAX_ISSUANCE);
    request.updateMaxIssuance().assetCode = asset;
    request.updateMaxIssuance().maxIssuanceAmount = amount;
    return request;
}

ManageAssetOp::_request_t ManageAssetTestHelper::createChangeSignerRequest(
    AssetCode code, AccountID accountID)
{
    ManageAssetOp::_request_t request;
    request.action(ManageAssetAction::CHANGE_PREISSUED_ASSET_SIGNER);
    request.changePreissuedSigner().accountID = accountID;
    request.changePreissuedSigner().code = code;
    return request;
}

void ManageAssetTestHelper::createAsset(Account& assetOwner,
                                        SecretKey& preIssuedSigner,
                                        AssetCode assetCode, Account& root,
                                        uint32_t policies,
                                        uint32_t* allTasks,
                                        uint32_t trailingDigitsCount
                                        )
{
    const uint64_t maxIssuanceAmount = UINT64_MAX - (UINT64_MAX %
            AssetFrame::getMinimumAmountFromTrailingDigits(trailingDigitsCount));
    auto creationRequest = createAssetCreationRequest(assetCode,
                                                      preIssuedSigner.
                                                      getPublicKey(),
                                                      "{}", maxIssuanceAmount,
                                                      policies, allTasks, 0);
    if (trailingDigitsCount != AssetFrame::kMaximumTrailingDigits)
    {
        creationRequest.createAssetCreationRequest().createAsset.ext.v(
                LedgerVersion::ADD_ASSET_BALANCE_PRECISION);
        creationRequest.createAssetCreationRequest().createAsset.ext.trailingDigitsCount() =
                trailingDigitsCount;
    }
    auto creationResult = applyManageAssetTx(assetOwner, 0, creationRequest);

    auto accountHelper = AccountHelper::Instance();
    auto assetOwnerFrame = accountHelper->
        loadAccount(assetOwner.key.getPublicKey(), mTestManager->getDB());
    if (assetOwnerFrame->getAccountType() == AccountType::MASTER)
        return;

    auto reviewableRequestHelper = ReviewableRequestHelper::Instance();
    auto approvingRequest = reviewableRequestHelper->loadRequest(creationResult.
                                                                 success().
                                                                 requestID,
                                                                 mTestManager->
                                                                 getDB(),
                                                                 nullptr);
    REQUIRE(approvingRequest);
    auto reviewRequetHelper = ReviewAssetRequestHelper(mTestManager);
    reviewRequetHelper.applyReviewRequestTx(root, approvingRequest->
                                            getRequestID(),
                                            approvingRequest->getHash(),
                                            approvingRequest->getType(),
                                            ReviewRequestOpAction::APPROVE, "");
}

void ManageAssetTestHelper::updateAsset(Account& assetOwner,
                                        AssetCode assetCode, Account& root,
                                        uint32_t policies)
{
    const auto updateRequest = createAssetUpdateRequest(assetCode,
                                                        "{}", policies);
    auto updateResult = applyManageAssetTx(assetOwner, 0, updateRequest);

    if (assetOwner.key.getPublicKey() == root.key.getPublicKey())
        return;

    auto reviewableRequestHelper = ReviewableRequestHelper::Instance();
    auto approvingRequest = reviewableRequestHelper->loadRequest(updateResult.
                                                                 success().
                                                                 requestID,
                                                                 mTestManager->
                                                                 getDB(),
                                                                 nullptr);
    REQUIRE(approvingRequest);
    auto reviewRequetHelper = ReviewAssetRequestHelper(mTestManager);
    reviewRequetHelper.applyReviewRequestTx(root, approvingRequest->
                                            getRequestID(),
                                            approvingRequest->getHash(),
                                            approvingRequest->getType(),
                                            ReviewRequestOpAction::APPROVE, "");
}

void ManageAssetTestHelper::changeAssetTrailingDigits(AssetCode assetCode,
                                                      uint32 trailingDigitsCount)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(
            new StorageHelperImpl(mTestManager->getDB(), nullptr));
    storageHelper->release();

    auto asset = storageHelper->getAssetHelper().mustLoadAsset(assetCode);
    asset->mEntry.data.asset().ext.v(LedgerVersion::ADD_ASSET_BALANCE_PRECISION);
    asset->setTrailingDigitsCount(trailingDigitsCount);
    storageHelper->getAssetHelper().storeChange(asset->mEntry);
}

void ManageAssetTestHelper::validateManageAssetEffect(
    ManageAssetOp::_request_t request)
{
    AssetCode assetCode;
    auto assetHelper = AssetHelperLegacy::Instance();
    switch (request.action())
    {
    case ManageAssetAction::CREATE_ASSET_CREATION_REQUEST:
        assetCode = request.createAssetCreationRequest().createAsset.code;
        break;
    case ManageAssetAction::CREATE_ASSET_UPDATE_REQUEST:
    {
        assetCode = request.createAssetUpdateRequest().updateAsset.code;
        auto assetFrame = assetHelper->loadAsset(assetCode,
                                                 mTestManager->getDB());
        REQUIRE(assetFrame);
        auto assetEntry = assetFrame->getAsset();
        REQUIRE(assetEntry.details == request.createAssetUpdateRequest().updateAsset.details);
        REQUIRE(assetEntry.policies == request.createAssetUpdateRequest().updateAsset.policies);
        break;
    }
    default:
        throw std::
            runtime_error("Unexpected manage asset action from master account");
    }
    auto assetFrame = assetHelper->loadAsset(assetCode, mTestManager->getDB());
    REQUIRE(assetFrame);
    auto balanceHelper = BalanceHelperLegacy::Instance();
    if (assetFrame->isPolicySet(AssetPolicy::BASE_ASSET))
    {
        auto systemAccounts = mTestManager->getApp().getSystemAccounts();
        for (auto systemAccount : systemAccounts)
        {
            auto balanceFrame = balanceHelper->loadBalance(systemAccount,
                                                           assetCode,
                                                           mTestManager->
                                                           getDB(), nullptr);
            REQUIRE(balanceFrame);
        }
    }
}
}
}
