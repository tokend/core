#include <ledger/FeeHelper.h>
#include "ledger/StorageHelper.h"
#include "ledger/AccountHelper.h"
#include "ledger/BalanceHelper.h"
#include "ParticipateInSaleTestHelper.h"
#include "transactions/test/TxTests.h"
#include "ledger/OfferHelper.h"
#include "ledger/SaleHelper.h"
#include "test/test_marshaler.h"
#include "IssuanceRequestHelper.h"
#include "ManageBalanceTestHelper.h"
#include "CreateAccountTestHelper.h"
#include "transactions/dex/OfferManager.h"

namespace stellar
{
namespace txtest
{
ParticipateInSaleTestHelper::ParticipateInSaleTestHelper(
    const TestManager::pointer testManager) : ManageOfferTestHelper(testManager)
{
}

BalanceEntry getBalance(LedgerDelta::KeyEntryMap& stateBeforeTx, BalanceID const& balanceID)
{
    LedgerKey key;
    key.type(LedgerEntryType::BALANCE);
    key.balance().balanceID = balanceID;
    return stateBeforeTx[key]->mEntry.data.balance();
}

void ParticipateInSaleTestHelper::ensureDeleteSuccess(Account& source,
                                                      ManageOfferOp op, const ManageOfferSuccessResult success,
                                                      LedgerDelta::KeyEntryMap& stateBeforeTx)
{
    LedgerKey key;
    key.type(LedgerEntryType::OFFER_ENTRY);
    key.offer().offerID = op.offerID;
    key.offer().ownerID = source.key.getPublicKey();
    auto offerBeforeTx = stateBeforeTx[key]->mEntry.data.offer();
    auto saleAfterTx = mTestManager->getStorageHelper().getSaleHelper().loadSale(op.orderBookID);
    auto balanceBeforeTx = getBalance(stateBeforeTx, offerBeforeTx.quoteBalance);
    SaleFrame saleBeforeTx(stateBeforeTx[saleAfterTx->getKey()]->mEntry);
    REQUIRE(saleBeforeTx.getSaleQuoteAsset(balanceBeforeTx.asset).currentCap
            == saleAfterTx->getSaleQuoteAsset(balanceBeforeTx.asset).currentCap + offerBeforeTx.quoteAmount);
    REQUIRE(saleBeforeTx.getSaleEntry().maxAmountToBeSold == saleAfterTx->getSaleEntry().maxAmountToBeSold);
    REQUIRE(saleBeforeTx.getSaleEntry().currentCapInBase
            == saleAfterTx->getSaleEntry().currentCapInBase + offerBeforeTx.baseAmount);
    ManageOfferTestHelper::ensureDeleteSuccess(source, op, success, stateBeforeTx);
}

void ParticipateInSaleTestHelper::ensureCreateSuccess(Account& source,
                                                      const ManageOfferOp op, ManageOfferSuccessResult success,
                                                      LedgerDelta::KeyEntryMap& stateBeforeTx)
{
    auto& storageHelper = mTestManager->getStorageHelper();

    auto saleAfterTx = storageHelper.getSaleHelper().loadSale(op.orderBookID);
    auto sale = stateBeforeTx.find(saleAfterTx->getKey());
    REQUIRE(sale != stateBeforeTx.end());
    SaleFrame saleBeforeTx(sale->second->mEntry);
    auto balanceBeforeTx = getBalance(stateBeforeTx, success.offer.offer().quoteBalance);
    REQUIRE(saleBeforeTx.getSaleQuoteAsset(balanceBeforeTx.asset).currentCap +
            success.offer.offer().quoteAmount == saleAfterTx->getSaleQuoteAsset(balanceBeforeTx.asset).currentCap);
    REQUIRE(saleBeforeTx.getSaleEntry().maxAmountToBeSold == saleAfterTx->getSaleEntry().maxAmountToBeSold);
    if (saleBeforeTx.getSaleType() != SaleType::CROWD_FUNDING)
    {
        REQUIRE(
            saleBeforeTx.getSaleEntry().currentCapInBase + op.amount == saleAfterTx->getSaleEntry().currentCapInBase);
    }

    auto sourceAccountFrame = storageHelper.getAccountHelper().loadAccount(source.key.getPublicKey());

    auto investFee = storageHelper.getFeeHelper().loadForAccount(FeeType::INVEST_FEE, balanceBeforeTx.asset, 0,
                                                           sourceAccountFrame, op.amount);
    if (!!investFee)
    {
        auto balanceAfterTx = storageHelper.getBalanceHelper().loadBalance(balanceBeforeTx.balanceID);
        REQUIRE(balanceAfterTx->getLocked() - success.offer.offer().quoteAmount ==
                balanceBeforeTx.locked);
    }

    return ManageOfferTestHelper::ensureCreateSuccess(source, op, success, stateBeforeTx);
}

    ManageOfferResult ParticipateInSaleTestHelper::addNewParticipant(Account& root, Account& participant, const uint64_t saleID, const AssetCode baseAsset,
                               const AssetCode quoteAsset, const uint64_t quoteAssetAmount, const uint64_t price, const uint64_t fee)
    {
        auto& storageHelper = mTestManager->getStorageHelper();
        IssuanceRequestHelper issuanceRequestHelper(mTestManager);
        auto quoteBalance = storageHelper.getBalanceHelper().loadBalance(participant.key.getPublicKey(), quoteAsset);
        REQUIRE(!!quoteBalance);
        // issue a tad more to ensure that it is enough to cover rounded up base amount
        const uint64 tad = quoteBalance->getMinimumAmount();
        uint32_t allTasks = 0;
        issuanceRequestHelper.authorizePreIssuedAmount(root, root.key, quoteAsset, quoteAssetAmount + fee + tad, root);
        issuanceRequestHelper.applyCreateIssuanceRequest(root, quoteAsset, quoteAssetAmount + fee + tad, quoteBalance->getBalanceID(),
                                                                          SecretKey::random().getStrKeyPublic(), &allTasks);

        auto accountID = participant.key.getPublicKey();
        auto balanceCreationResult = ManageBalanceTestHelper(mTestManager).applyManageBalanceTx(participant, accountID, baseAsset);
        const auto baseAssetAmount = bigDivide(quoteAssetAmount, ONE, price, ROUND_UP);
        auto manageOfferOp = OfferManager::buildManageOfferOp(balanceCreationResult.success().balanceID, quoteBalance->getBalanceID(),
                                                              true, baseAssetAmount, price, fee, 0, saleID);
        return applyManageOffer(participant, manageOfferOp);
    }

    ManageOfferResult ParticipateInSaleTestHelper::addNewParticipant(Account& root, const uint64_t saleID, const AssetCode baseAsset,
                               const AssetCode quoteAsset, const uint64_t quoteAssetAmount, const uint64_t price, const uint64_t fee)
    {
        auto account = Account{ SecretKey::random(), 0 };
        CreateAccountTestHelper(mTestManager).applyCreateAccountTx(root, account.key.getPublicKey(), 1);
        return addNewParticipant(root, account, saleID, baseAsset, quoteAsset, quoteAssetAmount, price, fee);
    }

}
}
