// -*- C++ -*-
// Automatically generated from ledger-entries-swap.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_LEDGER_ENTRIES_SWAP_H_INCLUDED__
#define __XDR_LEDGER_ENTRIES_SWAP_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"

namespace stellar {

struct SwapEntry  : xdr::xdr_abstract {
  uint64 swapID{};
  Hash secretHash{};
  BalanceID sourceBalance{};
  BalanceID destinationBalance{};
  longstring details{};
  uint64 amount{};
  int64 createdAt{};
  int64 lockTime{};
  uint64 fee{};
  EmptyExt ext{};

  SwapEntry() = default;
  template<typename _swapID_T,
           typename _secretHash_T,
           typename _sourceBalance_T,
           typename _destinationBalance_T,
           typename _details_T,
           typename _amount_T,
           typename _createdAt_T,
           typename _lockTime_T,
           typename _fee_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _swapID_T>::value
                          && std::is_constructible<Hash, _secretHash_T>::value
                          && std::is_constructible<BalanceID, _sourceBalance_T>::value
                          && std::is_constructible<BalanceID, _destinationBalance_T>::value
                          && std::is_constructible<longstring, _details_T>::value
                          && std::is_constructible<uint64, _amount_T>::value
                          && std::is_constructible<int64, _createdAt_T>::value
                          && std::is_constructible<int64, _lockTime_T>::value
                          && std::is_constructible<uint64, _fee_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit SwapEntry(_swapID_T &&_swapID,
                     _secretHash_T &&_secretHash,
                     _sourceBalance_T &&_sourceBalance,
                     _destinationBalance_T &&_destinationBalance,
                     _details_T &&_details,
                     _amount_T &&_amount,
                     _createdAt_T &&_createdAt,
                     _lockTime_T &&_lockTime,
                     _fee_T &&_fee,
                     _ext_T &&_ext)
    : swapID(std::forward<_swapID_T>(_swapID)),
      secretHash(std::forward<_secretHash_T>(_secretHash)),
      sourceBalance(std::forward<_sourceBalance_T>(_sourceBalance)),
      destinationBalance(std::forward<_destinationBalance_T>(_destinationBalance)),
      details(std::forward<_details_T>(_details)),
      amount(std::forward<_amount_T>(_amount)),
      createdAt(std::forward<_createdAt_T>(_createdAt)),
      lockTime(std::forward<_lockTime_T>(_lockTime)),
      fee(std::forward<_fee_T>(_fee)),
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

#endif // !__XDR_LEDGER_ENTRIES_SWAP_H_INCLUDED__
