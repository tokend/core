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
#include "ledger/AccountHelperLegacy.h"
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
                                                .setResultCode(CreateAccountResultCode::ALREADY_EXISTS)
                                                .setTxResultCode(TransactionResultCode::txFAILED));
        }
    }

    SECTION("Root account can create account")
    {
        auto account = SecretKey::random();

        AccountID validReferrer = root.key.getPublicKey();
        auto accountTestBuilder = createAccountTestBuilder
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

    SECTION("Non root account can't create")
    {
            auto emptyRoleID = manageAccountRoleTestHelper.createTxSenderRole(root);
            auto accountCreator = SecretKey::random();
            auto notAllowedBuilder = createAccountTestBuilder
                    .setToPublicKey(accountCreator.getPublicKey())
                    .setRoleID(emptyRoleID);
            createAccountHelper.applyTx(notAllowedBuilder);
            auto notRoot = Account{accountCreator, Salt(1)};
            auto toBeCreated = SecretKey::random();
            auto toBeCreatedHelper = notAllowedBuilder.setToPublicKey(toBeCreated.getPublicKey())
                    .setSource(notRoot)
                    .setOperationResultCode(OperationResultCode::opNO_ROLE_PERMISSION)
                    .setTxResultCode(TransactionResultCode::txFAILED);
            createAccountHelper.applyTx(toBeCreatedHelper);
    }
}
