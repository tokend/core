#pragma once

#include "TxHelper.h"

namespace stellar
{
    namespace txtest
    {
        class LPAddLiquidityTestHelper : TxHelper
        {
        public:
            explicit LPAddLiquidityTestHelper(TestManager::pointer testManager);

            TransactionFramePtr createAddLiquidityPoolTx(Account& from, BalanceID& firstBalance,
                BalanceID& secondBalance, uint64_t firstDesiredAmount, uint64_t secondDesiredAmount,
                uint64_t firstMinAmount, uint64_t secondMinAmount, Account* signer = nullptr);

            LPAddLiquidityResult applyAddLiquidityTx(Account& from, BalanceID& firstBalance,BalanceID& secondBalance,
                uint64_t firstDesiredAmount, uint64_t secondDesiredAmount, uint64_t firstMinAmount,
                uint64_t secondMinAmount, LPAddLiquidityResultCode expectedResultCode, Account* signer = nullptr);
        };
    }
}
