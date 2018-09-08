#include "main/Application.h"
#include "database/Database.h"
#include <transactions/dex/OfferManager.h>
#include <ledger/LedgerDelta.h>
#include <ledger/BalanceHelper.h>
#include <ledger/AssetHelper.h>
#include <ledger/ReviewableRequestFrame.h>
#include <ledger/ReviewableRequestHelper.h>
#include "CreateASwapBidCreationRequestOpFrame.h"

using namespace std;

namespace stellar
{

CreateASwapBidCreationRequestOpFrame::CreateASwapBidCreationRequestOpFrame(
        Operation const &op, OperationResult &opRes, TransactionFrame &parentTx)
        : OperationFrame(op, opRes, parentTx),
          mCreateASwapBidCreationRequest(
                  mOperation.body.createASwapBidCreationRequestOp())
{
}

std::unordered_map<AccountID, CounterpartyDetails>
CreateASwapBidCreationRequestOpFrame::getCounterpartyDetails(Database &db,
                                                          LedgerDelta *delta) const
{
    // no counterparties
    return {};
}

SourceDetails CreateASwapBidCreationRequestOpFrame::getSourceAccountDetails(
        std::unordered_map<AccountID, CounterpartyDetails> counterpartiesDetails,
        int32_t ledgerVersion) const
{
    return SourceDetails(getAllAccountTypes(), mSourceAccount->getHighThreshold(),
                         static_cast<int32_t>(SignerType::ATOMIC_SWAP_MANAGER));
}

CreateASwapBidCreationRequestResultCode
CreateASwapBidCreationRequestOpFrame::isBaseAssetValid(Database &db,
                                                       AssetCode baseAssetCode)
{
    AssetFrame::pointer baseAssetFrame =
            AssetHelper::Instance()->loadAsset(baseAssetCode, db);
    if (baseAssetFrame == nullptr)
    {
        return CreateASwapBidCreationRequestResultCode::BASE_ASSET_NOT_FOUND;
    }

    if (!baseAssetFrame->isPolicySet(AssetPolicy::CAN_BE_BASE_IN_ATOMIC_SWAP))
    {
        return CreateASwapBidCreationRequestResultCode::BASE_ASSET_CANNOT_BE_SWAPPED;
    }

    return CreateASwapBidCreationRequestResultCode::SUCCESS;
}

CreateASwapBidCreationRequestResultCode
CreateASwapBidCreationRequestOpFrame::isQuoteAssetValid(Database& db,
                                                        AssetCode baseAssetCode,
                                                        AssetCode quoteAssetCode)
{
    if (baseAssetCode == quoteAssetCode)
    {
        return CreateASwapBidCreationRequestResultCode::ASSETS_ARE_EQUAL;
    }

    auto quoteAssetFrame = AssetHelper::Instance()->loadAsset(quoteAssetCode, db);

    if (quoteAssetFrame == nullptr)
    {
        return CreateASwapBidCreationRequestResultCode::QUOTE_ASSET_NOT_FOUND;
    }

    if (!quoteAssetFrame->isPolicySet(AssetPolicy::CAN_BE_QUOTE_IN_ATOMIC_SWAP))
    {
        return CreateASwapBidCreationRequestResultCode::QUOTE_ASSET_CANNOT_BE_SWAPPED;
    }

    return CreateASwapBidCreationRequestResultCode::SUCCESS;
}

CreateASwapBidCreationRequestResultCode
CreateASwapBidCreationRequestOpFrame::areQuoteAssetsValid(
        Database& db, AssetCode baseAssetCode,
        xdr::xvector<ASwapBidQuoteAsset> quoteAssets)
{
    for (auto const& quoteAsset : quoteAssets)
    {
        auto quoteAssetValidationResultCode = isQuoteAssetValid(db, baseAssetCode,
                                                                quoteAsset.quoteAsset);
        if (quoteAssetValidationResultCode !=
            CreateASwapBidCreationRequestResultCode::SUCCESS)
        {
            return quoteAssetValidationResultCode;
        }
    }

    return CreateASwapBidCreationRequestResultCode::SUCCESS;
}

CreateASwapBidCreationRequestResultCode
CreateASwapBidCreationRequestOpFrame::areAllAssetsValid(
        Database &db, AssetCode baseAssetCode,
        xdr::xvector<ASwapBidQuoteAsset> quoteAssets)
{
    CreateASwapBidCreationRequestResultCode validationResultCode = isBaseAssetValid(
            db, baseAssetCode);
    if (validationResultCode != CreateASwapBidCreationRequestResultCode::SUCCESS)
    {
        return validationResultCode;
    }

    validationResultCode = areQuoteAssetsValid(db, baseAssetCode, quoteAssets);
    if (validationResultCode != CreateASwapBidCreationRequestResultCode::SUCCESS)
    {
        return validationResultCode;
    }

    return CreateASwapBidCreationRequestResultCode::SUCCESS;
}

bool CreateASwapBidCreationRequestOpFrame::doApply(Application &app, LedgerDelta &delta,
                                                LedgerManager &ledgerManager)
{
    Database& db = app.getDatabase();

    auto& aSwapBidCreationRequest = mCreateASwapBidCreationRequest.request;

    BalanceFrame::pointer baseBalanceFrame = BalanceHelper::Instance()->loadBalance(
                    getSourceID(), aSwapBidCreationRequest.baseBalance, db);
    if (baseBalanceFrame == nullptr)
    {
        innerResult().code(
                CreateASwapBidCreationRequestResultCode::BASE_BALANCE_NOT_FOUND);
        return false;
    }

    auto allAssetsValidationResultCode = areAllAssetsValid(
            db, baseBalanceFrame->getAsset(), aSwapBidCreationRequest.quoteAssets);
    if (allAssetsValidationResultCode !=
        CreateASwapBidCreationRequestResultCode::SUCCESS)
    {
        innerResult().code(allAssetsValidationResultCode);
        return false;
    }

    // TODO: move asset requirements check to separate method
    auto baseAssetFrame = AssetHelper::Instance()->loadAsset(baseBalanceFrame->getAsset(),
                                                             getSourceID(), db);
    if (baseAssetFrame == nullptr)
    {
        innerResult().code(CreateASwapBidCreationRequestResultCode::BASE_ASSET_NOT_FOUND);
        return false;
    }

    auto& sourceAccount = getSourceAccount();

    if (baseAssetFrame->isRequireVerification() &&
        sourceAccount.getAccountType() == AccountType::NOT_VERIFIED)
    {
        innerResult().code(
                CreateASwapBidCreationRequestResultCode::NOT_ALLOWED_BY_ASSET_POLICY);
        return false;
    }

    if (baseAssetFrame->isRequireKYC() &&
        (sourceAccount.getAccountType() == AccountType::NOT_VERIFIED ||
         sourceAccount.getAccountType() == AccountType::VERIFIED))
    {
        innerResult().code(
                CreateASwapBidCreationRequestResultCode::NOT_ALLOWED_BY_ASSET_POLICY);
        return false;
    }

    auto lockResult = baseBalanceFrame->tryLock(aSwapBidCreationRequest.amount);
    if (lockResult != BalanceFrame::Result::SUCCESS)
    {
        innerResult().code(
                CreateASwapBidCreationRequestResultCode::BASE_BALANCE_UNDERFUNDED);
        return false;
    }

    auto requestFrame = ReviewableRequestFrame::createNew(delta, getSourceID(),
                                                          app.getMasterID(), nullptr,
                                                          ledgerManager.getCloseTime());
    auto& requestEntry = requestFrame->getRequestEntry();
    requestEntry.body.type(ReviewableRequestType::CREATE_ATOMIC_SWAP_BID);
    requestEntry.body.aSwapBidCreationRequest() = aSwapBidCreationRequest;

    requestFrame->recalculateHashRejectReason();

    ReviewableRequestHelper::Instance()->storeAdd(delta, db, requestFrame->mEntry);

    innerResult().code(CreateASwapBidCreationRequestResultCode::SUCCESS);
    innerResult().success().requestID = requestFrame->getRequestID();

    return true;
}

bool CreateASwapBidCreationRequestOpFrame::doCheckValid(Application &app)
{
    auto& aSwapCreationRequest = mCreateASwapBidCreationRequest.request;

    if (aSwapCreationRequest.amount == 0)
    {
        innerResult().code(CreateASwapBidCreationRequestResultCode::INVALID_AMOUNT);
        return false;
    }

    if (!isValidJson(aSwapCreationRequest.details))
    {
        innerResult().code(CreateASwapBidCreationRequestResultCode::INVALID_DETAILS);
        return false;
    }

    set<AssetCode> quoteAssets;
    for (auto const& quoteAsset : aSwapCreationRequest.quoteAssets)
    {
        if (!AssetFrame::isAssetCodeValid(quoteAsset.quoteAsset))
        {
            innerResult().code(
                    CreateASwapBidCreationRequestResultCode::INVALID_QUOTE_ASSET);
            return false;
        }

        if (quoteAssets.find(quoteAsset.quoteAsset) != quoteAssets.end())
        {
            innerResult().code(
                    CreateASwapBidCreationRequestResultCode::INVALID_QUOTE_ASSET);
            return false;
        }

        quoteAssets.insert(quoteAsset.quoteAsset);

        if (quoteAsset.price == 0)
        {
            innerResult().code(CreateASwapBidCreationRequestResultCode::INVALID_PRICE);
        }

        const bool isQuoteAmountFits = OfferManager::calculateQuoteAmount(
                aSwapCreationRequest.amount, quoteAsset.price) > 0;
        if (!isQuoteAmountFits)
        {
            innerResult().code(
                    CreateASwapBidCreationRequestResultCode::ATOMIC_SWAP_BID_OVERFLOW);
            return false;
        }
    }

    return true;
}

}