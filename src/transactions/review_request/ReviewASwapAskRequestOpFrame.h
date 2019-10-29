#pragma once

#include "ledger/AtomicSwapAskFrame.h"
#include "ReviewRequestOpFrame.h"

namespace stellar
{

class ReviewASwapAskRequestOpFrame : public ReviewRequestOpFrame {
public:
    ReviewASwapAskRequestOpFrame(Operation const& op, OperationResult& res,
                                 TransactionFrame& parentTx);

protected:

    bool
    handleReject(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager,
                 ReviewableRequestFrame::pointer request) override;

    bool
    handleAllAssetsValidationResultCode(CreateAtomicSwapAskRequestResultCode code);

    AtomicSwapAskFrame::pointer
    buildNewAsk(AccountID ownerID, AssetCode baseAsset, uint64_t ledgerCloseTime,
                CreateAtomicSwapAskRequest request, LedgerDelta& delta);

    bool
    handleApprove(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager,
                  ReviewableRequestFrame::pointer request) override;

    bool
    handlePermanentReject(Application& app, StorageHelper& storageHelper,
                          LedgerManager& ledgerManager,
                          ReviewableRequestFrame::pointer request) override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result, LedgerManager& lm) const override;
};

}
