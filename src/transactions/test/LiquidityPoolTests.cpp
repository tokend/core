#include <test/test.h>
#include "TxTests.h"
#include <ledger/StorageHelper.h>
#include <ledger/BalanceHelper.h>
#include <ledger/LiquidityPoolHelper.h>
#include <ledger/LedgerManager.h>
#include <transactions/test/test_helper/LiquidityPoolTestHelper.h>
#include <transactions/test/test_helper/CreateAccountTestHelper.h>
#include <transactions/test/test_helper/ManageAccountRuleTestHelper.h>
#include <transactions/test/test_helper/IssuanceRequestHelper.h>
#include <transactions/test/test_helper/ManageAssetTestHelper.h>
#include <transactions/test/test_helper/ManageKeyValueTestHelper.h>
#include <transactions/test/test_helper/ManageAccountRoleTestHelper.h>
#include <transactions/test/test_helper/ManageBalanceTestHelper.h>
#include <transactions/liquidity_pool/LiquidityPoolAddLiquidityOpFrame.h>

using namespace stellar;
using namespace stellar::txtest;

typedef std::unique_ptr<Application> appPtr;

TEST_CASE("Liquidity pool", "[tx][liquidity_pool]")
{
    struct TestSet
    {
        const AssetCode firstAsset;
        const uint64_t firstAssetType;
        const AssetCode secondAsset;
        const uint64_t secondAssetType;

        const uint64_t trailingDigitsCount;
    };

    const TestSet testSet = GENERATE(
        TestSet {"USD", 1, "BTC", 1, AssetFrame::kMaximumTrailingDigits}
    );

    Config const& cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);
    VirtualClock clock;
    Application::pointer appPtr = Application::create(clock, cfg);
    Application& app = *appPtr;
    app.start();

    auto testManager = TestManager::make(app);

    Database& db = testManager->getDB();

    auto root = Account{getRoot(), Salt(0)};

    //helpers
    auto liquidityPoolTestHelper = LiquidityPoolTestHelper(testManager);
    auto createAccountTestHelper = CreateAccountTestHelper(testManager);
    auto manageAccountRuleTestHelper = ManageAccountRuleTestHelper(testManager);
    auto issuanceTestHelper = IssuanceRequestHelper(testManager);
    auto manageKeyValueHelper = ManageKeyValueTestHelper(testManager);
    auto manageAssetTestHelper = ManageAssetTestHelper(testManager);
    auto manageAccountRoleTestHelper = ManageAccountRoleTestHelper(testManager);
    auto manageBalanceTestHelper = ManageBalanceTestHelper(testManager);
    auto& storageHelper = testManager->getStorageHelper();
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto& liquidityPoolHelper = storageHelper.getLiquidityPoolHelper();

    manageKeyValueHelper.assetOpWithoutReview();

    longstring assetKey = ManageKeyValueOpFrame::makeAssetCreateTasksKey();
    manageKeyValueHelper.setKey(assetKey)->setUi32Value(0);
    manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);

    const AssetCode& firstAsset = testSet.firstAsset;
    const AssetCode& secondAsset = testSet.secondAsset;

    const uint64_t precision = AssetFrame::getMinimumAmountFromTrailingDigits(testSet.trailingDigitsCount);
    const uint64_t maxNonDividedAmount = INT64_MAX - (INT64_MAX % precision);

    auto assetCreationRequest = manageAssetTestHelper.createAssetCreationRequest(firstAsset, root.key.getPublicKey(),
        "{}", maxNonDividedAmount, 0, nullptr, maxNonDividedAmount, testSet.trailingDigitsCount);
    manageAssetTestHelper.applyManageAssetTx(root, 0, assetCreationRequest);

    assetCreationRequest = manageAssetTestHelper.createAssetCreationRequest(secondAsset, root.key.getPublicKey(),
        "{}", maxNonDividedAmount, 0, nullptr, maxNonDividedAmount, testSet.trailingDigitsCount);
    manageAssetTestHelper.applyManageAssetTx(root, 0, assetCreationRequest);

    auto account = Account{ SecretKey::random(), Salt(1) };
    AccountID accountID = account.key.getPublicKey();
    createAccountTestHelper.applyCreateAccountTx(root, accountID, 1);

    auto createFirstBalanceRes = manageBalanceTestHelper.applyManageBalanceTx(account, accountID, firstAsset);
    BalanceID firstBalance = createFirstBalanceRes.success().balanceID;
    auto createSecondBalanceRes = manageBalanceTestHelper.applyManageBalanceTx(account, accountID, secondAsset);
    BalanceID secondBalance = createSecondBalanceRes.success().balanceID;

    uint64_t firstDesiredAmount = 10 * ONE;
    uint64_t secondDesiredAmount = 20 * ONE;
    uint64_t firstMinAmount = 10 * ONE;
    uint64_t secondMinAmount = 20 * ONE;

    uint32_t issuanceTasks = 0;
    issuanceTestHelper.applyCreateIssuanceRequest(root, firstAsset, firstDesiredAmount*1000, firstBalance,
        "Some reference1", &issuanceTasks);
    issuanceTestHelper.applyCreateIssuanceRequest(root, secondAsset, secondDesiredAmount*1000, secondBalance,
        "Some reference2", &issuanceTasks);

    const auto lpTokensAmount10x20 = 14142135;

    SECTION("Create liquidity pool with initial liquidity and provide liquidity again")
    {
        auto result = liquidityPoolTestHelper.applyAddLiquidityTx(account, firstBalance, secondBalance, firstDesiredAmount,
            secondDesiredAmount, firstMinAmount, secondMinAmount, LPAddLiquidityResultCode::SUCCESS);

        auto pool = liquidityPoolHelper.loadPool(firstAsset, secondAsset);
        REQUIRE(pool->getLPTokensAmount() == lpTokensAmount10x20);

        auto lpFirstBalance = balanceHelper.loadBalance(pool->getAccountID(), firstAsset);
        auto lpSecondBalance = balanceHelper.loadBalance(pool->getAccountID(), secondAsset);
        REQUIRE(lpFirstBalance->getAmount() == firstDesiredAmount);
        REQUIRE(lpSecondBalance->getAmount() == secondDesiredAmount);

        auto sourceLPBalance = balanceHelper.loadBalance(accountID, pool->getLpTokenAsset());
        REQUIRE(sourceLPBalance->getAmount() == pool->getLPTokensAmount());

        result = liquidityPoolTestHelper.applyAddLiquidityTx(account, firstBalance, secondBalance, firstDesiredAmount * 2,
            secondDesiredAmount * 2, firstMinAmount, secondMinAmount, LPAddLiquidityResultCode::SUCCESS);

        pool = liquidityPoolHelper.loadPool(firstAsset, secondAsset);
        REQUIRE(pool->getLPTokensAmount() == lpTokensAmount10x20 * 3);

        lpFirstBalance = balanceHelper.loadBalance(pool->getAccountID(), firstAsset);
        lpSecondBalance = balanceHelper.loadBalance(pool->getAccountID(), secondAsset);
        REQUIRE(lpFirstBalance->getAmount() == firstDesiredAmount * 3);
        REQUIRE(lpSecondBalance->getAmount() == secondDesiredAmount * 3);

        sourceLPBalance = balanceHelper.loadBalance(accountID, pool->getLpTokenAsset());
        REQUIRE(sourceLPBalance->getAmount() == pool->getLPTokensAmount());
    }

    SECTION("Provide liquidity to existing pool in assets reverse order")
    {
        auto result = liquidityPoolTestHelper.applyAddLiquidityTx(account, firstBalance, secondBalance, firstDesiredAmount,
            secondDesiredAmount, firstMinAmount, secondMinAmount, LPAddLiquidityResultCode::SUCCESS);

        auto pool = liquidityPoolHelper.loadPool(firstAsset, secondAsset);
        REQUIRE(pool->getLPTokensAmount() == lpTokensAmount10x20);

        auto lpFirstBalance = balanceHelper.loadBalance(pool->getAccountID(), firstAsset);
        auto lpSecondBalance = balanceHelper.loadBalance(pool->getAccountID(), secondAsset);
        REQUIRE(lpFirstBalance->getAmount() == firstDesiredAmount);
        REQUIRE(lpSecondBalance->getAmount() == secondDesiredAmount);

        auto sourceLPBalance = balanceHelper.loadBalance(accountID, pool->getLpTokenAsset());
        REQUIRE(sourceLPBalance->getAmount() == pool->getLPTokensAmount());

        result = liquidityPoolTestHelper.applyAddLiquidityTx(account, secondBalance, firstBalance, secondDesiredAmount * 2,
            firstDesiredAmount * 2, secondMinAmount, firstMinAmount, LPAddLiquidityResultCode::SUCCESS);

        pool = liquidityPoolHelper.loadPool(firstAsset, secondAsset);
        REQUIRE(pool->getLPTokensAmount() == lpTokensAmount10x20 * 3);

        lpFirstBalance = balanceHelper.loadBalance(pool->getAccountID(), firstAsset);
        lpSecondBalance = balanceHelper.loadBalance(pool->getAccountID(), secondAsset);
        REQUIRE(lpFirstBalance->getAmount() == firstDesiredAmount * 3);
        REQUIRE(lpSecondBalance->getAmount() == secondDesiredAmount * 3);

        sourceLPBalance = balanceHelper.loadBalance(accountID, pool->getLpTokenAsset());
        REQUIRE(sourceLPBalance->getAmount() == pool->getLPTokensAmount());
    }

    SECTION("Create liquidity pool and provide liquidity from different user")
    {
        auto result = liquidityPoolTestHelper.applyAddLiquidityTx(account, firstBalance, secondBalance, firstDesiredAmount,
            secondDesiredAmount, firstMinAmount, secondMinAmount, LPAddLiquidityResultCode::SUCCESS);

        // Create different account for second liquidity provider
        auto secondProvider = Account{ SecretKey::random(), Salt(1) };
        AccountID secondProviderID = secondProvider.key.getPublicKey();
        createAccountTestHelper.applyCreateAccountTx(root, secondProviderID, 1);

        createFirstBalanceRes = manageBalanceTestHelper.applyManageBalanceTx(secondProvider, secondProviderID,
            firstAsset);
        firstBalance = createFirstBalanceRes.success().balanceID;
        createSecondBalanceRes = manageBalanceTestHelper.applyManageBalanceTx(secondProvider, secondProviderID,
            secondAsset);
        secondBalance = createSecondBalanceRes.success().balanceID;

        issuanceTestHelper.applyCreateIssuanceRequest(root, firstAsset, firstDesiredAmount*1000, firstBalance,
            "Some reference3", &issuanceTasks);
        issuanceTestHelper.applyCreateIssuanceRequest(root, secondAsset, secondDesiredAmount*1000, secondBalance,
            "Some reference4", &issuanceTasks);

        result = liquidityPoolTestHelper.applyAddLiquidityTx(secondProvider, firstBalance, secondBalance,
            firstDesiredAmount, secondDesiredAmount, firstMinAmount, secondMinAmount,
            LPAddLiquidityResultCode::SUCCESS);

        auto pool = liquidityPoolHelper.loadPool(firstAsset, secondAsset);
        auto lpFirstBalance = balanceHelper.loadBalance(pool->getAccountID(), firstAsset);
        auto lpSecondBalance = balanceHelper.loadBalance(pool->getAccountID(), secondAsset);
        REQUIRE(lpFirstBalance->getAmount() == firstDesiredAmount * 2);
        REQUIRE(lpSecondBalance->getAmount() == secondDesiredAmount * 2);

        auto secondProviderLPBalance = balanceHelper.loadBalance(secondProviderID, pool->getLpTokenAsset());
        REQUIRE(secondProviderLPBalance->getAmount() == lpTokensAmount10x20);
    }

    SECTION("Provide liquidity with minAmount > desiredAmount")
    {
        liquidityPoolTestHelper.applyAddLiquidityTx(account, secondBalance, firstBalance, secondDesiredAmount * 3,
            firstDesiredAmount * 3, secondMinAmount * 4, firstMinAmount * 4,
            LPAddLiquidityResultCode::MIN_AMOUNT_BIGGER_THAN_DESIRED);
    }

    SECTION("Provide liquidity with equal balances")
    {
        liquidityPoolTestHelper.applyAddLiquidityTx(account, firstBalance, firstBalance, secondDesiredAmount,
            firstDesiredAmount, secondMinAmount, firstMinAmount, LPAddLiquidityResultCode::MALFORMED);
    }

    SECTION("Provide liquidity with zero desired amount")
    {
        liquidityPoolTestHelper.applyAddLiquidityTx(account, firstBalance, secondBalance, 0,
            firstDesiredAmount, secondMinAmount, firstMinAmount, LPAddLiquidityResultCode::INVALID_DESIRED_AMOUNT);
    }

    SECTION("Provide liquidity with zero min amount")
    {
        liquidityPoolTestHelper.applyAddLiquidityTx(account, firstBalance, secondBalance, secondDesiredAmount,
            firstDesiredAmount, 0, 0, LPAddLiquidityResultCode::INVALID_MIN_AMOUNT);
    }

    SECTION("Provide liquidity with insufficient amount")
    {
        liquidityPoolTestHelper.applyAddLiquidityTx(account, firstBalance, secondBalance, firstDesiredAmount * 200000,
            secondDesiredAmount * 200000, firstMinAmount, secondMinAmount, LPAddLiquidityResultCode::UNDERFUNDED);
    }

    SECTION("Provide liquidity with wrong amount ratio (first asset)")
    {
        liquidityPoolTestHelper.applyAddLiquidityTx(account, firstBalance, secondBalance, firstDesiredAmount * 11,
            secondDesiredAmount * 11, firstMinAmount, secondMinAmount, LPAddLiquidityResultCode::SUCCESS);

        liquidityPoolTestHelper.applyAddLiquidityTx(account, firstBalance, secondBalance, firstDesiredAmount * 2,
            secondDesiredAmount, firstMinAmount * 2, secondMinAmount,
            LPAddLiquidityResultCode::INSUFFICIENT_SECOND_ASSET_AMOUNT);
    }

    SECTION("Provide liquidity with wrong amount ratio (second asset)")
    {
        liquidityPoolTestHelper.applyAddLiquidityTx(account, firstBalance, secondBalance, firstDesiredAmount * 12,
            secondDesiredAmount * 12, firstMinAmount, secondMinAmount, LPAddLiquidityResultCode::SUCCESS);

        liquidityPoolTestHelper.applyAddLiquidityTx(account, firstBalance, secondBalance, firstDesiredAmount,
            secondDesiredAmount * 5, firstMinAmount, secondMinAmount * 5,
            LPAddLiquidityResultCode::INSUFFICIENT_FIRST_ASSET_AMOUNT);
    }

    SECTION("Provide liquidity with incorrect assets precision")
    {
        const AssetCode& firstAsset = "USD1";
        const AssetCode& secondAsset = "BTC1";

        const uint16_t firstPrecision = 5;
        const uint16_t secondPrecision = 3;

        const uint64_t precisionFirst = AssetFrame::getMinimumAmountFromTrailingDigits(firstPrecision);
        const uint64_t maxNonDividedAmountFirst = INT64_MAX - (INT64_MAX % precisionFirst);

        assetCreationRequest = manageAssetTestHelper.createAssetCreationRequest(firstAsset, root.key.getPublicKey(),
            "{}", maxNonDividedAmountFirst, 0, nullptr, maxNonDividedAmountFirst, firstPrecision);
        manageAssetTestHelper.applyManageAssetTx(root, 0, assetCreationRequest);

        const uint64_t precisionSecond = AssetFrame::getMinimumAmountFromTrailingDigits(secondPrecision);
        const uint64_t maxNonDividedAmountSecond = INT64_MAX - (INT64_MAX % precisionSecond);

        assetCreationRequest = manageAssetTestHelper.createAssetCreationRequest(secondAsset, root.key.getPublicKey(),
            "{}", maxNonDividedAmountSecond, 0, nullptr, maxNonDividedAmountSecond, secondPrecision);
        manageAssetTestHelper.applyManageAssetTx(root, 0, assetCreationRequest);

        createFirstBalanceRes = manageBalanceTestHelper.applyManageBalanceTx(account, accountID, firstAsset);
        firstBalance = createFirstBalanceRes.success().balanceID;
        createSecondBalanceRes = manageBalanceTestHelper.applyManageBalanceTx(account, accountID, secondAsset);
        secondBalance = createSecondBalanceRes.success().balanceID;

        liquidityPoolTestHelper.applyAddLiquidityTx(account, firstBalance, secondBalance, firstDesiredAmount*10,
            secondDesiredAmount, firstMinAmount, secondMinAmount, LPAddLiquidityResultCode::INCORRECT_AMOUNT_PRECISION);
    }
}
