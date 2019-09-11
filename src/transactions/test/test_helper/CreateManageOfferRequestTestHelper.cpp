#include "CreateManageOfferRequestTestHelper.h"
#include "ManageOfferTestHelper.h"
#include "bucket/BucketApplicator.h"
#include "ledger/AccountHelperLegacy.h"
#include "test/test_marshaler.h"

namespace stellar
{

using xdr::operator==;

namespace txtest
{
CreateManageOfferRequestTestHelper::CreateManageOfferRequestTestHelper(
    const TestManager::pointer testManager)
    : TxHelper(testManager)
{
}

TransactionFramePtr
CreateManageOfferRequestTestHelper::createManageOfferRequestTx(
    Account& source, ManageOfferOp const& manageOfferOp, uint32* allTasks)
{
    Operation baseOp;
    baseOp.body.type(OperationType::CREATE_MANAGE_OFFER_REQUEST);
    auto& op = baseOp.body.createManageOfferRequestOp();
    op.request.op = manageOfferOp;
    if (allTasks != nullptr)
    {
        op.allTasks.activate() = *allTasks;
    }

    return txFromOperation(source, baseOp, nullptr);
}

CreateManageOfferRequestResult
CreateManageOfferRequestTestHelper::applyTx(
    Account& source, ManageOfferOp const& op, uint32* allTasks,
    CreateManageOfferRequestResultCode expectedResultCode)
{
    auto txFrame = createManageOfferRequestTx(source, op, allTasks);

    std::vector<LedgerDelta::KeyEntryMap> stateBeforeOps;
    mTestManager->applyCheck(txFrame, stateBeforeOps);

    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];
    auto const& actualResult = opResult.tr().createManageOfferRequestResult();
    auto const& actualResultCode = actualResult.code();
    REQUIRE(actualResultCode == expectedResultCode);

    if (actualResultCode != CreateManageOfferRequestResultCode::SUCCESS)
    {
        return actualResult;
    }

    if (allTasks != nullptr && *allTasks == 0)
    {
        return checkApprovedCreation(source, actualResult, op,
                                     stateBeforeOps[0]);
    }

    REQUIRE_FALSE(actualResult.success().fulfilled);

    return actualResult;
}

CreateManageOfferRequestResult
CreateManageOfferRequestTestHelper::checkApprovedCreation(
    Account& source, CreateManageOfferRequestResult opResult,
    ManageOfferOp const& op, LedgerDelta::KeyEntryMap stateBeforeOp)
{
    REQUIRE(opResult.success().fulfilled);

    ManageOfferTestHelper manageOfferTestHelper(mTestManager);
    manageOfferTestHelper.ensureCreateSuccess(
        source, op, opResult.success().manageOfferResult->success(),
        stateBeforeOp);

    return opResult;
}


}
}
