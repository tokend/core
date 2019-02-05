#include <ledger/ReviewableRequestFrame.h>
#include "transactions/ManageInvoiceRequestOpFrame.h"
#include "database/Database.h"
#include "main/Application.h"
#include <ledger/ReviewableRequestHelper.h>
#include <ledger/ContractHelper.h>
#include "ledger/KeyValueHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/StorageHelper.h"
#include "review_request/ReviewRequestHelper.h"
#include "ledger/BalanceHelperLegacy.h"
#include "ManageKeyValueOpFrame.h"

namespace stellar
{
using xdr::operator==;


ManageInvoiceRequestOpFrame::ManageInvoiceRequestOpFrame(Operation const& op, OperationResult& res,
                                     TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx)
    , mManageInvoiceRequest(mOperation.body.manageInvoiceRequestOp())
{
}

bool
ManageInvoiceRequestOpFrame::doApply(Application& app, StorageHelper &storageHelper, LedgerManager& ledgerManager)
{
    auto& db = storageHelper.getDatabase();
    auto delta = storageHelper.getLedgerDelta();

	innerResult().code(ManageInvoiceRequestResultCode::SUCCESS);

	if (mManageInvoiceRequest.details.action() == ManageInvoiceRequestAction::CREATE)
	{
	    return createManageInvoiceRequest(app, storageHelper, ledgerManager);
	}

    auto reviewableRequestHelper = ReviewableRequestHelper::Instance();
    auto reviewableRequest = reviewableRequestHelper->loadRequest(mManageInvoiceRequest.details.requestID(), db);
	if (!reviewableRequest || reviewableRequest->getRequestType() != ReviewableRequestType::CREATE_INVOICE)
	{
	    innerResult().code(ManageInvoiceRequestResultCode::NOT_FOUND);
	    return false;
	}

	if (!(reviewableRequest->getRequestor() == getSourceID()))
	{
        innerResult().code(ManageInvoiceRequestResultCode::NOT_ALLOWED_TO_REMOVE);
        return false;
	}

	auto invoiceRequest = reviewableRequest->getRequestEntry().body.invoiceRequest();

	if (invoiceRequest.isApproved)
	{
	    innerResult().code(ManageInvoiceRequestResultCode::INVOICE_IS_APPROVED);
	    return false;
	}

	if (!!invoiceRequest.contractID)
	{
	    auto contractHelper = ContractHelper::Instance();
	    auto contractFrame = contractHelper->loadContract(*invoiceRequest.contractID, db, delta);

	    if (!contractFrame)
	    {
	        innerResult().code(ManageInvoiceRequestResultCode::CONTRACT_NOT_FOUND);
            return false;
	    }

	    auto requestID = reviewableRequest->getRequestID();
	    auto& invoices = contractFrame->getInvoiceRequestIDs();

        auto invoicePos = std::find(invoices.begin(), invoices.end(), requestID);
	    if (invoicePos == invoices.end())
	    {
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected contract state. "
                                                   << "Expected invoice to be attached to contract. "
                                                   << "contractID: " + std::to_string(*invoiceRequest.contractID)
                                                   << "invoice requestID: " +
                                                      std::to_string(requestID);
            throw std::runtime_error("Unexpected contract state. Expected invoice to be attached to contract.");
	    }

	    invoices.erase(invoicePos);
	    contractHelper->storeChange(*delta, db, contractFrame->mEntry);
	}

	reviewableRequestHelper->storeDelete(*delta, db, reviewableRequest->getKey());

	innerResult().success().details.action(ManageInvoiceRequestAction::REMOVE);

	return true;
}

bool
ManageInvoiceRequestOpFrame::createManageInvoiceRequest(Application& app, StorageHelper &storageHelper,
                                                        LedgerManager& ledgerManager)
{
    auto& db = storageHelper.getDatabase();
    auto delta = storageHelper.getLedgerDelta();
    auto& invoiceCreationRequest = mManageInvoiceRequest.details.invoiceRequest();

    auto senderBalance = storageHelper.getBalanceHelper().loadBalance(invoiceCreationRequest.sender,
                                                                invoiceCreationRequest.asset);
    if (!senderBalance)
    {
        innerResult().code(ManageInvoiceRequestResultCode::BALANCE_NOT_FOUND);
        return false;
    }

    auto& keyValueHelper = storageHelper.getKeyValueHelper();
    if (!checkMaxInvoicesForReceiverAccount(app, db, keyValueHelper))
        return false;

    if (!checkMaxInvoiceDetailsLength(app, keyValueHelper))
        return false;

    auto receiverBalanceID = AccountManager::loadOrCreateBalanceForAsset(getSourceID(),
                                                                         invoiceCreationRequest.asset, db, *delta);
    InvoiceRequest invoiceRequest;
    invoiceRequest.asset = invoiceCreationRequest.asset;
    invoiceRequest.amount = invoiceCreationRequest.amount;
    invoiceRequest.creatorDetails = invoiceCreationRequest.details;
    invoiceRequest.isApproved = false;
    invoiceRequest.contractID = invoiceCreationRequest.contractID;
    invoiceRequest.senderBalance = senderBalance->getBalanceID();
    invoiceRequest.receiverBalance = receiverBalanceID;
    invoiceRequest.ext.v(LedgerVersion::EMPTY_VERSION);

    ReviewableRequestEntry::_body_t body;
    body.type(ReviewableRequestType::CREATE_INVOICE);
    body.invoiceRequest() = invoiceRequest;

    auto request = ReviewableRequestFrame::createNewWithHash(*delta, getSourceID(), invoiceCreationRequest.sender,
                                                             nullptr, body, ledgerManager.getCloseTime());

    EntryHelperProvider::storeAddEntry(*delta, db, request->mEntry);

    if (invoiceCreationRequest.contractID)
    {
        auto contractHelper = ContractHelper::Instance();
        auto contractFrame = contractHelper->loadContract(*invoiceCreationRequest.contractID, db, delta);

        if (!contractFrame)
        {
            innerResult().code(ManageInvoiceRequestResultCode::CONTRACT_NOT_FOUND);
            return false;
        }

        if (!(contractFrame->getContractor() == getSourceID()))
        {
            innerResult().code(ManageInvoiceRequestResultCode::ONLY_CONTRACTOR_CAN_ATTACH_INVOICE_TO_CONTRACT);
            return false;
        }

        if (!(contractFrame->getCustomer() == invoiceCreationRequest.sender))
        {
            innerResult().code(ManageInvoiceRequestResultCode::SENDER_ACCOUNT_MISMATCHED);
            return false;
        }

        contractFrame->addInvoice(request->getRequestID());
        contractHelper->storeChange(*delta, db, contractFrame->mEntry);
    }


    uint32_t allTasks = 0;
    if (!loadTasks(storageHelper, allTasks, mManageInvoiceRequest.details.invoiceRequest().allTasks))
    {
        innerResult().code(ManageInvoiceRequestResultCode::INVOICE_TASKS_NOT_FOUND);
        return false;
    }

    request->setTasks(allTasks);
    EntryHelperProvider::storeChangeEntry(*delta, db, request->mEntry);

    bool fulfilled = false;

    if (allTasks == 0) {
        auto result = ReviewRequestHelper::tryApproveRequestWithResult(mParentTx, app, ledgerManager, *delta, request);
        if (result.code() != ReviewRequestResultCode::SUCCESS) {
            throw std::runtime_error("Failed to review manage invoice request");
        }
        fulfilled = result.success().fulfilled;
    }

    innerResult().success().details.action(ManageInvoiceRequestAction::CREATE);
    innerResult().success().fulfilled = fulfilled;
    innerResult().success().details.response().requestID = request->getRequestID();
    innerResult().success().details.response().receiverBalance = receiverBalanceID;
    innerResult().success().details.response().senderBalance = senderBalance->getBalanceID();

    return true;
}

bool
ManageInvoiceRequestOpFrame::checkMaxInvoicesForReceiverAccount(Application& app, Database& db, KeyValueHelper &keyValueHelper)
{
    auto maxInvoicesCount = obtainMaxInvoicesCount(app, keyValueHelper);

    auto reviewableRequestHelper = ReviewableRequestHelper::Instance();
    auto allRequests = reviewableRequestHelper->loadRequests(getSourceID(), ReviewableRequestType::CREATE_INVOICE, db);
    if (allRequests.size() >= maxInvoicesCount)
    {
        innerResult().code(ManageInvoiceRequestResultCode::TOO_MANY_INVOICES);
        return false;
    }

    return true;
}

bool
ManageInvoiceRequestOpFrame::checkMaxInvoiceDetailsLength(Application& app, KeyValueHelper &keyValueHelper)
{
    auto maxInvoiceDetailsLength = obtainMaxInvoiceDetailsLength(app, keyValueHelper);

    if (mManageInvoiceRequest.details.invoiceRequest().details.size() >= maxInvoiceDetailsLength)
    {
        innerResult().code(ManageInvoiceRequestResultCode::DETAILS_TOO_LONG);
        return false;
    }

    return true;
}

int64_t
ManageInvoiceRequestOpFrame::obtainMaxInvoicesCount(Application& app, KeyValueHelper &keyValueHelper)
{
    auto maxInvoicesCountKey = ManageKeyValueOpFrame::makeMaxInvoicesCountKey();
    auto maxInvoicesCountKeyValue = keyValueHelper.loadKeyValue(maxInvoicesCountKey);

    if (!maxInvoicesCountKeyValue)
    {
        return app.getMaxInvoicesForReceiverAccount();
    }

    if (maxInvoicesCountKeyValue->getKeyValueEntryType() != KeyValueEntryType::UINT32)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected database state. "
             << "Expected max invoices count key value to be UINT32. Actual: "
             << xdr::xdr_traits<KeyValueEntryType>::enum_name(maxInvoicesCountKeyValue->getKeyValueEntryType());
        throw std::runtime_error("Unexpected database state, expected max invoices count key value to be UINT32");
    }

