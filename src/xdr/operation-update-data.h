// -*- C++ -*-
// Automatically generated from operation-update-data.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_UPDATE_DATA_H_INCLUDED__
#define __XDR_OPERATION_UPDATE_DATA_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"

namespace stellar {

struct UpdateDataOp  : xdr::xdr_abstract {
  uint64 dataID{};
  longstring value{};
  EmptyExt ext{};

  UpdateDataOp() = default;
  template<typename _dataID_T,
           typename _value_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _dataID_T>::value
                          && std::is_constructible<longstring, _value_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit UpdateDataOp(_dataID_T &&_dataID,
                        _value_T &&_value,
                        _ext_T &&_ext)
    : dataID(std::forward<_dataID_T>(_dataID)),
      value(std::forward<_value_T>(_value)),
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

enum class UpdateDataResultCode : std::int32_t {
  SUCCESS = 0,
  INVALID_DATA = -1,
  NOT_FOUND = -2,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::UpdateDataResultCode>
  : xdr_integral_base<::stellar::UpdateDataResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::UpdateDataResultCode val) {
    switch (val) {
    case ::stellar::UpdateDataResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::UpdateDataResultCode::INVALID_DATA:
      return "INVALID_DATA";
    case ::stellar::UpdateDataResultCode::NOT_FOUND:
      return "NOT_FOUND";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::UpdateDataResultCode::SUCCESS,
      (int32_t)::stellar::UpdateDataResultCode::INVALID_DATA,
      (int32_t)::stellar::UpdateDataResultCode::NOT_FOUND
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct UpdateDataResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<UpdateDataResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    EmptyExt ext_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<UpdateDataResultCode> &_xdr_case_values() {
    static const std::vector<UpdateDataResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)UpdateDataResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)UpdateDataResultCode::SUCCESS:
      _f(&UpdateDataResult::ext_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in UpdateDataResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~UpdateDataResult();
      code_ = which;switch (code_)
{
      case (int32_t)UpdateDataResultCode::SUCCESS:
new(&ext_) EmptyExt{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit UpdateDataResult(UpdateDataResultCode which = UpdateDataResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)UpdateDataResultCode::SUCCESS:
new(&ext_) EmptyExt{};
break;
    default:
      break;
}

  }
  UpdateDataResult(const UpdateDataResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)UpdateDataResultCode::SUCCESS:
new(&ext_) EmptyExt(source.ext_);
break;
    default:
      break;
}

  }
  UpdateDataResult(UpdateDataResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)UpdateDataResultCode::SUCCESS:
new(&ext_) EmptyExt(std::move(source.ext_));
break;
    default:
      break;
}

  }
  ~UpdateDataResult() {
switch (code_)
{
  case (int32_t)UpdateDataResultCode::SUCCESS:
ext_.~EmptyExt();
break;
  default:
    break;
}
}

  UpdateDataResult &operator=(const UpdateDataResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)UpdateDataResultCode::SUCCESS:
ext_ = source.ext_;
break;
    default:
      break;
}
}
else {this->~UpdateDataResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)UpdateDataResultCode::SUCCESS:
new(&ext_) EmptyExt(source.ext_);
break;
    default:
      break;
}
}
    return *this;
  }
  UpdateDataResult &operator=(UpdateDataResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)UpdateDataResultCode::SUCCESS:
ext_ = std::move(source.ext_);
break;
    default:
      break;
}
}
else {this->~UpdateDataResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)UpdateDataResultCode::SUCCESS:
new(&ext_) EmptyExt(std::move(source.ext_));
break;
    default:
      break;
}
}
    return *this;
  }

  UpdateDataResultCode code() const { return UpdateDataResultCode(code_); }
  UpdateDataResult &code(UpdateDataResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  EmptyExt &ext() {
    if (_xdr_field_number(code_) == 1)
      return ext_;
    throw xdr::xdr_wrong_union("UpdateDataResult: ext accessed when not selected");
  }
  const EmptyExt &ext() const {
    if (_xdr_field_number(code_) == 1)
      return ext_;
    throw xdr::xdr_wrong_union("UpdateDataResult: ext accessed when not selected");
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

#endif // !__XDR_OPERATION_UPDATE_DATA_H_INCLUDED__
