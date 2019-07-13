// -*- C++ -*-
// Automatically generated from operation-check-sale-state.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_CHECK_SALE_STATE_H_INCLUDED__
#define __XDR_OPERATION_CHECK_SALE_STATE_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/ledger-entries.h"
#include "xdr/operation-manage-offer.h"

namespace stellar {

struct CheckSaleStateOp  : xdr::xdr_abstract {
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

  uint64 saleID{};
  _ext_t ext{};

  CheckSaleStateOp() = default;
  template<typename _saleID_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _saleID_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CheckSaleStateOp(_saleID_T &&_saleID,
                            _ext_T &&_ext)
    : saleID(std::forward<_saleID_T>(_saleID)),
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

enum class CheckSaleStateResultCode : std::int32_t {
  SUCCESS = 0,
  NOT_FOUND = -1,
  NOT_READY = -2,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CheckSaleStateResultCode>
  : xdr_integral_base<::stellar::CheckSaleStateResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::CheckSaleStateResultCode val) {
    switch (val) {
    case ::stellar::CheckSaleStateResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::CheckSaleStateResultCode::NOT_FOUND:
      return "NOT_FOUND";
    case ::stellar::CheckSaleStateResultCode::NOT_READY:
      return "NOT_READY";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::CheckSaleStateResultCode::SUCCESS,
      (int32_t)::stellar::CheckSaleStateResultCode::NOT_FOUND,
      (int32_t)::stellar::CheckSaleStateResultCode::NOT_READY
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

enum class CheckSaleStateEffect : std::int32_t {
  CANCELED = 1,
  CLOSED = 2,
  UPDATED = 3,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CheckSaleStateEffect>
  : xdr_integral_base<::stellar::CheckSaleStateEffect, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::CheckSaleStateEffect val) {
    switch (val) {
    case ::stellar::CheckSaleStateEffect::CANCELED:
      return "CANCELED";
    case ::stellar::CheckSaleStateEffect::CLOSED:
      return "CLOSED";
    case ::stellar::CheckSaleStateEffect::UPDATED:
      return "UPDATED";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::CheckSaleStateEffect::CANCELED,
      (int32_t)::stellar::CheckSaleStateEffect::CLOSED,
      (int32_t)::stellar::CheckSaleStateEffect::UPDATED
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct SaleCanceled  : xdr::xdr_abstract {
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

  SaleCanceled() = default;
  template<typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit SaleCanceled(_ext_T &&_ext)
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

struct SaleUpdated  : xdr::xdr_abstract {
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

  SaleUpdated() = default;
  template<typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit SaleUpdated(_ext_T &&_ext)
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

struct CheckSubSaleClosedResult  : xdr::xdr_abstract {
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

  BalanceID saleBaseBalance{};
  BalanceID saleQuoteBalance{};
  ManageOfferSuccessResult saleDetails{};
  _ext_t ext{};

  CheckSubSaleClosedResult() = default;
  template<typename _saleBaseBalance_T,
           typename _saleQuoteBalance_T,
           typename _saleDetails_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<BalanceID, _saleBaseBalance_T>::value
                          && std::is_constructible<BalanceID, _saleQuoteBalance_T>::value
                          && std::is_constructible<ManageOfferSuccessResult, _saleDetails_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CheckSubSaleClosedResult(_saleBaseBalance_T &&_saleBaseBalance,
                                    _saleQuoteBalance_T &&_saleQuoteBalance,
                                    _saleDetails_T &&_saleDetails,
                                    _ext_T &&_ext)
    : saleBaseBalance(std::forward<_saleBaseBalance_T>(_saleBaseBalance)),
      saleQuoteBalance(std::forward<_saleQuoteBalance_T>(_saleQuoteBalance)),
      saleDetails(std::forward<_saleDetails_T>(_saleDetails)),
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

struct CheckSaleClosedResult  : xdr::xdr_abstract {
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

  AccountID saleOwner{};
  xdr::xvector<CheckSubSaleClosedResult> results{};
  _ext_t ext{};

  CheckSaleClosedResult() = default;
  template<typename _saleOwner_T,
           typename _results_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<AccountID, _saleOwner_T>::value
                          && std::is_constructible<xdr::xvector<CheckSubSaleClosedResult>, _results_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CheckSaleClosedResult(_saleOwner_T &&_saleOwner,
                                 _results_T &&_results,
                                 _ext_T &&_ext)
    : saleOwner(std::forward<_saleOwner_T>(_saleOwner)),
      results(std::forward<_results_T>(_results)),
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

struct CheckSaleStateSuccess  : xdr::xdr_abstract {
  struct _effect_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<CheckSaleStateEffect>::case_type;
  private:
    _xdr_case_type effect_;
    union {
      SaleCanceled saleCanceled_;
      CheckSaleClosedResult saleClosed_;
      SaleUpdated saleUpdated_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<CheckSaleStateEffect> &_xdr_case_values() {
      static const std::vector<CheckSaleStateEffect> _xdr_disc_vec {
        CheckSaleStateEffect::CANCELED,
        CheckSaleStateEffect::CLOSED,
        CheckSaleStateEffect::UPDATED
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)CheckSaleStateEffect::CANCELED ? 1
        : which == (int32_t)CheckSaleStateEffect::CLOSED ? 2
        : which == (int32_t)CheckSaleStateEffect::UPDATED ? 3
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)CheckSaleStateEffect::CANCELED:
        _f(&_effect_t::saleCanceled_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)CheckSaleStateEffect::CLOSED:
        _f(&_effect_t::saleClosed_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)CheckSaleStateEffect::UPDATED:
        _f(&_effect_t::saleUpdated_, std::forward<_A>(_a)...);
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return effect_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of effect in _effect_t");
      if (fnum != _xdr_field_number(effect_)) {
        this->~_effect_t();
        effect_ = which;switch (effect_)
{
        case (int32_t)CheckSaleStateEffect::CANCELED:
new(&saleCanceled_) SaleCanceled{};
break;
        case (int32_t)CheckSaleStateEffect::CLOSED:
new(&saleClosed_) CheckSaleClosedResult{};
break;
        case (int32_t)CheckSaleStateEffect::UPDATED:
new(&saleUpdated_) SaleUpdated{};
break;
}

      }
      else
        effect_ = which;
    }
    explicit _effect_t(CheckSaleStateEffect which = CheckSaleStateEffect{}) : effect_((int32_t)which) {
      switch (effect_)
{
      case (int32_t)CheckSaleStateEffect::CANCELED:
new(&saleCanceled_) SaleCanceled{};
break;
      case (int32_t)CheckSaleStateEffect::CLOSED:
new(&saleClosed_) CheckSaleClosedResult{};
break;
      case (int32_t)CheckSaleStateEffect::UPDATED:
new(&saleUpdated_) SaleUpdated{};
break;
}

    }
    _effect_t(const _effect_t &source) : effect_(source.effect_) {
      switch (effect_)
{
      case (int32_t)CheckSaleStateEffect::CANCELED:
new(&saleCanceled_) SaleCanceled(source.saleCanceled_);
break;
      case (int32_t)CheckSaleStateEffect::CLOSED:
new(&saleClosed_) CheckSaleClosedResult(source.saleClosed_);
break;
      case (int32_t)CheckSaleStateEffect::UPDATED:
new(&saleUpdated_) SaleUpdated(source.saleUpdated_);
break;
}

    }
    _effect_t(_effect_t &&source) : effect_(source.effect_) {
      switch (effect_)
{
      case (int32_t)CheckSaleStateEffect::CANCELED:
new(&saleCanceled_) SaleCanceled(std::move(source.saleCanceled_));
break;
      case (int32_t)CheckSaleStateEffect::CLOSED:
new(&saleClosed_) CheckSaleClosedResult(std::move(source.saleClosed_));
break;
      case (int32_t)CheckSaleStateEffect::UPDATED:
new(&saleUpdated_) SaleUpdated(std::move(source.saleUpdated_));
break;
}

    }
    ~_effect_t() {
switch (effect_)
{
    case (int32_t)CheckSaleStateEffect::CANCELED:
saleCanceled_.~SaleCanceled();
break;
    case (int32_t)CheckSaleStateEffect::CLOSED:
saleClosed_.~CheckSaleClosedResult();
break;
    case (int32_t)CheckSaleStateEffect::UPDATED:
saleUpdated_.~SaleUpdated();
break;
}
}

    _effect_t &operator=(const _effect_t &source) {
      if (effect_ == source.effect_)
{
switch (effect_)
{
      case (int32_t)CheckSaleStateEffect::CANCELED:
saleCanceled_ = source.saleCanceled_;
break;
      case (int32_t)CheckSaleStateEffect::CLOSED:
saleClosed_ = source.saleClosed_;
break;
      case (int32_t)CheckSaleStateEffect::UPDATED:
saleUpdated_ = source.saleUpdated_;
break;
}
}
else {this->~_effect_t();
      effect_ = source.effect_;
switch (effect_)
{
      case (int32_t)CheckSaleStateEffect::CANCELED:
new(&saleCanceled_) SaleCanceled(source.saleCanceled_);
break;
      case (int32_t)CheckSaleStateEffect::CLOSED:
new(&saleClosed_) CheckSaleClosedResult(source.saleClosed_);
break;
      case (int32_t)CheckSaleStateEffect::UPDATED:
new(&saleUpdated_) SaleUpdated(source.saleUpdated_);
break;
}
}
      return *this;
    }
    _effect_t &operator=(_effect_t &&source) {
      if (effect_ == source.effect_)
{
switch (effect_)
{
      case (int32_t)CheckSaleStateEffect::CANCELED:
saleCanceled_ = std::move(source.saleCanceled_);
break;
      case (int32_t)CheckSaleStateEffect::CLOSED:
saleClosed_ = std::move(source.saleClosed_);
break;
      case (int32_t)CheckSaleStateEffect::UPDATED:
saleUpdated_ = std::move(source.saleUpdated_);
break;
}
}
else {this->~_effect_t();
      effect_ = std::move(source.effect_);
switch (effect_)
{
      case (int32_t)CheckSaleStateEffect::CANCELED:
new(&saleCanceled_) SaleCanceled(std::move(source.saleCanceled_));
break;
      case (int32_t)CheckSaleStateEffect::CLOSED:
new(&saleClosed_) CheckSaleClosedResult(std::move(source.saleClosed_));
break;
      case (int32_t)CheckSaleStateEffect::UPDATED:
new(&saleUpdated_) SaleUpdated(std::move(source.saleUpdated_));
break;
}
}
      return *this;
    }

    CheckSaleStateEffect effect() const { return CheckSaleStateEffect(effect_); }
    _effect_t &effect(CheckSaleStateEffect _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    SaleCanceled &saleCanceled() {
      if (_xdr_field_number(effect_) == 1)
        return saleCanceled_;
      throw xdr::xdr_wrong_union("_effect_t: saleCanceled accessed when not selected");
    }
    const SaleCanceled &saleCanceled() const {
      if (_xdr_field_number(effect_) == 1)
        return saleCanceled_;
      throw xdr::xdr_wrong_union("_effect_t: saleCanceled accessed when not selected");
    }
    CheckSaleClosedResult &saleClosed() {
      if (_xdr_field_number(effect_) == 2)
        return saleClosed_;
      throw xdr::xdr_wrong_union("_effect_t: saleClosed accessed when not selected");
    }
    const CheckSaleClosedResult &saleClosed() const {
      if (_xdr_field_number(effect_) == 2)
        return saleClosed_;
      throw xdr::xdr_wrong_union("_effect_t: saleClosed accessed when not selected");
    }
    SaleUpdated &saleUpdated() {
      if (_xdr_field_number(effect_) == 3)
        return saleUpdated_;
      throw xdr::xdr_wrong_union("_effect_t: saleUpdated accessed when not selected");
    }
    const SaleUpdated &saleUpdated() const {
      if (_xdr_field_number(effect_) == 3)
        return saleUpdated_;
      throw xdr::xdr_wrong_union("_effect_t: saleUpdated accessed when not selected");
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

  uint64 saleID{};
  _effect_t effect{};
  _ext_t ext{};

  CheckSaleStateSuccess() = default;
  template<typename _saleID_T,
           typename _effect_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _saleID_T>::value
                          && std::is_constructible<_effect_t, _effect_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CheckSaleStateSuccess(_saleID_T &&_saleID,
                                 _effect_T &&_effect,
                                 _ext_T &&_ext)
    : saleID(std::forward<_saleID_T>(_saleID)),
      effect(std::forward<_effect_T>(_effect)),
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

struct CheckSaleStateResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<CheckSaleStateResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    CheckSaleStateSuccess success_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<CheckSaleStateResultCode> &_xdr_case_values() {
    static const std::vector<CheckSaleStateResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)CheckSaleStateResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)CheckSaleStateResultCode::SUCCESS:
      _f(&CheckSaleStateResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in CheckSaleStateResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~CheckSaleStateResult();
      code_ = which;switch (code_)
{
      case (int32_t)CheckSaleStateResultCode::SUCCESS:
new(&success_) CheckSaleStateSuccess{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit CheckSaleStateResult(CheckSaleStateResultCode which = CheckSaleStateResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)CheckSaleStateResultCode::SUCCESS:
new(&success_) CheckSaleStateSuccess{};
break;
    default:
      break;
}

  }
  CheckSaleStateResult(const CheckSaleStateResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CheckSaleStateResultCode::SUCCESS:
new(&success_) CheckSaleStateSuccess(source.success_);
break;
    default:
      break;
}

  }
  CheckSaleStateResult(CheckSaleStateResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)CheckSaleStateResultCode::SUCCESS:
new(&success_) CheckSaleStateSuccess(std::move(source.success_));
break;
    default:
      break;
}

  }
  ~CheckSaleStateResult() {
switch (code_)
{
  case (int32_t)CheckSaleStateResultCode::SUCCESS:
success_.~CheckSaleStateSuccess();
break;
  default:
    break;
}
}

  CheckSaleStateResult &operator=(const CheckSaleStateResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CheckSaleStateResultCode::SUCCESS:
success_ = source.success_;
break;
    default:
      break;
}
}
else {this->~CheckSaleStateResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)CheckSaleStateResultCode::SUCCESS:
new(&success_) CheckSaleStateSuccess(source.success_);
break;
    default:
      break;
}
}
    return *this;
  }
  CheckSaleStateResult &operator=(CheckSaleStateResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)CheckSaleStateResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    default:
      break;
}
}
else {this->~CheckSaleStateResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)CheckSaleStateResultCode::SUCCESS:
new(&success_) CheckSaleStateSuccess(std::move(source.success_));
break;
    default:
      break;
}
}
    return *this;
  }

  CheckSaleStateResultCode code() const { return CheckSaleStateResultCode(code_); }
  CheckSaleStateResult &code(CheckSaleStateResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  CheckSaleStateSuccess &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CheckSaleStateResult: success accessed when not selected");
  }
  const CheckSaleStateSuccess &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CheckSaleStateResult: success accessed when not selected");
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

#endif // !__XDR_OPERATION_CHECK_SALE_STATE_H_INCLUDED__
