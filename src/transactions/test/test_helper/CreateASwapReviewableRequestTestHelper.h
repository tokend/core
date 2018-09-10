#pragma once

#include "TxHelper.h"

namespace stellar
{
namespace txtest
{
class CreateAtomicSwapReviewableRequestTestHelper : TxHelper
{
public:
    explicit CreateAtomicSwapReviewableRequestTestHelper(
            TestManager::pointer testManager);


    TransactionFramePtr createASwapRequestTx(Account& source,
                 CreateASwapRequestOp& createASwapRequestOp);

    CreateASwapRequestResult applyCreateASwapRequest(Account& source,
                          CreateASwapRequestOp& createASwapRequestOp,
                          CreateASwapRequestResultCode expectedResult =
                          CreateASwapRequestResultCode::SUCCESS);

    CreateASwapRequestOp createASwapRequestOp(uint64_t bidID, AssetCode asset,
                                              uint64_t amount, uint64_t fee);

};

}
}