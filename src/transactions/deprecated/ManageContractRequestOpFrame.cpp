#include <ledger/ReviewableRequestFrame.h>
#include "ManageContractRequestOpFrame.h"
#include "database/Database.h"
#include "main/Application.h"
#include <ledger/ReviewableRequestHelper.h>
#include <ledger/ContractHelper.h>
#include "ledger/LedgerDelta.h"
#include "ledger/StorageHelper.h"
#include "ledger/BalanceHelperLegacy.h"
#include "ledger/KeyValueHelper.h"
#include "transactions/review_request/ReviewRequestHelper.h"
#include "transactions/ManageKeyValueOpFrame.h"

namespace stellar
{
using xdr::operator==;

ManageContractRequestOpFrame::ManageContractRequestOpFrame(Operation const& op, OperationResult& res,
        TransactionFrame& parentTx) : OperationFrame(op, res, parentTx),
        mManageContractRequest(mOperation.body.manageContractRequestOp())
{
}

bool
ManageContractRequestOpFrame::doApply(Application& app, StorageHelper &storageHelper, LedgerManager& ledgerManager)
{
    auto& db = storageHelper.getDatabase();
    auto delta = storageHelper.getLedgerDelta();

    innerResult().code(ManageContractRequestResultCode::SUCCESS);

    if (mManageContractRequest.details.action() == ManageContractRequestAction::CREATE)
    {
        return createManageContractRequest(app, storageHelper, ledgerManager);
    }

    auto reviewableRequestHelper = ReviewableRequestHelper::Instance();
    auto reviewableRequest = reviewableRequestHelper->loadRequest(mManageContractRequest.details.requestID(), db);

    if (!reviewableRequest || reviewableRequest->getRequestType() != ReviewableRequestType::MANAGE_CONTRACT)
    {
        innerResult().code(ManageContractRequestResultCode::NOT_FOUND);
        return false;
    }


    if (!(reviewableRequest->getRequestor() == getSourceID()))
    {
        innerResult().code(ManageContractRequestResultCode::NOT_ALLOWED_TO_REMOVE);
        return false;
    }

    LedgerKey requestKey;
    requestKey.type(LedgerEntryType::REVIEWABLE_REQUEST);
    requestKey.reviewableRequest().requestID = mManageContractRequest.details.requestID();
    reviewableRequestHelper->storeDelete(*delta, db, requestKey);

    innerResult().success().details.action(ManageContractRequestAction::REMOVE);

    return true;
}

bool
ManageContractRequestOpFrame::createManageContractRequest(Application& app, StorageHelper &storageHelper,
                                                          LedgerManager& ledgerManager)
{
    Database& db = storageHelper.getDatabase();
    auto delta = storageHelper.getLedgerDelta();

    auto& contractRequest = mManageContractRequest.details.createContractRequest().contractRequest;

    if (!checkMaxContractsForContractor(app, storageHelper, ledgerManager))
        return false;

    auto& keyValueHelper = storageHelper.getKeyValueHelper();
    if (!checkMaxContractDetailLength(app, keyValueHelper))
        return false;

    ReviewableRequestEntry::_body_t body;
    body.type(ReviewableRequestType::MANAGE_CONTRACT);
    body.contractRequest() = contractRequest;

    auto request = ReviewableRequestFrame::createNewWithHash(*delta, getSourceID(),
                                                             contractRequest.customer,
                                                             nullptr, body,
                                                             ledgerManager.getCloseTime());



    EntryHelperProvider::storeAddEntry(*delta, db, request->mEntry);


    uint32_t allTasks = 0;
    if (!loadTasks(storageHelper, allTasks, mManageContractRequest.details.createContractRequest().allTasks))
    {
        innerResult().code(ManageContractRequestResultCode::CONTRACT_CREATE_TASKS_NOT_FOUND);
        return false;
    }

    request->setTasks(allTasks);
    EntryHelperProvider::storeChangeEntry(*delta, db, request->mEntry);

    bool fulfilled = false;

    if (allTasks == 0) {
        auto result = ReviewRequestHelper::tryApproveRequestWithResult(mParentTx, app, ledgerManager, *delta, request);
        if (result.code() != ReviewRequestResultCode::SUCCESS) {
            throw std::runtime_error("Failed to review manage contract request");
        }
        fulfilled = result.success().fulfilled;
    }

    innerResult().success().details.action(ManageContractRequestAction::CREATE);
    innerResult().success().details.response().requestID = request->getRequestID();
    innerResult().success().details.response().fulfilled = fulfilled;

    return true;
}

bool
ManageContractRequestOpFrame::checkMaxContractsForContractor(Application& app, StorageHelper &storageHelper,
        LedgerManager& ledgerManager)
{
    auto& db = storageHelper.getDatabase();
    auto maxContractsCount = obtainMaxContractsForContractor(app, storageHelper);
    auto contractsCount = ContractHelper::Instance()->countContracts(getSourceID(), db);

    auto allRequests = ReviewableRequestHelper::Instance()->
            loadRequests(getSourceID(), ReviewableRequestType::MANAGE_CONTRACT, db);

    contractsCount += allRequests.size();

    if (contractsCount >= maxContractsCount)
    {
        innerResult().code(ManageContractRequestResultCode::TOO_MANY_CONTRACTS);
        return false;
    }

    return true;
}

uint64_t
ManageContractRequestOpFrame::obtainMaxContractsForContractor(Application& app, StorageHelper &storageHelper)
{
    auto& keyValueHelper = storageHelper.getKeyValueHelper();
    auto maxContractsCountKey = ManageKeyValueOpFrame::makeMaxContractsCountKey();
    auto maxContractsCountKeyValue = keyValueHelper.loadKeyValue(maxContractsCountKey);

    if (!maxContractsCountKeyValue)
    {
        return app.getMaxContractsForContractor();
    }

    if (maxContractsCountKeyValue->getKeyValueEntryType() != KeyValueEntryType::UINT32)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected database state. "
             << "Expected max contracts count key value to be UINT32. Actual: "
             << xdr::xdr_traits<KeyValueEntryType>::enum_name(maxContractsCountKeyValue->getKeyValueEntryType());
        throw std::runtime_error("Unexpected database state, expected max contracts count key value to be UINT32");
    }

