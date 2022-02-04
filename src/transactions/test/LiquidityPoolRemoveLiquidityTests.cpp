#include <test/test.h>
#include "TxTests.h"
#include <ledger/StorageHelper.h>
#include <ledger/BalanceHelper.h>
#include <ledger/LiquidityPoolHelper.h>
#include <ledger/LedgerManager.h>
#include <ledger/AccountHelper.h>
#include <transactions/test/test_helper/LPAddLiquidityTestHelper.h>
#include <transactions/test/test_helper/LPRemoveLiquidityTestHelper.h>
#include <transactions/test/test_helper/CreateAccountTestHelper.h>
#include <transactions/test/test_helper/ManageAccountRuleTestHelper.h>
#include <transactions/test/test_helper/IssuanceRequestHelper.h>
#include <transactions/test/test_helper/ManageAssetTestHelper.h>
#include <transactions/test/test_helper/ManageKeyValueTestHelper.h>
#include <transactions/test/test_helper/ManageAccountRoleTestHelper.h>
#include <transactions/test/test_helper/ManageBalanceTestHelper.h>
#include <transactions/test/test_helper/PaymentTestHelper.h>
#include <transactions/test/test_helper/SetFeesTestHelper.h>
#include <transactions/liquidity_pool/LiquidityPoolRemoveLiquidityOpFrame.h>

using namespace stellar;
using namespace stellar::txtest;

typedef std::unique_ptr<Application> appPtr;

