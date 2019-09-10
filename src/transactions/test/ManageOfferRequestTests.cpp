#include <transactions/test/test_helper/CreateAccountTestHelper.h>
#include <transactions/test/test_helper/ManageAccountRuleTestHelper.h>
#include <transactions/test/test_helper/ManageAccountRoleTestHelper.h>
#include "overlay/LoopbackPeer.h"
#include "test/test.h"
#include "transactions/dex/OfferExchange.h"
#include "ledger/LedgerDeltaImpl.h"
#include "ledger/BalanceHelperLegacy.h"
#include "ledger/OfferHelper.h"
#include "ledger/AssetPairHelper.h"
#include "test_helper/ManageAssetTestHelper.h"
#include "test_helper/IssuanceRequestHelper.h"
#include "test_helper/ManageAssetPairTestHelper.h"
#include "test_helper/ManageOfferTestHelper.h"
#include "test_helper/ManageKeyValueTestHelper.h"
#include "test/test_marshaler.h"

using namespace stellar;
using namespace stellar::txtest;

// Try setting each option to make sure it works
// try setting all at once
// try setting high threshold ones without the correct sigs
// make sure it doesn't allow us to add signers when we don't have the
// minbalance
TEST_CASE("manage offer request", "[tx][manage_offer_request]")
{
    Config const& cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);
    VirtualClock clock;
    Application::pointer appPtr = Application::create(clock, cfg);
    Application& app = *appPtr;
    app.start();
    auto testManager = TestManager::make(app);
    TestManager::upgradeToCurrentLedgerVersion(app);
    auto& db = testManager->getDB();
    LedgerDeltaImpl delta(testManager->getLedgerManager().getCurrentLedgerHeader(),
                          testManager->getDB());

    // set up world
    SecretKey root = getRoot();
    Salt rootSeq = 1;
    auto rootAccount = Account{ root, rootSeq };

    // test helpers
    auto assetTestHelper = ManageAssetTestHelper(testManager);
    auto assetPairHelper = ManageAssetPairTestHelper(testManager);
    auto issuanceHelper = IssuanceRequestHelper(testManager);
    auto offerTestHelper = ManageOfferTestHelper(testManager);
    CreateAccountTestHelper createAccountTestHelper(testManager);
    ManageAccountRuleTestHelper manageAccountRuleTestHelper(testManager);
    ManageAccountRoleTestHelper manageAccountRoleTestHelper(testManager);
    ManageKeyValueTestHelper manageKeyValueHelper(testManager);
    CreateManageOfferRequestTestHelper manageOfferRequestTestHelper(testManager);

    manageKeyValueHelper.assetOpWithoutReview();

    AssetCode base = "BTC";
    uint64_t baseType = 1;
    assetTestHelper.createAsset(rootAccount, rootAccount.key, base, rootAccount, 
                                int32(AssetPolicy::BASE_ASSET), nullptr, 6, baseType);
    AssetCode quote = "USD";
    uint64_t quoteType = 2;
    assetTestHelper.createAsset(rootAccount, rootAccount.key, quote, rootAccount,
                                int32(AssetPolicy::BASE_ASSET), nullptr, 6, quoteType);

    assetPairHelper.applyManageAssetPairTx(rootAccount, base, quote, 1, 0, 0, 
                                           int32(AssetPairPolicy::TRADEABLE_SECONDARY_MARKET));


    // basic create account builder
    auto createAccountBuilder = CreateAccountTestBuilder()
            .setSource(rootAccount)
            .setRoleID(1);

    auto balanceHelper = BalanceHelperLegacy::Instance();
    auto offerHelper = OfferHelper::Instance();

    auto buyer = Account{ SecretKey::random() , 0};
    createAccountTestHelper.applyTx(createAccountBuilder
                                .setToPublicKey(buyer.key.getPublicKey())
                                .addBasicSigner());
    auto baseBuyerBalance = balanceHelper->loadBalance(buyer.key.getPublicKey(),
                                                        base, db, &delta);
    REQUIRE(baseBuyerBalance);
    auto quoteBuyerBalance = balanceHelper->
        loadBalance(buyer.key.getPublicKey(), quote, db, &delta);
    REQUIRE(quoteBuyerBalance);
    auto quoteAssetAmount = 1000 * ONE;
    issuanceHelper.authorizePreIssuedAmount(rootAccount, rootAccount.key, quote, quoteAssetAmount, rootAccount);
    issuanceHelper.applyCreateIssuanceRequest(rootAccount, quote, quoteAssetAmount, quoteBuyerBalance->getBalanceID(), 
                                              SecretKey::random().getStrKeyPublic());

    
}