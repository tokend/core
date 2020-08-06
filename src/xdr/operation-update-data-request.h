// -*- C++ -*-
// Automatically generated from operation-update-data-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_UPDATE_DATA_REQUEST_H_INCLUDED__
#define __XDR_OPERATION_UPDATE_DATA_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/reviewable-request-update-data.h"

namespace stellar {

struct UpdateDataRequestOp  : xdr::xdr_abstract {
  UpdateDataRequest updateDataRequest{};
  xdr::pointer<uint32> allTasks{};
  EmptyExt ext{};

  UpdateDataRequestOp() = default;
  template<typename _updateDataRequest_T,
           typename _allTasks_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<UpdateDataRequest, _updateDataRequest_T>::value
                          && std::is_constructible<xdr::pointer<uint32>, _allTasks_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit UpdateDataRequestOp(_updateDataRequest_T &&_updateDataRequest,
                               _allTasks_T &&_allTasks,
                               _ext_T &&_ext)
    : updateDataRequest(std::forward<_updateDataRequest_T>(_updateDataRequest)),
      allTasks(std::forward<_allTasks_T>(_allTasks)),
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

enum class UpdateDataRequestResultCode : std::int32_t {
  SUCCESS = 0,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::UpdateDataRequestResultCode>
  : xdr_integral_base<::stellar::UpdateDataRequestResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::UpdateDataRequestResultCode val) {
    switch (val) {
    case ::stellar::UpdateDataRequestResultCode::SUCCESS:
      return "SUCCESS";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::UpdateDataRequestResultCode::SUCCESS
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct UpdateDataRequestResponse  : xdr::xdr_abstract {
  struct _ext_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
  private:
    _xdr_case_type v_;
    union {
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<LedgerVersion> &_xdr_case_values() {
      static const std::vector<LedgerVersion> _xdr_disc_vec {
        LedgerVersion::EMPTY_VERSION
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)LedgerVersion::EMPTY_VERSION ? 0
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return v_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of v in _ext_t");
      if (fnum != _xdr_field_number(v_)) {
        this->~_ext_t();
        v_ = which;switch (v_)
{
        case (int32_t)LedgerVersion::EMPTY_VERSION:
          break;
}

      }
      else
        v_ = which;
    }
    explicit _ext_t(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}

    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}

    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}

    }
    ~_ext_t() {
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
      break;
}
}

    _ext_t &operator=(const _ext_t &source) {
      if (v_ == source.v_)
{
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
else {this->~_ext_t();
      v_ = source.v_;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
      return *this;
    }
    _ext_t &operator=(_ext_t &&source) {
      if (v_ == source.v_)
{
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
else {this->~_ext_t();
      v_ = std::move(source.v_);
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
      return *this;
    }

    LedgerVersion v() const { return LedgerVersion(v_); }
    _ext_t &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }
bool
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

  uint64 requestID{};
  bool fulfilled{};
  uint64 type{};
  longstring value{};
  _ext_t ext{};

  UpdateDataRequestResponse() = default;
  template<typename _requestID_T,
           typename _fulfilled_T,
           typename _type_T,
           typename _value_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<bool, _fulfilled_T>::value
                          && std::is_constructible<uint64, _type_T>::value
                          && std::is_constructible<longstring, _value_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit UpdateDataRequestResponse(_requestID_T &&_requestID,
                                     _fulfilled_T &&_fulfilled,
                                     _type_T &&_type,
                                     _value_T &&_value,
                                     _ext_T &&_ext)
    : requestID(std::forward<_requestID_T>(_requestID)),
      fulfilled(std::forward<_fulfilled_T>(_fulfilled)),
      type(std::forward<_type_T>(_type)),
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

struct UpdateDataRequestResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<UpdateDataRequestResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    UpdateDataRequestResponse updateDataRequestResponse_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<UpdateDataRequestResultCode> &_xdr_case_values() {
    static const std::vector<UpdateDataRequestResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)UpdateDataRequestResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)UpdateDataRequestResultCode::SUCCESS:
      _f(&UpdateDataRequestResult::updateDataRequestResponse_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in UpdateDataRequestResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~UpdateDataRequestResult();
      code_ = which;switch (code_)
{
      case (int32_t)UpdateDataRequestResultCode::SUCCESS:
new(&updateDataRequestResponse_) UpdateDataRequestResponse{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit UpdateDataRequestResult(UpdateDataRequestResultCode which = UpdateDataRequestResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)UpdateDataRequestResultCode::SUCCESS:
new(&updateDataRequestResponse_) UpdateDataRequestResponse{};
break;
    default:
      break;
}

  }
  UpdateDataRequestResult(const UpdateDataRequestResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)UpdateDataRequestResultCode::SUCCESS:
new(&updateDataRequestResponse_) UpdateDataRequestResponse(source.updateDataRequestResponse_);
break;
    default:
      break;
}

  }
  UpdateDataRequestResult(UpdateDataRequestResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)UpdateDataRequestResultCode::SUCCESS:
new(&updateDataRequestResponse_) UpdateDataRequestResponse(std::move(source.updateDataRequestResponse_));
break;
    default:
      break;
}

  }
  ~UpdateDataRequestResult() {
switch (code_)
{
  case (int32_t)UpdateDataRequestResultCode::SUCCESS:
updateDataRequestResponse_.~UpdateDataRequestResponse();
break;
  default:
    break;
}
}

  UpdateDataRequestResult &operator=(const UpdateDataRequestResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)UpdateDataRequestResultCode::SUCCESS:
updateDataRequestResponse_ = source.updateDataRequestResponse_;
break;
    default:
      break;
}
}
else {this->~UpdateDataRequestResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)UpdateDataRequestResultCode::SUCCESS:
new(&updateDataRequestResponse_) UpdateDataRequestResponse(source.updateDataRequestResponse_);
break;
    default:
      break;
}
}
    return *this;
  }
  UpdateDataRequestResult &operator=(UpdateDataRequestResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)UpdateDataRequestResultCode::SUCCESS:
updateDataRequestResponse_ = std::move(source.updateDataRequestResponse_);
break;
    default:
      break;
}
}
else {this->~UpdateDataRequestResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)UpdateDataRequestResultCode::SUCCESS:
new(&updateDataRequestResponse_) UpdateDataRequestResponse(std::move(source.updateDataRequestResponse_));
break;
    default:
      break;
}
}
    return *this;
  }

  UpdateDataRequestResultCode code() const { return UpdateDataRequestResultCode(code_); }
  UpdateDataRequestResult &code(UpdateDataRequestResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  UpdateDataRequestResponse &updateDataRequestResponse() {
    if (_xdr_field_number(code_) == 1)
      return updateDataRequestResponse_;
    throw xdr::xdr_wrong_union("UpdateDataRequestResult: updateDataRequestResponse accessed when not selected");
  }
  const UpdateDataRequestResponse &updateDataRequestResponse() const {
    if (_xdr_field_number(code_) == 1)
      return updateDataRequestResponse_;
    throw xdr::xdr_wrong_union("UpdateDataRequestResult: updateDataRequestResponse accessed when not selected");
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

#endif // !__XDR_OPERATION_UPDATE_DATA_REQUEST_H_INCLUDED__
