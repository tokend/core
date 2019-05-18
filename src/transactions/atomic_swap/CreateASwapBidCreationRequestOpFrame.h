#pragma once

#include <ledger/ReviewableRequestFrame.h>
#include "transactions/OperationFrame.h"

namespace stellar
{

class CreateASwapBidCreationRequestOpFrame : public OperationFrame
{
private:
    CreateAtomicSwapBidRequestOp const& mCreateASwapBidCreationRequest;

    CreateAtomicSwapBidRequestResult& innerResult()
    {
        return mResult.tr().createAtomicSwapBidRequestResult();
    }

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;

    bool
    isSupported(LedgerManager& lm) const override
    {
        return lm.shouldUse(LedgerVersion::ATOMIC_SWAP_RETURNING);
    }

    void
    fillRequest(ReviewableRequestEntry &requestEntry,
                CreateAtomicSwapBidRequest body, uint32_t allTasks);

    std::vector<std::string>
    makeTasksKeyVector();

public:
    CreateASwapBidCreationRequestOpFrame(Operation const &op, OperationResult &opRes,
                                      TransactionFrame &parentTx);

    static CreateAtomicSwapBidRequestResultCode
    isBaseAssetValid(Database& db, uint64 baseAmount, AssetCode baseAssetCode);

    static CreateAtomicSwapBidRequestResultCode
    isQuoteAssetValid(Database& db, AssetCode baseAssetCode,
            AtomicSwapBidQuoteAsset quoteAsset);

    static CreateAtomicSwapBidRequestResultCode
    areQuoteAssetsValid(Database& db, AssetCode baseAssetCode,
                        xdr::xvector<AtomicSwapBidQuoteAsset> quoteAssets);

    static CreateAtomicSwapBidRequestResultCode
    areAllAssetsValid(Database& db, uint64_t baseAmount, AssetCode baseAssetCode,
                      xdr::xvector<AtomicSwapBidQuoteAsset> quoteAssets);

    void tryAutoApprove(Database& db, LedgerDelta& delta, Application& app,
                        ReviewableRequestFrame::pointer request);

    bool doApply(Application &app, StorageHelper& storageHelper,
                 LedgerManager &ledgerManager) override;

    bool doCheckValid(Application &app) override;

    static CreateAtomicSwapBidRequestResultCode getInnerCode(OperationResult& res)
    {
        return res.tr().createAtomicSwapBidRequestResult().code();
    }

    std::string getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<CreateAtomicSwapBidRequestResultCode>::enum_name(
                innerResult().code());
    }
};

}