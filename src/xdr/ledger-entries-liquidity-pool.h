// -*- C++ -*-
// Automatically generated from ledger-entries-liquidity-pool.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_LEDGER_ENTRIES_LIQUIDITY_POOL_H_INCLUDED__
#define __XDR_LEDGER_ENTRIES_LIQUIDITY_POOL_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"

namespace stellar {

struct LiquidityPoolEntry  : xdr::xdr_abstract {
  uint64 id{};
  AccountID liquidityPoolAccount{};
  AssetCode lpTokenAssetCode{};
  BalanceID firstAssetBalance{};
  BalanceID secondAssetBalance{};
  uint64 lpTokensTotalCap{};
  uint64 firstReserve{};
  uint64 secondReserve{};
  EmptyExt ext{};

  LiquidityPoolEntry() = default;
  template<typename _id_T,
           typename _liquidityPoolAccount_T,
           typename _lpTokenAssetCode_T,
           typename _firstAssetBalance_T,
           typename _secondAssetBalance_T,
           typename _lpTokensTotalCap_T,
           typename _firstReserve_T,
           typename _secondReserve_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _id_T>::value
                          && std::is_constructible<AccountID, _liquidityPoolAccount_T>::value
                          && std::is_constructible<AssetCode, _lpTokenAssetCode_T>::value
                          && std::is_constructible<BalanceID, _firstAssetBalance_T>::value
                          && std::is_constructible<BalanceID, _secondAssetBalance_T>::value
                          && std::is_constructible<uint64, _lpTokensTotalCap_T>::value
                          && std::is_constructible<uint64, _firstReserve_T>::value
                          && std::is_constructible<uint64, _secondReserve_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit LiquidityPoolEntry(_id_T &&_id,
                              _liquidityPoolAccount_T &&_liquidityPoolAccount,
                              _lpTokenAssetCode_T &&_lpTokenAssetCode,
                              _firstAssetBalance_T &&_firstAssetBalance,
                              _secondAssetBalance_T &&_secondAssetBalance,
                              _lpTokensTotalCap_T &&_lpTokensTotalCap,
                              _firstReserve_T &&_firstReserve,
                              _secondReserve_T &&_secondReserve,
                              _ext_T &&_ext)
    : id(std::forward<_id_T>(_id)),
      liquidityPoolAccount(std::forward<_liquidityPoolAccount_T>(_liquidityPoolAccount)),
      lpTokenAssetCode(std::forward<_lpTokenAssetCode_T>(_lpTokenAssetCode)),
      firstAssetBalance(std::forward<_firstAssetBalance_T>(_firstAssetBalance)),
      secondAssetBalance(std::forward<_secondAssetBalance_T>(_secondAssetBalance)),
      lpTokensTotalCap(std::forward<_lpTokensTotalCap_T>(_lpTokensTotalCap)),
      firstReserve(std::forward<_firstReserve_T>(_firstReserve)),
      secondReserve(std::forward<_secondReserve_T>(_secondReserve)),
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

#endif // !__XDR_LEDGER_ENTRIES_LIQUIDITY_POOL_H_INCLUDED__
