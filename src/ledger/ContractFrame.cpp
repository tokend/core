#include "ContractFrame.h"

namespace stellar
{

    ContractFrame::ContractFrame() : EntryFrame(LedgerEntryType::CONTRACT), mContract(mEntry.data.contract())
    {
    }

    ContractFrame::ContractFrame(LedgerEntry const& from) : EntryFrame(from), mContract(mEntry.data.contract())
    {
    }

    ContractFrame::ContractFrame(ContractFrame const& from) : ContractFrame(from.mEntry)
    {
    }

    ContractFrame& ContractFrame::operator=(ContractFrame const& other)
    {
        if (&other != this)
        {
            mContract = other.mContract;
            mKey = other.mKey;
            mKeyCalculated = other.mKeyCalculated;
        }
        return *this;
    }

    void
    ContractFrame::addContractDetails(longstring const& details)
    {
        mContract.details.emplace_back(details);
    }

    void
    ContractFrame::addInvoice(uint64_t const& requestID)
    {
        mContract.invoiceRequestsIDs.emplace_back(requestID);
    }

    bool ContractFrame::addState(ContractState state)
    {
        if (mContract.state & static_cast<uint32_t>(state))
            return false;

        mContract.state |= static_cast<uint32_t>(state);
        return true;
    }

    void ContractFrame::startDispute(AccountID const& disputer,
                                     longstring const& reason)
    {
        if (!(mContract.state & static_cast<uint32_t>(ContractState::DISPUTING)))
            addState(ContractState::DISPUTING);

        DisputeDetails disputeDetails;
        disputeDetails.disputer = disputer;
        disputeDetails.reason = reason;

        mContract.disputeDetails.activate() = disputeDetails;
    }

    bool ContractFrame::isBothConfirmed()
    {
        return (mContract.state &
                static_cast<int32_t>(ContractState::CUSTOMER_CONFIRMED)) &&
               (mContract.state &
                static_cast<int32_t>(ContractState::CONTRACTOR_CONFIRMED));
    }
}
