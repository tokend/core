// -*- C++ -*-
// Automatically generated from Stellar-types.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_TYPES_H_INCLUDED__
#define __XDR_STELLAR_TYPES_H_INCLUDED__ 1

#include <xdrpp/types.h>

namespace stellar {

enum class LedgerVersion : std::int32_t {
  EMPTY_VERSION = 0,
  CHECK_SET_FEE_ACCOUNT_EXISTING = 1,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LedgerVersion>
  : xdr_integral_base<::stellar::LedgerVersion, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::LedgerVersion val) {
    switch (val) {
    case ::stellar::LedgerVersion::EMPTY_VERSION:
      return "EMPTY_VERSION";
    case ::stellar::LedgerVersion::CHECK_SET_FEE_ACCOUNT_EXISTING:
      return "CHECK_SET_FEE_ACCOUNT_EXISTING";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::LedgerVersion::EMPTY_VERSION,
      (int32_t)::stellar::LedgerVersion::CHECK_SET_FEE_ACCOUNT_EXISTING
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct EmptyExt {
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
      throw xdr::xdr_bad_discriminant("bad value of v in EmptyExt");
    if (fnum != _xdr_field_number(v_)) {
      this->~EmptyExt();
      v_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    else
      v_ = which;
  }
  explicit EmptyExt(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
  }
  EmptyExt(const EmptyExt &source) : v_(source.v_) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
  }
  EmptyExt(EmptyExt &&source) : v_(source.v_) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                      std::move(source));
  }
  ~EmptyExt() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
  EmptyExt &operator=(const EmptyExt &source) {
    if (_xdr_field_number(v_)
        == _xdr_field_number(source.v_))
      _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
    else {
      this->~EmptyExt();
      v_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
    }
    v_ = source.v_;
    return *this;
  }
  EmptyExt &operator=(EmptyExt &&source) {
    if (_xdr_field_number(v_)
         == _xdr_field_number(source.v_))
      _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                        std::move(source));
    else {
      this->~EmptyExt();
      v_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                        std::move(source));
    }
    v_ = source.v_;
    return *this;
  }

  LedgerVersion v() const { return LedgerVersion(v_); }
  EmptyExt &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

};
} namespace xdr {
template<> struct xdr_traits<::stellar::EmptyExt> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::EmptyExt;
  using case_type = ::stellar::EmptyExt::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::EmptyExt &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in EmptyExt");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::EmptyExt &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in EmptyExt");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::EmptyExt &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
} namespace stellar {

using Hash = xdr::opaque_array<32>;
using uint256 = xdr::opaque_array<32>;
using uint32 = std::uint32_t;
using int32 = std::int32_t;
using uint64 = std::uint64_t;
using int64 = std::int64_t;

enum class CryptoKeyType : std::int32_t {
  KEY_TYPE_ED25519 = 0,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CryptoKeyType>
  : xdr_integral_base<::stellar::CryptoKeyType, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::CryptoKeyType val) {
    switch (val) {
    case ::stellar::CryptoKeyType::KEY_TYPE_ED25519:
      return "KEY_TYPE_ED25519";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::CryptoKeyType::KEY_TYPE_ED25519
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

enum class PublicKeyType : std::int32_t {
  PUBLIC_KEY_TYPE_ED25519 = 0,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::PublicKeyType>
  : xdr_integral_base<::stellar::PublicKeyType, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::PublicKeyType val) {
    switch (val) {
    case ::stellar::PublicKeyType::PUBLIC_KEY_TYPE_ED25519:
      return "PUBLIC_KEY_TYPE_ED25519";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::PublicKeyType::PUBLIC_KEY_TYPE_ED25519
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct PublicKey {
  using _xdr_case_type = xdr::xdr_traits<CryptoKeyType>::case_type;
private:
  _xdr_case_type type_;
  union {
    uint256 ed25519_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<CryptoKeyType> &_xdr_case_values() {
    static const std::vector<CryptoKeyType> _xdr_disc_vec {
      CryptoKeyType::KEY_TYPE_ED25519
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)CryptoKeyType::KEY_TYPE_ED25519 ? 1
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)CryptoKeyType::KEY_TYPE_ED25519:
      _f(&PublicKey::ed25519_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return type_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of type in PublicKey");
    if (fnum != _xdr_field_number(type_)) {
      this->~PublicKey();
      type_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    else
      type_ = which;
  }
  explicit PublicKey(CryptoKeyType which = CryptoKeyType{}) : type_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
  }
  PublicKey(const PublicKey &source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
  }
  PublicKey(PublicKey &&source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                      std::move(source));
  }
  ~PublicKey() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
  PublicKey &operator=(const PublicKey &source) {
    if (_xdr_field_number(type_)
        == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
    else {
      this->~PublicKey();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
    }
    type_ = source.type_;
    return *this;
  }
  PublicKey &operator=(PublicKey &&source) {
    if (_xdr_field_number(type_)
         == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                        std::move(source));
    else {
      this->~PublicKey();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                        std::move(source));
    }
    type_ = source.type_;
    return *this;
  }

  CryptoKeyType type() const { return CryptoKeyType(type_); }
  PublicKey &type(CryptoKeyType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  uint256 &ed25519() {
    if (_xdr_field_number(type_) == 1)
      return ed25519_;
    throw xdr::xdr_wrong_union("PublicKey: ed25519 accessed when not selected");
  }
  const uint256 &ed25519() const {
    if (_xdr_field_number(type_) == 1)
      return ed25519_;
    throw xdr::xdr_wrong_union("PublicKey: ed25519 accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::PublicKey> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::PublicKey;
  using case_type = ::stellar::PublicKey::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "ed25519";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::PublicKey &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in PublicKey");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::PublicKey &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in PublicKey");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::PublicKey &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.type(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum class LedgerEntryType : std::int32_t {
  ANY = 1,
  ACCOUNT = 2,
  SIGNER = 3,
  FEE = 4,
  BALANCE = 5,
  PAYMENT_REQUEST = 6,
  ASSET = 7,
  REFERENCE_ENTRY = 8,
  STATISTICS = 9,
  TRUST = 10,
  ACCOUNT_LIMITS = 11,
  ASSET_PAIR = 12,
  OFFER_ENTRY = 13,
  REVIEWABLE_REQUEST = 15,
  EXTERNAL_SYSTEM_ACCOUNT_ID = 16,
  SALE = 17,
  ACCOUNT_KYC = 18,
  EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY = 19,
  KEY_VALUE = 20,
  LIMITS_V2 = 22,
  STATISTICS_V2 = 23,
  PENDING_STATISTICS = 24,
  CONTRACT = 25,
  ACCOUNT_ROLE = 26,
  ACCOUNT_RULE = 27,
  ATOMIC_SWAP_BID = 28,
  TRANSACTION = 29,
  SIGNER_RULE = 30,
  SIGNER_ROLE = 31,
  STAMP = 32,
  LICENSE = 33,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LedgerEntryType>
  : xdr_integral_base<::stellar::LedgerEntryType, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::LedgerEntryType val) {
    switch (val) {
    case ::stellar::LedgerEntryType::ANY:
      return "ANY";
    case ::stellar::LedgerEntryType::ACCOUNT:
      return "ACCOUNT";
    case ::stellar::LedgerEntryType::SIGNER:
      return "SIGNER";
    case ::stellar::LedgerEntryType::FEE:
      return "FEE";
    case ::stellar::LedgerEntryType::BALANCE:
      return "BALANCE";
    case ::stellar::LedgerEntryType::PAYMENT_REQUEST:
      return "PAYMENT_REQUEST";
    case ::stellar::LedgerEntryType::ASSET:
      return "ASSET";
    case ::stellar::LedgerEntryType::REFERENCE_ENTRY:
      return "REFERENCE_ENTRY";
    case ::stellar::LedgerEntryType::STATISTICS:
      return "STATISTICS";
    case ::stellar::LedgerEntryType::TRUST:
      return "TRUST";
    case ::stellar::LedgerEntryType::ACCOUNT_LIMITS:
      return "ACCOUNT_LIMITS";
    case ::stellar::LedgerEntryType::ASSET_PAIR:
      return "ASSET_PAIR";
    case ::stellar::LedgerEntryType::OFFER_ENTRY:
      return "OFFER_ENTRY";
    case ::stellar::LedgerEntryType::REVIEWABLE_REQUEST:
      return "REVIEWABLE_REQUEST";
    case ::stellar::LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
      return "EXTERNAL_SYSTEM_ACCOUNT_ID";
    case ::stellar::LedgerEntryType::SALE:
      return "SALE";
    case ::stellar::LedgerEntryType::ACCOUNT_KYC:
      return "ACCOUNT_KYC";
    case ::stellar::LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
      return "EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY";
    case ::stellar::LedgerEntryType::KEY_VALUE:
      return "KEY_VALUE";
    case ::stellar::LedgerEntryType::LIMITS_V2:
      return "LIMITS_V2";
    case ::stellar::LedgerEntryType::STATISTICS_V2:
      return "STATISTICS_V2";
    case ::stellar::LedgerEntryType::PENDING_STATISTICS:
      return "PENDING_STATISTICS";
    case ::stellar::LedgerEntryType::CONTRACT:
      return "CONTRACT";
    case ::stellar::LedgerEntryType::ACCOUNT_ROLE:
      return "ACCOUNT_ROLE";
    case ::stellar::LedgerEntryType::ACCOUNT_RULE:
      return "ACCOUNT_RULE";
    case ::stellar::LedgerEntryType::ATOMIC_SWAP_BID:
      return "ATOMIC_SWAP_BID";
    case ::stellar::LedgerEntryType::TRANSACTION:
      return "TRANSACTION";
    case ::stellar::LedgerEntryType::SIGNER_RULE:
      return "SIGNER_RULE";
    case ::stellar::LedgerEntryType::SIGNER_ROLE:
      return "SIGNER_ROLE";
    case ::stellar::LedgerEntryType::STAMP:
      return "STAMP";
    case ::stellar::LedgerEntryType::LICENSE:
      return "LICENSE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::LedgerEntryType::ANY,
      (int32_t)::stellar::LedgerEntryType::ACCOUNT,
      (int32_t)::stellar::LedgerEntryType::SIGNER,
      (int32_t)::stellar::LedgerEntryType::FEE,
      (int32_t)::stellar::LedgerEntryType::BALANCE,
      (int32_t)::stellar::LedgerEntryType::PAYMENT_REQUEST,
      (int32_t)::stellar::LedgerEntryType::ASSET,
      (int32_t)::stellar::LedgerEntryType::REFERENCE_ENTRY,
      (int32_t)::stellar::LedgerEntryType::STATISTICS,
      (int32_t)::stellar::LedgerEntryType::TRUST,
      (int32_t)::stellar::LedgerEntryType::ACCOUNT_LIMITS,
      (int32_t)::stellar::LedgerEntryType::ASSET_PAIR,
      (int32_t)::stellar::LedgerEntryType::OFFER_ENTRY,
      (int32_t)::stellar::LedgerEntryType::REVIEWABLE_REQUEST,
      (int32_t)::stellar::LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID,
      (int32_t)::stellar::LedgerEntryType::SALE,
      (int32_t)::stellar::LedgerEntryType::ACCOUNT_KYC,
      (int32_t)::stellar::LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY,
      (int32_t)::stellar::LedgerEntryType::KEY_VALUE,
      (int32_t)::stellar::LedgerEntryType::LIMITS_V2,
      (int32_t)::stellar::LedgerEntryType::STATISTICS_V2,
      (int32_t)::stellar::LedgerEntryType::PENDING_STATISTICS,
      (int32_t)::stellar::LedgerEntryType::CONTRACT,
      (int32_t)::stellar::LedgerEntryType::ACCOUNT_ROLE,
      (int32_t)::stellar::LedgerEntryType::ACCOUNT_RULE,
      (int32_t)::stellar::LedgerEntryType::ATOMIC_SWAP_BID,
      (int32_t)::stellar::LedgerEntryType::TRANSACTION,
      (int32_t)::stellar::LedgerEntryType::SIGNER_RULE,
      (int32_t)::stellar::LedgerEntryType::SIGNER_ROLE,
      (int32_t)::stellar::LedgerEntryType::STAMP,
      (int32_t)::stellar::LedgerEntryType::LICENSE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

using Signature = xdr::opaque_vec<64>;
using SignatureHint = xdr::opaque_array<4>;
using NodeID = PublicKey;

struct Curve25519Secret {
  xdr::opaque_array<32> key{};

  Curve25519Secret() = default;
  template<typename _key_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::opaque_array<32>, _key_T>::value
                         >::type>
  explicit Curve25519Secret(_key_T &&_key)
    : key(std::forward<_key_T>(_key)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::Curve25519Secret>
  : xdr_struct_base<field_ptr<::stellar::Curve25519Secret,
                              decltype(::stellar::Curve25519Secret::key),
                              &::stellar::Curve25519Secret::key>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::Curve25519Secret &obj) {
    archive(ar, obj.key, "key");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::Curve25519Secret &obj) {
    archive(ar, obj.key, "key");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct Curve25519Public {
  xdr::opaque_array<32> key{};

  Curve25519Public() = default;
  template<typename _key_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::opaque_array<32>, _key_T>::value
                         >::type>
  explicit Curve25519Public(_key_T &&_key)
    : key(std::forward<_key_T>(_key)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::Curve25519Public>
  : xdr_struct_base<field_ptr<::stellar::Curve25519Public,
                              decltype(::stellar::Curve25519Public::key),
                              &::stellar::Curve25519Public::key>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::Curve25519Public &obj) {
    archive(ar, obj.key, "key");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::Curve25519Public &obj) {
    archive(ar, obj.key, "key");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct HmacSha256Key {
  xdr::opaque_array<32> key{};

  HmacSha256Key() = default;
  template<typename _key_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::opaque_array<32>, _key_T>::value
                         >::type>
  explicit HmacSha256Key(_key_T &&_key)
    : key(std::forward<_key_T>(_key)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::HmacSha256Key>
  : xdr_struct_base<field_ptr<::stellar::HmacSha256Key,
                              decltype(::stellar::HmacSha256Key::key),
                              &::stellar::HmacSha256Key::key>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::HmacSha256Key &obj) {
    archive(ar, obj.key, "key");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::HmacSha256Key &obj) {
    archive(ar, obj.key, "key");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct HmacSha256Mac {
  xdr::opaque_array<32> mac{};

  HmacSha256Mac() = default;
  template<typename _mac_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::opaque_array<32>, _mac_T>::value
                         >::type>
  explicit HmacSha256Mac(_mac_T &&_mac)
    : mac(std::forward<_mac_T>(_mac)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::HmacSha256Mac>
  : xdr_struct_base<field_ptr<::stellar::HmacSha256Mac,
                              decltype(::stellar::HmacSha256Mac::mac),
                              &::stellar::HmacSha256Mac::mac>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::HmacSha256Mac &obj) {
    archive(ar, obj.mac, "mac");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::HmacSha256Mac &obj) {
    archive(ar, obj.mac, "mac");
    xdr::validate(obj);
  }
};
} namespace stellar {

using AccountID = PublicKey;
using BalanceID = PublicKey;
using Thresholds = xdr::opaque_array<4>;
using string32 = xdr::xstring<32>;
using string64 = xdr::xstring<64>;
using string256 = xdr::xstring<256>;
using longstring = xdr::xstring<>;
using AssetCode = xdr::xstring<16>;
using Salt = uint64;
using DataValue = xdr::opaque_vec<64>;

struct Fee {
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

  uint64 fixed{};
  uint64 percent{};
  _ext_t ext{};

  Fee() = default;
  template<typename _fixed_T,
           typename _percent_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _fixed_T>::value
                          && std::is_constructible<uint64, _percent_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit Fee(_fixed_T &&_fixed,
               _percent_T &&_percent,
               _ext_T &&_ext)
    : fixed(std::forward<_fixed_T>(_fixed)),
      percent(std::forward<_percent_T>(_percent)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::Fee::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::Fee::_ext_t;
  using case_type = ::stellar::Fee::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::Fee::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::Fee::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::Fee::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::Fee>
  : xdr_struct_base<field_ptr<::stellar::Fee,
                              decltype(::stellar::Fee::fixed),
                              &::stellar::Fee::fixed>,
                    field_ptr<::stellar::Fee,
                              decltype(::stellar::Fee::percent),
                              &::stellar::Fee::percent>,
                    field_ptr<::stellar::Fee,
                              decltype(::stellar::Fee::ext),
                              &::stellar::Fee::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::Fee &obj) {
    archive(ar, obj.fixed, "fixed");
    archive(ar, obj.percent, "percent");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::Fee &obj) {
    archive(ar, obj.fixed, "fixed");
    archive(ar, obj.percent, "percent");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum class OperationType : std::int32_t {
  CREATE_ACCOUNT = 1,
  CREATE_ISSUANCE_REQUEST = 3,
  SET_FEES = 5,
  CREATE_WITHDRAWAL_REQUEST = 7,
  MANAGE_BALANCE = 9,
  MANAGE_ASSET = 11,
  CREATE_PREISSUANCE_REQUEST = 12,
  MANAGE_LIMITS = 13,
  MANAGE_ASSET_PAIR = 15,
  MANAGE_OFFER = 16,
  MANAGE_INVOICE_REQUEST = 17,
  REVIEW_REQUEST = 18,
  CREATE_SALE_REQUEST = 19,
  CHECK_SALE_STATE = 20,
  CREATE_AML_ALERT = 21,
  CREATE_CHANGE_ROLE_REQUEST = 22,
  PAYMENT = 23,
  MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY = 24,
  BIND_EXTERNAL_SYSTEM_ACCOUNT_ID = 25,
  MANAGE_SALE = 26,
  MANAGE_KEY_VALUE = 27,
  CREATE_MANAGE_LIMITS_REQUEST = 28,
  MANAGE_CONTRACT_REQUEST = 29,
  MANAGE_CONTRACT = 30,
  CANCEL_SALE_REQUEST = 31,
  PAYOUT = 32,
  MANAGE_ACCOUNT_ROLE = 33,
  MANAGE_ACCOUNT_RULE = 34,
  CREATE_ASWAP_BID_REQUEST = 35,
  CANCEL_ASWAP_BID = 36,
  CREATE_ASWAP_REQUEST = 37,
  MANAGE_SIGNER = 38,
  MANAGE_SIGNER_ROLE = 39,
  MANAGE_SIGNER_RULE = 40,
  STAMP = 41,
  LICENSE = 42,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::OperationType>
  : xdr_integral_base<::stellar::OperationType, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::OperationType val) {
    switch (val) {
    case ::stellar::OperationType::CREATE_ACCOUNT:
      return "CREATE_ACCOUNT";
    case ::stellar::OperationType::CREATE_ISSUANCE_REQUEST:
      return "CREATE_ISSUANCE_REQUEST";
    case ::stellar::OperationType::SET_FEES:
      return "SET_FEES";
    case ::stellar::OperationType::CREATE_WITHDRAWAL_REQUEST:
      return "CREATE_WITHDRAWAL_REQUEST";
    case ::stellar::OperationType::MANAGE_BALANCE:
      return "MANAGE_BALANCE";
    case ::stellar::OperationType::MANAGE_ASSET:
      return "MANAGE_ASSET";
    case ::stellar::OperationType::CREATE_PREISSUANCE_REQUEST:
      return "CREATE_PREISSUANCE_REQUEST";
    case ::stellar::OperationType::MANAGE_LIMITS:
      return "MANAGE_LIMITS";
    case ::stellar::OperationType::MANAGE_ASSET_PAIR:
      return "MANAGE_ASSET_PAIR";
    case ::stellar::OperationType::MANAGE_OFFER:
      return "MANAGE_OFFER";
    case ::stellar::OperationType::MANAGE_INVOICE_REQUEST:
      return "MANAGE_INVOICE_REQUEST";
    case ::stellar::OperationType::REVIEW_REQUEST:
      return "REVIEW_REQUEST";
    case ::stellar::OperationType::CREATE_SALE_REQUEST:
      return "CREATE_SALE_REQUEST";
    case ::stellar::OperationType::CHECK_SALE_STATE:
      return "CHECK_SALE_STATE";
    case ::stellar::OperationType::CREATE_AML_ALERT:
      return "CREATE_AML_ALERT";
    case ::stellar::OperationType::CREATE_CHANGE_ROLE_REQUEST:
      return "CREATE_CHANGE_ROLE_REQUEST";
    case ::stellar::OperationType::PAYMENT:
      return "PAYMENT";
    case ::stellar::OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
      return "MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY";
    case ::stellar::OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID:
      return "BIND_EXTERNAL_SYSTEM_ACCOUNT_ID";
    case ::stellar::OperationType::MANAGE_SALE:
      return "MANAGE_SALE";
    case ::stellar::OperationType::MANAGE_KEY_VALUE:
      return "MANAGE_KEY_VALUE";
    case ::stellar::OperationType::CREATE_MANAGE_LIMITS_REQUEST:
      return "CREATE_MANAGE_LIMITS_REQUEST";
    case ::stellar::OperationType::MANAGE_CONTRACT_REQUEST:
      return "MANAGE_CONTRACT_REQUEST";
    case ::stellar::OperationType::MANAGE_CONTRACT:
      return "MANAGE_CONTRACT";
    case ::stellar::OperationType::CANCEL_SALE_REQUEST:
      return "CANCEL_SALE_REQUEST";
    case ::stellar::OperationType::PAYOUT:
      return "PAYOUT";
    case ::stellar::OperationType::MANAGE_ACCOUNT_ROLE:
      return "MANAGE_ACCOUNT_ROLE";
    case ::stellar::OperationType::MANAGE_ACCOUNT_RULE:
      return "MANAGE_ACCOUNT_RULE";
    case ::stellar::OperationType::CREATE_ASWAP_BID_REQUEST:
      return "CREATE_ASWAP_BID_REQUEST";
    case ::stellar::OperationType::CANCEL_ASWAP_BID:
      return "CANCEL_ASWAP_BID";
    case ::stellar::OperationType::CREATE_ASWAP_REQUEST:
      return "CREATE_ASWAP_REQUEST";
    case ::stellar::OperationType::MANAGE_SIGNER:
      return "MANAGE_SIGNER";
    case ::stellar::OperationType::MANAGE_SIGNER_ROLE:
      return "MANAGE_SIGNER_ROLE";
    case ::stellar::OperationType::MANAGE_SIGNER_RULE:
      return "MANAGE_SIGNER_RULE";
    case ::stellar::OperationType::STAMP:
      return "STAMP";
    case ::stellar::OperationType::LICENSE:
      return "LICENSE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::OperationType::CREATE_ACCOUNT,
      (int32_t)::stellar::OperationType::CREATE_ISSUANCE_REQUEST,
      (int32_t)::stellar::OperationType::SET_FEES,
      (int32_t)::stellar::OperationType::CREATE_WITHDRAWAL_REQUEST,
      (int32_t)::stellar::OperationType::MANAGE_BALANCE,
      (int32_t)::stellar::OperationType::MANAGE_ASSET,
      (int32_t)::stellar::OperationType::CREATE_PREISSUANCE_REQUEST,
      (int32_t)::stellar::OperationType::MANAGE_LIMITS,
      (int32_t)::stellar::OperationType::MANAGE_ASSET_PAIR,
      (int32_t)::stellar::OperationType::MANAGE_OFFER,
      (int32_t)::stellar::OperationType::MANAGE_INVOICE_REQUEST,
      (int32_t)::stellar::OperationType::REVIEW_REQUEST,
      (int32_t)::stellar::OperationType::CREATE_SALE_REQUEST,
      (int32_t)::stellar::OperationType::CHECK_SALE_STATE,
      (int32_t)::stellar::OperationType::CREATE_AML_ALERT,
      (int32_t)::stellar::OperationType::CREATE_CHANGE_ROLE_REQUEST,
      (int32_t)::stellar::OperationType::PAYMENT,
      (int32_t)::stellar::OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY,
      (int32_t)::stellar::OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID,
      (int32_t)::stellar::OperationType::MANAGE_SALE,
      (int32_t)::stellar::OperationType::MANAGE_KEY_VALUE,
      (int32_t)::stellar::OperationType::CREATE_MANAGE_LIMITS_REQUEST,
      (int32_t)::stellar::OperationType::MANAGE_CONTRACT_REQUEST,
      (int32_t)::stellar::OperationType::MANAGE_CONTRACT,
      (int32_t)::stellar::OperationType::CANCEL_SALE_REQUEST,
      (int32_t)::stellar::OperationType::PAYOUT,
      (int32_t)::stellar::OperationType::MANAGE_ACCOUNT_ROLE,
      (int32_t)::stellar::OperationType::MANAGE_ACCOUNT_RULE,
      (int32_t)::stellar::OperationType::CREATE_ASWAP_BID_REQUEST,
      (int32_t)::stellar::OperationType::CANCEL_ASWAP_BID,
      (int32_t)::stellar::OperationType::CREATE_ASWAP_REQUEST,
      (int32_t)::stellar::OperationType::MANAGE_SIGNER,
      (int32_t)::stellar::OperationType::MANAGE_SIGNER_ROLE,
      (int32_t)::stellar::OperationType::MANAGE_SIGNER_RULE,
      (int32_t)::stellar::OperationType::STAMP,
      (int32_t)::stellar::OperationType::LICENSE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct DecoratedSignature {
  SignatureHint hint{};
  Signature signature{};

  DecoratedSignature() = default;
  template<typename _hint_T,
           typename _signature_T,
           typename = typename
           std::enable_if<std::is_constructible<SignatureHint, _hint_T>::value
                          && std::is_constructible<Signature, _signature_T>::value
                         >::type>
  explicit DecoratedSignature(_hint_T &&_hint,
                              _signature_T &&_signature)
    : hint(std::forward<_hint_T>(_hint)),
      signature(std::forward<_signature_T>(_signature)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::DecoratedSignature>
  : xdr_struct_base<field_ptr<::stellar::DecoratedSignature,
                              decltype(::stellar::DecoratedSignature::hint),
                              &::stellar::DecoratedSignature::hint>,
                    field_ptr<::stellar::DecoratedSignature,
                              decltype(::stellar::DecoratedSignature::signature),
                              &::stellar::DecoratedSignature::signature>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::DecoratedSignature &obj) {
    archive(ar, obj.hint, "hint");
    archive(ar, obj.signature, "signature");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::DecoratedSignature &obj) {
    archive(ar, obj.hint, "hint");
    archive(ar, obj.signature, "signature");
    xdr::validate(obj);
  }
};
} namespace stellar {

}

#endif // !__XDR_STELLAR_TYPES_H_INCLUDED__
