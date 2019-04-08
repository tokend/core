#include "bucket/BucketManager.h"
#include "herder/Herder.h"
#include "invariant/Invariants.h"
#include "ledger/LedgerHeaderFrame.h"
#include "main/CommandHandler.h"
#include "main/PersistentState.h"
#include "medida/metrics_registry.h"
#include "overlay/BanManager.h"
#include "overlay/OverlayManager.h"
#include "process/ProcessManager.h"
#include "simulation/LoadGenerator.h"
#include "test/test_marshaler.h"
#include "invariant/InvariantManagerImpl.h"
#include "herder/HerderPersistenceImpl.h"
#include "main/Maintainer.h"
#include "history/HistoryArchiveManager.h"
#include "herder/LedgerCloseData.h"
#include "transactions/external_system_pool/BindExternalSystemAccountIdOpFrame.h"
#include "transactions/test/mocks/MockApplication.h"
#include "transactions/test/mocks/MockDatabase.h"
#include "transactions/test/mocks/MockAccountRuleVerifier.h"
#include "transactions/test/mocks/MockExternalSystemAccountIDHelper.h"
#include "transactions/test/mocks/MockExternalSystemAccountIDPoolEntryHelper.h"
#include "transactions/test/mocks/MockKeyValueHelper.h"
#include "transactions/test/mocks/MockSignerHelper.h"
#include "transactions/test/mocks/MockSignerRuleHelper.h"
#include "transactions/test/mocks/MockSignerRoleHelper.h"
#include "transactions/test/mocks/MockLedgerDelta.h"
#include "transactions/test/mocks/MockLedgerManager.h"
#include "transactions/test/mocks/MockSignatureValidator.h"
#include "transactions/test/mocks/MockStorageHelper.h"
#include "transactions/test/mocks/MockTransactionFrame.h"
#include "transactions/test/mocks/MockAccountRuleHelper.h"
#include "transactions/test/mocks/MockAssetHelper.h"
#include "transactions/test/mocks/MockBalanceHelper.h"
#include "transactions/test/mocks/MockAccountRoleHelper.h"
#include "transactions/test/mocks/MockAccountRuleHelper.h"
#include "transactions/test/mocks/MockAccountHelper.h"
#include "transactions/test/mocks/MockSignerRuleVerifier.h"
#include "transactions/test/mocks/MockLicenseHelper.h"
#include "transactions/test/mocks/MockLicenseSignatureHelper.h"
#include "transactions/test/mocks/MockStampHelper.h"
#include "util/StatusManager.h"
#include "util/TmpDir.h"
#include "work/WorkManager.h"

using namespace stellar;
using namespace testing;

