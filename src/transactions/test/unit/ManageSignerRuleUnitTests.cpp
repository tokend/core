#include "transactions/test/mocks/MockLedgerHeaderFrame.h"
#include "transactions/manage_role_rule/ManageSignerRuleOpFrame.h"
#include "bucket/BucketManager.h"
#include "herder/Herder.h"
#include "invariant/Invariants.h"
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
#include "transactions/test/mocks/MockAccountSpecificRuleHelper.h"
#include "transactions/test/mocks/MockBalanceHelper.h"
#include "transactions/test/mocks/MockAccountRoleHelper.h"
#include "transactions/test/mocks/MockAccountRuleHelper.h"
#include "transactions/test/mocks/MockAccountHelper.h"
#include "transactions/test/mocks/MockSignerRuleVerifier.h"
#include "transactions/test/mocks/MockLicenseHelper.h"
#include "transactions/test/mocks/MockLicenseSignatureHelper.h"
#include "transactions/test/mocks/MockStampHelper.h"
#include "transactions/test/mocks/MockVoteHelper.h"
#include "transactions/test/mocks/MockPollHelper.h"
#include "util/StatusManager.h"
#include "util/TmpDir.h"
#include "work/WorkManager.h"

using namespace stellar;
using namespace testing;

TEST_CASE("manage signer rule unit test", "[tx][unit][manage_signer_rule]")
{
    MockApplication appMock;
    MockLedgerManager ledgerManagerMock;
    MockTransactionFrame transactionFrameMock;
    MockLedgerDelta ledgerDeltaMock;
    MockDatabase dbMock;
    MockStorageHelper storageHelperMock;
    MockLedgerHeaderFrame ledgerHeaderFrameMock;
    MockSignerRuleHelper signerRuleHelperMock;
    MockSignerRuleVerifier signerRuleVerifierMock;
    std::shared_ptr<MockSignatureValidator> signatureValidatorMock =
            std::make_shared<MockSignatureValidator>();

    auto secretKey = SecretKey::random();

    Operation op;
    op.body.type(OperationType::MANAGE_SIGNER_RULE);
    auto& operation = op.body.manageSignerRuleOp();
    op.sourceAccount.activate() = secretKey.getPublicKey();
    OperationResult operationResult;

    AccountFrame::pointer accountFrameFake =
            AccountFrame::makeAuthOnlyAccount(*op.sourceAccount);

    Database::EntryCache cacheFake(4096);

    ON_CALL(appMock, getDatabase()).WillByDefault(ReturnRef(dbMock));
    ON_CALL(appMock, getLedgerManager())
            .WillByDefault(ReturnRef(ledgerManagerMock));
    ON_CALL(storageHelperMock, getDatabase()).WillByDefault(ReturnRef(dbMock));
    ON_CALL(storageHelperMock, getLedgerDelta())
            .WillByDefault(Return(&ledgerDeltaMock));
    ON_CALL(transactionFrameMock, getSignatureValidator())
            .WillByDefault(Return(signatureValidatorMock));
    ON_CALL(*signatureValidatorMock,
            check(Ref(appMock), Ref(storageHelperMock), _, Const(*op.sourceAccount), _))
            .WillByDefault(Return(SignatureValidator::Result::SUCCESS));
    ON_CALL(dbMock, getEntryCache()).WillByDefault(ReturnRef(cacheFake));
    ON_CALL(storageHelperMock, getSignerRoleHelper());

    SECTION("invalid details")
    {
        operation.data.action(ManageSignerRuleAction::CREATE);
        operation.data.createData().details = "invalid details";

        operationResult.code(OperationResultCode::opINNER);
        operationResult.tr().type(OperationType::MANAGE_SIGNER_RULE);

        ManageSignerRuleOpFrame opFrame(op, operationResult, transactionFrameMock);

        REQUIRE_FALSE(opFrame.doCheckValid(appMock));
        REQUIRE(ManageSignerRuleOpFrame::getInnerCode(operationResult) ==
                ManageSignerRuleResultCode::INVALID_DETAILS);
    }

    SECTION("success create")
    {
        operation.data.action(ManageSignerRuleAction::CREATE);
        auto& createData = operation.data.createData();
        createData.details = "{}";
        createData.isReadOnly = false;
        createData.action = SignerRuleAction::MANAGE;
        createData.resource = SignerRuleResource(LedgerEntryType::ASSET_PAIR);
        createData.isDefault = false;
        createData.forbids = false;

        auto signerRuleFrame = std::make_shared<SignerRuleFrame>(1,
                secretKey.getPublicKey(), operation.data.createData());

        operationResult.code(OperationResultCode::opINNER);
        operationResult.tr().type(OperationType::MANAGE_SIGNER_RULE);

        ManageSignerRuleOpFrame opFrame(op, operationResult, transactionFrameMock);

        EXPECT_CALL(storageHelperMock, mustGetLedgerDelta())
                .WillOnce(ReturnRef(ledgerDeltaMock));
        EXPECT_CALL(ledgerDeltaMock, getHeaderFrame())
                .WillOnce(ReturnRef(ledgerHeaderFrameMock));
        EXPECT_CALL(ledgerHeaderFrameMock, generateID(LedgerEntryType::SIGNER_RULE))
                .WillOnce(Return(signerRuleFrame->getID()));
        EXPECT_CALL(appMock, getAdminID())
                .WillOnce(Return(secretKey.getPublicKey()));
        EXPECT_CALL(storageHelperMock, getSignerRuleHelper())
                .WillOnce(ReturnRef(signerRuleHelperMock));
        EXPECT_CALL(signerRuleHelperMock, storeAdd(signerRuleFrame->mEntry))
                .WillOnce(Return());

        REQUIRE(opFrame.doCheckValid(appMock));
        REQUIRE(opFrame.doApply(appMock, storageHelperMock, ledgerManagerMock));
        REQUIRE(ManageSignerRuleOpFrame::getInnerCode(operationResult) ==
                ManageSignerRuleResultCode::SUCCESS);

        CreateSignerRuleData data = createData;

        SECTION("update success")
        {
            operation.data.action(ManageSignerRuleAction::UPDATE);
            auto& updateData = operation.data.updateData();
            updateData.ruleID = signerRuleFrame->getID();
            updateData.details = R"({"data": "new details"})";
            updateData.action = data.action;
            updateData.resource = data.resource;
            updateData.isDefault = data.isDefault;
            updateData.forbids = data.forbids;

            signerRuleFrame->getEntry().details = updateData.details;

            operationResult.code(OperationResultCode::opINNER);
            operationResult.tr().type(OperationType::MANAGE_SIGNER_RULE);

            ManageSignerRuleOpFrame updateFrame(op, operationResult, transactionFrameMock);

            EXPECT_CALL(storageHelperMock, getSignerRuleHelper())
                    .WillOnce(ReturnRef(signerRuleHelperMock));
            EXPECT_CALL(signerRuleHelperMock, loadSignerRule(updateData.ruleID))
                    .WillOnce(Return(signerRuleFrame));
            EXPECT_CALL(signerRuleHelperMock, storeChange(signerRuleFrame->mEntry))
                    .Times(1);

            REQUIRE(updateFrame.doCheckValid(appMock));
            REQUIRE(updateFrame.doApply(appMock, storageHelperMock, ledgerManagerMock));
            REQUIRE(ManageSignerRuleOpFrame::getInnerCode(operationResult) ==
                    ManageSignerRuleResultCode::SUCCESS);
        }
    }
}
