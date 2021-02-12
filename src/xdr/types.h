// -*- C++ -*-
// Automatically generated from types.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_TYPES_H_INCLUDED__
#define __XDR_TYPES_H_INCLUDED__ 1

#include <xdrpp/types.h>

namespace stellar {

enum class LedgerVersion : std::int32_t {
  EMPTY_VERSION = 0,
  CHECK_SET_FEE_ACCOUNT_EXISTING = 1,
  FIX_PAYMENT_STATS = 2,
  ADD_INVEST_FEE = 3,
  ADD_SALE_WHITELISTS = 4,
  ASSET_PAIR_RESTRICTIONS = 5,
  FIX_CHANGE_TO_NON_EXISTING_ROLE = 6,
  FIX_REVERSE_SALE_PAIR = 7,
  FIX_NOT_CHECKING_SET_TASKS_PERMISSIONS = 8,
  UNLIMITED_ADMIN_COUNT = 9,
  FIX_AML_ALERT_ERROR_CODES = 10,
  FIX_EXT_SYS_ACC_EXPIRATION_TIME = 11,
  FIX_CHANGE_ROLE_REJECT_TASKS = 12,
  FIX_SAME_ASSET_PAIR = 13,
  ATOMIC_SWAP_RETURNING = 14,
  FIX_INVEST_FEE = 15,
  ADD_ACC_SPECIFIC_RULE_RESOURCE = 16,
  FIX_SIGNER_CHANGES_REMOVE = 17,
  FIX_DEPOSIT_STATS = 18,
  FIX_CREATE_KYC_RECOVERY_PERMISSIONS = 19,
  CLEAR_DATABASE_CACHE = 20,
  FIX_ISSUANCE_REVIEWER = 21,
  MARK_ASSET_AS_DELETED = 22,
  FIX_MAX_SUBJECT_SIZE = 23,
  FIX_MOVEMENT_REVIEW = 24,
  FIX_SIGNATURE_CHECK = 25,
  FIX_AUTOREVIEW = 26,
  MOVEMENT_REQUESTS_DETAILS = 27,
  FIX_CRASH_CORE_WITH_PAYMENT = 28,
  FIX_INVEST_TO_IMMEDIATE_SALE = 29,
  FIX_PAYMENT_TASKS_WILDCARD_VALUE = 30,
  FIX_CHANGE_ROLE_REQUEST_REQUESTOR = 31,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LedgerVersion>
  : xdr_integral_base<::stellar::LedgerVersion, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::LedgerVersion val) {
    switch (val) {
    case ::stellar::LedgerVersion::EMPTY_VERSION:
      return "EMPTY_VERSION";
    case ::stellar::LedgerVersion::CHECK_SET_FEE_ACCOUNT_EXISTING:
      return "CHECK_SET_FEE_ACCOUNT_EXISTING";
    case ::stellar::LedgerVersion::FIX_PAYMENT_STATS:
      return "FIX_PAYMENT_STATS";
    case ::stellar::LedgerVersion::ADD_INVEST_FEE:
      return "ADD_INVEST_FEE";
    case ::stellar::LedgerVersion::ADD_SALE_WHITELISTS:
      return "ADD_SALE_WHITELISTS";
    case ::stellar::LedgerVersion::ASSET_PAIR_RESTRICTIONS:
      return "ASSET_PAIR_RESTRICTIONS";
    case ::stellar::LedgerVersion::FIX_CHANGE_TO_NON_EXISTING_ROLE:
      return "FIX_CHANGE_TO_NON_EXISTING_ROLE";
    case ::stellar::LedgerVersion::FIX_REVERSE_SALE_PAIR:
      return "FIX_REVERSE_SALE_PAIR";
    case ::stellar::LedgerVersion::FIX_NOT_CHECKING_SET_TASKS_PERMISSIONS:
      return "FIX_NOT_CHECKING_SET_TASKS_PERMISSIONS";
    case ::stellar::LedgerVersion::UNLIMITED_ADMIN_COUNT:
      return "UNLIMITED_ADMIN_COUNT";
    case ::stellar::LedgerVersion::FIX_AML_ALERT_ERROR_CODES:
      return "FIX_AML_ALERT_ERROR_CODES";
    case ::stellar::LedgerVersion::FIX_EXT_SYS_ACC_EXPIRATION_TIME:
      return "FIX_EXT_SYS_ACC_EXPIRATION_TIME";
    case ::stellar::LedgerVersion::FIX_CHANGE_ROLE_REJECT_TASKS:
      return "FIX_CHANGE_ROLE_REJECT_TASKS";
    case ::stellar::LedgerVersion::FIX_SAME_ASSET_PAIR:
      return "FIX_SAME_ASSET_PAIR";
    case ::stellar::LedgerVersion::ATOMIC_SWAP_RETURNING:
      return "ATOMIC_SWAP_RETURNING";
    case ::stellar::LedgerVersion::FIX_INVEST_FEE:
      return "FIX_INVEST_FEE";
    case ::stellar::LedgerVersion::ADD_ACC_SPECIFIC_RULE_RESOURCE:
      return "ADD_ACC_SPECIFIC_RULE_RESOURCE";
    case ::stellar::LedgerVersion::FIX_SIGNER_CHANGES_REMOVE:
      return "FIX_SIGNER_CHANGES_REMOVE";
    case ::stellar::LedgerVersion::FIX_DEPOSIT_STATS:
      return "FIX_DEPOSIT_STATS";
    case ::stellar::LedgerVersion::FIX_CREATE_KYC_RECOVERY_PERMISSIONS:
      return "FIX_CREATE_KYC_RECOVERY_PERMISSIONS";
    case ::stellar::LedgerVersion::CLEAR_DATABASE_CACHE:
      return "CLEAR_DATABASE_CACHE";
    case ::stellar::LedgerVersion::FIX_ISSUANCE_REVIEWER:
      return "FIX_ISSUANCE_REVIEWER";
    case ::stellar::LedgerVersion::MARK_ASSET_AS_DELETED:
      return "MARK_ASSET_AS_DELETED";
    case ::stellar::LedgerVersion::FIX_MAX_SUBJECT_SIZE:
      return "FIX_MAX_SUBJECT_SIZE";
    case ::stellar::LedgerVersion::FIX_MOVEMENT_REVIEW:
      return "FIX_MOVEMENT_REVIEW";
    case ::stellar::LedgerVersion::FIX_SIGNATURE_CHECK:
      return "FIX_SIGNATURE_CHECK";
    case ::stellar::LedgerVersion::FIX_AUTOREVIEW:
      return "FIX_AUTOREVIEW";
    case ::stellar::LedgerVersion::MOVEMENT_REQUESTS_DETAILS:
      return "MOVEMENT_REQUESTS_DETAILS";
    case ::stellar::LedgerVersion::FIX_CRASH_CORE_WITH_PAYMENT:
      return "FIX_CRASH_CORE_WITH_PAYMENT";
    case ::stellar::LedgerVersion::FIX_INVEST_TO_IMMEDIATE_SALE:
      return "FIX_INVEST_TO_IMMEDIATE_SALE";
    case ::stellar::LedgerVersion::FIX_PAYMENT_TASKS_WILDCARD_VALUE:
      return "FIX_PAYMENT_TASKS_WILDCARD_VALUE";
    case ::stellar::LedgerVersion::FIX_CHANGE_ROLE_REQUEST_REQUESTOR:
      return "FIX_CHANGE_ROLE_REQUEST_REQUESTOR";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::LedgerVersion::EMPTY_VERSION,
      (int32_t)::stellar::LedgerVersion::CHECK_SET_FEE_ACCOUNT_EXISTING,
      (int32_t)::stellar::LedgerVersion::FIX_PAYMENT_STATS,
      (int32_t)::stellar::LedgerVersion::ADD_INVEST_FEE,
      (int32_t)::stellar::LedgerVersion::ADD_SALE_WHITELISTS,
      (int32_t)::stellar::LedgerVersion::ASSET_PAIR_RESTRICTIONS,
      (int32_t)::stellar::LedgerVersion::FIX_CHANGE_TO_NON_EXISTING_ROLE,
      (int32_t)::stellar::LedgerVersion::FIX_REVERSE_SALE_PAIR,
      (int32_t)::stellar::LedgerVersion::FIX_NOT_CHECKING_SET_TASKS_PERMISSIONS,
      (int32_t)::stellar::LedgerVersion::UNLIMITED_ADMIN_COUNT,
      (int32_t)::stellar::LedgerVersion::FIX_AML_ALERT_ERROR_CODES,
      (int32_t)::stellar::LedgerVersion::FIX_EXT_SYS_ACC_EXPIRATION_TIME,
      (int32_t)::stellar::LedgerVersion::FIX_CHANGE_ROLE_REJECT_TASKS,
      (int32_t)::stellar::LedgerVersion::FIX_SAME_ASSET_PAIR,
      (int32_t)::stellar::LedgerVersion::ATOMIC_SWAP_RETURNING,
      (int32_t)::stellar::LedgerVersion::FIX_INVEST_FEE,
      (int32_t)::stellar::LedgerVersion::ADD_ACC_SPECIFIC_RULE_RESOURCE,
      (int32_t)::stellar::LedgerVersion::FIX_SIGNER_CHANGES_REMOVE,
      (int32_t)::stellar::LedgerVersion::FIX_DEPOSIT_STATS,
      (int32_t)::stellar::LedgerVersion::FIX_CREATE_KYC_RECOVERY_PERMISSIONS,
      (int32_t)::stellar::LedgerVersion::CLEAR_DATABASE_CACHE,
      (int32_t)::stellar::LedgerVersion::FIX_ISSUANCE_REVIEWER,
      (int32_t)::stellar::LedgerVersion::MARK_ASSET_AS_DELETED,
      (int32_t)::stellar::LedgerVersion::FIX_MAX_SUBJECT_SIZE,
      (int32_t)::stellar::LedgerVersion::FIX_MOVEMENT_REVIEW,
      (int32_t)::stellar::LedgerVersion::FIX_SIGNATURE_CHECK,
      (int32_t)::stellar::LedgerVersion::FIX_AUTOREVIEW,
      (int32_t)::stellar::LedgerVersion::MOVEMENT_REQUESTS_DETAILS,
      (int32_t)::stellar::LedgerVersion::FIX_CRASH_CORE_WITH_PAYMENT,
      (int32_t)::stellar::LedgerVersion::FIX_INVEST_TO_IMMEDIATE_SALE,
      (int32_t)::stellar::LedgerVersion::FIX_PAYMENT_TASKS_WILDCARD_VALUE,
      (int32_t)::stellar::LedgerVersion::FIX_CHANGE_ROLE_REQUEST_REQUESTOR
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct EmptyExt : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
private:
  _xdr_case_type v_;
  union {
  };

public:
  static constexpr const bool _xdr_has_default_case = false;
  static const std::vector<LedgerVersion> &_xdr_case_values() {
    static const std::vector<LedgerVersion> _xdr_disc_vec {
      LedgerVersion::EMPTY_VERSION
    };
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
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
      v_ = which;switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}

    }
    else
      v_ = which;
  }
  explicit EmptyExt(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
    switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
      break;
}

  }
  EmptyExt(const EmptyExt &source) : v_(source.v_) {
    switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
      break;
}

  }
  EmptyExt(EmptyExt &&source) : v_(source.v_) {
    switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
      break;
}

  }
  ~EmptyExt() {
switch (v_)
{
  case (int32_t)LedgerVersion::EMPTY_VERSION:
    break;
}
}

  EmptyExt &operator=(const EmptyExt &source) {
    if (v_ == source.v_)
{
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
      break;
}
}
else {this->~EmptyExt();
    v_ = source.v_;
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
      break;
}
}
    return *this;
  }
  EmptyExt &operator=(EmptyExt &&source) {
    if (v_ == source.v_)
{
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
      break;
}
}
else {this->~EmptyExt();
    v_ = std::move(source.v_);
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
      break;
}
}
    return *this;
  }

  LedgerVersion v() const { return LedgerVersion(v_); }
  EmptyExt &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }
