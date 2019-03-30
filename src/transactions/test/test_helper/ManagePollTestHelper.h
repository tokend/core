#pragma once

#include "overlay/StellarXDR.h"
#include "TxHelper.h"
#include "transactions/test/TxTests.h"

namespace stellar
{

namespace txtest
{

class ManageCreatePollRequestTestBuilder : public OperationBuilder<ManageCreatePollRequestTestBuilder> {
public:
    ManageCreatePollRequestTestBuilder copy() override
    {
        return *this;
    }

    Operation buildOp() override;

    ManageCreatePollRequestTestBuilder setAction(ManageCreatePollRequestAction action);

    ManageCreatePollRequestTestBuilder setCreateRequestData(CreatePollRequestData data);

    ManageCreatePollRequestTestBuilder setClosePollData(ClosePollData data);

    ManageCreatePollRequestTestBuilder setCancelPollRequestData(CancelPollRequestData data);

    ManageCreatePollRequestTestBuilder setResultCode(ManageCreatePollRequestResultCode expectedResult);

    ManageCreatePollRequestTestBuilder setTxResultCode(
        TransactionResultCode expectedResult);

    TransactionResultCode expectedTxResult = TransactionResultCode::txSUCCESS;
    ManageCreatePollRequestResultCode expectedResult = ManageCreatePollRequestResultCode::SUCCESS;

    ManageCreatePollRequestAction action;
    CreatePollRequestData create;
    CancelPollRequestData cancel;
};

class ManagePollTestBuilder : public OperationBuilder<ManagePollTestBuilder> {
public:
    ManagePollTestBuilder copy() override
    {
        return *this;
    }

    Operation buildOp() override;

    ManagePollTestBuilder setAction(ManagePollAction action);

    ManagePollTestBuilder setClosePollData(ClosePollData data);

    ManagePollTestBuilder setPollID(uint64_t pollID);

    ManagePollTestBuilder setResultCode(ManagePollResultCode expectedResult);

    ManagePollTestBuilder setTxResultCode(
        TransactionResultCode expectedResult);

    TransactionResultCode expectedTxResult = TransactionResultCode::txSUCCESS;
    ManagePollResultCode expectedResult = ManagePollResultCode::SUCCESS;

    ManagePollAction action;
    ClosePollData close;
    uint64_t pollID;
};
class ManagePollTestHelper : public TxHelper
{
public:
    explicit ManagePollTestHelper(TestManager::pointer testManager);

    ManagePollResult applyTx(ManagePollTestBuilder builder);
    ManageCreatePollRequestResult applyTx(ManageCreatePollRequestTestBuilder builder);


};
}

}
