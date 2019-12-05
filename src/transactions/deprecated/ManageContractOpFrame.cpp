#include <ledger/EntryHelper.h>
#include "ledger/ContractHelper.h"
#include "ledger/KeyValueHelper.h"
#include "transactions/review_request/ReviewRequestHelper.h"
#include "ManageContractOpFrame.h"
#include "ledger/BalanceHelper.h"
#include "ledger/StorageHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "transactions/ManageKeyValueOpFrame.h"

namespace stellar
{
using xdr::operator==;

ManageContractOpFrame::ManageContractOpFrame(Operation const& op, OperationResult& res,
                                             TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx), mManageContract(mOperation.body.manageContractOp())
{
}

std::string
ManageContractOpFrame::getInnerResultCodeAsStr()
{
    const auto result = getResult();
    const auto code = getInnerCode(result);
    return xdr::xdr_traits<ManageContractResultCode>::enum_name(code);
}

bool
ManageContractOpFrame::ensureIsAllowed(std::vector<AccountID> validSources)
{
    auto source = getSourceID();
    for (AccountID validSource : validSources)
    {
        if (validSource == source)
            return true;
    }

    innerResult().code(ManageContractResultCode::NOT_ALLOWED);
    return false;
}

bool
ManageContractOpFrame::doApply(Application& app, StorageHelper& storageHelper,
                               LedgerManager& ledgerManager)
{
    AccountEntry& account = mSourceAccount->getAccount();

    innerResult().code(ManageContractResultCode::SUCCESS);

    auto contractFrame = storageHelper.getContractHelper().loadContract(mManageContract.contractID);

    if (!contractFrame)
    {
        innerResult().code(ManageContractResultCode::NOT_FOUND);
        return false;
    }

    switch (mManageContract.data.action())
    {
        case ManageContractAction::ADD_DETAILS:
            return tryAddContractDetails(contractFrame, app, storageHelper);
        case ManageContractAction::START_DISPUTE:
            return tryStartDispute(contractFrame, app, storageHelper);
        case ManageContractAction::CONFIRM_COMPLETED:
            return tryConfirmCompleted(contractFrame, storageHelper);
        case ManageContractAction::RESOLVE_DISPUTE:
            return tryResolveDispute(contractFrame, storageHelper);
        default:
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected source account. "
                                                   << "Expected contractor, customer or master";
            throw std::runtime_error("Unexpected source account. Expected contractor, customer or master");
    }
}

bool
ManageContractOpFrame::tryAddContractDetails(ContractFrame::pointer contractFrame,
                                             Application& app, StorageHelper& storageHelper)
{
    std::vector<AccountID> validSources = {contractFrame->getContractor(), contractFrame->getCustomer()};
    if (contractFrame->isInState(ContractState::DISPUTING))
        validSources.emplace_back(contractFrame->getEscrow());

    if (!ensureIsAllowed(validSources))
    {
        return false;
    }

    innerResult().response().data.action(ManageContractAction::ADD_DETAILS);

    auto maxContractDetailLength = obtainMaxContractDetailLength(app, storageHelper);

    if (mManageContract.data.details().size() > maxContractDetailLength)
    {
        innerResult().code(ManageContractResultCode::DETAILS_TOO_LONG);
        return false;
    }

    return true;
}

uint64_t
ManageContractOpFrame::obtainMaxContractDetailLength(Application& app, StorageHelper& storageHelper)
{
    auto maxContractDetailLengthKey = ManageKeyValueOpFrame::makeMaxContractDetailLengthKey();
    auto maxContractDetailLengthKeyValue = storageHelper.
        getKeyValueHelper().
        loadKeyValue(maxContractDetailLengthKey);

    if (!maxContractDetailLengthKeyValue)
    {
        return app.getMaxContractDetailLength();
    }

    if (maxContractDetailLengthKeyValue->getKeyValueEntryType() != KeyValueEntryType::UINT32)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected database state. "
                                               << "Expected max contract detail length key value to be UINT32. Actual: "
                                               << xdr::xdr_traits<KeyValueEntryType>::enum_name(maxContractDetailLengthKeyValue->getKeyValueEntryType());
        throw std::runtime_error("Unexpected database state, expected max contract detail length key value to be UINT32");
    }

