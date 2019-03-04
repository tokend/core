// -*- C++ -*-
// Automatically generated from Stellar-operation-manage-offer.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_OPERATION_MANAGE_OFFER_H_INCLUDED__
#define __XDR_STELLAR_OPERATION_MANAGE_OFFER_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-ledger-entries.h"

namespace stellar {

struct ManageOfferOp {
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageOfferOp::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageOfferOp::_ext_t;
  using case_type = ::stellar::ManageOfferOp::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageOfferOp::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageOfferOp::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageOfferOp::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageOfferOp>
  : xdr_struct_base<field_ptr<::stellar::ManageOfferOp,
                              decltype(::stellar::ManageOfferOp::baseBalance),
                              &::stellar::ManageOfferOp::baseBalance>,
                    field_ptr<::stellar::ManageOfferOp,
                              decltype(::stellar::ManageOfferOp::quoteBalance),
                              &::stellar::ManageOfferOp::quoteBalance>,
                    field_ptr<::stellar::ManageOfferOp,
                              decltype(::stellar::ManageOfferOp::isBuy),
                              &::stellar::ManageOfferOp::isBuy>,
                    field_ptr<::stellar::ManageOfferOp,
                              decltype(::stellar::ManageOfferOp::amount),
                              &::stellar::ManageOfferOp::amount>,
                    field_ptr<::stellar::ManageOfferOp,
                              decltype(::stellar::ManageOfferOp::price),
                              &::stellar::ManageOfferOp::price>,
                    field_ptr<::stellar::ManageOfferOp,
                              decltype(::stellar::ManageOfferOp::fee),
                              &::stellar::ManageOfferOp::fee>,
                    field_ptr<::stellar::ManageOfferOp,
                              decltype(::stellar::ManageOfferOp::offerID),
                              &::stellar::ManageOfferOp::offerID>,
                    field_ptr<::stellar::ManageOfferOp,
                              decltype(::stellar::ManageOfferOp::orderBookID),
                              &::stellar::ManageOfferOp::orderBookID>,
                    field_ptr<::stellar::ManageOfferOp,
                              decltype(::stellar::ManageOfferOp::ext),
                              &::stellar::ManageOfferOp::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageOfferOp &obj) {
    archive(ar, obj.baseBalance, "baseBalance");
    archive(ar, obj.quoteBalance, "quoteBalance");
    archive(ar, obj.isBuy, "isBuy");
    archive(ar, obj.amount, "amount");
    archive(ar, obj.price, "price");
    archive(ar, obj.fee, "fee");
    archive(ar, obj.offerID, "offerID");
    archive(ar, obj.orderBookID, "orderBookID");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageOfferOp &obj) {
    archive(ar, obj.baseBalance, "baseBalance");
    archive(ar, obj.quoteBalance, "quoteBalance");
    archive(ar, obj.isBuy, "isBuy");
    archive(ar, obj.amount, "amount");
    archive(ar, obj.price, "price");
    archive(ar, obj.fee, "fee");
    archive(ar, obj.offerID, "offerID");
    archive(ar, obj.orderBookID, "orderBookID");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageOfferResultCode>
  : xdr_integral_base<::stellar::ManageOfferResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
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
      (int32_t)::stellar::ManageOfferResultCode::INCORRECT_AMOUNT_PRECISION
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
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
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

struct ClaimOfferAtom {
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ClaimOfferAtom::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ClaimOfferAtom::_ext_t;
  using case_type = ::stellar::ClaimOfferAtom::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ClaimOfferAtom::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ClaimOfferAtom::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ClaimOfferAtom::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ClaimOfferAtom>
  : xdr_struct_base<field_ptr<::stellar::ClaimOfferAtom,
                              decltype(::stellar::ClaimOfferAtom::bAccountID),
                              &::stellar::ClaimOfferAtom::bAccountID>,
                    field_ptr<::stellar::ClaimOfferAtom,
                              decltype(::stellar::ClaimOfferAtom::offerID),
                              &::stellar::ClaimOfferAtom::offerID>,
                    field_ptr<::stellar::ClaimOfferAtom,
                              decltype(::stellar::ClaimOfferAtom::baseAmount),
                              &::stellar::ClaimOfferAtom::baseAmount>,
                    field_ptr<::stellar::ClaimOfferAtom,
                              decltype(::stellar::ClaimOfferAtom::quoteAmount),
                              &::stellar::ClaimOfferAtom::quoteAmount>,
                    field_ptr<::stellar::ClaimOfferAtom,
                              decltype(::stellar::ClaimOfferAtom::bFeePaid),
                              &::stellar::ClaimOfferAtom::bFeePaid>,
                    field_ptr<::stellar::ClaimOfferAtom,
                              decltype(::stellar::ClaimOfferAtom::aFeePaid),
                              &::stellar::ClaimOfferAtom::aFeePaid>,
                    field_ptr<::stellar::ClaimOfferAtom,
                              decltype(::stellar::ClaimOfferAtom::baseBalance),
                              &::stellar::ClaimOfferAtom::baseBalance>,
                    field_ptr<::stellar::ClaimOfferAtom,
                              decltype(::stellar::ClaimOfferAtom::quoteBalance),
                              &::stellar::ClaimOfferAtom::quoteBalance>,
                    field_ptr<::stellar::ClaimOfferAtom,
                              decltype(::stellar::ClaimOfferAtom::currentPrice),
                              &::stellar::ClaimOfferAtom::currentPrice>,
                    field_ptr<::stellar::ClaimOfferAtom,
                              decltype(::stellar::ClaimOfferAtom::ext),
                              &::stellar::ClaimOfferAtom::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ClaimOfferAtom &obj) {
    archive(ar, obj.bAccountID, "bAccountID");
    archive(ar, obj.offerID, "offerID");
    archive(ar, obj.baseAmount, "baseAmount");
    archive(ar, obj.quoteAmount, "quoteAmount");
    archive(ar, obj.bFeePaid, "bFeePaid");
    archive(ar, obj.aFeePaid, "aFeePaid");
    archive(ar, obj.baseBalance, "baseBalance");
    archive(ar, obj.quoteBalance, "quoteBalance");
    archive(ar, obj.currentPrice, "currentPrice");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ClaimOfferAtom &obj) {
    archive(ar, obj.bAccountID, "bAccountID");
    archive(ar, obj.offerID, "offerID");
    archive(ar, obj.baseAmount, "baseAmount");
    archive(ar, obj.quoteAmount, "quoteAmount");
    archive(ar, obj.bFeePaid, "bFeePaid");
    archive(ar, obj.aFeePaid, "aFeePaid");
    archive(ar, obj.baseBalance, "baseBalance");
    archive(ar, obj.quoteBalance, "quoteBalance");
    archive(ar, obj.currentPrice, "currentPrice");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ManageOfferSuccessResult {
  struct _offer_t {
    using _xdr_case_type = xdr::xdr_traits<ManageOfferEffect>::case_type;
  private:
    _xdr_case_type effect_;
    union {
      OfferEntry offer_;
    };

  public:
    static Constexpr const bool _xdr_has_default_case = true;
    static const std::vector<ManageOfferEffect> &_xdr_case_values() {
      static const std::vector<ManageOfferEffect> _xdr_disc_vec {};
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
        effect_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, effect_, *this);
      }
      else
        effect_ = which;
    }
    explicit _offer_t(ManageOfferEffect which = ManageOfferEffect{}) : effect_((int32_t)which) {
      _xdr_with_mem_ptr(xdr::field_constructor, effect_, *this);
    }
    _offer_t(const _offer_t &source) : effect_(source.effect_) {
      _xdr_with_mem_ptr(xdr::field_constructor, effect_, *this, source);
    }
    _offer_t(_offer_t &&source) : effect_(source.effect_) {
      _xdr_with_mem_ptr(xdr::field_constructor, effect_, *this,
                        std::move(source));
    }
    ~_offer_t() { _xdr_with_mem_ptr(xdr::field_destructor, effect_, *this); }
    _offer_t &operator=(const _offer_t &source) {
      if (_xdr_field_number(effect_)
          == _xdr_field_number(source.effect_))
        _xdr_with_mem_ptr(xdr::field_assigner, effect_, *this, source);
      else {
        this->~_offer_t();
        effect_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.effect_, *this, source);
      }
      effect_ = source.effect_;
      return *this;
    }
    _offer_t &operator=(_offer_t &&source) {
      if (_xdr_field_number(effect_)
           == _xdr_field_number(source.effect_))
        _xdr_with_mem_ptr(xdr::field_assigner, effect_, *this,
                          std::move(source));
      else {
        this->~_offer_t();
        effect_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.effect_, *this,
                          std::move(source));
      }
      effect_ = source.effect_;
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageOfferSuccessResult::_offer_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageOfferSuccessResult::_offer_t;
  using case_type = ::stellar::ManageOfferSuccessResult::_offer_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().effect());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "offer";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageOfferSuccessResult::_offer_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of effect in _offer_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageOfferSuccessResult::_offer_t &obj) {
    xdr::archive(ar, obj.effect(), "effect");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.effect(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of effect in _offer_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageOfferSuccessResult::_offer_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "effect");
    obj.effect(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.effect(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageOfferSuccessResult::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageOfferSuccessResult::_ext_t;
  using case_type = ::stellar::ManageOfferSuccessResult::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageOfferSuccessResult::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageOfferSuccessResult::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageOfferSuccessResult::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageOfferSuccessResult>
  : xdr_struct_base<field_ptr<::stellar::ManageOfferSuccessResult,
                              decltype(::stellar::ManageOfferSuccessResult::offersClaimed),
                              &::stellar::ManageOfferSuccessResult::offersClaimed>,
                    field_ptr<::stellar::ManageOfferSuccessResult,
                              decltype(::stellar::ManageOfferSuccessResult::baseAsset),
                              &::stellar::ManageOfferSuccessResult::baseAsset>,
                    field_ptr<::stellar::ManageOfferSuccessResult,
                              decltype(::stellar::ManageOfferSuccessResult::quoteAsset),
                              &::stellar::ManageOfferSuccessResult::quoteAsset>,
                    field_ptr<::stellar::ManageOfferSuccessResult,
                              decltype(::stellar::ManageOfferSuccessResult::offer),
                              &::stellar::ManageOfferSuccessResult::offer>,
                    field_ptr<::stellar::ManageOfferSuccessResult,
                              decltype(::stellar::ManageOfferSuccessResult::ext),
                              &::stellar::ManageOfferSuccessResult::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageOfferSuccessResult &obj) {
    archive(ar, obj.offersClaimed, "offersClaimed");
    archive(ar, obj.baseAsset, "baseAsset");
    archive(ar, obj.quoteAsset, "quoteAsset");
    archive(ar, obj.offer, "offer");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageOfferSuccessResult &obj) {
    archive(ar, obj.offersClaimed, "offersClaimed");
    archive(ar, obj.baseAsset, "baseAsset");
    archive(ar, obj.quoteAsset, "quoteAsset");
    archive(ar, obj.offer, "offer");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ManageOfferResult {
  struct _physicalPriceRestriction_t {
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
  };
  struct _currentPriceRestriction_t {
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
  static Constexpr const bool _xdr_has_default_case = true;
  static const std::vector<ManageOfferResultCode> &_xdr_case_values() {
    static const std::vector<ManageOfferResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit ManageOfferResult(ManageOfferResultCode which = ManageOfferResultCode{}) : code_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  ManageOfferResult(const ManageOfferResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  ManageOfferResult(ManageOfferResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~ManageOfferResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  ManageOfferResult &operator=(const ManageOfferResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~ManageOfferResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  ManageOfferResult &operator=(ManageOfferResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~ManageOfferResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
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
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageOfferResult::_physicalPriceRestriction_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageOfferResult::_physicalPriceRestriction_t::_ext_t;
  using case_type = ::stellar::ManageOfferResult::_physicalPriceRestriction_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageOfferResult::_physicalPriceRestriction_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageOfferResult::_physicalPriceRestriction_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageOfferResult::_physicalPriceRestriction_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageOfferResult::_physicalPriceRestriction_t>
  : xdr_struct_base<field_ptr<::stellar::ManageOfferResult::_physicalPriceRestriction_t,
                              decltype(::stellar::ManageOfferResult::_physicalPriceRestriction_t::physicalPrice),
                              &::stellar::ManageOfferResult::_physicalPriceRestriction_t::physicalPrice>,
                    field_ptr<::stellar::ManageOfferResult::_physicalPriceRestriction_t,
                              decltype(::stellar::ManageOfferResult::_physicalPriceRestriction_t::ext),
                              &::stellar::ManageOfferResult::_physicalPriceRestriction_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageOfferResult::_physicalPriceRestriction_t &obj) {
    archive(ar, obj.physicalPrice, "physicalPrice");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageOfferResult::_physicalPriceRestriction_t &obj) {
    archive(ar, obj.physicalPrice, "physicalPrice");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageOfferResult::_currentPriceRestriction_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageOfferResult::_currentPriceRestriction_t::_ext_t;
  using case_type = ::stellar::ManageOfferResult::_currentPriceRestriction_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageOfferResult::_currentPriceRestriction_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageOfferResult::_currentPriceRestriction_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageOfferResult::_currentPriceRestriction_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageOfferResult::_currentPriceRestriction_t>
  : xdr_struct_base<field_ptr<::stellar::ManageOfferResult::_currentPriceRestriction_t,
                              decltype(::stellar::ManageOfferResult::_currentPriceRestriction_t::currentPrice),
                              &::stellar::ManageOfferResult::_currentPriceRestriction_t::currentPrice>,
                    field_ptr<::stellar::ManageOfferResult::_currentPriceRestriction_t,
                              decltype(::stellar::ManageOfferResult::_currentPriceRestriction_t::ext),
                              &::stellar::ManageOfferResult::_currentPriceRestriction_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageOfferResult::_currentPriceRestriction_t &obj) {
    archive(ar, obj.currentPrice, "currentPrice");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageOfferResult::_currentPriceRestriction_t &obj) {
    archive(ar, obj.currentPrice, "currentPrice");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageOfferResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageOfferResult;
  using case_type = ::stellar::ManageOfferResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "success";
    case 2:
      return "physicalPriceRestriction";
    case 3:
      return "currentPriceRestriction";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageOfferResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in ManageOfferResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageOfferResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in ManageOfferResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageOfferResult &obj) {
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

#endif // !__XDR_STELLAR_OPERATION_MANAGE_OFFER_H_INCLUDED__