TEST_CASE("Remove liquidity", "[tx][liquidity_pool][remove_liquidity]")
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
    auto removeLiquidityTestHelper = LPRemoveLiquidityTestHelper(testManager);
    auto liquidityPoolTestHelper = LPAddLiquidityTestHelper(testManager);
    auto createAccountTestHelper = CreateAccountTestHelper(testManager);
    auto manageAccountRuleTestHelper = ManageAccountRuleTestHelper(testManager);
    auto issuanceTestHelper = IssuanceRequestHelper(testManager);
    auto manageKeyValueHelper = ManageKeyValueTestHelper(testManager);
    auto manageAssetTestHelper = ManageAssetTestHelper(testManager);
    auto manageAccountRoleTestHelper = ManageAccountRoleTestHelper(testManager);
    auto manageBalanceTestHelper = ManageBalanceTestHelper(testManager);
    auto paymentTestHelper = PaymentTestHelper(testManager);
    auto setFeesTestHelper = SetFeesTestHelper(testManager);
    auto& storageHelper = testManager->getStorageHelper();
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto& accountHelper = storageHelper.getAccountHelper();
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

    uint64_t issueAmount = 1000 * ONE;

    uint32_t issuanceTasks = 0;
    issuanceTestHelper.applyCreateIssuanceRequest(root, firstAsset, issueAmount, firstBalance,
        "Some reference1", &issuanceTasks);
    issuanceTestHelper.applyCreateIssuanceRequest(root, secondAsset, issueAmount, secondBalance,
        "Some reference2", &issuanceTasks);

    auto createLPResult = liquidityPoolTestHelper.applyAddLiquidityTx(account, firstBalance, secondBalance,
        firstDesiredAmount, secondDesiredAmount, firstMinAmount, secondMinAmount, LPAddLiquidityResultCode::SUCCESS);

    auto sourceLPBalanceFrame = balanceHelper.loadBalance(accountID, createLPResult.success().lpAsset);
    auto sourceLPBalanceID = sourceLPBalanceFrame->getBalanceID();

    SECTION("Remove liquidity")
    {
        uint64_t removeLPTokensAmount = createLPResult.success().lpTokensAmount;

        auto lpBefore = liquidityPoolHelper.loadPool(createLPResult.success().lpAsset);

        auto lpFirstBalanceBefore = balanceHelper.loadBalance(lpBefore->getFirstAssetBalance());
        auto lpSecondBalanceBefore = balanceHelper.loadBalance(lpBefore->getSecondAssetBalance());

        auto sourceLpBalanceBefore = balanceHelper.loadBalance(accountID, createLPResult.success().lpAsset);

        auto removeRes = removeLiquidityTestHelper.applyRemoveLiquidityTx(account, sourceLPBalanceID,
            removeLPTokensAmount, 0, 0, LPRemoveLiquidityResultCode::SUCCESS);

        auto lpAfter = liquidityPoolHelper.loadPool(createLPResult.success().lpAsset);

        REQUIRE(createLPResult.success().lpTokensAmount - removeLPTokensAmount == lpAfter->getLPTokensAmount());

        auto lpFirstBalanceAfter = balanceHelper.loadBalance(lpBefore->getFirstAssetBalance());
        auto lpSecondBalanceAfter = balanceHelper.loadBalance(lpBefore->getSecondAssetBalance());

        auto sourceLpBalanceAfter = balanceHelper.loadBalance(accountID, createLPResult.success().lpAsset);

        uint64_t lpBalanceDelta = sourceLpBalanceBefore->getAmount() - sourceLpBalanceAfter->getAmount();
        REQUIRE(lpBalanceDelta == removeLPTokensAmount);

        REQUIRE(lpFirstBalanceAfter->getAmount() ==
                lpFirstBalanceBefore->getAmount() - removeRes.success().firstAssetAmount);
        REQUIRE(lpSecondBalanceAfter->getAmount() ==
                lpSecondBalanceBefore->getAmount() - removeRes.success().secondAssetAmount);
    }

    SECTION("Non-existing liquidity pool")
    {
        uint64_t removeLPTokensAmount = createLPResult.success().lpTokensAmount;

        auto removeRes = removeLiquidityTestHelper.applyRemoveLiquidityTx(account, firstBalance,
            removeLPTokensAmount, 0, 0, LPRemoveLiquidityResultCode::LP_NOT_FOUND);
    }

    SECTION("Non-existing LP balance")
    {
        uint64_t removeLPTokensAmount = createLPResult.success().lpTokensAmount;

        auto fakeBalance = BalanceKeyUtils::forAccount(accountID, UINT64_MAX);
        auto removeRes = removeLiquidityTestHelper.applyRemoveLiquidityTx(account,
            fakeBalance, removeLPTokensAmount, 0, 0, LPRemoveLiquidityResultCode::LP_TOKEN_BALANCE_NOT_FOUND);
    }

    SECTION("Insufficient first min amount")
    {
        uint64_t removeLPTokensAmount = createLPResult.success().lpTokensAmount;

        auto removeRes = removeLiquidityTestHelper.applyRemoveLiquidityTx(account, sourceLPBalanceID,
            removeLPTokensAmount, UINT64_MAX, 0, LPRemoveLiquidityResultCode::INSUFFICIENT_FIRST_AMOUNT);
    }

    SECTION("Insufficient second min amount")
    {
        uint64_t removeLPTokensAmount = createLPResult.success().lpTokensAmount;

        auto removeRes = removeLiquidityTestHelper.applyRemoveLiquidityTx(account, sourceLPBalanceID,
            removeLPTokensAmount, 0, UINT64_MAX, LPRemoveLiquidityResultCode::INSUFFICIENT_SECOND_AMOUNT);
    }

    SECTION("LP tokens amount underfunded")
    {
        uint64_t removeLPTokensAmount = UINT64_MAX;

        auto removeRes = removeLiquidityTestHelper.applyRemoveLiquidityTx(account, sourceLPBalanceID,
            removeLPTokensAmount, 0, 0, LPRemoveLiquidityResultCode::UNDERFUNDED);
    }

    SECTION("Remove zero LP tokens")
    {
        uint64_t removeLPTokensAmount = 0;

        auto removeRes = removeLiquidityTestHelper.applyRemoveLiquidityTx(account, sourceLPBalanceID,
            removeLPTokensAmount, 0, 0, LPRemoveLiquidityResultCode::INVALID_LP_TOKENS_AMOUNT);
    }

    SECTION("Remove liquidity from transferred LP tokens")
    {
        auto lpBefore = liquidityPoolHelper.loadPool(createLPResult.success().lpAsset);

        auto lpFirstBalanceBefore = balanceHelper.loadBalance(lpBefore->getFirstAssetBalance());
        auto lpSecondBalanceBefore = balanceHelper.loadBalance(lpBefore->getSecondAssetBalance());

        auto lpReceiver = Account{ SecretKey::random(), Salt(1) };
        AccountID lpReceiverID = lpReceiver.key.getPublicKey();
        createAccountTestHelper.applyCreateAccountTx(root, lpReceiverID, 1);

        auto createLPTokensBalanceRes = manageBalanceTestHelper.applyManageBalanceTx(lpReceiver, lpReceiverID,
            sourceLPBalanceFrame->getAsset());
        BalanceID receiverBalanceID = createLPTokensBalanceRes.success().balanceID;

        auto senderLPTokensBalance = balanceHelper.loadBalance(accountID, sourceLPBalanceFrame->getAsset());

        uint64_t lpTokensAmountToSend = 10 * ONE;

        auto destination = paymentTestHelper.createDestinationForAccount(lpReceiver.key.getPublicKey());

        auto incomingFee = setFeesTestHelper.createFeeEntry(FeeType::PAYMENT_FEE, sourceLPBalanceFrame->getAsset(), 0, 0);
        setFeesTestHelper.applySetFeesTx(root, &incomingFee, false);
        auto outgoingFee = setFeesTestHelper.createFeeEntry(FeeType::PAYMENT_FEE, sourceLPBalanceFrame->getAsset(), 0, 0);
        setFeesTestHelper.applySetFeesTx(root , &outgoingFee, false);

        auto sourceFeeData = paymentTestHelper.createFeeData(outgoingFee.fixedFee, outgoingFee.percentFee);
        auto destFeeData = paymentTestHelper.createFeeData(incomingFee.fixedFee, incomingFee.percentFee);
        auto paymentFeeData = paymentTestHelper.createPaymentFeeData(sourceFeeData, destFeeData, false);

        paymentTestHelper.applyPaymentTx(account, senderLPTokensBalance->getBalanceID(), destination,
            lpTokensAmountToSend, paymentFeeData, "", "", nullptr, PaymentResultCode::SUCCESS);

        auto removeRes = removeLiquidityTestHelper.applyRemoveLiquidityTx(lpReceiver, receiverBalanceID,
            lpTokensAmountToSend, 0, 0, LPRemoveLiquidityResultCode::SUCCESS);

        auto lpAfter = liquidityPoolHelper.loadPool(createLPResult.success().lpAsset);

        REQUIRE(createLPResult.success().lpTokensAmount - lpTokensAmountToSend == lpAfter->getLPTokensAmount());

        auto lpFirstBalanceAfter = balanceHelper.loadBalance(lpBefore->getFirstAssetBalance());
        auto lpSecondBalanceAfter = balanceHelper.loadBalance(lpBefore->getSecondAssetBalance());

        REQUIRE(lpFirstBalanceAfter->getAmount() ==
                lpFirstBalanceBefore->getAmount() - removeRes.success().firstAssetAmount);
        REQUIRE(lpSecondBalanceAfter->getAmount() ==
                lpSecondBalanceBefore->getAmount() - removeRes.success().secondAssetAmount);

        SECTION("Remove left liquidity")
        {
            lpBefore = liquidityPoolHelper.loadPool(createLPResult.success().lpAsset);

            lpFirstBalanceBefore = balanceHelper.loadBalance(lpBefore->getFirstAssetBalance());
            lpSecondBalanceBefore = balanceHelper.loadBalance(lpBefore->getSecondAssetBalance());

            auto removeLPTokensAmount = createLPResult.success().lpTokensAmount - lpTokensAmountToSend;

            removeRes = removeLiquidityTestHelper.applyRemoveLiquidityTx(account, sourceLPBalanceID,
                removeLPTokensAmount, 0, 0, LPRemoveLiquidityResultCode::SUCCESS);

            auto expectedAmountLeft = createLPResult.success().lpTokensAmount - lpTokensAmountToSend - removeLPTokensAmount;

            lpAfter = liquidityPoolHelper.loadPool(createLPResult.success().lpAsset);

            REQUIRE(expectedAmountLeft == lpAfter->getLPTokensAmount());

            lpFirstBalanceAfter = balanceHelper.loadBalance(lpBefore->getFirstAssetBalance());
            lpSecondBalanceAfter = balanceHelper.loadBalance(lpBefore->getSecondAssetBalance());

            REQUIRE(lpFirstBalanceAfter->getAmount() ==
                    lpFirstBalanceBefore->getAmount() - removeRes.success().firstAssetAmount);
            REQUIRE(lpSecondBalanceAfter->getAmount() ==
                    lpSecondBalanceBefore->getAmount() - removeRes.success().secondAssetAmount);
        }
    }
}