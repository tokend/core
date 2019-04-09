#include "TxTests.h"
#include "crypto/SHA.h"
#include "ledger/AccountHelperLegacy.h"
#include "ledger/AccountRuleHelperImpl.h"
#include "ledger/AssetHelper.h"
#include "ledger/LedgerDeltaImpl.h"
#include "test/test.h"
#include "overlay/LoopbackPeer.h"
#include "test/test_marshaler.h"
#include "test_helper/CreateAccountTestHelper.h"
#include "transactions/test/test_helper/ManageAccountRuleTestHelper.h"
#include <transactions/test/test_helper/ManageAccountRoleTestHelper.h>
#include <transactions/test/test_helper/ManageKeyValueTestHelper.h>

using namespace stellar;
using namespace stellar::txtest;

typedef std::unique_ptr<Application> appPtr;

TEST_CASE("Set role policy", "[tx][manage_account_rule]")
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

    ManageAccountRoleTestHelper manageAccountRoleTestHelper(testManager);
    ManageAccountRuleTestHelper manageAccountRuleTestHelper(testManager);

    SECTION("Successful creation")
    {
        auto ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
                0, AccountRuleResource(LedgerEntryType::KEY_VALUE), AccountRuleAction::MANAGE, false);
        auto createRuleResult = manageAccountRuleTestHelper.applyTx(
                master, ruleEntry, ManageAccountRuleAction::CREATE);

        ruleEntry.id = createRuleResult.success().ruleID;

        SECTION("Successful updating")
        {
            ruleEntry.action = AccountRuleAction::ANY;
            manageAccountRuleTestHelper.applyTx(master, ruleEntry,
                                                ManageAccountRuleAction::UPDATE);
        }
        SECTION("Successful deletion")
        {
            manageAccountRuleTestHelper.applyTx(master, ruleEntry,
                                                ManageAccountRuleAction::REMOVE);
        }

        SECTION("cannot delete cause of role use rule")
        {
            auto creationRoleOp = manageAccountRoleTestHelper.buildCreateRoleOp(
                    "{}", {ruleEntry.id});
            manageAccountRoleTestHelper.applyTx(master, creationRoleOp);

            auto result = manageAccountRuleTestHelper.applyTx(master, ruleEntry,
                                                ManageAccountRuleAction::REMOVE,
                                                ManageAccountRuleResultCode::RULE_IS_USED,
                                                TransactionResultCode::txFAILED);

            REQUIRE(result.roleIDs().size() == 1);
            REQUIRE(result.roleIDs()[0] == ruleEntry.id);
        }
    }

    SECTION("Rule not found when trying to delete it")
    {
        auto ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
                228, AccountRuleResource(LedgerEntryType::KEY_VALUE), AccountRuleAction::MANAGE, false);
        manageAccountRuleTestHelper.applyTx(master, ruleEntry,
                                        ManageAccountRuleAction::REMOVE,
                                        ManageAccountRuleResultCode::NOT_FOUND,
                                        TransactionResultCode::txFAILED);
    }

    SECTION("Rule not found for update")
    {
        auto ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
                228, AccountRuleResource(LedgerEntryType::KEY_VALUE), AccountRuleAction::MANAGE, false);
        manageAccountRuleTestHelper.applyTx(master, ruleEntry,
                                            ManageAccountRuleAction::UPDATE,
                                            ManageAccountRuleResultCode::NOT_FOUND,
                                            TransactionResultCode::txFAILED);
    }
}