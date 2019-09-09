// -*- C++ -*-
// Automatically generated from operation-set-fees.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_SET_FEES_H_INCLUDED__
#define __XDR_OPERATION_SET_FEES_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/ledger-entries.h"
#include "xdr/ledger-entries-fee.h"

namespace stellar {

struct SetFeesOp  : xdr::xdr_abstract {
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

  xdr::pointer<FeeEntry> fee{};
  bool isDelete{};
  _ext_t ext{};

  SetFeesOp() = default;
  template<typename _fee_T,
           typename _isDelete_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::pointer<FeeEntry>, _fee_T>::value
                          && std::is_constructible<bool, _isDelete_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit SetFeesOp(_fee_T &&_fee,
                     _isDelete_T &&_isDelete,
                     _ext_T &&_ext)
    : fee(std::forward<_fee_T>(_fee)),
      isDelete(std::forward<_isDelete_T>(_isDelete)),
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

enum class SetFeesResultCode : std::int32_t {
  SUCCESS = 0,
  INVALID_AMOUNT = -1,
  INVALID_FEE_TYPE = -2,
  ASSET_NOT_FOUND = -3,
  INVALID_ASSET = -4,
  MALFORMED = -5,
  MALFORMED_RANGE = -6,
  RANGE_OVERLAP = -7,
  NOT_FOUND = -8,
  SUB_TYPE_NOT_EXIST = -9,
  INVALID_FEE_VERSION = -10,
  INVALID_FEE_ASSET = -11,
  FEE_ASSET_NOT_ALLOWED = -12,
  CROSS_ASSET_FEE_NOT_ALLOWED = -13,
  FEE_ASSET_NOT_FOUND = -14,
  ASSET_PAIR_NOT_FOUND = -15,
  INVALID_ASSET_PAIR_PRICE = -16,
  INVALID_FEE_HASH = -17,
  INVALID_AMOUNT_PRECISION = -18,
  ACCOUNT_NOT_FOUND = -19,
  ROLE_NOT_FOUND = -20,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SetFeesResultCode>
  : xdr_integral_base<::stellar::SetFeesResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::SetFeesResultCode val) {
    switch (val) {
    case ::stellar::SetFeesResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::SetFeesResultCode::INVALID_AMOUNT:
      return "INVALID_AMOUNT";
    case ::stellar::SetFeesResultCode::INVALID_FEE_TYPE:
      return "INVALID_FEE_TYPE";
    case ::stellar::SetFeesResultCode::ASSET_NOT_FOUND:
      return "ASSET_NOT_FOUND";
    case ::stellar::SetFeesResultCode::INVALID_ASSET:
      return "INVALID_ASSET";
    case ::stellar::SetFeesResultCode::MALFORMED:
      return "MALFORMED";
    case ::stellar::SetFeesResultCode::MALFORMED_RANGE:
      return "MALFORMED_RANGE";
    case ::stellar::SetFeesResultCode::RANGE_OVERLAP:
      return "RANGE_OVERLAP";
    case ::stellar::SetFeesResultCode::NOT_FOUND:
      return "NOT_FOUND";
    case ::stellar::SetFeesResultCode::SUB_TYPE_NOT_EXIST:
      return "SUB_TYPE_NOT_EXIST";
    case ::stellar::SetFeesResultCode::INVALID_FEE_VERSION:
      return "INVALID_FEE_VERSION";
    case ::stellar::SetFeesResultCode::INVALID_FEE_ASSET:
      return "INVALID_FEE_ASSET";
    case ::stellar::SetFeesResultCode::FEE_ASSET_NOT_ALLOWED:
      return "FEE_ASSET_NOT_ALLOWED";
    case ::stellar::SetFeesResultCode::CROSS_ASSET_FEE_NOT_ALLOWED:
      return "CROSS_ASSET_FEE_NOT_ALLOWED";
    case ::stellar::SetFeesResultCode::FEE_ASSET_NOT_FOUND:
      return "FEE_ASSET_NOT_FOUND";
    case ::stellar::SetFeesResultCode::ASSET_PAIR_NOT_FOUND:
      return "ASSET_PAIR_NOT_FOUND";
    case ::stellar::SetFeesResultCode::INVALID_ASSET_PAIR_PRICE:
      return "INVALID_ASSET_PAIR_PRICE";
    case ::stellar::SetFeesResultCode::INVALID_FEE_HASH:
      return "INVALID_FEE_HASH";
    case ::stellar::SetFeesResultCode::INVALID_AMOUNT_PRECISION:
      return "INVALID_AMOUNT_PRECISION";
    case ::stellar::SetFeesResultCode::ACCOUNT_NOT_FOUND:
      return "ACCOUNT_NOT_FOUND";
    case ::stellar::SetFeesResultCode::ROLE_NOT_FOUND:
      return "ROLE_NOT_FOUND";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::SetFeesResultCode::SUCCESS,
      (int32_t)::stellar::SetFeesResultCode::INVALID_AMOUNT,
      (int32_t)::stellar::SetFeesResultCode::INVALID_FEE_TYPE,
      (int32_t)::stellar::SetFeesResultCode::ASSET_NOT_FOUND,
      (int32_t)::stellar::SetFeesResultCode::INVALID_ASSET,
      (int32_t)::stellar::SetFeesResultCode::MALFORMED,
      (int32_t)::stellar::SetFeesResultCode::MALFORMED_RANGE,
      (int32_t)::stellar::SetFeesResultCode::RANGE_OVERLAP,
      (int32_t)::stellar::SetFeesResultCode::NOT_FOUND,
      (int32_t)::stellar::SetFeesResultCode::SUB_TYPE_NOT_EXIST,
      (int32_t)::stellar::SetFeesResultCode::INVALID_FEE_VERSION,
      (int32_t)::stellar::SetFeesResultCode::INVALID_FEE_ASSET,
      (int32_t)::stellar::SetFeesResultCode::FEE_ASSET_NOT_ALLOWED,
      (int32_t)::stellar::SetFeesResultCode::CROSS_ASSET_FEE_NOT_ALLOWED,
      (int32_t)::stellar::SetFeesResultCode::FEE_ASSET_NOT_FOUND,
      (int32_t)::stellar::SetFeesResultCode::ASSET_PAIR_NOT_FOUND,
      (int32_t)::stellar::SetFeesResultCode::INVALID_ASSET_PAIR_PRICE,
      (int32_t)::stellar::SetFeesResultCode::INVALID_FEE_HASH,
      (int32_t)::stellar::SetFeesResultCode::INVALID_AMOUNT_PRECISION,
      (int32_t)::stellar::SetFeesResultCode::ACCOUNT_NOT_FOUND,
      (int32_t)::stellar::SetFeesResultCode::ROLE_NOT_FOUND
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct SetFeesResult : xdr::xdr_abstract {
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

    _ext_t ext{};

    _success_t() = default;
    template<typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _success_t(_ext_T &&_ext)
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

  using _xdr_case_type = xdr::xdr_traits<SetFeesResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    _success_t success_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<SetFeesResultCode> &_xdr_case_values() {
    static const std::vector<SetFeesResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)SetFeesResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)SetFeesResultCode::SUCCESS:
      _f(&SetFeesResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in SetFeesResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~SetFeesResult();
      code_ = which;switch (code_)
{
      case (int32_t)SetFeesResultCode::SUCCESS:
new(&success_) _success_t{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit SetFeesResult(SetFeesResultCode which = SetFeesResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)SetFeesResultCode::SUCCESS:
new(&success_) _success_t{};
break;
    default:
      break;
}

  }
  SetFeesResult(const SetFeesResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)SetFeesResultCode::SUCCESS:
new(&success_) _success_t(source.success_);
break;
    default:
      break;
}

  }
  SetFeesResult(SetFeesResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)SetFeesResultCode::SUCCESS:
new(&success_) _success_t(std::move(source.success_));
break;
    default:
      break;
}

  }
  ~SetFeesResult() {
switch (code_)
{
  case (int32_t)SetFeesResultCode::SUCCESS:
success_.~_success_t();
break;
  default:
    break;
}
}

  SetFeesResult &operator=(const SetFeesResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)SetFeesResultCode::SUCCESS:
success_ = source.success_;
break;
    default:
      break;
}
}
else {this->~SetFeesResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)SetFeesResultCode::SUCCESS:
new(&success_) _success_t(source.success_);
break;
    default:
      break;
}
}
    return *this;
  }
  SetFeesResult &operator=(SetFeesResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)SetFeesResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    default:
      break;
}
}
else {this->~SetFeesResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)SetFeesResultCode::SUCCESS:
new(&success_) _success_t(std::move(source.success_));
break;
    default:
      break;
}
}
    return *this;
  }

  SetFeesResultCode code() const { return SetFeesResultCode(code_); }
  SetFeesResult &code(SetFeesResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  _success_t &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("SetFeesResult: success accessed when not selected");
  }
  const _success_t &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("SetFeesResult: success accessed when not selected");
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

#endif // !__XDR_OPERATION_SET_FEES_H_INCLUDED__
