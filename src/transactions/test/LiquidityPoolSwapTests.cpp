#include <test/test.h>
#include "TxTests.h"
#include <ledger/StorageHelper.h>
#include <ledger/BalanceHelper.h>
#include <ledger/LiquidityPoolHelper.h>
#include <ledger/LedgerManager.h>
#include <transactions/test/test_helper/LPSwapTestHelper.h>
#include <transactions/test/test_helper/LPAddLiquidityTestHelper.h>
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

TEST_CASE("LP swap", "[tx][liquidity_pool][swap]")
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
        TestSet {"USD", 1, "BTC", 1, AssetFrame::kMaximumTrailingDigits},
        TestSet {"BTC", 1, "USD", 1, AssetFrame::kMaximumTrailingDigits}
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
    auto lpSwapTestHelper = LPSwapTestHelper(testManager);
    auto lpAddLiquidityTestHelper = LPAddLiquidityTestHelper(testManager);
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

    AssetCode firstAsset = testSet.firstAsset;
    AssetCode secondAsset = testSet.secondAsset;

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
    issuanceTestHelper.applyCreateIssuanceRequest(root, firstAsset, firstDesiredAmount*100, firstBalance,
        "Some reference1", &issuanceTasks);
    issuanceTestHelper.applyCreateIssuanceRequest(root, secondAsset, secondDesiredAmount*100, secondBalance,
        "Some reference2", &issuanceTasks);

    auto result = lpAddLiquidityTestHelper.applyAddLiquidityTx(account, firstBalance, secondBalance,
        firstDesiredAmount, secondDesiredAmount, firstMinAmount, secondMinAmount, LPAddLiquidityResultCode::SUCCESS);

    SECTION("Swap exact A to B")
    {
        auto sourceFromBalanceBeforeSwap = balanceHelper.loadBalance(firstBalance);
        auto sourceToBalanceBeforeSwap = balanceHelper.loadBalance(secondBalance);

        uint64_t amountIn = 1 * ONE, amountOutMin = 1.8 * ONE;
        auto swapResult = lpSwapTestHelper.applyLPSwapTx(account, LPSwapType::EXACT_OUT_TOKENS_FOR_IN_TOKENS, firstBalance,
            secondBalance, amountIn, amountOutMin, LPSwapResultCode::SUCCESS);

        auto lpTokenAsset = LiquidityPoolFrame::calculateLPTokenAssetCode(firstAsset, secondAsset);
        auto pool = liquidityPoolHelper.loadPool(lpTokenAsset);

        auto lpFirstBalance = balanceHelper.loadBalance(pool->getFirstAssetBalance());
        auto lpSecondBalance = balanceHelper.loadBalance(pool->getSecondAssetBalance());

        REQUIRE(pool->getFirstReserve() == lpFirstBalance->getAmount());
        REQUIRE(pool->getSecondReserve() == lpSecondBalance->getAmount());

        auto sourceFromBalanceAfterSwap = balanceHelper.loadBalance(swapResult.success().sourceInBalanceID, accountID);
        auto sourceToBalanceAfterSwap = balanceHelper.loadBalance(swapResult.success().sourceOutBalanceID, accountID);

        REQUIRE(sourceFromBalanceBeforeSwap->getAmount() - swapResult.success().swapInAmount ==
                sourceFromBalanceAfterSwap->getAmount());
        REQUIRE(sourceToBalanceBeforeSwap->getAmount() + swapResult.success().swapOutAmount ==
                sourceToBalanceAfterSwap->getAmount());
    }

    SECTION("Swap exact B to A")
    {
        auto sourceFromBalanceBeforeSwap = balanceHelper.loadBalance(secondBalance);
        auto sourceToBalanceBeforeSwap = balanceHelper.loadBalance(firstBalance);

        uint64_t amountIn = 3 * ONE, amountOutMin = 1 * ONE;
        auto swapResult = lpSwapTestHelper.applyLPSwapTx(account, LPSwapType::EXACT_OUT_TOKENS_FOR_IN_TOKENS, secondBalance,
            firstBalance, amountIn, amountOutMin, LPSwapResultCode::SUCCESS);

        auto lpTokenAsset = LiquidityPoolFrame::calculateLPTokenAssetCode(firstAsset, secondAsset);
        auto pool = liquidityPoolHelper.loadPool(lpTokenAsset);

        auto lpFirstBalance = balanceHelper.loadBalance(pool->getFirstAssetBalance());
        auto lpSecondBalance = balanceHelper.loadBalance(pool->getSecondAssetBalance());

        REQUIRE(pool->getFirstReserve() == lpFirstBalance->getAmount());
        REQUIRE(pool->getSecondReserve() == lpSecondBalance->getAmount());

        auto sourceFromBalanceAfterSwap = balanceHelper.loadBalance(swapResult.success().sourceInBalanceID, accountID);
        auto sourceToBalanceAfterSwap = balanceHelper.loadBalance(swapResult.success().sourceOutBalanceID, accountID);

        REQUIRE(sourceFromBalanceBeforeSwap->getAmount() - swapResult.success().swapInAmount ==
                sourceFromBalanceAfterSwap->getAmount());
        REQUIRE(sourceToBalanceBeforeSwap->getAmount() + swapResult.success().swapOutAmount ==
                sourceToBalanceAfterSwap->getAmount());
    }

    SECTION("Swap A to exact B")
    {
        auto sourceFromBalanceBeforeSwap = balanceHelper.loadBalance(firstBalance);
        auto sourceToBalanceBeforeSwap = balanceHelper.loadBalance(secondBalance);

        uint64_t amountInMax = 2 * ONE, amountOut = 2 * ONE;
        auto swapResult = lpSwapTestHelper.applyLPSwapTx(account, LPSwapType::EXACT_IN_TOKENS_FOR_OUT_TOKENS, firstBalance,
            secondBalance, amountInMax, amountOut, LPSwapResultCode::SUCCESS);

        auto lpTokenAsset = LiquidityPoolFrame::calculateLPTokenAssetCode(firstAsset, secondAsset);
        auto pool = liquidityPoolHelper.loadPool(lpTokenAsset);

        auto lpFirstBalance = balanceHelper.loadBalance(pool->getFirstAssetBalance());
        auto lpSecondBalance = balanceHelper.loadBalance(pool->getSecondAssetBalance());

        REQUIRE(pool->getFirstReserve() == lpFirstBalance->getAmount());
        REQUIRE(pool->getSecondReserve() == lpSecondBalance->getAmount());

        auto sourceFromBalanceAfterSwap = balanceHelper.loadBalance(swapResult.success().sourceInBalanceID, accountID);
        auto sourceToBalanceAfterSwap = balanceHelper.loadBalance(swapResult.success().sourceOutBalanceID, accountID);

        REQUIRE(sourceFromBalanceBeforeSwap->getAmount() - swapResult.success().swapInAmount ==
                sourceFromBalanceAfterSwap->getAmount());
        REQUIRE(sourceToBalanceBeforeSwap->getAmount() + swapResult.success().swapOutAmount ==
                sourceToBalanceAfterSwap->getAmount());
    }

    SECTION("Swap B to exact A")
    {
        auto sourceFromBalanceBeforeSwap = balanceHelper.loadBalance(secondBalance);
        auto sourceToBalanceBeforeSwap = balanceHelper.loadBalance(firstBalance);

        uint64_t amountInMax = 2.5 * ONE, amountOut = 1 * ONE;
        auto swapResult = lpSwapTestHelper.applyLPSwapTx(account, LPSwapType::EXACT_IN_TOKENS_FOR_OUT_TOKENS, secondBalance,
            firstBalance, amountInMax, amountOut, LPSwapResultCode::SUCCESS);

        auto lpTokenAsset = LiquidityPoolFrame::calculateLPTokenAssetCode(firstAsset, secondAsset);
        auto pool = liquidityPoolHelper.loadPool(lpTokenAsset);

        auto lpFirstBalance = balanceHelper.loadBalance(pool->getFirstAssetBalance());
        auto lpSecondBalance = balanceHelper.loadBalance(pool->getSecondAssetBalance());

        REQUIRE(pool->getFirstReserve() == lpFirstBalance->getAmount());
        REQUIRE(pool->getSecondReserve() == lpSecondBalance->getAmount());

        auto sourceFromBalanceAfterSwap = balanceHelper.loadBalance(swapResult.success().sourceInBalanceID, accountID);
        auto sourceToBalanceAfterSwap = balanceHelper.loadBalance(swapResult.success().sourceOutBalanceID, accountID);

        REQUIRE(sourceFromBalanceBeforeSwap->getAmount() - swapResult.success().swapInAmount ==
                sourceFromBalanceAfterSwap->getAmount());
        REQUIRE(sourceToBalanceBeforeSwap->getAmount() + swapResult.success().swapOutAmount ==
                sourceToBalanceAfterSwap->getAmount());
    }

    SECTION("Swap for same balances")
    {
        uint64_t amountIn = 1 * ONE, amountOutMin = 1.8 * ONE;

        auto swapResult = lpSwapTestHelper.applyLPSwapTx(account, LPSwapType::EXACT_OUT_TOKENS_FOR_IN_TOKENS, firstBalance,
            firstBalance, amountIn, amountOutMin, LPSwapResultCode::SAME_BALANCES);
    }

    SECTION("Swap with zero in")
    {
        uint64_t amountIn = 0 * ONE, amountOutMin = 1.8 * ONE;

        auto swapResult = lpSwapTestHelper.applyLPSwapTx(account, LPSwapType::EXACT_OUT_TOKENS_FOR_IN_TOKENS, firstBalance,
            secondBalance, amountIn, amountOutMin, LPSwapResultCode::EXCESSIVE_INPUT_AMOUNT);
    }

    SECTION("Swap with zero out")
    {
        uint64_t amountIn = 1 * ONE, amountOutMin = 0 * ONE;

        auto swapResult = lpSwapTestHelper.applyLPSwapTx(account, LPSwapType::EXACT_IN_TOKENS_FOR_OUT_TOKENS, firstBalance,
            secondBalance, amountIn, amountOutMin, LPSwapResultCode::SUCCESS);
    }

    SECTION("Swap exact A to B with excessive outMin")
    {
        uint64_t amountIn = 1 * ONE, amountOutMin = 2 * ONE;

        auto swapResult = lpSwapTestHelper.applyLPSwapTx(account, LPSwapType::EXACT_IN_TOKENS_FOR_OUT_TOKENS, firstBalance,
            secondBalance, amountIn, amountOutMin, LPSwapResultCode::INSUFFICIENT_OUTPUT_AMOUNT);
    }

    SECTION("Swap exact A to B with insufficient B reserve")
    {
        uint64_t amountIn = 10 * ONE, amountOutMin = 21 * ONE;

        auto swapResult = lpSwapTestHelper.applyLPSwapTx(account, LPSwapType::EXACT_IN_TOKENS_FOR_OUT_TOKENS, firstBalance,
            secondBalance, amountIn, amountOutMin, LPSwapResultCode::INSUFFICIENT_LIQUIDITY);
    }

    SECTION("Swap A to exact B with excessive outMin")
    {
        uint64_t amountInMax = 1 * ONE, amountOut = 2 * ONE;

        auto swapResult = lpSwapTestHelper.applyLPSwapTx(account, LPSwapType::EXACT_OUT_TOKENS_FOR_IN_TOKENS, firstBalance,
            secondBalance, amountInMax, amountOut, LPSwapResultCode::EXCESSIVE_INPUT_AMOUNT);
    }

    SECTION("Swap through non-existing pool")
    {
        firstAsset = "USD1", secondAsset = "BTC1";
        assetCreationRequest = manageAssetTestHelper.createAssetCreationRequest(firstAsset, root.key.getPublicKey(),
            "{}", maxNonDividedAmount, 0, nullptr, maxNonDividedAmount, testSet.trailingDigitsCount);
        manageAssetTestHelper.applyManageAssetTx(root, 0, assetCreationRequest);

        assetCreationRequest = manageAssetTestHelper.createAssetCreationRequest(secondAsset, root.key.getPublicKey(),
            "{}", maxNonDividedAmount, 0, nullptr, maxNonDividedAmount, testSet.trailingDigitsCount);
        manageAssetTestHelper.applyManageAssetTx(root, 0, assetCreationRequest);

        createFirstBalanceRes = manageBalanceTestHelper.applyManageBalanceTx(account, accountID, firstAsset);
        firstBalance = createFirstBalanceRes.success().balanceID;
        createSecondBalanceRes = manageBalanceTestHelper.applyManageBalanceTx(account, accountID, secondAsset);
        secondBalance = createSecondBalanceRes.success().balanceID;

        uint64_t amountInMax = 1 * ONE, amountOut = 2 * ONE;

        auto swapResult = lpSwapTestHelper.applyLPSwapTx(account, LPSwapType::EXACT_IN_TOKENS_FOR_OUT_TOKENS,
            firstBalance, secondBalance, amountInMax, amountOut, LPSwapResultCode::LIQUIDITY_POOL_NOT_FOUND);
    }
}
