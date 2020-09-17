// -*- C++ -*-
// Automatically generated from reviewable-request-close-deferred-payment.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_REVIEWABLE_REQUEST_CLOSE_DEFERRED_PAYMENT_H_INCLUDED__
#define __XDR_REVIEWABLE_REQUEST_CLOSE_DEFERRED_PAYMENT_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"
#include "xdr/operation-payment.h"

namespace stellar {

struct CloseDeferredPaymentRequest  : xdr::xdr_abstract {
  uint64 deferredPaymentID{};
  BalanceID destinationBalance{};
  longstring creatorDetails{};
  uint64 amount{};
  PaymentFeeData feeData{};
  uint32 sequenceNumber{};
  EmptyExt ext{};

  CloseDeferredPaymentRequest() = default;
  template<typename _deferredPaymentID_T,
           typename _destinationBalance_T,
           typename _creatorDetails_T,
           typename _amount_T,
           typename _feeData_T,
           typename _sequenceNumber_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _deferredPaymentID_T>::value
                          && std::is_constructible<BalanceID, _destinationBalance_T>::value
                          && std::is_constructible<longstring, _creatorDetails_T>::value
                          && std::is_constructible<uint64, _amount_T>::value
                          && std::is_constructible<PaymentFeeData, _feeData_T>::value
                          && std::is_constructible<uint32, _sequenceNumber_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit CloseDeferredPaymentRequest(_deferredPaymentID_T &&_deferredPaymentID,
                                       _destinationBalance_T &&_destinationBalance,
                                       _creatorDetails_T &&_creatorDetails,
                                       _amount_T &&_amount,
                                       _feeData_T &&_feeData,
                                       _sequenceNumber_T &&_sequenceNumber,
                                       _ext_T &&_ext)
    : deferredPaymentID(std::forward<_deferredPaymentID_T>(_deferredPaymentID)),
      destinationBalance(std::forward<_destinationBalance_T>(_destinationBalance)),
      creatorDetails(std::forward<_creatorDetails_T>(_creatorDetails)),
      amount(std::forward<_amount_T>(_amount)),
      feeData(std::forward<_feeData_T>(_feeData)),
      sequenceNumber(std::forward<_sequenceNumber_T>(_sequenceNumber)),
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

#endif // !__XDR_REVIEWABLE_REQUEST_CLOSE_DEFERRED_PAYMENT_H_INCLUDED__
