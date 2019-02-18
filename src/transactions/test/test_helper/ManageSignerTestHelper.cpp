#include <transactions/ManageSignerOpFrame.h>
#include <ledger/SignerHelper.h>
#include <ledger/SignerRuleFrame.h>
#include "ManageSignerTestHelper.h"
#include "test/test_marshaler.h"
#include "ledger/StorageHelper.h"

namespace stellar
{
namespace txtest
{

ManageSignerTestHelper::ManageSignerTestHelper(TestManager::pointer testManager)
        : TxHelper(testManager)
{
}

ManageSignerOp
ManageSignerTestHelper::buildCreateOp(PublicKey key, uint32_t weight,
                                      uint32_t identity, uint64_t roleID)
{
    ManageSignerOp op;
    op.data.action(ManageSignerAction::CREATE);
    auto& data = op.data.createData();
    data.publicKey = key;
    data.weight = weight;
    data.identity = identity;
    data.roleID = roleID;
    data.details = R"({"from":"create signer op"})";

    return op;
}

ManageSignerOp
ManageSignerTestHelper::buildUpdateOp(PublicKey key, uint32_t weight,
                                      uint32_t identity, uint64_t roleID)
{
    ManageSignerOp op;
    op.data.action(ManageSignerAction::UPDATE);
    auto& data = op.data.updateData();
    data.publicKey = key;
    data.weight = weight;
    data.identity = identity;
    data.roleID = roleID;
    data.details = R"({"from":"update signer op"})";

    return op;
}

ManageSignerOp
ManageSignerTestHelper::buildRemoveOp(PublicKey key)
{
    ManageSignerOp op;
    op.data.action(ManageSignerAction::REMOVE);
    auto& data = op.data.removeData();
    data.publicKey = key;

    return op;
}

TransactionFramePtr
ManageSignerTestHelper::buildTx(Account &source, const ManageSignerOp &op,
                                Account* signer)
{
    Operation baseOp;
    baseOp.body.type(OperationType::MANAGE_SIGNER);
    baseOp.body.manageSignerOp() = op;
    return txFromOperation(source, baseOp, signer);
}

ManageSignerResult
ManageSignerTestHelper::applyTx(Account &source, const ManageSignerOp &op,
                                ManageSignerResultCode expectedResultCode,
                                OperationResultCode expectedOpCode,
                                TransactionResultCode expectedTxResult,
                                Account* signer)
{
    auto txFrame = buildTx(source, op, signer);

    mTestManager->applyCheck(txFrame);
    auto txResult = txFrame->getResult();

    REQUIRE(txResult.result.code() == expectedTxResult);

    auto opResult = txResult.result.results()[0];

    REQUIRE(opResult.code() == expectedOpCode);
    if (opResult.code() != OperationResultCode::opINNER)
    {
        return ManageSignerResult();
    }
    auto actualResultCode = ManageSignerOpFrame::getInnerCode(opResult);
    REQUIRE(actualResultCode == expectedResultCode);

    if (expectedResultCode != ManageSignerResultCode::SUCCESS)
    {
        return ManageSignerResult{};
    }

    auto& signerHelper = mTestManager->getStorageHelper().getSignerHelper();
    PublicKey signerKey;
    bool isRequired = true;

    switch (op.data.action())
    {
        case ManageSignerAction::CREATE:
            signerKey = op.data.createData().publicKey;
            break;
        case ManageSignerAction::UPDATE:
            signerKey = op.data.updateData().publicKey;
            break;
        case ManageSignerAction::REMOVE:
            signerKey = op.data.removeData().publicKey;
            isRequired = false;
            break;
        default:
            throw std::runtime_error("Unexpected action");
    }

    auto signerFrame = signerHelper.loadSigner(signerKey, source.key.getPublicKey());
    if (isRequired)
    {
        REQUIRE(signerFrame);
    }
    else
    {
        REQUIRE(!signerFrame);
    }

    return opResult.tr().manageSignerResult();
}

void
ManageSignerTestHelper::applyCreateOperationalSigner(Account &source,
                                                     PublicKey signerKey)
{
    auto op = buildCreateOp(signerKey, SignerRuleFrame::threshold, 777, 1);

    applyTx(source, op);
}

}
}