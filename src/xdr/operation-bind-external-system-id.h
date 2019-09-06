// -*- C++ -*-
// Automatically generated from operation-bind-external-system-id.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_BIND_EXTERNAL_SYSTEM_ID_H_INCLUDED__
#define __XDR_OPERATION_BIND_EXTERNAL_SYSTEM_ID_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/ledger-entries.h"

namespace stellar {

struct BindExternalSystemAccountIdOp  : xdr::xdr_abstract {
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

  int32 externalSystemType{};
  _ext_t ext{};

  BindExternalSystemAccountIdOp() = default;
  template<typename _externalSystemType_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<int32, _externalSystemType_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit BindExternalSystemAccountIdOp(_externalSystemType_T &&_externalSystemType,
                                         _ext_T &&_ext)
    : externalSystemType(std::forward<_externalSystemType_T>(_externalSystemType)),
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

enum class BindExternalSystemAccountIdResultCode : std::int32_t {
  SUCCESS = 0,
  MALFORMED = -1,
  NO_AVAILABLE_ID = -2,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::BindExternalSystemAccountIdResultCode>
  : xdr_integral_base<::stellar::BindExternalSystemAccountIdResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::BindExternalSystemAccountIdResultCode val) {
    switch (val) {
    case ::stellar::BindExternalSystemAccountIdResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::BindExternalSystemAccountIdResultCode::MALFORMED:
      return "MALFORMED";
    case ::stellar::BindExternalSystemAccountIdResultCode::NO_AVAILABLE_ID:
      return "NO_AVAILABLE_ID";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::BindExternalSystemAccountIdResultCode::SUCCESS,
      (int32_t)::stellar::BindExternalSystemAccountIdResultCode::MALFORMED,
      (int32_t)::stellar::BindExternalSystemAccountIdResultCode::NO_AVAILABLE_ID
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct BindExternalSystemAccountIdSuccess  : xdr::xdr_abstract {
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

  longstring data{};
  _ext_t ext{};

  BindExternalSystemAccountIdSuccess() = default;
  template<typename _data_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<longstring, _data_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit BindExternalSystemAccountIdSuccess(_data_T &&_data,
                                              _ext_T &&_ext)
    : data(std::forward<_data_T>(_data)),
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

struct BindExternalSystemAccountIdResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<BindExternalSystemAccountIdResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    BindExternalSystemAccountIdSuccess success_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<BindExternalSystemAccountIdResultCode> &_xdr_case_values() {
    static const std::vector<BindExternalSystemAccountIdResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)BindExternalSystemAccountIdResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)BindExternalSystemAccountIdResultCode::SUCCESS:
      _f(&BindExternalSystemAccountIdResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in BindExternalSystemAccountIdResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~BindExternalSystemAccountIdResult();
      code_ = which;switch (code_)
{
      case (int32_t)BindExternalSystemAccountIdResultCode::SUCCESS:
new(&success_) BindExternalSystemAccountIdSuccess{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit BindExternalSystemAccountIdResult(BindExternalSystemAccountIdResultCode which = BindExternalSystemAccountIdResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)BindExternalSystemAccountIdResultCode::SUCCESS:
new(&success_) BindExternalSystemAccountIdSuccess{};
break;
    default:
      break;
}

  }
  BindExternalSystemAccountIdResult(const BindExternalSystemAccountIdResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)BindExternalSystemAccountIdResultCode::SUCCESS:
new(&success_) BindExternalSystemAccountIdSuccess(source.success_);
break;
    default:
      break;
}

  }
  BindExternalSystemAccountIdResult(BindExternalSystemAccountIdResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)BindExternalSystemAccountIdResultCode::SUCCESS:
new(&success_) BindExternalSystemAccountIdSuccess(std::move(source.success_));
break;
    default:
      break;
}

  }
  ~BindExternalSystemAccountIdResult() {
switch (code_)
{
  case (int32_t)BindExternalSystemAccountIdResultCode::SUCCESS:
success_.~BindExternalSystemAccountIdSuccess();
break;
  default:
    break;
}
}

  BindExternalSystemAccountIdResult &operator=(const BindExternalSystemAccountIdResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)BindExternalSystemAccountIdResultCode::SUCCESS:
success_ = source.success_;
break;
    default:
      break;
}
}
else {this->~BindExternalSystemAccountIdResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)BindExternalSystemAccountIdResultCode::SUCCESS:
new(&success_) BindExternalSystemAccountIdSuccess(source.success_);
break;
    default:
      break;
}
}
    return *this;
  }
  BindExternalSystemAccountIdResult &operator=(BindExternalSystemAccountIdResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)BindExternalSystemAccountIdResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    default:
      break;
}
}
else {this->~BindExternalSystemAccountIdResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)BindExternalSystemAccountIdResultCode::SUCCESS:
new(&success_) BindExternalSystemAccountIdSuccess(std::move(source.success_));
break;
    default:
      break;
}
}
    return *this;
  }

  BindExternalSystemAccountIdResultCode code() const { return BindExternalSystemAccountIdResultCode(code_); }
  BindExternalSystemAccountIdResult &code(BindExternalSystemAccountIdResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  BindExternalSystemAccountIdSuccess &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("BindExternalSystemAccountIdResult: success accessed when not selected");
  }
  const BindExternalSystemAccountIdSuccess &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("BindExternalSystemAccountIdResult: success accessed when not selected");
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

#endif // !__XDR_OPERATION_BIND_EXTERNAL_SYSTEM_ID_H_INCLUDED__
