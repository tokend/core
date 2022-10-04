// -*- C++ -*-
// Automatically generated from operation-update-data-owner.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_UPDATE_DATA_OWNER_H_INCLUDED__
#define __XDR_OPERATION_UPDATE_DATA_OWNER_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"

namespace stellar {

struct UpdateDataOwnerOp  : xdr::xdr_abstract {
  uint64 dataID{};
  AccountID newOwner{};
  EmptyExt ext{};

  UpdateDataOwnerOp() = default;
  template<typename _dataID_T,
           typename _newOwner_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _dataID_T>::value
                          && std::is_constructible<AccountID, _newOwner_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit UpdateDataOwnerOp(_dataID_T &&_dataID,
                             _newOwner_T &&_newOwner,
                             _ext_T &&_ext)
    : dataID(std::forward<_dataID_T>(_dataID)),
      newOwner(std::forward<_newOwner_T>(_newOwner)),
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

enum class UpdateDataOwnerResultCode : std::int32_t {
  SUCCESS = 0,
  NOT_FOUND = -1,
  NOT_AUTHORIZED = -2,
  USER_NOT_FOUND = -3,
  OLD_AND_NEW_USERS_ARE_SAME = -4,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::UpdateDataOwnerResultCode>
  : xdr_integral_base<::stellar::UpdateDataOwnerResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::UpdateDataOwnerResultCode val) {
    switch (val) {
    case ::stellar::UpdateDataOwnerResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::UpdateDataOwnerResultCode::NOT_FOUND:
      return "NOT_FOUND";
    case ::stellar::UpdateDataOwnerResultCode::NOT_AUTHORIZED:
      return "NOT_AUTHORIZED";
    case ::stellar::UpdateDataOwnerResultCode::USER_NOT_FOUND:
      return "USER_NOT_FOUND";
    case ::stellar::UpdateDataOwnerResultCode::OLD_AND_NEW_USERS_ARE_SAME:
      return "OLD_AND_NEW_USERS_ARE_SAME";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::UpdateDataOwnerResultCode::SUCCESS,
      (int32_t)::stellar::UpdateDataOwnerResultCode::NOT_FOUND,
      (int32_t)::stellar::UpdateDataOwnerResultCode::NOT_AUTHORIZED,
      (int32_t)::stellar::UpdateDataOwnerResultCode::USER_NOT_FOUND,
      (int32_t)::stellar::UpdateDataOwnerResultCode::OLD_AND_NEW_USERS_ARE_SAME
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct UpdateDataOwnerSuccess  : xdr::xdr_abstract {
  AccountID owner{};
  EmptyExt ext{};

  UpdateDataOwnerSuccess() = default;
  template<typename _owner_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<AccountID, _owner_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit UpdateDataOwnerSuccess(_owner_T &&_owner,
                                  _ext_T &&_ext)
    : owner(std::forward<_owner_T>(_owner)),
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

struct UpdateDataOwnerResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<UpdateDataOwnerResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    UpdateDataOwnerSuccess success_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<UpdateDataOwnerResultCode> &_xdr_case_values() {
    static const std::vector<UpdateDataOwnerResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)UpdateDataOwnerResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)UpdateDataOwnerResultCode::SUCCESS:
      _f(&UpdateDataOwnerResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in UpdateDataOwnerResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~UpdateDataOwnerResult();
      code_ = which;switch (code_)
{
      case (int32_t)UpdateDataOwnerResultCode::SUCCESS:
new(&success_) UpdateDataOwnerSuccess{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit UpdateDataOwnerResult(UpdateDataOwnerResultCode which = UpdateDataOwnerResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)UpdateDataOwnerResultCode::SUCCESS:
new(&success_) UpdateDataOwnerSuccess{};
break;
    default:
      break;
}

  }
  UpdateDataOwnerResult(const UpdateDataOwnerResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)UpdateDataOwnerResultCode::SUCCESS:
new(&success_) UpdateDataOwnerSuccess(source.success_);
break;
    default:
      break;
}

  }
  UpdateDataOwnerResult(UpdateDataOwnerResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)UpdateDataOwnerResultCode::SUCCESS:
new(&success_) UpdateDataOwnerSuccess(std::move(source.success_));
break;
    default:
      break;
}

  }
  ~UpdateDataOwnerResult() {
switch (code_)
{
  case (int32_t)UpdateDataOwnerResultCode::SUCCESS:
success_.~UpdateDataOwnerSuccess();
break;
  default:
    break;
}
}

  UpdateDataOwnerResult &operator=(const UpdateDataOwnerResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)UpdateDataOwnerResultCode::SUCCESS:
success_ = source.success_;
break;
    default:
      break;
}
}
else {this->~UpdateDataOwnerResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)UpdateDataOwnerResultCode::SUCCESS:
new(&success_) UpdateDataOwnerSuccess(source.success_);
break;
    default:
      break;
}
}
    return *this;
  }
  UpdateDataOwnerResult &operator=(UpdateDataOwnerResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)UpdateDataOwnerResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    default:
      break;
}
}
else {this->~UpdateDataOwnerResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)UpdateDataOwnerResultCode::SUCCESS:
new(&success_) UpdateDataOwnerSuccess(std::move(source.success_));
break;
    default:
      break;
}
}
    return *this;
  }

  UpdateDataOwnerResultCode code() const { return UpdateDataOwnerResultCode(code_); }
  UpdateDataOwnerResult &code(UpdateDataOwnerResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  UpdateDataOwnerSuccess &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("UpdateDataOwnerResult: success accessed when not selected");
  }
  const UpdateDataOwnerSuccess &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("UpdateDataOwnerResult: success accessed when not selected");
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

#endif // !__XDR_OPERATION_UPDATE_DATA_OWNER_H_INCLUDED__
