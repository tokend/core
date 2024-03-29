#include "transactions/test/test_helper/CreateAccountTestHelper.h"
#include "transactions/test/test_helper/ManageAssetPairTestHelper.h"
#include "ledger/FeeHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "test/test.h"
#include "crypto/SHA.h"
#include "test_helper/ManageAssetTestHelper.h"
#include "test_helper/IssuanceRequestHelper.h"
#include "test_helper/ManageKeyValueTestHelper.h"
#include "ledger/StorageHelper.h"
#include "ledger/BalanceHelper.h"
#include "test_helper/WithdrawRequestHelper.h"
#include "test_helper/ReviewWithdrawalRequestHelper.h"
#include "test/test_marshaler.h"

using namespace stellar;
using namespace stellar::txtest;

typedef std::unique_ptr<Application> appPtr;

TEST_CASE("KV limits", "[tx][withdraw][limits][manage_key_value]")
{
    Config const& cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);
    VirtualClock clock;
    Application::pointer appPtr = Application::create(clock, cfg);
    Application& app = *appPtr;
    app.start();
    auto testManager = TestManager::make(app);
    TestManager::upgradeToCurrentLedgerVersion(app);

    //Helpers
    auto& storageHelper = testManager->getStorageHelper();
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto& accountHelper = storageHelper.getAccountHelper();

    auto root = Account{getRoot(), Salt(0)};
    auto issuanceHelper = IssuanceRequestHelper(testManager);
    auto manageAssetTestHelper = ManageAssetTestHelper(testManager);
    auto assetPairHelper = ManageAssetPairTestHelper(testManager);
    auto reviewWithdrawHelper = ReviewWithdrawRequestHelper(testManager);
    auto withdrawRequestHelper = WithdrawRequestHelper(testManager);
    auto createAccountTestHelper = CreateAccountTestHelper(testManager);
    auto manageKVHelper = ManageKeyValueTestHelper(testManager);

    manageKVHelper.assetOpWithoutReview();

    longstring key = ManageKeyValueOpFrame::makeWithdrawalTasksKey("*");
    manageKVHelper.setKey(key)->setUi32Value(1);
    manageKVHelper.doApply(app, ManageKVAction::PUT, true);

    // create asset and make it withdrawable
    const AssetCode asset = "USD";
    const uint64_t preIssuedAmount = 10000 * ONE;
    issuanceHelper.createAssetWithPreIssuedAmount(root, asset, preIssuedAmount, root);
    manageAssetTestHelper.updateAsset(root, asset, root,
                                      static_cast<uint32_t>(AssetPolicy::BASE_ASSET)
                                      | static_cast<uint32_t>(AssetPolicy::WITHDRAWABLE));

    //Tasks
    uint32_t allTasks = 0;

    //create stats asset and stats asset pair
    const AssetCode statsAsset = "UAH";
    manageAssetTestHelper.createAsset(root, root.key, statsAsset, root, static_cast<uint32_t>(AssetPolicy::STATS_QUOTE_ASSET));
    const uint64_t statsPricePerUnit = 25;
    const uint64_t statsPrice = 25 * ONE;
    assetPairHelper.createAssetPair(root, asset, statsAsset, statsPrice);

    // create account which will withdraw
    auto withdrawerKP = SecretKey::random();
    createAccountTestHelper.applyCreateAccountTx(root, withdrawerKP.getPublicKey(), 1);
    auto withdrawer = Account{withdrawerKP, Salt(0)};
    auto withdrawerBalance = balanceHelper.
        loadBalance(withdrawerKP.getPublicKey(), asset);
    REQUIRE(withdrawerBalance);
    issuanceHelper.applyCreateIssuanceRequest(root, asset, preIssuedAmount, withdrawerBalance->getBalanceID(),
                                              "RANDOM ISSUANCE REFERENCE", &allTasks);

    SECTION("Happy path")
    {
        // create asset to withdraw to
        const AssetCode withdrawDestAsset = "BTC";
        manageAssetTestHelper.createAsset(root, root.key, withdrawDestAsset, root, 0);
        const uint64_t price = 2000 * ONE;
        assetPairHelper.createAssetPair(root, withdrawDestAsset, asset, price);

        //create withdraw request
        uint64_t amountToWithdraw = 100 * ONE;
        withdrawerBalance = balanceHelper.loadBalance(withdrawerKP.getPublicKey(), asset);
        REQUIRE(withdrawerBalance->getAmount() >= amountToWithdraw);
        const uint64_t expectedAmountInDestAsset = 0.05 * ONE;

        Fee zeroFee;
        zeroFee.fixed = 0;
        zeroFee.percent = 0;
        auto withdrawRequest = withdrawRequestHelper.createWithdrawRequest(withdrawerBalance->getBalanceID(), amountToWithdraw,
                                                                           zeroFee, "{}");

        auto key = ManageKeyValueOpFrame::makeWithdrawLowerBoundKey("USD");

        SECTION("Approve")
        {
            uint64 lowerLimits = ONE;
            manageKVHelper.setKey(key);
            manageKVHelper.setUi64Value(lowerLimits);
            manageKVHelper.doApply(app, ManageKVAction::PUT, true);
            withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawRequest,
                                                             nullptr);
        }
        SECTION("Reject")
        {
            uint64 lowerLimits = 1000 * ONE;
            manageKVHelper.setKey(key);
            manageKVHelper.setUi64Value(lowerLimits);
            manageKVHelper.doApply(app, ManageKVAction::PUT, true);
            withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawRequest,
                                                             nullptr,
                                                             CreateWithdrawalRequestResultCode::LOWER_BOUND_NOT_EXCEEDED);
        }

        SECTION("KV limits not set")
        {
            withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawRequest, nullptr);
        }
    }

}