TEST_CASE("bind external system account_id - unit test",
          "[tx][bind_external_system_account_id_unit_test]")
{
    MockApplication appMock;
    MockLedgerManager ledgerManagerMock;
    MockTransactionFrame transactionFrameMock;
    MockLedgerDelta ledgerDeltaMock;
    MockDatabase dbMock;
    MockStorageHelper storageHelperMock;
    MockSignerHelper signerHelperMock;
    MockSignerRuleHelper signerRuleHelperMock;
    MockSignerRoleHelper signerRoleHelperMock;
    MockKeyValueHelper keyValueHelperMock;
    MockAccountRuleVerifier accountRuleVerifierMock;
    MockExternalSystemAccountIDHelper externalSystemAccountIDHelperMock;
    MockExternalSystemAccountIDPoolEntryHelper
        externalSystemAccountIDPoolEntryHelperMock;
    MockSignerRuleVerifier signerRuleVerifierMock;
    std::shared_ptr<MockSignatureValidator> signatureValidatorMock =
        std::make_shared<MockSignatureValidator>();

    BindExternalSystemAccountIdOp op;
    op.externalSystemType = 5;
    Operation operation;
    operation.body = Operation::_body_t(
        stellar::OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID);
    operation.body.bindExternalSystemAccountIdOp() = op;
    operation.sourceAccount =
        xdr::pointer<AccountID>(new AccountID(CryptoKeyType::KEY_TYPE_ED25519));
    operation.sourceAccount->ed25519() = hexToBin256(
            "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABB");
    OperationResult operationResult;

    AccountFrame::pointer accountFrameFake =
        AccountFrame::makeAuthOnlyAccount(*operation.sourceAccount);
    LedgerHeader ledgerHeaderFake;

    Database::EntryCache cacheFake(4096);

    ON_CALL(appMock, getDatabase()).WillByDefault(ReturnRef(dbMock));
    ON_CALL(appMock, getLedgerManager())
        .WillByDefault(ReturnRef(ledgerManagerMock));
    ON_CALL(ledgerManagerMock, getCurrentLedgerHeader())
        .WillByDefault(ReturnRef(ledgerHeaderFake));
    ON_CALL(storageHelperMock, getDatabase()).WillByDefault(ReturnRef(dbMock));
    ON_CALL(storageHelperMock, getLedgerDelta())
        .WillByDefault(Return(&ledgerDeltaMock));
    ON_CALL(transactionFrameMock, getSignatureValidator())
        .WillByDefault(Return(signatureValidatorMock));
    ON_CALL(*signatureValidatorMock,
            check(Ref(appMock), _, _, Const(*operation.sourceAccount), _))
        .WillByDefault(Return(SignatureValidator::Result::SUCCESS));
    ON_CALL(dbMock, getEntryCache()).WillByDefault(ReturnRef(cacheFake));

    ON_CALL(storageHelperMock, getKeyValueHelper())
        .WillByDefault(ReturnRef(keyValueHelperMock));
    ON_CALL(storageHelperMock, getSignerHelper())
            .WillByDefault(ReturnRef(signerHelperMock));
    ON_CALL(storageHelperMock, getSignerRuleHelper())
            .WillByDefault(ReturnRef(signerRuleHelperMock));
    ON_CALL(storageHelperMock, getSignerRoleHelper())
            .WillByDefault(ReturnRef(signerRoleHelperMock));
    ON_CALL(storageHelperMock, getExternalSystemAccountIDHelper())
        .WillByDefault(ReturnRef(externalSystemAccountIDHelperMock));
    ON_CALL(storageHelperMock, getExternalSystemAccountIDPoolEntryHelper())
        .WillByDefault(ReturnRef(externalSystemAccountIDPoolEntryHelperMock));
    ON_CALL(accountRuleVerifierMock, isAllowed(_, _))
            .WillByDefault(Return(true));

    BindExternalSystemAccountIdOpFrame opFrame(operation, operationResult,
                                               transactionFrameMock);
    SECTION("Check validity")
    {
        EXPECT_CALL(transactionFrameMock,
                    loadAccount(&ledgerDeltaMock, Ref(dbMock),
                                *operation.sourceAccount))
            .WillOnce(Return(accountFrameFake));
        REQUIRE(opFrame.checkValid(appMock, accountRuleVerifierMock, &ledgerDeltaMock));

        SECTION("Apply, no pool entry to bind")
        {
            EXPECT_CALL(externalSystemAccountIDPoolEntryHelperMock,
                        load(op.externalSystemType, *operation.sourceAccount))
                .WillOnce(Return(nullptr));
            EXPECT_CALL(externalSystemAccountIDPoolEntryHelperMock,
                        loadAvailablePoolEntry(Ref(ledgerManagerMock),
                                               op.externalSystemType))
                .WillOnce(Return(nullptr));
            REQUIRE_FALSE(
                opFrame.doApply(appMock, storageHelperMock, ledgerManagerMock));
            REQUIRE(opFrame.getResult()
                        .tr()
                        .bindExternalSystemAccountIdResult()
                        .code() ==
                    BindExternalSystemAccountIdResultCode::NO_AVAILABLE_ID);
        }
    }
}