    return maxContractDetailLengthKeyValue->getKeyValue().value.ui32Value();
}

bool
ManageContractOpFrame::tryConfirmCompleted(ContractFrame::pointer contractFrame, StorageHelper& storageHelper)
{
    if (!ensureIsAllowed({contractFrame->getContractor(), contractFrame->getCustomer()}))
        return false;

    innerResult().response().data.action(ManageContractAction::CONFIRM_COMPLETED);

    auto invoiceRequests = storageHelper.
        getReviewableRequestHelper().
        loadRequests(contractFrame->getInvoiceRequestIDs());

    if (!checkIsInvoicesApproved(invoiceRequests))
        return false;

    auto stateToBeAdded = ContractState::CONTRACTOR_CONFIRMED;

    if (contractFrame->getCustomer() == getSourceID())
    {
        stateToBeAdded = ContractState::CUSTOMER_CONFIRMED;
    }

    if (!contractFrame->addState(stateToBeAdded))
    {
        innerResult().code(ManageContractResultCode::ALREADY_CONFIRMED);
        return false;
    }

    storageHelper.getHelper(contractFrame->mEntry.data.type())->storeChange(contractFrame->mEntry);

    return tryCompleted(contractFrame, invoiceRequests, storageHelper);
}

bool
ManageContractOpFrame::tryCompleted(ContractFrame::pointer contractFrame,
                                    std::vector<ReviewableRequestFrame::pointer> invoiceRequests,
                                    StorageHelper& storageHelper)
{
    if (!contractFrame->isBothConfirmed())
    {
        innerResult().response().data.isCompleted() = false;
        return true;
    }

    innerResult().response().data.isCompleted() = true;

    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    auto& balanceHelper = storageHelper.getBalanceHelper();

    for (ReviewableRequestFrame::pointer invoiceRequest : invoiceRequests)
    {
        auto invoice = invoiceRequest->getRequestEntry().body.invoiceRequest();
        auto balanceFrame = balanceHelper.mustLoadBalance(invoice.receiverBalance);

        if (balanceFrame->unlock(invoice.amount) != BalanceFrame::Result::SUCCESS)
        {
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected balance state. "
                                                   << "Expected success unlock in manage contract. ";
            throw std::runtime_error("Unexpected balance state. Expected success unlock in manage contract.");
        }

        balanceHelper.storeChange(balanceFrame->mEntry);
        requestHelper.storeDelete(invoiceRequest->getKey());
    }

    storageHelper.getHelper(contractFrame->getKey().type())->storeDelete(contractFrame->getKey());

    return true;
}

bool ManageContractOpFrame::checkIsInvoicesApproved(std::vector<ReviewableRequestFrame::pointer> invoiceRequests)
{
    for (ReviewableRequestFrame::pointer invoiceRequest : invoiceRequests)
    {
        auto invoice = invoiceRequest->getRequestEntry().body.invoiceRequest();
        if (!invoice.isApproved)
        {
            innerResult().code(ManageContractResultCode::INVOICE_NOT_APPROVED);
            return false;
        }
    }

    return true;
}

bool
ManageContractOpFrame::tryStartDispute(ContractFrame::pointer contractFrame,
                                       Application& app, StorageHelper& storageHelper)
{
    innerResult().response().data.action(ManageContractAction::START_DISPUTE);

    if (contractFrame->isInState(ContractState::DISPUTING))
    {
        innerResult().code(ManageContractResultCode::DISPUTE_ALREADY_STARTED);
        return false;
    }

    if (!ensureIsAllowed({contractFrame->getContractor(), contractFrame->getCustomer()}))
    {
        return false;
    }

    auto maxDisputeLength = obtainMaxContractDetailLength(app, storageHelper);
    if (mManageContract.data.disputeReason().size() > maxDisputeLength)
    {
        innerResult().code(ManageContractResultCode::DISPUTE_REASON_TOO_LONG);
        return false;
    }

    contractFrame->addState(ContractState::DISPUTING);

    storageHelper.getContractHelper().storeChange(contractFrame->mEntry);

    return true;
}

