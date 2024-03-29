#include <transactions/test/test_helper/ManageAccountRoleTestHelper.h>
#include <transactions/test/test_helper/ManageAccountRuleTestHelper.h>
#include "test/test_marshaler.h"
#include "TxTests.h"
#include "test/test.h"
#include "test_helper/ManageAMLAlertTestHelper.h"
#include "test_helper/IssuanceRequestHelper.h"
#include "test_helper/ManageAssetTestHelper.h"
#include "ledger/BalanceHelper.h"
#include "transactions/ManageKeyValueOpFrame.h"
#include "test_helper/ManageKeyValueTestHelper.h"
#include "test_helper/CreateAccountTestHelper.h"
#include "test_helper/ReviewAMLAlertRequestHelper.h"
#include "ledger/StorageHelper.h"

using namespace stellar;
using namespace stellar::txtest;

typedef std::unique_ptr<Application> appPtr;


TEST_CASE("Aml alert", "[tx][aml_alert]")
{
    Config const& cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);
    VirtualClock clock;
    Application::pointer appPtr = Application::create(clock, cfg);
    Application& app = *appPtr;
    app.start();
    auto testManager = TestManager::make(app);
    TestManager::upgradeToCurrentLedgerVersion(app);

    Database& db = testManager->getDB();

    auto root = Account{ getRoot(), Salt(0) };

    // helpers
    auto amlAlertHelper = ManageAMLAlertTestHelper(testManager);
    CreateAccountTestHelper createAccountTestHelper(testManager);
    ManageAccountRoleTestHelper manageAccountRoleTestHelper(testManager);
    ManageAccountRuleTestHelper manageAccountRuleTestHelper(testManager);

    uint32_t zeroTasks = 0;
    SECTION("Empty reason is not allowed")
    {
        BalanceID balanceID;
        amlAlertHelper.applyCreateAmlAlert(root, balanceID, 0, "", "", &zeroTasks, CreateAMLAlertRequestResultCode::INVALID_CREATOR_DETAILS);
    }
    SECTION("Zero amount is not allowed")
    {
        BalanceID balanceID;
        amlAlertHelper.applyCreateAmlAlert(root, balanceID, 0, "Inalid", "", &zeroTasks, CreateAMLAlertRequestResultCode::INVALID_AMOUNT);
    }
    SECTION("Balance does not exists")
    {
        BalanceID balanceID;
        amlAlertHelper.applyCreateAmlAlert(root, balanceID, 10, "Inalid", "", &zeroTasks, CreateAMLAlertRequestResultCode::BALANCE_NOT_EXIST);
    }

    auto reference = "Random reference";
    SECTION("Given valid account with balance")
    {
        auto issuanceHelper = IssuanceRequestHelper(testManager);
        const AssetCode asset = "USD";
        const uint64_t  assetType = 1;
        const uint64_t preIssuedAmount = 10000 * ONE;

        ManageKeyValueTestHelper manageKeyValueHelper(testManager);
        manageKeyValueHelper.assetOpWithoutReview();

        issuanceHelper.createAssetWithPreIssuedAmount(root, asset, preIssuedAmount, root, 6, assetType);
        ManageAssetTestHelper(testManager).updateAsset(root, asset, root, static_cast<uint32_t>(AssetPolicy::BASE_ASSET) | static_cast<uint32_t>(AssetPolicy::WITHDRAWABLE));

        AccountRuleResource assetResource(LedgerEntryType::ASSET);
        assetResource.asset().assetCode = asset;
        assetResource.asset().assetType = assetType;

        auto ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
                0, assetResource, AccountRuleAction::RECEIVE_ISSUANCE, false);
        // write this entry to DB
        auto createReceiverRuleResult = manageAccountRuleTestHelper.applyTx(
                root, ruleEntry, ManageAccountRuleAction::CREATE);

        // create account role using root as source
        auto createReceiverAccountRoleOp = manageAccountRoleTestHelper.buildCreateRoleOp(
                R"({"name":"usd_receiver"})", {createReceiverRuleResult.success().ruleID});

        auto recipientAccountRoleID = manageAccountRoleTestHelper.applyTx(
                root, createReceiverAccountRoleOp).success().roleID;

        auto account = SecretKey::random();
        createAccountTestHelper.applyTx(CreateAccountTestBuilder()
                                                .setSource(root)
                                                .setToPublicKey(account.getPublicKey())
                                                .addBasicSigner()
                                                .setRoleID(1));

        auto balance = testManager->getStorageHelper().getBalanceHelper().loadBalance(account.getPublicKey(), asset);
        REQUIRE(!!balance);
        uint32_t allTasks = 0;
        issuanceHelper.applyCreateIssuanceRequest(root, asset, preIssuedAmount, balance->getBalanceID(),
                                                  "RANDOM ISSUANCE REFERENCE", &allTasks);
        SECTION("Insufficient balance")
        {
            amlAlertHelper.applyCreateAmlAlert(root, balance->getBalanceID(), preIssuedAmount + 1, "Inalid", reference,
                                               &zeroTasks, CreateAMLAlertRequestResultCode::UNDERFUNDED);
        }
        SECTION("Mismatching balance precision and amount")
        {
            ManageAssetTestHelper(testManager).changeAssetTrailingDigits(balance->getAsset(), 0);
            amlAlertHelper.applyCreateAmlAlert(root, balance->getBalanceID(), preIssuedAmount - 1, "Inalid", reference, &zeroTasks, CreateAMLAlertRequestResultCode::INCORRECT_PRECISION);
        }
        SECTION("Autoapprove")
        {
            auto result = amlAlertHelper.applyCreateAmlAlert(root, balance->getBalanceID(), preIssuedAmount/2, "Inalid", reference,
                                               &zeroTasks,
                                               CreateAMLAlertRequestResultCode::SUCCESS);
            REQUIRE(result.success().fulfilled);
        }

        SECTION("Tasks permissions")
        {
            longstring key = ManageKeyValueOpFrame::makeAmlAlertCreateTasksKey();
            manageKeyValueHelper.setKey(key)->setUi32Value(0);
            manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);

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

            auto syndicate = Account{ SecretKey::random(), 0 };
            auto syndicatePubKey = syndicate.key.getPublicKey();
            createAccountTestHelper.applyTx(createAccountBuilder
                                                    .setToPublicKey(syndicatePubKey)
                                                    .addBasicSigner()
                                                    .setRoleID(syndicateRoleID));

            SECTION("Set tasks without permission")
            {
                amlAlertHelper.applyCreateAmlAlert(syndicate, balance->getBalanceID(), preIssuedAmount / 2, "Inalid",
                        reference, &zeroTasks,
                        CreateAMLAlertRequestResultCode::SUCCESS, // No need to check inner code
                        OperationResultCode::opNO_ROLE_PERMISSION);
            }
            SECTION("Without setting tasks")
            {
                amlAlertHelper.applyCreateAmlAlert(syndicate, balance->getBalanceID(), preIssuedAmount / 2, "Inalid",
                        reference, nullptr, CreateAMLAlertRequestResultCode::SUCCESS);
            }
        }

        SECTION("Given valid aml alert request with tasks")
        {
            uint32_t nonZeroTasks = 2;
            auto result = amlAlertHelper.applyCreateAmlAlert(root, balance->getBalanceID(), preIssuedAmount/2, "Inalid", reference,
                &nonZeroTasks,
                CreateAMLAlertRequestResultCode::SUCCESS);
            const auto requestID = result.success().requestID;

            REQUIRE_FALSE(result.success().fulfilled);

            SECTION("Reference duplication")
            {
                amlAlertHelper.applyCreateAmlAlert(root, balance->getBalanceID(), preIssuedAmount / 2, "Inalid", reference,
                        &zeroTasks,
                        CreateAMLAlertRequestResultCode::REFERENCE_DUPLICATION);
            }
            auto amlReviewHelper = ReviewAmlAlertHelper(testManager);
            SECTION("Approve")
            {
                uint32_t tasksToAdd = 0, tasksToRemove = 2;
                auto reviewResult = amlReviewHelper.applyReviewRequestTxWithTasks(root, requestID, ReviewRequestOpAction::APPROVE, "",
                        ReviewRequestResultCode::SUCCESS, &tasksToAdd, &tasksToRemove);

                REQUIRE(reviewResult.success().fulfilled);
                SECTION("Reference duplication")
                {
                    amlAlertHelper.applyCreateAmlAlert(root, balance->getBalanceID(), preIssuedAmount / 2, "Inalid", reference,
                            &zeroTasks,
                            CreateAMLAlertRequestResultCode::REFERENCE_DUPLICATION);
                }
            }
            SECTION("Reject is not allowed")
            {
                amlReviewHelper.applyReviewRequestTx(root, requestID, ReviewRequestOpAction::REJECT, "Everthing seems to be ok", ReviewRequestResultCode::REJECT_NOT_ALLOWED);
            }
            SECTION("Permanent Reject")
            {
                amlReviewHelper.applyReviewRequestTx(root, requestID, ReviewRequestOpAction::PERMANENT_REJECT, "Everthing seems to be ok");
                SECTION("Reference duplication")
                {
                    amlAlertHelper.applyCreateAmlAlert(root, balance->getBalanceID(), preIssuedAmount / 2, "Inalid", reference,
                            &zeroTasks,
                            CreateAMLAlertRequestResultCode::REFERENCE_DUPLICATION);
                }
            }
        }
    }
}