bool
operator==(xdr::xdr_abstract const& other) const override;
bool
operator<(xdr::xdr_abstract const& other) const override;
private:
  bool
from_bytes(xdr::unmarshaler& u) override;
bool
to_bytes(xdr::marshaler& m) const override;
void
count_size(xdr::measurer& m) const override;

};

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
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
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
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
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

struct PublicKey : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<CryptoKeyType>::case_type;
private:
  _xdr_case_type type_;
  union {
    uint256 ed25519_;
  };

public:
  static constexpr const bool _xdr_has_default_case = false;
  static const std::vector<CryptoKeyType> &_xdr_case_values() {
    static const std::vector<CryptoKeyType> _xdr_disc_vec {
      CryptoKeyType::KEY_TYPE_ED25519
    };
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
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
      type_ = which;switch (type_)
{
      case (int32_t)CryptoKeyType::KEY_TYPE_ED25519:
new(&ed25519_) uint256{};
break;
}

    }
    else
      type_ = which;
  }
  explicit PublicKey(CryptoKeyType which = CryptoKeyType{}) : type_((int32_t)which) {
    switch (type_)
{
    case (int32_t)CryptoKeyType::KEY_TYPE_ED25519:
new(&ed25519_) uint256{};
break;
}

  }
  PublicKey(const PublicKey &source) : type_(source.type_) {
    switch (type_)
{
    case (int32_t)CryptoKeyType::KEY_TYPE_ED25519:
new(&ed25519_) uint256(source.ed25519_);
break;
}

  }
  PublicKey(PublicKey &&source) : type_(source.type_) {
    switch (type_)
{
    case (int32_t)CryptoKeyType::KEY_TYPE_ED25519:
new(&ed25519_) uint256(std::move(source.ed25519_));
break;
}

  }
  ~PublicKey() {
switch (type_)
{
  case (int32_t)CryptoKeyType::KEY_TYPE_ED25519:
ed25519_.~uint256();
break;
}
}

  PublicKey &operator=(const PublicKey &source) {
    if (type_ == source.type_)
{
switch (type_)
{
    case (int32_t)CryptoKeyType::KEY_TYPE_ED25519:
ed25519_ = source.ed25519_;
break;
}
}
else {this->~PublicKey();
    type_ = source.type_;
switch (type_)
{
    case (int32_t)CryptoKeyType::KEY_TYPE_ED25519:
new(&ed25519_) uint256(source.ed25519_);
break;
}
}
    return *this;
  }
  PublicKey &operator=(PublicKey &&source) {
    if (type_ == source.type_)
{
switch (type_)
{
    case (int32_t)CryptoKeyType::KEY_TYPE_ED25519:
ed25519_ = std::move(source.ed25519_);
break;
}
}
else {this->~PublicKey();
    type_ = std::move(source.type_);
switch (type_)
{
    case (int32_t)CryptoKeyType::KEY_TYPE_ED25519:
new(&ed25519_) uint256(std::move(source.ed25519_));
break;
}
}
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
  }bool
