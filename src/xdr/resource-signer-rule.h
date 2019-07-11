// -*- C++ -*-
// Automatically generated from resource-signer-rule.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_RESOURCE_SIGNER_RULE_H_INCLUDED__
#define __XDR_RESOURCE_SIGNER_RULE_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"

namespace stellar {

struct SignerRuleResource : xdr::xdr_abstract {
  struct _reviewableRequest_t  : xdr::xdr_abstract {
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
  struct _signerRule_t  : xdr::xdr_abstract {
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
  struct _signerRole_t  : xdr::xdr_abstract {
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
  struct _signer_t  : xdr::xdr_abstract {
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

  using _xdr_case_type = xdr::xdr_traits<LedgerEntryType>::case_type;
private:
  _xdr_case_type type_;
  union {
    _reviewableRequest_t reviewableRequest_;
    _asset_t asset_;
    _offer_t offer_;
    _sale_t sale_;
    _atomicSwapAsk_t atomicSwapAsk_;
    _signerRule_t signerRule_;
    _signerRole_t signerRole_;
    _signer_t signer_;
    _keyValue_t keyValue_;
    _poll_t poll_;
    _vote_t vote_;
    _initiateKYCRecovery_t initiateKYCRecovery_;
    _accountSpecificRuleExt_t accountSpecificRuleExt_;
    EmptyExt ext_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<LedgerEntryType> &_xdr_case_values() {
    static const std::vector<LedgerEntryType> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)LedgerEntryType::REVIEWABLE_REQUEST ? 1
      : which == (int32_t)LedgerEntryType::ASSET ? 2
      : which == (int32_t)LedgerEntryType::ANY ? 0
      : which == (int32_t)LedgerEntryType::OFFER_ENTRY ? 3
      : which == (int32_t)LedgerEntryType::SALE ? 4
      : which == (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK ? 5
      : which == (int32_t)LedgerEntryType::SIGNER_RULE ? 6
      : which == (int32_t)LedgerEntryType::SIGNER_ROLE ? 7
      : which == (int32_t)LedgerEntryType::SIGNER ? 8
      : which == (int32_t)LedgerEntryType::KEY_VALUE ? 9
      : which == (int32_t)LedgerEntryType::POLL ? 10
      : which == (int32_t)LedgerEntryType::VOTE ? 11
      : which == (int32_t)LedgerEntryType::INITIATE_KYC_RECOVERY ? 12
      : which == (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE ? 13
      : 14;
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
    case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
      _f(&SignerRuleResource::atomicSwapAsk_, std::forward<_A>(_a)...);
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
    case (int32_t)LedgerEntryType::POLL:
      _f(&SignerRuleResource::poll_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::VOTE:
      _f(&SignerRuleResource::vote_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::INITIATE_KYC_RECOVERY:
      _f(&SignerRuleResource::initiateKYCRecovery_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
      _f(&SignerRuleResource::accountSpecificRuleExt_, std::forward<_A>(_a)...);
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
      type_ = which;switch (type_)
{
      case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
new(&reviewableRequest_) _reviewableRequest_t{};
break;
      case (int32_t)LedgerEntryType::ASSET:
new(&asset_) _asset_t{};
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
      case (int32_t)LedgerEntryType::SIGNER_RULE:
new(&signerRule_) _signerRule_t{};
break;
      case (int32_t)LedgerEntryType::SIGNER_ROLE:
new(&signerRole_) _signerRole_t{};
break;
      case (int32_t)LedgerEntryType::SIGNER:
new(&signer_) _signer_t{};
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
      default:
new(&ext_) EmptyExt{};
break;
}

    }
    else
      type_ = which;
  }
  explicit SignerRuleResource(LedgerEntryType which = LedgerEntryType{}) : type_((int32_t)which) {
    switch (type_)
{
    case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
new(&reviewableRequest_) _reviewableRequest_t{};
break;
    case (int32_t)LedgerEntryType::ASSET:
new(&asset_) _asset_t{};
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
    case (int32_t)LedgerEntryType::SIGNER_RULE:
new(&signerRule_) _signerRule_t{};
break;
    case (int32_t)LedgerEntryType::SIGNER_ROLE:
new(&signerRole_) _signerRole_t{};
break;
    case (int32_t)LedgerEntryType::SIGNER:
new(&signer_) _signer_t{};
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
    default:
new(&ext_) EmptyExt{};
break;
}

  }
  SignerRuleResource(const SignerRuleResource &source) : type_(source.type_) {
    switch (type_)
{
    case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
new(&reviewableRequest_) _reviewableRequest_t(source.reviewableRequest_);
break;
    case (int32_t)LedgerEntryType::ASSET:
new(&asset_) _asset_t(source.asset_);
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
    case (int32_t)LedgerEntryType::SIGNER_RULE:
new(&signerRule_) _signerRule_t(source.signerRule_);
break;
    case (int32_t)LedgerEntryType::SIGNER_ROLE:
new(&signerRole_) _signerRole_t(source.signerRole_);
break;
    case (int32_t)LedgerEntryType::SIGNER:
new(&signer_) _signer_t(source.signer_);
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
    default:
new(&ext_) EmptyExt(source.ext_);
break;
}

  }
  SignerRuleResource(SignerRuleResource &&source) : type_(source.type_) {
    switch (type_)
{
    case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
new(&reviewableRequest_) _reviewableRequest_t(std::move(source.reviewableRequest_));
break;
    case (int32_t)LedgerEntryType::ASSET:
new(&asset_) _asset_t(std::move(source.asset_));
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
    case (int32_t)LedgerEntryType::SIGNER_RULE:
new(&signerRule_) _signerRule_t(std::move(source.signerRule_));
break;
    case (int32_t)LedgerEntryType::SIGNER_ROLE:
new(&signerRole_) _signerRole_t(std::move(source.signerRole_));
break;
    case (int32_t)LedgerEntryType::SIGNER:
new(&signer_) _signer_t(std::move(source.signer_));
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
    default:
new(&ext_) EmptyExt(std::move(source.ext_));
break;
}

  }
  ~SignerRuleResource() {
switch (type_)
{
  case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
reviewableRequest_.~_reviewableRequest_t();
break;
  case (int32_t)LedgerEntryType::ASSET:
asset_.~_asset_t();
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
  case (int32_t)LedgerEntryType::SIGNER_RULE:
signerRule_.~_signerRule_t();
break;
  case (int32_t)LedgerEntryType::SIGNER_ROLE:
signerRole_.~_signerRole_t();
break;
  case (int32_t)LedgerEntryType::SIGNER:
signer_.~_signer_t();
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
  default:
ext_.~EmptyExt();
break;
}
}

  SignerRuleResource &operator=(const SignerRuleResource &source) {
    if (type_ == source.type_)
{
switch (type_)
{
    case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
reviewableRequest_ = source.reviewableRequest_;
break;
    case (int32_t)LedgerEntryType::ASSET:
asset_ = source.asset_;
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
    case (int32_t)LedgerEntryType::SIGNER_RULE:
signerRule_ = source.signerRule_;
break;
    case (int32_t)LedgerEntryType::SIGNER_ROLE:
signerRole_ = source.signerRole_;
break;
    case (int32_t)LedgerEntryType::SIGNER:
signer_ = source.signer_;
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
    default:
ext_ = source.ext_;
break;
}
}
else {this->~SignerRuleResource();
    type_ = source.type_;
switch (type_)
{
    case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
new(&reviewableRequest_) _reviewableRequest_t(source.reviewableRequest_);
break;
    case (int32_t)LedgerEntryType::ASSET:
new(&asset_) _asset_t(source.asset_);
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
    case (int32_t)LedgerEntryType::SIGNER_RULE:
new(&signerRule_) _signerRule_t(source.signerRule_);
break;
    case (int32_t)LedgerEntryType::SIGNER_ROLE:
new(&signerRole_) _signerRole_t(source.signerRole_);
break;
    case (int32_t)LedgerEntryType::SIGNER:
new(&signer_) _signer_t(source.signer_);
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
    default:
new(&ext_) EmptyExt(source.ext_);
break;
}
}
    return *this;
  }
  SignerRuleResource &operator=(SignerRuleResource &&source) {
    if (type_ == source.type_)
{
switch (type_)
{
    case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
reviewableRequest_ = std::move(source.reviewableRequest_);
break;
    case (int32_t)LedgerEntryType::ASSET:
asset_ = std::move(source.asset_);
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
    case (int32_t)LedgerEntryType::SIGNER_RULE:
signerRule_ = std::move(source.signerRule_);
break;
    case (int32_t)LedgerEntryType::SIGNER_ROLE:
signerRole_ = std::move(source.signerRole_);
break;
    case (int32_t)LedgerEntryType::SIGNER:
signer_ = std::move(source.signer_);
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
    default:
ext_ = std::move(source.ext_);
break;
}
}
else {this->~SignerRuleResource();
    type_ = std::move(source.type_);
switch (type_)
{
    case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
new(&reviewableRequest_) _reviewableRequest_t(std::move(source.reviewableRequest_));
break;
    case (int32_t)LedgerEntryType::ASSET:
new(&asset_) _asset_t(std::move(source.asset_));
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
    case (int32_t)LedgerEntryType::SIGNER_RULE:
new(&signerRule_) _signerRule_t(std::move(source.signerRule_));
break;
    case (int32_t)LedgerEntryType::SIGNER_ROLE:
new(&signerRole_) _signerRole_t(std::move(source.signerRole_));
break;
    case (int32_t)LedgerEntryType::SIGNER:
new(&signer_) _signer_t(std::move(source.signer_));
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
    default:
new(&ext_) EmptyExt(std::move(source.ext_));
break;
}
}
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
  _atomicSwapAsk_t &atomicSwapAsk() {
    if (_xdr_field_number(type_) == 5)
      return atomicSwapAsk_;
    throw xdr::xdr_wrong_union("SignerRuleResource: atomicSwapAsk accessed when not selected");
  }
  const _atomicSwapAsk_t &atomicSwapAsk() const {
    if (_xdr_field_number(type_) == 5)
      return atomicSwapAsk_;
    throw xdr::xdr_wrong_union("SignerRuleResource: atomicSwapAsk accessed when not selected");
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
  _poll_t &poll() {
    if (_xdr_field_number(type_) == 10)
      return poll_;
    throw xdr::xdr_wrong_union("SignerRuleResource: poll accessed when not selected");
  }
  const _poll_t &poll() const {
    if (_xdr_field_number(type_) == 10)
      return poll_;
    throw xdr::xdr_wrong_union("SignerRuleResource: poll accessed when not selected");
  }
  _vote_t &vote() {
    if (_xdr_field_number(type_) == 11)
      return vote_;
    throw xdr::xdr_wrong_union("SignerRuleResource: vote accessed when not selected");
  }
  const _vote_t &vote() const {
    if (_xdr_field_number(type_) == 11)
      return vote_;
    throw xdr::xdr_wrong_union("SignerRuleResource: vote accessed when not selected");
  }
  _initiateKYCRecovery_t &initiateKYCRecovery() {
    if (_xdr_field_number(type_) == 12)
      return initiateKYCRecovery_;
    throw xdr::xdr_wrong_union("SignerRuleResource: initiateKYCRecovery accessed when not selected");
  }
  const _initiateKYCRecovery_t &initiateKYCRecovery() const {
    if (_xdr_field_number(type_) == 12)
      return initiateKYCRecovery_;
    throw xdr::xdr_wrong_union("SignerRuleResource: initiateKYCRecovery accessed when not selected");
  }
  _accountSpecificRuleExt_t &accountSpecificRuleExt() {
    if (_xdr_field_number(type_) == 13)
      return accountSpecificRuleExt_;
    throw xdr::xdr_wrong_union("SignerRuleResource: accountSpecificRuleExt accessed when not selected");
  }
  const _accountSpecificRuleExt_t &accountSpecificRuleExt() const {
    if (_xdr_field_number(type_) == 13)
      return accountSpecificRuleExt_;
    throw xdr::xdr_wrong_union("SignerRuleResource: accountSpecificRuleExt accessed when not selected");
  }
  EmptyExt &ext() {
    if (_xdr_field_number(type_) == 14)
      return ext_;
    throw xdr::xdr_wrong_union("SignerRuleResource: ext accessed when not selected");
  }
  const EmptyExt &ext() const {
    if (_xdr_field_number(type_) == 14)
      return ext_;
    throw xdr::xdr_wrong_union("SignerRuleResource: ext accessed when not selected");
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
  CLOSE = 15,
  UPDATE_END_TIME = 16,
  CREATE_WITH_TASKS = 17,
  CREATE_FOR_OTHER_WITH_TASKS = 18,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SignerRuleAction>
  : xdr_integral_base<::stellar::SignerRuleAction, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
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
    case ::stellar::SignerRuleAction::CLOSE:
      return "CLOSE";
    case ::stellar::SignerRuleAction::UPDATE_END_TIME:
      return "UPDATE_END_TIME";
    case ::stellar::SignerRuleAction::CREATE_WITH_TASKS:
      return "CREATE_WITH_TASKS";
    case ::stellar::SignerRuleAction::CREATE_FOR_OTHER_WITH_TASKS:
      return "CREATE_FOR_OTHER_WITH_TASKS";
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
      (int32_t)::stellar::SignerRuleAction::CHECK,
      (int32_t)::stellar::SignerRuleAction::CLOSE,
      (int32_t)::stellar::SignerRuleAction::UPDATE_END_TIME,
      (int32_t)::stellar::SignerRuleAction::CREATE_WITH_TASKS,
      (int32_t)::stellar::SignerRuleAction::CREATE_FOR_OTHER_WITH_TASKS
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

}

#endif // !__XDR_RESOURCE_SIGNER_RULE_H_INCLUDED__
