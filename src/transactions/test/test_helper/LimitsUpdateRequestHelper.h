#pragma once

// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ledger/AccountLimitsFrame.h"
#include <ledger/ReviewableRequestFrame.h>
#include "overlay/StellarXDR.h"
#include "TxHelper.h"

namespace stellar
{
namespace txtest
{
class LimitsUpdateRequestHelper : TxHelper
{
public:
    explicit LimitsUpdateRequestHelper(TestManager::pointer testManager);

    CreateManageLimitsRequestResult
    applyCreateLimitsUpdateRequest(Account &source, LimitsUpdateRequest request, uint32_t *allTasks,
                                       uint64_t *requestID = 0,
                                       CreateManageLimitsRequestResultCode expectedResult = CreateManageLimitsRequestResultCode::SUCCESS,
                                       OperationResultCode expectedOpResultCode = OperationResultCode::opINNER);

    static LimitsUpdateRequest createLimitsUpdateRequest(longstring details);

    TransactionFramePtr createLimitsUpdateRequestTx(Account& source, LimitsUpdateRequest request,
                                                    uint32_t* allTasks,
                                                    uint64_t* requestID = 0);
};
}
}