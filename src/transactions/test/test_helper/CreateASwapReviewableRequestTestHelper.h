#pragma once

#include "TxHelper.h"

namespace stellar
{
namespace txtest
{
class CreateASwapReviewableRequestTestHelper : TxHelper
{
public:
    explicit CreateASwapReviewableRequestTestHelper(
            TestManager::pointer testManager);

    CreateAtomicSwapRequestOp createASwapRequestOp(uint64_t bidID, AssetCode asset,
                                              uint64_t amount);

    TransactionFramePtr createASwapRequestTx(Account& source,
                 CreateAtomicSwapRequestOp& createASwapRequestOp);

    CreateAtomicSwapRequestResult applyCreateASwapRequest(Account& source,
                          CreateAtomicSwapRequestOp& createASwapRequestOp,
                          CreateAtomicSwapRequestResultCode expectedResult =
                          CreateAtomicSwapRequestResultCode::SUCCESS,
                          OperationResultCode expectedOpRes =
                          OperationResultCode::opINNER);
};

}
}