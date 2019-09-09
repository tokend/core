#include <crypto/SHA.h>
#include "test/test_marshaler.h"
#include "invariant/InvariantManagerImpl.h"
#include "herder/HerderPersistenceImpl.h"
#include "main/Maintainer.h"
#include "history/HistoryArchiveManager.h"
#include "transactions/SignatureValidatorImpl.h"
#include "transactions/test/mocks/MockApplication.h"
#include "transactions/test/mocks/MockStorageHelper.h"
#include "transactions/test/mocks/MockSignerRuleVerifier.h"
#include "transactions/test/mocks/MockAccountRuleHelper.h"
#include "transactions/test/mocks/MockAssetHelper.h"
#include "transactions/test/mocks/MockBalanceHelper.h"
#include "transactions/test/mocks/MockAccountRoleHelper.h"
#include "transactions/test/mocks/MockAccountRuleHelper.h"
#include "transactions/test/mocks/MockAccountHelper.h"
#include "transactions/test/mocks/MockExternalSystemAccountIDHelper.h"
#include "transactions/test/mocks/MockExternalSystemAccountIDPoolEntryHelper.h"
#include "transactions/test/mocks/MockKeyValueHelper.h"
#include "transactions/test/mocks/MockSignerHelper.h"
#include "transactions/test/mocks/MockSignerRuleHelper.h"
#include "transactions/test/mocks/MockSignerRoleHelper.h"
#include "transactions/test/mocks/MockLedgerDelta.h"
#include "transactions/test/mocks/MockLedgerHeaderFrame.h"
#include "transactions/test/mocks/MockDatabase.h"
#include "transactions/test/mocks/MockLicenseHelper.h"
#include "transactions/test/mocks/MockLicenseSignatureHelper.h"
#include "transactions/test/mocks/MockStampHelper.h"
#include "transactions/test/mocks/MockVoteHelper.h"
#include "transactions/test/mocks/MockPollHelper.h"
#include "transactions/test/mocks/MockAccountSpecificRuleHelper.h"
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
#include "util/StatusManager.h"
#include "work/WorkManager.h"
#include "util/TmpDir.h"

using namespace stellar;
using namespace testing;

