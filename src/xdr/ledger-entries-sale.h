// -*- C++ -*-
// Automatically generated from ledger-entries-sale.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_LEDGER_ENTRIES_SALE_H_INCLUDED__
#define __XDR_LEDGER_ENTRIES_SALE_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"

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
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
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

struct FixedPriceSale  : xdr::xdr_abstract {
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

  FixedPriceSale() = default;
  template<typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit FixedPriceSale(_ext_T &&_ext)
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

struct CrowdFundingSale  : xdr::xdr_abstract {
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

  CrowdFundingSale() = default;
  template<typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CrowdFundingSale(_ext_T &&_ext)
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

struct BasicSale  : xdr::xdr_abstract {
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

  BasicSale() = default;
  template<typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit BasicSale(_ext_T &&_ext)
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

struct SaleTypeExt : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<SaleType>::case_type;
private:
  _xdr_case_type saleType_;
  union {
    BasicSale basicSale_;
    CrowdFundingSale crowdFundingSale_;
    FixedPriceSale fixedPriceSale_;
  };

public:
  static constexpr const bool _xdr_has_default_case = false;
  static const std::vector<SaleType> &_xdr_case_values() {
    static const std::vector<SaleType> _xdr_disc_vec {
      SaleType::BASIC_SALE,
      SaleType::CROWD_FUNDING,
      SaleType::FIXED_PRICE
    };
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
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
      saleType_ = which;switch (saleType_)
{
      case (int32_t)SaleType::BASIC_SALE:
new(&basicSale_) BasicSale{};
break;
      case (int32_t)SaleType::CROWD_FUNDING:
new(&crowdFundingSale_) CrowdFundingSale{};
break;
      case (int32_t)SaleType::FIXED_PRICE:
new(&fixedPriceSale_) FixedPriceSale{};
break;
}

    }
    else
      saleType_ = which;
  }
  explicit SaleTypeExt(SaleType which = SaleType{}) : saleType_((int32_t)which) {
    switch (saleType_)
{
    case (int32_t)SaleType::BASIC_SALE:
new(&basicSale_) BasicSale{};
break;
    case (int32_t)SaleType::CROWD_FUNDING:
new(&crowdFundingSale_) CrowdFundingSale{};
break;
    case (int32_t)SaleType::FIXED_PRICE:
new(&fixedPriceSale_) FixedPriceSale{};
break;
}

  }
  SaleTypeExt(const SaleTypeExt &source) : saleType_(source.saleType_) {
    switch (saleType_)
{
    case (int32_t)SaleType::BASIC_SALE:
new(&basicSale_) BasicSale(source.basicSale_);
break;
    case (int32_t)SaleType::CROWD_FUNDING:
new(&crowdFundingSale_) CrowdFundingSale(source.crowdFundingSale_);
break;
    case (int32_t)SaleType::FIXED_PRICE:
new(&fixedPriceSale_) FixedPriceSale(source.fixedPriceSale_);
break;
}

  }
  SaleTypeExt(SaleTypeExt &&source) : saleType_(source.saleType_) {
    switch (saleType_)
{
    case (int32_t)SaleType::BASIC_SALE:
new(&basicSale_) BasicSale(std::move(source.basicSale_));
break;
    case (int32_t)SaleType::CROWD_FUNDING:
new(&crowdFundingSale_) CrowdFundingSale(std::move(source.crowdFundingSale_));
break;
    case (int32_t)SaleType::FIXED_PRICE:
new(&fixedPriceSale_) FixedPriceSale(std::move(source.fixedPriceSale_));
break;
}

  }
  ~SaleTypeExt() {
switch (saleType_)
{
  case (int32_t)SaleType::BASIC_SALE:
basicSale_.~BasicSale();
break;
  case (int32_t)SaleType::CROWD_FUNDING:
crowdFundingSale_.~CrowdFundingSale();
break;
  case (int32_t)SaleType::FIXED_PRICE:
fixedPriceSale_.~FixedPriceSale();
break;
}
}

