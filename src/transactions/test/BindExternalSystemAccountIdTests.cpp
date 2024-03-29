#include "main/Application.h"
#include "util/Timer.h"
#include "main/Config.h"
#include "test/test.h"
#include "TxTests.h"
#include "ledger/LedgerDeltaImpl.h"
#include "test_helper/BindExternalSystemAccountIdTestHelper.h"
#include "test_helper/CreateAccountTestHelper.h"
#include "test_helper/ManageExternalSystemAccountIDPoolEntryTestHelper.h"
#include "transactions/test/test_helper/ManageAccountRoleTestHelper.h"
#include "transactions/test/test_helper/ManageAccountRuleTestHelper.h"
#include "test/test_marshaler.h"
#include "transactions/test/test_helper/ManageKeyValueTestHelper.h"

using namespace stellar;
using namespace stellar::txtest;

typedef std::unique_ptr<Application> appPtr;


TEST_CASE("bind external system account_id", "[tx][bind_external_system_account_id]")
{
    const int32 BitcoinExternalSystemType = 1;
    auto const ERC20_TokenExternalSystemType = 4;
    Config const& cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);
    VirtualClock clock;
    auto const appPtr = Application::create(clock, cfg);
    auto& app = *appPtr;
    app.start();
    auto testManager = TestManager::make(app);
    testManager->upgradeToCurrentLedgerVersion(app);

    LedgerDeltaImpl delta(app.getLedgerManager().getCurrentLedgerHeader(),
                          app.getDatabase());

    auto root = Account{ getRoot(), Salt(0) };

    BindExternalSystemAccountIdTestHelper bindExternalSystemAccountIdTestHelper(testManager);
    CreateAccountTestHelper createAccountTestHelper(testManager);
    ManageAccountRuleTestHelper manageAccountRuleTestHelper(testManager);
    ManageAccountRoleTestHelper manageAccountRoleTestHelper(testManager);
    ManageExternalSystemAccountIDPoolEntryTestHelper manageExternalSystemAccountIDPoolEntryTestHelper(testManager);
    ManageKeyValueTestHelper manageKeyValueHelper(testManager);
    longstring assetKey = ManageKeyValueOpFrame::makeExternalSystemExpirationPeriodKey(BitcoinExternalSystemType);
    manageKeyValueHelper.setKey(assetKey)->setUi32Value(BindExternalSystemAccountIdOpFrame::dayInSeconds * 2);
    manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);

    // create policy (just entry)
    AccountRuleResource poolResource(LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY);

    auto ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
            0, poolResource, AccountRuleAction::MANAGE, false);
    // write this entry to DB
    auto createManagePoolRuleResult = manageAccountRuleTestHelper.applyTx(
            root, ruleEntry, ManageAccountRuleAction::CREATE);

    ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
            0, poolResource, AccountRuleAction::BIND, false);
    // write this entry to DB
    auto createBindPoolRuleResult = manageAccountRuleTestHelper.applyTx(
            root, ruleEntry, ManageAccountRuleAction::CREATE);

    auto createPoolManagerRoleOp = manageAccountRoleTestHelper.buildCreateRoleOp(
            R"({"name": "pool_manager"})", {createManagePoolRuleResult.success().ruleID,
                             createBindPoolRuleResult.success().ruleID});

    auto roleID = manageAccountRoleTestHelper.applyTx(
            root, createPoolManagerRoleOp).success().roleID;

    auto account = Account { SecretKey::random(), Salt(0) };
    createAccountTestHelper.applyTx(CreateAccountTestBuilder()
                                            .setSource(root)
                                            .setToPublicKey(account.key.getPublicKey())
                                            .addBasicSigner()
                                            .setRoleID(1));

    testManager->advanceToTime(BindExternalSystemAccountIdOpFrame::dayInSeconds);

    SECTION("Happy path")
    {
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
        createAccountTestHelper.applyTx(CreateAccountTestBuilder()
                                                .setSource(root)
                                                .setToPublicKey(binder.key.getPublicKey())
                                                .addBasicSigner()
                                                .setRoleID(1));

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
        createAccountTestHelper.applyTx(CreateAccountTestBuilder()
                                                .setSource(root)
                                                .setToPublicKey(binder.key.getPublicKey())
                                                .addBasicSigner()
                                                .setRoleID(1));

        manageExternalSystemAccountIDPoolEntryTestHelper.createExternalSystemAccountIdPoolEntry(root,
                                                                                                ERC20_TokenExternalSystemType,
                                                                                                "Some data");

        bindExternalSystemAccountIdTestHelper.applyBindExternalSystemAccountIdTx(binder, ERC20_TokenExternalSystemType);

        testManager->advanceToTime(BindExternalSystemAccountIdOpFrame::dayInSeconds * 3);

        bindExternalSystemAccountIdTestHelper.applyBindExternalSystemAccountIdTx(account, ERC20_TokenExternalSystemType);
    }
}