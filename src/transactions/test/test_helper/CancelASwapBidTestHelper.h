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

CancelASwapBidResult applyCancelASwapBid(Account& source, uint64_t bidID,
                                         CancelASwapBidResultCode expectedResult =
                                         CancelASwapBidResultCode::SUCCESS,
                                         OperationResultCode expectedOpCode =
                                         OperationResultCode::opINNER);
};

}

}