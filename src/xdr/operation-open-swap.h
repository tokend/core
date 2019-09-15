// -*- C++ -*-
// Automatically generated from operation-open-swap.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_OPEN_SWAP_H_INCLUDED__
#define __XDR_OPERATION_OPEN_SWAP_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"
#include "xdr/operation-payment.h"

namespace stellar {

struct OpenSwapOp  : xdr::xdr_abstract {
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

  BalanceID sourceBalance{};
  uint64 amount{};
  _destination_t destination{};
  PaymentFeeData feeData{};
  longstring details{};
  Hash secretHash{};
  int64 lockTime{};
  EmptyExt ext{};

  OpenSwapOp() = default;
  template<typename _sourceBalance_T,
           typename _amount_T,
           typename _destination_T,
           typename _feeData_T,
           typename _details_T,
           typename _secretHash_T,
           typename _lockTime_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<BalanceID, _sourceBalance_T>::value
                          && std::is_constructible<uint64, _amount_T>::value
                          && std::is_constructible<_destination_t, _destination_T>::value
                          && std::is_constructible<PaymentFeeData, _feeData_T>::value
                          && std::is_constructible<longstring, _details_T>::value
                          && std::is_constructible<Hash, _secretHash_T>::value
                          && std::is_constructible<int64, _lockTime_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit OpenSwapOp(_sourceBalance_T &&_sourceBalance,
                      _amount_T &&_amount,
                      _destination_T &&_destination,
                      _feeData_T &&_feeData,
                      _details_T &&_details,
                      _secretHash_T &&_secretHash,
                      _lockTime_T &&_lockTime,
                      _ext_T &&_ext)
    : sourceBalance(std::forward<_sourceBalance_T>(_sourceBalance)),
      amount(std::forward<_amount_T>(_amount)),
      destination(std::forward<_destination_T>(_destination)),
      feeData(std::forward<_feeData_T>(_feeData)),
      details(std::forward<_details_T>(_details)),
      secretHash(std::forward<_secretHash_T>(_secretHash)),
      lockTime(std::forward<_lockTime_T>(_lockTime)),
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

enum class OpenSwapResultCode : std::int32_t {
  SUCCESS = 0,
  MALFORMED = -1,
  UNDERFUNDED = -2,
  DESTINATION_BALANCE_NOT_FOUND = -3,
  BALANCE_ASSETS_MISMATCHED = -4,
  SRC_BALANCE_NOT_FOUND = -5,
  NOT_ALLOWED_BY_ASSET_POLICY = -6,
  INVALID_DESTINATION_FEE = -7,
  INSUFFICIENT_FEE_AMOUNT = -8,
  AMOUNT_IS_LESS_THAN_DEST_FEE = -9,
  DESTINATION_ACCOUNT_NOT_FOUND = -10,
  INCORRECT_AMOUNT_PRECISION = -11,
  INVALID_DETAILS = -12,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::OpenSwapResultCode>
  : xdr_integral_base<::stellar::OpenSwapResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::OpenSwapResultCode val) {
    switch (val) {
    case ::stellar::OpenSwapResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::OpenSwapResultCode::MALFORMED:
      return "MALFORMED";
    case ::stellar::OpenSwapResultCode::UNDERFUNDED:
      return "UNDERFUNDED";
    case ::stellar::OpenSwapResultCode::DESTINATION_BALANCE_NOT_FOUND:
      return "DESTINATION_BALANCE_NOT_FOUND";
    case ::stellar::OpenSwapResultCode::BALANCE_ASSETS_MISMATCHED:
      return "BALANCE_ASSETS_MISMATCHED";
    case ::stellar::OpenSwapResultCode::SRC_BALANCE_NOT_FOUND:
      return "SRC_BALANCE_NOT_FOUND";
    case ::stellar::OpenSwapResultCode::NOT_ALLOWED_BY_ASSET_POLICY:
      return "NOT_ALLOWED_BY_ASSET_POLICY";
    case ::stellar::OpenSwapResultCode::INVALID_DESTINATION_FEE:
      return "INVALID_DESTINATION_FEE";
    case ::stellar::OpenSwapResultCode::INSUFFICIENT_FEE_AMOUNT:
      return "INSUFFICIENT_FEE_AMOUNT";
    case ::stellar::OpenSwapResultCode::AMOUNT_IS_LESS_THAN_DEST_FEE:
      return "AMOUNT_IS_LESS_THAN_DEST_FEE";
    case ::stellar::OpenSwapResultCode::DESTINATION_ACCOUNT_NOT_FOUND:
      return "DESTINATION_ACCOUNT_NOT_FOUND";
    case ::stellar::OpenSwapResultCode::INCORRECT_AMOUNT_PRECISION:
      return "INCORRECT_AMOUNT_PRECISION";
    case ::stellar::OpenSwapResultCode::INVALID_DETAILS:
      return "INVALID_DETAILS";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::OpenSwapResultCode::SUCCESS,
      (int32_t)::stellar::OpenSwapResultCode::MALFORMED,
      (int32_t)::stellar::OpenSwapResultCode::UNDERFUNDED,
      (int32_t)::stellar::OpenSwapResultCode::DESTINATION_BALANCE_NOT_FOUND,
      (int32_t)::stellar::OpenSwapResultCode::BALANCE_ASSETS_MISMATCHED,
      (int32_t)::stellar::OpenSwapResultCode::SRC_BALANCE_NOT_FOUND,
      (int32_t)::stellar::OpenSwapResultCode::NOT_ALLOWED_BY_ASSET_POLICY,
      (int32_t)::stellar::OpenSwapResultCode::INVALID_DESTINATION_FEE,
      (int32_t)::stellar::OpenSwapResultCode::INSUFFICIENT_FEE_AMOUNT,
      (int32_t)::stellar::OpenSwapResultCode::AMOUNT_IS_LESS_THAN_DEST_FEE,
      (int32_t)::stellar::OpenSwapResultCode::DESTINATION_ACCOUNT_NOT_FOUND,
      (int32_t)::stellar::OpenSwapResultCode::INCORRECT_AMOUNT_PRECISION,
      (int32_t)::stellar::OpenSwapResultCode::INVALID_DETAILS
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct OpenSwapSuccess  : xdr::xdr_abstract {
  uint64 swapID{};
  AccountID destination{};
  BalanceID destinationBalance{};
  AssetCode asset{};
  Fee actualSourceFee{};
  Fee actualDestinationFee{};
  EmptyExt ext{};

  OpenSwapSuccess() = default;
  template<typename _swapID_T,
           typename _destination_T,
           typename _destinationBalance_T,
           typename _asset_T,
           typename _actualSourceFee_T,
           typename _actualDestinationFee_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _swapID_T>::value
                          && std::is_constructible<AccountID, _destination_T>::value
                          && std::is_constructible<BalanceID, _destinationBalance_T>::value
                          && std::is_constructible<AssetCode, _asset_T>::value
                          && std::is_constructible<Fee, _actualSourceFee_T>::value
                          && std::is_constructible<Fee, _actualDestinationFee_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit OpenSwapSuccess(_swapID_T &&_swapID,
                           _destination_T &&_destination,
                           _destinationBalance_T &&_destinationBalance,
                           _asset_T &&_asset,
                           _actualSourceFee_T &&_actualSourceFee,
                           _actualDestinationFee_T &&_actualDestinationFee,
                           _ext_T &&_ext)
    : swapID(std::forward<_swapID_T>(_swapID)),
      destination(std::forward<_destination_T>(_destination)),
      destinationBalance(std::forward<_destinationBalance_T>(_destinationBalance)),
      asset(std::forward<_asset_T>(_asset)),
      actualSourceFee(std::forward<_actualSourceFee_T>(_actualSourceFee)),
      actualDestinationFee(std::forward<_actualDestinationFee_T>(_actualDestinationFee)),
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

struct OpenSwapResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<OpenSwapResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    OpenSwapSuccess success_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<OpenSwapResultCode> &_xdr_case_values() {
    static const std::vector<OpenSwapResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)OpenSwapResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)OpenSwapResultCode::SUCCESS:
      _f(&OpenSwapResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in OpenSwapResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~OpenSwapResult();
      code_ = which;switch (code_)
{
      case (int32_t)OpenSwapResultCode::SUCCESS:
new(&success_) OpenSwapSuccess{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit OpenSwapResult(OpenSwapResultCode which = OpenSwapResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)OpenSwapResultCode::SUCCESS:
new(&success_) OpenSwapSuccess{};
break;
    default:
      break;
}

  }
  OpenSwapResult(const OpenSwapResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)OpenSwapResultCode::SUCCESS:
new(&success_) OpenSwapSuccess(source.success_);
break;
    default:
      break;
}

  }
  OpenSwapResult(OpenSwapResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)OpenSwapResultCode::SUCCESS:
new(&success_) OpenSwapSuccess(std::move(source.success_));
break;
    default:
      break;
}

  }
  ~OpenSwapResult() {
switch (code_)
{
  case (int32_t)OpenSwapResultCode::SUCCESS:
success_.~OpenSwapSuccess();
break;
  default:
    break;
}
}

  OpenSwapResult &operator=(const OpenSwapResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)OpenSwapResultCode::SUCCESS:
success_ = source.success_;
break;
    default:
      break;
}
}
else {this->~OpenSwapResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)OpenSwapResultCode::SUCCESS:
new(&success_) OpenSwapSuccess(source.success_);
break;
    default:
      break;
}
}
    return *this;
  }
  OpenSwapResult &operator=(OpenSwapResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)OpenSwapResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    default:
      break;
}
}
else {this->~OpenSwapResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)OpenSwapResultCode::SUCCESS:
new(&success_) OpenSwapSuccess(std::move(source.success_));
break;
    default:
      break;
}
}
    return *this;
  }

  OpenSwapResultCode code() const { return OpenSwapResultCode(code_); }
  OpenSwapResult &code(OpenSwapResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  OpenSwapSuccess &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("OpenSwapResult: success accessed when not selected");
  }
  const OpenSwapSuccess &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("OpenSwapResult: success accessed when not selected");
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

#endif // !__XDR_OPERATION_OPEN_SWAP_H_INCLUDED__
