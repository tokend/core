// -*- C++ -*-
// Automatically generated from operation-create-close-deferred-payment-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_CREATE_CLOSE_DEFERRED_PAYMENT_REQUEST_H_INCLUDED__
#define __XDR_OPERATION_CREATE_CLOSE_DEFERRED_PAYMENT_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/ledger-entries.h"
#include "xdr/reviewable-request-close-deferred-payment.h"

namespace stellar {

struct CreateCloseDeferredPaymentRequestOp  : xdr::xdr_abstract {
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
  CloseDeferredPaymentRequest request{};
  xdr::pointer<uint32> allTasks{};
  _ext_t ext{};

  CreateCloseDeferredPaymentRequestOp() = default;
  template<typename _requestID_T,
           typename _request_T,
           typename _allTasks_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<CloseDeferredPaymentRequest, _request_T>::value
                          && std::is_constructible<xdr::pointer<uint32>, _allTasks_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateCloseDeferredPaymentRequestOp(_requestID_T &&_requestID,
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

enum class CreateCloseDeferredPaymentRequestResultCode : std::int32_t {
  SUCCESS = 0,
  UNDERFUNDED = -1,
  INVALID_CREATOR_DETAILS = -2,
  NOT_AUTHORIZED = -3,
  DESTINATION_ACCOUNT_NOT_FOUND = -4,
  INCORRECT_PRECISION = -5,
  ASSET_MISMATCH = -6,
  LINE_FULL = -7,
  TASKS_NOT_FOUND = -8,
  INVALID_AMOUNT = -9,
  DESTINATION_BALANCE_NOT_FOUND = -10,
  REQUEST_NOT_FOUND = -11,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateCloseDeferredPaymentRequestResultCode>
  : xdr_integral_base<::stellar::CreateCloseDeferredPaymentRequestResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::CreateCloseDeferredPaymentRequestResultCode val) {
    switch (val) {
    case ::stellar::CreateCloseDeferredPaymentRequestResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::CreateCloseDeferredPaymentRequestResultCode::UNDERFUNDED:
      return "UNDERFUNDED";
    case ::stellar::CreateCloseDeferredPaymentRequestResultCode::INVALID_CREATOR_DETAILS:
      return "INVALID_CREATOR_DETAILS";
    case ::stellar::CreateCloseDeferredPaymentRequestResultCode::NOT_AUTHORIZED:
      return "NOT_AUTHORIZED";
    case ::stellar::CreateCloseDeferredPaymentRequestResultCode::DESTINATION_ACCOUNT_NOT_FOUND:
      return "DESTINATION_ACCOUNT_NOT_FOUND";
    case ::stellar::CreateCloseDeferredPaymentRequestResultCode::INCORRECT_PRECISION:
      return "INCORRECT_PRECISION";
    case ::stellar::CreateCloseDeferredPaymentRequestResultCode::ASSET_MISMATCH:
      return "ASSET_MISMATCH";
    case ::stellar::CreateCloseDeferredPaymentRequestResultCode::LINE_FULL:
      return "LINE_FULL";
    case ::stellar::CreateCloseDeferredPaymentRequestResultCode::TASKS_NOT_FOUND:
      return "TASKS_NOT_FOUND";
    case ::stellar::CreateCloseDeferredPaymentRequestResultCode::INVALID_AMOUNT:
      return "INVALID_AMOUNT";
    case ::stellar::CreateCloseDeferredPaymentRequestResultCode::DESTINATION_BALANCE_NOT_FOUND:
      return "DESTINATION_BALANCE_NOT_FOUND";
    case ::stellar::CreateCloseDeferredPaymentRequestResultCode::REQUEST_NOT_FOUND:
      return "REQUEST_NOT_FOUND";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::CreateCloseDeferredPaymentRequestResultCode::SUCCESS,
      (int32_t)::stellar::CreateCloseDeferredPaymentRequestResultCode::UNDERFUNDED,
      (int32_t)::stellar::CreateCloseDeferredPaymentRequestResultCode::INVALID_CREATOR_DETAILS,
      (int32_t)::stellar::CreateCloseDeferredPaymentRequestResultCode::NOT_AUTHORIZED,
      (int32_t)::stellar::CreateCloseDeferredPaymentRequestResultCode::DESTINATION_ACCOUNT_NOT_FOUND,
      (int32_t)::stellar::CreateCloseDeferredPaymentRequestResultCode::INCORRECT_PRECISION,
      (int32_t)::stellar::CreateCloseDeferredPaymentRequestResultCode::ASSET_MISMATCH,
      (int32_t)::stellar::CreateCloseDeferredPaymentRequestResultCode::LINE_FULL,
      (int32_t)::stellar::CreateCloseDeferredPaymentRequestResultCode::TASKS_NOT_FOUND,
      (int32_t)::stellar::CreateCloseDeferredPaymentRequestResultCode::INVALID_AMOUNT,
      (int32_t)::stellar::CreateCloseDeferredPaymentRequestResultCode::DESTINATION_BALANCE_NOT_FOUND,
      (int32_t)::stellar::CreateCloseDeferredPaymentRequestResultCode::REQUEST_NOT_FOUND
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

enum class CloseDeferredPaymentEffect : std::int32_t {
  CHARGED = 0,
  DELETED = 1,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CloseDeferredPaymentEffect>
  : xdr_integral_base<::stellar::CloseDeferredPaymentEffect, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::CloseDeferredPaymentEffect val) {
    switch (val) {
    case ::stellar::CloseDeferredPaymentEffect::CHARGED:
      return "CHARGED";
    case ::stellar::CloseDeferredPaymentEffect::DELETED:
      return "DELETED";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::CloseDeferredPaymentEffect::CHARGED,
      (int32_t)::stellar::CloseDeferredPaymentEffect::DELETED
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CloseDeferredPaymentResult  : xdr::xdr_abstract {
  uint64 deferredPaymentID{};
  AccountID destination{};
  BalanceID destinationBalance{};
  CloseDeferredPaymentEffect effect{};
  uint64 deferredPaymentRemainder{};
  uint64 totalFee{};
  uint64 totalAmount{};
  EmptyExt ext{};

  CloseDeferredPaymentResult() = default;
  template<typename _deferredPaymentID_T,
           typename _destination_T,
           typename _destinationBalance_T,
           typename _effect_T,
           typename _deferredPaymentRemainder_T,
           typename _totalFee_T,
           typename _totalAmount_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _deferredPaymentID_T>::value
                          && std::is_constructible<AccountID, _destination_T>::value
                          && std::is_constructible<BalanceID, _destinationBalance_T>::value
                          && std::is_constructible<CloseDeferredPaymentEffect, _effect_T>::value
                          && std::is_constructible<uint64, _deferredPaymentRemainder_T>::value
                          && std::is_constructible<uint64, _totalFee_T>::value
                          && std::is_constructible<uint64, _totalAmount_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit CloseDeferredPaymentResult(_deferredPaymentID_T &&_deferredPaymentID,
                                      _destination_T &&_destination,
                                      _destinationBalance_T &&_destinationBalance,
                                      _effect_T &&_effect,
                                      _deferredPaymentRemainder_T &&_deferredPaymentRemainder,
                                      _totalFee_T &&_totalFee,
                                      _totalAmount_T &&_totalAmount,
                                      _ext_T &&_ext)
    : deferredPaymentID(std::forward<_deferredPaymentID_T>(_deferredPaymentID)),
      destination(std::forward<_destination_T>(_destination)),
      destinationBalance(std::forward<_destinationBalance_T>(_destinationBalance)),
      effect(std::forward<_effect_T>(_effect)),
      deferredPaymentRemainder(std::forward<_deferredPaymentRemainder_T>(_deferredPaymentRemainder)),
      totalFee(std::forward<_totalFee_T>(_totalFee)),
      totalAmount(std::forward<_totalAmount_T>(_totalAmount)),
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

struct CreateCloseDeferredPaymentRequestSuccess  : xdr::xdr_abstract {
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
  xdr::pointer<CloseDeferredPaymentResult> extendedResult{};
  _ext_t ext{};

  CreateCloseDeferredPaymentRequestSuccess() = default;
  template<typename _requestID_T,
           typename _fulfilled_T,
           typename _deferredPaymentID_T,
           typename _extendedResult_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<bool, _fulfilled_T>::value
                          && std::is_constructible<uint64, _deferredPaymentID_T>::value
                          && std::is_constructible<xdr::pointer<CloseDeferredPaymentResult>, _extendedResult_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateCloseDeferredPaymentRequestSuccess(_requestID_T &&_requestID,
                                                    _fulfilled_T &&_fulfilled,
                                                    _deferredPaymentID_T &&_deferredPaymentID,
                                                    _extendedResult_T &&_extendedResult,
                                                    _ext_T &&_ext)
    : requestID(std::forward<_requestID_T>(_requestID)),
      fulfilled(std::forward<_fulfilled_T>(_fulfilled)),
      deferredPaymentID(std::forward<_deferredPaymentID_T>(_deferredPaymentID)),
      extendedResult(std::forward<_extendedResult_T>(_extendedResult)),
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

struct CreateCloseDeferredPaymentRequestResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<CreateCloseDeferredPaymentRequestResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    CreateCloseDeferredPaymentRequestSuccess success_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<CreateCloseDeferredPaymentRequestResultCode> &_xdr_case_values() {
    static const std::vector<CreateCloseDeferredPaymentRequestResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)CreateCloseDeferredPaymentRequestResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)CreateCloseDeferredPaymentRequestResultCode::SUCCESS:
      _f(&CreateCloseDeferredPaymentRequestResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in CreateCloseDeferredPaymentRequestResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~CreateCloseDeferredPaymentRequestResult();
      code_ = which;switch (code_)
{
      case (int32_t)CreateCloseDeferredPaymentRequestResultCode::SUCCESS:
new(&success_) CreateCloseDeferredPaymentRequestSuccess{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit CreateCloseDeferredPaymentRequestResult(CreateCloseDeferredPaymentRequestResultCode which = CreateCloseDeferredPaymentRequestResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)CreateCloseDeferredPaymentRequestResultCode::SUCCESS:
new(&success_) CreateCloseDeferredPaymentRequestSuccess{};
break;
    default:
      break;
}

  }
  CreateCloseDeferredPaymentRequestResult(const CreateCloseDeferredPaymentRequestResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CreateCloseDeferredPaymentRequestResultCode::SUCCESS:
new(&success_) CreateCloseDeferredPaymentRequestSuccess(source.success_);
break;
    default:
      break;
}

  }
  CreateCloseDeferredPaymentRequestResult(CreateCloseDeferredPaymentRequestResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CreateCloseDeferredPaymentRequestResultCode::SUCCESS:
new(&success_) CreateCloseDeferredPaymentRequestSuccess(std::move(source.success_));
break;
    default:
      break;
}

  }
  ~CreateCloseDeferredPaymentRequestResult() {
switch (code_)
{
  case (int32_t)CreateCloseDeferredPaymentRequestResultCode::SUCCESS:
success_.~CreateCloseDeferredPaymentRequestSuccess();
break;
  default:
    break;
}
}

  CreateCloseDeferredPaymentRequestResult &operator=(const CreateCloseDeferredPaymentRequestResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CreateCloseDeferredPaymentRequestResultCode::SUCCESS:
success_ = source.success_;
break;
    default:
      break;
}
}
else {this->~CreateCloseDeferredPaymentRequestResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)CreateCloseDeferredPaymentRequestResultCode::SUCCESS:
new(&success_) CreateCloseDeferredPaymentRequestSuccess(source.success_);
break;
    default:
      break;
}
}
    return *this;
  }
  CreateCloseDeferredPaymentRequestResult &operator=(CreateCloseDeferredPaymentRequestResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CreateCloseDeferredPaymentRequestResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    default:
      break;
}
}
else {this->~CreateCloseDeferredPaymentRequestResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)CreateCloseDeferredPaymentRequestResultCode::SUCCESS:
new(&success_) CreateCloseDeferredPaymentRequestSuccess(std::move(source.success_));
break;
    default:
      break;
}
}
    return *this;
  }

  CreateCloseDeferredPaymentRequestResultCode code() const { return CreateCloseDeferredPaymentRequestResultCode(code_); }
  CreateCloseDeferredPaymentRequestResult &code(CreateCloseDeferredPaymentRequestResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  CreateCloseDeferredPaymentRequestSuccess &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateCloseDeferredPaymentRequestResult: success accessed when not selected");
  }
  const CreateCloseDeferredPaymentRequestSuccess &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateCloseDeferredPaymentRequestResult: success accessed when not selected");
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

#endif // !__XDR_OPERATION_CREATE_CLOSE_DEFERRED_PAYMENT_REQUEST_H_INCLUDED__
