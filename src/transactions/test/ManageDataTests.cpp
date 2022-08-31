#include "ledger/LedgerDeltaImpl.h"
#include "test/test.h"
#include "TxTests.h"
#include "test_helper/CreateAccountTestHelper.h"
#include "test/test_marshaler.h"
#include "test_helper/CreateDataTestHelper.h"
#include "test_helper/UpdateDataTestHelper.h"
#include "test_helper/RemoveDataTestHelper.h"
#include "test_helper/ManageAccountRoleTestHelper.h"
#include "test_helper/ManageAccountRuleTestHelper.h"
#include "test_helper/UpdateDataOwnerTestHelper.h"

using namespace stellar;
using namespace stellar::txtest;

TEST_CASE("Data", "[tx][data]")
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
    CreateDataTestHelper createDataTestHelper(testManager);
    UpdateDataTestHelper updateDataTestHelper(testManager);
    RemoveDataTestHelper removeDataTestHelper(testManager);
    UpdateDataOwnerTestHelper updateDataOwnerTestHelper(testManager);

    // a new owner
    auto roleID = manageAccountRoleHelper.createTxSenderRole(master);
    auto dataManager = Account{SecretKey::random(), 228};
    auto newOwner = dataManager.key.getPublicKey();
    auto createAccountBuilder = CreateAccountTestBuilder()
                                        .setSource(master)
                                        .setRoleID(roleID);
    createAccountTestHelper.applyTx(createAccountBuilder
                                        .setToPublicKey(newOwner)
                                        .addBasicSigner());

    SECTION("master: successful creation")
    {
        auto result = createDataTestHelper.applyCreateData(master, 1, R"({"data":"signature"})");
        auto id = result.success().dataID;

        SECTION("successful update") 
        {
            updateDataTestHelper.applyUpdateData(master, id, R"({"data":"new_signature"})");
        }

        SECTION("successful update owner") 
        {
            updateDataOwnerTestHelper.applyUpdateDataOwner(master, id, newOwner);
        }

        SECTION("successful delete") 
        {
            removeDataTestHelper.applyRemoveData(master, id);
        }
    }

    SECTION("create account with certain rules")
    {
        uint64_t dataType(2);
        auto roleID = manageAccountRoleHelper.createTxSenderRole(master);

        AccountRuleResource dataResource(LedgerEntryType::DATA);
        dataResource.data().type = dataType;
        auto actions = {AccountRuleAction::CREATE, AccountRuleAction::UPDATE, AccountRuleAction::REMOVE, AccountRuleAction::TRANSFER_OWNERSHIP};
        std::vector<uint64_t> ruleIDs = {2}; // 2 - rule for send tx
        for (auto action : actions) 
        {
            auto ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(0,
                                    dataResource, action, false);

            auto ruleID = manageAccountRuleTestHelper.applyTx(master, ruleEntry,
                            ManageAccountRuleAction::CREATE).success().ruleID;

            ruleIDs.emplace_back(ruleID);
        }

        auto op = manageAccountRoleHelper.buildUpdateRoleOp(roleID, R"({"name":"data manager"})", ruleIDs);
        manageAccountRoleHelper.applyTx(master, op);

        auto dataManager = Account{SecretKey::random(), 228};
        auto accountID = dataManager.key.getPublicKey();
        auto createAccountBuilder = CreateAccountTestBuilder()
                                        .setSource(master)
                                        .setRoleID(roleID);
        createAccountTestHelper.applyTx(createAccountBuilder
                                        .setToPublicKey(accountID)
                                        .addBasicSigner());

        SECTION("dataManager: successful creation")
        {
            auto result = createDataTestHelper.applyCreateData(dataManager, dataType, R"({"data":"signature"})");
            auto id = result.success().dataID;

            SECTION("successful update") 
            {
                updateDataTestHelper.applyUpdateData(dataManager, id, R"({"data":"new_signature"})");
            }

            SECTION("successful update owner") 
            {
                updateDataOwnerTestHelper.applyUpdateDataOwner(master, id, newOwner);
            }

            SECTION("successful delete") 
            {
                removeDataTestHelper.applyRemoveData(dataManager, id);
            }
        }
    }

    SECTION("invalid details (create)") 
    {
        auto result = createDataTestHelper.applyCreateData(master, 1, "data",
                                                           CreateDataResultCode::INVALID_DATA);
    }

    SECTION("invalid details (update)") 
    {
        auto result = updateDataTestHelper.applyUpdateData(master, 1, "data", 
                                                           UpdateDataResultCode::INVALID_DATA);
    }

    SECTION("not found (update)")
    {
        auto result = updateDataTestHelper.applyUpdateData(master, 228, R"({"not":"found"})",
                                                           UpdateDataResultCode::NOT_FOUND, 
                                                           OperationResultCode::opNO_ENTRY);
    }

    SECTION("not found (update owner)")
    {
        auto result = updateDataOwnerTestHelper.applyUpdateDataOwner(master, 228, newOwner,
                                                           UpdateDataOwnerResultCode::NOT_FOUND, 
                                                           OperationResultCode::opNO_ENTRY);
    }

     SECTION("not found (delete)")
    {
        auto result = removeDataTestHelper.applyRemoveData(master, 228, RemoveDataResultCode::NOT_FOUND,
                                                           OperationResultCode::opNO_ENTRY);
    }
}