#include "crypto/SHA.h"
#include "ledger/SignerHelper.h"
#include "ledger/LicenseHelper.h"
#include "ledger/SignerRuleFrame.h"
#include "ledger/StorageHelper.h"
#include "test/test.h"
#include "test/test_marshaler.h"
#include "test_helper/LicenseTestHelper.h"
#include "test_helper/StampTestHelper.h"
#include "transactions/test/test_helper/CreateAccountTestHelper.h"
#include "transactions/test/test_helper/ManageSignerRoleTestHelper.h"
#include "transactions/test/test_helper/ManageSignerRuleTestHelper.h"
#include "transactions/test/test_helper/ManageSignerTestHelper.h"

using namespace stellar;
using namespace stellar::txtest;

TEST_CASE("Signer tests", "[tx][manage_signer]")
{
    Config cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);
    auto wiredKey = SecretKey::random();
    cfg.WIRED_KEYS.emplace_back(wiredKey.getPublicKey());

    VirtualClock clock;
    Application::pointer appPtr = Application::create(clock, cfg);
    Application& app = *appPtr;
    app.start();
    auto testManager = TestManager::make(app);
    TestManager::upgradeToCurrentLedgerVersion(app);

    // set up world
    auto master = Account{getRoot(), Salt(0)};
    uint64_t ownerSignerRoleID = 1;


    LicenseTestHelper licenseTestHelper(testManager);
    StampTestHelper stampTestHelper(testManager);
    ManageSignerTestHelper manageSignerTestHelper(testManager);
    ManageSignerRoleTestHelper manageSignerRoleTestHelper(testManager);
    ManageSignerRuleTestHelper manageSignerRuleTestHelper(testManager);
    CreateAccountTestHelper createAccountTestHelper(testManager);


    SECTION("Create operational signer")
    {
        // create operational signer role
        std::vector<uint64> ruleIDs{ownerSignerRoleID};

        auto createSignerRoleOp = manageSignerRoleTestHelper.buildCreateRoleOp(
            R"({"from": "manage signer test"})", ruleIDs, false);

        auto result =
            manageSignerRoleTestHelper.applyTx(master, createSignerRoleOp);
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
                    SignerRuleResource(LedgerEntryType::FEE),
                    SignerRuleAction::MANAGE, true, true, true);
                manageSignerRuleTestHelper.applyTx(
                    master, op, ManageSignerRuleResultCode::SUCCESS,
                    OperationResultCode::opBAD_AUTH,
                    TransactionResultCode::txFAILED, &signer);
            }

            SECTION("update")
            {
                auto op = manageSignerRuleTestHelper.buildUpdateRuleOp(
                    2, SignerRuleResource(LedgerEntryType::FEE),
                    SignerRuleAction::MANAGE, false, false);
                manageSignerRuleTestHelper.applyTx(
                    master, op, ManageSignerRuleResultCode::SUCCESS,
                    OperationResultCode::opBAD_AUTH,
                    TransactionResultCode::txFAILED, &signer);
            }

            SECTION("remove")
            {
                auto op = manageSignerRuleTestHelper.buildRemoveRuleOp(2);
                manageSignerRuleTestHelper.applyTx(
                    master, op, ManageSignerRuleResultCode::SUCCESS,
                    OperationResultCode::opBAD_AUTH,
                    TransactionResultCode::txFAILED, &signer);
            }
        }

        SECTION("operational try manage readonly rule")
        {
            auto op =
                manageSignerRuleTestHelper.buildRemoveRuleOp(ownerSignerRoleID);
            manageSignerRuleTestHelper.applyTx(
                master, op, ManageSignerRuleResultCode::NOT_FOUND,
                OperationResultCode::opINNER, TransactionResultCode::txFAILED,
                &signer);

            op = manageSignerRuleTestHelper.buildUpdateRuleOp(
                ownerSignerRoleID, SignerRuleResource(LedgerEntryType::FEE),
                SignerRuleAction::MANAGE, false, false);
            manageSignerRuleTestHelper.applyTx(
                master, op, ManageSignerRuleResultCode::NOT_FOUND,
                OperationResultCode::opINNER, TransactionResultCode::txFAILED,
                &signer);
        }

        SECTION("operational tries to manage owner signer role")
        {
            std::string validDetails = R"({"from": "manage signer test"})";

            SECTION("update")
            {
                auto op = manageSignerRoleTestHelper.buildUpdateRoleOp(
                    ownerSignerRoleID, validDetails, {1});
                manageSignerRoleTestHelper.applyTx(
                    master, op, ManageSignerRoleResultCode::SUCCESS,
                    OperationResultCode::opBAD_AUTH,
                    TransactionResultCode::txFAILED, &signer);
            }

            SECTION("remove")
            {
                auto op = manageSignerRoleTestHelper.buildRemoveRoleOp(1);
                manageSignerRoleTestHelper.applyTx(
                    master, op, ManageSignerRoleResultCode::SUCCESS,
                    OperationResultCode::opBAD_AUTH,
                    TransactionResultCode::txFAILED, &signer);
            }
        }

        SECTION("operational tries to manage owner signer")
        {
            SECTION("create")
            {
                auto op = manageSignerTestHelper.buildCreateOp(
                    SecretKey::random().getPublicKey(), 1, 0,
                    ownerSignerRoleID);
                manageSignerTestHelper.applyTx(
                    master, op, ManageSignerResultCode::SUCCESS,
                    OperationResultCode::opBAD_AUTH,
                    TransactionResultCode::txFAILED, &signer);
            }

            SECTION("update owner")
            {
                auto op = manageSignerTestHelper.buildUpdateOp(
                    master.key.getPublicKey(), 1, 0, roleID);
                manageSignerTestHelper.applyTx(
                    master, op, ManageSignerResultCode::SUCCESS,
                    OperationResultCode::opBAD_AUTH,
                    TransactionResultCode::txFAILED, &signer);
            }

            SECTION("change own role to owner roleID")
            {
                auto op = manageSignerTestHelper.buildUpdateOp(
                    signer.key.getPublicKey(), 1, 0, ownerSignerRoleID);
                manageSignerTestHelper.applyTx(
                    master, op, ManageSignerResultCode::SUCCESS,
                    OperationResultCode::opBAD_AUTH,
                    TransactionResultCode::txFAILED, &signer);
            }

            SECTION("remove")
            {
                auto op = manageSignerTestHelper.buildRemoveOp(
                    master.key.getPublicKey());
                manageSignerTestHelper.applyTx(
                    master, op, ManageSignerResultCode::SUCCESS,
                    OperationResultCode::opBAD_AUTH,
                    TransactionResultCode::txFAILED, &signer);
            }
        }

        SECTION("operational can create another operational")
        {
            auto anotherSignerKey = SecretKey::random();
            auto anotherSigner = Account{anotherSignerKey, Salt(4)};

            auto op = manageSignerTestHelper.buildCreateOp(
                anotherSigner.key.getPublicKey(), 1, 0, roleID);
            manageSignerTestHelper.applyTx(
                master, op, ManageSignerResultCode::SUCCESS,
                OperationResultCode::opINNER, TransactionResultCode::txSUCCESS,
                &signer);
        }

        SECTION("Use public key of existing signer for other account")
        {
            auto accountKey = SecretKey::random();
            auto account = Account{accountKey, Salt(5)};

            UpdateSignerData signerData;
            auto data = createSignerOp.data.createData();
            signerData.publicKey = data.publicKey;
            signerData.weight = data.weight;
            signerData.identity = data.identity;
            signerData.roleID = data.roleID;
            signerData.details = data.details;

            createAccountTestHelper.applyTx(
                CreateAccountTestBuilder()
                    .setSource(master)
                    .setToPublicKey(accountKey.getPublicKey())
                    .setRoleID(1)
                    .addBasicSigner()
                    .addSignerData(signerData));
        }
    }

    SECTION("Use one signer for two accounts")
    {
        // create new account
        auto accountKey = SecretKey::random();
        auto account = Account{accountKey, Salt(5)};
        createAccountTestHelper.applyTx(CreateAccountTestBuilder()
                                                .setSource(master)
                                                .setToPublicKey(accountKey.getPublicKey())
                                                .setRoleID(1)
                                                .addBasicSigner());

        // create signer
        auto signerKey = SecretKey::random();
        auto signer = Account{signerKey, Salt(6)};
        auto createSignerOp = manageSignerTestHelper.buildCreateOp(
                signerKey.getPublicKey(), SignerRuleFrame::threshold, 200, 1);
        manageSignerTestHelper.applyTx(master, createSignerOp);
        manageSignerTestHelper.applyTx(account, createSignerOp);

        SECTION("Update signer")
        {
            auto updateSignerOp = manageSignerTestHelper.buildUpdateOp(
                    signerKey.getPublicKey(), SignerRuleFrame::threshold, 210, 1);

            manageSignerTestHelper.applyTx(master, updateSignerOp);
            manageSignerTestHelper.applyTx(account, updateSignerOp);

            updateSignerOp = manageSignerTestHelper.buildUpdateOp(
                    signerKey.getPublicKey(), SignerRuleFrame::threshold, 210, 210);

            manageSignerTestHelper.applyTx(account, updateSignerOp,
                                           ManageSignerResultCode::NO_SUCH_ROLE,
                                           OperationResultCode::opINNER,
                                           TransactionResultCode::txFAILED);
        }
    }

    SECTION("Create owner")
    {
        // create signer
        auto signerKey = SecretKey::random();
        auto signer = Account{signerKey, Salt(4)};
        auto createSignerOp = manageSignerTestHelper.buildCreateOp(
            signerKey.getPublicKey(), SignerRuleFrame::threshold, 200, 1);
        manageSignerTestHelper.applyTx(master, createSignerOp);

        SECTION("Remove previous owner")
        {
            auto op =
                manageSignerTestHelper.buildRemoveOp(master.key.getPublicKey());
            manageSignerTestHelper.applyTx(
                master, op, ManageSignerResultCode::SUCCESS,
                OperationResultCode::opINNER, TransactionResultCode::txSUCCESS,
                &signer);
        }
    }

    SECTION("Create owner and Remove previous owner in one tx")
    {
        // create signer
        auto signerKey = SecretKey::random();
        auto signer = Account{signerKey, Salt(4)};
        auto createSignerOp = manageSignerTestHelper.buildCreateOp(
            signerKey.getPublicKey(), SignerRuleFrame::threshold, 200,
            ownerSignerRoleID);

        auto op =
            manageSignerTestHelper.buildRemoveOp(master.key.getPublicKey());
        std::vector<ManageSignerOp> ops = {createSignerOp, op};
        manageSignerTestHelper.applyTx(
            master, ops, ManageSignerResultCode::SUCCESS,
            OperationResultCode::opINNER, TransactionResultCode::txSUCCESS);
    }

    SECTION("Adding 1000 signers with free license")
    {
        auto& storageHelper = testManager->getStorageHelper();

        for (int i = 0; i < 1000; i++)
        {
            auto signer = Account{SecretKey::random(), Salt(4)};
            auto createSignerOp = manageSignerTestHelper.buildCreateOp(
                    signer.key.getPublicKey(), SignerRuleFrame::threshold, 200,
                    ownerSignerRoleID);
            manageSignerTestHelper.applyTx(
                    master, {createSignerOp},
                    ManageSignerResultCode::SUCCESS,
                    OperationResultCode::opINNER, TransactionResultCode::txSUCCESS);
        }

    }

    SECTION("Should not allow to add new signers above license limits")
    {

        auto& storageHelper = testManager->getStorageHelper();

        uint64_t adminCount = 10;
        uint64_t dueDate = 1000;
        auto stampResult = stampTestHelper.applyStamp(master);
        auto stampSuccess = stampResult.success();
        auto licenseResult = licenseTestHelper.applyLicenseOp(master,
                                                              {wiredKey},
                                                              stampSuccess.ledgerHash,
                                                              stampSuccess.licenseHash,
                                                              adminCount,
                                                              dueDate
        );

        auto currentNumberOfAdmins =
            storageHelper.getSignerHelper().loadSigners(testManager->getApp().getAdminID()).size();
        auto allowedNumberOfAdmins =
                storageHelper.getLicenseHelper().getAllowedAdmins(
                    testManager->getApp());
        for (; currentNumberOfAdmins < allowedNumberOfAdmins;
             currentNumberOfAdmins++)
        {
            auto signer = Account{SecretKey::random(), Salt(4)};
            auto createSignerOp = manageSignerTestHelper.buildCreateOp(
                signer.key.getPublicKey(), SignerRuleFrame::threshold, 200,
                ownerSignerRoleID);
            manageSignerTestHelper.applyTx(
                master, {createSignerOp},
                ManageSignerResultCode::SUCCESS,
                OperationResultCode::opINNER, TransactionResultCode::txSUCCESS);
        }

        auto signer = Account
        {
            SecretKey::random(), Salt(4)
        };
        auto createSignerOp = manageSignerTestHelper.buildCreateOp(
            signer.key.getPublicKey(), SignerRuleFrame::threshold, 200,
            ownerSignerRoleID);
        manageSignerTestHelper.applyTx(
            master, {createSignerOp},
                ManageSignerResultCode::NUMBER_OF_ADMINS_EXCEEDS_LICENSE,
                OperationResultCode::opINNER, TransactionResultCode::txFAILED);
    }

    SECTION("Removing signers when applied license with lower amount of signers")
    {
        auto& storageHelper = testManager->getStorageHelper();

        std::stack<Account> signers;
        Account* removeOpSigner = nullptr;
        for (int i = 0; i < 10; i++)
        {
            auto signer = Account{SecretKey::random(), Salt(4)};
            if (!removeOpSigner) {
                removeOpSigner = &signer;
            }
            auto createSignerOp = manageSignerTestHelper.buildCreateOp(
                    signer.key.getPublicKey(), SignerRuleFrame::threshold, 200,
                    ownerSignerRoleID);
            manageSignerTestHelper.applyTx(
                    master, {createSignerOp},
                    ManageSignerResultCode::SUCCESS,
                    OperationResultCode::opINNER, TransactionResultCode::txSUCCESS);
            signers.push(signer);
        }

        uint64_t adminCount = 5;
        uint64_t dueDate = 1000;
        auto stampResult = stampTestHelper.applyStamp(master);
        auto stampSuccess = stampResult.success();
        auto licenseResult = licenseTestHelper.applyLicenseOp(master,
                                                              {wiredKey},
                                                              stampSuccess.ledgerHash,
                                                              stampSuccess.licenseHash,
                                                              adminCount,
                                                              dueDate
        );

        auto currentNumberOfAdmins =
                storageHelper.getSignerHelper().loadSigners(testManager->getApp().getAdminID()).size();

        auto allowedNumberOfAdmins =
                storageHelper.getLicenseHelper().getAllowedAdmins(
                        testManager->getApp());

        while (currentNumberOfAdmins > allowedNumberOfAdmins) {
            auto signerToRemove = signers.top();
            auto op =
                    manageSignerTestHelper.buildRemoveOp(signerToRemove.key.getPublicKey());

            manageSignerTestHelper.applyTx(
                    master, op, ManageSignerResultCode::SUCCESS,
                    OperationResultCode::opINNER, TransactionResultCode::txSUCCESS, removeOpSigner);
            signers.pop();
            currentNumberOfAdmins =
                    storageHelper.getSignerHelper().loadSigners(testManager->getApp().getAdminID()).size();
        }

        SECTION("try to add the signer and exceed the license signers limit")
        {
            auto signer = Account
            {
                SecretKey::random(), Salt(4)
            };
            auto createSignerOp = manageSignerTestHelper.buildCreateOp(
                    signer.key.getPublicKey(), SignerRuleFrame::threshold, 200,
                    ownerSignerRoleID);
            manageSignerTestHelper.applyTx(
                    master, {createSignerOp},
                    ManageSignerResultCode::NUMBER_OF_ADMINS_EXCEEDS_LICENSE,
                    OperationResultCode::opINNER, TransactionResultCode::txFAILED);
        }
    }
}
