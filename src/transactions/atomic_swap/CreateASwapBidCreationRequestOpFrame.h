#pragma once

#include "transactions/OperationFrame.h"

namespace stellar
{

class CreateASwapBidCreationRequestOpFrame : public OperationFrame
{
protected:
    CreateASwapBidCreationRequestOp& const mCreateASwapBidCreationRequest;

    CreateASwapBidCreationRequestResult& innerResult()
    {
        return mResult.tr().createASwapBidCreationRequestResult();
    }

    std::unordered_map<AccountID, CounterpartyDetails>
    getCounterpartyDetails(Database &db, LedgerDelta *delta) const override;

    SourceDetails
    getSourceAccountDetails(std::unordered_map<AccountID, CounterpartyDetails>
                            counterpartiesDetails, int32_t ledgerVersion) const override;

public:
    CreateASwapBidCreationRequestOpFrame(Operation const &op, OperationResult &opRes,
                                      TransactionFrame &parentTx);

    bool isQuoteAssetValid(Database& db, AssetCode baseAssetCode,
                           AssetCode quoteAssetCode);

    bool areQuoteAssetsValid(Database& db, AssetCode baseAssetCode);

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