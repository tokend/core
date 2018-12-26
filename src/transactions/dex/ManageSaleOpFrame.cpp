#include "ManageSaleOpFrame.h"
#include "OfferManager.h"
#include "transactions/sale/CreateSaleCreationRequestOpFrame.h"
#include "transactions/ManageKeyValueOpFrame.h"
#include <ledger/BalanceHelperLegacy.h>
#include <ledger/OfferHelper.h>
#include <ledger/KeyValueHelper.h>
#include <ledger/ReviewableRequestHelper.h>
#include <ledger/SaleAnteHelper.h>
#include <ledger/SaleHelper.h>
#include <ledger/StorageHelper.h>
#include <transactions/review_request/ReviewRequestHelper.h>

namespace stellar {
    ManageSaleOpFrame::ManageSaleOpFrame(Operation const &op, OperationResult &opRes, TransactionFrame &parentTx)
            : OperationFrame(op, opRes, parentTx), mManageSaleOp(mOperation.body.manageSaleOp()) {
    }

    std::unordered_map<AccountID, CounterpartyDetails>
    ManageSaleOpFrame::getCounterpartyDetails(Database &db, LedgerDelta *delta) const {
        // no counterparties
        return {};
    }

    SourceDetails
    ManageSaleOpFrame::getSourceAccountDetails(std::unordered_map<AccountID, CounterpartyDetails> counterpartiesDetails,
                                               int32_t ledgerVersion) const {
        std::vector<AccountType> allowedSourceAccountTypes = {AccountType::SYNDICATE};

        if (ledgerVersion >= static_cast<int32_t>(LedgerVersion::ALLOW_MASTER_TO_MANAGE_SALE)) {
            allowedSourceAccountTypes.push_back(AccountType::MASTER);
        }

        return SourceDetails(allowedSourceAccountTypes, mSourceAccount->getHighThreshold(),
                             static_cast<int32_t>(SignerType::ASSET_MANAGER));
    }

    bool ManageSaleOpFrame::amendUpdateSaleDetailsRequest(Application &app, LedgerManager &lm, StorageHelper &storageHelper) {

        auto& db = storageHelper.getDatabase();
        auto delta = storageHelper.getLedgerDelta();

        auto requestFrame = ReviewableRequestHelper::Instance()->loadRequest(
                mManageSaleOp.data.updateSaleDetailsData().requestID, getSourceID(),
                ReviewableRequestType::UPDATE_SALE_DETAILS, db, delta);

        if (!requestFrame) {
            innerResult().code(ManageSaleResultCode::UPDATE_DETAILS_REQUEST_NOT_FOUND);
            return false;
        }

        auto &requestEntry = requestFrame->getRequestEntry();
        if (!ensureSaleUpdateDataValid(requestFrame)) {
            return false;
        }

        requestEntry.body.updateSaleDetailsRequest().newDetails = mManageSaleOp.data.updateSaleDetailsData().newDetails;
        requestEntry.body.updateSaleDetailsRequest().sequenceNumber++;
        requestFrame->setTasks(requestEntry.tasks.allTasks);

        requestFrame->recalculateHashRejectReason();
        ReviewableRequestHelper::Instance()->storeChange(*delta, db, requestFrame->mEntry);

        bool fulfilled = false;
        if (getSourceAccount().getAccountType() == AccountType::MASTER) {
            auto resultCode = ReviewRequestHelper::tryApproveRequest(mParentTx, app, lm, *delta, requestFrame);

            if (resultCode == ReviewRequestResultCode::SUCCESS) {
                fulfilled = true;
            }
        }

        innerResult().code(ManageSaleResultCode::SUCCESS);
        innerResult().success().response.action(ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST);
        innerResult().success().response.requestID() = requestFrame->getRequestID();
        innerResult().success().fulfilled = fulfilled;

        return true;
    }

