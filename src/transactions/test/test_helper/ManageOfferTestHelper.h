#ifndef STELLAR_MANAGE_OFFER_TEST_HELPER_H
#define STELLAR_MANAGE_OFFER_TEST_HELPER_H

#include "ReviewRequestTestHelper.h"
#include "TxHelper.h"
#include "transactions/dex/ManageOfferOpFrame.h"

namespace stellar
{
namespace txtest
{

class ManageOfferTestHelper : public TxHelper
{
  protected:
    virtual void ensureDeleteSuccess(Account& source, ManageOfferOp op,
                                     ManageOfferSuccessResult success,
                                     LedgerDelta::KeyEntryMap& stateBeforeTx);

  public:
    virtual void ensureCreateSuccess(Account& source, ManageOfferOp op,
                                     ManageOfferSuccessResult success,
                                     LedgerDelta::KeyEntryMap& stateBeforeTx);
    explicit ManageOfferTestHelper(TestManager::pointer testManager);

    ManageOfferResult applyManageOffer(
        Account& source, uint64_t offerID, BalanceID const& baseBalance,
        BalanceID const& quoteBalance, int64_t amount, int64_t price,
        bool isBuy, int64_t fee,
        ManageOfferResultCode expectedResult = ManageOfferResultCode::SUCCESS);

    TransactionFramePtr creatManageOfferTx(Account& source, uint64_t offerID,
                                           BalanceID const& baseBalance,
                                           BalanceID const& quoteBalance,
                                           int64_t amount, int64_t price,
                                           bool isBuy, int64_t fee);

    ManageOfferResult applyManageOffer(
        Account& source, ManageOfferOp& manageOfferOp,
        ManageOfferResultCode expectedResult = ManageOfferResultCode::SUCCESS,
        OperationResultCode expectedOpCode = OperationResultCode::opINNER);

    TransactionFramePtr createManageOfferTx(Account& source,
                                            ManageOfferOp& manageOfferOp);


    ManageOfferOp
    manageOfferOp(
        const uint64_t offerID, BalanceID const& baseBalance,
        BalanceID const& quoteBalance, const int64_t amount, const int64_t price,
        const bool isBuy, const int64_t fee);
};
}

}

#endif // STELLAR_MANAGE_OFFER_TEST_HELPER_H
