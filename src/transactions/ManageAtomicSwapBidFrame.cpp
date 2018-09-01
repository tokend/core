#include "main/Application.h"
#include "database/Database.h"
#include "ledger/LedgerDelta.h"
#include "ledger/AssetHelper.h"
#include "ledger/BalanceHelper.h"
#include <transactions/dex/OfferManager.h>
#include <ledger/AtomicSwapBidHelper.h>
#include "ManageAtomicSwapBidFrame.h"
#include "FeesManager.h"

using namespace std;

namespace stellar
{

    ManageAtomicSwapBidOpFrame::ManageAtomicSwapBidOpFrame(Operation const &op,
                                                           OperationResult &opRes,
                                                           TransactionFrame &parentTx)
            : OperationFrame(op, opRes, parentTx),
              mManageAtomicSwapBidOp(mOperation.body.manageAtomicSwapBidOp())
    {
    }

    unordered_map<AccountID, CounterpartyDetails>
    ManageAtomicSwapBidOpFrame::getCounterpartyDetails(Database &db,
                                                       LedgerDelta *delta) const
    {
        // no counterparties
        return {};
    }

    SourceDetails
    ManageAtomicSwapBidOpFrame::getSourceAccountDetails(
            unordered_map<AccountID, CounterpartyDetails> counterpartiesDetails,
            int32_t ledgerVersion) const
    {
        return SourceDetails(getAllAccountTypes(), mSourceAccount->getMediumThreshold(),
                static_cast<int32_t>(SignerType::ATOMIC_SWAP_MANAGER));
    }

    bool
    ManageAtomicSwapBidOpFrame::assetsSupportSwap(AssetFrame::pointer baseAssetFrame,
                                                  AssetFrame::pointer quoteAssetFrame)
    {
        if (baseAssetFrame->isPolicySet(AssetPolicy::CAN_BE_BASE_IN_ATOMIC_SWAP))
        {
            innerResult().code(
                    ManageAtomicSwapBidResultCode::BASE_ASSET_CANNOT_BE_SWAPPED);
            return false;
        }

        if (quoteAssetFrame->isPolicySet(AssetPolicy::CAN_BE_QUOTE_IN_ATOMIC_SWAP))
        {
            innerResult().code(
                    ManageAtomicSwapBidResultCode::QUOTE_ASSET_CANNOT_BE_SWAPPED);
            return false;
        }

        return true;
    }

    AtomicSwapBidFrame::pointer
    ManageAtomicSwapBidOpFrame::buildNewBid(AccountID ownerID, AssetCode baseAsset,
                                            uint64_t ledgerCloseTime,
                                            CreateManageAtomicSwapBidData creationData,
                                            LedgerDelta& delta)
    {
        AtomicSwapBidEntry bidEntry;
        bidEntry.bidID = delta.getHeaderFrame().generateID(
                LedgerEntryType::ATOMIC_SWAP_BID);
        bidEntry.ownerID = ownerID;
        bidEntry.baseAsset = baseAsset;
        bidEntry.quoteAsset = creationData.quoteAsset;
        bidEntry.baseBalance = creationData.baseBalance;
        bidEntry.baseAmount = creationData.amount;
        bidEntry.price = creationData.price;
        bidEntry.details = creationData.details;
        bidEntry.createdAt = ledgerCloseTime;

        LedgerEntry le;
        le.data.type(LedgerEntryType::ATOMIC_SWAP_BID);
        le.data.atomicSwapBid() = bidEntry;
        return make_shared<AtomicSwapBidFrame>(le);
    }

