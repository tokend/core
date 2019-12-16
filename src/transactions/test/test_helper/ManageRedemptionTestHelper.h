#pragma once


#include "TxHelper.h"
#include <ledger/AssetPairFrame.h>
#include <ledger/AssetPairHelper.h>
#include <transactions/manage_asset_pair/ManageAssetPairOpFrame.h>
#include "ledger/ReviewableRequestFrame.h"
#include "ReviewRequestTestHelper.h"

namespace stellar
{

    namespace txtest
    {
        class RedemptionReviewChecker : public ReviewChecker
        {
        protected:
            void checkApproval(RedemptionRequest const& request,
                               AccountID const& requestor);
            void checkPermanentReject(RedemptionRequest const& request,
                                      AccountID const& requestor);
        public:
            explicit RedemptionReviewChecker(const TestManager::pointer& testManager)
                    : ReviewChecker(testManager)
            {
            }

            void checkApprove(ReviewableRequestFrame::pointer) override;
            void checkPermanentReject(ReviewableRequestFrame::pointer) override;
        };
        class ManageRedemptionTestHelper:TxHelper
        {
        public:
            explicit ManageRedemptionTestHelper(TestManager::pointer testManager);

            TransactionFramePtr createRedemptionTx(Account& opSource, BalanceID sourceBalanceID, AccountID destinationAccountID, uint64 amount,
                                                 std::string reason, std::string reference, uint32_t *allTasks = nullptr);

            CreateRedemptionRequestResult applyCreateRedemption(Account& opSource,
                                                            BalanceID sourceBalanceID, AccountID destinationAccountID,
                                                            uint64 amount, std::string reason,
                                                            std::string reference, uint32_t *allTasks = nullptr,
                                                            CreateRedemptionRequestResultCode expectedResultCode = CreateRedemptionRequestResultCode::SUCCESS,
                                                            OperationResultCode expectedOpResult = OperationResultCode::opINNER);
        };
    }

}
