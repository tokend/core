#include "ManageSaleTestHelper.h"
#include "CheckSaleStateTestHelper.h"
#include "ManageAssetTestHelper.h"
#include "StateBeforeTxHelper.h"
#include "TestManager.h"
#include "TxHelper.h"
#include "test/test_marshaler.h"
#include <ledger/AssetHelperLegacy.h>
#include <ledger/ReviewableRequestHelper.h>
#include <ledger/SaleHelper.h>
#include <lib/catch.hpp>
#include <transactions/dex/ManageSaleOpFrame.h>

class pointer;
namespace stellar
{
namespace txtest
{

txtest::ManageSaleTestHelper::ManageSaleTestHelper(
    TestManager::pointer testManager)
    : TxHelper(testManager)
{
}

ManageSaleOp::_data_t
ManageSaleTestHelper::createDataForAction(ManageSaleAction action,
        uint32_t *allTasks,
        uint64_t* requestID,
        std::string* newDetails)
{
    ManageSaleOp::_data_t data;

    switch (action)
    {
    case ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
    {
        if (!requestID || !newDetails)
        {
            throw std::runtime_error(
                "Request ID and new details string cannot be nullptr "
                "while creating update sale details request");
        }
        data.action(ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST);
        data.updateSaleDetailsData().requestID = *requestID;
        data.updateSaleDetailsData().newDetails = *newDetails;
        if (allTasks)
        {
            data.updateSaleDetailsData().allTasks.activate() = *allTasks;
        }
        break;
    }
    case ManageSaleAction::CANCEL:
    {
        data.action(ManageSaleAction::CANCEL);
        break;
    }
    default:
    {
        throw std::runtime_error("Unexpected ManageSaleAction type");
    }
    }

    return data;
}

TransactionFramePtr
ManageSaleTestHelper::createManageSaleTx(Account& source, uint64_t saleID,
                                         ManageSaleOp::_data_t data)
{
    Operation op;
    op.body.type(OperationType::MANAGE_SALE);
    ManageSaleOp& manageSaleOp = op.body.manageSaleOp();
    manageSaleOp.saleID = saleID;
    manageSaleOp.data = data;
    return txFromOperation(source, op, nullptr);
}


ManageSaleResult
ManageSaleTestHelper::applyManageSaleTx(Account& source, uint64_t saleID,
                                        ManageSaleOp::_data_t data,
                                        ManageSaleResultCode expectedResultCode)
{
    auto& db = mTestManager->getDB();
    auto reviewableRequestHelper = ReviewableRequestHelper::Instance();
    auto saleHelper = SaleHelper::Instance();

    auto saleBeforeOp = saleHelper->loadSale(saleID, db);

    ReviewableRequestFrame::pointer requestBeforeTx;

    switch (data.action())
    {
    case ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
    {
        requestBeforeTx = reviewableRequestHelper->loadRequest(
            data.updateSaleDetailsData().requestID, db);
        break;
    }
    default:
        break;
    }

    std::vector<LedgerDelta::KeyEntryMap> stateBeforeOp;
    TransactionFramePtr txFrame;
    txFrame = createManageSaleTx(source, saleID, data);
    mTestManager->applyCheck(txFrame, stateBeforeOp);

    auto txResult = txFrame->getResult();
    auto actualResultCode =
        ManageSaleOpFrame::getInnerCode(txResult.result.results()[0]);

    REQUIRE(actualResultCode == expectedResultCode);

    auto txFee = mTestManager->getApp().getLedgerManager().getTxFee();
    REQUIRE(txResult.feeCharged == txFee);

    ManageSaleResult manageSaleResult =
        txResult.result.results()[0].tr().manageSaleResult();

    if (actualResultCode != ManageSaleResultCode::SUCCESS)
        return manageSaleResult;

    auto saleAfterOp = saleHelper->loadSale(saleID, db);

    switch (data.action())
    {
    case ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
    {
        if (!manageSaleResult.success().fulfilled)
        {
            auto requestAfterTx = reviewableRequestHelper->loadRequest(
                    manageSaleResult.success().response.requestID(), db);
            REQUIRE(!!requestAfterTx);

            auto requestAfterTxEntry = requestAfterTx->getRequestEntry();

            REQUIRE(requestAfterTxEntry.body.updateSaleDetailsRequest().saleID ==
                    saleID);
            REQUIRE(
                    requestAfterTxEntry.body.updateSaleDetailsRequest().newDetails ==
                    data.updateSaleDetailsData().newDetails);

            if (!!requestBeforeTx)
            {
                auto requestBeforeTxEntry = requestBeforeTx->getRequestEntry();

                REQUIRE(
                        requestBeforeTxEntry.body.updateSaleDetailsRequest().saleID ==
                        requestAfterTxEntry.body.updateSaleDetailsRequest().saleID);

                REQUIRE(
                        requestBeforeTxEntry.body.updateSaleDetailsRequest()
                                .newDetails !=
                        requestAfterTxEntry.body.updateSaleDetailsRequest().newDetails);
            }
        }

        break;
    }
    case ManageSaleAction::CANCEL:
    {
        REQUIRE(!saleAfterOp);
        REQUIRE(stateBeforeOp.size() == 1);
        StateBeforeTxHelper stateBeforeTxHelper(stateBeforeOp[0]);
        CheckSaleStateHelper(mTestManager)
            .ensureCancel(saleID, stateBeforeTxHelper);
        break;
    }
    }

    return manageSaleResult;
}
}
}