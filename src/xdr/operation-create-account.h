// -*- C++ -*-
// Automatically generated from operation-create-account.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_CREATE_ACCOUNT_H_INCLUDED__
#define __XDR_OPERATION_CREATE_ACCOUNT_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"
#include "xdr/operation-manage-signer.h"

namespace stellar {

struct CreateAccountOp  : xdr::xdr_abstract {
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

  AccountID destination{};
  xdr::pointer<AccountID> referrer{};
  uint64 roleID{};
  xdr::xvector<UpdateSignerData> signersData{};
  _ext_t ext{};

  CreateAccountOp() = default;
  template<typename _destination_T,
           typename _referrer_T,
           typename _roleID_T,
           typename _signersData_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<AccountID, _destination_T>::value
                          && std::is_constructible<xdr::pointer<AccountID>, _referrer_T>::value
                          && std::is_constructible<uint64, _roleID_T>::value
                          && std::is_constructible<xdr::xvector<UpdateSignerData>, _signersData_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateAccountOp(_destination_T &&_destination,
                           _referrer_T &&_referrer,
                           _roleID_T &&_roleID,
                           _signersData_T &&_signersData,
                           _ext_T &&_ext)
    : destination(std::forward<_destination_T>(_destination)),
      referrer(std::forward<_referrer_T>(_referrer)),
      roleID(std::forward<_roleID_T>(_roleID)),
      signersData(std::forward<_signersData_T>(_signersData)),
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

enum class CreateAccountResultCode : std::int32_t {
  SUCCESS = 0,
  INVALID_DESTINATION = -1,
  ALREADY_EXISTS = -2,
  INVALID_WEIGHT = -3,
  NO_SUCH_ROLE = -4,
  INVALID_SIGNER_DATA = -5,
  NO_SIGNER_DATA = -6,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateAccountResultCode>
  : xdr_integral_base<::stellar::CreateAccountResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::CreateAccountResultCode val) {
    switch (val) {
    case ::stellar::CreateAccountResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::CreateAccountResultCode::INVALID_DESTINATION:
      return "INVALID_DESTINATION";
    case ::stellar::CreateAccountResultCode::ALREADY_EXISTS:
      return "ALREADY_EXISTS";
    case ::stellar::CreateAccountResultCode::INVALID_WEIGHT:
      return "INVALID_WEIGHT";
    case ::stellar::CreateAccountResultCode::NO_SUCH_ROLE:
      return "NO_SUCH_ROLE";
    case ::stellar::CreateAccountResultCode::INVALID_SIGNER_DATA:
      return "INVALID_SIGNER_DATA";
    case ::stellar::CreateAccountResultCode::NO_SIGNER_DATA:
      return "NO_SIGNER_DATA";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::CreateAccountResultCode::SUCCESS,
      (int32_t)::stellar::CreateAccountResultCode::INVALID_DESTINATION,
      (int32_t)::stellar::CreateAccountResultCode::ALREADY_EXISTS,
      (int32_t)::stellar::CreateAccountResultCode::INVALID_WEIGHT,
      (int32_t)::stellar::CreateAccountResultCode::NO_SUCH_ROLE,
      (int32_t)::stellar::CreateAccountResultCode::INVALID_SIGNER_DATA,
      (int32_t)::stellar::CreateAccountResultCode::NO_SIGNER_DATA
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateAccountSuccess  : xdr::xdr_abstract {
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

  uint64 sequentialID{};
  _ext_t ext{};

  CreateAccountSuccess() = default;
  template<typename _sequentialID_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _sequentialID_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateAccountSuccess(_sequentialID_T &&_sequentialID,
                                _ext_T &&_ext)
    : sequentialID(std::forward<_sequentialID_T>(_sequentialID)),
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

struct CreateAccountResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<CreateAccountResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    CreateAccountSuccess success_;
    ManageSignerResultCode createSignerErrorCode_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<CreateAccountResultCode> &_xdr_case_values() {
    static const std::vector<CreateAccountResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)CreateAccountResultCode::SUCCESS ? 1
      : which == (int32_t)CreateAccountResultCode::INVALID_SIGNER_DATA ? 2
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)CreateAccountResultCode::SUCCESS:
      _f(&CreateAccountResult::success_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)CreateAccountResultCode::INVALID_SIGNER_DATA:
      _f(&CreateAccountResult::createSignerErrorCode_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in CreateAccountResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~CreateAccountResult();
      code_ = which;switch (code_)
{
      case (int32_t)CreateAccountResultCode::SUCCESS:
new(&success_) CreateAccountSuccess{};
break;
      case (int32_t)CreateAccountResultCode::INVALID_SIGNER_DATA:
new(&createSignerErrorCode_) ManageSignerResultCode{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit CreateAccountResult(CreateAccountResultCode which = CreateAccountResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)CreateAccountResultCode::SUCCESS:
new(&success_) CreateAccountSuccess{};
break;
    case (int32_t)CreateAccountResultCode::INVALID_SIGNER_DATA:
new(&createSignerErrorCode_) ManageSignerResultCode{};
break;
    default:
      break;
}

  }
  CreateAccountResult(const CreateAccountResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CreateAccountResultCode::SUCCESS:
new(&success_) CreateAccountSuccess(source.success_);
break;
    case (int32_t)CreateAccountResultCode::INVALID_SIGNER_DATA:
new(&createSignerErrorCode_) ManageSignerResultCode(source.createSignerErrorCode_);
break;
    default:
      break;
}

  }
  CreateAccountResult(CreateAccountResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CreateAccountResultCode::SUCCESS:
new(&success_) CreateAccountSuccess(std::move(source.success_));
break;
    case (int32_t)CreateAccountResultCode::INVALID_SIGNER_DATA:
new(&createSignerErrorCode_) ManageSignerResultCode(std::move(source.createSignerErrorCode_));
break;
    default:
      break;
}

  }
  ~CreateAccountResult() {
switch (code_)
{
  case (int32_t)CreateAccountResultCode::SUCCESS:
success_.~CreateAccountSuccess();
break;
  case (int32_t)CreateAccountResultCode::INVALID_SIGNER_DATA:
createSignerErrorCode_.~ManageSignerResultCode();
break;
  default:
    break;
}
}

  CreateAccountResult &operator=(const CreateAccountResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CreateAccountResultCode::SUCCESS:
success_ = source.success_;
break;
    case (int32_t)CreateAccountResultCode::INVALID_SIGNER_DATA:
createSignerErrorCode_ = source.createSignerErrorCode_;
break;
    default:
      break;
}
}
else {this->~CreateAccountResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)CreateAccountResultCode::SUCCESS:
new(&success_) CreateAccountSuccess(source.success_);
break;
    case (int32_t)CreateAccountResultCode::INVALID_SIGNER_DATA:
new(&createSignerErrorCode_) ManageSignerResultCode(source.createSignerErrorCode_);
break;
    default:
      break;
}
}
    return *this;
  }
  CreateAccountResult &operator=(CreateAccountResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CreateAccountResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    case (int32_t)CreateAccountResultCode::INVALID_SIGNER_DATA:
createSignerErrorCode_ = std::move(source.createSignerErrorCode_);
break;
    default:
      break;
}
}
else {this->~CreateAccountResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)CreateAccountResultCode::SUCCESS:
new(&success_) CreateAccountSuccess(std::move(source.success_));
break;
    case (int32_t)CreateAccountResultCode::INVALID_SIGNER_DATA:
new(&createSignerErrorCode_) ManageSignerResultCode(std::move(source.createSignerErrorCode_));
break;
    default:
      break;
}
}
    return *this;
  }

  CreateAccountResultCode code() const { return CreateAccountResultCode(code_); }
  CreateAccountResult &code(CreateAccountResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  CreateAccountSuccess &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateAccountResult: success accessed when not selected");
  }
  const CreateAccountSuccess &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateAccountResult: success accessed when not selected");
  }
  ManageSignerResultCode &createSignerErrorCode() {
    if (_xdr_field_number(code_) == 2)
      return createSignerErrorCode_;
    throw xdr::xdr_wrong_union("CreateAccountResult: createSignerErrorCode accessed when not selected");
  }
  const ManageSignerResultCode &createSignerErrorCode() const {
    if (_xdr_field_number(code_) == 2)
      return createSignerErrorCode_;
    throw xdr::xdr_wrong_union("CreateAccountResult: createSignerErrorCode accessed when not selected");
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

#endif // !__XDR_OPERATION_CREATE_ACCOUNT_H_INCLUDED__
