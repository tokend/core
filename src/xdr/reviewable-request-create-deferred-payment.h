// -*- C++ -*-
// Automatically generated from reviewable-request-create-deferred-payment.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_REVIEWABLE_REQUEST_CREATE_DEFERRED_PAYMENT_H_INCLUDED__
#define __XDR_REVIEWABLE_REQUEST_CREATE_DEFERRED_PAYMENT_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"
#include "xdr/operation-payment.h"

namespace stellar {

struct CreateDeferredPaymentRequest  : xdr::xdr_abstract {
  BalanceID sourceBalance{};
  AccountID destination{};
  uint64 amount{};
  uint32 sequenceNumber{};
  longstring creatorDetails{};
  EmptyExt ext{};

  CreateDeferredPaymentRequest() = default;
  template<typename _sourceBalance_T,
           typename _destination_T,
           typename _amount_T,
           typename _sequenceNumber_T,
           typename _creatorDetails_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<BalanceID, _sourceBalance_T>::value
                          && std::is_constructible<AccountID, _destination_T>::value
                          && std::is_constructible<uint64, _amount_T>::value
                          && std::is_constructible<uint32, _sequenceNumber_T>::value
                          && std::is_constructible<longstring, _creatorDetails_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit CreateDeferredPaymentRequest(_sourceBalance_T &&_sourceBalance,
                                        _destination_T &&_destination,
                                        _amount_T &&_amount,
                                        _sequenceNumber_T &&_sequenceNumber,
                                        _creatorDetails_T &&_creatorDetails,
                                        _ext_T &&_ext)
    : sourceBalance(std::forward<_sourceBalance_T>(_sourceBalance)),
      destination(std::forward<_destination_T>(_destination)),
      amount(std::forward<_amount_T>(_amount)),
      sequenceNumber(std::forward<_sequenceNumber_T>(_sequenceNumber)),
      creatorDetails(std::forward<_creatorDetails_T>(_creatorDetails)),
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

#endif // !__XDR_REVIEWABLE_REQUEST_CREATE_DEFERRED_PAYMENT_H_INCLUDED__
