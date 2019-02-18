#ifndef STELLAR_MANAGE_OFFER_TEST_HELPER_H
#define STELLAR_MANAGE_OFFER_TEST_HELPER_H

#include "TxHelper.h"
#include "ReviewRequestTestHelper.h"
#include "transactions/dex/ManageOfferOpFrame.h"

namespace stellar
{
namespace txtest
{

    class ManageOfferTestHelper : public TxHelper
    {
    protected:

        virtual void ensureDeleteSuccess(Account& source, ManageOfferOp op, ManageOfferSuccessResult success, LedgerDelta::KeyEntryMap& stateBeforeTx);
        virtual void ensureCreateSuccess(Account& source, ManageOfferOp op, ManageOfferSuccessResult success, LedgerDelta::KeyEntryMap& stateBeforeTx);
    public:
        explicit ManageOfferTestHelper(TestManager::pointer testManager);

        ManageOfferResult applyManageOffer(Account& source, uint64_t offerID, BalanceID const& baseBalance,
            BalanceID const& quoteBalance, int64_t amount, int64_t price, bool isBuy, int64_t fee,
            ManageOfferResultCode expectedResult = ManageOfferResultCode::SUCCESS);

        TransactionFramePtr creatManageOfferTx(Account& source, uint64_t offerID, BalanceID const& baseBalance,
            BalanceID const& quoteBalance, int64_t amount, int64_t price, bool isBuy, int64_t fee);

        ManageOfferResult applyManageOffer(Account& source, ManageOfferOp& manageOfferOp,
            ManageOfferResultCode expectedResult = ManageOfferResultCode::SUCCESS,
                    OperationResultCode expectedOpCode = OperationResultCode::opINNER);

        TransactionFramePtr createManageOfferTx(Account& source, ManageOfferOp& manageOfferOp);

    };
}

}


#endif //STELLAR_MANAGE_OFFER_TEST_HELPER_H