    bool
    ManageSaleOpFrame::createUpdateSaleDetailsRequest(Application &app, StorageHelper &storageHelper,
                                                      LedgerManager &ledgerManager) {
        auto& db = storageHelper.getDatabase();
        auto delta = storageHelper.getLedgerDelta();

        auto reference = getUpdateSaleDetailsRequestReference();
        auto const referencePtr = xdr::pointer<string64>(new string64(reference));
        auto requestHelper = ReviewableRequestHelper::Instance();
        if (requestHelper->isReferenceExist(db, getSourceID(), reference)) {
            innerResult().code(ManageSaleResultCode::UPDATE_DETAILS_REQUEST_ALREADY_EXISTS);
            return false;
        }

        auto request = ReviewableRequestFrame::createNew(*delta, getSourceID(), app.getMasterID(),
                                                              referencePtr, ledgerManager.getCloseTime());
        auto &requestEntry = request->getRequestEntry();
        requestEntry.body.type(ReviewableRequestType::UPDATE_SALE_DETAILS);
        requestEntry.body.updateSaleDetailsRequest().saleID = mManageSaleOp.saleID;
        requestEntry.body.updateSaleDetailsRequest().newDetails = mManageSaleOp.data.updateSaleDetailsData().newDetails;
        requestEntry.body.updateSaleDetailsRequest().sequenceNumber = 0;

        request->recalculateHashRejectReason();

        requestHelper->storeAdd(*delta, db, request->mEntry);


        uint32_t allTasks = 0;
        if (!loadTasks(storageHelper, allTasks, mManageSaleOp.data.updateSaleDetailsData().allTasks))
        {
            innerResult().code(ManageSaleResultCode::SALE_UPDATE_DETAILS_TASKS_NOT_FOUND);
            return false;
        }

        request->setTasks(allTasks);
        EntryHelperProvider::storeChangeEntry(*delta, db, request->mEntry);

        bool fulfilled = false;

        if (allTasks == 0) {
            auto result = ReviewRequestHelper::tryApproveRequestWithResult(mParentTx, app, ledgerManager, *delta, request);
            if (result.code() != ReviewRequestResultCode::SUCCESS) {
                throw std::runtime_error("Failed to review manage sale request");
            }
            fulfilled = result.success().fulfilled;
        }

        innerResult().code(ManageSaleResultCode::SUCCESS);
        innerResult().success().response.action(ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST);
        innerResult().success().response.requestID() = request->getRequestID();
        innerResult().success().fulfilled = fulfilled;

        return true;
    }

    void ManageSaleOpFrame::cancelSale(SaleFrame::pointer sale, LedgerDelta &delta, Database &db, LedgerManager &lm) {
        for (auto &saleQuoteAsset : sale->getSaleEntry().quoteAssets) {
            cancelAllOffersForQuoteAsset(sale, saleQuoteAsset, delta, db);
        }

        if (lm.shouldUse(LedgerVersion::USE_SALE_ANTE)) {
            deleteAllAntesForSale(sale->getID(), delta, db);
        }

        AccountManager::unlockPendingIssuanceForSale(sale, delta, db, lm);
        SaleHelper::Instance()->storeDelete(delta, db, sale->getKey());
    }

    void ManageSaleOpFrame::cancelAllOffersForQuoteAsset(SaleFrame::pointer sale, SaleQuoteAsset const &saleQuoteAsset,
                                                         LedgerDelta &delta, Database &db) {
        auto orderBookID = sale->getID();
        const auto offersToCancel = OfferHelper::Instance()->loadOffersWithFilters(sale->getBaseAsset(),
                                                                                   saleQuoteAsset.quoteAsset,
                                                                                   &orderBookID, nullptr, db);
        OfferManager::deleteOffers(offersToCancel, db, delta);
    }

