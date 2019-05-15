#pragma once

#include <ledger/ReviewableRequestFrame.h>
#include "transactions/OperationFrame.h"

namespace stellar
{

class CreateASwapBidCreationRequestOpFrame : public OperationFrame
{
private:
    CreateAtomicSwapBidCreationRequestOp const& mCreateASwapBidCreationRequest;

    CreateAtomicSwapBidCreationRequestResult& innerResult()
    {
        return mResult.tr().createAtomicSwapBidCreationRequestResult();
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
                AtomicSwapBidCreationRequest body, uint32_t allTasks);

    std::vector<std::string>
    makeTasksKeyVector();

public:
    CreateASwapBidCreationRequestOpFrame(Operation const &op, OperationResult &opRes,
                                      TransactionFrame &parentTx);

    static CreateAtomicSwapBidCreationRequestResultCode
    isBaseAssetValid(Database& db, AssetCode baseAssetCode);

    static CreateAtomicSwapBidCreationRequestResultCode
    isQuoteAssetValid(Database& db, uint64_t baseAmount, AssetCode baseAssetCode,
            AtomicSwapBidQuoteAsset quoteAsset);

    static CreateAtomicSwapBidCreationRequestResultCode
    areQuoteAssetsValid(Database& db, uint64_t baseAmount, AssetCode baseAssetCode,
                        xdr::xvector<AtomicSwapBidQuoteAsset> quoteAssets);

    static CreateAtomicSwapBidCreationRequestResultCode
    areAllAssetsValid(Database& db, uint64_t baseAmount, AssetCode baseAssetCode,
                      xdr::xvector<AtomicSwapBidQuoteAsset> quoteAssets);

    void tryAutoApprove(Database& db, LedgerDelta& delta, Application& app,
                        ReviewableRequestFrame::pointer request);

    bool doApply(Application &app, StorageHelper& storageHelper,
                 LedgerManager &ledgerManager) override;

    bool doCheckValid(Application &app) override;

    static CreateAtomicSwapBidCreationRequestResultCode getInnerCode(OperationResult& res)
    {
        return res.tr().createAtomicSwapBidCreationRequestResult().code();
    }

    std::string getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<CreateAtomicSwapBidCreationRequestResultCode>::enum_name(
                innerResult().code());
    }
};

}