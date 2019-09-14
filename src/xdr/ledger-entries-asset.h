// -*- C++ -*-
// Automatically generated from ledger-entries-asset.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_LEDGER_ENTRIES_ASSET_H_INCLUDED__
#define __XDR_LEDGER_ENTRIES_ASSET_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"

namespace stellar {

enum class AssetPolicy : std::int32_t {
  TRANSFERABLE = 1,
  BASE_ASSET = 2,
  STATS_QUOTE_ASSET = 4,
  WITHDRAWABLE = 8,
  ISSUANCE_MANUAL_REVIEW_REQUIRED = 16,
  CAN_BE_BASE_IN_ATOMIC_SWAP = 32,
  CAN_BE_QUOTE_IN_ATOMIC_SWAP = 64,
  SWAPPABLE = 128,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::AssetPolicy>
  : xdr_integral_base<::stellar::AssetPolicy, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::AssetPolicy val) {
    switch (val) {
    case ::stellar::AssetPolicy::TRANSFERABLE:
      return "TRANSFERABLE";
    case ::stellar::AssetPolicy::BASE_ASSET:
      return "BASE_ASSET";
    case ::stellar::AssetPolicy::STATS_QUOTE_ASSET:
      return "STATS_QUOTE_ASSET";
    case ::stellar::AssetPolicy::WITHDRAWABLE:
      return "WITHDRAWABLE";
    case ::stellar::AssetPolicy::ISSUANCE_MANUAL_REVIEW_REQUIRED:
      return "ISSUANCE_MANUAL_REVIEW_REQUIRED";
    case ::stellar::AssetPolicy::CAN_BE_BASE_IN_ATOMIC_SWAP:
      return "CAN_BE_BASE_IN_ATOMIC_SWAP";
    case ::stellar::AssetPolicy::CAN_BE_QUOTE_IN_ATOMIC_SWAP:
      return "CAN_BE_QUOTE_IN_ATOMIC_SWAP";
    case ::stellar::AssetPolicy::SWAPPABLE:
      return "SWAPPABLE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::AssetPolicy::TRANSFERABLE,
      (int32_t)::stellar::AssetPolicy::BASE_ASSET,
      (int32_t)::stellar::AssetPolicy::STATS_QUOTE_ASSET,
      (int32_t)::stellar::AssetPolicy::WITHDRAWABLE,
      (int32_t)::stellar::AssetPolicy::ISSUANCE_MANUAL_REVIEW_REQUIRED,
      (int32_t)::stellar::AssetPolicy::CAN_BE_BASE_IN_ATOMIC_SWAP,
      (int32_t)::stellar::AssetPolicy::CAN_BE_QUOTE_IN_ATOMIC_SWAP,
      (int32_t)::stellar::AssetPolicy::SWAPPABLE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct AssetEntry  : xdr::xdr_abstract {
  AssetCode code{};
  AccountID owner{};
  AccountID preissuedAssetSigner{};
  longstring details{};
  uint64 maxIssuanceAmount{};
  uint64 availableForIssueance{};
  uint64 issued{};
  uint64 pendingIssuance{};
  uint32 policies{};
  uint64 type{};
  uint32 trailingDigitsCount{};
  EmptyExt ext{};

  AssetEntry() = default;
  template<typename _code_T,
           typename _owner_T,
           typename _preissuedAssetSigner_T,
           typename _details_T,
           typename _maxIssuanceAmount_T,
           typename _availableForIssueance_T,
           typename _issued_T,
           typename _pendingIssuance_T,
           typename _policies_T,
           typename _type_T,
           typename _trailingDigitsCount_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<AssetCode, _code_T>::value
                          && std::is_constructible<AccountID, _owner_T>::value
                          && std::is_constructible<AccountID, _preissuedAssetSigner_T>::value
                          && std::is_constructible<longstring, _details_T>::value
                          && std::is_constructible<uint64, _maxIssuanceAmount_T>::value
                          && std::is_constructible<uint64, _availableForIssueance_T>::value
                          && std::is_constructible<uint64, _issued_T>::value
                          && std::is_constructible<uint64, _pendingIssuance_T>::value
                          && std::is_constructible<uint32, _policies_T>::value
                          && std::is_constructible<uint64, _type_T>::value
                          && std::is_constructible<uint32, _trailingDigitsCount_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit AssetEntry(_code_T &&_code,
                      _owner_T &&_owner,
                      _preissuedAssetSigner_T &&_preissuedAssetSigner,
                      _details_T &&_details,
                      _maxIssuanceAmount_T &&_maxIssuanceAmount,
                      _availableForIssueance_T &&_availableForIssueance,
                      _issued_T &&_issued,
                      _pendingIssuance_T &&_pendingIssuance,
                      _policies_T &&_policies,
                      _type_T &&_type,
                      _trailingDigitsCount_T &&_trailingDigitsCount,
                      _ext_T &&_ext)
    : code(std::forward<_code_T>(_code)),
      owner(std::forward<_owner_T>(_owner)),
      preissuedAssetSigner(std::forward<_preissuedAssetSigner_T>(_preissuedAssetSigner)),
      details(std::forward<_details_T>(_details)),
      maxIssuanceAmount(std::forward<_maxIssuanceAmount_T>(_maxIssuanceAmount)),
      availableForIssueance(std::forward<_availableForIssueance_T>(_availableForIssueance)),
      issued(std::forward<_issued_T>(_issued)),
      pendingIssuance(std::forward<_pendingIssuance_T>(_pendingIssuance)),
      policies(std::forward<_policies_T>(_policies)),
      type(std::forward<_type_T>(_type)),
      trailingDigitsCount(std::forward<_trailingDigitsCount_T>(_trailingDigitsCount)),
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

#endif // !__XDR_LEDGER_ENTRIES_ASSET_H_INCLUDED__
