#pragma once

#include "TxHelper.h"

namespace stellar
{
    namespace txtest
    {
        class LPSwapTestHelper : TxHelper
        {
        public:
            explicit LPSwapTestHelper(TestManager::pointer testManager);

            TransactionFramePtr createLPSwapTx(Account& from, LPSwapType swapType, BalanceID& fromBalance,
                BalanceID& toBalance, uint64_t amountIn, uint64_t amountOut, Account* signer = nullptr);

            LPSwapResult applyLPSwapTx(Account& from, LPSwapType swapType, BalanceID& fromBalance,
                BalanceID& toBalance, uint64_t amountIn, uint64_t amountOut, LPSwapResultCode expectedResultCode,
                Account* signer = nullptr);
        };
    }
}
