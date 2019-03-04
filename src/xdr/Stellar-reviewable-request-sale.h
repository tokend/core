// -*- C++ -*-
// Automatically generated from Stellar-reviewable-request-sale.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_REVIEWABLE_REQUEST_SALE_H_INCLUDED__
#define __XDR_STELLAR_REVIEWABLE_REQUEST_SALE_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-types.h"
#include "xdr/Stellar-ledger-entries-sale.h"

namespace stellar {

struct SaleCreationRequestQuoteAsset {
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

  SaleCreationRequestQuoteAsset() = default;
  template<typename _quoteAsset_T,
           typename _price_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<AssetCode, _quoteAsset_T>::value
                          && std::is_constructible<uint64, _price_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit SaleCreationRequestQuoteAsset(_quoteAsset_T &&_quoteAsset,
                                         _price_T &&_price,
                                         _ext_T &&_ext)
    : quoteAsset(std::forward<_quoteAsset_T>(_quoteAsset)),
      price(std::forward<_price_T>(_price)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SaleCreationRequestQuoteAsset::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::SaleCreationRequestQuoteAsset::_ext_t;
  using case_type = ::stellar::SaleCreationRequestQuoteAsset::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::SaleCreationRequestQuoteAsset::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SaleCreationRequestQuoteAsset::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SaleCreationRequestQuoteAsset::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::SaleCreationRequestQuoteAsset>
  : xdr_struct_base<field_ptr<::stellar::SaleCreationRequestQuoteAsset,
                              decltype(::stellar::SaleCreationRequestQuoteAsset::quoteAsset),
                              &::stellar::SaleCreationRequestQuoteAsset::quoteAsset>,
                    field_ptr<::stellar::SaleCreationRequestQuoteAsset,
                              decltype(::stellar::SaleCreationRequestQuoteAsset::price),
                              &::stellar::SaleCreationRequestQuoteAsset::price>,
                    field_ptr<::stellar::SaleCreationRequestQuoteAsset,
                              decltype(::stellar::SaleCreationRequestQuoteAsset::ext),
                              &::stellar::SaleCreationRequestQuoteAsset::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SaleCreationRequestQuoteAsset &obj) {
    archive(ar, obj.quoteAsset, "quoteAsset");
    archive(ar, obj.price, "price");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SaleCreationRequestQuoteAsset &obj) {
    archive(ar, obj.quoteAsset, "quoteAsset");
    archive(ar, obj.price, "price");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SaleCreationRequest {
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

  uint64 saleType{};
  AssetCode baseAsset{};
  AssetCode defaultQuoteAsset{};
  uint64 startTime{};
  uint64 endTime{};
  uint64 softCap{};
  uint64 hardCap{};
  longstring creatorDetails{};
  SaleTypeExt saleTypeExt{};
  uint64 requiredBaseAssetForHardCap{};
  uint32 sequenceNumber{};
  xdr::xvector<SaleCreationRequestQuoteAsset,100> quoteAssets{};
  _ext_t ext{};

  SaleCreationRequest() = default;
  template<typename _saleType_T,
           typename _baseAsset_T,
           typename _defaultQuoteAsset_T,
           typename _startTime_T,
           typename _endTime_T,
           typename _softCap_T,
           typename _hardCap_T,
           typename _creatorDetails_T,
           typename _saleTypeExt_T,
           typename _requiredBaseAssetForHardCap_T,
           typename _sequenceNumber_T,
           typename _quoteAssets_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _saleType_T>::value
                          && std::is_constructible<AssetCode, _baseAsset_T>::value
                          && std::is_constructible<AssetCode, _defaultQuoteAsset_T>::value
                          && std::is_constructible<uint64, _startTime_T>::value
                          && std::is_constructible<uint64, _endTime_T>::value
                          && std::is_constructible<uint64, _softCap_T>::value
                          && std::is_constructible<uint64, _hardCap_T>::value
                          && std::is_constructible<longstring, _creatorDetails_T>::value
                          && std::is_constructible<SaleTypeExt, _saleTypeExt_T>::value
                          && std::is_constructible<uint64, _requiredBaseAssetForHardCap_T>::value
                          && std::is_constructible<uint32, _sequenceNumber_T>::value
                          && std::is_constructible<xdr::xvector<SaleCreationRequestQuoteAsset,100>, _quoteAssets_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit SaleCreationRequest(_saleType_T &&_saleType,
                               _baseAsset_T &&_baseAsset,
                               _defaultQuoteAsset_T &&_defaultQuoteAsset,
                               _startTime_T &&_startTime,
                               _endTime_T &&_endTime,
                               _softCap_T &&_softCap,
                               _hardCap_T &&_hardCap,
                               _creatorDetails_T &&_creatorDetails,
                               _saleTypeExt_T &&_saleTypeExt,
                               _requiredBaseAssetForHardCap_T &&_requiredBaseAssetForHardCap,
                               _sequenceNumber_T &&_sequenceNumber,
                               _quoteAssets_T &&_quoteAssets,
                               _ext_T &&_ext)
    : saleType(std::forward<_saleType_T>(_saleType)),
      baseAsset(std::forward<_baseAsset_T>(_baseAsset)),
      defaultQuoteAsset(std::forward<_defaultQuoteAsset_T>(_defaultQuoteAsset)),
      startTime(std::forward<_startTime_T>(_startTime)),
      endTime(std::forward<_endTime_T>(_endTime)),
      softCap(std::forward<_softCap_T>(_softCap)),
      hardCap(std::forward<_hardCap_T>(_hardCap)),
      creatorDetails(std::forward<_creatorDetails_T>(_creatorDetails)),
      saleTypeExt(std::forward<_saleTypeExt_T>(_saleTypeExt)),
      requiredBaseAssetForHardCap(std::forward<_requiredBaseAssetForHardCap_T>(_requiredBaseAssetForHardCap)),
      sequenceNumber(std::forward<_sequenceNumber_T>(_sequenceNumber)),
      quoteAssets(std::forward<_quoteAssets_T>(_quoteAssets)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SaleCreationRequest::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::SaleCreationRequest::_ext_t;
  using case_type = ::stellar::SaleCreationRequest::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::SaleCreationRequest::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SaleCreationRequest::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SaleCreationRequest::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::SaleCreationRequest>
  : xdr_struct_base<field_ptr<::stellar::SaleCreationRequest,
                              decltype(::stellar::SaleCreationRequest::saleType),
                              &::stellar::SaleCreationRequest::saleType>,
                    field_ptr<::stellar::SaleCreationRequest,
                              decltype(::stellar::SaleCreationRequest::baseAsset),
                              &::stellar::SaleCreationRequest::baseAsset>,
                    field_ptr<::stellar::SaleCreationRequest,
                              decltype(::stellar::SaleCreationRequest::defaultQuoteAsset),
                              &::stellar::SaleCreationRequest::defaultQuoteAsset>,
                    field_ptr<::stellar::SaleCreationRequest,
                              decltype(::stellar::SaleCreationRequest::startTime),
                              &::stellar::SaleCreationRequest::startTime>,
                    field_ptr<::stellar::SaleCreationRequest,
                              decltype(::stellar::SaleCreationRequest::endTime),
                              &::stellar::SaleCreationRequest::endTime>,
                    field_ptr<::stellar::SaleCreationRequest,
                              decltype(::stellar::SaleCreationRequest::softCap),
                              &::stellar::SaleCreationRequest::softCap>,
                    field_ptr<::stellar::SaleCreationRequest,
                              decltype(::stellar::SaleCreationRequest::hardCap),
                              &::stellar::SaleCreationRequest::hardCap>,
                    field_ptr<::stellar::SaleCreationRequest,
                              decltype(::stellar::SaleCreationRequest::creatorDetails),
                              &::stellar::SaleCreationRequest::creatorDetails>,
                    field_ptr<::stellar::SaleCreationRequest,
                              decltype(::stellar::SaleCreationRequest::saleTypeExt),
                              &::stellar::SaleCreationRequest::saleTypeExt>,
                    field_ptr<::stellar::SaleCreationRequest,
                              decltype(::stellar::SaleCreationRequest::requiredBaseAssetForHardCap),
                              &::stellar::SaleCreationRequest::requiredBaseAssetForHardCap>,
                    field_ptr<::stellar::SaleCreationRequest,
                              decltype(::stellar::SaleCreationRequest::sequenceNumber),
                              &::stellar::SaleCreationRequest::sequenceNumber>,
                    field_ptr<::stellar::SaleCreationRequest,
                              decltype(::stellar::SaleCreationRequest::quoteAssets),
                              &::stellar::SaleCreationRequest::quoteAssets>,
                    field_ptr<::stellar::SaleCreationRequest,
                              decltype(::stellar::SaleCreationRequest::ext),
                              &::stellar::SaleCreationRequest::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SaleCreationRequest &obj) {
    archive(ar, obj.saleType, "saleType");
    archive(ar, obj.baseAsset, "baseAsset");
    archive(ar, obj.defaultQuoteAsset, "defaultQuoteAsset");
    archive(ar, obj.startTime, "startTime");
    archive(ar, obj.endTime, "endTime");
    archive(ar, obj.softCap, "softCap");
    archive(ar, obj.hardCap, "hardCap");
    archive(ar, obj.creatorDetails, "creatorDetails");
    archive(ar, obj.saleTypeExt, "saleTypeExt");
    archive(ar, obj.requiredBaseAssetForHardCap, "requiredBaseAssetForHardCap");
    archive(ar, obj.sequenceNumber, "sequenceNumber");
    archive(ar, obj.quoteAssets, "quoteAssets");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SaleCreationRequest &obj) {
    archive(ar, obj.saleType, "saleType");
    archive(ar, obj.baseAsset, "baseAsset");
    archive(ar, obj.defaultQuoteAsset, "defaultQuoteAsset");
    archive(ar, obj.startTime, "startTime");
    archive(ar, obj.endTime, "endTime");
    archive(ar, obj.softCap, "softCap");
    archive(ar, obj.hardCap, "hardCap");
    archive(ar, obj.creatorDetails, "creatorDetails");
    archive(ar, obj.saleTypeExt, "saleTypeExt");
    archive(ar, obj.requiredBaseAssetForHardCap, "requiredBaseAssetForHardCap");
    archive(ar, obj.sequenceNumber, "sequenceNumber");
    archive(ar, obj.quoteAssets, "quoteAssets");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

}

#endif // !__XDR_STELLAR_REVIEWABLE_REQUEST_SALE_H_INCLUDED__
