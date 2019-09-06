// -*- C++ -*-
// Automatically generated from operation-manage-offer.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_MANAGE_OFFER_H_INCLUDED__
#define __XDR_OPERATION_MANAGE_OFFER_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/ledger-entries.h"

namespace stellar {

struct ManageOfferOp  : xdr::xdr_abstract {
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

  BalanceID baseBalance{};
  BalanceID quoteBalance{};
  bool isBuy{};
  int64 amount{};
  int64 price{};
  int64 fee{};
  uint64 offerID{};
  uint64 orderBookID{};
  _ext_t ext{};

  ManageOfferOp() = default;
  template<typename _baseBalance_T,
           typename _quoteBalance_T,
           typename _isBuy_T,
           typename _amount_T,
           typename _price_T,
           typename _fee_T,
           typename _offerID_T,
           typename _orderBookID_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<BalanceID, _baseBalance_T>::value
                          && std::is_constructible<BalanceID, _quoteBalance_T>::value
                          && std::is_constructible<bool, _isBuy_T>::value
                          && std::is_constructible<int64, _amount_T>::value
                          && std::is_constructible<int64, _price_T>::value
                          && std::is_constructible<int64, _fee_T>::value
                          && std::is_constructible<uint64, _offerID_T>::value
                          && std::is_constructible<uint64, _orderBookID_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ManageOfferOp(_baseBalance_T &&_baseBalance,
                         _quoteBalance_T &&_quoteBalance,
                         _isBuy_T &&_isBuy,
                         _amount_T &&_amount,
                         _price_T &&_price,
                         _fee_T &&_fee,
                         _offerID_T &&_offerID,
                         _orderBookID_T &&_orderBookID,
                         _ext_T &&_ext)
    : baseBalance(std::forward<_baseBalance_T>(_baseBalance)),
      quoteBalance(std::forward<_quoteBalance_T>(_quoteBalance)),
      isBuy(std::forward<_isBuy_T>(_isBuy)),
      amount(std::forward<_amount_T>(_amount)),
      price(std::forward<_price_T>(_price)),
      fee(std::forward<_fee_T>(_fee)),
      offerID(std::forward<_offerID_T>(_offerID)),
      orderBookID(std::forward<_orderBookID_T>(_orderBookID)),
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

enum class ManageOfferResultCode : std::int32_t {
  SUCCESS = 0,
  MALFORMED = -1,
  PAIR_NOT_TRADED = -2,
  BALANCE_NOT_FOUND = -3,
  UNDERFUNDED = -4,
  CROSS_SELF = -5,
  OFFER_OVERFLOW = -6,
  ASSET_PAIR_NOT_TRADABLE = -7,
  PHYSICAL_PRICE_RESTRICTION = -8,
  CURRENT_PRICE_RESTRICTION = -9,
  NOT_FOUND = -10,
  INVALID_PERCENT_FEE = -11,
  INSUFFICIENT_PRICE = -12,
  ORDER_BOOK_DOES_NOT_EXISTS = -13,
  SALE_IS_NOT_STARTED_YET = -14,
  SALE_ALREADY_ENDED = -15,
  ORDER_VIOLATES_HARD_CAP = -16,
  CANT_PARTICIPATE_OWN_SALE = -17,
  ASSET_MISMATCHED = -18,
  PRICE_DOES_NOT_MATCH = -19,
  PRICE_IS_INVALID = -20,
  UPDATE_IS_NOT_ALLOWED = -21,
  INVALID_AMOUNT = -22,
  SALE_IS_NOT_ACTIVE = -23,
  REQUIRES_KYC = -24,
  SOURCE_UNDERFUNDED = -25,
  SOURCE_BALANCE_LOCK_OVERFLOW = -26,
  REQUIRES_VERIFICATION = -27,
  INCORRECT_AMOUNT_PRECISION = -28,
  SPECIFIC_RULE_FORBIDS = -29,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageOfferResultCode>
  : xdr_integral_base<::stellar::ManageOfferResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageOfferResultCode val) {
    switch (val) {
    case ::stellar::ManageOfferResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::ManageOfferResultCode::MALFORMED:
      return "MALFORMED";
    case ::stellar::ManageOfferResultCode::PAIR_NOT_TRADED:
      return "PAIR_NOT_TRADED";
    case ::stellar::ManageOfferResultCode::BALANCE_NOT_FOUND:
      return "BALANCE_NOT_FOUND";
    case ::stellar::ManageOfferResultCode::UNDERFUNDED:
      return "UNDERFUNDED";
    case ::stellar::ManageOfferResultCode::CROSS_SELF:
      return "CROSS_SELF";
    case ::stellar::ManageOfferResultCode::OFFER_OVERFLOW:
      return "OFFER_OVERFLOW";
    case ::stellar::ManageOfferResultCode::ASSET_PAIR_NOT_TRADABLE:
      return "ASSET_PAIR_NOT_TRADABLE";
    case ::stellar::ManageOfferResultCode::PHYSICAL_PRICE_RESTRICTION:
      return "PHYSICAL_PRICE_RESTRICTION";
    case ::stellar::ManageOfferResultCode::CURRENT_PRICE_RESTRICTION:
      return "CURRENT_PRICE_RESTRICTION";
    case ::stellar::ManageOfferResultCode::NOT_FOUND:
      return "NOT_FOUND";
    case ::stellar::ManageOfferResultCode::INVALID_PERCENT_FEE:
      return "INVALID_PERCENT_FEE";
    case ::stellar::ManageOfferResultCode::INSUFFICIENT_PRICE:
      return "INSUFFICIENT_PRICE";
    case ::stellar::ManageOfferResultCode::ORDER_BOOK_DOES_NOT_EXISTS:
      return "ORDER_BOOK_DOES_NOT_EXISTS";
    case ::stellar::ManageOfferResultCode::SALE_IS_NOT_STARTED_YET:
      return "SALE_IS_NOT_STARTED_YET";
    case ::stellar::ManageOfferResultCode::SALE_ALREADY_ENDED:
      return "SALE_ALREADY_ENDED";
    case ::stellar::ManageOfferResultCode::ORDER_VIOLATES_HARD_CAP:
      return "ORDER_VIOLATES_HARD_CAP";
    case ::stellar::ManageOfferResultCode::CANT_PARTICIPATE_OWN_SALE:
      return "CANT_PARTICIPATE_OWN_SALE";
    case ::stellar::ManageOfferResultCode::ASSET_MISMATCHED:
      return "ASSET_MISMATCHED";
    case ::stellar::ManageOfferResultCode::PRICE_DOES_NOT_MATCH:
      return "PRICE_DOES_NOT_MATCH";
    case ::stellar::ManageOfferResultCode::PRICE_IS_INVALID:
      return "PRICE_IS_INVALID";
    case ::stellar::ManageOfferResultCode::UPDATE_IS_NOT_ALLOWED:
      return "UPDATE_IS_NOT_ALLOWED";
    case ::stellar::ManageOfferResultCode::INVALID_AMOUNT:
      return "INVALID_AMOUNT";
    case ::stellar::ManageOfferResultCode::SALE_IS_NOT_ACTIVE:
      return "SALE_IS_NOT_ACTIVE";
    case ::stellar::ManageOfferResultCode::REQUIRES_KYC:
      return "REQUIRES_KYC";
    case ::stellar::ManageOfferResultCode::SOURCE_UNDERFUNDED:
      return "SOURCE_UNDERFUNDED";
    case ::stellar::ManageOfferResultCode::SOURCE_BALANCE_LOCK_OVERFLOW:
      return "SOURCE_BALANCE_LOCK_OVERFLOW";
    case ::stellar::ManageOfferResultCode::REQUIRES_VERIFICATION:
      return "REQUIRES_VERIFICATION";
    case ::stellar::ManageOfferResultCode::INCORRECT_AMOUNT_PRECISION:
      return "INCORRECT_AMOUNT_PRECISION";
    case ::stellar::ManageOfferResultCode::SPECIFIC_RULE_FORBIDS:
      return "SPECIFIC_RULE_FORBIDS";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageOfferResultCode::SUCCESS,
      (int32_t)::stellar::ManageOfferResultCode::MALFORMED,
      (int32_t)::stellar::ManageOfferResultCode::PAIR_NOT_TRADED,
      (int32_t)::stellar::ManageOfferResultCode::BALANCE_NOT_FOUND,
      (int32_t)::stellar::ManageOfferResultCode::UNDERFUNDED,
      (int32_t)::stellar::ManageOfferResultCode::CROSS_SELF,
      (int32_t)::stellar::ManageOfferResultCode::OFFER_OVERFLOW,
      (int32_t)::stellar::ManageOfferResultCode::ASSET_PAIR_NOT_TRADABLE,
      (int32_t)::stellar::ManageOfferResultCode::PHYSICAL_PRICE_RESTRICTION,
      (int32_t)::stellar::ManageOfferResultCode::CURRENT_PRICE_RESTRICTION,
      (int32_t)::stellar::ManageOfferResultCode::NOT_FOUND,
      (int32_t)::stellar::ManageOfferResultCode::INVALID_PERCENT_FEE,
      (int32_t)::stellar::ManageOfferResultCode::INSUFFICIENT_PRICE,
      (int32_t)::stellar::ManageOfferResultCode::ORDER_BOOK_DOES_NOT_EXISTS,
      (int32_t)::stellar::ManageOfferResultCode::SALE_IS_NOT_STARTED_YET,
      (int32_t)::stellar::ManageOfferResultCode::SALE_ALREADY_ENDED,
      (int32_t)::stellar::ManageOfferResultCode::ORDER_VIOLATES_HARD_CAP,
      (int32_t)::stellar::ManageOfferResultCode::CANT_PARTICIPATE_OWN_SALE,
      (int32_t)::stellar::ManageOfferResultCode::ASSET_MISMATCHED,
      (int32_t)::stellar::ManageOfferResultCode::PRICE_DOES_NOT_MATCH,
      (int32_t)::stellar::ManageOfferResultCode::PRICE_IS_INVALID,
      (int32_t)::stellar::ManageOfferResultCode::UPDATE_IS_NOT_ALLOWED,
      (int32_t)::stellar::ManageOfferResultCode::INVALID_AMOUNT,
      (int32_t)::stellar::ManageOfferResultCode::SALE_IS_NOT_ACTIVE,
      (int32_t)::stellar::ManageOfferResultCode::REQUIRES_KYC,
      (int32_t)::stellar::ManageOfferResultCode::SOURCE_UNDERFUNDED,
      (int32_t)::stellar::ManageOfferResultCode::SOURCE_BALANCE_LOCK_OVERFLOW,
      (int32_t)::stellar::ManageOfferResultCode::REQUIRES_VERIFICATION,
      (int32_t)::stellar::ManageOfferResultCode::INCORRECT_AMOUNT_PRECISION,
      (int32_t)::stellar::ManageOfferResultCode::SPECIFIC_RULE_FORBIDS
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

enum class ManageOfferEffect : std::int32_t {
  CREATED = 0,
  UPDATED = 1,
  DELETED = 2,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageOfferEffect>
  : xdr_integral_base<::stellar::ManageOfferEffect, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageOfferEffect val) {
    switch (val) {
    case ::stellar::ManageOfferEffect::CREATED:
      return "CREATED";
    case ::stellar::ManageOfferEffect::UPDATED:
      return "UPDATED";
    case ::stellar::ManageOfferEffect::DELETED:
      return "DELETED";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageOfferEffect::CREATED,
      (int32_t)::stellar::ManageOfferEffect::UPDATED,
      (int32_t)::stellar::ManageOfferEffect::DELETED
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ClaimOfferAtom  : xdr::xdr_abstract {
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

  AccountID bAccountID{};
  uint64 offerID{};
  int64 baseAmount{};
  int64 quoteAmount{};
  int64 bFeePaid{};
  int64 aFeePaid{};
  BalanceID baseBalance{};
  BalanceID quoteBalance{};
  int64 currentPrice{};
  _ext_t ext{};

  ClaimOfferAtom() = default;
  template<typename _bAccountID_T,
           typename _offerID_T,
           typename _baseAmount_T,
           typename _quoteAmount_T,
           typename _bFeePaid_T,
           typename _aFeePaid_T,
           typename _baseBalance_T,
           typename _quoteBalance_T,
           typename _currentPrice_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<AccountID, _bAccountID_T>::value
                          && std::is_constructible<uint64, _offerID_T>::value
                          && std::is_constructible<int64, _baseAmount_T>::value
                          && std::is_constructible<int64, _quoteAmount_T>::value
                          && std::is_constructible<int64, _bFeePaid_T>::value
                          && std::is_constructible<int64, _aFeePaid_T>::value
                          && std::is_constructible<BalanceID, _baseBalance_T>::value
                          && std::is_constructible<BalanceID, _quoteBalance_T>::value
                          && std::is_constructible<int64, _currentPrice_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ClaimOfferAtom(_bAccountID_T &&_bAccountID,
                          _offerID_T &&_offerID,
                          _baseAmount_T &&_baseAmount,
                          _quoteAmount_T &&_quoteAmount,
                          _bFeePaid_T &&_bFeePaid,
                          _aFeePaid_T &&_aFeePaid,
                          _baseBalance_T &&_baseBalance,
                          _quoteBalance_T &&_quoteBalance,
                          _currentPrice_T &&_currentPrice,
                          _ext_T &&_ext)
    : bAccountID(std::forward<_bAccountID_T>(_bAccountID)),
      offerID(std::forward<_offerID_T>(_offerID)),
      baseAmount(std::forward<_baseAmount_T>(_baseAmount)),
      quoteAmount(std::forward<_quoteAmount_T>(_quoteAmount)),
      bFeePaid(std::forward<_bFeePaid_T>(_bFeePaid)),
      aFeePaid(std::forward<_aFeePaid_T>(_aFeePaid)),
      baseBalance(std::forward<_baseBalance_T>(_baseBalance)),
      quoteBalance(std::forward<_quoteBalance_T>(_quoteBalance)),
      currentPrice(std::forward<_currentPrice_T>(_currentPrice)),
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

struct ManageOfferSuccessResult  : xdr::xdr_abstract {
  struct _offer_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<ManageOfferEffect>::case_type;
  private:
    _xdr_case_type effect_;
    union {
      OfferEntry offer_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = true;
    static const std::vector<ManageOfferEffect> &_xdr_case_values() {
      static const std::vector<ManageOfferEffect> _xdr_disc_vec {};
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)ManageOfferEffect::CREATED || which == (int32_t)ManageOfferEffect::UPDATED ? 1
        : 0;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)ManageOfferEffect::CREATED:
      case (int32_t)ManageOfferEffect::UPDATED:
        _f(&_offer_t::offer_, std::forward<_A>(_a)...);
        return true;
      default:
        return true;
      }
    }

    _xdr_case_type _xdr_discriminant() const { return effect_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of effect in _offer_t");
      if (fnum != _xdr_field_number(effect_)) {
        this->~_offer_t();
        effect_ = which;switch (effect_)
{
        case (int32_t)ManageOfferEffect::CREATED:
        case (int32_t)ManageOfferEffect::UPDATED:
new(&offer_) OfferEntry{};
break;
        default:
          break;
}

      }
      else
        effect_ = which;
    }
    explicit _offer_t(ManageOfferEffect which = ManageOfferEffect{}) : effect_((int32_t)which) {
      switch (effect_)
{
      case (int32_t)ManageOfferEffect::CREATED:
      case (int32_t)ManageOfferEffect::UPDATED:
new(&offer_) OfferEntry{};
break;
      default:
        break;
}

    }
    _offer_t(const _offer_t &source) : effect_(source.effect_) {
      switch (effect_)
{
      case (int32_t)ManageOfferEffect::CREATED:
      case (int32_t)ManageOfferEffect::UPDATED:
new(&offer_) OfferEntry(source.offer_);
break;
      default:
        break;
}

    }
    _offer_t(_offer_t &&source) : effect_(source.effect_) {
      switch (effect_)
{
      case (int32_t)ManageOfferEffect::CREATED:
      case (int32_t)ManageOfferEffect::UPDATED:
new(&offer_) OfferEntry(std::move(source.offer_));
break;
      default:
        break;
}

    }
    ~_offer_t() {
switch (effect_)
{
    case (int32_t)ManageOfferEffect::CREATED:
    case (int32_t)ManageOfferEffect::UPDATED:
offer_.~OfferEntry();
break;
    default:
      break;
}
}

    _offer_t &operator=(const _offer_t &source) {
      if (effect_ == source.effect_)
{
switch (effect_)
{
      case (int32_t)ManageOfferEffect::CREATED:
      case (int32_t)ManageOfferEffect::UPDATED:
offer_ = source.offer_;
break;
      default:
        break;
}
}
else {this->~_offer_t();
      effect_ = source.effect_;
switch (effect_)
{
      case (int32_t)ManageOfferEffect::CREATED:
      case (int32_t)ManageOfferEffect::UPDATED:
new(&offer_) OfferEntry(source.offer_);
break;
      default:
        break;
}
}
      return *this;
    }
    _offer_t &operator=(_offer_t &&source) {
      if (effect_ == source.effect_)
{
switch (effect_)
{
      case (int32_t)ManageOfferEffect::CREATED:
      case (int32_t)ManageOfferEffect::UPDATED:
offer_ = std::move(source.offer_);
break;
      default:
        break;
}
}
else {this->~_offer_t();
      effect_ = std::move(source.effect_);
switch (effect_)
{
      case (int32_t)ManageOfferEffect::CREATED:
      case (int32_t)ManageOfferEffect::UPDATED:
new(&offer_) OfferEntry(std::move(source.offer_));
break;
      default:
        break;
}
}
      return *this;
    }

    ManageOfferEffect effect() const { return ManageOfferEffect(effect_); }
    _offer_t &effect(ManageOfferEffect _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    OfferEntry &offer() {
      if (_xdr_field_number(effect_) == 1)
        return offer_;
      throw xdr::xdr_wrong_union("_offer_t: offer accessed when not selected");
    }
    const OfferEntry &offer() const {
      if (_xdr_field_number(effect_) == 1)
        return offer_;
      throw xdr::xdr_wrong_union("_offer_t: offer accessed when not selected");
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

  xdr::xvector<ClaimOfferAtom> offersClaimed{};
  AssetCode baseAsset{};
  AssetCode quoteAsset{};
  _offer_t offer{};
  _ext_t ext{};

  ManageOfferSuccessResult() = default;
  template<typename _offersClaimed_T,
           typename _baseAsset_T,
           typename _quoteAsset_T,
           typename _offer_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xvector<ClaimOfferAtom>, _offersClaimed_T>::value
                          && std::is_constructible<AssetCode, _baseAsset_T>::value
                          && std::is_constructible<AssetCode, _quoteAsset_T>::value
                          && std::is_constructible<_offer_t, _offer_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ManageOfferSuccessResult(_offersClaimed_T &&_offersClaimed,
                                    _baseAsset_T &&_baseAsset,
                                    _quoteAsset_T &&_quoteAsset,
                                    _offer_T &&_offer,
                                    _ext_T &&_ext)
    : offersClaimed(std::forward<_offersClaimed_T>(_offersClaimed)),
      baseAsset(std::forward<_baseAsset_T>(_baseAsset)),
      quoteAsset(std::forward<_quoteAsset_T>(_quoteAsset)),
      offer(std::forward<_offer_T>(_offer)),
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

struct ManageOfferResult : xdr::xdr_abstract {
  struct _physicalPriceRestriction_t  : xdr::xdr_abstract {
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

    int64 physicalPrice{};
    _ext_t ext{};

    _physicalPriceRestriction_t() = default;
    template<typename _physicalPrice_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<int64, _physicalPrice_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _physicalPriceRestriction_t(_physicalPrice_T &&_physicalPrice,
                                         _ext_T &&_ext)
      : physicalPrice(std::forward<_physicalPrice_T>(_physicalPrice)),
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
  struct _currentPriceRestriction_t  : xdr::xdr_abstract {
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

    int64 currentPrice{};
    _ext_t ext{};

    _currentPriceRestriction_t() = default;
    template<typename _currentPrice_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<int64, _currentPrice_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _currentPriceRestriction_t(_currentPrice_T &&_currentPrice,
                                        _ext_T &&_ext)
      : currentPrice(std::forward<_currentPrice_T>(_currentPrice)),
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

  using _xdr_case_type = xdr::xdr_traits<ManageOfferResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    ManageOfferSuccessResult success_;
    _physicalPriceRestriction_t physicalPriceRestriction_;
    _currentPriceRestriction_t currentPriceRestriction_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<ManageOfferResultCode> &_xdr_case_values() {
    static const std::vector<ManageOfferResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)ManageOfferResultCode::SUCCESS ? 1
      : which == (int32_t)ManageOfferResultCode::PHYSICAL_PRICE_RESTRICTION ? 2
      : which == (int32_t)ManageOfferResultCode::CURRENT_PRICE_RESTRICTION ? 3
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)ManageOfferResultCode::SUCCESS:
      _f(&ManageOfferResult::success_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)ManageOfferResultCode::PHYSICAL_PRICE_RESTRICTION:
      _f(&ManageOfferResult::physicalPriceRestriction_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)ManageOfferResultCode::CURRENT_PRICE_RESTRICTION:
      _f(&ManageOfferResult::currentPriceRestriction_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in ManageOfferResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~ManageOfferResult();
      code_ = which;switch (code_)
{
      case (int32_t)ManageOfferResultCode::SUCCESS:
new(&success_) ManageOfferSuccessResult{};
break;
      case (int32_t)ManageOfferResultCode::PHYSICAL_PRICE_RESTRICTION:
new(&physicalPriceRestriction_) _physicalPriceRestriction_t{};
break;
      case (int32_t)ManageOfferResultCode::CURRENT_PRICE_RESTRICTION:
new(&currentPriceRestriction_) _currentPriceRestriction_t{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit ManageOfferResult(ManageOfferResultCode which = ManageOfferResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)ManageOfferResultCode::SUCCESS:
new(&success_) ManageOfferSuccessResult{};
break;
    case (int32_t)ManageOfferResultCode::PHYSICAL_PRICE_RESTRICTION:
new(&physicalPriceRestriction_) _physicalPriceRestriction_t{};
break;
    case (int32_t)ManageOfferResultCode::CURRENT_PRICE_RESTRICTION:
new(&currentPriceRestriction_) _currentPriceRestriction_t{};
break;
    default:
      break;
}

  }
  ManageOfferResult(const ManageOfferResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManageOfferResultCode::SUCCESS:
new(&success_) ManageOfferSuccessResult(source.success_);
break;
    case (int32_t)ManageOfferResultCode::PHYSICAL_PRICE_RESTRICTION:
new(&physicalPriceRestriction_) _physicalPriceRestriction_t(source.physicalPriceRestriction_);
break;
    case (int32_t)ManageOfferResultCode::CURRENT_PRICE_RESTRICTION:
new(&currentPriceRestriction_) _currentPriceRestriction_t(source.currentPriceRestriction_);
break;
    default:
      break;
}

  }
  ManageOfferResult(ManageOfferResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManageOfferResultCode::SUCCESS:
new(&success_) ManageOfferSuccessResult(std::move(source.success_));
break;
    case (int32_t)ManageOfferResultCode::PHYSICAL_PRICE_RESTRICTION:
new(&physicalPriceRestriction_) _physicalPriceRestriction_t(std::move(source.physicalPriceRestriction_));
break;
    case (int32_t)ManageOfferResultCode::CURRENT_PRICE_RESTRICTION:
new(&currentPriceRestriction_) _currentPriceRestriction_t(std::move(source.currentPriceRestriction_));
break;
    default:
      break;
}

  }
  ~ManageOfferResult() {
switch (code_)
{
  case (int32_t)ManageOfferResultCode::SUCCESS:
success_.~ManageOfferSuccessResult();
break;
  case (int32_t)ManageOfferResultCode::PHYSICAL_PRICE_RESTRICTION:
physicalPriceRestriction_.~_physicalPriceRestriction_t();
break;
  case (int32_t)ManageOfferResultCode::CURRENT_PRICE_RESTRICTION:
currentPriceRestriction_.~_currentPriceRestriction_t();
break;
  default:
    break;
}
}

  ManageOfferResult &operator=(const ManageOfferResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManageOfferResultCode::SUCCESS:
success_ = source.success_;
break;
    case (int32_t)ManageOfferResultCode::PHYSICAL_PRICE_RESTRICTION:
physicalPriceRestriction_ = source.physicalPriceRestriction_;
break;
    case (int32_t)ManageOfferResultCode::CURRENT_PRICE_RESTRICTION:
currentPriceRestriction_ = source.currentPriceRestriction_;
break;
    default:
      break;
}
}
else {this->~ManageOfferResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)ManageOfferResultCode::SUCCESS:
new(&success_) ManageOfferSuccessResult(source.success_);
break;
    case (int32_t)ManageOfferResultCode::PHYSICAL_PRICE_RESTRICTION:
new(&physicalPriceRestriction_) _physicalPriceRestriction_t(source.physicalPriceRestriction_);
break;
    case (int32_t)ManageOfferResultCode::CURRENT_PRICE_RESTRICTION:
new(&currentPriceRestriction_) _currentPriceRestriction_t(source.currentPriceRestriction_);
break;
    default:
      break;
}
}
    return *this;
  }
  ManageOfferResult &operator=(ManageOfferResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManageOfferResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    case (int32_t)ManageOfferResultCode::PHYSICAL_PRICE_RESTRICTION:
physicalPriceRestriction_ = std::move(source.physicalPriceRestriction_);
break;
    case (int32_t)ManageOfferResultCode::CURRENT_PRICE_RESTRICTION:
currentPriceRestriction_ = std::move(source.currentPriceRestriction_);
break;
    default:
      break;
}
}
else {this->~ManageOfferResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)ManageOfferResultCode::SUCCESS:
new(&success_) ManageOfferSuccessResult(std::move(source.success_));
break;
    case (int32_t)ManageOfferResultCode::PHYSICAL_PRICE_RESTRICTION:
new(&physicalPriceRestriction_) _physicalPriceRestriction_t(std::move(source.physicalPriceRestriction_));
break;
    case (int32_t)ManageOfferResultCode::CURRENT_PRICE_RESTRICTION:
new(&currentPriceRestriction_) _currentPriceRestriction_t(std::move(source.currentPriceRestriction_));
break;
    default:
      break;
}
}
    return *this;
  }

