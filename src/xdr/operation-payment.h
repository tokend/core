// -*- C++ -*-
// Automatically generated from operation-payment.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_PAYMENT_H_INCLUDED__
#define __XDR_OPERATION_PAYMENT_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"

namespace stellar {

struct PaymentFeeData  : xdr::xdr_abstract {
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

  Fee sourceFee{};
  Fee destinationFee{};
  bool sourcePaysForDest{};
  _ext_t ext{};

  PaymentFeeData() = default;
  template<typename _sourceFee_T,
           typename _destinationFee_T,
           typename _sourcePaysForDest_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<Fee, _sourceFee_T>::value
                          && std::is_constructible<Fee, _destinationFee_T>::value
                          && std::is_constructible<bool, _sourcePaysForDest_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit PaymentFeeData(_sourceFee_T &&_sourceFee,
                          _destinationFee_T &&_destinationFee,
                          _sourcePaysForDest_T &&_sourcePaysForDest,
                          _ext_T &&_ext)
    : sourceFee(std::forward<_sourceFee_T>(_sourceFee)),
      destinationFee(std::forward<_destinationFee_T>(_destinationFee)),
      sourcePaysForDest(std::forward<_sourcePaysForDest_T>(_sourcePaysForDest)),
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

enum class PaymentDestinationType : std::int32_t {
  ACCOUNT = 0,
  BALANCE = 1,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::PaymentDestinationType>
  : xdr_integral_base<::stellar::PaymentDestinationType, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::PaymentDestinationType val) {
    switch (val) {
    case ::stellar::PaymentDestinationType::ACCOUNT:
      return "ACCOUNT";
    case ::stellar::PaymentDestinationType::BALANCE:
      return "BALANCE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::PaymentDestinationType::ACCOUNT,
      (int32_t)::stellar::PaymentDestinationType::BALANCE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct PaymentOp  : xdr::xdr_abstract {
  struct _destination_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<PaymentDestinationType>::case_type;
  private:
    _xdr_case_type type_;
    union {
      AccountID accountID_;
      BalanceID balanceID_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<PaymentDestinationType> &_xdr_case_values() {
      static const std::vector<PaymentDestinationType> _xdr_disc_vec {
        PaymentDestinationType::ACCOUNT,
        PaymentDestinationType::BALANCE
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)PaymentDestinationType::ACCOUNT ? 1
        : which == (int32_t)PaymentDestinationType::BALANCE ? 2
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)PaymentDestinationType::ACCOUNT:
        _f(&_destination_t::accountID_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)PaymentDestinationType::BALANCE:
        _f(&_destination_t::balanceID_, std::forward<_A>(_a)...);
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return type_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of type in _destination_t");
      if (fnum != _xdr_field_number(type_)) {
        this->~_destination_t();
        type_ = which;switch (type_)
{
        case (int32_t)PaymentDestinationType::ACCOUNT:
new(&accountID_) AccountID{};
break;
        case (int32_t)PaymentDestinationType::BALANCE:
new(&balanceID_) BalanceID{};
break;
}

      }
      else
        type_ = which;
    }
    explicit _destination_t(PaymentDestinationType which = PaymentDestinationType{}) : type_((int32_t)which) {
      switch (type_)
{
      case (int32_t)PaymentDestinationType::ACCOUNT:
new(&accountID_) AccountID{};
break;
      case (int32_t)PaymentDestinationType::BALANCE:
new(&balanceID_) BalanceID{};
break;
}

    }
    _destination_t(const _destination_t &source) : type_(source.type_) {
      switch (type_)
{
      case (int32_t)PaymentDestinationType::ACCOUNT:
new(&accountID_) AccountID(source.accountID_);
break;
      case (int32_t)PaymentDestinationType::BALANCE:
new(&balanceID_) BalanceID(source.balanceID_);
break;
}

    }
    _destination_t(_destination_t &&source) : type_(source.type_) {
      switch (type_)
{
      case (int32_t)PaymentDestinationType::ACCOUNT:
new(&accountID_) AccountID(std::move(source.accountID_));
break;
      case (int32_t)PaymentDestinationType::BALANCE:
new(&balanceID_) BalanceID(std::move(source.balanceID_));
break;
}

    }
    ~_destination_t() {
switch (type_)
{
    case (int32_t)PaymentDestinationType::ACCOUNT:
accountID_.~AccountID();
break;
    case (int32_t)PaymentDestinationType::BALANCE:
balanceID_.~BalanceID();
break;
}
}

    _destination_t &operator=(const _destination_t &source) {
      if (type_ == source.type_)
{
switch (type_)
{
      case (int32_t)PaymentDestinationType::ACCOUNT:
accountID_ = source.accountID_;
break;
      case (int32_t)PaymentDestinationType::BALANCE:
balanceID_ = source.balanceID_;
break;
}
}
else {this->~_destination_t();
      type_ = source.type_;
switch (type_)
{
      case (int32_t)PaymentDestinationType::ACCOUNT:
new(&accountID_) AccountID(source.accountID_);
break;
      case (int32_t)PaymentDestinationType::BALANCE:
new(&balanceID_) BalanceID(source.balanceID_);
break;
}
}
      return *this;
    }
    _destination_t &operator=(_destination_t &&source) {
      if (type_ == source.type_)
{
switch (type_)
{
      case (int32_t)PaymentDestinationType::ACCOUNT:
accountID_ = std::move(source.accountID_);
break;
      case (int32_t)PaymentDestinationType::BALANCE:
balanceID_ = std::move(source.balanceID_);
break;
}
}
else {this->~_destination_t();
      type_ = std::move(source.type_);
switch (type_)
{
      case (int32_t)PaymentDestinationType::ACCOUNT:
new(&accountID_) AccountID(std::move(source.accountID_));
break;
      case (int32_t)PaymentDestinationType::BALANCE:
new(&balanceID_) BalanceID(std::move(source.balanceID_));
break;
}
}
      return *this;
    }

    PaymentDestinationType type() const { return PaymentDestinationType(type_); }
    _destination_t &type(PaymentDestinationType _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    AccountID &accountID() {
      if (_xdr_field_number(type_) == 1)
        return accountID_;
      throw xdr::xdr_wrong_union("_destination_t: accountID accessed when not selected");
    }
    const AccountID &accountID() const {
      if (_xdr_field_number(type_) == 1)
        return accountID_;
      throw xdr::xdr_wrong_union("_destination_t: accountID accessed when not selected");
    }
    BalanceID &balanceID() {
      if (_xdr_field_number(type_) == 2)
        return balanceID_;
      throw xdr::xdr_wrong_union("_destination_t: balanceID accessed when not selected");
    }
    const BalanceID &balanceID() const {
      if (_xdr_field_number(type_) == 2)
        return balanceID_;
      throw xdr::xdr_wrong_union("_destination_t: balanceID accessed when not selected");
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

  BalanceID sourceBalanceID{};
  _destination_t destination{};
  uint64 amount{};
  PaymentFeeData feeData{};
  longstring subject{};
  longstring reference{};
  _ext_t ext{};

  PaymentOp() = default;
  template<typename _sourceBalanceID_T,
           typename _destination_T,
           typename _amount_T,
           typename _feeData_T,
           typename _subject_T,
           typename _reference_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<BalanceID, _sourceBalanceID_T>::value
                          && std::is_constructible<_destination_t, _destination_T>::value
                          && std::is_constructible<uint64, _amount_T>::value
                          && std::is_constructible<PaymentFeeData, _feeData_T>::value
                          && std::is_constructible<longstring, _subject_T>::value
                          && std::is_constructible<longstring, _reference_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit PaymentOp(_sourceBalanceID_T &&_sourceBalanceID,
                     _destination_T &&_destination,
                     _amount_T &&_amount,
                     _feeData_T &&_feeData,
                     _subject_T &&_subject,
                     _reference_T &&_reference,
                     _ext_T &&_ext)
    : sourceBalanceID(std::forward<_sourceBalanceID_T>(_sourceBalanceID)),
      destination(std::forward<_destination_T>(_destination)),
      amount(std::forward<_amount_T>(_amount)),
      feeData(std::forward<_feeData_T>(_feeData)),
      subject(std::forward<_subject_T>(_subject)),
      reference(std::forward<_reference_T>(_reference)),
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

enum class PaymentResultCode : std::int32_t {
  SUCCESS = 0,
  MALFORMED = -1,
  UNDERFUNDED = -2,
  LINE_FULL = -3,
  DESTINATION_BALANCE_NOT_FOUND = -4,
  BALANCE_ASSETS_MISMATCHED = -5,
  SRC_BALANCE_NOT_FOUND = -6,
  REFERENCE_DUPLICATION = -7,
  STATS_OVERFLOW = -8,
  LIMITS_EXCEEDED = -9,
  NOT_ALLOWED_BY_ASSET_POLICY = -10,
  INVALID_DESTINATION_FEE = -11,
  INSUFFICIENT_FEE_AMOUNT = -12,
  PAYMENT_AMOUNT_IS_LESS_THAN_DEST_FEE = -13,
  DESTINATION_ACCOUNT_NOT_FOUND = -14,
  INCORRECT_AMOUNT_PRECISION = -15,
  TOO_MUCH_SIGNS = -16,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::PaymentResultCode>
  : xdr_integral_base<::stellar::PaymentResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::PaymentResultCode val) {
    switch (val) {
    case ::stellar::PaymentResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::PaymentResultCode::MALFORMED:
      return "MALFORMED";
    case ::stellar::PaymentResultCode::UNDERFUNDED:
      return "UNDERFUNDED";
    case ::stellar::PaymentResultCode::LINE_FULL:
      return "LINE_FULL";
    case ::stellar::PaymentResultCode::DESTINATION_BALANCE_NOT_FOUND:
      return "DESTINATION_BALANCE_NOT_FOUND";
    case ::stellar::PaymentResultCode::BALANCE_ASSETS_MISMATCHED:
      return "BALANCE_ASSETS_MISMATCHED";
    case ::stellar::PaymentResultCode::SRC_BALANCE_NOT_FOUND:
      return "SRC_BALANCE_NOT_FOUND";
    case ::stellar::PaymentResultCode::REFERENCE_DUPLICATION:
      return "REFERENCE_DUPLICATION";
    case ::stellar::PaymentResultCode::STATS_OVERFLOW:
      return "STATS_OVERFLOW";
    case ::stellar::PaymentResultCode::LIMITS_EXCEEDED:
      return "LIMITS_EXCEEDED";
    case ::stellar::PaymentResultCode::NOT_ALLOWED_BY_ASSET_POLICY:
      return "NOT_ALLOWED_BY_ASSET_POLICY";
    case ::stellar::PaymentResultCode::INVALID_DESTINATION_FEE:
      return "INVALID_DESTINATION_FEE";
    case ::stellar::PaymentResultCode::INSUFFICIENT_FEE_AMOUNT:
      return "INSUFFICIENT_FEE_AMOUNT";
    case ::stellar::PaymentResultCode::PAYMENT_AMOUNT_IS_LESS_THAN_DEST_FEE:
      return "PAYMENT_AMOUNT_IS_LESS_THAN_DEST_FEE";
    case ::stellar::PaymentResultCode::DESTINATION_ACCOUNT_NOT_FOUND:
      return "DESTINATION_ACCOUNT_NOT_FOUND";
    case ::stellar::PaymentResultCode::INCORRECT_AMOUNT_PRECISION:
      return "INCORRECT_AMOUNT_PRECISION";
    case ::stellar::PaymentResultCode::TOO_MUCH_SIGNS:
      return "TOO_MUCH_SIGNS";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::PaymentResultCode::SUCCESS,
      (int32_t)::stellar::PaymentResultCode::MALFORMED,
      (int32_t)::stellar::PaymentResultCode::UNDERFUNDED,
      (int32_t)::stellar::PaymentResultCode::LINE_FULL,
      (int32_t)::stellar::PaymentResultCode::DESTINATION_BALANCE_NOT_FOUND,
      (int32_t)::stellar::PaymentResultCode::BALANCE_ASSETS_MISMATCHED,
      (int32_t)::stellar::PaymentResultCode::SRC_BALANCE_NOT_FOUND,
      (int32_t)::stellar::PaymentResultCode::REFERENCE_DUPLICATION,
      (int32_t)::stellar::PaymentResultCode::STATS_OVERFLOW,
      (int32_t)::stellar::PaymentResultCode::LIMITS_EXCEEDED,
      (int32_t)::stellar::PaymentResultCode::NOT_ALLOWED_BY_ASSET_POLICY,
      (int32_t)::stellar::PaymentResultCode::INVALID_DESTINATION_FEE,
      (int32_t)::stellar::PaymentResultCode::INSUFFICIENT_FEE_AMOUNT,
      (int32_t)::stellar::PaymentResultCode::PAYMENT_AMOUNT_IS_LESS_THAN_DEST_FEE,
      (int32_t)::stellar::PaymentResultCode::DESTINATION_ACCOUNT_NOT_FOUND,
      (int32_t)::stellar::PaymentResultCode::INCORRECT_AMOUNT_PRECISION,
      (int32_t)::stellar::PaymentResultCode::TOO_MUCH_SIGNS
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct PaymentResponse  : xdr::xdr_abstract {
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

  AccountID destination{};
  BalanceID destinationBalanceID{};
  AssetCode asset{};
  uint64 sourceSentUniversal{};
  uint64 paymentID{};
  Fee actualSourcePaymentFee{};
  Fee actualDestinationPaymentFee{};
  _ext_t ext{};

  PaymentResponse() = default;
  template<typename _destination_T,
           typename _destinationBalanceID_T,
           typename _asset_T,
           typename _sourceSentUniversal_T,
           typename _paymentID_T,
           typename _actualSourcePaymentFee_T,
           typename _actualDestinationPaymentFee_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<AccountID, _destination_T>::value
                          && std::is_constructible<BalanceID, _destinationBalanceID_T>::value
                          && std::is_constructible<AssetCode, _asset_T>::value
                          && std::is_constructible<uint64, _sourceSentUniversal_T>::value
                          && std::is_constructible<uint64, _paymentID_T>::value
                          && std::is_constructible<Fee, _actualSourcePaymentFee_T>::value
                          && std::is_constructible<Fee, _actualDestinationPaymentFee_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit PaymentResponse(_destination_T &&_destination,
                           _destinationBalanceID_T &&_destinationBalanceID,
                           _asset_T &&_asset,
                           _sourceSentUniversal_T &&_sourceSentUniversal,
                           _paymentID_T &&_paymentID,
                           _actualSourcePaymentFee_T &&_actualSourcePaymentFee,
                           _actualDestinationPaymentFee_T &&_actualDestinationPaymentFee,
                           _ext_T &&_ext)
    : destination(std::forward<_destination_T>(_destination)),
      destinationBalanceID(std::forward<_destinationBalanceID_T>(_destinationBalanceID)),
      asset(std::forward<_asset_T>(_asset)),
      sourceSentUniversal(std::forward<_sourceSentUniversal_T>(_sourceSentUniversal)),
      paymentID(std::forward<_paymentID_T>(_paymentID)),
      actualSourcePaymentFee(std::forward<_actualSourcePaymentFee_T>(_actualSourcePaymentFee)),
      actualDestinationPaymentFee(std::forward<_actualDestinationPaymentFee_T>(_actualDestinationPaymentFee)),
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

struct PaymentResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<PaymentResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    PaymentResponse paymentResponse_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<PaymentResultCode> &_xdr_case_values() {
    static const std::vector<PaymentResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)PaymentResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)PaymentResultCode::SUCCESS:
      _f(&PaymentResult::paymentResponse_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in PaymentResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~PaymentResult();
      code_ = which;switch (code_)
{
      case (int32_t)PaymentResultCode::SUCCESS:
new(&paymentResponse_) PaymentResponse{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit PaymentResult(PaymentResultCode which = PaymentResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)PaymentResultCode::SUCCESS:
new(&paymentResponse_) PaymentResponse{};
break;
    default:
      break;
}

  }
  PaymentResult(const PaymentResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)PaymentResultCode::SUCCESS:
new(&paymentResponse_) PaymentResponse(source.paymentResponse_);
break;
    default:
      break;
}

  }
  PaymentResult(PaymentResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)PaymentResultCode::SUCCESS:
new(&paymentResponse_) PaymentResponse(std::move(source.paymentResponse_));
break;
    default:
      break;
}

  }
  ~PaymentResult() {
switch (code_)
{
  case (int32_t)PaymentResultCode::SUCCESS:
paymentResponse_.~PaymentResponse();
break;
  default:
    break;
}
}

  PaymentResult &operator=(const PaymentResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)PaymentResultCode::SUCCESS:
paymentResponse_ = source.paymentResponse_;
break;
    default:
      break;
}
}
else {this->~PaymentResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)PaymentResultCode::SUCCESS:
new(&paymentResponse_) PaymentResponse(source.paymentResponse_);
break;
    default:
      break;
}
}
    return *this;
  }
  PaymentResult &operator=(PaymentResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)PaymentResultCode::SUCCESS:
paymentResponse_ = std::move(source.paymentResponse_);
break;
    default:
      break;
}
}
else {this->~PaymentResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)PaymentResultCode::SUCCESS:
new(&paymentResponse_) PaymentResponse(std::move(source.paymentResponse_));
break;
    default:
      break;
}
}
    return *this;
  }

  PaymentResultCode code() const { return PaymentResultCode(code_); }
  PaymentResult &code(PaymentResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  PaymentResponse &paymentResponse() {
    if (_xdr_field_number(code_) == 1)
      return paymentResponse_;
    throw xdr::xdr_wrong_union("PaymentResult: paymentResponse accessed when not selected");
  }
  const PaymentResponse &paymentResponse() const {
    if (_xdr_field_number(code_) == 1)
      return paymentResponse_;
    throw xdr::xdr_wrong_union("PaymentResult: paymentResponse accessed when not selected");
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

}

#endif // !__XDR_OPERATION_PAYMENT_H_INCLUDED__
