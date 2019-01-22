#include <ledger/EntryHelperLegacy.h>
#include <ledger/ReviewableRequestFrame.h>
#include <crypto/SHA.h>
#include <ledger/ReviewableRequestHelper.h>
#include "ledger/StorageHelper.h"
#include "review_request/ReviewRequestHelper.h"
#include <lib/xdrpp/xdrpp/marshal.h>
#include "CreateManageLimitsRequestOpFrame.h"

namespace stellar
{

bool
CreateManageLimitsRequestOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                                        std::vector<OperationCondition>& result) const
{
    AccountRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::LIMITS_UPDATE);

    result.emplace_back(resource, "create", mSourceAccount);

    return true;
}

CreateManageLimitsRequestOpFrame::CreateManageLimitsRequestOpFrame(
        Operation const& op, OperationResult& res,
        TransactionFrame& parentTx)
        : OperationFrame(op, res, parentTx)
        , mCreateManageLimitsRequest(mOperation.body.createManageLimitsRequestOp()){}

std::string
CreateManageLimitsRequestOpFrame::getLimitsManageRequestReference(Hash const& documentHash) const
{
    const auto hash = sha256(xdr::xdr_to_opaque(ReviewableRequestType::LIMITS_UPDATE, documentHash));
    return binToHex(hash);
}

std::string
CreateManageLimitsRequestOpFrame::getLimitsManageRequestDetailsReference(longstring const& details) const
{
    const auto hash = sha256(xdr::xdr_to_opaque(ReviewableRequestType::LIMITS_UPDATE, details));
    return binToHex(hash);
}

bool CreateManageLimitsRequestOpFrame::updateManageLimitsRequest(Application &app, StorageHelper &storageHelper, LedgerManager &lm) {
    auto delta = storageHelper.getLedgerDelta();
    auto& db = storageHelper.getDatabase();

    auto reviewableRequestHelper = ReviewableRequestHelper::Instance();
    auto requestFrame = reviewableRequestHelper->loadRequest(mCreateManageLimitsRequest.ext.requestID(), getSourceID(),
                                                             ReviewableRequestType::LIMITS_UPDATE, db, delta);
    if (!requestFrame)
    {
        innerResult().code(CreateManageLimitsRequestResultCode::MANAGE_LIMITS_REQUEST_NOT_FOUND);
        return false;
    }

    if (!ensureLimitsUpdateValid())
    {
        innerResult().code(CreateManageLimitsRequestResultCode::NOT_ALLOWED_TO_SET_TASKS_ON_UPDATE);
        return false;
    }

    auto& limitsUpdateRequest = requestFrame->getRequestEntry().body.limitsUpdateRequest();
    limitsUpdateRequest.ext.details() = mCreateManageLimitsRequest.manageLimitsRequest.ext.details();

    requestFrame->recalculateHashRejectReason();
    reviewableRequestHelper->storeChange(*delta, db, requestFrame->mEntry);

    innerResult().success().fulfilled = false;
    innerResult().code(CreateManageLimitsRequestResultCode::SUCCESS);
    innerResult().success().ext.v(LedgerVersion::EMPTY_VERSION);
    innerResult().success().manageLimitsRequestID = requestFrame->getRequestID();

    return true;
}

