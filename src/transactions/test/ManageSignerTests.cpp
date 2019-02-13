#include <ledger/SignerRuleFrame.h>
#include "transactions/test/test_helper/ManageSignerRoleTestHelper.h"
#include "transactions/test/test_helper/ManageSignerRuleTestHelper.h"
#include "transactions/test/test_helper/ManageSignerTestHelper.h"
#include "TxTests.h"
#include "crypto/SHA.h"
#include "main/test.h"
#include "test/test_marshaler.h"

using namespace stellar;
using namespace stellar::txtest;

TEST_CASE("Signer tests", "[tx][manage_signer]")
{
    Config const& cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);

    VirtualClock clock;
    Application::pointer appPtr = Application::create(clock, cfg);
    Application& app = *appPtr;
    app.start();
    auto testManager = TestManager::make(app);
    TestManager::upgradeToCurrentLedgerVersion(app);

    // set up world
    auto master = Account{getRoot(), Salt(1)};
    uint64_t ownerSignerRoleID = 1;

    ManageSignerTestHelper manageSignerTestHelper(testManager);
    ManageSignerRoleTestHelper manageSignerRoleTestHelper(testManager);
    ManageSignerRuleTestHelper manageSignerRuleTestHelper(testManager);

    SECTION("Create operational signer")
    {
        // create operational signer role
        std::vector<uint64> ruleIDs{ownerSignerRoleID};

        auto createSignerRoleOp = manageSignerRoleTestHelper.buildCreateRoleOp(
                R"({"from": "manage signer test"})", ruleIDs, false);

        auto result = manageSignerRoleTestHelper.applyTx(master, createSignerRoleOp);
        auto roleID = result.success().roleID;

        // create signer
        auto signerKey = SecretKey::random();
        auto signer = Account{signerKey, Salt(3)};
        auto createSignerOp = manageSignerTestHelper.buildCreateOp(
                signerKey.getPublicKey(), SignerRuleFrame::threshold, 300, roleID);
        manageSignerTestHelper.applyTx(master, createSignerOp);

        SECTION("operational try manage default rules")
        {
            SECTION("create")
            {
                auto op = manageSignerRuleTestHelper.buildCreateRuleOp(
                        SignerRuleResource(LedgerEntryType::FEE), "manage", true, true, true);
                manageSignerRuleTestHelper.applyTx(master, op,
                                                   ManageSignerRuleResultCode::SUCCESS,
                                                   OperationResultCode::opBAD_AUTH,
                                                   TransactionResultCode::txFAILED, &signer);
            }

            SECTION("update")
            {
                auto op = manageSignerRuleTestHelper.buildUpdateRoleOp(2,
                        SignerRuleResource(LedgerEntryType::FEE), "manage", false, false);
                manageSignerRuleTestHelper.applyTx(master, op,
                                                   ManageSignerRuleResultCode::SUCCESS,
                                                   OperationResultCode::opBAD_AUTH,
                                                   TransactionResultCode::txFAILED, &signer);
            }

            SECTION("remove")
            {
                auto op = manageSignerRuleTestHelper.buildRemoveRoleOp(2);
                manageSignerRuleTestHelper.applyTx(master, op,
                                                   ManageSignerRuleResultCode::SUCCESS,
                                                   OperationResultCode::opBAD_AUTH,
                                                   TransactionResultCode::txFAILED, &signer);
            }
        }

        SECTION("operational try manage readonly rule")
        {

        }

        /*auto removeRoleOp = manageSignerRoleTestHelper.buildRemoveRoleOp(roleID);
        SECTION("Delete signer role")
        {
            manageSignerRoleTestHelper.applyTx(master, removeRoleOp);

            SECTION("Delete non-existing signer role")
            {
                manageSignerRoleTestHelper.applyTx(master, removeRoleOp,
                                                   ManageSignerRoleResultCode::NOT_FOUND);
            }
        }

        SECTION("Cannot delete role that is used")
        {
            auto randomKey = SecretKey::random();
            auto createSignerOp = manageSignerTestHelper.buildCreateOp(
                    randomKey.getPublicKey(), 10, 12, roleID);
            manageSignerTestHelper.applyTx(master, createSignerOp);

            manageSignerRoleTestHelper.applyTx(master, removeRoleOp,
                                               ManageSignerRoleResultCode::ROLE_IS_USED);
        }
    }


    SECTION("Default Rule id duplication")
    {
        std::vector<uint64> ruleIDs{ruleID, 2};

        auto createSignerRoleOp = manageSignerRoleTestHelper.buildCreateRoleOp(
                R"({"data": "new_details"})", ruleIDs, false);

        manageSignerRoleTestHelper.applyTx(master, createSignerRoleOp,
                                           ManageSignerRoleResultCode::DEFAULT_RULE_ID_DUPLICATION);*/
    }
}
