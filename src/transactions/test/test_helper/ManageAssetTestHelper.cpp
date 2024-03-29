// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <transactions/test/TxTests.h>
#include <crypto/SHA.h>
#include "ManageAssetTestHelper.h"
#include "ledger/StorageHelperImpl.h"
#include "ledger/AccountHelper.h"
#include "ledger/AssetHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/ReviewableRequestFrame.h"
#include "ledger/ReviewableRequestHelper.h"
#include "transactions/manage_asset/ManageAssetOpFrame.h"
#include "transactions/manage_asset/RemoveAssetOpFrame.h"
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
    auto& storageHelper = mTestManager->getStorageHelper();
    auto& requestHelper = storageHelper.getReviewableRequestHelper();

    auto requestCreationResult = applyManageAssetTx(source, 0, request);
    if (requestCreationResult.success().fulfilled)
        return;
    auto requestFrame = requestHelper.
        loadRequest(requestCreationResult.success().requestID);
    auto reviewHelper = ReviewAssetRequestHelper(mTestManager);
    reviewHelper.applyReviewRequestTx(root, requestCreationResult.success().
                                          requestID,
                                      requestFrame->getHash(),
                                      requestFrame->getRequestType(),
                                      ReviewRequestOpAction::APPROVE, "");
}


TransactionFramePtr
ManageAssetTestHelper::
createRemoveAssetTx
(txtest::Account &source, AssetCode code, txtest::Account *signer)
{
    Operation op;
    op.body.type(OperationType::REMOVE_ASSET);
    auto& body = op.body.removeAssetOp();
    body.code = code;

    return TxHelper::txFromOperation(source, op, signer);
}



RemoveAssetResult ManageAssetTestHelper::applyRemoveAssetTx(txtest::Account &source,
                                                                        AssetCode code, txtest::Account *signer,
                                                                        RemoveAssetResultCode expectedResult,
                                                                        OperationResultCode expectedOpResult)
{
    auto& assetHelper = mTestManager->getStorageHelper().getAssetHelper();
    Database& db = mTestManager->getDB();

    TransactionFramePtr txFrame;
    txFrame = createRemoveAssetTx(source, code, signer);

    mTestManager->applyCheck(txFrame);
    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];
    REQUIRE(opResult.code() == expectedOpResult);
    if (opResult.code() != OperationResultCode::opINNER)
    {
        return RemoveAssetResult();
    }

    auto actualResultCode = RemoveAssetOpFrame::getInnerCode(opResult);

    REQUIRE(expectedResult == actualResultCode);

    if (actualResultCode != RemoveAssetResultCode::SUCCESS)
    {
        REQUIRE(assetHelper.existActive(code));
    }
    else
    {
        REQUIRE_FALSE(assetHelper.existActive(code));
        REQUIRE(assetHelper.exists(code));
    }

    return opResult.tr().removeAssetResult();
}

ManageAssetResult ManageAssetTestHelper::applyManageAssetTx(
    Account& source, uint64_t requestID, ManageAssetOp::_request_t request,
    ManageAssetResultCode expectedResult, OperationResultCode expectedOpCode)
{
    auto& storageHelper = mTestManager->getStorageHelper();
    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    auto reviewableRequestCountBeforeTx = requestHelper.countObjects();
    auto requestBeforeTx = requestHelper.loadRequest(requestID);

    auto txFrame = createManageAssetTx(source, requestID, request);

    mTestManager->applyCheck(txFrame);
    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];
    REQUIRE(opResult.code() == expectedOpCode);
    if (opResult.code() != OperationResultCode::opINNER)
    {
        return ManageAssetResult();
    }
    auto actualResultCode = ManageAssetOpFrame::getInnerCode(opResult);
    REQUIRE(actualResultCode == expectedResult);

    uint64 reviewableRequestCountAfterTx = requestHelper.countObjects();
    if (expectedResult != ManageAssetResultCode::SUCCESS)
    {
        REQUIRE(reviewableRequestCountBeforeTx == reviewableRequestCountAfterTx);
        return ManageAssetResult{};
    }

    auto& accountHelper = storageHelper.getAccountHelper();
    auto sourceFrame = accountHelper.loadAccount(source.key.getPublicKey());
    auto manageAssetResult = opResult.tr().manageAssetResult();

    auto& assetHelper = storageHelper.getAssetHelper();
    auto& balanceHelper = storageHelper.getBalanceHelper();

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

    auto requestAfterTx = requestHelper.loadRequest(manageAssetResult
                                                        .success().
        requestID);
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
            if (requestID == 0)
            {
                REQUIRE(requestAfterTx->getRequestEntry().body.assetCreationRequest() ==
                        request.createAssetCreationRequest().createAsset);

            }
            break;
        case ManageAssetAction::CREATE_ASSET_UPDATE_REQUEST:
            if (requestID == 0)
            {
                REQUIRE(requestAfterTx->getRequestEntry().body.assetUpdateRequest() ==
                        request.createAssetUpdateRequest().updateAsset);
            }
            break;
        default:
            throw std::runtime_error("Unexpected action for manage asset");
    }

    return manageAssetResult;
}

