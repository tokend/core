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

    CreateASwapRequestOp createASwapRequestOp(uint64_t bidID, AssetCode asset,
                                              uint64_t amount);

    TransactionFramePtr createASwapRequestTx(Account& source,
                 CreateASwapRequestOp& createASwapRequestOp);

    CreateASwapRequestResult applyCreateASwapRequest(Account& source,
                          CreateASwapRequestOp& createASwapRequestOp,
                          CreateASwapRequestResultCode expectedResult =
                          CreateASwapRequestResultCode::SUCCESS,
                          OperationResultCode expectedOpRes =
                          OperationResultCode::opINNER);
};

}
}