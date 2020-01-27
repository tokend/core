#include "transactions/LicenseOpFrame.h"
#include "ledger/LicenseHelper.h"
#include "ledger/StorageHelper.h"
#include "LicenseTestHelper.h"
#include "test/test_marshaler.h"

namespace stellar
{

namespace txtest
{

LicenseTestHelper::LicenseTestHelper(TestManager::pointer testManager)
        : TxHelper(testManager)
{
}

TransactionFramePtr
LicenseTestHelper::createLicenseOp(Account& source, std::vector<SecretKey> wiredKeys, Hash ledgerHash, Hash prevLicenseHash, uint64_t adminCount, uint64_t dueDate)
{
    Operation baseOp;
    baseOp.body.type(OperationType::LICENSE);
    auto& op = baseOp.body.licenseOp();
    auto signatureData = LicenseFrame::getSignatureData(ledgerHash, prevLicenseHash, adminCount, dueDate);
    op.ledgerHash = ledgerHash;
    op.prevLicenseHash = prevLicenseHash;
    op.adminCount = adminCount;
    op.dueDate = dueDate;

    for(auto key = wiredKeys.begin(); key != wiredKeys.end(); key++) {
        auto sig = createLicenseSignature(*key, signatureData);
        op.signatures.push_back(sig);
    }

    op.ext.v(LedgerVersion::EMPTY_VERSION);
    return txFromOperation(source, baseOp, nullptr);
}

DecoratedSignature LicenseTestHelper::createLicenseSignature(SecretKey & wiredKey, Hash signatureData)
{
    DecoratedSignature sig;
    sig.signature = wiredKey.sign(signatureData);
    sig.hint = PubKeyUtils::getHint(wiredKey.getPublicKey());
    return sig;
}

LicenseResult
LicenseTestHelper::applyLicenseOp(Account& source, std::vector<SecretKey> wiredKeys, Hash ledgerHash, Hash prevLicenseHash, uint64_t adminCount, uint64_t dueDate, LicenseResultCode expectedResult)
{

    auto& licenseHelper = mTestManager->getStorageHelper().getLicenseHelper();
    auto prevLicenseEntry = licenseHelper.loadCurrentLicense();

    if (prevLicenseEntry)
    {
        auto actualPrevLicenseHash = prevLicenseEntry->getFullHash();

        REQUIRE(actualPrevLicenseHash == prevLicenseHash);

    }
    auto txFrame = createLicenseOp(source, wiredKeys, ledgerHash, prevLicenseHash, adminCount, dueDate);
    mTestManager->applyCheck(txFrame);
    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];
    auto actualResultCode = LicenseOpFrame::getInnerCode(opResult);

    REQUIRE(actualResultCode == expectedResult);

    auto licenseResult = opResult.tr().licenseResult();

    if (expectedResult != LicenseResultCode::SUCCESS)
    {
        return licenseResult;
    }

    auto newLicenseFrame = licenseHelper.loadCurrentLicense();

    REQUIRE(newLicenseFrame->getLicenseEntry().adminCount == adminCount);
    REQUIRE(newLicenseFrame->getLicenseEntry().dueDate == dueDate);
    REQUIRE(newLicenseFrame->getLicenseEntry().ledgerHash == ledgerHash);
    REQUIRE(newLicenseFrame->getLicenseEntry().prevLicenseHash == prevLicenseHash);

    return licenseResult;
}


}

}
