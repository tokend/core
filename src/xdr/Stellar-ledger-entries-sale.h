// -*- C++ -*-
// Automatically generated from Stellar-ledger-entries-sale.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_LEDGER_ENTRIES_SALE_H_INCLUDED__
#define __XDR_STELLAR_LEDGER_ENTRIES_SALE_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-types.h"

namespace stellar {

enum class SaleType : std::int32_t {
  BASIC_SALE = 1,
  CROWD_FUNDING = 2,
  FIXED_PRICE = 3,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SaleType>
  : xdr_integral_base<::stellar::SaleType, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::SaleType val) {
    switch (val) {
    case ::stellar::SaleType::BASIC_SALE:
      return "BASIC_SALE";
    case ::stellar::SaleType::CROWD_FUNDING:
      return "CROWD_FUNDING";
    case ::stellar::SaleType::FIXED_PRICE:
      return "FIXED_PRICE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::SaleType::BASIC_SALE,
      (int32_t)::stellar::SaleType::CROWD_FUNDING,
      (int32_t)::stellar::SaleType::FIXED_PRICE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct FixedPriceSale {
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

  FixedPriceSale() = default;
  template<typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit FixedPriceSale(_ext_T &&_ext)
    : ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::FixedPriceSale::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::FixedPriceSale::_ext_t;
  using case_type = ::stellar::FixedPriceSale::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::FixedPriceSale::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::FixedPriceSale::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::FixedPriceSale::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::FixedPriceSale>
  : xdr_struct_base<field_ptr<::stellar::FixedPriceSale,
                              decltype(::stellar::FixedPriceSale::ext),
                              &::stellar::FixedPriceSale::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::FixedPriceSale &obj) {
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::FixedPriceSale &obj) {
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct CrowdFundingSale {
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

  CrowdFundingSale() = default;
  template<typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CrowdFundingSale(_ext_T &&_ext)
    : ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CrowdFundingSale::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CrowdFundingSale::_ext_t;
  using case_type = ::stellar::CrowdFundingSale::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::CrowdFundingSale::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CrowdFundingSale::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CrowdFundingSale::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::CrowdFundingSale>
  : xdr_struct_base<field_ptr<::stellar::CrowdFundingSale,
                              decltype(::stellar::CrowdFundingSale::ext),
                              &::stellar::CrowdFundingSale::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CrowdFundingSale &obj) {
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CrowdFundingSale &obj) {
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct BasicSale {
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

  BasicSale() = default;
  template<typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit BasicSale(_ext_T &&_ext)
    : ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::BasicSale::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::BasicSale::_ext_t;
  using case_type = ::stellar::BasicSale::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::BasicSale::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::BasicSale::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::BasicSale::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::BasicSale>
  : xdr_struct_base<field_ptr<::stellar::BasicSale,
                              decltype(::stellar::BasicSale::ext),
                              &::stellar::BasicSale::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::BasicSale &obj) {
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::BasicSale &obj) {
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SaleTypeExt {
  using _xdr_case_type = xdr::xdr_traits<SaleType>::case_type;
private:
  _xdr_case_type saleType_;
  union {
    BasicSale basicSale_;
    CrowdFundingSale crowdFundingSale_;
    FixedPriceSale fixedPriceSale_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<SaleType> &_xdr_case_values() {
    static const std::vector<SaleType> _xdr_disc_vec {
      SaleType::BASIC_SALE,
      SaleType::CROWD_FUNDING,
      SaleType::FIXED_PRICE
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)SaleType::BASIC_SALE ? 1
      : which == (int32_t)SaleType::CROWD_FUNDING ? 2
      : which == (int32_t)SaleType::FIXED_PRICE ? 3
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)SaleType::BASIC_SALE:
      _f(&SaleTypeExt::basicSale_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)SaleType::CROWD_FUNDING:
      _f(&SaleTypeExt::crowdFundingSale_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)SaleType::FIXED_PRICE:
      _f(&SaleTypeExt::fixedPriceSale_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return saleType_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of saleType in SaleTypeExt");
    if (fnum != _xdr_field_number(saleType_)) {
      this->~SaleTypeExt();
      saleType_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, saleType_, *this);
    }
    else
      saleType_ = which;
  }
  explicit SaleTypeExt(SaleType which = SaleType{}) : saleType_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, saleType_, *this);
  }
  SaleTypeExt(const SaleTypeExt &source) : saleType_(source.saleType_) {
    _xdr_with_mem_ptr(xdr::field_constructor, saleType_, *this, source);
  }
  SaleTypeExt(SaleTypeExt &&source) : saleType_(source.saleType_) {
    _xdr_with_mem_ptr(xdr::field_constructor, saleType_, *this,
                      std::move(source));
  }
  ~SaleTypeExt() { _xdr_with_mem_ptr(xdr::field_destructor, saleType_, *this); }
  SaleTypeExt &operator=(const SaleTypeExt &source) {
    if (_xdr_field_number(saleType_)
        == _xdr_field_number(source.saleType_))
      _xdr_with_mem_ptr(xdr::field_assigner, saleType_, *this, source);
    else {
      this->~SaleTypeExt();
      saleType_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.saleType_, *this, source);
    }
    saleType_ = source.saleType_;
    return *this;
  }
  SaleTypeExt &operator=(SaleTypeExt &&source) {
    if (_xdr_field_number(saleType_)
         == _xdr_field_number(source.saleType_))
      _xdr_with_mem_ptr(xdr::field_assigner, saleType_, *this,
                        std::move(source));
    else {
      this->~SaleTypeExt();
      saleType_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.saleType_, *this,
                        std::move(source));
    }
    saleType_ = source.saleType_;
    return *this;
  }

  SaleType saleType() const { return SaleType(saleType_); }
  SaleTypeExt &saleType(SaleType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  BasicSale &basicSale() {
    if (_xdr_field_number(saleType_) == 1)
      return basicSale_;
    throw xdr::xdr_wrong_union("SaleTypeExt: basicSale accessed when not selected");
  }
  const BasicSale &basicSale() const {
    if (_xdr_field_number(saleType_) == 1)
      return basicSale_;
    throw xdr::xdr_wrong_union("SaleTypeExt: basicSale accessed when not selected");
  }
  CrowdFundingSale &crowdFundingSale() {
    if (_xdr_field_number(saleType_) == 2)
      return crowdFundingSale_;
    throw xdr::xdr_wrong_union("SaleTypeExt: crowdFundingSale accessed when not selected");
  }
  const CrowdFundingSale &crowdFundingSale() const {
    if (_xdr_field_number(saleType_) == 2)
      return crowdFundingSale_;
    throw xdr::xdr_wrong_union("SaleTypeExt: crowdFundingSale accessed when not selected");
  }
  FixedPriceSale &fixedPriceSale() {
    if (_xdr_field_number(saleType_) == 3)
      return fixedPriceSale_;
    throw xdr::xdr_wrong_union("SaleTypeExt: fixedPriceSale accessed when not selected");
  }
  const FixedPriceSale &fixedPriceSale() const {
    if (_xdr_field_number(saleType_) == 3)
      return fixedPriceSale_;
    throw xdr::xdr_wrong_union("SaleTypeExt: fixedPriceSale accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SaleTypeExt> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::SaleTypeExt;
  using case_type = ::stellar::SaleTypeExt::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().saleType());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "basicSale";
    case 2:
      return "crowdFundingSale";
    case 3:
      return "fixedPriceSale";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::SaleTypeExt &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of saleType in SaleTypeExt");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SaleTypeExt &obj) {
    xdr::archive(ar, obj.saleType(), "saleType");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.saleType(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of saleType in SaleTypeExt");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SaleTypeExt &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "saleType");
    obj.saleType(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.saleType(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SaleQuoteAsset {
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

  AssetCode quoteAsset{};
  uint64 price{};
  BalanceID quoteBalance{};
  uint64 currentCap{};
  _ext_t ext{};

  SaleQuoteAsset() = default;
  template<typename _quoteAsset_T,
           typename _price_T,
           typename _quoteBalance_T,
           typename _currentCap_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<AssetCode, _quoteAsset_T>::value
                          && std::is_constructible<uint64, _price_T>::value
                          && std::is_constructible<BalanceID, _quoteBalance_T>::value
                          && std::is_constructible<uint64, _currentCap_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit SaleQuoteAsset(_quoteAsset_T &&_quoteAsset,
                          _price_T &&_price,
                          _quoteBalance_T &&_quoteBalance,
                          _currentCap_T &&_currentCap,
                          _ext_T &&_ext)
    : quoteAsset(std::forward<_quoteAsset_T>(_quoteAsset)),
      price(std::forward<_price_T>(_price)),
      quoteBalance(std::forward<_quoteBalance_T>(_quoteBalance)),
      currentCap(std::forward<_currentCap_T>(_currentCap)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SaleQuoteAsset::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::SaleQuoteAsset::_ext_t;
  using case_type = ::stellar::SaleQuoteAsset::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::SaleQuoteAsset::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SaleQuoteAsset::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SaleQuoteAsset::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::SaleQuoteAsset>
  : xdr_struct_base<field_ptr<::stellar::SaleQuoteAsset,
                              decltype(::stellar::SaleQuoteAsset::quoteAsset),
                              &::stellar::SaleQuoteAsset::quoteAsset>,
                    field_ptr<::stellar::SaleQuoteAsset,
                              decltype(::stellar::SaleQuoteAsset::price),
                              &::stellar::SaleQuoteAsset::price>,
                    field_ptr<::stellar::SaleQuoteAsset,
                              decltype(::stellar::SaleQuoteAsset::quoteBalance),
                              &::stellar::SaleQuoteAsset::quoteBalance>,
                    field_ptr<::stellar::SaleQuoteAsset,
                              decltype(::stellar::SaleQuoteAsset::currentCap),
                              &::stellar::SaleQuoteAsset::currentCap>,
                    field_ptr<::stellar::SaleQuoteAsset,
                              decltype(::stellar::SaleQuoteAsset::ext),
                              &::stellar::SaleQuoteAsset::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SaleQuoteAsset &obj) {
    archive(ar, obj.quoteAsset, "quoteAsset");
    archive(ar, obj.price, "price");
    archive(ar, obj.quoteBalance, "quoteBalance");
    archive(ar, obj.currentCap, "currentCap");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SaleQuoteAsset &obj) {
    archive(ar, obj.quoteAsset, "quoteAsset");
    archive(ar, obj.price, "price");
    archive(ar, obj.quoteBalance, "quoteBalance");
    archive(ar, obj.currentCap, "currentCap");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SaleEntry {
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
  uint64 saleType{};
  AccountID ownerID{};
  AssetCode baseAsset{};
  uint64 startTime{};
  uint64 endTime{};
  AssetCode defaultQuoteAsset{};
  uint64 softCap{};
  uint64 hardCap{};
  uint64 currentCapInBase{};
  uint64 maxAmountToBeSold{};
  longstring details{};
  xdr::xvector<SaleQuoteAsset,100> quoteAssets{};
  BalanceID baseBalance{};
  SaleTypeExt saleTypeExt{};
  _ext_t ext{};

  SaleEntry() = default;
  template<typename _saleID_T,
           typename _saleType_T,
           typename _ownerID_T,
           typename _baseAsset_T,
           typename _startTime_T,
           typename _endTime_T,
           typename _defaultQuoteAsset_T,
           typename _softCap_T,
           typename _hardCap_T,
           typename _currentCapInBase_T,
           typename _maxAmountToBeSold_T,
           typename _details_T,
           typename _quoteAssets_T,
           typename _baseBalance_T,
           typename _saleTypeExt_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _saleID_T>::value
                          && std::is_constructible<uint64, _saleType_T>::value
                          && std::is_constructible<AccountID, _ownerID_T>::value
                          && std::is_constructible<AssetCode, _baseAsset_T>::value
                          && std::is_constructible<uint64, _startTime_T>::value
                          && std::is_constructible<uint64, _endTime_T>::value
                          && std::is_constructible<AssetCode, _defaultQuoteAsset_T>::value
                          && std::is_constructible<uint64, _softCap_T>::value
                          && std::is_constructible<uint64, _hardCap_T>::value
                          && std::is_constructible<uint64, _currentCapInBase_T>::value
                          && std::is_constructible<uint64, _maxAmountToBeSold_T>::value
                          && std::is_constructible<longstring, _details_T>::value
                          && std::is_constructible<xdr::xvector<SaleQuoteAsset,100>, _quoteAssets_T>::value
                          && std::is_constructible<BalanceID, _baseBalance_T>::value
                          && std::is_constructible<SaleTypeExt, _saleTypeExt_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit SaleEntry(_saleID_T &&_saleID,
                     _saleType_T &&_saleType,
                     _ownerID_T &&_ownerID,
                     _baseAsset_T &&_baseAsset,
                     _startTime_T &&_startTime,
                     _endTime_T &&_endTime,
                     _defaultQuoteAsset_T &&_defaultQuoteAsset,
                     _softCap_T &&_softCap,
                     _hardCap_T &&_hardCap,
                     _currentCapInBase_T &&_currentCapInBase,
                     _maxAmountToBeSold_T &&_maxAmountToBeSold,
                     _details_T &&_details,
                     _quoteAssets_T &&_quoteAssets,
                     _baseBalance_T &&_baseBalance,
                     _saleTypeExt_T &&_saleTypeExt,
                     _ext_T &&_ext)
    : saleID(std::forward<_saleID_T>(_saleID)),
      saleType(std::forward<_saleType_T>(_saleType)),
      ownerID(std::forward<_ownerID_T>(_ownerID)),
      baseAsset(std::forward<_baseAsset_T>(_baseAsset)),
      startTime(std::forward<_startTime_T>(_startTime)),
      endTime(std::forward<_endTime_T>(_endTime)),
      defaultQuoteAsset(std::forward<_defaultQuoteAsset_T>(_defaultQuoteAsset)),
      softCap(std::forward<_softCap_T>(_softCap)),
      hardCap(std::forward<_hardCap_T>(_hardCap)),
      currentCapInBase(std::forward<_currentCapInBase_T>(_currentCapInBase)),
      maxAmountToBeSold(std::forward<_maxAmountToBeSold_T>(_maxAmountToBeSold)),
      details(std::forward<_details_T>(_details)),
      quoteAssets(std::forward<_quoteAssets_T>(_quoteAssets)),
      baseBalance(std::forward<_baseBalance_T>(_baseBalance)),
      saleTypeExt(std::forward<_saleTypeExt_T>(_saleTypeExt)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SaleEntry::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::SaleEntry::_ext_t;
  using case_type = ::stellar::SaleEntry::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::SaleEntry::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SaleEntry::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SaleEntry::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::SaleEntry>
  : xdr_struct_base<field_ptr<::stellar::SaleEntry,
                              decltype(::stellar::SaleEntry::saleID),
                              &::stellar::SaleEntry::saleID>,
                    field_ptr<::stellar::SaleEntry,
                              decltype(::stellar::SaleEntry::saleType),
                              &::stellar::SaleEntry::saleType>,
                    field_ptr<::stellar::SaleEntry,
                              decltype(::stellar::SaleEntry::ownerID),
                              &::stellar::SaleEntry::ownerID>,
                    field_ptr<::stellar::SaleEntry,
                              decltype(::stellar::SaleEntry::baseAsset),
                              &::stellar::SaleEntry::baseAsset>,
                    field_ptr<::stellar::SaleEntry,
                              decltype(::stellar::SaleEntry::startTime),
                              &::stellar::SaleEntry::startTime>,
                    field_ptr<::stellar::SaleEntry,
                              decltype(::stellar::SaleEntry::endTime),
                              &::stellar::SaleEntry::endTime>,
                    field_ptr<::stellar::SaleEntry,
                              decltype(::stellar::SaleEntry::defaultQuoteAsset),
                              &::stellar::SaleEntry::defaultQuoteAsset>,
                    field_ptr<::stellar::SaleEntry,
                              decltype(::stellar::SaleEntry::softCap),
                              &::stellar::SaleEntry::softCap>,
                    field_ptr<::stellar::SaleEntry,
                              decltype(::stellar::SaleEntry::hardCap),
                              &::stellar::SaleEntry::hardCap>,
                    field_ptr<::stellar::SaleEntry,
                              decltype(::stellar::SaleEntry::currentCapInBase),
                              &::stellar::SaleEntry::currentCapInBase>,
                    field_ptr<::stellar::SaleEntry,
                              decltype(::stellar::SaleEntry::maxAmountToBeSold),
                              &::stellar::SaleEntry::maxAmountToBeSold>,
                    field_ptr<::stellar::SaleEntry,
                              decltype(::stellar::SaleEntry::details),
                              &::stellar::SaleEntry::details>,
                    field_ptr<::stellar::SaleEntry,
                              decltype(::stellar::SaleEntry::quoteAssets),
                              &::stellar::SaleEntry::quoteAssets>,
                    field_ptr<::stellar::SaleEntry,
                              decltype(::stellar::SaleEntry::baseBalance),
                              &::stellar::SaleEntry::baseBalance>,
                    field_ptr<::stellar::SaleEntry,
                              decltype(::stellar::SaleEntry::saleTypeExt),
                              &::stellar::SaleEntry::saleTypeExt>,
                    field_ptr<::stellar::SaleEntry,
                              decltype(::stellar::SaleEntry::ext),
                              &::stellar::SaleEntry::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SaleEntry &obj) {
    archive(ar, obj.saleID, "saleID");
    archive(ar, obj.saleType, "saleType");
    archive(ar, obj.ownerID, "ownerID");
    archive(ar, obj.baseAsset, "baseAsset");
    archive(ar, obj.startTime, "startTime");
    archive(ar, obj.endTime, "endTime");
    archive(ar, obj.defaultQuoteAsset, "defaultQuoteAsset");
    archive(ar, obj.softCap, "softCap");
    archive(ar, obj.hardCap, "hardCap");
    archive(ar, obj.currentCapInBase, "currentCapInBase");
    archive(ar, obj.maxAmountToBeSold, "maxAmountToBeSold");
    archive(ar, obj.details, "details");
    archive(ar, obj.quoteAssets, "quoteAssets");
    archive(ar, obj.baseBalance, "baseBalance");
    archive(ar, obj.saleTypeExt, "saleTypeExt");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SaleEntry &obj) {
    archive(ar, obj.saleID, "saleID");
    archive(ar, obj.saleType, "saleType");
    archive(ar, obj.ownerID, "ownerID");
    archive(ar, obj.baseAsset, "baseAsset");
    archive(ar, obj.startTime, "startTime");
    archive(ar, obj.endTime, "endTime");
    archive(ar, obj.defaultQuoteAsset, "defaultQuoteAsset");
    archive(ar, obj.softCap, "softCap");
    archive(ar, obj.hardCap, "hardCap");
    archive(ar, obj.currentCapInBase, "currentCapInBase");
    archive(ar, obj.maxAmountToBeSold, "maxAmountToBeSold");
    archive(ar, obj.details, "details");
    archive(ar, obj.quoteAssets, "quoteAssets");
    archive(ar, obj.baseBalance, "baseBalance");
    archive(ar, obj.saleTypeExt, "saleTypeExt");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

}

#endif // !__XDR_STELLAR_LEDGER_ENTRIES_SALE_H_INCLUDED__
