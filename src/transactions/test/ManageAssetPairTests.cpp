// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0
#include <transactions/test/test_helper/TestManager.h>
#include <transactions/test/test_helper/ManageAssetPairTestHelper.h>
#include <transactions/test/test_helper/ManageAssetTestHelper.h>
#include "main/Application.h"
#include "util/Timer.h"
#include "main/Config.h"
#include "test/test.h"
#include "TxTests.h"
#include "ledger/LedgerDelta.h"
#include "test/test_marshaler.h"
#include "transactions/test/test_helper/CreateAccountTestHelper.h"
#include "transactions/test/test_helper/ManageAccountRoleTestHelper.h"
#include "transactions/test/test_helper/ManageOfferTestHelper.h"
#include "transactions/test/test_helper/IssuanceRequestHelper.h"
#include "transactions/test/test_helper/SaleRequestHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/StorageHelper.h"

using namespace stellar;
using namespace stellar::txtest;

typedef std::unique_ptr<Application> appPtr;

TEST_CASE("manage asset pair", "[tx][manage_asset_pair]")
{
    Config const& cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);
    VirtualClock clock;
    Application::pointer appPtr = Application::create(clock, cfg);
    Application& app = *appPtr;
    app.start();
    auto testManager = TestManager::make(app);
<<<<<<< HEAD

=======
    testManager->upgradeToCurrentLedgerVersion(app);
    auto assetPairTestHelper = ManageAssetPairTestHelper(testManager);

    // set up world
