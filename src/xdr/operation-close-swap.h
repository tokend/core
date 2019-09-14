// -*- C++ -*-
// Automatically generated from operation-close-swap.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_CLOSE_SWAP_H_INCLUDED__
#define __XDR_OPERATION_CLOSE_SWAP_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"
#include "xdr/operation-payment.h"

namespace stellar {

struct CloseSwapOp  : xdr::xdr_abstract {
  uint64 swapID{};
  xdr::pointer<Hash> secret{};
  EmptyExt ext{};

  CloseSwapOp() = default;
  template<typename _swapID_T,
           typename _secret_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _swapID_T>::value
                          && std::is_constructible<xdr::pointer<Hash>, _secret_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit CloseSwapOp(_swapID_T &&_swapID,
                       _secret_T &&_secret,
                       _ext_T &&_ext)
    : swapID(std::forward<_swapID_T>(_swapID)),
      secret(std::forward<_secret_T>(_secret)),
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

enum class CloseSwapResultCode : std::int32_t {
  SUCCESS = 0,
  SWAP_EXPIRED = -1,
  INVALID_SECRET = -2,
  LINE_FULL = -3,
  NOT_AUTHORIZED = -4,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CloseSwapResultCode>
  : xdr_integral_base<::stellar::CloseSwapResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::CloseSwapResultCode val) {
    switch (val) {
    case ::stellar::CloseSwapResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::CloseSwapResultCode::SWAP_EXPIRED:
      return "SWAP_EXPIRED";
    case ::stellar::CloseSwapResultCode::INVALID_SECRET:
      return "INVALID_SECRET";
    case ::stellar::CloseSwapResultCode::LINE_FULL:
      return "LINE_FULL";
    case ::stellar::CloseSwapResultCode::NOT_AUTHORIZED:
      return "NOT_AUTHORIZED";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::CloseSwapResultCode::SUCCESS,
      (int32_t)::stellar::CloseSwapResultCode::SWAP_EXPIRED,
      (int32_t)::stellar::CloseSwapResultCode::INVALID_SECRET,
      (int32_t)::stellar::CloseSwapResultCode::LINE_FULL,
      (int32_t)::stellar::CloseSwapResultCode::NOT_AUTHORIZED
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CloseSwapSuccess  : xdr::xdr_abstract {
  EmptyExt ext{};

  CloseSwapSuccess() = default;
  template<typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit CloseSwapSuccess(_ext_T &&_ext)
    : ext(std::forward<_ext_T>(_ext)) {}
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

struct CloseSwapResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<CloseSwapResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    CloseSwapSuccess success_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<CloseSwapResultCode> &_xdr_case_values() {
    static const std::vector<CloseSwapResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)CloseSwapResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)CloseSwapResultCode::SUCCESS:
      _f(&CloseSwapResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in CloseSwapResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~CloseSwapResult();
      code_ = which;switch (code_)
{
      case (int32_t)CloseSwapResultCode::SUCCESS:
new(&success_) CloseSwapSuccess{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit CloseSwapResult(CloseSwapResultCode which = CloseSwapResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)CloseSwapResultCode::SUCCESS:
new(&success_) CloseSwapSuccess{};
break;
    default:
      break;
}

  }
  CloseSwapResult(const CloseSwapResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CloseSwapResultCode::SUCCESS:
new(&success_) CloseSwapSuccess(source.success_);
break;
    default:
      break;
}

  }
  CloseSwapResult(CloseSwapResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CloseSwapResultCode::SUCCESS:
new(&success_) CloseSwapSuccess(std::move(source.success_));
break;
    default:
      break;
}

  }
  ~CloseSwapResult() {
switch (code_)
{
  case (int32_t)CloseSwapResultCode::SUCCESS:
success_.~CloseSwapSuccess();
break;
  default:
    break;
}
}

  CloseSwapResult &operator=(const CloseSwapResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CloseSwapResultCode::SUCCESS:
success_ = source.success_;
break;
    default:
      break;
}
}
else {this->~CloseSwapResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)CloseSwapResultCode::SUCCESS:
new(&success_) CloseSwapSuccess(source.success_);
break;
    default:
      break;
}
}
    return *this;
  }
  CloseSwapResult &operator=(CloseSwapResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CloseSwapResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    default:
      break;
}
}
else {this->~CloseSwapResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)CloseSwapResultCode::SUCCESS:
new(&success_) CloseSwapSuccess(std::move(source.success_));
break;
    default:
      break;
}
}
    return *this;
  }

  CloseSwapResultCode code() const { return CloseSwapResultCode(code_); }
  CloseSwapResult &code(CloseSwapResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  CloseSwapSuccess &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CloseSwapResult: success accessed when not selected");
  }
  const CloseSwapSuccess &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CloseSwapResult: success accessed when not selected");
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

#endif // !__XDR_OPERATION_CLOSE_SWAP_H_INCLUDED__
