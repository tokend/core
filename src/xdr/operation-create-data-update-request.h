// -*- C++ -*-
// Automatically generated from operation-create-data-update-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_CREATE_DATA_UPDATE_REQUEST_H_INCLUDED__
#define __XDR_OPERATION_CREATE_DATA_UPDATE_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/reviewable-request-update-data.h"

namespace stellar {

struct CreateDataUpdateRequestOp  : xdr::xdr_abstract {
  uint64 requestID{};
  DataUpdateRequest dataUpdateRequest{};
  xdr::pointer<uint32> allTasks{};
  EmptyExt ext{};

  CreateDataUpdateRequestOp() = default;
  template<typename _requestID_T,
           typename _dataUpdateRequest_T,
           typename _allTasks_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<DataUpdateRequest, _dataUpdateRequest_T>::value
                          && std::is_constructible<xdr::pointer<uint32>, _allTasks_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit CreateDataUpdateRequestOp(_requestID_T &&_requestID,
                                     _dataUpdateRequest_T &&_dataUpdateRequest,
                                     _allTasks_T &&_allTasks,
                                     _ext_T &&_ext)
    : requestID(std::forward<_requestID_T>(_requestID)),
      dataUpdateRequest(std::forward<_dataUpdateRequest_T>(_dataUpdateRequest)),
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

enum class CreateDataUpdateRequestResultCode : std::int32_t {
  SUCCESS = 0,
  INVALID_VALUE = -1,
  UPDATE_DATA_TASKS_NOT_FOUND = -2,
  DATA_NOT_FOUND = -3,
  INVALID_CREATOR_DETAILS = -4,
  REQUEST_NOT_FOUND = -5,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateDataUpdateRequestResultCode>
  : xdr_integral_base<::stellar::CreateDataUpdateRequestResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::CreateDataUpdateRequestResultCode val) {
    switch (val) {
    case ::stellar::CreateDataUpdateRequestResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::CreateDataUpdateRequestResultCode::INVALID_VALUE:
      return "INVALID_VALUE";
    case ::stellar::CreateDataUpdateRequestResultCode::UPDATE_DATA_TASKS_NOT_FOUND:
      return "UPDATE_DATA_TASKS_NOT_FOUND";
    case ::stellar::CreateDataUpdateRequestResultCode::DATA_NOT_FOUND:
      return "DATA_NOT_FOUND";
    case ::stellar::CreateDataUpdateRequestResultCode::INVALID_CREATOR_DETAILS:
      return "INVALID_CREATOR_DETAILS";
    case ::stellar::CreateDataUpdateRequestResultCode::REQUEST_NOT_FOUND:
      return "REQUEST_NOT_FOUND";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::CreateDataUpdateRequestResultCode::SUCCESS,
      (int32_t)::stellar::CreateDataUpdateRequestResultCode::INVALID_VALUE,
      (int32_t)::stellar::CreateDataUpdateRequestResultCode::UPDATE_DATA_TASKS_NOT_FOUND,
      (int32_t)::stellar::CreateDataUpdateRequestResultCode::DATA_NOT_FOUND,
      (int32_t)::stellar::CreateDataUpdateRequestResultCode::INVALID_CREATOR_DETAILS,
      (int32_t)::stellar::CreateDataUpdateRequestResultCode::REQUEST_NOT_FOUND
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateDataUpdateRequestSuccess  : xdr::xdr_abstract {
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
  _ext_t ext{};

  CreateDataUpdateRequestSuccess() = default;
  template<typename _requestID_T,
           typename _fulfilled_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<bool, _fulfilled_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateDataUpdateRequestSuccess(_requestID_T &&_requestID,
                                          _fulfilled_T &&_fulfilled,
                                          _ext_T &&_ext)
    : requestID(std::forward<_requestID_T>(_requestID)),
      fulfilled(std::forward<_fulfilled_T>(_fulfilled)),
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

struct CreateDataUpdateRequestResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<CreateDataUpdateRequestResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    CreateDataUpdateRequestSuccess success_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<CreateDataUpdateRequestResultCode> &_xdr_case_values() {
    static const std::vector<CreateDataUpdateRequestResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)CreateDataUpdateRequestResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)CreateDataUpdateRequestResultCode::SUCCESS:
      _f(&CreateDataUpdateRequestResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in CreateDataUpdateRequestResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~CreateDataUpdateRequestResult();
      code_ = which;switch (code_)
{
      case (int32_t)CreateDataUpdateRequestResultCode::SUCCESS:
new(&success_) CreateDataUpdateRequestSuccess{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit CreateDataUpdateRequestResult(CreateDataUpdateRequestResultCode which = CreateDataUpdateRequestResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)CreateDataUpdateRequestResultCode::SUCCESS:
new(&success_) CreateDataUpdateRequestSuccess{};
break;
    default:
      break;
}

  }
  CreateDataUpdateRequestResult(const CreateDataUpdateRequestResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CreateDataUpdateRequestResultCode::SUCCESS:
new(&success_) CreateDataUpdateRequestSuccess(source.success_);
break;
    default:
      break;
}

  }
  CreateDataUpdateRequestResult(CreateDataUpdateRequestResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CreateDataUpdateRequestResultCode::SUCCESS:
new(&success_) CreateDataUpdateRequestSuccess(std::move(source.success_));
break;
    default:
      break;
}

  }
  ~CreateDataUpdateRequestResult() {
switch (code_)
{
  case (int32_t)CreateDataUpdateRequestResultCode::SUCCESS:
success_.~CreateDataUpdateRequestSuccess();
break;
  default:
    break;
}
}

  CreateDataUpdateRequestResult &operator=(const CreateDataUpdateRequestResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CreateDataUpdateRequestResultCode::SUCCESS:
success_ = source.success_;
break;
    default:
      break;
}
}
else {this->~CreateDataUpdateRequestResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)CreateDataUpdateRequestResultCode::SUCCESS:
new(&success_) CreateDataUpdateRequestSuccess(source.success_);
break;
    default:
      break;
}
}
    return *this;
  }
  CreateDataUpdateRequestResult &operator=(CreateDataUpdateRequestResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CreateDataUpdateRequestResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    default:
      break;
}
}
else {this->~CreateDataUpdateRequestResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)CreateDataUpdateRequestResultCode::SUCCESS:
new(&success_) CreateDataUpdateRequestSuccess(std::move(source.success_));
break;
    default:
      break;
}
}
    return *this;
  }

  CreateDataUpdateRequestResultCode code() const { return CreateDataUpdateRequestResultCode(code_); }
  CreateDataUpdateRequestResult &code(CreateDataUpdateRequestResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  CreateDataUpdateRequestSuccess &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateDataUpdateRequestResult: success accessed when not selected");
  }
  const CreateDataUpdateRequestSuccess &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateDataUpdateRequestResult: success accessed when not selected");
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

#endif // !__XDR_OPERATION_CREATE_DATA_UPDATE_REQUEST_H_INCLUDED__
