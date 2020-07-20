// -*- C++ -*-
// Automatically generated from operation-remove-data.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_REMOVE_DATA_H_INCLUDED__
#define __XDR_OPERATION_REMOVE_DATA_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"

namespace stellar {

struct RemoveDataOp  : xdr::xdr_abstract {
  uint64 dataID{};
  EmptyExt ext{};

  RemoveDataOp() = default;
  template<typename _dataID_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _dataID_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit RemoveDataOp(_dataID_T &&_dataID,
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

enum class RemoveDataResultCode : std::int32_t {
  SUCCESS = 0,
  NOT_FOUND = -1,
  NOT_AUTHORIZED = -2,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::RemoveDataResultCode>
  : xdr_integral_base<::stellar::RemoveDataResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::RemoveDataResultCode val) {
    switch (val) {
    case ::stellar::RemoveDataResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::RemoveDataResultCode::NOT_FOUND:
      return "NOT_FOUND";
    case ::stellar::RemoveDataResultCode::NOT_AUTHORIZED:
      return "NOT_AUTHORIZED";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::RemoveDataResultCode::SUCCESS,
      (int32_t)::stellar::RemoveDataResultCode::NOT_FOUND,
      (int32_t)::stellar::RemoveDataResultCode::NOT_AUTHORIZED
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct RemoveDataResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<RemoveDataResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    EmptyExt ext_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<RemoveDataResultCode> &_xdr_case_values() {
    static const std::vector<RemoveDataResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)RemoveDataResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)RemoveDataResultCode::SUCCESS:
      _f(&RemoveDataResult::ext_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in RemoveDataResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~RemoveDataResult();
      code_ = which;switch (code_)
{
      case (int32_t)RemoveDataResultCode::SUCCESS:
new(&ext_) EmptyExt{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit RemoveDataResult(RemoveDataResultCode which = RemoveDataResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)RemoveDataResultCode::SUCCESS:
new(&ext_) EmptyExt{};
break;
    default:
      break;
}

  }
  RemoveDataResult(const RemoveDataResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)RemoveDataResultCode::SUCCESS:
new(&ext_) EmptyExt(source.ext_);
break;
    default:
      break;
}

  }
  RemoveDataResult(RemoveDataResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)RemoveDataResultCode::SUCCESS:
new(&ext_) EmptyExt(std::move(source.ext_));
break;
    default:
      break;
}

  }
  ~RemoveDataResult() {
switch (code_)
{
  case (int32_t)RemoveDataResultCode::SUCCESS:
ext_.~EmptyExt();
break;
  default:
    break;
}
}

  RemoveDataResult &operator=(const RemoveDataResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)RemoveDataResultCode::SUCCESS:
ext_ = source.ext_;
break;
    default:
      break;
}
}
else {this->~RemoveDataResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)RemoveDataResultCode::SUCCESS:
new(&ext_) EmptyExt(source.ext_);
break;
    default:
      break;
}
}
    return *this;
  }
  RemoveDataResult &operator=(RemoveDataResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)RemoveDataResultCode::SUCCESS:
ext_ = std::move(source.ext_);
break;
    default:
      break;
}
}
else {this->~RemoveDataResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)RemoveDataResultCode::SUCCESS:
new(&ext_) EmptyExt(std::move(source.ext_));
break;
    default:
      break;
}
}
    return *this;
  }

  RemoveDataResultCode code() const { return RemoveDataResultCode(code_); }
  RemoveDataResult &code(RemoveDataResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  EmptyExt &ext() {
    if (_xdr_field_number(code_) == 1)
      return ext_;
    throw xdr::xdr_wrong_union("RemoveDataResult: ext accessed when not selected");
  }
  const EmptyExt &ext() const {
    if (_xdr_field_number(code_) == 1)
      return ext_;
    throw xdr::xdr_wrong_union("RemoveDataResult: ext accessed when not selected");
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

#endif // !__XDR_OPERATION_REMOVE_DATA_H_INCLUDED__
