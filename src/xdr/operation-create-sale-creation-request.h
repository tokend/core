// -*- C++ -*-
// Automatically generated from operation-create-sale-creation-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_CREATE_SALE_CREATION_REQUEST_H_INCLUDED__
#define __XDR_OPERATION_CREATE_SALE_CREATION_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/ledger-entries.h"
#include "xdr/operation-review-request.h"

namespace stellar {

struct CreateSaleCreationRequestOp  : xdr::xdr_abstract {
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
  SaleCreationRequest request{};
  xdr::pointer<uint32> allTasks{};
  _ext_t ext{};

  CreateSaleCreationRequestOp() = default;
  template<typename _requestID_T,
           typename _request_T,
           typename _allTasks_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<SaleCreationRequest, _request_T>::value
                          && std::is_constructible<xdr::pointer<uint32>, _allTasks_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateSaleCreationRequestOp(_requestID_T &&_requestID,
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

enum class CreateSaleCreationRequestResultCode : std::int32_t {
  SUCCESS = 0,
  REQUEST_NOT_FOUND = -1,
  BASE_ASSET_OR_ASSET_REQUEST_NOT_FOUND = -2,
  QUOTE_ASSET_NOT_FOUND = -3,
  START_END_INVALID = -4,
  INVALID_END = -5,
  INVALID_PRICE = -6,
  INVALID_CAP = -7,
  INSUFFICIENT_MAX_ISSUANCE = -8,
  INVALID_ASSET_PAIR = -9,
  REQUEST_OR_SALE_ALREADY_EXISTS = -10,
  INSUFFICIENT_PREISSUED = -11,
  INVALID_CREATOR_DETAILS = -12,
  VERSION_IS_NOT_SUPPORTED_YET = -13,
  SALE_CREATE_TASKS_NOT_FOUND = -14,
  NOT_ALLOWED_TO_SET_TASKS_ON_UPDATE = -15,
  AUTO_REVIEW_FAILED = -16,
  EXCEEDED_MAX_RULES_SIZE = -17,
  GLOBAL_SPECIFIC_RULE_DUPLICATION = -18,
  ACCOUNT_SPECIFIC_RULE_DUPLICATION = -19,
  GLOBAL_SPECIFIC_RULE_REQUIRED = -20,
  ACCOUNT_NOT_FOUND = -21,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateSaleCreationRequestResultCode>
  : xdr_integral_base<::stellar::CreateSaleCreationRequestResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::CreateSaleCreationRequestResultCode val) {
    switch (val) {
    case ::stellar::CreateSaleCreationRequestResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::CreateSaleCreationRequestResultCode::REQUEST_NOT_FOUND:
      return "REQUEST_NOT_FOUND";
    case ::stellar::CreateSaleCreationRequestResultCode::BASE_ASSET_OR_ASSET_REQUEST_NOT_FOUND:
      return "BASE_ASSET_OR_ASSET_REQUEST_NOT_FOUND";
    case ::stellar::CreateSaleCreationRequestResultCode::QUOTE_ASSET_NOT_FOUND:
      return "QUOTE_ASSET_NOT_FOUND";
    case ::stellar::CreateSaleCreationRequestResultCode::START_END_INVALID:
      return "START_END_INVALID";
    case ::stellar::CreateSaleCreationRequestResultCode::INVALID_END:
      return "INVALID_END";
    case ::stellar::CreateSaleCreationRequestResultCode::INVALID_PRICE:
      return "INVALID_PRICE";
    case ::stellar::CreateSaleCreationRequestResultCode::INVALID_CAP:
      return "INVALID_CAP";
    case ::stellar::CreateSaleCreationRequestResultCode::INSUFFICIENT_MAX_ISSUANCE:
      return "INSUFFICIENT_MAX_ISSUANCE";
    case ::stellar::CreateSaleCreationRequestResultCode::INVALID_ASSET_PAIR:
      return "INVALID_ASSET_PAIR";
    case ::stellar::CreateSaleCreationRequestResultCode::REQUEST_OR_SALE_ALREADY_EXISTS:
      return "REQUEST_OR_SALE_ALREADY_EXISTS";
    case ::stellar::CreateSaleCreationRequestResultCode::INSUFFICIENT_PREISSUED:
      return "INSUFFICIENT_PREISSUED";
    case ::stellar::CreateSaleCreationRequestResultCode::INVALID_CREATOR_DETAILS:
      return "INVALID_CREATOR_DETAILS";
    case ::stellar::CreateSaleCreationRequestResultCode::VERSION_IS_NOT_SUPPORTED_YET:
      return "VERSION_IS_NOT_SUPPORTED_YET";
    case ::stellar::CreateSaleCreationRequestResultCode::SALE_CREATE_TASKS_NOT_FOUND:
      return "SALE_CREATE_TASKS_NOT_FOUND";
    case ::stellar::CreateSaleCreationRequestResultCode::NOT_ALLOWED_TO_SET_TASKS_ON_UPDATE:
      return "NOT_ALLOWED_TO_SET_TASKS_ON_UPDATE";
    case ::stellar::CreateSaleCreationRequestResultCode::AUTO_REVIEW_FAILED:
      return "AUTO_REVIEW_FAILED";
    case ::stellar::CreateSaleCreationRequestResultCode::EXCEEDED_MAX_RULES_SIZE:
      return "EXCEEDED_MAX_RULES_SIZE";
    case ::stellar::CreateSaleCreationRequestResultCode::GLOBAL_SPECIFIC_RULE_DUPLICATION:
      return "GLOBAL_SPECIFIC_RULE_DUPLICATION";
    case ::stellar::CreateSaleCreationRequestResultCode::ACCOUNT_SPECIFIC_RULE_DUPLICATION:
      return "ACCOUNT_SPECIFIC_RULE_DUPLICATION";
    case ::stellar::CreateSaleCreationRequestResultCode::GLOBAL_SPECIFIC_RULE_REQUIRED:
      return "GLOBAL_SPECIFIC_RULE_REQUIRED";
    case ::stellar::CreateSaleCreationRequestResultCode::ACCOUNT_NOT_FOUND:
      return "ACCOUNT_NOT_FOUND";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::SUCCESS,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::REQUEST_NOT_FOUND,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::BASE_ASSET_OR_ASSET_REQUEST_NOT_FOUND,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::QUOTE_ASSET_NOT_FOUND,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::START_END_INVALID,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::INVALID_END,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::INVALID_PRICE,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::INVALID_CAP,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::INSUFFICIENT_MAX_ISSUANCE,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::INVALID_ASSET_PAIR,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::REQUEST_OR_SALE_ALREADY_EXISTS,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::INSUFFICIENT_PREISSUED,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::INVALID_CREATOR_DETAILS,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::VERSION_IS_NOT_SUPPORTED_YET,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::SALE_CREATE_TASKS_NOT_FOUND,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::NOT_ALLOWED_TO_SET_TASKS_ON_UPDATE,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::AUTO_REVIEW_FAILED,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::EXCEEDED_MAX_RULES_SIZE,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::GLOBAL_SPECIFIC_RULE_DUPLICATION,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::ACCOUNT_SPECIFIC_RULE_DUPLICATION,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::GLOBAL_SPECIFIC_RULE_REQUIRED,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::ACCOUNT_NOT_FOUND
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateSaleCreationSuccess  : xdr::xdr_abstract {
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
  uint64 saleID{};
  bool fulfilled{};
  _ext_t ext{};

  CreateSaleCreationSuccess() = default;
  template<typename _requestID_T,
           typename _saleID_T,
           typename _fulfilled_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<uint64, _saleID_T>::value
                          && std::is_constructible<bool, _fulfilled_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateSaleCreationSuccess(_requestID_T &&_requestID,
                                     _saleID_T &&_saleID,
                                     _fulfilled_T &&_fulfilled,
                                     _ext_T &&_ext)
    : requestID(std::forward<_requestID_T>(_requestID)),
      saleID(std::forward<_saleID_T>(_saleID)),
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

struct CreateSaleCreationAutoReviewFailed  : xdr::xdr_abstract {
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

  ReviewRequestResult reviewRequestRequest{};
  _ext_t ext{};

  CreateSaleCreationAutoReviewFailed() = default;
  template<typename _reviewRequestRequest_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<ReviewRequestResult, _reviewRequestRequest_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateSaleCreationAutoReviewFailed(_reviewRequestRequest_T &&_reviewRequestRequest,
                                              _ext_T &&_ext)
    : reviewRequestRequest(std::forward<_reviewRequestRequest_T>(_reviewRequestRequest)),
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

struct CreateSaleCreationRequestResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<CreateSaleCreationRequestResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    CreateSaleCreationSuccess success_;
    CreateSaleCreationAutoReviewFailed autoReviewFailed_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<CreateSaleCreationRequestResultCode> &_xdr_case_values() {
    static const std::vector<CreateSaleCreationRequestResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)CreateSaleCreationRequestResultCode::SUCCESS ? 1
      : which == (int32_t)CreateSaleCreationRequestResultCode::AUTO_REVIEW_FAILED ? 2
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)CreateSaleCreationRequestResultCode::SUCCESS:
      _f(&CreateSaleCreationRequestResult::success_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)CreateSaleCreationRequestResultCode::AUTO_REVIEW_FAILED:
      _f(&CreateSaleCreationRequestResult::autoReviewFailed_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in CreateSaleCreationRequestResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~CreateSaleCreationRequestResult();
      code_ = which;switch (code_)
{
      case (int32_t)CreateSaleCreationRequestResultCode::SUCCESS:
new(&success_) CreateSaleCreationSuccess{};
break;
      case (int32_t)CreateSaleCreationRequestResultCode::AUTO_REVIEW_FAILED:
new(&autoReviewFailed_) CreateSaleCreationAutoReviewFailed{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit CreateSaleCreationRequestResult(CreateSaleCreationRequestResultCode which = CreateSaleCreationRequestResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)CreateSaleCreationRequestResultCode::SUCCESS:
new(&success_) CreateSaleCreationSuccess{};
break;
    case (int32_t)CreateSaleCreationRequestResultCode::AUTO_REVIEW_FAILED:
new(&autoReviewFailed_) CreateSaleCreationAutoReviewFailed{};
break;
    default:
      break;
}

  }
  CreateSaleCreationRequestResult(const CreateSaleCreationRequestResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CreateSaleCreationRequestResultCode::SUCCESS:
new(&success_) CreateSaleCreationSuccess(source.success_);
break;
    case (int32_t)CreateSaleCreationRequestResultCode::AUTO_REVIEW_FAILED:
new(&autoReviewFailed_) CreateSaleCreationAutoReviewFailed(source.autoReviewFailed_);
break;
    default:
      break;
}

  }
  CreateSaleCreationRequestResult(CreateSaleCreationRequestResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CreateSaleCreationRequestResultCode::SUCCESS:
new(&success_) CreateSaleCreationSuccess(std::move(source.success_));
break;
    case (int32_t)CreateSaleCreationRequestResultCode::AUTO_REVIEW_FAILED:
new(&autoReviewFailed_) CreateSaleCreationAutoReviewFailed(std::move(source.autoReviewFailed_));
break;
    default:
      break;
}

  }
  ~CreateSaleCreationRequestResult() {
switch (code_)
{
  case (int32_t)CreateSaleCreationRequestResultCode::SUCCESS:
success_.~CreateSaleCreationSuccess();
break;
  case (int32_t)CreateSaleCreationRequestResultCode::AUTO_REVIEW_FAILED:
autoReviewFailed_.~CreateSaleCreationAutoReviewFailed();
break;
  default:
    break;
}
}

  CreateSaleCreationRequestResult &operator=(const CreateSaleCreationRequestResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CreateSaleCreationRequestResultCode::SUCCESS:
success_ = source.success_;
break;
    case (int32_t)CreateSaleCreationRequestResultCode::AUTO_REVIEW_FAILED:
autoReviewFailed_ = source.autoReviewFailed_;
break;
    default:
      break;
}
}
else {this->~CreateSaleCreationRequestResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)CreateSaleCreationRequestResultCode::SUCCESS:
new(&success_) CreateSaleCreationSuccess(source.success_);
break;
    case (int32_t)CreateSaleCreationRequestResultCode::AUTO_REVIEW_FAILED:
new(&autoReviewFailed_) CreateSaleCreationAutoReviewFailed(source.autoReviewFailed_);
break;
    default:
      break;
}
}
    return *this;
  }
  CreateSaleCreationRequestResult &operator=(CreateSaleCreationRequestResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CreateSaleCreationRequestResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    case (int32_t)CreateSaleCreationRequestResultCode::AUTO_REVIEW_FAILED:
autoReviewFailed_ = std::move(source.autoReviewFailed_);
break;
    default:
      break;
}
}
else {this->~CreateSaleCreationRequestResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)CreateSaleCreationRequestResultCode::SUCCESS:
new(&success_) CreateSaleCreationSuccess(std::move(source.success_));
break;
    case (int32_t)CreateSaleCreationRequestResultCode::AUTO_REVIEW_FAILED:
