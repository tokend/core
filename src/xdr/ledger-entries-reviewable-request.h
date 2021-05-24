// -*- C++ -*-
// Automatically generated from ledger-entries-reviewable-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_LEDGER_ENTRIES_REVIEWABLE_REQUEST_H_INCLUDED__
#define __XDR_LEDGER_ENTRIES_REVIEWABLE_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"
#include "xdr/reviewable-request-asset.h"
#include "xdr/reviewable-request-issuance.h"
#include "xdr/reviewable-request-withdrawal.h"
#include "xdr/reviewable-request-sale.h"
#include "xdr/reviewable-request-change-role.h"
#include "xdr/reviewable-request-limits-update.h"
#include "xdr/reviewable-request-AML-alert.h"
#include "xdr/reviewable-request-update-sale-details.h"
#include "xdr/reviewable-request-invoice.h"
#include "xdr/reviewable-request-contract.h"
#include "xdr/reviewable-request-atomic-swap-ask.h"
#include "xdr/reviewable-request-atomic-swap-bid.h"
#include "xdr/reviewable-request-create-poll.h"
#include "xdr/reviewable-request-kyc-recovery.h"
#include "xdr/reviewable-request-manage-offer.h"
#include "xdr/reviewable-request-payment.h"
#include "xdr/reviewable-request-redemption.h"
#include "xdr/reviewable-request-create-data.h"
#include "xdr/reviewable-request-update-data.h"
#include "xdr/reviewable-request-remove-data.h"
#include "xdr/reviewable-request-create-deferred-payment.h"
#include "xdr/reviewable-request-close-deferred-payment.h"

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
  CREATE_POLL = 14,
  CREATE_ATOMIC_SWAP_ASK = 16,
  CREATE_ATOMIC_SWAP_BID = 17,
  KYC_RECOVERY = 18,
  MANAGE_OFFER = 19,
  CREATE_PAYMENT = 20,
  PERFORM_REDEMPTION = 21,
  DATA_CREATION = 22,
  DATA_UPDATE = 23,
  DATA_REMOVE = 24,
  CREATE_DEFERRED_PAYMENT = 25,
  CLOSE_DEFERRED_PAYMENT = 26,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ReviewableRequestType>
  : xdr_integral_base<::stellar::ReviewableRequestType, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
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
    case ::stellar::ReviewableRequestType::CREATE_POLL:
      return "CREATE_POLL";
    case ::stellar::ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
      return "CREATE_ATOMIC_SWAP_ASK";
    case ::stellar::ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
      return "CREATE_ATOMIC_SWAP_BID";
    case ::stellar::ReviewableRequestType::KYC_RECOVERY:
      return "KYC_RECOVERY";
    case ::stellar::ReviewableRequestType::MANAGE_OFFER:
      return "MANAGE_OFFER";
    case ::stellar::ReviewableRequestType::CREATE_PAYMENT:
      return "CREATE_PAYMENT";
    case ::stellar::ReviewableRequestType::PERFORM_REDEMPTION:
      return "PERFORM_REDEMPTION";
    case ::stellar::ReviewableRequestType::DATA_CREATION:
      return "DATA_CREATION";
    case ::stellar::ReviewableRequestType::DATA_UPDATE:
      return "DATA_UPDATE";
    case ::stellar::ReviewableRequestType::DATA_REMOVE:
      return "DATA_REMOVE";
    case ::stellar::ReviewableRequestType::CREATE_DEFERRED_PAYMENT:
      return "CREATE_DEFERRED_PAYMENT";
    case ::stellar::ReviewableRequestType::CLOSE_DEFERRED_PAYMENT:
      return "CLOSE_DEFERRED_PAYMENT";
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
      (int32_t)::stellar::ReviewableRequestType::CREATE_POLL,
      (int32_t)::stellar::ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK,
      (int32_t)::stellar::ReviewableRequestType::CREATE_ATOMIC_SWAP_BID,
      (int32_t)::stellar::ReviewableRequestType::KYC_RECOVERY,
      (int32_t)::stellar::ReviewableRequestType::MANAGE_OFFER,
      (int32_t)::stellar::ReviewableRequestType::CREATE_PAYMENT,
      (int32_t)::stellar::ReviewableRequestType::PERFORM_REDEMPTION,
      (int32_t)::stellar::ReviewableRequestType::DATA_CREATION,
      (int32_t)::stellar::ReviewableRequestType::DATA_UPDATE,
      (int32_t)::stellar::ReviewableRequestType::DATA_REMOVE,
      (int32_t)::stellar::ReviewableRequestType::CREATE_DEFERRED_PAYMENT,
      (int32_t)::stellar::ReviewableRequestType::CLOSE_DEFERRED_PAYMENT
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct TasksExt  : xdr::xdr_abstract {
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

struct ReviewableRequestEntry  : xdr::xdr_abstract {
  struct _body_t : xdr::xdr_abstract {
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
      CreateAtomicSwapAskRequest createAtomicSwapAskRequest_;
      CreateAtomicSwapBidRequest createAtomicSwapBidRequest_;
      CreatePollRequest createPollRequest_;
      KYCRecoveryRequest kycRecoveryRequest_;
      ManageOfferRequest manageOfferRequest_;
      CreatePaymentRequest createPaymentRequest_;
      RedemptionRequest redemptionRequest_;
      DataCreationRequest dataCreationRequest_;
      DataUpdateRequest dataUpdateRequest_;
      DataRemoveRequest dataRemoveRequest_;
      CreateDeferredPaymentRequest createDeferredPaymentRequest_;
      CloseDeferredPaymentRequest closeDeferredPaymentRequest_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
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
        ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK,
        ReviewableRequestType::CREATE_ATOMIC_SWAP_BID,
        ReviewableRequestType::CREATE_POLL,
        ReviewableRequestType::KYC_RECOVERY,
        ReviewableRequestType::MANAGE_OFFER,
        ReviewableRequestType::CREATE_PAYMENT,
        ReviewableRequestType::PERFORM_REDEMPTION,
        ReviewableRequestType::DATA_CREATION,
        ReviewableRequestType::DATA_UPDATE,
        ReviewableRequestType::DATA_REMOVE,
        ReviewableRequestType::CREATE_DEFERRED_PAYMENT,
        ReviewableRequestType::CLOSE_DEFERRED_PAYMENT
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
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
        : which == (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK ? 13
        : which == (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID ? 14
        : which == (int32_t)ReviewableRequestType::CREATE_POLL ? 15
        : which == (int32_t)ReviewableRequestType::KYC_RECOVERY ? 16
        : which == (int32_t)ReviewableRequestType::MANAGE_OFFER ? 17
        : which == (int32_t)ReviewableRequestType::CREATE_PAYMENT ? 18
        : which == (int32_t)ReviewableRequestType::PERFORM_REDEMPTION ? 19
        : which == (int32_t)ReviewableRequestType::DATA_CREATION ? 20
        : which == (int32_t)ReviewableRequestType::DATA_UPDATE ? 21
        : which == (int32_t)ReviewableRequestType::DATA_REMOVE ? 22
        : which == (int32_t)ReviewableRequestType::CREATE_DEFERRED_PAYMENT ? 23
        : which == (int32_t)ReviewableRequestType::CLOSE_DEFERRED_PAYMENT ? 24
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
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
        _f(&_body_t::createAtomicSwapAskRequest_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
        _f(&_body_t::createAtomicSwapBidRequest_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::CREATE_POLL:
        _f(&_body_t::createPollRequest_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::KYC_RECOVERY:
        _f(&_body_t::kycRecoveryRequest_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::MANAGE_OFFER:
        _f(&_body_t::manageOfferRequest_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::CREATE_PAYMENT:
        _f(&_body_t::createPaymentRequest_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::PERFORM_REDEMPTION:
        _f(&_body_t::redemptionRequest_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::DATA_CREATION:
        _f(&_body_t::dataCreationRequest_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::DATA_UPDATE:
        _f(&_body_t::dataUpdateRequest_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::DATA_REMOVE:
        _f(&_body_t::dataRemoveRequest_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::CREATE_DEFERRED_PAYMENT:
        _f(&_body_t::createDeferredPaymentRequest_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ReviewableRequestType::CLOSE_DEFERRED_PAYMENT:
        _f(&_body_t::closeDeferredPaymentRequest_, std::forward<_A>(_a)...);
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
        type_ = which;switch (type_)
{
        case (int32_t)ReviewableRequestType::CREATE_ASSET:
new(&assetCreationRequest_) AssetCreationRequest{};
break;
        case (int32_t)ReviewableRequestType::UPDATE_ASSET:
new(&assetUpdateRequest_) AssetUpdateRequest{};
break;
        case (int32_t)ReviewableRequestType::CREATE_PRE_ISSUANCE:
new(&preIssuanceRequest_) PreIssuanceRequest{};
break;
        case (int32_t)ReviewableRequestType::CREATE_ISSUANCE:
new(&issuanceRequest_) IssuanceRequest{};
break;
        case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
new(&withdrawalRequest_) WithdrawalRequest{};
break;
        case (int32_t)ReviewableRequestType::CREATE_SALE:
new(&saleCreationRequest_) SaleCreationRequest{};
break;
        case (int32_t)ReviewableRequestType::UPDATE_LIMITS:
new(&limitsUpdateRequest_) LimitsUpdateRequest{};
break;
        case (int32_t)ReviewableRequestType::CREATE_AML_ALERT:
new(&amlAlertRequest_) AMLAlertRequest{};
break;
        case (int32_t)ReviewableRequestType::CHANGE_ROLE:
new(&changeRoleRequest_) ChangeRoleRequest{};
break;
        case (int32_t)ReviewableRequestType::UPDATE_SALE_DETAILS:
new(&updateSaleDetailsRequest_) UpdateSaleDetailsRequest{};
break;
        case (int32_t)ReviewableRequestType::CREATE_INVOICE:
new(&invoiceRequest_) InvoiceRequest{};
break;
        case (int32_t)ReviewableRequestType::MANAGE_CONTRACT:
new(&contractRequest_) ContractRequest{};
break;
        case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
new(&createAtomicSwapAskRequest_) CreateAtomicSwapAskRequest{};
break;
        case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
new(&createAtomicSwapBidRequest_) CreateAtomicSwapBidRequest{};
break;
        case (int32_t)ReviewableRequestType::CREATE_POLL:
new(&createPollRequest_) CreatePollRequest{};
break;
        case (int32_t)ReviewableRequestType::KYC_RECOVERY:
new(&kycRecoveryRequest_) KYCRecoveryRequest{};
break;
        case (int32_t)ReviewableRequestType::MANAGE_OFFER:
new(&manageOfferRequest_) ManageOfferRequest{};
break;
        case (int32_t)ReviewableRequestType::CREATE_PAYMENT:
new(&createPaymentRequest_) CreatePaymentRequest{};
break;
        case (int32_t)ReviewableRequestType::PERFORM_REDEMPTION:
new(&redemptionRequest_) RedemptionRequest{};
break;
        case (int32_t)ReviewableRequestType::DATA_CREATION:
new(&dataCreationRequest_) DataCreationRequest{};
break;
        case (int32_t)ReviewableRequestType::DATA_UPDATE:
new(&dataUpdateRequest_) DataUpdateRequest{};
break;
        case (int32_t)ReviewableRequestType::DATA_REMOVE:
new(&dataRemoveRequest_) DataRemoveRequest{};
break;
        case (int32_t)ReviewableRequestType::CREATE_DEFERRED_PAYMENT:
new(&createDeferredPaymentRequest_) CreateDeferredPaymentRequest{};
break;
        case (int32_t)ReviewableRequestType::CLOSE_DEFERRED_PAYMENT:
new(&closeDeferredPaymentRequest_) CloseDeferredPaymentRequest{};
break;
}

      }
      else
        type_ = which;
    }
    explicit _body_t(ReviewableRequestType which = ReviewableRequestType{}) : type_((int32_t)which) {
      switch (type_)
{
      case (int32_t)ReviewableRequestType::CREATE_ASSET:
new(&assetCreationRequest_) AssetCreationRequest{};
break;
      case (int32_t)ReviewableRequestType::UPDATE_ASSET:
new(&assetUpdateRequest_) AssetUpdateRequest{};
break;
      case (int32_t)ReviewableRequestType::CREATE_PRE_ISSUANCE:
new(&preIssuanceRequest_) PreIssuanceRequest{};
break;
      case (int32_t)ReviewableRequestType::CREATE_ISSUANCE:
new(&issuanceRequest_) IssuanceRequest{};
break;
      case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
new(&withdrawalRequest_) WithdrawalRequest{};
break;
      case (int32_t)ReviewableRequestType::CREATE_SALE:
new(&saleCreationRequest_) SaleCreationRequest{};
break;
      case (int32_t)ReviewableRequestType::UPDATE_LIMITS:
new(&limitsUpdateRequest_) LimitsUpdateRequest{};
break;
      case (int32_t)ReviewableRequestType::CREATE_AML_ALERT:
new(&amlAlertRequest_) AMLAlertRequest{};
break;
      case (int32_t)ReviewableRequestType::CHANGE_ROLE:
new(&changeRoleRequest_) ChangeRoleRequest{};
break;
      case (int32_t)ReviewableRequestType::UPDATE_SALE_DETAILS:
new(&updateSaleDetailsRequest_) UpdateSaleDetailsRequest{};
break;
      case (int32_t)ReviewableRequestType::CREATE_INVOICE:
new(&invoiceRequest_) InvoiceRequest{};
break;
      case (int32_t)ReviewableRequestType::MANAGE_CONTRACT:
new(&contractRequest_) ContractRequest{};
break;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
new(&createAtomicSwapAskRequest_) CreateAtomicSwapAskRequest{};
break;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
new(&createAtomicSwapBidRequest_) CreateAtomicSwapBidRequest{};
break;
      case (int32_t)ReviewableRequestType::CREATE_POLL:
new(&createPollRequest_) CreatePollRequest{};
break;
      case (int32_t)ReviewableRequestType::KYC_RECOVERY:
new(&kycRecoveryRequest_) KYCRecoveryRequest{};
break;
      case (int32_t)ReviewableRequestType::MANAGE_OFFER:
new(&manageOfferRequest_) ManageOfferRequest{};
break;
      case (int32_t)ReviewableRequestType::CREATE_PAYMENT:
new(&createPaymentRequest_) CreatePaymentRequest{};
break;
      case (int32_t)ReviewableRequestType::PERFORM_REDEMPTION:
new(&redemptionRequest_) RedemptionRequest{};
break;
      case (int32_t)ReviewableRequestType::DATA_CREATION:
new(&dataCreationRequest_) DataCreationRequest{};
break;
      case (int32_t)ReviewableRequestType::DATA_UPDATE:
new(&dataUpdateRequest_) DataUpdateRequest{};
break;
      case (int32_t)ReviewableRequestType::DATA_REMOVE:
new(&dataRemoveRequest_) DataRemoveRequest{};
break;
      case (int32_t)ReviewableRequestType::CREATE_DEFERRED_PAYMENT:
new(&createDeferredPaymentRequest_) CreateDeferredPaymentRequest{};
break;
      case (int32_t)ReviewableRequestType::CLOSE_DEFERRED_PAYMENT:
new(&closeDeferredPaymentRequest_) CloseDeferredPaymentRequest{};
break;
}

    }
    _body_t(const _body_t &source) : type_(source.type_) {
      switch (type_)
{
      case (int32_t)ReviewableRequestType::CREATE_ASSET:
new(&assetCreationRequest_) AssetCreationRequest(source.assetCreationRequest_);
break;
      case (int32_t)ReviewableRequestType::UPDATE_ASSET:
new(&assetUpdateRequest_) AssetUpdateRequest(source.assetUpdateRequest_);
break;
      case (int32_t)ReviewableRequestType::CREATE_PRE_ISSUANCE:
new(&preIssuanceRequest_) PreIssuanceRequest(source.preIssuanceRequest_);
break;
      case (int32_t)ReviewableRequestType::CREATE_ISSUANCE:
new(&issuanceRequest_) IssuanceRequest(source.issuanceRequest_);
break;
      case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
new(&withdrawalRequest_) WithdrawalRequest(source.withdrawalRequest_);
break;
      case (int32_t)ReviewableRequestType::CREATE_SALE:
new(&saleCreationRequest_) SaleCreationRequest(source.saleCreationRequest_);
break;
      case (int32_t)ReviewableRequestType::UPDATE_LIMITS:
new(&limitsUpdateRequest_) LimitsUpdateRequest(source.limitsUpdateRequest_);
break;
      case (int32_t)ReviewableRequestType::CREATE_AML_ALERT:
new(&amlAlertRequest_) AMLAlertRequest(source.amlAlertRequest_);
break;
      case (int32_t)ReviewableRequestType::CHANGE_ROLE:
new(&changeRoleRequest_) ChangeRoleRequest(source.changeRoleRequest_);
break;
      case (int32_t)ReviewableRequestType::UPDATE_SALE_DETAILS:
new(&updateSaleDetailsRequest_) UpdateSaleDetailsRequest(source.updateSaleDetailsRequest_);
break;
      case (int32_t)ReviewableRequestType::CREATE_INVOICE:
new(&invoiceRequest_) InvoiceRequest(source.invoiceRequest_);
break;
      case (int32_t)ReviewableRequestType::MANAGE_CONTRACT:
new(&contractRequest_) ContractRequest(source.contractRequest_);
break;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
new(&createAtomicSwapAskRequest_) CreateAtomicSwapAskRequest(source.createAtomicSwapAskRequest_);
break;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
new(&createAtomicSwapBidRequest_) CreateAtomicSwapBidRequest(source.createAtomicSwapBidRequest_);
break;
      case (int32_t)ReviewableRequestType::CREATE_POLL:
new(&createPollRequest_) CreatePollRequest(source.createPollRequest_);
break;
      case (int32_t)ReviewableRequestType::KYC_RECOVERY:
new(&kycRecoveryRequest_) KYCRecoveryRequest(source.kycRecoveryRequest_);
break;
      case (int32_t)ReviewableRequestType::MANAGE_OFFER:
new(&manageOfferRequest_) ManageOfferRequest(source.manageOfferRequest_);
break;
      case (int32_t)ReviewableRequestType::CREATE_PAYMENT:
new(&createPaymentRequest_) CreatePaymentRequest(source.createPaymentRequest_);
break;
      case (int32_t)ReviewableRequestType::PERFORM_REDEMPTION:
new(&redemptionRequest_) RedemptionRequest(source.redemptionRequest_);
break;
      case (int32_t)ReviewableRequestType::DATA_CREATION:
new(&dataCreationRequest_) DataCreationRequest(source.dataCreationRequest_);
break;
      case (int32_t)ReviewableRequestType::DATA_UPDATE:
new(&dataUpdateRequest_) DataUpdateRequest(source.dataUpdateRequest_);
break;
      case (int32_t)ReviewableRequestType::DATA_REMOVE:
new(&dataRemoveRequest_) DataRemoveRequest(source.dataRemoveRequest_);
break;
      case (int32_t)ReviewableRequestType::CREATE_DEFERRED_PAYMENT:
new(&createDeferredPaymentRequest_) CreateDeferredPaymentRequest(source.createDeferredPaymentRequest_);
break;
      case (int32_t)ReviewableRequestType::CLOSE_DEFERRED_PAYMENT:
new(&closeDeferredPaymentRequest_) CloseDeferredPaymentRequest(source.closeDeferredPaymentRequest_);
break;
}

    }
    _body_t(_body_t &&source) : type_(source.type_) {
      switch (type_)
{
      case (int32_t)ReviewableRequestType::CREATE_ASSET:
new(&assetCreationRequest_) AssetCreationRequest(std::move(source.assetCreationRequest_));
break;
      case (int32_t)ReviewableRequestType::UPDATE_ASSET:
new(&assetUpdateRequest_) AssetUpdateRequest(std::move(source.assetUpdateRequest_));
break;
      case (int32_t)ReviewableRequestType::CREATE_PRE_ISSUANCE:
new(&preIssuanceRequest_) PreIssuanceRequest(std::move(source.preIssuanceRequest_));
break;
      case (int32_t)ReviewableRequestType::CREATE_ISSUANCE:
new(&issuanceRequest_) IssuanceRequest(std::move(source.issuanceRequest_));
break;
      case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
new(&withdrawalRequest_) WithdrawalRequest(std::move(source.withdrawalRequest_));
break;
      case (int32_t)ReviewableRequestType::CREATE_SALE:
new(&saleCreationRequest_) SaleCreationRequest(std::move(source.saleCreationRequest_));
break;
      case (int32_t)ReviewableRequestType::UPDATE_LIMITS:
new(&limitsUpdateRequest_) LimitsUpdateRequest(std::move(source.limitsUpdateRequest_));
break;
      case (int32_t)ReviewableRequestType::CREATE_AML_ALERT:
new(&amlAlertRequest_) AMLAlertRequest(std::move(source.amlAlertRequest_));
break;
      case (int32_t)ReviewableRequestType::CHANGE_ROLE:
new(&changeRoleRequest_) ChangeRoleRequest(std::move(source.changeRoleRequest_));
break;
      case (int32_t)ReviewableRequestType::UPDATE_SALE_DETAILS:
new(&updateSaleDetailsRequest_) UpdateSaleDetailsRequest(std::move(source.updateSaleDetailsRequest_));
break;
      case (int32_t)ReviewableRequestType::CREATE_INVOICE:
new(&invoiceRequest_) InvoiceRequest(std::move(source.invoiceRequest_));
break;
      case (int32_t)ReviewableRequestType::MANAGE_CONTRACT:
new(&contractRequest_) ContractRequest(std::move(source.contractRequest_));
break;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
new(&createAtomicSwapAskRequest_) CreateAtomicSwapAskRequest(std::move(source.createAtomicSwapAskRequest_));
break;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
new(&createAtomicSwapBidRequest_) CreateAtomicSwapBidRequest(std::move(source.createAtomicSwapBidRequest_));
break;
      case (int32_t)ReviewableRequestType::CREATE_POLL:
new(&createPollRequest_) CreatePollRequest(std::move(source.createPollRequest_));
break;
      case (int32_t)ReviewableRequestType::KYC_RECOVERY:
new(&kycRecoveryRequest_) KYCRecoveryRequest(std::move(source.kycRecoveryRequest_));
break;
      case (int32_t)ReviewableRequestType::MANAGE_OFFER:
new(&manageOfferRequest_) ManageOfferRequest(std::move(source.manageOfferRequest_));
break;
      case (int32_t)ReviewableRequestType::CREATE_PAYMENT:
new(&createPaymentRequest_) CreatePaymentRequest(std::move(source.createPaymentRequest_));
break;
      case (int32_t)ReviewableRequestType::PERFORM_REDEMPTION:
new(&redemptionRequest_) RedemptionRequest(std::move(source.redemptionRequest_));
break;
      case (int32_t)ReviewableRequestType::DATA_CREATION:
new(&dataCreationRequest_) DataCreationRequest(std::move(source.dataCreationRequest_));
break;
      case (int32_t)ReviewableRequestType::DATA_UPDATE:
new(&dataUpdateRequest_) DataUpdateRequest(std::move(source.dataUpdateRequest_));
break;
      case (int32_t)ReviewableRequestType::DATA_REMOVE:
new(&dataRemoveRequest_) DataRemoveRequest(std::move(source.dataRemoveRequest_));
break;
      case (int32_t)ReviewableRequestType::CREATE_DEFERRED_PAYMENT:
new(&createDeferredPaymentRequest_) CreateDeferredPaymentRequest(std::move(source.createDeferredPaymentRequest_));
break;
      case (int32_t)ReviewableRequestType::CLOSE_DEFERRED_PAYMENT:
new(&closeDeferredPaymentRequest_) CloseDeferredPaymentRequest(std::move(source.closeDeferredPaymentRequest_));
break;
}

    }
    ~_body_t() {
switch (type_)
{
    case (int32_t)ReviewableRequestType::CREATE_ASSET:
assetCreationRequest_.~AssetCreationRequest();
break;
    case (int32_t)ReviewableRequestType::UPDATE_ASSET:
assetUpdateRequest_.~AssetUpdateRequest();
break;
    case (int32_t)ReviewableRequestType::CREATE_PRE_ISSUANCE:
preIssuanceRequest_.~PreIssuanceRequest();
break;
    case (int32_t)ReviewableRequestType::CREATE_ISSUANCE:
issuanceRequest_.~IssuanceRequest();
break;
    case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
withdrawalRequest_.~WithdrawalRequest();
break;
    case (int32_t)ReviewableRequestType::CREATE_SALE:
saleCreationRequest_.~SaleCreationRequest();
break;
    case (int32_t)ReviewableRequestType::UPDATE_LIMITS:
limitsUpdateRequest_.~LimitsUpdateRequest();
break;
    case (int32_t)ReviewableRequestType::CREATE_AML_ALERT:
amlAlertRequest_.~AMLAlertRequest();
break;
    case (int32_t)ReviewableRequestType::CHANGE_ROLE:
changeRoleRequest_.~ChangeRoleRequest();
break;
    case (int32_t)ReviewableRequestType::UPDATE_SALE_DETAILS:
updateSaleDetailsRequest_.~UpdateSaleDetailsRequest();
break;
    case (int32_t)ReviewableRequestType::CREATE_INVOICE:
invoiceRequest_.~InvoiceRequest();
break;
    case (int32_t)ReviewableRequestType::MANAGE_CONTRACT:
contractRequest_.~ContractRequest();
break;
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
createAtomicSwapAskRequest_.~CreateAtomicSwapAskRequest();
break;
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
createAtomicSwapBidRequest_.~CreateAtomicSwapBidRequest();
break;
    case (int32_t)ReviewableRequestType::CREATE_POLL:
createPollRequest_.~CreatePollRequest();
break;
    case (int32_t)ReviewableRequestType::KYC_RECOVERY:
kycRecoveryRequest_.~KYCRecoveryRequest();
break;
    case (int32_t)ReviewableRequestType::MANAGE_OFFER:
manageOfferRequest_.~ManageOfferRequest();
break;
    case (int32_t)ReviewableRequestType::CREATE_PAYMENT:
createPaymentRequest_.~CreatePaymentRequest();
break;
    case (int32_t)ReviewableRequestType::PERFORM_REDEMPTION:
redemptionRequest_.~RedemptionRequest();
break;
    case (int32_t)ReviewableRequestType::DATA_CREATION:
dataCreationRequest_.~DataCreationRequest();
break;
    case (int32_t)ReviewableRequestType::DATA_UPDATE:
dataUpdateRequest_.~DataUpdateRequest();
break;
    case (int32_t)ReviewableRequestType::DATA_REMOVE:
dataRemoveRequest_.~DataRemoveRequest();
break;
    case (int32_t)ReviewableRequestType::CREATE_DEFERRED_PAYMENT:
createDeferredPaymentRequest_.~CreateDeferredPaymentRequest();
break;
    case (int32_t)ReviewableRequestType::CLOSE_DEFERRED_PAYMENT:
closeDeferredPaymentRequest_.~CloseDeferredPaymentRequest();
break;
}
}

    _body_t &operator=(const _body_t &source) {
      if (type_ == source.type_)
{
switch (type_)
{
      case (int32_t)ReviewableRequestType::CREATE_ASSET:
assetCreationRequest_ = source.assetCreationRequest_;
break;
      case (int32_t)ReviewableRequestType::UPDATE_ASSET:
assetUpdateRequest_ = source.assetUpdateRequest_;
break;
      case (int32_t)ReviewableRequestType::CREATE_PRE_ISSUANCE:
preIssuanceRequest_ = source.preIssuanceRequest_;
break;
      case (int32_t)ReviewableRequestType::CREATE_ISSUANCE:
issuanceRequest_ = source.issuanceRequest_;
break;
      case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
withdrawalRequest_ = source.withdrawalRequest_;
break;
      case (int32_t)ReviewableRequestType::CREATE_SALE:
saleCreationRequest_ = source.saleCreationRequest_;
break;
      case (int32_t)ReviewableRequestType::UPDATE_LIMITS:
limitsUpdateRequest_ = source.limitsUpdateRequest_;
break;
      case (int32_t)ReviewableRequestType::CREATE_AML_ALERT:
amlAlertRequest_ = source.amlAlertRequest_;
break;
      case (int32_t)ReviewableRequestType::CHANGE_ROLE:
changeRoleRequest_ = source.changeRoleRequest_;
break;
      case (int32_t)ReviewableRequestType::UPDATE_SALE_DETAILS:
updateSaleDetailsRequest_ = source.updateSaleDetailsRequest_;
break;
      case (int32_t)ReviewableRequestType::CREATE_INVOICE:
invoiceRequest_ = source.invoiceRequest_;
break;
      case (int32_t)ReviewableRequestType::MANAGE_CONTRACT:
contractRequest_ = source.contractRequest_;
break;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
createAtomicSwapAskRequest_ = source.createAtomicSwapAskRequest_;
break;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
createAtomicSwapBidRequest_ = source.createAtomicSwapBidRequest_;
break;
      case (int32_t)ReviewableRequestType::CREATE_POLL:
createPollRequest_ = source.createPollRequest_;
break;
      case (int32_t)ReviewableRequestType::KYC_RECOVERY:
kycRecoveryRequest_ = source.kycRecoveryRequest_;
break;
      case (int32_t)ReviewableRequestType::MANAGE_OFFER:
manageOfferRequest_ = source.manageOfferRequest_;
break;
      case (int32_t)ReviewableRequestType::CREATE_PAYMENT:
createPaymentRequest_ = source.createPaymentRequest_;
break;
      case (int32_t)ReviewableRequestType::PERFORM_REDEMPTION:
redemptionRequest_ = source.redemptionRequest_;
break;
      case (int32_t)ReviewableRequestType::DATA_CREATION:
dataCreationRequest_ = source.dataCreationRequest_;
break;
      case (int32_t)ReviewableRequestType::DATA_UPDATE:
dataUpdateRequest_ = source.dataUpdateRequest_;
break;
      case (int32_t)ReviewableRequestType::DATA_REMOVE:
dataRemoveRequest_ = source.dataRemoveRequest_;
break;
      case (int32_t)ReviewableRequestType::CREATE_DEFERRED_PAYMENT:
createDeferredPaymentRequest_ = source.createDeferredPaymentRequest_;
break;
      case (int32_t)ReviewableRequestType::CLOSE_DEFERRED_PAYMENT:
closeDeferredPaymentRequest_ = source.closeDeferredPaymentRequest_;
break;
}
}
else {this->~_body_t();
      type_ = source.type_;
switch (type_)
{
      case (int32_t)ReviewableRequestType::CREATE_ASSET:
new(&assetCreationRequest_) AssetCreationRequest(source.assetCreationRequest_);
break;
      case (int32_t)ReviewableRequestType::UPDATE_ASSET:
new(&assetUpdateRequest_) AssetUpdateRequest(source.assetUpdateRequest_);
break;
      case (int32_t)ReviewableRequestType::CREATE_PRE_ISSUANCE:
new(&preIssuanceRequest_) PreIssuanceRequest(source.preIssuanceRequest_);
break;
      case (int32_t)ReviewableRequestType::CREATE_ISSUANCE:
new(&issuanceRequest_) IssuanceRequest(source.issuanceRequest_);
break;
      case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
new(&withdrawalRequest_) WithdrawalRequest(source.withdrawalRequest_);
break;
      case (int32_t)ReviewableRequestType::CREATE_SALE:
new(&saleCreationRequest_) SaleCreationRequest(source.saleCreationRequest_);
break;
      case (int32_t)ReviewableRequestType::UPDATE_LIMITS:
new(&limitsUpdateRequest_) LimitsUpdateRequest(source.limitsUpdateRequest_);
break;
      case (int32_t)ReviewableRequestType::CREATE_AML_ALERT:
new(&amlAlertRequest_) AMLAlertRequest(source.amlAlertRequest_);
break;
      case (int32_t)ReviewableRequestType::CHANGE_ROLE:
new(&changeRoleRequest_) ChangeRoleRequest(source.changeRoleRequest_);
break;
      case (int32_t)ReviewableRequestType::UPDATE_SALE_DETAILS:
new(&updateSaleDetailsRequest_) UpdateSaleDetailsRequest(source.updateSaleDetailsRequest_);
break;
      case (int32_t)ReviewableRequestType::CREATE_INVOICE:
new(&invoiceRequest_) InvoiceRequest(source.invoiceRequest_);
break;
      case (int32_t)ReviewableRequestType::MANAGE_CONTRACT:
new(&contractRequest_) ContractRequest(source.contractRequest_);
break;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
new(&createAtomicSwapAskRequest_) CreateAtomicSwapAskRequest(source.createAtomicSwapAskRequest_);
break;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
new(&createAtomicSwapBidRequest_) CreateAtomicSwapBidRequest(source.createAtomicSwapBidRequest_);
break;
      case (int32_t)ReviewableRequestType::CREATE_POLL:
new(&createPollRequest_) CreatePollRequest(source.createPollRequest_);
break;
      case (int32_t)ReviewableRequestType::KYC_RECOVERY:
new(&kycRecoveryRequest_) KYCRecoveryRequest(source.kycRecoveryRequest_);
break;
      case (int32_t)ReviewableRequestType::MANAGE_OFFER:
new(&manageOfferRequest_) ManageOfferRequest(source.manageOfferRequest_);
break;
      case (int32_t)ReviewableRequestType::CREATE_PAYMENT:
new(&createPaymentRequest_) CreatePaymentRequest(source.createPaymentRequest_);
break;
      case (int32_t)ReviewableRequestType::PERFORM_REDEMPTION:
new(&redemptionRequest_) RedemptionRequest(source.redemptionRequest_);
break;
      case (int32_t)ReviewableRequestType::DATA_CREATION:
new(&dataCreationRequest_) DataCreationRequest(source.dataCreationRequest_);
break;
      case (int32_t)ReviewableRequestType::DATA_UPDATE:
new(&dataUpdateRequest_) DataUpdateRequest(source.dataUpdateRequest_);
break;
      case (int32_t)ReviewableRequestType::DATA_REMOVE:
new(&dataRemoveRequest_) DataRemoveRequest(source.dataRemoveRequest_);
break;
      case (int32_t)ReviewableRequestType::CREATE_DEFERRED_PAYMENT:
new(&createDeferredPaymentRequest_) CreateDeferredPaymentRequest(source.createDeferredPaymentRequest_);
break;
      case (int32_t)ReviewableRequestType::CLOSE_DEFERRED_PAYMENT:
new(&closeDeferredPaymentRequest_) CloseDeferredPaymentRequest(source.closeDeferredPaymentRequest_);
break;
}
}
      return *this;
    }
    _body_t &operator=(_body_t &&source) {
      if (type_ == source.type_)
{
switch (type_)
{
      case (int32_t)ReviewableRequestType::CREATE_ASSET:
assetCreationRequest_ = std::move(source.assetCreationRequest_);
break;
      case (int32_t)ReviewableRequestType::UPDATE_ASSET:
assetUpdateRequest_ = std::move(source.assetUpdateRequest_);
break;
      case (int32_t)ReviewableRequestType::CREATE_PRE_ISSUANCE:
preIssuanceRequest_ = std::move(source.preIssuanceRequest_);
break;
      case (int32_t)ReviewableRequestType::CREATE_ISSUANCE:
issuanceRequest_ = std::move(source.issuanceRequest_);
break;
      case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
withdrawalRequest_ = std::move(source.withdrawalRequest_);
break;
      case (int32_t)ReviewableRequestType::CREATE_SALE:
saleCreationRequest_ = std::move(source.saleCreationRequest_);
break;
      case (int32_t)ReviewableRequestType::UPDATE_LIMITS:
limitsUpdateRequest_ = std::move(source.limitsUpdateRequest_);
break;
      case (int32_t)ReviewableRequestType::CREATE_AML_ALERT:
amlAlertRequest_ = std::move(source.amlAlertRequest_);
break;
      case (int32_t)ReviewableRequestType::CHANGE_ROLE:
changeRoleRequest_ = std::move(source.changeRoleRequest_);
break;
      case (int32_t)ReviewableRequestType::UPDATE_SALE_DETAILS:
updateSaleDetailsRequest_ = std::move(source.updateSaleDetailsRequest_);
break;
      case (int32_t)ReviewableRequestType::CREATE_INVOICE:
invoiceRequest_ = std::move(source.invoiceRequest_);
break;
      case (int32_t)ReviewableRequestType::MANAGE_CONTRACT:
contractRequest_ = std::move(source.contractRequest_);
break;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
createAtomicSwapAskRequest_ = std::move(source.createAtomicSwapAskRequest_);
break;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
createAtomicSwapBidRequest_ = std::move(source.createAtomicSwapBidRequest_);
break;
      case (int32_t)ReviewableRequestType::CREATE_POLL:
createPollRequest_ = std::move(source.createPollRequest_);
break;
      case (int32_t)ReviewableRequestType::KYC_RECOVERY:
kycRecoveryRequest_ = std::move(source.kycRecoveryRequest_);
break;
      case (int32_t)ReviewableRequestType::MANAGE_OFFER:
manageOfferRequest_ = std::move(source.manageOfferRequest_);
break;
      case (int32_t)ReviewableRequestType::CREATE_PAYMENT:
createPaymentRequest_ = std::move(source.createPaymentRequest_);
break;
      case (int32_t)ReviewableRequestType::PERFORM_REDEMPTION:
redemptionRequest_ = std::move(source.redemptionRequest_);
break;
      case (int32_t)ReviewableRequestType::DATA_CREATION:
dataCreationRequest_ = std::move(source.dataCreationRequest_);
break;
      case (int32_t)ReviewableRequestType::DATA_UPDATE:
dataUpdateRequest_ = std::move(source.dataUpdateRequest_);
break;
      case (int32_t)ReviewableRequestType::DATA_REMOVE:
dataRemoveRequest_ = std::move(source.dataRemoveRequest_);
break;
      case (int32_t)ReviewableRequestType::CREATE_DEFERRED_PAYMENT:
createDeferredPaymentRequest_ = std::move(source.createDeferredPaymentRequest_);
break;
      case (int32_t)ReviewableRequestType::CLOSE_DEFERRED_PAYMENT:
closeDeferredPaymentRequest_ = std::move(source.closeDeferredPaymentRequest_);
break;
}
}
else {this->~_body_t();
      type_ = std::move(source.type_);
switch (type_)
{
      case (int32_t)ReviewableRequestType::CREATE_ASSET:
new(&assetCreationRequest_) AssetCreationRequest(std::move(source.assetCreationRequest_));
break;
      case (int32_t)ReviewableRequestType::UPDATE_ASSET:
new(&assetUpdateRequest_) AssetUpdateRequest(std::move(source.assetUpdateRequest_));
break;
      case (int32_t)ReviewableRequestType::CREATE_PRE_ISSUANCE:
new(&preIssuanceRequest_) PreIssuanceRequest(std::move(source.preIssuanceRequest_));
break;
      case (int32_t)ReviewableRequestType::CREATE_ISSUANCE:
new(&issuanceRequest_) IssuanceRequest(std::move(source.issuanceRequest_));
break;
      case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
new(&withdrawalRequest_) WithdrawalRequest(std::move(source.withdrawalRequest_));
break;
      case (int32_t)ReviewableRequestType::CREATE_SALE:
new(&saleCreationRequest_) SaleCreationRequest(std::move(source.saleCreationRequest_));
break;
      case (int32_t)ReviewableRequestType::UPDATE_LIMITS:
new(&limitsUpdateRequest_) LimitsUpdateRequest(std::move(source.limitsUpdateRequest_));
break;
      case (int32_t)ReviewableRequestType::CREATE_AML_ALERT:
new(&amlAlertRequest_) AMLAlertRequest(std::move(source.amlAlertRequest_));
break;
      case (int32_t)ReviewableRequestType::CHANGE_ROLE:
new(&changeRoleRequest_) ChangeRoleRequest(std::move(source.changeRoleRequest_));
break;
      case (int32_t)ReviewableRequestType::UPDATE_SALE_DETAILS:
new(&updateSaleDetailsRequest_) UpdateSaleDetailsRequest(std::move(source.updateSaleDetailsRequest_));
break;
      case (int32_t)ReviewableRequestType::CREATE_INVOICE:
new(&invoiceRequest_) InvoiceRequest(std::move(source.invoiceRequest_));
break;
      case (int32_t)ReviewableRequestType::MANAGE_CONTRACT:
new(&contractRequest_) ContractRequest(std::move(source.contractRequest_));
break;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
new(&createAtomicSwapAskRequest_) CreateAtomicSwapAskRequest(std::move(source.createAtomicSwapAskRequest_));
break;
      case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
new(&createAtomicSwapBidRequest_) CreateAtomicSwapBidRequest(std::move(source.createAtomicSwapBidRequest_));
break;
      case (int32_t)ReviewableRequestType::CREATE_POLL:
new(&createPollRequest_) CreatePollRequest(std::move(source.createPollRequest_));
break;
      case (int32_t)ReviewableRequestType::KYC_RECOVERY:
new(&kycRecoveryRequest_) KYCRecoveryRequest(std::move(source.kycRecoveryRequest_));
break;
      case (int32_t)ReviewableRequestType::MANAGE_OFFER:
new(&manageOfferRequest_) ManageOfferRequest(std::move(source.manageOfferRequest_));
break;
      case (int32_t)ReviewableRequestType::CREATE_PAYMENT:
new(&createPaymentRequest_) CreatePaymentRequest(std::move(source.createPaymentRequest_));
break;
      case (int32_t)ReviewableRequestType::PERFORM_REDEMPTION:
new(&redemptionRequest_) RedemptionRequest(std::move(source.redemptionRequest_));
break;
      case (int32_t)ReviewableRequestType::DATA_CREATION:
new(&dataCreationRequest_) DataCreationRequest(std::move(source.dataCreationRequest_));
break;
      case (int32_t)ReviewableRequestType::DATA_UPDATE:
new(&dataUpdateRequest_) DataUpdateRequest(std::move(source.dataUpdateRequest_));
break;
      case (int32_t)ReviewableRequestType::DATA_REMOVE:
new(&dataRemoveRequest_) DataRemoveRequest(std::move(source.dataRemoveRequest_));
break;
      case (int32_t)ReviewableRequestType::CREATE_DEFERRED_PAYMENT:
new(&createDeferredPaymentRequest_) CreateDeferredPaymentRequest(std::move(source.createDeferredPaymentRequest_));
break;
      case (int32_t)ReviewableRequestType::CLOSE_DEFERRED_PAYMENT:
new(&closeDeferredPaymentRequest_) CloseDeferredPaymentRequest(std::move(source.closeDeferredPaymentRequest_));
break;
}
}
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
    CreateAtomicSwapAskRequest &createAtomicSwapAskRequest() {
      if (_xdr_field_number(type_) == 13)
        return createAtomicSwapAskRequest_;
      throw xdr::xdr_wrong_union("_body_t: createAtomicSwapAskRequest accessed when not selected");
    }
    const CreateAtomicSwapAskRequest &createAtomicSwapAskRequest() const {
      if (_xdr_field_number(type_) == 13)
        return createAtomicSwapAskRequest_;
      throw xdr::xdr_wrong_union("_body_t: createAtomicSwapAskRequest accessed when not selected");
    }
    CreateAtomicSwapBidRequest &createAtomicSwapBidRequest() {
      if (_xdr_field_number(type_) == 14)
        return createAtomicSwapBidRequest_;
      throw xdr::xdr_wrong_union("_body_t: createAtomicSwapBidRequest accessed when not selected");
    }
    const CreateAtomicSwapBidRequest &createAtomicSwapBidRequest() const {
      if (_xdr_field_number(type_) == 14)
        return createAtomicSwapBidRequest_;
      throw xdr::xdr_wrong_union("_body_t: createAtomicSwapBidRequest accessed when not selected");
    }
    CreatePollRequest &createPollRequest() {
      if (_xdr_field_number(type_) == 15)
        return createPollRequest_;
      throw xdr::xdr_wrong_union("_body_t: createPollRequest accessed when not selected");
    }
    const CreatePollRequest &createPollRequest() const {
      if (_xdr_field_number(type_) == 15)
        return createPollRequest_;
      throw xdr::xdr_wrong_union("_body_t: createPollRequest accessed when not selected");
    }
    KYCRecoveryRequest &kycRecoveryRequest() {
      if (_xdr_field_number(type_) == 16)
        return kycRecoveryRequest_;
      throw xdr::xdr_wrong_union("_body_t: kycRecoveryRequest accessed when not selected");
    }
    const KYCRecoveryRequest &kycRecoveryRequest() const {
      if (_xdr_field_number(type_) == 16)
        return kycRecoveryRequest_;
      throw xdr::xdr_wrong_union("_body_t: kycRecoveryRequest accessed when not selected");
    }
    ManageOfferRequest &manageOfferRequest() {
      if (_xdr_field_number(type_) == 17)
        return manageOfferRequest_;
      throw xdr::xdr_wrong_union("_body_t: manageOfferRequest accessed when not selected");
    }
    const ManageOfferRequest &manageOfferRequest() const {
      if (_xdr_field_number(type_) == 17)
        return manageOfferRequest_;
      throw xdr::xdr_wrong_union("_body_t: manageOfferRequest accessed when not selected");
    }
    CreatePaymentRequest &createPaymentRequest() {
      if (_xdr_field_number(type_) == 18)
        return createPaymentRequest_;
      throw xdr::xdr_wrong_union("_body_t: createPaymentRequest accessed when not selected");
    }
    const CreatePaymentRequest &createPaymentRequest() const {
      if (_xdr_field_number(type_) == 18)
        return createPaymentRequest_;
      throw xdr::xdr_wrong_union("_body_t: createPaymentRequest accessed when not selected");
    }
    RedemptionRequest &redemptionRequest() {
      if (_xdr_field_number(type_) == 19)
        return redemptionRequest_;
      throw xdr::xdr_wrong_union("_body_t: redemptionRequest accessed when not selected");
    }
    const RedemptionRequest &redemptionRequest() const {
      if (_xdr_field_number(type_) == 19)
        return redemptionRequest_;
      throw xdr::xdr_wrong_union("_body_t: redemptionRequest accessed when not selected");
    }
    DataCreationRequest &dataCreationRequest() {
      if (_xdr_field_number(type_) == 20)
        return dataCreationRequest_;
      throw xdr::xdr_wrong_union("_body_t: dataCreationRequest accessed when not selected");
    }
    const DataCreationRequest &dataCreationRequest() const {
      if (_xdr_field_number(type_) == 20)
        return dataCreationRequest_;
      throw xdr::xdr_wrong_union("_body_t: dataCreationRequest accessed when not selected");
    }
    DataUpdateRequest &dataUpdateRequest() {
      if (_xdr_field_number(type_) == 21)
        return dataUpdateRequest_;
      throw xdr::xdr_wrong_union("_body_t: dataUpdateRequest accessed when not selected");
    }
    const DataUpdateRequest &dataUpdateRequest() const {
      if (_xdr_field_number(type_) == 21)
        return dataUpdateRequest_;
      throw xdr::xdr_wrong_union("_body_t: dataUpdateRequest accessed when not selected");
    }
    DataRemoveRequest &dataRemoveRequest() {
      if (_xdr_field_number(type_) == 22)
        return dataRemoveRequest_;
      throw xdr::xdr_wrong_union("_body_t: dataRemoveRequest accessed when not selected");
    }
    const DataRemoveRequest &dataRemoveRequest() const {
      if (_xdr_field_number(type_) == 22)
        return dataRemoveRequest_;
      throw xdr::xdr_wrong_union("_body_t: dataRemoveRequest accessed when not selected");
    }
    CreateDeferredPaymentRequest &createDeferredPaymentRequest() {
      if (_xdr_field_number(type_) == 23)
        return createDeferredPaymentRequest_;
      throw xdr::xdr_wrong_union("_body_t: createDeferredPaymentRequest accessed when not selected");
    }
    const CreateDeferredPaymentRequest &createDeferredPaymentRequest() const {
      if (_xdr_field_number(type_) == 23)
        return createDeferredPaymentRequest_;
      throw xdr::xdr_wrong_union("_body_t: createDeferredPaymentRequest accessed when not selected");
    }
    CloseDeferredPaymentRequest &closeDeferredPaymentRequest() {
      if (_xdr_field_number(type_) == 24)
        return closeDeferredPaymentRequest_;
      throw xdr::xdr_wrong_union("_body_t: closeDeferredPaymentRequest accessed when not selected");
    }
    const CloseDeferredPaymentRequest &closeDeferredPaymentRequest() const {
      if (_xdr_field_number(type_) == 24)
        return closeDeferredPaymentRequest_;
      throw xdr::xdr_wrong_union("_body_t: closeDeferredPaymentRequest accessed when not selected");
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

#endif // !__XDR_LEDGER_ENTRIES_REVIEWABLE_REQUEST_H_INCLUDED__