operator==(xdr::xdr_abstract const& other) const override;
bool
operator<(xdr::xdr_abstract const& other) const override;
private:
  bool
from_bytes(xdr::unmarshaler& u) override;
bool
to_bytes(xdr::marshaler& m) const override;
void
count_size(xdr::measurer& m) const override;

};

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
  ATOMIC_SWAP_ASK = 28,
  TRANSACTION = 29,
  SIGNER_RULE = 30,
  SIGNER_ROLE = 31,
  STAMP = 32,
  LICENSE = 33,
  POLL = 34,
  VOTE = 35,
  ACCOUNT_SPECIFIC_RULE = 36,
  INITIATE_KYC_RECOVERY = 37,
  SWAP = 38,
  DATA = 39,
  CUSTOM = 40,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LedgerEntryType>
  : xdr_integral_base<::stellar::LedgerEntryType, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
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
    case ::stellar::LedgerEntryType::ATOMIC_SWAP_ASK:
      return "ATOMIC_SWAP_ASK";
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
    case ::stellar::LedgerEntryType::POLL:
      return "POLL";
    case ::stellar::LedgerEntryType::VOTE:
      return "VOTE";
    case ::stellar::LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
      return "ACCOUNT_SPECIFIC_RULE";
    case ::stellar::LedgerEntryType::INITIATE_KYC_RECOVERY:
      return "INITIATE_KYC_RECOVERY";
    case ::stellar::LedgerEntryType::SWAP:
      return "SWAP";
    case ::stellar::LedgerEntryType::DATA:
      return "DATA";
    case ::stellar::LedgerEntryType::CUSTOM:
      return "CUSTOM";
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
      (int32_t)::stellar::LedgerEntryType::ATOMIC_SWAP_ASK,
      (int32_t)::stellar::LedgerEntryType::TRANSACTION,
      (int32_t)::stellar::LedgerEntryType::SIGNER_RULE,
      (int32_t)::stellar::LedgerEntryType::SIGNER_ROLE,
      (int32_t)::stellar::LedgerEntryType::STAMP,
      (int32_t)::stellar::LedgerEntryType::LICENSE,
      (int32_t)::stellar::LedgerEntryType::POLL,
      (int32_t)::stellar::LedgerEntryType::VOTE,
      (int32_t)::stellar::LedgerEntryType::ACCOUNT_SPECIFIC_RULE,
      (int32_t)::stellar::LedgerEntryType::INITIATE_KYC_RECOVERY,
      (int32_t)::stellar::LedgerEntryType::SWAP,
      (int32_t)::stellar::LedgerEntryType::DATA,
      (int32_t)::stellar::LedgerEntryType::CUSTOM
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

