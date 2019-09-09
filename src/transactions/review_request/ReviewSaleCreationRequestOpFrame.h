#pragma once

// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ReviewRequestOpFrame.h"
#include "ledger/ReviewableRequestFrame.h"
#include "ledger/SaleFrame.h"

namespace stellar {
    class ReviewSaleCreationRequestOpFrame : public ReviewRequestOpFrame {

        bool
        tryGetSignerRequirements(StorageHelper& storageHelper,
                                 std::vector<SignerRequirement>& result) const override;

    public:

        ReviewSaleCreationRequestOpFrame(Operation const &op, OperationResult &res, TransactionFrame &parentTx);

        static uint64 getRequiredBaseAssetForHardCap(SaleCreationRequest const &saleCreationRequest);

    protected:
        bool handleApprove(Application &app, LedgerDelta &delta, LedgerManager &ledgerManager,
                           ReviewableRequestFrame::pointer request) override;

        ReviewRequestResultCode tryCreateSale(Application &app, Database &db, LedgerDelta &delta,
                                              LedgerManager &ledgerManager,
                                              ReviewableRequestFrame::pointer request, uint64_t saleID);

        void
        createSaleRules(Application& app, StorageHelper& sh, LedgerManager &lm,
                SaleCreationRequest const& request, SaleFrame::pointer const& sale);

        SaleCreationRequest &getSaleCreationRequestFromBody(ReviewableRequestFrame::pointer request);

        void createAssetPair(SaleFrame::pointer sale, Application &app, LedgerManager &ledgerManager,
                             LedgerDelta &delta) const;

        std::map<AssetCode, BalanceID>
        loadBalances(AccountManager &accountManager, ReviewableRequestFrame::pointer request,
                     SaleCreationRequest const &sale);
    };
}
