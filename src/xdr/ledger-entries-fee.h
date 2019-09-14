// -*- C++ -*-
// Automatically generated from ledger-entries-fee.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_LEDGER_ENTRIES_FEE_H_INCLUDED__
#define __XDR_LEDGER_ENTRIES_FEE_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"

namespace stellar {

enum class FeeType : std::int32_t {
  PAYMENT_FEE = 0,
  OFFER_FEE = 1,
  WITHDRAWAL_FEE = 2,
  ISSUANCE_FEE = 3,
  INVEST_FEE = 4,
  CAPITAL_DEPLOYMENT_FEE = 5,
  OPERATION_FEE = 6,
  PAYOUT_FEE = 7,
  ATOMIC_SWAP_SALE_FEE = 8,
  ATOMIC_SWAP_PURCHASE_FEE = 9,
  SWAP_FEE = 10,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::FeeType>
  : xdr_integral_base<::stellar::FeeType, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::FeeType val) {
    switch (val) {
    case ::stellar::FeeType::PAYMENT_FEE:
      return "PAYMENT_FEE";
    case ::stellar::FeeType::OFFER_FEE:
      return "OFFER_FEE";
    case ::stellar::FeeType::WITHDRAWAL_FEE:
      return "WITHDRAWAL_FEE";
    case ::stellar::FeeType::ISSUANCE_FEE:
      return "ISSUANCE_FEE";
    case ::stellar::FeeType::INVEST_FEE:
      return "INVEST_FEE";
    case ::stellar::FeeType::CAPITAL_DEPLOYMENT_FEE:
      return "CAPITAL_DEPLOYMENT_FEE";
    case ::stellar::FeeType::OPERATION_FEE:
      return "OPERATION_FEE";
    case ::stellar::FeeType::PAYOUT_FEE:
      return "PAYOUT_FEE";
    case ::stellar::FeeType::ATOMIC_SWAP_SALE_FEE:
      return "ATOMIC_SWAP_SALE_FEE";
    case ::stellar::FeeType::ATOMIC_SWAP_PURCHASE_FEE:
      return "ATOMIC_SWAP_PURCHASE_FEE";
    case ::stellar::FeeType::SWAP_FEE:
      return "SWAP_FEE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::FeeType::PAYMENT_FEE,
      (int32_t)::stellar::FeeType::OFFER_FEE,
      (int32_t)::stellar::FeeType::WITHDRAWAL_FEE,
      (int32_t)::stellar::FeeType::ISSUANCE_FEE,
      (int32_t)::stellar::FeeType::INVEST_FEE,
      (int32_t)::stellar::FeeType::CAPITAL_DEPLOYMENT_FEE,
      (int32_t)::stellar::FeeType::OPERATION_FEE,
      (int32_t)::stellar::FeeType::PAYOUT_FEE,
      (int32_t)::stellar::FeeType::ATOMIC_SWAP_SALE_FEE,
      (int32_t)::stellar::FeeType::ATOMIC_SWAP_PURCHASE_FEE,
      (int32_t)::stellar::FeeType::SWAP_FEE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

enum class EmissionFeeType : std::int32_t {
  PRIMARY_MARKET = 1,
  SECONDARY_MARKET = 2,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::EmissionFeeType>
  : xdr_integral_base<::stellar::EmissionFeeType, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::EmissionFeeType val) {
    switch (val) {
    case ::stellar::EmissionFeeType::PRIMARY_MARKET:
      return "PRIMARY_MARKET";
    case ::stellar::EmissionFeeType::SECONDARY_MARKET:
      return "SECONDARY_MARKET";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::EmissionFeeType::PRIMARY_MARKET,
      (int32_t)::stellar::EmissionFeeType::SECONDARY_MARKET
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

enum class PaymentFeeType : std::int32_t {
  OUTGOING = 1,
  INCOMING = 2,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::PaymentFeeType>
  : xdr_integral_base<::stellar::PaymentFeeType, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::PaymentFeeType val) {
    switch (val) {
    case ::stellar::PaymentFeeType::OUTGOING:
      return "OUTGOING";
    case ::stellar::PaymentFeeType::INCOMING:
      return "INCOMING";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::PaymentFeeType::OUTGOING,
      (int32_t)::stellar::PaymentFeeType::INCOMING
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct FeeEntry  : xdr::xdr_abstract {
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

  FeeType feeType{};
  AssetCode asset{};
  int64 fixedFee{};
  int64 percentFee{};
  xdr::pointer<AccountID> accountID{};
  xdr::pointer<uint64> accountRole{};
  int64 subtype{};
  int64 lowerBound{};
  int64 upperBound{};
  Hash hash{};
  _ext_t ext{};

  FeeEntry() = default;
  template<typename _feeType_T,
           typename _asset_T,
           typename _fixedFee_T,
           typename _percentFee_T,
           typename _accountID_T,
           typename _accountRole_T,
           typename _subtype_T,
           typename _lowerBound_T,
           typename _upperBound_T,
           typename _hash_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<FeeType, _feeType_T>::value
                          && std::is_constructible<AssetCode, _asset_T>::value
                          && std::is_constructible<int64, _fixedFee_T>::value
                          && std::is_constructible<int64, _percentFee_T>::value
                          && std::is_constructible<xdr::pointer<AccountID>, _accountID_T>::value
                          && std::is_constructible<xdr::pointer<uint64>, _accountRole_T>::value
                          && std::is_constructible<int64, _subtype_T>::value
                          && std::is_constructible<int64, _lowerBound_T>::value
                          && std::is_constructible<int64, _upperBound_T>::value
                          && std::is_constructible<Hash, _hash_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit FeeEntry(_feeType_T &&_feeType,
                    _asset_T &&_asset,
                    _fixedFee_T &&_fixedFee,
                    _percentFee_T &&_percentFee,
                    _accountID_T &&_accountID,
                    _accountRole_T &&_accountRole,
                    _subtype_T &&_subtype,
                    _lowerBound_T &&_lowerBound,
                    _upperBound_T &&_upperBound,
                    _hash_T &&_hash,
                    _ext_T &&_ext)
    : feeType(std::forward<_feeType_T>(_feeType)),
      asset(std::forward<_asset_T>(_asset)),
      fixedFee(std::forward<_fixedFee_T>(_fixedFee)),
      percentFee(std::forward<_percentFee_T>(_percentFee)),
      accountID(std::forward<_accountID_T>(_accountID)),
      accountRole(std::forward<_accountRole_T>(_accountRole)),
      subtype(std::forward<_subtype_T>(_subtype)),
      lowerBound(std::forward<_lowerBound_T>(_lowerBound)),
      upperBound(std::forward<_upperBound_T>(_upperBound)),
      hash(std::forward<_hash_T>(_hash)),
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

#endif // !__XDR_LEDGER_ENTRIES_FEE_H_INCLUDED__
