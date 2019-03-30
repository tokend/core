#include <lib/json/json.h>
#include "ReviewableRequestFrame.h"
#include "database/Database.h"
#include "LedgerDelta.h"
#include "ledger/ReferenceFrame.h"
#include "ledger/AssetFrame.h"
#include "ledger/LedgerHeaderFrame.h"
#include "xdrpp/printer.h"
#include "xdrpp/marshal.h"
#include "crypto/SHA.h"
#include "SaleFrame.h"

using namespace soci;
using namespace std;

namespace stellar
{
using xdr::operator<;

ReviewableRequestFrame::ReviewableRequestFrame() : EntryFrame(LedgerEntryType::REVIEWABLE_REQUEST), mRequest(mEntry.data.reviewableRequest())
{
}

ReviewableRequestFrame::ReviewableRequestFrame(LedgerEntry const& from)
    : EntryFrame(from), mRequest(mEntry.data.reviewableRequest())
{
}

ReviewableRequestFrame::ReviewableRequestFrame(ReviewableRequestFrame const& from) : ReviewableRequestFrame(from.mEntry)
{
}

ReviewableRequestFrame& ReviewableRequestFrame::operator=(ReviewableRequestFrame const& other)
{
    if (&other != this)
    {
        mRequest = other.mRequest;
        mKey = other.mKey;
        mKeyCalculated = other.mKeyCalculated;
    }
    return *this;
}

ReviewableRequestFrame::pointer
ReviewableRequestFrame::createNew(LedgerDelta &delta, AccountID requestor, AccountID reviewer, xdr::pointer<stellar::string64> reference,
                                  time_t createdAt)
{
    return createNew(delta.getHeaderFrame().generateID(LedgerEntryType::REVIEWABLE_REQUEST), requestor, reviewer, reference, createdAt);
}

ReviewableRequestFrame::pointer ReviewableRequestFrame::createNew(uint64_t requestID, AccountID requestor, AccountID reviewer,
    xdr::pointer<string64> reference, time_t createdAt)
{
	LedgerEntry entry;
	entry.data.type(LedgerEntryType::REVIEWABLE_REQUEST);
	auto& request = entry.data.reviewableRequest();
	request.requestor = requestor;
	request.reviewer = reviewer;
	request.requestID = requestID;
	request.reference = reference;
    request.createdAt = createdAt;
	return make_shared<ReviewableRequestFrame>(entry);
}

ReviewableRequestFrame::pointer
ReviewableRequestFrame::createNewWithHash(LedgerDelta &delta, AccountID requestor, AccountID reviewer,
                                         xdr::pointer<stellar::string64> reference,
                                         ReviewableRequestEntry::_body_t body, time_t createdAt)
{
	auto result = createNew(delta, requestor, reviewer, reference, createdAt);
	auto& reviewableRequestEntry = result->getRequestEntry();
	reviewableRequestEntry.body = body;
	result->recalculateHashRejectReason();
	return result;
}

void ReviewableRequestFrame::ensureAssetCreateValid(AssetCreationRequest const& request)
{
    const auto owner = AccountID{};
    AssetFrame::create(request, owner)->ensureValid();
}

void ReviewableRequestFrame::ensureAssetUpdateValid(AssetUpdateRequest const& request)
{
	if (!AssetFrame::isAssetCodeValid(request.code))
	{
            throw runtime_error("Asset code is invalid");
	}

    if (!isValidJson(request.creatorDetails))
    {
        throw runtime_error("invalid details");
    }
}

void ReviewableRequestFrame::ensurePreIssuanceValid(PreIssuanceRequest const & request)
{
    if (!AssetFrame::isAssetCodeValid(request.asset))
    {
        throw runtime_error("invalid asset code");
    }

    if (request.amount == 0)
    {
        throw runtime_error("invalid amount");
    }
}

void ReviewableRequestFrame::ensureIssuanceValid(IssuanceRequest const & request)
{
    if (!AssetFrame::isAssetCodeValid(request.asset))
    {
        throw runtime_error("invalid asset code");
    }

    if (request.amount == 0)
    {
        throw runtime_error("invalid amount");
    }

    if (!isValidJson(request.creatorDetails))
    {
        throw runtime_error("invalid external details");
    }
}

void ReviewableRequestFrame::ensureWithdrawalValid(WithdrawalRequest const& request)
{
    if (request.amount == 0)
    {
        throw runtime_error("amount is invalid");
    }

    if (!isValidJson(request.creatorDetails))
    {
        throw runtime_error("external details is invalid");
    }
}

void ReviewableRequestFrame::ensureSaleCreationValid(
    SaleCreationRequest const& request)
{
    const AccountID dummyAccountID;
    map<AssetCode, BalanceID> dummyBalances;
    const BalanceID dummyBalanceID;
    for (auto const& quoteAsset : request.quoteAssets)
    {
        dummyBalances[quoteAsset.quoteAsset] = dummyBalanceID;
    }
    const auto saleFrame = SaleFrame::createNew(0, dummyAccountID, request, dummyBalances, 0);
    saleFrame->ensureValid();
}
void ReviewableRequestFrame::ensureAMLAlertValid(AMLAlertRequest const &request) {
    if(request.creatorDetails.empty()){
        throw runtime_error("reason is invalid");
    }

    if (request.amount == 0)
    {
        throw runtime_error("amount can not be 0");
    }

}

void
ReviewableRequestFrame::ensureChangeRoleValid(const ChangeRoleRequest &request)
{
	if (!isValidJson(request.creatorDetails)) {
		throw std::runtime_error("KYC data is invalid");
	}
}

void ReviewableRequestFrame::ensureUpdateSaleDetailsValid(UpdateSaleDetailsRequest const &request) {
    if (!isValidJson(request.creatorDetails)) {
        throw std::runtime_error("New sale details is invalid");
    }
}

void ReviewableRequestFrame::ensureInvoiceValid(InvoiceRequest const& request)
{
    if (request.amount == 0)
        throw runtime_error("amount can not be 0");
}

void ReviewableRequestFrame::ensureASwapBidCreationValid(
        const ASwapBidCreationRequest &request)
{
    if (request.amount == 0)
    {
        throw runtime_error("amount can not be zero");
    }

    if (!isValidJson(request.creatorDetails))
    {
        throw runtime_error("details must be valid JSON");
    }

    if (request.quoteAssets.empty())
    {
        throw runtime_error("quote assets vector cannot be empty");
    }
}

void ReviewableRequestFrame::ensureASwapValid(const ASwapRequest &request)
{
    if (request.bidID == 0)
    {
        throw runtime_error("bid ID cannot be zero");
    }

    if (request.baseAmount == 0)
    {
        throw runtime_error("base amount cannot be zero");
    }

    if (!AssetFrame::isAssetCodeValid(request.quoteAsset))
    {
        throw runtime_error("invalid quote asset");
    }
}

void ReviewableRequestFrame::ensurePollCreationValid(CreatePollRequest const& request)
{
    if (request.numberOfChoices == 0)
    {
        throw runtime_error("number of choices cannot be zero");
    }
}


uint256 ReviewableRequestFrame::calculateHash(ReviewableRequestEntry::_body_t const & body)
{
	return sha256(xdr::xdr_to_opaque(body));
}

void ReviewableRequestFrame::ensureValid(ReviewableRequestEntry const& oe)
{
    try
    {
        const auto hash = calculateHash(oe.body);
        if (oe.hash != hash)
            throw runtime_error("Calculated hash does not match one in request");
        switch (oe.body.type()) {
        case ReviewableRequestType::CREATE_ASSET:
            ensureAssetCreateValid(oe.body.assetCreationRequest());
            return;
        case ReviewableRequestType::UPDATE_ASSET:
            ensureAssetUpdateValid(oe.body.assetUpdateRequest());
            return;
        case ReviewableRequestType::CREATE_ISSUANCE:
            ensureIssuanceValid(oe.body.issuanceRequest());
            return;
        case ReviewableRequestType::CREATE_PRE_ISSUANCE:
            ensurePreIssuanceValid(oe.body.preIssuanceRequest());
            return;
        case ReviewableRequestType::CREATE_WITHDRAW:
            ensureWithdrawalValid(oe.body.withdrawalRequest());
            return;
        case ReviewableRequestType::CREATE_SALE:
            ensureSaleCreationValid(oe.body.saleCreationRequest());
            return;
        case ReviewableRequestType::UPDATE_LIMITS:
            return;
        case ReviewableRequestType::CREATE_AML_ALERT:
            ensureAMLAlertValid(oe.body.amlAlertRequest());
            return;
		case ReviewableRequestType::CHANGE_ROLE:
            ensureChangeRoleValid(oe.body.changeRoleRequest());
			return;
        case ReviewableRequestType::UPDATE_SALE_DETAILS:
            ensureUpdateSaleDetailsValid(oe.body.updateSaleDetailsRequest());
            return;
        case ReviewableRequestType::CREATE_INVOICE:
            ensureInvoiceValid(oe.body.invoiceRequest());
            return;
        case ReviewableRequestType::MANAGE_CONTRACT:
            return;
        case ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
            return ensureASwapBidCreationValid(oe.body.aSwapBidCreationRequest());
        case ReviewableRequestType::CREATE_ATOMIC_SWAP:
            return ensureASwapValid(oe.body.aSwapRequest());
        case ReviewableRequestType::CREATE_POLL:
            return ensurePollCreationValid(oe.body.createPollRequest());
        default:
            throw runtime_error("Unexpected reviewable request type");
        }
    } catch(exception ex)
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER) << "Reviewable request is invalid: " << xdr::xdr_to_string(oe) << " reason:" << ex.what();
        throw_with_nested(runtime_error("Reviewable request is invalid")); 
    }
}

void
ReviewableRequestFrame::ensureValid() const
{
    ensureValid(mRequest);
}

void ReviewableRequestFrame::setTasks(uint32_t allTasks)
{
    mRequest.tasks.allTasks = allTasks;
    mRequest.tasks.pendingTasks = allTasks;
}

void ReviewableRequestFrame::checkRequestType(ReviewableRequestType requestType) const
{
    if (mRequest.body.type() != requestType) {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected request type. Expected "
                                               << xdr::xdr_traits<ReviewableRequestType>::enum_name(requestType)
                                               << " but got "
                                               << xdr::xdr_traits<ReviewableRequestType>::enum_name(
                                                       mRequest.body.type());
        throw std::invalid_argument("Unexpected request type");
    }
}

bool ReviewableRequestFrame::canBeFulfilled(LedgerManager& lm) const
{
    return mRequest.tasks.pendingTasks == 0;
}

}
