// -*- C++ -*-
// Automatically generated from resource-account-rule.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_RESOURCE_ACCOUNT_RULE_H_INCLUDED__
#define __XDR_RESOURCE_ACCOUNT_RULE_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/ledger-keys.h"
#include "xdr/ledger-entries-reviewable-request.h"

namespace stellar {

struct ReviewableRequestResource : xdr::xdr_abstract {
  struct _createSale_t  : xdr::xdr_abstract {
    uint64 type{};
    EmptyExt ext{};

    _createSale_t() = default;
    template<typename _type_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _type_T>::value
                            && std::is_constructible<EmptyExt, _ext_T>::value
                           >::type>
    explicit _createSale_t(_type_T &&_type,
                           _ext_T &&_ext)
      : type(std::forward<_type_T>(_type)),
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
  struct _createIssuance_t  : xdr::xdr_abstract {
    AssetCode assetCode{};
    uint64 assetType{};
    EmptyExt ext{};

    _createIssuance_t() = default;
    template<typename _assetCode_T,
             typename _assetType_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<AssetCode, _assetCode_T>::value
                            && std::is_constructible<uint64, _assetType_T>::value
                            && std::is_constructible<EmptyExt, _ext_T>::value
                           >::type>
    explicit _createIssuance_t(_assetCode_T &&_assetCode,
                               _assetType_T &&_assetType,
                               _ext_T &&_ext)
      : assetCode(std::forward<_assetCode_T>(_assetCode)),
        assetType(std::forward<_assetType_T>(_assetType)),
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
  struct _createWithdraw_t  : xdr::xdr_abstract {
    AssetCode assetCode{};
    uint64 assetType{};
    EmptyExt ext{};

    _createWithdraw_t() = default;
    template<typename _assetCode_T,
             typename _assetType_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<AssetCode, _assetCode_T>::value
                            && std::is_constructible<uint64, _assetType_T>::value
                            && std::is_constructible<EmptyExt, _ext_T>::value
                           >::type>
    explicit _createWithdraw_t(_assetCode_T &&_assetCode,
                               _assetType_T &&_assetType,
                               _ext_T &&_ext)
      : assetCode(std::forward<_assetCode_T>(_assetCode)),
        assetType(std::forward<_assetType_T>(_assetType)),
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
  struct _createAtomicSwapAskExt_t : xdr::xdr_abstract {
    struct _createAtomicSwapAsk_t  : xdr::xdr_abstract {
      AssetCode assetCode{};
      uint64 assetType{};
      EmptyExt ext{};

      _createAtomicSwapAsk_t() = default;
      template<typename _assetCode_T,
               typename _assetType_T,
               typename _ext_T,
               typename = typename
               std::enable_if<std::is_constructible<AssetCode, _assetCode_T>::value
                              && std::is_constructible<uint64, _assetType_T>::value
                              && std::is_constructible<EmptyExt, _ext_T>::value
                             >::type>
      explicit _createAtomicSwapAsk_t(_assetCode_T &&_assetCode,
                                      _assetType_T &&_assetType,
                                      _ext_T &&_ext)
        : assetCode(std::forward<_assetCode_T>(_assetCode)),
          assetType(std::forward<_assetType_T>(_assetType)),
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

    using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
  private:
    _xdr_case_type v_;
    union {
      _createAtomicSwapAsk_t createAtomicSwapAsk_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<LedgerVersion> &_xdr_case_values() {
      static const std::vector<LedgerVersion> _xdr_disc_vec {
        LedgerVersion::EMPTY_VERSION,
        LedgerVersion::ATOMIC_SWAP_RETURNING
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)LedgerVersion::EMPTY_VERSION ? 0
        : which == (int32_t)LedgerVersion::ATOMIC_SWAP_RETURNING ? 1
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
      case (int32_t)LedgerVersion::ATOMIC_SWAP_RETURNING:
        _f(&_createAtomicSwapAskExt_t::createAtomicSwapAsk_, std::forward<_A>(_a)...);
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return v_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of v in _createAtomicSwapAskExt_t");
      if (fnum != _xdr_field_number(v_)) {
        this->~_createAtomicSwapAskExt_t();
        v_ = which;switch (v_)
{
        case (int32_t)LedgerVersion::EMPTY_VERSION:
          break;
        case (int32_t)LedgerVersion::ATOMIC_SWAP_RETURNING:
new(&createAtomicSwapAsk_) _createAtomicSwapAsk_t{};
break;
}

      }
      else
        v_ = which;
    }
    explicit _createAtomicSwapAskExt_t(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
      case (int32_t)LedgerVersion::ATOMIC_SWAP_RETURNING:
new(&createAtomicSwapAsk_) _createAtomicSwapAsk_t{};
break;
}

    }
    _createAtomicSwapAskExt_t(const _createAtomicSwapAskExt_t &source) : v_(source.v_) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
      case (int32_t)LedgerVersion::ATOMIC_SWAP_RETURNING:
new(&createAtomicSwapAsk_) _createAtomicSwapAsk_t(source.createAtomicSwapAsk_);
break;
}

    }
    _createAtomicSwapAskExt_t(_createAtomicSwapAskExt_t &&source) : v_(source.v_) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
      case (int32_t)LedgerVersion::ATOMIC_SWAP_RETURNING:
new(&createAtomicSwapAsk_) _createAtomicSwapAsk_t(std::move(source.createAtomicSwapAsk_));
break;
}

    }
    ~_createAtomicSwapAskExt_t() {
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
      break;
    case (int32_t)LedgerVersion::ATOMIC_SWAP_RETURNING:
createAtomicSwapAsk_.~_createAtomicSwapAsk_t();
break;
}
}

