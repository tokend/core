#include <transactions/dex/OfferManager.h>
#include <transactions/dex/CreateSaleParticipationOpFrame.h>
#include "test/test_marshaler.h"
#include "test/test.h"
#include "TxTests.h"
#include "test_helper/SaleRequestHelper.h"
#include "test_helper/ManageAssetTestHelper.h"
#include "test_helper/IssuanceRequestHelper.h"
#include "test_helper/ParticipateInSaleTestHelper.h"
#include "test_helper/ManageKeyValueTestHelper.h"
#include "test_helper/CheckSaleStateTestHelper.h"
#include "test_helper/ManageAccountSpecificRuleTestHelper.h"
#include "test_helper/CreateAccountTestHelper.h"
#include "test_helper/ManageBalanceTestHelper.h"
#include "ledger/StorageHelperImpl.h"
#include "ledger/BalanceHelper.h"
#include "ledger/SaleHelper.h"

using namespace stellar;
using namespace stellar::txtest;

// This test case check exceeding of max issuance amount of asset
TEST_CASE("Sale and specific rules", "[tx][sale][specific_rule]")
{
    Config const& cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);
    VirtualClock clock;
    Application::pointer appPtr = Application::create(clock, cfg);
    Application& app = *appPtr;
    app.start();
    auto testManager = TestManager::make(app);
    TestManager::upgradeToCurrentLedgerVersion(app);

    StorageHelperImpl storageHelperImpl(app.getDatabase(), nullptr);
    StorageHelper& storageHelper = storageHelperImpl;

    ManageAssetTestHelper assetTestHelper(testManager);
    IssuanceRequestHelper issuanceHelper(testManager);
    SaleRequestHelper saleRequestHelper(testManager);
    ParticipateInSaleTestHelper participateHelper(testManager);
    ManageKeyValueTestHelper manageKeyValueTestHelper(testManager);
    CheckSaleStateHelper checkStateHelper(testManager);
    ManageAccountSpecificRuleTestHelper specificRuleTestHelper(testManager);
    CreateAccountTestHelper createAccountTestHelper(testManager);
    ManageBalanceTestHelper manageBalanceTestHelper(testManager);

    manageKeyValueTestHelper.assetOpWithoutReview();
    longstring saleCreateKey = ManageKeyValueOpFrame::makeSaleCreateTasksKey("*");
    manageKeyValueTestHelper.setKey(saleCreateKey)->setUi32Value(0);
    manageKeyValueTestHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);

    auto root = Account{ getRoot(), Salt(0) };

    AssetCode baseAsset("BASE0ASSET");
    AssetCode quoteAsset("QUOTE0ASSET");
    uint32_t zeroTasks(0);
    uint64_t preIssuedAmount(3*ONE);

    auto saleOwner = Account{ SecretKey::random(), 0 };
    createAccountTestHelper.applyCreateAccountTx(root, saleOwner.key.getPublicKey(), 1);

    issuanceHelper.createAssetWithPreIssuedAmount(saleOwner, baseAsset, preIssuedAmount/3*2, root, 6, 1, preIssuedAmount);
    issuanceHelper.createAssetWithPreIssuedAmount(root, quoteAsset, preIssuedAmount, root, 6, 1);

    const uint64_t price = ONE;
    auto hardCap = preIssuedAmount / 3;
    uint64_t softCap = hardCap / 2;
    const auto currentTime = testManager->getLedgerManager().getCloseTime();
    const auto endTime = currentTime + 1000;
    const auto requiredBaseAssetForHardCap = ONE * hardCap / price;
    auto saleRequest = SaleRequestHelper::createSaleRequest(baseAsset, quoteAsset,
            currentTime, endTime, softCap, hardCap, "{}",
            {saleRequestHelper.createSaleQuoteAsset(quoteAsset, price)},
            requiredBaseAssetForHardCap);

    SECTION("Sale rule not supported")
    {
        auto saleID = saleRequestHelper.createApprovedSale(root, saleOwner, saleRequest)
                .success().typeExt.saleExtended().saleID;

        LedgerKey ledgerKey(LedgerEntryType::SALE);
        ledgerKey.sale().saleID = saleID;

        auto createRuleResult = specificRuleTestHelper.applyTx(root, ledgerKey, true, nullptr,
                ManageAccountSpecificRuleResultCode::SPECIFIC_RULE_NOT_SUPPORTED, TransactionResultCode::txFAILED);
    }

    saleRequest.ext.v(LedgerVersion::ADD_SALE_WHITELISTS);

    SECTION("Create with forbid rule")
    {
        saleRequest.ext.saleRules().emplace_back(nullptr, true, LedgerVersion::EMPTY_VERSION);

        auto saleID = saleRequestHelper.createApprovedSale(root, saleOwner, saleRequest)
                .success().typeExt.saleExtended().saleID;

        auto account = Account{ SecretKey::random(), 0 };
        AccountID accountID = account.key.getPublicKey();
        createAccountTestHelper.applyCreateAccountTx(root, accountID, 1);

        auto quoteBalance = BalanceHelperLegacy::Instance()->loadBalance(
                account.key.getPublicKey(), quoteAsset, testManager->getDB(), nullptr);
        auto baseBalance = manageBalanceTestHelper.applyManageBalanceTx(
                account, accountID, baseAsset).success().balanceID;

        auto manageOfferOp = OfferManager::buildManageOfferOp(baseBalance,
                quoteBalance->getBalanceID(), true, requiredBaseAssetForHardCap, price, 0, 0, saleID);
        auto result = participateHelper.applyManageOffer(account, manageOfferOp,
                ManageOfferResultCode::SPECIFIC_RULE_FORBIDS);

        LedgerKey ledgerKey(LedgerEntryType::SALE);
        ledgerKey.sale().saleID = saleID;

        specificRuleTestHelper.applyTx(saleOwner, ledgerKey, false, &accountID);

        participateHelper.addNewParticipant(root, account, saleID, baseAsset, quoteAsset, saleRequest.hardCap, price, 0);
        checkStateHelper.applyCheckSaleStateTx(root, saleID);
    }
    SECTION("Create with allow rules")
    {
        saleRequest.ext.saleRules().emplace_back(nullptr, false, LedgerVersion::EMPTY_VERSION);

        auto saleID = saleRequestHelper.createApprovedSale(root, saleOwner, saleRequest)
                .success().typeExt.saleExtended().saleID;

        auto account = Account{ SecretKey::random(), 0 };
        AccountID accountID = account.key.getPublicKey();
        createAccountTestHelper.applyCreateAccountTx(root, accountID, 1);

        participateHelper.addNewParticipant(root, account, saleID, baseAsset, quoteAsset, saleRequest.hardCap, price, 0);
        checkStateHelper.applyCheckSaleStateTx(root, saleID);
    }

    SECTION("Success sale creation")
    {

        saleRequest.ext.saleRules().emplace_back(nullptr, true, LedgerVersion::EMPTY_VERSION);
        auto saleID = saleRequestHelper.createApprovedSale(root, saleOwner, saleRequest)
                .success().typeExt.saleExtended().saleID;

        SECTION("Successful creation")
        {
            LedgerKey saleKey(LedgerEntryType::SALE);
            saleKey.sale().saleID = saleID;

            auto account = Account{ SecretKey::random(), 0 };
            AccountID accountID = account.key.getPublicKey();

            SECTION("Account not found")
            {
                auto createRuleResult = specificRuleTestHelper.applyTx(root, saleKey, true, &accountID,
                        ManageAccountSpecificRuleResultCode::ACCOUNT_NOT_FOUND, TransactionResultCode::txFAILED);
            }

            createAccountTestHelper.applyCreateAccountTx(root, accountID, 1);

            auto createRuleResult = specificRuleTestHelper.applyTx(root, saleKey, false, &accountID);

            SECTION("Create the same")
            {
                specificRuleTestHelper.applyTx(root, saleKey, false, &accountID,
                        ManageAccountSpecificRuleResultCode::ALREADY_EXISTS, TransactionResultCode::txFAILED);
            }

            SECTION("Create inverted")
            {
                specificRuleTestHelper.applyTx(root, saleKey, true, &accountID,
                        ManageAccountSpecificRuleResultCode::REVERSED_ALREADY_EXISTS, TransactionResultCode::txFAILED);
            }

            SECTION("Remove")
            {
                participateHelper.addNewParticipant(root, account, saleID, baseAsset, quoteAsset, saleRequest.hardCap, price, 0);
                specificRuleTestHelper.applyTx(root, createRuleResult.success().ruleID);
                checkStateHelper.applyCheckSaleStateTx(root, saleID, CheckSaleStateResultCode::NOT_READY);
                auto sale = SaleHelper::Instance()->loadSale(saleID, testManager->getDB());
                uint64_t currentCap(0);
                REQUIRE(CreateSaleParticipationOpFrame::getSaleCurrentCap(sale, testManager->getDB(), currentCap));
                REQUIRE(currentCap == 0);
                REQUIRE(sale->getCurrentCapInBase() == 0);

                SECTION("Create")
                {
                    specificRuleTestHelper.applyTx(root, saleKey, true, &accountID);
                }

                SECTION("Not authorized to create")
                {
                    specificRuleTestHelper.applyTx(account, saleKey, false, &accountID,
                            ManageAccountSpecificRuleResultCode::NOT_AUTHORIZED, TransactionResultCode::txFAILED);
                }
            }

            SECTION("Not authorized to remove")
            {
                specificRuleTestHelper.applyTx(account, createRuleResult.success().ruleID,
                        ManageAccountSpecificRuleResultCode::NOT_AUTHORIZED, TransactionResultCode::txFAILED);
            }
        }

        SECTION("Entry type not supported")
        {
            LedgerKey key(LedgerEntryType::ATOMIC_SWAP_BID);
            key.atomicSwapBid().bidID = 123;

            auto createRuleResult = specificRuleTestHelper.applyTx(root, key, true, nullptr,
                    ManageAccountSpecificRuleResultCode::ENTRY_TYPE_NOT_SUPPORTED, TransactionResultCode::txFAILED);
        }

        SECTION("Sale not found")
        {
            LedgerKey key(LedgerEntryType::SALE);
            key.sale().saleID = 1488;

            auto createRuleResult = specificRuleTestHelper.applyTx(root, key, true, nullptr,
                    ManageAccountSpecificRuleResultCode::SALE_NOT_FOUND, TransactionResultCode::txFAILED);
        }
    }
}
