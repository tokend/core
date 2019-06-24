#pragma once

#include "main/Application.h"
#include "medida/metrics_registry.h"
#include "xdr/operation-manage-sale.h"
#include "xdrpp/printer.h"
#include <crypto/SHA.h>
#include <ledger/ReviewableRequestFrame.h>
#include <ledger/SaleFrame.h>
#include <lib/xdrpp/xdrpp/marshal.h>
#include <transactions/OperationFrame.h>

namespace stellar {
    class ManageSaleOpFrame : public OperationFrame {
    protected:
        ManageSaleOp const &mManageSaleOp;

        ManageSaleResult &innerResult() {
            return mResult.tr().manageSaleResult();
        }

        bool
        tryGetOperationConditions(StorageHelper& storageHelper,
                                  std::vector<OperationCondition>& result,
                                  LedgerManager& ledgerManager) const override;

        bool
        tryGetSignerRequirements(StorageHelper& storageHelper,
                                 std::vector<SignerRequirement>& result) const override;

    public:
        ManageSaleOpFrame(Operation const &op, OperationResult &opRes, TransactionFrame &parentTx);

        bool createUpdateSaleDetailsRequest(Application &app, StorageHelper &storageHelper,
                                            LedgerManager &ledgerManager);

        bool amendUpdateSaleDetailsRequest(Application &app, LedgerManager &lm, StorageHelper &storageHelper);

        bool doCheckValid(Application &app) override;

        bool ensureSaleUpdateDataValid(ReviewableRequestFrame::pointer request);

        bool doApply(Application &app, StorageHelper &storageHelper, LedgerManager &lm) override;

        static void cancelSale(SaleFrame::pointer sale, LedgerDelta &delta, Database &db, LedgerManager &lm);

        static void
        removeSaleRules(StorageHelper& sh, LedgerKey const& saleKey);

        static void cancelAllOffersForQuoteAsset(SaleFrame::pointer sale, SaleQuoteAsset const &saleQuoteAsset,
                                     LedgerDelta &delta, Database &db);

        std::string getUpdateSaleDetailsRequestReference() const {
            const auto hash = sha256(xdr::xdr_to_opaque(ReviewableRequestType::UPDATE_SALE_DETAILS,
                                                        mManageSaleOp.saleID));
            return binToHex(hash);
        }

        static ManageSaleResultCode getInnerCode(OperationResult &res) {
            return res.tr().manageSaleResult().code();
        }

        std::string getInnerResultCodeAsStr() override {
            return xdr::xdr_traits<ManageSaleResultCode>::enum_name(innerResult().code());
        }

        std::vector<std::string> makeTasksKeyVector();

    };
}
