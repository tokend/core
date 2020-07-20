// -*- C++ -*-
// Automatically generated from operation-create-data.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_CREATE_DATA_H_INCLUDED__
#define __XDR_OPERATION_CREATE_DATA_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"

namespace stellar {

struct CreateDataOp  : xdr::xdr_abstract {
  uint64 type{};
  longstring value{};
  EmptyExt ext{};

  CreateDataOp() = default;
  template<typename _type_T,
           typename _value_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _type_T>::value
                          && std::is_constructible<longstring, _value_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit CreateDataOp(_type_T &&_type,
                        _value_T &&_value,
                        _ext_T &&_ext)
    : type(std::forward<_type_T>(_type)),
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

enum class CreateDataResultCode : std::int32_t {
  SUCCESS = 0,
  INVALID_DATA = -1,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateDataResultCode>
  : xdr_integral_base<::stellar::CreateDataResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::CreateDataResultCode val) {
    switch (val) {
    case ::stellar::CreateDataResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::CreateDataResultCode::INVALID_DATA:
      return "INVALID_DATA";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::CreateDataResultCode::SUCCESS,
      (int32_t)::stellar::CreateDataResultCode::INVALID_DATA
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateDataSuccess  : xdr::xdr_abstract {
  uint64 dataID{};
  EmptyExt ext{};

  CreateDataSuccess() = default;
  template<typename _dataID_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _dataID_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit CreateDataSuccess(_dataID_T &&_dataID,
                             _ext_T &&_ext)
    : dataID(std::forward<_dataID_T>(_dataID)),
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

struct CreateDataResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<CreateDataResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    CreateDataSuccess success_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<CreateDataResultCode> &_xdr_case_values() {
    static const std::vector<CreateDataResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)CreateDataResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)CreateDataResultCode::SUCCESS:
      _f(&CreateDataResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in CreateDataResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~CreateDataResult();
      code_ = which;switch (code_)
{
      case (int32_t)CreateDataResultCode::SUCCESS:
new(&success_) CreateDataSuccess{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit CreateDataResult(CreateDataResultCode which = CreateDataResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)CreateDataResultCode::SUCCESS:
new(&success_) CreateDataSuccess{};
break;
    default:
      break;
}

  }
  CreateDataResult(const CreateDataResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CreateDataResultCode::SUCCESS:
new(&success_) CreateDataSuccess(source.success_);
break;
    default:
      break;
}

  }
  CreateDataResult(CreateDataResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CreateDataResultCode::SUCCESS:
new(&success_) CreateDataSuccess(std::move(source.success_));
break;
    default:
      break;
}

  }
  ~CreateDataResult() {
switch (code_)
{
  case (int32_t)CreateDataResultCode::SUCCESS:
success_.~CreateDataSuccess();
break;
  default:
    break;
}
}

  CreateDataResult &operator=(const CreateDataResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CreateDataResultCode::SUCCESS:
success_ = source.success_;
break;
    default:
      break;
}
}
else {this->~CreateDataResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)CreateDataResultCode::SUCCESS:
new(&success_) CreateDataSuccess(source.success_);
break;
    default:
      break;
}
}
    return *this;
  }
  CreateDataResult &operator=(CreateDataResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CreateDataResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    default:
      break;
}
}
else {this->~CreateDataResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)CreateDataResultCode::SUCCESS:
new(&success_) CreateDataSuccess(std::move(source.success_));
break;
    default:
      break;
}
}
    return *this;
  }

  CreateDataResultCode code() const { return CreateDataResultCode(code_); }
  CreateDataResult &code(CreateDataResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  CreateDataSuccess &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateDataResult: success accessed when not selected");
  }
  const CreateDataSuccess &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateDataResult: success accessed when not selected");
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

#endif // !__XDR_OPERATION_CREATE_DATA_H_INCLUDED__
