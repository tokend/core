#pragma once

#include "TxHelper.h"

namespace stellar
{
namespace txtest
{
struct BalanceDelta
{
    AssetCode asset;
    int64_t amountDelta;
};

struct CloseSwapDelta
{
    std::vector<BalanceDelta> source;
    std::vector<BalanceDelta> destination;
    std::vector<BalanceDelta> commission;
};

class CloseSwapTestHelper : TxHelper
{
  public:
    explicit CloseSwapTestHelper(TestManager::pointer testManager);

    TransactionFramePtr createCloseSwapTx(Account& source, int64_t swapID,
                                          Hash* secret = nullptr);
    CloseSwapOp makeCloseSwap(int64_t swapID, Hash* secret = nullptr);

    CloseSwapResult applyCloseSwapTx(
        Account& source, int64_t swapID, Hash* secret = nullptr,
        CloseSwapDelta* closeSwapDelta = nullptr,
        CloseSwapResultCode expectedResultCode = CloseSwapResultCode::SUCCESS,
        OperationResultCode expectedOpResultCode =
            OperationResultCode::opINNER);

};
}
}