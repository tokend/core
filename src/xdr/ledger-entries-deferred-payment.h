// -*- C++ -*-
// Automatically generated from ledger-entries-deferred-payment.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_LEDGER_ENTRIES_DEFERRED_PAYMENT_H_INCLUDED__
#define __XDR_LEDGER_ENTRIES_DEFERRED_PAYMENT_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"
#include "xdr/operation-payment.h"

namespace stellar {

struct DeferredPaymentEntry  : xdr::xdr_abstract {
  uint64 id{};
  uint64 amount{};
  PaymentFeeData feeData{};
  AccountID source{};
  BalanceID sourceBalance{};
  AccountID destination{};
  EmptyExt ext{};

  DeferredPaymentEntry() = default;
  template<typename _id_T,
           typename _amount_T,
           typename _feeData_T,
           typename _source_T,
           typename _sourceBalance_T,
           typename _destination_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _id_T>::value
                          && std::is_constructible<uint64, _amount_T>::value
                          && std::is_constructible<PaymentFeeData, _feeData_T>::value
                          && std::is_constructible<AccountID, _source_T>::value
                          && std::is_constructible<BalanceID, _sourceBalance_T>::value
                          && std::is_constructible<AccountID, _destination_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit DeferredPaymentEntry(_id_T &&_id,
                                _amount_T &&_amount,
                                _feeData_T &&_feeData,
                                _source_T &&_source,
                                _sourceBalance_T &&_sourceBalance,
                                _destination_T &&_destination,
                                _ext_T &&_ext)
    : id(std::forward<_id_T>(_id)),
      amount(std::forward<_amount_T>(_amount)),
      feeData(std::forward<_feeData_T>(_feeData)),
      source(std::forward<_source_T>(_source)),
      sourceBalance(std::forward<_sourceBalance_T>(_sourceBalance)),
      destination(std::forward<_destination_T>(_destination)),
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

#endif // !__XDR_LEDGER_ENTRIES_DEFERRED_PAYMENT_H_INCLUDED__
