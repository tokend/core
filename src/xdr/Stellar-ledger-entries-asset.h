// -*- C++ -*-
// Automatically generated from Stellar-ledger-entries-asset.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_LEDGER_ENTRIES_ASSET_H_INCLUDED__
#define __XDR_STELLAR_LEDGER_ENTRIES_ASSET_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-types.h"

namespace stellar {

enum class AssetPolicy : std::int32_t {
  TRANSFERABLE = 1,
  BASE_ASSET = 2,
  STATS_QUOTE_ASSET = 4,
  WITHDRAWABLE = 8,
  ISSUANCE_MANUAL_REVIEW_REQUIRED = 16,
  CAN_BE_BASE_IN_ATOMIC_SWAP = 32,
  CAN_BE_QUOTE_IN_ATOMIC_SWAP = 64,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::AssetPolicy>
  : xdr_integral_base<::stellar::AssetPolicy, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
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
      (int32_t)::stellar::AssetPolicy::CAN_BE_QUOTE_IN_ATOMIC_SWAP
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct AssetEntry {
  struct _ext_t {
    using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
  private:
    _xdr_case_type v_;
    union {
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<LedgerVersion> &_xdr_case_values() {
      static const std::vector<LedgerVersion> _xdr_disc_vec {
        LedgerVersion::EMPTY_VERSION
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)LedgerVersion::EMPTY_VERSION ? 0
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return v_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of v in _ext_t");
      if (fnum != _xdr_field_number(v_)) {
        this->~_ext_t();
        v_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
      }
      else
        v_ = which;
    }
    explicit _ext_t(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                        std::move(source));
    }
    ~_ext_t() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
    _ext_t &operator=(const _ext_t &source) {
      if (_xdr_field_number(v_)
          == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
      }
      v_ = source.v_;
      return *this;
    }
    _ext_t &operator=(_ext_t &&source) {
      if (_xdr_field_number(v_)
           == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                          std::move(source));
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                          std::move(source));
      }
      v_ = source.v_;
      return *this;
    }

    LedgerVersion v() const { return LedgerVersion(v_); }
    _ext_t &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

  };

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
  _ext_t ext{};

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
                          && std::is_constructible<_ext_t, _ext_T>::value
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::AssetEntry::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::AssetEntry::_ext_t;
  using case_type = ::stellar::AssetEntry::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::AssetEntry::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::AssetEntry::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::AssetEntry::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::AssetEntry>
  : xdr_struct_base<field_ptr<::stellar::AssetEntry,
                              decltype(::stellar::AssetEntry::code),
                              &::stellar::AssetEntry::code>,
                    field_ptr<::stellar::AssetEntry,
                              decltype(::stellar::AssetEntry::owner),
                              &::stellar::AssetEntry::owner>,
                    field_ptr<::stellar::AssetEntry,
                              decltype(::stellar::AssetEntry::preissuedAssetSigner),
                              &::stellar::AssetEntry::preissuedAssetSigner>,
                    field_ptr<::stellar::AssetEntry,
                              decltype(::stellar::AssetEntry::details),
                              &::stellar::AssetEntry::details>,
                    field_ptr<::stellar::AssetEntry,
                              decltype(::stellar::AssetEntry::maxIssuanceAmount),
                              &::stellar::AssetEntry::maxIssuanceAmount>,
                    field_ptr<::stellar::AssetEntry,
                              decltype(::stellar::AssetEntry::availableForIssueance),
                              &::stellar::AssetEntry::availableForIssueance>,
                    field_ptr<::stellar::AssetEntry,
                              decltype(::stellar::AssetEntry::issued),
                              &::stellar::AssetEntry::issued>,
                    field_ptr<::stellar::AssetEntry,
                              decltype(::stellar::AssetEntry::pendingIssuance),
                              &::stellar::AssetEntry::pendingIssuance>,
                    field_ptr<::stellar::AssetEntry,
                              decltype(::stellar::AssetEntry::policies),
                              &::stellar::AssetEntry::policies>,
                    field_ptr<::stellar::AssetEntry,
                              decltype(::stellar::AssetEntry::type),
                              &::stellar::AssetEntry::type>,
                    field_ptr<::stellar::AssetEntry,
                              decltype(::stellar::AssetEntry::trailingDigitsCount),
                              &::stellar::AssetEntry::trailingDigitsCount>,
                    field_ptr<::stellar::AssetEntry,
                              decltype(::stellar::AssetEntry::ext),
                              &::stellar::AssetEntry::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::AssetEntry &obj) {
    archive(ar, obj.code, "code");
    archive(ar, obj.owner, "owner");
    archive(ar, obj.preissuedAssetSigner, "preissuedAssetSigner");
    archive(ar, obj.details, "details");
    archive(ar, obj.maxIssuanceAmount, "maxIssuanceAmount");
    archive(ar, obj.availableForIssueance, "availableForIssueance");
    archive(ar, obj.issued, "issued");
    archive(ar, obj.pendingIssuance, "pendingIssuance");
    archive(ar, obj.policies, "policies");
    archive(ar, obj.type, "type");
    archive(ar, obj.trailingDigitsCount, "trailingDigitsCount");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::AssetEntry &obj) {
    archive(ar, obj.code, "code");
    archive(ar, obj.owner, "owner");
    archive(ar, obj.preissuedAssetSigner, "preissuedAssetSigner");
    archive(ar, obj.details, "details");
    archive(ar, obj.maxIssuanceAmount, "maxIssuanceAmount");
    archive(ar, obj.availableForIssueance, "availableForIssueance");
    archive(ar, obj.issued, "issued");
    archive(ar, obj.pendingIssuance, "pendingIssuance");
    archive(ar, obj.policies, "policies");
    archive(ar, obj.type, "type");
    archive(ar, obj.trailingDigitsCount, "trailingDigitsCount");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

}

#endif // !__XDR_STELLAR_LEDGER_ENTRIES_ASSET_H_INCLUDED__
