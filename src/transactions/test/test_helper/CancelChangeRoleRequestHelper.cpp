#include "CancelChangeRoleRequestHelper.h"
#include "transactions/CancelChangeRoleRequestOpFrame.h"
#include "test/test_marshaler.h"
#include "ledger/ReviewableRequestHelper.h"

namespace stellar
{
namespace txtest
{
CancelChangeRoleRequestHelper::CancelChangeRoleRequestHelper(txtest::TestManager::pointer testManager)
: TxHelper(testManager) {}

CancelChangeRoleRequestResult
CancelChangeRoleRequestHelper::applyCancelChangeRoleRequest(txtest::Account &source, uint64_t requestID,
                                                                CancelChangeRoleRequestResultCode expectedResult)
{
    auto reviewableRequestHelper = ReviewableRequestHelperLegacy::Instance();
    auto reviewableRequestCountBeforeTx = reviewableRequestHelper->
            countObjects(mTestManager->getDB().getSession());


    auto txFrame = cancelChangeRoleRequest(source, requestID);
    mTestManager->applyCheck(txFrame);
    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];

    auto actualResultCode =
            CancelChangeRoleRequestOpFrame::getInnerCode(opResult);
    REQUIRE(actualResultCode == expectedResult);

    auto reviewableRequestCountAfterTx = reviewableRequestHelper->
            countObjects(mTestManager->getDB().getSession());
    if (expectedResult != CancelChangeRoleRequestResultCode::SUCCESS)
    {
        REQUIRE(reviewableRequestCountBeforeTx == reviewableRequestCountAfterTx);
        return CancelChangeRoleRequestResult{};
    }

    REQUIRE(reviewableRequestCountBeforeTx == reviewableRequestCountAfterTx + 1);

    return opResult.tr().cancelChangeRoleRequestResult();
}

TransactionFramePtr
CancelChangeRoleRequestHelper::cancelChangeRoleRequest(txtest::Account &source, uint64_t requestID)
{
    Operation baseOp;
    baseOp.body.type(OperationType::CANCEL_CHANGE_ROLE_REQUEST);
    auto& op = baseOp.body.cancelChangeRoleRequestOp();
    op.requestID = requestID;
    op.ext.v(LedgerVersion::EMPTY_VERSION);
    return txFromOperation(source, baseOp, nullptr);
}
}
}
