#pragma once

#include <ledger/ReviewableRequestFrame.h>
#include "transactions/OperationFrame.h"

namespace stellar
{

class CreateASwapBidCreationRequestOpFrame : public OperationFrame
{
private:
    CreateASwapBidCreationRequestOp const& mCreateASwapBidCreationRequest;

    CreateASwapBidCreationRequestResult& innerResult()
    {
        return mResult.tr().createASwapBidCreationRequestResult();
    }

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;

public:
    CreateASwapBidCreationRequestOpFrame(Operation const &op, OperationResult &opRes,
                                      TransactionFrame &parentTx);

    static CreateASwapBidCreationRequestResultCode
    isBaseAssetValid(Database& db, AssetCode baseAssetCode);

    static CreateASwapBidCreationRequestResultCode
    isQuoteAssetValid(Database& db, AssetCode baseAssetCode, AssetCode quoteAssetCode);

    static CreateASwapBidCreationRequestResultCode
    areQuoteAssetsValid(Database& db, AssetCode baseAssetCode,
                        xdr::xvector<ASwapBidQuoteAsset> quoteAssets);

    static CreateASwapBidCreationRequestResultCode
    areAllAssetsValid(Database& db, AssetCode baseAssetCode,
                      xdr::xvector<ASwapBidQuoteAsset> quoteAssets);

    void tryAutoApprove(Database& db, LedgerDelta& delta, Application& app,
                        ReviewableRequestFrame::pointer request);

    bool doApply(Application &app, LedgerDelta &delta,
                 LedgerManager &ledgerManager) override;

    bool doCheckValid(Application &app) override;

    static CreateASwapBidCreationRequestResultCode getInnerCode(OperationResult& res)
    {
        return res.tr().createASwapBidCreationRequestResult().code();
    }

    std::string getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<CreateASwapBidCreationRequestResultCode>::enum_name(
                innerResult().code());
    }
};

}