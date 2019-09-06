// -*- C++ -*-
// Automatically generated from operation-payout.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_PAYOUT_H_INCLUDED__
#define __XDR_OPERATION_PAYOUT_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/ledger-entries.h"

namespace stellar {

struct PayoutOp  : xdr::xdr_abstract {
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

  AssetCode asset{};
  BalanceID sourceBalanceID{};
  uint64 maxPayoutAmount{};
  uint64 minPayoutAmount{};
  uint64 minAssetHolderAmount{};
  Fee fee{};
  _ext_t ext{};

  PayoutOp() = default;
  template<typename _asset_T,
           typename _sourceBalanceID_T,
           typename _maxPayoutAmount_T,
           typename _minPayoutAmount_T,
           typename _minAssetHolderAmount_T,
           typename _fee_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<AssetCode, _asset_T>::value
                          && std::is_constructible<BalanceID, _sourceBalanceID_T>::value
                          && std::is_constructible<uint64, _maxPayoutAmount_T>::value
                          && std::is_constructible<uint64, _minPayoutAmount_T>::value
                          && std::is_constructible<uint64, _minAssetHolderAmount_T>::value
                          && std::is_constructible<Fee, _fee_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit PayoutOp(_asset_T &&_asset,
                    _sourceBalanceID_T &&_sourceBalanceID,
                    _maxPayoutAmount_T &&_maxPayoutAmount,
                    _minPayoutAmount_T &&_minPayoutAmount,
                    _minAssetHolderAmount_T &&_minAssetHolderAmount,
                    _fee_T &&_fee,
                    _ext_T &&_ext)
    : asset(std::forward<_asset_T>(_asset)),
      sourceBalanceID(std::forward<_sourceBalanceID_T>(_sourceBalanceID)),
      maxPayoutAmount(std::forward<_maxPayoutAmount_T>(_maxPayoutAmount)),
      minPayoutAmount(std::forward<_minPayoutAmount_T>(_minPayoutAmount)),
      minAssetHolderAmount(std::forward<_minAssetHolderAmount_T>(_minAssetHolderAmount)),
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

enum class PayoutResultCode : std::int32_t {
  SUCCESS = 0,
  INVALID_AMOUNT = -1,
  INVALID_ASSET = -2,
  ASSET_NOT_FOUND = -3,
  ASSET_NOT_TRANSFERABLE = -4,
  BALANCE_NOT_FOUND = -5,
  INSUFFICIENT_FEE_AMOUNT = -6,
  FEE_EXCEEDS_ACTUAL_AMOUNT = -7,
  TOTAL_FEE_OVERFLOW = -8,
  UNDERFUNDED = -9,
  HOLDERS_NOT_FOUND = -10,
  MIN_AMOUNT_TOO_BIG = -11,
  LINE_FULL = -12,
  STATS_OVERFLOW = -13,
  LIMITS_EXCEEDED = -14,
  INCORRECT_PRECISION = -15,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::PayoutResultCode>
  : xdr_integral_base<::stellar::PayoutResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::PayoutResultCode val) {
    switch (val) {
    case ::stellar::PayoutResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::PayoutResultCode::INVALID_AMOUNT:
      return "INVALID_AMOUNT";
    case ::stellar::PayoutResultCode::INVALID_ASSET:
      return "INVALID_ASSET";
    case ::stellar::PayoutResultCode::ASSET_NOT_FOUND:
      return "ASSET_NOT_FOUND";
    case ::stellar::PayoutResultCode::ASSET_NOT_TRANSFERABLE:
      return "ASSET_NOT_TRANSFERABLE";
    case ::stellar::PayoutResultCode::BALANCE_NOT_FOUND:
      return "BALANCE_NOT_FOUND";
    case ::stellar::PayoutResultCode::INSUFFICIENT_FEE_AMOUNT:
      return "INSUFFICIENT_FEE_AMOUNT";
    case ::stellar::PayoutResultCode::FEE_EXCEEDS_ACTUAL_AMOUNT:
      return "FEE_EXCEEDS_ACTUAL_AMOUNT";
    case ::stellar::PayoutResultCode::TOTAL_FEE_OVERFLOW:
      return "TOTAL_FEE_OVERFLOW";
    case ::stellar::PayoutResultCode::UNDERFUNDED:
      return "UNDERFUNDED";
    case ::stellar::PayoutResultCode::HOLDERS_NOT_FOUND:
      return "HOLDERS_NOT_FOUND";
    case ::stellar::PayoutResultCode::MIN_AMOUNT_TOO_BIG:
      return "MIN_AMOUNT_TOO_BIG";
    case ::stellar::PayoutResultCode::LINE_FULL:
      return "LINE_FULL";
    case ::stellar::PayoutResultCode::STATS_OVERFLOW:
      return "STATS_OVERFLOW";
    case ::stellar::PayoutResultCode::LIMITS_EXCEEDED:
      return "LIMITS_EXCEEDED";
    case ::stellar::PayoutResultCode::INCORRECT_PRECISION:
      return "INCORRECT_PRECISION";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::PayoutResultCode::SUCCESS,
      (int32_t)::stellar::PayoutResultCode::INVALID_AMOUNT,
      (int32_t)::stellar::PayoutResultCode::INVALID_ASSET,
      (int32_t)::stellar::PayoutResultCode::ASSET_NOT_FOUND,
      (int32_t)::stellar::PayoutResultCode::ASSET_NOT_TRANSFERABLE,
      (int32_t)::stellar::PayoutResultCode::BALANCE_NOT_FOUND,
      (int32_t)::stellar::PayoutResultCode::INSUFFICIENT_FEE_AMOUNT,
      (int32_t)::stellar::PayoutResultCode::FEE_EXCEEDS_ACTUAL_AMOUNT,
      (int32_t)::stellar::PayoutResultCode::TOTAL_FEE_OVERFLOW,
      (int32_t)::stellar::PayoutResultCode::UNDERFUNDED,
      (int32_t)::stellar::PayoutResultCode::HOLDERS_NOT_FOUND,
      (int32_t)::stellar::PayoutResultCode::MIN_AMOUNT_TOO_BIG,
      (int32_t)::stellar::PayoutResultCode::LINE_FULL,
      (int32_t)::stellar::PayoutResultCode::STATS_OVERFLOW,
      (int32_t)::stellar::PayoutResultCode::LIMITS_EXCEEDED,
      (int32_t)::stellar::PayoutResultCode::INCORRECT_PRECISION
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct PayoutResponse  : xdr::xdr_abstract {
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

  AccountID receiverID{};
  BalanceID receiverBalanceID{};
  uint64 receivedAmount{};
  _ext_t ext{};

  PayoutResponse() = default;
  template<typename _receiverID_T,
           typename _receiverBalanceID_T,
           typename _receivedAmount_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<AccountID, _receiverID_T>::value
                          && std::is_constructible<BalanceID, _receiverBalanceID_T>::value
                          && std::is_constructible<uint64, _receivedAmount_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit PayoutResponse(_receiverID_T &&_receiverID,
                          _receiverBalanceID_T &&_receiverBalanceID,
                          _receivedAmount_T &&_receivedAmount,
                          _ext_T &&_ext)
    : receiverID(std::forward<_receiverID_T>(_receiverID)),
      receiverBalanceID(std::forward<_receiverBalanceID_T>(_receiverBalanceID)),
      receivedAmount(std::forward<_receivedAmount_T>(_receivedAmount)),
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

struct PayoutSuccessResult  : xdr::xdr_abstract {
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

  xdr::xvector<PayoutResponse> payoutResponses{};
  uint64 actualPayoutAmount{};
  Fee actualFee{};
  _ext_t ext{};

  PayoutSuccessResult() = default;
  template<typename _payoutResponses_T,
           typename _actualPayoutAmount_T,
           typename _actualFee_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xvector<PayoutResponse>, _payoutResponses_T>::value
                          && std::is_constructible<uint64, _actualPayoutAmount_T>::value
                          && std::is_constructible<Fee, _actualFee_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit PayoutSuccessResult(_payoutResponses_T &&_payoutResponses,
                               _actualPayoutAmount_T &&_actualPayoutAmount,
                               _actualFee_T &&_actualFee,
                               _ext_T &&_ext)
    : payoutResponses(std::forward<_payoutResponses_T>(_payoutResponses)),
      actualPayoutAmount(std::forward<_actualPayoutAmount_T>(_actualPayoutAmount)),
      actualFee(std::forward<_actualFee_T>(_actualFee)),
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

struct PayoutResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<PayoutResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    PayoutSuccessResult success_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<PayoutResultCode> &_xdr_case_values() {
    static const std::vector<PayoutResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)PayoutResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)PayoutResultCode::SUCCESS:
      _f(&PayoutResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in PayoutResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~PayoutResult();
      code_ = which;switch (code_)
{
      case (int32_t)PayoutResultCode::SUCCESS:
new(&success_) PayoutSuccessResult{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit PayoutResult(PayoutResultCode which = PayoutResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)PayoutResultCode::SUCCESS:
new(&success_) PayoutSuccessResult{};
break;
    default:
      break;
}

  }
  PayoutResult(const PayoutResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)PayoutResultCode::SUCCESS:
new(&success_) PayoutSuccessResult(source.success_);
break;
    default:
      break;
}

  }
  PayoutResult(PayoutResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)PayoutResultCode::SUCCESS:
new(&success_) PayoutSuccessResult(std::move(source.success_));
break;
    default:
      break;
}

  }
  ~PayoutResult() {
switch (code_)
{
  case (int32_t)PayoutResultCode::SUCCESS:
success_.~PayoutSuccessResult();
break;
  default:
    break;
}
}

  PayoutResult &operator=(const PayoutResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)PayoutResultCode::SUCCESS:
success_ = source.success_;
break;
    default:
      break;
}
}
else {this->~PayoutResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)PayoutResultCode::SUCCESS:
new(&success_) PayoutSuccessResult(source.success_);
break;
    default:
      break;
}
}
    return *this;
  }
  PayoutResult &operator=(PayoutResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)PayoutResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    default:
      break;
}
}
else {this->~PayoutResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)PayoutResultCode::SUCCESS:
new(&success_) PayoutSuccessResult(std::move(source.success_));
break;
    default:
      break;
}
}
    return *this;
  }

  PayoutResultCode code() const { return PayoutResultCode(code_); }
  PayoutResult &code(PayoutResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  PayoutSuccessResult &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("PayoutResult: success accessed when not selected");
  }
  const PayoutSuccessResult &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("PayoutResult: success accessed when not selected");
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

#endif // !__XDR_OPERATION_PAYOUT_H_INCLUDED__
