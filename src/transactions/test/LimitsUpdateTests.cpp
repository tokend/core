// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ledger/StorageHelper.h"
#include "transactions/test/test_helper/ManageLimitsTestHelper.h"
#include "test/test.h"
#include "TxTests.h"
#include "crypto/SHA.h"
#include "test_helper/CreateAccountTestHelper.h"
#include "test_helper/IssuanceRequestHelper.h"
#include "test_helper/LimitsUpdateRequestHelper.h"
#include "test_helper/ReviewLimitsUpdateRequestHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "test/test_marshaler.h"
#include "transactions/test/test_helper/ManageAccountRuleTestHelper.h"
#include "transactions/test/test_helper/ManageAccountRoleTestHelper.h"
#include "transactions/test/test_helper/ManageKeyValueTestHelper.h"

using namespace stellar;
using namespace stellar::txtest;

typedef std::unique_ptr<Application> appPtr;

TEST_CASE("limits update", "[tx][limits_update]")
{
    Config const& cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);
    VirtualClock clock;
    Application::pointer appPtr = Application::create(clock, cfg);
    Application& app = *appPtr;
    app.start();
    auto testManager = TestManager::make(app);
    auto& db = testManager->getDB();

    upgradeToCurrentLedgerVersion(app);

    //Helpers
    auto& storageHelper = testManager->getStorageHelper();
    auto& requestHelper = storageHelper.getReviewableRequestHelper();

    auto root = Account{getRoot(), Salt(0)};
    auto createAccountTestHelper = CreateAccountTestHelper(testManager);
    auto limitsUpdateRequestHelper = LimitsUpdateRequestHelper(testManager);
    auto reviewLimitsUpdateHelper = ReviewLimitsUpdateRequestHelper(testManager);
    auto manageLimitsTestHelper = ManageLimitsTestHelper(testManager);

    // create requestor
    auto requestor = Account{SecretKey::random(), Salt(0)};
    AccountID requestorID = requestor.key.getPublicKey();
    createAccountTestHelper.applyCreateAccountTx(root, requestorID, 1);
    auto issuanceHelper = IssuanceRequestHelper(testManager);

    uint64_t preIssuedAmount = 10*ONE;

    AssetCode asset = "USD";
    ManageKeyValueTestHelper manageKeyValueHelper(testManager);
    longstring key = ManageKeyValueOpFrame::makeIssuanceTasksKey(asset);
    manageKeyValueHelper.setKey(key)->setUi32Value(0);
    manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);

    key = ManageKeyValueOpFrame::makePreIssuanceTasksKey(asset);
    manageKeyValueHelper.setKey(key)->setUi32Value(0);
    manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);

    key = ManageKeyValueOpFrame::makeAssetCreateTasksKey();
    manageKeyValueHelper.setKey(key)->setUi32Value(0);
    manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);
    issuanceHelper.createAssetWithPreIssuedAmount(root, asset, preIssuedAmount/3*2, root, AssetFrame::kMaximumTrailingDigits, 1, preIssuedAmount);


    // set default limits for review request
    reviewLimitsUpdateHelper.initializeLimits(requestorID, asset);

    // prepare data for request
    std::string documentData = "{}";


    SECTION("with tasks")
    {
        uint32_t allTasks = 2, tasksToAdd = 0, tasksToRemove = 2;
        auto limitsUpdateRequest = limitsUpdateRequestHelper.createLimitsUpdateRequest(documentData);
        auto limitsUpdateResult = limitsUpdateRequestHelper.applyCreateLimitsUpdateRequest(requestor,
                                                                                           limitsUpdateRequest, &allTasks,
                                                                                           nullptr,
                                                                                           CreateManageLimitsRequestResultCode::SUCCESS);

        REQUIRE_FALSE(limitsUpdateResult.success().fulfilled);

        SECTION("Happy path")
        {
            SECTION("Approve")
            {
                auto request = requestHelper.loadRequest(limitsUpdateResult.success().manageLimitsRequestID);
                REQUIRE(request);
                auto reviewResult = reviewLimitsUpdateHelper.applyReviewRequestTxWithTasks(root, limitsUpdateResult.success().manageLimitsRequestID,
                                                                                           request->getHash(),
                                                                                           request->getRequestType(),
                                                                                           ReviewRequestOpAction::APPROVE, "",
                                                                                           ReviewRequestResultCode::SUCCESS,
                                                                                           &tasksToAdd,
                                                                                           &tasksToRemove);

                REQUIRE(reviewResult.success().fulfilled);
            }

            SECTION("No asset")
            {
                reviewLimitsUpdateHelper.initializeLimits(requestorID, "asset");

                auto request = requestHelper.loadRequest(limitsUpdateResult.success().manageLimitsRequestID);
                REQUIRE(request);
                auto reviewResult = reviewLimitsUpdateHelper.applyReviewRequestTxWithTasks(root, limitsUpdateResult.success().manageLimitsRequestID,
                                                                                           request->getHash(),
                                                                                           request->getRequestType(),
                                                                                           ReviewRequestOpAction::APPROVE, "",
                                                                                           ReviewRequestResultCode::ASSET_DOES_NOT_EXISTS,
                                                                                           &tasksToAdd,
                                                                                           &tasksToRemove);

            }
            SECTION("Reject")
            {
                reviewLimitsUpdateHelper.applyReviewRequestTx(root, limitsUpdateResult.success().manageLimitsRequestID,
                                                              ReviewRequestOpAction::REJECT, "Invalid document");
            }
            SECTION("Permanent reject")
            {
                reviewLimitsUpdateHelper.applyReviewRequestTx(root, limitsUpdateResult.success().manageLimitsRequestID,
                                                              ReviewRequestOpAction::PERMANENT_REJECT,
                                                              "Invalid document");

            }
            SECTION("Approve for account with limits")
            {
                auto accountWithLimits = Account{SecretKey::random(), Salt(0)};
                AccountID accountWithoutLimitsID = accountWithLimits.key.getPublicKey();
                createAccountTestHelper.applyCreateAccountTx(root, accountWithoutLimitsID, 1);
                ManageLimitsOp manageLimitsOp;
                manageLimitsOp.details.action(ManageLimitsAction::CREATE);
                manageLimitsOp.details.limitsCreateDetails().accountID.activate() = accountWithoutLimitsID;
                manageLimitsOp.details.limitsCreateDetails().assetCode = "USD";
                manageLimitsOp.details.limitsCreateDetails().statsOpType = StatsOpType::PAYMENT_OUT;
                manageLimitsOp.details.limitsCreateDetails().isConvertNeeded = false;
                manageLimitsOp.details.limitsCreateDetails().dailyOut = 10;
                manageLimitsOp.details.limitsCreateDetails().weeklyOut = 20;
                manageLimitsOp.details.limitsCreateDetails().monthlyOut = 30;
                manageLimitsOp.details.limitsCreateDetails().annualOut = 50;
                manageLimitsTestHelper.applyManageLimitsTx(root, manageLimitsOp);

                std::string documentDataOfAccountWithLimits = "{\n \"a\": \"I have a lot of money\" \n}";

                limitsUpdateRequest = limitsUpdateRequestHelper.createLimitsUpdateRequest(
                    documentDataOfAccountWithLimits);
                limitsUpdateResult = limitsUpdateRequestHelper.applyCreateLimitsUpdateRequest(accountWithLimits,
                                                                                              limitsUpdateRequest,
                                                                                              &allTasks, nullptr,
                                                                                              CreateManageLimitsRequestResultCode::SUCCESS);

                REQUIRE_FALSE(limitsUpdateResult.success().fulfilled);
                auto request = requestHelper.loadRequest(limitsUpdateResult.success().manageLimitsRequestID);
                REQUIRE(request);
                auto reviewResult = reviewLimitsUpdateHelper.applyReviewRequestTxWithTasks(root, limitsUpdateResult.success().manageLimitsRequestID,
                                                                                           request->getHash(),
                                                                                           request->getRequestType(),
                                                                                           ReviewRequestOpAction::APPROVE, "",
                                                                                           ReviewRequestResultCode::SUCCESS,
                                                                                           &tasksToAdd,
                                                                                           &tasksToRemove);
            }
            SECTION("Update limits update request")
            {
                std::string newDocumentData = "{\n \"a\": \"New document data\" \n}";
                limitsUpdateRequest.creatorDetails = newDocumentData;
                uint64_t limitsUpdateRequestID = limitsUpdateResult.success().manageLimitsRequestID;
                limitsUpdateResult = limitsUpdateRequestHelper.applyCreateLimitsUpdateRequest(requestor,
                                                                                              limitsUpdateRequest,
                                                                                              nullptr,
                                                                                              &limitsUpdateRequestID,
                                                                                              CreateManageLimitsRequestResultCode::SUCCESS);
            }
        }
        uint64_t requestID = 0;

        SECTION("Invalid details")
        {
            limitsUpdateRequest.creatorDetails = "Some document data, huge data, very huge data to check convert to string64"
                                                 " when get reference to write to database information about request";
            limitsUpdateResult = limitsUpdateRequestHelper.applyCreateLimitsUpdateRequest(requestor,
                                                                                          limitsUpdateRequest, nullptr,
                                                                                          &requestID,
                                                                                          CreateManageLimitsRequestResultCode::INVALID_CREATOR_DETAILS);
        }

        SECTION("Update non existing request")
        {
            requestID = 42;
            limitsUpdateResult = limitsUpdateRequestHelper.applyCreateLimitsUpdateRequest(requestor,
                                                                                          limitsUpdateRequest, nullptr,
                                                                                          &requestID,
                                                                                          CreateManageLimitsRequestResultCode::MANAGE_LIMITS_REQUEST_NOT_FOUND);

        }

        SECTION("Create same request for second time")
        {
            limitsUpdateResult = limitsUpdateRequestHelper.applyCreateLimitsUpdateRequest(requestor,
                                                                                          limitsUpdateRequest, nullptr,
                                                                                          &requestID,
                                                                                          CreateManageLimitsRequestResultCode::MANAGE_LIMITS_REQUEST_REFERENCE_DUPLICATION);
        }
        SECTION("Approve and create same request for second time")
        {
            auto request = requestHelper.loadRequest(limitsUpdateResult.success().manageLimitsRequestID);
            REQUIRE(request);
            auto reviewResult = reviewLimitsUpdateHelper.applyReviewRequestTxWithTasks(root, limitsUpdateResult.success().manageLimitsRequestID,
                                                                                       request->getHash(),
                                                                                       request->getRequestType(),
                                                                                       ReviewRequestOpAction::APPROVE, "",
                                                                                       ReviewRequestResultCode::SUCCESS,
                                                                                       &tasksToAdd,
                                                                                       &tasksToRemove);

            limitsUpdateResult = limitsUpdateRequestHelper.applyCreateLimitsUpdateRequest(requestor,
                                                                                          limitsUpdateRequest, nullptr,
                                                                                          &requestID,
                                                                                          CreateManageLimitsRequestResultCode::MANAGE_LIMITS_REQUEST_REFERENCE_DUPLICATION);
        }
    }
    SECTION("Tasks permissions")
    {
        longstring key = ManageKeyValueOpFrame::makeLimitsUpdateTasksKey();
        ManageKeyValueTestHelper manageKeyValueHelper(testManager);
        manageKeyValueHelper.setKey(key)->setUi32Value(2);
        manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);

        ManageAccountRuleTestHelper manageAccountRuleTestHelper(testManager);
        ManageAccountRoleTestHelper manageAccountRoleTestHelper(testManager);

        AccountRuleResource txResource(LedgerEntryType::TRANSACTION);
        auto txRuleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(0,
                                                                              txResource, AccountRuleAction::SEND, false);
        auto txRuleId = manageAccountRuleTestHelper.applyTx(root,
                                                            txRuleEntry, ManageAccountRuleAction::CREATE).success().ruleID;

        AccountRuleResource reviewableRequestResource(LedgerEntryType::REVIEWABLE_REQUEST);
        reviewableRequestResource.reviewableRequest().details.requestType(ReviewableRequestType::ANY);
        auto revReqRuleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(0,
                                                                                  reviewableRequestResource, AccountRuleAction::CREATE, false);
        auto revReqRuleId = manageAccountRuleTestHelper.applyTx(root,
                                                                revReqRuleEntry, ManageAccountRuleAction::CREATE).success().ruleID;

        auto createSyndicateRoleOp = manageAccountRoleTestHelper.buildCreateRoleOp("{}",
                                                                                   {revReqRuleId, txRuleId});
        auto syndicateRoleID = manageAccountRoleTestHelper.applyTx(root, createSyndicateRoleOp).success().roleID;

        auto createAccountBuilder = CreateAccountTestBuilder()
            .setSource(root);

        auto syndicate = Account{SecretKey::random(), 0};
        auto syndicatePubKey = syndicate.key.getPublicKey();
        createAccountTestHelper.applyTx(createAccountBuilder
                                            .setToPublicKey(syndicatePubKey)
                                            .addBasicSigner()
                                            .setRoleID(syndicateRoleID));

        SECTION("Set tasks without permission")
        {
            uint32_t zeroTasks = 0;
            auto limitsUpdateRequest = limitsUpdateRequestHelper.createLimitsUpdateRequest(documentData);
            auto limitsUpdateResult = limitsUpdateRequestHelper.applyCreateLimitsUpdateRequest(syndicate,
                                                                                               limitsUpdateRequest, &zeroTasks, nullptr,
                                                                                               CreateManageLimitsRequestResultCode::SUCCESS, // No need to check inner code
                                                                                               OperationResultCode::opNO_ROLE_PERMISSION);
        }
        SECTION("Without setting tasks")
        {
            auto limitsUpdateRequest = limitsUpdateRequestHelper.createLimitsUpdateRequest(documentData);
            auto limitsUpdateResult = limitsUpdateRequestHelper.applyCreateLimitsUpdateRequest(syndicate,
                                                                                               limitsUpdateRequest, nullptr, nullptr, CreateManageLimitsRequestResultCode::SUCCESS);
        }
    }
}
