// -*- C++ -*-
// Automatically generated from operation-create-manage-limits-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_CREATE_MANAGE_LIMITS_REQUEST_H_INCLUDED__
#define __XDR_OPERATION_CREATE_MANAGE_LIMITS_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/ledger-entries.h"

namespace stellar {

struct CreateManageLimitsRequestOp  : xdr::xdr_abstract {
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

  LimitsUpdateRequest manageLimitsRequest{};
  xdr::pointer<uint32> allTasks{};
  uint64 requestID{};
  _ext_t ext{};

  CreateManageLimitsRequestOp() = default;
  template<typename _manageLimitsRequest_T,
           typename _allTasks_T,
           typename _requestID_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<LimitsUpdateRequest, _manageLimitsRequest_T>::value
                          && std::is_constructible<xdr::pointer<uint32>, _allTasks_T>::value
                          && std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateManageLimitsRequestOp(_manageLimitsRequest_T &&_manageLimitsRequest,
                                       _allTasks_T &&_allTasks,
                                       _requestID_T &&_requestID,
                                       _ext_T &&_ext)
    : manageLimitsRequest(std::forward<_manageLimitsRequest_T>(_manageLimitsRequest)),
      allTasks(std::forward<_allTasks_T>(_allTasks)),
      requestID(std::forward<_requestID_T>(_requestID)),
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

enum class CreateManageLimitsRequestResultCode : std::int32_t {
  SUCCESS = 0,
  MANAGE_LIMITS_REQUEST_REFERENCE_DUPLICATION = -1,
  MANAGE_LIMITS_REQUEST_NOT_FOUND = -2,
  INVALID_CREATOR_DETAILS = -3,
  LIMITS_UPDATE_TASKS_NOT_FOUND = -5,
  NOT_ALLOWED_TO_SET_TASKS_ON_UPDATE = -6,
  LIMITS_UPDATE_ZERO_TASKS_NOT_ALLOWED = -7,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateManageLimitsRequestResultCode>
  : xdr_integral_base<::stellar::CreateManageLimitsRequestResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::CreateManageLimitsRequestResultCode val) {
    switch (val) {
    case ::stellar::CreateManageLimitsRequestResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::CreateManageLimitsRequestResultCode::MANAGE_LIMITS_REQUEST_REFERENCE_DUPLICATION:
      return "MANAGE_LIMITS_REQUEST_REFERENCE_DUPLICATION";
    case ::stellar::CreateManageLimitsRequestResultCode::MANAGE_LIMITS_REQUEST_NOT_FOUND:
      return "MANAGE_LIMITS_REQUEST_NOT_FOUND";
    case ::stellar::CreateManageLimitsRequestResultCode::INVALID_CREATOR_DETAILS:
      return "INVALID_CREATOR_DETAILS";
    case ::stellar::CreateManageLimitsRequestResultCode::LIMITS_UPDATE_TASKS_NOT_FOUND:
      return "LIMITS_UPDATE_TASKS_NOT_FOUND";
    case ::stellar::CreateManageLimitsRequestResultCode::NOT_ALLOWED_TO_SET_TASKS_ON_UPDATE:
      return "NOT_ALLOWED_TO_SET_TASKS_ON_UPDATE";
    case ::stellar::CreateManageLimitsRequestResultCode::LIMITS_UPDATE_ZERO_TASKS_NOT_ALLOWED:
      return "LIMITS_UPDATE_ZERO_TASKS_NOT_ALLOWED";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::CreateManageLimitsRequestResultCode::SUCCESS,
      (int32_t)::stellar::CreateManageLimitsRequestResultCode::MANAGE_LIMITS_REQUEST_REFERENCE_DUPLICATION,
      (int32_t)::stellar::CreateManageLimitsRequestResultCode::MANAGE_LIMITS_REQUEST_NOT_FOUND,
      (int32_t)::stellar::CreateManageLimitsRequestResultCode::INVALID_CREATOR_DETAILS,
      (int32_t)::stellar::CreateManageLimitsRequestResultCode::LIMITS_UPDATE_TASKS_NOT_FOUND,
      (int32_t)::stellar::CreateManageLimitsRequestResultCode::NOT_ALLOWED_TO_SET_TASKS_ON_UPDATE,
      (int32_t)::stellar::CreateManageLimitsRequestResultCode::LIMITS_UPDATE_ZERO_TASKS_NOT_ALLOWED
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateManageLimitsRequestResult : xdr::xdr_abstract {
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

    uint64 manageLimitsRequestID{};
    bool fulfilled{};
    _ext_t ext{};

    _success_t() = default;
    template<typename _manageLimitsRequestID_T,
             typename _fulfilled_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _manageLimitsRequestID_T>::value
                            && std::is_constructible<bool, _fulfilled_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _success_t(_manageLimitsRequestID_T &&_manageLimitsRequestID,
                        _fulfilled_T &&_fulfilled,
                        _ext_T &&_ext)
      : manageLimitsRequestID(std::forward<_manageLimitsRequestID_T>(_manageLimitsRequestID)),
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

  using _xdr_case_type = xdr::xdr_traits<CreateManageLimitsRequestResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    _success_t success_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<CreateManageLimitsRequestResultCode> &_xdr_case_values() {
    static const std::vector<CreateManageLimitsRequestResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)CreateManageLimitsRequestResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)CreateManageLimitsRequestResultCode::SUCCESS:
      _f(&CreateManageLimitsRequestResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in CreateManageLimitsRequestResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~CreateManageLimitsRequestResult();
      code_ = which;switch (code_)
{
      case (int32_t)CreateManageLimitsRequestResultCode::SUCCESS:
new(&success_) _success_t{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit CreateManageLimitsRequestResult(CreateManageLimitsRequestResultCode which = CreateManageLimitsRequestResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)CreateManageLimitsRequestResultCode::SUCCESS:
new(&success_) _success_t{};
break;
    default:
      break;
}

  }
  CreateManageLimitsRequestResult(const CreateManageLimitsRequestResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CreateManageLimitsRequestResultCode::SUCCESS:
new(&success_) _success_t(source.success_);
break;
    default:
      break;
}

  }
  CreateManageLimitsRequestResult(CreateManageLimitsRequestResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CreateManageLimitsRequestResultCode::SUCCESS:
new(&success_) _success_t(std::move(source.success_));
break;
    default:
      break;
}

  }
  ~CreateManageLimitsRequestResult() {
switch (code_)
{
  case (int32_t)CreateManageLimitsRequestResultCode::SUCCESS:
success_.~_success_t();
break;
  default:
    break;
}
}

  CreateManageLimitsRequestResult &operator=(const CreateManageLimitsRequestResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CreateManageLimitsRequestResultCode::SUCCESS:
success_ = source.success_;
break;
    default:
      break;
}
}
else {this->~CreateManageLimitsRequestResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)CreateManageLimitsRequestResultCode::SUCCESS:
new(&success_) _success_t(source.success_);
break;
    default:
      break;
}
}
    return *this;
  }
  CreateManageLimitsRequestResult &operator=(CreateManageLimitsRequestResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CreateManageLimitsRequestResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    default:
      break;
}
}
else {this->~CreateManageLimitsRequestResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)CreateManageLimitsRequestResultCode::SUCCESS:
new(&success_) _success_t(std::move(source.success_));
break;
    default:
      break;
}
}
    return *this;
  }

  CreateManageLimitsRequestResultCode code() const { return CreateManageLimitsRequestResultCode(code_); }
  CreateManageLimitsRequestResult &code(CreateManageLimitsRequestResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  _success_t &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateManageLimitsRequestResult: success accessed when not selected");
  }
  const _success_t &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateManageLimitsRequestResult: success accessed when not selected");
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

#endif // !__XDR_OPERATION_CREATE_MANAGE_LIMITS_REQUEST_H_INCLUDED__
