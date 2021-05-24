#pragma once

#include "ledger/EntryFrame.h"

namespace stellar
{
class DeferredPaymentFrame : public EntryFrame
{
    DeferredPaymentEntry& mDeferredPaymentEntry;

    DeferredPaymentFrame(DeferredPaymentFrame const& from);

  public:
    typedef std::shared_ptr<DeferredPaymentFrame> pointer;

    DeferredPaymentFrame();
    DeferredPaymentFrame(LedgerEntry const& from);

    EntryFrame::pointer
    copy() const override
    {
        return EntryFrame::pointer(new DeferredPaymentFrame(*this));
    }

    static DeferredPaymentFrame::pointer
    createNew(uint64_t const id, CreateDeferredPaymentRequest request,
              const AccountID& ownerID);

    LedgerKey const& getKey() const override;

    DeferredPaymentEntry const&
    getDeferredPayment() const
    {
        return mDeferredPaymentEntry;
    }

    DeferredPaymentEntry&
    getDeferredPayment()
    {
        clearCached();
        return mDeferredPaymentEntry;
    }
};
}