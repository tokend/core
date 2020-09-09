#include "DeferredPaymentFrame.h"

namespace stellar
{
DeferredPaymentFrame::DeferredPaymentFrame()
    : EntryFrame(LedgerEntryType::DEFERRED_PAYMENT)
    , mDeferredPaymentEntry(mEntry.data.deferredPayment())
{
}

DeferredPaymentFrame::DeferredPaymentFrame(LedgerEntry const& from)
    : EntryFrame(from), mDeferredPaymentEntry(mEntry.data.deferredPayment())
{
}

DeferredPaymentFrame::DeferredPaymentFrame(DeferredPaymentFrame const& from)
    : DeferredPaymentFrame(from.mEntry)
{
}

DeferredPaymentFrame::pointer
DeferredPaymentFrame::createNew(uint64_t const id,
                                CreateDeferredPaymentRequest request,
                                const AccountID& ownerID)
{
    LedgerEntry entry;
    entry.data.type(LedgerEntryType::DEFERRED_PAYMENT);
    auto& deferredPayment = entry.data.deferredPayment();

    deferredPayment.id = id;
    deferredPayment.amount = request.amount;
    deferredPayment.sourceBalance = request.sourceBalance;
    deferredPayment.destination = request.destination;
    deferredPayment.source = ownerID;
    deferredPayment.feeData = request.feeData;

    return std::make_shared<DeferredPaymentFrame>(entry);
}

LedgerKey const&
DeferredPaymentFrame::getKey() const
{
    if (!mKeyCalculated)
    {
        mKey = LedgerKey(LedgerEntryType::DEFERRED_PAYMENT);
        mKey.deferredPayment().id = mDeferredPaymentEntry.id;
        mKeyCalculated = true;
    }

    return mKey;
}

}