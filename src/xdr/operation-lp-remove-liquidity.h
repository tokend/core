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
  AssetCode lpTokenAsset{};
  uint64 lpTokensAmount{};
  uint64 firstAssetMinAmount{};
  uint64 secondAssetMinAmount{};
  PaymentFeeData feeData{};
  uint64 deadline{};
  EmptyExt ext{};

  LPRemoveLiquidityOp() = default;
  template<typename _lpTokenAsset_T,
           typename _lpTokensAmount_T,
           typename _firstAssetMinAmount_T,
           typename _secondAssetMinAmount_T,
           typename _feeData_T,
           typename _deadline_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<AssetCode, _lpTokenAsset_T>::value
                          && std::is_constructible<uint64, _lpTokensAmount_T>::value
                          && std::is_constructible<uint64, _firstAssetMinAmount_T>::value
                          && std::is_constructible<uint64, _secondAssetMinAmount_T>::value
                          && std::is_constructible<PaymentFeeData, _feeData_T>::value
                          && std::is_constructible<uint64, _deadline_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit LPRemoveLiquidityOp(_lpTokenAsset_T &&_lpTokenAsset,
                               _lpTokensAmount_T &&_lpTokensAmount,
                               _firstAssetMinAmount_T &&_firstAssetMinAmount,
                               _secondAssetMinAmount_T &&_secondAssetMinAmount,
                               _feeData_T &&_feeData,
                               _deadline_T &&_deadline,
                               _ext_T &&_ext)
    : lpTokenAsset(std::forward<_lpTokenAsset_T>(_lpTokenAsset)),
      lpTokensAmount(std::forward<_lpTokensAmount_T>(_lpTokensAmount)),
      firstAssetMinAmount(std::forward<_firstAssetMinAmount_T>(_firstAssetMinAmount)),
      secondAssetMinAmount(std::forward<_secondAssetMinAmount_T>(_secondAssetMinAmount)),
      feeData(std::forward<_feeData_T>(_feeData)),
      deadline(std::forward<_deadline_T>(_deadline)),
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
  MALFORMED = -1,
  UNDERFUNDED = -2,
  LINE_FULL = -3,
  INVALID_DESTINATION_FEE = -5,
  INSUFFICIENT_FEE_AMOUNT = -6,
  RECIEVED_AMOUNT_IS_LESS_THAN_FEE = -7,
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
    case ::stellar::LPRemoveLiquidityResultCode::MALFORMED:
      return "MALFORMED";
    case ::stellar::LPRemoveLiquidityResultCode::UNDERFUNDED:
      return "UNDERFUNDED";
    case ::stellar::LPRemoveLiquidityResultCode::LINE_FULL:
      return "LINE_FULL";
    case ::stellar::LPRemoveLiquidityResultCode::INVALID_DESTINATION_FEE:
      return "INVALID_DESTINATION_FEE";
    case ::stellar::LPRemoveLiquidityResultCode::INSUFFICIENT_FEE_AMOUNT:
      return "INSUFFICIENT_FEE_AMOUNT";
    case ::stellar::LPRemoveLiquidityResultCode::RECIEVED_AMOUNT_IS_LESS_THAN_FEE:
      return "RECIEVED_AMOUNT_IS_LESS_THAN_FEE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::LPRemoveLiquidityResultCode::SUCCESS,
      (int32_t)::stellar::LPRemoveLiquidityResultCode::MALFORMED,
      (int32_t)::stellar::LPRemoveLiquidityResultCode::UNDERFUNDED,
      (int32_t)::stellar::LPRemoveLiquidityResultCode::LINE_FULL,
      (int32_t)::stellar::LPRemoveLiquidityResultCode::INVALID_DESTINATION_FEE,
      (int32_t)::stellar::LPRemoveLiquidityResultCode::INSUFFICIENT_FEE_AMOUNT,
      (int32_t)::stellar::LPRemoveLiquidityResultCode::RECIEVED_AMOUNT_IS_LESS_THAN_FEE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct LPRemoveLiquiditySuccess  : xdr::xdr_abstract {
  uint64 liquidityPoolID{};
  BalanceID firstAssetBalanceID{};
  BalanceID secondAssetBalanceID{};
  AssetCode firstAsset{};
  AssetCode secondAsset{};
  uint64 firstAssetAmount{};
  uint64 secondAssetAmount{};

  LPRemoveLiquiditySuccess() = default;
  template<typename _liquidityPoolID_T,
           typename _firstAssetBalanceID_T,
           typename _secondAssetBalanceID_T,
           typename _firstAsset_T,
           typename _secondAsset_T,
           typename _firstAssetAmount_T,
           typename _secondAssetAmount_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _liquidityPoolID_T>::value
                          && std::is_constructible<BalanceID, _firstAssetBalanceID_T>::value
                          && std::is_constructible<BalanceID, _secondAssetBalanceID_T>::value
                          && std::is_constructible<AssetCode, _firstAsset_T>::value
                          && std::is_constructible<AssetCode, _secondAsset_T>::value
                          && std::is_constructible<uint64, _firstAssetAmount_T>::value
                          && std::is_constructible<uint64, _secondAssetAmount_T>::value
                         >::type>
  explicit LPRemoveLiquiditySuccess(_liquidityPoolID_T &&_liquidityPoolID,
                                    _firstAssetBalanceID_T &&_firstAssetBalanceID,
                                    _secondAssetBalanceID_T &&_secondAssetBalanceID,
                                    _firstAsset_T &&_firstAsset,
                                    _secondAsset_T &&_secondAsset,
                                    _firstAssetAmount_T &&_firstAssetAmount,
                                    _secondAssetAmount_T &&_secondAssetAmount)
    : liquidityPoolID(std::forward<_liquidityPoolID_T>(_liquidityPoolID)),
      firstAssetBalanceID(std::forward<_firstAssetBalanceID_T>(_firstAssetBalanceID)),
      secondAssetBalanceID(std::forward<_secondAssetBalanceID_T>(_secondAssetBalanceID)),
      firstAsset(std::forward<_firstAsset_T>(_firstAsset)),
      secondAsset(std::forward<_secondAsset_T>(_secondAsset)),
      firstAssetAmount(std::forward<_firstAssetAmount_T>(_firstAssetAmount)),
      secondAssetAmount(std::forward<_secondAssetAmount_T>(_secondAssetAmount)) {}
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
