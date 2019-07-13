// -*- C++ -*-
// Automatically generated from operation-create-issuance-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_CREATE_ISSUANCE_REQUEST_H_INCLUDED__
#define __XDR_OPERATION_CREATE_ISSUANCE_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/ledger-entries.h"

namespace stellar {

struct CreateIssuanceRequestOp  : xdr::xdr_abstract {
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

  IssuanceRequest request{};
  string64 reference{};
  xdr::pointer<uint32> allTasks{};
  _ext_t ext{};

  CreateIssuanceRequestOp() = default;
  template<typename _request_T,
           typename _reference_T,
           typename _allTasks_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<IssuanceRequest, _request_T>::value
                          && std::is_constructible<string64, _reference_T>::value
                          && std::is_constructible<xdr::pointer<uint32>, _allTasks_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateIssuanceRequestOp(_request_T &&_request,
                                   _reference_T &&_reference,
                                   _allTasks_T &&_allTasks,
                                   _ext_T &&_ext)
    : request(std::forward<_request_T>(_request)),
      reference(std::forward<_reference_T>(_reference)),
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

enum class CreateIssuanceRequestResultCode : std::int32_t {
  SUCCESS = 0,
  ASSET_NOT_FOUND = -1,
  INVALID_AMOUNT = -2,
  REFERENCE_DUPLICATION = -3,
  NO_COUNTERPARTY = -4,
  NOT_AUTHORIZED = -5,
  EXCEEDS_MAX_ISSUANCE_AMOUNT = -6,
  RECEIVER_FULL_LINE = -7,
  INVALID_CREATOR_DETAILS = -8,
  FEE_EXCEEDS_AMOUNT = -9,
  REQUIRES_KYC = -10,
  REQUIRES_VERIFICATION = -11,
  ISSUANCE_TASKS_NOT_FOUND = -12,
  SYSTEM_TASKS_NOT_ALLOWED = -13,
  INVALID_AMOUNT_PRECISION = -14,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateIssuanceRequestResultCode>
  : xdr_integral_base<::stellar::CreateIssuanceRequestResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::CreateIssuanceRequestResultCode val) {
    switch (val) {
    case ::stellar::CreateIssuanceRequestResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::CreateIssuanceRequestResultCode::ASSET_NOT_FOUND:
      return "ASSET_NOT_FOUND";
    case ::stellar::CreateIssuanceRequestResultCode::INVALID_AMOUNT:
      return "INVALID_AMOUNT";
    case ::stellar::CreateIssuanceRequestResultCode::REFERENCE_DUPLICATION:
      return "REFERENCE_DUPLICATION";
    case ::stellar::CreateIssuanceRequestResultCode::NO_COUNTERPARTY:
      return "NO_COUNTERPARTY";
    case ::stellar::CreateIssuanceRequestResultCode::NOT_AUTHORIZED:
      return "NOT_AUTHORIZED";
    case ::stellar::CreateIssuanceRequestResultCode::EXCEEDS_MAX_ISSUANCE_AMOUNT:
      return "EXCEEDS_MAX_ISSUANCE_AMOUNT";
    case ::stellar::CreateIssuanceRequestResultCode::RECEIVER_FULL_LINE:
      return "RECEIVER_FULL_LINE";
    case ::stellar::CreateIssuanceRequestResultCode::INVALID_CREATOR_DETAILS:
      return "INVALID_CREATOR_DETAILS";
    case ::stellar::CreateIssuanceRequestResultCode::FEE_EXCEEDS_AMOUNT:
      return "FEE_EXCEEDS_AMOUNT";
    case ::stellar::CreateIssuanceRequestResultCode::REQUIRES_KYC:
      return "REQUIRES_KYC";
    case ::stellar::CreateIssuanceRequestResultCode::REQUIRES_VERIFICATION:
      return "REQUIRES_VERIFICATION";
    case ::stellar::CreateIssuanceRequestResultCode::ISSUANCE_TASKS_NOT_FOUND:
      return "ISSUANCE_TASKS_NOT_FOUND";
    case ::stellar::CreateIssuanceRequestResultCode::SYSTEM_TASKS_NOT_ALLOWED:
      return "SYSTEM_TASKS_NOT_ALLOWED";
    case ::stellar::CreateIssuanceRequestResultCode::INVALID_AMOUNT_PRECISION:
      return "INVALID_AMOUNT_PRECISION";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::CreateIssuanceRequestResultCode::SUCCESS,
      (int32_t)::stellar::CreateIssuanceRequestResultCode::ASSET_NOT_FOUND,
      (int32_t)::stellar::CreateIssuanceRequestResultCode::INVALID_AMOUNT,
      (int32_t)::stellar::CreateIssuanceRequestResultCode::REFERENCE_DUPLICATION,
      (int32_t)::stellar::CreateIssuanceRequestResultCode::NO_COUNTERPARTY,
      (int32_t)::stellar::CreateIssuanceRequestResultCode::NOT_AUTHORIZED,
      (int32_t)::stellar::CreateIssuanceRequestResultCode::EXCEEDS_MAX_ISSUANCE_AMOUNT,
      (int32_t)::stellar::CreateIssuanceRequestResultCode::RECEIVER_FULL_LINE,
      (int32_t)::stellar::CreateIssuanceRequestResultCode::INVALID_CREATOR_DETAILS,
      (int32_t)::stellar::CreateIssuanceRequestResultCode::FEE_EXCEEDS_AMOUNT,
      (int32_t)::stellar::CreateIssuanceRequestResultCode::REQUIRES_KYC,
      (int32_t)::stellar::CreateIssuanceRequestResultCode::REQUIRES_VERIFICATION,
      (int32_t)::stellar::CreateIssuanceRequestResultCode::ISSUANCE_TASKS_NOT_FOUND,
      (int32_t)::stellar::CreateIssuanceRequestResultCode::SYSTEM_TASKS_NOT_ALLOWED,
      (int32_t)::stellar::CreateIssuanceRequestResultCode::INVALID_AMOUNT_PRECISION
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateIssuanceRequestSuccess  : xdr::xdr_abstract {
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
  AccountID receiver{};
  bool fulfilled{};
  Fee fee{};
  _ext_t ext{};

  CreateIssuanceRequestSuccess() = default;
  template<typename _requestID_T,
           typename _receiver_T,
           typename _fulfilled_T,
           typename _fee_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<AccountID, _receiver_T>::value
                          && std::is_constructible<bool, _fulfilled_T>::value
                          && std::is_constructible<Fee, _fee_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateIssuanceRequestSuccess(_requestID_T &&_requestID,
                                        _receiver_T &&_receiver,
                                        _fulfilled_T &&_fulfilled,
                                        _fee_T &&_fee,
                                        _ext_T &&_ext)
    : requestID(std::forward<_requestID_T>(_requestID)),
      receiver(std::forward<_receiver_T>(_receiver)),
      fulfilled(std::forward<_fulfilled_T>(_fulfilled)),
      fee(std::forward<_fee_T>(_fee)),
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

struct CreateIssuanceRequestResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<CreateIssuanceRequestResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    CreateIssuanceRequestSuccess success_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<CreateIssuanceRequestResultCode> &_xdr_case_values() {
    static const std::vector<CreateIssuanceRequestResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)CreateIssuanceRequestResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)CreateIssuanceRequestResultCode::SUCCESS:
      _f(&CreateIssuanceRequestResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in CreateIssuanceRequestResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~CreateIssuanceRequestResult();
      code_ = which;switch (code_)
{
      case (int32_t)CreateIssuanceRequestResultCode::SUCCESS:
new(&success_) CreateIssuanceRequestSuccess{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit CreateIssuanceRequestResult(CreateIssuanceRequestResultCode which = CreateIssuanceRequestResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)CreateIssuanceRequestResultCode::SUCCESS:
new(&success_) CreateIssuanceRequestSuccess{};
break;
    default:
      break;
}

  }
  CreateIssuanceRequestResult(const CreateIssuanceRequestResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CreateIssuanceRequestResultCode::SUCCESS:
new(&success_) CreateIssuanceRequestSuccess(source.success_);
break;
    default:
      break;
}

  }
  CreateIssuanceRequestResult(CreateIssuanceRequestResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CreateIssuanceRequestResultCode::SUCCESS:
new(&success_) CreateIssuanceRequestSuccess(std::move(source.success_));
break;
    default:
      break;
}

  }
  ~CreateIssuanceRequestResult() {
switch (code_)
{
  case (int32_t)CreateIssuanceRequestResultCode::SUCCESS:
success_.~CreateIssuanceRequestSuccess();
break;
  default:
    break;
}
}

  CreateIssuanceRequestResult &operator=(const CreateIssuanceRequestResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CreateIssuanceRequestResultCode::SUCCESS:
success_ = source.success_;
break;
    default:
      break;
}
}
else {this->~CreateIssuanceRequestResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)CreateIssuanceRequestResultCode::SUCCESS:
new(&success_) CreateIssuanceRequestSuccess(source.success_);
break;
    default:
      break;
}
}
    return *this;
  }
  CreateIssuanceRequestResult &operator=(CreateIssuanceRequestResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CreateIssuanceRequestResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    default:
      break;
}
}
else {this->~CreateIssuanceRequestResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)CreateIssuanceRequestResultCode::SUCCESS:
new(&success_) CreateIssuanceRequestSuccess(std::move(source.success_));
break;
    default:
      break;
}
}
    return *this;
  }

  CreateIssuanceRequestResultCode code() const { return CreateIssuanceRequestResultCode(code_); }
  CreateIssuanceRequestResult &code(CreateIssuanceRequestResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  CreateIssuanceRequestSuccess &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateIssuanceRequestResult: success accessed when not selected");
  }
  const CreateIssuanceRequestSuccess &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateIssuanceRequestResult: success accessed when not selected");
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

#endif // !__XDR_OPERATION_CREATE_ISSUANCE_REQUEST_H_INCLUDED__
