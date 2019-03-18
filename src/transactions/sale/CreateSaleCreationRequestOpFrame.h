#pragma once

// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "transactions/OperationFrame.h"
#include "ledger/ReviewableRequestFrame.h"

namespace stellar
{
class CreateSaleCreationRequestOpFrame : public OperationFrame
{
    CreateSaleCreationRequestResult& innerResult()
    {
        return mResult.tr().createSaleCreationRequestResult();
    }

    CreateSaleCreationRequestOp const& mCreateSaleCreationRequest;

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;

    // tryLoadAssetOrRequest - tries to load base asset or request. If fails returns nullptr. If request exists - creates asset frame wrapper for it
    static AssetFrame::pointer tryLoadBaseAssetOrRequest(SaleCreationRequest const& request, Database& db, AccountID const& source);

    static bool isPriceValid(SaleCreationRequestQuoteAsset const& quoteAsset,
                             SaleCreationRequest const& saleCreationRequest);
public:

    CreateSaleCreationRequestOpFrame(Operation const& op, OperationResult& res,
                                   TransactionFrame& parentTx);
    bool doApply(Application& app, StorageHelper &storageHelper,
                 LedgerManager& ledgerManager) override;

    bool doCheckValid(Application& app) override;

    static bool ensureEnoughAvailable(const SaleCreationRequest& saleCreationRequest,
            const AssetFrame::pointer baseAsset);

    static CreateSaleCreationRequestResultCode doCheckValid(Application& app,
                                                            SaleCreationRequest const& saleCreationRequest, AccountID const& source);

    static bool areQuoteAssetsValid(Database& db, xdr::xvector<SaleCreationRequestQuoteAsset, 100> quoteAssets, AssetCode defaultQuoteAsset);

    static CreateSaleCreationRequestResultCode getInnerCode(
        OperationResult const& res)
    {
        return res.tr().createSaleCreationRequestResult().code();
    }

    std::string getInnerResultCodeAsStr() override {
        return xdr::xdr_traits<CreateSaleCreationRequestResultCode>::enum_name(innerResult().code());
    }

    bool createRequest(Application& app, StorageHelper& storageHelper,
                       LedgerManager& ledgerManager);
    bool updateRequest(Application& app, StorageHelper& storageHelper,
                       LedgerManager& ledgerManager);

    bool isRequestValid(StorageHelper& storageHelper, LedgerManager& ledgerManager,
                        ReviewableRequestFrame::pointer request);

    std::vector<std::string> makeTasksKeyVector();

};
}
