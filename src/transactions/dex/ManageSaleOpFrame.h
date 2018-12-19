#pragma once

#include "main/Application.h"
#include "medida/metrics_registry.h"
#include "xdr/Stellar-operation-manage-sale.h"
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

        std::unordered_map<AccountID, CounterpartyDetails>
        getCounterpartyDetails(Database &db, LedgerDelta *delta) const override;

        SourceDetails getSourceAccountDetails(std::unordered_map<AccountID, CounterpartyDetails> counterpartiesDetails,
                                int32_t ledgerVersion) const override;

    public:
        ManageSaleOpFrame(Operation const &op, OperationResult &opRes, TransactionFrame &parentTx);

        bool createUpdateSaleDetailsRequest(Application &app, StorageHelper &storageHelper,
                                            LedgerManager &ledgerManager);

        bool amendUpdateSaleDetailsRequest(Application &app, LedgerManager &lm, StorageHelper &storageHelper);

        bool setSaleState(SaleFrame::pointer sale, Application &app, LedgerDelta &delta, LedgerManager &ledgerManager,
                          Database &db);

        bool doCheckValid(Application &app) override;

        bool ensureSaleUpdateDataValid(ReviewableRequestEntry& requestEntry);

        bool doApply(Application &app, StorageHelper &storageHelper, LedgerManager &lm) override;

        static void checkRequestType(ReviewableRequestFrame::pointer request, ReviewableRequestType requestType);

        static void cancelSale(SaleFrame::pointer sale, LedgerDelta &delta, Database &db, LedgerManager &lm);

        static void cancelAllOffersForQuoteAsset(SaleFrame::pointer sale, SaleQuoteAsset const &saleQuoteAsset,
                                     LedgerDelta &delta, Database &db);

        static void deleteAllAntesForSale(uint64_t saleID, LedgerDelta &delta, Database &db);

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

        std::vector<longstring> makeTasksKeyVector(StorageHelper &storageHelper) override;

    };
}