using Signature = xdr::opaque_vec<64>;
using SignatureHint = xdr::opaque_array<4>;
using NodeID = PublicKey;

struct Curve25519Secret  : xdr::xdr_abstract {
  xdr::opaque_array<32> key{};

  Curve25519Secret() = default;
  template<typename _key_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::opaque_array<32>, _key_T>::value
                         >::type>
  explicit Curve25519Secret(_key_T &&_key)
    : key(std::forward<_key_T>(_key)) {}
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

struct Curve25519Public  : xdr::xdr_abstract {
  xdr::opaque_array<32> key{};

  Curve25519Public() = default;
  template<typename _key_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::opaque_array<32>, _key_T>::value
                         >::type>
  explicit Curve25519Public(_key_T &&_key)
    : key(std::forward<_key_T>(_key)) {}
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

struct HmacSha256Key  : xdr::xdr_abstract {
  xdr::opaque_array<32> key{};

  HmacSha256Key() = default;
  template<typename _key_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::opaque_array<32>, _key_T>::value
                         >::type>
  explicit HmacSha256Key(_key_T &&_key)
    : key(std::forward<_key_T>(_key)) {}
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

struct HmacSha256Mac  : xdr::xdr_abstract {
  xdr::opaque_array<32> mac{};

  HmacSha256Mac() = default;
  template<typename _mac_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::opaque_array<32>, _mac_T>::value
                         >::type>
  explicit HmacSha256Mac(_mac_T &&_mac)
    : mac(std::forward<_mac_T>(_mac)) {}
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

struct Fee  : xdr::xdr_abstract {
  struct _ext_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
  private:
    _xdr_case_type v_;
    union {
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<LedgerVersion> &_xdr_case_values() {
      static const std::vector<LedgerVersion> _xdr_disc_vec {
        LedgerVersion::EMPTY_VERSION
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
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
        v_ = which;switch (v_)
{
        case (int32_t)LedgerVersion::EMPTY_VERSION:
          break;
}

      }
      else
        v_ = which;
    }
    explicit _ext_t(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}

    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}

    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}

    }
    ~_ext_t() {
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
      break;
}
}

