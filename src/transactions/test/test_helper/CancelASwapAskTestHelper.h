#pragma once

#include "TxHelper.h"

namespace stellar
{

namespace txtest
{

class CancelASwapAskHelper : TxHelper
{
public:
explicit CancelASwapAskHelper(TestManager::pointer testManager);

TransactionFramePtr createCancelASwapAskTx(Account &source, uint64_t bidID);

CancelAtomicSwapAskResult applyCancelASwapBid(Account& source, uint64_t bidID,
                                         CancelAtomicSwapAskResultCode expectedResult =
                                         CancelAtomicSwapAskResultCode::SUCCESS,
                                         OperationResultCode expectedOpCode =
                                         OperationResultCode::opINNER);
};

}

}