    bool
    ManageAtomicSwapBidOpFrame::createAtomicSwapBid(Application &app,
                                                    LedgerDelta &delta,
                                                    LedgerManager &ledgerManager)
    {
        Database& db = app.getDatabase();

        auto& creationData = mManageAtomicSwapBidOp.data.creationData();

        BalanceFrame::pointer baseBalanceFrame =
                BalanceHelper::Instance()->loadBalance(creationData.baseBalance, db);
        if (baseBalanceFrame == nullptr)
        {
            innerResult().code(ManageAtomicSwapBidResultCode::BASE_BALANCE_NOT_FOUND);
            return false;
        }

        if (baseBalanceFrame->getAsset() == creationData.quoteAsset)
        {
            innerResult().code(ManageAtomicSwapBidResultCode::ASSETS_ARE_EQUAL);
            return false;
        }

        AssetFrame::pointer baseAssetFrame =
                AssetHelper::Instance()->loadAsset(baseBalanceFrame->getAsset(), db);
        if (baseAssetFrame == nullptr)
        {
            innerResult().code(ManageAtomicSwapBidResultCode::BASE_ASSET_NOT_FOUND);
            return false;
        }

        AssetFrame::pointer quoteAssetFrame =
                AssetHelper::Instance()->loadAsset(creationData.quoteAsset, db);
        if (quoteAssetFrame == nullptr)
        {
            innerResult().code(ManageAtomicSwapBidResultCode::QUOTE_ASSET_NOT_FOUND);
            return false;
        }

        if (!assetsSupportSwap(baseAssetFrame, quoteAssetFrame))
        {
            return false;
        }

        if (!baseBalanceFrame->hasEnoughAmount(creationData.amount))
        {
            innerResult().code(ManageAtomicSwapBidResultCode::BASE_BALANCE_UNDERFUNDED);
            return false;
        }

        auto bidFrame = buildNewBid(getSourceID(), baseAssetFrame->getCode(),
                                    ledgerManager.getCloseTime(), creationData, delta);

        auto const feeResult = FeeManager::calcualteFeeForAccount(
                mSourceAccount, FeeType::ATOMIC_SWAP_SALE_FEE, baseAssetFrame->getCode(),
                FeeFrame::SUBTYPE_ANY, bidFrame->getAmount(), db);

        if (feeResult.isOverflow)
        {
            innerResult().code(ManageAtomicSwapBidResultCode::ATOMIC_SWAP_BID_OVERFLOW);
            return false;
        }

        bidFrame->setFee(feeResult.calculatedPercentFee);
        bidFrame->setPercentFee(feeResult.percentFee);

        bool const isFeeEnough = bidFrame->getFee() <= creationData.fee;

        if (!isFeeEnough)
        {
            innerResult().code(ManageAtomicSwapBidResultCode::INSUFFICIENT_FEE);
            return false;
        }

        // TODO: maybe have to do the same thing here
        // offer.fee = mManageOffer.fee;

        EntryHelperProvider::storeAddEntry(delta, db, bidFrame->mEntry);

        innerResult().code(ManageAtomicSwapBidResultCode::SUCCESS);
        innerResult().success().bidID = bidFrame->getBidID();

        return true;
    }

    bool
    ManageAtomicSwapBidOpFrame::cancelAtomicSwapBid(Database &db, LedgerDelta &delta,
                                                    LedgerManager &ledgerManager)
    {
        auto bidFrame = AtomicSwapBidHelper::Instance()->loadAtomicSwapBid(
                getSourceID(), mManageAtomicSwapBidOp.data.bidID(), db, &delta);
        if (bidFrame == nullptr)
        {
            innerResult().code(ManageAtomicSwapBidResultCode::NOT_FOUND);
            return false;
        }

        EntryHelperProvider::storeDeleteEntry(delta, db, bidFrame->getKey());

        innerResult().code(ManageAtomicSwapBidResultCode::SUCCESS);
        innerResult().success().bidID = bidFrame->getBidID();
        return true;
    }

    bool ManageAtomicSwapBidOpFrame::doApply(Application &app, LedgerDelta &delta,
                                             LedgerManager &ledgerManager)
    {
        switch (mManageAtomicSwapBidOp.data.action())
        {
            case ManageAtomicSwapBidAction::CREATE:
            {
                return createAtomicSwapBid(app, delta, ledgerManager);
            }
            case ManageAtomicSwapBidAction ::CANCEL:
            {
                return cancelAtomicSwapBid(app, delta, ledgerManager);
            }
            default:
            {
                CLOG(ERROR, Logging::OPERATION_LOGGER)
                        << "Unexpected action from manage atomic swap bid op: "
                        << xdr::xdr_to_string(mManageAtomicSwapBidOp.data.action());
                throw runtime_error(
                        "Unexpected action from manage atomic swap bid op");
            }
        }
    }

    bool ManageAtomicSwapBidOpFrame::doCheckValid(Application &app)
    {
        if (mManageAtomicSwapBidOp.data.action() == ManageAtomicSwapBidAction::CANCEL)
        {
            if (mManageAtomicSwapBidOp.data.bidID() == 0)
            {
                innerResult().code(ManageAtomicSwapBidResultCode::NOT_FOUND);
                return false;
            }
            return true;
        }

        auto& creationData = mManageAtomicSwapBidOp.data.creationData();

        if (creationData.amount == 0)
        {
            innerResult().code(ManageAtomicSwapBidResultCode::INVALID_AMOUNT);
            return false;
        }

        if (creationData.price == 0)
        {
            innerResult().code(ManageAtomicSwapBidResultCode::INVALID_PRICE);
            return false;
        }

        if (!isValidJson(creationData.details))
        {
            innerResult().code(ManageAtomicSwapBidResultCode::INVALID_DETAILS);
            return false;
        }

        const bool isQuoteAmountFits = OfferManager::calculateQuoteAmount(
                creationData.amount, creationData.price) > 0;
        if (!isQuoteAmountFits)
        {
            innerResult().code(ManageAtomicSwapBidResultCode::ATOMIC_SWAP_BID_OVERFLOW);
            return false;
        }

        return true;
    }

}