TEST_CASE("Signature validator", "[tx][unit][signature_validator]")
{
    MockApplication appMock;
    MockStorageHelper storageHelperMock;
    MockSignerHelper signerHelperMock;
    MockSignerRuleVerifier signerRuleVerifierMock;
    Config config;

    Hash content = sha256("Some content");
    xdr::xvector<DecoratedSignature, 20>  signatures;
    std::vector<SignerFrame::pointer> signers;
    for (uint32_t i = 0; i < 3; i++)
    {
        auto secretKey = SecretKey::random();
        DecoratedSignature signature;
        signature.signature = secretKey.sign(content);
        signature.hint = PubKeyUtils::getHint(secretKey.getPublicKey());
        signatures.emplace_back(signature);
        auto signer = std::make_shared<SignerFrame>();
        signer->getEntry().pubKey = secretKey.getPublicKey();
        signer->getEntry().weight = 334;
        signer->getEntry().identity = i;
        signers.emplace_back(signer);
    }

    AccountID source = SecretKey::random().getPublicKey();
    SignatureValidatorImpl signatureValidator(content, signatures);

    SECTION("One operation")
    {

        SECTION("Success")
        {
            EXPECT_CALL(appMock, getConfig())
                    .WillOnce(ReturnRef(Const(config)));
            EXPECT_CALL(storageHelperMock, getSignerHelper())
                    .WillOnce(ReturnRef(signerHelperMock));
            EXPECT_CALL(signerHelperMock, loadSigners(Ref(Const(source))))
                    .WillOnce(Return(signers));
            EXPECT_CALL(signerRuleVerifierMock, isAllowed(_, _, Ref(storageHelperMock)))
                    .Times(3).WillRepeatedly(Return(true));

            auto result = signatureValidator.check(appMock, storageHelperMock,
                    signerRuleVerifierMock, source,
                    {SignerRequirement(SignerRuleResource(LedgerEntryType::SALE), SignerRuleAction::MANAGE)});

            REQUIRE(result == SignatureValidatorImpl::Result::SUCCESS);
            REQUIRE(signatureValidator.checkAllSignaturesUsed());
        }

        SECTION("Not enough weight")
        {
            EXPECT_CALL(appMock, getConfig())
                    .WillOnce(ReturnRef(Const(config)));
            EXPECT_CALL(storageHelperMock, getSignerHelper())
                    .WillOnce(ReturnRef(signerHelperMock));
            EXPECT_CALL(signerHelperMock, loadSigners(Ref(Const(source))))
                    .WillOnce(Return(signers));
            EXPECT_CALL(signerRuleVerifierMock, isAllowed(_, _, Ref(storageHelperMock)))
                    .Times(3).WillOnce(Return(false)).WillRepeatedly(Return(true));

            auto result = signatureValidator.check(appMock, storageHelperMock,
                    signerRuleVerifierMock, source,
                    {SignerRequirement(SignerRuleResource(LedgerEntryType::SALE), SignerRuleAction::MANAGE)});

            REQUIRE(result == SignatureValidatorImpl::Result::NOT_ENOUGH_WEIGHT);
        }

        SECTION("Extra")
        {
            signers[0]->getEntry().weight = 700;
            EXPECT_CALL(appMock, getConfig())
                    .WillOnce(ReturnRef(Const(config)));
            EXPECT_CALL(storageHelperMock, getSignerHelper())
                    .WillOnce(ReturnRef(signerHelperMock));
            EXPECT_CALL(signerHelperMock, loadSigners(Ref(Const(source))))
                    .WillOnce(Return(signers));
            EXPECT_CALL(signerRuleVerifierMock, isAllowed(_, _, Ref(storageHelperMock)))
                    .Times(2).WillRepeatedly(Return(true));

            auto result = signatureValidator.check(appMock, storageHelperMock,
                    signerRuleVerifierMock, source,
                    {SignerRequirement(SignerRuleResource(LedgerEntryType::SALE), SignerRuleAction::MANAGE)});

            REQUIRE(result == SignatureValidatorImpl::Result::SUCCESS);
            REQUIRE(!signatureValidator.checkAllSignaturesUsed());
        }

        SECTION("Try to use signers with fewer weight")
        {
            for (uint32_t i = 0; i < 3; i++)
            {
                auto secretKey = SecretKey::random();
                DecoratedSignature signature;
                signature.signature = secretKey.sign(content);
                signature.hint = PubKeyUtils::getHint(secretKey.getPublicKey());
                signatures.insert(signatures.begin(), signature);
                auto signer = std::make_shared<SignerFrame>();
                signer->getEntry().pubKey = secretKey.getPublicKey();
                signer->getEntry().weight = i;
                signer->getEntry().identity = i;
                signers.emplace_back(signer);
            }

            signatureValidator = SignatureValidatorImpl(content, signatures);

            EXPECT_CALL(appMock, getConfig())
                    .WillOnce(ReturnRef(Const(config)));
            EXPECT_CALL(storageHelperMock, getSignerHelper())
                    .WillOnce(ReturnRef(signerHelperMock));
            EXPECT_CALL(signerHelperMock, loadSigners(Ref(Const(source))))
                    .WillOnce(Return(signers));
            EXPECT_CALL(signerRuleVerifierMock, isAllowed(_, _, Ref(storageHelperMock)))
                    .Times(6).WillRepeatedly(Return(true));

            auto result = signatureValidator.check(appMock, storageHelperMock,
                    signerRuleVerifierMock, source,
                    {SignerRequirement(SignerRuleResource(LedgerEntryType::SALE), SignerRuleAction::MANAGE)});

            REQUIRE(result == SignatureValidatorImpl::Result::SUCCESS);
            REQUIRE(!signatureValidator.checkAllSignaturesUsed());
        }
    }

    SECTION("Two operations")
    {
        for (auto& signer : signers)
        {
            signer->getEntry().weight = signer->getEntry().weight * 2;
        }


        SECTION("Success")
        {
            SignerRequirement saleReq(SignerRuleResource(LedgerEntryType::SALE), SignerRuleAction::MANAGE);
            EXPECT_CALL(appMock, getConfig())
                    .WillOnce(ReturnRef(Const(config)));
            EXPECT_CALL(storageHelperMock, getSignerHelper())
                    .WillOnce(ReturnRef(signerHelperMock));
            EXPECT_CALL(signerHelperMock, loadSigners(Ref(Const(source))))
                    .WillOnce(Return(signers));
            EXPECT_CALL(signerRuleVerifierMock, isAllowed(_, _, Ref(storageHelperMock)))
                    .Times(2).WillRepeatedly(Return(true));

            auto result = signatureValidator.check(appMock, storageHelperMock,
                    signerRuleVerifierMock, source,
                    {saleReq});

            REQUIRE(result == SignatureValidatorImpl::Result::SUCCESS);
            REQUIRE(!signatureValidator.checkAllSignaturesUsed());

            SignerRequirement feeReq(SignerRuleResource(LedgerEntryType::FEE), SignerRuleAction::MANAGE);
            EXPECT_CALL(appMock, getConfig())
                    .WillOnce(ReturnRef(Const(config)));
            EXPECT_CALL(storageHelperMock, getSignerHelper())
                    .WillOnce(ReturnRef(signerHelperMock));
            EXPECT_CALL(signerHelperMock, loadSigners(Ref(Const(source))))
                    .WillOnce(Return(signers));
            EXPECT_CALL(signerRuleVerifierMock, isAllowed(_, _, Ref(storageHelperMock)))
                    .Times(3).WillOnce(Return(false)).WillRepeatedly(Return(true));

            result = signatureValidator.check(appMock, storageHelperMock,
                    signerRuleVerifierMock, source,
                    {feeReq});

            REQUIRE(result == SignatureValidatorImpl::Result::SUCCESS);
            REQUIRE(signatureValidator.checkAllSignaturesUsed());
        }

        SECTION("Not enough weight")
        {
            EXPECT_CALL(appMock, getConfig())
                    .WillOnce(ReturnRef(Const(config)));
            EXPECT_CALL(storageHelperMock, getSignerHelper())
                    .WillOnce(ReturnRef(signerHelperMock));
            EXPECT_CALL(signerHelperMock, loadSigners(Ref(Const(source))))
                    .WillOnce(Return(signers));
            EXPECT_CALL(signerRuleVerifierMock, isAllowed(_, _, Ref(storageHelperMock)))
                    .Times(2).WillRepeatedly(Return(true));

            auto result = signatureValidator.check(appMock, storageHelperMock,
                    signerRuleVerifierMock, source,
                    {SignerRequirement(SignerRuleResource(LedgerEntryType::SALE), SignerRuleAction::MANAGE)});

            REQUIRE(result == SignatureValidatorImpl::Result::SUCCESS);
            REQUIRE(!signatureValidator.checkAllSignaturesUsed());

            EXPECT_CALL(appMock, getConfig())
                    .WillOnce(ReturnRef(Const(config)));
            EXPECT_CALL(storageHelperMock, getSignerHelper())
                    .WillOnce(ReturnRef(signerHelperMock));
            EXPECT_CALL(signerHelperMock, loadSigners(Ref(Const(source))))
                    .WillOnce(Return(signers));
            EXPECT_CALL(signerRuleVerifierMock, isAllowed(_, _, Ref(storageHelperMock)))
                    .WillOnce(Return(false)).WillOnce(Return(false)).WillOnce(Return(true));

            result = signatureValidator.check(appMock, storageHelperMock,
                    signerRuleVerifierMock, source,
                    {SignerRequirement(SignerRuleResource(LedgerEntryType::SALE), SignerRuleAction::MANAGE)});

            REQUIRE(result == SignatureValidatorImpl::Result::NOT_ENOUGH_WEIGHT);
        }

        SECTION("Extra")
        {
            signers[0]->getEntry().weight = 1000;
            signers[1]->getEntry().weight = 1000;
            EXPECT_CALL(appMock, getConfig())
                    .WillOnce(ReturnRef(Const(config)));
            EXPECT_CALL(storageHelperMock, getSignerHelper())
                    .WillOnce(ReturnRef(signerHelperMock));
            EXPECT_CALL(signerHelperMock, loadSigners(Ref(Const(source))))
                    .WillOnce(Return(signers));
            EXPECT_CALL(signerRuleVerifierMock, isAllowed(_, _, Ref(storageHelperMock)))
                    .WillOnce(Return(true));

            auto result = signatureValidator.check(appMock, storageHelperMock,
                    signerRuleVerifierMock, source,
                    {SignerRequirement(SignerRuleResource(LedgerEntryType::SALE), SignerRuleAction::MANAGE)});

            REQUIRE(result == SignatureValidatorImpl::Result::SUCCESS);
            REQUIRE(!signatureValidator.checkAllSignaturesUsed());

            EXPECT_CALL(appMock, getConfig())
                    .WillOnce(ReturnRef(Const(config)));
            EXPECT_CALL(storageHelperMock, getSignerHelper())
                    .WillOnce(ReturnRef(signerHelperMock));
            EXPECT_CALL(signerHelperMock, loadSigners(Ref(Const(source))))
                    .WillOnce(Return(signers));
            EXPECT_CALL(signerRuleVerifierMock, isAllowed(_, _, Ref(storageHelperMock)))
                    .WillOnce(Return(false)).WillOnce(Return(true));

            result = signatureValidator.check(appMock, storageHelperMock,
                    signerRuleVerifierMock, source,
                    {SignerRequirement(SignerRuleResource(LedgerEntryType::SALE), SignerRuleAction::MANAGE)});

            REQUIRE(result == SignatureValidatorImpl::Result::SUCCESS);
            REQUIRE(!signatureValidator.checkAllSignaturesUsed());
        }
    }
}
