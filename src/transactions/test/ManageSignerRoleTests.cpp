#include <transactions/test/test_helper/ManageSignerRoleTestHelper.h>
#include <transactions/test/test_helper/ManageSignerRuleTestHelper.h>
#include <transactions/test/test_helper/ManageSignerTestHelper.h>
#include "TxTests.h"
#include "crypto/SHA.h"
#include "main/test.h"
#include "overlay/LoopbackPeer.h"
#include "test/test_marshaler.h"
#include "test_helper/CreateAccountTestHelper.h"

using namespace stellar;
using namespace stellar::txtest;

TEST_CASE("Signer role tests", "[tx][manage_signer_role]")
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

    ManageSignerTestHelper manageSignerTestHelper(testManager);
    ManageSignerRoleTestHelper manageSignerRoleTestHelper(testManager);
    ManageSignerRuleTestHelper manageSignerRuleTestHelper(testManager);

    auto op = manageSignerRuleTestHelper.buildCreateRuleOp(
            SignerRuleResource(LedgerEntryType::FEE), SignerRuleAction::MANAGE, true, false, true);
    auto ruleID = manageSignerRuleTestHelper.applyTx(master, op).success().ruleID;

    SECTION("Create signer role")
    {
        std::vector<uint64> ruleIDs{ruleID};

        auto createSignerRoleOp = manageSignerRoleTestHelper.buildCreateRoleOp(
                R"({"data": "new_details"})", ruleIDs, false);

        auto result = manageSignerRoleTestHelper.applyTx(master, createSignerRoleOp);
        auto roleID = result.success().roleID;

        SECTION("update")
        {
            auto updateRoleOp = manageSignerRoleTestHelper.buildUpdateRoleOp(
                    roleID, "{}", ruleIDs);

            manageSignerRoleTestHelper.applyTx(master, updateRoleOp);
        }

        auto removeRoleOp = manageSignerRoleTestHelper.buildRemoveRoleOp(roleID);
        SECTION("Delete signer role")
        {
            manageSignerRoleTestHelper.applyTx(master, removeRoleOp);

            SECTION("Delete non-existing signer role")
            {
                manageSignerRoleTestHelper.applyTx(master, removeRoleOp,
                                                   ManageSignerRoleResultCode::NOT_FOUND,
                                                   OperationResultCode::opINNER,
                                                   TransactionResultCode::txFAILED);
            }
        }

        SECTION("Cannot delete role that is used")
        {
            auto randomKey = SecretKey::random();
            auto createSignerOp = manageSignerTestHelper.buildCreateOp(
                    randomKey.getPublicKey(), 10, 12, roleID);
            manageSignerTestHelper.applyTx(master, createSignerOp);

            manageSignerRoleTestHelper.applyTx(master, removeRoleOp,
                                               ManageSignerRoleResultCode::ROLE_IS_USED,
                                               OperationResultCode::opINNER,
                                               TransactionResultCode::txFAILED);
        }
    }

    SECTION("no such rule")
    {
        uint64_t nonExistingRuleID = 1408;

        auto createAccountRoleOp = manageSignerRoleTestHelper.buildCreateRoleOp(
                R"({"data": "new_details"})", {nonExistingRuleID}, true);

        auto result = manageSignerRoleTestHelper.applyTx(master,
                createAccountRoleOp, ManageSignerRoleResultCode::NO_SUCH_RULE,
                OperationResultCode::opINNER, TransactionResultCode::txFAILED);

        REQUIRE(result.ruleID() == nonExistingRuleID);
    }

    SECTION("Rule id duplication")
    {
        std::vector<uint64> ruleIDs{ruleID, ruleID};

        auto createSignerRoleOp = manageSignerRoleTestHelper.buildCreateRoleOp(
                R"({"data": "new_details"})", ruleIDs, false);

        auto result = manageSignerRoleTestHelper.applyTx(master, createSignerRoleOp,
                ManageSignerRoleResultCode::RULE_ID_DUPLICATION,
                OperationResultCode::opINNER, TransactionResultCode::txFAILED);

        REQUIRE(result.ruleID() == ruleID);
    }

    SECTION("Default Rule id duplication")
    {
        std::vector<uint64> ruleIDs{ruleID, 2};

        auto createSignerRoleOp = manageSignerRoleTestHelper.buildCreateRoleOp(
                R"({"data": "new_details"})", ruleIDs, false);

        auto result = manageSignerRoleTestHelper.applyTx(master, createSignerRoleOp,
                ManageSignerRoleResultCode::DEFAULT_RULE_ID_DUPLICATION,
                OperationResultCode::opINNER, TransactionResultCode::txFAILED);

        REQUIRE(result.ruleID() == 2);
    }
}
