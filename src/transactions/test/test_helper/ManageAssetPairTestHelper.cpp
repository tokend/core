#include "ManageAssetPairTestHelper.h"
#include "test/test_marshaler.h"
#include "ledger/StorageHelperImpl.h"
namespace stellar
{

namespace txtest
{

    ManageAssetPairTestHelper::ManageAssetPairTestHelper(TestManager::pointer testManager) : TxHelper(testManager)
    {
    }

    TransactionFramePtr ManageAssetPairTestHelper::createManageAssetPairTx(Account& source, AssetCode base, AssetCode quote,
                                                       int64_t physicalPrice,
                                                       int64_t physicalPriceCorrection, int64_t maxPriceStep,
                                                       int32_t policies,
                                                       ManageAssetPairAction action, Account* signer)
    {
        Operation op;
        op.body.type(OperationType::MANAGE_ASSET_PAIR);
        auto& manageAssetPair = op.body.manageAssetPairOp();
        manageAssetPair.action = action;
        manageAssetPair.base = base;
        manageAssetPair.quote = quote;
        manageAssetPair.maxPriceStep = maxPriceStep;
        manageAssetPair.physicalPrice = physicalPrice;
        manageAssetPair.physicalPriceCorrection = physicalPriceCorrection;
        manageAssetPair.policies = policies;

        return TxHelper::txFromOperation(source, op, signer);
    }

    ManageAssetPairResultCode ManageAssetPairTestHelper::applyManageAssetPairTx(Account &source, AssetCode base, AssetCode quote,
                                                      int64_t physicalPrice, int64_t physicalPriceCorrection,
                                                      int64_t maxPriceStep, int32_t policies,
                                                      ManageAssetPairAction action, Account *signer,
                                                      ManageAssetPairResultCode expectedResult)
    {
        auto& assetPairHelper = mTestManager->getStorageHelper().getAssetPairHelper();
        auto assetPairFrameBefore = assetPairHelper.loadAssetPair(base, quote);
        auto countBefore = assetPairHelper.countObjects();

        TransactionFramePtr txFrame;
        txFrame = createManageAssetPairTx(source, base, quote, physicalPrice, physicalPriceCorrection, maxPriceStep,
                                          policies, action, signer);

        mTestManager->applyCheck(txFrame);
        auto txResult = txFrame->getResult();
        auto opResult = txResult.result.results()[0];
        auto actualResultCode = ManageAssetPairOpFrame::getInnerCode(opResult);

        REQUIRE(expectedResult == actualResultCode);

        auto countAfter = assetPairHelper.countObjects();
        auto assetPairFrameAfter = assetPairHelper.loadAssetPair(base, quote);

        if (actualResultCode != ManageAssetPairResultCode::SUCCESS)
        {
            REQUIRE(countBefore == countAfter);
            if (assetPairFrameBefore)
                REQUIRE(assetPairFrameBefore->getAssetPair() == assetPairFrameAfter->getAssetPair());
            return actualResultCode;
        }

        if (action == ManageAssetPairAction::CREATE)
            REQUIRE(countAfter == countBefore + 1);

        REQUIRE(assetPairFrameAfter);

        auto assetPairAfter = assetPairFrameAfter->getAssetPair();
        auto manageAssetPairResult = opResult.tr().manageAssetPairResult();
        REQUIRE(manageAssetPairResult.success().currentPrice == assetPairAfter.currentPrice);

        auto manageAssetPairOp = txFrame->getOperations()[0]->getOperation().body.manageAssetPairOp();
        AssetPairEntry expectedAssetPair = calculateExpectedAssetPair(manageAssetPairOp, assetPairFrameBefore, action);

        REQUIRE(expectedAssetPair == assetPairAfter);

        return actualResultCode;
    }

