#pragma once


#include "TxHelper.h"
#include <ledger/AssetPairFrame.h>
#include <ledger/AssetPairHelper.h>
#include <transactions/ManageAssetPairOpFrame.h>

namespace stellar
{

namespace txtest
{
    class ManageAMLAlertTestHelper:TxHelper
    {
    public:
        explicit ManageAMLAlertTestHelper(TestManager::pointer testManager);

        TransactionFramePtr createAmlAlertTx(Account &source, BalanceID balance, uint64 amount,
                std::string reason, std::string reference, uint32_t *allTasks = nullptr);

        CreateAMLAlertRequestResult applyCreateAmlAlert(Account &source, BalanceID balance, uint64 amount, std::string reason,
            std::string reference, uint32_t *allTasks = nullptr, CreateAMLAlertRequestResultCode expectedResultCode = CreateAMLAlertRequestResultCode::SUCCESS);

    };
}

}
