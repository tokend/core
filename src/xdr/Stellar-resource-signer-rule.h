// -*- C++ -*-
// Automatically generated from Stellar-resource-signer-rule.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_RESOURCE_SIGNER_RULE_H_INCLUDED__
#define __XDR_STELLAR_RESOURCE_SIGNER_RULE_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-types.h"

namespace stellar {

struct SignerRuleResource {
  struct _reviewableRequest_t {
    ReviewableRequestResource details{};
    uint64 tasksToAdd{};
    uint64 tasksToRemove{};
    uint64 allTasks{};
    EmptyExt ext{};

    _reviewableRequest_t() = default;
    template<typename _details_T,
             typename _tasksToAdd_T,
             typename _tasksToRemove_T,
             typename _allTasks_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<ReviewableRequestResource, _details_T>::value
                            && std::is_constructible<uint64, _tasksToAdd_T>::value
                            && std::is_constructible<uint64, _tasksToRemove_T>::value
                            && std::is_constructible<uint64, _allTasks_T>::value
                            && std::is_constructible<EmptyExt, _ext_T>::value
                           >::type>
    explicit _reviewableRequest_t(_details_T &&_details,
                                  _tasksToAdd_T &&_tasksToAdd,
                                  _tasksToRemove_T &&_tasksToRemove,
                                  _allTasks_T &&_allTasks,
                                  _ext_T &&_ext)
      : details(std::forward<_details_T>(_details)),
        tasksToAdd(std::forward<_tasksToAdd_T>(_tasksToAdd)),
        tasksToRemove(std::forward<_tasksToRemove_T>(_tasksToRemove)),
        allTasks(std::forward<_allTasks_T>(_allTasks)),
        ext(std::forward<_ext_T>(_ext)) {}
  };
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
  struct _signerRule_t {
    bool isDefault{};
    EmptyExt ext{};

    _signerRule_t() = default;
    template<typename _isDefault_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<bool, _isDefault_T>::value
                            && std::is_constructible<EmptyExt, _ext_T>::value
                           >::type>
    explicit _signerRule_t(_isDefault_T &&_isDefault,
                           _ext_T &&_ext)
      : isDefault(std::forward<_isDefault_T>(_isDefault)),
        ext(std::forward<_ext_T>(_ext)) {}
  };
  struct _signerRole_t {
    uint64 roleID{};
    EmptyExt ext{};

    _signerRole_t() = default;
    template<typename _roleID_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _roleID_T>::value
                            && std::is_constructible<EmptyExt, _ext_T>::value
                           >::type>
    explicit _signerRole_t(_roleID_T &&_roleID,
                           _ext_T &&_ext)
      : roleID(std::forward<_roleID_T>(_roleID)),
        ext(std::forward<_ext_T>(_ext)) {}
  };
  struct _signer_t {
    uint64 roleID{};
    EmptyExt ext{};

