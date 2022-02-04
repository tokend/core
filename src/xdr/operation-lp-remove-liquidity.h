// -*- C++ -*-
// Automatically generated from operation-lp-remove-liquidity.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_LP_REMOVE_LIQUIDITY_H_INCLUDED__
#define __XDR_OPERATION_LP_REMOVE_LIQUIDITY_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"
#include "xdr/operation-payment.h"

namespace stellar {

struct LPRemoveLiquidityOp  : xdr::xdr_abstract {
  BalanceID lpTokenBalance{};
  uint64 lpTokensAmount{};
  uint64 firstAssetMinAmount{};
  uint64 secondAssetMinAmount{};
  EmptyExt ext{};

  LPRemoveLiquidityOp() = default;
  template<typename _lpTokenBalance_T,
           typename _lpTokensAmount_T,
           typename _firstAssetMinAmount_T,
           typename _secondAssetMinAmount_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<BalanceID, _lpTokenBalance_T>::value
                          && std::is_constructible<uint64, _lpTokensAmount_T>::value
                          && std::is_constructible<uint64, _firstAssetMinAmount_T>::value
                          && std::is_constructible<uint64, _secondAssetMinAmount_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit LPRemoveLiquidityOp(_lpTokenBalance_T &&_lpTokenBalance,
                               _lpTokensAmount_T &&_lpTokensAmount,
                               _firstAssetMinAmount_T &&_firstAssetMinAmount,
                               _secondAssetMinAmount_T &&_secondAssetMinAmount,
                               _ext_T &&_ext)
    : lpTokenBalance(std::forward<_lpTokenBalance_T>(_lpTokenBalance)),
      lpTokensAmount(std::forward<_lpTokensAmount_T>(_lpTokensAmount)),
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

enum class LPRemoveLiquidityResultCode : std::int32_t {
  SUCCESS = 0,
  LP_TOKEN_BALANCE_NOT_FOUND = -1,
  UNDERFUNDED = -2,
  BALANCE_OVERFLOW = -3,
  LP_NOT_FOUND = -4,
  INVALID_LP_TOKENS_AMOUNT = -5,
  INSUFFICIENT_FIRST_AMOUNT = -6,
  INSUFFICIENT_SECOND_AMOUNT = -7,
  INCORRECT_AMOUNT_PRECISION = -8,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LPRemoveLiquidityResultCode>
  : xdr_integral_base<::stellar::LPRemoveLiquidityResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::LPRemoveLiquidityResultCode val) {
    switch (val) {
    case ::stellar::LPRemoveLiquidityResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::LPRemoveLiquidityResultCode::LP_TOKEN_BALANCE_NOT_FOUND:
      return "LP_TOKEN_BALANCE_NOT_FOUND";
    case ::stellar::LPRemoveLiquidityResultCode::UNDERFUNDED:
      return "UNDERFUNDED";
    case ::stellar::LPRemoveLiquidityResultCode::BALANCE_OVERFLOW:
      return "BALANCE_OVERFLOW";
    case ::stellar::LPRemoveLiquidityResultCode::LP_NOT_FOUND:
      return "LP_NOT_FOUND";
    case ::stellar::LPRemoveLiquidityResultCode::INVALID_LP_TOKENS_AMOUNT:
      return "INVALID_LP_TOKENS_AMOUNT";
    case ::stellar::LPRemoveLiquidityResultCode::INSUFFICIENT_FIRST_AMOUNT:
      return "INSUFFICIENT_FIRST_AMOUNT";
    case ::stellar::LPRemoveLiquidityResultCode::INSUFFICIENT_SECOND_AMOUNT:
      return "INSUFFICIENT_SECOND_AMOUNT";
    case ::stellar::LPRemoveLiquidityResultCode::INCORRECT_AMOUNT_PRECISION:
      return "INCORRECT_AMOUNT_PRECISION";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::LPRemoveLiquidityResultCode::SUCCESS,
      (int32_t)::stellar::LPRemoveLiquidityResultCode::LP_TOKEN_BALANCE_NOT_FOUND,
      (int32_t)::stellar::LPRemoveLiquidityResultCode::UNDERFUNDED,
      (int32_t)::stellar::LPRemoveLiquidityResultCode::BALANCE_OVERFLOW,
      (int32_t)::stellar::LPRemoveLiquidityResultCode::LP_NOT_FOUND,
      (int32_t)::stellar::LPRemoveLiquidityResultCode::INVALID_LP_TOKENS_AMOUNT,
      (int32_t)::stellar::LPRemoveLiquidityResultCode::INSUFFICIENT_FIRST_AMOUNT,
      (int32_t)::stellar::LPRemoveLiquidityResultCode::INSUFFICIENT_SECOND_AMOUNT,
      (int32_t)::stellar::LPRemoveLiquidityResultCode::INCORRECT_AMOUNT_PRECISION
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct LPRemoveLiquiditySuccess  : xdr::xdr_abstract {
  uint64 liquidityPoolID{};
  BalanceID firstAssetBalanceID{};
  BalanceID secondAssetBalanceID{};
  uint64 firstAssetAmount{};
  uint64 secondAssetAmount{};
  EmptyExt ext{};

  LPRemoveLiquiditySuccess() = default;
  template<typename _liquidityPoolID_T,
           typename _firstAssetBalanceID_T,
           typename _secondAssetBalanceID_T,
           typename _firstAssetAmount_T,
           typename _secondAssetAmount_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _liquidityPoolID_T>::value
                          && std::is_constructible<BalanceID, _firstAssetBalanceID_T>::value
                          && std::is_constructible<BalanceID, _secondAssetBalanceID_T>::value
                          && std::is_constructible<uint64, _firstAssetAmount_T>::value
                          && std::is_constructible<uint64, _secondAssetAmount_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit LPRemoveLiquiditySuccess(_liquidityPoolID_T &&_liquidityPoolID,
                                    _firstAssetBalanceID_T &&_firstAssetBalanceID,
                                    _secondAssetBalanceID_T &&_secondAssetBalanceID,
                                    _firstAssetAmount_T &&_firstAssetAmount,
                                    _secondAssetAmount_T &&_secondAssetAmount,
                                    _ext_T &&_ext)
    : liquidityPoolID(std::forward<_liquidityPoolID_T>(_liquidityPoolID)),
      firstAssetBalanceID(std::forward<_firstAssetBalanceID_T>(_firstAssetBalanceID)),
      secondAssetBalanceID(std::forward<_secondAssetBalanceID_T>(_secondAssetBalanceID)),
      firstAssetAmount(std::forward<_firstAssetAmount_T>(_firstAssetAmount)),
      secondAssetAmount(std::forward<_secondAssetAmount_T>(_secondAssetAmount)),
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

struct LPRemoveLiquidityResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<LPRemoveLiquidityResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    LPRemoveLiquiditySuccess success_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<LPRemoveLiquidityResultCode> &_xdr_case_values() {
    static const std::vector<LPRemoveLiquidityResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)LPRemoveLiquidityResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)LPRemoveLiquidityResultCode::SUCCESS:
      _f(&LPRemoveLiquidityResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in LPRemoveLiquidityResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~LPRemoveLiquidityResult();
      code_ = which;switch (code_)
{
      case (int32_t)LPRemoveLiquidityResultCode::SUCCESS:
new(&success_) LPRemoveLiquiditySuccess{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit LPRemoveLiquidityResult(LPRemoveLiquidityResultCode which = LPRemoveLiquidityResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)LPRemoveLiquidityResultCode::SUCCESS:
new(&success_) LPRemoveLiquiditySuccess{};
break;
    default:
      break;
}

  }
  LPRemoveLiquidityResult(const LPRemoveLiquidityResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)LPRemoveLiquidityResultCode::SUCCESS:
new(&success_) LPRemoveLiquiditySuccess(source.success_);
break;
    default:
      break;
}

  }
  LPRemoveLiquidityResult(LPRemoveLiquidityResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)LPRemoveLiquidityResultCode::SUCCESS:
new(&success_) LPRemoveLiquiditySuccess(std::move(source.success_));
break;
    default:
      break;
}

  }
  ~LPRemoveLiquidityResult() {
switch (code_)
{
  case (int32_t)LPRemoveLiquidityResultCode::SUCCESS:
success_.~LPRemoveLiquiditySuccess();
break;
  default:
    break;
}
}