    _ext_t &operator=(const _ext_t &source) {
      if (v_ == source.v_)
{
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
else {this->~_ext_t();
      v_ = source.v_;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
      return *this;
    }
    _ext_t &operator=(_ext_t &&source) {
      if (v_ == source.v_)
{
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
else {this->~_ext_t();
      v_ = std::move(source.v_);
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
      return *this;
    }

    LedgerVersion v() const { return LedgerVersion(v_); }
    _ext_t &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }
bool
operator==(xdr::xdr_abstract const& other) const override;
bool
operator<(xdr::xdr_abstract const& other) const override;
private:
    bool
from_bytes(xdr::unmarshaler& u) override;
bool
to_bytes(xdr::marshaler& m) const override;
void
count_size(xdr::measurer& m) const override;

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
  CREATE_ATOMIC_SWAP_ASK_REQUEST = 35,
  CANCEL_ATOMIC_SWAP_ASK = 36,
  CREATE_ATOMIC_SWAP_BID_REQUEST = 37,
  MANAGE_SIGNER = 38,
  MANAGE_SIGNER_ROLE = 39,
  MANAGE_SIGNER_RULE = 40,
  STAMP = 41,
  LICENSE = 42,
  MANAGE_CREATE_POLL_REQUEST = 43,
  MANAGE_POLL = 44,
  MANAGE_VOTE = 45,
  MANAGE_ACCOUNT_SPECIFIC_RULE = 46,
  CANCEL_CHANGE_ROLE_REQUEST = 47,
  INITIATE_KYC_RECOVERY = 48,
  CREATE_KYC_RECOVERY_REQUEST = 49,
  REMOVE_ASSET_PAIR = 50,
  CREATE_MANAGE_OFFER_REQUEST = 51,
  CREATE_PAYMENT_REQUEST = 52,
  REMOVE_ASSET = 53,
  OPEN_SWAP = 54,
  CLOSE_SWAP = 55,
  CREATE_REDEMPTION_REQUEST = 56,
  CREATE_DATA = 57,
  UPDATE_DATA = 58,
  REMOVE_DATA = 59,
  CREATE_DATA_CREATION_REQUEST = 60,
  CANCEL_DATA_CREATION_REQUEST = 61,
  CREATE_DATA_UPDATE_REQUEST = 62,
  CREATE_DATA_REMOVE_REQUEST = 63,
  CANCEL_DATA_UPDATE_REQUEST = 64,
  CANCEL_DATA_REMOVE_REQUEST = 65,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::OperationType>
  : xdr_integral_base<::stellar::OperationType, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
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
    case ::stellar::OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST:
      return "CREATE_ATOMIC_SWAP_ASK_REQUEST";
    case ::stellar::OperationType::CANCEL_ATOMIC_SWAP_ASK:
      return "CANCEL_ATOMIC_SWAP_ASK";
    case ::stellar::OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST:
      return "CREATE_ATOMIC_SWAP_BID_REQUEST";
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
    case ::stellar::OperationType::MANAGE_CREATE_POLL_REQUEST:
      return "MANAGE_CREATE_POLL_REQUEST";
    case ::stellar::OperationType::MANAGE_POLL:
      return "MANAGE_POLL";
    case ::stellar::OperationType::MANAGE_VOTE:
      return "MANAGE_VOTE";
    case ::stellar::OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE:
      return "MANAGE_ACCOUNT_SPECIFIC_RULE";
    case ::stellar::OperationType::CANCEL_CHANGE_ROLE_REQUEST:
      return "CANCEL_CHANGE_ROLE_REQUEST";
    case ::stellar::OperationType::INITIATE_KYC_RECOVERY:
      return "INITIATE_KYC_RECOVERY";
    case ::stellar::OperationType::CREATE_KYC_RECOVERY_REQUEST:
      return "CREATE_KYC_RECOVERY_REQUEST";
    case ::stellar::OperationType::REMOVE_ASSET_PAIR:
      return "REMOVE_ASSET_PAIR";
    case ::stellar::OperationType::CREATE_MANAGE_OFFER_REQUEST:
      return "CREATE_MANAGE_OFFER_REQUEST";
    case ::stellar::OperationType::CREATE_PAYMENT_REQUEST:
      return "CREATE_PAYMENT_REQUEST";
    case ::stellar::OperationType::REMOVE_ASSET:
      return "REMOVE_ASSET";
    case ::stellar::OperationType::OPEN_SWAP:
      return "OPEN_SWAP";
    case ::stellar::OperationType::CLOSE_SWAP:
      return "CLOSE_SWAP";
    case ::stellar::OperationType::CREATE_REDEMPTION_REQUEST:
      return "CREATE_REDEMPTION_REQUEST";
    case ::stellar::OperationType::CREATE_DATA:
      return "CREATE_DATA";
    case ::stellar::OperationType::UPDATE_DATA:
      return "UPDATE_DATA";
    case ::stellar::OperationType::REMOVE_DATA:
      return "REMOVE_DATA";
    case ::stellar::OperationType::CREATE_DATA_CREATION_REQUEST:
      return "CREATE_DATA_CREATION_REQUEST";
    case ::stellar::OperationType::CANCEL_DATA_CREATION_REQUEST:
      return "CANCEL_DATA_CREATION_REQUEST";
    case ::stellar::OperationType::CREATE_DATA_UPDATE_REQUEST:
      return "CREATE_DATA_UPDATE_REQUEST";
    case ::stellar::OperationType::CREATE_DATA_REMOVE_REQUEST:
      return "CREATE_DATA_REMOVE_REQUEST";
    case ::stellar::OperationType::CANCEL_DATA_UPDATE_REQUEST:
      return "CANCEL_DATA_UPDATE_REQUEST";
    case ::stellar::OperationType::CANCEL_DATA_REMOVE_REQUEST:
      return "CANCEL_DATA_REMOVE_REQUEST";
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
      (int32_t)::stellar::OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST,
      (int32_t)::stellar::OperationType::CANCEL_ATOMIC_SWAP_ASK,
      (int32_t)::stellar::OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST,
      (int32_t)::stellar::OperationType::MANAGE_SIGNER,
      (int32_t)::stellar::OperationType::MANAGE_SIGNER_ROLE,
      (int32_t)::stellar::OperationType::MANAGE_SIGNER_RULE,
      (int32_t)::stellar::OperationType::STAMP,
      (int32_t)::stellar::OperationType::LICENSE,
      (int32_t)::stellar::OperationType::MANAGE_CREATE_POLL_REQUEST,
      (int32_t)::stellar::OperationType::MANAGE_POLL,
      (int32_t)::stellar::OperationType::MANAGE_VOTE,
      (int32_t)::stellar::OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE,
      (int32_t)::stellar::OperationType::CANCEL_CHANGE_ROLE_REQUEST,
      (int32_t)::stellar::OperationType::INITIATE_KYC_RECOVERY,
      (int32_t)::stellar::OperationType::CREATE_KYC_RECOVERY_REQUEST,
      (int32_t)::stellar::OperationType::REMOVE_ASSET_PAIR,
      (int32_t)::stellar::OperationType::CREATE_MANAGE_OFFER_REQUEST,
      (int32_t)::stellar::OperationType::CREATE_PAYMENT_REQUEST,
      (int32_t)::stellar::OperationType::REMOVE_ASSET,
      (int32_t)::stellar::OperationType::OPEN_SWAP,
      (int32_t)::stellar::OperationType::CLOSE_SWAP,
      (int32_t)::stellar::OperationType::CREATE_REDEMPTION_REQUEST,
      (int32_t)::stellar::OperationType::CREATE_DATA,
      (int32_t)::stellar::OperationType::UPDATE_DATA,
      (int32_t)::stellar::OperationType::REMOVE_DATA,
      (int32_t)::stellar::OperationType::CREATE_DATA_CREATION_REQUEST,
      (int32_t)::stellar::OperationType::CANCEL_DATA_CREATION_REQUEST,
      (int32_t)::stellar::OperationType::CREATE_DATA_UPDATE_REQUEST,
      (int32_t)::stellar::OperationType::CREATE_DATA_REMOVE_REQUEST,
      (int32_t)::stellar::OperationType::CANCEL_DATA_UPDATE_REQUEST,
      (int32_t)::stellar::OperationType::CANCEL_DATA_REMOVE_REQUEST
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct DecoratedSignature  : xdr::xdr_abstract {
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

#endif // !__XDR_TYPES_H_INCLUDED__
