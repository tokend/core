#pragma once

#include "xdrpp/marshal.h"
#include "xdrpp/printer.h"
#include "OperationFrame.h"
#include "ledger/AtomicSwapBidFrame.h"

namespace stellar
{

class ManageAtomicSwapBidOpFrame : public OperationFrame
{
protected:
    ManageAtomicSwapBidOp const& mManageAtomicSwapBidOp;

    ManageAtomicSwapBidResult& innerResult()
    {
        return mResult.tr().manageAtomicSwapBidResult();
    }

    std::unordered_map<AccountID, CounterpartyDetails>
    getCounterpartyDetails(Database &db, LedgerDelta *delta) const override;

    SourceDetails
    getSourceAccountDetails(std::unordered_map<AccountID, CounterpartyDetails>
            counterpartiesDetails, int32_t ledgerVersion) const override;

public:
    ManageAtomicSwapBidOpFrame(Operation const &op, OperationResult &opRes,
                               TransactionFrame &parentTx);

    bool assetsSupportSwap(AssetFrame::pointer baseAssetFrame,
                           AssetFrame::pointer quoteAssetFrame);

    AtomicSwapBidFrame::pointer
    buildNewBid(AccountID ownerID, AssetCode baseAsset, uint64_t ledgerCloseTime,
                CreateManageAtomicSwapBidData creationData, LedgerDelta& delta);

    bool createAtomicSwapBid(Application &app, LedgerDelta &delta,
                             LedgerManager &ledgerManager);

    bool cancelAtomicSwapBid(Database &db, LedgerDelta &delta,
                             LedgerManager &ledgerManager);

    bool doApply(Application &app, LedgerDelta &delta,
                 LedgerManager &ledgerManager) override;

    bool doCheckValid(Application &app) override;

    static ManageAtomicSwapBidResultCode getInnerCode(OperationResult& res)
    {
        return res.tr().manageAtomicSwapBidResult().code();
    }

    std::string getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<ManageAtomicSwapBidResultCode>::enum_name(
                innerResult().code());
    }
};

}