#include <transactions/test/test_helper/ManageKeyValueTestHelper.h>
#include <transactions/test/test_helper/ManageAccountRoleTestHelper.h>
#include <transactions/test/test_helper/ManageAccountRuleTestHelper.h>
#include <ledger/ReviewableRequestHelper.h>
#include "transactions/test/test_helper/CreateChangeRoleRequestTestHelper.h"
#include "test/test_marshaler.h"
#include "main/test.h"
#include "ledger/AccountHelperLegacy.h"
#include "ledger/AccountKYCHelper.h"
#include "ledger/LedgerDeltaImpl.h"
#include "bucket/BucketApplicator.h"
#include "test_helper/CreateAccountTestHelper.h"
#include "transactions/test/test_helper/ReviewChangeRoleRequestHelper.h"

using namespace stellar;
using namespace stellar::txtest;

typedef std::unique_ptr<Application> appPtr;

TEST_CASE("create KYC request", "[tx][create_change_role_request]")
{
    Config cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);

    VirtualClock clock;
    Application::pointer appPtr = Application::create(clock, cfg);
    Application &app = *appPtr;
    app.start();
    TestManager::upgradeToCurrentLedgerVersion(app);

    auto testManager = TestManager::make(app);

    auto randomSecretKey = SecretKey::random();
    auto account = Account{randomSecretKey, Salt(1)};

    auto master = Account{getRoot(), Salt(1)};

    CreateAccountTestHelper accountTestHelper(testManager);
    CreateChangeRoleTestHelper changeRoleRequestHelper(testManager);
    ManageKeyValueTestHelper manageKVHelper(testManager);
    ManageAccountRuleTestHelper manageAccountRuleTestHelper(testManager);
    ManageAccountRoleTestHelper manageAccountRoleTestHelper(testManager);
    ReviewChangeRoleRequestTestHelper reviewChangeRoleRequestHelper(testManager);

    // create new account with empty role
    AccountRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::CHANGE_ROLE);
    auto ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(0, resource, AccountRuleAction::CREATE, false);
    auto ruleID = manageAccountRuleTestHelper.applyTx(master, ruleEntry, ManageAccountRuleAction::CREATE).success().ruleID;

    auto createEmptyRoleOp = manageAccountRoleTestHelper.buildCreateRoleOp(
            R"({"name":"create_change_role_request"})", {ruleID});

    auto emptyAccountRoleID = manageAccountRoleTestHelper.applyTx(
            master, createEmptyRoleOp).success().roleID;

    auto createAccountTestBuilder = CreateAccountTestBuilder()
            .setSource(master)
            .setToPublicKey(account.key.getPublicKey())
            .addBasicSigner()
            .setRoleID(1);

    accountTestHelper.applyTx(createAccountTestBuilder);

    // add new role
    AccountRuleResource assetResource(LedgerEntryType::ASSET);
    assetResource.asset().assetType = UINT64_MAX;
    assetResource.asset().assetCode = "COOL0TOKEN";

    ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(0, assetResource, AccountRuleAction::ANY, false);
    ruleID = manageAccountRuleTestHelper.applyTx(master, ruleEntry, ManageAccountRuleAction::CREATE).success().ruleID;

    auto createTokenOwnerRoleOp = manageAccountRoleTestHelper.buildCreateRoleOp(
            R"({"name":"cool_token_owner"})", {ruleID});
    auto tokenOwnerRoleID = manageAccountRoleTestHelper.applyTx(
            master, createTokenOwnerRoleOp).success().roleID;

    longstring kycData = "{}";
    uint64 requestID = 0;
    uint32 tasks = 30;

    //make KYC_RULE key
    longstring key = ManageKeyValueOpFrame::makeChangeRoleKey(emptyAccountRoleID, tokenOwnerRoleID);
    longstring anotherKey = ManageKeyValueOpFrame::makeChangeRoleKey(1, tokenOwnerRoleID);

    SECTION("success")
    {
        //store KV record into DB
        manageKVHelper.setKey(key)->setUi32Value(tasks);
        manageKVHelper.doApply(app, ManageKVAction::PUT, true);

        manageKVHelper.setKey(anotherKey)->setUi32Value(tasks);
        manageKVHelper.doApply(app, ManageKVAction::PUT, true);

        SECTION("source master, create and approve")
        {

            auto createUpdateKYCRequestResult = changeRoleRequestHelper.applyCreateChangeRoleRequest(
                    master, requestID, account.key.getPublicKey(), tokenOwnerRoleID, kycData);

            requestID = createUpdateKYCRequestResult.success().requestID;
            auto request = ReviewableRequestHelper::Instance()->loadRequest(
                    requestID, account.key.getPublicKey(),
                    ReviewableRequestType::CHANGE_ROLE, testManager->getDB());

            reviewChangeRoleRequestHelper.applyReviewRequestTx(master, requestID, ReviewRequestOpAction::APPROVE, "");
        }
        SECTION("source master, autoApprove") {
            tasks = 0;
            auto createUpdateKYCRequestResult = changeRoleRequestHelper.applyCreateChangeRoleRequest(
                    master, 0, account.key.getPublicKey(), tokenOwnerRoleID, kycData, &tasks);

            REQUIRE(createUpdateKYCRequestResult.success().fulfilled);
        }

        SECTION("source is general, create -> reject -> update -> approve")
        {
            auto createUpdateKYCRequestResult = changeRoleRequestHelper.applyCreateChangeRoleRequest(
                    account, 0, account.key.getPublicKey(), tokenOwnerRoleID, kycData);

            requestID = createUpdateKYCRequestResult.success().requestID;
            auto request = ReviewableRequestHelper::Instance()->loadRequest(requestID,
                    account.key.getPublicKey(), ReviewableRequestType::CHANGE_ROLE,
                    testManager->getDB());

            reviewChangeRoleRequestHelper.applyReviewRequestTx(master, requestID, ReviewRequestOpAction::REJECT,
                                                            "Not enough docs for third kyc level");
            reviewChangeRoleRequestHelper.applyReviewRequestTx(master, requestID, ReviewRequestOpAction::REJECT,
                                                            "One more reject, just for fun");

            auto changeUpdateKYCRequestResult = changeRoleRequestHelper.applyCreateChangeRoleRequest(
                    account, requestID, account.key.getPublicKey(), tokenOwnerRoleID, kycData);

            reviewChangeRoleRequestHelper.applyReviewRequestTx(master, requestID, ReviewRequestOpAction::APPROVE, "");
        }
        SECTION("set the same type")
        {
            key = ManageKeyValueOpFrame::makeChangeRoleKey(1, emptyAccountRoleID);
            manageKVHelper.setKey(key)->doApply(app, ManageKVAction::PUT, true);

            changeRoleRequestHelper.applyCreateChangeRoleRequest(master, 0,
                     account.key.getPublicKey(), emptyAccountRoleID, kycData);
        }
    }

    SECTION("failed")
    {
        SECTION("kyc rule not found")
        {
            changeRoleRequestHelper.applyCreateChangeRoleRequest(account, 0,
                     account.key.getPublicKey(), tokenOwnerRoleID, kycData, nullptr,
                     CreateChangeRoleRequestResultCode::KYC_RULE_NOT_FOUND);
        }

        manageKVHelper.setKey(key)->setUi32Value(tasks);
        manageKVHelper.doApply(app, ManageKVAction::PUT, true);

        manageKVHelper.setKey(anotherKey)->setUi32Value(tasks);
        manageKVHelper.doApply(app, ManageKVAction::PUT, true);


        SECTION("double creating, request exists") {

            changeRoleRequestHelper.applyCreateChangeRoleRequest(account, 0,
                          account.key.getPublicKey(), tokenOwnerRoleID, kycData);

            changeRoleRequestHelper.applyCreateChangeRoleRequest(account, 0,
                      account.key.getPublicKey(), tokenOwnerRoleID, kycData, nullptr,
                      CreateChangeRoleRequestResultCode::REQUEST_ALREADY_EXISTS);

        }
        SECTION("updated request does not exist")
        {
            changeRoleRequestHelper.applyCreateChangeRoleRequest(account, 1408,
                      account.key.getPublicKey(), tokenOwnerRoleID, kycData, nullptr,
                      CreateChangeRoleRequestResultCode::REQUEST_DOES_NOT_EXIST);

        }
        SECTION("update pending is not allowed for user")
        {
            auto createUpdateKYCRequestResult = changeRoleRequestHelper.applyCreateChangeRoleRequest(
                    account, 0, account.key.getPublicKey(), tokenOwnerRoleID, kycData);
            requestID = createUpdateKYCRequestResult.success().requestID;
            changeRoleRequestHelper.applyCreateChangeRoleRequest(account, requestID,
                  account.key.getPublicKey(), tokenOwnerRoleID, kycData, nullptr,
                  CreateChangeRoleRequestResultCode::PENDING_REQUEST_UPDATE_NOT_ALLOWED);
        }
        SECTION("source master, create and update pending")
        {
            auto createUpdateKYCRequestResult = changeRoleRequestHelper.applyCreateChangeRoleRequest(
                    master, 0, account.key.getPublicKey(), tokenOwnerRoleID, kycData, &tasks);

            requestID = createUpdateKYCRequestResult.success().requestID;
            uint32 newTasks = 1;

            changeRoleRequestHelper.applyCreateChangeRoleRequest(master, requestID,
                  account.key.getPublicKey(), tokenOwnerRoleID, kycData, &newTasks,
                  CreateChangeRoleRequestResultCode::NOT_ALLOWED_TO_UPDATE_REQUEST);
        }
    }
}