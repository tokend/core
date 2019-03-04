// -*- C++ -*-
// Automatically generated from Stellar-resource-account-rule.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_RESOURCE_ACCOUNT_RULE_H_INCLUDED__
#define __XDR_STELLAR_RESOURCE_ACCOUNT_RULE_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-types.h"

namespace stellar {

struct ReviewableRequestResource {
  struct _createSale_t {
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
  };
  struct _createIssuance_t {
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
  };
  struct _createWithdraw_t {
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
  };

  using _xdr_case_type = xdr::xdr_traits<ReviewableRequestType>::case_type;
private:
  _xdr_case_type requestType_;
  union {
    _createSale_t createSale_;
    _createIssuance_t createIssuance_;
    _createWithdraw_t createWithdraw_;
    EmptyExt ext_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = true;
  static const std::vector<ReviewableRequestType> &_xdr_case_values() {
    static const std::vector<ReviewableRequestType> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)ReviewableRequestType::CREATE_SALE ? 1
      : which == (int32_t)ReviewableRequestType::CREATE_ISSUANCE ? 2
      : which == (int32_t)ReviewableRequestType::CREATE_WITHDRAW ? 3
      : 4;
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
      requestType_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, requestType_, *this);
    }
    else
      requestType_ = which;
  }
  explicit ReviewableRequestResource(ReviewableRequestType which = ReviewableRequestType{}) : requestType_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, requestType_, *this);
  }
  ReviewableRequestResource(const ReviewableRequestResource &source) : requestType_(source.requestType_) {
    _xdr_with_mem_ptr(xdr::field_constructor, requestType_, *this, source);
  }
  ReviewableRequestResource(ReviewableRequestResource &&source) : requestType_(source.requestType_) {
    _xdr_with_mem_ptr(xdr::field_constructor, requestType_, *this,
                      std::move(source));
  }
  ~ReviewableRequestResource() { _xdr_with_mem_ptr(xdr::field_destructor, requestType_, *this); }
  ReviewableRequestResource &operator=(const ReviewableRequestResource &source) {
    if (_xdr_field_number(requestType_)
        == _xdr_field_number(source.requestType_))
      _xdr_with_mem_ptr(xdr::field_assigner, requestType_, *this, source);
    else {
      this->~ReviewableRequestResource();
      requestType_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.requestType_, *this, source);
    }
    requestType_ = source.requestType_;
    return *this;
  }
  ReviewableRequestResource &operator=(ReviewableRequestResource &&source) {
    if (_xdr_field_number(requestType_)
         == _xdr_field_number(source.requestType_))
      _xdr_with_mem_ptr(xdr::field_assigner, requestType_, *this,
                        std::move(source));
    else {
      this->~ReviewableRequestResource();
      requestType_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.requestType_, *this,
                        std::move(source));
    }
    requestType_ = source.requestType_;
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
  EmptyExt &ext() {
    if (_xdr_field_number(requestType_) == 4)
      return ext_;
    throw xdr::xdr_wrong_union("ReviewableRequestResource: ext accessed when not selected");
  }
  const EmptyExt &ext() const {
    if (_xdr_field_number(requestType_) == 4)
      return ext_;
    throw xdr::xdr_wrong_union("ReviewableRequestResource: ext accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ReviewableRequestResource::_createSale_t>
  : xdr_struct_base<field_ptr<::stellar::ReviewableRequestResource::_createSale_t,
                              decltype(::stellar::ReviewableRequestResource::_createSale_t::type),
                              &::stellar::ReviewableRequestResource::_createSale_t::type>,
                    field_ptr<::stellar::ReviewableRequestResource::_createSale_t,
                              decltype(::stellar::ReviewableRequestResource::_createSale_t::ext),
                              &::stellar::ReviewableRequestResource::_createSale_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ReviewableRequestResource::_createSale_t &obj) {
    archive(ar, obj.type, "type");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ReviewableRequestResource::_createSale_t &obj) {
    archive(ar, obj.type, "type");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ReviewableRequestResource::_createIssuance_t>
  : xdr_struct_base<field_ptr<::stellar::ReviewableRequestResource::_createIssuance_t,
                              decltype(::stellar::ReviewableRequestResource::_createIssuance_t::assetCode),
                              &::stellar::ReviewableRequestResource::_createIssuance_t::assetCode>,
                    field_ptr<::stellar::ReviewableRequestResource::_createIssuance_t,
                              decltype(::stellar::ReviewableRequestResource::_createIssuance_t::assetType),
                              &::stellar::ReviewableRequestResource::_createIssuance_t::assetType>,
                    field_ptr<::stellar::ReviewableRequestResource::_createIssuance_t,
                              decltype(::stellar::ReviewableRequestResource::_createIssuance_t::ext),
                              &::stellar::ReviewableRequestResource::_createIssuance_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ReviewableRequestResource::_createIssuance_t &obj) {
    archive(ar, obj.assetCode, "assetCode");
    archive(ar, obj.assetType, "assetType");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ReviewableRequestResource::_createIssuance_t &obj) {
    archive(ar, obj.assetCode, "assetCode");
    archive(ar, obj.assetType, "assetType");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ReviewableRequestResource::_createWithdraw_t>
  : xdr_struct_base<field_ptr<::stellar::ReviewableRequestResource::_createWithdraw_t,
                              decltype(::stellar::ReviewableRequestResource::_createWithdraw_t::assetCode),
                              &::stellar::ReviewableRequestResource::_createWithdraw_t::assetCode>,
                    field_ptr<::stellar::ReviewableRequestResource::_createWithdraw_t,
                              decltype(::stellar::ReviewableRequestResource::_createWithdraw_t::assetType),
                              &::stellar::ReviewableRequestResource::_createWithdraw_t::assetType>,
                    field_ptr<::stellar::ReviewableRequestResource::_createWithdraw_t,
                              decltype(::stellar::ReviewableRequestResource::_createWithdraw_t::ext),
                              &::stellar::ReviewableRequestResource::_createWithdraw_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ReviewableRequestResource::_createWithdraw_t &obj) {
    archive(ar, obj.assetCode, "assetCode");
    archive(ar, obj.assetType, "assetType");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ReviewableRequestResource::_createWithdraw_t &obj) {
    archive(ar, obj.assetCode, "assetCode");
    archive(ar, obj.assetType, "assetType");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ReviewableRequestResource> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ReviewableRequestResource;
  using case_type = ::stellar::ReviewableRequestResource::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().requestType());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "createSale";
    case 2:
      return "createIssuance";
    case 3:
      return "createWithdraw";
    default:
      return "ext";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ReviewableRequestResource &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of requestType in ReviewableRequestResource");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ReviewableRequestResource &obj) {
    xdr::archive(ar, obj.requestType(), "requestType");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.requestType(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of requestType in ReviewableRequestResource");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ReviewableRequestResource &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "requestType");
    obj.requestType(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.requestType(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
} namespace stellar {

struct AccountRuleResource {
  struct _asset_t {
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
  };
  struct _reviewableRequest_t {
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
  };
  struct _offer_t {
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
  };
  struct _sale_t {
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
  };
  struct _atomicSwapBid_t {
    uint64 assetType{};
    AssetCode assetCode{};
    EmptyExt ext{};

    _atomicSwapBid_t() = default;
    template<typename _assetType_T,
             typename _assetCode_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _assetType_T>::value
                            && std::is_constructible<AssetCode, _assetCode_T>::value
                            && std::is_constructible<EmptyExt, _ext_T>::value
                           >::type>
    explicit _atomicSwapBid_t(_assetType_T &&_assetType,
                              _assetCode_T &&_assetCode,
                              _ext_T &&_ext)
      : assetType(std::forward<_assetType_T>(_assetType)),
        assetCode(std::forward<_assetCode_T>(_assetCode)),
        ext(std::forward<_ext_T>(_ext)) {}
  };
  struct _keyValue_t {
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
  };

  using _xdr_case_type = xdr::xdr_traits<LedgerEntryType>::case_type;
private:
  _xdr_case_type type_;
  union {
    _asset_t asset_;
    _reviewableRequest_t reviewableRequest_;
    _offer_t offer_;
    _sale_t sale_;
    _atomicSwapBid_t atomicSwapBid_;
    _keyValue_t keyValue_;
    EmptyExt ext_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = true;
  static const std::vector<LedgerEntryType> &_xdr_case_values() {
    static const std::vector<LedgerEntryType> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)LedgerEntryType::ASSET ? 1
      : which == (int32_t)LedgerEntryType::REVIEWABLE_REQUEST ? 2
      : which == (int32_t)LedgerEntryType::ANY ? 0
      : which == (int32_t)LedgerEntryType::OFFER_ENTRY ? 3
      : which == (int32_t)LedgerEntryType::SALE ? 4
      : which == (int32_t)LedgerEntryType::ATOMIC_SWAP_BID ? 5
      : which == (int32_t)LedgerEntryType::KEY_VALUE ? 6
      : 7;
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
    case (int32_t)LedgerEntryType::ATOMIC_SWAP_BID:
      _f(&AccountRuleResource::atomicSwapBid_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::KEY_VALUE:
      _f(&AccountRuleResource::keyValue_, std::forward<_A>(_a)...);
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
      type_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    else
      type_ = which;
  }
  explicit AccountRuleResource(LedgerEntryType which = LedgerEntryType{}) : type_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
  }
  AccountRuleResource(const AccountRuleResource &source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
  }
  AccountRuleResource(AccountRuleResource &&source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                      std::move(source));
  }
  ~AccountRuleResource() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
  AccountRuleResource &operator=(const AccountRuleResource &source) {
    if (_xdr_field_number(type_)
        == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
    else {
      this->~AccountRuleResource();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
    }
    type_ = source.type_;
    return *this;
  }
  AccountRuleResource &operator=(AccountRuleResource &&source) {
    if (_xdr_field_number(type_)
         == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                        std::move(source));
    else {
      this->~AccountRuleResource();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                        std::move(source));
    }
    type_ = source.type_;
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
  _atomicSwapBid_t &atomicSwapBid() {
    if (_xdr_field_number(type_) == 5)
      return atomicSwapBid_;
    throw xdr::xdr_wrong_union("AccountRuleResource: atomicSwapBid accessed when not selected");
  }
  const _atomicSwapBid_t &atomicSwapBid() const {
    if (_xdr_field_number(type_) == 5)
      return atomicSwapBid_;
    throw xdr::xdr_wrong_union("AccountRuleResource: atomicSwapBid accessed when not selected");
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
  EmptyExt &ext() {
    if (_xdr_field_number(type_) == 7)
      return ext_;
    throw xdr::xdr_wrong_union("AccountRuleResource: ext accessed when not selected");
  }
  const EmptyExt &ext() const {
    if (_xdr_field_number(type_) == 7)
      return ext_;
    throw xdr::xdr_wrong_union("AccountRuleResource: ext accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::AccountRuleResource::_asset_t>
  : xdr_struct_base<field_ptr<::stellar::AccountRuleResource::_asset_t,
                              decltype(::stellar::AccountRuleResource::_asset_t::assetCode),
                              &::stellar::AccountRuleResource::_asset_t::assetCode>,
                    field_ptr<::stellar::AccountRuleResource::_asset_t,
                              decltype(::stellar::AccountRuleResource::_asset_t::assetType),
                              &::stellar::AccountRuleResource::_asset_t::assetType>,
                    field_ptr<::stellar::AccountRuleResource::_asset_t,
                              decltype(::stellar::AccountRuleResource::_asset_t::ext),
                              &::stellar::AccountRuleResource::_asset_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::AccountRuleResource::_asset_t &obj) {
    archive(ar, obj.assetCode, "assetCode");
    archive(ar, obj.assetType, "assetType");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::AccountRuleResource::_asset_t &obj) {
    archive(ar, obj.assetCode, "assetCode");
    archive(ar, obj.assetType, "assetType");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::AccountRuleResource::_reviewableRequest_t>
  : xdr_struct_base<field_ptr<::stellar::AccountRuleResource::_reviewableRequest_t,
                              decltype(::stellar::AccountRuleResource::_reviewableRequest_t::details),
                              &::stellar::AccountRuleResource::_reviewableRequest_t::details>,
                    field_ptr<::stellar::AccountRuleResource::_reviewableRequest_t,
                              decltype(::stellar::AccountRuleResource::_reviewableRequest_t::ext),
                              &::stellar::AccountRuleResource::_reviewableRequest_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::AccountRuleResource::_reviewableRequest_t &obj) {
    archive(ar, obj.details, "details");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::AccountRuleResource::_reviewableRequest_t &obj) {
    archive(ar, obj.details, "details");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::AccountRuleResource::_offer_t>
  : xdr_struct_base<field_ptr<::stellar::AccountRuleResource::_offer_t,
                              decltype(::stellar::AccountRuleResource::_offer_t::baseAssetType),
                              &::stellar::AccountRuleResource::_offer_t::baseAssetType>,
                    field_ptr<::stellar::AccountRuleResource::_offer_t,
                              decltype(::stellar::AccountRuleResource::_offer_t::quoteAssetType),
                              &::stellar::AccountRuleResource::_offer_t::quoteAssetType>,
                    field_ptr<::stellar::AccountRuleResource::_offer_t,
                              decltype(::stellar::AccountRuleResource::_offer_t::baseAssetCode),
                              &::stellar::AccountRuleResource::_offer_t::baseAssetCode>,
                    field_ptr<::stellar::AccountRuleResource::_offer_t,
                              decltype(::stellar::AccountRuleResource::_offer_t::quoteAssetCode),
                              &::stellar::AccountRuleResource::_offer_t::quoteAssetCode>,
                    field_ptr<::stellar::AccountRuleResource::_offer_t,
                              decltype(::stellar::AccountRuleResource::_offer_t::isBuy),
                              &::stellar::AccountRuleResource::_offer_t::isBuy>,
                    field_ptr<::stellar::AccountRuleResource::_offer_t,
                              decltype(::stellar::AccountRuleResource::_offer_t::ext),
                              &::stellar::AccountRuleResource::_offer_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::AccountRuleResource::_offer_t &obj) {
    archive(ar, obj.baseAssetType, "baseAssetType");
    archive(ar, obj.quoteAssetType, "quoteAssetType");
    archive(ar, obj.baseAssetCode, "baseAssetCode");
    archive(ar, obj.quoteAssetCode, "quoteAssetCode");
    archive(ar, obj.isBuy, "isBuy");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::AccountRuleResource::_offer_t &obj) {
    archive(ar, obj.baseAssetType, "baseAssetType");
    archive(ar, obj.quoteAssetType, "quoteAssetType");
    archive(ar, obj.baseAssetCode, "baseAssetCode");
    archive(ar, obj.quoteAssetCode, "quoteAssetCode");
    archive(ar, obj.isBuy, "isBuy");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::AccountRuleResource::_sale_t>
  : xdr_struct_base<field_ptr<::stellar::AccountRuleResource::_sale_t,
                              decltype(::stellar::AccountRuleResource::_sale_t::saleID),
                              &::stellar::AccountRuleResource::_sale_t::saleID>,
                    field_ptr<::stellar::AccountRuleResource::_sale_t,
                              decltype(::stellar::AccountRuleResource::_sale_t::saleType),
                              &::stellar::AccountRuleResource::_sale_t::saleType>,
                    field_ptr<::stellar::AccountRuleResource::_sale_t,
                              decltype(::stellar::AccountRuleResource::_sale_t::ext),
                              &::stellar::AccountRuleResource::_sale_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::AccountRuleResource::_sale_t &obj) {
    archive(ar, obj.saleID, "saleID");
    archive(ar, obj.saleType, "saleType");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::AccountRuleResource::_sale_t &obj) {
    archive(ar, obj.saleID, "saleID");
    archive(ar, obj.saleType, "saleType");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::AccountRuleResource::_atomicSwapBid_t>
  : xdr_struct_base<field_ptr<::stellar::AccountRuleResource::_atomicSwapBid_t,
                              decltype(::stellar::AccountRuleResource::_atomicSwapBid_t::assetType),
                              &::stellar::AccountRuleResource::_atomicSwapBid_t::assetType>,
                    field_ptr<::stellar::AccountRuleResource::_atomicSwapBid_t,
                              decltype(::stellar::AccountRuleResource::_atomicSwapBid_t::assetCode),
                              &::stellar::AccountRuleResource::_atomicSwapBid_t::assetCode>,
                    field_ptr<::stellar::AccountRuleResource::_atomicSwapBid_t,
                              decltype(::stellar::AccountRuleResource::_atomicSwapBid_t::ext),
                              &::stellar::AccountRuleResource::_atomicSwapBid_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::AccountRuleResource::_atomicSwapBid_t &obj) {
    archive(ar, obj.assetType, "assetType");
    archive(ar, obj.assetCode, "assetCode");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::AccountRuleResource::_atomicSwapBid_t &obj) {
    archive(ar, obj.assetType, "assetType");
    archive(ar, obj.assetCode, "assetCode");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::AccountRuleResource::_keyValue_t>
  : xdr_struct_base<field_ptr<::stellar::AccountRuleResource::_keyValue_t,
                              decltype(::stellar::AccountRuleResource::_keyValue_t::keyPrefix),
                              &::stellar::AccountRuleResource::_keyValue_t::keyPrefix>,
                    field_ptr<::stellar::AccountRuleResource::_keyValue_t,
                              decltype(::stellar::AccountRuleResource::_keyValue_t::ext),
                              &::stellar::AccountRuleResource::_keyValue_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::AccountRuleResource::_keyValue_t &obj) {
    archive(ar, obj.keyPrefix, "keyPrefix");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::AccountRuleResource::_keyValue_t &obj) {
    archive(ar, obj.keyPrefix, "keyPrefix");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::AccountRuleResource> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::AccountRuleResource;
  using case_type = ::stellar::AccountRuleResource::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "asset";
    case 2:
      return "reviewableRequest";
    case 3:
      return "offer";
    case 4:
      return "sale";
    case 5:
      return "atomicSwapBid";
    case 6:
      return "keyValue";
    default:
      return "ext";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::AccountRuleResource &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in AccountRuleResource");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::AccountRuleResource &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in AccountRuleResource");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::AccountRuleResource &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.type(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
} namespace stellar {

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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::AccountRuleAction>
  : xdr_integral_base<::stellar::AccountRuleAction, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
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
      (int32_t)::stellar::AccountRuleAction::CANCEL
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

}

#endif // !__XDR_STELLAR_RESOURCE_ACCOUNT_RULE_H_INCLUDED__
