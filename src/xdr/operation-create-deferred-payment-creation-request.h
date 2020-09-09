// -*- C++ -*-
// Automatically generated from operation-create-deferred-payment-creation-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_CREATE_DEFERRED_PAYMENT_CREATION_REQUEST_H_INCLUDED__
#define __XDR_OPERATION_CREATE_DEFERRED_PAYMENT_CREATION_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/ledger-entries.h"
#include "xdr/reviewable-request-create-deferred-payment.h"

namespace stellar {

struct CreateDeferredPaymentCreationRequestOp  : xdr::xdr_abstract {
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
  CreateDeferredPaymentRequest request{};
  xdr::pointer<uint32> allTasks{};
  _ext_t ext{};

  CreateDeferredPaymentCreationRequestOp() = default;
  template<typename _requestID_T,
           typename _request_T,
           typename _allTasks_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<CreateDeferredPaymentRequest, _request_T>::value
                          && std::is_constructible<xdr::pointer<uint32>, _allTasks_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateDeferredPaymentCreationRequestOp(_requestID_T &&_requestID,
                                                  _request_T &&_request,
                                                  _allTasks_T &&_allTasks,
                                                  _ext_T &&_ext)
    : requestID(std::forward<_requestID_T>(_requestID)),
      request(std::forward<_request_T>(_request)),
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

enum class CreateDeferredPaymentCreationRequestResultCode : std::int32_t {
  SUCCESS = 0,
  SOURCE_BALANCE_NOT_FOUND = -1,
  DESTINATION_ACCOUNT_NOT_FOUND = -2,
  INCORRECT_PRECISION = -3,
  UNDERFUNDED = -4,
  TASKS_NOT_FOUND = -5,
  INVALID_CREATOR_DETAILS = -6,
  INVALID_AMOUNT = -7,
  REQUEST_NOT_FOUND = -8,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateDeferredPaymentCreationRequestResultCode>
  : xdr_integral_base<::stellar::CreateDeferredPaymentCreationRequestResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::CreateDeferredPaymentCreationRequestResultCode val) {
    switch (val) {
    case ::stellar::CreateDeferredPaymentCreationRequestResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::CreateDeferredPaymentCreationRequestResultCode::SOURCE_BALANCE_NOT_FOUND:
      return "SOURCE_BALANCE_NOT_FOUND";
    case ::stellar::CreateDeferredPaymentCreationRequestResultCode::DESTINATION_ACCOUNT_NOT_FOUND:
      return "DESTINATION_ACCOUNT_NOT_FOUND";
    case ::stellar::CreateDeferredPaymentCreationRequestResultCode::INCORRECT_PRECISION:
      return "INCORRECT_PRECISION";
    case ::stellar::CreateDeferredPaymentCreationRequestResultCode::UNDERFUNDED:
      return "UNDERFUNDED";
    case ::stellar::CreateDeferredPaymentCreationRequestResultCode::TASKS_NOT_FOUND:
      return "TASKS_NOT_FOUND";
    case ::stellar::CreateDeferredPaymentCreationRequestResultCode::INVALID_CREATOR_DETAILS:
      return "INVALID_CREATOR_DETAILS";
    case ::stellar::CreateDeferredPaymentCreationRequestResultCode::INVALID_AMOUNT:
      return "INVALID_AMOUNT";
    case ::stellar::CreateDeferredPaymentCreationRequestResultCode::REQUEST_NOT_FOUND:
      return "REQUEST_NOT_FOUND";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::CreateDeferredPaymentCreationRequestResultCode::SUCCESS,
      (int32_t)::stellar::CreateDeferredPaymentCreationRequestResultCode::SOURCE_BALANCE_NOT_FOUND,
      (int32_t)::stellar::CreateDeferredPaymentCreationRequestResultCode::DESTINATION_ACCOUNT_NOT_FOUND,
      (int32_t)::stellar::CreateDeferredPaymentCreationRequestResultCode::INCORRECT_PRECISION,
      (int32_t)::stellar::CreateDeferredPaymentCreationRequestResultCode::UNDERFUNDED,
      (int32_t)::stellar::CreateDeferredPaymentCreationRequestResultCode::TASKS_NOT_FOUND,
      (int32_t)::stellar::CreateDeferredPaymentCreationRequestResultCode::INVALID_CREATOR_DETAILS,
      (int32_t)::stellar::CreateDeferredPaymentCreationRequestResultCode::INVALID_AMOUNT,
      (int32_t)::stellar::CreateDeferredPaymentCreationRequestResultCode::REQUEST_NOT_FOUND
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateDeferredPaymentCreationRequestSuccess  : xdr::xdr_abstract {
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
  uint64 deferredPaymentID{};
  _ext_t ext{};

  CreateDeferredPaymentCreationRequestSuccess() = default;
  template<typename _requestID_T,
           typename _fulfilled_T,
           typename _deferredPaymentID_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<bool, _fulfilled_T>::value
                          && std::is_constructible<uint64, _deferredPaymentID_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateDeferredPaymentCreationRequestSuccess(_requestID_T &&_requestID,
                                                       _fulfilled_T &&_fulfilled,
                                                       _deferredPaymentID_T &&_deferredPaymentID,
                                                       _ext_T &&_ext)
    : requestID(std::forward<_requestID_T>(_requestID)),
      fulfilled(std::forward<_fulfilled_T>(_fulfilled)),
      deferredPaymentID(std::forward<_deferredPaymentID_T>(_deferredPaymentID)),
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

struct CreateDeferredPaymentCreationRequestResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<CreateDeferredPaymentCreationRequestResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    CreateDeferredPaymentCreationRequestSuccess success_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<CreateDeferredPaymentCreationRequestResultCode> &_xdr_case_values() {
    static const std::vector<CreateDeferredPaymentCreationRequestResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)CreateDeferredPaymentCreationRequestResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)CreateDeferredPaymentCreationRequestResultCode::SUCCESS:
      _f(&CreateDeferredPaymentCreationRequestResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in CreateDeferredPaymentCreationRequestResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~CreateDeferredPaymentCreationRequestResult();
      code_ = which;switch (code_)
{
      case (int32_t)CreateDeferredPaymentCreationRequestResultCode::SUCCESS:
new(&success_) CreateDeferredPaymentCreationRequestSuccess{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit CreateDeferredPaymentCreationRequestResult(CreateDeferredPaymentCreationRequestResultCode which = CreateDeferredPaymentCreationRequestResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)CreateDeferredPaymentCreationRequestResultCode::SUCCESS:
new(&success_) CreateDeferredPaymentCreationRequestSuccess{};
break;
    default:
      break;
}

  }
  CreateDeferredPaymentCreationRequestResult(const CreateDeferredPaymentCreationRequestResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CreateDeferredPaymentCreationRequestResultCode::SUCCESS:
new(&success_) CreateDeferredPaymentCreationRequestSuccess(source.success_);
break;
    default:
      break;
}

  }
  CreateDeferredPaymentCreationRequestResult(CreateDeferredPaymentCreationRequestResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CreateDeferredPaymentCreationRequestResultCode::SUCCESS:
new(&success_) CreateDeferredPaymentCreationRequestSuccess(std::move(source.success_));
break;
    default:
      break;
}

  }
  ~CreateDeferredPaymentCreationRequestResult() {
switch (code_)
{
  case (int32_t)CreateDeferredPaymentCreationRequestResultCode::SUCCESS:
success_.~CreateDeferredPaymentCreationRequestSuccess();
break;
  default:
    break;
}
}

  CreateDeferredPaymentCreationRequestResult &operator=(const CreateDeferredPaymentCreationRequestResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CreateDeferredPaymentCreationRequestResultCode::SUCCESS:
success_ = source.success_;
break;
    default:
      break;
}
}
else {this->~CreateDeferredPaymentCreationRequestResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)CreateDeferredPaymentCreationRequestResultCode::SUCCESS:
new(&success_) CreateDeferredPaymentCreationRequestSuccess(source.success_);
break;
    default:
      break;
}
}
    return *this;
  }
  CreateDeferredPaymentCreationRequestResult &operator=(CreateDeferredPaymentCreationRequestResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CreateDeferredPaymentCreationRequestResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    default:
      break;
}
}
else {this->~CreateDeferredPaymentCreationRequestResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)CreateDeferredPaymentCreationRequestResultCode::SUCCESS:
new(&success_) CreateDeferredPaymentCreationRequestSuccess(std::move(source.success_));
break;
    default:
      break;
}
}
    return *this;
  }

  CreateDeferredPaymentCreationRequestResultCode code() const { return CreateDeferredPaymentCreationRequestResultCode(code_); }
  CreateDeferredPaymentCreationRequestResult &code(CreateDeferredPaymentCreationRequestResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  CreateDeferredPaymentCreationRequestSuccess &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateDeferredPaymentCreationRequestResult: success accessed when not selected");
  }
  const CreateDeferredPaymentCreationRequestSuccess &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateDeferredPaymentCreationRequestResult: success accessed when not selected");
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

#endif // !__XDR_OPERATION_CREATE_DEFERRED_PAYMENT_CREATION_REQUEST_H_INCLUDED__
