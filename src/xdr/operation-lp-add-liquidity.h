// -*- C++ -*-
// Automatically generated from operation-lp-add-liquidity.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_LP_ADD_LIQUIDITY_H_INCLUDED__
#define __XDR_OPERATION_LP_ADD_LIQUIDITY_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"
#include "xdr/operation-payment.h"

namespace stellar {

struct LPAddLiquidityOp  : xdr::xdr_abstract {
  BalanceID firstAssetBalanceID{};
  BalanceID secondAssetBalanceID{};
  uint64 firstAssetDesiredAmount{};
  uint64 secondAssetDesiredAmount{};
  uint64 firstAssetMinAmount{};
  uint64 secondAssetMinAmount{};
  EmptyExt ext{};

  LPAddLiquidityOp() = default;
  template<typename _firstAssetBalanceID_T,
           typename _secondAssetBalanceID_T,
           typename _firstAssetDesiredAmount_T,
           typename _secondAssetDesiredAmount_T,
           typename _firstAssetMinAmount_T,
           typename _secondAssetMinAmount_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<BalanceID, _firstAssetBalanceID_T>::value
                          && std::is_constructible<BalanceID, _secondAssetBalanceID_T>::value
                          && std::is_constructible<uint64, _firstAssetDesiredAmount_T>::value
                          && std::is_constructible<uint64, _secondAssetDesiredAmount_T>::value
                          && std::is_constructible<uint64, _firstAssetMinAmount_T>::value
                          && std::is_constructible<uint64, _secondAssetMinAmount_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit LPAddLiquidityOp(_firstAssetBalanceID_T &&_firstAssetBalanceID,
                            _secondAssetBalanceID_T &&_secondAssetBalanceID,
                            _firstAssetDesiredAmount_T &&_firstAssetDesiredAmount,
                            _secondAssetDesiredAmount_T &&_secondAssetDesiredAmount,
                            _firstAssetMinAmount_T &&_firstAssetMinAmount,
                            _secondAssetMinAmount_T &&_secondAssetMinAmount,
                            _ext_T &&_ext)
    : firstAssetBalanceID(std::forward<_firstAssetBalanceID_T>(_firstAssetBalanceID)),
      secondAssetBalanceID(std::forward<_secondAssetBalanceID_T>(_secondAssetBalanceID)),
      firstAssetDesiredAmount(std::forward<_firstAssetDesiredAmount_T>(_firstAssetDesiredAmount)),
      secondAssetDesiredAmount(std::forward<_secondAssetDesiredAmount_T>(_secondAssetDesiredAmount)),
      firstAssetMinAmount(std::forward<_firstAssetMinAmount_T>(_firstAssetMinAmount)),
      secondAssetMinAmount(std::forward<_secondAssetMinAmount_T>(_secondAssetMinAmount)),
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

enum class LPAddLiquidityResultCode : std::int32_t {
  SUCCESS = 0,
  SAME_ASSETS = -1,
  UNDERFUNDED = -2,
  BALANCE_OVERFLOW = -3,
  NOT_ALLOWED_BY_ASSET_POLICY = -4,
  SRC_BALANCE_NOT_FOUND = -5,
  INVALID_DESIRED_AMOUNT = -6,
  INVALID_MIN_AMOUNT = -7,
  INCORRECT_AMOUNT_PRECISION = -8,
  INSUFFICIENT_FIRST_ASSET_AMOUNT = -9,
  INSUFFICIENT_SECOND_ASSET_AMOUNT = -10,
  MIN_AMOUNT_BIGGER_THAN_DESIRED = -11,
  INSUFFICIENT_LIQUIDITY_PROVIDED = -12,
  SAME_BALANCES = -13,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LPAddLiquidityResultCode>
  : xdr_integral_base<::stellar::LPAddLiquidityResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::LPAddLiquidityResultCode val) {
    switch (val) {
    case ::stellar::LPAddLiquidityResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::LPAddLiquidityResultCode::SAME_ASSETS:
      return "SAME_ASSETS";
    case ::stellar::LPAddLiquidityResultCode::UNDERFUNDED:
      return "UNDERFUNDED";
    case ::stellar::LPAddLiquidityResultCode::BALANCE_OVERFLOW:
      return "BALANCE_OVERFLOW";
    case ::stellar::LPAddLiquidityResultCode::NOT_ALLOWED_BY_ASSET_POLICY:
      return "NOT_ALLOWED_BY_ASSET_POLICY";
    case ::stellar::LPAddLiquidityResultCode::SRC_BALANCE_NOT_FOUND:
      return "SRC_BALANCE_NOT_FOUND";
    case ::stellar::LPAddLiquidityResultCode::INVALID_DESIRED_AMOUNT:
      return "INVALID_DESIRED_AMOUNT";
    case ::stellar::LPAddLiquidityResultCode::INVALID_MIN_AMOUNT:
      return "INVALID_MIN_AMOUNT";
    case ::stellar::LPAddLiquidityResultCode::INCORRECT_AMOUNT_PRECISION:
      return "INCORRECT_AMOUNT_PRECISION";
    case ::stellar::LPAddLiquidityResultCode::INSUFFICIENT_FIRST_ASSET_AMOUNT:
      return "INSUFFICIENT_FIRST_ASSET_AMOUNT";
    case ::stellar::LPAddLiquidityResultCode::INSUFFICIENT_SECOND_ASSET_AMOUNT:
      return "INSUFFICIENT_SECOND_ASSET_AMOUNT";
    case ::stellar::LPAddLiquidityResultCode::MIN_AMOUNT_BIGGER_THAN_DESIRED:
      return "MIN_AMOUNT_BIGGER_THAN_DESIRED";
    case ::stellar::LPAddLiquidityResultCode::INSUFFICIENT_LIQUIDITY_PROVIDED:
      return "INSUFFICIENT_LIQUIDITY_PROVIDED";
    case ::stellar::LPAddLiquidityResultCode::SAME_BALANCES:
      return "SAME_BALANCES";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::LPAddLiquidityResultCode::SUCCESS,
      (int32_t)::stellar::LPAddLiquidityResultCode::SAME_ASSETS,
      (int32_t)::stellar::LPAddLiquidityResultCode::UNDERFUNDED,
      (int32_t)::stellar::LPAddLiquidityResultCode::BALANCE_OVERFLOW,
      (int32_t)::stellar::LPAddLiquidityResultCode::NOT_ALLOWED_BY_ASSET_POLICY,
      (int32_t)::stellar::LPAddLiquidityResultCode::SRC_BALANCE_NOT_FOUND,
      (int32_t)::stellar::LPAddLiquidityResultCode::INVALID_DESIRED_AMOUNT,
      (int32_t)::stellar::LPAddLiquidityResultCode::INVALID_MIN_AMOUNT,
      (int32_t)::stellar::LPAddLiquidityResultCode::INCORRECT_AMOUNT_PRECISION,
      (int32_t)::stellar::LPAddLiquidityResultCode::INSUFFICIENT_FIRST_ASSET_AMOUNT,
      (int32_t)::stellar::LPAddLiquidityResultCode::INSUFFICIENT_SECOND_ASSET_AMOUNT,
      (int32_t)::stellar::LPAddLiquidityResultCode::MIN_AMOUNT_BIGGER_THAN_DESIRED,
      (int32_t)::stellar::LPAddLiquidityResultCode::INSUFFICIENT_LIQUIDITY_PROVIDED,
      (int32_t)::stellar::LPAddLiquidityResultCode::SAME_BALANCES
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct LPAddLiquiditySuccess  : xdr::xdr_abstract {
  uint64 liquidityPoolID{};
  AccountID poolAccount{};
  BalanceID lpFirstAssetBalanceID{};
  BalanceID lpSecondAssetBalanceID{};
  BalanceID sourceFirstAssetBalanceID{};
  BalanceID sourceSecondAssetBalanceID{};
  uint64 firstAssetAmount{};
  uint64 secondAssetAmount{};
  BalanceID lpTokensBalanceID{};
  uint64 lpTokensAmount{};
  EmptyExt ext{};

  LPAddLiquiditySuccess() = default;
  template<typename _liquidityPoolID_T,
           typename _poolAccount_T,
           typename _lpFirstAssetBalanceID_T,
           typename _lpSecondAssetBalanceID_T,
           typename _sourceFirstAssetBalanceID_T,
           typename _sourceSecondAssetBalanceID_T,
           typename _firstAssetAmount_T,
           typename _secondAssetAmount_T,
           typename _lpTokensBalanceID_T,
           typename _lpTokensAmount_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _liquidityPoolID_T>::value
                          && std::is_constructible<AccountID, _poolAccount_T>::value
                          && std::is_constructible<BalanceID, _lpFirstAssetBalanceID_T>::value
                          && std::is_constructible<BalanceID, _lpSecondAssetBalanceID_T>::value
                          && std::is_constructible<BalanceID, _sourceFirstAssetBalanceID_T>::value
                          && std::is_constructible<BalanceID, _sourceSecondAssetBalanceID_T>::value
                          && std::is_constructible<uint64, _firstAssetAmount_T>::value
                          && std::is_constructible<uint64, _secondAssetAmount_T>::value
                          && std::is_constructible<BalanceID, _lpTokensBalanceID_T>::value
                          && std::is_constructible<uint64, _lpTokensAmount_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit LPAddLiquiditySuccess(_liquidityPoolID_T &&_liquidityPoolID,
                                 _poolAccount_T &&_poolAccount,
                                 _lpFirstAssetBalanceID_T &&_lpFirstAssetBalanceID,
                                 _lpSecondAssetBalanceID_T &&_lpSecondAssetBalanceID,
                                 _sourceFirstAssetBalanceID_T &&_sourceFirstAssetBalanceID,
                                 _sourceSecondAssetBalanceID_T &&_sourceSecondAssetBalanceID,
                                 _firstAssetAmount_T &&_firstAssetAmount,
                                 _secondAssetAmount_T &&_secondAssetAmount,
                                 _lpTokensBalanceID_T &&_lpTokensBalanceID,
                                 _lpTokensAmount_T &&_lpTokensAmount,
                                 _ext_T &&_ext)
    : liquidityPoolID(std::forward<_liquidityPoolID_T>(_liquidityPoolID)),
      poolAccount(std::forward<_poolAccount_T>(_poolAccount)),
      lpFirstAssetBalanceID(std::forward<_lpFirstAssetBalanceID_T>(_lpFirstAssetBalanceID)),
      lpSecondAssetBalanceID(std::forward<_lpSecondAssetBalanceID_T>(_lpSecondAssetBalanceID)),
      sourceFirstAssetBalanceID(std::forward<_sourceFirstAssetBalanceID_T>(_sourceFirstAssetBalanceID)),
      sourceSecondAssetBalanceID(std::forward<_sourceSecondAssetBalanceID_T>(_sourceSecondAssetBalanceID)),
      firstAssetAmount(std::forward<_firstAssetAmount_T>(_firstAssetAmount)),
      secondAssetAmount(std::forward<_secondAssetAmount_T>(_secondAssetAmount)),
      lpTokensBalanceID(std::forward<_lpTokensBalanceID_T>(_lpTokensBalanceID)),
      lpTokensAmount(std::forward<_lpTokensAmount_T>(_lpTokensAmount)),
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

struct LPAddLiquidityResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<LPAddLiquidityResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    LPAddLiquiditySuccess success_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<LPAddLiquidityResultCode> &_xdr_case_values() {
    static const std::vector<LPAddLiquidityResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)LPAddLiquidityResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)LPAddLiquidityResultCode::SUCCESS:
      _f(&LPAddLiquidityResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in LPAddLiquidityResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~LPAddLiquidityResult();
      code_ = which;switch (code_)
{
      case (int32_t)LPAddLiquidityResultCode::SUCCESS:
new(&success_) LPAddLiquiditySuccess{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit LPAddLiquidityResult(LPAddLiquidityResultCode which = LPAddLiquidityResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)LPAddLiquidityResultCode::SUCCESS:
new(&success_) LPAddLiquiditySuccess{};
break;
    default:
      break;
}

  }
  LPAddLiquidityResult(const LPAddLiquidityResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)LPAddLiquidityResultCode::SUCCESS:
new(&success_) LPAddLiquiditySuccess(source.success_);
break;
    default:
      break;
}

  }
  LPAddLiquidityResult(LPAddLiquidityResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)LPAddLiquidityResultCode::SUCCESS:
new(&success_) LPAddLiquiditySuccess(std::move(source.success_));
break;
    default:
      break;
}

  }
  ~LPAddLiquidityResult() {
switch (code_)
{
  case (int32_t)LPAddLiquidityResultCode::SUCCESS:
success_.~LPAddLiquiditySuccess();
break;
  default:
    break;
}
}

  LPAddLiquidityResult &operator=(const LPAddLiquidityResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)LPAddLiquidityResultCode::SUCCESS:
success_ = source.success_;
break;
    default:
      break;
}
}
else {this->~LPAddLiquidityResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)LPAddLiquidityResultCode::SUCCESS:
new(&success_) LPAddLiquiditySuccess(source.success_);
break;
    default:
      break;
}
}
    return *this;
  }
  LPAddLiquidityResult &operator=(LPAddLiquidityResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)LPAddLiquidityResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    default:
      break;
}
}
else {this->~LPAddLiquidityResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)LPAddLiquidityResultCode::SUCCESS:
new(&success_) LPAddLiquiditySuccess(std::move(source.success_));
break;
    default:
      break;
}
}
    return *this;
  }

  LPAddLiquidityResultCode code() const { return LPAddLiquidityResultCode(code_); }
  LPAddLiquidityResult &code(LPAddLiquidityResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  LPAddLiquiditySuccess &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("LPAddLiquidityResult: success accessed when not selected");
  }
  const LPAddLiquiditySuccess &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("LPAddLiquidityResult: success accessed when not selected");
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

#endif // !__XDR_OPERATION_LP_ADD_LIQUIDITY_H_INCLUDED__
