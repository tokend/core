#include "TxTests.h"
#include "crypto/SHA.h"
#include "ledger/AccountHelper.h"
#include "ledger/LedgerDeltaImpl.h"
#include "main/test.h"
#include "overlay/LoopbackPeer.h"
#include "test/test_marshaler.h"
#include "test_helper/CreateAccountTestHelper.h"
#include "transactions/BindExternalSystemAccountIdOpFrame.h"
#include "transactions/ManageAccountRuleOpFrame.h"
#include "transactions/test/test_helper/ManageAccountRuleTestHelper.h"
#include "transactions/test/test_helper/ManageAccountRoleTestHelper.h"
#include "util/make_unique.h"

using namespace stellar;
using namespace stellar::txtest;

typedef std::unique_ptr<Application> appPtr;

TEST_CASE("Account role tests", "[tx][set_account_roles]")
{
    Config const& cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);

    VirtualClock clock;
    Application::pointer appPtr = Application::create(clock, cfg);
    Application& app = *appPtr;
    app.start();
    TestManager::upgradeToLedgerVersion(app, LedgerVersion::REPLACE_ACCOUNT_TYPES_WITH_POLICIES);

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
            0, AccountRuleResource(LedgerEntryType::KEY_VALUE), "manage", false);
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
                                                    .setType(AccountType::NOT_VERIFIED)
                                                    .setRecovery(SecretKey::random().getPublicKey())
                                                    .setRoleID(accountRoleID));

            manageAccountRoleHelper.applyTx(master, removeRoleOp,
                                            ManageAccountRoleResultCode::ROLE_IS_USED);
        }
    }
}