  LPRemoveLiquidityResult &operator=(const LPRemoveLiquidityResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)LPRemoveLiquidityResultCode::SUCCESS:
success_ = source.success_;
break;
    default:
      break;
}
}
else {this->~LPRemoveLiquidityResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)LPRemoveLiquidityResultCode::SUCCESS:
new(&success_) LPRemoveLiquiditySuccess(source.success_);
break;
    default:
      break;
}
}
    return *this;
  }
  LPRemoveLiquidityResult &operator=(LPRemoveLiquidityResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)LPRemoveLiquidityResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    default:
      break;
}
}
else {this->~LPRemoveLiquidityResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)LPRemoveLiquidityResultCode::SUCCESS:
new(&success_) LPRemoveLiquiditySuccess(std::move(source.success_));
break;
    default:
      break;
}
}
    return *this;
  }

  LPRemoveLiquidityResultCode code() const { return LPRemoveLiquidityResultCode(code_); }
  LPRemoveLiquidityResult &code(LPRemoveLiquidityResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  LPRemoveLiquiditySuccess &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("LPRemoveLiquidityResult: success accessed when not selected");
  }
  const LPRemoveLiquiditySuccess &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("LPRemoveLiquidityResult: success accessed when not selected");
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

#endif // !__XDR_OPERATION_LP_REMOVE_LIQUIDITY_H_INCLUDED__
