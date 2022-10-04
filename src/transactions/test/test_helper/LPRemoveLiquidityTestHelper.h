#pragma once

#include "TxHelper.h"

namespace stellar
{
    namespace txtest
    {
        class LPRemoveLiquidityTestHelper : TxHelper
        {
        public:
            explicit LPRemoveLiquidityTestHelper(TestManager::pointer testManager);

            TransactionFramePtr createRemoveLiquidityPoolTx(Account& from, BalanceID& lpTokensBalance,
                uint64_t lpTokensAmount, uint64_t firstMinAmount, uint64_t secondMinAmount,
                Account* signer = nullptr);

            LPRemoveLiquidityResult applyRemoveLiquidityTx(Account& from, BalanceID& lpTokensBalance,
                uint64_t lpTokensAmount, uint64_t firstMinAmount, uint64_t secondMinAmount,
                LPRemoveLiquidityResultCode expectedResultCode, Account* signer = nullptr);
        };
    }
}