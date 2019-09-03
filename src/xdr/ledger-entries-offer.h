// -*- C++ -*-
// Automatically generated from ledger-entries-offer.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_LEDGER_ENTRIES_OFFER_H_INCLUDED__
#define __XDR_LEDGER_ENTRIES_OFFER_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"

namespace stellar {

struct OfferEntry  : xdr::xdr_abstract {
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

  uint64 offerID{};
  uint64 orderBookID{};
  AccountID ownerID{};
  bool isBuy{};
  AssetCode base{};
  AssetCode quote{};
  BalanceID baseBalance{};
  BalanceID quoteBalance{};
  int64 baseAmount{};
  int64 quoteAmount{};
  uint64 createdAt{};
  int64 fee{};
  int64 percentFee{};
  int64 price{};
  _ext_t ext{};

  OfferEntry() = default;
  template<typename _offerID_T,
           typename _orderBookID_T,
           typename _ownerID_T,
           typename _isBuy_T,
           typename _base_T,
           typename _quote_T,
           typename _baseBalance_T,
           typename _quoteBalance_T,
           typename _baseAmount_T,
           typename _quoteAmount_T,
           typename _createdAt_T,
           typename _fee_T,
           typename _percentFee_T,
           typename _price_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _offerID_T>::value
                          && std::is_constructible<uint64, _orderBookID_T>::value
                          && std::is_constructible<AccountID, _ownerID_T>::value
                          && std::is_constructible<bool, _isBuy_T>::value
                          && std::is_constructible<AssetCode, _base_T>::value
                          && std::is_constructible<AssetCode, _quote_T>::value
                          && std::is_constructible<BalanceID, _baseBalance_T>::value
                          && std::is_constructible<BalanceID, _quoteBalance_T>::value
                          && std::is_constructible<int64, _baseAmount_T>::value
                          && std::is_constructible<int64, _quoteAmount_T>::value
                          && std::is_constructible<uint64, _createdAt_T>::value
                          && std::is_constructible<int64, _fee_T>::value
                          && std::is_constructible<int64, _percentFee_T>::value
                          && std::is_constructible<int64, _price_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit OfferEntry(_offerID_T &&_offerID,
                      _orderBookID_T &&_orderBookID,
                      _ownerID_T &&_ownerID,
                      _isBuy_T &&_isBuy,
                      _base_T &&_base,
                      _quote_T &&_quote,
                      _baseBalance_T &&_baseBalance,
                      _quoteBalance_T &&_quoteBalance,
                      _baseAmount_T &&_baseAmount,
                      _quoteAmount_T &&_quoteAmount,
                      _createdAt_T &&_createdAt,
                      _fee_T &&_fee,
                      _percentFee_T &&_percentFee,
                      _price_T &&_price,
                      _ext_T &&_ext)
    : offerID(std::forward<_offerID_T>(_offerID)),
      orderBookID(std::forward<_orderBookID_T>(_orderBookID)),
      ownerID(std::forward<_ownerID_T>(_ownerID)),
      isBuy(std::forward<_isBuy_T>(_isBuy)),
      base(std::forward<_base_T>(_base)),
      quote(std::forward<_quote_T>(_quote)),
      baseBalance(std::forward<_baseBalance_T>(_baseBalance)),
      quoteBalance(std::forward<_quoteBalance_T>(_quoteBalance)),
      baseAmount(std::forward<_baseAmount_T>(_baseAmount)),
      quoteAmount(std::forward<_quoteAmount_T>(_quoteAmount)),
      createdAt(std::forward<_createdAt_T>(_createdAt)),
      fee(std::forward<_fee_T>(_fee)),
      percentFee(std::forward<_percentFee_T>(_percentFee)),
      price(std::forward<_price_T>(_price)),
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

#endif // !__XDR_LEDGER_ENTRIES_OFFER_H_INCLUDED__
