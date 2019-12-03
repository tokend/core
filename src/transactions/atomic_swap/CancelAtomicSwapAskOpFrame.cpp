#include "main/Application.h"
#include <database/Database.h>
#include <ledger/AtomicSwapAskHelper.h>
#include <ledger/BalanceHelper.h>
#include <ledger/EntryHelper.h>
#include "CancelAtomicSwapAskOpFrame.h"
#include "ledger/StorageHelper.h"
#include "ledger/AssetHelper.h"

using namespace std;

namespace stellar
{

CancelAtomicSwapAskOpFrame::CancelAtomicSwapAskOpFrame(Operation const& op,
                                                       OperationResult& opRes, TransactionFrame& parentTx)
    : OperationFrame(op, opRes, parentTx), mCancelASwapBid(mOperation.body.cancelAtomicSwapAskOp())
{
}

bool
CancelAtomicSwapAskOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                                                      std::vector<OperationCondition>& result) const
{
    // only ask owner can do this
    return true;
}

bool
CancelAtomicSwapAskOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                                     std::vector<SignerRequirement>& result) const
{
    auto ask = storageHelper.getAtomicSwapAskHelper().loadAtomicSwapAsk(
        mCancelASwapBid.askID);
    if (!ask)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::ATOMIC_SWAP_ASK;
        return false;
    }

    auto asset = storageHelper.getAssetHelper().mustLoadAsset(ask->getBaseAsset());
    if (!asset)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::ASSET;
        return false;
    }

    SignerRuleResource resource(LedgerEntryType::ATOMIC_SWAP_ASK);
    resource.atomicSwapAsk().assetCode = asset->getCode();
    resource.atomicSwapAsk().assetType = asset->getType();

    result.emplace_back(resource, SignerRuleAction::CANCEL);

    return true;
}

bool CancelAtomicSwapAskOpFrame::doApply(Application& app, StorageHelper& storageHelper,
                                         LedgerManager& ledgerManager)
{
    innerResult().code(CancelAtomicSwapAskResultCode::SUCCESS);
    auto& delta = storageHelper.mustGetLedgerDelta();

    auto askFrame = storageHelper.getAtomicSwapAskHelper().loadAtomicSwapAsk(
        getSourceID(), mCancelASwapBid.askID);
    if (askFrame == nullptr)
    {
        innerResult().code(CancelAtomicSwapAskResultCode::NOT_FOUND);
        return false;
    }

    if (askFrame->isCancelled())
    {
        innerResult().code(CancelAtomicSwapAskResultCode::ALREADY_CANCELLED);
        return false;
    }

    innerResult().success().lockedAmount = askFrame->getLockedAmount();
    if (askFrame->getLockedAmount() != 0)
    {
        askFrame->setIsCancelled(true);
        storageHelper.getAtomicSwapAskHelper().storeChange(askFrame->mEntry);
        return true;
    }

    auto& balanceHelper = storageHelper.getBalanceHelper();

    auto bidOwnerBalanceFrame = balanceHelper.loadBalance(askFrame->getOwnerID(), askFrame->getBaseAsset());
    if (!bidOwnerBalanceFrame)
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER) << "expected balance to exist";
        throw std::runtime_error("expected balance to exist");
    }

    if (bidOwnerBalanceFrame->unlock(askFrame->getAmount()) != BalanceFrame::Result::SUCCESS)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Unexpected state: failed to unlock amount in ask owner balance, "
               "ask ID: " << askFrame->getID();
        throw runtime_error(
            "Unexpected state: failed to unlock amount in ask owner balance");
    }
    storageHelper.getAtomicSwapAskHelper().storeChange(bidOwnerBalanceFrame->mEntry);
    storageHelper.getAtomicSwapAskHelper().storeDelete(askFrame->getKey());

    return true;
}

bool CancelAtomicSwapAskOpFrame::doCheckValid(Application& app)
{
    if (mCancelASwapBid.askID == 0)
    {
        innerResult().code(CancelAtomicSwapAskResultCode::NOT_FOUND);
        return false;
    }

    return true;
}

}
