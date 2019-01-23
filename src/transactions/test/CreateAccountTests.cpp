// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0
#include <transactions/test/test_helper/TestManager.h>
#include <transactions/test/test_helper/ManageAssetTestHelper.h>
#include <transactions/test/test_helper/CreateAccountTestHelper.h>
#include <ledger/ExternalSystemAccountIDPoolEntry.h>
#include <transactions/test/test_helper/ManageAccountRoleTestHelper.h>
#include "overlay/LoopbackPeer.h"
#include "main/test.h"
#include "ledger/AccountHelper.h"
#include "ledger/ExternalSystemAccountID.h"
#include "ledger/ExternalSystemAccountIDHelperLegacy.h"
#include "test/test_marshaler.h"

using namespace stellar;
using namespace stellar::txtest;

typedef std::unique_ptr<Application> appPtr;

TEST_CASE("create account", "[tx][create_account]") {
    Config const &cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);

    VirtualClock clock;
    Application::pointer appPtr = Application::create(clock, cfg);
    Application &app = *appPtr;
    app.start();
    TestManager::upgradeToCurrentLedgerVersion(app);

    auto testManager = TestManager::make(app);
    auto root = Account{getRoot(), Salt(1)};

    auto createAccountHelper = CreateAccountTestHelper(testManager);
    ManageAccountRoleTestHelper manageAccountRoleTestHelper(testManager);

    auto createReceiverAccountRoleOp = manageAccountRoleTestHelper.
            buildCreateRoleOp(R"({"name":"empty_role"})", {});

    auto emptyAccountRoleID = manageAccountRoleTestHelper.applyTx(
            root, createReceiverAccountRoleOp).success().roleID;

    auto randomAccount = SecretKey::random();
    auto createAccountTestBuilder = CreateAccountTestBuilder()
            .setSource(root)
            .setToPublicKey(randomAccount.getPublicKey())
            .setType(AccountType::NOT_VERIFIED)
            .setRecovery(SecretKey::random().getPublicKey())
            .setRoleID(emptyAccountRoleID);

    int32 BitcoinExternalSystemType = 1;
    int32 EthereumExternalSystemType = 2;

    SECTION("External system account id are not generated") {
        auto externalSystemAccountIDHelper = ExternalSystemAccountIDHelperLegacy::Instance();
        createAccountHelper.applyTx(createAccountTestBuilder);
        const auto btcKey = externalSystemAccountIDHelper->load(randomAccount.getPublicKey(),
                                                                BitcoinExternalSystemType, app.getDatabase());
        REQUIRE(!btcKey);

        const auto ethKey = externalSystemAccountIDHelper->load(randomAccount.getPublicKey(),
                                                                EthereumExternalSystemType, app.getDatabase());
        REQUIRE(!ethKey);

        SECTION("update account not allowed") {
            createAccountHelper.applyTx(createAccountTestBuilder
                                                .setType(AccountType::GENERAL)
                                                .setResultCode(CreateAccountResultCode::ALREADY_EXISTS)
                                                .setTxResultCode(TransactionResultCode::txFAILED));
        }
    }
    SECTION("Can't create system account") {
        auto systemCreateAccountBuilder = createAccountTestBuilder
                .setOperationResultCode(OperationResultCode::opNOT_ALLOWED)
                .setResultCode(CreateAccountResultCode::TYPE_NOT_ALLOWED)
                .setTxResultCode(TransactionResultCode::txFAILED);
        for (auto systemAccountType : getSystemAccountTypes()) {
            auto randomAccount = SecretKey::random();
            systemCreateAccountBuilder =
                    systemCreateAccountBuilder.setType(systemAccountType).setToPublicKey(randomAccount.getPublicKey());
            createAccountHelper.applyTx(systemCreateAccountBuilder);
        }
    }

    SECTION("Can create account with policies") {
        auto account = SecretKey::random();
        AccountID validReferrer = root.key.getPublicKey();

        auto accountTestBuilder = createAccountTestBuilder
                .setToPublicKey(account.getPublicKey())
                .setReferrer(&validReferrer);

        createAccountHelper.applyTx(accountTestBuilder.setType(AccountType::GENERAL)
                                            .setPolicies(AccountPolicies::ALLOW_TO_CREATE_USER_VIA_API));
    }

    SECTION("Can't create account with non-zero policies and NON_VERYFIED type") {
        auto account = SecretKey::random();
        AccountID validReferrer = root.key.getPublicKey();
        createAccountHelper.applyTx(
                createAccountTestBuilder
                        .setToPublicKey(account.getPublicKey())
                        .setType(AccountType::NOT_VERIFIED)
                        .setReferrer(&validReferrer)
                        .setPolicies(1)
                        .setRoleID(emptyAccountRoleID)
                        .setResultCode(CreateAccountResultCode::NOT_VERIFIED_CANNOT_HAVE_POLICIES)
                        .setTxResultCode(TransactionResultCode::txFAILED)
        );
    }

    SECTION("Root account can create account") {
        auto account = SecretKey::random();

        SECTION("referrer not found") {
            AccountID invalidReferrer = SecretKey::random().getPublicKey();
            createAccountHelper.applyTx(
                    createAccountTestBuilder
                            .setToPublicKey(account.getPublicKey())
                            .setReferrer(&invalidReferrer)
                            .setType(AccountType::GENERAL)
                            .setRoleID(emptyAccountRoleID)
            );
            auto accountFrame = AccountHelper::Instance()->loadAccount(account.getPublicKey(), app.getDatabase());
            REQUIRE(accountFrame);
            REQUIRE(!accountFrame->getReferrer());
        }

        AccountID validReferrer = root.key.getPublicKey();
        auto accountTestBuilder = createAccountTestBuilder
                .setType(AccountType::GENERAL)
                .setReferrer(&validReferrer)
                .setToPublicKey(account.getPublicKey())
                .setRoleID(emptyAccountRoleID);
        createAccountHelper.applyTx(accountTestBuilder);

       /* SECTION("Root can create GENERAL account only with account creator signer") {
            auto rootAcc = loadAccount(root.key.getPublicKey(), app);
            auto s1KP = SecretKey::random();
            auto signerTypes = xdr::xdr_traits<SignerType>::enum_values();
            for (auto signerType = signerTypes.begin();
                 signerType != signerTypes.end(); ++signerType) {
                auto s1 = Signer(s1KP.getPublicKey(), rootAcc->getMediumThreshold() + 1,
                                 static_cast<int32_t >(*signerType),
                                 1, "", Signer::_ext_t{});
                applySetOptions(app, root.key, root.getNextSalt(), nullptr, &s1);
                account = SecretKey::random();
                auto createAccount = accountTestBuilder.setType(AccountType::GENERAL).buildTx(testManager);
                createAccount->getEnvelope().signatures.clear();
                createAccount->addSignature(s1KP);
                auto mustApply = *signerType == static_cast<int32_t >(SignerType::GENERAL_ACC_MANAGER) ||
                                 *signerType == static_cast<int32_t >(SignerType::NOT_VERIFIED_ACC_MANAGER);
                REQUIRE(mustApply == testManager->applyCheck(createAccount));
            }
        }*/
    }

    SECTION("Non root account can't create") {
        for (auto accountType : xdr::xdr_traits<AccountType>::enum_values()) {
            // can be created only once
            if (isSystemAccountType(AccountType(accountType)) ||
                accountType == static_cast<int32_t >(AccountType::ACCREDITED_INVESTOR) ||
                accountType == static_cast<int32_t >(AccountType::INSTITUTIONAL_INVESTOR))
                continue;

            auto accountCreator = SecretKey::random();
            auto notAllowedBuilder = createAccountTestBuilder
                    .setToPublicKey(accountCreator.getPublicKey())
                    .setType(accountType);
            createAccountHelper.applyTx(notAllowedBuilder);
            auto accountCreatorSeq = 1;
            auto notRoot = Account{accountCreator, Salt(1)};
            auto toBeCreated = SecretKey::random();
            auto toBeCreatedHelper = notAllowedBuilder.setToPublicKey(toBeCreated.getPublicKey())
                    .setSource(notRoot)
                    .setType(AccountType::GENERAL)
                    .setOperationResultCode(OperationResultCode::opNO_ROLE_PERMISSION);
            createAccountHelper.applyTx(toBeCreatedHelper);
        }
    }
}
