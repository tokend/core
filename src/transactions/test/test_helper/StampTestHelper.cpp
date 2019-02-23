#include "transactions/StampOpFrame.h"
#include "StampTestHelper.h"
#include "test/test_marshaler.h"

namespace stellar
{

namespace txtest
{

StampTestHelper::StampTestHelper(TestManager::pointer testManager)
        : TxHelper(testManager)
{
}

TransactionFramePtr
StampTestHelper::stamp(Account &source)
{
    Operation baseOp;
    baseOp.body.type(OperationType::STAMP);
    auto& op = baseOp.body.stampOp();
    op.ext.v(LedgerVersion::EMPTY_VERSION);
    return txFromOperation(source, baseOp, nullptr);
}

StampResult
StampTestHelper::applyStamp(txtest::Account& source, StampResultCode expectedResult)
{
    Database& db = mTestManager->getDB();

    auto txFrame = stamp(source);
    mTestManager->applyCheck(txFrame);
    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];
    auto actualResultCode = StampOpFrame::getInnerCode(opResult);

    REQUIRE(actualResultCode == expectedResult);

    return opResult.tr().stampResult();
}


}

}
