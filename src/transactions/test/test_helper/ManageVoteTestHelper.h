#pragma once

// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "overlay/StellarXDR.h"
#include "TxHelper.h"
#include "transactions/test/TxTests.h"

namespace stellar
{

namespace txtest
{

class ManageVoteTestBuilder : public OperationBuilder<ManageVoteTestBuilder> {
public:
    ManageVoteTestBuilder copy() override
    {
        return *this;
    }

    Operation buildOp() override;

    ManageVoteTestBuilder setAction(ManageVoteAction action);

    ManageVoteTestBuilder setCreateVoteData(CreateVoteData data);

    ManageVoteTestBuilder setRemoveVoteData(RemoveVoteData data);

    ManageVoteTestBuilder setResultCode(ManageVoteResultCode expectedResult);

    ManageVoteTestBuilder setTxResultCode(
        TransactionResultCode expectedResult);

    TransactionResultCode expectedTxResult = TransactionResultCode::txSUCCESS;
    ManageVoteResultCode expectedResult = ManageVoteResultCode::SUCCESS;

    ManageVoteAction action;
    CreateVoteData create;
    RemoveVoteData remove;
};
class ManageVoteTestHelper : public TxHelper
{
public:
    explicit ManageVoteTestHelper(TestManager::pointer testManager);

    ManageVoteResult applyTx(ManageVoteTestBuilder builder);


};
}

}
