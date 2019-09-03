// -*- C++ -*-
// Automatically generated from operation-create-change-role-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_CREATE_CHANGE_ROLE_REQUEST_H_INCLUDED__
#define __XDR_OPERATION_CREATE_CHANGE_ROLE_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"

namespace stellar {

struct CreateChangeRoleRequestOp  : xdr::xdr_abstract {
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
  AccountID destinationAccount{};
  uint64 accountRoleToSet{};
  longstring creatorDetails{};
  xdr::pointer<uint32> allTasks{};
  _ext_t ext{};

  CreateChangeRoleRequestOp() = default;
  template<typename _requestID_T,
           typename _destinationAccount_T,
           typename _accountRoleToSet_T,
           typename _creatorDetails_T,
           typename _allTasks_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<AccountID, _destinationAccount_T>::value
                          && std::is_constructible<uint64, _accountRoleToSet_T>::value
                          && std::is_constructible<longstring, _creatorDetails_T>::value
                          && std::is_constructible<xdr::pointer<uint32>, _allTasks_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateChangeRoleRequestOp(_requestID_T &&_requestID,
                                     _destinationAccount_T &&_destinationAccount,
                                     _accountRoleToSet_T &&_accountRoleToSet,
                                     _creatorDetails_T &&_creatorDetails,
                                     _allTasks_T &&_allTasks,
                                     _ext_T &&_ext)
    : requestID(std::forward<_requestID_T>(_requestID)),
      destinationAccount(std::forward<_destinationAccount_T>(_destinationAccount)),
      accountRoleToSet(std::forward<_accountRoleToSet_T>(_accountRoleToSet)),
      creatorDetails(std::forward<_creatorDetails_T>(_creatorDetails)),
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

enum class CreateChangeRoleRequestResultCode : std::int32_t {
  SUCCESS = 0,
  ACC_TO_UPDATE_DOES_NOT_EXIST = -1,
  REQUEST_ALREADY_EXISTS = -2,
  REQUEST_DOES_NOT_EXIST = -4,
  NOT_ALLOWED_TO_UPDATE_REQUEST = -6,
  INVALID_CHANGE_ROLE_REQUEST_DATA = -7,
  INVALID_CREATOR_DETAILS = -8,
  CHANGE_ROLE_TASKS_NOT_FOUND = -9,
  ACCOUNT_ROLE_TO_SET_DOES_NOT_EXIST = -10,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateChangeRoleRequestResultCode>
  : xdr_integral_base<::stellar::CreateChangeRoleRequestResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::CreateChangeRoleRequestResultCode val) {
    switch (val) {
    case ::stellar::CreateChangeRoleRequestResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::CreateChangeRoleRequestResultCode::ACC_TO_UPDATE_DOES_NOT_EXIST:
      return "ACC_TO_UPDATE_DOES_NOT_EXIST";
    case ::stellar::CreateChangeRoleRequestResultCode::REQUEST_ALREADY_EXISTS:
      return "REQUEST_ALREADY_EXISTS";
    case ::stellar::CreateChangeRoleRequestResultCode::REQUEST_DOES_NOT_EXIST:
      return "REQUEST_DOES_NOT_EXIST";
    case ::stellar::CreateChangeRoleRequestResultCode::NOT_ALLOWED_TO_UPDATE_REQUEST:
      return "NOT_ALLOWED_TO_UPDATE_REQUEST";
    case ::stellar::CreateChangeRoleRequestResultCode::INVALID_CHANGE_ROLE_REQUEST_DATA:
      return "INVALID_CHANGE_ROLE_REQUEST_DATA";
    case ::stellar::CreateChangeRoleRequestResultCode::INVALID_CREATOR_DETAILS:
      return "INVALID_CREATOR_DETAILS";
    case ::stellar::CreateChangeRoleRequestResultCode::CHANGE_ROLE_TASKS_NOT_FOUND:
      return "CHANGE_ROLE_TASKS_NOT_FOUND";
    case ::stellar::CreateChangeRoleRequestResultCode::ACCOUNT_ROLE_TO_SET_DOES_NOT_EXIST:
      return "ACCOUNT_ROLE_TO_SET_DOES_NOT_EXIST";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::CreateChangeRoleRequestResultCode::SUCCESS,
      (int32_t)::stellar::CreateChangeRoleRequestResultCode::ACC_TO_UPDATE_DOES_NOT_EXIST,
      (int32_t)::stellar::CreateChangeRoleRequestResultCode::REQUEST_ALREADY_EXISTS,
      (int32_t)::stellar::CreateChangeRoleRequestResultCode::REQUEST_DOES_NOT_EXIST,
      (int32_t)::stellar::CreateChangeRoleRequestResultCode::NOT_ALLOWED_TO_UPDATE_REQUEST,
      (int32_t)::stellar::CreateChangeRoleRequestResultCode::INVALID_CHANGE_ROLE_REQUEST_DATA,
      (int32_t)::stellar::CreateChangeRoleRequestResultCode::INVALID_CREATOR_DETAILS,
      (int32_t)::stellar::CreateChangeRoleRequestResultCode::CHANGE_ROLE_TASKS_NOT_FOUND,
      (int32_t)::stellar::CreateChangeRoleRequestResultCode::ACCOUNT_ROLE_TO_SET_DOES_NOT_EXIST
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateChangeRoleRequestResult : xdr::xdr_abstract {
  struct _success_t  : xdr::xdr_abstract {
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

    _success_t() = default;
    template<typename _requestID_T,
             typename _fulfilled_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                            && std::is_constructible<bool, _fulfilled_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _success_t(_requestID_T &&_requestID,
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

  using _xdr_case_type = xdr::xdr_traits<CreateChangeRoleRequestResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    _success_t success_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<CreateChangeRoleRequestResultCode> &_xdr_case_values() {
    static const std::vector<CreateChangeRoleRequestResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)CreateChangeRoleRequestResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)CreateChangeRoleRequestResultCode::SUCCESS:
      _f(&CreateChangeRoleRequestResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in CreateChangeRoleRequestResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~CreateChangeRoleRequestResult();
      code_ = which;switch (code_)
{
      case (int32_t)CreateChangeRoleRequestResultCode::SUCCESS:
new(&success_) _success_t{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit CreateChangeRoleRequestResult(CreateChangeRoleRequestResultCode which = CreateChangeRoleRequestResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)CreateChangeRoleRequestResultCode::SUCCESS:
new(&success_) _success_t{};
break;
    default:
      break;
}

  }
  CreateChangeRoleRequestResult(const CreateChangeRoleRequestResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CreateChangeRoleRequestResultCode::SUCCESS:
new(&success_) _success_t(source.success_);
break;
    default:
      break;
}

  }
  CreateChangeRoleRequestResult(CreateChangeRoleRequestResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CreateChangeRoleRequestResultCode::SUCCESS:
new(&success_) _success_t(std::move(source.success_));
break;
    default:
      break;
}

  }
  ~CreateChangeRoleRequestResult() {
switch (code_)
{
  case (int32_t)CreateChangeRoleRequestResultCode::SUCCESS:
success_.~_success_t();
break;
  default:
    break;
}
}

  CreateChangeRoleRequestResult &operator=(const CreateChangeRoleRequestResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CreateChangeRoleRequestResultCode::SUCCESS:
success_ = source.success_;
break;
    default:
      break;
}
}
else {this->~CreateChangeRoleRequestResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)CreateChangeRoleRequestResultCode::SUCCESS:
new(&success_) _success_t(source.success_);
break;
    default:
      break;
}
}
    return *this;
  }
  CreateChangeRoleRequestResult &operator=(CreateChangeRoleRequestResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CreateChangeRoleRequestResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    default:
      break;
}
}
else {this->~CreateChangeRoleRequestResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)CreateChangeRoleRequestResultCode::SUCCESS:
new(&success_) _success_t(std::move(source.success_));
break;
    default:
      break;
}
}
    return *this;
  }

  CreateChangeRoleRequestResultCode code() const { return CreateChangeRoleRequestResultCode(code_); }
  CreateChangeRoleRequestResult &code(CreateChangeRoleRequestResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  _success_t &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateChangeRoleRequestResult: success accessed when not selected");
  }
  const _success_t &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateChangeRoleRequestResult: success accessed when not selected");
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

#endif // !__XDR_OPERATION_CREATE_CHANGE_ROLE_REQUEST_H_INCLUDED__
