#pragma once


#include "TxHelper.h"
#include <ledger/AssetPairFrame.h>
#include <ledger/AssetPairHelper.h>
#include <transactions/manage_asset_pair/ManageAssetPairOpFrame.h>

namespace stellar
{

    namespace txtest
    {
        class ManageRedemptionTestHelper:TxHelper
        {
        public:
            explicit ManageRedemptionTestHelper(TestManager::pointer testManager);

            TransactionFramePtr createRedemptionTx(Account& opSource, BalanceID sourceBalanceID, BalanceID destinationBalanceID, uint64 amount,
                                                 std::string reason, std::string reference, uint32_t *allTasks = nullptr);

            CreateRedemptionRequestResult applyCreateRedemption(Account& opSource,
                                                            BalanceID sourceBalanceID, BalanceID destinationBalanceID,
                                                            uint64 amount, std::string reason,
                                                            std::string reference, uint32_t *allTasks = nullptr,
                                                            CreateRedemptionRequestResultCode expectedResultCode = CreateRedemptionRequestResultCode::SUCCESS,
                                                            OperationResultCode expectedOpResult = OperationResultCode::opINNER);

        };
    }

}