bool CreateManageLimitsRequestOpFrame::createManageLimitsRequest(Application &app, StorageHelper& storageHelper,
                                                                 LedgerManager &ledgerManager)
{
    Database& db = ledgerManager.getDatabase();
    auto delta = storageHelper.getLedgerDelta();

    longstring reference;
    auto& manageLimitsRequest = mCreateManageLimitsRequest.manageLimitsRequest;
    if (ledgerManager.shouldUse(LedgerVersion::LIMITS_UPDATE_REQUEST_DEPRECATED_DOCUMENT_HASH) &&
        manageLimitsRequest.ext.v() == LedgerVersion::LIMITS_UPDATE_REQUEST_DEPRECATED_DOCUMENT_HASH)
    {
        auto details = manageLimitsRequest.ext.details();
        reference = getLimitsManageRequestDetailsReference(details);
    }
    else
        reference = getLimitsManageRequestReference(mCreateManageLimitsRequest.manageLimitsRequest.deprecatedDocumentHash);

    const auto referencePtr = xdr::pointer<string64>(new string64(reference));

    auto reviewableRequestHelper = ReviewableRequestHelper::Instance();
    if (reviewableRequestHelper->isReferenceExist(db, getSourceID(), reference))
    {
        innerResult().code(CreateManageLimitsRequestResultCode::MANAGE_LIMITS_REQUEST_REFERENCE_DUPLICATION);
        return false;
    }

    ReviewableRequestEntry::_body_t body;
    body.type(ReviewableRequestType::LIMITS_UPDATE);
    if (ledgerManager.shouldUse(LedgerVersion::LIMITS_UPDATE_REQUEST_DEPRECATED_DOCUMENT_HASH))
    {
        body.limitsUpdateRequest().ext.v(LedgerVersion::LIMITS_UPDATE_REQUEST_DEPRECATED_DOCUMENT_HASH);
        body.limitsUpdateRequest().ext.details() = mCreateManageLimitsRequest.manageLimitsRequest.ext.details();
    }
    else
        body.limitsUpdateRequest().deprecatedDocumentHash =
                mCreateManageLimitsRequest.manageLimitsRequest.deprecatedDocumentHash;

    auto request = ReviewableRequestFrame::createNewWithHash(*delta, getSourceID(),
                                                             app.getAdminID(), referencePtr,
                                                             body, ledgerManager.getCloseTime());


    uint32_t allTasks = 0;
    if (!loadTasks(storageHelper, allTasks, mCreateManageLimitsRequest.allTasks))
    {
        innerResult().code(CreateManageLimitsRequestResultCode::LIMITS_UPDATE_TASKS_NOT_FOUND);
        return false;
    }

    if (allTasks == 0)
    {
        innerResult().code(CreateManageLimitsRequestResultCode::LIMITS_UPDATE_ZERO_TASKS_NOT_ALLOWED);
        return false;
    }
    request->setTasks(allTasks);
    EntryHelperProvider::storeAddEntry(*delta, db, request->mEntry);

    innerResult().code(CreateManageLimitsRequestResultCode::SUCCESS);
    innerResult().success().manageLimitsRequestID = request->getRequestID();
    innerResult().success().fulfilled = false;

    return true;
}

bool
CreateManageLimitsRequestOpFrame::doApply(Application& app, StorageHelper &storageHelper, LedgerManager& ledgerManager)
{
    if(!ledgerManager.shouldUse(mCreateManageLimitsRequest.ext.v()))
    {
        innerResult().code(CreateManageLimitsRequestResultCode::INVALID_MANAGE_LIMITS_REQUEST_VERSION);
        return false;
    }
    auto delta = storageHelper.getLedgerDelta();
    if (!ledgerManager.shouldUse(LedgerVersion::ALLOW_TO_UPDATE_AND_REJECT_LIMITS_UPDATE_REQUESTS))
    {
        return createManageLimitsRequest(app, storageHelper, ledgerManager);
    }

    auto& manageLimitsRequest = mCreateManageLimitsRequest.manageLimitsRequest;
    bool requestHasNewDetails = manageLimitsRequest.ext.v() ==
                                LedgerVersion::LIMITS_UPDATE_REQUEST_DEPRECATED_DOCUMENT_HASH;

    if (requestHasNewDetails && !isValidJson(manageLimitsRequest.ext.details()))
    {
        innerResult().code(CreateManageLimitsRequestResultCode::INVALID_DETAILS);
        return false;
    }

    // required for the new flow, when source have to specify request id for creation or update of the request
    bool isUpdating = mCreateManageLimitsRequest.ext.v() ==
                      LedgerVersion::ALLOW_TO_UPDATE_AND_REJECT_LIMITS_UPDATE_REQUESTS &&
                      mCreateManageLimitsRequest.ext.requestID() != 0;
    if (isUpdating)
    {
        return updateManageLimitsRequest(app, storageHelper, ledgerManager);
    }

    return createManageLimitsRequest(app, storageHelper, ledgerManager);
}

bool CreateManageLimitsRequestOpFrame::doCheckValid(Application& app)
{
    return true;
}

bool CreateManageLimitsRequestOpFrame::ensureLimitsUpdateValid()
{
    if (mCreateManageLimitsRequest.allTasks)
    {
        return false;
    }

    return true;
}

}