#include <ledger/ExternalSystemAccountIDPoolEntry.h>
#include "main/Application.h"
#include "util/Timer.h"
#include "main/Config.h"
#include "overlay/LoopbackPeer.h"
#include "main/test.h"
#include "TxTests.h"
#include "ledger/BalanceHelperLegacy.h"
#include "ledger/LedgerDeltaImpl.h"
#include "test_helper/BindExternalSystemAccountIdTestHelper.h"
#include "test_helper/CreateAccountTestHelper.h"
#include "test_helper/ManageExternalSystemAccountIDPoolEntryTestHelper.h"
#include "transactions/test/test_helper/ManageAccountRoleTestHelper.h"
#include "transactions/test/test_helper/ManageAccountRuleTestHelper.h"
#include "test/test_marshaler.h"

using namespace stellar;
using namespace stellar::txtest;

typedef std::unique_ptr<Application> appPtr;


TEST_CASE("bind external system account_id", "[tx][bind_external_system_account_id]")
{
    auto const ERC20_TokenExternalSystemType = 4;
    Config const& cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);
    VirtualClock clock;
    auto const appPtr = Application::create(clock, cfg);
    auto& app = *appPtr;
    app.start();
    auto testManager = TestManager::make(app);
    testManager->upgradeToLedgerVersion(app, LedgerVersion::ADD_ASSET_BALANCE_PRECISION);

    LedgerDeltaImpl delta(app.getLedgerManager().getCurrentLedgerHeader(),
                          app.getDatabase());

    auto root = Account{ getRoot(), Salt(0) };

    BindExternalSystemAccountIdTestHelper bindExternalSystemAccountIdTestHelper(testManager);
    CreateAccountTestHelper createAccountTestHelper(testManager);
    ManageExternalSystemAccountIDPoolEntryTestHelper manageExternalSystemAccountIDPoolEntryTestHelper(testManager);

    auto account = Account { SecretKey::random(), Salt(0) };
    createAccountTestHelper.applyCreateAccountTx(root, account.key.getPublicKey(), AccountType::GENERAL);

    testManager->advanceToTime(BindExternalSystemAccountIdOpFrame::dayInSeconds);

    SECTION("Happy path")
    {
        int32 BitcoinExternalSystemType = 1;

        manageExternalSystemAccountIDPoolEntryTestHelper.createExternalSystemAccountIdPoolEntry(root,
                                                                                                BitcoinExternalSystemType,
                                                                                            "Some data");

        bindExternalSystemAccountIdTestHelper.applyBindExternalSystemAccountIdTx(account, BitcoinExternalSystemType);

        SECTION("Prolongation of external system account id")
        {
            testManager->advanceToTime(BindExternalSystemAccountIdOpFrame::dayInSeconds * 2);

            bindExternalSystemAccountIdTestHelper.applyBindExternalSystemAccountIdTx(account, BitcoinExternalSystemType);
        }
    }

    SECTION("No external system account ids of this type in pool")
    {
        bindExternalSystemAccountIdTestHelper.applyBindExternalSystemAccountIdTx(account, ERC20_TokenExternalSystemType,
                                                             BindExternalSystemAccountIdResultCode::NO_AVAILABLE_ID);
    }

    SECTION("All external system account ids of this type are bound")
    {
        auto binder = Account { SecretKey::random(), Salt(0) };
        createAccountTestHelper.applyCreateAccountTx(root, binder.key.getPublicKey(), AccountType::GENERAL);

        manageExternalSystemAccountIDPoolEntryTestHelper.createExternalSystemAccountIdPoolEntry(root,
                                                                                                ERC20_TokenExternalSystemType,
                                                                                            "Some data");

        bindExternalSystemAccountIdTestHelper.applyBindExternalSystemAccountIdTx(binder, ERC20_TokenExternalSystemType);

        bindExternalSystemAccountIdTestHelper.applyBindExternalSystemAccountIdTx(account, ERC20_TokenExternalSystemType,
                                                             BindExternalSystemAccountIdResultCode::NO_AVAILABLE_ID);
    }
    SECTION("Bind expired external system account id")
    {
        auto binder = Account {SecretKey::random(), Salt(0)};
        createAccountTestHelper.applyCreateAccountTx(root, binder.key.getPublicKey(), AccountType::GENERAL);

        manageExternalSystemAccountIDPoolEntryTestHelper.createExternalSystemAccountIdPoolEntry(root,
                                                                                                ERC20_TokenExternalSystemType,
                                                                                                "Some data");

        bindExternalSystemAccountIdTestHelper.applyBindExternalSystemAccountIdTx(binder, ERC20_TokenExternalSystemType);

        testManager->advanceToTime(BindExternalSystemAccountIdOpFrame::dayInSeconds * 3);

        bindExternalSystemAccountIdTestHelper.applyBindExternalSystemAccountIdTx(account, ERC20_TokenExternalSystemType);
    }
    SECTION("Cannot proceed frame due to policies")
    {
        app.resumeCheckingPolicies();

        manageExternalSystemAccountIDPoolEntryTestHelper.createExternalSystemAccountIdPoolEntry(root,
                                                                                                ERC20_TokenExternalSystemType,
                                                                                                "Some data");

        auto binder = Account {SecretKey::random(), Salt(0)};
        createAccountTestHelper.applyTx(
                CreateAccountTestBuilder()
                        .setSource(root)
                        .setToPublicKey(binder.key.getPublicKey()));

        testManager->upgradeToLedgerVersion(app, LedgerVersion::REPLACE_ACCOUNT_TYPES_WITH_POLICIES);

        REQUIRE_FALSE(testManager->applyCheck(bindExternalSystemAccountIdTestHelper.createBindExternalSystemAccountIdTx(
                account, ERC20_TokenExternalSystemType)));

        app.stopCheckingPolicies();
    }
    SECTION("Happy path with policies check")
    {
        ManageAccountRoleTestHelper setAccountRoleTestHelper(testManager);
        ManageAccountRuleTestHelper setAccountRolePolicyTestHelper(testManager);

        // create policy (just entry)
        auto policyEntry = setAccountRolePolicyTestHelper.createAccountRuleEntry(
                0,
                AccountRuleResource(
                        LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY),
                "bind", false);
        // write this entry to DB
        auto createRuleResult = setAccountRolePolicyTestHelper.applyTx(
                root, policyEntry, ManageAccountRuleAction::CREATE,
                ManageAccountRuleResultCode::SUCCESS);

        std::vector<uint64_t> ruleIDs{createRuleResult.success().ruleID};

        policyEntry = setAccountRolePolicyTestHelper.createAccountRuleEntry(0,
                                                                            AccountRuleResource(
                                                                                    LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID),
                                                                            "manage",
                                                                            false);
        // write this entry to DB
        createRuleResult = setAccountRolePolicyTestHelper.applyTx(
                root, policyEntry, ManageAccountRuleAction::CREATE,
                ManageAccountRuleResultCode::SUCCESS);

        ruleIDs.emplace_back(createRuleResult.success().ruleID);

        // create account role using root as source
        auto createAccountRoleOp = setAccountRoleTestHelper.createCreationOpInput("external_pool_binder", ruleIDs);

        auto accountRoleID = setAccountRoleTestHelper.applySetAccountRole(
                root, createAccountRoleOp).success().roleID;

        manageExternalSystemAccountIDPoolEntryTestHelper
                .createExternalSystemAccountIdPoolEntry(root,
                                                        ERC20_TokenExternalSystemType,
                                                        "Some data");
        testManager->upgradeToLedgerVersion(app, LedgerVersion::REPLACE_ACCOUNT_TYPES_WITH_POLICIES);

        // create binder with this role using root as source
        auto binder = Account {SecretKey::random(), Salt(0)};
        createAccountTestHelper.applyTx(CreateAccountTestBuilder()
                        .setSource(root)
                        .setToPublicKey(binder.key.getPublicKey())
                        .setRoleID(accountRoleID));

        bindExternalSystemAccountIdTestHelper.applyBindExternalSystemAccountIdTx(binder, ERC20_TokenExternalSystemType);

    }
}