// -*- C++ -*-
// Automatically generated from Stellar-operation-review-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_OPERATION_REVIEW_REQUEST_H_INCLUDED__
#define __XDR_STELLAR_OPERATION_REVIEW_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-ledger-entries.h"
#include "xdr/Stellar-operation-payment.h"

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
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
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

struct LimitsUpdateDetails {
  struct _ext_t {
    using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
  private:
    _xdr_case_type v_;
    union {
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<LedgerVersion> &_xdr_case_values() {
      static const std::vector<LedgerVersion> _xdr_disc_vec {
        LedgerVersion::EMPTY_VERSION
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
        v_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
      }
      else
        v_ = which;
    }
    explicit _ext_t(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                        std::move(source));
    }
    ~_ext_t() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
    _ext_t &operator=(const _ext_t &source) {
      if (_xdr_field_number(v_)
          == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
      }
      v_ = source.v_;
      return *this;
    }
    _ext_t &operator=(_ext_t &&source) {
      if (_xdr_field_number(v_)
           == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                          std::move(source));
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                          std::move(source));
      }
      v_ = source.v_;
      return *this;
    }

    LedgerVersion v() const { return LedgerVersion(v_); }
    _ext_t &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LimitsUpdateDetails::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LimitsUpdateDetails::_ext_t;
  using case_type = ::stellar::LimitsUpdateDetails::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LimitsUpdateDetails::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LimitsUpdateDetails::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LimitsUpdateDetails::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LimitsUpdateDetails>
  : xdr_struct_base<field_ptr<::stellar::LimitsUpdateDetails,
                              decltype(::stellar::LimitsUpdateDetails::newLimitsV2),
                              &::stellar::LimitsUpdateDetails::newLimitsV2>,
                    field_ptr<::stellar::LimitsUpdateDetails,
                              decltype(::stellar::LimitsUpdateDetails::ext),
                              &::stellar::LimitsUpdateDetails::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LimitsUpdateDetails &obj) {
    archive(ar, obj.newLimitsV2, "newLimitsV2");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LimitsUpdateDetails &obj) {
    archive(ar, obj.newLimitsV2, "newLimitsV2");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct WithdrawalDetails {
  struct _ext_t {
    using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
  private:
    _xdr_case_type v_;
    union {
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<LedgerVersion> &_xdr_case_values() {
      static const std::vector<LedgerVersion> _xdr_disc_vec {
        LedgerVersion::EMPTY_VERSION
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
        v_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
      }
      else
        v_ = which;
    }
    explicit _ext_t(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                        std::move(source));
    }
    ~_ext_t() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
    _ext_t &operator=(const _ext_t &source) {
      if (_xdr_field_number(v_)
          == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
      }
      v_ = source.v_;
      return *this;
    }
    _ext_t &operator=(_ext_t &&source) {
      if (_xdr_field_number(v_)
           == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                          std::move(source));
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                          std::move(source));
      }
      v_ = source.v_;
      return *this;
    }

    LedgerVersion v() const { return LedgerVersion(v_); }
    _ext_t &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::WithdrawalDetails::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::WithdrawalDetails::_ext_t;
  using case_type = ::stellar::WithdrawalDetails::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::WithdrawalDetails::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::WithdrawalDetails::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::WithdrawalDetails::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::WithdrawalDetails>
  : xdr_struct_base<field_ptr<::stellar::WithdrawalDetails,
                              decltype(::stellar::WithdrawalDetails::externalDetails),
                              &::stellar::WithdrawalDetails::externalDetails>,
                    field_ptr<::stellar::WithdrawalDetails,
                              decltype(::stellar::WithdrawalDetails::ext),
                              &::stellar::WithdrawalDetails::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::WithdrawalDetails &obj) {
    archive(ar, obj.externalDetails, "externalDetails");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::WithdrawalDetails &obj) {
    archive(ar, obj.externalDetails, "externalDetails");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct AMLAlertDetails {
  struct _ext_t {
    using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
  private:
    _xdr_case_type v_;
    union {
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<LedgerVersion> &_xdr_case_values() {
      static const std::vector<LedgerVersion> _xdr_disc_vec {
        LedgerVersion::EMPTY_VERSION
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
        v_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
      }
      else
        v_ = which;
    }
    explicit _ext_t(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                        std::move(source));
    }
    ~_ext_t() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
    _ext_t &operator=(const _ext_t &source) {
      if (_xdr_field_number(v_)
          == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
      }
      v_ = source.v_;
      return *this;
    }
    _ext_t &operator=(_ext_t &&source) {
      if (_xdr_field_number(v_)
           == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                          std::move(source));
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                          std::move(source));
      }
      v_ = source.v_;
      return *this;
    }

    LedgerVersion v() const { return LedgerVersion(v_); }
    _ext_t &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::AMLAlertDetails::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::AMLAlertDetails::_ext_t;
  using case_type = ::stellar::AMLAlertDetails::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::AMLAlertDetails::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::AMLAlertDetails::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::AMLAlertDetails::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::AMLAlertDetails>
  : xdr_struct_base<field_ptr<::stellar::AMLAlertDetails,
                              decltype(::stellar::AMLAlertDetails::comment),
                              &::stellar::AMLAlertDetails::comment>,
                    field_ptr<::stellar::AMLAlertDetails,
                              decltype(::stellar::AMLAlertDetails::ext),
                              &::stellar::AMLAlertDetails::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::AMLAlertDetails &obj) {
    archive(ar, obj.comment, "comment");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::AMLAlertDetails &obj) {
    archive(ar, obj.comment, "comment");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ContractDetails {
  struct _ext_t {
    using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
  private:
    _xdr_case_type v_;
    union {
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<LedgerVersion> &_xdr_case_values() {
      static const std::vector<LedgerVersion> _xdr_disc_vec {
        LedgerVersion::EMPTY_VERSION
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
        v_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
      }
      else
        v_ = which;
    }
    explicit _ext_t(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                        std::move(source));
    }
    ~_ext_t() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
    _ext_t &operator=(const _ext_t &source) {
      if (_xdr_field_number(v_)
          == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
      }
      v_ = source.v_;
      return *this;
    }
    _ext_t &operator=(_ext_t &&source) {
      if (_xdr_field_number(v_)
           == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                          std::move(source));
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                          std::move(source));
      }
      v_ = source.v_;
      return *this;
    }

    LedgerVersion v() const { return LedgerVersion(v_); }
    _ext_t &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ContractDetails::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ContractDetails::_ext_t;
  using case_type = ::stellar::ContractDetails::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ContractDetails::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ContractDetails::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ContractDetails::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ContractDetails>
  : xdr_struct_base<field_ptr<::stellar::ContractDetails,
                              decltype(::stellar::ContractDetails::details),
                              &::stellar::ContractDetails::details>,
                    field_ptr<::stellar::ContractDetails,
                              decltype(::stellar::ContractDetails::ext),
                              &::stellar::ContractDetails::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ContractDetails &obj) {
    archive(ar, obj.details, "details");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ContractDetails &obj) {
    archive(ar, obj.details, "details");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct BillPayDetails {
  struct _ext_t {
    using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
  private:
    _xdr_case_type v_;
    union {
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<LedgerVersion> &_xdr_case_values() {
      static const std::vector<LedgerVersion> _xdr_disc_vec {
        LedgerVersion::EMPTY_VERSION
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
        v_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
      }
      else
        v_ = which;
    }
    explicit _ext_t(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                        std::move(source));
    }
    ~_ext_t() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
    _ext_t &operator=(const _ext_t &source) {
      if (_xdr_field_number(v_)
          == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
      }
      v_ = source.v_;
      return *this;
    }
    _ext_t &operator=(_ext_t &&source) {
      if (_xdr_field_number(v_)
           == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                          std::move(source));
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                          std::move(source));
      }
      v_ = source.v_;
      return *this;
    }

    LedgerVersion v() const { return LedgerVersion(v_); }
    _ext_t &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::BillPayDetails::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::BillPayDetails::_ext_t;
  using case_type = ::stellar::BillPayDetails::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::BillPayDetails::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::BillPayDetails::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::BillPayDetails::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::BillPayDetails>
  : xdr_struct_base<field_ptr<::stellar::BillPayDetails,
                              decltype(::stellar::BillPayDetails::paymentDetails),
                              &::stellar::BillPayDetails::paymentDetails>,
                    field_ptr<::stellar::BillPayDetails,
                              decltype(::stellar::BillPayDetails::ext),
                              &::stellar::BillPayDetails::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::BillPayDetails &obj) {
    archive(ar, obj.paymentDetails, "paymentDetails");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::BillPayDetails &obj) {
    archive(ar, obj.paymentDetails, "paymentDetails");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ReviewDetails {
  struct _ext_t {
    using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
  private:
    _xdr_case_type v_;
    union {
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<LedgerVersion> &_xdr_case_values() {
      static const std::vector<LedgerVersion> _xdr_disc_vec {
        LedgerVersion::EMPTY_VERSION
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
        v_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
      }
      else
        v_ = which;
    }
    explicit _ext_t(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                        std::move(source));
    }
    ~_ext_t() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
    _ext_t &operator=(const _ext_t &source) {
      if (_xdr_field_number(v_)
          == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
      }
      v_ = source.v_;
      return *this;
    }
    _ext_t &operator=(_ext_t &&source) {
      if (_xdr_field_number(v_)
           == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                          std::move(source));
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                          std::move(source));
      }
      v_ = source.v_;
      return *this;
    }

    LedgerVersion v() const { return LedgerVersion(v_); }
    _ext_t &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ReviewDetails::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ReviewDetails::_ext_t;
  using case_type = ::stellar::ReviewDetails::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ReviewDetails::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ReviewDetails::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ReviewDetails::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ReviewDetails>
  : xdr_struct_base<field_ptr<::stellar::ReviewDetails,
                              decltype(::stellar::ReviewDetails::tasksToAdd),
                              &::stellar::ReviewDetails::tasksToAdd>,
                    field_ptr<::stellar::ReviewDetails,
                              decltype(::stellar::ReviewDetails::tasksToRemove),
                              &::stellar::ReviewDetails::tasksToRemove>,
                    field_ptr<::stellar::ReviewDetails,
                              decltype(::stellar::ReviewDetails::externalDetails),
                              &::stellar::ReviewDetails::externalDetails>,
                    field_ptr<::stellar::ReviewDetails,
                              decltype(::stellar::ReviewDetails::ext),
                              &::stellar::ReviewDetails::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ReviewDetails &obj) {
    archive(ar, obj.tasksToAdd, "tasksToAdd");
    archive(ar, obj.tasksToRemove, "tasksToRemove");
    archive(ar, obj.externalDetails, "externalDetails");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ReviewDetails &obj) {
    archive(ar, obj.tasksToAdd, "tasksToAdd");
    archive(ar, obj.tasksToRemove, "tasksToRemove");
    archive(ar, obj.externalDetails, "externalDetails");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SaleExtended {
  struct _ext_t {
    using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
  private:
    _xdr_case_type v_;
    union {
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<LedgerVersion> &_xdr_case_values() {
      static const std::vector<LedgerVersion> _xdr_disc_vec {
        LedgerVersion::EMPTY_VERSION
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
        v_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
      }
      else
        v_ = which;
    }
    explicit _ext_t(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                        std::move(source));
    }
    ~_ext_t() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
    _ext_t &operator=(const _ext_t &source) {
      if (_xdr_field_number(v_)
          == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
      }
      v_ = source.v_;
      return *this;
    }
    _ext_t &operator=(_ext_t &&source) {
      if (_xdr_field_number(v_)
           == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                          std::move(source));
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                          std::move(source));
      }
      v_ = source.v_;
      return *this;
    }

    LedgerVersion v() const { return LedgerVersion(v_); }
    _ext_t &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SaleExtended::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::SaleExtended::_ext_t;
  using case_type = ::stellar::SaleExtended::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::SaleExtended::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SaleExtended::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SaleExtended::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::SaleExtended>
  : xdr_struct_base<field_ptr<::stellar::SaleExtended,
                              decltype(::stellar::SaleExtended::saleID),
                              &::stellar::SaleExtended::saleID>,
                    field_ptr<::stellar::SaleExtended,
                              decltype(::stellar::SaleExtended::ext),
                              &::stellar::SaleExtended::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SaleExtended &obj) {
    archive(ar, obj.saleID, "saleID");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SaleExtended &obj) {
    archive(ar, obj.saleID, "saleID");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ASwapBidExtended {
  struct _ext_t {
    using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
  private:
    _xdr_case_type v_;
    union {
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<LedgerVersion> &_xdr_case_values() {
      static const std::vector<LedgerVersion> _xdr_disc_vec {
        LedgerVersion::EMPTY_VERSION
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
        v_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
      }
      else
        v_ = which;
    }
    explicit _ext_t(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                        std::move(source));
    }
    ~_ext_t() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
    _ext_t &operator=(const _ext_t &source) {
      if (_xdr_field_number(v_)
          == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
      }
      v_ = source.v_;
      return *this;
    }
    _ext_t &operator=(_ext_t &&source) {
      if (_xdr_field_number(v_)
           == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                          std::move(source));
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                          std::move(source));
      }
      v_ = source.v_;
      return *this;
    }

    LedgerVersion v() const { return LedgerVersion(v_); }
    _ext_t &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

  };

  uint64 bidID{};
  _ext_t ext{};

  ASwapBidExtended() = default;
  template<typename _bidID_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _bidID_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ASwapBidExtended(_bidID_T &&_bidID,
                            _ext_T &&_ext)
    : bidID(std::forward<_bidID_T>(_bidID)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ASwapBidExtended::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ASwapBidExtended::_ext_t;
  using case_type = ::stellar::ASwapBidExtended::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ASwapBidExtended::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ASwapBidExtended::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ASwapBidExtended::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ASwapBidExtended>
  : xdr_struct_base<field_ptr<::stellar::ASwapBidExtended,
                              decltype(::stellar::ASwapBidExtended::bidID),
                              &::stellar::ASwapBidExtended::bidID>,
                    field_ptr<::stellar::ASwapBidExtended,
                              decltype(::stellar::ASwapBidExtended::ext),
                              &::stellar::ASwapBidExtended::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ASwapBidExtended &obj) {
    archive(ar, obj.bidID, "bidID");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ASwapBidExtended &obj) {
    archive(ar, obj.bidID, "bidID");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ASwapExtended {
  struct _ext_t {
    using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
  private:
    _xdr_case_type v_;
    union {
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<LedgerVersion> &_xdr_case_values() {
      static const std::vector<LedgerVersion> _xdr_disc_vec {
        LedgerVersion::EMPTY_VERSION
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
        v_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
      }
      else
        v_ = which;
    }
    explicit _ext_t(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                        std::move(source));
    }
    ~_ext_t() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
    _ext_t &operator=(const _ext_t &source) {
      if (_xdr_field_number(v_)
          == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
      }
      v_ = source.v_;
      return *this;
    }
    _ext_t &operator=(_ext_t &&source) {
      if (_xdr_field_number(v_)
           == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                          std::move(source));
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                          std::move(source));
      }
      v_ = source.v_;
      return *this;
    }

    LedgerVersion v() const { return LedgerVersion(v_); }
    _ext_t &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

  };

  uint64 bidID{};
  AccountID bidOwnerID{};
  AccountID purchaserID{};
  AssetCode baseAsset{};
  AssetCode quoteAsset{};
  uint64 baseAmount{};
  uint64 quoteAmount{};
  uint64 price{};
  BalanceID bidOwnerBaseBalanceID{};
  BalanceID purchaserBaseBalanceID{};
  _ext_t ext{};

  ASwapExtended() = default;
  template<typename _bidID_T,
           typename _bidOwnerID_T,
           typename _purchaserID_T,
           typename _baseAsset_T,
           typename _quoteAsset_T,
           typename _baseAmount_T,
           typename _quoteAmount_T,
           typename _price_T,
           typename _bidOwnerBaseBalanceID_T,
           typename _purchaserBaseBalanceID_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _bidID_T>::value
                          && std::is_constructible<AccountID, _bidOwnerID_T>::value
                          && std::is_constructible<AccountID, _purchaserID_T>::value
                          && std::is_constructible<AssetCode, _baseAsset_T>::value
                          && std::is_constructible<AssetCode, _quoteAsset_T>::value
                          && std::is_constructible<uint64, _baseAmount_T>::value
                          && std::is_constructible<uint64, _quoteAmount_T>::value
                          && std::is_constructible<uint64, _price_T>::value
                          && std::is_constructible<BalanceID, _bidOwnerBaseBalanceID_T>::value
                          && std::is_constructible<BalanceID, _purchaserBaseBalanceID_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ASwapExtended(_bidID_T &&_bidID,
                         _bidOwnerID_T &&_bidOwnerID,
                         _purchaserID_T &&_purchaserID,
                         _baseAsset_T &&_baseAsset,
                         _quoteAsset_T &&_quoteAsset,
                         _baseAmount_T &&_baseAmount,
                         _quoteAmount_T &&_quoteAmount,
                         _price_T &&_price,
                         _bidOwnerBaseBalanceID_T &&_bidOwnerBaseBalanceID,
                         _purchaserBaseBalanceID_T &&_purchaserBaseBalanceID,
                         _ext_T &&_ext)
    : bidID(std::forward<_bidID_T>(_bidID)),
      bidOwnerID(std::forward<_bidOwnerID_T>(_bidOwnerID)),
      purchaserID(std::forward<_purchaserID_T>(_purchaserID)),
      baseAsset(std::forward<_baseAsset_T>(_baseAsset)),
      quoteAsset(std::forward<_quoteAsset_T>(_quoteAsset)),
      baseAmount(std::forward<_baseAmount_T>(_baseAmount)),
      quoteAmount(std::forward<_quoteAmount_T>(_quoteAmount)),
      price(std::forward<_price_T>(_price)),
      bidOwnerBaseBalanceID(std::forward<_bidOwnerBaseBalanceID_T>(_bidOwnerBaseBalanceID)),
      purchaserBaseBalanceID(std::forward<_purchaserBaseBalanceID_T>(_purchaserBaseBalanceID)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ASwapExtended::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ASwapExtended::_ext_t;
  using case_type = ::stellar::ASwapExtended::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ASwapExtended::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ASwapExtended::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ASwapExtended::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ASwapExtended>
  : xdr_struct_base<field_ptr<::stellar::ASwapExtended,
                              decltype(::stellar::ASwapExtended::bidID),
                              &::stellar::ASwapExtended::bidID>,
                    field_ptr<::stellar::ASwapExtended,
                              decltype(::stellar::ASwapExtended::bidOwnerID),
                              &::stellar::ASwapExtended::bidOwnerID>,
                    field_ptr<::stellar::ASwapExtended,
                              decltype(::stellar::ASwapExtended::purchaserID),
                              &::stellar::ASwapExtended::purchaserID>,
                    field_ptr<::stellar::ASwapExtended,
                              decltype(::stellar::ASwapExtended::baseAsset),
                              &::stellar::ASwapExtended::baseAsset>,
                    field_ptr<::stellar::ASwapExtended,
                              decltype(::stellar::ASwapExtended::quoteAsset),
                              &::stellar::ASwapExtended::quoteAsset>,
                    field_ptr<::stellar::ASwapExtended,
                              decltype(::stellar::ASwapExtended::baseAmount),
                              &::stellar::ASwapExtended::baseAmount>,
                    field_ptr<::stellar::ASwapExtended,
                              decltype(::stellar::ASwapExtended::quoteAmount),
                              &::stellar::ASwapExtended::quoteAmount>,
                    field_ptr<::stellar::ASwapExtended,
                              decltype(::stellar::ASwapExtended::price),
                              &::stellar::ASwapExtended::price>,
                    field_ptr<::stellar::ASwapExtended,
                              decltype(::stellar::ASwapExtended::bidOwnerBaseBalanceID),
                              &::stellar::ASwapExtended::bidOwnerBaseBalanceID>,
                    field_ptr<::stellar::ASwapExtended,
                              decltype(::stellar::ASwapExtended::purchaserBaseBalanceID),
                              &::stellar::ASwapExtended::purchaserBaseBalanceID>,
                    field_ptr<::stellar::ASwapExtended,
                              decltype(::stellar::ASwapExtended::ext),
                              &::stellar::ASwapExtended::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ASwapExtended &obj) {
    archive(ar, obj.bidID, "bidID");
    archive(ar, obj.bidOwnerID, "bidOwnerID");
    archive(ar, obj.purchaserID, "purchaserID");
    archive(ar, obj.baseAsset, "baseAsset");
    archive(ar, obj.quoteAsset, "quoteAsset");
    archive(ar, obj.baseAmount, "baseAmount");
    archive(ar, obj.quoteAmount, "quoteAmount");
    archive(ar, obj.price, "price");
    archive(ar, obj.bidOwnerBaseBalanceID, "bidOwnerBaseBalanceID");
    archive(ar, obj.purchaserBaseBalanceID, "purchaserBaseBalanceID");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ASwapExtended &obj) {
    archive(ar, obj.bidID, "bidID");
    archive(ar, obj.bidOwnerID, "bidOwnerID");
    archive(ar, obj.purchaserID, "purchaserID");
    archive(ar, obj.baseAsset, "baseAsset");
    archive(ar, obj.quoteAsset, "quoteAsset");
    archive(ar, obj.baseAmount, "baseAmount");
    archive(ar, obj.quoteAmount, "quoteAmount");
    archive(ar, obj.price, "price");
    archive(ar, obj.bidOwnerBaseBalanceID, "bidOwnerBaseBalanceID");
    archive(ar, obj.purchaserBaseBalanceID, "purchaserBaseBalanceID");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ExtendedResult {
  struct _typeExt_t {
    using _xdr_case_type = xdr::xdr_traits<ReviewableRequestType>::case_type;
  private:
    _xdr_case_type requestType_;
    union {
      SaleExtended saleExtended_;
      ASwapBidExtended aSwapBidExtended_;
      ASwapExtended aSwapExtended_;
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<ReviewableRequestType> &_xdr_case_values() {
      static const std::vector<ReviewableRequestType> _xdr_disc_vec {
        ReviewableRequestType::CREATE_SALE,
        ReviewableRequestType::NONE,
        ReviewableRequestType::CREATE_ATOMIC_SWAP_BID,
        ReviewableRequestType::CREATE_ATOMIC_SWAP
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)ReviewableRequestType::CREATE_SALE ? 1
        : which == (int32_t)ReviewableRequestType::NONE ? 0
        : which == (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID ? 2
        : which == (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP ? 3
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
        _f(&_typeExt_t::aSwapBidExtended_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP:
        _f(&_typeExt_t::aSwapExtended_, std::forward<_A>(_a)...);
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
        requestType_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, requestType_, *this);
      }
      else
        requestType_ = which;
    }
    explicit _typeExt_t(ReviewableRequestType which = ReviewableRequestType{}) : requestType_((int32_t)which) {
      _xdr_with_mem_ptr(xdr::field_constructor, requestType_, *this);
    }
    _typeExt_t(const _typeExt_t &source) : requestType_(source.requestType_) {
      _xdr_with_mem_ptr(xdr::field_constructor, requestType_, *this, source);
    }
    _typeExt_t(_typeExt_t &&source) : requestType_(source.requestType_) {
      _xdr_with_mem_ptr(xdr::field_constructor, requestType_, *this,
                        std::move(source));
    }
    ~_typeExt_t() { _xdr_with_mem_ptr(xdr::field_destructor, requestType_, *this); }
    _typeExt_t &operator=(const _typeExt_t &source) {
      if (_xdr_field_number(requestType_)
          == _xdr_field_number(source.requestType_))
        _xdr_with_mem_ptr(xdr::field_assigner, requestType_, *this, source);
      else {
        this->~_typeExt_t();
        requestType_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.requestType_, *this, source);
      }
      requestType_ = source.requestType_;
      return *this;
    }
    _typeExt_t &operator=(_typeExt_t &&source) {
      if (_xdr_field_number(requestType_)
           == _xdr_field_number(source.requestType_))
        _xdr_with_mem_ptr(xdr::field_assigner, requestType_, *this,
                          std::move(source));
      else {
        this->~_typeExt_t();
        requestType_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.requestType_, *this,
                          std::move(source));
      }
      requestType_ = source.requestType_;
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
    ASwapBidExtended &aSwapBidExtended() {
      if (_xdr_field_number(requestType_) == 2)
        return aSwapBidExtended_;
      throw xdr::xdr_wrong_union("_typeExt_t: aSwapBidExtended accessed when not selected");
    }
    const ASwapBidExtended &aSwapBidExtended() const {
      if (_xdr_field_number(requestType_) == 2)
        return aSwapBidExtended_;
      throw xdr::xdr_wrong_union("_typeExt_t: aSwapBidExtended accessed when not selected");
    }
    ASwapExtended &aSwapExtended() {
      if (_xdr_field_number(requestType_) == 3)
        return aSwapExtended_;
      throw xdr::xdr_wrong_union("_typeExt_t: aSwapExtended accessed when not selected");
    }
    const ASwapExtended &aSwapExtended() const {
      if (_xdr_field_number(requestType_) == 3)
        return aSwapExtended_;
      throw xdr::xdr_wrong_union("_typeExt_t: aSwapExtended accessed when not selected");
    }
  };
  struct _ext_t {
    using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
  private:
    _xdr_case_type v_;
    union {
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<LedgerVersion> &_xdr_case_values() {
      static const std::vector<LedgerVersion> _xdr_disc_vec {
        LedgerVersion::EMPTY_VERSION
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
        v_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
      }
      else
        v_ = which;
    }
    explicit _ext_t(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                        std::move(source));
    }
    ~_ext_t() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
    _ext_t &operator=(const _ext_t &source) {
      if (_xdr_field_number(v_)
          == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
      }
      v_ = source.v_;
      return *this;
    }
    _ext_t &operator=(_ext_t &&source) {
      if (_xdr_field_number(v_)
           == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                          std::move(source));
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                          std::move(source));
      }
      v_ = source.v_;
      return *this;
    }

    LedgerVersion v() const { return LedgerVersion(v_); }
    _ext_t &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ExtendedResult::_typeExt_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ExtendedResult::_typeExt_t;
  using case_type = ::stellar::ExtendedResult::_typeExt_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().requestType());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "saleExtended";
    case 2:
      return "aSwapBidExtended";
    case 3:
      return "aSwapExtended";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ExtendedResult::_typeExt_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of requestType in _typeExt_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ExtendedResult::_typeExt_t &obj) {
    xdr::archive(ar, obj.requestType(), "requestType");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.requestType(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of requestType in _typeExt_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ExtendedResult::_typeExt_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "requestType");
    obj.requestType(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.requestType(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ExtendedResult::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ExtendedResult::_ext_t;
  using case_type = ::stellar::ExtendedResult::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ExtendedResult::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ExtendedResult::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ExtendedResult::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ExtendedResult>
  : xdr_struct_base<field_ptr<::stellar::ExtendedResult,
                              decltype(::stellar::ExtendedResult::fulfilled),
                              &::stellar::ExtendedResult::fulfilled>,
                    field_ptr<::stellar::ExtendedResult,
                              decltype(::stellar::ExtendedResult::typeExt),
                              &::stellar::ExtendedResult::typeExt>,
                    field_ptr<::stellar::ExtendedResult,
                              decltype(::stellar::ExtendedResult::ext),
                              &::stellar::ExtendedResult::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ExtendedResult &obj) {
    archive(ar, obj.fulfilled, "fulfilled");
    archive(ar, obj.typeExt, "typeExt");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ExtendedResult &obj) {
    archive(ar, obj.fulfilled, "fulfilled");
    archive(ar, obj.typeExt, "typeExt");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ReviewRequestOp {
  struct _requestDetails_t {
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
    static Constexpr const bool _xdr_has_default_case = true;
    static const std::vector<ReviewableRequestType> &_xdr_case_values() {
      static const std::vector<ReviewableRequestType> _xdr_disc_vec {};
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
        requestType_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, requestType_, *this);
      }
      else
        requestType_ = which;
    }
    explicit _requestDetails_t(ReviewableRequestType which = ReviewableRequestType{}) : requestType_((int32_t)which) {
      _xdr_with_mem_ptr(xdr::field_constructor, requestType_, *this);
    }
    _requestDetails_t(const _requestDetails_t &source) : requestType_(source.requestType_) {
      _xdr_with_mem_ptr(xdr::field_constructor, requestType_, *this, source);
    }
    _requestDetails_t(_requestDetails_t &&source) : requestType_(source.requestType_) {
      _xdr_with_mem_ptr(xdr::field_constructor, requestType_, *this,
                        std::move(source));
    }
    ~_requestDetails_t() { _xdr_with_mem_ptr(xdr::field_destructor, requestType_, *this); }
    _requestDetails_t &operator=(const _requestDetails_t &source) {
      if (_xdr_field_number(requestType_)
          == _xdr_field_number(source.requestType_))
        _xdr_with_mem_ptr(xdr::field_assigner, requestType_, *this, source);
      else {
        this->~_requestDetails_t();
        requestType_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.requestType_, *this, source);
      }
      requestType_ = source.requestType_;
      return *this;
    }
    _requestDetails_t &operator=(_requestDetails_t &&source) {
      if (_xdr_field_number(requestType_)
           == _xdr_field_number(source.requestType_))
        _xdr_with_mem_ptr(xdr::field_assigner, requestType_, *this,
                          std::move(source));
      else {
        this->~_requestDetails_t();
        requestType_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.requestType_, *this,
                          std::move(source));
      }
      requestType_ = source.requestType_;
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
    }
  };
  struct _ext_t {
    using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
  private:
    _xdr_case_type v_;
    union {
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<LedgerVersion> &_xdr_case_values() {
      static const std::vector<LedgerVersion> _xdr_disc_vec {
        LedgerVersion::EMPTY_VERSION
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
        v_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
      }
      else
        v_ = which;
    }
    explicit _ext_t(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                        std::move(source));
    }
    ~_ext_t() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
    _ext_t &operator=(const _ext_t &source) {
      if (_xdr_field_number(v_)
          == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
      }
      v_ = source.v_;
      return *this;
    }
    _ext_t &operator=(_ext_t &&source) {
      if (_xdr_field_number(v_)
           == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                          std::move(source));
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                          std::move(source));
      }
      v_ = source.v_;
      return *this;
    }

    LedgerVersion v() const { return LedgerVersion(v_); }
    _ext_t &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ReviewRequestOp::_requestDetails_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ReviewRequestOp::_requestDetails_t;
  using case_type = ::stellar::ReviewRequestOp::_requestDetails_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().requestType());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "withdrawal";
    case 2:
      return "limitsUpdate";
    case 3:
      return "amlAlertDetails";
    case 4:
      return "billPay";
    case 5:
      return "contract";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ReviewRequestOp::_requestDetails_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of requestType in _requestDetails_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ReviewRequestOp::_requestDetails_t &obj) {
    xdr::archive(ar, obj.requestType(), "requestType");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.requestType(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of requestType in _requestDetails_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ReviewRequestOp::_requestDetails_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "requestType");
    obj.requestType(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.requestType(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ReviewRequestOp::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ReviewRequestOp::_ext_t;
  using case_type = ::stellar::ReviewRequestOp::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ReviewRequestOp::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ReviewRequestOp::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ReviewRequestOp::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ReviewRequestOp>
  : xdr_struct_base<field_ptr<::stellar::ReviewRequestOp,
                              decltype(::stellar::ReviewRequestOp::requestID),
                              &::stellar::ReviewRequestOp::requestID>,
                    field_ptr<::stellar::ReviewRequestOp,
                              decltype(::stellar::ReviewRequestOp::requestHash),
                              &::stellar::ReviewRequestOp::requestHash>,
                    field_ptr<::stellar::ReviewRequestOp,
                              decltype(::stellar::ReviewRequestOp::requestDetails),
                              &::stellar::ReviewRequestOp::requestDetails>,
                    field_ptr<::stellar::ReviewRequestOp,
                              decltype(::stellar::ReviewRequestOp::action),
                              &::stellar::ReviewRequestOp::action>,
                    field_ptr<::stellar::ReviewRequestOp,
                              decltype(::stellar::ReviewRequestOp::reason),
                              &::stellar::ReviewRequestOp::reason>,
                    field_ptr<::stellar::ReviewRequestOp,
                              decltype(::stellar::ReviewRequestOp::reviewDetails),
                              &::stellar::ReviewRequestOp::reviewDetails>,
                    field_ptr<::stellar::ReviewRequestOp,
                              decltype(::stellar::ReviewRequestOp::ext),
                              &::stellar::ReviewRequestOp::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ReviewRequestOp &obj) {
    archive(ar, obj.requestID, "requestID");
    archive(ar, obj.requestHash, "requestHash");
    archive(ar, obj.requestDetails, "requestDetails");
    archive(ar, obj.action, "action");
    archive(ar, obj.reason, "reason");
    archive(ar, obj.reviewDetails, "reviewDetails");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ReviewRequestOp &obj) {
    archive(ar, obj.requestID, "requestID");
    archive(ar, obj.requestHash, "requestHash");
    archive(ar, obj.requestDetails, "requestDetails");
    archive(ar, obj.action, "action");
    archive(ar, obj.reason, "reason");
    archive(ar, obj.reviewDetails, "reviewDetails");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

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
  QUOTE_ASSET_NOT_FOUND = -550,
  NON_ZERO_TASKS_TO_REMOVE_NOT_ALLOWED = -600,
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
  ASSETS_ARE_EQUAL = -1502,
  ASWAP_BID_UNDERFUNDED = -1503,
  ASWAP_PURCHASER_FULL_LINE = -1504,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ReviewRequestResultCode>
  : xdr_integral_base<::stellar::ReviewRequestResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
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
    case ::stellar::ReviewRequestResultCode::QUOTE_ASSET_NOT_FOUND:
      return "QUOTE_ASSET_NOT_FOUND";
    case ::stellar::ReviewRequestResultCode::NON_ZERO_TASKS_TO_REMOVE_NOT_ALLOWED:
      return "NON_ZERO_TASKS_TO_REMOVE_NOT_ALLOWED";
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
    case ::stellar::ReviewRequestResultCode::ASSETS_ARE_EQUAL:
      return "ASSETS_ARE_EQUAL";
    case ::stellar::ReviewRequestResultCode::ASWAP_BID_UNDERFUNDED:
      return "ASWAP_BID_UNDERFUNDED";
    case ::stellar::ReviewRequestResultCode::ASWAP_PURCHASER_FULL_LINE:
      return "ASWAP_PURCHASER_FULL_LINE";
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
      (int32_t)::stellar::ReviewRequestResultCode::QUOTE_ASSET_NOT_FOUND,
      (int32_t)::stellar::ReviewRequestResultCode::NON_ZERO_TASKS_TO_REMOVE_NOT_ALLOWED,
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
      (int32_t)::stellar::ReviewRequestResultCode::ASSETS_ARE_EQUAL,
      (int32_t)::stellar::ReviewRequestResultCode::ASWAP_BID_UNDERFUNDED,
      (int32_t)::stellar::ReviewRequestResultCode::ASWAP_PURCHASER_FULL_LINE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ReviewRequestResult {
  using _xdr_case_type = xdr::xdr_traits<ReviewRequestResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    ExtendedResult success_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = true;
  static const std::vector<ReviewRequestResultCode> &_xdr_case_values() {
    static const std::vector<ReviewRequestResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)ReviewRequestResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)ReviewRequestResultCode::SUCCESS:
      _f(&ReviewRequestResult::success_, std::forward<_A>(_a)...);
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
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit ReviewRequestResult(ReviewRequestResultCode which = ReviewRequestResultCode{}) : code_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  ReviewRequestResult(const ReviewRequestResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  ReviewRequestResult(ReviewRequestResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~ReviewRequestResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  ReviewRequestResult &operator=(const ReviewRequestResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~ReviewRequestResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  ReviewRequestResult &operator=(ReviewRequestResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~ReviewRequestResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ReviewRequestResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ReviewRequestResult;
  using case_type = ::stellar::ReviewRequestResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "success";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ReviewRequestResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in ReviewRequestResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ReviewRequestResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in ReviewRequestResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ReviewRequestResult &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.code(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
} namespace stellar {

}

#endif // !__XDR_STELLAR_OPERATION_REVIEW_REQUEST_H_INCLUDED__
