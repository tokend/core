#include <transactions/test/test_helper/ManageKeyValueTestHelper.h>
#include <transactions/test/test_helper/ManageAccountRoleTestHelper.h>
#include <transactions/test/test_helper/ManageAccountRuleTestHelper.h>
#include <ledger/ReviewableRequestHelper.h>
#include "transactions/test/test_helper/CreateChangeRoleRequestTestHelper.h"
#include "test/test_marshaler.h"
#include "test/test.h"
#include "ledger/AccountHelperLegacy.h"
#include "ledger/AccountKYCHelper.h"
#include "ledger/LedgerDeltaImpl.h"
#include "bucket/BucketApplicator.h"
#include "test_helper/CreateAccountTestHelper.h"
#include "test_helper/KYCRecoveryTestHelper.h"
#include "transactions/test/test_helper/ReviewKYCRecoveryRequestHelper.h"

using namespace stellar;
using namespace stellar::txtest;

typedef std::unique_ptr<Application> appPtr;

TEST_CASE("kyc recovery", "[tx][kyc_recovery]")
{
    Config cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);

    VirtualClock clock;
    Application::pointer appPtr = Application::create(clock, cfg);
    Application& app = *appPtr;
    app.start();
    TestManager::upgradeToCurrentLedgerVersion(app);

    auto testManager = TestManager::make(app);

    auto randomSecretKey = SecretKey::random();
    auto account = Account{randomSecretKey, Salt(1)};

    auto master = Account{getRoot(), Salt(1)};

    CreateAccountTestHelper accountTestHelper(testManager);
    CreateKYCRecoveryRequestTestHelper createKycRecoveryRequestTestHelper(testManager);
    InitiateKYCRecoveryTestHelper initKycRecoveryTestHelper(testManager);
    ManageKeyValueTestHelper manageKVHelper(testManager);
    ReviewKycRecoveryHelper reviewKycRecoveryHelper(testManager);

    auto createAccountTestBuilder = CreateAccountTestBuilder()
        .setSource(master)
        .setToPublicKey(account.key.getPublicKey())
        .addBasicSigner()
        .setRoleID(1);

    accountTestHelper.applyTx(createAccountTestBuilder);

    auto recoverySigner = SecretKey::random();
    AccountID targetAccountID = account.key.getPublicKey();
    auto initKYCRecovery = InitiateKYCRecoveryTestBuilder()
        .setTargetAccount(targetAccountID)
        .setSigner(recoverySigner.getPublicKey())
        .setSource(master);

    SECTION("Recovery not allowed")
    {
        initKycRecoveryTestHelper.applyTx(initKYCRecovery
                                              .setResultCode(InitiateKYCRecoveryResultCode::RECOVERY_NOT_ALLOWED)
                                              .setTxResultCode(TransactionResultCode::txFAILED));
    }

    longstring kycEnableKey = ManageKeyValueOpFrame::makeKYCRecoveryKey();
    manageKVHelper.setKey(kycEnableKey)->setUi32Value(1);
    manageKVHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);

    SECTION("Target not found")
    {

        auto nonExistingAccount = Account{SecretKey::random(), Salt(1)};
        AccountID accID = nonExistingAccount.key.getPublicKey();

        initKycRecoveryTestHelper.applyTx(initKYCRecovery
                                              .setTargetAccount(accID)
                                              .setOperationResultCode(OperationResultCode::opNO_ENTRY)
                                              .setTxResultCode(TransactionResultCode::txFAILED));

    }

    SECTION("Recovery signer role not found")
    {
        initKycRecoveryTestHelper.applyTx(initKYCRecovery
                                              .setResultCode(InitiateKYCRecoveryResultCode::RECOVERY_SIGNER_ROLE_NOT_FOUND)
                                              .setTxResultCode(TransactionResultCode::txFAILED));
    }

    longstring signerRoleKey = ManageKeyValueOpFrame::makeKYCRecoverySignerRoleKey();
    manageKVHelper.setKey(signerRoleKey)->setUi64Value(1);
    manageKVHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);

    SECTION("Successful init")
    {
        initKycRecoveryTestHelper.applyTx(initKYCRecovery);
    }

    SECTION("KYC recovery request")
    {
        auto signer = SecretKey::random();
        UpdateSignerData createSignerData;
        createSignerData.publicKey = signer.getPublicKey();
        createSignerData.roleID = 1;
        createSignerData.weight = 1000;
        createSignerData.identity = 1;
        createSignerData.details = "{}";

        auto createKYCRecoveryReqBuilder = CreateKYCRecoveryRequestTestBuilder()
            .setTargetAccount(targetAccountID)
            .addSignerData(createSignerData)
            .setSource(master);

        SECTION("kyc recovery tasks not found")
        {
            createKycRecoveryRequestTestHelper.applyTx(createKYCRecoveryReqBuilder
                                                           .setResultCode(CreateKYCRecoveryRequestResultCode::KYC_RECOVERY_TASKS_NOT_FOUND)
                                                           .setTxResultCode(TransactionResultCode::txFAILED));
        }

        longstring kycRecoveryTasksKey = ManageKeyValueOpFrame::makeCreateKYCRecoveryTasksKey();
        manageKVHelper.setKey(kycRecoveryTasksKey)->setUi32Value(1);
        manageKVHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);

        SECTION("No signer data")
        {
            createKycRecoveryRequestTestHelper.applyTx(createKYCRecoveryReqBuilder
                                                           .clearSignerData()
                                                           .setResultCode(CreateKYCRecoveryRequestResultCode::NO_SIGNER_DATA)
                                                           .setTxResultCode(TransactionResultCode::txFAILED));
        }

        SECTION("Signer duplication")
        {
            createKycRecoveryRequestTestHelper.applyTx(createKYCRecoveryReqBuilder
                                                           .addSignerData(createSignerData)
                                                           .setResultCode(CreateKYCRecoveryRequestResultCode::SIGNER_DUPLICATION)
                                                           .setTxResultCode(TransactionResultCode::txFAILED));
        }

        SECTION("Invalid weight")
        {
            createSignerData.weight = 1200;
            createKycRecoveryRequestTestHelper.applyTx(createKYCRecoveryReqBuilder
                                                           .clearSignerData()
                                                           .addSignerData(createSignerData)
                                                           .setResultCode(CreateKYCRecoveryRequestResultCode::INVALID_WEIGHT)
                                                           .setTxResultCode(TransactionResultCode::txFAILED));
        }

        SECTION("Target not found")
        {
            auto nonExistingAccount = Account{SecretKey::random(), Salt(1)};
            AccountID accID = nonExistingAccount.key.getPublicKey();

            createKycRecoveryRequestTestHelper.applyTx(createKYCRecoveryReqBuilder
                                                           .setTargetAccount(accID)
                                                           .setResultCode(CreateKYCRecoveryRequestResultCode::TARGET_ACCOUNT_NOT_FOUND)
                                                           .setTxResultCode(TransactionResultCode::txFAILED));
        }
        SECTION("Not allowed again")
        {
            manageKVHelper.setKey(ManageKeyValueOpFrame::makeKYCRecoveryKey());
            manageKVHelper.doApply(testManager->getApp(), ManageKVAction::REMOVE, true);

            createKycRecoveryRequestTestHelper.applyTx(createKYCRecoveryReqBuilder
                                                           .setResultCode(CreateKYCRecoveryRequestResultCode::RECOVERY_NOT_ALLOWED)
                                                           .setTxResultCode(TransactionResultCode::txFAILED));
        }

        SECTION("Autoapprove")
        {
            longstring kycRecoveryTasksKey = ManageKeyValueOpFrame::makeCreateKYCRecoveryTasksKey();
            manageKVHelper.setKey(kycRecoveryTasksKey)->setUi32Value(0);
            manageKVHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);

            auto createRecoveryResult = createKycRecoveryRequestTestHelper.applyTx(createKYCRecoveryReqBuilder);
            REQUIRE(createRecoveryResult.success().fulfilled);
        }
        SECTION("Successfully create")
        {
            auto createRecoveryResult = createKycRecoveryRequestTestHelper.applyTx(createKYCRecoveryReqBuilder);
            auto requestID = createRecoveryResult.success().requestID;
            REQUIRE_FALSE(createRecoveryResult.success().fulfilled);
            SECTION("Request already exists")
            {
                createKycRecoveryRequestTestHelper.applyTx(createKYCRecoveryReqBuilder
                                                               .setResultCode(CreateKYCRecoveryRequestResultCode::REQUEST_ALREADY_EXISTS)
                                                               .setTxResultCode(TransactionResultCode::txFAILED));
            }
            SECTION("Try to update someones request")
            {
                createKycRecoveryRequestTestHelper.applyTx(createKYCRecoveryReqBuilder
                                                               .setRequestID(requestID)
                                                               .setSource(master)
                                                               .setResultCode(CreateKYCRecoveryRequestResultCode::NOT_ALLOWED_TO_UPDATE_REQUEST)
                                                               .setTxResultCode(TransactionResultCode::txFAILED));
            }

            SECTION("Try to set tasks on update")
            {
                uint32_t tasks = 1;
                createKycRecoveryRequestTestHelper.applyTx(createKYCRecoveryReqBuilder
                                                               .setRequestID(requestID)
                                                               .setSource(account)
                                                               .setTasks(&tasks)
                                                               .setResultCode(CreateKYCRecoveryRequestResultCode::NOT_ALLOWED_TO_SET_TASKS_ON_UPDATE)
                                                               .setTxResultCode(TransactionResultCode::txFAILED));
            }

            SECTION("Initiate another kyc recovery and create another request")
            {
                initKycRecoveryTestHelper.applyTx(initKYCRecovery);
                auto req = ReviewableRequestHelper::Instance()->loadRequest(requestID, testManager->getDB());
                REQUIRE_FALSE(req);
                auto createRecoveryResult = createKycRecoveryRequestTestHelper.applyTx(createKYCRecoveryReqBuilder);
                REQUIRE_FALSE(createRecoveryResult.success().fulfilled);
            }

            SECTION("Review")
            {
                uint32_t tasksToAdd = 2, tasksToRemove = 1;
                auto request = ReviewableRequestHelper::Instance()->loadRequest(requestID, testManager->getDB());
                REQUIRE(request);
                reviewKycRecoveryHelper.applyReviewRequestTxWithTasks(master, requestID, request->getHash(),
                    ReviewableRequestType::KYC_RECOVERY, ReviewRequestOpAction::APPROVE, "", ReviewRequestResultCode::SUCCESS,
                    &tasksToAdd, &tasksToRemove);
                tasksToAdd = 0;
                tasksToRemove = 2;
                request = ReviewableRequestHelper::Instance()->loadRequest(requestID, testManager->getDB());
                REQUIRE(request);
                auto reviewResult = reviewKycRecoveryHelper.applyReviewRequestTxWithTasks(master, requestID, request->getHash(),
                    ReviewableRequestType::KYC_RECOVERY, ReviewRequestOpAction::APPROVE, "", ReviewRequestResultCode::SUCCESS,
                    &tasksToAdd, &tasksToRemove);

                REQUIRE(reviewResult.success().fulfilled);
            }


        }

    }
}