bool
ManageContractOpFrame::tryResolveDispute(ContractFrame::pointer contractFrame,
                                         StorageHelper& storageHelper)
{
    if (!ensureIsAllowed({contractFrame->getEscrow()}))
        return false;

    innerResult().response().data.action(ManageContractAction::RESOLVE_DISPUTE);

    storageHelper.getHelper(contractFrame->getKey().type())->storeDelete(contractFrame->getKey());

    if (mManageContract.data.isRevert())
    {
        return revertInvoicesAmounts(contractFrame, storageHelper);
    }

    unlockApprovedInvoicesAmounts(contractFrame, storageHelper);

    return true;
}

bool
ManageContractOpFrame::revertInvoicesAmounts(ContractFrame::pointer contractFrame,
                                             StorageHelper& storageHelper)
{
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    auto invoiceRequests = requestHelper.loadRequests(contractFrame->getInvoiceRequestIDs());

    for (ReviewableRequestFrame::pointer invoiceRequest : invoiceRequests)
    {
        requestHelper.storeDelete(invoiceRequest->getKey());

        auto invoice = invoiceRequest->getRequestEntry().body.invoiceRequest();
        if (!invoice.isApproved)
        {
            continue;
        }

        auto contractorBalance = balanceHelper.mustLoadBalance(invoice.receiverBalance);
        const BalanceFrame::Result contractorBalanceChargeResult = contractorBalance->tryChargeFromLocked(invoice.amount);
        if (contractorBalanceChargeResult != BalanceFrame::Result::SUCCESS)
        {
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected balance state. "
                                                   << "Expected success charge from locked in manage contract. ";
            throw std::runtime_error("Unexpected balance state. Expected success charge from locked in manage contract.");
        }
        balanceHelper.storeChange(contractorBalance->mEntry);

        auto customerBalance = balanceHelper.mustLoadBalance(invoice.senderBalance);
        const BalanceFrame::Result customerBalanceFundResult = customerBalance->tryFundAccount(invoice.amount);
        if (customerBalanceFundResult != BalanceFrame::Result::SUCCESS)
        {
            innerResult().code(
                customerBalanceFundResult == BalanceFrame::Result::NONMATCHING_PRECISION ?
                ManageContractResultCode::INCORRECT_PRECISION :
                ManageContractResultCode::CUSTOMER_BALANCE_OVERFLOW);
            return false;
        }
        balanceHelper.storeChange(customerBalance->mEntry);
    }

    return true;
}

void
ManageContractOpFrame::unlockApprovedInvoicesAmounts(ContractFrame::pointer contractFrame,
                                                     StorageHelper& storageHelper)
{
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    auto invoiceRequests = requestHelper.loadRequests(contractFrame->getInvoiceRequestIDs());

    for (ReviewableRequestFrame::pointer invoiceRequest : invoiceRequests)
    {
        requestHelper.storeDelete(invoiceRequest->getKey());

        auto invoice = invoiceRequest->getRequestEntry().body.invoiceRequest();
        if (!invoice.isApproved)
        {
            continue;
        }

        auto contractorBalance = balanceHelper.mustLoadBalance(invoice.receiverBalance);
        if (contractorBalance->unlock(invoice.amount) != BalanceFrame::Result::SUCCESS)
        {
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected balance state. "
                                                   << "Expected success charge from locked in manage contract. ";
            throw std::runtime_error("Unexpected balance state. Expected success charge from locked in manage contract.");
        }
        balanceHelper.storeChange(contractorBalance->mEntry);
    }
}

bool
ManageContractOpFrame::doCheckValid(Application& app)
{
    if (((mManageContract.data.action() == ManageContractAction::ADD_DETAILS) &&
         mManageContract.data.details().empty()) ||
        ((mManageContract.data.action() == ManageContractAction::START_DISPUTE) &&
         mManageContract.data.disputeReason().empty()))
    {
        innerResult().code(ManageContractResultCode::MALFORMED);
        return false;
    }

    return true;
}

}