    void ManageSaleOpFrame::deleteAllAntesForSale(uint64_t saleID, LedgerDelta &delta, Database &db) {
        auto saleAntes = SaleAnteHelper::Instance()->loadSaleAntesForSale(saleID, db);
        for (auto &saleAnte : saleAntes) {
            auto participantBalanceFrame = BalanceHelperLegacy::Instance()->mustLoadBalance(
                    saleAnte->getParticipantBalanceID(),
                    db, &delta);
            const BalanceFrame::Result unlockResult = participantBalanceFrame->unlock(saleAnte->getAmount());
            if (unlockResult != BalanceFrame::Result::SUCCESS) {
                std::string strParticipantBalanceID = PubKeyUtils::toStrKey(saleAnte->getParticipantBalanceID());
                CLOG(ERROR, Logging::OPERATION_LOGGER)
                        << "Failed to unlock locked amount for sale ante with reason " << unlockResult
                        << " sale id: " << saleAnte->getSaleID() << " and participant balance id: "
                        << strParticipantBalanceID;
                throw std::runtime_error("Failed to unlock locked amount for sale ante");
            }

            EntryHelperProvider::storeChangeEntry(delta, db, participantBalanceFrame->mEntry);
            EntryHelperProvider::storeDeleteEntry(delta, db, saleAnte->getKey());
        }
    }

    bool ManageSaleOpFrame::doApply(Application &app, StorageHelper &storageHelper, LedgerManager &lm) {
        auto &db = storageHelper.getDatabase();
        auto delta = storageHelper.getLedgerDelta();

        auto saleFrame = getSourceAccount().getAccountType() == AccountType::MASTER
                         ? SaleHelper::Instance()->loadSale(mManageSaleOp.saleID, db, delta)
                         : SaleHelper::Instance()->loadSale(mManageSaleOp.saleID, getSourceID(), db, delta);

        if (!saleFrame) {
            innerResult().code(ManageSaleResultCode::SALE_NOT_FOUND);
            return false;
        }

        switch (mManageSaleOp.data.action()) {
            case ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST: {
                if (mManageSaleOp.data.updateSaleDetailsData().requestID != 0) {
                    return amendUpdateSaleDetailsRequest(app, lm, storageHelper);
                }
                return createUpdateSaleDetailsRequest(app, storageHelper, lm);
            }
            case ManageSaleAction::CANCEL: {
                cancelSale(saleFrame, *delta, db, lm);
                innerResult().code(ManageSaleResultCode::SUCCESS);
                innerResult().success().response.action(ManageSaleAction::CANCEL);
                break;
            }
            default:
                CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected action from manage sale op: "
                                                       << xdr::xdr_to_string(mManageSaleOp.data.action());
                throw std::runtime_error("Unexpected action from manage sale op");
        }

        return true;
    }

    bool ManageSaleOpFrame::doCheckValid(Application &app) {
        if (mManageSaleOp.saleID == 0) {
            innerResult().code(ManageSaleResultCode::SALE_NOT_FOUND);
            return false;
        }

        if (mManageSaleOp.data.action() != ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST) {
            return true;
        }

        if (!isValidJson(mManageSaleOp.data.updateSaleDetailsData().newDetails)) {
            innerResult().code(ManageSaleResultCode::INVALID_NEW_DETAILS);
            return false;
        }

        return true;
    }

    std::vector<longstring> ManageSaleOpFrame::makeTasksKeyVector(StorageHelper &storageHelper) {
        return std::vector<longstring> {
                ManageKeyValueOpFrame::makeSaleUpdateTasksKey(xdr::xdr_to_string(mManageSaleOp.saleID)),
                ManageKeyValueOpFrame::makeSaleUpdateTasksKey("*")
        };
    }

    bool ManageSaleOpFrame::ensureSaleUpdateDataValid(ReviewableRequestFrame::pointer request)
    {
        auto &updateSaleDetailsRequest = request->getRequestEntry().body.updateSaleDetailsRequest();
        auto updateSaleDetailsRequestData = mManageSaleOp.data.updateSaleDetailsData();

        if (updateSaleDetailsRequestData.allTasks)
        {
            innerResult().code(ManageSaleResultCode::NOT_ALLOWED_TO_SET_TASKS_ON_UPDATE);
            return false;
        }

        if (request->getRejectReason().empty()) {
            innerResult().code(ManageSaleResultCode::PENDING_REQUEST_UPDATE_NOT_ALLOWED);
            return false;
        }

        return true;
    }
}
