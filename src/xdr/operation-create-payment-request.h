// -*- C++ -*-
// Automatically generated from operation-create-payment-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_CREATE_PAYMENT_REQUEST_H_INCLUDED__
#define __XDR_OPERATION_CREATE_PAYMENT_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"
#include "xdr/operation-payment.h"
#include "xdr/reviewable-request-payment.h"

namespace stellar {

struct CreatePaymentRequestOp  : xdr::xdr_abstract {
  CreatePaymentRequest request{};
  xdr::pointer<uint32> allTasks{};
  EmptyExt ext{};

  CreatePaymentRequestOp() = default;
  template<typename _request_T,
           typename _allTasks_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<CreatePaymentRequest, _request_T>::value
                          && std::is_constructible<xdr::pointer<uint32>, _allTasks_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit CreatePaymentRequestOp(_request_T &&_request,
                                  _allTasks_T &&_allTasks,
                                  _ext_T &&_ext)
    : request(std::forward<_request_T>(_request)),
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

enum class CreatePaymentRequestResultCode : std::int32_t {
  SUCCESS = 0,
  INVALID_PAYMENT = -1,
  PAYMENT_TASKS_NOT_FOUND = -2,
  INVALID_CREATOR_DETAILS = -3,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreatePaymentRequestResultCode>
  : xdr_integral_base<::stellar::CreatePaymentRequestResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::CreatePaymentRequestResultCode val) {
    switch (val) {
    case ::stellar::CreatePaymentRequestResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::CreatePaymentRequestResultCode::INVALID_PAYMENT:
      return "INVALID_PAYMENT";
    case ::stellar::CreatePaymentRequestResultCode::PAYMENT_TASKS_NOT_FOUND:
      return "PAYMENT_TASKS_NOT_FOUND";
    case ::stellar::CreatePaymentRequestResultCode::INVALID_CREATOR_DETAILS:
      return "INVALID_CREATOR_DETAILS";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::CreatePaymentRequestResultCode::SUCCESS,
      (int32_t)::stellar::CreatePaymentRequestResultCode::INVALID_PAYMENT,
      (int32_t)::stellar::CreatePaymentRequestResultCode::PAYMENT_TASKS_NOT_FOUND,
      (int32_t)::stellar::CreatePaymentRequestResultCode::INVALID_CREATOR_DETAILS
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreatePaymentRequestSuccessResult  : xdr::xdr_abstract {
  uint64 requestID{};
  bool fulfilled{};
  xdr::pointer<PaymentResult> paymentResult{};
  EmptyExt ext{};

  CreatePaymentRequestSuccessResult() = default;
  template<typename _requestID_T,
           typename _fulfilled_T,
           typename _paymentResult_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<bool, _fulfilled_T>::value
                          && std::is_constructible<xdr::pointer<PaymentResult>, _paymentResult_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit CreatePaymentRequestSuccessResult(_requestID_T &&_requestID,
                                             _fulfilled_T &&_fulfilled,
                                             _paymentResult_T &&_paymentResult,
                                             _ext_T &&_ext)
    : requestID(std::forward<_requestID_T>(_requestID)),
      fulfilled(std::forward<_fulfilled_T>(_fulfilled)),
      paymentResult(std::forward<_paymentResult_T>(_paymentResult)),
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

struct CreatePaymentRequestResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<CreatePaymentRequestResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    CreatePaymentRequestSuccessResult success_;
    PaymentResultCode paymentCode_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<CreatePaymentRequestResultCode> &_xdr_case_values() {
    static const std::vector<CreatePaymentRequestResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)CreatePaymentRequestResultCode::SUCCESS ? 1
      : which == (int32_t)CreatePaymentRequestResultCode::INVALID_PAYMENT ? 2
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)CreatePaymentRequestResultCode::SUCCESS:
      _f(&CreatePaymentRequestResult::success_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)CreatePaymentRequestResultCode::INVALID_PAYMENT:
      _f(&CreatePaymentRequestResult::paymentCode_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in CreatePaymentRequestResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~CreatePaymentRequestResult();
      code_ = which;switch (code_)
{
      case (int32_t)CreatePaymentRequestResultCode::SUCCESS:
new(&success_) CreatePaymentRequestSuccessResult{};
break;
      case (int32_t)CreatePaymentRequestResultCode::INVALID_PAYMENT:
new(&paymentCode_) PaymentResultCode{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit CreatePaymentRequestResult(CreatePaymentRequestResultCode which = CreatePaymentRequestResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)CreatePaymentRequestResultCode::SUCCESS:
new(&success_) CreatePaymentRequestSuccessResult{};
break;
    case (int32_t)CreatePaymentRequestResultCode::INVALID_PAYMENT:
new(&paymentCode_) PaymentResultCode{};
break;
    default:
      break;
}

  }
  CreatePaymentRequestResult(const CreatePaymentRequestResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CreatePaymentRequestResultCode::SUCCESS:
new(&success_) CreatePaymentRequestSuccessResult(source.success_);
break;
    case (int32_t)CreatePaymentRequestResultCode::INVALID_PAYMENT:
new(&paymentCode_) PaymentResultCode(source.paymentCode_);
break;
    default:
      break;
}

  }
  CreatePaymentRequestResult(CreatePaymentRequestResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CreatePaymentRequestResultCode::SUCCESS:
new(&success_) CreatePaymentRequestSuccessResult(std::move(source.success_));
break;
    case (int32_t)CreatePaymentRequestResultCode::INVALID_PAYMENT:
new(&paymentCode_) PaymentResultCode(std::move(source.paymentCode_));
break;
    default:
      break;
}

  }
  ~CreatePaymentRequestResult() {
switch (code_)
{
  case (int32_t)CreatePaymentRequestResultCode::SUCCESS:
success_.~CreatePaymentRequestSuccessResult();
break;
  case (int32_t)CreatePaymentRequestResultCode::INVALID_PAYMENT:
paymentCode_.~PaymentResultCode();
break;
  default:
    break;
}
}

  CreatePaymentRequestResult &operator=(const CreatePaymentRequestResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CreatePaymentRequestResultCode::SUCCESS:
success_ = source.success_;
break;
    case (int32_t)CreatePaymentRequestResultCode::INVALID_PAYMENT:
paymentCode_ = source.paymentCode_;
break;
    default:
      break;
}
}
else {this->~CreatePaymentRequestResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)CreatePaymentRequestResultCode::SUCCESS:
new(&success_) CreatePaymentRequestSuccessResult(source.success_);
break;
    case (int32_t)CreatePaymentRequestResultCode::INVALID_PAYMENT:
new(&paymentCode_) PaymentResultCode(source.paymentCode_);
break;
    default:
      break;
}
}
    return *this;
  }
  CreatePaymentRequestResult &operator=(CreatePaymentRequestResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CreatePaymentRequestResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    case (int32_t)CreatePaymentRequestResultCode::INVALID_PAYMENT:
paymentCode_ = std::move(source.paymentCode_);
break;
    default:
      break;
}
}
else {this->~CreatePaymentRequestResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)CreatePaymentRequestResultCode::SUCCESS:
new(&success_) CreatePaymentRequestSuccessResult(std::move(source.success_));
break;
    case (int32_t)CreatePaymentRequestResultCode::INVALID_PAYMENT:
new(&paymentCode_) PaymentResultCode(std::move(source.paymentCode_));
break;
    default:
      break;
}
}
    return *this;
  }

  CreatePaymentRequestResultCode code() const { return CreatePaymentRequestResultCode(code_); }
  CreatePaymentRequestResult &code(CreatePaymentRequestResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  CreatePaymentRequestSuccessResult &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreatePaymentRequestResult: success accessed when not selected");
  }
  const CreatePaymentRequestSuccessResult &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreatePaymentRequestResult: success accessed when not selected");
  }
  PaymentResultCode &paymentCode() {
    if (_xdr_field_number(code_) == 2)
      return paymentCode_;
    throw xdr::xdr_wrong_union("CreatePaymentRequestResult: paymentCode accessed when not selected");
  }
  const PaymentResultCode &paymentCode() const {
    if (_xdr_field_number(code_) == 2)
      return paymentCode_;
    throw xdr::xdr_wrong_union("CreatePaymentRequestResult: paymentCode accessed when not selected");
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

#endif // !__XDR_OPERATION_CREATE_PAYMENT_REQUEST_H_INCLUDED__
