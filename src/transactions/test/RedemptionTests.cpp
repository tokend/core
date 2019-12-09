#include <transactions/test/test_helper/ManageAccountRoleTestHelper.h>
#include <transactions/test/test_helper/ManageAccountRuleTestHelper.h>
#include <transactions/test/test_helper/ManageRedemptionTestHelper.h>
#include "test_helper/CreateAccountTestHelper.h"
#include "test_helper/ManageBalanceTestHelper.h"
#include "test/test_marshaler.h"
#include "TxTests.h"
#include "test/test.h"

using namespace stellar;
using namespace stellar::txtest;

typedef std::unique_ptr<Application> appPtr;

TEST_CASE("Redemption", "[tx][redemption]")
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
    auto payer = Account{SecretKey::random(), Salt(1)};
    auto recipient = Account{SecretKey::random(), Salt(1)};

    // helpers
    auto redemptionHelper = ManageRedemptionTestHelper(testManager);
    CreateAccountTestHelper createAccountTestHelper(testManager);
    ManageAccountRoleTestHelper manageAccountRoleTestHelper(testManager);
    ManageAccountRuleTestHelper manageAccountRuleTestHelper(testManager);
    ManageBalanceTestHelper manageBalanceTestHelper(testManager);
    uint32_t zeroTasks = 0;

    SECTION("empty reason is not allowed")
    {
        BalanceID srcBalanceID;
        AccountID dstAccountID;
        redemptionHelper.applyCreateRedemption(root, srcBalanceID, dstAccountID, 0, "", "", &zeroTasks, CreateRedemptionRequestResultCode::INVALID_CREATOR_DETAILS);
    }
    SECTION("zero amount is not allowed")
    {
        BalanceID srcBalanceID;
        AccountID dstAccountID;
        redemptionHelper.applyCreateRedemption(root, srcBalanceID, dstAccountID, 0, "Inalid", "", &zeroTasks, CreateRedemptionRequestResultCode::INVALID_AMOUNT);
    }
    SECTION("src balance does not exist")
    {
        BalanceID srcBalanceID;
        AccountID dstAccountID;
        redemptionHelper.applyCreateRedemption(root, srcBalanceID, dstAccountID, 10, "Inalid", "", &zeroTasks, CreateRedemptionRequestResultCode::SOURCE_BALANCE_NOT_EXIST);
    }
    SECTION("dst account does not exist")
    {
        BalanceID srcBalanceID = manageBalanceTestHelper.createBalance(root, root);
        AccountID dstAccountID;
        redemptionHelper.applyCreateRedemption(root, srcBalanceID, dstAccountID, 10, "Inalid", "", &zeroTasks, CreateRedemptionRequestResultCode::SOURCE_BALANCE_NOT_EXIST);
    }
}