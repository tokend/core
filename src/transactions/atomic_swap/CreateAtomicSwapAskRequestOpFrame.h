#pragma once

#include <ledger/ReviewableRequestFrame.h>
#include "transactions/OperationFrame.h"

namespace stellar
{

class CreateAtomicSwapAskRequestOpFrame : public OperationFrame
{
private:
    CreateAtomicSwapAskRequestOp const& mCreateASwapAskCreationRequest;

    CreateAtomicSwapAskRequestResult& innerResult()
    {
        return mResult.tr().createAtomicSwapAskRequestResult();
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
                CreateAtomicSwapAskRequest body, uint32_t allTasks);

    std::vector<std::string>
    makeTasksKeyVector();

public:
    CreateAtomicSwapAskRequestOpFrame(Operation const &op, OperationResult &opRes,
                                      TransactionFrame &parentTx);

    static CreateAtomicSwapAskRequestResultCode
    isBaseAssetValid(Database& db, uint64 baseAmount, AssetCode baseAssetCode);

    static CreateAtomicSwapAskRequestResultCode
    isQuoteAssetValid(Database& db, AssetCode baseAssetCode,
            AtomicSwapAskQuoteAsset quoteAsset);

    static CreateAtomicSwapAskRequestResultCode
    areQuoteAssetsValid(Database& db, AssetCode baseAssetCode,
                        xdr::xvector<AtomicSwapAskQuoteAsset> quoteAssets);

    static CreateAtomicSwapAskRequestResultCode
    areAllAssetsValid(Database& db, uint64_t baseAmount, AssetCode baseAssetCode,
                      xdr::xvector<AtomicSwapAskQuoteAsset> quoteAssets);

    void tryAutoApprove(Database& db, LedgerDelta& delta, Application& app,
                        ReviewableRequestFrame::pointer request);

    bool doApply(Application &app, StorageHelper& storageHelper,
                 LedgerManager &ledgerManager) override;

    bool doCheckValid(Application &app) override;

    static CreateAtomicSwapAskRequestResultCode getInnerCode(OperationResult& res)
    {
        return res.tr().createAtomicSwapAskRequestResult().code();
    }

    std::string getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<CreateAtomicSwapAskRequestResultCode>::enum_name(
                innerResult().code());
    }
};

}