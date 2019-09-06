// -*- C++ -*-
// Automatically generated from operation-create-AML-alert-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_CREATE_AML_ALERT_REQUEST_H_INCLUDED__
#define __XDR_OPERATION_CREATE_AML_ALERT_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/reviewable-request-AML-alert.h"

namespace stellar {

struct CreateAMLAlertRequestOp  : xdr::xdr_abstract {
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

  string64 reference{};
  AMLAlertRequest amlAlertRequest{};
  xdr::pointer<uint32> allTasks{};
  _ext_t ext{};

  CreateAMLAlertRequestOp() = default;
  template<typename _reference_T,
           typename _amlAlertRequest_T,
           typename _allTasks_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<string64, _reference_T>::value
                          && std::is_constructible<AMLAlertRequest, _amlAlertRequest_T>::value
                          && std::is_constructible<xdr::pointer<uint32>, _allTasks_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateAMLAlertRequestOp(_reference_T &&_reference,
                                   _amlAlertRequest_T &&_amlAlertRequest,
                                   _allTasks_T &&_allTasks,
                                   _ext_T &&_ext)
    : reference(std::forward<_reference_T>(_reference)),
      amlAlertRequest(std::forward<_amlAlertRequest_T>(_amlAlertRequest)),
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

enum class CreateAMLAlertRequestResultCode : std::int32_t {
  SUCCESS = 0,
  OLD_BALANCE_NOT_EXIST = 1,
  OLD_INVALID_CREATOR_DETAILS = 2,
  OLD_UNDERFUNDED = 3,
  OLD_REFERENCE_DUPLICATION = 4,
  OLD_INVALID_AMOUNT = 5,
  OLD_INCORRECT_PRECISION = 6,
  AML_ALERT_TASKS_NOT_FOUND = -1,
  BALANCE_NOT_EXIST = -2,
  INVALID_CREATOR_DETAILS = -3,
  UNDERFUNDED = -4,
  REFERENCE_DUPLICATION = -5,
  INVALID_AMOUNT = -6,
  INCORRECT_PRECISION = -7,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateAMLAlertRequestResultCode>
  : xdr_integral_base<::stellar::CreateAMLAlertRequestResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::CreateAMLAlertRequestResultCode val) {
    switch (val) {
    case ::stellar::CreateAMLAlertRequestResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::CreateAMLAlertRequestResultCode::OLD_BALANCE_NOT_EXIST:
      return "OLD_BALANCE_NOT_EXIST";
    case ::stellar::CreateAMLAlertRequestResultCode::OLD_INVALID_CREATOR_DETAILS:
      return "OLD_INVALID_CREATOR_DETAILS";
    case ::stellar::CreateAMLAlertRequestResultCode::OLD_UNDERFUNDED:
      return "OLD_UNDERFUNDED";
    case ::stellar::CreateAMLAlertRequestResultCode::OLD_REFERENCE_DUPLICATION:
      return "OLD_REFERENCE_DUPLICATION";
    case ::stellar::CreateAMLAlertRequestResultCode::OLD_INVALID_AMOUNT:
      return "OLD_INVALID_AMOUNT";
    case ::stellar::CreateAMLAlertRequestResultCode::OLD_INCORRECT_PRECISION:
      return "OLD_INCORRECT_PRECISION";
    case ::stellar::CreateAMLAlertRequestResultCode::AML_ALERT_TASKS_NOT_FOUND:
      return "AML_ALERT_TASKS_NOT_FOUND";
    case ::stellar::CreateAMLAlertRequestResultCode::BALANCE_NOT_EXIST:
      return "BALANCE_NOT_EXIST";
    case ::stellar::CreateAMLAlertRequestResultCode::INVALID_CREATOR_DETAILS:
      return "INVALID_CREATOR_DETAILS";
    case ::stellar::CreateAMLAlertRequestResultCode::UNDERFUNDED:
      return "UNDERFUNDED";
    case ::stellar::CreateAMLAlertRequestResultCode::REFERENCE_DUPLICATION:
      return "REFERENCE_DUPLICATION";
    case ::stellar::CreateAMLAlertRequestResultCode::INVALID_AMOUNT:
      return "INVALID_AMOUNT";
    case ::stellar::CreateAMLAlertRequestResultCode::INCORRECT_PRECISION:
      return "INCORRECT_PRECISION";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::CreateAMLAlertRequestResultCode::SUCCESS,
      (int32_t)::stellar::CreateAMLAlertRequestResultCode::OLD_BALANCE_NOT_EXIST,
      (int32_t)::stellar::CreateAMLAlertRequestResultCode::OLD_INVALID_CREATOR_DETAILS,
      (int32_t)::stellar::CreateAMLAlertRequestResultCode::OLD_UNDERFUNDED,
      (int32_t)::stellar::CreateAMLAlertRequestResultCode::OLD_REFERENCE_DUPLICATION,
      (int32_t)::stellar::CreateAMLAlertRequestResultCode::OLD_INVALID_AMOUNT,
      (int32_t)::stellar::CreateAMLAlertRequestResultCode::OLD_INCORRECT_PRECISION,
      (int32_t)::stellar::CreateAMLAlertRequestResultCode::AML_ALERT_TASKS_NOT_FOUND,
      (int32_t)::stellar::CreateAMLAlertRequestResultCode::BALANCE_NOT_EXIST,
      (int32_t)::stellar::CreateAMLAlertRequestResultCode::INVALID_CREATOR_DETAILS,
      (int32_t)::stellar::CreateAMLAlertRequestResultCode::UNDERFUNDED,
      (int32_t)::stellar::CreateAMLAlertRequestResultCode::REFERENCE_DUPLICATION,
      (int32_t)::stellar::CreateAMLAlertRequestResultCode::INVALID_AMOUNT,
      (int32_t)::stellar::CreateAMLAlertRequestResultCode::INCORRECT_PRECISION
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateAMLAlertRequestSuccess  : xdr::xdr_abstract {
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

  CreateAMLAlertRequestSuccess() = default;
  template<typename _requestID_T,
           typename _fulfilled_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<bool, _fulfilled_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateAMLAlertRequestSuccess(_requestID_T &&_requestID,
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

struct CreateAMLAlertRequestResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<CreateAMLAlertRequestResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    CreateAMLAlertRequestSuccess success_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<CreateAMLAlertRequestResultCode> &_xdr_case_values() {
    static const std::vector<CreateAMLAlertRequestResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)CreateAMLAlertRequestResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)CreateAMLAlertRequestResultCode::SUCCESS:
      _f(&CreateAMLAlertRequestResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in CreateAMLAlertRequestResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~CreateAMLAlertRequestResult();
      code_ = which;switch (code_)
{
      case (int32_t)CreateAMLAlertRequestResultCode::SUCCESS:
new(&success_) CreateAMLAlertRequestSuccess{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit CreateAMLAlertRequestResult(CreateAMLAlertRequestResultCode which = CreateAMLAlertRequestResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)CreateAMLAlertRequestResultCode::SUCCESS:
new(&success_) CreateAMLAlertRequestSuccess{};
break;
    default:
      break;
}

  }
  CreateAMLAlertRequestResult(const CreateAMLAlertRequestResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CreateAMLAlertRequestResultCode::SUCCESS:
new(&success_) CreateAMLAlertRequestSuccess(source.success_);
break;
    default:
      break;
}

  }
  CreateAMLAlertRequestResult(CreateAMLAlertRequestResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CreateAMLAlertRequestResultCode::SUCCESS:
new(&success_) CreateAMLAlertRequestSuccess(std::move(source.success_));
break;
    default:
      break;
}

  }
  ~CreateAMLAlertRequestResult() {
switch (code_)
{
  case (int32_t)CreateAMLAlertRequestResultCode::SUCCESS:
success_.~CreateAMLAlertRequestSuccess();
break;
  default:
    break;
}
}

  CreateAMLAlertRequestResult &operator=(const CreateAMLAlertRequestResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CreateAMLAlertRequestResultCode::SUCCESS:
success_ = source.success_;
break;
    default:
      break;
}
}
else {this->~CreateAMLAlertRequestResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)CreateAMLAlertRequestResultCode::SUCCESS:
new(&success_) CreateAMLAlertRequestSuccess(source.success_);
break;
    default:
      break;
}
}
    return *this;
  }
  CreateAMLAlertRequestResult &operator=(CreateAMLAlertRequestResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CreateAMLAlertRequestResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    default:
      break;
}
}
else {this->~CreateAMLAlertRequestResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)CreateAMLAlertRequestResultCode::SUCCESS:
new(&success_) CreateAMLAlertRequestSuccess(std::move(source.success_));
break;
    default:
      break;
}
}
    return *this;
  }

  CreateAMLAlertRequestResultCode code() const { return CreateAMLAlertRequestResultCode(code_); }
  CreateAMLAlertRequestResult &code(CreateAMLAlertRequestResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  CreateAMLAlertRequestSuccess &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateAMLAlertRequestResult: success accessed when not selected");
  }
  const CreateAMLAlertRequestSuccess &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateAMLAlertRequestResult: success accessed when not selected");
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

#endif // !__XDR_OPERATION_CREATE_AML_ALERT_REQUEST_H_INCLUDED__