  SaleTypeExt &operator=(const SaleTypeExt &source) {
    if (saleType_ == source.saleType_)
{
switch (saleType_)
{
    case (int32_t)SaleType::BASIC_SALE:
basicSale_ = source.basicSale_;
break;
    case (int32_t)SaleType::CROWD_FUNDING:
crowdFundingSale_ = source.crowdFundingSale_;
break;
    case (int32_t)SaleType::FIXED_PRICE:
fixedPriceSale_ = source.fixedPriceSale_;
break;
}
}
else {this->~SaleTypeExt();
    saleType_ = source.saleType_;
switch (saleType_)
{
    case (int32_t)SaleType::BASIC_SALE:
new(&basicSale_) BasicSale(source.basicSale_);
break;
    case (int32_t)SaleType::CROWD_FUNDING:
new(&crowdFundingSale_) CrowdFundingSale(source.crowdFundingSale_);
break;
    case (int32_t)SaleType::FIXED_PRICE:
new(&fixedPriceSale_) FixedPriceSale(source.fixedPriceSale_);
break;
}
}
    return *this;
  }
  SaleTypeExt &operator=(SaleTypeExt &&source) {
    if (saleType_ == source.saleType_)
{
switch (saleType_)
{
    case (int32_t)SaleType::BASIC_SALE:
basicSale_ = std::move(source.basicSale_);
break;
    case (int32_t)SaleType::CROWD_FUNDING:
crowdFundingSale_ = std::move(source.crowdFundingSale_);
break;
    case (int32_t)SaleType::FIXED_PRICE:
fixedPriceSale_ = std::move(source.fixedPriceSale_);
break;
}
}
else {this->~SaleTypeExt();
    saleType_ = std::move(source.saleType_);
switch (saleType_)
{
    case (int32_t)SaleType::BASIC_SALE:
new(&basicSale_) BasicSale(std::move(source.basicSale_));
break;
    case (int32_t)SaleType::CROWD_FUNDING:
new(&crowdFundingSale_) CrowdFundingSale(std::move(source.crowdFundingSale_));
break;
    case (int32_t)SaleType::FIXED_PRICE:
new(&fixedPriceSale_) FixedPriceSale(std::move(source.fixedPriceSale_));
break;
}
}
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

struct SaleQuoteAsset  : xdr::xdr_abstract {
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

struct SaleEntry  : xdr::xdr_abstract {
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
        LedgerVersion::EMPTY_VERSION,
        LedgerVersion::ADD_SALE_WHITELISTS
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)LedgerVersion::EMPTY_VERSION ? 0
        : which == (int32_t)LedgerVersion::ADD_SALE_WHITELISTS ? 0
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
      case (int32_t)LedgerVersion::ADD_SALE_WHITELISTS:
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
        case (int32_t)LedgerVersion::ADD_SALE_WHITELISTS:
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
      case (int32_t)LedgerVersion::ADD_SALE_WHITELISTS:
        break;
}

    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
      case (int32_t)LedgerVersion::ADD_SALE_WHITELISTS:
        break;
}

    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
      case (int32_t)LedgerVersion::ADD_SALE_WHITELISTS:
        break;
}

    }
    ~_ext_t() {
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
      break;
    case (int32_t)LedgerVersion::ADD_SALE_WHITELISTS:
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
      case (int32_t)LedgerVersion::ADD_SALE_WHITELISTS:
        break;
}
}
else {this->~_ext_t();
      v_ = source.v_;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
      case (int32_t)LedgerVersion::ADD_SALE_WHITELISTS:
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
      case (int32_t)LedgerVersion::ADD_SALE_WHITELISTS:
        break;
}
}
else {this->~_ext_t();
      v_ = std::move(source.v_);
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
      case (int32_t)LedgerVersion::ADD_SALE_WHITELISTS:
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

}

#endif // !__XDR_LEDGER_ENTRIES_SALE_H_INCLUDED__