    _createAtomicSwapAskExt_t &operator=(const _createAtomicSwapAskExt_t &source) {
      if (v_ == source.v_)
{
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
      case (int32_t)LedgerVersion::ATOMIC_SWAP_RETURNING:
createAtomicSwapAsk_ = source.createAtomicSwapAsk_;
break;
}
}
else {this->~_createAtomicSwapAskExt_t();
      v_ = source.v_;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
      case (int32_t)LedgerVersion::ATOMIC_SWAP_RETURNING:
new(&createAtomicSwapAsk_) _createAtomicSwapAsk_t(source.createAtomicSwapAsk_);
break;
}
}
      return *this;
    }
    _createAtomicSwapAskExt_t &operator=(_createAtomicSwapAskExt_t &&source) {
      if (v_ == source.v_)
{
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
      case (int32_t)LedgerVersion::ATOMIC_SWAP_RETURNING:
createAtomicSwapAsk_ = std::move(source.createAtomicSwapAsk_);
break;
}
}
else {this->~_createAtomicSwapAskExt_t();
      v_ = std::move(source.v_);
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
      case (int32_t)LedgerVersion::ATOMIC_SWAP_RETURNING:
new(&createAtomicSwapAsk_) _createAtomicSwapAsk_t(std::move(source.createAtomicSwapAsk_));
break;
}
}
      return *this;
    }

    LedgerVersion v() const { return LedgerVersion(v_); }
    _createAtomicSwapAskExt_t &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    _createAtomicSwapAsk_t &createAtomicSwapAsk() {
      if (_xdr_field_number(v_) == 1)
        return createAtomicSwapAsk_;
      throw xdr::xdr_wrong_union("_createAtomicSwapAskExt_t: createAtomicSwapAsk accessed when not selected");
    }
    const _createAtomicSwapAsk_t &createAtomicSwapAsk() const {
      if (_xdr_field_number(v_) == 1)
        return createAtomicSwapAsk_;
      throw xdr::xdr_wrong_union("_createAtomicSwapAskExt_t: createAtomicSwapAsk accessed when not selected");
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
  struct _createAtomicSwapBidExt_t : xdr::xdr_abstract {
    struct _createAtomicSwapBid_t  : xdr::xdr_abstract {
      AssetCode assetCode{};
      uint64 assetType{};
      EmptyExt ext{};

      _createAtomicSwapBid_t() = default;
      template<typename _assetCode_T,
               typename _assetType_T,
               typename _ext_T,
               typename = typename
               std::enable_if<std::is_constructible<AssetCode, _assetCode_T>::value
                              && std::is_constructible<uint64, _assetType_T>::value
                              && std::is_constructible<EmptyExt, _ext_T>::value
                             >::type>
      explicit _createAtomicSwapBid_t(_assetCode_T &&_assetCode,
                                      _assetType_T &&_assetType,
                                      _ext_T &&_ext)
        : assetCode(std::forward<_assetCode_T>(_assetCode)),
          assetType(std::forward<_assetType_T>(_assetType)),
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

    using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
  private:
    _xdr_case_type v_;
    union {
      _createAtomicSwapBid_t createAtomicSwapBid_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<LedgerVersion> &_xdr_case_values() {
      static const std::vector<LedgerVersion> _xdr_disc_vec {
        LedgerVersion::EMPTY_VERSION,
        LedgerVersion::ATOMIC_SWAP_RETURNING
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)LedgerVersion::EMPTY_VERSION ? 0
        : which == (int32_t)LedgerVersion::ATOMIC_SWAP_RETURNING ? 1
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
      case (int32_t)LedgerVersion::ATOMIC_SWAP_RETURNING:
        _f(&_createAtomicSwapBidExt_t::createAtomicSwapBid_, std::forward<_A>(_a)...);
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return v_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of v in _createAtomicSwapBidExt_t");
      if (fnum != _xdr_field_number(v_)) {
        this->~_createAtomicSwapBidExt_t();
        v_ = which;switch (v_)
{
        case (int32_t)LedgerVersion::EMPTY_VERSION:
          break;
        case (int32_t)LedgerVersion::ATOMIC_SWAP_RETURNING:
new(&createAtomicSwapBid_) _createAtomicSwapBid_t{};
break;
}

      }
      else
        v_ = which;
    }
    explicit _createAtomicSwapBidExt_t(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
      case (int32_t)LedgerVersion::ATOMIC_SWAP_RETURNING:
new(&createAtomicSwapBid_) _createAtomicSwapBid_t{};
break;
}

    }
    _createAtomicSwapBidExt_t(const _createAtomicSwapBidExt_t &source) : v_(source.v_) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
      case (int32_t)LedgerVersion::ATOMIC_SWAP_RETURNING:
new(&createAtomicSwapBid_) _createAtomicSwapBid_t(source.createAtomicSwapBid_);
break;
}

    }
    _createAtomicSwapBidExt_t(_createAtomicSwapBidExt_t &&source) : v_(source.v_) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
      case (int32_t)LedgerVersion::ATOMIC_SWAP_RETURNING:
new(&createAtomicSwapBid_) _createAtomicSwapBid_t(std::move(source.createAtomicSwapBid_));
break;
}

    }
    ~_createAtomicSwapBidExt_t() {
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
      break;
    case (int32_t)LedgerVersion::ATOMIC_SWAP_RETURNING:
createAtomicSwapBid_.~_createAtomicSwapBid_t();
break;
}
}

    _createAtomicSwapBidExt_t &operator=(const _createAtomicSwapBidExt_t &source) {
      if (v_ == source.v_)
{
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
      case (int32_t)LedgerVersion::ATOMIC_SWAP_RETURNING:
createAtomicSwapBid_ = source.createAtomicSwapBid_;
break;
}
}
else {this->~_createAtomicSwapBidExt_t();
      v_ = source.v_;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
      case (int32_t)LedgerVersion::ATOMIC_SWAP_RETURNING:
new(&createAtomicSwapBid_) _createAtomicSwapBid_t(source.createAtomicSwapBid_);
break;
}
}
      return *this;
    }
    _createAtomicSwapBidExt_t &operator=(_createAtomicSwapBidExt_t &&source) {
      if (v_ == source.v_)
{
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
      case (int32_t)LedgerVersion::ATOMIC_SWAP_RETURNING:
createAtomicSwapBid_ = std::move(source.createAtomicSwapBid_);
break;
}
}
else {this->~_createAtomicSwapBidExt_t();
      v_ = std::move(source.v_);
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
      case (int32_t)LedgerVersion::ATOMIC_SWAP_RETURNING:
new(&createAtomicSwapBid_) _createAtomicSwapBid_t(std::move(source.createAtomicSwapBid_));
break;
}
}
      return *this;
    }

    LedgerVersion v() const { return LedgerVersion(v_); }
    _createAtomicSwapBidExt_t &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    _createAtomicSwapBid_t &createAtomicSwapBid() {
      if (_xdr_field_number(v_) == 1)
        return createAtomicSwapBid_;
      throw xdr::xdr_wrong_union("_createAtomicSwapBidExt_t: createAtomicSwapBid accessed when not selected");
    }
    const _createAtomicSwapBid_t &createAtomicSwapBid() const {
      if (_xdr_field_number(v_) == 1)
        return createAtomicSwapBid_;
      throw xdr::xdr_wrong_union("_createAtomicSwapBidExt_t: createAtomicSwapBid accessed when not selected");
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
  struct _createPoll_t  : xdr::xdr_abstract {
    uint32 permissionType{};
    EmptyExt ext{};

    _createPoll_t() = default;
    template<typename _permissionType_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint32, _permissionType_T>::value
                            && std::is_constructible<EmptyExt, _ext_T>::value
                           >::type>
    explicit _createPoll_t(_permissionType_T &&_permissionType,
                           _ext_T &&_ext)
      : permissionType(std::forward<_permissionType_T>(_permissionType)),
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

  using _xdr_case_type = xdr::xdr_traits<ReviewableRequestType>::case_type;
private:
  _xdr_case_type requestType_;
  union {
    _createSale_t createSale_;
    _createIssuance_t createIssuance_;
    _createWithdraw_t createWithdraw_;
    _createAtomicSwapAskExt_t createAtomicSwapAskExt_;
    _createAtomicSwapBidExt_t createAtomicSwapBidExt_;
    _createPoll_t createPoll_;
    EmptyExt ext_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<ReviewableRequestType> &_xdr_case_values() {
    static const std::vector<ReviewableRequestType> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)ReviewableRequestType::CREATE_SALE ? 1
      : which == (int32_t)ReviewableRequestType::CREATE_ISSUANCE ? 2
      : which == (int32_t)ReviewableRequestType::CREATE_WITHDRAW ? 3
      : which == (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK ? 4
      : which == (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID ? 5
      : which == (int32_t)ReviewableRequestType::CREATE_POLL ? 6
      : 7;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)ReviewableRequestType::CREATE_SALE:
      _f(&ReviewableRequestResource::createSale_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)ReviewableRequestType::CREATE_ISSUANCE:
      _f(&ReviewableRequestResource::createIssuance_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
      _f(&ReviewableRequestResource::createWithdraw_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
      _f(&ReviewableRequestResource::createAtomicSwapAskExt_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
      _f(&ReviewableRequestResource::createAtomicSwapBidExt_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)ReviewableRequestType::CREATE_POLL:
      _f(&ReviewableRequestResource::createPoll_, std::forward<_A>(_a)...);
      return true;
    default:
      _f(&ReviewableRequestResource::ext_, std::forward<_A>(_a)...);
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return requestType_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of requestType in ReviewableRequestResource");
    if (fnum != _xdr_field_number(requestType_)) {
      this->~ReviewableRequestResource();
      requestType_ = which;switch (requestType_)
{
      case (int32_t)ReviewableRequestType::CREATE_SALE:
new(&createSale_) _createSale_t{};
break;
      case (int32_t)ReviewableRequestType::CREATE_ISSUANCE:
new(&createIssuance_) _createIssuance_t{};
break;
      case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
new(&createWithdraw_) _createWithdraw_t{};
break;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
new(&createAtomicSwapAskExt_) _createAtomicSwapAskExt_t{};
break;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
new(&createAtomicSwapBidExt_) _createAtomicSwapBidExt_t{};
break;
      case (int32_t)ReviewableRequestType::CREATE_POLL:
new(&createPoll_) _createPoll_t{};
break;
      default:
new(&ext_) EmptyExt{};
break;
}

    }
    else
      requestType_ = which;
  }
  explicit ReviewableRequestResource(ReviewableRequestType which = ReviewableRequestType{}) : requestType_((int32_t)which) {
    switch (requestType_)
{
    case (int32_t)ReviewableRequestType::CREATE_SALE:
new(&createSale_) _createSale_t{};
break;
    case (int32_t)ReviewableRequestType::CREATE_ISSUANCE:
new(&createIssuance_) _createIssuance_t{};
break;
    case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
new(&createWithdraw_) _createWithdraw_t{};
break;
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
new(&createAtomicSwapAskExt_) _createAtomicSwapAskExt_t{};
break;
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
new(&createAtomicSwapBidExt_) _createAtomicSwapBidExt_t{};
break;
    case (int32_t)ReviewableRequestType::CREATE_POLL:
new(&createPoll_) _createPoll_t{};
break;
    default:
new(&ext_) EmptyExt{};
break;
}

  }
  ReviewableRequestResource(const ReviewableRequestResource &source) : requestType_(source.requestType_) {
    switch (requestType_)
{
    case (int32_t)ReviewableRequestType::CREATE_SALE:
new(&createSale_) _createSale_t(source.createSale_);
break;
    case (int32_t)ReviewableRequestType::CREATE_ISSUANCE:
new(&createIssuance_) _createIssuance_t(source.createIssuance_);
break;
    case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
new(&createWithdraw_) _createWithdraw_t(source.createWithdraw_);
break;
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
new(&createAtomicSwapAskExt_) _createAtomicSwapAskExt_t(source.createAtomicSwapAskExt_);
break;
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
new(&createAtomicSwapBidExt_) _createAtomicSwapBidExt_t(source.createAtomicSwapBidExt_);
break;
    case (int32_t)ReviewableRequestType::CREATE_POLL:
new(&createPoll_) _createPoll_t(source.createPoll_);
break;
    default:
new(&ext_) EmptyExt(source.ext_);
break;
}

  }
  ReviewableRequestResource(ReviewableRequestResource &&source) : requestType_(source.requestType_) {
    switch (requestType_)
{
    case (int32_t)ReviewableRequestType::CREATE_SALE:
new(&createSale_) _createSale_t(std::move(source.createSale_));
break;
    case (int32_t)ReviewableRequestType::CREATE_ISSUANCE:
new(&createIssuance_) _createIssuance_t(std::move(source.createIssuance_));
break;
    case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
new(&createWithdraw_) _createWithdraw_t(std::move(source.createWithdraw_));
break;
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
new(&createAtomicSwapAskExt_) _createAtomicSwapAskExt_t(std::move(source.createAtomicSwapAskExt_));
break;
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
new(&createAtomicSwapBidExt_) _createAtomicSwapBidExt_t(std::move(source.createAtomicSwapBidExt_));
break;
    case (int32_t)ReviewableRequestType::CREATE_POLL:
new(&createPoll_) _createPoll_t(std::move(source.createPoll_));
break;
    default:
new(&ext_) EmptyExt(std::move(source.ext_));
break;
}

  }
  ~ReviewableRequestResource() {
switch (requestType_)
{
  case (int32_t)ReviewableRequestType::CREATE_SALE:
createSale_.~_createSale_t();
break;
  case (int32_t)ReviewableRequestType::CREATE_ISSUANCE:
createIssuance_.~_createIssuance_t();
break;
  case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
createWithdraw_.~_createWithdraw_t();
break;
  case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
createAtomicSwapAskExt_.~_createAtomicSwapAskExt_t();
break;
  case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
createAtomicSwapBidExt_.~_createAtomicSwapBidExt_t();
break;
  case (int32_t)ReviewableRequestType::CREATE_POLL:
createPoll_.~_createPoll_t();
break;
  default:
ext_.~EmptyExt();
break;
}
}

  ReviewableRequestResource &operator=(const ReviewableRequestResource &source) {
    if (requestType_ == source.requestType_)
{
switch (requestType_)
{
    case (int32_t)ReviewableRequestType::CREATE_SALE:
createSale_ = source.createSale_;
break;
    case (int32_t)ReviewableRequestType::CREATE_ISSUANCE:
createIssuance_ = source.createIssuance_;
break;
    case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
createWithdraw_ = source.createWithdraw_;
break;
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
createAtomicSwapAskExt_ = source.createAtomicSwapAskExt_;
break;
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
createAtomicSwapBidExt_ = source.createAtomicSwapBidExt_;
break;
    case (int32_t)ReviewableRequestType::CREATE_POLL:
createPoll_ = source.createPoll_;
break;
    default:
ext_ = source.ext_;
break;
}
}
else {this->~ReviewableRequestResource();
    requestType_ = source.requestType_;
switch (requestType_)
{
    case (int32_t)ReviewableRequestType::CREATE_SALE:
new(&createSale_) _createSale_t(source.createSale_);
break;
    case (int32_t)ReviewableRequestType::CREATE_ISSUANCE:
new(&createIssuance_) _createIssuance_t(source.createIssuance_);
break;
    case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
new(&createWithdraw_) _createWithdraw_t(source.createWithdraw_);
break;
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
new(&createAtomicSwapAskExt_) _createAtomicSwapAskExt_t(source.createAtomicSwapAskExt_);
break;
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
new(&createAtomicSwapBidExt_) _createAtomicSwapBidExt_t(source.createAtomicSwapBidExt_);
break;
    case (int32_t)ReviewableRequestType::CREATE_POLL:
new(&createPoll_) _createPoll_t(source.createPoll_);
break;
    default:
new(&ext_) EmptyExt(source.ext_);
break;
}
}
    return *this;
  }
  ReviewableRequestResource &operator=(ReviewableRequestResource &&source) {
    if (requestType_ == source.requestType_)
{
switch (requestType_)
{
    case (int32_t)ReviewableRequestType::CREATE_SALE:
createSale_ = std::move(source.createSale_);
break;
    case (int32_t)ReviewableRequestType::CREATE_ISSUANCE:
createIssuance_ = std::move(source.createIssuance_);
break;
    case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
createWithdraw_ = std::move(source.createWithdraw_);
break;
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
createAtomicSwapAskExt_ = std::move(source.createAtomicSwapAskExt_);
break;
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
createAtomicSwapBidExt_ = std::move(source.createAtomicSwapBidExt_);
break;
    case (int32_t)ReviewableRequestType::CREATE_POLL:
createPoll_ = std::move(source.createPoll_);
break;
    default:
ext_ = std::move(source.ext_);
break;
}
}
else {this->~ReviewableRequestResource();
    requestType_ = std::move(source.requestType_);
switch (requestType_)
{
    case (int32_t)ReviewableRequestType::CREATE_SALE:
new(&createSale_) _createSale_t(std::move(source.createSale_));
break;
    case (int32_t)ReviewableRequestType::CREATE_ISSUANCE:
new(&createIssuance_) _createIssuance_t(std::move(source.createIssuance_));
break;
    case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
new(&createWithdraw_) _createWithdraw_t(std::move(source.createWithdraw_));
break;
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
new(&createAtomicSwapAskExt_) _createAtomicSwapAskExt_t(std::move(source.createAtomicSwapAskExt_));
break;
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
new(&createAtomicSwapBidExt_) _createAtomicSwapBidExt_t(std::move(source.createAtomicSwapBidExt_));
break;
    case (int32_t)ReviewableRequestType::CREATE_POLL:
new(&createPoll_) _createPoll_t(std::move(source.createPoll_));
break;
    default:
new(&ext_) EmptyExt(std::move(source.ext_));
break;
}
}
    return *this;
  }

  ReviewableRequestType requestType() const { return ReviewableRequestType(requestType_); }
  ReviewableRequestResource &requestType(ReviewableRequestType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  _createSale_t &createSale() {
    if (_xdr_field_number(requestType_) == 1)
      return createSale_;
    throw xdr::xdr_wrong_union("ReviewableRequestResource: createSale accessed when not selected");
  }
  const _createSale_t &createSale() const {
    if (_xdr_field_number(requestType_) == 1)
      return createSale_;
    throw xdr::xdr_wrong_union("ReviewableRequestResource: createSale accessed when not selected");
  }
  _createIssuance_t &createIssuance() {
    if (_xdr_field_number(requestType_) == 2)
      return createIssuance_;
    throw xdr::xdr_wrong_union("ReviewableRequestResource: createIssuance accessed when not selected");
  }
  const _createIssuance_t &createIssuance() const {
    if (_xdr_field_number(requestType_) == 2)
      return createIssuance_;
    throw xdr::xdr_wrong_union("ReviewableRequestResource: createIssuance accessed when not selected");
  }
  _createWithdraw_t &createWithdraw() {
    if (_xdr_field_number(requestType_) == 3)
      return createWithdraw_;
    throw xdr::xdr_wrong_union("ReviewableRequestResource: createWithdraw accessed when not selected");
  }
  const _createWithdraw_t &createWithdraw() const {
    if (_xdr_field_number(requestType_) == 3)
      return createWithdraw_;
    throw xdr::xdr_wrong_union("ReviewableRequestResource: createWithdraw accessed when not selected");
  }
  _createAtomicSwapAskExt_t &createAtomicSwapAskExt() {
    if (_xdr_field_number(requestType_) == 4)
      return createAtomicSwapAskExt_;
    throw xdr::xdr_wrong_union("ReviewableRequestResource: createAtomicSwapAskExt accessed when not selected");
  }
  const _createAtomicSwapAskExt_t &createAtomicSwapAskExt() const {
    if (_xdr_field_number(requestType_) == 4)
      return createAtomicSwapAskExt_;
    throw xdr::xdr_wrong_union("ReviewableRequestResource: createAtomicSwapAskExt accessed when not selected");
  }
  _createAtomicSwapBidExt_t &createAtomicSwapBidExt() {
    if (_xdr_field_number(requestType_) == 5)
      return createAtomicSwapBidExt_;
    throw xdr::xdr_wrong_union("ReviewableRequestResource: createAtomicSwapBidExt accessed when not selected");
  }
  const _createAtomicSwapBidExt_t &createAtomicSwapBidExt() const {
    if (_xdr_field_number(requestType_) == 5)
      return createAtomicSwapBidExt_;
    throw xdr::xdr_wrong_union("ReviewableRequestResource: createAtomicSwapBidExt accessed when not selected");
  }
  _createPoll_t &createPoll() {
    if (_xdr_field_number(requestType_) == 6)
      return createPoll_;
    throw xdr::xdr_wrong_union("ReviewableRequestResource: createPoll accessed when not selected");
  }
  const _createPoll_t &createPoll() const {
    if (_xdr_field_number(requestType_) == 6)
      return createPoll_;
    throw xdr::xdr_wrong_union("ReviewableRequestResource: createPoll accessed when not selected");
  }
  EmptyExt &ext() {
    if (_xdr_field_number(requestType_) == 7)
      return ext_;
    throw xdr::xdr_wrong_union("ReviewableRequestResource: ext accessed when not selected");
  }
  const EmptyExt &ext() const {
    if (_xdr_field_number(requestType_) == 7)
      return ext_;
    throw xdr::xdr_wrong_union("ReviewableRequestResource: ext accessed when not selected");
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

struct AccountRuleResource : xdr::xdr_abstract {
  struct _asset_t  : xdr::xdr_abstract {
    AssetCode assetCode{};
    uint64 assetType{};
    EmptyExt ext{};

    _asset_t() = default;
    template<typename _assetCode_T,
             typename _assetType_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<AssetCode, _assetCode_T>::value
                            && std::is_constructible<uint64, _assetType_T>::value
                            && std::is_constructible<EmptyExt, _ext_T>::value
                           >::type>
    explicit _asset_t(_assetCode_T &&_assetCode,
                      _assetType_T &&_assetType,
                      _ext_T &&_ext)
      : assetCode(std::forward<_assetCode_T>(_assetCode)),
        assetType(std::forward<_assetType_T>(_assetType)),
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
  struct _reviewableRequest_t  : xdr::xdr_abstract {
    ReviewableRequestResource details{};
    EmptyExt ext{};

    _reviewableRequest_t() = default;
    template<typename _details_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<ReviewableRequestResource, _details_T>::value
                            && std::is_constructible<EmptyExt, _ext_T>::value
                           >::type>
    explicit _reviewableRequest_t(_details_T &&_details,
                                  _ext_T &&_ext)
      : details(std::forward<_details_T>(_details)),
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
  struct _offer_t  : xdr::xdr_abstract {
    uint64 baseAssetType{};
    uint64 quoteAssetType{};
    AssetCode baseAssetCode{};
    AssetCode quoteAssetCode{};
    bool isBuy{};
    EmptyExt ext{};

    _offer_t() = default;
    template<typename _baseAssetType_T,
             typename _quoteAssetType_T,
             typename _baseAssetCode_T,
             typename _quoteAssetCode_T,
             typename _isBuy_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _baseAssetType_T>::value
                            && std::is_constructible<uint64, _quoteAssetType_T>::value
                            && std::is_constructible<AssetCode, _baseAssetCode_T>::value
                            && std::is_constructible<AssetCode, _quoteAssetCode_T>::value
                            && std::is_constructible<bool, _isBuy_T>::value
                            && std::is_constructible<EmptyExt, _ext_T>::value
                           >::type>
    explicit _offer_t(_baseAssetType_T &&_baseAssetType,
                      _quoteAssetType_T &&_quoteAssetType,
                      _baseAssetCode_T &&_baseAssetCode,
                      _quoteAssetCode_T &&_quoteAssetCode,
                      _isBuy_T &&_isBuy,
                      _ext_T &&_ext)
      : baseAssetType(std::forward<_baseAssetType_T>(_baseAssetType)),
        quoteAssetType(std::forward<_quoteAssetType_T>(_quoteAssetType)),
        baseAssetCode(std::forward<_baseAssetCode_T>(_baseAssetCode)),
        quoteAssetCode(std::forward<_quoteAssetCode_T>(_quoteAssetCode)),
        isBuy(std::forward<_isBuy_T>(_isBuy)),
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
  struct _sale_t  : xdr::xdr_abstract {
    uint64 saleID{};
    uint64 saleType{};
    EmptyExt ext{};

    _sale_t() = default;
    template<typename _saleID_T,
             typename _saleType_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _saleID_T>::value
                            && std::is_constructible<uint64, _saleType_T>::value
                            && std::is_constructible<EmptyExt, _ext_T>::value
                           >::type>
    explicit _sale_t(_saleID_T &&_saleID,
                     _saleType_T &&_saleType,
                     _ext_T &&_ext)
      : saleID(std::forward<_saleID_T>(_saleID)),
        saleType(std::forward<_saleType_T>(_saleType)),
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
  struct _atomicSwapAsk_t  : xdr::xdr_abstract {
    uint64 assetType{};
    AssetCode assetCode{};
    EmptyExt ext{};

    _atomicSwapAsk_t() = default;
    template<typename _assetType_T,
             typename _assetCode_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _assetType_T>::value
                            && std::is_constructible<AssetCode, _assetCode_T>::value
                            && std::is_constructible<EmptyExt, _ext_T>::value
                           >::type>
    explicit _atomicSwapAsk_t(_assetType_T &&_assetType,
                              _assetCode_T &&_assetCode,
                              _ext_T &&_ext)
      : assetType(std::forward<_assetType_T>(_assetType)),
        assetCode(std::forward<_assetCode_T>(_assetCode)),
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
  struct _keyValue_t  : xdr::xdr_abstract {
    longstring keyPrefix{};
    EmptyExt ext{};

    _keyValue_t() = default;
    template<typename _keyPrefix_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<longstring, _keyPrefix_T>::value
                            && std::is_constructible<EmptyExt, _ext_T>::value
                           >::type>
    explicit _keyValue_t(_keyPrefix_T &&_keyPrefix,
                         _ext_T &&_ext)
      : keyPrefix(std::forward<_keyPrefix_T>(_keyPrefix)),
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
  struct _poll_t  : xdr::xdr_abstract {
    uint64 pollID{};
    uint32 permissionType{};
    EmptyExt ext{};

    _poll_t() = default;
    template<typename _pollID_T,
             typename _permissionType_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _pollID_T>::value
                            && std::is_constructible<uint32, _permissionType_T>::value
                            && std::is_constructible<EmptyExt, _ext_T>::value
                           >::type>
    explicit _poll_t(_pollID_T &&_pollID,
                     _permissionType_T &&_permissionType,
                     _ext_T &&_ext)
      : pollID(std::forward<_pollID_T>(_pollID)),
        permissionType(std::forward<_permissionType_T>(_permissionType)),
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
  struct _vote_t  : xdr::xdr_abstract {
    uint64 pollID{};
    uint32 permissionType{};
    EmptyExt ext{};

    _vote_t() = default;
    template<typename _pollID_T,
             typename _permissionType_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _pollID_T>::value
                            && std::is_constructible<uint32, _permissionType_T>::value
                            && std::is_constructible<EmptyExt, _ext_T>::value
                           >::type>
    explicit _vote_t(_pollID_T &&_pollID,
                     _permissionType_T &&_permissionType,
                     _ext_T &&_ext)
      : pollID(std::forward<_pollID_T>(_pollID)),
        permissionType(std::forward<_permissionType_T>(_permissionType)),
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
  struct _initiateKYCRecovery_t  : xdr::xdr_abstract {
    uint64 roleID{};
    EmptyExt ext{};

    _initiateKYCRecovery_t() = default;
    template<typename _roleID_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _roleID_T>::value
                            && std::is_constructible<EmptyExt, _ext_T>::value
                           >::type>
    explicit _initiateKYCRecovery_t(_roleID_T &&_roleID,
                                    _ext_T &&_ext)
      : roleID(std::forward<_roleID_T>(_roleID)),
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
  struct _accountSpecificRuleExt_t : xdr::xdr_abstract {
    struct _accountSpecificRule_t  : xdr::xdr_abstract {
      LedgerKey ledgerKey{};
      EmptyExt ext{};

      _accountSpecificRule_t() = default;
      template<typename _ledgerKey_T,
               typename _ext_T,
               typename = typename
               std::enable_if<std::is_constructible<LedgerKey, _ledgerKey_T>::value
                              && std::is_constructible<EmptyExt, _ext_T>::value
                             >::type>
      explicit _accountSpecificRule_t(_ledgerKey_T &&_ledgerKey,
                                      _ext_T &&_ext)
        : ledgerKey(std::forward<_ledgerKey_T>(_ledgerKey)),
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

    using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
  private:
    _xdr_case_type v_;
    union {
      _accountSpecificRule_t accountSpecificRule_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<LedgerVersion> &_xdr_case_values() {
      static const std::vector<LedgerVersion> _xdr_disc_vec {
        LedgerVersion::EMPTY_VERSION,
        LedgerVersion::ADD_ACC_SPECIFIC_RULE_RESOURCE
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)LedgerVersion::EMPTY_VERSION ? 0
        : which == (int32_t)LedgerVersion::ADD_ACC_SPECIFIC_RULE_RESOURCE ? 1
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
      case (int32_t)LedgerVersion::ADD_ACC_SPECIFIC_RULE_RESOURCE:
        _f(&_accountSpecificRuleExt_t::accountSpecificRule_, std::forward<_A>(_a)...);
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return v_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of v in _accountSpecificRuleExt_t");
      if (fnum != _xdr_field_number(v_)) {
        this->~_accountSpecificRuleExt_t();
        v_ = which;switch (v_)
{
        case (int32_t)LedgerVersion::EMPTY_VERSION:
          break;
        case (int32_t)LedgerVersion::ADD_ACC_SPECIFIC_RULE_RESOURCE:
new(&accountSpecificRule_) _accountSpecificRule_t{};
break;
}

      }
      else
        v_ = which;
    }
    explicit _accountSpecificRuleExt_t(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
      case (int32_t)LedgerVersion::ADD_ACC_SPECIFIC_RULE_RESOURCE:
new(&accountSpecificRule_) _accountSpecificRule_t{};
break;
}

    }
    _accountSpecificRuleExt_t(const _accountSpecificRuleExt_t &source) : v_(source.v_) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
      case (int32_t)LedgerVersion::ADD_ACC_SPECIFIC_RULE_RESOURCE:
new(&accountSpecificRule_) _accountSpecificRule_t(source.accountSpecificRule_);
break;
}

    }
    _accountSpecificRuleExt_t(_accountSpecificRuleExt_t &&source) : v_(source.v_) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
      case (int32_t)LedgerVersion::ADD_ACC_SPECIFIC_RULE_RESOURCE:
new(&accountSpecificRule_) _accountSpecificRule_t(std::move(source.accountSpecificRule_));
break;
}

    }
    ~_accountSpecificRuleExt_t() {
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
      break;
    case (int32_t)LedgerVersion::ADD_ACC_SPECIFIC_RULE_RESOURCE:
accountSpecificRule_.~_accountSpecificRule_t();
break;
}
}

    _accountSpecificRuleExt_t &operator=(const _accountSpecificRuleExt_t &source) {
      if (v_ == source.v_)
{
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
      case (int32_t)LedgerVersion::ADD_ACC_SPECIFIC_RULE_RESOURCE:
accountSpecificRule_ = source.accountSpecificRule_;
break;
}
}
else {this->~_accountSpecificRuleExt_t();
      v_ = source.v_;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
      case (int32_t)LedgerVersion::ADD_ACC_SPECIFIC_RULE_RESOURCE:
new(&accountSpecificRule_) _accountSpecificRule_t(source.accountSpecificRule_);
break;
}
}
      return *this;
    }
    _accountSpecificRuleExt_t &operator=(_accountSpecificRuleExt_t &&source) {
      if (v_ == source.v_)
{
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
      case (int32_t)LedgerVersion::ADD_ACC_SPECIFIC_RULE_RESOURCE:
accountSpecificRule_ = std::move(source.accountSpecificRule_);
break;
}
}
else {this->~_accountSpecificRuleExt_t();
      v_ = std::move(source.v_);
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
      case (int32_t)LedgerVersion::ADD_ACC_SPECIFIC_RULE_RESOURCE:
new(&accountSpecificRule_) _accountSpecificRule_t(std::move(source.accountSpecificRule_));
break;
}
}
      return *this;
    }

    LedgerVersion v() const { return LedgerVersion(v_); }
    _accountSpecificRuleExt_t &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    _accountSpecificRule_t &accountSpecificRule() {
      if (_xdr_field_number(v_) == 1)
        return accountSpecificRule_;
      throw xdr::xdr_wrong_union("_accountSpecificRuleExt_t: accountSpecificRule accessed when not selected");
    }
    const _accountSpecificRule_t &accountSpecificRule() const {
      if (_xdr_field_number(v_) == 1)
        return accountSpecificRule_;
      throw xdr::xdr_wrong_union("_accountSpecificRuleExt_t: accountSpecificRule accessed when not selected");
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
  struct _swap_t  : xdr::xdr_abstract {
    AssetCode assetCode{};
    uint64 assetType{};
    EmptyExt ext{};

    _swap_t() = default;
    template<typename _assetCode_T,
             typename _assetType_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<AssetCode, _assetCode_T>::value
                            && std::is_constructible<uint64, _assetType_T>::value
                            && std::is_constructible<EmptyExt, _ext_T>::value
                           >::type>
    explicit _swap_t(_assetCode_T &&_assetCode,
                     _assetType_T &&_assetType,
                     _ext_T &&_ext)
      : assetCode(std::forward<_assetCode_T>(_assetCode)),
        assetType(std::forward<_assetType_T>(_assetType)),
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

  using _xdr_case_type = xdr::xdr_traits<LedgerEntryType>::case_type;
private:
  _xdr_case_type type_;
  union {
    _asset_t asset_;
    _reviewableRequest_t reviewableRequest_;
    _offer_t offer_;
    _sale_t sale_;
    _atomicSwapAsk_t atomicSwapAsk_;
    _keyValue_t keyValue_;
    _poll_t poll_;
    _vote_t vote_;
    _initiateKYCRecovery_t initiateKYCRecovery_;
    _accountSpecificRuleExt_t accountSpecificRuleExt_;
    _swap_t swap_;
    EmptyExt ext_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<LedgerEntryType> &_xdr_case_values() {
    static const std::vector<LedgerEntryType> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)LedgerEntryType::ASSET ? 1
      : which == (int32_t)LedgerEntryType::REVIEWABLE_REQUEST ? 2
      : which == (int32_t)LedgerEntryType::ANY ? 0
      : which == (int32_t)LedgerEntryType::OFFER_ENTRY ? 3
      : which == (int32_t)LedgerEntryType::SALE ? 4
      : which == (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK ? 5
      : which == (int32_t)LedgerEntryType::KEY_VALUE ? 6
      : which == (int32_t)LedgerEntryType::POLL ? 7
      : which == (int32_t)LedgerEntryType::VOTE ? 8
      : which == (int32_t)LedgerEntryType::INITIATE_KYC_RECOVERY ? 9
      : which == (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE ? 10
      : which == (int32_t)LedgerEntryType::SWAP ? 11
      : 12;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)LedgerEntryType::ASSET:
      _f(&AccountRuleResource::asset_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
      _f(&AccountRuleResource::reviewableRequest_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::ANY:
      return true;
    case (int32_t)LedgerEntryType::OFFER_ENTRY:
      _f(&AccountRuleResource::offer_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::SALE:
      _f(&AccountRuleResource::sale_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
      _f(&AccountRuleResource::atomicSwapAsk_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::KEY_VALUE:
      _f(&AccountRuleResource::keyValue_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::POLL:
      _f(&AccountRuleResource::poll_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::VOTE:
      _f(&AccountRuleResource::vote_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::INITIATE_KYC_RECOVERY:
      _f(&AccountRuleResource::initiateKYCRecovery_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
      _f(&AccountRuleResource::accountSpecificRuleExt_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::SWAP:
      _f(&AccountRuleResource::swap_, std::forward<_A>(_a)...);
      return true;
    default:
      _f(&AccountRuleResource::ext_, std::forward<_A>(_a)...);
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return type_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of type in AccountRuleResource");
    if (fnum != _xdr_field_number(type_)) {
      this->~AccountRuleResource();
      type_ = which;switch (type_)
{
      case (int32_t)LedgerEntryType::ASSET:
new(&asset_) _asset_t{};
break;
      case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
new(&reviewableRequest_) _reviewableRequest_t{};
break;
      case (int32_t)LedgerEntryType::ANY:
        break;
      case (int32_t)LedgerEntryType::OFFER_ENTRY:
new(&offer_) _offer_t{};
break;
      case (int32_t)LedgerEntryType::SALE:
new(&sale_) _sale_t{};
break;
      case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
new(&atomicSwapAsk_) _atomicSwapAsk_t{};
break;
      case (int32_t)LedgerEntryType::KEY_VALUE:
new(&keyValue_) _keyValue_t{};
break;
      case (int32_t)LedgerEntryType::POLL:
new(&poll_) _poll_t{};
break;
      case (int32_t)LedgerEntryType::VOTE:
new(&vote_) _vote_t{};
break;
      case (int32_t)LedgerEntryType::INITIATE_KYC_RECOVERY:
new(&initiateKYCRecovery_) _initiateKYCRecovery_t{};
break;
      case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
new(&accountSpecificRuleExt_) _accountSpecificRuleExt_t{};
break;
      case (int32_t)LedgerEntryType::SWAP:
new(&swap_) _swap_t{};
break;
      default:
new(&ext_) EmptyExt{};
break;
}

    }
    else
      type_ = which;
  }
  explicit AccountRuleResource(LedgerEntryType which = LedgerEntryType{}) : type_((int32_t)which) {
    switch (type_)
{
    case (int32_t)LedgerEntryType::ASSET:
new(&asset_) _asset_t{};
break;
    case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
new(&reviewableRequest_) _reviewableRequest_t{};
break;
    case (int32_t)LedgerEntryType::ANY:
      break;
    case (int32_t)LedgerEntryType::OFFER_ENTRY:
new(&offer_) _offer_t{};
break;
    case (int32_t)LedgerEntryType::SALE:
new(&sale_) _sale_t{};
break;
    case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
new(&atomicSwapAsk_) _atomicSwapAsk_t{};
break;
    case (int32_t)LedgerEntryType::KEY_VALUE:
new(&keyValue_) _keyValue_t{};
break;
    case (int32_t)LedgerEntryType::POLL:
new(&poll_) _poll_t{};
break;
    case (int32_t)LedgerEntryType::VOTE:
new(&vote_) _vote_t{};
break;
    case (int32_t)LedgerEntryType::INITIATE_KYC_RECOVERY:
new(&initiateKYCRecovery_) _initiateKYCRecovery_t{};
break;
    case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
new(&accountSpecificRuleExt_) _accountSpecificRuleExt_t{};
break;
    case (int32_t)LedgerEntryType::SWAP:
new(&swap_) _swap_t{};
break;
    default:
new(&ext_) EmptyExt{};
break;
}

  }
  AccountRuleResource(const AccountRuleResource &source) : type_(source.type_) {
    switch (type_)
{
    case (int32_t)LedgerEntryType::ASSET:
new(&asset_) _asset_t(source.asset_);
break;
    case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
new(&reviewableRequest_) _reviewableRequest_t(source.reviewableRequest_);
break;
    case (int32_t)LedgerEntryType::ANY:
      break;
    case (int32_t)LedgerEntryType::OFFER_ENTRY:
new(&offer_) _offer_t(source.offer_);
break;
    case (int32_t)LedgerEntryType::SALE:
new(&sale_) _sale_t(source.sale_);
break;
    case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
new(&atomicSwapAsk_) _atomicSwapAsk_t(source.atomicSwapAsk_);
break;
    case (int32_t)LedgerEntryType::KEY_VALUE:
new(&keyValue_) _keyValue_t(source.keyValue_);
break;
    case (int32_t)LedgerEntryType::POLL:
new(&poll_) _poll_t(source.poll_);
break;
    case (int32_t)LedgerEntryType::VOTE:
new(&vote_) _vote_t(source.vote_);
break;
    case (int32_t)LedgerEntryType::INITIATE_KYC_RECOVERY:
new(&initiateKYCRecovery_) _initiateKYCRecovery_t(source.initiateKYCRecovery_);
break;
    case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
new(&accountSpecificRuleExt_) _accountSpecificRuleExt_t(source.accountSpecificRuleExt_);
break;
    case (int32_t)LedgerEntryType::SWAP:
new(&swap_) _swap_t(source.swap_);
break;
    default:
new(&ext_) EmptyExt(source.ext_);
break;
}

  }
  AccountRuleResource(AccountRuleResource &&source) : type_(source.type_) {
    switch (type_)
{
    case (int32_t)LedgerEntryType::ASSET:
new(&asset_) _asset_t(std::move(source.asset_));
break;
    case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
new(&reviewableRequest_) _reviewableRequest_t(std::move(source.reviewableRequest_));
break;
    case (int32_t)LedgerEntryType::ANY:
      break;
    case (int32_t)LedgerEntryType::OFFER_ENTRY:
new(&offer_) _offer_t(std::move(source.offer_));
break;
    case (int32_t)LedgerEntryType::SALE:
new(&sale_) _sale_t(std::move(source.sale_));
break;
    case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
new(&atomicSwapAsk_) _atomicSwapAsk_t(std::move(source.atomicSwapAsk_));
break;
    case (int32_t)LedgerEntryType::KEY_VALUE:
new(&keyValue_) _keyValue_t(std::move(source.keyValue_));
break;
    case (int32_t)LedgerEntryType::POLL:
new(&poll_) _poll_t(std::move(source.poll_));
break;
    case (int32_t)LedgerEntryType::VOTE:
new(&vote_) _vote_t(std::move(source.vote_));
break;
    case (int32_t)LedgerEntryType::INITIATE_KYC_RECOVERY:
new(&initiateKYCRecovery_) _initiateKYCRecovery_t(std::move(source.initiateKYCRecovery_));
break;
    case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
new(&accountSpecificRuleExt_) _accountSpecificRuleExt_t(std::move(source.accountSpecificRuleExt_));
break;
    case (int32_t)LedgerEntryType::SWAP:
new(&swap_) _swap_t(std::move(source.swap_));
break;
    default:
new(&ext_) EmptyExt(std::move(source.ext_));
break;
}

  }
  ~AccountRuleResource() {
switch (type_)
{
  case (int32_t)LedgerEntryType::ASSET:
asset_.~_asset_t();
break;
  case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
reviewableRequest_.~_reviewableRequest_t();
break;
  case (int32_t)LedgerEntryType::ANY:
    break;
  case (int32_t)LedgerEntryType::OFFER_ENTRY:
offer_.~_offer_t();
break;
  case (int32_t)LedgerEntryType::SALE:
sale_.~_sale_t();
break;
  case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
atomicSwapAsk_.~_atomicSwapAsk_t();
break;
  case (int32_t)LedgerEntryType::KEY_VALUE:
keyValue_.~_keyValue_t();
break;
  case (int32_t)LedgerEntryType::POLL:
poll_.~_poll_t();
break;
  case (int32_t)LedgerEntryType::VOTE:
vote_.~_vote_t();
break;
  case (int32_t)LedgerEntryType::INITIATE_KYC_RECOVERY:
initiateKYCRecovery_.~_initiateKYCRecovery_t();
break;
  case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
accountSpecificRuleExt_.~_accountSpecificRuleExt_t();
break;
  case (int32_t)LedgerEntryType::SWAP:
swap_.~_swap_t();
break;
  default:
ext_.~EmptyExt();
break;
}
}

  AccountRuleResource &operator=(const AccountRuleResource &source) {
    if (type_ == source.type_)
{
switch (type_)
{
    case (int32_t)LedgerEntryType::ASSET:
asset_ = source.asset_;
break;
    case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
reviewableRequest_ = source.reviewableRequest_;
break;
    case (int32_t)LedgerEntryType::ANY:
      break;
    case (int32_t)LedgerEntryType::OFFER_ENTRY:
offer_ = source.offer_;
break;
    case (int32_t)LedgerEntryType::SALE:
sale_ = source.sale_;
break;
    case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
atomicSwapAsk_ = source.atomicSwapAsk_;
break;
    case (int32_t)LedgerEntryType::KEY_VALUE:
keyValue_ = source.keyValue_;
break;
    case (int32_t)LedgerEntryType::POLL:
poll_ = source.poll_;
break;
    case (int32_t)LedgerEntryType::VOTE:
vote_ = source.vote_;
break;
    case (int32_t)LedgerEntryType::INITIATE_KYC_RECOVERY:
initiateKYCRecovery_ = source.initiateKYCRecovery_;
break;
    case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
accountSpecificRuleExt_ = source.accountSpecificRuleExt_;
break;
    case (int32_t)LedgerEntryType::SWAP:
swap_ = source.swap_;
break;
    default:
ext_ = source.ext_;
break;
}
}
else {this->~AccountRuleResource();
    type_ = source.type_;
switch (type_)
{
    case (int32_t)LedgerEntryType::ASSET:
new(&asset_) _asset_t(source.asset_);
break;
    case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
new(&reviewableRequest_) _reviewableRequest_t(source.reviewableRequest_);
break;
    case (int32_t)LedgerEntryType::ANY:
      break;
    case (int32_t)LedgerEntryType::OFFER_ENTRY:
new(&offer_) _offer_t(source.offer_);
break;
    case (int32_t)LedgerEntryType::SALE:
new(&sale_) _sale_t(source.sale_);
break;
    case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
new(&atomicSwapAsk_) _atomicSwapAsk_t(source.atomicSwapAsk_);
break;
    case (int32_t)LedgerEntryType::KEY_VALUE:
new(&keyValue_) _keyValue_t(source.keyValue_);
break;
    case (int32_t)LedgerEntryType::POLL:
new(&poll_) _poll_t(source.poll_);
break;
    case (int32_t)LedgerEntryType::VOTE:
new(&vote_) _vote_t(source.vote_);
break;
    case (int32_t)LedgerEntryType::INITIATE_KYC_RECOVERY:
new(&initiateKYCRecovery_) _initiateKYCRecovery_t(source.initiateKYCRecovery_);
break;
    case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
new(&accountSpecificRuleExt_) _accountSpecificRuleExt_t(source.accountSpecificRuleExt_);
break;
    case (int32_t)LedgerEntryType::SWAP:
new(&swap_) _swap_t(source.swap_);
break;
    default:
new(&ext_) EmptyExt(source.ext_);
break;
}
}
    return *this;
  }
  AccountRuleResource &operator=(AccountRuleResource &&source) {
    if (type_ == source.type_)
{
switch (type_)
{
    case (int32_t)LedgerEntryType::ASSET:
asset_ = std::move(source.asset_);
break;
    case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
reviewableRequest_ = std::move(source.reviewableRequest_);
break;
    case (int32_t)LedgerEntryType::ANY:
      break;
    case (int32_t)LedgerEntryType::OFFER_ENTRY:
offer_ = std::move(source.offer_);
break;
    case (int32_t)LedgerEntryType::SALE:
sale_ = std::move(source.sale_);
break;
    case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
atomicSwapAsk_ = std::move(source.atomicSwapAsk_);
break;
    case (int32_t)LedgerEntryType::KEY_VALUE:
keyValue_ = std::move(source.keyValue_);
break;
    case (int32_t)LedgerEntryType::POLL:
poll_ = std::move(source.poll_);
break;
    case (int32_t)LedgerEntryType::VOTE:
vote_ = std::move(source.vote_);
break;
    case (int32_t)LedgerEntryType::INITIATE_KYC_RECOVERY:
initiateKYCRecovery_ = std::move(source.initiateKYCRecovery_);
break;
    case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
accountSpecificRuleExt_ = std::move(source.accountSpecificRuleExt_);
break;
    case (int32_t)LedgerEntryType::SWAP:
swap_ = std::move(source.swap_);
break;
    default:
ext_ = std::move(source.ext_);
break;
}
}
else {this->~AccountRuleResource();
    type_ = std::move(source.type_);
switch (type_)
{
    case (int32_t)LedgerEntryType::ASSET:
new(&asset_) _asset_t(std::move(source.asset_));
break;
    case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
new(&reviewableRequest_) _reviewableRequest_t(std::move(source.reviewableRequest_));
break;
    case (int32_t)LedgerEntryType::ANY:
      break;
    case (int32_t)LedgerEntryType::OFFER_ENTRY:
new(&offer_) _offer_t(std::move(source.offer_));
break;
    case (int32_t)LedgerEntryType::SALE:
new(&sale_) _sale_t(std::move(source.sale_));
break;
    case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
new(&atomicSwapAsk_) _atomicSwapAsk_t(std::move(source.atomicSwapAsk_));
break;
    case (int32_t)LedgerEntryType::KEY_VALUE:
new(&keyValue_) _keyValue_t(std::move(source.keyValue_));
break;
    case (int32_t)LedgerEntryType::POLL:
new(&poll_) _poll_t(std::move(source.poll_));
break;
    case (int32_t)LedgerEntryType::VOTE:
new(&vote_) _vote_t(std::move(source.vote_));
break;
    case (int32_t)LedgerEntryType::INITIATE_KYC_RECOVERY:
new(&initiateKYCRecovery_) _initiateKYCRecovery_t(std::move(source.initiateKYCRecovery_));
break;
    case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
new(&accountSpecificRuleExt_) _accountSpecificRuleExt_t(std::move(source.accountSpecificRuleExt_));
break;
    case (int32_t)LedgerEntryType::SWAP:
new(&swap_) _swap_t(std::move(source.swap_));
break;
    default:
new(&ext_) EmptyExt(std::move(source.ext_));
break;
}
}
    return *this;
  }

  LedgerEntryType type() const { return LedgerEntryType(type_); }
  AccountRuleResource &type(LedgerEntryType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  _asset_t &asset() {
    if (_xdr_field_number(type_) == 1)
      return asset_;
    throw xdr::xdr_wrong_union("AccountRuleResource: asset accessed when not selected");
  }
  const _asset_t &asset() const {
    if (_xdr_field_number(type_) == 1)
      return asset_;
    throw xdr::xdr_wrong_union("AccountRuleResource: asset accessed when not selected");
  }
  _reviewableRequest_t &reviewableRequest() {
    if (_xdr_field_number(type_) == 2)
      return reviewableRequest_;
    throw xdr::xdr_wrong_union("AccountRuleResource: reviewableRequest accessed when not selected");
  }
  const _reviewableRequest_t &reviewableRequest() const {
    if (_xdr_field_number(type_) == 2)
      return reviewableRequest_;
    throw xdr::xdr_wrong_union("AccountRuleResource: reviewableRequest accessed when not selected");
  }
  _offer_t &offer() {
    if (_xdr_field_number(type_) == 3)
      return offer_;
    throw xdr::xdr_wrong_union("AccountRuleResource: offer accessed when not selected");
  }
  const _offer_t &offer() const {
    if (_xdr_field_number(type_) == 3)
      return offer_;
    throw xdr::xdr_wrong_union("AccountRuleResource: offer accessed when not selected");
  }
  _sale_t &sale() {
    if (_xdr_field_number(type_) == 4)
      return sale_;
    throw xdr::xdr_wrong_union("AccountRuleResource: sale accessed when not selected");
  }
  const _sale_t &sale() const {
    if (_xdr_field_number(type_) == 4)
      return sale_;
    throw xdr::xdr_wrong_union("AccountRuleResource: sale accessed when not selected");
  }
  _atomicSwapAsk_t &atomicSwapAsk() {
    if (_xdr_field_number(type_) == 5)
      return atomicSwapAsk_;
    throw xdr::xdr_wrong_union("AccountRuleResource: atomicSwapAsk accessed when not selected");
  }
  const _atomicSwapAsk_t &atomicSwapAsk() const {
    if (_xdr_field_number(type_) == 5)
      return atomicSwapAsk_;
    throw xdr::xdr_wrong_union("AccountRuleResource: atomicSwapAsk accessed when not selected");
  }
  _keyValue_t &keyValue() {
    if (_xdr_field_number(type_) == 6)
      return keyValue_;
    throw xdr::xdr_wrong_union("AccountRuleResource: keyValue accessed when not selected");
  }
  const _keyValue_t &keyValue() const {
    if (_xdr_field_number(type_) == 6)
      return keyValue_;
    throw xdr::xdr_wrong_union("AccountRuleResource: keyValue accessed when not selected");
  }
  _poll_t &poll() {
    if (_xdr_field_number(type_) == 7)
      return poll_;
    throw xdr::xdr_wrong_union("AccountRuleResource: poll accessed when not selected");
  }
  const _poll_t &poll() const {
    if (_xdr_field_number(type_) == 7)
      return poll_;
    throw xdr::xdr_wrong_union("AccountRuleResource: poll accessed when not selected");
  }
  _vote_t &vote() {
    if (_xdr_field_number(type_) == 8)
      return vote_;
    throw xdr::xdr_wrong_union("AccountRuleResource: vote accessed when not selected");
  }
  const _vote_t &vote() const {
    if (_xdr_field_number(type_) == 8)
      return vote_;
    throw xdr::xdr_wrong_union("AccountRuleResource: vote accessed when not selected");
  }
  _initiateKYCRecovery_t &initiateKYCRecovery() {
    if (_xdr_field_number(type_) == 9)
      return initiateKYCRecovery_;
    throw xdr::xdr_wrong_union("AccountRuleResource: initiateKYCRecovery accessed when not selected");
  }
  const _initiateKYCRecovery_t &initiateKYCRecovery() const {
    if (_xdr_field_number(type_) == 9)
      return initiateKYCRecovery_;
    throw xdr::xdr_wrong_union("AccountRuleResource: initiateKYCRecovery accessed when not selected");
  }
  _accountSpecificRuleExt_t &accountSpecificRuleExt() {
    if (_xdr_field_number(type_) == 10)
      return accountSpecificRuleExt_;
    throw xdr::xdr_wrong_union("AccountRuleResource: accountSpecificRuleExt accessed when not selected");
  }
  const _accountSpecificRuleExt_t &accountSpecificRuleExt() const {
    if (_xdr_field_number(type_) == 10)
      return accountSpecificRuleExt_;
    throw xdr::xdr_wrong_union("AccountRuleResource: accountSpecificRuleExt accessed when not selected");
  }
  _swap_t &swap() {
    if (_xdr_field_number(type_) == 11)
      return swap_;
    throw xdr::xdr_wrong_union("AccountRuleResource: swap accessed when not selected");
  }
  const _swap_t &swap() const {
    if (_xdr_field_number(type_) == 11)
      return swap_;
    throw xdr::xdr_wrong_union("AccountRuleResource: swap accessed when not selected");
  }
  EmptyExt &ext() {
    if (_xdr_field_number(type_) == 12)
      return ext_;
    throw xdr::xdr_wrong_union("AccountRuleResource: ext accessed when not selected");
  }
  const EmptyExt &ext() const {
    if (_xdr_field_number(type_) == 12)
      return ext_;
    throw xdr::xdr_wrong_union("AccountRuleResource: ext accessed when not selected");
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

enum class AccountRuleAction : std::int32_t {
  ANY = 1,
  CREATE = 2,
  CREATE_FOR_OTHER = 3,
  CREATE_WITH_TASKS = 4,
  MANAGE = 5,
  SEND = 6,
  WITHDRAW = 7,
  RECEIVE_ISSUANCE = 8,
  RECEIVE_PAYMENT = 9,
  RECEIVE_ATOMIC_SWAP = 10,
  PARTICIPATE = 11,
  BIND = 12,
  UPDATE_MAX_ISSUANCE = 13,
  CHECK = 14,
  CANCEL = 15,
  CLOSE = 16,
  REMOVE = 17,
  UPDATE_END_TIME = 18,
  CREATE_FOR_OTHER_WITH_TASKS = 19,
  EXCHANGE = 20,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::AccountRuleAction>
  : xdr_integral_base<::stellar::AccountRuleAction, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::AccountRuleAction val) {
    switch (val) {
    case ::stellar::AccountRuleAction::ANY:
      return "ANY";
    case ::stellar::AccountRuleAction::CREATE:
      return "CREATE";
    case ::stellar::AccountRuleAction::CREATE_FOR_OTHER:
      return "CREATE_FOR_OTHER";
    case ::stellar::AccountRuleAction::CREATE_WITH_TASKS:
      return "CREATE_WITH_TASKS";
    case ::stellar::AccountRuleAction::MANAGE:
      return "MANAGE";
    case ::stellar::AccountRuleAction::SEND:
      return "SEND";
    case ::stellar::AccountRuleAction::WITHDRAW:
      return "WITHDRAW";
    case ::stellar::AccountRuleAction::RECEIVE_ISSUANCE:
      return "RECEIVE_ISSUANCE";
    case ::stellar::AccountRuleAction::RECEIVE_PAYMENT:
      return "RECEIVE_PAYMENT";
    case ::stellar::AccountRuleAction::RECEIVE_ATOMIC_SWAP:
      return "RECEIVE_ATOMIC_SWAP";
    case ::stellar::AccountRuleAction::PARTICIPATE:
      return "PARTICIPATE";
    case ::stellar::AccountRuleAction::BIND:
      return "BIND";
    case ::stellar::AccountRuleAction::UPDATE_MAX_ISSUANCE:
      return "UPDATE_MAX_ISSUANCE";
    case ::stellar::AccountRuleAction::CHECK:
      return "CHECK";
    case ::stellar::AccountRuleAction::CANCEL:
      return "CANCEL";
    case ::stellar::AccountRuleAction::CLOSE:
      return "CLOSE";
    case ::stellar::AccountRuleAction::REMOVE:
      return "REMOVE";
    case ::stellar::AccountRuleAction::UPDATE_END_TIME:
      return "UPDATE_END_TIME";
    case ::stellar::AccountRuleAction::CREATE_FOR_OTHER_WITH_TASKS:
      return "CREATE_FOR_OTHER_WITH_TASKS";
    case ::stellar::AccountRuleAction::EXCHANGE:
      return "EXCHANGE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::AccountRuleAction::ANY,
      (int32_t)::stellar::AccountRuleAction::CREATE,
      (int32_t)::stellar::AccountRuleAction::CREATE_FOR_OTHER,
      (int32_t)::stellar::AccountRuleAction::CREATE_WITH_TASKS,
      (int32_t)::stellar::AccountRuleAction::MANAGE,
      (int32_t)::stellar::AccountRuleAction::SEND,
      (int32_t)::stellar::AccountRuleAction::WITHDRAW,
      (int32_t)::stellar::AccountRuleAction::RECEIVE_ISSUANCE,
      (int32_t)::stellar::AccountRuleAction::RECEIVE_PAYMENT,
      (int32_t)::stellar::AccountRuleAction::RECEIVE_ATOMIC_SWAP,
      (int32_t)::stellar::AccountRuleAction::PARTICIPATE,
      (int32_t)::stellar::AccountRuleAction::BIND,
      (int32_t)::stellar::AccountRuleAction::UPDATE_MAX_ISSUANCE,
      (int32_t)::stellar::AccountRuleAction::CHECK,
      (int32_t)::stellar::AccountRuleAction::CANCEL,
      (int32_t)::stellar::AccountRuleAction::CLOSE,
      (int32_t)::stellar::AccountRuleAction::REMOVE,
      (int32_t)::stellar::AccountRuleAction::UPDATE_END_TIME,
      (int32_t)::stellar::AccountRuleAction::CREATE_FOR_OTHER_WITH_TASKS,
      (int32_t)::stellar::AccountRuleAction::EXCHANGE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

}

#endif // !__XDR_RESOURCE_ACCOUNT_RULE_H_INCLUDED__
