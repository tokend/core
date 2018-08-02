// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <transactions/manage_asset/ManageAssetHelper.h>
#include <transactions/payment/PaymentOpV2Frame.h>
#include "util/asio.h"
#include "ReviewContractRequestOpFrame.h"
#include "database/Database.h"
#include "ledger/LedgerDelta.h"
#include "ledger/AssetHelper.h"
#include "ledger/ContractHelper.h"
#include "ledger/BalanceHelper.h"
#include "main/Application.h"

namespace stellar
{

using namespace std;
using xdr::operator==;


SourceDetails
ReviewContractRequestOpFrame::getSourceAccountDetails(
        unordered_map<AccountID, CounterpartyDetails> counterpartiesDetails, int32_t ledgerVersion) const
{
    std::vector<AccountType> allowedAccountTypes = {AccountType::GENERAL, AccountType::NOT_VERIFIED,
                                                    AccountType::EXCHANGE, AccountType::ACCREDITED_INVESTOR,
                                                    AccountType::INSTITUTIONAL_INVESTOR, AccountType::VERIFIED,
                                                    AccountType::MASTER};

    return SourceDetails(allowedAccountTypes, mSourceAccount->getHighThreshold(),
                         static_cast<int32_t>(SignerType::INVOICE_MANAGER));
}

bool
ReviewContractRequestOpFrame::handleApprove(Application& app, LedgerDelta& delta,
                                           LedgerManager& ledgerManager,
                                           ReviewableRequestFrame::pointer request)
{
    innerResult().code(ReviewRequestResultCode::SUCCESS);

    if (request->getRequestType() != ReviewableRequestType::CONTRACT)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected request type. Expected CONTRACT, but got "
                                               << xdr::xdr_traits<ReviewableRequestType>::enum_name(request->getRequestType());
        throw invalid_argument("Unexpected request type for review contract request");
    }

    Database& db = ledgerManager.getDatabase();
    EntryHelperProvider::storeDeleteEntry(delta, db, request->getKey());

    auto contractFrame = make_shared<ContractFrame>();
    auto& contractEntry = contractFrame->getContract();
    auto contractRequest = request->getRequestEntry().body.contractRequest();

    contractEntry.contractID = delta.getHeaderFrame().generateID(LedgerEntryType::CONTRACT);
    contractEntry.contractor = request->getRequestor();
    contractEntry.customer = request->getReviewer();
    contractEntry.judge = app.getMasterID();
    contractEntry.details = contractRequest.details;
    contractEntry.startTime = contractRequest.startTime;
    contractEntry.endTime = contractRequest.endTime;

    EntryHelperProvider::storeAddEntry(delta, db, contractFrame->mEntry);

    if (ledgerManager.shouldUse(LedgerVersion::ADD_CONTRACT_ID_REVIEW_REQUEST_RESULT))
    {
        innerResult().success().ext.v(LedgerVersion::ADD_CONTRACT_ID_REVIEW_REQUEST_RESULT);
        innerResult().success().ext.contractID() = contractEntry.contractID;
    }

    return true;
}


bool
ReviewContractRequestOpFrame::handleReject(Application& app, LedgerDelta& delta, LedgerManager& ledgerManager,
                                           ReviewableRequestFrame::pointer request)
{
    innerResult().code(ReviewRequestResultCode::REJECT_NOT_ALLOWED);
    return false;
}

ReviewContractRequestOpFrame::ReviewContractRequestOpFrame(Operation const & op, OperationResult & res,
                                                           TransactionFrame & parentTx)
        : ReviewRequestOpFrame(op, res, parentTx)
{
}

}
