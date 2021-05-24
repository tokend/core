#pragma once

#include "EntryHelper.h"
#include "DeferredPaymentFrame.h"

namespace stellar 
{
class DeferredPaymentHelper : public EntryHelper 
{
public:
    virtual DeferredPaymentFrame::pointer
    loadDeferredPayment(uint64_t id) = 0;
};
}