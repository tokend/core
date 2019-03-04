// -*- C++ -*-
// Automatically generated from Stellar-operation-payout.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_OPERATION_PAYOUT_H_INCLUDED__
#define __XDR_STELLAR_OPERATION_PAYOUT_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-ledger-entries.h"

namespace stellar {

struct PayoutOp {
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

  AssetCode asset{};
  BalanceID sourceBalanceID{};
  uint64 maxPayoutAmount{};
  uint64 minPayoutAmount{};
  uint64 minAssetHolderAmount{};
  Fee fee{};
  _ext_t ext{};

  PayoutOp() = default;
  template<typename _asset_T,
           typename _sourceBalanceID_T,
           typename _maxPayoutAmount_T,
           typename _minPayoutAmount_T,
           typename _minAssetHolderAmount_T,
           typename _fee_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<AssetCode, _asset_T>::value
                          && std::is_constructible<BalanceID, _sourceBalanceID_T>::value
                          && std::is_constructible<uint64, _maxPayoutAmount_T>::value
                          && std::is_constructible<uint64, _minPayoutAmount_T>::value
                          && std::is_constructible<uint64, _minAssetHolderAmount_T>::value
                          && std::is_constructible<Fee, _fee_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit PayoutOp(_asset_T &&_asset,
                    _sourceBalanceID_T &&_sourceBalanceID,
                    _maxPayoutAmount_T &&_maxPayoutAmount,
                    _minPayoutAmount_T &&_minPayoutAmount,
                    _minAssetHolderAmount_T &&_minAssetHolderAmount,
                    _fee_T &&_fee,
                    _ext_T &&_ext)
    : asset(std::forward<_asset_T>(_asset)),
      sourceBalanceID(std::forward<_sourceBalanceID_T>(_sourceBalanceID)),
      maxPayoutAmount(std::forward<_maxPayoutAmount_T>(_maxPayoutAmount)),
      minPayoutAmount(std::forward<_minPayoutAmount_T>(_minPayoutAmount)),
      minAssetHolderAmount(std::forward<_minAssetHolderAmount_T>(_minAssetHolderAmount)),
      fee(std::forward<_fee_T>(_fee)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::PayoutOp::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::PayoutOp::_ext_t;
  using case_type = ::stellar::PayoutOp::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::PayoutOp::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::PayoutOp::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::PayoutOp::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::PayoutOp>
  : xdr_struct_base<field_ptr<::stellar::PayoutOp,
                              decltype(::stellar::PayoutOp::asset),
                              &::stellar::PayoutOp::asset>,
                    field_ptr<::stellar::PayoutOp,
                              decltype(::stellar::PayoutOp::sourceBalanceID),
                              &::stellar::PayoutOp::sourceBalanceID>,
                    field_ptr<::stellar::PayoutOp,
                              decltype(::stellar::PayoutOp::maxPayoutAmount),
                              &::stellar::PayoutOp::maxPayoutAmount>,
                    field_ptr<::stellar::PayoutOp,
                              decltype(::stellar::PayoutOp::minPayoutAmount),
                              &::stellar::PayoutOp::minPayoutAmount>,
                    field_ptr<::stellar::PayoutOp,
                              decltype(::stellar::PayoutOp::minAssetHolderAmount),
                              &::stellar::PayoutOp::minAssetHolderAmount>,
                    field_ptr<::stellar::PayoutOp,
                              decltype(::stellar::PayoutOp::fee),
                              &::stellar::PayoutOp::fee>,
                    field_ptr<::stellar::PayoutOp,
                              decltype(::stellar::PayoutOp::ext),
                              &::stellar::PayoutOp::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::PayoutOp &obj) {
    archive(ar, obj.asset, "asset");
    archive(ar, obj.sourceBalanceID, "sourceBalanceID");
    archive(ar, obj.maxPayoutAmount, "maxPayoutAmount");
    archive(ar, obj.minPayoutAmount, "minPayoutAmount");
    archive(ar, obj.minAssetHolderAmount, "minAssetHolderAmount");
    archive(ar, obj.fee, "fee");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::PayoutOp &obj) {
    archive(ar, obj.asset, "asset");
    archive(ar, obj.sourceBalanceID, "sourceBalanceID");
    archive(ar, obj.maxPayoutAmount, "maxPayoutAmount");
    archive(ar, obj.minPayoutAmount, "minPayoutAmount");
    archive(ar, obj.minAssetHolderAmount, "minAssetHolderAmount");
    archive(ar, obj.fee, "fee");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum class PayoutResultCode : std::int32_t {
  SUCCESS = 0,
  INVALID_AMOUNT = -1,
  INVALID_ASSET = -2,
  ASSET_NOT_FOUND = -3,
  ASSET_NOT_TRANSFERABLE = -4,
  BALANCE_NOT_FOUND = -5,
  INSUFFICIENT_FEE_AMOUNT = -6,
  FEE_EXCEEDS_ACTUAL_AMOUNT = -7,
  TOTAL_FEE_OVERFLOW = -8,
  UNDERFUNDED = -9,
  HOLDERS_NOT_FOUND = -10,
  MIN_AMOUNT_TOO_BIG = -11,
  LINE_FULL = -12,
  STATS_OVERFLOW = -13,
  LIMITS_EXCEEDED = -14,
  INCORRECT_PRECISION = -15,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::PayoutResultCode>
  : xdr_integral_base<::stellar::PayoutResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::PayoutResultCode val) {
    switch (val) {
    case ::stellar::PayoutResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::PayoutResultCode::INVALID_AMOUNT:
      return "INVALID_AMOUNT";
    case ::stellar::PayoutResultCode::INVALID_ASSET:
      return "INVALID_ASSET";
    case ::stellar::PayoutResultCode::ASSET_NOT_FOUND:
      return "ASSET_NOT_FOUND";
    case ::stellar::PayoutResultCode::ASSET_NOT_TRANSFERABLE:
      return "ASSET_NOT_TRANSFERABLE";
    case ::stellar::PayoutResultCode::BALANCE_NOT_FOUND:
      return "BALANCE_NOT_FOUND";
    case ::stellar::PayoutResultCode::INSUFFICIENT_FEE_AMOUNT:
      return "INSUFFICIENT_FEE_AMOUNT";
    case ::stellar::PayoutResultCode::FEE_EXCEEDS_ACTUAL_AMOUNT:
      return "FEE_EXCEEDS_ACTUAL_AMOUNT";
    case ::stellar::PayoutResultCode::TOTAL_FEE_OVERFLOW:
      return "TOTAL_FEE_OVERFLOW";
    case ::stellar::PayoutResultCode::UNDERFUNDED:
      return "UNDERFUNDED";
    case ::stellar::PayoutResultCode::HOLDERS_NOT_FOUND:
      return "HOLDERS_NOT_FOUND";
    case ::stellar::PayoutResultCode::MIN_AMOUNT_TOO_BIG:
      return "MIN_AMOUNT_TOO_BIG";
    case ::stellar::PayoutResultCode::LINE_FULL:
      return "LINE_FULL";
    case ::stellar::PayoutResultCode::STATS_OVERFLOW:
      return "STATS_OVERFLOW";
    case ::stellar::PayoutResultCode::LIMITS_EXCEEDED:
      return "LIMITS_EXCEEDED";
    case ::stellar::PayoutResultCode::INCORRECT_PRECISION:
      return "INCORRECT_PRECISION";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::PayoutResultCode::SUCCESS,
      (int32_t)::stellar::PayoutResultCode::INVALID_AMOUNT,
      (int32_t)::stellar::PayoutResultCode::INVALID_ASSET,
      (int32_t)::stellar::PayoutResultCode::ASSET_NOT_FOUND,
      (int32_t)::stellar::PayoutResultCode::ASSET_NOT_TRANSFERABLE,
      (int32_t)::stellar::PayoutResultCode::BALANCE_NOT_FOUND,
      (int32_t)::stellar::PayoutResultCode::INSUFFICIENT_FEE_AMOUNT,
      (int32_t)::stellar::PayoutResultCode::FEE_EXCEEDS_ACTUAL_AMOUNT,
      (int32_t)::stellar::PayoutResultCode::TOTAL_FEE_OVERFLOW,
      (int32_t)::stellar::PayoutResultCode::UNDERFUNDED,
      (int32_t)::stellar::PayoutResultCode::HOLDERS_NOT_FOUND,
      (int32_t)::stellar::PayoutResultCode::MIN_AMOUNT_TOO_BIG,
      (int32_t)::stellar::PayoutResultCode::LINE_FULL,
      (int32_t)::stellar::PayoutResultCode::STATS_OVERFLOW,
      (int32_t)::stellar::PayoutResultCode::LIMITS_EXCEEDED,
      (int32_t)::stellar::PayoutResultCode::INCORRECT_PRECISION
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct PayoutResponse {
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

  AccountID receiverID{};
  BalanceID receiverBalanceID{};
  uint64 receivedAmount{};
  _ext_t ext{};

  PayoutResponse() = default;
  template<typename _receiverID_T,
           typename _receiverBalanceID_T,
           typename _receivedAmount_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<AccountID, _receiverID_T>::value
                          && std::is_constructible<BalanceID, _receiverBalanceID_T>::value
                          && std::is_constructible<uint64, _receivedAmount_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit PayoutResponse(_receiverID_T &&_receiverID,
                          _receiverBalanceID_T &&_receiverBalanceID,
                          _receivedAmount_T &&_receivedAmount,
                          _ext_T &&_ext)
    : receiverID(std::forward<_receiverID_T>(_receiverID)),
      receiverBalanceID(std::forward<_receiverBalanceID_T>(_receiverBalanceID)),
      receivedAmount(std::forward<_receivedAmount_T>(_receivedAmount)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::PayoutResponse::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::PayoutResponse::_ext_t;
  using case_type = ::stellar::PayoutResponse::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::PayoutResponse::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::PayoutResponse::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::PayoutResponse::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::PayoutResponse>
  : xdr_struct_base<field_ptr<::stellar::PayoutResponse,
                              decltype(::stellar::PayoutResponse::receiverID),
                              &::stellar::PayoutResponse::receiverID>,
                    field_ptr<::stellar::PayoutResponse,
                              decltype(::stellar::PayoutResponse::receiverBalanceID),
                              &::stellar::PayoutResponse::receiverBalanceID>,
                    field_ptr<::stellar::PayoutResponse,
                              decltype(::stellar::PayoutResponse::receivedAmount),
                              &::stellar::PayoutResponse::receivedAmount>,
                    field_ptr<::stellar::PayoutResponse,
                              decltype(::stellar::PayoutResponse::ext),
                              &::stellar::PayoutResponse::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::PayoutResponse &obj) {
    archive(ar, obj.receiverID, "receiverID");
    archive(ar, obj.receiverBalanceID, "receiverBalanceID");
    archive(ar, obj.receivedAmount, "receivedAmount");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::PayoutResponse &obj) {
    archive(ar, obj.receiverID, "receiverID");
    archive(ar, obj.receiverBalanceID, "receiverBalanceID");
    archive(ar, obj.receivedAmount, "receivedAmount");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct PayoutSuccessResult {
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

  xdr::xvector<PayoutResponse> payoutResponses{};
  uint64 actualPayoutAmount{};
  Fee actualFee{};
  _ext_t ext{};

  PayoutSuccessResult() = default;
  template<typename _payoutResponses_T,
           typename _actualPayoutAmount_T,
           typename _actualFee_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xvector<PayoutResponse>, _payoutResponses_T>::value
                          && std::is_constructible<uint64, _actualPayoutAmount_T>::value
                          && std::is_constructible<Fee, _actualFee_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit PayoutSuccessResult(_payoutResponses_T &&_payoutResponses,
                               _actualPayoutAmount_T &&_actualPayoutAmount,
                               _actualFee_T &&_actualFee,
                               _ext_T &&_ext)
    : payoutResponses(std::forward<_payoutResponses_T>(_payoutResponses)),
      actualPayoutAmount(std::forward<_actualPayoutAmount_T>(_actualPayoutAmount)),
      actualFee(std::forward<_actualFee_T>(_actualFee)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::PayoutSuccessResult::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::PayoutSuccessResult::_ext_t;
  using case_type = ::stellar::PayoutSuccessResult::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::PayoutSuccessResult::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::PayoutSuccessResult::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::PayoutSuccessResult::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::PayoutSuccessResult>
  : xdr_struct_base<field_ptr<::stellar::PayoutSuccessResult,
                              decltype(::stellar::PayoutSuccessResult::payoutResponses),
                              &::stellar::PayoutSuccessResult::payoutResponses>,
                    field_ptr<::stellar::PayoutSuccessResult,
                              decltype(::stellar::PayoutSuccessResult::actualPayoutAmount),
                              &::stellar::PayoutSuccessResult::actualPayoutAmount>,
                    field_ptr<::stellar::PayoutSuccessResult,
                              decltype(::stellar::PayoutSuccessResult::actualFee),
                              &::stellar::PayoutSuccessResult::actualFee>,
                    field_ptr<::stellar::PayoutSuccessResult,
                              decltype(::stellar::PayoutSuccessResult::ext),
                              &::stellar::PayoutSuccessResult::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::PayoutSuccessResult &obj) {
    archive(ar, obj.payoutResponses, "payoutResponses");
    archive(ar, obj.actualPayoutAmount, "actualPayoutAmount");
    archive(ar, obj.actualFee, "actualFee");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::PayoutSuccessResult &obj) {
    archive(ar, obj.payoutResponses, "payoutResponses");
    archive(ar, obj.actualPayoutAmount, "actualPayoutAmount");
    archive(ar, obj.actualFee, "actualFee");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct PayoutResult {
  using _xdr_case_type = xdr::xdr_traits<PayoutResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    PayoutSuccessResult success_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = true;
  static const std::vector<PayoutResultCode> &_xdr_case_values() {
    static const std::vector<PayoutResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)PayoutResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)PayoutResultCode::SUCCESS:
      _f(&PayoutResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in PayoutResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~PayoutResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit PayoutResult(PayoutResultCode which = PayoutResultCode{}) : code_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  PayoutResult(const PayoutResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  PayoutResult(PayoutResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~PayoutResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  PayoutResult &operator=(const PayoutResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~PayoutResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  PayoutResult &operator=(PayoutResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~PayoutResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  PayoutResultCode code() const { return PayoutResultCode(code_); }
  PayoutResult &code(PayoutResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  PayoutSuccessResult &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("PayoutResult: success accessed when not selected");
  }
  const PayoutSuccessResult &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("PayoutResult: success accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::PayoutResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::PayoutResult;
  using case_type = ::stellar::PayoutResult::_xdr_case_type;
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

  static std::size_t serial_size(const ::stellar::PayoutResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in PayoutResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::PayoutResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in PayoutResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::PayoutResult &obj) {
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

#endif // !__XDR_STELLAR_OPERATION_PAYOUT_H_INCLUDED__
