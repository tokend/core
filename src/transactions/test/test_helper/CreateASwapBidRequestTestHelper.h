#pragma once

#include "TxHelper.h"

namespace stellar
{
namespace txtest
{
class CreateASwapBidRequestTestHelper : TxHelper
{
public:
    explicit
    CreateASwapBidRequestTestHelper(TestManager::pointer testManager);

    CreateAtomicSwapBidRequestOp
    createASwapRequestOp(uint64_t bidID, AssetCode asset, uint64_t amount);

    TransactionFramePtr
    createASwapRequestTx(Account& source,
            CreateAtomicSwapBidRequestOp& createASwapRequestOp);

    CreateAtomicSwapBidRequestResult
    applyCreateASwapRequest(Account& source,
            CreateAtomicSwapBidRequestOp& createASwapRequestOp,
            CreateAtomicSwapBidRequestResultCode expectedResult =
                    CreateAtomicSwapBidRequestResultCode::SUCCESS,
            OperationResultCode expectedOpRes =
                    OperationResultCode::opINNER);
};

}
}