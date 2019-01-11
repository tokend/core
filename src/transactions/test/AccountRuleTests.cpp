#include "TxTests.h"
#include "crypto/SHA.h"
#include "ledger/AccountHelper.h"
#include "ledger/AccountRuleHelperImpl.h"
#include "ledger/AssetHelper.h"
#include "ledger/LedgerDeltaImpl.h"
#include "main/test.h"
#include "overlay/LoopbackPeer.h"
#include "test/test_marshaler.h"
#include "test_helper/CreateAccountTestHelper.h"
#include "transactions/test/test_helper/ManageAccountRuleTestHelper.h"
#include "util/make_unique.h"
#include <transactions/test/test_helper/ManageAccountRoleTestHelper.h>
#include <transactions/test/test_helper/ManageKeyValueTestHelper.h>

using namespace stellar;
using namespace stellar::txtest;

typedef std::unique_ptr<Application> appPtr;

TEST_CASE("Set role policy", "[tx][set_account_role_permissions]")
{
    Config const& cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);

    VirtualClock clock;
    Application::pointer appPtr = Application::create(clock, cfg);
    Application& app = *appPtr;
    app.start();
    TestManager::upgradeToCurrentLedgerVersion(app);
    //TestManager::upgradeToLedgerVersion(app, LedgerVersion::REPLACE_ACCOUNT_TYPES_WITH_POLICIES);

    Database& db = app.getDatabase();

    auto testManager = TestManager::make(app);

    LedgerDeltaImpl delta(app.getLedgerManager().getCurrentLedgerHeader(),
                          app.getDatabase());

    // set up world
    auto master = Account{getRoot(), Salt(1)};

    CreateAccountTestHelper createAccountTestHelper(testManager);
    ManageAccountRoleTestHelper setAccountRoleTestHelper(testManager);
    ManageAccountRuleTestHelper manageAccountRolePolicyTestHelper(
        testManager);

    // create account for further tests
    auto accountKey = SecretKey::random();
    auto account = Account{accountKey, Salt(1)};

    auto policyEntry =
            manageAccountRolePolicyTestHelper.createAccountRuleEntry(
                    0, AccountRuleResource(LedgerEntryType::KEY_VALUE), "*",
                    false);
    auto createRuleResult = manageAccountRolePolicyTestHelper.applyTx(
            master, policyEntry, ManageAccountRuleAction::CREATE,
            ManageAccountRuleResultCode::SUCCESS);

    auto createAccountRoleOp = setAccountRoleTestHelper.createCreationOpInput("key_value_manager", {createRuleResult.success().ruleID});

    auto result = setAccountRoleTestHelper.applySetAccountRole(master, createAccountRoleOp);

    TestManager::upgradeToLedgerVersion(app, LedgerVersion::REPLACE_ACCOUNT_TYPES_WITH_POLICIES);

    auto createAccountTestBuilder = CreateAccountTestBuilder()
            .setSource(master)
            .setToPublicKey(accountKey.getPublicKey())
            .setType(AccountType::NOT_VERIFIED)
            .setRecovery(SecretKey::random().getPublicKey())
            .setRoleID(result.success().roleID);

    createAccountTestHelper.applyTx(createAccountTestBuilder);

  /*  // create account role
    auto accountRoleID =
        setAccountRoleTestHelper
            .applySetAccountRole(
                master,
                setAccountRoleTestHelper.createCreationOpInput("regular"))
            .success()
            .accountRoleID;*/

    SECTION("Successful creation")
    {

        ManageKeyValueTestHelper testHelper(testManager);

        ManageKeyValueOp op;
        op.key = "some_key";
        op.action.action(ManageKVAction::PUT);
        op.action.value().type(KeyValueEntryType::UINT32);
        op.action.value().ui32Value() = 30;
        testHelper.applyTx(account, op);

        /*SECTION("Successful updating")
        {
            policyEntry.opType = OperationType::CREATE_ACCOUNT;
            manageAccountRolePolicyTestHelper.applySetIdentityPermissionTx(
                account, policyEntry,
                ManageAccountRolePermissionOpAction::UPDATE,
                ManageAccountRolePermissionResultCode::SUCCESS);
        }
        SECTION("Successful deletion")
        {
            manageAccountRolePolicyTestHelper.applyTx(
                account, policyEntry,
                ManageAccountRolePermissionOpAction::REMOVE,
                ManageAccountRolePermissionResultCode::SUCCESS);
        }*/
    }
    /*SECTION("Invalid operation type")
    {
        auto policyEntryResourceAndAction =
            manageAccountRolePolicyTestHelper.createAccountRolePermissionEntry(
                accountRoleID, static_cast<OperationType>(-1));
        REQUIRE_THROWS(manageAccountRolePolicyTestHelper.applySetIdentityPermissionTx(
            account, policyEntryResourceAndAction,
            ManageAccountRolePermissionOpAction::CREATE));
    }
    SECTION("Identity policy not found when trying to delete it")
    {
        auto policyEntry =
            manageAccountRolePolicyTestHelper.createAccountRuleEntry(
                accountRoleID, kOperationType);
        manageAccountRolePolicyTestHelper.applyTx(
            account, policyEntry, ManageAccountRolePermissionOpAction::REMOVE,
            ManageAccountRolePermissionResultCode::NOT_FOUND);
    }*/
}