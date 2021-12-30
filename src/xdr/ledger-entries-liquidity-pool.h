// -*- C++ -*-
// Automatically generated from ledger-entries-liquidity-pool.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_LEDGER_ENTRIES_LIQUIDITY_POOL_H_INCLUDED__
#define __XDR_LEDGER_ENTRIES_LIQUIDITY_POOL_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"

namespace stellar {

struct LPAssetPair  : xdr::xdr_abstract {
  AssetCode firstAsset{};
  uint64 firtsAssetAmount{};
  BalanceID firstAssetBalance{};
  AssetCode secondAsset{};
  uint64 secondAssetAmount{};
  BalanceID secondAssetID{};

  LPAssetPair() = default;
  template<typename _firstAsset_T,
           typename _firtsAssetAmount_T,
           typename _firstAssetBalance_T,
           typename _secondAsset_T,
           typename _secondAssetAmount_T,
           typename _secondAssetID_T,
           typename = typename
           std::enable_if<std::is_constructible<AssetCode, _firstAsset_T>::value
                          && std::is_constructible<uint64, _firtsAssetAmount_T>::value
                          && std::is_constructible<BalanceID, _firstAssetBalance_T>::value
                          && std::is_constructible<AssetCode, _secondAsset_T>::value
                          && std::is_constructible<uint64, _secondAssetAmount_T>::value
                          && std::is_constructible<BalanceID, _secondAssetID_T>::value
                         >::type>
  explicit LPAssetPair(_firstAsset_T &&_firstAsset,
                       _firtsAssetAmount_T &&_firtsAssetAmount,
                       _firstAssetBalance_T &&_firstAssetBalance,
                       _secondAsset_T &&_secondAsset,
                       _secondAssetAmount_T &&_secondAssetAmount,
                       _secondAssetID_T &&_secondAssetID)
    : firstAsset(std::forward<_firstAsset_T>(_firstAsset)),
      firtsAssetAmount(std::forward<_firtsAssetAmount_T>(_firtsAssetAmount)),
      firstAssetBalance(std::forward<_firstAssetBalance_T>(_firstAssetBalance)),
      secondAsset(std::forward<_secondAsset_T>(_secondAsset)),
      secondAssetAmount(std::forward<_secondAssetAmount_T>(_secondAssetAmount)),
      secondAssetID(std::forward<_secondAssetID_T>(_secondAssetID)) {}
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

struct LiquidityPoolEntry  : xdr::xdr_abstract {
  uint64 sequentialID{};
  AccountID liquidityPoolOwner{};
  BalanceID lpTokensBalance{};
  uint64 lpTokensAmount{};
  LPAssetPair assetPair{};
  EmptyExt ext{};

  LiquidityPoolEntry() = default;
  template<typename _sequentialID_T,
           typename _liquidityPoolOwner_T,
           typename _lpTokensBalance_T,
           typename _lpTokensAmount_T,
           typename _assetPair_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _sequentialID_T>::value
                          && std::is_constructible<AccountID, _liquidityPoolOwner_T>::value
                          && std::is_constructible<BalanceID, _lpTokensBalance_T>::value
                          && std::is_constructible<uint64, _lpTokensAmount_T>::value
                          && std::is_constructible<LPAssetPair, _assetPair_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit LiquidityPoolEntry(_sequentialID_T &&_sequentialID,
                              _liquidityPoolOwner_T &&_liquidityPoolOwner,
                              _lpTokensBalance_T &&_lpTokensBalance,
                              _lpTokensAmount_T &&_lpTokensAmount,
                              _assetPair_T &&_assetPair,
                              _ext_T &&_ext)
    : sequentialID(std::forward<_sequentialID_T>(_sequentialID)),
      liquidityPoolOwner(std::forward<_liquidityPoolOwner_T>(_liquidityPoolOwner)),
      lpTokensBalance(std::forward<_lpTokensBalance_T>(_lpTokensBalance)),
      lpTokensAmount(std::forward<_lpTokensAmount_T>(_lpTokensAmount)),
      assetPair(std::forward<_assetPair_T>(_assetPair)),
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