    return maxContractsCountKeyValue->getKeyValue().value.ui32Value();
}

bool
ManageContractRequestOpFrame::checkMaxContractDetailLength(Application& app, KeyValueHelper &keyValueHelper)
{
    auto maxContractInitialDetailLength = obtainMaxContractInitialDetailLength(app, keyValueHelper);

    if (mManageContractRequest.details.createContractRequest().contractRequest.creatorDetails.size() > maxContractInitialDetailLength)
    {
        innerResult().code(ManageContractRequestResultCode::DETAILS_TOO_LONG);
        return false;
    }

    return true;
}

uint64_t
ManageContractRequestOpFrame::obtainMaxContractInitialDetailLength(Application& app, KeyValueHelper &keyValueHelper)
{
    auto maxContractInitialDetailLengthKey = ManageKeyValueOpFrame::makeMaxContractInitialDetailLengthKey();
    auto maxContractInitialDetailLengthKeyValue = keyValueHelper.loadKeyValue(maxContractInitialDetailLengthKey);

    if (!maxContractInitialDetailLengthKeyValue)
    {
        return app.getMaxContractInitialDetailLength();
    }

    if (maxContractInitialDetailLengthKeyValue->getKeyValueEntryType() != KeyValueEntryType::UINT32)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected database state. "
             << "Expected max contracts initial detail length key value to be UINT32. Actual: "
             << xdr::xdr_traits<KeyValueEntryType>::enum_name(maxContractInitialDetailLengthKeyValue->getKeyValueEntryType());
        throw std::runtime_error("Unexpected database state, expected max contracts initial detail length key value to be UINT32");
    }

    return maxContractInitialDetailLengthKeyValue->getKeyValue().value.ui32Value();
}

bool
ManageContractRequestOpFrame::doCheckValid(Application& app)
{
    if (mManageContractRequest.details.action() != ManageContractRequestAction::CREATE)
        return true;

    if (mManageContractRequest.details.createContractRequest().contractRequest.creatorDetails.empty())
    {
        innerResult().code(ManageContractRequestResultCode::MALFORMED);
        return false;
    }

    if (mManageContractRequest.details.createContractRequest().contractRequest.customer == getSourceID())
    {
        innerResult().code(ManageContractRequestResultCode::MALFORMED);
        return false;
    }

    if (mManageContractRequest.details.createContractRequest().contractRequest.escrow == getSourceID())
    {
        innerResult().code(ManageContractRequestResultCode::MALFORMED);
        return false;
    }

    if (mManageContractRequest.details.createContractRequest().contractRequest.customer ==
        mManageContractRequest.details.createContractRequest().contractRequest.escrow)
    {
        innerResult().code(ManageContractRequestResultCode::MALFORMED);
        return false;
    }

    if (app.getLedgerManager().getCloseTime() >=
        mManageContractRequest.details.createContractRequest().contractRequest.endTime)
    {
        innerResult().code(ManageContractRequestResultCode::MALFORMED);
        return false;
    }


    if (mManageContractRequest.details.createContractRequest().contractRequest.startTime >=
        mManageContractRequest.details.createContractRequest().contractRequest.endTime)
    {
        innerResult().code(ManageContractRequestResultCode::MALFORMED);
        return false;
    }

    return true;
}

std::vector<longstring>
ManageContractRequestOpFrame::makeTasksKeyVector(StorageHelper &storageHelper)
{
    return std::vector<longstring>{
        ManageKeyValueOpFrame::makeContractCreateTasksKey()
    };
}

}