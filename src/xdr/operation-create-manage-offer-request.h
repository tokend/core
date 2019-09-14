// -*- C++ -*-
// Automatically generated from operation-create-manage-offer-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_CREATE_MANAGE_OFFER_REQUEST_H_INCLUDED__
#define __XDR_OPERATION_CREATE_MANAGE_OFFER_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/reviewable-request-manage-offer.h"
#include "xdr/operation-manage-offer.h"

namespace stellar {

struct CreateManageOfferRequestOp  : xdr::xdr_abstract {
  ManageOfferRequest request{};
  xdr::pointer<uint32> allTasks{};
  EmptyExt ext{};

  CreateManageOfferRequestOp() = default;
  template<typename _request_T,
           typename _allTasks_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<ManageOfferRequest, _request_T>::value
                          && std::is_constructible<xdr::pointer<uint32>, _allTasks_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit CreateManageOfferRequestOp(_request_T &&_request,
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

enum class CreateManageOfferRequestResultCode : std::int32_t {
  SUCCESS = 0,
  INVALID_OFFER = -1,
  MANAGE_OFFER_TASKS_NOT_FOUND = -2,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateManageOfferRequestResultCode>
  : xdr_integral_base<::stellar::CreateManageOfferRequestResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::CreateManageOfferRequestResultCode val) {
    switch (val) {
    case ::stellar::CreateManageOfferRequestResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::CreateManageOfferRequestResultCode::INVALID_OFFER:
      return "INVALID_OFFER";
    case ::stellar::CreateManageOfferRequestResultCode::MANAGE_OFFER_TASKS_NOT_FOUND:
      return "MANAGE_OFFER_TASKS_NOT_FOUND";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::CreateManageOfferRequestResultCode::SUCCESS,
      (int32_t)::stellar::CreateManageOfferRequestResultCode::INVALID_OFFER,
      (int32_t)::stellar::CreateManageOfferRequestResultCode::MANAGE_OFFER_TASKS_NOT_FOUND
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateManagerOfferRequestSuccessResult  : xdr::xdr_abstract {
  uint64 requestID{};
  bool fulfilled{};
  xdr::pointer<ManageOfferResult> manageOfferResult{};
  EmptyExt ext{};

  CreateManagerOfferRequestSuccessResult() = default;
  template<typename _requestID_T,
           typename _fulfilled_T,
           typename _manageOfferResult_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<bool, _fulfilled_T>::value
                          && std::is_constructible<xdr::pointer<ManageOfferResult>, _manageOfferResult_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit CreateManagerOfferRequestSuccessResult(_requestID_T &&_requestID,
                                                  _fulfilled_T &&_fulfilled,
                                                  _manageOfferResult_T &&_manageOfferResult,
                                                  _ext_T &&_ext)
    : requestID(std::forward<_requestID_T>(_requestID)),
      fulfilled(std::forward<_fulfilled_T>(_fulfilled)),
      manageOfferResult(std::forward<_manageOfferResult_T>(_manageOfferResult)),
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

struct CreateManageOfferRequestResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<CreateManageOfferRequestResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    CreateManagerOfferRequestSuccessResult success_;
    ManageOfferResultCode manageOfferCode_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<CreateManageOfferRequestResultCode> &_xdr_case_values() {
    static const std::vector<CreateManageOfferRequestResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)CreateManageOfferRequestResultCode::SUCCESS ? 1
      : which == (int32_t)CreateManageOfferRequestResultCode::INVALID_OFFER ? 2
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)CreateManageOfferRequestResultCode::SUCCESS:
      _f(&CreateManageOfferRequestResult::success_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)CreateManageOfferRequestResultCode::INVALID_OFFER:
      _f(&CreateManageOfferRequestResult::manageOfferCode_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in CreateManageOfferRequestResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~CreateManageOfferRequestResult();
      code_ = which;switch (code_)
{
      case (int32_t)CreateManageOfferRequestResultCode::SUCCESS:
new(&success_) CreateManagerOfferRequestSuccessResult{};
break;
      case (int32_t)CreateManageOfferRequestResultCode::INVALID_OFFER:
new(&manageOfferCode_) ManageOfferResultCode{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit CreateManageOfferRequestResult(CreateManageOfferRequestResultCode which = CreateManageOfferRequestResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)CreateManageOfferRequestResultCode::SUCCESS:
new(&success_) CreateManagerOfferRequestSuccessResult{};
break;
    case (int32_t)CreateManageOfferRequestResultCode::INVALID_OFFER:
new(&manageOfferCode_) ManageOfferResultCode{};
break;
    default:
      break;
}

  }
  CreateManageOfferRequestResult(const CreateManageOfferRequestResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CreateManageOfferRequestResultCode::SUCCESS:
new(&success_) CreateManagerOfferRequestSuccessResult(source.success_);
break;
    case (int32_t)CreateManageOfferRequestResultCode::INVALID_OFFER:
new(&manageOfferCode_) ManageOfferResultCode(source.manageOfferCode_);
break;
    default:
      break;
}

  }
  CreateManageOfferRequestResult(CreateManageOfferRequestResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CreateManageOfferRequestResultCode::SUCCESS:
new(&success_) CreateManagerOfferRequestSuccessResult(std::move(source.success_));
break;
    case (int32_t)CreateManageOfferRequestResultCode::INVALID_OFFER:
new(&manageOfferCode_) ManageOfferResultCode(std::move(source.manageOfferCode_));
break;
    default:
      break;
}

  }
  ~CreateManageOfferRequestResult() {
switch (code_)
{
  case (int32_t)CreateManageOfferRequestResultCode::SUCCESS:
success_.~CreateManagerOfferRequestSuccessResult();
break;
  case (int32_t)CreateManageOfferRequestResultCode::INVALID_OFFER:
manageOfferCode_.~ManageOfferResultCode();
break;
  default:
    break;
}
}

  CreateManageOfferRequestResult &operator=(const CreateManageOfferRequestResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CreateManageOfferRequestResultCode::SUCCESS:
success_ = source.success_;
break;
    case (int32_t)CreateManageOfferRequestResultCode::INVALID_OFFER:
manageOfferCode_ = source.manageOfferCode_;
break;
    default:
      break;
}
}
else {this->~CreateManageOfferRequestResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)CreateManageOfferRequestResultCode::SUCCESS:
new(&success_) CreateManagerOfferRequestSuccessResult(source.success_);
break;
    case (int32_t)CreateManageOfferRequestResultCode::INVALID_OFFER:
new(&manageOfferCode_) ManageOfferResultCode(source.manageOfferCode_);
break;
    default:
      break;
}
}
    return *this;
  }
  CreateManageOfferRequestResult &operator=(CreateManageOfferRequestResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CreateManageOfferRequestResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    case (int32_t)CreateManageOfferRequestResultCode::INVALID_OFFER:
manageOfferCode_ = std::move(source.manageOfferCode_);
break;
    default:
      break;
}
}
else {this->~CreateManageOfferRequestResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)CreateManageOfferRequestResultCode::SUCCESS:
new(&success_) CreateManagerOfferRequestSuccessResult(std::move(source.success_));
break;
    case (int32_t)CreateManageOfferRequestResultCode::INVALID_OFFER:
new(&manageOfferCode_) ManageOfferResultCode(std::move(source.manageOfferCode_));
break;
    default:
      break;
}
}
    return *this;
  }

  CreateManageOfferRequestResultCode code() const { return CreateManageOfferRequestResultCode(code_); }
  CreateManageOfferRequestResult &code(CreateManageOfferRequestResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  CreateManagerOfferRequestSuccessResult &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateManageOfferRequestResult: success accessed when not selected");
  }
  const CreateManagerOfferRequestSuccessResult &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateManageOfferRequestResult: success accessed when not selected");
  }
  ManageOfferResultCode &manageOfferCode() {
    if (_xdr_field_number(code_) == 2)
      return manageOfferCode_;
    throw xdr::xdr_wrong_union("CreateManageOfferRequestResult: manageOfferCode accessed when not selected");
  }
  const ManageOfferResultCode &manageOfferCode() const {
    if (_xdr_field_number(code_) == 2)
      return manageOfferCode_;
    throw xdr::xdr_wrong_union("CreateManageOfferRequestResult: manageOfferCode accessed when not selected");
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

#endif // !__XDR_OPERATION_CREATE_MANAGE_OFFER_REQUEST_H_INCLUDED__
