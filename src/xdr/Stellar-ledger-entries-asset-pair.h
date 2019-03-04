// -*- C++ -*-
// Automatically generated from Stellar-ledger-entries-asset-pair.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_LEDGER_ENTRIES_ASSET_PAIR_H_INCLUDED__
#define __XDR_STELLAR_LEDGER_ENTRIES_ASSET_PAIR_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-types.h"

namespace stellar {

enum class AssetPairPolicy : std::int32_t {
  TRADEABLE_SECONDARY_MARKET = 1,
  PHYSICAL_PRICE_RESTRICTION = 2,
  CURRENT_PRICE_RESTRICTION = 4,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::AssetPairPolicy>
  : xdr_integral_base<::stellar::AssetPairPolicy, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::AssetPairPolicy val) {
    switch (val) {
    case ::stellar::AssetPairPolicy::TRADEABLE_SECONDARY_MARKET:
      return "TRADEABLE_SECONDARY_MARKET";
    case ::stellar::AssetPairPolicy::PHYSICAL_PRICE_RESTRICTION:
      return "PHYSICAL_PRICE_RESTRICTION";
    case ::stellar::AssetPairPolicy::CURRENT_PRICE_RESTRICTION:
      return "CURRENT_PRICE_RESTRICTION";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::AssetPairPolicy::TRADEABLE_SECONDARY_MARKET,
      (int32_t)::stellar::AssetPairPolicy::PHYSICAL_PRICE_RESTRICTION,
      (int32_t)::stellar::AssetPairPolicy::CURRENT_PRICE_RESTRICTION
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct AssetPairEntry {
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

  AssetCode base{};
  AssetCode quote{};
  int64 currentPrice{};
  int64 physicalPrice{};
  int64 physicalPriceCorrection{};
  int64 maxPriceStep{};
  int32 policies{};
  _ext_t ext{};

  AssetPairEntry() = default;
  template<typename _base_T,
           typename _quote_T,
           typename _currentPrice_T,
           typename _physicalPrice_T,
           typename _physicalPriceCorrection_T,
           typename _maxPriceStep_T,
           typename _policies_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<AssetCode, _base_T>::value
                          && std::is_constructible<AssetCode, _quote_T>::value
                          && std::is_constructible<int64, _currentPrice_T>::value
                          && std::is_constructible<int64, _physicalPrice_T>::value
                          && std::is_constructible<int64, _physicalPriceCorrection_T>::value
                          && std::is_constructible<int64, _maxPriceStep_T>::value
                          && std::is_constructible<int32, _policies_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit AssetPairEntry(_base_T &&_base,
                          _quote_T &&_quote,
                          _currentPrice_T &&_currentPrice,
                          _physicalPrice_T &&_physicalPrice,
                          _physicalPriceCorrection_T &&_physicalPriceCorrection,
                          _maxPriceStep_T &&_maxPriceStep,
                          _policies_T &&_policies,
                          _ext_T &&_ext)
    : base(std::forward<_base_T>(_base)),
      quote(std::forward<_quote_T>(_quote)),
      currentPrice(std::forward<_currentPrice_T>(_currentPrice)),
      physicalPrice(std::forward<_physicalPrice_T>(_physicalPrice)),
      physicalPriceCorrection(std::forward<_physicalPriceCorrection_T>(_physicalPriceCorrection)),
      maxPriceStep(std::forward<_maxPriceStep_T>(_maxPriceStep)),
      policies(std::forward<_policies_T>(_policies)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::AssetPairEntry::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::AssetPairEntry::_ext_t;
  using case_type = ::stellar::AssetPairEntry::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::AssetPairEntry::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::AssetPairEntry::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::AssetPairEntry::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::AssetPairEntry>
  : xdr_struct_base<field_ptr<::stellar::AssetPairEntry,
                              decltype(::stellar::AssetPairEntry::base),
                              &::stellar::AssetPairEntry::base>,
                    field_ptr<::stellar::AssetPairEntry,
                              decltype(::stellar::AssetPairEntry::quote),
                              &::stellar::AssetPairEntry::quote>,
                    field_ptr<::stellar::AssetPairEntry,
                              decltype(::stellar::AssetPairEntry::currentPrice),
                              &::stellar::AssetPairEntry::currentPrice>,
                    field_ptr<::stellar::AssetPairEntry,
                              decltype(::stellar::AssetPairEntry::physicalPrice),
                              &::stellar::AssetPairEntry::physicalPrice>,
                    field_ptr<::stellar::AssetPairEntry,
                              decltype(::stellar::AssetPairEntry::physicalPriceCorrection),
                              &::stellar::AssetPairEntry::physicalPriceCorrection>,
                    field_ptr<::stellar::AssetPairEntry,
                              decltype(::stellar::AssetPairEntry::maxPriceStep),
                              &::stellar::AssetPairEntry::maxPriceStep>,
                    field_ptr<::stellar::AssetPairEntry,
                              decltype(::stellar::AssetPairEntry::policies),
                              &::stellar::AssetPairEntry::policies>,
                    field_ptr<::stellar::AssetPairEntry,
                              decltype(::stellar::AssetPairEntry::ext),
                              &::stellar::AssetPairEntry::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::AssetPairEntry &obj) {
    archive(ar, obj.base, "base");
    archive(ar, obj.quote, "quote");
    archive(ar, obj.currentPrice, "currentPrice");
    archive(ar, obj.physicalPrice, "physicalPrice");
    archive(ar, obj.physicalPriceCorrection, "physicalPriceCorrection");
    archive(ar, obj.maxPriceStep, "maxPriceStep");
    archive(ar, obj.policies, "policies");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::AssetPairEntry &obj) {
    archive(ar, obj.base, "base");
    archive(ar, obj.quote, "quote");
    archive(ar, obj.currentPrice, "currentPrice");
    archive(ar, obj.physicalPrice, "physicalPrice");
    archive(ar, obj.physicalPriceCorrection, "physicalPriceCorrection");
    archive(ar, obj.maxPriceStep, "maxPriceStep");
    archive(ar, obj.policies, "policies");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

}

#endif // !__XDR_STELLAR_LEDGER_ENTRIES_ASSET_PAIR_H_INCLUDED__