new(&autoReviewFailed_) CreateSaleCreationAutoReviewFailed(std::move(source.autoReviewFailed_));
break;
    default:
      break;
}
}
    return *this;
  }

  CreateSaleCreationRequestResultCode code() const { return CreateSaleCreationRequestResultCode(code_); }
  CreateSaleCreationRequestResult &code(CreateSaleCreationRequestResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  CreateSaleCreationSuccess &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateSaleCreationRequestResult: success accessed when not selected");
  }
  const CreateSaleCreationSuccess &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateSaleCreationRequestResult: success accessed when not selected");
  }
  CreateSaleCreationAutoReviewFailed &autoReviewFailed() {
    if (_xdr_field_number(code_) == 2)
      return autoReviewFailed_;
    throw xdr::xdr_wrong_union("CreateSaleCreationRequestResult: autoReviewFailed accessed when not selected");
  }
  const CreateSaleCreationAutoReviewFailed &autoReviewFailed() const {
    if (_xdr_field_number(code_) == 2)
      return autoReviewFailed_;
    throw xdr::xdr_wrong_union("CreateSaleCreationRequestResult: autoReviewFailed accessed when not selected");
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

#endif // !__XDR_OPERATION_CREATE_SALE_CREATION_REQUEST_H_INCLUDED__
