// -*- C++ -*-
// Automatically generated from operation-license.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_LICENSE_H_INCLUDED__
#define __XDR_OPERATION_LICENSE_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/ledger-entries.h"

namespace stellar {

struct LicenseOp  : xdr::xdr_abstract {
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

  uint64 adminCount{};
  uint64 dueDate{};
  Hash ledgerHash{};
  Hash prevLicenseHash{};
  xdr::xvector<DecoratedSignature> signatures{};
  _ext_t ext{};

  LicenseOp() = default;
  template<typename _adminCount_T,
           typename _dueDate_T,
           typename _ledgerHash_T,
           typename _prevLicenseHash_T,
           typename _signatures_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _adminCount_T>::value
                          && std::is_constructible<uint64, _dueDate_T>::value
                          && std::is_constructible<Hash, _ledgerHash_T>::value
                          && std::is_constructible<Hash, _prevLicenseHash_T>::value
                          && std::is_constructible<xdr::xvector<DecoratedSignature>, _signatures_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit LicenseOp(_adminCount_T &&_adminCount,
                     _dueDate_T &&_dueDate,
                     _ledgerHash_T &&_ledgerHash,
                     _prevLicenseHash_T &&_prevLicenseHash,
                     _signatures_T &&_signatures,
                     _ext_T &&_ext)
    : adminCount(std::forward<_adminCount_T>(_adminCount)),
      dueDate(std::forward<_dueDate_T>(_dueDate)),
      ledgerHash(std::forward<_ledgerHash_T>(_ledgerHash)),
      prevLicenseHash(std::forward<_prevLicenseHash_T>(_prevLicenseHash)),
      signatures(std::forward<_signatures_T>(_signatures)),
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

enum class LicenseResultCode : std::int32_t {
  SUCCESS = 0,
  INVALID_STAMP = -1,
  INVALID_DUE_DATE = -2,
  INVALID_SIGNATURE = -3,
  EXTRA_SIGNATURES = -4,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LicenseResultCode>
  : xdr_integral_base<::stellar::LicenseResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::LicenseResultCode val) {
    switch (val) {
    case ::stellar::LicenseResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::LicenseResultCode::INVALID_STAMP:
      return "INVALID_STAMP";
    case ::stellar::LicenseResultCode::INVALID_DUE_DATE:
      return "INVALID_DUE_DATE";
    case ::stellar::LicenseResultCode::INVALID_SIGNATURE:
      return "INVALID_SIGNATURE";
    case ::stellar::LicenseResultCode::EXTRA_SIGNATURES:
      return "EXTRA_SIGNATURES";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::LicenseResultCode::SUCCESS,
      (int32_t)::stellar::LicenseResultCode::INVALID_STAMP,
      (int32_t)::stellar::LicenseResultCode::INVALID_DUE_DATE,
      (int32_t)::stellar::LicenseResultCode::INVALID_SIGNATURE,
      (int32_t)::stellar::LicenseResultCode::EXTRA_SIGNATURES
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct LicenseSuccess  : xdr::xdr_abstract {
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

  LicenseSuccess() = default;
  template<typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit LicenseSuccess(_ext_T &&_ext)
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

struct LicenseResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<LicenseResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    LicenseSuccess success_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<LicenseResultCode> &_xdr_case_values() {
    static const std::vector<LicenseResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)LicenseResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)LicenseResultCode::SUCCESS:
      _f(&LicenseResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in LicenseResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~LicenseResult();
      code_ = which;switch (code_)
{
      case (int32_t)LicenseResultCode::SUCCESS:
new(&success_) LicenseSuccess{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit LicenseResult(LicenseResultCode which = LicenseResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)LicenseResultCode::SUCCESS:
new(&success_) LicenseSuccess{};
break;
    default:
      break;
}

  }
  LicenseResult(const LicenseResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)LicenseResultCode::SUCCESS:
new(&success_) LicenseSuccess(source.success_);
break;
    default:
      break;
}

  }
  LicenseResult(LicenseResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)LicenseResultCode::SUCCESS:
new(&success_) LicenseSuccess(std::move(source.success_));
break;
    default:
      break;
}

  }
  ~LicenseResult() {
switch (code_)
{
  case (int32_t)LicenseResultCode::SUCCESS:
success_.~LicenseSuccess();
break;
  default:
    break;
}
}

  LicenseResult &operator=(const LicenseResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)LicenseResultCode::SUCCESS:
success_ = source.success_;
break;
    default:
      break;
}
}
else {this->~LicenseResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)LicenseResultCode::SUCCESS:
new(&success_) LicenseSuccess(source.success_);
break;
    default:
      break;
}
}
    return *this;
  }
  LicenseResult &operator=(LicenseResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)LicenseResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    default:
      break;
}
}
else {this->~LicenseResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)LicenseResultCode::SUCCESS:
new(&success_) LicenseSuccess(std::move(source.success_));
break;
    default:
      break;
}
}
    return *this;
  }

  LicenseResultCode code() const { return LicenseResultCode(code_); }
  LicenseResult &code(LicenseResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  LicenseSuccess &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("LicenseResult: success accessed when not selected");
  }
  const LicenseSuccess &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("LicenseResult: success accessed when not selected");
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

#endif // !__XDR_OPERATION_LICENSE_H_INCLUDED__
