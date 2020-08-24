// -*- C++ -*-
// Automatically generated from operation-create-data-creation-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_CREATE_DATA_CREATION_REQUEST_H_INCLUDED__
#define __XDR_OPERATION_CREATE_DATA_CREATION_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/reviewable-request-create-data.h"

namespace stellar {

struct CreateDataCreationRequestOp  : xdr::xdr_abstract {
  uint64 requestID{};
  DataCreationRequest dataCreationRequest{};
  xdr::pointer<uint32> allTasks{};
  EmptyExt ext{};

  CreateDataCreationRequestOp() = default;
  template<typename _requestID_T,
           typename _dataCreationRequest_T,
           typename _allTasks_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<DataCreationRequest, _dataCreationRequest_T>::value
                          && std::is_constructible<xdr::pointer<uint32>, _allTasks_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit CreateDataCreationRequestOp(_requestID_T &&_requestID,
                                       _dataCreationRequest_T &&_dataCreationRequest,
                                       _allTasks_T &&_allTasks,
                                       _ext_T &&_ext)
    : requestID(std::forward<_requestID_T>(_requestID)),
      dataCreationRequest(std::forward<_dataCreationRequest_T>(_dataCreationRequest)),
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

enum class CreateDataCreationRequestResultCode : std::int32_t {
  SUCCESS = 0,
  INVALID_VALUE = -1,
  CREATE_DATA_TASKS_NOT_FOUND = -2,
  REQUEST_NOT_FOUND = -3,
  INVALID_CREATOR_DETAILS = -4,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateDataCreationRequestResultCode>
  : xdr_integral_base<::stellar::CreateDataCreationRequestResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::CreateDataCreationRequestResultCode val) {
    switch (val) {
    case ::stellar::CreateDataCreationRequestResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::CreateDataCreationRequestResultCode::INVALID_VALUE:
      return "INVALID_VALUE";
    case ::stellar::CreateDataCreationRequestResultCode::CREATE_DATA_TASKS_NOT_FOUND:
      return "CREATE_DATA_TASKS_NOT_FOUND";
    case ::stellar::CreateDataCreationRequestResultCode::REQUEST_NOT_FOUND:
      return "REQUEST_NOT_FOUND";
    case ::stellar::CreateDataCreationRequestResultCode::INVALID_CREATOR_DETAILS:
      return "INVALID_CREATOR_DETAILS";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::CreateDataCreationRequestResultCode::SUCCESS,
      (int32_t)::stellar::CreateDataCreationRequestResultCode::INVALID_VALUE,
      (int32_t)::stellar::CreateDataCreationRequestResultCode::CREATE_DATA_TASKS_NOT_FOUND,
      (int32_t)::stellar::CreateDataCreationRequestResultCode::REQUEST_NOT_FOUND,
      (int32_t)::stellar::CreateDataCreationRequestResultCode::INVALID_CREATOR_DETAILS
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateDataCreationRequestResponse  : xdr::xdr_abstract {
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
  AccountID owner{};
  uint64 id{};
  uint64 type{};
  longstring value{};
  _ext_t ext{};

  CreateDataCreationRequestResponse() = default;
  template<typename _requestID_T,
           typename _fulfilled_T,
           typename _owner_T,
           typename _id_T,
           typename _type_T,
           typename _value_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<bool, _fulfilled_T>::value
                          && std::is_constructible<AccountID, _owner_T>::value
                          && std::is_constructible<uint64, _id_T>::value
                          && std::is_constructible<uint64, _type_T>::value
                          && std::is_constructible<longstring, _value_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateDataCreationRequestResponse(_requestID_T &&_requestID,
                                             _fulfilled_T &&_fulfilled,
                                             _owner_T &&_owner,
                                             _id_T &&_id,
                                             _type_T &&_type,
                                             _value_T &&_value,
                                             _ext_T &&_ext)
    : requestID(std::forward<_requestID_T>(_requestID)),
      fulfilled(std::forward<_fulfilled_T>(_fulfilled)),
      owner(std::forward<_owner_T>(_owner)),
      id(std::forward<_id_T>(_id)),
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

struct CreateDataCreationRequestResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<CreateDataCreationRequestResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    CreateDataCreationRequestResponse createDataCreationRequestResponse_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<CreateDataCreationRequestResultCode> &_xdr_case_values() {
    static const std::vector<CreateDataCreationRequestResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)CreateDataCreationRequestResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)CreateDataCreationRequestResultCode::SUCCESS:
      _f(&CreateDataCreationRequestResult::createDataCreationRequestResponse_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in CreateDataCreationRequestResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~CreateDataCreationRequestResult();
      code_ = which;switch (code_)
{
      case (int32_t)CreateDataCreationRequestResultCode::SUCCESS:
new(&createDataCreationRequestResponse_) CreateDataCreationRequestResponse{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit CreateDataCreationRequestResult(CreateDataCreationRequestResultCode which = CreateDataCreationRequestResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)CreateDataCreationRequestResultCode::SUCCESS:
new(&createDataCreationRequestResponse_) CreateDataCreationRequestResponse{};
break;
    default:
      break;
}

  }
  CreateDataCreationRequestResult(const CreateDataCreationRequestResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CreateDataCreationRequestResultCode::SUCCESS:
new(&createDataCreationRequestResponse_) CreateDataCreationRequestResponse(source.createDataCreationRequestResponse_);
break;
    default:
      break;
}

  }
  CreateDataCreationRequestResult(CreateDataCreationRequestResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CreateDataCreationRequestResultCode::SUCCESS:
new(&createDataCreationRequestResponse_) CreateDataCreationRequestResponse(std::move(source.createDataCreationRequestResponse_));
break;
    default:
      break;
}

  }
  ~CreateDataCreationRequestResult() {
switch (code_)
{
  case (int32_t)CreateDataCreationRequestResultCode::SUCCESS:
createDataCreationRequestResponse_.~CreateDataCreationRequestResponse();
break;
  default:
    break;
}
}

  CreateDataCreationRequestResult &operator=(const CreateDataCreationRequestResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CreateDataCreationRequestResultCode::SUCCESS:
createDataCreationRequestResponse_ = source.createDataCreationRequestResponse_;
break;
    default:
      break;
}
}
else {this->~CreateDataCreationRequestResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)CreateDataCreationRequestResultCode::SUCCESS:
new(&createDataCreationRequestResponse_) CreateDataCreationRequestResponse(source.createDataCreationRequestResponse_);
break;
    default:
      break;
}
}
    return *this;
  }
  CreateDataCreationRequestResult &operator=(CreateDataCreationRequestResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CreateDataCreationRequestResultCode::SUCCESS:
createDataCreationRequestResponse_ = std::move(source.createDataCreationRequestResponse_);
break;
    default:
      break;
}
}
else {this->~CreateDataCreationRequestResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)CreateDataCreationRequestResultCode::SUCCESS:
new(&createDataCreationRequestResponse_) CreateDataCreationRequestResponse(std::move(source.createDataCreationRequestResponse_));
break;
    default:
      break;
}
}
    return *this;
  }

  CreateDataCreationRequestResultCode code() const { return CreateDataCreationRequestResultCode(code_); }
  CreateDataCreationRequestResult &code(CreateDataCreationRequestResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  CreateDataCreationRequestResponse &createDataCreationRequestResponse() {
    if (_xdr_field_number(code_) == 1)
      return createDataCreationRequestResponse_;
    throw xdr::xdr_wrong_union("CreateDataCreationRequestResult: createDataCreationRequestResponse accessed when not selected");
  }
  const CreateDataCreationRequestResponse &createDataCreationRequestResponse() const {
    if (_xdr_field_number(code_) == 1)
      return createDataCreationRequestResponse_;
    throw xdr::xdr_wrong_union("CreateDataCreationRequestResult: createDataCreationRequestResponse accessed when not selected");
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

#endif // !__XDR_OPERATION_CREATE_DATA_CREATION_REQUEST_H_INCLUDED__