    _signer_t() = default;
    template<typename _roleID_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _roleID_T>::value
                            && std::is_constructible<EmptyExt, _ext_T>::value
                           >::type>
    explicit _signer_t(_roleID_T &&_roleID,
                       _ext_T &&_ext)
      : roleID(std::forward<_roleID_T>(_roleID)),
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
    _reviewableRequest_t reviewableRequest_;
    _asset_t asset_;
    _offer_t offer_;
    _sale_t sale_;
    _atomicSwapBid_t atomicSwapBid_;
    _signerRule_t signerRule_;
    _signerRole_t signerRole_;
    _signer_t signer_;
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
    return which == (int32_t)LedgerEntryType::REVIEWABLE_REQUEST ? 1
      : which == (int32_t)LedgerEntryType::ASSET ? 2
      : which == (int32_t)LedgerEntryType::ANY ? 0
      : which == (int32_t)LedgerEntryType::OFFER_ENTRY ? 3
      : which == (int32_t)LedgerEntryType::SALE ? 4
      : which == (int32_t)LedgerEntryType::ATOMIC_SWAP_BID ? 5
      : which == (int32_t)LedgerEntryType::SIGNER_RULE ? 6
      : which == (int32_t)LedgerEntryType::SIGNER_ROLE ? 7
      : which == (int32_t)LedgerEntryType::SIGNER ? 8
      : which == (int32_t)LedgerEntryType::KEY_VALUE ? 9
      : 10;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
      _f(&SignerRuleResource::reviewableRequest_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::ASSET:
      _f(&SignerRuleResource::asset_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::ANY:
      return true;
    case (int32_t)LedgerEntryType::OFFER_ENTRY:
      _f(&SignerRuleResource::offer_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::SALE:
      _f(&SignerRuleResource::sale_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::ATOMIC_SWAP_BID:
      _f(&SignerRuleResource::atomicSwapBid_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::SIGNER_RULE:
      _f(&SignerRuleResource::signerRule_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::SIGNER_ROLE:
      _f(&SignerRuleResource::signerRole_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::SIGNER:
      _f(&SignerRuleResource::signer_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::KEY_VALUE:
      _f(&SignerRuleResource::keyValue_, std::forward<_A>(_a)...);
      return true;
    default:
      _f(&SignerRuleResource::ext_, std::forward<_A>(_a)...);
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return type_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of type in SignerRuleResource");
    if (fnum != _xdr_field_number(type_)) {
      this->~SignerRuleResource();
      type_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    else
      type_ = which;
  }
  explicit SignerRuleResource(LedgerEntryType which = LedgerEntryType{}) : type_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
  }
  SignerRuleResource(const SignerRuleResource &source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
  }
  SignerRuleResource(SignerRuleResource &&source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                      std::move(source));
  }
  ~SignerRuleResource() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
  SignerRuleResource &operator=(const SignerRuleResource &source) {
    if (_xdr_field_number(type_)
        == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
    else {
      this->~SignerRuleResource();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
    }
    type_ = source.type_;
    return *this;
  }
  SignerRuleResource &operator=(SignerRuleResource &&source) {
    if (_xdr_field_number(type_)
         == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                        std::move(source));
    else {
      this->~SignerRuleResource();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                        std::move(source));
    }
    type_ = source.type_;
    return *this;
  }

  LedgerEntryType type() const { return LedgerEntryType(type_); }
  SignerRuleResource &type(LedgerEntryType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  _reviewableRequest_t &reviewableRequest() {
    if (_xdr_field_number(type_) == 1)
      return reviewableRequest_;
    throw xdr::xdr_wrong_union("SignerRuleResource: reviewableRequest accessed when not selected");
  }
  const _reviewableRequest_t &reviewableRequest() const {
    if (_xdr_field_number(type_) == 1)
      return reviewableRequest_;
    throw xdr::xdr_wrong_union("SignerRuleResource: reviewableRequest accessed when not selected");
  }
  _asset_t &asset() {
    if (_xdr_field_number(type_) == 2)
      return asset_;
    throw xdr::xdr_wrong_union("SignerRuleResource: asset accessed when not selected");
  }
  const _asset_t &asset() const {
    if (_xdr_field_number(type_) == 2)
      return asset_;
    throw xdr::xdr_wrong_union("SignerRuleResource: asset accessed when not selected");
  }
  _offer_t &offer() {
    if (_xdr_field_number(type_) == 3)
      return offer_;
    throw xdr::xdr_wrong_union("SignerRuleResource: offer accessed when not selected");
  }
  const _offer_t &offer() const {
    if (_xdr_field_number(type_) == 3)
      return offer_;
    throw xdr::xdr_wrong_union("SignerRuleResource: offer accessed when not selected");
  }
  _sale_t &sale() {
    if (_xdr_field_number(type_) == 4)
      return sale_;
    throw xdr::xdr_wrong_union("SignerRuleResource: sale accessed when not selected");
  }
  const _sale_t &sale() const {
    if (_xdr_field_number(type_) == 4)
      return sale_;
    throw xdr::xdr_wrong_union("SignerRuleResource: sale accessed when not selected");
  }
  _atomicSwapBid_t &atomicSwapBid() {
    if (_xdr_field_number(type_) == 5)
      return atomicSwapBid_;
    throw xdr::xdr_wrong_union("SignerRuleResource: atomicSwapBid accessed when not selected");
  }
  const _atomicSwapBid_t &atomicSwapBid() const {
    if (_xdr_field_number(type_) == 5)
      return atomicSwapBid_;
    throw xdr::xdr_wrong_union("SignerRuleResource: atomicSwapBid accessed when not selected");
  }
  _signerRule_t &signerRule() {
    if (_xdr_field_number(type_) == 6)
      return signerRule_;
    throw xdr::xdr_wrong_union("SignerRuleResource: signerRule accessed when not selected");
  }
  const _signerRule_t &signerRule() const {
    if (_xdr_field_number(type_) == 6)
      return signerRule_;
    throw xdr::xdr_wrong_union("SignerRuleResource: signerRule accessed when not selected");
  }
  _signerRole_t &signerRole() {
    if (_xdr_field_number(type_) == 7)
      return signerRole_;
    throw xdr::xdr_wrong_union("SignerRuleResource: signerRole accessed when not selected");
  }
  const _signerRole_t &signerRole() const {
    if (_xdr_field_number(type_) == 7)
      return signerRole_;
    throw xdr::xdr_wrong_union("SignerRuleResource: signerRole accessed when not selected");
  }
  _signer_t &signer() {
    if (_xdr_field_number(type_) == 8)
      return signer_;
    throw xdr::xdr_wrong_union("SignerRuleResource: signer accessed when not selected");
  }
  const _signer_t &signer() const {
    if (_xdr_field_number(type_) == 8)
      return signer_;
    throw xdr::xdr_wrong_union("SignerRuleResource: signer accessed when not selected");
  }
  _keyValue_t &keyValue() {
    if (_xdr_field_number(type_) == 9)
      return keyValue_;
    throw xdr::xdr_wrong_union("SignerRuleResource: keyValue accessed when not selected");
  }
  const _keyValue_t &keyValue() const {
    if (_xdr_field_number(type_) == 9)
      return keyValue_;
    throw xdr::xdr_wrong_union("SignerRuleResource: keyValue accessed when not selected");
  }
  EmptyExt &ext() {
    if (_xdr_field_number(type_) == 10)
      return ext_;
    throw xdr::xdr_wrong_union("SignerRuleResource: ext accessed when not selected");
  }
  const EmptyExt &ext() const {
    if (_xdr_field_number(type_) == 10)
      return ext_;
    throw xdr::xdr_wrong_union("SignerRuleResource: ext accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SignerRuleResource::_reviewableRequest_t>
  : xdr_struct_base<field_ptr<::stellar::SignerRuleResource::_reviewableRequest_t,
                              decltype(::stellar::SignerRuleResource::_reviewableRequest_t::details),
                              &::stellar::SignerRuleResource::_reviewableRequest_t::details>,
                    field_ptr<::stellar::SignerRuleResource::_reviewableRequest_t,
                              decltype(::stellar::SignerRuleResource::_reviewableRequest_t::tasksToAdd),
                              &::stellar::SignerRuleResource::_reviewableRequest_t::tasksToAdd>,
                    field_ptr<::stellar::SignerRuleResource::_reviewableRequest_t,
                              decltype(::stellar::SignerRuleResource::_reviewableRequest_t::tasksToRemove),
                              &::stellar::SignerRuleResource::_reviewableRequest_t::tasksToRemove>,
                    field_ptr<::stellar::SignerRuleResource::_reviewableRequest_t,
                              decltype(::stellar::SignerRuleResource::_reviewableRequest_t::allTasks),
                              &::stellar::SignerRuleResource::_reviewableRequest_t::allTasks>,
                    field_ptr<::stellar::SignerRuleResource::_reviewableRequest_t,
                              decltype(::stellar::SignerRuleResource::_reviewableRequest_t::ext),
                              &::stellar::SignerRuleResource::_reviewableRequest_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SignerRuleResource::_reviewableRequest_t &obj) {
    archive(ar, obj.details, "details");
    archive(ar, obj.tasksToAdd, "tasksToAdd");
    archive(ar, obj.tasksToRemove, "tasksToRemove");
    archive(ar, obj.allTasks, "allTasks");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SignerRuleResource::_reviewableRequest_t &obj) {
    archive(ar, obj.details, "details");
    archive(ar, obj.tasksToAdd, "tasksToAdd");
    archive(ar, obj.tasksToRemove, "tasksToRemove");
    archive(ar, obj.allTasks, "allTasks");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::SignerRuleResource::_asset_t>
  : xdr_struct_base<field_ptr<::stellar::SignerRuleResource::_asset_t,
                              decltype(::stellar::SignerRuleResource::_asset_t::assetCode),
                              &::stellar::SignerRuleResource::_asset_t::assetCode>,
                    field_ptr<::stellar::SignerRuleResource::_asset_t,
                              decltype(::stellar::SignerRuleResource::_asset_t::assetType),
                              &::stellar::SignerRuleResource::_asset_t::assetType>,
                    field_ptr<::stellar::SignerRuleResource::_asset_t,
                              decltype(::stellar::SignerRuleResource::_asset_t::ext),
                              &::stellar::SignerRuleResource::_asset_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SignerRuleResource::_asset_t &obj) {
    archive(ar, obj.assetCode, "assetCode");
    archive(ar, obj.assetType, "assetType");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SignerRuleResource::_asset_t &obj) {
    archive(ar, obj.assetCode, "assetCode");
    archive(ar, obj.assetType, "assetType");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::SignerRuleResource::_offer_t>
  : xdr_struct_base<field_ptr<::stellar::SignerRuleResource::_offer_t,
                              decltype(::stellar::SignerRuleResource::_offer_t::baseAssetType),
                              &::stellar::SignerRuleResource::_offer_t::baseAssetType>,
                    field_ptr<::stellar::SignerRuleResource::_offer_t,
                              decltype(::stellar::SignerRuleResource::_offer_t::quoteAssetType),
                              &::stellar::SignerRuleResource::_offer_t::quoteAssetType>,
                    field_ptr<::stellar::SignerRuleResource::_offer_t,
                              decltype(::stellar::SignerRuleResource::_offer_t::baseAssetCode),
                              &::stellar::SignerRuleResource::_offer_t::baseAssetCode>,
                    field_ptr<::stellar::SignerRuleResource::_offer_t,
                              decltype(::stellar::SignerRuleResource::_offer_t::quoteAssetCode),
                              &::stellar::SignerRuleResource::_offer_t::quoteAssetCode>,
                    field_ptr<::stellar::SignerRuleResource::_offer_t,
                              decltype(::stellar::SignerRuleResource::_offer_t::isBuy),
                              &::stellar::SignerRuleResource::_offer_t::isBuy>,
                    field_ptr<::stellar::SignerRuleResource::_offer_t,
                              decltype(::stellar::SignerRuleResource::_offer_t::ext),
                              &::stellar::SignerRuleResource::_offer_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SignerRuleResource::_offer_t &obj) {
    archive(ar, obj.baseAssetType, "baseAssetType");
    archive(ar, obj.quoteAssetType, "quoteAssetType");
    archive(ar, obj.baseAssetCode, "baseAssetCode");
    archive(ar, obj.quoteAssetCode, "quoteAssetCode");
    archive(ar, obj.isBuy, "isBuy");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SignerRuleResource::_offer_t &obj) {
    archive(ar, obj.baseAssetType, "baseAssetType");
    archive(ar, obj.quoteAssetType, "quoteAssetType");
    archive(ar, obj.baseAssetCode, "baseAssetCode");
    archive(ar, obj.quoteAssetCode, "quoteAssetCode");
    archive(ar, obj.isBuy, "isBuy");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::SignerRuleResource::_sale_t>
  : xdr_struct_base<field_ptr<::stellar::SignerRuleResource::_sale_t,
                              decltype(::stellar::SignerRuleResource::_sale_t::saleID),
                              &::stellar::SignerRuleResource::_sale_t::saleID>,
                    field_ptr<::stellar::SignerRuleResource::_sale_t,
                              decltype(::stellar::SignerRuleResource::_sale_t::saleType),
                              &::stellar::SignerRuleResource::_sale_t::saleType>,
                    field_ptr<::stellar::SignerRuleResource::_sale_t,
                              decltype(::stellar::SignerRuleResource::_sale_t::ext),
                              &::stellar::SignerRuleResource::_sale_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SignerRuleResource::_sale_t &obj) {
    archive(ar, obj.saleID, "saleID");
    archive(ar, obj.saleType, "saleType");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SignerRuleResource::_sale_t &obj) {
    archive(ar, obj.saleID, "saleID");
    archive(ar, obj.saleType, "saleType");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::SignerRuleResource::_atomicSwapBid_t>
  : xdr_struct_base<field_ptr<::stellar::SignerRuleResource::_atomicSwapBid_t,
                              decltype(::stellar::SignerRuleResource::_atomicSwapBid_t::assetType),
                              &::stellar::SignerRuleResource::_atomicSwapBid_t::assetType>,
                    field_ptr<::stellar::SignerRuleResource::_atomicSwapBid_t,
                              decltype(::stellar::SignerRuleResource::_atomicSwapBid_t::assetCode),
                              &::stellar::SignerRuleResource::_atomicSwapBid_t::assetCode>,
                    field_ptr<::stellar::SignerRuleResource::_atomicSwapBid_t,
                              decltype(::stellar::SignerRuleResource::_atomicSwapBid_t::ext),
                              &::stellar::SignerRuleResource::_atomicSwapBid_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SignerRuleResource::_atomicSwapBid_t &obj) {
    archive(ar, obj.assetType, "assetType");
    archive(ar, obj.assetCode, "assetCode");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SignerRuleResource::_atomicSwapBid_t &obj) {
    archive(ar, obj.assetType, "assetType");
    archive(ar, obj.assetCode, "assetCode");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::SignerRuleResource::_signerRule_t>
  : xdr_struct_base<field_ptr<::stellar::SignerRuleResource::_signerRule_t,
                              decltype(::stellar::SignerRuleResource::_signerRule_t::isDefault),
                              &::stellar::SignerRuleResource::_signerRule_t::isDefault>,
                    field_ptr<::stellar::SignerRuleResource::_signerRule_t,
                              decltype(::stellar::SignerRuleResource::_signerRule_t::ext),
                              &::stellar::SignerRuleResource::_signerRule_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SignerRuleResource::_signerRule_t &obj) {
    archive(ar, obj.isDefault, "isDefault");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SignerRuleResource::_signerRule_t &obj) {
    archive(ar, obj.isDefault, "isDefault");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::SignerRuleResource::_signerRole_t>
  : xdr_struct_base<field_ptr<::stellar::SignerRuleResource::_signerRole_t,
                              decltype(::stellar::SignerRuleResource::_signerRole_t::roleID),
                              &::stellar::SignerRuleResource::_signerRole_t::roleID>,
                    field_ptr<::stellar::SignerRuleResource::_signerRole_t,
                              decltype(::stellar::SignerRuleResource::_signerRole_t::ext),
                              &::stellar::SignerRuleResource::_signerRole_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SignerRuleResource::_signerRole_t &obj) {
    archive(ar, obj.roleID, "roleID");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SignerRuleResource::_signerRole_t &obj) {
    archive(ar, obj.roleID, "roleID");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::SignerRuleResource::_signer_t>
  : xdr_struct_base<field_ptr<::stellar::SignerRuleResource::_signer_t,
                              decltype(::stellar::SignerRuleResource::_signer_t::roleID),
                              &::stellar::SignerRuleResource::_signer_t::roleID>,
                    field_ptr<::stellar::SignerRuleResource::_signer_t,
                              decltype(::stellar::SignerRuleResource::_signer_t::ext),
                              &::stellar::SignerRuleResource::_signer_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SignerRuleResource::_signer_t &obj) {
    archive(ar, obj.roleID, "roleID");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SignerRuleResource::_signer_t &obj) {
    archive(ar, obj.roleID, "roleID");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::SignerRuleResource::_keyValue_t>
  : xdr_struct_base<field_ptr<::stellar::SignerRuleResource::_keyValue_t,
                              decltype(::stellar::SignerRuleResource::_keyValue_t::keyPrefix),
                              &::stellar::SignerRuleResource::_keyValue_t::keyPrefix>,
                    field_ptr<::stellar::SignerRuleResource::_keyValue_t,
                              decltype(::stellar::SignerRuleResource::_keyValue_t::ext),
                              &::stellar::SignerRuleResource::_keyValue_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SignerRuleResource::_keyValue_t &obj) {
    archive(ar, obj.keyPrefix, "keyPrefix");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SignerRuleResource::_keyValue_t &obj) {
    archive(ar, obj.keyPrefix, "keyPrefix");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::SignerRuleResource> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::SignerRuleResource;
  using case_type = ::stellar::SignerRuleResource::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "reviewableRequest";
    case 2:
      return "asset";
    case 3:
      return "offer";
    case 4:
      return "sale";
    case 5:
      return "atomicSwapBid";
    case 6:
      return "signerRule";
    case 7:
      return "signerRole";
    case 8:
      return "signer";
    case 9:
      return "keyValue";
    default:
      return "ext";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::SignerRuleResource &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in SignerRuleResource");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SignerRuleResource &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in SignerRuleResource");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SignerRuleResource &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.type(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum class SignerRuleAction : std::int32_t {
  ANY = 1,
  CREATE = 2,
  CREATE_FOR_OTHER = 3,
  UPDATE = 4,
  MANAGE = 5,
  SEND = 6,
  REMOVE = 7,
  CANCEL = 8,
  REVIEW = 9,
  RECEIVE_ATOMIC_SWAP = 10,
  PARTICIPATE = 11,
  BIND = 12,
  UPDATE_MAX_ISSUANCE = 13,
  CHECK = 14,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SignerRuleAction>
  : xdr_integral_base<::stellar::SignerRuleAction, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::SignerRuleAction val) {
    switch (val) {
    case ::stellar::SignerRuleAction::ANY:
      return "ANY";
    case ::stellar::SignerRuleAction::CREATE:
      return "CREATE";
    case ::stellar::SignerRuleAction::CREATE_FOR_OTHER:
      return "CREATE_FOR_OTHER";
    case ::stellar::SignerRuleAction::UPDATE:
      return "UPDATE";
    case ::stellar::SignerRuleAction::MANAGE:
      return "MANAGE";
    case ::stellar::SignerRuleAction::SEND:
      return "SEND";
    case ::stellar::SignerRuleAction::REMOVE:
      return "REMOVE";
    case ::stellar::SignerRuleAction::CANCEL:
      return "CANCEL";
    case ::stellar::SignerRuleAction::REVIEW:
      return "REVIEW";
    case ::stellar::SignerRuleAction::RECEIVE_ATOMIC_SWAP:
      return "RECEIVE_ATOMIC_SWAP";
    case ::stellar::SignerRuleAction::PARTICIPATE:
      return "PARTICIPATE";
    case ::stellar::SignerRuleAction::BIND:
      return "BIND";
    case ::stellar::SignerRuleAction::UPDATE_MAX_ISSUANCE:
      return "UPDATE_MAX_ISSUANCE";
    case ::stellar::SignerRuleAction::CHECK:
      return "CHECK";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::SignerRuleAction::ANY,
      (int32_t)::stellar::SignerRuleAction::CREATE,
      (int32_t)::stellar::SignerRuleAction::CREATE_FOR_OTHER,
      (int32_t)::stellar::SignerRuleAction::UPDATE,
      (int32_t)::stellar::SignerRuleAction::MANAGE,
      (int32_t)::stellar::SignerRuleAction::SEND,
      (int32_t)::stellar::SignerRuleAction::REMOVE,
      (int32_t)::stellar::SignerRuleAction::CANCEL,
      (int32_t)::stellar::SignerRuleAction::REVIEW,
      (int32_t)::stellar::SignerRuleAction::RECEIVE_ATOMIC_SWAP,
      (int32_t)::stellar::SignerRuleAction::PARTICIPATE,
      (int32_t)::stellar::SignerRuleAction::BIND,
      (int32_t)::stellar::SignerRuleAction::UPDATE_MAX_ISSUANCE,
      (int32_t)::stellar::SignerRuleAction::CHECK
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

}

#endif // !__XDR_STELLAR_RESOURCE_SIGNER_RULE_H_INCLUDED__
