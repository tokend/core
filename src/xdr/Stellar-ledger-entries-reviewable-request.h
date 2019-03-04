// -*- C++ -*-
// Automatically generated from Stellar-ledger-entries-reviewable-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_LEDGER_ENTRIES_REVIEWABLE_REQUEST_H_INCLUDED__
#define __XDR_STELLAR_LEDGER_ENTRIES_REVIEWABLE_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-types.h"
#include "xdr/Stellar-reviewable-request-asset.h"
#include "xdr/Stellar-reviewable-request-issuance.h"
#include "xdr/Stellar-reviewable-request-withdrawal.h"
#include "xdr/Stellar-reviewable-request-sale.h"
#include "xdr/Stellar-reviewable-request-change-role.h"
#include "xdr/Stellar-reviewable-request-limits-update.h"
#include "xdr/Stellar-reviewable-request-AML-alert.h"
#include "xdr/Stellar-reviewable-request-update-sale-details.h"
#include "xdr/Stellar-reviewable-request-invoice.h"
#include "xdr/Stellar-reviewable-request-contract.h"
#include "xdr/Stellar-reviewable-request-atomic-swap.h"
#include "xdr/Stellar-reviewable-request-atomic-swap-bid.h"

namespace stellar {

enum class ReviewableRequestType : std::int32_t {
  NONE = 0,
  ANY = 1,
  CREATE_PRE_ISSUANCE = 2,
  CREATE_ISSUANCE = 3,
  CREATE_WITHDRAW = 4,
  CREATE_SALE = 5,
  UPDATE_LIMITS = 6,
  CREATE_AML_ALERT = 7,
  CHANGE_ROLE = 8,
  UPDATE_SALE_DETAILS = 9,
  CREATE_ASSET = 10,
  CREATE_INVOICE = 11,
  MANAGE_CONTRACT = 12,
  UPDATE_ASSET = 13,
  CREATE_ATOMIC_SWAP_BID = 16,
  CREATE_ATOMIC_SWAP = 17,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ReviewableRequestType>
  : xdr_integral_base<::stellar::ReviewableRequestType, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ReviewableRequestType val) {
    switch (val) {
    case ::stellar::ReviewableRequestType::NONE:
      return "NONE";
    case ::stellar::ReviewableRequestType::ANY:
      return "ANY";
    case ::stellar::ReviewableRequestType::CREATE_PRE_ISSUANCE:
      return "CREATE_PRE_ISSUANCE";
    case ::stellar::ReviewableRequestType::CREATE_ISSUANCE:
      return "CREATE_ISSUANCE";
    case ::stellar::ReviewableRequestType::CREATE_WITHDRAW:
      return "CREATE_WITHDRAW";
    case ::stellar::ReviewableRequestType::CREATE_SALE:
      return "CREATE_SALE";
    case ::stellar::ReviewableRequestType::UPDATE_LIMITS:
      return "UPDATE_LIMITS";
    case ::stellar::ReviewableRequestType::CREATE_AML_ALERT:
      return "CREATE_AML_ALERT";
    case ::stellar::ReviewableRequestType::CHANGE_ROLE:
      return "CHANGE_ROLE";
    case ::stellar::ReviewableRequestType::UPDATE_SALE_DETAILS:
      return "UPDATE_SALE_DETAILS";
    case ::stellar::ReviewableRequestType::CREATE_ASSET:
      return "CREATE_ASSET";
    case ::stellar::ReviewableRequestType::CREATE_INVOICE:
      return "CREATE_INVOICE";
    case ::stellar::ReviewableRequestType::MANAGE_CONTRACT:
      return "MANAGE_CONTRACT";
    case ::stellar::ReviewableRequestType::UPDATE_ASSET:
      return "UPDATE_ASSET";
    case ::stellar::ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
      return "CREATE_ATOMIC_SWAP_BID";
    case ::stellar::ReviewableRequestType::CREATE_ATOMIC_SWAP:
      return "CREATE_ATOMIC_SWAP";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ReviewableRequestType::NONE,
      (int32_t)::stellar::ReviewableRequestType::ANY,
      (int32_t)::stellar::ReviewableRequestType::CREATE_PRE_ISSUANCE,
      (int32_t)::stellar::ReviewableRequestType::CREATE_ISSUANCE,
      (int32_t)::stellar::ReviewableRequestType::CREATE_WITHDRAW,
      (int32_t)::stellar::ReviewableRequestType::CREATE_SALE,
      (int32_t)::stellar::ReviewableRequestType::UPDATE_LIMITS,
      (int32_t)::stellar::ReviewableRequestType::CREATE_AML_ALERT,
      (int32_t)::stellar::ReviewableRequestType::CHANGE_ROLE,
      (int32_t)::stellar::ReviewableRequestType::UPDATE_SALE_DETAILS,
      (int32_t)::stellar::ReviewableRequestType::CREATE_ASSET,
      (int32_t)::stellar::ReviewableRequestType::CREATE_INVOICE,
      (int32_t)::stellar::ReviewableRequestType::MANAGE_CONTRACT,
      (int32_t)::stellar::ReviewableRequestType::UPDATE_ASSET,
      (int32_t)::stellar::ReviewableRequestType::CREATE_ATOMIC_SWAP_BID,
      (int32_t)::stellar::ReviewableRequestType::CREATE_ATOMIC_SWAP
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct TasksExt {
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

  uint32 allTasks{};
  uint32 pendingTasks{};
  xdr::xvector<longstring> externalDetails{};
  _ext_t ext{};

  TasksExt() = default;
  template<typename _allTasks_T,
           typename _pendingTasks_T,
           typename _externalDetails_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint32, _allTasks_T>::value
                          && std::is_constructible<uint32, _pendingTasks_T>::value
                          && std::is_constructible<xdr::xvector<longstring>, _externalDetails_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit TasksExt(_allTasks_T &&_allTasks,
                    _pendingTasks_T &&_pendingTasks,
                    _externalDetails_T &&_externalDetails,
                    _ext_T &&_ext)
    : allTasks(std::forward<_allTasks_T>(_allTasks)),
      pendingTasks(std::forward<_pendingTasks_T>(_pendingTasks)),
      externalDetails(std::forward<_externalDetails_T>(_externalDetails)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TasksExt::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::TasksExt::_ext_t;
  using case_type = ::stellar::TasksExt::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::TasksExt::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TasksExt::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TasksExt::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::TasksExt>
  : xdr_struct_base<field_ptr<::stellar::TasksExt,
                              decltype(::stellar::TasksExt::allTasks),
                              &::stellar::TasksExt::allTasks>,
                    field_ptr<::stellar::TasksExt,
                              decltype(::stellar::TasksExt::pendingTasks),
                              &::stellar::TasksExt::pendingTasks>,
                    field_ptr<::stellar::TasksExt,
                              decltype(::stellar::TasksExt::externalDetails),
                              &::stellar::TasksExt::externalDetails>,
                    field_ptr<::stellar::TasksExt,
                              decltype(::stellar::TasksExt::ext),
                              &::stellar::TasksExt::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TasksExt &obj) {
    archive(ar, obj.allTasks, "allTasks");
    archive(ar, obj.pendingTasks, "pendingTasks");
    archive(ar, obj.externalDetails, "externalDetails");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TasksExt &obj) {
    archive(ar, obj.allTasks, "allTasks");
    archive(ar, obj.pendingTasks, "pendingTasks");
    archive(ar, obj.externalDetails, "externalDetails");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ReviewableRequestEntry {
  struct _body_t {
    using _xdr_case_type = xdr::xdr_traits<ReviewableRequestType>::case_type;
  private:
    _xdr_case_type type_;
    union {
      AssetCreationRequest assetCreationRequest_;
      AssetUpdateRequest assetUpdateRequest_;
      PreIssuanceRequest preIssuanceRequest_;
      IssuanceRequest issuanceRequest_;
      WithdrawalRequest withdrawalRequest_;
      SaleCreationRequest saleCreationRequest_;
      LimitsUpdateRequest limitsUpdateRequest_;
      AMLAlertRequest amlAlertRequest_;
      ChangeRoleRequest changeRoleRequest_;
      UpdateSaleDetailsRequest updateSaleDetailsRequest_;
      InvoiceRequest invoiceRequest_;
      ContractRequest contractRequest_;
      ASwapBidCreationRequest aSwapBidCreationRequest_;
      ASwapRequest aSwapRequest_;
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<ReviewableRequestType> &_xdr_case_values() {
      static const std::vector<ReviewableRequestType> _xdr_disc_vec {
        ReviewableRequestType::CREATE_ASSET,
        ReviewableRequestType::UPDATE_ASSET,
        ReviewableRequestType::CREATE_PRE_ISSUANCE,
        ReviewableRequestType::CREATE_ISSUANCE,
        ReviewableRequestType::CREATE_WITHDRAW,
        ReviewableRequestType::CREATE_SALE,
        ReviewableRequestType::UPDATE_LIMITS,
        ReviewableRequestType::CREATE_AML_ALERT,
        ReviewableRequestType::CHANGE_ROLE,
        ReviewableRequestType::UPDATE_SALE_DETAILS,
        ReviewableRequestType::CREATE_INVOICE,
        ReviewableRequestType::MANAGE_CONTRACT,
        ReviewableRequestType::CREATE_ATOMIC_SWAP_BID,
        ReviewableRequestType::CREATE_ATOMIC_SWAP
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)ReviewableRequestType::CREATE_ASSET ? 1
        : which == (int32_t)ReviewableRequestType::UPDATE_ASSET ? 2
        : which == (int32_t)ReviewableRequestType::CREATE_PRE_ISSUANCE ? 3
        : which == (int32_t)ReviewableRequestType::CREATE_ISSUANCE ? 4
        : which == (int32_t)ReviewableRequestType::CREATE_WITHDRAW ? 5
        : which == (int32_t)ReviewableRequestType::CREATE_SALE ? 6
        : which == (int32_t)ReviewableRequestType::UPDATE_LIMITS ? 7
        : which == (int32_t)ReviewableRequestType::CREATE_AML_ALERT ? 8
        : which == (int32_t)ReviewableRequestType::CHANGE_ROLE ? 9
        : which == (int32_t)ReviewableRequestType::UPDATE_SALE_DETAILS ? 10
        : which == (int32_t)ReviewableRequestType::CREATE_INVOICE ? 11
        : which == (int32_t)ReviewableRequestType::MANAGE_CONTRACT ? 12
        : which == (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID ? 13
        : which == (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP ? 14
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)ReviewableRequestType::CREATE_ASSET:
        _f(&_body_t::assetCreationRequest_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::UPDATE_ASSET:
        _f(&_body_t::assetUpdateRequest_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::CREATE_PRE_ISSUANCE:
        _f(&_body_t::preIssuanceRequest_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::CREATE_ISSUANCE:
        _f(&_body_t::issuanceRequest_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
        _f(&_body_t::withdrawalRequest_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::CREATE_SALE:
        _f(&_body_t::saleCreationRequest_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::UPDATE_LIMITS:
        _f(&_body_t::limitsUpdateRequest_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::CREATE_AML_ALERT:
        _f(&_body_t::amlAlertRequest_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::CHANGE_ROLE:
        _f(&_body_t::changeRoleRequest_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::UPDATE_SALE_DETAILS:
        _f(&_body_t::updateSaleDetailsRequest_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::CREATE_INVOICE:
        _f(&_body_t::invoiceRequest_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::MANAGE_CONTRACT:
        _f(&_body_t::contractRequest_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
        _f(&_body_t::aSwapBidCreationRequest_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP:
        _f(&_body_t::aSwapRequest_, std::forward<_A>(_a)...);
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return type_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of type in _body_t");
      if (fnum != _xdr_field_number(type_)) {
        this->~_body_t();
        type_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
      }
      else
        type_ = which;
    }
    explicit _body_t(ReviewableRequestType which = ReviewableRequestType{}) : type_((int32_t)which) {
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    _body_t(const _body_t &source) : type_(source.type_) {
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
    }
    _body_t(_body_t &&source) : type_(source.type_) {
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                        std::move(source));
    }
    ~_body_t() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
    _body_t &operator=(const _body_t &source) {
      if (_xdr_field_number(type_)
          == _xdr_field_number(source.type_))
        _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
      else {
        this->~_body_t();
        type_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
      }
      type_ = source.type_;
      return *this;
    }
    _body_t &operator=(_body_t &&source) {
      if (_xdr_field_number(type_)
           == _xdr_field_number(source.type_))
        _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                          std::move(source));
      else {
        this->~_body_t();
        type_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                          std::move(source));
      }
      type_ = source.type_;
      return *this;
    }

    ReviewableRequestType type() const { return ReviewableRequestType(type_); }
    _body_t &type(ReviewableRequestType _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    AssetCreationRequest &assetCreationRequest() {
      if (_xdr_field_number(type_) == 1)
        return assetCreationRequest_;
      throw xdr::xdr_wrong_union("_body_t: assetCreationRequest accessed when not selected");
    }
    const AssetCreationRequest &assetCreationRequest() const {
      if (_xdr_field_number(type_) == 1)
        return assetCreationRequest_;
      throw xdr::xdr_wrong_union("_body_t: assetCreationRequest accessed when not selected");
    }
    AssetUpdateRequest &assetUpdateRequest() {
      if (_xdr_field_number(type_) == 2)
        return assetUpdateRequest_;
      throw xdr::xdr_wrong_union("_body_t: assetUpdateRequest accessed when not selected");
    }
    const AssetUpdateRequest &assetUpdateRequest() const {
      if (_xdr_field_number(type_) == 2)
        return assetUpdateRequest_;
      throw xdr::xdr_wrong_union("_body_t: assetUpdateRequest accessed when not selected");
    }
    PreIssuanceRequest &preIssuanceRequest() {
      if (_xdr_field_number(type_) == 3)
        return preIssuanceRequest_;
      throw xdr::xdr_wrong_union("_body_t: preIssuanceRequest accessed when not selected");
    }
    const PreIssuanceRequest &preIssuanceRequest() const {
      if (_xdr_field_number(type_) == 3)
        return preIssuanceRequest_;
      throw xdr::xdr_wrong_union("_body_t: preIssuanceRequest accessed when not selected");
    }
    IssuanceRequest &issuanceRequest() {
      if (_xdr_field_number(type_) == 4)
        return issuanceRequest_;
      throw xdr::xdr_wrong_union("_body_t: issuanceRequest accessed when not selected");
    }
    const IssuanceRequest &issuanceRequest() const {
      if (_xdr_field_number(type_) == 4)
        return issuanceRequest_;
      throw xdr::xdr_wrong_union("_body_t: issuanceRequest accessed when not selected");
    }
    WithdrawalRequest &withdrawalRequest() {
      if (_xdr_field_number(type_) == 5)
        return withdrawalRequest_;
      throw xdr::xdr_wrong_union("_body_t: withdrawalRequest accessed when not selected");
    }
    const WithdrawalRequest &withdrawalRequest() const {
      if (_xdr_field_number(type_) == 5)
        return withdrawalRequest_;
      throw xdr::xdr_wrong_union("_body_t: withdrawalRequest accessed when not selected");
    }
    SaleCreationRequest &saleCreationRequest() {
      if (_xdr_field_number(type_) == 6)
        return saleCreationRequest_;
      throw xdr::xdr_wrong_union("_body_t: saleCreationRequest accessed when not selected");
    }
    const SaleCreationRequest &saleCreationRequest() const {
      if (_xdr_field_number(type_) == 6)
        return saleCreationRequest_;
      throw xdr::xdr_wrong_union("_body_t: saleCreationRequest accessed when not selected");
    }
    LimitsUpdateRequest &limitsUpdateRequest() {
      if (_xdr_field_number(type_) == 7)
        return limitsUpdateRequest_;
      throw xdr::xdr_wrong_union("_body_t: limitsUpdateRequest accessed when not selected");
    }
    const LimitsUpdateRequest &limitsUpdateRequest() const {
      if (_xdr_field_number(type_) == 7)
        return limitsUpdateRequest_;
      throw xdr::xdr_wrong_union("_body_t: limitsUpdateRequest accessed when not selected");
    }
    AMLAlertRequest &amlAlertRequest() {
      if (_xdr_field_number(type_) == 8)
        return amlAlertRequest_;
      throw xdr::xdr_wrong_union("_body_t: amlAlertRequest accessed when not selected");
    }
    const AMLAlertRequest &amlAlertRequest() const {
      if (_xdr_field_number(type_) == 8)
        return amlAlertRequest_;
      throw xdr::xdr_wrong_union("_body_t: amlAlertRequest accessed when not selected");
    }
    ChangeRoleRequest &changeRoleRequest() {
      if (_xdr_field_number(type_) == 9)
        return changeRoleRequest_;
      throw xdr::xdr_wrong_union("_body_t: changeRoleRequest accessed when not selected");
    }
    const ChangeRoleRequest &changeRoleRequest() const {
      if (_xdr_field_number(type_) == 9)
        return changeRoleRequest_;
      throw xdr::xdr_wrong_union("_body_t: changeRoleRequest accessed when not selected");
    }
    UpdateSaleDetailsRequest &updateSaleDetailsRequest() {
      if (_xdr_field_number(type_) == 10)
        return updateSaleDetailsRequest_;
      throw xdr::xdr_wrong_union("_body_t: updateSaleDetailsRequest accessed when not selected");
    }
    const UpdateSaleDetailsRequest &updateSaleDetailsRequest() const {
      if (_xdr_field_number(type_) == 10)
        return updateSaleDetailsRequest_;
      throw xdr::xdr_wrong_union("_body_t: updateSaleDetailsRequest accessed when not selected");
    }
    InvoiceRequest &invoiceRequest() {
      if (_xdr_field_number(type_) == 11)
        return invoiceRequest_;
      throw xdr::xdr_wrong_union("_body_t: invoiceRequest accessed when not selected");
    }
    const InvoiceRequest &invoiceRequest() const {
      if (_xdr_field_number(type_) == 11)
        return invoiceRequest_;
      throw xdr::xdr_wrong_union("_body_t: invoiceRequest accessed when not selected");
    }
    ContractRequest &contractRequest() {
      if (_xdr_field_number(type_) == 12)
        return contractRequest_;
      throw xdr::xdr_wrong_union("_body_t: contractRequest accessed when not selected");
    }
    const ContractRequest &contractRequest() const {
      if (_xdr_field_number(type_) == 12)
        return contractRequest_;
      throw xdr::xdr_wrong_union("_body_t: contractRequest accessed when not selected");
    }
    ASwapBidCreationRequest &aSwapBidCreationRequest() {
      if (_xdr_field_number(type_) == 13)
        return aSwapBidCreationRequest_;
      throw xdr::xdr_wrong_union("_body_t: aSwapBidCreationRequest accessed when not selected");
    }
    const ASwapBidCreationRequest &aSwapBidCreationRequest() const {
      if (_xdr_field_number(type_) == 13)
        return aSwapBidCreationRequest_;
      throw xdr::xdr_wrong_union("_body_t: aSwapBidCreationRequest accessed when not selected");
    }
    ASwapRequest &aSwapRequest() {
      if (_xdr_field_number(type_) == 14)
        return aSwapRequest_;
      throw xdr::xdr_wrong_union("_body_t: aSwapRequest accessed when not selected");
    }
    const ASwapRequest &aSwapRequest() const {
      if (_xdr_field_number(type_) == 14)
        return aSwapRequest_;
      throw xdr::xdr_wrong_union("_body_t: aSwapRequest accessed when not selected");
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

  uint64 requestID{};
  Hash hash{};
  AccountID requestor{};
  longstring rejectReason{};
  AccountID reviewer{};
  xdr::pointer<string64> reference{};
  int64 createdAt{};
  _body_t body{};
  TasksExt tasks{};
  _ext_t ext{};

  ReviewableRequestEntry() = default;
  template<typename _requestID_T,
           typename _hash_T,
           typename _requestor_T,
           typename _rejectReason_T,
           typename _reviewer_T,
           typename _reference_T,
           typename _createdAt_T,
           typename _body_T,
           typename _tasks_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<Hash, _hash_T>::value
                          && std::is_constructible<AccountID, _requestor_T>::value
                          && std::is_constructible<longstring, _rejectReason_T>::value
                          && std::is_constructible<AccountID, _reviewer_T>::value
                          && std::is_constructible<xdr::pointer<string64>, _reference_T>::value
                          && std::is_constructible<int64, _createdAt_T>::value
                          && std::is_constructible<_body_t, _body_T>::value
                          && std::is_constructible<TasksExt, _tasks_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ReviewableRequestEntry(_requestID_T &&_requestID,
                                  _hash_T &&_hash,
                                  _requestor_T &&_requestor,
                                  _rejectReason_T &&_rejectReason,
                                  _reviewer_T &&_reviewer,
                                  _reference_T &&_reference,
                                  _createdAt_T &&_createdAt,
                                  _body_T &&_body,
                                  _tasks_T &&_tasks,
                                  _ext_T &&_ext)
    : requestID(std::forward<_requestID_T>(_requestID)),
      hash(std::forward<_hash_T>(_hash)),
      requestor(std::forward<_requestor_T>(_requestor)),
      rejectReason(std::forward<_rejectReason_T>(_rejectReason)),
      reviewer(std::forward<_reviewer_T>(_reviewer)),
      reference(std::forward<_reference_T>(_reference)),
      createdAt(std::forward<_createdAt_T>(_createdAt)),
      body(std::forward<_body_T>(_body)),
      tasks(std::forward<_tasks_T>(_tasks)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ReviewableRequestEntry::_body_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ReviewableRequestEntry::_body_t;
  using case_type = ::stellar::ReviewableRequestEntry::_body_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "assetCreationRequest";
    case 2:
      return "assetUpdateRequest";
    case 3:
      return "preIssuanceRequest";
    case 4:
      return "issuanceRequest";
    case 5:
      return "withdrawalRequest";
    case 6:
      return "saleCreationRequest";
    case 7:
      return "limitsUpdateRequest";
    case 8:
      return "amlAlertRequest";
    case 9:
      return "changeRoleRequest";
    case 10:
      return "updateSaleDetailsRequest";
    case 11:
      return "invoiceRequest";
    case 12:
      return "contractRequest";
    case 13:
      return "aSwapBidCreationRequest";
    case 14:
      return "aSwapRequest";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ReviewableRequestEntry::_body_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in _body_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ReviewableRequestEntry::_body_t &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in _body_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ReviewableRequestEntry::_body_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.type(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ReviewableRequestEntry::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ReviewableRequestEntry::_ext_t;
  using case_type = ::stellar::ReviewableRequestEntry::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ReviewableRequestEntry::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ReviewableRequestEntry::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ReviewableRequestEntry::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ReviewableRequestEntry>
  : xdr_struct_base<field_ptr<::stellar::ReviewableRequestEntry,
                              decltype(::stellar::ReviewableRequestEntry::requestID),
                              &::stellar::ReviewableRequestEntry::requestID>,
                    field_ptr<::stellar::ReviewableRequestEntry,
                              decltype(::stellar::ReviewableRequestEntry::hash),
                              &::stellar::ReviewableRequestEntry::hash>,
                    field_ptr<::stellar::ReviewableRequestEntry,
                              decltype(::stellar::ReviewableRequestEntry::requestor),
                              &::stellar::ReviewableRequestEntry::requestor>,
                    field_ptr<::stellar::ReviewableRequestEntry,
                              decltype(::stellar::ReviewableRequestEntry::rejectReason),
                              &::stellar::ReviewableRequestEntry::rejectReason>,
                    field_ptr<::stellar::ReviewableRequestEntry,
                              decltype(::stellar::ReviewableRequestEntry::reviewer),
                              &::stellar::ReviewableRequestEntry::reviewer>,
                    field_ptr<::stellar::ReviewableRequestEntry,
                              decltype(::stellar::ReviewableRequestEntry::reference),
                              &::stellar::ReviewableRequestEntry::reference>,
                    field_ptr<::stellar::ReviewableRequestEntry,
                              decltype(::stellar::ReviewableRequestEntry::createdAt),
                              &::stellar::ReviewableRequestEntry::createdAt>,
                    field_ptr<::stellar::ReviewableRequestEntry,
                              decltype(::stellar::ReviewableRequestEntry::body),
                              &::stellar::ReviewableRequestEntry::body>,
                    field_ptr<::stellar::ReviewableRequestEntry,
                              decltype(::stellar::ReviewableRequestEntry::tasks),
                              &::stellar::ReviewableRequestEntry::tasks>,
                    field_ptr<::stellar::ReviewableRequestEntry,
                              decltype(::stellar::ReviewableRequestEntry::ext),
                              &::stellar::ReviewableRequestEntry::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ReviewableRequestEntry &obj) {
    archive(ar, obj.requestID, "requestID");
    archive(ar, obj.hash, "hash");
    archive(ar, obj.requestor, "requestor");
    archive(ar, obj.rejectReason, "rejectReason");
    archive(ar, obj.reviewer, "reviewer");
    archive(ar, obj.reference, "reference");
    archive(ar, obj.createdAt, "createdAt");
    archive(ar, obj.body, "body");
    archive(ar, obj.tasks, "tasks");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ReviewableRequestEntry &obj) {
    archive(ar, obj.requestID, "requestID");
    archive(ar, obj.hash, "hash");
    archive(ar, obj.requestor, "requestor");
    archive(ar, obj.rejectReason, "rejectReason");
    archive(ar, obj.reviewer, "reviewer");
    archive(ar, obj.reference, "reference");
    archive(ar, obj.createdAt, "createdAt");
    archive(ar, obj.body, "body");
    archive(ar, obj.tasks, "tasks");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

}

#endif // !__XDR_STELLAR_LEDGER_ENTRIES_REVIEWABLE_REQUEST_H_INCLUDED__