>>>>>>> master
    auto root = Account{getRoot(), 0};

    auto assetPairTestHelper = ManageAssetPairTestHelper(testManager);
    CreateAccountTestHelper createAccountTestHelper(testManager);
    ManageAccountRoleTestHelper manageAccountRoleTestHelper(testManager);
    auto createAccountBuilder = CreateAccountTestBuilder()
            .setSource(root);
    ManageOfferTestHelper offerTestHelper(testManager);
    IssuanceRequestHelper issuanceTestHelper(testManager);
    SaleRequestHelper saleTestHelper(testManager);
    BalanceHelper& balanceHelper = testManager->getStorageHelper().getBalanceHelper();

    SECTION("Basic")
    {
        AssetCode base = "EUR";
        const AssetCode quote = "UAH";
        int64_t physicalPrice = 12;
        int64_t physicalPriceCorrection = 95 * ONE;
        int64_t maxPriceStep = 5 * ONE;
        int32_t policies = getAnyAssetPairPolicy();
        SECTION("Invalid asset")
        {
            base = "''asd";
            assetPairTestHelper.applyManageAssetPairTx(root, base, quote,
                                                       physicalPrice,
                                                       physicalPriceCorrection,
                                                       maxPriceStep, policies,
                                                       ManageAssetPairAction::
                                                       CREATE, nullptr,
                                                       ManageAssetPairResultCode
                                                       ::INVALID_ASSET);
            assetPairTestHelper.applyManageAssetPairTx(root, quote, base,
                                                       physicalPrice,
                                                       physicalPriceCorrection,
                                                       maxPriceStep, policies,
                                                       ManageAssetPairAction::
                                                       CREATE, nullptr,
                                                       ManageAssetPairResultCode
                                                       ::INVALID_ASSET);
        }

        SECTION("Same asset")
        {
            base = quote;
            assetPairTestHelper.applyManageAssetPairTx(root, base, quote,
                                                       physicalPrice,
                                                       physicalPriceCorrection,
                                                       maxPriceStep, policies,
                                                       ManageAssetPairAction::
                                                       CREATE, nullptr,
                                                       ManageAssetPairResultCode::SAME_ASSET);
            assetPairTestHelper.applyManageAssetPairTx(root, quote, base,
                                                       physicalPrice,
                                                       physicalPriceCorrection,
                                                       maxPriceStep, policies,
                                                       ManageAssetPairAction::
                                                       CREATE, nullptr,
                                                       ManageAssetPairResultCode::SAME_ASSET);
        }
        SECTION("Invalid action")
        {
            assetPairTestHelper.applyManageAssetPairTx(root, quote, base,
                                                       physicalPrice,
                                                       physicalPriceCorrection,
                                                       maxPriceStep, policies,
                                                       ManageAssetPairAction(1201),
                                                       nullptr,
                                                       ManageAssetPairResultCode
                                                       ::INVALID_ACTION);
        }
        SECTION("Invalid physical price")
        {
            assetPairTestHelper.applyManageAssetPairTx(root, quote, base,
                                                       -physicalPrice,
                                                       physicalPriceCorrection,
                                                       maxPriceStep, policies,
                                                       ManageAssetPairAction::
                                                       CREATE, nullptr,
                                                       ManageAssetPairResultCode
                                                       ::MALFORMED);
        }
        SECTION("Invalid physical price correction")
        {
            assetPairTestHelper.applyManageAssetPairTx(root, quote, base,
                                                       physicalPrice,
                                                       -physicalPriceCorrection,
                                                       maxPriceStep, policies,
                                                       ManageAssetPairAction::
                                                       CREATE, nullptr,
                                                       ManageAssetPairResultCode
                                                       ::MALFORMED);
        }
        SECTION("Invalid max price step")
        {
            assetPairTestHelper.applyManageAssetPairTx(root, quote, base,
                                                       physicalPrice,
                                                       physicalPriceCorrection,
                                                       -maxPriceStep, policies,
                                                       ManageAssetPairAction::
                                                       CREATE, nullptr,
                                                       ManageAssetPairResultCode
                                                       ::MALFORMED);
        }
        SECTION("Invalid policies")
        {
            assetPairTestHelper.applyManageAssetPairTx(root, quote, base,
                                                       physicalPrice,
                                                       physicalPriceCorrection,
                                                       maxPriceStep, -policies,
                                                       ManageAssetPairAction::
                                                       CREATE, nullptr,
                                                       ManageAssetPairResultCode
                                                       ::INVALID_POLICIES);
        }
        SECTION("Asset does not exists")
        {
            assetPairTestHelper.applyManageAssetPairTx(root, quote, base,
                                                       physicalPrice,
                                                       physicalPriceCorrection,
                                                       maxPriceStep, policies,
                                                       ManageAssetPairAction::
                                                       CREATE, nullptr,
                                                       ManageAssetPairResultCode
                                                       ::ASSET_NOT_FOUND);
        }
        SECTION("Asset created")
        {
            uint32_t zeroTasks = 0;
            auto assetTestHelper = ManageAssetTestHelper(testManager);
            assetTestHelper.createAsset(root, root.key, base, root, 0, &zeroTasks);
            assetTestHelper.createAsset(root, root.key, quote, root, 0, &zeroTasks);
            SECTION("Pair already exists")
            {
                assetPairTestHelper.applyManageAssetPairTx(root, quote, base,
                                                           physicalPrice,
                                                           physicalPriceCorrection,
                                                           maxPriceStep,
                                                           policies);
                assetPairTestHelper.applyManageAssetPairTx(root, quote, base,
                                                           physicalPrice,
                                                           physicalPriceCorrection,
                                                           maxPriceStep,
                                                           policies,
                                                           ManageAssetPairAction
                                                           ::CREATE, nullptr,
                                                           ManageAssetPairResultCode
                                                           ::ALREADY_EXISTS);
                // reverse pair already exists
                assetPairTestHelper.applyManageAssetPairTx(root, base, quote,
                                                           physicalPrice,
                                                           physicalPriceCorrection,
                                                           maxPriceStep,
                                                           policies,
                                                           ManageAssetPairAction
                                                           ::CREATE, nullptr,
                                                           ManageAssetPairResultCode
                                                           ::ALREADY_EXISTS);
            }
            SECTION("Pair does not exists")
            {
                assetPairTestHelper.applyManageAssetPairTx(root, quote, base,
                                                           physicalPrice,
                                                           physicalPriceCorrection,
                                                           maxPriceStep,
                                                           policies,
                                                           ManageAssetPairAction
                                                           ::UPDATE_POLICIES,
                                                           nullptr,
                                                           ManageAssetPairResultCode
                                                           ::NOT_FOUND);
                assetPairTestHelper.applyManageAssetPairTx(root, quote, base,
                                                           physicalPrice,
                                                           physicalPriceCorrection,
                                                           maxPriceStep,
                                                           policies,
                                                           ManageAssetPairAction
                                                           ::UPDATE_PRICE,
                                                           nullptr,
                                                           ManageAssetPairResultCode
                                                           ::NOT_FOUND);
            }
            SECTION("Create -> update policies -> update price")
            {
                // create
                assetPairTestHelper.applyManageAssetPairTx(root, quote, base,
                                                           physicalPrice,
                                                           physicalPriceCorrection,
                                                           maxPriceStep,
                                                           policies,
                                                           ManageAssetPairAction
                                                           ::CREATE);
                // update policies
                physicalPriceCorrection = physicalPriceCorrection + 100 * ONE;
                maxPriceStep = maxPriceStep + 1 * ONE;
                policies = static_cast<int32_t>(AssetPairPolicy::TRADEABLE_SECONDARY_MARKET) |
                           static_cast<int32_t>(AssetPairPolicy::
                               CURRENT_PRICE_RESTRICTION);
                assetPairTestHelper.applyManageAssetPairTx(root, quote, base,
                                                           physicalPrice,
                                                           physicalPriceCorrection,
                                                           maxPriceStep,
                                                           policies,
                                                           ManageAssetPairAction
                                                           ::UPDATE_POLICIES);
                // update price
                physicalPrice = physicalPrice + 125 * ONE;
                assetPairTestHelper.applyManageAssetPairTx(root, quote, base,
                                                           physicalPrice,
                                                           physicalPriceCorrection,
                                                           maxPriceStep,
                                                           policies,
                                                           ManageAssetPairAction
                                                           ::UPDATE_PRICE);
            }
        }
        SECTION("Remove asset pair")
        {
            uint32_t zeroTasks = 0;
            auto assetTestHelper = ManageAssetTestHelper(testManager);
            assetTestHelper.createAsset(root, root.key, base, root, 0, &zeroTasks);
            assetTestHelper.createAsset(root, root.key, quote, root, 0, &zeroTasks);

            assetPairTestHelper.createAssetPair(root, base, quote, physicalPrice, physicalPriceCorrection,
                    maxPriceStep, policies);

            SECTION("Invalid asset code")
            {
                assetPairTestHelper.applyRemoveAssetPairTx(root, "''asd", quote, nullptr,
                                                           RemoveAssetPairResultCode::INVALID_ASSET_CODE);
            }
            SECTION("Asset pair not found")
            {
                assetPairTestHelper.applyRemoveAssetPairTx(root, quote, base, nullptr,
                                                           RemoveAssetPairResultCode::NOT_FOUND);
            }
            SECTION("Has active sales")
            {
                auto pubKey = root.key.getPublicKey();
                auto saleAmount = 200 * ONE;

                issuanceTestHelper.applyCreatePreIssuanceRequest(root, root.key, base, saleAmount,
                        SecretKey::random().getStrKeyPublic(), CreatePreIssuanceRequestResultCode::SUCCESS, &zeroTasks);
                const auto currentTime = testManager->getLedgerManager().getCloseTime();
                const auto endTime = currentTime + 1000;
                auto saleRequest = SaleRequestHelper::createSaleRequest(base, quote, currentTime, endTime, saleAmount,
                        saleAmount, "{}", {saleTestHelper.createSaleQuoteAsset(quote, ONE)}, saleAmount);
                saleTestHelper.applyCreateSaleRequest(root, 0, saleRequest, &zeroTasks);

                assetPairTestHelper.applyRemoveAssetPairTx(root, base, quote, nullptr,
                                                           RemoveAssetPairResultCode::HAS_ACTIVE_SALES);
            }
            SECTION("Has active offers")
            {
                auto pubKey = root.key.getPublicKey();
                auto baseBalance = balanceHelper.loadBalance(pubKey, base);
                auto quoteBalance = balanceHelper.loadBalance(pubKey, quote);
                auto offerAmount = 200 * ONE;

                issuanceTestHelper.applyCreatePreIssuanceRequest(root, root.key, base, offerAmount,
                        SecretKey::random().getStrKeyPublic(), CreatePreIssuanceRequestResultCode::SUCCESS, &zeroTasks);
                issuanceTestHelper.applyCreateIssuanceRequest(root, base, offerAmount, baseBalance->getBalanceID(),
                        SecretKey::random().getStrKeyPublic(), &zeroTasks);

                offerTestHelper.applyManageOffer(root, 0,
                                                 baseBalance->getBalanceID(),
                                                 quoteBalance->getBalanceID(),
                                                 offerAmount / 2, 5 * ONE, false, 0);

                assetPairTestHelper.applyRemoveAssetPairTx(root, base, quote, nullptr,
                                                           RemoveAssetPairResultCode::HAS_ACTIVE_OFFERS);
            }
            SECTION("Try to remove without role permissions")
            {
                auto roleId = manageAccountRoleTestHelper.createTxSenderRole(root);
                auto account = Account{ SecretKey::random(), 0 };
                createAccountTestHelper.applyTx(createAccountBuilder
                                                        .setToPublicKey(account.key.getPublicKey())
                                                        .addBasicSigner()
                                                        .setRoleID(roleId));

                assetPairTestHelper.applyRemoveAssetPairTx(account, base, quote, nullptr,
                        RemoveAssetPairResultCode::SUCCESS, // No need to check inner result code
                        OperationResultCode::opNO_ROLE_PERMISSION);
            }
            SECTION("Success")
            {
                assetPairTestHelper.applyRemoveAssetPairTx(root, base, quote, nullptr,
                                                           RemoveAssetPairResultCode::SUCCESS);
            }
        }
    }
}
