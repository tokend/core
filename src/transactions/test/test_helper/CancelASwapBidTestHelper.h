#pragma once

#include "TxHelper.h"

namespace stellar
{

namespace txtest
{

class CancelASwapBidHelper : TxHelper
{
public:
explicit CancelASwapBidHelper(TestManager::pointer testManager);

TransactionFramePtr createCancelASwapBidTx(Account& source, uint64_t bidID);

CancelAtomicSwapBidResult applyCancelASwapBid(Account& source, uint64_t bidID,
                                         CancelAtomicSwapBidResultCode expectedResult =
                                         CancelAtomicSwapBidResultCode::SUCCESS,
                                         OperationResultCode expectedOpCode =
                                         OperationResultCode::opINNER);
};

}

}