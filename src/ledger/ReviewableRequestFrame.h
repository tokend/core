#pragma once

// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ledger/EntryFrame.h"
#include "ledger/LedgerManager.h"
#include <functional>
#include <unordered_map>

namespace soci
{
class session;
}

namespace stellar
{
class StatementContext;

class ReviewableRequestFrame : public EntryFrame
{

    ReviewableRequestEntry& mRequest;

    ReviewableRequestFrame(ReviewableRequestFrame const& from);

	static void ensureAssetCreateValid(AssetCreationRequest const & request);
	static void ensureAssetUpdateValid(AssetUpdateRequest const& request);
	static void ensurePreIssuanceValid(PreIssuanceRequest const& request);
	static void ensureIssuanceValid(IssuanceRequest const& request);
	static void ensureWithdrawalValid(WithdrawalRequest const& request);
	static void ensureSaleCreationValid(SaleCreationRequest const& request);
	static void ensureAMLAlertValid(AMLAlertRequest const& request);
	static void ensureChangeRoleValid(ChangeRoleRequest const &request);
	static void ensureUpdateSaleDetailsValid(UpdateSaleDetailsRequest const &request);
	static void ensureInvoiceValid(InvoiceRequest const& request);
	static void ensureASwapAskValid(CreateAtomicSwapAskRequest const& request);
	static void ensureASwapBidValid(CreateAtomicSwapBidRequest const& request);
	static void ensurePollCreationValid(CreatePollRequest const& request);
        static void ensureKYCRecoveryValid(KYCRecoveryRequest const& request);
	static void ensureManageOfferValid(ManageOfferRequest const& request);
	static void ensureCreatePaymentValid(CreatePaymentRequest const& request);
	static void ensureRedemptionValid(RedemptionRequest const &request);
	static void ensureCreateDataValid(DataCreationRequest const &request);
	static void ensureUpdateDataValid(DataUpdateRequest const &request);
	static void ensureRemoveDataValid(DataRemoveRequest const &request);
        static void ensureCreateDeferredPaymentValid(CreateDeferredPaymentRequest const &request);
        static void ensureCloseDeferredPaymentValid(CloseDeferredPaymentRequest const &request);

  public:
    typedef std::shared_ptr<ReviewableRequestFrame> pointer;

    ReviewableRequestFrame();
    ReviewableRequestFrame(LedgerEntry const& from);

    ReviewableRequestFrame& operator=(ReviewableRequestFrame const& other);

    static pointer createNew(uint64_t requestID, AccountID requestor, AccountID reviewer,
        xdr::pointer<stellar::string64> reference, time_t createdAt);
	static pointer createNew(LedgerDelta &delta, AccountID requestor, AccountID reviewer, xdr::pointer<stellar::string64> reference,
						     time_t createdAt);
	// creates new reviewable request and calculates hash for it
	static pointer createNewWithHash(LedgerDelta &delta, AccountID requestor, AccountID reviewer,
                                     xdr::pointer<stellar::string64> reference, ReviewableRequestEntry::_body_t body,
                                     time_t createdAt);

	void setBody(ReviewableRequestEntry::_body_t body) {
		mRequest.body = body;
	}

	void setTasks(uint32_t allTasks);

	AccountID& getRequestor() const {
		return mRequest.requestor;
	}

	AccountID& getReviewer() {
		return mRequest.reviewer;
	}

	xdr::pointer<stellar::string64> getReference() {
		return mRequest.reference;
	}

	uint64 getRequestID() const {
		return mRequest.requestID;
	}

	void setRequestID(uint64_t requestID)
	{
		mRequest.requestID = requestID;
	}

	stellar::longstring const& getRejectReason() const {
		return mRequest.rejectReason;
	}

	ReviewableRequestType getRequestType() const {
		return mRequest.body.type();
	}

	ReviewableRequestEntry const& getRequestEntry() const {
		return mRequest;
	}

	ReviewableRequestEntry& getRequestEntry() {
		return mRequest;
	}

	Hash const& getHash() {
		return mRequest.hash;
	}

	ReviewableRequestType getType() {
		return mRequest.body.type();
	}

    time_t getCreatedAt() {
        return mRequest.createdAt;
    }

    uint32_t getAllTasks() const
	{
		return mRequest.tasks.allTasks;
	}

	uint32_t getPendingTasks() const
	{
		return mRequest.tasks.pendingTasks;
	}

	xdr::xvector<longstring> getExternalDetails() const
	{
		return mRequest.tasks.externalDetails;
	}

	void setRejectReason(stellar::longstring rejectReason) {
		mRequest.rejectReason = rejectReason;
	}

	static uint256 calculateHash(ReviewableRequestEntry::_body_t const& body);

	void recalculateHashRejectReason() {
		const auto newHash = calculateHash(mRequest.body);
		mRequest.hash = newHash;
		mRequest.rejectReason = "";
	}

    EntryFrame::pointer
    copy() const override
    {
        return EntryFrame::pointer(new ReviewableRequestFrame(*this));
    }

    static void ensureValid(ReviewableRequestEntry const& oe);
    void ensureValid() const;

	void checkRequestType(ReviewableRequestType requestType) const;

	bool canBeFulfilled(LedgerManager& lm) const;

    LedgerKey const&
    getKey() const override;
};

}