  ManageOfferResultCode code() const { return ManageOfferResultCode(code_); }
  ManageOfferResult &code(ManageOfferResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  ManageOfferSuccessResult &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageOfferResult: success accessed when not selected");
  }
  const ManageOfferSuccessResult &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageOfferResult: success accessed when not selected");
  }
  _physicalPriceRestriction_t &physicalPriceRestriction() {
    if (_xdr_field_number(code_) == 2)
      return physicalPriceRestriction_;
    throw xdr::xdr_wrong_union("ManageOfferResult: physicalPriceRestriction accessed when not selected");
  }
  const _physicalPriceRestriction_t &physicalPriceRestriction() const {
    if (_xdr_field_number(code_) == 2)
      return physicalPriceRestriction_;
    throw xdr::xdr_wrong_union("ManageOfferResult: physicalPriceRestriction accessed when not selected");
  }
  _currentPriceRestriction_t &currentPriceRestriction() {
    if (_xdr_field_number(code_) == 3)
      return currentPriceRestriction_;
    throw xdr::xdr_wrong_union("ManageOfferResult: currentPriceRestriction accessed when not selected");
  }
  const _currentPriceRestriction_t &currentPriceRestriction() const {
    if (_xdr_field_number(code_) == 3)
      return currentPriceRestriction_;
    throw xdr::xdr_wrong_union("ManageOfferResult: currentPriceRestriction accessed when not selected");
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

#endif // !__XDR_OPERATION_MANAGE_OFFER_H_INCLUDED__