    return maxInvoicesCountKeyValue->getKeyValue().value.ui32Value();
}

uint64_t
ManageInvoiceRequestOpFrame::obtainMaxInvoiceDetailsLength(Application& app, KeyValueHelper &keyValueHelper)
{
    auto maxInvoicesDetailsLengthKey = ManageKeyValueOpFrame::makeMaxInvoiceDetailLengthKey();
    auto maxInvoicesDetailsLengthKeyValue = keyValueHelper.loadKeyValue(maxInvoicesDetailsLengthKey);

    if (!maxInvoicesDetailsLengthKeyValue)
    {
        return app.getMaxInvoiceDetailLength();
    }

    if (maxInvoicesDetailsLengthKeyValue->getKeyValueEntryType() != KeyValueEntryType::UINT32)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected database state. "
             << "Expected max invoices detail length key value to be UINT32. Actual: "
             << xdr::xdr_traits<KeyValueEntryType>::enum_name(maxInvoicesDetailsLengthKeyValue->getKeyValueEntryType());
        throw std::runtime_error("Unexpected database state, expected max invoices details length key value to be UINT32");
    }

    return maxInvoicesDetailsLengthKeyValue->getKeyValue().value.ui32Value();
}

bool
ManageInvoiceRequestOpFrame::doCheckValid(Application& app)
{
    if (mManageInvoiceRequest.details.action() == ManageInvoiceRequestAction::CREATE &&
        mManageInvoiceRequest.details.invoiceRequest().amount == 0)
    {
        innerResult().code(ManageInvoiceRequestResultCode::MALFORMED);
        return false;
    }

    if (mManageInvoiceRequest.details.action() == ManageInvoiceRequestAction::CREATE &&
        mManageInvoiceRequest.details.invoiceRequest().sender == getSourceID())
    {
        innerResult().code(ManageInvoiceRequestResultCode::MALFORMED);
        return false;
    }

    return true;
}

std::vector<longstring> ManageInvoiceRequestOpFrame::makeTasksKeyVector(StorageHelper &storageHelper) {
    return std::vector<longstring> {
        ManageKeyValueOpFrame::makeInvoiceCreateTasksKey()
    };
}
}
