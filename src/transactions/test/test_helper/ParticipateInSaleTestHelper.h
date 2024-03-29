#ifndef STELLAR_PARTICIPATE_IN_SALE_TEST_HELPER_H
#define STELLAR_PARTICIPATE_IN_SALE_TEST_HELPER_H

#include "ManageOfferTestHelper.h"

namespace stellar
{
namespace txtest
{

    class ParticipateInSaleTestHelper : public ManageOfferTestHelper
    {
    public:
        explicit ParticipateInSaleTestHelper(TestManager::pointer testManager);
        ManageOfferResult
        addNewParticipant(Account &root, Account &participant, const uint64_t saleID, const AssetCode baseAsset,
                          const AssetCode quoteAsset, const uint64_t quoteAssetAmount, const uint64_t price,
                          const uint64_t fee);

        ManageOfferResult
        addNewParticipant(Account &root, const uint64_t saleID, const AssetCode baseAsset,
                                          const AssetCode quoteAsset, const uint64_t quoteAssetAmount,
                                          const uint64_t price, const uint64_t fee);

    protected:
        void ensureDeleteSuccess(Account& source, ManageOfferOp op,
            ManageOfferSuccessResult success,
            LedgerDelta::KeyEntryMap& stateBeforeTx) override;
        void ensureCreateSuccess(Account& source, ManageOfferOp op,
            ManageOfferSuccessResult success,
            LedgerDelta::KeyEntryMap& stateBeforeTx) override;
    };
}

}


#endif //STELLAR_PARTICIPATE_IN_SALE_TEST_HELPER_H
