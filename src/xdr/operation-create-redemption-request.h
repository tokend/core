// -*- C++ -*-
// Automatically generated from operation-create-redemption-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_CREATE_REDEMPTION_REQUEST_H_INCLUDED__
#define __XDR_OPERATION_CREATE_REDEMPTION_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/reviewable-request-redemption.h"

namespace stellar {

struct CreateRedemptionRequestOp  : xdr::xdr_abstract {
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
  RedemptionRequest redemptionRequest{};
  xdr::pointer<uint32> allTasks{};
  _ext_t ext{};

  CreateRedemptionRequestOp() = default;
  template<typename _reference_T,
           typename _redemptionRequest_T,
           typename _allTasks_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<string64, _reference_T>::value
                          && std::is_constructible<RedemptionRequest, _redemptionRequest_T>::value
                          && std::is_constructible<xdr::pointer<uint32>, _allTasks_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateRedemptionRequestOp(_reference_T &&_reference,
                                     _redemptionRequest_T &&_redemptionRequest,
                                     _allTasks_T &&_allTasks,
                                     _ext_T &&_ext)
    : reference(std::forward<_reference_T>(_reference)),
      redemptionRequest(std::forward<_redemptionRequest_T>(_redemptionRequest)),
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

enum class CreateRedemptionRequestResultCode : std::int32_t {
  SUCCESS = 0,
  INVALID_REDEMPTION = -1,
  REDEMPTION_TASKS_NOT_FOUND = -2,
  INVALID_CREATOR_DETAILS = -3,
  INVALID_AMOUNT = -4,
  INVALID_REFERENCE = -5,
  SOURCE_BALANCE_NOT_EXIST = -6,
  INCORRECT_PRECISION = -7,
  UNDERFUNDED = -8,
  REFERENCE_DUPLICATION = -9,
  DST_ACCOUNT_NOT_FOUND = -10,
  REDEMPTION_ZERO_TASKS_NOT_ALLOWED = -11,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateRedemptionRequestResultCode>
  : xdr_integral_base<::stellar::CreateRedemptionRequestResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::CreateRedemptionRequestResultCode val) {
    switch (val) {
    case ::stellar::CreateRedemptionRequestResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::CreateRedemptionRequestResultCode::INVALID_REDEMPTION:
      return "INVALID_REDEMPTION";
    case ::stellar::CreateRedemptionRequestResultCode::REDEMPTION_TASKS_NOT_FOUND:
      return "REDEMPTION_TASKS_NOT_FOUND";
    case ::stellar::CreateRedemptionRequestResultCode::INVALID_CREATOR_DETAILS:
      return "INVALID_CREATOR_DETAILS";
    case ::stellar::CreateRedemptionRequestResultCode::INVALID_AMOUNT:
      return "INVALID_AMOUNT";
    case ::stellar::CreateRedemptionRequestResultCode::INVALID_REFERENCE:
      return "INVALID_REFERENCE";
    case ::stellar::CreateRedemptionRequestResultCode::SOURCE_BALANCE_NOT_EXIST:
      return "SOURCE_BALANCE_NOT_EXIST";
    case ::stellar::CreateRedemptionRequestResultCode::INCORRECT_PRECISION:
      return "INCORRECT_PRECISION";
    case ::stellar::CreateRedemptionRequestResultCode::UNDERFUNDED:
      return "UNDERFUNDED";
    case ::stellar::CreateRedemptionRequestResultCode::REFERENCE_DUPLICATION:
      return "REFERENCE_DUPLICATION";
    case ::stellar::CreateRedemptionRequestResultCode::DST_ACCOUNT_NOT_FOUND:
      return "DST_ACCOUNT_NOT_FOUND";
    case ::stellar::CreateRedemptionRequestResultCode::REDEMPTION_ZERO_TASKS_NOT_ALLOWED:
      return "REDEMPTION_ZERO_TASKS_NOT_ALLOWED";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::CreateRedemptionRequestResultCode::SUCCESS,
      (int32_t)::stellar::CreateRedemptionRequestResultCode::INVALID_REDEMPTION,
      (int32_t)::stellar::CreateRedemptionRequestResultCode::REDEMPTION_TASKS_NOT_FOUND,
      (int32_t)::stellar::CreateRedemptionRequestResultCode::INVALID_CREATOR_DETAILS,
      (int32_t)::stellar::CreateRedemptionRequestResultCode::INVALID_AMOUNT,
      (int32_t)::stellar::CreateRedemptionRequestResultCode::INVALID_REFERENCE,
      (int32_t)::stellar::CreateRedemptionRequestResultCode::SOURCE_BALANCE_NOT_EXIST,
      (int32_t)::stellar::CreateRedemptionRequestResultCode::INCORRECT_PRECISION,
      (int32_t)::stellar::CreateRedemptionRequestResultCode::UNDERFUNDED,
      (int32_t)::stellar::CreateRedemptionRequestResultCode::REFERENCE_DUPLICATION,
      (int32_t)::stellar::CreateRedemptionRequestResultCode::DST_ACCOUNT_NOT_FOUND,
      (int32_t)::stellar::CreateRedemptionRequestResultCode::REDEMPTION_ZERO_TASKS_NOT_ALLOWED
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateRedemptionRequestSuccess  : xdr::xdr_abstract {
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

  CreateRedemptionRequestSuccess() = default;
  template<typename _requestID_T,
           typename _fulfilled_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<bool, _fulfilled_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateRedemptionRequestSuccess(_requestID_T &&_requestID,
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

struct CreateRedemptionRequestResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<CreateRedemptionRequestResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    CreateRedemptionRequestSuccess success_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<CreateRedemptionRequestResultCode> &_xdr_case_values() {
    static const std::vector<CreateRedemptionRequestResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)CreateRedemptionRequestResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)CreateRedemptionRequestResultCode::SUCCESS:
      _f(&CreateRedemptionRequestResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in CreateRedemptionRequestResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~CreateRedemptionRequestResult();
      code_ = which;switch (code_)
{
      case (int32_t)CreateRedemptionRequestResultCode::SUCCESS:
new(&success_) CreateRedemptionRequestSuccess{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit CreateRedemptionRequestResult(CreateRedemptionRequestResultCode which = CreateRedemptionRequestResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)CreateRedemptionRequestResultCode::SUCCESS:
new(&success_) CreateRedemptionRequestSuccess{};
break;
    default:
      break;
}

  }
  CreateRedemptionRequestResult(const CreateRedemptionRequestResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CreateRedemptionRequestResultCode::SUCCESS:
new(&success_) CreateRedemptionRequestSuccess(source.success_);
break;
    default:
      break;
}

  }
  CreateRedemptionRequestResult(CreateRedemptionRequestResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CreateRedemptionRequestResultCode::SUCCESS:
new(&success_) CreateRedemptionRequestSuccess(std::move(source.success_));
break;
    default:
      break;
}

  }
  ~CreateRedemptionRequestResult() {
switch (code_)
{
  case (int32_t)CreateRedemptionRequestResultCode::SUCCESS:
success_.~CreateRedemptionRequestSuccess();
break;
  default:
    break;
}
}

  CreateRedemptionRequestResult &operator=(const CreateRedemptionRequestResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CreateRedemptionRequestResultCode::SUCCESS:
success_ = source.success_;
break;
    default:
      break;
}
}
else {this->~CreateRedemptionRequestResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)CreateRedemptionRequestResultCode::SUCCESS:
new(&success_) CreateRedemptionRequestSuccess(source.success_);
break;
    default:
      break;
}
}
    return *this;
  }
  CreateRedemptionRequestResult &operator=(CreateRedemptionRequestResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CreateRedemptionRequestResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    default:
      break;
}
}
else {this->~CreateRedemptionRequestResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)CreateRedemptionRequestResultCode::SUCCESS:
new(&success_) CreateRedemptionRequestSuccess(std::move(source.success_));
break;
    default:
      break;
}
}
    return *this;
  }

  CreateRedemptionRequestResultCode code() const { return CreateRedemptionRequestResultCode(code_); }
  CreateRedemptionRequestResult &code(CreateRedemptionRequestResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  CreateRedemptionRequestSuccess &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateRedemptionRequestResult: success accessed when not selected");
  }
  const CreateRedemptionRequestSuccess &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateRedemptionRequestResult: success accessed when not selected");
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

#endif // !__XDR_OPERATION_CREATE_REDEMPTION_REQUEST_H_INCLUDED__
