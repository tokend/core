// -*- C++ -*-
// Automatically generated from operation-cancel-data-remove-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_CANCEL_DATA_REMOVE_REQUEST_H_INCLUDED__
#define __XDR_OPERATION_CANCEL_DATA_REMOVE_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/ledger-entries.h"

namespace stellar {

struct CancelDataRemoveRequestOp  : xdr::xdr_abstract {
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
  _ext_t ext{};

  CancelDataRemoveRequestOp() = default;
  template<typename _requestID_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CancelDataRemoveRequestOp(_requestID_T &&_requestID,
                                     _ext_T &&_ext)
    : requestID(std::forward<_requestID_T>(_requestID)),
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

enum class CancelDataRemoveRequestResultCode : std::int32_t {
  SUCCESS = 0,
  REQUEST_ID_INVALID = -1,
  REQUEST_NOT_FOUND = -2,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CancelDataRemoveRequestResultCode>
  : xdr_integral_base<::stellar::CancelDataRemoveRequestResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::CancelDataRemoveRequestResultCode val) {
    switch (val) {
    case ::stellar::CancelDataRemoveRequestResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::CancelDataRemoveRequestResultCode::REQUEST_ID_INVALID:
      return "REQUEST_ID_INVALID";
    case ::stellar::CancelDataRemoveRequestResultCode::REQUEST_NOT_FOUND:
      return "REQUEST_NOT_FOUND";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::CancelDataRemoveRequestResultCode::SUCCESS,
      (int32_t)::stellar::CancelDataRemoveRequestResultCode::REQUEST_ID_INVALID,
      (int32_t)::stellar::CancelDataRemoveRequestResultCode::REQUEST_NOT_FOUND
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CancelDataRemoveSuccess  : xdr::xdr_abstract {
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

  _ext_t ext{};

  CancelDataRemoveSuccess() = default;
  template<typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CancelDataRemoveSuccess(_ext_T &&_ext)
    : ext(std::forward<_ext_T>(_ext)) {}
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

struct CancelDataRemoveRequestResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<CancelDataRemoveRequestResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    CancelDataRemoveSuccess success_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<CancelDataRemoveRequestResultCode> &_xdr_case_values() {
    static const std::vector<CancelDataRemoveRequestResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)CancelDataRemoveRequestResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)CancelDataRemoveRequestResultCode::SUCCESS:
      _f(&CancelDataRemoveRequestResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in CancelDataRemoveRequestResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~CancelDataRemoveRequestResult();
      code_ = which;switch (code_)
{
      case (int32_t)CancelDataRemoveRequestResultCode::SUCCESS:
new(&success_) CancelDataRemoveSuccess{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit CancelDataRemoveRequestResult(CancelDataRemoveRequestResultCode which = CancelDataRemoveRequestResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)CancelDataRemoveRequestResultCode::SUCCESS:
new(&success_) CancelDataRemoveSuccess{};
break;
    default:
      break;
}

  }
  CancelDataRemoveRequestResult(const CancelDataRemoveRequestResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CancelDataRemoveRequestResultCode::SUCCESS:
new(&success_) CancelDataRemoveSuccess(source.success_);
break;
    default:
      break;
}

  }
  CancelDataRemoveRequestResult(CancelDataRemoveRequestResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CancelDataRemoveRequestResultCode::SUCCESS:
new(&success_) CancelDataRemoveSuccess(std::move(source.success_));
break;
    default:
      break;
}

  }
  ~CancelDataRemoveRequestResult() {
switch (code_)
{
  case (int32_t)CancelDataRemoveRequestResultCode::SUCCESS:
success_.~CancelDataRemoveSuccess();
break;
  default:
    break;
}
}

  CancelDataRemoveRequestResult &operator=(const CancelDataRemoveRequestResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CancelDataRemoveRequestResultCode::SUCCESS:
success_ = source.success_;
break;
    default:
      break;
}
}
else {this->~CancelDataRemoveRequestResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)CancelDataRemoveRequestResultCode::SUCCESS:
new(&success_) CancelDataRemoveSuccess(source.success_);
break;
    default:
      break;
}
}
    return *this;
  }
  CancelDataRemoveRequestResult &operator=(CancelDataRemoveRequestResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CancelDataRemoveRequestResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    default:
      break;
}
}
else {this->~CancelDataRemoveRequestResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)CancelDataRemoveRequestResultCode::SUCCESS:
new(&success_) CancelDataRemoveSuccess(std::move(source.success_));
break;
    default:
      break;
}
}
    return *this;
  }

  CancelDataRemoveRequestResultCode code() const { return CancelDataRemoveRequestResultCode(code_); }
  CancelDataRemoveRequestResult &code(CancelDataRemoveRequestResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  CancelDataRemoveSuccess &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CancelDataRemoveRequestResult: success accessed when not selected");
  }
  const CancelDataRemoveSuccess &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CancelDataRemoveRequestResult: success accessed when not selected");
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

#endif // !__XDR_OPERATION_CANCEL_DATA_REMOVE_REQUEST_H_INCLUDED__
