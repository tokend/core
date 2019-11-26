// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <transactions/payment/PaymentOpFrame.h>
#include <transactions/deprecated/ManageContractOpFrame.h>
#include <ledger/EntryHelperLegacy.h>
#include "util/asio.h"
#include "ReviewContractRequestOpFrame.h"
#include "database/Database.h"
#include "ledger/LedgerDelta.h"
#include "ledger/AssetHelper.h"
#include "ledger/StorageHelper.h"
#include "ledger/ContractHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/LedgerHeaderFrame.h"
#include "main/Application.h"

namespace stellar
{

using namespace std;
using xdr::operator==;

bool
ReviewContractRequestOpFrame::handleApprove(Application& app, StorageHelper& storageHelper,
                                            LedgerManager& ledgerManager,
                                            ReviewableRequestFrame::pointer request)
{
    if (request->getRequestType() != ReviewableRequestType::MANAGE_CONTRACT)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected request type. Expected CONTRACT, but got "
                                               << xdr::xdr_traits<ReviewableRequestType>::enum_name(request->getRequestType());
        throw invalid_argument("Unexpected request type for review contract request");
    }

    auto& requestHelper = storageHelper.getReviewableRequestHelper();

    handleTasks(requestHelper, request);

    if (!request->canBeFulfilled(ledgerManager))
    {
        innerResult().code(ReviewRequestResultCode::SUCCESS);
        innerResult().success().fulfilled = false;
        return true;
    }

    requestHelper.storeDelete(request->getKey());

    auto contractFrame = make_shared<ContractFrame>();
    auto& contractEntry = contractFrame->getContract();
    auto contractRequest = request->getRequestEntry().body.contractRequest();

    auto& delta = storageHelper.mustGetLedgerDelta();

    contractEntry.contractID = delta.getHeaderFrame().generateID(LedgerEntryType::CONTRACT);
    contractEntry.contractor = request->getRequestor();
    contractEntry.customer = request->getReviewer();
    contractEntry.escrow = contractRequest.escrow;
    contractEntry.startTime = contractRequest.startTime;
    contractEntry.endTime = contractRequest.endTime;
    contractEntry.initialDetails = contractRequest.creatorDetails;
    contractEntry.state = static_cast<uint32_t>(ContractState::NO_CONFIRMATIONS);

    if (!checkCustomerDetailsLength(app, storageHelper))
        return false;

    contractEntry.customerDetails = mReviewRequest.requestDetails.contract().details;

    auto& db = storageHelper.getDatabase();
    EntryHelperProvider::storeAddEntry(delta, db, contractFrame->mEntry);

    innerResult().code(ReviewRequestResultCode::SUCCESS);
    innerResult().success().fulfilled = false;
    return true;
}

bool
ReviewContractRequestOpFrame::checkCustomerDetailsLength(Application& app, StorageHelper& storageHelper)
{
    auto maxCustomerDetailsLength = ManageContractOpFrame::obtainMaxContractDetailLength(app, storageHelper);
    if (mReviewRequest.requestDetails.contract().details.size() > maxCustomerDetailsLength)
    {
        innerResult().code(ReviewRequestResultCode::CONTRACT_DETAILS_TOO_LONG);
        return false;
    }

    return true;
}

bool
ReviewContractRequestOpFrame::handleReject(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager,
                                           ReviewableRequestFrame::pointer request)
{
    innerResult().code(ReviewRequestResultCode::REJECT_NOT_ALLOWED);
    return false;
}

ReviewContractRequestOpFrame::ReviewContractRequestOpFrame(Operation const& op, OperationResult& res,
                                                           TransactionFrame& parentTx)
    : ReviewRequestOpFrame(op, res, parentTx)
{
}

}
