#pragma once

#include "TxHelper.h"

namespace stellar
{
namespace txtest
{
class CreateASwapReviewableRequestTestHelper : TxHelper
{
public:
    explicit
    CreateASwapReviewableRequestTestHelper(TestManager::pointer testManager);

    CreateAtomicSwapAskRequestOp
    createASwapRequestOp(uint64_t bidID, AssetCode asset, uint64_t amount);

    TransactionFramePtr
    createASwapRequestTx(Account& source,
            CreateAtomicSwapAskRequestOp& createASwapRequestOp);

    CreateAtomicSwapAskRequestResult
    applyCreateASwapRequest(Account& source,
            CreateAtomicSwapAskRequestOp& createASwapRequestOp,
            CreateAtomicSwapAskRequestResultCode expectedResult =
                    CreateAtomicSwapAskRequestResultCode::SUCCESS,
            OperationResultCode expectedOpRes =
                    OperationResultCode::opINNER);
};

}
}