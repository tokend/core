// -*- C++ -*-
// Automatically generated from ledger-entries-asset-pair.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_LEDGER_ENTRIES_ASSET_PAIR_H_INCLUDED__
#define __XDR_LEDGER_ENTRIES_ASSET_PAIR_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"

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
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
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

struct AssetPairEntry  : xdr::xdr_abstract {
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

#endif // !__XDR_LEDGER_ENTRIES_ASSET_PAIR_H_INCLUDED__