Operation
ManageAssetTestHelper::createManageAssetOp(Account& source, uint64_t requestID, ManageAssetOp::_request_t request)
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
    std::string creatorDetails,
    uint64_t maxIssuanceAmount,
    uint32_t policies,
    uint32_t *allTasks,
    uint64_t initialPreissuanceAmount,
    uint32_t trailingDigitsCount,
    uint64_t assetType
)
{
    ManageAssetOp::_request_t request;
    request.action(ManageAssetAction::CREATE_ASSET_CREATION_REQUEST);
    AssetCreationRequest& assetCreationRequest = request.createAssetCreationRequest().createAsset;
    assetCreationRequest.code = code;
    assetCreationRequest.creatorDetails = creatorDetails;
    assetCreationRequest.maxIssuanceAmount = maxIssuanceAmount;
    assetCreationRequest.policies = policies;
    assetCreationRequest.preissuedAssetSigner = preissuedAssetSigner;
    assetCreationRequest.initialPreissuedAmount = initialPreissuanceAmount;
    assetCreationRequest.type = assetType;
    assetCreationRequest.trailingDigitsCount = trailingDigitsCount;
    if (allTasks)
    {
        request.createAssetCreationRequest().allTasks.activate() = *allTasks;
    }
    return request;
}

ManageAssetOp::_request_t ManageAssetTestHelper::createAssetUpdateRequest(
    AssetCode code,
    std::string creatorDetails,
    uint32_t policies,
    uint32_t *allTasks
)
{
    ManageAssetOp::_request_t request;
    request.action(ManageAssetAction::CREATE_ASSET_UPDATE_REQUEST);
    AssetUpdateRequest& assetUpdateRequest = request.createAssetUpdateRequest().updateAsset;
    assetUpdateRequest.code = code;
    assetUpdateRequest.creatorDetails = creatorDetails;
    assetUpdateRequest.policies = policies;
    if (allTasks)
    {
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
    Account& account, AssetCode code, AccountID accountID)
{
    ManageAssetOp::_request_t request;
    request.action(ManageAssetAction::CHANGE_PREISSUED_ASSET_SIGNER);
    request.changePreissuedSigner().accountID = accountID;
    request.changePreissuedSigner().code = code;

    DecoratedSignature sig;
    sig.signature = account.key.sign(Hash(sha256(std::string(code) + ":" + PubKeyUtils::toStrKey(accountID))));
    sig.hint = PubKeyUtils::getHint(account.key.getPublicKey());
    request.changePreissuedSigner().signature = sig;

    return request;

}

void ManageAssetTestHelper::createAsset(Account& assetOwner,
                                        SecretKey& preIssuedSigner,
                                        AssetCode assetCode, Account& root,
                                        uint32_t policies,
                                        uint32_t *allTasks,
                                        uint32_t trailingDigitsCount,
                                        uint64_t assetType, uint64_t maxIssuance
)
{
    const uint64_t maxIssuanceAmount = maxIssuance - (maxIssuance %
                                                      AssetFrame::getMinimumAmountFromTrailingDigits(trailingDigitsCount));
    auto creationRequest = createAssetCreationRequest(assetCode,
                                                      preIssuedSigner.
                                                          getPublicKey(),
                                                      "{}", maxIssuanceAmount,
                                                      policies, allTasks, 0,
                                                      trailingDigitsCount,
                                                      assetType);
    auto creationResult = applyManageAssetTx(assetOwner, 0, creationRequest);

    auto& storageHelper = mTestManager->getStorageHelper();
    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    auto& accountHelper = storageHelper.getAccountHelper();

    auto assetOwnerFrame = accountHelper.
        loadAccount(assetOwner.key.getPublicKey());
    if (creationResult.code() == ManageAssetResultCode::SUCCESS
        && creationResult.success().fulfilled)
        return;

    auto approvingRequest = requestHelper.loadRequest(creationResult.
        success().
        requestID);
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

    if (updateResult.success().fulfilled)
        return;

    auto& storageHelper = mTestManager->getStorageHelper();
    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    auto approvingRequest = requestHelper.loadRequest(updateResult.
        success().
        requestID);

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
    asset->setTrailingDigitsCount(trailingDigitsCount);
    storageHelper->getAssetHelper().storeChange(asset->mEntry);
}

void ManageAssetTestHelper::validateManageAssetEffect(
    ManageAssetOp::_request_t request)
{
    auto& storageHelper = mTestManager->getStorageHelper();

    AssetCode assetCode;
    auto& assetHelper = storageHelper.getAssetHelper();
    switch (request.action())
    {
        case ManageAssetAction::CREATE_ASSET_CREATION_REQUEST:
            assetCode = request.createAssetCreationRequest().createAsset.code;
            break;
        case ManageAssetAction::CREATE_ASSET_UPDATE_REQUEST:
        {
            assetCode = request.createAssetUpdateRequest().updateAsset.code;
            auto assetFrame = assetHelper.loadActiveAsset(assetCode);
            REQUIRE(assetFrame);
            auto assetEntry = assetFrame->getAsset();
            REQUIRE(assetEntry.details == request.createAssetUpdateRequest().updateAsset.creatorDetails);
            REQUIRE(assetEntry.policies == request.createAssetUpdateRequest().updateAsset.policies);
            break;
        }
        default:
            throw std::
            runtime_error("Unexpected manage asset action from master account");
    }
    auto assetFrame = assetHelper.loadActiveAsset(assetCode);
    REQUIRE(assetFrame);
    auto& balanceHelper = storageHelper.getBalanceHelper();
    if (assetFrame->isPolicySet(AssetPolicy::BASE_ASSET))
    {
        auto systemAccount = mTestManager->getApp().getAdminID();

        auto balanceFrame = balanceHelper.loadBalance(systemAccount,
                                                      assetCode);
        REQUIRE(balanceFrame);

    }
}
}
}
