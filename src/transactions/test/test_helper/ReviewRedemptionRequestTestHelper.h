#include "overlay/StellarXDR.h"
#include "ReviewRequestTestHelper.h"
#include "ledger/ReviewableRequestFrame.h"
#include "ledger/AssetFrame.h"
#include "ledger/BalanceFrame.h"
#include "ledger/StatisticsFrame.h"

namespace stellar
{

namespace txtest
{
    class ReviewRedemptionRequestTestHelper : public ReviewRequestHelper {

    public:
        explicit ReviewRedemptionRequestTestHelper(TestManager::pointer testManager);

        TransactionFramePtr createReviewRequestTx(Account& source,
                                                  uint64_t requestID, Hash requestHash, ReviewableRequestType requestType,
                                                  ReviewRequestOpAction action, std::string rejectReason) override;

        using ReviewRequestHelper::applyReviewRequestTx;

        ReviewRequestResult applyReviewRequestTx(Account& source,
                                                 uint64_t requestID,
                                                 Hash requestHash,
                                                 ReviewableRequestType requestType,
                                                 ReviewRequestOpAction action,
                                                 std::string rejectReason,
                                                 ReviewRequestResultCode
                                                 expectedResult =
                                                 ReviewRequestResultCode::
                                                 SUCCESS) override;

    };
}
}