// -*- C++ -*-
// Automatically generated from operation-review-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_REVIEW_REQUEST_H_INCLUDED__
#define __XDR_OPERATION_REVIEW_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/ledger-entries.h"
#include "xdr/operation-payment.h"
#include "xdr/operation-manage-offer.h"
#include "xdr/operation-create-redemption-request.h"

namespace stellar {

enum class ReviewRequestOpAction : std::int32_t {
  APPROVE = 1,
  REJECT = 2,
  PERMANENT_REJECT = 3,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ReviewRequestOpAction>
  : xdr_integral_base<::stellar::ReviewRequestOpAction, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ReviewRequestOpAction val) {
    switch (val) {
    case ::stellar::ReviewRequestOpAction::APPROVE:
      return "APPROVE";
    case ::stellar::ReviewRequestOpAction::REJECT:
      return "REJECT";
    case ::stellar::ReviewRequestOpAction::PERMANENT_REJECT:
      return "PERMANENT_REJECT";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ReviewRequestOpAction::APPROVE,
      (int32_t)::stellar::ReviewRequestOpAction::REJECT,
      (int32_t)::stellar::ReviewRequestOpAction::PERMANENT_REJECT
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct LimitsUpdateDetails  : xdr::xdr_abstract {
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

  LimitsV2Entry newLimitsV2{};
  _ext_t ext{};

  LimitsUpdateDetails() = default;
  template<typename _newLimitsV2_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<LimitsV2Entry, _newLimitsV2_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit LimitsUpdateDetails(_newLimitsV2_T &&_newLimitsV2,
                               _ext_T &&_ext)
    : newLimitsV2(std::forward<_newLimitsV2_T>(_newLimitsV2)),
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

struct WithdrawalDetails  : xdr::xdr_abstract {
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

  xdr::xstring<> externalDetails{};
  _ext_t ext{};

  WithdrawalDetails() = default;
  template<typename _externalDetails_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xstring<>, _externalDetails_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit WithdrawalDetails(_externalDetails_T &&_externalDetails,
                             _ext_T &&_ext)
    : externalDetails(std::forward<_externalDetails_T>(_externalDetails)),
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

struct AMLAlertDetails  : xdr::xdr_abstract {
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

  xdr::xstring<> comment{};
  _ext_t ext{};

  AMLAlertDetails() = default;
  template<typename _comment_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xstring<>, _comment_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit AMLAlertDetails(_comment_T &&_comment,
                           _ext_T &&_ext)
    : comment(std::forward<_comment_T>(_comment)),
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

struct ContractDetails  : xdr::xdr_abstract {
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

  longstring details{};
  _ext_t ext{};

  ContractDetails() = default;
  template<typename _details_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<longstring, _details_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ContractDetails(_details_T &&_details,
                           _ext_T &&_ext)
    : details(std::forward<_details_T>(_details)),
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

struct BillPayDetails  : xdr::xdr_abstract {
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

  PaymentOp paymentDetails{};
  _ext_t ext{};

  BillPayDetails() = default;
  template<typename _paymentDetails_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<PaymentOp, _paymentDetails_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit BillPayDetails(_paymentDetails_T &&_paymentDetails,
                          _ext_T &&_ext)
    : paymentDetails(std::forward<_paymentDetails_T>(_paymentDetails)),
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

struct ReviewDetails  : xdr::xdr_abstract {
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

  uint32 tasksToAdd{};
  uint32 tasksToRemove{};
  xdr::xstring<> externalDetails{};
  _ext_t ext{};

  ReviewDetails() = default;
  template<typename _tasksToAdd_T,
           typename _tasksToRemove_T,
           typename _externalDetails_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint32, _tasksToAdd_T>::value
                          && std::is_constructible<uint32, _tasksToRemove_T>::value
                          && std::is_constructible<xdr::xstring<>, _externalDetails_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ReviewDetails(_tasksToAdd_T &&_tasksToAdd,
                         _tasksToRemove_T &&_tasksToRemove,
                         _externalDetails_T &&_externalDetails,
                         _ext_T &&_ext)
    : tasksToAdd(std::forward<_tasksToAdd_T>(_tasksToAdd)),
      tasksToRemove(std::forward<_tasksToRemove_T>(_tasksToRemove)),
      externalDetails(std::forward<_externalDetails_T>(_externalDetails)),
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

struct SaleExtended  : xdr::xdr_abstract {
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

  SaleExtended() = default;
  template<typename _saleID_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _saleID_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit SaleExtended(_saleID_T &&_saleID,
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

struct AtomicSwapAskExtended  : xdr::xdr_abstract {
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

  uint64 askID{};
  _ext_t ext{};

  AtomicSwapAskExtended() = default;
  template<typename _askID_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _askID_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit AtomicSwapAskExtended(_askID_T &&_askID,
                                 _ext_T &&_ext)
    : askID(std::forward<_askID_T>(_askID)),
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

struct CreatePollExtended  : xdr::xdr_abstract {
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

  uint64 pollID{};
  _ext_t ext{};

  CreatePollExtended() = default;
  template<typename _pollID_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _pollID_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreatePollExtended(_pollID_T &&_pollID,
                              _ext_T &&_ext)
    : pollID(std::forward<_pollID_T>(_pollID)),
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

struct AtomicSwapBidExtended  : xdr::xdr_abstract {
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

  uint64 askID{};
  AccountID askOwnerID{};
  AccountID bidOwnerID{};
  AssetCode baseAsset{};
  AssetCode quoteAsset{};
  uint64 baseAmount{};
  uint64 quoteAmount{};
  uint64 price{};
  BalanceID askOwnerBaseBalanceID{};
  BalanceID bidOwnerBaseBalanceID{};
  uint64 unlockedAmount{};
  _ext_t ext{};

  AtomicSwapBidExtended() = default;
  template<typename _askID_T,
           typename _askOwnerID_T,
           typename _bidOwnerID_T,
           typename _baseAsset_T,
           typename _quoteAsset_T,
           typename _baseAmount_T,
           typename _quoteAmount_T,
           typename _price_T,
           typename _askOwnerBaseBalanceID_T,
           typename _bidOwnerBaseBalanceID_T,
           typename _unlockedAmount_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _askID_T>::value
                          && std::is_constructible<AccountID, _askOwnerID_T>::value
                          && std::is_constructible<AccountID, _bidOwnerID_T>::value
                          && std::is_constructible<AssetCode, _baseAsset_T>::value
                          && std::is_constructible<AssetCode, _quoteAsset_T>::value
                          && std::is_constructible<uint64, _baseAmount_T>::value
                          && std::is_constructible<uint64, _quoteAmount_T>::value
                          && std::is_constructible<uint64, _price_T>::value
                          && std::is_constructible<BalanceID, _askOwnerBaseBalanceID_T>::value
                          && std::is_constructible<BalanceID, _bidOwnerBaseBalanceID_T>::value
                          && std::is_constructible<uint64, _unlockedAmount_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit AtomicSwapBidExtended(_askID_T &&_askID,
                                 _askOwnerID_T &&_askOwnerID,
                                 _bidOwnerID_T &&_bidOwnerID,
                                 _baseAsset_T &&_baseAsset,
                                 _quoteAsset_T &&_quoteAsset,
                                 _baseAmount_T &&_baseAmount,
                                 _quoteAmount_T &&_quoteAmount,
                                 _price_T &&_price,
                                 _askOwnerBaseBalanceID_T &&_askOwnerBaseBalanceID,
                                 _bidOwnerBaseBalanceID_T &&_bidOwnerBaseBalanceID,
                                 _unlockedAmount_T &&_unlockedAmount,
                                 _ext_T &&_ext)
    : askID(std::forward<_askID_T>(_askID)),
      askOwnerID(std::forward<_askOwnerID_T>(_askOwnerID)),
      bidOwnerID(std::forward<_bidOwnerID_T>(_bidOwnerID)),
      baseAsset(std::forward<_baseAsset_T>(_baseAsset)),
      quoteAsset(std::forward<_quoteAsset_T>(_quoteAsset)),
      baseAmount(std::forward<_baseAmount_T>(_baseAmount)),
      quoteAmount(std::forward<_quoteAmount_T>(_quoteAmount)),
      price(std::forward<_price_T>(_price)),
      askOwnerBaseBalanceID(std::forward<_askOwnerBaseBalanceID_T>(_askOwnerBaseBalanceID)),
      bidOwnerBaseBalanceID(std::forward<_bidOwnerBaseBalanceID_T>(_bidOwnerBaseBalanceID)),
      unlockedAmount(std::forward<_unlockedAmount_T>(_unlockedAmount)),
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

struct ExtendedResult  : xdr::xdr_abstract {
  struct _typeExt_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<ReviewableRequestType>::case_type;
  private:
    _xdr_case_type requestType_;
    union {
      SaleExtended saleExtended_;
      AtomicSwapBidExtended atomicSwapBidExtended_;
      AtomicSwapAskExtended atomicSwapAskExtended_;
      CreatePollExtended createPoll_;
      ManageOfferResult manageOfferResult_;
      PaymentResult paymentResult_;
      CreateRedemptionRequestResult createRedemptionResult_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<ReviewableRequestType> &_xdr_case_values() {
      static const std::vector<ReviewableRequestType> _xdr_disc_vec {
        ReviewableRequestType::CREATE_SALE,
        ReviewableRequestType::NONE,
        ReviewableRequestType::CREATE_ATOMIC_SWAP_BID,
        ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK,
        ReviewableRequestType::CREATE_POLL,
        ReviewableRequestType::MANAGE_OFFER,
        ReviewableRequestType::CREATE_PAYMENT,
        ReviewableRequestType::PERFORM_REDEMPTION
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)ReviewableRequestType::CREATE_SALE ? 1
        : which == (int32_t)ReviewableRequestType::NONE ? 0
        : which == (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID ? 2
        : which == (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK ? 3
        : which == (int32_t)ReviewableRequestType::CREATE_POLL ? 4
        : which == (int32_t)ReviewableRequestType::MANAGE_OFFER ? 5
        : which == (int32_t)ReviewableRequestType::CREATE_PAYMENT ? 6
        : which == (int32_t)ReviewableRequestType::PERFORM_REDEMPTION ? 7
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)ReviewableRequestType::CREATE_SALE:
        _f(&_typeExt_t::saleExtended_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::NONE:
        return true;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
        _f(&_typeExt_t::atomicSwapBidExtended_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
        _f(&_typeExt_t::atomicSwapAskExtended_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::CREATE_POLL:
        _f(&_typeExt_t::createPoll_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::MANAGE_OFFER:
        _f(&_typeExt_t::manageOfferResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::CREATE_PAYMENT:
        _f(&_typeExt_t::paymentResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::PERFORM_REDEMPTION:
        _f(&_typeExt_t::createRedemptionResult_, std::forward<_A>(_a)...);
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return requestType_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of requestType in _typeExt_t");
      if (fnum != _xdr_field_number(requestType_)) {
        this->~_typeExt_t();
        requestType_ = which;switch (requestType_)
{
        case (int32_t)ReviewableRequestType::CREATE_SALE:
new(&saleExtended_) SaleExtended{};
break;
        case (int32_t)ReviewableRequestType::NONE:
          break;
        case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
new(&atomicSwapBidExtended_) AtomicSwapBidExtended{};
break;
        case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
new(&atomicSwapAskExtended_) AtomicSwapAskExtended{};
break;
        case (int32_t)ReviewableRequestType::CREATE_POLL:
new(&createPoll_) CreatePollExtended{};
break;
        case (int32_t)ReviewableRequestType::MANAGE_OFFER:
new(&manageOfferResult_) ManageOfferResult{};
break;
        case (int32_t)ReviewableRequestType::CREATE_PAYMENT:
new(&paymentResult_) PaymentResult{};
break;
        case (int32_t)ReviewableRequestType::PERFORM_REDEMPTION:
new(&createRedemptionResult_) CreateRedemptionRequestResult{};
break;
}

      }
      else
        requestType_ = which;
    }
    explicit _typeExt_t(ReviewableRequestType which = ReviewableRequestType{}) : requestType_((int32_t)which) {
      switch (requestType_)
{
      case (int32_t)ReviewableRequestType::CREATE_SALE:
new(&saleExtended_) SaleExtended{};
break;
      case (int32_t)ReviewableRequestType::NONE:
        break;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
new(&atomicSwapBidExtended_) AtomicSwapBidExtended{};
break;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
new(&atomicSwapAskExtended_) AtomicSwapAskExtended{};
break;
      case (int32_t)ReviewableRequestType::CREATE_POLL:
new(&createPoll_) CreatePollExtended{};
break;
      case (int32_t)ReviewableRequestType::MANAGE_OFFER:
new(&manageOfferResult_) ManageOfferResult{};
break;
      case (int32_t)ReviewableRequestType::CREATE_PAYMENT:
new(&paymentResult_) PaymentResult{};
break;
      case (int32_t)ReviewableRequestType::PERFORM_REDEMPTION:
new(&createRedemptionResult_) CreateRedemptionRequestResult{};
break;
}

    }
    _typeExt_t(const _typeExt_t &source) : requestType_(source.requestType_) {
      switch (requestType_)
{
      case (int32_t)ReviewableRequestType::CREATE_SALE:
new(&saleExtended_) SaleExtended(source.saleExtended_);
break;
      case (int32_t)ReviewableRequestType::NONE:
        break;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
new(&atomicSwapBidExtended_) AtomicSwapBidExtended(source.atomicSwapBidExtended_);
break;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
new(&atomicSwapAskExtended_) AtomicSwapAskExtended(source.atomicSwapAskExtended_);
break;
      case (int32_t)ReviewableRequestType::CREATE_POLL:
new(&createPoll_) CreatePollExtended(source.createPoll_);
break;
      case (int32_t)ReviewableRequestType::MANAGE_OFFER:
new(&manageOfferResult_) ManageOfferResult(source.manageOfferResult_);
break;
      case (int32_t)ReviewableRequestType::CREATE_PAYMENT:
new(&paymentResult_) PaymentResult(source.paymentResult_);
break;
      case (int32_t)ReviewableRequestType::PERFORM_REDEMPTION:
new(&createRedemptionResult_) CreateRedemptionRequestResult(source.createRedemptionResult_);
break;
}

    }
    _typeExt_t(_typeExt_t &&source) : requestType_(source.requestType_) {
      switch (requestType_)
{
      case (int32_t)ReviewableRequestType::CREATE_SALE:
new(&saleExtended_) SaleExtended(std::move(source.saleExtended_));
break;
      case (int32_t)ReviewableRequestType::NONE:
        break;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
new(&atomicSwapBidExtended_) AtomicSwapBidExtended(std::move(source.atomicSwapBidExtended_));
break;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
new(&atomicSwapAskExtended_) AtomicSwapAskExtended(std::move(source.atomicSwapAskExtended_));
break;
      case (int32_t)ReviewableRequestType::CREATE_POLL:
new(&createPoll_) CreatePollExtended(std::move(source.createPoll_));
break;
      case (int32_t)ReviewableRequestType::MANAGE_OFFER:
new(&manageOfferResult_) ManageOfferResult(std::move(source.manageOfferResult_));
break;
      case (int32_t)ReviewableRequestType::CREATE_PAYMENT:
new(&paymentResult_) PaymentResult(std::move(source.paymentResult_));
break;
      case (int32_t)ReviewableRequestType::PERFORM_REDEMPTION:
new(&createRedemptionResult_) CreateRedemptionRequestResult(std::move(source.createRedemptionResult_));
break;
}

    }
    ~_typeExt_t() {
switch (requestType_)
{
    case (int32_t)ReviewableRequestType::CREATE_SALE:
saleExtended_.~SaleExtended();
break;
    case (int32_t)ReviewableRequestType::NONE:
      break;
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
atomicSwapBidExtended_.~AtomicSwapBidExtended();
break;
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
atomicSwapAskExtended_.~AtomicSwapAskExtended();
break;
    case (int32_t)ReviewableRequestType::CREATE_POLL:
createPoll_.~CreatePollExtended();
break;
    case (int32_t)ReviewableRequestType::MANAGE_OFFER:
manageOfferResult_.~ManageOfferResult();
break;
    case (int32_t)ReviewableRequestType::CREATE_PAYMENT:
paymentResult_.~PaymentResult();
break;
    case (int32_t)ReviewableRequestType::PERFORM_REDEMPTION:
createRedemptionResult_.~CreateRedemptionRequestResult();
break;
}
}

    _typeExt_t &operator=(const _typeExt_t &source) {
      if (requestType_ == source.requestType_)
{
switch (requestType_)
{
      case (int32_t)ReviewableRequestType::CREATE_SALE:
saleExtended_ = source.saleExtended_;
break;
      case (int32_t)ReviewableRequestType::NONE:
        break;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
atomicSwapBidExtended_ = source.atomicSwapBidExtended_;
break;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
atomicSwapAskExtended_ = source.atomicSwapAskExtended_;
break;
      case (int32_t)ReviewableRequestType::CREATE_POLL:
createPoll_ = source.createPoll_;
break;
      case (int32_t)ReviewableRequestType::MANAGE_OFFER:
manageOfferResult_ = source.manageOfferResult_;
break;
      case (int32_t)ReviewableRequestType::CREATE_PAYMENT:
paymentResult_ = source.paymentResult_;
break;
      case (int32_t)ReviewableRequestType::PERFORM_REDEMPTION:
createRedemptionResult_ = source.createRedemptionResult_;
break;
}
}
else {this->~_typeExt_t();
      requestType_ = source.requestType_;
switch (requestType_)
{
      case (int32_t)ReviewableRequestType::CREATE_SALE:
new(&saleExtended_) SaleExtended(source.saleExtended_);
break;
      case (int32_t)ReviewableRequestType::NONE:
        break;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
new(&atomicSwapBidExtended_) AtomicSwapBidExtended(source.atomicSwapBidExtended_);
break;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
new(&atomicSwapAskExtended_) AtomicSwapAskExtended(source.atomicSwapAskExtended_);
break;
      case (int32_t)ReviewableRequestType::CREATE_POLL:
new(&createPoll_) CreatePollExtended(source.createPoll_);
break;
      case (int32_t)ReviewableRequestType::MANAGE_OFFER:
new(&manageOfferResult_) ManageOfferResult(source.manageOfferResult_);
break;
      case (int32_t)ReviewableRequestType::CREATE_PAYMENT:
new(&paymentResult_) PaymentResult(source.paymentResult_);
break;
      case (int32_t)ReviewableRequestType::PERFORM_REDEMPTION:
new(&createRedemptionResult_) CreateRedemptionRequestResult(source.createRedemptionResult_);
break;
}
}
      return *this;
    }
    _typeExt_t &operator=(_typeExt_t &&source) {
      if (requestType_ == source.requestType_)
{
switch (requestType_)
{
      case (int32_t)ReviewableRequestType::CREATE_SALE:
saleExtended_ = std::move(source.saleExtended_);
break;
      case (int32_t)ReviewableRequestType::NONE:
        break;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
atomicSwapBidExtended_ = std::move(source.atomicSwapBidExtended_);
break;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
atomicSwapAskExtended_ = std::move(source.atomicSwapAskExtended_);
break;
      case (int32_t)ReviewableRequestType::CREATE_POLL:
createPoll_ = std::move(source.createPoll_);
break;
      case (int32_t)ReviewableRequestType::MANAGE_OFFER:
manageOfferResult_ = std::move(source.manageOfferResult_);
break;
      case (int32_t)ReviewableRequestType::CREATE_PAYMENT:
paymentResult_ = std::move(source.paymentResult_);
break;
      case (int32_t)ReviewableRequestType::PERFORM_REDEMPTION:
createRedemptionResult_ = std::move(source.createRedemptionResult_);
break;
}
}
else {this->~_typeExt_t();
      requestType_ = std::move(source.requestType_);
switch (requestType_)
{
      case (int32_t)ReviewableRequestType::CREATE_SALE:
new(&saleExtended_) SaleExtended(std::move(source.saleExtended_));
break;
      case (int32_t)ReviewableRequestType::NONE:
        break;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
new(&atomicSwapBidExtended_) AtomicSwapBidExtended(std::move(source.atomicSwapBidExtended_));
break;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
new(&atomicSwapAskExtended_) AtomicSwapAskExtended(std::move(source.atomicSwapAskExtended_));
break;
      case (int32_t)ReviewableRequestType::CREATE_POLL:
new(&createPoll_) CreatePollExtended(std::move(source.createPoll_));
break;
      case (int32_t)ReviewableRequestType::MANAGE_OFFER:
new(&manageOfferResult_) ManageOfferResult(std::move(source.manageOfferResult_));
break;
      case (int32_t)ReviewableRequestType::CREATE_PAYMENT:
new(&paymentResult_) PaymentResult(std::move(source.paymentResult_));
break;
      case (int32_t)ReviewableRequestType::PERFORM_REDEMPTION:
new(&createRedemptionResult_) CreateRedemptionRequestResult(std::move(source.createRedemptionResult_));
break;
}
}
      return *this;
    }

    ReviewableRequestType requestType() const { return ReviewableRequestType(requestType_); }
    _typeExt_t &requestType(ReviewableRequestType _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    SaleExtended &saleExtended() {
      if (_xdr_field_number(requestType_) == 1)
        return saleExtended_;
      throw xdr::xdr_wrong_union("_typeExt_t: saleExtended accessed when not selected");
    }
    const SaleExtended &saleExtended() const {
      if (_xdr_field_number(requestType_) == 1)
        return saleExtended_;
      throw xdr::xdr_wrong_union("_typeExt_t: saleExtended accessed when not selected");
    }
    AtomicSwapBidExtended &atomicSwapBidExtended() {
      if (_xdr_field_number(requestType_) == 2)
        return atomicSwapBidExtended_;
      throw xdr::xdr_wrong_union("_typeExt_t: atomicSwapBidExtended accessed when not selected");
    }
    const AtomicSwapBidExtended &atomicSwapBidExtended() const {
      if (_xdr_field_number(requestType_) == 2)
        return atomicSwapBidExtended_;
      throw xdr::xdr_wrong_union("_typeExt_t: atomicSwapBidExtended accessed when not selected");
    }
    AtomicSwapAskExtended &atomicSwapAskExtended() {
      if (_xdr_field_number(requestType_) == 3)
        return atomicSwapAskExtended_;
      throw xdr::xdr_wrong_union("_typeExt_t: atomicSwapAskExtended accessed when not selected");
    }
    const AtomicSwapAskExtended &atomicSwapAskExtended() const {
      if (_xdr_field_number(requestType_) == 3)
        return atomicSwapAskExtended_;
      throw xdr::xdr_wrong_union("_typeExt_t: atomicSwapAskExtended accessed when not selected");
    }
    CreatePollExtended &createPoll() {
      if (_xdr_field_number(requestType_) == 4)
        return createPoll_;
      throw xdr::xdr_wrong_union("_typeExt_t: createPoll accessed when not selected");
    }
    const CreatePollExtended &createPoll() const {
      if (_xdr_field_number(requestType_) == 4)
        return createPoll_;
      throw xdr::xdr_wrong_union("_typeExt_t: createPoll accessed when not selected");
    }
    ManageOfferResult &manageOfferResult() {
      if (_xdr_field_number(requestType_) == 5)
        return manageOfferResult_;
      throw xdr::xdr_wrong_union("_typeExt_t: manageOfferResult accessed when not selected");
    }
    const ManageOfferResult &manageOfferResult() const {
      if (_xdr_field_number(requestType_) == 5)
        return manageOfferResult_;
      throw xdr::xdr_wrong_union("_typeExt_t: manageOfferResult accessed when not selected");
    }
    PaymentResult &paymentResult() {
      if (_xdr_field_number(requestType_) == 6)
        return paymentResult_;
      throw xdr::xdr_wrong_union("_typeExt_t: paymentResult accessed when not selected");
    }
    const PaymentResult &paymentResult() const {
      if (_xdr_field_number(requestType_) == 6)
        return paymentResult_;
      throw xdr::xdr_wrong_union("_typeExt_t: paymentResult accessed when not selected");
    }
    CreateRedemptionRequestResult &createRedemptionResult() {
      if (_xdr_field_number(requestType_) == 7)
        return createRedemptionResult_;
      throw xdr::xdr_wrong_union("_typeExt_t: createRedemptionResult accessed when not selected");
    }
    const CreateRedemptionRequestResult &createRedemptionResult() const {
      if (_xdr_field_number(requestType_) == 7)
        return createRedemptionResult_;
      throw xdr::xdr_wrong_union("_typeExt_t: createRedemptionResult accessed when not selected");
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

  bool fulfilled{};
  _typeExt_t typeExt{};
  _ext_t ext{};

  ExtendedResult() = default;
  template<typename _fulfilled_T,
           typename _typeExt_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<bool, _fulfilled_T>::value
                          && std::is_constructible<_typeExt_t, _typeExt_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ExtendedResult(_fulfilled_T &&_fulfilled,
                          _typeExt_T &&_typeExt,
                          _ext_T &&_ext)
    : fulfilled(std::forward<_fulfilled_T>(_fulfilled)),
      typeExt(std::forward<_typeExt_T>(_typeExt)),
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

struct ReviewRequestOp  : xdr::xdr_abstract {
  struct _requestDetails_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<ReviewableRequestType>::case_type;
  private:
    _xdr_case_type requestType_;
    union {
      WithdrawalDetails withdrawal_;
      LimitsUpdateDetails limitsUpdate_;
      AMLAlertDetails amlAlertDetails_;
      BillPayDetails billPay_;
      ContractDetails contract_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = true;
    static const std::vector<ReviewableRequestType> &_xdr_case_values() {
      static const std::vector<ReviewableRequestType> _xdr_disc_vec {};
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)ReviewableRequestType::CREATE_WITHDRAW ? 1
        : which == (int32_t)ReviewableRequestType::UPDATE_LIMITS ? 2
        : which == (int32_t)ReviewableRequestType::CREATE_AML_ALERT ? 3
        : which == (int32_t)ReviewableRequestType::CREATE_INVOICE ? 4
        : which == (int32_t)ReviewableRequestType::MANAGE_CONTRACT ? 5
        : 0;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
        _f(&_requestDetails_t::withdrawal_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::UPDATE_LIMITS:
        _f(&_requestDetails_t::limitsUpdate_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::CREATE_AML_ALERT:
        _f(&_requestDetails_t::amlAlertDetails_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::CREATE_INVOICE:
        _f(&_requestDetails_t::billPay_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::MANAGE_CONTRACT:
        _f(&_requestDetails_t::contract_, std::forward<_A>(_a)...);
        return true;
      default:
        return true;
      }
    }

    _xdr_case_type _xdr_discriminant() const { return requestType_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of requestType in _requestDetails_t");
      if (fnum != _xdr_field_number(requestType_)) {
        this->~_requestDetails_t();
        requestType_ = which;switch (requestType_)
{
        case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
new(&withdrawal_) WithdrawalDetails{};
break;
        case (int32_t)ReviewableRequestType::UPDATE_LIMITS:
new(&limitsUpdate_) LimitsUpdateDetails{};
break;
        case (int32_t)ReviewableRequestType::CREATE_AML_ALERT:
new(&amlAlertDetails_) AMLAlertDetails{};
break;
        case (int32_t)ReviewableRequestType::CREATE_INVOICE:
new(&billPay_) BillPayDetails{};
break;
        case (int32_t)ReviewableRequestType::MANAGE_CONTRACT:
new(&contract_) ContractDetails{};
break;
        default:
          break;
}

      }
      else
        requestType_ = which;
    }
    explicit _requestDetails_t(ReviewableRequestType which = ReviewableRequestType{}) : requestType_((int32_t)which) {
      switch (requestType_)
{
      case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
new(&withdrawal_) WithdrawalDetails{};
break;
      case (int32_t)ReviewableRequestType::UPDATE_LIMITS:
new(&limitsUpdate_) LimitsUpdateDetails{};
break;
      case (int32_t)ReviewableRequestType::CREATE_AML_ALERT:
new(&amlAlertDetails_) AMLAlertDetails{};
break;
      case (int32_t)ReviewableRequestType::CREATE_INVOICE:
new(&billPay_) BillPayDetails{};
break;
      case (int32_t)ReviewableRequestType::MANAGE_CONTRACT:
new(&contract_) ContractDetails{};
break;
      default:
        break;
}

    }
    _requestDetails_t(const _requestDetails_t &source) : requestType_(source.requestType_) {
      switch (requestType_)
{
      case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
new(&withdrawal_) WithdrawalDetails(source.withdrawal_);
break;
      case (int32_t)ReviewableRequestType::UPDATE_LIMITS:
new(&limitsUpdate_) LimitsUpdateDetails(source.limitsUpdate_);
break;
      case (int32_t)ReviewableRequestType::CREATE_AML_ALERT:
new(&amlAlertDetails_) AMLAlertDetails(source.amlAlertDetails_);
break;
      case (int32_t)ReviewableRequestType::CREATE_INVOICE:
new(&billPay_) BillPayDetails(source.billPay_);
break;
      case (int32_t)ReviewableRequestType::MANAGE_CONTRACT:
new(&contract_) ContractDetails(source.contract_);
break;
      default:
        break;
}

    }
    _requestDetails_t(_requestDetails_t &&source) : requestType_(source.requestType_) {
      switch (requestType_)
{
      case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
new(&withdrawal_) WithdrawalDetails(std::move(source.withdrawal_));
break;
      case (int32_t)ReviewableRequestType::UPDATE_LIMITS:
new(&limitsUpdate_) LimitsUpdateDetails(std::move(source.limitsUpdate_));
break;
      case (int32_t)ReviewableRequestType::CREATE_AML_ALERT:
new(&amlAlertDetails_) AMLAlertDetails(std::move(source.amlAlertDetails_));
break;
      case (int32_t)ReviewableRequestType::CREATE_INVOICE:
new(&billPay_) BillPayDetails(std::move(source.billPay_));
break;
      case (int32_t)ReviewableRequestType::MANAGE_CONTRACT:
new(&contract_) ContractDetails(std::move(source.contract_));
break;
      default:
        break;
}

    }
    ~_requestDetails_t() {
switch (requestType_)
{
    case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
withdrawal_.~WithdrawalDetails();
break;
    case (int32_t)ReviewableRequestType::UPDATE_LIMITS:
limitsUpdate_.~LimitsUpdateDetails();
break;
    case (int32_t)ReviewableRequestType::CREATE_AML_ALERT:
amlAlertDetails_.~AMLAlertDetails();
break;
    case (int32_t)ReviewableRequestType::CREATE_INVOICE:
billPay_.~BillPayDetails();
break;
    case (int32_t)ReviewableRequestType::MANAGE_CONTRACT:
contract_.~ContractDetails();
break;
    default:
      break;
}
}

    _requestDetails_t &operator=(const _requestDetails_t &source) {
      if (requestType_ == source.requestType_)
{
switch (requestType_)
{
      case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
withdrawal_ = source.withdrawal_;
break;
      case (int32_t)ReviewableRequestType::UPDATE_LIMITS:
limitsUpdate_ = source.limitsUpdate_;
break;
      case (int32_t)ReviewableRequestType::CREATE_AML_ALERT:
amlAlertDetails_ = source.amlAlertDetails_;
break;
      case (int32_t)ReviewableRequestType::CREATE_INVOICE:
billPay_ = source.billPay_;
break;
      case (int32_t)ReviewableRequestType::MANAGE_CONTRACT:
contract_ = source.contract_;
break;
      default:
        break;
}
}
else {this->~_requestDetails_t();
      requestType_ = source.requestType_;
switch (requestType_)
{
      case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
new(&withdrawal_) WithdrawalDetails(source.withdrawal_);
break;
      case (int32_t)ReviewableRequestType::UPDATE_LIMITS:
new(&limitsUpdate_) LimitsUpdateDetails(source.limitsUpdate_);
break;
      case (int32_t)ReviewableRequestType::CREATE_AML_ALERT:
new(&amlAlertDetails_) AMLAlertDetails(source.amlAlertDetails_);
break;
      case (int32_t)ReviewableRequestType::CREATE_INVOICE:
new(&billPay_) BillPayDetails(source.billPay_);
break;
      case (int32_t)ReviewableRequestType::MANAGE_CONTRACT:
new(&contract_) ContractDetails(source.contract_);
break;
      default:
        break;
}
}
      return *this;
    }
    _requestDetails_t &operator=(_requestDetails_t &&source) {
      if (requestType_ == source.requestType_)
{
switch (requestType_)
{
      case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
withdrawal_ = std::move(source.withdrawal_);
break;
      case (int32_t)ReviewableRequestType::UPDATE_LIMITS:
limitsUpdate_ = std::move(source.limitsUpdate_);
break;
      case (int32_t)ReviewableRequestType::CREATE_AML_ALERT:
amlAlertDetails_ = std::move(source.amlAlertDetails_);
break;
      case (int32_t)ReviewableRequestType::CREATE_INVOICE:
billPay_ = std::move(source.billPay_);
break;
      case (int32_t)ReviewableRequestType::MANAGE_CONTRACT:
contract_ = std::move(source.contract_);
break;
      default:
        break;
}
}
else {this->~_requestDetails_t();
      requestType_ = std::move(source.requestType_);
switch (requestType_)
{
      case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
new(&withdrawal_) WithdrawalDetails(std::move(source.withdrawal_));
break;
      case (int32_t)ReviewableRequestType::UPDATE_LIMITS:
new(&limitsUpdate_) LimitsUpdateDetails(std::move(source.limitsUpdate_));
break;
      case (int32_t)ReviewableRequestType::CREATE_AML_ALERT:
new(&amlAlertDetails_) AMLAlertDetails(std::move(source.amlAlertDetails_));
break;
      case (int32_t)ReviewableRequestType::CREATE_INVOICE:
new(&billPay_) BillPayDetails(std::move(source.billPay_));
break;
      case (int32_t)ReviewableRequestType::MANAGE_CONTRACT:
new(&contract_) ContractDetails(std::move(source.contract_));
break;
      default:
        break;
}
}
      return *this;
    }

    ReviewableRequestType requestType() const { return ReviewableRequestType(requestType_); }
    _requestDetails_t &requestType(ReviewableRequestType _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    WithdrawalDetails &withdrawal() {
      if (_xdr_field_number(requestType_) == 1)
        return withdrawal_;
      throw xdr::xdr_wrong_union("_requestDetails_t: withdrawal accessed when not selected");
    }
    const WithdrawalDetails &withdrawal() const {
      if (_xdr_field_number(requestType_) == 1)
        return withdrawal_;
      throw xdr::xdr_wrong_union("_requestDetails_t: withdrawal accessed when not selected");
    }
    LimitsUpdateDetails &limitsUpdate() {
      if (_xdr_field_number(requestType_) == 2)
        return limitsUpdate_;
      throw xdr::xdr_wrong_union("_requestDetails_t: limitsUpdate accessed when not selected");
    }
    const LimitsUpdateDetails &limitsUpdate() const {
      if (_xdr_field_number(requestType_) == 2)
        return limitsUpdate_;
      throw xdr::xdr_wrong_union("_requestDetails_t: limitsUpdate accessed when not selected");
    }
    AMLAlertDetails &amlAlertDetails() {
      if (_xdr_field_number(requestType_) == 3)
        return amlAlertDetails_;
      throw xdr::xdr_wrong_union("_requestDetails_t: amlAlertDetails accessed when not selected");
    }
    const AMLAlertDetails &amlAlertDetails() const {
      if (_xdr_field_number(requestType_) == 3)
        return amlAlertDetails_;
      throw xdr::xdr_wrong_union("_requestDetails_t: amlAlertDetails accessed when not selected");
    }
    BillPayDetails &billPay() {
      if (_xdr_field_number(requestType_) == 4)
        return billPay_;
      throw xdr::xdr_wrong_union("_requestDetails_t: billPay accessed when not selected");
    }
    const BillPayDetails &billPay() const {
      if (_xdr_field_number(requestType_) == 4)
        return billPay_;
      throw xdr::xdr_wrong_union("_requestDetails_t: billPay accessed when not selected");
    }
    ContractDetails &contract() {
      if (_xdr_field_number(requestType_) == 5)
        return contract_;
      throw xdr::xdr_wrong_union("_requestDetails_t: contract accessed when not selected");
    }
    const ContractDetails &contract() const {
      if (_xdr_field_number(requestType_) == 5)
        return contract_;
      throw xdr::xdr_wrong_union("_requestDetails_t: contract accessed when not selected");
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

  uint64 requestID{};
  Hash requestHash{};
  _requestDetails_t requestDetails{};
  ReviewRequestOpAction action{};
  longstring reason{};
  ReviewDetails reviewDetails{};
  _ext_t ext{};

  ReviewRequestOp() = default;
  template<typename _requestID_T,
           typename _requestHash_T,
           typename _requestDetails_T,
           typename _action_T,
           typename _reason_T,
           typename _reviewDetails_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<Hash, _requestHash_T>::value
                          && std::is_constructible<_requestDetails_t, _requestDetails_T>::value
                          && std::is_constructible<ReviewRequestOpAction, _action_T>::value
                          && std::is_constructible<longstring, _reason_T>::value
                          && std::is_constructible<ReviewDetails, _reviewDetails_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ReviewRequestOp(_requestID_T &&_requestID,
                           _requestHash_T &&_requestHash,
                           _requestDetails_T &&_requestDetails,
                           _action_T &&_action,
                           _reason_T &&_reason,
                           _reviewDetails_T &&_reviewDetails,
                           _ext_T &&_ext)
    : requestID(std::forward<_requestID_T>(_requestID)),
      requestHash(std::forward<_requestHash_T>(_requestHash)),
      requestDetails(std::forward<_requestDetails_T>(_requestDetails)),
      action(std::forward<_action_T>(_action)),
      reason(std::forward<_reason_T>(_reason)),
      reviewDetails(std::forward<_reviewDetails_T>(_reviewDetails)),
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

enum class ReviewRequestResultCode : std::int32_t {
  SUCCESS = 0,
  INVALID_REASON = -1,
  INVALID_ACTION = -2,
  HASH_MISMATCHED = -3,
  NOT_FOUND = -4,
  TYPE_MISMATCHED = -5,
  REJECT_NOT_ALLOWED = -6,
  INVALID_EXTERNAL_DETAILS = -7,
  REQUESTOR_IS_BLOCKED = -8,
  PERMANENT_REJECT_NOT_ALLOWED = -9,
  REMOVING_NOT_SET_TASKS = -100,
  ASSET_ALREADY_EXISTS = -200,
  ASSET_DOES_NOT_EXISTS = -210,
  MAX_ISSUANCE_AMOUNT_EXCEEDED = -400,
  INSUFFICIENT_AVAILABLE_FOR_ISSUANCE_AMOUNT = -410,
  FULL_LINE = -420,
  SYSTEM_TASKS_NOT_ALLOWED = -430,
  INCORRECT_PRECISION = -440,
  BASE_ASSET_DOES_NOT_EXISTS = -500,
  HARD_CAP_WILL_EXCEED_MAX_ISSUANCE = -510,
  INSUFFICIENT_PREISSUED_FOR_HARD_CAP = -520,
  BASE_ASSET_NOT_FOUND = -530,
  ASSET_PAIR_NOT_FOUND = -540,
  QUOTE_ASSET_NOT_FOUND = -550,
  NON_ZERO_TASKS_TO_REMOVE_NOT_ALLOWED = -600,
  ACCOUNT_ROLE_TO_SET_DOES_NOT_EXIST = -610,
  SALE_NOT_FOUND = -700,
  AMOUNT_MISMATCHED = -1010,
  DESTINATION_BALANCE_MISMATCHED = -1020,
  NOT_ALLOWED_ACCOUNT_DESTINATION = -1030,
  REQUIRED_SOURCE_PAY_FOR_DESTINATION = -1040,
  SOURCE_BALANCE_MISMATCHED = -1050,
  CONTRACT_NOT_FOUND = -1060,
  INVOICE_RECEIVER_BALANCE_LOCK_AMOUNT_OVERFLOW = -1070,
  INVOICE_ALREADY_APPROVED = -1080,
  PAYMENT_V2_MALFORMED = -1100,
  UNDERFUNDED = -1110,
  LINE_FULL = -1120,
  DESTINATION_BALANCE_NOT_FOUND = -1130,
  BALANCE_ASSETS_MISMATCHED = -1140,
  SRC_BALANCE_NOT_FOUND = -1150,
  REFERENCE_DUPLICATION = -1160,
  STATS_OVERFLOW = -1170,
  LIMITS_EXCEEDED = -1180,
  NOT_ALLOWED_BY_ASSET_POLICY = -1190,
  INVALID_DESTINATION_FEE = -1200,
  INVALID_DESTINATION_FEE_ASSET = -1210,
  FEE_ASSET_MISMATCHED = -1220,
  INSUFFICIENT_FEE_AMOUNT = -1230,
  BALANCE_TO_CHARGE_FEE_FROM_NOT_FOUND = -1240,
  PAYMENT_AMOUNT_IS_LESS_THAN_DEST_FEE = -1250,
  DESTINATION_ACCOUNT_NOT_FOUND = -1260,
  CANNOT_CREATE_FOR_ACC_ID_AND_ACC_TYPE = 1300,
  INVALID_LIMITS = 1310,
  ACCOUNT_NOT_FOUND = -1311,
  ROLE_NOT_FOUND = -1312,
  CONTRACT_DETAILS_TOO_LONG = -1400,
  BASE_ASSET_CANNOT_BE_SWAPPED = -1500,
  QUOTE_ASSET_CANNOT_BE_SWAPPED = -1501,
  ATOMIC_SWAP_BID_OWNER_FULL_LINE = -1504,
  INVALID_SIGNER_DATA = -1600,
  MANAGE_OFFER_FAILED = -1700,
  PAYMENT_FAILED = -1800,
  DATA_NOT_FOUND = -1900,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ReviewRequestResultCode>
  : xdr_integral_base<::stellar::ReviewRequestResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ReviewRequestResultCode val) {
    switch (val) {
    case ::stellar::ReviewRequestResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::ReviewRequestResultCode::INVALID_REASON:
      return "INVALID_REASON";
    case ::stellar::ReviewRequestResultCode::INVALID_ACTION:
      return "INVALID_ACTION";
    case ::stellar::ReviewRequestResultCode::HASH_MISMATCHED:
      return "HASH_MISMATCHED";
    case ::stellar::ReviewRequestResultCode::NOT_FOUND:
      return "NOT_FOUND";
    case ::stellar::ReviewRequestResultCode::TYPE_MISMATCHED:
      return "TYPE_MISMATCHED";
    case ::stellar::ReviewRequestResultCode::REJECT_NOT_ALLOWED:
      return "REJECT_NOT_ALLOWED";
    case ::stellar::ReviewRequestResultCode::INVALID_EXTERNAL_DETAILS:
      return "INVALID_EXTERNAL_DETAILS";
    case ::stellar::ReviewRequestResultCode::REQUESTOR_IS_BLOCKED:
      return "REQUESTOR_IS_BLOCKED";
    case ::stellar::ReviewRequestResultCode::PERMANENT_REJECT_NOT_ALLOWED:
      return "PERMANENT_REJECT_NOT_ALLOWED";
    case ::stellar::ReviewRequestResultCode::REMOVING_NOT_SET_TASKS:
      return "REMOVING_NOT_SET_TASKS";
    case ::stellar::ReviewRequestResultCode::ASSET_ALREADY_EXISTS:
      return "ASSET_ALREADY_EXISTS";
    case ::stellar::ReviewRequestResultCode::ASSET_DOES_NOT_EXISTS:
      return "ASSET_DOES_NOT_EXISTS";
    case ::stellar::ReviewRequestResultCode::MAX_ISSUANCE_AMOUNT_EXCEEDED:
      return "MAX_ISSUANCE_AMOUNT_EXCEEDED";
    case ::stellar::ReviewRequestResultCode::INSUFFICIENT_AVAILABLE_FOR_ISSUANCE_AMOUNT:
      return "INSUFFICIENT_AVAILABLE_FOR_ISSUANCE_AMOUNT";
    case ::stellar::ReviewRequestResultCode::FULL_LINE:
      return "FULL_LINE";
    case ::stellar::ReviewRequestResultCode::SYSTEM_TASKS_NOT_ALLOWED:
      return "SYSTEM_TASKS_NOT_ALLOWED";
    case ::stellar::ReviewRequestResultCode::INCORRECT_PRECISION:
      return "INCORRECT_PRECISION";
    case ::stellar::ReviewRequestResultCode::BASE_ASSET_DOES_NOT_EXISTS:
      return "BASE_ASSET_DOES_NOT_EXISTS";
    case ::stellar::ReviewRequestResultCode::HARD_CAP_WILL_EXCEED_MAX_ISSUANCE:
      return "HARD_CAP_WILL_EXCEED_MAX_ISSUANCE";
    case ::stellar::ReviewRequestResultCode::INSUFFICIENT_PREISSUED_FOR_HARD_CAP:
      return "INSUFFICIENT_PREISSUED_FOR_HARD_CAP";
    case ::stellar::ReviewRequestResultCode::BASE_ASSET_NOT_FOUND:
      return "BASE_ASSET_NOT_FOUND";
    case ::stellar::ReviewRequestResultCode::ASSET_PAIR_NOT_FOUND:
      return "ASSET_PAIR_NOT_FOUND";
    case ::stellar::ReviewRequestResultCode::QUOTE_ASSET_NOT_FOUND:
      return "QUOTE_ASSET_NOT_FOUND";
    case ::stellar::ReviewRequestResultCode::NON_ZERO_TASKS_TO_REMOVE_NOT_ALLOWED:
      return "NON_ZERO_TASKS_TO_REMOVE_NOT_ALLOWED";
    case ::stellar::ReviewRequestResultCode::ACCOUNT_ROLE_TO_SET_DOES_NOT_EXIST:
      return "ACCOUNT_ROLE_TO_SET_DOES_NOT_EXIST";
    case ::stellar::ReviewRequestResultCode::SALE_NOT_FOUND:
      return "SALE_NOT_FOUND";
    case ::stellar::ReviewRequestResultCode::AMOUNT_MISMATCHED:
      return "AMOUNT_MISMATCHED";
    case ::stellar::ReviewRequestResultCode::DESTINATION_BALANCE_MISMATCHED:
      return "DESTINATION_BALANCE_MISMATCHED";
    case ::stellar::ReviewRequestResultCode::NOT_ALLOWED_ACCOUNT_DESTINATION:
      return "NOT_ALLOWED_ACCOUNT_DESTINATION";
    case ::stellar::ReviewRequestResultCode::REQUIRED_SOURCE_PAY_FOR_DESTINATION:
      return "REQUIRED_SOURCE_PAY_FOR_DESTINATION";
    case ::stellar::ReviewRequestResultCode::SOURCE_BALANCE_MISMATCHED:
      return "SOURCE_BALANCE_MISMATCHED";
    case ::stellar::ReviewRequestResultCode::CONTRACT_NOT_FOUND:
      return "CONTRACT_NOT_FOUND";
    case ::stellar::ReviewRequestResultCode::INVOICE_RECEIVER_BALANCE_LOCK_AMOUNT_OVERFLOW:
      return "INVOICE_RECEIVER_BALANCE_LOCK_AMOUNT_OVERFLOW";
    case ::stellar::ReviewRequestResultCode::INVOICE_ALREADY_APPROVED:
      return "INVOICE_ALREADY_APPROVED";
    case ::stellar::ReviewRequestResultCode::PAYMENT_V2_MALFORMED:
      return "PAYMENT_V2_MALFORMED";
    case ::stellar::ReviewRequestResultCode::UNDERFUNDED:
      return "UNDERFUNDED";
    case ::stellar::ReviewRequestResultCode::LINE_FULL:
      return "LINE_FULL";
    case ::stellar::ReviewRequestResultCode::DESTINATION_BALANCE_NOT_FOUND:
      return "DESTINATION_BALANCE_NOT_FOUND";
    case ::stellar::ReviewRequestResultCode::BALANCE_ASSETS_MISMATCHED:
      return "BALANCE_ASSETS_MISMATCHED";
    case ::stellar::ReviewRequestResultCode::SRC_BALANCE_NOT_FOUND:
      return "SRC_BALANCE_NOT_FOUND";
    case ::stellar::ReviewRequestResultCode::REFERENCE_DUPLICATION:
      return "REFERENCE_DUPLICATION";
    case ::stellar::ReviewRequestResultCode::STATS_OVERFLOW:
      return "STATS_OVERFLOW";
    case ::stellar::ReviewRequestResultCode::LIMITS_EXCEEDED:
      return "LIMITS_EXCEEDED";
    case ::stellar::ReviewRequestResultCode::NOT_ALLOWED_BY_ASSET_POLICY:
      return "NOT_ALLOWED_BY_ASSET_POLICY";
    case ::stellar::ReviewRequestResultCode::INVALID_DESTINATION_FEE:
      return "INVALID_DESTINATION_FEE";
    case ::stellar::ReviewRequestResultCode::INVALID_DESTINATION_FEE_ASSET:
      return "INVALID_DESTINATION_FEE_ASSET";
    case ::stellar::ReviewRequestResultCode::FEE_ASSET_MISMATCHED:
      return "FEE_ASSET_MISMATCHED";
    case ::stellar::ReviewRequestResultCode::INSUFFICIENT_FEE_AMOUNT:
      return "INSUFFICIENT_FEE_AMOUNT";
    case ::stellar::ReviewRequestResultCode::BALANCE_TO_CHARGE_FEE_FROM_NOT_FOUND:
      return "BALANCE_TO_CHARGE_FEE_FROM_NOT_FOUND";
    case ::stellar::ReviewRequestResultCode::PAYMENT_AMOUNT_IS_LESS_THAN_DEST_FEE:
      return "PAYMENT_AMOUNT_IS_LESS_THAN_DEST_FEE";
    case ::stellar::ReviewRequestResultCode::DESTINATION_ACCOUNT_NOT_FOUND:
      return "DESTINATION_ACCOUNT_NOT_FOUND";
    case ::stellar::ReviewRequestResultCode::CANNOT_CREATE_FOR_ACC_ID_AND_ACC_TYPE:
      return "CANNOT_CREATE_FOR_ACC_ID_AND_ACC_TYPE";
    case ::stellar::ReviewRequestResultCode::INVALID_LIMITS:
      return "INVALID_LIMITS";
    case ::stellar::ReviewRequestResultCode::ACCOUNT_NOT_FOUND:
      return "ACCOUNT_NOT_FOUND";
    case ::stellar::ReviewRequestResultCode::ROLE_NOT_FOUND:
      return "ROLE_NOT_FOUND";
    case ::stellar::ReviewRequestResultCode::CONTRACT_DETAILS_TOO_LONG:
      return "CONTRACT_DETAILS_TOO_LONG";
    case ::stellar::ReviewRequestResultCode::BASE_ASSET_CANNOT_BE_SWAPPED:
      return "BASE_ASSET_CANNOT_BE_SWAPPED";
    case ::stellar::ReviewRequestResultCode::QUOTE_ASSET_CANNOT_BE_SWAPPED:
      return "QUOTE_ASSET_CANNOT_BE_SWAPPED";
    case ::stellar::ReviewRequestResultCode::ATOMIC_SWAP_BID_OWNER_FULL_LINE:
      return "ATOMIC_SWAP_BID_OWNER_FULL_LINE";
    case ::stellar::ReviewRequestResultCode::INVALID_SIGNER_DATA:
      return "INVALID_SIGNER_DATA";
    case ::stellar::ReviewRequestResultCode::MANAGE_OFFER_FAILED:
      return "MANAGE_OFFER_FAILED";
    case ::stellar::ReviewRequestResultCode::PAYMENT_FAILED:
      return "PAYMENT_FAILED";
    case ::stellar::ReviewRequestResultCode::DATA_NOT_FOUND:
      return "DATA_NOT_FOUND";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ReviewRequestResultCode::SUCCESS,
      (int32_t)::stellar::ReviewRequestResultCode::INVALID_REASON,
      (int32_t)::stellar::ReviewRequestResultCode::INVALID_ACTION,
      (int32_t)::stellar::ReviewRequestResultCode::HASH_MISMATCHED,
      (int32_t)::stellar::ReviewRequestResultCode::NOT_FOUND,
      (int32_t)::stellar::ReviewRequestResultCode::TYPE_MISMATCHED,
      (int32_t)::stellar::ReviewRequestResultCode::REJECT_NOT_ALLOWED,
      (int32_t)::stellar::ReviewRequestResultCode::INVALID_EXTERNAL_DETAILS,
      (int32_t)::stellar::ReviewRequestResultCode::REQUESTOR_IS_BLOCKED,
      (int32_t)::stellar::ReviewRequestResultCode::PERMANENT_REJECT_NOT_ALLOWED,
      (int32_t)::stellar::ReviewRequestResultCode::REMOVING_NOT_SET_TASKS,
      (int32_t)::stellar::ReviewRequestResultCode::ASSET_ALREADY_EXISTS,
      (int32_t)::stellar::ReviewRequestResultCode::ASSET_DOES_NOT_EXISTS,
      (int32_t)::stellar::ReviewRequestResultCode::MAX_ISSUANCE_AMOUNT_EXCEEDED,
      (int32_t)::stellar::ReviewRequestResultCode::INSUFFICIENT_AVAILABLE_FOR_ISSUANCE_AMOUNT,
      (int32_t)::stellar::ReviewRequestResultCode::FULL_LINE,
      (int32_t)::stellar::ReviewRequestResultCode::SYSTEM_TASKS_NOT_ALLOWED,
      (int32_t)::stellar::ReviewRequestResultCode::INCORRECT_PRECISION,
      (int32_t)::stellar::ReviewRequestResultCode::BASE_ASSET_DOES_NOT_EXISTS,
      (int32_t)::stellar::ReviewRequestResultCode::HARD_CAP_WILL_EXCEED_MAX_ISSUANCE,
      (int32_t)::stellar::ReviewRequestResultCode::INSUFFICIENT_PREISSUED_FOR_HARD_CAP,
      (int32_t)::stellar::ReviewRequestResultCode::BASE_ASSET_NOT_FOUND,
      (int32_t)::stellar::ReviewRequestResultCode::ASSET_PAIR_NOT_FOUND,
      (int32_t)::stellar::ReviewRequestResultCode::QUOTE_ASSET_NOT_FOUND,
      (int32_t)::stellar::ReviewRequestResultCode::NON_ZERO_TASKS_TO_REMOVE_NOT_ALLOWED,
      (int32_t)::stellar::ReviewRequestResultCode::ACCOUNT_ROLE_TO_SET_DOES_NOT_EXIST,
      (int32_t)::stellar::ReviewRequestResultCode::SALE_NOT_FOUND,
      (int32_t)::stellar::ReviewRequestResultCode::AMOUNT_MISMATCHED,
      (int32_t)::stellar::ReviewRequestResultCode::DESTINATION_BALANCE_MISMATCHED,
      (int32_t)::stellar::ReviewRequestResultCode::NOT_ALLOWED_ACCOUNT_DESTINATION,
      (int32_t)::stellar::ReviewRequestResultCode::REQUIRED_SOURCE_PAY_FOR_DESTINATION,
      (int32_t)::stellar::ReviewRequestResultCode::SOURCE_BALANCE_MISMATCHED,
      (int32_t)::stellar::ReviewRequestResultCode::CONTRACT_NOT_FOUND,
      (int32_t)::stellar::ReviewRequestResultCode::INVOICE_RECEIVER_BALANCE_LOCK_AMOUNT_OVERFLOW,
      (int32_t)::stellar::ReviewRequestResultCode::INVOICE_ALREADY_APPROVED,
      (int32_t)::stellar::ReviewRequestResultCode::PAYMENT_V2_MALFORMED,
      (int32_t)::stellar::ReviewRequestResultCode::UNDERFUNDED,
      (int32_t)::stellar::ReviewRequestResultCode::LINE_FULL,
      (int32_t)::stellar::ReviewRequestResultCode::DESTINATION_BALANCE_NOT_FOUND,
      (int32_t)::stellar::ReviewRequestResultCode::BALANCE_ASSETS_MISMATCHED,
      (int32_t)::stellar::ReviewRequestResultCode::SRC_BALANCE_NOT_FOUND,
      (int32_t)::stellar::ReviewRequestResultCode::REFERENCE_DUPLICATION,
      (int32_t)::stellar::ReviewRequestResultCode::STATS_OVERFLOW,
      (int32_t)::stellar::ReviewRequestResultCode::LIMITS_EXCEEDED,
      (int32_t)::stellar::ReviewRequestResultCode::NOT_ALLOWED_BY_ASSET_POLICY,
      (int32_t)::stellar::ReviewRequestResultCode::INVALID_DESTINATION_FEE,
      (int32_t)::stellar::ReviewRequestResultCode::INVALID_DESTINATION_FEE_ASSET,
      (int32_t)::stellar::ReviewRequestResultCode::FEE_ASSET_MISMATCHED,
      (int32_t)::stellar::ReviewRequestResultCode::INSUFFICIENT_FEE_AMOUNT,
      (int32_t)::stellar::ReviewRequestResultCode::BALANCE_TO_CHARGE_FEE_FROM_NOT_FOUND,
      (int32_t)::stellar::ReviewRequestResultCode::PAYMENT_AMOUNT_IS_LESS_THAN_DEST_FEE,
      (int32_t)::stellar::ReviewRequestResultCode::DESTINATION_ACCOUNT_NOT_FOUND,
      (int32_t)::stellar::ReviewRequestResultCode::CANNOT_CREATE_FOR_ACC_ID_AND_ACC_TYPE,
      (int32_t)::stellar::ReviewRequestResultCode::INVALID_LIMITS,
      (int32_t)::stellar::ReviewRequestResultCode::ACCOUNT_NOT_FOUND,
      (int32_t)::stellar::ReviewRequestResultCode::ROLE_NOT_FOUND,
      (int32_t)::stellar::ReviewRequestResultCode::CONTRACT_DETAILS_TOO_LONG,
      (int32_t)::stellar::ReviewRequestResultCode::BASE_ASSET_CANNOT_BE_SWAPPED,
      (int32_t)::stellar::ReviewRequestResultCode::QUOTE_ASSET_CANNOT_BE_SWAPPED,
      (int32_t)::stellar::ReviewRequestResultCode::ATOMIC_SWAP_BID_OWNER_FULL_LINE,
      (int32_t)::stellar::ReviewRequestResultCode::INVALID_SIGNER_DATA,
      (int32_t)::stellar::ReviewRequestResultCode::MANAGE_OFFER_FAILED,
      (int32_t)::stellar::ReviewRequestResultCode::PAYMENT_FAILED,
      (int32_t)::stellar::ReviewRequestResultCode::DATA_NOT_FOUND
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ReviewRequestResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<ReviewRequestResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    ExtendedResult success_;
    ManageOfferResultCode manageOfferCode_;
    PaymentResultCode paymentCode_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<ReviewRequestResultCode> &_xdr_case_values() {
    static const std::vector<ReviewRequestResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)ReviewRequestResultCode::SUCCESS ? 1
      : which == (int32_t)ReviewRequestResultCode::MANAGE_OFFER_FAILED ? 2
      : which == (int32_t)ReviewRequestResultCode::PAYMENT_FAILED ? 3
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)ReviewRequestResultCode::SUCCESS:
      _f(&ReviewRequestResult::success_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)ReviewRequestResultCode::MANAGE_OFFER_FAILED:
      _f(&ReviewRequestResult::manageOfferCode_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)ReviewRequestResultCode::PAYMENT_FAILED:
      _f(&ReviewRequestResult::paymentCode_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in ReviewRequestResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~ReviewRequestResult();
      code_ = which;switch (code_)
{
      case (int32_t)ReviewRequestResultCode::SUCCESS:
new(&success_) ExtendedResult{};
break;
      case (int32_t)ReviewRequestResultCode::MANAGE_OFFER_FAILED:
new(&manageOfferCode_) ManageOfferResultCode{};
break;
      case (int32_t)ReviewRequestResultCode::PAYMENT_FAILED:
new(&paymentCode_) PaymentResultCode{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit ReviewRequestResult(ReviewRequestResultCode which = ReviewRequestResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)ReviewRequestResultCode::SUCCESS:
new(&success_) ExtendedResult{};
break;
    case (int32_t)ReviewRequestResultCode::MANAGE_OFFER_FAILED:
new(&manageOfferCode_) ManageOfferResultCode{};
break;
    case (int32_t)ReviewRequestResultCode::PAYMENT_FAILED:
new(&paymentCode_) PaymentResultCode{};
break;
    default:
      break;
}

  }
  ReviewRequestResult(const ReviewRequestResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ReviewRequestResultCode::SUCCESS:
new(&success_) ExtendedResult(source.success_);
break;
    case (int32_t)ReviewRequestResultCode::MANAGE_OFFER_FAILED:
new(&manageOfferCode_) ManageOfferResultCode(source.manageOfferCode_);
break;
    case (int32_t)ReviewRequestResultCode::PAYMENT_FAILED:
new(&paymentCode_) PaymentResultCode(source.paymentCode_);
break;
    default:
      break;
}

  }
  ReviewRequestResult(ReviewRequestResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ReviewRequestResultCode::SUCCESS:
new(&success_) ExtendedResult(std::move(source.success_));
break;
    case (int32_t)ReviewRequestResultCode::MANAGE_OFFER_FAILED:
new(&manageOfferCode_) ManageOfferResultCode(std::move(source.manageOfferCode_));
break;
    case (int32_t)ReviewRequestResultCode::PAYMENT_FAILED:
new(&paymentCode_) PaymentResultCode(std::move(source.paymentCode_));
break;
    default:
      break;
}

  }
  ~ReviewRequestResult() {
switch (code_)
{
  case (int32_t)ReviewRequestResultCode::SUCCESS:
success_.~ExtendedResult();
break;
  case (int32_t)ReviewRequestResultCode::MANAGE_OFFER_FAILED:
manageOfferCode_.~ManageOfferResultCode();
break;
  case (int32_t)ReviewRequestResultCode::PAYMENT_FAILED:
paymentCode_.~PaymentResultCode();
break;
  default:
    break;
}
}

  ReviewRequestResult &operator=(const ReviewRequestResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ReviewRequestResultCode::SUCCESS:
success_ = source.success_;
break;
    case (int32_t)ReviewRequestResultCode::MANAGE_OFFER_FAILED:
manageOfferCode_ = source.manageOfferCode_;
break;
    case (int32_t)ReviewRequestResultCode::PAYMENT_FAILED:
paymentCode_ = source.paymentCode_;
break;
    default:
      break;
}
}
else {this->~ReviewRequestResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)ReviewRequestResultCode::SUCCESS:
new(&success_) ExtendedResult(source.success_);
break;
    case (int32_t)ReviewRequestResultCode::MANAGE_OFFER_FAILED:
new(&manageOfferCode_) ManageOfferResultCode(source.manageOfferCode_);
break;
    case (int32_t)ReviewRequestResultCode::PAYMENT_FAILED:
new(&paymentCode_) PaymentResultCode(source.paymentCode_);
break;
    default:
      break;
}
}
    return *this;
  }
  ReviewRequestResult &operator=(ReviewRequestResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ReviewRequestResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    case (int32_t)ReviewRequestResultCode::MANAGE_OFFER_FAILED:
manageOfferCode_ = std::move(source.manageOfferCode_);
break;
    case (int32_t)ReviewRequestResultCode::PAYMENT_FAILED:
paymentCode_ = std::move(source.paymentCode_);
break;
    default:
      break;
}
}
else {this->~ReviewRequestResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)ReviewRequestResultCode::SUCCESS:
new(&success_) ExtendedResult(std::move(source.success_));
break;
    case (int32_t)ReviewRequestResultCode::MANAGE_OFFER_FAILED:
new(&manageOfferCode_) ManageOfferResultCode(std::move(source.manageOfferCode_));
break;
    case (int32_t)ReviewRequestResultCode::PAYMENT_FAILED:
new(&paymentCode_) PaymentResultCode(std::move(source.paymentCode_));
break;
    default:
      break;
}
}
    return *this;
  }

  ReviewRequestResultCode code() const { return ReviewRequestResultCode(code_); }
  ReviewRequestResult &code(ReviewRequestResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  ExtendedResult &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ReviewRequestResult: success accessed when not selected");
  }
  const ExtendedResult &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ReviewRequestResult: success accessed when not selected");
  }
  ManageOfferResultCode &manageOfferCode() {
    if (_xdr_field_number(code_) == 2)
      return manageOfferCode_;
    throw xdr::xdr_wrong_union("ReviewRequestResult: manageOfferCode accessed when not selected");
  }
  const ManageOfferResultCode &manageOfferCode() const {
    if (_xdr_field_number(code_) == 2)
      return manageOfferCode_;
    throw xdr::xdr_wrong_union("ReviewRequestResult: manageOfferCode accessed when not selected");
  }
  PaymentResultCode &paymentCode() {
    if (_xdr_field_number(code_) == 3)
      return paymentCode_;
    throw xdr::xdr_wrong_union("ReviewRequestResult: paymentCode accessed when not selected");
  }
  const PaymentResultCode &paymentCode() const {
    if (_xdr_field_number(code_) == 3)
      return paymentCode_;
    throw xdr::xdr_wrong_union("ReviewRequestResult: paymentCode accessed when not selected");
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

#endif // !__XDR_OPERATION_REVIEW_REQUEST_H_INCLUDED__
