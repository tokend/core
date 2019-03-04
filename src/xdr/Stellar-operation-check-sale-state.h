// -*- C++ -*-
// Automatically generated from Stellar-operation-check-sale-state.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_OPERATION_CHECK_SALE_STATE_H_INCLUDED__
#define __XDR_STELLAR_OPERATION_CHECK_SALE_STATE_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-ledger-entries.h"
#include "xdr/Stellar-operation-manage-offer.h"

namespace stellar {

struct CheckSaleStateOp {
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CheckSaleStateOp::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CheckSaleStateOp::_ext_t;
  using case_type = ::stellar::CheckSaleStateOp::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::CheckSaleStateOp::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CheckSaleStateOp::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CheckSaleStateOp::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::CheckSaleStateOp>
  : xdr_struct_base<field_ptr<::stellar::CheckSaleStateOp,
                              decltype(::stellar::CheckSaleStateOp::saleID),
                              &::stellar::CheckSaleStateOp::saleID>,
                    field_ptr<::stellar::CheckSaleStateOp,
                              decltype(::stellar::CheckSaleStateOp::ext),
                              &::stellar::CheckSaleStateOp::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CheckSaleStateOp &obj) {
    archive(ar, obj.saleID, "saleID");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CheckSaleStateOp &obj) {
    archive(ar, obj.saleID, "saleID");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum class CheckSaleStateResultCode : std::int32_t {
  SUCCESS = 0,
  NOT_FOUND = -1,
  NOT_READY = -2,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CheckSaleStateResultCode>
  : xdr_integral_base<::stellar::CheckSaleStateResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
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
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
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

struct SaleCanceled {
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

  _ext_t ext{};

  SaleCanceled() = default;
  template<typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit SaleCanceled(_ext_T &&_ext)
    : ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SaleCanceled::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::SaleCanceled::_ext_t;
  using case_type = ::stellar::SaleCanceled::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::SaleCanceled::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SaleCanceled::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SaleCanceled::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::SaleCanceled>
  : xdr_struct_base<field_ptr<::stellar::SaleCanceled,
                              decltype(::stellar::SaleCanceled::ext),
                              &::stellar::SaleCanceled::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SaleCanceled &obj) {
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SaleCanceled &obj) {
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SaleUpdated {
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

  _ext_t ext{};

  SaleUpdated() = default;
  template<typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit SaleUpdated(_ext_T &&_ext)
    : ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SaleUpdated::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::SaleUpdated::_ext_t;
  using case_type = ::stellar::SaleUpdated::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::SaleUpdated::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SaleUpdated::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SaleUpdated::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::SaleUpdated>
  : xdr_struct_base<field_ptr<::stellar::SaleUpdated,
                              decltype(::stellar::SaleUpdated::ext),
                              &::stellar::SaleUpdated::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SaleUpdated &obj) {
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SaleUpdated &obj) {
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct CheckSubSaleClosedResult {
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CheckSubSaleClosedResult::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CheckSubSaleClosedResult::_ext_t;
  using case_type = ::stellar::CheckSubSaleClosedResult::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::CheckSubSaleClosedResult::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CheckSubSaleClosedResult::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CheckSubSaleClosedResult::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::CheckSubSaleClosedResult>
  : xdr_struct_base<field_ptr<::stellar::CheckSubSaleClosedResult,
                              decltype(::stellar::CheckSubSaleClosedResult::saleBaseBalance),
                              &::stellar::CheckSubSaleClosedResult::saleBaseBalance>,
                    field_ptr<::stellar::CheckSubSaleClosedResult,
                              decltype(::stellar::CheckSubSaleClosedResult::saleQuoteBalance),
                              &::stellar::CheckSubSaleClosedResult::saleQuoteBalance>,
                    field_ptr<::stellar::CheckSubSaleClosedResult,
                              decltype(::stellar::CheckSubSaleClosedResult::saleDetails),
                              &::stellar::CheckSubSaleClosedResult::saleDetails>,
                    field_ptr<::stellar::CheckSubSaleClosedResult,
                              decltype(::stellar::CheckSubSaleClosedResult::ext),
                              &::stellar::CheckSubSaleClosedResult::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CheckSubSaleClosedResult &obj) {
    archive(ar, obj.saleBaseBalance, "saleBaseBalance");
    archive(ar, obj.saleQuoteBalance, "saleQuoteBalance");
    archive(ar, obj.saleDetails, "saleDetails");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CheckSubSaleClosedResult &obj) {
    archive(ar, obj.saleBaseBalance, "saleBaseBalance");
    archive(ar, obj.saleQuoteBalance, "saleQuoteBalance");
    archive(ar, obj.saleDetails, "saleDetails");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct CheckSaleClosedResult {
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CheckSaleClosedResult::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CheckSaleClosedResult::_ext_t;
  using case_type = ::stellar::CheckSaleClosedResult::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::CheckSaleClosedResult::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CheckSaleClosedResult::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CheckSaleClosedResult::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::CheckSaleClosedResult>
  : xdr_struct_base<field_ptr<::stellar::CheckSaleClosedResult,
                              decltype(::stellar::CheckSaleClosedResult::saleOwner),
                              &::stellar::CheckSaleClosedResult::saleOwner>,
                    field_ptr<::stellar::CheckSaleClosedResult,
                              decltype(::stellar::CheckSaleClosedResult::results),
                              &::stellar::CheckSaleClosedResult::results>,
                    field_ptr<::stellar::CheckSaleClosedResult,
                              decltype(::stellar::CheckSaleClosedResult::ext),
                              &::stellar::CheckSaleClosedResult::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CheckSaleClosedResult &obj) {
    archive(ar, obj.saleOwner, "saleOwner");
    archive(ar, obj.results, "results");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CheckSaleClosedResult &obj) {
    archive(ar, obj.saleOwner, "saleOwner");
    archive(ar, obj.results, "results");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct CheckSaleStateSuccess {
  struct _effect_t {
    using _xdr_case_type = xdr::xdr_traits<CheckSaleStateEffect>::case_type;
  private:
    _xdr_case_type effect_;
    union {
      SaleCanceled saleCanceled_;
      CheckSaleClosedResult saleClosed_;
      SaleUpdated saleUpdated_;
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<CheckSaleStateEffect> &_xdr_case_values() {
      static const std::vector<CheckSaleStateEffect> _xdr_disc_vec {
        CheckSaleStateEffect::CANCELED,
        CheckSaleStateEffect::CLOSED,
        CheckSaleStateEffect::UPDATED
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
        effect_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, effect_, *this);
      }
      else
        effect_ = which;
    }
    explicit _effect_t(CheckSaleStateEffect which = CheckSaleStateEffect{}) : effect_((int32_t)which) {
      _xdr_with_mem_ptr(xdr::field_constructor, effect_, *this);
    }
    _effect_t(const _effect_t &source) : effect_(source.effect_) {
      _xdr_with_mem_ptr(xdr::field_constructor, effect_, *this, source);
    }
    _effect_t(_effect_t &&source) : effect_(source.effect_) {
      _xdr_with_mem_ptr(xdr::field_constructor, effect_, *this,
                        std::move(source));
    }
    ~_effect_t() { _xdr_with_mem_ptr(xdr::field_destructor, effect_, *this); }
    _effect_t &operator=(const _effect_t &source) {
      if (_xdr_field_number(effect_)
          == _xdr_field_number(source.effect_))
        _xdr_with_mem_ptr(xdr::field_assigner, effect_, *this, source);
      else {
        this->~_effect_t();
        effect_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.effect_, *this, source);
      }
      effect_ = source.effect_;
      return *this;
    }
    _effect_t &operator=(_effect_t &&source) {
      if (_xdr_field_number(effect_)
           == _xdr_field_number(source.effect_))
        _xdr_with_mem_ptr(xdr::field_assigner, effect_, *this,
                          std::move(source));
      else {
        this->~_effect_t();
        effect_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.effect_, *this,
                          std::move(source));
      }
      effect_ = source.effect_;
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CheckSaleStateSuccess::_effect_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CheckSaleStateSuccess::_effect_t;
  using case_type = ::stellar::CheckSaleStateSuccess::_effect_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().effect());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "saleCanceled";
    case 2:
      return "saleClosed";
    case 3:
      return "saleUpdated";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::CheckSaleStateSuccess::_effect_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of effect in _effect_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CheckSaleStateSuccess::_effect_t &obj) {
    xdr::archive(ar, obj.effect(), "effect");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.effect(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of effect in _effect_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CheckSaleStateSuccess::_effect_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "effect");
    obj.effect(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.effect(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::CheckSaleStateSuccess::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CheckSaleStateSuccess::_ext_t;
  using case_type = ::stellar::CheckSaleStateSuccess::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::CheckSaleStateSuccess::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CheckSaleStateSuccess::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CheckSaleStateSuccess::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::CheckSaleStateSuccess>
  : xdr_struct_base<field_ptr<::stellar::CheckSaleStateSuccess,
                              decltype(::stellar::CheckSaleStateSuccess::saleID),
                              &::stellar::CheckSaleStateSuccess::saleID>,
                    field_ptr<::stellar::CheckSaleStateSuccess,
                              decltype(::stellar::CheckSaleStateSuccess::effect),
                              &::stellar::CheckSaleStateSuccess::effect>,
                    field_ptr<::stellar::CheckSaleStateSuccess,
                              decltype(::stellar::CheckSaleStateSuccess::ext),
                              &::stellar::CheckSaleStateSuccess::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CheckSaleStateSuccess &obj) {
    archive(ar, obj.saleID, "saleID");
    archive(ar, obj.effect, "effect");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CheckSaleStateSuccess &obj) {
    archive(ar, obj.saleID, "saleID");
    archive(ar, obj.effect, "effect");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct CheckSaleStateResult {
  using _xdr_case_type = xdr::xdr_traits<CheckSaleStateResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    CheckSaleStateSuccess success_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = true;
  static const std::vector<CheckSaleStateResultCode> &_xdr_case_values() {
    static const std::vector<CheckSaleStateResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit CheckSaleStateResult(CheckSaleStateResultCode which = CheckSaleStateResultCode{}) : code_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  CheckSaleStateResult(const CheckSaleStateResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  CheckSaleStateResult(CheckSaleStateResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~CheckSaleStateResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  CheckSaleStateResult &operator=(const CheckSaleStateResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~CheckSaleStateResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  CheckSaleStateResult &operator=(CheckSaleStateResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~CheckSaleStateResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
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
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CheckSaleStateResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CheckSaleStateResult;
  using case_type = ::stellar::CheckSaleStateResult::_xdr_case_type;
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

  static std::size_t serial_size(const ::stellar::CheckSaleStateResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in CheckSaleStateResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CheckSaleStateResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in CheckSaleStateResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CheckSaleStateResult &obj) {
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

#endif // !__XDR_STELLAR_OPERATION_CHECK_SALE_STATE_H_INCLUDED__
