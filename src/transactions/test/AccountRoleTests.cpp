#include "TxTests.h"
#include "crypto/SHA.h"
#include "ledger/LedgerDeltaImpl.h"
#include "test/test.h"
#include "overlay/LoopbackPeer.h"
#include "test/test_marshaler.h"
#include "test_helper/CreateAccountTestHelper.h"
#include "transactions/external_system_pool/BindExternalSystemAccountIdOpFrame.h"
#include "transactions/manage_role_rule/ManageAccountRuleOpFrame.h"
#include "transactions/test/test_helper/ManageAccountRuleTestHelper.h"
#include "transactions/test/test_helper/ManageAccountRoleTestHelper.h"

using namespace stellar;
using namespace stellar::txtest;

typedef std::unique_ptr<Application> appPtr;

TEST_CASE("Account role tests", "[tx][manage_account_role]")
{
    Config const& cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);

    VirtualClock clock;
    Application::pointer appPtr = Application::create(clock, cfg);
    Application& app = *appPtr;
    app.start();
    TestManager::upgradeToCurrentLedgerVersion(app);

    Database& db = app.getDatabase();

    auto testManager = TestManager::make(app);

    LedgerDeltaImpl delta(app.getLedgerManager().getCurrentLedgerHeader(),
                          app.getDatabase());

    // set up world
    auto master = Account{getRoot(), Salt(1)};

    CreateAccountTestHelper createAccountTestHelper(testManager);
    ManageAccountRoleTestHelper manageAccountRoleHelper(testManager);
    ManageAccountRuleTestHelper manageAccountRuleTestHelper(testManager);

    auto ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
        0, AccountRuleResource(LedgerEntryType::KEY_VALUE), AccountRuleAction::MANAGE, false);
    auto createRuleResult = manageAccountRuleTestHelper.applyTx(
        master, ruleEntry, ManageAccountRuleAction::CREATE);

    SECTION("Create account role")
    {
        std::vector<uint64> ruleIDs{createRuleResult.success().ruleID};

        auto createAccountRoleOp = manageAccountRoleHelper.buildCreateRoleOp(R"({"data": "new_details"})", ruleIDs);

        ManageAccountRoleResult result = manageAccountRoleHelper.applyTx(master,
                                                                         createAccountRoleOp);
        auto accountRoleID = result.success().roleID;

        SECTION("update")
        {
            auto updateRoleOp = manageAccountRoleHelper.buildUpdateRoleOp(
                accountRoleID, "{}", ruleIDs);

            manageAccountRoleHelper.applyTx(master, updateRoleOp);
        }

        SECTION("no such rule")
        {
            uint64_t nonExistingRuleID = 1408;

            auto updateRoleOp = manageAccountRoleHelper.buildUpdateRoleOp(
                accountRoleID, R"({"data": "new_details"})", {nonExistingRuleID});

            result = manageAccountRoleHelper.applyTx(master, updateRoleOp,
                                                     ManageAccountRoleResultCode::NO_SUCH_RULE);

            REQUIRE(result.ruleID() == nonExistingRuleID);
        }

        auto removeRoleOp = manageAccountRoleHelper.buildRemoveRoleOp(accountRoleID);
        SECTION("Delete account role")
        {
            manageAccountRoleHelper.applyTx(master, removeRoleOp);

            SECTION("Delete non-existing account role")
            {
                manageAccountRoleHelper.applyTx(master, removeRoleOp,
                                                ManageAccountRoleResultCode::NOT_FOUND);
            }
        }

        SECTION("Cannot delete role that is used")
        {
            auto randomAccount = SecretKey::random();
            createAccountTestHelper.applyTx(CreateAccountTestBuilder()
                                                .setSource(master)
                                                .setToPublicKey(randomAccount.getPublicKey())
                                                .addBasicSigner()
                                                .setRoleID(accountRoleID));

            manageAccountRoleHelper.applyTx(master, removeRoleOp,
                                            ManageAccountRoleResultCode::ROLE_IS_USED);
        }
    }

    SECTION("no such rule")
    {
        uint64_t nonExistingRuleID = 1408;

        auto createAccountRoleOp = manageAccountRoleHelper.buildCreateRoleOp(
            R"({"data": "new_details"})", {nonExistingRuleID});

        ManageAccountRoleResult result = manageAccountRoleHelper.applyTx(master,
                                                                         createAccountRoleOp, ManageAccountRoleResultCode::NO_SUCH_RULE);

        REQUIRE(result.ruleID() == nonExistingRuleID);
    }
}