    AssetPairEntry ManageAssetPairTestHelper::calculateExpectedAssetPair(const ManageAssetPairOp &op,
                                                                         AssetPairFrame::pointer assetPairFrameBefore,
                                                                         ManageAssetPairAction action)
    {
        AssetPairEntry expectedAssetPair;
        switch (action)
        {
            case ManageAssetPairAction::CREATE:
                expectedAssetPair.base = op.base;
                expectedAssetPair.quote = op.quote;
                expectedAssetPair.currentPrice = op.physicalPrice;
                expectedAssetPair.maxPriceStep = op.maxPriceStep;
                expectedAssetPair.physicalPrice = op.physicalPrice;
                expectedAssetPair.physicalPriceCorrection = op.physicalPriceCorrection;
                expectedAssetPair.policies = op.policies;
                break;
            case ManageAssetPairAction::UPDATE_PRICE:
            {
                REQUIRE(assetPairFrameBefore);
                int64_t premium = assetPairFrameBefore->getCurrentPrice() - assetPairFrameBefore->getAssetPair().physicalPrice;
                expectedAssetPair = assetPairFrameBefore->getAssetPair();
                expectedAssetPair.physicalPrice = op.physicalPrice;
                expectedAssetPair.currentPrice = op.physicalPrice + premium;
                break;
            }
            case ManageAssetPairAction::UPDATE_POLICIES:
                REQUIRE(assetPairFrameBefore);
                expectedAssetPair = assetPairFrameBefore->getAssetPair();
                expectedAssetPair.policies = op.policies;
                expectedAssetPair.physicalPriceCorrection = op.physicalPriceCorrection;
                expectedAssetPair.maxPriceStep = op.maxPriceStep;
                break;
            default:
                throw new std::runtime_error("Unexpected manage asset pair action");
        }
        return expectedAssetPair;
    }

    void ManageAssetPairTestHelper::createAssetPair(Account &source, AssetCode base, AssetCode quote, int64_t physicalPrice,
                                                   int64_t physicalPriceCorrection, int64_t maxPriceStep, int32_t policies)
    {
        applyManageAssetPairTx(source, base, quote, physicalPrice, physicalPriceCorrection, maxPriceStep, policies);
    }

    TransactionFramePtr ManageAssetPairTestHelper::createRemoveAssetPairTx(txtest::Account &source, AssetCode base,
                                                                           AssetCode quote, txtest::Account *signer)
    {
        Operation op;
        op.body.type(OperationType::REMOVE_ASSET_PAIR);
        auto& body = op.body.removeAssetPairOp();
        body.base = base;
        body.quote = quote;

        return TxHelper::txFromOperation(source, op, signer);
    }

    RemoveAssetPairResult ManageAssetPairTestHelper::applyRemoveAssetPairTx(txtest::Account &source, AssetCode base,
                                                                            AssetCode quote, txtest::Account *signer,
                                                                            RemoveAssetPairResultCode expectedResult,
                                                                            OperationResultCode expectedOpResult)
    {
        auto& assetPairHelper = mTestManager->getStorageHelper().getAssetPairHelper();
        auto countBefore = assetPairHelper.countObjects();

        TransactionFramePtr txFrame;
        txFrame = createRemoveAssetPairTx(source, base, quote, signer);

        mTestManager->applyCheck(txFrame);
        auto txResult = txFrame->getResult();
        auto opResult = txResult.result.results()[0];
        REQUIRE(opResult.code() == expectedOpResult);
        if (opResult.code() != OperationResultCode::opINNER)
        {
            return RemoveAssetPairResult();
        }

        auto actualResultCode = RemoveAssetPairOpFrame::getInnerCode(opResult);

        REQUIRE(expectedResult == actualResultCode);

        auto countAfter = assetPairHelper.countObjects();
        auto assetPairFrameAfter = assetPairHelper.loadAssetPair(base, quote);

        if (actualResultCode != RemoveAssetPairResultCode::SUCCESS)
        {
            REQUIRE(countBefore == countAfter);
        }
        else
        {
            REQUIRE(countBefore == countAfter + 1);
        }

        return opResult.tr().removeAssetPairResult();
    }

    void ManageAssetPairTestHelper::removeAssetPair(txtest::Account &source, AssetCode base, AssetCode quote)
    {
        applyRemoveAssetPairTx(source, base, quote);
    }

}

}
