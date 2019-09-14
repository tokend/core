#pragma once

// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "transactions/OperationFrame.h"
#include "ledger/SaleFrame.h"
#include "transactions/FeesManager.h"

namespace stellar
{
class CheckSaleStateOpFrame : public OperationFrame
{
    enum SaleState
    {
        CLOSE = 1,
        CANCEL = 2,
        NOT_READY = 3
    };

    enum TokenAction
    {
        NOTHING,
        DESTROY,
        RESTRICT
    };

    static SaleState getSaleState(SaleFrame::pointer sale, Database& db, LedgerManager& lm);

    CheckSaleStateResult& innerResult()
    {
        return mResult.tr().checkSaleStateResult();
    }

    CheckSaleStateOp const& mCheckSaleState;

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;

    void issueBaseTokens(SaleFrame::pointer sale, AccountFrame::pointer saleOwnerAccount, Application& app,
                        LedgerDelta& delta, Database& db, LedgerManager& lm) const;

    bool handleCancel(SaleFrame::pointer sale, LedgerManager& lm, LedgerDelta& delta, Database& db);
    bool handleClose(SaleFrame::pointer sale, Application& app, LedgerManager& lm, LedgerDelta& delta, Database& db);

    CreateIssuanceRequestResult applyCreateIssuanceRequest(const SaleFrame::pointer sale, const AccountFrame::pointer saleOwnerAccount, Application& app,
        LedgerDelta& delta, LedgerManager& lm) const;

    static void issueTokens(TransactionFrame& parentTx, Application& app, LedgerDelta& delta, LedgerManager &lm, AccountFrame::pointer source, AssetCode const& asset, uint64_t amount, BalanceID const& receiver);

    void applyOffers(Application& app, LedgerDelta& delta, LedgerManager& lm, SaleFrame::pointer sale, AccountFrame::pointer owner);

    FeeManager::FeeResult obtainCalculatedFeeForAccount(const AccountFrame::pointer saleOwnerAccount,
                                                        AssetCode const& asset, int64_t amount,
                                                        LedgerManager& lm, Database& db) const;

    ManageOfferSuccessResult applySaleOffer(AccountFrame::pointer saleOwner, SaleFrame::pointer sale, SaleQuoteAsset const& saleQuoteAsset, Application& app, LedgerManager& lm, LedgerDelta& delta) const;

    // Returns true if sale was updated due to cleanup
    bool cleanSale(SaleFrame::pointer sale, Application& app, LedgerDelta& delta, LedgerManager& ledgerManager) const;

    void updateOfferPrices(SaleFrame::pointer sale, LedgerDelta& delta, Database& db) const;

    static int64_t getSaleCurrentPriceInDefaultQuote(SaleFrame::pointer sale, LedgerDelta& delta, Database& db);

    void cleanupIssuerBalance(SaleFrame::pointer sale, LedgerManager& lm,  Database& db, LedgerDelta& delta, BalanceFrame::pointer balanceBefore);

public:

    CheckSaleStateOpFrame(Operation const& op, OperationResult& res,
                         TransactionFrame& parentTx);

    static ManageOfferSuccessResult createCounterOffer(
        Application& app, LedgerDelta& delta, LedgerManager& lm,
        TransactionFrame& parentTx, SaleFrame::pointer sale,
        AccountFrame::pointer saleOwnerAccount,
        SaleQuoteAsset const& saleQuoteAsset, int64_t baseAmount, int64_t price,
        FeeManager::FeeResult feeResult);

    bool doApply(Application& app, StorageHelper& storageHelper,
                 LedgerManager& ledgerManager) override;
    bool doCheckValid(Application& app) override;

    static int64_t getSalePriceForCap(int64_t const cap, SaleFrame::pointer sale);
    static int64_t getPriceInQuoteAsset(int64_t const salePriceInDefaultQuote, SaleFrame::pointer sale, AssetCode const quoteAsset, Database& db);

    static CheckSaleStateResultCode getInnerCode(OperationResult const& res)
    {
        return res.tr().checkSaleStateResult().code();
    }

    std::string getInnerResultCodeAsStr() override;

private:
    static uint64 getMinimumAssetAmount(const AssetCode& balance, Database& db, LedgerDelta* delta);
};
}
