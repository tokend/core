// -*- C++ -*-
// Automatically generated from reviewable-request-payment.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_REVIEWABLE_REQUEST_PAYMENT_H_INCLUDED__
#define __XDR_REVIEWABLE_REQUEST_PAYMENT_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/operation-payment.h"

namespace stellar {

struct CreatePaymentRequest  : xdr::xdr_abstract {
  PaymentOp paymentOp{};
  EmptyExt ext{};

  CreatePaymentRequest() = default;
  template<typename _paymentOp_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<PaymentOp, _paymentOp_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit CreatePaymentRequest(_paymentOp_T &&_paymentOp,
                                _ext_T &&_ext)
    : paymentOp(std::forward<_paymentOp_T>(_paymentOp)),
      ext(std::forward<_ext_T>(_ext)) {}
  bool
operator==(xdr::xdr_abstract const& other) const override;bool
operator<(xdr::xdr_abstract const& other) const override;private:
  bool
from_bytes(xdr::unmarshaler& u) override;
bool
to_bytes(xdr::marshaler& m) const override;
void
count_size(xdr::measurer& m) const override;

};

}

#endif // !__XDR_REVIEWABLE_REQUEST_PAYMENT_H_INCLUDED__
