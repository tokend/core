// -*- C++ -*-
// Automatically generated from Stellar-ledger-entries-atomic-swap-bid.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_LEDGER_ENTRIES_ATOMIC_SWAP_BID_H_INCLUDED__
#define __XDR_STELLAR_LEDGER_ENTRIES_ATOMIC_SWAP_BID_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-types.h"

namespace stellar {

struct ASwapBidQuoteAsset {
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
  _ext_t ext{};

  ASwapBidQuoteAsset() = default;
  template<typename _quoteAsset_T,
           typename _price_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<AssetCode, _quoteAsset_T>::value
                          && std::is_constructible<uint64, _price_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ASwapBidQuoteAsset(_quoteAsset_T &&_quoteAsset,
                              _price_T &&_price,
                              _ext_T &&_ext)
    : quoteAsset(std::forward<_quoteAsset_T>(_quoteAsset)),
      price(std::forward<_price_T>(_price)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ASwapBidQuoteAsset::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ASwapBidQuoteAsset::_ext_t;
  using case_type = ::stellar::ASwapBidQuoteAsset::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ASwapBidQuoteAsset::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ASwapBidQuoteAsset::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ASwapBidQuoteAsset::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ASwapBidQuoteAsset>
  : xdr_struct_base<field_ptr<::stellar::ASwapBidQuoteAsset,
                              decltype(::stellar::ASwapBidQuoteAsset::quoteAsset),
                              &::stellar::ASwapBidQuoteAsset::quoteAsset>,
                    field_ptr<::stellar::ASwapBidQuoteAsset,
                              decltype(::stellar::ASwapBidQuoteAsset::price),
                              &::stellar::ASwapBidQuoteAsset::price>,
                    field_ptr<::stellar::ASwapBidQuoteAsset,
                              decltype(::stellar::ASwapBidQuoteAsset::ext),
                              &::stellar::ASwapBidQuoteAsset::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ASwapBidQuoteAsset &obj) {
    archive(ar, obj.quoteAsset, "quoteAsset");
    archive(ar, obj.price, "price");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ASwapBidQuoteAsset &obj) {
    archive(ar, obj.quoteAsset, "quoteAsset");
    archive(ar, obj.price, "price");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct AtomicSwapBidEntry {
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
  AccountID ownerID{};
  AssetCode baseAsset{};
  BalanceID baseBalance{};
  uint64 amount{};
  uint64 lockedAmount{};
  uint64 createdAt{};
  bool isCancelled{};
  longstring details{};
  xdr::xvector<ASwapBidQuoteAsset> quoteAssets{};
  _ext_t ext{};

  AtomicSwapBidEntry() = default;
  template<typename _bidID_T,
           typename _ownerID_T,
           typename _baseAsset_T,
           typename _baseBalance_T,
           typename _amount_T,
           typename _lockedAmount_T,
           typename _createdAt_T,
           typename _isCancelled_T,
           typename _details_T,
           typename _quoteAssets_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _bidID_T>::value
                          && std::is_constructible<AccountID, _ownerID_T>::value
                          && std::is_constructible<AssetCode, _baseAsset_T>::value
                          && std::is_constructible<BalanceID, _baseBalance_T>::value
                          && std::is_constructible<uint64, _amount_T>::value
                          && std::is_constructible<uint64, _lockedAmount_T>::value
                          && std::is_constructible<uint64, _createdAt_T>::value
                          && std::is_constructible<bool, _isCancelled_T>::value
                          && std::is_constructible<longstring, _details_T>::value
                          && std::is_constructible<xdr::xvector<ASwapBidQuoteAsset>, _quoteAssets_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit AtomicSwapBidEntry(_bidID_T &&_bidID,
                              _ownerID_T &&_ownerID,
                              _baseAsset_T &&_baseAsset,
                              _baseBalance_T &&_baseBalance,
                              _amount_T &&_amount,
                              _lockedAmount_T &&_lockedAmount,
                              _createdAt_T &&_createdAt,
                              _isCancelled_T &&_isCancelled,
                              _details_T &&_details,
                              _quoteAssets_T &&_quoteAssets,
                              _ext_T &&_ext)
    : bidID(std::forward<_bidID_T>(_bidID)),
      ownerID(std::forward<_ownerID_T>(_ownerID)),
      baseAsset(std::forward<_baseAsset_T>(_baseAsset)),
      baseBalance(std::forward<_baseBalance_T>(_baseBalance)),
      amount(std::forward<_amount_T>(_amount)),
      lockedAmount(std::forward<_lockedAmount_T>(_lockedAmount)),
      createdAt(std::forward<_createdAt_T>(_createdAt)),
      isCancelled(std::forward<_isCancelled_T>(_isCancelled)),
      details(std::forward<_details_T>(_details)),
      quoteAssets(std::forward<_quoteAssets_T>(_quoteAssets)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::AtomicSwapBidEntry::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::AtomicSwapBidEntry::_ext_t;
  using case_type = ::stellar::AtomicSwapBidEntry::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::AtomicSwapBidEntry::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::AtomicSwapBidEntry::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::AtomicSwapBidEntry::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::AtomicSwapBidEntry>
  : xdr_struct_base<field_ptr<::stellar::AtomicSwapBidEntry,
                              decltype(::stellar::AtomicSwapBidEntry::bidID),
                              &::stellar::AtomicSwapBidEntry::bidID>,
                    field_ptr<::stellar::AtomicSwapBidEntry,
                              decltype(::stellar::AtomicSwapBidEntry::ownerID),
                              &::stellar::AtomicSwapBidEntry::ownerID>,
                    field_ptr<::stellar::AtomicSwapBidEntry,
                              decltype(::stellar::AtomicSwapBidEntry::baseAsset),
                              &::stellar::AtomicSwapBidEntry::baseAsset>,
                    field_ptr<::stellar::AtomicSwapBidEntry,
                              decltype(::stellar::AtomicSwapBidEntry::baseBalance),
                              &::stellar::AtomicSwapBidEntry::baseBalance>,
                    field_ptr<::stellar::AtomicSwapBidEntry,
                              decltype(::stellar::AtomicSwapBidEntry::amount),
                              &::stellar::AtomicSwapBidEntry::amount>,
                    field_ptr<::stellar::AtomicSwapBidEntry,
                              decltype(::stellar::AtomicSwapBidEntry::lockedAmount),
                              &::stellar::AtomicSwapBidEntry::lockedAmount>,
                    field_ptr<::stellar::AtomicSwapBidEntry,
                              decltype(::stellar::AtomicSwapBidEntry::createdAt),
                              &::stellar::AtomicSwapBidEntry::createdAt>,
                    field_ptr<::stellar::AtomicSwapBidEntry,
                              decltype(::stellar::AtomicSwapBidEntry::isCancelled),
                              &::stellar::AtomicSwapBidEntry::isCancelled>,
                    field_ptr<::stellar::AtomicSwapBidEntry,
                              decltype(::stellar::AtomicSwapBidEntry::details),
                              &::stellar::AtomicSwapBidEntry::details>,
                    field_ptr<::stellar::AtomicSwapBidEntry,
                              decltype(::stellar::AtomicSwapBidEntry::quoteAssets),
                              &::stellar::AtomicSwapBidEntry::quoteAssets>,
                    field_ptr<::stellar::AtomicSwapBidEntry,
                              decltype(::stellar::AtomicSwapBidEntry::ext),
                              &::stellar::AtomicSwapBidEntry::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::AtomicSwapBidEntry &obj) {
    archive(ar, obj.bidID, "bidID");
    archive(ar, obj.ownerID, "ownerID");
    archive(ar, obj.baseAsset, "baseAsset");
    archive(ar, obj.baseBalance, "baseBalance");
    archive(ar, obj.amount, "amount");
    archive(ar, obj.lockedAmount, "lockedAmount");
    archive(ar, obj.createdAt, "createdAt");
    archive(ar, obj.isCancelled, "isCancelled");
    archive(ar, obj.details, "details");
    archive(ar, obj.quoteAssets, "quoteAssets");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::AtomicSwapBidEntry &obj) {
    archive(ar, obj.bidID, "bidID");
    archive(ar, obj.ownerID, "ownerID");
    archive(ar, obj.baseAsset, "baseAsset");
    archive(ar, obj.baseBalance, "baseBalance");
    archive(ar, obj.amount, "amount");
    archive(ar, obj.lockedAmount, "lockedAmount");
    archive(ar, obj.createdAt, "createdAt");
    archive(ar, obj.isCancelled, "isCancelled");
    archive(ar, obj.details, "details");
    archive(ar, obj.quoteAssets, "quoteAssets");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

}

#endif // !__XDR_STELLAR_LEDGER_ENTRIES_ATOMIC_SWAP_BID_H_INCLUDED__
