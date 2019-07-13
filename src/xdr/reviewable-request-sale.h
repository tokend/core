// -*- C++ -*-
// Automatically generated from reviewable-request-sale.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_REVIEWABLE_REQUEST_SALE_H_INCLUDED__
#define __XDR_REVIEWABLE_REQUEST_SALE_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/ledger-entries-sale.h"

namespace stellar {

struct SaleCreationRequestQuoteAsset  : xdr::xdr_abstract {
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

struct CreateAccountSaleRuleData  : xdr::xdr_abstract {
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

  xdr::pointer<AccountID> accountID{};
  bool forbids{};
  _ext_t ext{};

  CreateAccountSaleRuleData() = default;
  template<typename _accountID_T,
           typename _forbids_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::pointer<AccountID>, _accountID_T>::value
                          && std::is_constructible<bool, _forbids_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateAccountSaleRuleData(_accountID_T &&_accountID,
                                     _forbids_T &&_forbids,
                                     _ext_T &&_ext)
    : accountID(std::forward<_accountID_T>(_accountID)),
      forbids(std::forward<_forbids_T>(_forbids)),
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

struct SaleCreationRequest  : xdr::xdr_abstract {
  struct _ext_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
  private:
    _xdr_case_type v_;
    union {
      xdr::xvector<CreateAccountSaleRuleData> saleRules_;
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
        : which == (int32_t)LedgerVersion::ADD_SALE_WHITELISTS ? 1
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
      case (int32_t)LedgerVersion::ADD_SALE_WHITELISTS:
        _f(&_ext_t::saleRules_, std::forward<_A>(_a)...);
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
new(&saleRules_) xdr::xvector<CreateAccountSaleRuleData>{};
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
new(&saleRules_) xdr::xvector<CreateAccountSaleRuleData>{};
break;
}

    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
      case (int32_t)LedgerVersion::ADD_SALE_WHITELISTS:
new(&saleRules_) xdr::xvector<CreateAccountSaleRuleData>(source.saleRules_);
break;
}

    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
      case (int32_t)LedgerVersion::ADD_SALE_WHITELISTS:
new(&saleRules_) xdr::xvector<CreateAccountSaleRuleData>(std::move(source.saleRules_));
break;
}

    }
    ~_ext_t() {
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
      break;
    case (int32_t)LedgerVersion::ADD_SALE_WHITELISTS:
saleRules_.~xvector<CreateAccountSaleRuleData>();
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
saleRules_ = source.saleRules_;
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
new(&saleRules_) xdr::xvector<CreateAccountSaleRuleData>(source.saleRules_);
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
saleRules_ = std::move(source.saleRules_);
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
new(&saleRules_) xdr::xvector<CreateAccountSaleRuleData>(std::move(source.saleRules_));
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

    xdr::xvector<CreateAccountSaleRuleData> &saleRules() {
      if (_xdr_field_number(v_) == 1)
        return saleRules_;
      throw xdr::xdr_wrong_union("_ext_t: saleRules accessed when not selected");
    }
    const xdr::xvector<CreateAccountSaleRuleData> &saleRules() const {
      if (_xdr_field_number(v_) == 1)
        return saleRules_;
      throw xdr::xdr_wrong_union("_ext_t: saleRules accessed when not selected");
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

#endif // !__XDR_REVIEWABLE_REQUEST_SALE_H_INCLUDED__
