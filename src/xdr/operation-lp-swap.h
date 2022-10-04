// -*- C++ -*-
// Automatically generated from operation-lp-swap.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_LP_SWAP_H_INCLUDED__
#define __XDR_OPERATION_LP_SWAP_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"
#include "xdr/operation-payment.h"

namespace stellar {

enum class LPSwapType : std::int32_t {
  EXACT_IN_TOKENS_FOR_OUT_TOKENS = 0,
  EXACT_OUT_TOKENS_FOR_IN_TOKENS = 1,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LPSwapType>
  : xdr_integral_base<::stellar::LPSwapType, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::LPSwapType val) {
    switch (val) {
    case ::stellar::LPSwapType::EXACT_IN_TOKENS_FOR_OUT_TOKENS:
      return "EXACT_IN_TOKENS_FOR_OUT_TOKENS";
    case ::stellar::LPSwapType::EXACT_OUT_TOKENS_FOR_IN_TOKENS:
      return "EXACT_OUT_TOKENS_FOR_IN_TOKENS";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::LPSwapType::EXACT_IN_TOKENS_FOR_OUT_TOKENS,
      (int32_t)::stellar::LPSwapType::EXACT_OUT_TOKENS_FOR_IN_TOKENS
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct LPSwapOp  : xdr::xdr_abstract {
  struct _lpSwapRequest_t : xdr::xdr_abstract {
    struct _swapExactOutTokensForInTokens_t  : xdr::xdr_abstract {
      uint64 amountInMax{};
      uint64 amountOut{};

      _swapExactOutTokensForInTokens_t() = default;
      template<typename _amountInMax_T,
               typename _amountOut_T,
               typename = typename
               std::enable_if<std::is_constructible<uint64, _amountInMax_T>::value
                              && std::is_constructible<uint64, _amountOut_T>::value
                             >::type>
      explicit _swapExactOutTokensForInTokens_t(_amountInMax_T &&_amountInMax,
                                                _amountOut_T &&_amountOut)
        : amountInMax(std::forward<_amountInMax_T>(_amountInMax)),
          amountOut(std::forward<_amountOut_T>(_amountOut)) {}
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
    struct _swapExactInTokensForOutTokens_t  : xdr::xdr_abstract {
      uint64 amountIn{};
      uint64 amountOutMin{};

      _swapExactInTokensForOutTokens_t() = default;
      template<typename _amountIn_T,
               typename _amountOutMin_T,
               typename = typename
               std::enable_if<std::is_constructible<uint64, _amountIn_T>::value
                              && std::is_constructible<uint64, _amountOutMin_T>::value
                             >::type>
      explicit _swapExactInTokensForOutTokens_t(_amountIn_T &&_amountIn,
                                                _amountOutMin_T &&_amountOutMin)
        : amountIn(std::forward<_amountIn_T>(_amountIn)),
          amountOutMin(std::forward<_amountOutMin_T>(_amountOutMin)) {}
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

    using _xdr_case_type = xdr::xdr_traits<LPSwapType>::case_type;
  private:
    _xdr_case_type type_;
    union {
      _swapExactOutTokensForInTokens_t swapExactOutTokensForInTokens_;
      _swapExactInTokensForOutTokens_t swapExactInTokensForOutTokens_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<LPSwapType> &_xdr_case_values() {
      static const std::vector<LPSwapType> _xdr_disc_vec {
        LPSwapType::EXACT_OUT_TOKENS_FOR_IN_TOKENS,
        LPSwapType::EXACT_IN_TOKENS_FOR_OUT_TOKENS
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)LPSwapType::EXACT_OUT_TOKENS_FOR_IN_TOKENS ? 1
        : which == (int32_t)LPSwapType::EXACT_IN_TOKENS_FOR_OUT_TOKENS ? 2
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)LPSwapType::EXACT_OUT_TOKENS_FOR_IN_TOKENS:
        _f(&_lpSwapRequest_t::swapExactOutTokensForInTokens_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)LPSwapType::EXACT_IN_TOKENS_FOR_OUT_TOKENS:
        _f(&_lpSwapRequest_t::swapExactInTokensForOutTokens_, std::forward<_A>(_a)...);
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return type_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of type in _lpSwapRequest_t");
      if (fnum != _xdr_field_number(type_)) {
        this->~_lpSwapRequest_t();
        type_ = which;switch (type_)
{
        case (int32_t)LPSwapType::EXACT_OUT_TOKENS_FOR_IN_TOKENS:
new(&swapExactOutTokensForInTokens_) _swapExactOutTokensForInTokens_t{};
break;
        case (int32_t)LPSwapType::EXACT_IN_TOKENS_FOR_OUT_TOKENS:
new(&swapExactInTokensForOutTokens_) _swapExactInTokensForOutTokens_t{};
break;
}

      }
      else
        type_ = which;
    }
    explicit _lpSwapRequest_t(LPSwapType which = LPSwapType{}) : type_((int32_t)which) {
      switch (type_)
{
      case (int32_t)LPSwapType::EXACT_OUT_TOKENS_FOR_IN_TOKENS:
new(&swapExactOutTokensForInTokens_) _swapExactOutTokensForInTokens_t{};
break;
      case (int32_t)LPSwapType::EXACT_IN_TOKENS_FOR_OUT_TOKENS:
new(&swapExactInTokensForOutTokens_) _swapExactInTokensForOutTokens_t{};
break;
}

    }
    _lpSwapRequest_t(const _lpSwapRequest_t &source) : type_(source.type_) {
      switch (type_)
{
      case (int32_t)LPSwapType::EXACT_OUT_TOKENS_FOR_IN_TOKENS:
new(&swapExactOutTokensForInTokens_) _swapExactOutTokensForInTokens_t(source.swapExactOutTokensForInTokens_);
break;
      case (int32_t)LPSwapType::EXACT_IN_TOKENS_FOR_OUT_TOKENS:
new(&swapExactInTokensForOutTokens_) _swapExactInTokensForOutTokens_t(source.swapExactInTokensForOutTokens_);
break;
}

    }
    _lpSwapRequest_t(_lpSwapRequest_t &&source) : type_(source.type_) {
      switch (type_)
{
      case (int32_t)LPSwapType::EXACT_OUT_TOKENS_FOR_IN_TOKENS:
new(&swapExactOutTokensForInTokens_) _swapExactOutTokensForInTokens_t(std::move(source.swapExactOutTokensForInTokens_));
break;
      case (int32_t)LPSwapType::EXACT_IN_TOKENS_FOR_OUT_TOKENS:
new(&swapExactInTokensForOutTokens_) _swapExactInTokensForOutTokens_t(std::move(source.swapExactInTokensForOutTokens_));
break;
}

    }
    ~_lpSwapRequest_t() {
switch (type_)
{
    case (int32_t)LPSwapType::EXACT_OUT_TOKENS_FOR_IN_TOKENS:
swapExactOutTokensForInTokens_.~_swapExactOutTokensForInTokens_t();
break;
    case (int32_t)LPSwapType::EXACT_IN_TOKENS_FOR_OUT_TOKENS:
swapExactInTokensForOutTokens_.~_swapExactInTokensForOutTokens_t();
break;
}
}

    _lpSwapRequest_t &operator=(const _lpSwapRequest_t &source) {
      if (type_ == source.type_)
{
switch (type_)
{
      case (int32_t)LPSwapType::EXACT_OUT_TOKENS_FOR_IN_TOKENS:
swapExactOutTokensForInTokens_ = source.swapExactOutTokensForInTokens_;
break;
      case (int32_t)LPSwapType::EXACT_IN_TOKENS_FOR_OUT_TOKENS:
swapExactInTokensForOutTokens_ = source.swapExactInTokensForOutTokens_;
break;
}
}
else {this->~_lpSwapRequest_t();
      type_ = source.type_;
switch (type_)
{
      case (int32_t)LPSwapType::EXACT_OUT_TOKENS_FOR_IN_TOKENS:
new(&swapExactOutTokensForInTokens_) _swapExactOutTokensForInTokens_t(source.swapExactOutTokensForInTokens_);
break;
      case (int32_t)LPSwapType::EXACT_IN_TOKENS_FOR_OUT_TOKENS:
new(&swapExactInTokensForOutTokens_) _swapExactInTokensForOutTokens_t(source.swapExactInTokensForOutTokens_);
break;
}
}
      return *this;
    }
    _lpSwapRequest_t &operator=(_lpSwapRequest_t &&source) {
      if (type_ == source.type_)
{
switch (type_)
{
      case (int32_t)LPSwapType::EXACT_OUT_TOKENS_FOR_IN_TOKENS:
swapExactOutTokensForInTokens_ = std::move(source.swapExactOutTokensForInTokens_);
break;
      case (int32_t)LPSwapType::EXACT_IN_TOKENS_FOR_OUT_TOKENS:
swapExactInTokensForOutTokens_ = std::move(source.swapExactInTokensForOutTokens_);
break;
}
}
else {this->~_lpSwapRequest_t();
      type_ = std::move(source.type_);
switch (type_)
{
      case (int32_t)LPSwapType::EXACT_OUT_TOKENS_FOR_IN_TOKENS:
new(&swapExactOutTokensForInTokens_) _swapExactOutTokensForInTokens_t(std::move(source.swapExactOutTokensForInTokens_));
break;
      case (int32_t)LPSwapType::EXACT_IN_TOKENS_FOR_OUT_TOKENS:
new(&swapExactInTokensForOutTokens_) _swapExactInTokensForOutTokens_t(std::move(source.swapExactInTokensForOutTokens_));
break;
}
}
      return *this;
    }

    LPSwapType type() const { return LPSwapType(type_); }
    _lpSwapRequest_t &type(LPSwapType _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    _swapExactOutTokensForInTokens_t &swapExactOutTokensForInTokens() {
      if (_xdr_field_number(type_) == 1)
        return swapExactOutTokensForInTokens_;
      throw xdr::xdr_wrong_union("_lpSwapRequest_t: swapExactOutTokensForInTokens accessed when not selected");
    }
    const _swapExactOutTokensForInTokens_t &swapExactOutTokensForInTokens() const {
      if (_xdr_field_number(type_) == 1)
        return swapExactOutTokensForInTokens_;
      throw xdr::xdr_wrong_union("_lpSwapRequest_t: swapExactOutTokensForInTokens accessed when not selected");
    }
    _swapExactInTokensForOutTokens_t &swapExactInTokensForOutTokens() {
      if (_xdr_field_number(type_) == 2)
        return swapExactInTokensForOutTokens_;
      throw xdr::xdr_wrong_union("_lpSwapRequest_t: swapExactInTokensForOutTokens accessed when not selected");
    }
    const _swapExactInTokensForOutTokens_t &swapExactInTokensForOutTokens() const {
      if (_xdr_field_number(type_) == 2)
        return swapExactInTokensForOutTokens_;
      throw xdr::xdr_wrong_union("_lpSwapRequest_t: swapExactInTokensForOutTokens accessed when not selected");
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

  BalanceID fromBalance{};
  BalanceID toBalance{};
  _lpSwapRequest_t lpSwapRequest{};
  PaymentFeeData feeData{};
  EmptyExt ext{};

  LPSwapOp() = default;
  template<typename _fromBalance_T,
           typename _toBalance_T,
           typename _lpSwapRequest_T,
           typename _feeData_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<BalanceID, _fromBalance_T>::value
                          && std::is_constructible<BalanceID, _toBalance_T>::value
                          && std::is_constructible<_lpSwapRequest_t, _lpSwapRequest_T>::value
                          && std::is_constructible<PaymentFeeData, _feeData_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit LPSwapOp(_fromBalance_T &&_fromBalance,
                    _toBalance_T &&_toBalance,
                    _lpSwapRequest_T &&_lpSwapRequest,
                    _feeData_T &&_feeData,
                    _ext_T &&_ext)
    : fromBalance(std::forward<_fromBalance_T>(_fromBalance)),
      toBalance(std::forward<_toBalance_T>(_toBalance)),
      lpSwapRequest(std::forward<_lpSwapRequest_T>(_lpSwapRequest)),
      feeData(std::forward<_feeData_T>(_feeData)),
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

enum class LPSwapResultCode : std::int32_t {
  SUCCESS = 0,
  SAME_BALANCES = -1,
  UNDERFUNDED = -2,
  BALANCE_ASSETS_MATCHED = -3,
  FROM_BALANCE_NOT_FOUND = -4,
  TO_BALANCE_NOT_FOUND = -5,
  NOT_ALLOWED_BY_ASSET_POLICY = -6,
  INVALID_DESTINATION_FEE = -7,
  INSUFFICIENT_FEE_AMOUNT = -8,
  AMOUNT_IS_LESS_THAN_DEST_FEE = -9,
  INCORRECT_AMOUNT_PRECISION = -10,
  INSUFFICIENT_INPUT_AMOUNT = -11,
  INSUFFICIENT_OUTPUT_AMOUNT = -12,
  SAME_ASSETS = -13,
  LIQUIDITY_POOL_NOT_FOUND = -14,
  INSUFFICIENT_LIQUIDITY = -15,
  EXCESSIVE_INPUT_AMOUNT = -16,
  BALANCE_OVERFLOW = -17,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LPSwapResultCode>
  : xdr_integral_base<::stellar::LPSwapResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::LPSwapResultCode val) {
    switch (val) {
    case ::stellar::LPSwapResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::LPSwapResultCode::SAME_BALANCES:
      return "SAME_BALANCES";
    case ::stellar::LPSwapResultCode::UNDERFUNDED:
      return "UNDERFUNDED";
    case ::stellar::LPSwapResultCode::BALANCE_ASSETS_MATCHED:
      return "BALANCE_ASSETS_MATCHED";
    case ::stellar::LPSwapResultCode::FROM_BALANCE_NOT_FOUND:
      return "FROM_BALANCE_NOT_FOUND";
    case ::stellar::LPSwapResultCode::TO_BALANCE_NOT_FOUND:
      return "TO_BALANCE_NOT_FOUND";
    case ::stellar::LPSwapResultCode::NOT_ALLOWED_BY_ASSET_POLICY:
      return "NOT_ALLOWED_BY_ASSET_POLICY";
    case ::stellar::LPSwapResultCode::INVALID_DESTINATION_FEE:
      return "INVALID_DESTINATION_FEE";
    case ::stellar::LPSwapResultCode::INSUFFICIENT_FEE_AMOUNT:
      return "INSUFFICIENT_FEE_AMOUNT";
    case ::stellar::LPSwapResultCode::AMOUNT_IS_LESS_THAN_DEST_FEE:
      return "AMOUNT_IS_LESS_THAN_DEST_FEE";
    case ::stellar::LPSwapResultCode::INCORRECT_AMOUNT_PRECISION:
      return "INCORRECT_AMOUNT_PRECISION";
    case ::stellar::LPSwapResultCode::INSUFFICIENT_INPUT_AMOUNT:
      return "INSUFFICIENT_INPUT_AMOUNT";
    case ::stellar::LPSwapResultCode::INSUFFICIENT_OUTPUT_AMOUNT:
      return "INSUFFICIENT_OUTPUT_AMOUNT";
    case ::stellar::LPSwapResultCode::SAME_ASSETS:
      return "SAME_ASSETS";
    case ::stellar::LPSwapResultCode::LIQUIDITY_POOL_NOT_FOUND:
      return "LIQUIDITY_POOL_NOT_FOUND";
    case ::stellar::LPSwapResultCode::INSUFFICIENT_LIQUIDITY:
      return "INSUFFICIENT_LIQUIDITY";
    case ::stellar::LPSwapResultCode::EXCESSIVE_INPUT_AMOUNT:
      return "EXCESSIVE_INPUT_AMOUNT";
    case ::stellar::LPSwapResultCode::BALANCE_OVERFLOW:
      return "BALANCE_OVERFLOW";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::LPSwapResultCode::SUCCESS,
      (int32_t)::stellar::LPSwapResultCode::SAME_BALANCES,
      (int32_t)::stellar::LPSwapResultCode::UNDERFUNDED,
      (int32_t)::stellar::LPSwapResultCode::BALANCE_ASSETS_MATCHED,
      (int32_t)::stellar::LPSwapResultCode::FROM_BALANCE_NOT_FOUND,
      (int32_t)::stellar::LPSwapResultCode::TO_BALANCE_NOT_FOUND,
      (int32_t)::stellar::LPSwapResultCode::NOT_ALLOWED_BY_ASSET_POLICY,
      (int32_t)::stellar::LPSwapResultCode::INVALID_DESTINATION_FEE,
      (int32_t)::stellar::LPSwapResultCode::INSUFFICIENT_FEE_AMOUNT,
      (int32_t)::stellar::LPSwapResultCode::AMOUNT_IS_LESS_THAN_DEST_FEE,
      (int32_t)::stellar::LPSwapResultCode::INCORRECT_AMOUNT_PRECISION,
      (int32_t)::stellar::LPSwapResultCode::INSUFFICIENT_INPUT_AMOUNT,
      (int32_t)::stellar::LPSwapResultCode::INSUFFICIENT_OUTPUT_AMOUNT,
      (int32_t)::stellar::LPSwapResultCode::SAME_ASSETS,
      (int32_t)::stellar::LPSwapResultCode::LIQUIDITY_POOL_NOT_FOUND,
      (int32_t)::stellar::LPSwapResultCode::INSUFFICIENT_LIQUIDITY,
      (int32_t)::stellar::LPSwapResultCode::EXCESSIVE_INPUT_AMOUNT,
      (int32_t)::stellar::LPSwapResultCode::BALANCE_OVERFLOW
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct LPSwapSuccess  : xdr::xdr_abstract {
  uint64 liquidityPoolID{};
  AccountID poolAccount{};
  BalanceID lpInBalanceID{};
  BalanceID lpOutBalanceID{};
  BalanceID sourceInBalanceID{};
  BalanceID sourceOutBalanceID{};
  uint64 swapInAmount{};
  uint64 swapOutAmount{};
  Fee actualSourcePaymentFee{};
  Fee actualDestinationPaymentFee{};
  EmptyExt ext{};

  LPSwapSuccess() = default;
  template<typename _liquidityPoolID_T,
           typename _poolAccount_T,
           typename _lpInBalanceID_T,
           typename _lpOutBalanceID_T,
           typename _sourceInBalanceID_T,
           typename _sourceOutBalanceID_T,
           typename _swapInAmount_T,
           typename _swapOutAmount_T,
           typename _actualSourcePaymentFee_T,
           typename _actualDestinationPaymentFee_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _liquidityPoolID_T>::value
                          && std::is_constructible<AccountID, _poolAccount_T>::value
                          && std::is_constructible<BalanceID, _lpInBalanceID_T>::value
                          && std::is_constructible<BalanceID, _lpOutBalanceID_T>::value
                          && std::is_constructible<BalanceID, _sourceInBalanceID_T>::value
                          && std::is_constructible<BalanceID, _sourceOutBalanceID_T>::value
                          && std::is_constructible<uint64, _swapInAmount_T>::value
                          && std::is_constructible<uint64, _swapOutAmount_T>::value
                          && std::is_constructible<Fee, _actualSourcePaymentFee_T>::value
                          && std::is_constructible<Fee, _actualDestinationPaymentFee_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit LPSwapSuccess(_liquidityPoolID_T &&_liquidityPoolID,
                         _poolAccount_T &&_poolAccount,
                         _lpInBalanceID_T &&_lpInBalanceID,
                         _lpOutBalanceID_T &&_lpOutBalanceID,
                         _sourceInBalanceID_T &&_sourceInBalanceID,
                         _sourceOutBalanceID_T &&_sourceOutBalanceID,
                         _swapInAmount_T &&_swapInAmount,
                         _swapOutAmount_T &&_swapOutAmount,
                         _actualSourcePaymentFee_T &&_actualSourcePaymentFee,
                         _actualDestinationPaymentFee_T &&_actualDestinationPaymentFee,
                         _ext_T &&_ext)
    : liquidityPoolID(std::forward<_liquidityPoolID_T>(_liquidityPoolID)),
      poolAccount(std::forward<_poolAccount_T>(_poolAccount)),
      lpInBalanceID(std::forward<_lpInBalanceID_T>(_lpInBalanceID)),
      lpOutBalanceID(std::forward<_lpOutBalanceID_T>(_lpOutBalanceID)),
      sourceInBalanceID(std::forward<_sourceInBalanceID_T>(_sourceInBalanceID)),
      sourceOutBalanceID(std::forward<_sourceOutBalanceID_T>(_sourceOutBalanceID)),
      swapInAmount(std::forward<_swapInAmount_T>(_swapInAmount)),
      swapOutAmount(std::forward<_swapOutAmount_T>(_swapOutAmount)),
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

struct LPSwapResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<LPSwapResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    LPSwapSuccess success_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<LPSwapResultCode> &_xdr_case_values() {
    static const std::vector<LPSwapResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)LPSwapResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)LPSwapResultCode::SUCCESS:
      _f(&LPSwapResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in LPSwapResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~LPSwapResult();
      code_ = which;switch (code_)
{
      case (int32_t)LPSwapResultCode::SUCCESS:
new(&success_) LPSwapSuccess{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit LPSwapResult(LPSwapResultCode which = LPSwapResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)LPSwapResultCode::SUCCESS:
new(&success_) LPSwapSuccess{};
break;
    default:
      break;
}

  }
  LPSwapResult(const LPSwapResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)LPSwapResultCode::SUCCESS:
new(&success_) LPSwapSuccess(source.success_);
break;
    default:
      break;
}

  }
  LPSwapResult(LPSwapResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)LPSwapResultCode::SUCCESS:
new(&success_) LPSwapSuccess(std::move(source.success_));
break;
    default:
      break;
}

  }
  ~LPSwapResult() {
switch (code_)
{
  case (int32_t)LPSwapResultCode::SUCCESS:
success_.~LPSwapSuccess();
break;
  default:
    break;
}
}

  LPSwapResult &operator=(const LPSwapResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)LPSwapResultCode::SUCCESS:
success_ = source.success_;
break;
    default:
      break;
}
}
else {this->~LPSwapResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)LPSwapResultCode::SUCCESS:
new(&success_) LPSwapSuccess(source.success_);
break;
    default:
      break;
}
}
    return *this;
  }
  LPSwapResult &operator=(LPSwapResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)LPSwapResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    default:
      break;
}
}
else {this->~LPSwapResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)LPSwapResultCode::SUCCESS:
new(&success_) LPSwapSuccess(std::move(source.success_));
break;
    default:
      break;
}
}
    return *this;
  }

  LPSwapResultCode code() const { return LPSwapResultCode(code_); }
  LPSwapResult &code(LPSwapResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  LPSwapSuccess &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("LPSwapResult: success accessed when not selected");
  }
  const LPSwapSuccess &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("LPSwapResult: success accessed when not selected");
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

#endif // !__XDR_OPERATION_LP_SWAP_H_INCLUDED__
