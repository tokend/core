// -*- C++ -*-
// Automatically generated from transaction.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_TRANSACTION_H_INCLUDED__
#define __XDR_TRANSACTION_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/ledger-entries.h"
#include "xdr/operation-create-account.h"
#include "xdr/operation-set-fees.h"
#include "xdr/operation-create-withdrawal-request.h"
#include "xdr/operation-manage-balance.h"
#include "xdr/operation-manage-asset.h"
#include "xdr/operation-create-preissuance-request.h"
#include "xdr/operation-create-issuance-request.h"
#include "xdr/operation-manage-limits.h"
#include "xdr/operation-manage-asset-pair.h"
#include "xdr/operation-manage-offer.h"
#include "xdr/operation-manage-invoice-request.h"
#include "xdr/operation-review-request.h"
#include "xdr/operation-create-sale-creation-request.h"
#include "xdr/operation-cancel-sale-creation-request.h"
#include "xdr/operation-check-sale-state.h"
#include "xdr/operation-payout.h"
#include "xdr/operation-create-AML-alert-request.h"
#include "xdr/operation-manage-key-value.h"
#include "xdr/operation-create-change-role-request.h"
#include "xdr/operation-manage-external-system-id-pool-entry.h"
#include "xdr/operation-bind-external-system-id.h"
#include "xdr/operation-payment.h"
#include "xdr/operation-manage-sale.h"
#include "xdr/operation-create-manage-limits-request.h"
#include "xdr/operation-manage-contract.h"
#include "xdr/operation-manage-contract-request.h"
#include "xdr/operation-create-atomic-swap-bid-request.h"
#include "xdr/operation-cancel-atomic-swap-ask.h"
#include "xdr/operation-create-atomic-swap-ask-request.h"
#include "xdr/operation-manage-account-role.h"
#include "xdr/operation-manage-account-rule.h"
#include "xdr/operation-manage-signer-role.h"
#include "xdr/operation-manage-signer-rule.h"
#include "xdr/operation-manage-signer.h"
#include "xdr/operation-license.h"
#include "xdr/operation-stamp.h"
#include "xdr/operation-manage-poll.h"
#include "xdr/operation-manage-create-poll-request.h"
#include "xdr/operation-manage-vote.h"
#include "xdr/operation-manage-account-specific-rule.h"
#include "xdr/operation-cancel-change-role-request.h"
#include "xdr/operation-create-kyc-recovery-request.h"
#include "xdr/operation-initiate-kyc-recovery.h"
#include "xdr/operation-remove-asset-pair.h"
#include "xdr/operation-create-manage-offer-request.h"
#include "xdr/operation-create-payment-request.h"
#include "xdr/operation-create-redemption-request.h"
#include "xdr/operation-remove-asset.h"
#include "xdr/operation-open-swap.h"
#include "xdr/operation-close-swap.h"
#include "xdr/operation-create-data.h"
#include "xdr/operation-update-data.h"
#include "xdr/operation-remove-data.h"
#include "xdr/operation-create-data-creation-request.h"
#include "xdr/operation-cancel-data-creation-request.h"

namespace stellar {

struct Operation  : xdr::xdr_abstract {
  struct _body_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<OperationType>::case_type;
  private:
    _xdr_case_type type_;
    union {
      CreateAccountOp createAccountOp_;
      CreateIssuanceRequestOp createIssuanceRequestOp_;
      SetFeesOp setFeesOp_;
      CreateWithdrawalRequestOp createWithdrawalRequestOp_;
      ManageBalanceOp manageBalanceOp_;
      ManageAssetOp manageAssetOp_;
      CreatePreIssuanceRequestOp createPreIssuanceRequest_;
      ManageLimitsOp manageLimitsOp_;
      ManageAssetPairOp manageAssetPairOp_;
      ManageOfferOp manageOfferOp_;
      ManageInvoiceRequestOp manageInvoiceRequestOp_;
      ReviewRequestOp reviewRequestOp_;
      CreateSaleCreationRequestOp createSaleCreationRequestOp_;
      CheckSaleStateOp checkSaleStateOp_;
      PayoutOp payoutOp_;
      CreateAMLAlertRequestOp createAMLAlertRequestOp_;
      ManageKeyValueOp manageKeyValueOp_;
      CreateChangeRoleRequestOp createChangeRoleRequestOp_;
      ManageExternalSystemAccountIdPoolEntryOp manageExternalSystemAccountIdPoolEntryOp_;
      BindExternalSystemAccountIdOp bindExternalSystemAccountIdOp_;
      PaymentOp paymentOp_;
      ManageSaleOp manageSaleOp_;
      CreateManageLimitsRequestOp createManageLimitsRequestOp_;
      ManageContractRequestOp manageContractRequestOp_;
      ManageContractOp manageContractOp_;
      CancelSaleCreationRequestOp cancelSaleCreationRequestOp_;
      CreateAtomicSwapAskRequestOp createAtomicSwapAskRequestOp_;
      CancelAtomicSwapAskOp cancelAtomicSwapAskOp_;
      CreateAtomicSwapBidRequestOp createAtomicSwapBidRequestOp_;
      ManageAccountRoleOp manageAccountRoleOp_;
      ManageAccountRuleOp manageAccountRuleOp_;
      ManageSignerOp manageSignerOp_;
      ManageSignerRoleOp manageSignerRoleOp_;
      ManageSignerRuleOp manageSignerRuleOp_;
      StampOp stampOp_;
      LicenseOp licenseOp_;
      ManageCreatePollRequestOp manageCreatePollRequestOp_;
      ManagePollOp managePollOp_;
      ManageVoteOp manageVoteOp_;
      ManageAccountSpecificRuleOp manageAccountSpecificRuleOp_;
      CancelChangeRoleRequestOp cancelChangeRoleRequestOp_;
      RemoveAssetPairOp removeAssetPairOp_;
      InitiateKYCRecoveryOp initiateKYCRecoveryOp_;
      CreateKYCRecoveryRequestOp createKYCRecoveryRequestOp_;
      CreateManageOfferRequestOp createManageOfferRequestOp_;
      CreatePaymentRequestOp createPaymentRequestOp_;
      RemoveAssetOp removeAssetOp_;
      OpenSwapOp openSwapOp_;
      CloseSwapOp closeSwapOp_;
      CreateRedemptionRequestOp createRedemptionRequestOp_;
      CreateDataOp createDataOp_;
      UpdateDataOp updateDataOp_;
      RemoveDataOp removeDataOp_;
      CreateDataCreationRequestOp createDataCreationRequestOp_;
      CancelDataCreationRequestOp cancelDataCreationRequestOp_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<OperationType> &_xdr_case_values() {
      static const std::vector<OperationType> _xdr_disc_vec {
        OperationType::CREATE_ACCOUNT,
        OperationType::CREATE_ISSUANCE_REQUEST,
        OperationType::SET_FEES,
        OperationType::CREATE_WITHDRAWAL_REQUEST,
        OperationType::MANAGE_BALANCE,
        OperationType::MANAGE_ASSET,
        OperationType::CREATE_PREISSUANCE_REQUEST,
        OperationType::MANAGE_LIMITS,
        OperationType::MANAGE_ASSET_PAIR,
        OperationType::MANAGE_OFFER,
        OperationType::MANAGE_INVOICE_REQUEST,
        OperationType::REVIEW_REQUEST,
        OperationType::CREATE_SALE_REQUEST,
        OperationType::CHECK_SALE_STATE,
        OperationType::PAYOUT,
        OperationType::CREATE_AML_ALERT,
        OperationType::MANAGE_KEY_VALUE,
        OperationType::CREATE_CHANGE_ROLE_REQUEST,
        OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY,
        OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID,
        OperationType::PAYMENT,
        OperationType::MANAGE_SALE,
        OperationType::CREATE_MANAGE_LIMITS_REQUEST,
        OperationType::MANAGE_CONTRACT_REQUEST,
        OperationType::MANAGE_CONTRACT,
        OperationType::CANCEL_SALE_REQUEST,
        OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST,
        OperationType::CANCEL_ATOMIC_SWAP_ASK,
        OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST,
        OperationType::MANAGE_ACCOUNT_ROLE,
        OperationType::MANAGE_ACCOUNT_RULE,
        OperationType::MANAGE_SIGNER,
        OperationType::MANAGE_SIGNER_ROLE,
        OperationType::MANAGE_SIGNER_RULE,
        OperationType::STAMP,
        OperationType::LICENSE,
        OperationType::MANAGE_CREATE_POLL_REQUEST,
        OperationType::MANAGE_POLL,
        OperationType::MANAGE_VOTE,
        OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE,
        OperationType::CANCEL_CHANGE_ROLE_REQUEST,
        OperationType::REMOVE_ASSET_PAIR,
        OperationType::INITIATE_KYC_RECOVERY,
        OperationType::CREATE_KYC_RECOVERY_REQUEST,
        OperationType::CREATE_MANAGE_OFFER_REQUEST,
        OperationType::CREATE_PAYMENT_REQUEST,
        OperationType::REMOVE_ASSET,
        OperationType::OPEN_SWAP,
        OperationType::CLOSE_SWAP,
        OperationType::CREATE_REDEMPTION_REQUEST,
        OperationType::CREATE_DATA,
        OperationType::UPDATE_DATA,
        OperationType::REMOVE_DATA,
        OperationType::CREATE_DATA_CREATION_REQUEST,
        OperationType::CANCEL_DATA_CREATION_REQUEST
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)OperationType::CREATE_ACCOUNT ? 1
        : which == (int32_t)OperationType::CREATE_ISSUANCE_REQUEST ? 2
        : which == (int32_t)OperationType::SET_FEES ? 3
        : which == (int32_t)OperationType::CREATE_WITHDRAWAL_REQUEST ? 4
        : which == (int32_t)OperationType::MANAGE_BALANCE ? 5
        : which == (int32_t)OperationType::MANAGE_ASSET ? 6
        : which == (int32_t)OperationType::CREATE_PREISSUANCE_REQUEST ? 7
        : which == (int32_t)OperationType::MANAGE_LIMITS ? 8
        : which == (int32_t)OperationType::MANAGE_ASSET_PAIR ? 9
        : which == (int32_t)OperationType::MANAGE_OFFER ? 10
        : which == (int32_t)OperationType::MANAGE_INVOICE_REQUEST ? 11
        : which == (int32_t)OperationType::REVIEW_REQUEST ? 12
        : which == (int32_t)OperationType::CREATE_SALE_REQUEST ? 13
        : which == (int32_t)OperationType::CHECK_SALE_STATE ? 14
        : which == (int32_t)OperationType::PAYOUT ? 15
        : which == (int32_t)OperationType::CREATE_AML_ALERT ? 16
        : which == (int32_t)OperationType::MANAGE_KEY_VALUE ? 17
        : which == (int32_t)OperationType::CREATE_CHANGE_ROLE_REQUEST ? 18
        : which == (int32_t)OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY ? 19
        : which == (int32_t)OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID ? 20
        : which == (int32_t)OperationType::PAYMENT ? 21
        : which == (int32_t)OperationType::MANAGE_SALE ? 22
        : which == (int32_t)OperationType::CREATE_MANAGE_LIMITS_REQUEST ? 23
        : which == (int32_t)OperationType::MANAGE_CONTRACT_REQUEST ? 24
        : which == (int32_t)OperationType::MANAGE_CONTRACT ? 25
        : which == (int32_t)OperationType::CANCEL_SALE_REQUEST ? 26
        : which == (int32_t)OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST ? 27
        : which == (int32_t)OperationType::CANCEL_ATOMIC_SWAP_ASK ? 28
        : which == (int32_t)OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST ? 29
        : which == (int32_t)OperationType::MANAGE_ACCOUNT_ROLE ? 30
        : which == (int32_t)OperationType::MANAGE_ACCOUNT_RULE ? 31
        : which == (int32_t)OperationType::MANAGE_SIGNER ? 32
        : which == (int32_t)OperationType::MANAGE_SIGNER_ROLE ? 33
        : which == (int32_t)OperationType::MANAGE_SIGNER_RULE ? 34
        : which == (int32_t)OperationType::STAMP ? 35
        : which == (int32_t)OperationType::LICENSE ? 36
        : which == (int32_t)OperationType::MANAGE_CREATE_POLL_REQUEST ? 37
        : which == (int32_t)OperationType::MANAGE_POLL ? 38
        : which == (int32_t)OperationType::MANAGE_VOTE ? 39
        : which == (int32_t)OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE ? 40
        : which == (int32_t)OperationType::CANCEL_CHANGE_ROLE_REQUEST ? 41
        : which == (int32_t)OperationType::REMOVE_ASSET_PAIR ? 42
        : which == (int32_t)OperationType::INITIATE_KYC_RECOVERY ? 43
        : which == (int32_t)OperationType::CREATE_KYC_RECOVERY_REQUEST ? 44
        : which == (int32_t)OperationType::CREATE_MANAGE_OFFER_REQUEST ? 45
        : which == (int32_t)OperationType::CREATE_PAYMENT_REQUEST ? 46
        : which == (int32_t)OperationType::REMOVE_ASSET ? 47
        : which == (int32_t)OperationType::OPEN_SWAP ? 48
        : which == (int32_t)OperationType::CLOSE_SWAP ? 49
        : which == (int32_t)OperationType::CREATE_REDEMPTION_REQUEST ? 50
        : which == (int32_t)OperationType::CREATE_DATA ? 51
        : which == (int32_t)OperationType::UPDATE_DATA ? 52
        : which == (int32_t)OperationType::REMOVE_DATA ? 53
        : which == (int32_t)OperationType::CREATE_DATA_CREATION_REQUEST ? 54
        : which == (int32_t)OperationType::CANCEL_DATA_CREATION_REQUEST ? 55
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)OperationType::CREATE_ACCOUNT:
        _f(&_body_t::createAccountOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CREATE_ISSUANCE_REQUEST:
        _f(&_body_t::createIssuanceRequestOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::SET_FEES:
        _f(&_body_t::setFeesOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CREATE_WITHDRAWAL_REQUEST:
        _f(&_body_t::createWithdrawalRequestOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_BALANCE:
        _f(&_body_t::manageBalanceOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_ASSET:
        _f(&_body_t::manageAssetOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CREATE_PREISSUANCE_REQUEST:
        _f(&_body_t::createPreIssuanceRequest_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_LIMITS:
        _f(&_body_t::manageLimitsOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_ASSET_PAIR:
        _f(&_body_t::manageAssetPairOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_OFFER:
        _f(&_body_t::manageOfferOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_INVOICE_REQUEST:
        _f(&_body_t::manageInvoiceRequestOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::REVIEW_REQUEST:
        _f(&_body_t::reviewRequestOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CREATE_SALE_REQUEST:
        _f(&_body_t::createSaleCreationRequestOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CHECK_SALE_STATE:
        _f(&_body_t::checkSaleStateOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::PAYOUT:
        _f(&_body_t::payoutOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CREATE_AML_ALERT:
        _f(&_body_t::createAMLAlertRequestOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_KEY_VALUE:
        _f(&_body_t::manageKeyValueOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CREATE_CHANGE_ROLE_REQUEST:
        _f(&_body_t::createChangeRoleRequestOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
        _f(&_body_t::manageExternalSystemAccountIdPoolEntryOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID:
        _f(&_body_t::bindExternalSystemAccountIdOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::PAYMENT:
        _f(&_body_t::paymentOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_SALE:
        _f(&_body_t::manageSaleOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CREATE_MANAGE_LIMITS_REQUEST:
        _f(&_body_t::createManageLimitsRequestOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_CONTRACT_REQUEST:
        _f(&_body_t::manageContractRequestOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_CONTRACT:
        _f(&_body_t::manageContractOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CANCEL_SALE_REQUEST:
        _f(&_body_t::cancelSaleCreationRequestOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST:
        _f(&_body_t::createAtomicSwapAskRequestOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CANCEL_ATOMIC_SWAP_ASK:
        _f(&_body_t::cancelAtomicSwapAskOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST:
        _f(&_body_t::createAtomicSwapBidRequestOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_ACCOUNT_ROLE:
        _f(&_body_t::manageAccountRoleOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_ACCOUNT_RULE:
        _f(&_body_t::manageAccountRuleOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_SIGNER:
        _f(&_body_t::manageSignerOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_SIGNER_ROLE:
        _f(&_body_t::manageSignerRoleOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_SIGNER_RULE:
        _f(&_body_t::manageSignerRuleOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::STAMP:
        _f(&_body_t::stampOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::LICENSE:
        _f(&_body_t::licenseOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_CREATE_POLL_REQUEST:
        _f(&_body_t::manageCreatePollRequestOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_POLL:
        _f(&_body_t::managePollOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_VOTE:
        _f(&_body_t::manageVoteOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE:
        _f(&_body_t::manageAccountSpecificRuleOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CANCEL_CHANGE_ROLE_REQUEST:
        _f(&_body_t::cancelChangeRoleRequestOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::REMOVE_ASSET_PAIR:
        _f(&_body_t::removeAssetPairOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::INITIATE_KYC_RECOVERY:
        _f(&_body_t::initiateKYCRecoveryOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CREATE_KYC_RECOVERY_REQUEST:
        _f(&_body_t::createKYCRecoveryRequestOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CREATE_MANAGE_OFFER_REQUEST:
        _f(&_body_t::createManageOfferRequestOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CREATE_PAYMENT_REQUEST:
        _f(&_body_t::createPaymentRequestOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::REMOVE_ASSET:
        _f(&_body_t::removeAssetOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::OPEN_SWAP:
        _f(&_body_t::openSwapOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CLOSE_SWAP:
        _f(&_body_t::closeSwapOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CREATE_REDEMPTION_REQUEST:
        _f(&_body_t::createRedemptionRequestOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CREATE_DATA:
        _f(&_body_t::createDataOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::UPDATE_DATA:
        _f(&_body_t::updateDataOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::REMOVE_DATA:
        _f(&_body_t::removeDataOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CREATE_DATA_CREATION_REQUEST:
        _f(&_body_t::createDataCreationRequestOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CANCEL_DATA_CREATION_REQUEST:
        _f(&_body_t::cancelDataCreationRequestOp_, std::forward<_A>(_a)...);
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
        case (int32_t)OperationType::CREATE_ACCOUNT:
new(&createAccountOp_) CreateAccountOp{};
break;
        case (int32_t)OperationType::CREATE_ISSUANCE_REQUEST:
new(&createIssuanceRequestOp_) CreateIssuanceRequestOp{};
break;
        case (int32_t)OperationType::SET_FEES:
new(&setFeesOp_) SetFeesOp{};
break;
        case (int32_t)OperationType::CREATE_WITHDRAWAL_REQUEST:
new(&createWithdrawalRequestOp_) CreateWithdrawalRequestOp{};
break;
        case (int32_t)OperationType::MANAGE_BALANCE:
new(&manageBalanceOp_) ManageBalanceOp{};
break;
        case (int32_t)OperationType::MANAGE_ASSET:
new(&manageAssetOp_) ManageAssetOp{};
break;
        case (int32_t)OperationType::CREATE_PREISSUANCE_REQUEST:
new(&createPreIssuanceRequest_) CreatePreIssuanceRequestOp{};
break;
        case (int32_t)OperationType::MANAGE_LIMITS:
new(&manageLimitsOp_) ManageLimitsOp{};
break;
        case (int32_t)OperationType::MANAGE_ASSET_PAIR:
new(&manageAssetPairOp_) ManageAssetPairOp{};
break;
        case (int32_t)OperationType::MANAGE_OFFER:
new(&manageOfferOp_) ManageOfferOp{};
break;
        case (int32_t)OperationType::MANAGE_INVOICE_REQUEST:
new(&manageInvoiceRequestOp_) ManageInvoiceRequestOp{};
break;
        case (int32_t)OperationType::REVIEW_REQUEST:
new(&reviewRequestOp_) ReviewRequestOp{};
break;
        case (int32_t)OperationType::CREATE_SALE_REQUEST:
new(&createSaleCreationRequestOp_) CreateSaleCreationRequestOp{};
break;
        case (int32_t)OperationType::CHECK_SALE_STATE:
new(&checkSaleStateOp_) CheckSaleStateOp{};
break;
        case (int32_t)OperationType::PAYOUT:
new(&payoutOp_) PayoutOp{};
break;
        case (int32_t)OperationType::CREATE_AML_ALERT:
new(&createAMLAlertRequestOp_) CreateAMLAlertRequestOp{};
break;
        case (int32_t)OperationType::MANAGE_KEY_VALUE:
new(&manageKeyValueOp_) ManageKeyValueOp{};
break;
        case (int32_t)OperationType::CREATE_CHANGE_ROLE_REQUEST:
new(&createChangeRoleRequestOp_) CreateChangeRoleRequestOp{};
break;
        case (int32_t)OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
new(&manageExternalSystemAccountIdPoolEntryOp_) ManageExternalSystemAccountIdPoolEntryOp{};
break;
        case (int32_t)OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID:
new(&bindExternalSystemAccountIdOp_) BindExternalSystemAccountIdOp{};
break;
        case (int32_t)OperationType::PAYMENT:
new(&paymentOp_) PaymentOp{};
break;
        case (int32_t)OperationType::MANAGE_SALE:
new(&manageSaleOp_) ManageSaleOp{};
break;
        case (int32_t)OperationType::CREATE_MANAGE_LIMITS_REQUEST:
new(&createManageLimitsRequestOp_) CreateManageLimitsRequestOp{};
break;
        case (int32_t)OperationType::MANAGE_CONTRACT_REQUEST:
new(&manageContractRequestOp_) ManageContractRequestOp{};
break;
        case (int32_t)OperationType::MANAGE_CONTRACT:
new(&manageContractOp_) ManageContractOp{};
break;
        case (int32_t)OperationType::CANCEL_SALE_REQUEST:
new(&cancelSaleCreationRequestOp_) CancelSaleCreationRequestOp{};
break;
        case (int32_t)OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST:
new(&createAtomicSwapAskRequestOp_) CreateAtomicSwapAskRequestOp{};
break;
        case (int32_t)OperationType::CANCEL_ATOMIC_SWAP_ASK:
new(&cancelAtomicSwapAskOp_) CancelAtomicSwapAskOp{};
break;
        case (int32_t)OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST:
new(&createAtomicSwapBidRequestOp_) CreateAtomicSwapBidRequestOp{};
break;
        case (int32_t)OperationType::MANAGE_ACCOUNT_ROLE:
new(&manageAccountRoleOp_) ManageAccountRoleOp{};
break;
        case (int32_t)OperationType::MANAGE_ACCOUNT_RULE:
new(&manageAccountRuleOp_) ManageAccountRuleOp{};
break;
        case (int32_t)OperationType::MANAGE_SIGNER:
new(&manageSignerOp_) ManageSignerOp{};
break;
        case (int32_t)OperationType::MANAGE_SIGNER_ROLE:
new(&manageSignerRoleOp_) ManageSignerRoleOp{};
break;
        case (int32_t)OperationType::MANAGE_SIGNER_RULE:
new(&manageSignerRuleOp_) ManageSignerRuleOp{};
break;
        case (int32_t)OperationType::STAMP:
new(&stampOp_) StampOp{};
break;
        case (int32_t)OperationType::LICENSE:
new(&licenseOp_) LicenseOp{};
break;
        case (int32_t)OperationType::MANAGE_CREATE_POLL_REQUEST:
new(&manageCreatePollRequestOp_) ManageCreatePollRequestOp{};
break;
        case (int32_t)OperationType::MANAGE_POLL:
new(&managePollOp_) ManagePollOp{};
break;
        case (int32_t)OperationType::MANAGE_VOTE:
new(&manageVoteOp_) ManageVoteOp{};
break;
        case (int32_t)OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE:
new(&manageAccountSpecificRuleOp_) ManageAccountSpecificRuleOp{};
break;
        case (int32_t)OperationType::CANCEL_CHANGE_ROLE_REQUEST:
new(&cancelChangeRoleRequestOp_) CancelChangeRoleRequestOp{};
break;
        case (int32_t)OperationType::REMOVE_ASSET_PAIR:
new(&removeAssetPairOp_) RemoveAssetPairOp{};
break;
        case (int32_t)OperationType::INITIATE_KYC_RECOVERY:
new(&initiateKYCRecoveryOp_) InitiateKYCRecoveryOp{};
break;
        case (int32_t)OperationType::CREATE_KYC_RECOVERY_REQUEST:
new(&createKYCRecoveryRequestOp_) CreateKYCRecoveryRequestOp{};
break;
        case (int32_t)OperationType::CREATE_MANAGE_OFFER_REQUEST:
new(&createManageOfferRequestOp_) CreateManageOfferRequestOp{};
break;
        case (int32_t)OperationType::CREATE_PAYMENT_REQUEST:
new(&createPaymentRequestOp_) CreatePaymentRequestOp{};
break;
        case (int32_t)OperationType::REMOVE_ASSET:
new(&removeAssetOp_) RemoveAssetOp{};
break;
        case (int32_t)OperationType::OPEN_SWAP:
new(&openSwapOp_) OpenSwapOp{};
break;
        case (int32_t)OperationType::CLOSE_SWAP:
new(&closeSwapOp_) CloseSwapOp{};
break;
        case (int32_t)OperationType::CREATE_REDEMPTION_REQUEST:
new(&createRedemptionRequestOp_) CreateRedemptionRequestOp{};
break;
        case (int32_t)OperationType::CREATE_DATA:
new(&createDataOp_) CreateDataOp{};
break;
        case (int32_t)OperationType::UPDATE_DATA:
new(&updateDataOp_) UpdateDataOp{};
break;
        case (int32_t)OperationType::REMOVE_DATA:
new(&removeDataOp_) RemoveDataOp{};
break;
        case (int32_t)OperationType::CREATE_DATA_CREATION_REQUEST:
new(&createDataCreationRequestOp_) CreateDataCreationRequestOp{};
break;
        case (int32_t)OperationType::CANCEL_DATA_CREATION_REQUEST:
new(&cancelDataCreationRequestOp_) CancelDataCreationRequestOp{};
break;
}

      }
      else
        type_ = which;
    }
    explicit _body_t(OperationType which = OperationType{}) : type_((int32_t)which) {
      switch (type_)
{
      case (int32_t)OperationType::CREATE_ACCOUNT:
new(&createAccountOp_) CreateAccountOp{};
break;
      case (int32_t)OperationType::CREATE_ISSUANCE_REQUEST:
new(&createIssuanceRequestOp_) CreateIssuanceRequestOp{};
break;
      case (int32_t)OperationType::SET_FEES:
new(&setFeesOp_) SetFeesOp{};
break;
      case (int32_t)OperationType::CREATE_WITHDRAWAL_REQUEST:
new(&createWithdrawalRequestOp_) CreateWithdrawalRequestOp{};
break;
      case (int32_t)OperationType::MANAGE_BALANCE:
new(&manageBalanceOp_) ManageBalanceOp{};
break;
      case (int32_t)OperationType::MANAGE_ASSET:
new(&manageAssetOp_) ManageAssetOp{};
break;
      case (int32_t)OperationType::CREATE_PREISSUANCE_REQUEST:
new(&createPreIssuanceRequest_) CreatePreIssuanceRequestOp{};
break;
      case (int32_t)OperationType::MANAGE_LIMITS:
new(&manageLimitsOp_) ManageLimitsOp{};
break;
      case (int32_t)OperationType::MANAGE_ASSET_PAIR:
new(&manageAssetPairOp_) ManageAssetPairOp{};
break;
      case (int32_t)OperationType::MANAGE_OFFER:
new(&manageOfferOp_) ManageOfferOp{};
break;
      case (int32_t)OperationType::MANAGE_INVOICE_REQUEST:
new(&manageInvoiceRequestOp_) ManageInvoiceRequestOp{};
break;
      case (int32_t)OperationType::REVIEW_REQUEST:
new(&reviewRequestOp_) ReviewRequestOp{};
break;
      case (int32_t)OperationType::CREATE_SALE_REQUEST:
new(&createSaleCreationRequestOp_) CreateSaleCreationRequestOp{};
break;
      case (int32_t)OperationType::CHECK_SALE_STATE:
new(&checkSaleStateOp_) CheckSaleStateOp{};
break;
      case (int32_t)OperationType::PAYOUT:
new(&payoutOp_) PayoutOp{};
break;
      case (int32_t)OperationType::CREATE_AML_ALERT:
new(&createAMLAlertRequestOp_) CreateAMLAlertRequestOp{};
break;
      case (int32_t)OperationType::MANAGE_KEY_VALUE:
new(&manageKeyValueOp_) ManageKeyValueOp{};
break;
      case (int32_t)OperationType::CREATE_CHANGE_ROLE_REQUEST:
new(&createChangeRoleRequestOp_) CreateChangeRoleRequestOp{};
break;
      case (int32_t)OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
new(&manageExternalSystemAccountIdPoolEntryOp_) ManageExternalSystemAccountIdPoolEntryOp{};
break;
      case (int32_t)OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID:
new(&bindExternalSystemAccountIdOp_) BindExternalSystemAccountIdOp{};
break;
      case (int32_t)OperationType::PAYMENT:
new(&paymentOp_) PaymentOp{};
break;
      case (int32_t)OperationType::MANAGE_SALE:
new(&manageSaleOp_) ManageSaleOp{};
break;
      case (int32_t)OperationType::CREATE_MANAGE_LIMITS_REQUEST:
new(&createManageLimitsRequestOp_) CreateManageLimitsRequestOp{};
break;
      case (int32_t)OperationType::MANAGE_CONTRACT_REQUEST:
new(&manageContractRequestOp_) ManageContractRequestOp{};
break;
      case (int32_t)OperationType::MANAGE_CONTRACT:
new(&manageContractOp_) ManageContractOp{};
break;
      case (int32_t)OperationType::CANCEL_SALE_REQUEST:
new(&cancelSaleCreationRequestOp_) CancelSaleCreationRequestOp{};
break;
      case (int32_t)OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST:
new(&createAtomicSwapAskRequestOp_) CreateAtomicSwapAskRequestOp{};
break;
      case (int32_t)OperationType::CANCEL_ATOMIC_SWAP_ASK:
new(&cancelAtomicSwapAskOp_) CancelAtomicSwapAskOp{};
break;
      case (int32_t)OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST:
new(&createAtomicSwapBidRequestOp_) CreateAtomicSwapBidRequestOp{};
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_ROLE:
new(&manageAccountRoleOp_) ManageAccountRoleOp{};
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_RULE:
new(&manageAccountRuleOp_) ManageAccountRuleOp{};
break;
      case (int32_t)OperationType::MANAGE_SIGNER:
new(&manageSignerOp_) ManageSignerOp{};
break;
      case (int32_t)OperationType::MANAGE_SIGNER_ROLE:
new(&manageSignerRoleOp_) ManageSignerRoleOp{};
break;
      case (int32_t)OperationType::MANAGE_SIGNER_RULE:
new(&manageSignerRuleOp_) ManageSignerRuleOp{};
break;
      case (int32_t)OperationType::STAMP:
new(&stampOp_) StampOp{};
break;
      case (int32_t)OperationType::LICENSE:
new(&licenseOp_) LicenseOp{};
break;
      case (int32_t)OperationType::MANAGE_CREATE_POLL_REQUEST:
new(&manageCreatePollRequestOp_) ManageCreatePollRequestOp{};
break;
      case (int32_t)OperationType::MANAGE_POLL:
new(&managePollOp_) ManagePollOp{};
break;
      case (int32_t)OperationType::MANAGE_VOTE:
new(&manageVoteOp_) ManageVoteOp{};
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE:
new(&manageAccountSpecificRuleOp_) ManageAccountSpecificRuleOp{};
break;
      case (int32_t)OperationType::CANCEL_CHANGE_ROLE_REQUEST:
new(&cancelChangeRoleRequestOp_) CancelChangeRoleRequestOp{};
break;
      case (int32_t)OperationType::REMOVE_ASSET_PAIR:
new(&removeAssetPairOp_) RemoveAssetPairOp{};
break;
      case (int32_t)OperationType::INITIATE_KYC_RECOVERY:
new(&initiateKYCRecoveryOp_) InitiateKYCRecoveryOp{};
break;
      case (int32_t)OperationType::CREATE_KYC_RECOVERY_REQUEST:
new(&createKYCRecoveryRequestOp_) CreateKYCRecoveryRequestOp{};
break;
      case (int32_t)OperationType::CREATE_MANAGE_OFFER_REQUEST:
new(&createManageOfferRequestOp_) CreateManageOfferRequestOp{};
break;
      case (int32_t)OperationType::CREATE_PAYMENT_REQUEST:
new(&createPaymentRequestOp_) CreatePaymentRequestOp{};
break;
      case (int32_t)OperationType::REMOVE_ASSET:
new(&removeAssetOp_) RemoveAssetOp{};
break;
      case (int32_t)OperationType::OPEN_SWAP:
new(&openSwapOp_) OpenSwapOp{};
break;
      case (int32_t)OperationType::CLOSE_SWAP:
new(&closeSwapOp_) CloseSwapOp{};
break;
      case (int32_t)OperationType::CREATE_REDEMPTION_REQUEST:
new(&createRedemptionRequestOp_) CreateRedemptionRequestOp{};
break;
      case (int32_t)OperationType::CREATE_DATA:
new(&createDataOp_) CreateDataOp{};
break;
      case (int32_t)OperationType::UPDATE_DATA:
new(&updateDataOp_) UpdateDataOp{};
break;
      case (int32_t)OperationType::REMOVE_DATA:
new(&removeDataOp_) RemoveDataOp{};
break;
      case (int32_t)OperationType::CREATE_DATA_CREATION_REQUEST:
new(&createDataCreationRequestOp_) CreateDataCreationRequestOp{};
break;
      case (int32_t)OperationType::CANCEL_DATA_CREATION_REQUEST:
new(&cancelDataCreationRequestOp_) CancelDataCreationRequestOp{};
break;
}

    }
    _body_t(const _body_t &source) : type_(source.type_) {
      switch (type_)
{
      case (int32_t)OperationType::CREATE_ACCOUNT:
new(&createAccountOp_) CreateAccountOp(source.createAccountOp_);
break;
      case (int32_t)OperationType::CREATE_ISSUANCE_REQUEST:
new(&createIssuanceRequestOp_) CreateIssuanceRequestOp(source.createIssuanceRequestOp_);
break;
      case (int32_t)OperationType::SET_FEES:
new(&setFeesOp_) SetFeesOp(source.setFeesOp_);
break;
      case (int32_t)OperationType::CREATE_WITHDRAWAL_REQUEST:
new(&createWithdrawalRequestOp_) CreateWithdrawalRequestOp(source.createWithdrawalRequestOp_);
break;
      case (int32_t)OperationType::MANAGE_BALANCE:
new(&manageBalanceOp_) ManageBalanceOp(source.manageBalanceOp_);
break;
      case (int32_t)OperationType::MANAGE_ASSET:
new(&manageAssetOp_) ManageAssetOp(source.manageAssetOp_);
break;
      case (int32_t)OperationType::CREATE_PREISSUANCE_REQUEST:
new(&createPreIssuanceRequest_) CreatePreIssuanceRequestOp(source.createPreIssuanceRequest_);
break;
      case (int32_t)OperationType::MANAGE_LIMITS:
new(&manageLimitsOp_) ManageLimitsOp(source.manageLimitsOp_);
break;
      case (int32_t)OperationType::MANAGE_ASSET_PAIR:
new(&manageAssetPairOp_) ManageAssetPairOp(source.manageAssetPairOp_);
break;
      case (int32_t)OperationType::MANAGE_OFFER:
new(&manageOfferOp_) ManageOfferOp(source.manageOfferOp_);
break;
      case (int32_t)OperationType::MANAGE_INVOICE_REQUEST:
new(&manageInvoiceRequestOp_) ManageInvoiceRequestOp(source.manageInvoiceRequestOp_);
break;
      case (int32_t)OperationType::REVIEW_REQUEST:
new(&reviewRequestOp_) ReviewRequestOp(source.reviewRequestOp_);
break;
      case (int32_t)OperationType::CREATE_SALE_REQUEST:
new(&createSaleCreationRequestOp_) CreateSaleCreationRequestOp(source.createSaleCreationRequestOp_);
break;
      case (int32_t)OperationType::CHECK_SALE_STATE:
new(&checkSaleStateOp_) CheckSaleStateOp(source.checkSaleStateOp_);
break;
      case (int32_t)OperationType::PAYOUT:
new(&payoutOp_) PayoutOp(source.payoutOp_);
break;
      case (int32_t)OperationType::CREATE_AML_ALERT:
new(&createAMLAlertRequestOp_) CreateAMLAlertRequestOp(source.createAMLAlertRequestOp_);
break;
      case (int32_t)OperationType::MANAGE_KEY_VALUE:
new(&manageKeyValueOp_) ManageKeyValueOp(source.manageKeyValueOp_);
break;
      case (int32_t)OperationType::CREATE_CHANGE_ROLE_REQUEST:
new(&createChangeRoleRequestOp_) CreateChangeRoleRequestOp(source.createChangeRoleRequestOp_);
break;
      case (int32_t)OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
new(&manageExternalSystemAccountIdPoolEntryOp_) ManageExternalSystemAccountIdPoolEntryOp(source.manageExternalSystemAccountIdPoolEntryOp_);
break;
      case (int32_t)OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID:
new(&bindExternalSystemAccountIdOp_) BindExternalSystemAccountIdOp(source.bindExternalSystemAccountIdOp_);
break;
      case (int32_t)OperationType::PAYMENT:
new(&paymentOp_) PaymentOp(source.paymentOp_);
break;
      case (int32_t)OperationType::MANAGE_SALE:
new(&manageSaleOp_) ManageSaleOp(source.manageSaleOp_);
break;
      case (int32_t)OperationType::CREATE_MANAGE_LIMITS_REQUEST:
new(&createManageLimitsRequestOp_) CreateManageLimitsRequestOp(source.createManageLimitsRequestOp_);
break;
      case (int32_t)OperationType::MANAGE_CONTRACT_REQUEST:
new(&manageContractRequestOp_) ManageContractRequestOp(source.manageContractRequestOp_);
break;
      case (int32_t)OperationType::MANAGE_CONTRACT:
new(&manageContractOp_) ManageContractOp(source.manageContractOp_);
break;
      case (int32_t)OperationType::CANCEL_SALE_REQUEST:
new(&cancelSaleCreationRequestOp_) CancelSaleCreationRequestOp(source.cancelSaleCreationRequestOp_);
break;
      case (int32_t)OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST:
new(&createAtomicSwapAskRequestOp_) CreateAtomicSwapAskRequestOp(source.createAtomicSwapAskRequestOp_);
break;
      case (int32_t)OperationType::CANCEL_ATOMIC_SWAP_ASK:
new(&cancelAtomicSwapAskOp_) CancelAtomicSwapAskOp(source.cancelAtomicSwapAskOp_);
break;
      case (int32_t)OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST:
new(&createAtomicSwapBidRequestOp_) CreateAtomicSwapBidRequestOp(source.createAtomicSwapBidRequestOp_);
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_ROLE:
new(&manageAccountRoleOp_) ManageAccountRoleOp(source.manageAccountRoleOp_);
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_RULE:
new(&manageAccountRuleOp_) ManageAccountRuleOp(source.manageAccountRuleOp_);
break;
      case (int32_t)OperationType::MANAGE_SIGNER:
new(&manageSignerOp_) ManageSignerOp(source.manageSignerOp_);
break;
      case (int32_t)OperationType::MANAGE_SIGNER_ROLE:
new(&manageSignerRoleOp_) ManageSignerRoleOp(source.manageSignerRoleOp_);
break;
      case (int32_t)OperationType::MANAGE_SIGNER_RULE:
new(&manageSignerRuleOp_) ManageSignerRuleOp(source.manageSignerRuleOp_);
break;
      case (int32_t)OperationType::STAMP:
new(&stampOp_) StampOp(source.stampOp_);
break;
      case (int32_t)OperationType::LICENSE:
new(&licenseOp_) LicenseOp(source.licenseOp_);
break;
      case (int32_t)OperationType::MANAGE_CREATE_POLL_REQUEST:
new(&manageCreatePollRequestOp_) ManageCreatePollRequestOp(source.manageCreatePollRequestOp_);
break;
      case (int32_t)OperationType::MANAGE_POLL:
new(&managePollOp_) ManagePollOp(source.managePollOp_);
break;
      case (int32_t)OperationType::MANAGE_VOTE:
new(&manageVoteOp_) ManageVoteOp(source.manageVoteOp_);
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE:
new(&manageAccountSpecificRuleOp_) ManageAccountSpecificRuleOp(source.manageAccountSpecificRuleOp_);
break;
      case (int32_t)OperationType::CANCEL_CHANGE_ROLE_REQUEST:
new(&cancelChangeRoleRequestOp_) CancelChangeRoleRequestOp(source.cancelChangeRoleRequestOp_);
break;
      case (int32_t)OperationType::REMOVE_ASSET_PAIR:
new(&removeAssetPairOp_) RemoveAssetPairOp(source.removeAssetPairOp_);
break;
      case (int32_t)OperationType::INITIATE_KYC_RECOVERY:
new(&initiateKYCRecoveryOp_) InitiateKYCRecoveryOp(source.initiateKYCRecoveryOp_);
break;
      case (int32_t)OperationType::CREATE_KYC_RECOVERY_REQUEST:
new(&createKYCRecoveryRequestOp_) CreateKYCRecoveryRequestOp(source.createKYCRecoveryRequestOp_);
break;
      case (int32_t)OperationType::CREATE_MANAGE_OFFER_REQUEST:
new(&createManageOfferRequestOp_) CreateManageOfferRequestOp(source.createManageOfferRequestOp_);
break;
      case (int32_t)OperationType::CREATE_PAYMENT_REQUEST:
new(&createPaymentRequestOp_) CreatePaymentRequestOp(source.createPaymentRequestOp_);
break;
      case (int32_t)OperationType::REMOVE_ASSET:
new(&removeAssetOp_) RemoveAssetOp(source.removeAssetOp_);
break;
      case (int32_t)OperationType::OPEN_SWAP:
new(&openSwapOp_) OpenSwapOp(source.openSwapOp_);
break;
      case (int32_t)OperationType::CLOSE_SWAP:
new(&closeSwapOp_) CloseSwapOp(source.closeSwapOp_);
break;
      case (int32_t)OperationType::CREATE_REDEMPTION_REQUEST:
new(&createRedemptionRequestOp_) CreateRedemptionRequestOp(source.createRedemptionRequestOp_);
break;
      case (int32_t)OperationType::CREATE_DATA:
new(&createDataOp_) CreateDataOp(source.createDataOp_);
break;
      case (int32_t)OperationType::UPDATE_DATA:
new(&updateDataOp_) UpdateDataOp(source.updateDataOp_);
break;
      case (int32_t)OperationType::REMOVE_DATA:
new(&removeDataOp_) RemoveDataOp(source.removeDataOp_);
break;
      case (int32_t)OperationType::CREATE_DATA_CREATION_REQUEST:
new(&createDataCreationRequestOp_) CreateDataCreationRequestOp(source.createDataCreationRequestOp_);
break;
      case (int32_t)OperationType::CANCEL_DATA_CREATION_REQUEST:
new(&cancelDataCreationRequestOp_) CancelDataCreationRequestOp(source.cancelDataCreationRequestOp_);
break;
}

    }
    _body_t(_body_t &&source) : type_(source.type_) {
      switch (type_)
{
      case (int32_t)OperationType::CREATE_ACCOUNT:
new(&createAccountOp_) CreateAccountOp(std::move(source.createAccountOp_));
break;
      case (int32_t)OperationType::CREATE_ISSUANCE_REQUEST:
new(&createIssuanceRequestOp_) CreateIssuanceRequestOp(std::move(source.createIssuanceRequestOp_));
break;
      case (int32_t)OperationType::SET_FEES:
new(&setFeesOp_) SetFeesOp(std::move(source.setFeesOp_));
break;
      case (int32_t)OperationType::CREATE_WITHDRAWAL_REQUEST:
new(&createWithdrawalRequestOp_) CreateWithdrawalRequestOp(std::move(source.createWithdrawalRequestOp_));
break;
      case (int32_t)OperationType::MANAGE_BALANCE:
new(&manageBalanceOp_) ManageBalanceOp(std::move(source.manageBalanceOp_));
break;
      case (int32_t)OperationType::MANAGE_ASSET:
new(&manageAssetOp_) ManageAssetOp(std::move(source.manageAssetOp_));
break;
      case (int32_t)OperationType::CREATE_PREISSUANCE_REQUEST:
new(&createPreIssuanceRequest_) CreatePreIssuanceRequestOp(std::move(source.createPreIssuanceRequest_));
break;
      case (int32_t)OperationType::MANAGE_LIMITS:
new(&manageLimitsOp_) ManageLimitsOp(std::move(source.manageLimitsOp_));
break;
      case (int32_t)OperationType::MANAGE_ASSET_PAIR:
new(&manageAssetPairOp_) ManageAssetPairOp(std::move(source.manageAssetPairOp_));
break;
      case (int32_t)OperationType::MANAGE_OFFER:
new(&manageOfferOp_) ManageOfferOp(std::move(source.manageOfferOp_));
break;
      case (int32_t)OperationType::MANAGE_INVOICE_REQUEST:
new(&manageInvoiceRequestOp_) ManageInvoiceRequestOp(std::move(source.manageInvoiceRequestOp_));
break;
      case (int32_t)OperationType::REVIEW_REQUEST:
new(&reviewRequestOp_) ReviewRequestOp(std::move(source.reviewRequestOp_));
break;
      case (int32_t)OperationType::CREATE_SALE_REQUEST:
new(&createSaleCreationRequestOp_) CreateSaleCreationRequestOp(std::move(source.createSaleCreationRequestOp_));
break;
      case (int32_t)OperationType::CHECK_SALE_STATE:
new(&checkSaleStateOp_) CheckSaleStateOp(std::move(source.checkSaleStateOp_));
break;
      case (int32_t)OperationType::PAYOUT:
new(&payoutOp_) PayoutOp(std::move(source.payoutOp_));
break;
      case (int32_t)OperationType::CREATE_AML_ALERT:
new(&createAMLAlertRequestOp_) CreateAMLAlertRequestOp(std::move(source.createAMLAlertRequestOp_));
break;
      case (int32_t)OperationType::MANAGE_KEY_VALUE:
new(&manageKeyValueOp_) ManageKeyValueOp(std::move(source.manageKeyValueOp_));
break;
      case (int32_t)OperationType::CREATE_CHANGE_ROLE_REQUEST:
new(&createChangeRoleRequestOp_) CreateChangeRoleRequestOp(std::move(source.createChangeRoleRequestOp_));
break;
      case (int32_t)OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
new(&manageExternalSystemAccountIdPoolEntryOp_) ManageExternalSystemAccountIdPoolEntryOp(std::move(source.manageExternalSystemAccountIdPoolEntryOp_));
break;
      case (int32_t)OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID:
new(&bindExternalSystemAccountIdOp_) BindExternalSystemAccountIdOp(std::move(source.bindExternalSystemAccountIdOp_));
break;
      case (int32_t)OperationType::PAYMENT:
new(&paymentOp_) PaymentOp(std::move(source.paymentOp_));
break;
      case (int32_t)OperationType::MANAGE_SALE:
new(&manageSaleOp_) ManageSaleOp(std::move(source.manageSaleOp_));
break;
      case (int32_t)OperationType::CREATE_MANAGE_LIMITS_REQUEST:
new(&createManageLimitsRequestOp_) CreateManageLimitsRequestOp(std::move(source.createManageLimitsRequestOp_));
break;
      case (int32_t)OperationType::MANAGE_CONTRACT_REQUEST:
new(&manageContractRequestOp_) ManageContractRequestOp(std::move(source.manageContractRequestOp_));
break;
      case (int32_t)OperationType::MANAGE_CONTRACT:
new(&manageContractOp_) ManageContractOp(std::move(source.manageContractOp_));
break;
      case (int32_t)OperationType::CANCEL_SALE_REQUEST:
new(&cancelSaleCreationRequestOp_) CancelSaleCreationRequestOp(std::move(source.cancelSaleCreationRequestOp_));
break;
      case (int32_t)OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST:
new(&createAtomicSwapAskRequestOp_) CreateAtomicSwapAskRequestOp(std::move(source.createAtomicSwapAskRequestOp_));
break;
      case (int32_t)OperationType::CANCEL_ATOMIC_SWAP_ASK:
new(&cancelAtomicSwapAskOp_) CancelAtomicSwapAskOp(std::move(source.cancelAtomicSwapAskOp_));
break;
      case (int32_t)OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST:
new(&createAtomicSwapBidRequestOp_) CreateAtomicSwapBidRequestOp(std::move(source.createAtomicSwapBidRequestOp_));
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_ROLE:
new(&manageAccountRoleOp_) ManageAccountRoleOp(std::move(source.manageAccountRoleOp_));
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_RULE:
new(&manageAccountRuleOp_) ManageAccountRuleOp(std::move(source.manageAccountRuleOp_));
break;
      case (int32_t)OperationType::MANAGE_SIGNER:
new(&manageSignerOp_) ManageSignerOp(std::move(source.manageSignerOp_));
break;
      case (int32_t)OperationType::MANAGE_SIGNER_ROLE:
new(&manageSignerRoleOp_) ManageSignerRoleOp(std::move(source.manageSignerRoleOp_));
break;
      case (int32_t)OperationType::MANAGE_SIGNER_RULE:
new(&manageSignerRuleOp_) ManageSignerRuleOp(std::move(source.manageSignerRuleOp_));
break;
      case (int32_t)OperationType::STAMP:
new(&stampOp_) StampOp(std::move(source.stampOp_));
break;
      case (int32_t)OperationType::LICENSE:
new(&licenseOp_) LicenseOp(std::move(source.licenseOp_));
break;
      case (int32_t)OperationType::MANAGE_CREATE_POLL_REQUEST:
new(&manageCreatePollRequestOp_) ManageCreatePollRequestOp(std::move(source.manageCreatePollRequestOp_));
break;
      case (int32_t)OperationType::MANAGE_POLL:
new(&managePollOp_) ManagePollOp(std::move(source.managePollOp_));
break;
      case (int32_t)OperationType::MANAGE_VOTE:
new(&manageVoteOp_) ManageVoteOp(std::move(source.manageVoteOp_));
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE:
new(&manageAccountSpecificRuleOp_) ManageAccountSpecificRuleOp(std::move(source.manageAccountSpecificRuleOp_));
break;
      case (int32_t)OperationType::CANCEL_CHANGE_ROLE_REQUEST:
new(&cancelChangeRoleRequestOp_) CancelChangeRoleRequestOp(std::move(source.cancelChangeRoleRequestOp_));
break;
      case (int32_t)OperationType::REMOVE_ASSET_PAIR:
new(&removeAssetPairOp_) RemoveAssetPairOp(std::move(source.removeAssetPairOp_));
break;
      case (int32_t)OperationType::INITIATE_KYC_RECOVERY:
new(&initiateKYCRecoveryOp_) InitiateKYCRecoveryOp(std::move(source.initiateKYCRecoveryOp_));
break;
      case (int32_t)OperationType::CREATE_KYC_RECOVERY_REQUEST:
new(&createKYCRecoveryRequestOp_) CreateKYCRecoveryRequestOp(std::move(source.createKYCRecoveryRequestOp_));
break;
      case (int32_t)OperationType::CREATE_MANAGE_OFFER_REQUEST:
new(&createManageOfferRequestOp_) CreateManageOfferRequestOp(std::move(source.createManageOfferRequestOp_));
break;
      case (int32_t)OperationType::CREATE_PAYMENT_REQUEST:
new(&createPaymentRequestOp_) CreatePaymentRequestOp(std::move(source.createPaymentRequestOp_));
break;
      case (int32_t)OperationType::REMOVE_ASSET:
new(&removeAssetOp_) RemoveAssetOp(std::move(source.removeAssetOp_));
break;
      case (int32_t)OperationType::OPEN_SWAP:
new(&openSwapOp_) OpenSwapOp(std::move(source.openSwapOp_));
break;
      case (int32_t)OperationType::CLOSE_SWAP:
new(&closeSwapOp_) CloseSwapOp(std::move(source.closeSwapOp_));
break;
      case (int32_t)OperationType::CREATE_REDEMPTION_REQUEST:
new(&createRedemptionRequestOp_) CreateRedemptionRequestOp(std::move(source.createRedemptionRequestOp_));
break;
      case (int32_t)OperationType::CREATE_DATA:
new(&createDataOp_) CreateDataOp(std::move(source.createDataOp_));
break;
      case (int32_t)OperationType::UPDATE_DATA:
new(&updateDataOp_) UpdateDataOp(std::move(source.updateDataOp_));
break;
      case (int32_t)OperationType::REMOVE_DATA:
new(&removeDataOp_) RemoveDataOp(std::move(source.removeDataOp_));
break;
      case (int32_t)OperationType::CREATE_DATA_CREATION_REQUEST:
new(&createDataCreationRequestOp_) CreateDataCreationRequestOp(std::move(source.createDataCreationRequestOp_));
break;
      case (int32_t)OperationType::CANCEL_DATA_CREATION_REQUEST:
new(&cancelDataCreationRequestOp_) CancelDataCreationRequestOp(std::move(source.cancelDataCreationRequestOp_));
break;
}

    }
    ~_body_t() {
switch (type_)
{
    case (int32_t)OperationType::CREATE_ACCOUNT:
createAccountOp_.~CreateAccountOp();
break;
    case (int32_t)OperationType::CREATE_ISSUANCE_REQUEST:
createIssuanceRequestOp_.~CreateIssuanceRequestOp();
break;
    case (int32_t)OperationType::SET_FEES:
setFeesOp_.~SetFeesOp();
break;
    case (int32_t)OperationType::CREATE_WITHDRAWAL_REQUEST:
createWithdrawalRequestOp_.~CreateWithdrawalRequestOp();
break;
    case (int32_t)OperationType::MANAGE_BALANCE:
manageBalanceOp_.~ManageBalanceOp();
break;
    case (int32_t)OperationType::MANAGE_ASSET:
manageAssetOp_.~ManageAssetOp();
break;
    case (int32_t)OperationType::CREATE_PREISSUANCE_REQUEST:
createPreIssuanceRequest_.~CreatePreIssuanceRequestOp();
break;
    case (int32_t)OperationType::MANAGE_LIMITS:
manageLimitsOp_.~ManageLimitsOp();
break;
    case (int32_t)OperationType::MANAGE_ASSET_PAIR:
manageAssetPairOp_.~ManageAssetPairOp();
break;
    case (int32_t)OperationType::MANAGE_OFFER:
manageOfferOp_.~ManageOfferOp();
break;
    case (int32_t)OperationType::MANAGE_INVOICE_REQUEST:
manageInvoiceRequestOp_.~ManageInvoiceRequestOp();
break;
    case (int32_t)OperationType::REVIEW_REQUEST:
reviewRequestOp_.~ReviewRequestOp();
break;
    case (int32_t)OperationType::CREATE_SALE_REQUEST:
createSaleCreationRequestOp_.~CreateSaleCreationRequestOp();
break;
    case (int32_t)OperationType::CHECK_SALE_STATE:
checkSaleStateOp_.~CheckSaleStateOp();
break;
    case (int32_t)OperationType::PAYOUT:
payoutOp_.~PayoutOp();
break;
    case (int32_t)OperationType::CREATE_AML_ALERT:
createAMLAlertRequestOp_.~CreateAMLAlertRequestOp();
break;
    case (int32_t)OperationType::MANAGE_KEY_VALUE:
manageKeyValueOp_.~ManageKeyValueOp();
break;
    case (int32_t)OperationType::CREATE_CHANGE_ROLE_REQUEST:
createChangeRoleRequestOp_.~CreateChangeRoleRequestOp();
break;
    case (int32_t)OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
manageExternalSystemAccountIdPoolEntryOp_.~ManageExternalSystemAccountIdPoolEntryOp();
break;
    case (int32_t)OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID:
bindExternalSystemAccountIdOp_.~BindExternalSystemAccountIdOp();
break;
    case (int32_t)OperationType::PAYMENT:
paymentOp_.~PaymentOp();
break;
    case (int32_t)OperationType::MANAGE_SALE:
manageSaleOp_.~ManageSaleOp();
break;
    case (int32_t)OperationType::CREATE_MANAGE_LIMITS_REQUEST:
createManageLimitsRequestOp_.~CreateManageLimitsRequestOp();
break;
    case (int32_t)OperationType::MANAGE_CONTRACT_REQUEST:
manageContractRequestOp_.~ManageContractRequestOp();
break;
    case (int32_t)OperationType::MANAGE_CONTRACT:
manageContractOp_.~ManageContractOp();
break;
    case (int32_t)OperationType::CANCEL_SALE_REQUEST:
cancelSaleCreationRequestOp_.~CancelSaleCreationRequestOp();
break;
    case (int32_t)OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST:
createAtomicSwapAskRequestOp_.~CreateAtomicSwapAskRequestOp();
break;
    case (int32_t)OperationType::CANCEL_ATOMIC_SWAP_ASK:
cancelAtomicSwapAskOp_.~CancelAtomicSwapAskOp();
break;
    case (int32_t)OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST:
createAtomicSwapBidRequestOp_.~CreateAtomicSwapBidRequestOp();
break;
    case (int32_t)OperationType::MANAGE_ACCOUNT_ROLE:
manageAccountRoleOp_.~ManageAccountRoleOp();
break;
    case (int32_t)OperationType::MANAGE_ACCOUNT_RULE:
manageAccountRuleOp_.~ManageAccountRuleOp();
break;
    case (int32_t)OperationType::MANAGE_SIGNER:
manageSignerOp_.~ManageSignerOp();
break;
    case (int32_t)OperationType::MANAGE_SIGNER_ROLE:
manageSignerRoleOp_.~ManageSignerRoleOp();
break;
    case (int32_t)OperationType::MANAGE_SIGNER_RULE:
manageSignerRuleOp_.~ManageSignerRuleOp();
break;
    case (int32_t)OperationType::STAMP:
stampOp_.~StampOp();
break;
    case (int32_t)OperationType::LICENSE:
licenseOp_.~LicenseOp();
break;
    case (int32_t)OperationType::MANAGE_CREATE_POLL_REQUEST:
manageCreatePollRequestOp_.~ManageCreatePollRequestOp();
break;
    case (int32_t)OperationType::MANAGE_POLL:
managePollOp_.~ManagePollOp();
break;
    case (int32_t)OperationType::MANAGE_VOTE:
manageVoteOp_.~ManageVoteOp();
break;
    case (int32_t)OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE:
manageAccountSpecificRuleOp_.~ManageAccountSpecificRuleOp();
break;
    case (int32_t)OperationType::CANCEL_CHANGE_ROLE_REQUEST:
cancelChangeRoleRequestOp_.~CancelChangeRoleRequestOp();
break;
    case (int32_t)OperationType::REMOVE_ASSET_PAIR:
removeAssetPairOp_.~RemoveAssetPairOp();
break;
    case (int32_t)OperationType::INITIATE_KYC_RECOVERY:
initiateKYCRecoveryOp_.~InitiateKYCRecoveryOp();
break;
    case (int32_t)OperationType::CREATE_KYC_RECOVERY_REQUEST:
createKYCRecoveryRequestOp_.~CreateKYCRecoveryRequestOp();
break;
    case (int32_t)OperationType::CREATE_MANAGE_OFFER_REQUEST:
createManageOfferRequestOp_.~CreateManageOfferRequestOp();
break;
    case (int32_t)OperationType::CREATE_PAYMENT_REQUEST:
createPaymentRequestOp_.~CreatePaymentRequestOp();
break;
    case (int32_t)OperationType::REMOVE_ASSET:
removeAssetOp_.~RemoveAssetOp();
break;
    case (int32_t)OperationType::OPEN_SWAP:
openSwapOp_.~OpenSwapOp();
break;
    case (int32_t)OperationType::CLOSE_SWAP:
closeSwapOp_.~CloseSwapOp();
break;
    case (int32_t)OperationType::CREATE_REDEMPTION_REQUEST:
createRedemptionRequestOp_.~CreateRedemptionRequestOp();
break;
    case (int32_t)OperationType::CREATE_DATA:
createDataOp_.~CreateDataOp();
break;
    case (int32_t)OperationType::UPDATE_DATA:
updateDataOp_.~UpdateDataOp();
break;
    case (int32_t)OperationType::REMOVE_DATA:
removeDataOp_.~RemoveDataOp();
break;
    case (int32_t)OperationType::CREATE_DATA_CREATION_REQUEST:
createDataCreationRequestOp_.~CreateDataCreationRequestOp();
break;
    case (int32_t)OperationType::CANCEL_DATA_CREATION_REQUEST:
cancelDataCreationRequestOp_.~CancelDataCreationRequestOp();
break;
}
}

    _body_t &operator=(const _body_t &source) {
      if (type_ == source.type_)
{
switch (type_)
{
      case (int32_t)OperationType::CREATE_ACCOUNT:
createAccountOp_ = source.createAccountOp_;
break;
      case (int32_t)OperationType::CREATE_ISSUANCE_REQUEST:
createIssuanceRequestOp_ = source.createIssuanceRequestOp_;
break;
      case (int32_t)OperationType::SET_FEES:
setFeesOp_ = source.setFeesOp_;
break;
      case (int32_t)OperationType::CREATE_WITHDRAWAL_REQUEST:
createWithdrawalRequestOp_ = source.createWithdrawalRequestOp_;
break;
      case (int32_t)OperationType::MANAGE_BALANCE:
manageBalanceOp_ = source.manageBalanceOp_;
break;
      case (int32_t)OperationType::MANAGE_ASSET:
manageAssetOp_ = source.manageAssetOp_;
break;
      case (int32_t)OperationType::CREATE_PREISSUANCE_REQUEST:
createPreIssuanceRequest_ = source.createPreIssuanceRequest_;
break;
      case (int32_t)OperationType::MANAGE_LIMITS:
manageLimitsOp_ = source.manageLimitsOp_;
break;
      case (int32_t)OperationType::MANAGE_ASSET_PAIR:
manageAssetPairOp_ = source.manageAssetPairOp_;
break;
      case (int32_t)OperationType::MANAGE_OFFER:
manageOfferOp_ = source.manageOfferOp_;
break;
      case (int32_t)OperationType::MANAGE_INVOICE_REQUEST:
manageInvoiceRequestOp_ = source.manageInvoiceRequestOp_;
break;
      case (int32_t)OperationType::REVIEW_REQUEST:
reviewRequestOp_ = source.reviewRequestOp_;
break;
      case (int32_t)OperationType::CREATE_SALE_REQUEST:
createSaleCreationRequestOp_ = source.createSaleCreationRequestOp_;
break;
      case (int32_t)OperationType::CHECK_SALE_STATE:
checkSaleStateOp_ = source.checkSaleStateOp_;
break;
      case (int32_t)OperationType::PAYOUT:
payoutOp_ = source.payoutOp_;
break;
      case (int32_t)OperationType::CREATE_AML_ALERT:
createAMLAlertRequestOp_ = source.createAMLAlertRequestOp_;
break;
      case (int32_t)OperationType::MANAGE_KEY_VALUE:
manageKeyValueOp_ = source.manageKeyValueOp_;
break;
      case (int32_t)OperationType::CREATE_CHANGE_ROLE_REQUEST:
createChangeRoleRequestOp_ = source.createChangeRoleRequestOp_;
break;
      case (int32_t)OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
manageExternalSystemAccountIdPoolEntryOp_ = source.manageExternalSystemAccountIdPoolEntryOp_;
break;
      case (int32_t)OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID:
bindExternalSystemAccountIdOp_ = source.bindExternalSystemAccountIdOp_;
break;
      case (int32_t)OperationType::PAYMENT:
paymentOp_ = source.paymentOp_;
break;
      case (int32_t)OperationType::MANAGE_SALE:
manageSaleOp_ = source.manageSaleOp_;
break;
      case (int32_t)OperationType::CREATE_MANAGE_LIMITS_REQUEST:
createManageLimitsRequestOp_ = source.createManageLimitsRequestOp_;
break;
      case (int32_t)OperationType::MANAGE_CONTRACT_REQUEST:
manageContractRequestOp_ = source.manageContractRequestOp_;
break;
      case (int32_t)OperationType::MANAGE_CONTRACT:
manageContractOp_ = source.manageContractOp_;
break;
      case (int32_t)OperationType::CANCEL_SALE_REQUEST:
cancelSaleCreationRequestOp_ = source.cancelSaleCreationRequestOp_;
break;
      case (int32_t)OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST:
createAtomicSwapAskRequestOp_ = source.createAtomicSwapAskRequestOp_;
break;
      case (int32_t)OperationType::CANCEL_ATOMIC_SWAP_ASK:
cancelAtomicSwapAskOp_ = source.cancelAtomicSwapAskOp_;
break;
      case (int32_t)OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST:
createAtomicSwapBidRequestOp_ = source.createAtomicSwapBidRequestOp_;
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_ROLE:
manageAccountRoleOp_ = source.manageAccountRoleOp_;
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_RULE:
manageAccountRuleOp_ = source.manageAccountRuleOp_;
break;
      case (int32_t)OperationType::MANAGE_SIGNER:
manageSignerOp_ = source.manageSignerOp_;
break;
      case (int32_t)OperationType::MANAGE_SIGNER_ROLE:
manageSignerRoleOp_ = source.manageSignerRoleOp_;
break;
      case (int32_t)OperationType::MANAGE_SIGNER_RULE:
manageSignerRuleOp_ = source.manageSignerRuleOp_;
break;
      case (int32_t)OperationType::STAMP:
stampOp_ = source.stampOp_;
break;
      case (int32_t)OperationType::LICENSE:
licenseOp_ = source.licenseOp_;
break;
      case (int32_t)OperationType::MANAGE_CREATE_POLL_REQUEST:
manageCreatePollRequestOp_ = source.manageCreatePollRequestOp_;
break;
      case (int32_t)OperationType::MANAGE_POLL:
managePollOp_ = source.managePollOp_;
break;
      case (int32_t)OperationType::MANAGE_VOTE:
manageVoteOp_ = source.manageVoteOp_;
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE:
manageAccountSpecificRuleOp_ = source.manageAccountSpecificRuleOp_;
break;
      case (int32_t)OperationType::CANCEL_CHANGE_ROLE_REQUEST:
cancelChangeRoleRequestOp_ = source.cancelChangeRoleRequestOp_;
break;
      case (int32_t)OperationType::REMOVE_ASSET_PAIR:
removeAssetPairOp_ = source.removeAssetPairOp_;
break;
      case (int32_t)OperationType::INITIATE_KYC_RECOVERY:
initiateKYCRecoveryOp_ = source.initiateKYCRecoveryOp_;
break;
      case (int32_t)OperationType::CREATE_KYC_RECOVERY_REQUEST:
createKYCRecoveryRequestOp_ = source.createKYCRecoveryRequestOp_;
break;
      case (int32_t)OperationType::CREATE_MANAGE_OFFER_REQUEST:
createManageOfferRequestOp_ = source.createManageOfferRequestOp_;
break;
      case (int32_t)OperationType::CREATE_PAYMENT_REQUEST:
createPaymentRequestOp_ = source.createPaymentRequestOp_;
break;
      case (int32_t)OperationType::REMOVE_ASSET:
removeAssetOp_ = source.removeAssetOp_;
break;
      case (int32_t)OperationType::OPEN_SWAP:
openSwapOp_ = source.openSwapOp_;
break;
      case (int32_t)OperationType::CLOSE_SWAP:
closeSwapOp_ = source.closeSwapOp_;
break;
      case (int32_t)OperationType::CREATE_REDEMPTION_REQUEST:
createRedemptionRequestOp_ = source.createRedemptionRequestOp_;
break;
      case (int32_t)OperationType::CREATE_DATA:
createDataOp_ = source.createDataOp_;
break;
      case (int32_t)OperationType::UPDATE_DATA:
updateDataOp_ = source.updateDataOp_;
break;
      case (int32_t)OperationType::REMOVE_DATA:
removeDataOp_ = source.removeDataOp_;
break;
      case (int32_t)OperationType::CREATE_DATA_CREATION_REQUEST:
createDataCreationRequestOp_ = source.createDataCreationRequestOp_;
break;
      case (int32_t)OperationType::CANCEL_DATA_CREATION_REQUEST:
cancelDataCreationRequestOp_ = source.cancelDataCreationRequestOp_;
break;
}
}
else {this->~_body_t();
      type_ = source.type_;
switch (type_)
{
      case (int32_t)OperationType::CREATE_ACCOUNT:
new(&createAccountOp_) CreateAccountOp(source.createAccountOp_);
break;
      case (int32_t)OperationType::CREATE_ISSUANCE_REQUEST:
new(&createIssuanceRequestOp_) CreateIssuanceRequestOp(source.createIssuanceRequestOp_);
break;
      case (int32_t)OperationType::SET_FEES:
new(&setFeesOp_) SetFeesOp(source.setFeesOp_);
break;
      case (int32_t)OperationType::CREATE_WITHDRAWAL_REQUEST:
new(&createWithdrawalRequestOp_) CreateWithdrawalRequestOp(source.createWithdrawalRequestOp_);
break;
      case (int32_t)OperationType::MANAGE_BALANCE:
new(&manageBalanceOp_) ManageBalanceOp(source.manageBalanceOp_);
break;
      case (int32_t)OperationType::MANAGE_ASSET:
new(&manageAssetOp_) ManageAssetOp(source.manageAssetOp_);
break;
      case (int32_t)OperationType::CREATE_PREISSUANCE_REQUEST:
new(&createPreIssuanceRequest_) CreatePreIssuanceRequestOp(source.createPreIssuanceRequest_);
break;
      case (int32_t)OperationType::MANAGE_LIMITS:
new(&manageLimitsOp_) ManageLimitsOp(source.manageLimitsOp_);
break;
      case (int32_t)OperationType::MANAGE_ASSET_PAIR:
new(&manageAssetPairOp_) ManageAssetPairOp(source.manageAssetPairOp_);
break;
      case (int32_t)OperationType::MANAGE_OFFER:
new(&manageOfferOp_) ManageOfferOp(source.manageOfferOp_);
break;
      case (int32_t)OperationType::MANAGE_INVOICE_REQUEST:
new(&manageInvoiceRequestOp_) ManageInvoiceRequestOp(source.manageInvoiceRequestOp_);
break;
      case (int32_t)OperationType::REVIEW_REQUEST:
new(&reviewRequestOp_) ReviewRequestOp(source.reviewRequestOp_);
break;
      case (int32_t)OperationType::CREATE_SALE_REQUEST:
new(&createSaleCreationRequestOp_) CreateSaleCreationRequestOp(source.createSaleCreationRequestOp_);
break;
      case (int32_t)OperationType::CHECK_SALE_STATE:
new(&checkSaleStateOp_) CheckSaleStateOp(source.checkSaleStateOp_);
break;
      case (int32_t)OperationType::PAYOUT:
new(&payoutOp_) PayoutOp(source.payoutOp_);
break;
      case (int32_t)OperationType::CREATE_AML_ALERT:
new(&createAMLAlertRequestOp_) CreateAMLAlertRequestOp(source.createAMLAlertRequestOp_);
break;
      case (int32_t)OperationType::MANAGE_KEY_VALUE:
new(&manageKeyValueOp_) ManageKeyValueOp(source.manageKeyValueOp_);
break;
      case (int32_t)OperationType::CREATE_CHANGE_ROLE_REQUEST:
new(&createChangeRoleRequestOp_) CreateChangeRoleRequestOp(source.createChangeRoleRequestOp_);
break;
      case (int32_t)OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
new(&manageExternalSystemAccountIdPoolEntryOp_) ManageExternalSystemAccountIdPoolEntryOp(source.manageExternalSystemAccountIdPoolEntryOp_);
break;
      case (int32_t)OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID:
new(&bindExternalSystemAccountIdOp_) BindExternalSystemAccountIdOp(source.bindExternalSystemAccountIdOp_);
break;
      case (int32_t)OperationType::PAYMENT:
new(&paymentOp_) PaymentOp(source.paymentOp_);
break;
      case (int32_t)OperationType::MANAGE_SALE:
new(&manageSaleOp_) ManageSaleOp(source.manageSaleOp_);
break;
      case (int32_t)OperationType::CREATE_MANAGE_LIMITS_REQUEST:
new(&createManageLimitsRequestOp_) CreateManageLimitsRequestOp(source.createManageLimitsRequestOp_);
break;
      case (int32_t)OperationType::MANAGE_CONTRACT_REQUEST:
new(&manageContractRequestOp_) ManageContractRequestOp(source.manageContractRequestOp_);
break;
      case (int32_t)OperationType::MANAGE_CONTRACT:
new(&manageContractOp_) ManageContractOp(source.manageContractOp_);
break;
      case (int32_t)OperationType::CANCEL_SALE_REQUEST:
new(&cancelSaleCreationRequestOp_) CancelSaleCreationRequestOp(source.cancelSaleCreationRequestOp_);
break;
      case (int32_t)OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST:
new(&createAtomicSwapAskRequestOp_) CreateAtomicSwapAskRequestOp(source.createAtomicSwapAskRequestOp_);
break;
      case (int32_t)OperationType::CANCEL_ATOMIC_SWAP_ASK:
new(&cancelAtomicSwapAskOp_) CancelAtomicSwapAskOp(source.cancelAtomicSwapAskOp_);
break;
      case (int32_t)OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST:
new(&createAtomicSwapBidRequestOp_) CreateAtomicSwapBidRequestOp(source.createAtomicSwapBidRequestOp_);
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_ROLE:
new(&manageAccountRoleOp_) ManageAccountRoleOp(source.manageAccountRoleOp_);
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_RULE:
new(&manageAccountRuleOp_) ManageAccountRuleOp(source.manageAccountRuleOp_);
break;
      case (int32_t)OperationType::MANAGE_SIGNER:
new(&manageSignerOp_) ManageSignerOp(source.manageSignerOp_);
break;
      case (int32_t)OperationType::MANAGE_SIGNER_ROLE:
new(&manageSignerRoleOp_) ManageSignerRoleOp(source.manageSignerRoleOp_);
break;
      case (int32_t)OperationType::MANAGE_SIGNER_RULE:
new(&manageSignerRuleOp_) ManageSignerRuleOp(source.manageSignerRuleOp_);
break;
      case (int32_t)OperationType::STAMP:
new(&stampOp_) StampOp(source.stampOp_);
break;
      case (int32_t)OperationType::LICENSE:
new(&licenseOp_) LicenseOp(source.licenseOp_);
break;
      case (int32_t)OperationType::MANAGE_CREATE_POLL_REQUEST:
new(&manageCreatePollRequestOp_) ManageCreatePollRequestOp(source.manageCreatePollRequestOp_);
break;
      case (int32_t)OperationType::MANAGE_POLL:
new(&managePollOp_) ManagePollOp(source.managePollOp_);
break;
      case (int32_t)OperationType::MANAGE_VOTE:
new(&manageVoteOp_) ManageVoteOp(source.manageVoteOp_);
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE:
new(&manageAccountSpecificRuleOp_) ManageAccountSpecificRuleOp(source.manageAccountSpecificRuleOp_);
break;
      case (int32_t)OperationType::CANCEL_CHANGE_ROLE_REQUEST:
new(&cancelChangeRoleRequestOp_) CancelChangeRoleRequestOp(source.cancelChangeRoleRequestOp_);
break;
      case (int32_t)OperationType::REMOVE_ASSET_PAIR:
new(&removeAssetPairOp_) RemoveAssetPairOp(source.removeAssetPairOp_);
break;
      case (int32_t)OperationType::INITIATE_KYC_RECOVERY:
new(&initiateKYCRecoveryOp_) InitiateKYCRecoveryOp(source.initiateKYCRecoveryOp_);
break;
      case (int32_t)OperationType::CREATE_KYC_RECOVERY_REQUEST:
new(&createKYCRecoveryRequestOp_) CreateKYCRecoveryRequestOp(source.createKYCRecoveryRequestOp_);
break;
      case (int32_t)OperationType::CREATE_MANAGE_OFFER_REQUEST:
new(&createManageOfferRequestOp_) CreateManageOfferRequestOp(source.createManageOfferRequestOp_);
break;
      case (int32_t)OperationType::CREATE_PAYMENT_REQUEST:
new(&createPaymentRequestOp_) CreatePaymentRequestOp(source.createPaymentRequestOp_);
break;
      case (int32_t)OperationType::REMOVE_ASSET:
new(&removeAssetOp_) RemoveAssetOp(source.removeAssetOp_);
break;
      case (int32_t)OperationType::OPEN_SWAP:
new(&openSwapOp_) OpenSwapOp(source.openSwapOp_);
break;
      case (int32_t)OperationType::CLOSE_SWAP:
new(&closeSwapOp_) CloseSwapOp(source.closeSwapOp_);
break;
      case (int32_t)OperationType::CREATE_REDEMPTION_REQUEST:
new(&createRedemptionRequestOp_) CreateRedemptionRequestOp(source.createRedemptionRequestOp_);
break;
      case (int32_t)OperationType::CREATE_DATA:
new(&createDataOp_) CreateDataOp(source.createDataOp_);
break;
      case (int32_t)OperationType::UPDATE_DATA:
new(&updateDataOp_) UpdateDataOp(source.updateDataOp_);
break;
      case (int32_t)OperationType::REMOVE_DATA:
new(&removeDataOp_) RemoveDataOp(source.removeDataOp_);
break;
      case (int32_t)OperationType::CREATE_DATA_CREATION_REQUEST:
new(&createDataCreationRequestOp_) CreateDataCreationRequestOp(source.createDataCreationRequestOp_);
break;
      case (int32_t)OperationType::CANCEL_DATA_CREATION_REQUEST:
new(&cancelDataCreationRequestOp_) CancelDataCreationRequestOp(source.cancelDataCreationRequestOp_);
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
      case (int32_t)OperationType::CREATE_ACCOUNT:
createAccountOp_ = std::move(source.createAccountOp_);
break;
      case (int32_t)OperationType::CREATE_ISSUANCE_REQUEST:
createIssuanceRequestOp_ = std::move(source.createIssuanceRequestOp_);
break;
      case (int32_t)OperationType::SET_FEES:
setFeesOp_ = std::move(source.setFeesOp_);
break;
      case (int32_t)OperationType::CREATE_WITHDRAWAL_REQUEST:
createWithdrawalRequestOp_ = std::move(source.createWithdrawalRequestOp_);
break;
      case (int32_t)OperationType::MANAGE_BALANCE:
manageBalanceOp_ = std::move(source.manageBalanceOp_);
break;
      case (int32_t)OperationType::MANAGE_ASSET:
manageAssetOp_ = std::move(source.manageAssetOp_);
break;
      case (int32_t)OperationType::CREATE_PREISSUANCE_REQUEST:
createPreIssuanceRequest_ = std::move(source.createPreIssuanceRequest_);
break;
      case (int32_t)OperationType::MANAGE_LIMITS:
manageLimitsOp_ = std::move(source.manageLimitsOp_);
break;
      case (int32_t)OperationType::MANAGE_ASSET_PAIR:
manageAssetPairOp_ = std::move(source.manageAssetPairOp_);
break;
      case (int32_t)OperationType::MANAGE_OFFER:
manageOfferOp_ = std::move(source.manageOfferOp_);
break;
      case (int32_t)OperationType::MANAGE_INVOICE_REQUEST:
manageInvoiceRequestOp_ = std::move(source.manageInvoiceRequestOp_);
break;
      case (int32_t)OperationType::REVIEW_REQUEST:
reviewRequestOp_ = std::move(source.reviewRequestOp_);
break;
      case (int32_t)OperationType::CREATE_SALE_REQUEST:
createSaleCreationRequestOp_ = std::move(source.createSaleCreationRequestOp_);
break;
      case (int32_t)OperationType::CHECK_SALE_STATE:
checkSaleStateOp_ = std::move(source.checkSaleStateOp_);
break;
      case (int32_t)OperationType::PAYOUT:
payoutOp_ = std::move(source.payoutOp_);
break;
      case (int32_t)OperationType::CREATE_AML_ALERT:
createAMLAlertRequestOp_ = std::move(source.createAMLAlertRequestOp_);
break;
      case (int32_t)OperationType::MANAGE_KEY_VALUE:
manageKeyValueOp_ = std::move(source.manageKeyValueOp_);
break;
      case (int32_t)OperationType::CREATE_CHANGE_ROLE_REQUEST:
createChangeRoleRequestOp_ = std::move(source.createChangeRoleRequestOp_);
break;
      case (int32_t)OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
manageExternalSystemAccountIdPoolEntryOp_ = std::move(source.manageExternalSystemAccountIdPoolEntryOp_);
break;
      case (int32_t)OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID:
bindExternalSystemAccountIdOp_ = std::move(source.bindExternalSystemAccountIdOp_);
break;
      case (int32_t)OperationType::PAYMENT:
paymentOp_ = std::move(source.paymentOp_);
break;
      case (int32_t)OperationType::MANAGE_SALE:
manageSaleOp_ = std::move(source.manageSaleOp_);
break;
      case (int32_t)OperationType::CREATE_MANAGE_LIMITS_REQUEST:
createManageLimitsRequestOp_ = std::move(source.createManageLimitsRequestOp_);
break;
      case (int32_t)OperationType::MANAGE_CONTRACT_REQUEST:
manageContractRequestOp_ = std::move(source.manageContractRequestOp_);
break;
      case (int32_t)OperationType::MANAGE_CONTRACT:
manageContractOp_ = std::move(source.manageContractOp_);
break;
      case (int32_t)OperationType::CANCEL_SALE_REQUEST:
cancelSaleCreationRequestOp_ = std::move(source.cancelSaleCreationRequestOp_);
break;
      case (int32_t)OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST:
createAtomicSwapAskRequestOp_ = std::move(source.createAtomicSwapAskRequestOp_);
break;
      case (int32_t)OperationType::CANCEL_ATOMIC_SWAP_ASK:
cancelAtomicSwapAskOp_ = std::move(source.cancelAtomicSwapAskOp_);
break;
      case (int32_t)OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST:
createAtomicSwapBidRequestOp_ = std::move(source.createAtomicSwapBidRequestOp_);
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_ROLE:
manageAccountRoleOp_ = std::move(source.manageAccountRoleOp_);
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_RULE:
manageAccountRuleOp_ = std::move(source.manageAccountRuleOp_);
break;
      case (int32_t)OperationType::MANAGE_SIGNER:
manageSignerOp_ = std::move(source.manageSignerOp_);
break;
      case (int32_t)OperationType::MANAGE_SIGNER_ROLE:
manageSignerRoleOp_ = std::move(source.manageSignerRoleOp_);
break;
      case (int32_t)OperationType::MANAGE_SIGNER_RULE:
manageSignerRuleOp_ = std::move(source.manageSignerRuleOp_);
break;
      case (int32_t)OperationType::STAMP:
stampOp_ = std::move(source.stampOp_);
break;
      case (int32_t)OperationType::LICENSE:
licenseOp_ = std::move(source.licenseOp_);
break;
      case (int32_t)OperationType::MANAGE_CREATE_POLL_REQUEST:
manageCreatePollRequestOp_ = std::move(source.manageCreatePollRequestOp_);
break;
      case (int32_t)OperationType::MANAGE_POLL:
managePollOp_ = std::move(source.managePollOp_);
break;
      case (int32_t)OperationType::MANAGE_VOTE:
manageVoteOp_ = std::move(source.manageVoteOp_);
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE:
manageAccountSpecificRuleOp_ = std::move(source.manageAccountSpecificRuleOp_);
break;
      case (int32_t)OperationType::CANCEL_CHANGE_ROLE_REQUEST:
cancelChangeRoleRequestOp_ = std::move(source.cancelChangeRoleRequestOp_);
break;
      case (int32_t)OperationType::REMOVE_ASSET_PAIR:
removeAssetPairOp_ = std::move(source.removeAssetPairOp_);
break;
      case (int32_t)OperationType::INITIATE_KYC_RECOVERY:
initiateKYCRecoveryOp_ = std::move(source.initiateKYCRecoveryOp_);
break;
      case (int32_t)OperationType::CREATE_KYC_RECOVERY_REQUEST:
createKYCRecoveryRequestOp_ = std::move(source.createKYCRecoveryRequestOp_);
break;
      case (int32_t)OperationType::CREATE_MANAGE_OFFER_REQUEST:
createManageOfferRequestOp_ = std::move(source.createManageOfferRequestOp_);
break;
      case (int32_t)OperationType::CREATE_PAYMENT_REQUEST:
createPaymentRequestOp_ = std::move(source.createPaymentRequestOp_);
break;
      case (int32_t)OperationType::REMOVE_ASSET:
removeAssetOp_ = std::move(source.removeAssetOp_);
break;
      case (int32_t)OperationType::OPEN_SWAP:
openSwapOp_ = std::move(source.openSwapOp_);
break;
      case (int32_t)OperationType::CLOSE_SWAP:
closeSwapOp_ = std::move(source.closeSwapOp_);
break;
      case (int32_t)OperationType::CREATE_REDEMPTION_REQUEST:
createRedemptionRequestOp_ = std::move(source.createRedemptionRequestOp_);
break;
      case (int32_t)OperationType::CREATE_DATA:
createDataOp_ = std::move(source.createDataOp_);
break;
      case (int32_t)OperationType::UPDATE_DATA:
updateDataOp_ = std::move(source.updateDataOp_);
break;
      case (int32_t)OperationType::REMOVE_DATA:
removeDataOp_ = std::move(source.removeDataOp_);
break;
      case (int32_t)OperationType::CREATE_DATA_CREATION_REQUEST:
createDataCreationRequestOp_ = std::move(source.createDataCreationRequestOp_);
break;
      case (int32_t)OperationType::CANCEL_DATA_CREATION_REQUEST:
cancelDataCreationRequestOp_ = std::move(source.cancelDataCreationRequestOp_);
break;
}
}
else {this->~_body_t();
      type_ = std::move(source.type_);
switch (type_)
{
      case (int32_t)OperationType::CREATE_ACCOUNT:
new(&createAccountOp_) CreateAccountOp(std::move(source.createAccountOp_));
break;
      case (int32_t)OperationType::CREATE_ISSUANCE_REQUEST:
new(&createIssuanceRequestOp_) CreateIssuanceRequestOp(std::move(source.createIssuanceRequestOp_));
break;
      case (int32_t)OperationType::SET_FEES:
new(&setFeesOp_) SetFeesOp(std::move(source.setFeesOp_));
break;
      case (int32_t)OperationType::CREATE_WITHDRAWAL_REQUEST:
new(&createWithdrawalRequestOp_) CreateWithdrawalRequestOp(std::move(source.createWithdrawalRequestOp_));
break;
      case (int32_t)OperationType::MANAGE_BALANCE:
new(&manageBalanceOp_) ManageBalanceOp(std::move(source.manageBalanceOp_));
break;
      case (int32_t)OperationType::MANAGE_ASSET:
new(&manageAssetOp_) ManageAssetOp(std::move(source.manageAssetOp_));
break;
      case (int32_t)OperationType::CREATE_PREISSUANCE_REQUEST:
new(&createPreIssuanceRequest_) CreatePreIssuanceRequestOp(std::move(source.createPreIssuanceRequest_));
break;
      case (int32_t)OperationType::MANAGE_LIMITS:
new(&manageLimitsOp_) ManageLimitsOp(std::move(source.manageLimitsOp_));
break;
      case (int32_t)OperationType::MANAGE_ASSET_PAIR:
new(&manageAssetPairOp_) ManageAssetPairOp(std::move(source.manageAssetPairOp_));
break;
      case (int32_t)OperationType::MANAGE_OFFER:
new(&manageOfferOp_) ManageOfferOp(std::move(source.manageOfferOp_));
break;
      case (int32_t)OperationType::MANAGE_INVOICE_REQUEST:
new(&manageInvoiceRequestOp_) ManageInvoiceRequestOp(std::move(source.manageInvoiceRequestOp_));
break;
      case (int32_t)OperationType::REVIEW_REQUEST:
new(&reviewRequestOp_) ReviewRequestOp(std::move(source.reviewRequestOp_));
break;
      case (int32_t)OperationType::CREATE_SALE_REQUEST:
new(&createSaleCreationRequestOp_) CreateSaleCreationRequestOp(std::move(source.createSaleCreationRequestOp_));
break;
      case (int32_t)OperationType::CHECK_SALE_STATE:
new(&checkSaleStateOp_) CheckSaleStateOp(std::move(source.checkSaleStateOp_));
break;
      case (int32_t)OperationType::PAYOUT:
new(&payoutOp_) PayoutOp(std::move(source.payoutOp_));
break;
      case (int32_t)OperationType::CREATE_AML_ALERT:
new(&createAMLAlertRequestOp_) CreateAMLAlertRequestOp(std::move(source.createAMLAlertRequestOp_));
break;
      case (int32_t)OperationType::MANAGE_KEY_VALUE:
new(&manageKeyValueOp_) ManageKeyValueOp(std::move(source.manageKeyValueOp_));
break;
      case (int32_t)OperationType::CREATE_CHANGE_ROLE_REQUEST:
new(&createChangeRoleRequestOp_) CreateChangeRoleRequestOp(std::move(source.createChangeRoleRequestOp_));
break;
      case (int32_t)OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
new(&manageExternalSystemAccountIdPoolEntryOp_) ManageExternalSystemAccountIdPoolEntryOp(std::move(source.manageExternalSystemAccountIdPoolEntryOp_));
break;
      case (int32_t)OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID:
new(&bindExternalSystemAccountIdOp_) BindExternalSystemAccountIdOp(std::move(source.bindExternalSystemAccountIdOp_));
break;
      case (int32_t)OperationType::PAYMENT:
new(&paymentOp_) PaymentOp(std::move(source.paymentOp_));
break;
      case (int32_t)OperationType::MANAGE_SALE:
new(&manageSaleOp_) ManageSaleOp(std::move(source.manageSaleOp_));
break;
      case (int32_t)OperationType::CREATE_MANAGE_LIMITS_REQUEST:
new(&createManageLimitsRequestOp_) CreateManageLimitsRequestOp(std::move(source.createManageLimitsRequestOp_));
break;
      case (int32_t)OperationType::MANAGE_CONTRACT_REQUEST:
new(&manageContractRequestOp_) ManageContractRequestOp(std::move(source.manageContractRequestOp_));
break;
      case (int32_t)OperationType::MANAGE_CONTRACT:
new(&manageContractOp_) ManageContractOp(std::move(source.manageContractOp_));
break;
      case (int32_t)OperationType::CANCEL_SALE_REQUEST:
new(&cancelSaleCreationRequestOp_) CancelSaleCreationRequestOp(std::move(source.cancelSaleCreationRequestOp_));
break;
      case (int32_t)OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST:
new(&createAtomicSwapAskRequestOp_) CreateAtomicSwapAskRequestOp(std::move(source.createAtomicSwapAskRequestOp_));
break;
      case (int32_t)OperationType::CANCEL_ATOMIC_SWAP_ASK:
new(&cancelAtomicSwapAskOp_) CancelAtomicSwapAskOp(std::move(source.cancelAtomicSwapAskOp_));
break;
      case (int32_t)OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST:
new(&createAtomicSwapBidRequestOp_) CreateAtomicSwapBidRequestOp(std::move(source.createAtomicSwapBidRequestOp_));
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_ROLE:
new(&manageAccountRoleOp_) ManageAccountRoleOp(std::move(source.manageAccountRoleOp_));
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_RULE:
new(&manageAccountRuleOp_) ManageAccountRuleOp(std::move(source.manageAccountRuleOp_));
break;
      case (int32_t)OperationType::MANAGE_SIGNER:
new(&manageSignerOp_) ManageSignerOp(std::move(source.manageSignerOp_));
break;
      case (int32_t)OperationType::MANAGE_SIGNER_ROLE:
new(&manageSignerRoleOp_) ManageSignerRoleOp(std::move(source.manageSignerRoleOp_));
break;
      case (int32_t)OperationType::MANAGE_SIGNER_RULE:
new(&manageSignerRuleOp_) ManageSignerRuleOp(std::move(source.manageSignerRuleOp_));
break;
      case (int32_t)OperationType::STAMP:
new(&stampOp_) StampOp(std::move(source.stampOp_));
break;
      case (int32_t)OperationType::LICENSE:
new(&licenseOp_) LicenseOp(std::move(source.licenseOp_));
break;
      case (int32_t)OperationType::MANAGE_CREATE_POLL_REQUEST:
new(&manageCreatePollRequestOp_) ManageCreatePollRequestOp(std::move(source.manageCreatePollRequestOp_));
break;
      case (int32_t)OperationType::MANAGE_POLL:
new(&managePollOp_) ManagePollOp(std::move(source.managePollOp_));
break;
      case (int32_t)OperationType::MANAGE_VOTE:
new(&manageVoteOp_) ManageVoteOp(std::move(source.manageVoteOp_));
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE:
new(&manageAccountSpecificRuleOp_) ManageAccountSpecificRuleOp(std::move(source.manageAccountSpecificRuleOp_));
break;
      case (int32_t)OperationType::CANCEL_CHANGE_ROLE_REQUEST:
new(&cancelChangeRoleRequestOp_) CancelChangeRoleRequestOp(std::move(source.cancelChangeRoleRequestOp_));
break;
      case (int32_t)OperationType::REMOVE_ASSET_PAIR:
new(&removeAssetPairOp_) RemoveAssetPairOp(std::move(source.removeAssetPairOp_));
break;
      case (int32_t)OperationType::INITIATE_KYC_RECOVERY:
new(&initiateKYCRecoveryOp_) InitiateKYCRecoveryOp(std::move(source.initiateKYCRecoveryOp_));
break;
      case (int32_t)OperationType::CREATE_KYC_RECOVERY_REQUEST:
new(&createKYCRecoveryRequestOp_) CreateKYCRecoveryRequestOp(std::move(source.createKYCRecoveryRequestOp_));
break;
      case (int32_t)OperationType::CREATE_MANAGE_OFFER_REQUEST:
new(&createManageOfferRequestOp_) CreateManageOfferRequestOp(std::move(source.createManageOfferRequestOp_));
break;
      case (int32_t)OperationType::CREATE_PAYMENT_REQUEST:
new(&createPaymentRequestOp_) CreatePaymentRequestOp(std::move(source.createPaymentRequestOp_));
break;
      case (int32_t)OperationType::REMOVE_ASSET:
new(&removeAssetOp_) RemoveAssetOp(std::move(source.removeAssetOp_));
break;
      case (int32_t)OperationType::OPEN_SWAP:
new(&openSwapOp_) OpenSwapOp(std::move(source.openSwapOp_));
break;
      case (int32_t)OperationType::CLOSE_SWAP:
new(&closeSwapOp_) CloseSwapOp(std::move(source.closeSwapOp_));
break;
      case (int32_t)OperationType::CREATE_REDEMPTION_REQUEST:
new(&createRedemptionRequestOp_) CreateRedemptionRequestOp(std::move(source.createRedemptionRequestOp_));
break;
      case (int32_t)OperationType::CREATE_DATA:
new(&createDataOp_) CreateDataOp(std::move(source.createDataOp_));
break;
      case (int32_t)OperationType::UPDATE_DATA:
new(&updateDataOp_) UpdateDataOp(std::move(source.updateDataOp_));
break;
      case (int32_t)OperationType::REMOVE_DATA:
new(&removeDataOp_) RemoveDataOp(std::move(source.removeDataOp_));
break;
      case (int32_t)OperationType::CREATE_DATA_CREATION_REQUEST:
new(&createDataCreationRequestOp_) CreateDataCreationRequestOp(std::move(source.createDataCreationRequestOp_));
break;
      case (int32_t)OperationType::CANCEL_DATA_CREATION_REQUEST:
new(&cancelDataCreationRequestOp_) CancelDataCreationRequestOp(std::move(source.cancelDataCreationRequestOp_));
break;
}
}
      return *this;
    }

    OperationType type() const { return OperationType(type_); }
    _body_t &type(OperationType _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    CreateAccountOp &createAccountOp() {
      if (_xdr_field_number(type_) == 1)
        return createAccountOp_;
      throw xdr::xdr_wrong_union("_body_t: createAccountOp accessed when not selected");
    }
    const CreateAccountOp &createAccountOp() const {
      if (_xdr_field_number(type_) == 1)
        return createAccountOp_;
      throw xdr::xdr_wrong_union("_body_t: createAccountOp accessed when not selected");
    }
    CreateIssuanceRequestOp &createIssuanceRequestOp() {
      if (_xdr_field_number(type_) == 2)
        return createIssuanceRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: createIssuanceRequestOp accessed when not selected");
    }
    const CreateIssuanceRequestOp &createIssuanceRequestOp() const {
      if (_xdr_field_number(type_) == 2)
        return createIssuanceRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: createIssuanceRequestOp accessed when not selected");
    }
    SetFeesOp &setFeesOp() {
      if (_xdr_field_number(type_) == 3)
        return setFeesOp_;
      throw xdr::xdr_wrong_union("_body_t: setFeesOp accessed when not selected");
    }
    const SetFeesOp &setFeesOp() const {
      if (_xdr_field_number(type_) == 3)
        return setFeesOp_;
      throw xdr::xdr_wrong_union("_body_t: setFeesOp accessed when not selected");
    }
    CreateWithdrawalRequestOp &createWithdrawalRequestOp() {
      if (_xdr_field_number(type_) == 4)
        return createWithdrawalRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: createWithdrawalRequestOp accessed when not selected");
    }
    const CreateWithdrawalRequestOp &createWithdrawalRequestOp() const {
      if (_xdr_field_number(type_) == 4)
        return createWithdrawalRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: createWithdrawalRequestOp accessed when not selected");
    }
    ManageBalanceOp &manageBalanceOp() {
      if (_xdr_field_number(type_) == 5)
        return manageBalanceOp_;
      throw xdr::xdr_wrong_union("_body_t: manageBalanceOp accessed when not selected");
    }
    const ManageBalanceOp &manageBalanceOp() const {
      if (_xdr_field_number(type_) == 5)
        return manageBalanceOp_;
      throw xdr::xdr_wrong_union("_body_t: manageBalanceOp accessed when not selected");
    }
    ManageAssetOp &manageAssetOp() {
      if (_xdr_field_number(type_) == 6)
        return manageAssetOp_;
      throw xdr::xdr_wrong_union("_body_t: manageAssetOp accessed when not selected");
    }
    const ManageAssetOp &manageAssetOp() const {
      if (_xdr_field_number(type_) == 6)
        return manageAssetOp_;
      throw xdr::xdr_wrong_union("_body_t: manageAssetOp accessed when not selected");
    }
    CreatePreIssuanceRequestOp &createPreIssuanceRequest() {
      if (_xdr_field_number(type_) == 7)
        return createPreIssuanceRequest_;
      throw xdr::xdr_wrong_union("_body_t: createPreIssuanceRequest accessed when not selected");
    }
    const CreatePreIssuanceRequestOp &createPreIssuanceRequest() const {
      if (_xdr_field_number(type_) == 7)
        return createPreIssuanceRequest_;
      throw xdr::xdr_wrong_union("_body_t: createPreIssuanceRequest accessed when not selected");
    }
    ManageLimitsOp &manageLimitsOp() {
      if (_xdr_field_number(type_) == 8)
        return manageLimitsOp_;
      throw xdr::xdr_wrong_union("_body_t: manageLimitsOp accessed when not selected");
    }
    const ManageLimitsOp &manageLimitsOp() const {
      if (_xdr_field_number(type_) == 8)
        return manageLimitsOp_;
      throw xdr::xdr_wrong_union("_body_t: manageLimitsOp accessed when not selected");
    }
    ManageAssetPairOp &manageAssetPairOp() {
      if (_xdr_field_number(type_) == 9)
        return manageAssetPairOp_;
      throw xdr::xdr_wrong_union("_body_t: manageAssetPairOp accessed when not selected");
    }
    const ManageAssetPairOp &manageAssetPairOp() const {
      if (_xdr_field_number(type_) == 9)
        return manageAssetPairOp_;
      throw xdr::xdr_wrong_union("_body_t: manageAssetPairOp accessed when not selected");
    }
    ManageOfferOp &manageOfferOp() {
      if (_xdr_field_number(type_) == 10)
        return manageOfferOp_;
      throw xdr::xdr_wrong_union("_body_t: manageOfferOp accessed when not selected");
    }
    const ManageOfferOp &manageOfferOp() const {
      if (_xdr_field_number(type_) == 10)
        return manageOfferOp_;
      throw xdr::xdr_wrong_union("_body_t: manageOfferOp accessed when not selected");
    }
    ManageInvoiceRequestOp &manageInvoiceRequestOp() {
      if (_xdr_field_number(type_) == 11)
        return manageInvoiceRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: manageInvoiceRequestOp accessed when not selected");
    }
    const ManageInvoiceRequestOp &manageInvoiceRequestOp() const {
      if (_xdr_field_number(type_) == 11)
        return manageInvoiceRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: manageInvoiceRequestOp accessed when not selected");
    }
    ReviewRequestOp &reviewRequestOp() {
      if (_xdr_field_number(type_) == 12)
        return reviewRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: reviewRequestOp accessed when not selected");
    }
    const ReviewRequestOp &reviewRequestOp() const {
      if (_xdr_field_number(type_) == 12)
        return reviewRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: reviewRequestOp accessed when not selected");
    }
    CreateSaleCreationRequestOp &createSaleCreationRequestOp() {
      if (_xdr_field_number(type_) == 13)
        return createSaleCreationRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: createSaleCreationRequestOp accessed when not selected");
    }
    const CreateSaleCreationRequestOp &createSaleCreationRequestOp() const {
      if (_xdr_field_number(type_) == 13)
        return createSaleCreationRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: createSaleCreationRequestOp accessed when not selected");
    }
    CheckSaleStateOp &checkSaleStateOp() {
      if (_xdr_field_number(type_) == 14)
        return checkSaleStateOp_;
      throw xdr::xdr_wrong_union("_body_t: checkSaleStateOp accessed when not selected");
    }
    const CheckSaleStateOp &checkSaleStateOp() const {
      if (_xdr_field_number(type_) == 14)
        return checkSaleStateOp_;
      throw xdr::xdr_wrong_union("_body_t: checkSaleStateOp accessed when not selected");
    }
    PayoutOp &payoutOp() {
      if (_xdr_field_number(type_) == 15)
        return payoutOp_;
      throw xdr::xdr_wrong_union("_body_t: payoutOp accessed when not selected");
    }
    const PayoutOp &payoutOp() const {
      if (_xdr_field_number(type_) == 15)
        return payoutOp_;
      throw xdr::xdr_wrong_union("_body_t: payoutOp accessed when not selected");
    }
    CreateAMLAlertRequestOp &createAMLAlertRequestOp() {
      if (_xdr_field_number(type_) == 16)
        return createAMLAlertRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: createAMLAlertRequestOp accessed when not selected");
    }
    const CreateAMLAlertRequestOp &createAMLAlertRequestOp() const {
      if (_xdr_field_number(type_) == 16)
        return createAMLAlertRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: createAMLAlertRequestOp accessed when not selected");
    }
    ManageKeyValueOp &manageKeyValueOp() {
      if (_xdr_field_number(type_) == 17)
        return manageKeyValueOp_;
      throw xdr::xdr_wrong_union("_body_t: manageKeyValueOp accessed when not selected");
    }
    const ManageKeyValueOp &manageKeyValueOp() const {
      if (_xdr_field_number(type_) == 17)
        return manageKeyValueOp_;
      throw xdr::xdr_wrong_union("_body_t: manageKeyValueOp accessed when not selected");
    }
    CreateChangeRoleRequestOp &createChangeRoleRequestOp() {
      if (_xdr_field_number(type_) == 18)
        return createChangeRoleRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: createChangeRoleRequestOp accessed when not selected");
    }
    const CreateChangeRoleRequestOp &createChangeRoleRequestOp() const {
      if (_xdr_field_number(type_) == 18)
        return createChangeRoleRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: createChangeRoleRequestOp accessed when not selected");
    }
    ManageExternalSystemAccountIdPoolEntryOp &manageExternalSystemAccountIdPoolEntryOp() {
      if (_xdr_field_number(type_) == 19)
        return manageExternalSystemAccountIdPoolEntryOp_;
      throw xdr::xdr_wrong_union("_body_t: manageExternalSystemAccountIdPoolEntryOp accessed when not selected");
    }
    const ManageExternalSystemAccountIdPoolEntryOp &manageExternalSystemAccountIdPoolEntryOp() const {
      if (_xdr_field_number(type_) == 19)
        return manageExternalSystemAccountIdPoolEntryOp_;
      throw xdr::xdr_wrong_union("_body_t: manageExternalSystemAccountIdPoolEntryOp accessed when not selected");
    }
    BindExternalSystemAccountIdOp &bindExternalSystemAccountIdOp() {
      if (_xdr_field_number(type_) == 20)
        return bindExternalSystemAccountIdOp_;
      throw xdr::xdr_wrong_union("_body_t: bindExternalSystemAccountIdOp accessed when not selected");
    }
    const BindExternalSystemAccountIdOp &bindExternalSystemAccountIdOp() const {
      if (_xdr_field_number(type_) == 20)
        return bindExternalSystemAccountIdOp_;
      throw xdr::xdr_wrong_union("_body_t: bindExternalSystemAccountIdOp accessed when not selected");
    }
    PaymentOp &paymentOp() {
      if (_xdr_field_number(type_) == 21)
        return paymentOp_;
      throw xdr::xdr_wrong_union("_body_t: paymentOp accessed when not selected");
    }
    const PaymentOp &paymentOp() const {
      if (_xdr_field_number(type_) == 21)
        return paymentOp_;
      throw xdr::xdr_wrong_union("_body_t: paymentOp accessed when not selected");
    }
    ManageSaleOp &manageSaleOp() {
      if (_xdr_field_number(type_) == 22)
        return manageSaleOp_;
      throw xdr::xdr_wrong_union("_body_t: manageSaleOp accessed when not selected");
    }
    const ManageSaleOp &manageSaleOp() const {
      if (_xdr_field_number(type_) == 22)
        return manageSaleOp_;
      throw xdr::xdr_wrong_union("_body_t: manageSaleOp accessed when not selected");
    }
    CreateManageLimitsRequestOp &createManageLimitsRequestOp() {
      if (_xdr_field_number(type_) == 23)
        return createManageLimitsRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: createManageLimitsRequestOp accessed when not selected");
    }
    const CreateManageLimitsRequestOp &createManageLimitsRequestOp() const {
      if (_xdr_field_number(type_) == 23)
        return createManageLimitsRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: createManageLimitsRequestOp accessed when not selected");
    }
    ManageContractRequestOp &manageContractRequestOp() {
      if (_xdr_field_number(type_) == 24)
        return manageContractRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: manageContractRequestOp accessed when not selected");
    }
    const ManageContractRequestOp &manageContractRequestOp() const {
      if (_xdr_field_number(type_) == 24)
        return manageContractRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: manageContractRequestOp accessed when not selected");
    }
    ManageContractOp &manageContractOp() {
      if (_xdr_field_number(type_) == 25)
        return manageContractOp_;
      throw xdr::xdr_wrong_union("_body_t: manageContractOp accessed when not selected");
    }
    const ManageContractOp &manageContractOp() const {
      if (_xdr_field_number(type_) == 25)
        return manageContractOp_;
      throw xdr::xdr_wrong_union("_body_t: manageContractOp accessed when not selected");
    }
    CancelSaleCreationRequestOp &cancelSaleCreationRequestOp() {
      if (_xdr_field_number(type_) == 26)
        return cancelSaleCreationRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: cancelSaleCreationRequestOp accessed when not selected");
    }
    const CancelSaleCreationRequestOp &cancelSaleCreationRequestOp() const {
      if (_xdr_field_number(type_) == 26)
        return cancelSaleCreationRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: cancelSaleCreationRequestOp accessed when not selected");
    }
    CreateAtomicSwapAskRequestOp &createAtomicSwapAskRequestOp() {
      if (_xdr_field_number(type_) == 27)
        return createAtomicSwapAskRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: createAtomicSwapAskRequestOp accessed when not selected");
    }
    const CreateAtomicSwapAskRequestOp &createAtomicSwapAskRequestOp() const {
      if (_xdr_field_number(type_) == 27)
        return createAtomicSwapAskRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: createAtomicSwapAskRequestOp accessed when not selected");
    }
    CancelAtomicSwapAskOp &cancelAtomicSwapAskOp() {
      if (_xdr_field_number(type_) == 28)
        return cancelAtomicSwapAskOp_;
      throw xdr::xdr_wrong_union("_body_t: cancelAtomicSwapAskOp accessed when not selected");
    }
    const CancelAtomicSwapAskOp &cancelAtomicSwapAskOp() const {
      if (_xdr_field_number(type_) == 28)
        return cancelAtomicSwapAskOp_;
      throw xdr::xdr_wrong_union("_body_t: cancelAtomicSwapAskOp accessed when not selected");
    }
    CreateAtomicSwapBidRequestOp &createAtomicSwapBidRequestOp() {
      if (_xdr_field_number(type_) == 29)
        return createAtomicSwapBidRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: createAtomicSwapBidRequestOp accessed when not selected");
    }
    const CreateAtomicSwapBidRequestOp &createAtomicSwapBidRequestOp() const {
      if (_xdr_field_number(type_) == 29)
        return createAtomicSwapBidRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: createAtomicSwapBidRequestOp accessed when not selected");
    }
    ManageAccountRoleOp &manageAccountRoleOp() {
      if (_xdr_field_number(type_) == 30)
        return manageAccountRoleOp_;
      throw xdr::xdr_wrong_union("_body_t: manageAccountRoleOp accessed when not selected");
    }
    const ManageAccountRoleOp &manageAccountRoleOp() const {
      if (_xdr_field_number(type_) == 30)
        return manageAccountRoleOp_;
      throw xdr::xdr_wrong_union("_body_t: manageAccountRoleOp accessed when not selected");
    }
    ManageAccountRuleOp &manageAccountRuleOp() {
      if (_xdr_field_number(type_) == 31)
        return manageAccountRuleOp_;
      throw xdr::xdr_wrong_union("_body_t: manageAccountRuleOp accessed when not selected");
    }
    const ManageAccountRuleOp &manageAccountRuleOp() const {
      if (_xdr_field_number(type_) == 31)
        return manageAccountRuleOp_;
      throw xdr::xdr_wrong_union("_body_t: manageAccountRuleOp accessed when not selected");
    }
    ManageSignerOp &manageSignerOp() {
      if (_xdr_field_number(type_) == 32)
        return manageSignerOp_;
      throw xdr::xdr_wrong_union("_body_t: manageSignerOp accessed when not selected");
    }
    const ManageSignerOp &manageSignerOp() const {
      if (_xdr_field_number(type_) == 32)
        return manageSignerOp_;
      throw xdr::xdr_wrong_union("_body_t: manageSignerOp accessed when not selected");
    }
    ManageSignerRoleOp &manageSignerRoleOp() {
      if (_xdr_field_number(type_) == 33)
        return manageSignerRoleOp_;
      throw xdr::xdr_wrong_union("_body_t: manageSignerRoleOp accessed when not selected");
    }
    const ManageSignerRoleOp &manageSignerRoleOp() const {
      if (_xdr_field_number(type_) == 33)
        return manageSignerRoleOp_;
      throw xdr::xdr_wrong_union("_body_t: manageSignerRoleOp accessed when not selected");
    }
    ManageSignerRuleOp &manageSignerRuleOp() {
      if (_xdr_field_number(type_) == 34)
        return manageSignerRuleOp_;
      throw xdr::xdr_wrong_union("_body_t: manageSignerRuleOp accessed when not selected");
    }
    const ManageSignerRuleOp &manageSignerRuleOp() const {
      if (_xdr_field_number(type_) == 34)
        return manageSignerRuleOp_;
      throw xdr::xdr_wrong_union("_body_t: manageSignerRuleOp accessed when not selected");
    }
    StampOp &stampOp() {
      if (_xdr_field_number(type_) == 35)
        return stampOp_;
      throw xdr::xdr_wrong_union("_body_t: stampOp accessed when not selected");
    }
    const StampOp &stampOp() const {
      if (_xdr_field_number(type_) == 35)
        return stampOp_;
      throw xdr::xdr_wrong_union("_body_t: stampOp accessed when not selected");
    }
    LicenseOp &licenseOp() {
      if (_xdr_field_number(type_) == 36)
        return licenseOp_;
      throw xdr::xdr_wrong_union("_body_t: licenseOp accessed when not selected");
    }
    const LicenseOp &licenseOp() const {
      if (_xdr_field_number(type_) == 36)
        return licenseOp_;
      throw xdr::xdr_wrong_union("_body_t: licenseOp accessed when not selected");
    }
    ManageCreatePollRequestOp &manageCreatePollRequestOp() {
      if (_xdr_field_number(type_) == 37)
        return manageCreatePollRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: manageCreatePollRequestOp accessed when not selected");
    }
    const ManageCreatePollRequestOp &manageCreatePollRequestOp() const {
      if (_xdr_field_number(type_) == 37)
        return manageCreatePollRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: manageCreatePollRequestOp accessed when not selected");
    }
    ManagePollOp &managePollOp() {
      if (_xdr_field_number(type_) == 38)
        return managePollOp_;
      throw xdr::xdr_wrong_union("_body_t: managePollOp accessed when not selected");
    }
    const ManagePollOp &managePollOp() const {
      if (_xdr_field_number(type_) == 38)
        return managePollOp_;
      throw xdr::xdr_wrong_union("_body_t: managePollOp accessed when not selected");
    }
    ManageVoteOp &manageVoteOp() {
      if (_xdr_field_number(type_) == 39)
        return manageVoteOp_;
      throw xdr::xdr_wrong_union("_body_t: manageVoteOp accessed when not selected");
    }
    const ManageVoteOp &manageVoteOp() const {
      if (_xdr_field_number(type_) == 39)
        return manageVoteOp_;
      throw xdr::xdr_wrong_union("_body_t: manageVoteOp accessed when not selected");
    }
    ManageAccountSpecificRuleOp &manageAccountSpecificRuleOp() {
      if (_xdr_field_number(type_) == 40)
        return manageAccountSpecificRuleOp_;
      throw xdr::xdr_wrong_union("_body_t: manageAccountSpecificRuleOp accessed when not selected");
    }
    const ManageAccountSpecificRuleOp &manageAccountSpecificRuleOp() const {
      if (_xdr_field_number(type_) == 40)
        return manageAccountSpecificRuleOp_;
      throw xdr::xdr_wrong_union("_body_t: manageAccountSpecificRuleOp accessed when not selected");
    }
    CancelChangeRoleRequestOp &cancelChangeRoleRequestOp() {
      if (_xdr_field_number(type_) == 41)
        return cancelChangeRoleRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: cancelChangeRoleRequestOp accessed when not selected");
    }
    const CancelChangeRoleRequestOp &cancelChangeRoleRequestOp() const {
      if (_xdr_field_number(type_) == 41)
        return cancelChangeRoleRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: cancelChangeRoleRequestOp accessed when not selected");
    }
    RemoveAssetPairOp &removeAssetPairOp() {
      if (_xdr_field_number(type_) == 42)
        return removeAssetPairOp_;
      throw xdr::xdr_wrong_union("_body_t: removeAssetPairOp accessed when not selected");
    }
    const RemoveAssetPairOp &removeAssetPairOp() const {
      if (_xdr_field_number(type_) == 42)
        return removeAssetPairOp_;
      throw xdr::xdr_wrong_union("_body_t: removeAssetPairOp accessed when not selected");
    }
    InitiateKYCRecoveryOp &initiateKYCRecoveryOp() {
      if (_xdr_field_number(type_) == 43)
        return initiateKYCRecoveryOp_;
      throw xdr::xdr_wrong_union("_body_t: initiateKYCRecoveryOp accessed when not selected");
    }
    const InitiateKYCRecoveryOp &initiateKYCRecoveryOp() const {
      if (_xdr_field_number(type_) == 43)
        return initiateKYCRecoveryOp_;
      throw xdr::xdr_wrong_union("_body_t: initiateKYCRecoveryOp accessed when not selected");
    }
    CreateKYCRecoveryRequestOp &createKYCRecoveryRequestOp() {
      if (_xdr_field_number(type_) == 44)
        return createKYCRecoveryRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: createKYCRecoveryRequestOp accessed when not selected");
    }
    const CreateKYCRecoveryRequestOp &createKYCRecoveryRequestOp() const {
      if (_xdr_field_number(type_) == 44)
        return createKYCRecoveryRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: createKYCRecoveryRequestOp accessed when not selected");
    }
    CreateManageOfferRequestOp &createManageOfferRequestOp() {
      if (_xdr_field_number(type_) == 45)
        return createManageOfferRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: createManageOfferRequestOp accessed when not selected");
    }
    const CreateManageOfferRequestOp &createManageOfferRequestOp() const {
      if (_xdr_field_number(type_) == 45)
        return createManageOfferRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: createManageOfferRequestOp accessed when not selected");
    }
    CreatePaymentRequestOp &createPaymentRequestOp() {
      if (_xdr_field_number(type_) == 46)
        return createPaymentRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: createPaymentRequestOp accessed when not selected");
    }
    const CreatePaymentRequestOp &createPaymentRequestOp() const {
      if (_xdr_field_number(type_) == 46)
        return createPaymentRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: createPaymentRequestOp accessed when not selected");
    }
    RemoveAssetOp &removeAssetOp() {
      if (_xdr_field_number(type_) == 47)
        return removeAssetOp_;
      throw xdr::xdr_wrong_union("_body_t: removeAssetOp accessed when not selected");
    }
    const RemoveAssetOp &removeAssetOp() const {
      if (_xdr_field_number(type_) == 47)
        return removeAssetOp_;
      throw xdr::xdr_wrong_union("_body_t: removeAssetOp accessed when not selected");
    }
    OpenSwapOp &openSwapOp() {
      if (_xdr_field_number(type_) == 48)
        return openSwapOp_;
      throw xdr::xdr_wrong_union("_body_t: openSwapOp accessed when not selected");
    }
    const OpenSwapOp &openSwapOp() const {
      if (_xdr_field_number(type_) == 48)
        return openSwapOp_;
      throw xdr::xdr_wrong_union("_body_t: openSwapOp accessed when not selected");
    }
    CloseSwapOp &closeSwapOp() {
      if (_xdr_field_number(type_) == 49)
        return closeSwapOp_;
      throw xdr::xdr_wrong_union("_body_t: closeSwapOp accessed when not selected");
    }
    const CloseSwapOp &closeSwapOp() const {
      if (_xdr_field_number(type_) == 49)
        return closeSwapOp_;
      throw xdr::xdr_wrong_union("_body_t: closeSwapOp accessed when not selected");
    }
    CreateRedemptionRequestOp &createRedemptionRequestOp() {
      if (_xdr_field_number(type_) == 50)
        return createRedemptionRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: createRedemptionRequestOp accessed when not selected");
    }
    const CreateRedemptionRequestOp &createRedemptionRequestOp() const {
      if (_xdr_field_number(type_) == 50)
        return createRedemptionRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: createRedemptionRequestOp accessed when not selected");
    }
    CreateDataOp &createDataOp() {
      if (_xdr_field_number(type_) == 51)
        return createDataOp_;
      throw xdr::xdr_wrong_union("_body_t: createDataOp accessed when not selected");
    }
    const CreateDataOp &createDataOp() const {
      if (_xdr_field_number(type_) == 51)
        return createDataOp_;
      throw xdr::xdr_wrong_union("_body_t: createDataOp accessed when not selected");
    }
    UpdateDataOp &updateDataOp() {
      if (_xdr_field_number(type_) == 52)
        return updateDataOp_;
      throw xdr::xdr_wrong_union("_body_t: updateDataOp accessed when not selected");
    }
    const UpdateDataOp &updateDataOp() const {
      if (_xdr_field_number(type_) == 52)
        return updateDataOp_;
      throw xdr::xdr_wrong_union("_body_t: updateDataOp accessed when not selected");
    }
    RemoveDataOp &removeDataOp() {
      if (_xdr_field_number(type_) == 53)
        return removeDataOp_;
      throw xdr::xdr_wrong_union("_body_t: removeDataOp accessed when not selected");
    }
    const RemoveDataOp &removeDataOp() const {
      if (_xdr_field_number(type_) == 53)
        return removeDataOp_;
      throw xdr::xdr_wrong_union("_body_t: removeDataOp accessed when not selected");
    }
    CreateDataCreationRequestOp &createDataCreationRequestOp() {
      if (_xdr_field_number(type_) == 54)
        return createDataCreationRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: createDataCreationRequestOp accessed when not selected");
    }
    const CreateDataCreationRequestOp &createDataCreationRequestOp() const {
      if (_xdr_field_number(type_) == 54)
        return createDataCreationRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: createDataCreationRequestOp accessed when not selected");
    }
    CancelDataCreationRequestOp &cancelDataCreationRequestOp() {
      if (_xdr_field_number(type_) == 55)
        return cancelDataCreationRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: cancelDataCreationRequestOp accessed when not selected");
    }
    const CancelDataCreationRequestOp &cancelDataCreationRequestOp() const {
      if (_xdr_field_number(type_) == 55)
        return cancelDataCreationRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: cancelDataCreationRequestOp accessed when not selected");
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

  xdr::pointer<AccountID> sourceAccount{};
  _body_t body{};

  Operation() = default;
  template<typename _sourceAccount_T,
           typename _body_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::pointer<AccountID>, _sourceAccount_T>::value
                          && std::is_constructible<_body_t, _body_T>::value
                         >::type>
  explicit Operation(_sourceAccount_T &&_sourceAccount,
                     _body_T &&_body)
    : sourceAccount(std::forward<_sourceAccount_T>(_sourceAccount)),
      body(std::forward<_body_T>(_body)) {}
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

enum class MemoType : std::int32_t {
  MEMO_NONE = 0,
  MEMO_TEXT = 1,
  MEMO_ID = 2,
  MEMO_HASH = 3,
  MEMO_RETURN = 4,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::MemoType>
  : xdr_integral_base<::stellar::MemoType, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::MemoType val) {
    switch (val) {
    case ::stellar::MemoType::MEMO_NONE:
      return "MEMO_NONE";
    case ::stellar::MemoType::MEMO_TEXT:
      return "MEMO_TEXT";
    case ::stellar::MemoType::MEMO_ID:
      return "MEMO_ID";
    case ::stellar::MemoType::MEMO_HASH:
      return "MEMO_HASH";
    case ::stellar::MemoType::MEMO_RETURN:
      return "MEMO_RETURN";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::MemoType::MEMO_NONE,
      (int32_t)::stellar::MemoType::MEMO_TEXT,
      (int32_t)::stellar::MemoType::MEMO_ID,
      (int32_t)::stellar::MemoType::MEMO_HASH,
      (int32_t)::stellar::MemoType::MEMO_RETURN
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct Memo : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<MemoType>::case_type;
private:
  _xdr_case_type type_;
  union {
    xdr::xstring<28> text_;
    uint64 id_;
    Hash hash_;
    Hash retHash_;
  };

public:
  static constexpr const bool _xdr_has_default_case = false;
  static const std::vector<MemoType> &_xdr_case_values() {
    static const std::vector<MemoType> _xdr_disc_vec {
      MemoType::MEMO_NONE,
      MemoType::MEMO_TEXT,
      MemoType::MEMO_ID,
      MemoType::MEMO_HASH,
      MemoType::MEMO_RETURN
    };
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)MemoType::MEMO_NONE ? 0
      : which == (int32_t)MemoType::MEMO_TEXT ? 1
      : which == (int32_t)MemoType::MEMO_ID ? 2
      : which == (int32_t)MemoType::MEMO_HASH ? 3
      : which == (int32_t)MemoType::MEMO_RETURN ? 4
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)MemoType::MEMO_NONE:
      return true;
    case (int32_t)MemoType::MEMO_TEXT:
      _f(&Memo::text_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)MemoType::MEMO_ID:
      _f(&Memo::id_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)MemoType::MEMO_HASH:
      _f(&Memo::hash_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)MemoType::MEMO_RETURN:
      _f(&Memo::retHash_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return type_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of type in Memo");
    if (fnum != _xdr_field_number(type_)) {
      this->~Memo();
      type_ = which;switch (type_)
{
      case (int32_t)MemoType::MEMO_NONE:
        break;
      case (int32_t)MemoType::MEMO_TEXT:
new(&text_) xdr::xstring<28>{};
break;
      case (int32_t)MemoType::MEMO_ID:
new(&id_) uint64{};
break;
      case (int32_t)MemoType::MEMO_HASH:
new(&hash_) Hash{};
break;
      case (int32_t)MemoType::MEMO_RETURN:
new(&retHash_) Hash{};
break;
}

    }
    else
      type_ = which;
  }
  explicit Memo(MemoType which = MemoType{}) : type_((int32_t)which) {
    switch (type_)
{
    case (int32_t)MemoType::MEMO_NONE:
      break;
    case (int32_t)MemoType::MEMO_TEXT:
new(&text_) xdr::xstring<28>{};
break;
    case (int32_t)MemoType::MEMO_ID:
new(&id_) uint64{};
break;
    case (int32_t)MemoType::MEMO_HASH:
new(&hash_) Hash{};
break;
    case (int32_t)MemoType::MEMO_RETURN:
new(&retHash_) Hash{};
break;
}

  }
  Memo(const Memo &source) : type_(source.type_) {
    switch (type_)
{
    case (int32_t)MemoType::MEMO_NONE:
      break;
    case (int32_t)MemoType::MEMO_TEXT:
new(&text_) xdr::xstring<28>(source.text_);
break;
    case (int32_t)MemoType::MEMO_ID:
new(&id_) uint64(source.id_);
break;
    case (int32_t)MemoType::MEMO_HASH:
new(&hash_) Hash(source.hash_);
break;
    case (int32_t)MemoType::MEMO_RETURN:
new(&retHash_) Hash(source.retHash_);
break;
}

  }
  Memo(Memo &&source) : type_(source.type_) {
    switch (type_)
{
    case (int32_t)MemoType::MEMO_NONE:
      break;
    case (int32_t)MemoType::MEMO_TEXT:
new(&text_) xdr::xstring<28>(std::move(source.text_));
break;
    case (int32_t)MemoType::MEMO_ID:
new(&id_) uint64(std::move(source.id_));
break;
    case (int32_t)MemoType::MEMO_HASH:
new(&hash_) Hash(std::move(source.hash_));
break;
    case (int32_t)MemoType::MEMO_RETURN:
new(&retHash_) Hash(std::move(source.retHash_));
break;
}

  }
  ~Memo() {
switch (type_)
{
  case (int32_t)MemoType::MEMO_NONE:
    break;
  case (int32_t)MemoType::MEMO_TEXT:
text_.~xstring<28>();
break;
  case (int32_t)MemoType::MEMO_ID:
id_.~uint64();
break;
  case (int32_t)MemoType::MEMO_HASH:
hash_.~Hash();
break;
  case (int32_t)MemoType::MEMO_RETURN:
retHash_.~Hash();
break;
}
}

  Memo &operator=(const Memo &source) {
    if (type_ == source.type_)
{
switch (type_)
{
    case (int32_t)MemoType::MEMO_NONE:
      break;
    case (int32_t)MemoType::MEMO_TEXT:
text_ = source.text_;
break;
    case (int32_t)MemoType::MEMO_ID:
id_ = source.id_;
break;
    case (int32_t)MemoType::MEMO_HASH:
hash_ = source.hash_;
break;
    case (int32_t)MemoType::MEMO_RETURN:
retHash_ = source.retHash_;
break;
}
}
else {this->~Memo();
    type_ = source.type_;
switch (type_)
{
    case (int32_t)MemoType::MEMO_NONE:
      break;
    case (int32_t)MemoType::MEMO_TEXT:
new(&text_) xdr::xstring<28>(source.text_);
break;
    case (int32_t)MemoType::MEMO_ID:
new(&id_) uint64(source.id_);
break;
    case (int32_t)MemoType::MEMO_HASH:
new(&hash_) Hash(source.hash_);
break;
    case (int32_t)MemoType::MEMO_RETURN:
new(&retHash_) Hash(source.retHash_);
break;
}
}
    return *this;
  }
  Memo &operator=(Memo &&source) {
    if (type_ == source.type_)
{
switch (type_)
{
    case (int32_t)MemoType::MEMO_NONE:
      break;
    case (int32_t)MemoType::MEMO_TEXT:
text_ = std::move(source.text_);
break;
    case (int32_t)MemoType::MEMO_ID:
id_ = std::move(source.id_);
break;
    case (int32_t)MemoType::MEMO_HASH:
hash_ = std::move(source.hash_);
break;
    case (int32_t)MemoType::MEMO_RETURN:
retHash_ = std::move(source.retHash_);
break;
}
}
else {this->~Memo();
    type_ = std::move(source.type_);
switch (type_)
{
    case (int32_t)MemoType::MEMO_NONE:
      break;
    case (int32_t)MemoType::MEMO_TEXT:
new(&text_) xdr::xstring<28>(std::move(source.text_));
break;
    case (int32_t)MemoType::MEMO_ID:
new(&id_) uint64(std::move(source.id_));
break;
    case (int32_t)MemoType::MEMO_HASH:
new(&hash_) Hash(std::move(source.hash_));
break;
    case (int32_t)MemoType::MEMO_RETURN:
new(&retHash_) Hash(std::move(source.retHash_));
break;
}
}
    return *this;
  }

  MemoType type() const { return MemoType(type_); }
  Memo &type(MemoType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  xdr::xstring<28> &text() {
    if (_xdr_field_number(type_) == 1)
      return text_;
    throw xdr::xdr_wrong_union("Memo: text accessed when not selected");
  }
  const xdr::xstring<28> &text() const {
    if (_xdr_field_number(type_) == 1)
      return text_;
    throw xdr::xdr_wrong_union("Memo: text accessed when not selected");
  }
  uint64 &id() {
    if (_xdr_field_number(type_) == 2)
      return id_;
    throw xdr::xdr_wrong_union("Memo: id accessed when not selected");
  }
  const uint64 &id() const {
    if (_xdr_field_number(type_) == 2)
      return id_;
    throw xdr::xdr_wrong_union("Memo: id accessed when not selected");
  }
  Hash &hash() {
    if (_xdr_field_number(type_) == 3)
      return hash_;
    throw xdr::xdr_wrong_union("Memo: hash accessed when not selected");
  }
  const Hash &hash() const {
    if (_xdr_field_number(type_) == 3)
      return hash_;
    throw xdr::xdr_wrong_union("Memo: hash accessed when not selected");
  }
  Hash &retHash() {
    if (_xdr_field_number(type_) == 4)
      return retHash_;
    throw xdr::xdr_wrong_union("Memo: retHash accessed when not selected");
  }
  const Hash &retHash() const {
    if (_xdr_field_number(type_) == 4)
      return retHash_;
    throw xdr::xdr_wrong_union("Memo: retHash accessed when not selected");
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

struct TimeBounds  : xdr::xdr_abstract {
  uint64 minTime{};
  uint64 maxTime{};

  TimeBounds() = default;
  template<typename _minTime_T,
           typename _maxTime_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _minTime_T>::value
                          && std::is_constructible<uint64, _maxTime_T>::value
                         >::type>
  explicit TimeBounds(_minTime_T &&_minTime,
                      _maxTime_T &&_maxTime)
    : minTime(std::forward<_minTime_T>(_minTime)),
      maxTime(std::forward<_maxTime_T>(_maxTime)) {}
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

struct Transaction  : xdr::xdr_abstract {
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

  AccountID sourceAccount{};
  Salt salt{};
  TimeBounds timeBounds{};
  Memo memo{};
  xdr::xvector<Operation,100> operations{};
  _ext_t ext{};

  Transaction() = default;
  template<typename _sourceAccount_T,
           typename _salt_T,
           typename _timeBounds_T,
           typename _memo_T,
           typename _operations_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<AccountID, _sourceAccount_T>::value
                          && std::is_constructible<Salt, _salt_T>::value
                          && std::is_constructible<TimeBounds, _timeBounds_T>::value
                          && std::is_constructible<Memo, _memo_T>::value
                          && std::is_constructible<xdr::xvector<Operation,100>, _operations_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit Transaction(_sourceAccount_T &&_sourceAccount,
                       _salt_T &&_salt,
                       _timeBounds_T &&_timeBounds,
                       _memo_T &&_memo,
                       _operations_T &&_operations,
                       _ext_T &&_ext)
    : sourceAccount(std::forward<_sourceAccount_T>(_sourceAccount)),
      salt(std::forward<_salt_T>(_salt)),
      timeBounds(std::forward<_timeBounds_T>(_timeBounds)),
      memo(std::forward<_memo_T>(_memo)),
      operations(std::forward<_operations_T>(_operations)),
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

struct TransactionEnvelope  : xdr::xdr_abstract {
  Transaction tx{};
  xdr::xvector<DecoratedSignature,20> signatures{};

  TransactionEnvelope() = default;
  template<typename _tx_T,
           typename _signatures_T,
           typename = typename
           std::enable_if<std::is_constructible<Transaction, _tx_T>::value
                          && std::is_constructible<xdr::xvector<DecoratedSignature,20>, _signatures_T>::value
                         >::type>
  explicit TransactionEnvelope(_tx_T &&_tx,
                               _signatures_T &&_signatures)
    : tx(std::forward<_tx_T>(_tx)),
      signatures(std::forward<_signatures_T>(_signatures)) {}
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

enum class OperationResultCode : std::int32_t {
  opINNER = 0,
  opBAD_AUTH = -1,
  opNO_ACCOUNT = -2,
  opNOT_ALLOWED = -3,
  opACCOUNT_BLOCKED = -4,
  opNO_COUNTERPARTY = -5,
  opCOUNTERPARTY_BLOCKED = -6,
  opCOUNTERPARTY_WRONG_TYPE = -7,
  opBAD_AUTH_EXTRA = -8,
  opNO_ROLE_PERMISSION = -9,
  opNO_ENTRY = -10,
  opNOT_SUPPORTED = -11,
  opLICENSE_VIOLATION = -12,
  opSKIPPED = -13,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::OperationResultCode>
  : xdr_integral_base<::stellar::OperationResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::OperationResultCode val) {
    switch (val) {
    case ::stellar::OperationResultCode::opINNER:
      return "opINNER";
    case ::stellar::OperationResultCode::opBAD_AUTH:
      return "opBAD_AUTH";
    case ::stellar::OperationResultCode::opNO_ACCOUNT:
      return "opNO_ACCOUNT";
    case ::stellar::OperationResultCode::opNOT_ALLOWED:
      return "opNOT_ALLOWED";
    case ::stellar::OperationResultCode::opACCOUNT_BLOCKED:
      return "opACCOUNT_BLOCKED";
    case ::stellar::OperationResultCode::opNO_COUNTERPARTY:
      return "opNO_COUNTERPARTY";
    case ::stellar::OperationResultCode::opCOUNTERPARTY_BLOCKED:
      return "opCOUNTERPARTY_BLOCKED";
    case ::stellar::OperationResultCode::opCOUNTERPARTY_WRONG_TYPE:
      return "opCOUNTERPARTY_WRONG_TYPE";
    case ::stellar::OperationResultCode::opBAD_AUTH_EXTRA:
      return "opBAD_AUTH_EXTRA";
    case ::stellar::OperationResultCode::opNO_ROLE_PERMISSION:
      return "opNO_ROLE_PERMISSION";
    case ::stellar::OperationResultCode::opNO_ENTRY:
      return "opNO_ENTRY";
    case ::stellar::OperationResultCode::opNOT_SUPPORTED:
      return "opNOT_SUPPORTED";
    case ::stellar::OperationResultCode::opLICENSE_VIOLATION:
      return "opLICENSE_VIOLATION";
    case ::stellar::OperationResultCode::opSKIPPED:
      return "opSKIPPED";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::OperationResultCode::opINNER,
      (int32_t)::stellar::OperationResultCode::opBAD_AUTH,
      (int32_t)::stellar::OperationResultCode::opNO_ACCOUNT,
      (int32_t)::stellar::OperationResultCode::opNOT_ALLOWED,
      (int32_t)::stellar::OperationResultCode::opACCOUNT_BLOCKED,
      (int32_t)::stellar::OperationResultCode::opNO_COUNTERPARTY,
      (int32_t)::stellar::OperationResultCode::opCOUNTERPARTY_BLOCKED,
      (int32_t)::stellar::OperationResultCode::opCOUNTERPARTY_WRONG_TYPE,
      (int32_t)::stellar::OperationResultCode::opBAD_AUTH_EXTRA,
      (int32_t)::stellar::OperationResultCode::opNO_ROLE_PERMISSION,
      (int32_t)::stellar::OperationResultCode::opNO_ENTRY,
      (int32_t)::stellar::OperationResultCode::opNOT_SUPPORTED,
      (int32_t)::stellar::OperationResultCode::opLICENSE_VIOLATION,
      (int32_t)::stellar::OperationResultCode::opSKIPPED
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct AccountRuleRequirement  : xdr::xdr_abstract {
  AccountRuleResource resource{};
  AccountRuleAction action{};
  AccountID account{};
  EmptyExt ext{};

  AccountRuleRequirement() = default;
  template<typename _resource_T,
           typename _action_T,
           typename _account_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<AccountRuleResource, _resource_T>::value
                          && std::is_constructible<AccountRuleAction, _action_T>::value
                          && std::is_constructible<AccountID, _account_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit AccountRuleRequirement(_resource_T &&_resource,
                                  _action_T &&_action,
                                  _account_T &&_account,
                                  _ext_T &&_ext)
    : resource(std::forward<_resource_T>(_resource)),
      action(std::forward<_action_T>(_action)),
      account(std::forward<_account_T>(_account)),
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

struct OperationResult : xdr::xdr_abstract {
  struct _tr_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<OperationType>::case_type;
  private:
    _xdr_case_type type_;
    union {
      CreateAccountResult createAccountResult_;
      CreateIssuanceRequestResult createIssuanceRequestResult_;
      SetFeesResult setFeesResult_;
      CreateWithdrawalRequestResult createWithdrawalRequestResult_;
      ManageBalanceResult manageBalanceResult_;
      ManageAssetResult manageAssetResult_;
      CreatePreIssuanceRequestResult createPreIssuanceRequestResult_;
      ManageLimitsResult manageLimitsResult_;
      ManageAssetPairResult manageAssetPairResult_;
      ManageOfferResult manageOfferResult_;
      ManageInvoiceRequestResult manageInvoiceRequestResult_;
      ReviewRequestResult reviewRequestResult_;
      CreateSaleCreationRequestResult createSaleCreationRequestResult_;
      CheckSaleStateResult checkSaleStateResult_;
      PayoutResult payoutResult_;
      CreateAMLAlertRequestResult createAMLAlertRequestResult_;
      ManageKeyValueResult manageKeyValueResult_;
      CreateChangeRoleRequestResult createChangeRoleRequestResult_;
      ManageExternalSystemAccountIdPoolEntryResult manageExternalSystemAccountIdPoolEntryResult_;
      BindExternalSystemAccountIdResult bindExternalSystemAccountIdResult_;
      PaymentResult paymentResult_;
      ManageSaleResult manageSaleResult_;
      CreateManageLimitsRequestResult createManageLimitsRequestResult_;
      ManageContractRequestResult manageContractRequestResult_;
      ManageContractResult manageContractResult_;
      CancelSaleCreationRequestResult cancelSaleCreationRequestResult_;
      CreateAtomicSwapAskRequestResult createAtomicSwapAskRequestResult_;
      CancelAtomicSwapAskResult cancelAtomicSwapAskResult_;
      CreateAtomicSwapBidRequestResult createAtomicSwapBidRequestResult_;
      ManageAccountRoleResult manageAccountRoleResult_;
      ManageAccountRuleResult manageAccountRuleResult_;
      ManageSignerResult manageSignerResult_;
      ManageSignerRoleResult manageSignerRoleResult_;
      ManageSignerRuleResult manageSignerRuleResult_;
      StampResult stampResult_;
      LicenseResult licenseResult_;
      ManagePollResult managePollResult_;
      ManageCreatePollRequestResult manageCreatePollRequestResult_;
      ManageVoteResult manageVoteResult_;
      ManageAccountSpecificRuleResult manageAccountSpecificRuleResult_;
      CancelChangeRoleRequestResult cancelChangeRoleRequestResult_;
      RemoveAssetPairResult removeAssetPairResult_;
      CreateKYCRecoveryRequestResult createKYCRecoveryRequestResult_;
      InitiateKYCRecoveryResult initiateKYCRecoveryResult_;
      CreateManageOfferRequestResult createManageOfferRequestResult_;
      CreatePaymentRequestResult createPaymentRequestResult_;
      RemoveAssetResult removeAssetResult_;
      OpenSwapResult openSwapResult_;
      CloseSwapResult closeSwapResult_;
      CreateRedemptionRequestResult createRedemptionRequestResult_;
      CreateDataResult createDataResult_;
      UpdateDataResult updateDataResult_;
      RemoveDataResult removeDataResult_;
      CreateDataRequestResult createDataRequestResult_;
      CreateDataCreationRequestResult CreateDataCreationRequestResult_;
      CancelDataCreationRequestResult CancelDataCreationRequestResult_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<OperationType> &_xdr_case_values() {
      static const std::vector<OperationType> _xdr_disc_vec {
        OperationType::CREATE_ACCOUNT,
        OperationType::CREATE_ISSUANCE_REQUEST,
        OperationType::SET_FEES,
        OperationType::CREATE_WITHDRAWAL_REQUEST,
        OperationType::MANAGE_BALANCE,
        OperationType::MANAGE_ASSET,
        OperationType::CREATE_PREISSUANCE_REQUEST,
        OperationType::MANAGE_LIMITS,
        OperationType::MANAGE_ASSET_PAIR,
        OperationType::MANAGE_OFFER,
        OperationType::MANAGE_INVOICE_REQUEST,
        OperationType::REVIEW_REQUEST,
        OperationType::CREATE_SALE_REQUEST,
        OperationType::CHECK_SALE_STATE,
        OperationType::PAYOUT,
        OperationType::CREATE_AML_ALERT,
        OperationType::MANAGE_KEY_VALUE,
        OperationType::CREATE_CHANGE_ROLE_REQUEST,
        OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY,
        OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID,
        OperationType::PAYMENT,
        OperationType::MANAGE_SALE,
        OperationType::CREATE_MANAGE_LIMITS_REQUEST,
        OperationType::MANAGE_CONTRACT_REQUEST,
        OperationType::MANAGE_CONTRACT,
        OperationType::CANCEL_SALE_REQUEST,
        OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST,
        OperationType::CANCEL_ATOMIC_SWAP_ASK,
        OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST,
        OperationType::MANAGE_ACCOUNT_ROLE,
        OperationType::MANAGE_ACCOUNT_RULE,
        OperationType::MANAGE_SIGNER,
        OperationType::MANAGE_SIGNER_ROLE,
        OperationType::MANAGE_SIGNER_RULE,
        OperationType::STAMP,
        OperationType::LICENSE,
        OperationType::MANAGE_POLL,
        OperationType::MANAGE_CREATE_POLL_REQUEST,
        OperationType::MANAGE_VOTE,
        OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE,
        OperationType::CANCEL_CHANGE_ROLE_REQUEST,
        OperationType::REMOVE_ASSET_PAIR,
        OperationType::CREATE_KYC_RECOVERY_REQUEST,
        OperationType::INITIATE_KYC_RECOVERY,
        OperationType::CREATE_MANAGE_OFFER_REQUEST,
        OperationType::CREATE_PAYMENT_REQUEST,
        OperationType::REMOVE_ASSET,
        OperationType::OPEN_SWAP,
        OperationType::CLOSE_SWAP,
        OperationType::CREATE_REDEMPTION_REQUEST,
        OperationType::CREATE_DATA,
        OperationType::UPDATE_DATA,
        OperationType::REMOVE_DATA,
        OperationType::CREATE_DATA_REQUEST,
        OperationType::CREATE_DATA_CREATION_REQUEST,
        OperationType::CANCEL_DATA_CREATION_REQUEST
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)OperationType::CREATE_ACCOUNT ? 1
        : which == (int32_t)OperationType::CREATE_ISSUANCE_REQUEST ? 2
        : which == (int32_t)OperationType::SET_FEES ? 3
        : which == (int32_t)OperationType::CREATE_WITHDRAWAL_REQUEST ? 4
        : which == (int32_t)OperationType::MANAGE_BALANCE ? 5
        : which == (int32_t)OperationType::MANAGE_ASSET ? 6
        : which == (int32_t)OperationType::CREATE_PREISSUANCE_REQUEST ? 7
        : which == (int32_t)OperationType::MANAGE_LIMITS ? 8
        : which == (int32_t)OperationType::MANAGE_ASSET_PAIR ? 9
        : which == (int32_t)OperationType::MANAGE_OFFER ? 10
        : which == (int32_t)OperationType::MANAGE_INVOICE_REQUEST ? 11
        : which == (int32_t)OperationType::REVIEW_REQUEST ? 12
        : which == (int32_t)OperationType::CREATE_SALE_REQUEST ? 13
        : which == (int32_t)OperationType::CHECK_SALE_STATE ? 14
        : which == (int32_t)OperationType::PAYOUT ? 15
        : which == (int32_t)OperationType::CREATE_AML_ALERT ? 16
        : which == (int32_t)OperationType::MANAGE_KEY_VALUE ? 17
        : which == (int32_t)OperationType::CREATE_CHANGE_ROLE_REQUEST ? 18
        : which == (int32_t)OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY ? 19
        : which == (int32_t)OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID ? 20
        : which == (int32_t)OperationType::PAYMENT ? 21
        : which == (int32_t)OperationType::MANAGE_SALE ? 22
        : which == (int32_t)OperationType::CREATE_MANAGE_LIMITS_REQUEST ? 23
        : which == (int32_t)OperationType::MANAGE_CONTRACT_REQUEST ? 24
        : which == (int32_t)OperationType::MANAGE_CONTRACT ? 25
        : which == (int32_t)OperationType::CANCEL_SALE_REQUEST ? 26
        : which == (int32_t)OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST ? 27
        : which == (int32_t)OperationType::CANCEL_ATOMIC_SWAP_ASK ? 28
        : which == (int32_t)OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST ? 29
        : which == (int32_t)OperationType::MANAGE_ACCOUNT_ROLE ? 30
        : which == (int32_t)OperationType::MANAGE_ACCOUNT_RULE ? 31
        : which == (int32_t)OperationType::MANAGE_SIGNER ? 32
        : which == (int32_t)OperationType::MANAGE_SIGNER_ROLE ? 33
        : which == (int32_t)OperationType::MANAGE_SIGNER_RULE ? 34
        : which == (int32_t)OperationType::STAMP ? 35
        : which == (int32_t)OperationType::LICENSE ? 36
        : which == (int32_t)OperationType::MANAGE_POLL ? 37
        : which == (int32_t)OperationType::MANAGE_CREATE_POLL_REQUEST ? 38
        : which == (int32_t)OperationType::MANAGE_VOTE ? 39
        : which == (int32_t)OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE ? 40
        : which == (int32_t)OperationType::CANCEL_CHANGE_ROLE_REQUEST ? 41
        : which == (int32_t)OperationType::REMOVE_ASSET_PAIR ? 42
        : which == (int32_t)OperationType::CREATE_KYC_RECOVERY_REQUEST ? 43
        : which == (int32_t)OperationType::INITIATE_KYC_RECOVERY ? 44
        : which == (int32_t)OperationType::CREATE_MANAGE_OFFER_REQUEST ? 45
        : which == (int32_t)OperationType::CREATE_PAYMENT_REQUEST ? 46
        : which == (int32_t)OperationType::REMOVE_ASSET ? 47
        : which == (int32_t)OperationType::OPEN_SWAP ? 48
        : which == (int32_t)OperationType::CLOSE_SWAP ? 49
        : which == (int32_t)OperationType::CREATE_REDEMPTION_REQUEST ? 50
        : which == (int32_t)OperationType::CREATE_DATA ? 51
        : which == (int32_t)OperationType::UPDATE_DATA ? 52
        : which == (int32_t)OperationType::REMOVE_DATA ? 53
        : which == (int32_t)OperationType::CREATE_DATA_REQUEST ? 54
        : which == (int32_t)OperationType::CREATE_DATA_CREATION_REQUEST ? 55
        : which == (int32_t)OperationType::CANCEL_DATA_CREATION_REQUEST ? 56
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)OperationType::CREATE_ACCOUNT:
        _f(&_tr_t::createAccountResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CREATE_ISSUANCE_REQUEST:
        _f(&_tr_t::createIssuanceRequestResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::SET_FEES:
        _f(&_tr_t::setFeesResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CREATE_WITHDRAWAL_REQUEST:
        _f(&_tr_t::createWithdrawalRequestResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_BALANCE:
        _f(&_tr_t::manageBalanceResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_ASSET:
        _f(&_tr_t::manageAssetResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CREATE_PREISSUANCE_REQUEST:
        _f(&_tr_t::createPreIssuanceRequestResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_LIMITS:
        _f(&_tr_t::manageLimitsResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_ASSET_PAIR:
        _f(&_tr_t::manageAssetPairResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_OFFER:
        _f(&_tr_t::manageOfferResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_INVOICE_REQUEST:
        _f(&_tr_t::manageInvoiceRequestResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::REVIEW_REQUEST:
        _f(&_tr_t::reviewRequestResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CREATE_SALE_REQUEST:
        _f(&_tr_t::createSaleCreationRequestResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CHECK_SALE_STATE:
        _f(&_tr_t::checkSaleStateResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::PAYOUT:
        _f(&_tr_t::payoutResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CREATE_AML_ALERT:
        _f(&_tr_t::createAMLAlertRequestResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_KEY_VALUE:
        _f(&_tr_t::manageKeyValueResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CREATE_CHANGE_ROLE_REQUEST:
        _f(&_tr_t::createChangeRoleRequestResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
        _f(&_tr_t::manageExternalSystemAccountIdPoolEntryResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID:
        _f(&_tr_t::bindExternalSystemAccountIdResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::PAYMENT:
        _f(&_tr_t::paymentResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_SALE:
        _f(&_tr_t::manageSaleResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CREATE_MANAGE_LIMITS_REQUEST:
        _f(&_tr_t::createManageLimitsRequestResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_CONTRACT_REQUEST:
        _f(&_tr_t::manageContractRequestResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_CONTRACT:
        _f(&_tr_t::manageContractResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CANCEL_SALE_REQUEST:
        _f(&_tr_t::cancelSaleCreationRequestResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST:
        _f(&_tr_t::createAtomicSwapAskRequestResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CANCEL_ATOMIC_SWAP_ASK:
        _f(&_tr_t::cancelAtomicSwapAskResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST:
        _f(&_tr_t::createAtomicSwapBidRequestResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_ACCOUNT_ROLE:
        _f(&_tr_t::manageAccountRoleResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_ACCOUNT_RULE:
        _f(&_tr_t::manageAccountRuleResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_SIGNER:
        _f(&_tr_t::manageSignerResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_SIGNER_ROLE:
        _f(&_tr_t::manageSignerRoleResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_SIGNER_RULE:
        _f(&_tr_t::manageSignerRuleResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::STAMP:
        _f(&_tr_t::stampResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::LICENSE:
        _f(&_tr_t::licenseResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_POLL:
        _f(&_tr_t::managePollResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_CREATE_POLL_REQUEST:
        _f(&_tr_t::manageCreatePollRequestResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_VOTE:
        _f(&_tr_t::manageVoteResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE:
        _f(&_tr_t::manageAccountSpecificRuleResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CANCEL_CHANGE_ROLE_REQUEST:
        _f(&_tr_t::cancelChangeRoleRequestResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::REMOVE_ASSET_PAIR:
        _f(&_tr_t::removeAssetPairResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CREATE_KYC_RECOVERY_REQUEST:
        _f(&_tr_t::createKYCRecoveryRequestResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::INITIATE_KYC_RECOVERY:
        _f(&_tr_t::initiateKYCRecoveryResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CREATE_MANAGE_OFFER_REQUEST:
        _f(&_tr_t::createManageOfferRequestResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CREATE_PAYMENT_REQUEST:
        _f(&_tr_t::createPaymentRequestResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::REMOVE_ASSET:
        _f(&_tr_t::removeAssetResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::OPEN_SWAP:
        _f(&_tr_t::openSwapResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CLOSE_SWAP:
        _f(&_tr_t::closeSwapResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CREATE_REDEMPTION_REQUEST:
        _f(&_tr_t::createRedemptionRequestResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CREATE_DATA:
        _f(&_tr_t::createDataResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::UPDATE_DATA:
        _f(&_tr_t::updateDataResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::REMOVE_DATA:
        _f(&_tr_t::removeDataResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CREATE_DATA_REQUEST:
        _f(&_tr_t::createDataRequestResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CREATE_DATA_CREATION_REQUEST:
        _f(&_tr_t::CreateDataCreationRequestResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CANCEL_DATA_CREATION_REQUEST:
        _f(&_tr_t::CancelDataCreationRequestResult_, std::forward<_A>(_a)...);
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return type_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of type in _tr_t");
      if (fnum != _xdr_field_number(type_)) {
        this->~_tr_t();
        type_ = which;switch (type_)
{
        case (int32_t)OperationType::CREATE_ACCOUNT:
new(&createAccountResult_) CreateAccountResult{};
break;
        case (int32_t)OperationType::CREATE_ISSUANCE_REQUEST:
new(&createIssuanceRequestResult_) CreateIssuanceRequestResult{};
break;
        case (int32_t)OperationType::SET_FEES:
new(&setFeesResult_) SetFeesResult{};
break;
        case (int32_t)OperationType::CREATE_WITHDRAWAL_REQUEST:
new(&createWithdrawalRequestResult_) CreateWithdrawalRequestResult{};
break;
        case (int32_t)OperationType::MANAGE_BALANCE:
new(&manageBalanceResult_) ManageBalanceResult{};
break;
        case (int32_t)OperationType::MANAGE_ASSET:
new(&manageAssetResult_) ManageAssetResult{};
break;
        case (int32_t)OperationType::CREATE_PREISSUANCE_REQUEST:
new(&createPreIssuanceRequestResult_) CreatePreIssuanceRequestResult{};
break;
        case (int32_t)OperationType::MANAGE_LIMITS:
new(&manageLimitsResult_) ManageLimitsResult{};
break;
        case (int32_t)OperationType::MANAGE_ASSET_PAIR:
new(&manageAssetPairResult_) ManageAssetPairResult{};
break;
        case (int32_t)OperationType::MANAGE_OFFER:
new(&manageOfferResult_) ManageOfferResult{};
break;
        case (int32_t)OperationType::MANAGE_INVOICE_REQUEST:
new(&manageInvoiceRequestResult_) ManageInvoiceRequestResult{};
break;
        case (int32_t)OperationType::REVIEW_REQUEST:
new(&reviewRequestResult_) ReviewRequestResult{};
break;
        case (int32_t)OperationType::CREATE_SALE_REQUEST:
new(&createSaleCreationRequestResult_) CreateSaleCreationRequestResult{};
break;
        case (int32_t)OperationType::CHECK_SALE_STATE:
new(&checkSaleStateResult_) CheckSaleStateResult{};
break;
        case (int32_t)OperationType::PAYOUT:
new(&payoutResult_) PayoutResult{};
break;
        case (int32_t)OperationType::CREATE_AML_ALERT:
new(&createAMLAlertRequestResult_) CreateAMLAlertRequestResult{};
break;
        case (int32_t)OperationType::MANAGE_KEY_VALUE:
new(&manageKeyValueResult_) ManageKeyValueResult{};
break;
        case (int32_t)OperationType::CREATE_CHANGE_ROLE_REQUEST:
new(&createChangeRoleRequestResult_) CreateChangeRoleRequestResult{};
break;
        case (int32_t)OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
new(&manageExternalSystemAccountIdPoolEntryResult_) ManageExternalSystemAccountIdPoolEntryResult{};
break;
        case (int32_t)OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID:
new(&bindExternalSystemAccountIdResult_) BindExternalSystemAccountIdResult{};
break;
        case (int32_t)OperationType::PAYMENT:
new(&paymentResult_) PaymentResult{};
break;
        case (int32_t)OperationType::MANAGE_SALE:
new(&manageSaleResult_) ManageSaleResult{};
break;
        case (int32_t)OperationType::CREATE_MANAGE_LIMITS_REQUEST:
new(&createManageLimitsRequestResult_) CreateManageLimitsRequestResult{};
break;
        case (int32_t)OperationType::MANAGE_CONTRACT_REQUEST:
new(&manageContractRequestResult_) ManageContractRequestResult{};
break;
        case (int32_t)OperationType::MANAGE_CONTRACT:
new(&manageContractResult_) ManageContractResult{};
break;
        case (int32_t)OperationType::CANCEL_SALE_REQUEST:
new(&cancelSaleCreationRequestResult_) CancelSaleCreationRequestResult{};
break;
        case (int32_t)OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST:
new(&createAtomicSwapAskRequestResult_) CreateAtomicSwapAskRequestResult{};
break;
        case (int32_t)OperationType::CANCEL_ATOMIC_SWAP_ASK:
new(&cancelAtomicSwapAskResult_) CancelAtomicSwapAskResult{};
break;
        case (int32_t)OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST:
new(&createAtomicSwapBidRequestResult_) CreateAtomicSwapBidRequestResult{};
break;
        case (int32_t)OperationType::MANAGE_ACCOUNT_ROLE:
new(&manageAccountRoleResult_) ManageAccountRoleResult{};
break;
        case (int32_t)OperationType::MANAGE_ACCOUNT_RULE:
new(&manageAccountRuleResult_) ManageAccountRuleResult{};
break;
        case (int32_t)OperationType::MANAGE_SIGNER:
new(&manageSignerResult_) ManageSignerResult{};
break;
        case (int32_t)OperationType::MANAGE_SIGNER_ROLE:
new(&manageSignerRoleResult_) ManageSignerRoleResult{};
break;
        case (int32_t)OperationType::MANAGE_SIGNER_RULE:
new(&manageSignerRuleResult_) ManageSignerRuleResult{};
break;
        case (int32_t)OperationType::STAMP:
new(&stampResult_) StampResult{};
break;
        case (int32_t)OperationType::LICENSE:
new(&licenseResult_) LicenseResult{};
break;
        case (int32_t)OperationType::MANAGE_POLL:
new(&managePollResult_) ManagePollResult{};
break;
        case (int32_t)OperationType::MANAGE_CREATE_POLL_REQUEST:
new(&manageCreatePollRequestResult_) ManageCreatePollRequestResult{};
break;
        case (int32_t)OperationType::MANAGE_VOTE:
new(&manageVoteResult_) ManageVoteResult{};
break;
        case (int32_t)OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE:
new(&manageAccountSpecificRuleResult_) ManageAccountSpecificRuleResult{};
break;
        case (int32_t)OperationType::CANCEL_CHANGE_ROLE_REQUEST:
new(&cancelChangeRoleRequestResult_) CancelChangeRoleRequestResult{};
break;
        case (int32_t)OperationType::REMOVE_ASSET_PAIR:
new(&removeAssetPairResult_) RemoveAssetPairResult{};
break;
        case (int32_t)OperationType::CREATE_KYC_RECOVERY_REQUEST:
new(&createKYCRecoveryRequestResult_) CreateKYCRecoveryRequestResult{};
break;
        case (int32_t)OperationType::INITIATE_KYC_RECOVERY:
new(&initiateKYCRecoveryResult_) InitiateKYCRecoveryResult{};
break;
        case (int32_t)OperationType::CREATE_MANAGE_OFFER_REQUEST:
new(&createManageOfferRequestResult_) CreateManageOfferRequestResult{};
break;
        case (int32_t)OperationType::CREATE_PAYMENT_REQUEST:
new(&createPaymentRequestResult_) CreatePaymentRequestResult{};
break;
        case (int32_t)OperationType::REMOVE_ASSET:
new(&removeAssetResult_) RemoveAssetResult{};
break;
        case (int32_t)OperationType::OPEN_SWAP:
new(&openSwapResult_) OpenSwapResult{};
break;
        case (int32_t)OperationType::CLOSE_SWAP:
new(&closeSwapResult_) CloseSwapResult{};
break;
        case (int32_t)OperationType::CREATE_REDEMPTION_REQUEST:
new(&createRedemptionRequestResult_) CreateRedemptionRequestResult{};
break;
        case (int32_t)OperationType::CREATE_DATA:
new(&createDataResult_) CreateDataResult{};
break;
        case (int32_t)OperationType::UPDATE_DATA:
new(&updateDataResult_) UpdateDataResult{};
break;
        case (int32_t)OperationType::REMOVE_DATA:
new(&removeDataResult_) RemoveDataResult{};
break;
        case (int32_t)OperationType::CREATE_DATA_REQUEST:
new(&createDataRequestResult_) CreateDataRequestResult{};
break;
        case (int32_t)OperationType::CREATE_DATA_CREATION_REQUEST:
new(&CreateDataCreationRequestResult_) CreateDataCreationRequestResult{};
break;
        case (int32_t)OperationType::CANCEL_DATA_CREATION_REQUEST:
new(&CancelDataCreationRequestResult_) CancelDataCreationRequestResult{};
break;
}

      }
      else
        type_ = which;
    }
    explicit _tr_t(OperationType which = OperationType{}) : type_((int32_t)which) {
      switch (type_)
{
      case (int32_t)OperationType::CREATE_ACCOUNT:
new(&createAccountResult_) CreateAccountResult{};
break;
      case (int32_t)OperationType::CREATE_ISSUANCE_REQUEST:
new(&createIssuanceRequestResult_) CreateIssuanceRequestResult{};
break;
      case (int32_t)OperationType::SET_FEES:
new(&setFeesResult_) SetFeesResult{};
break;
      case (int32_t)OperationType::CREATE_WITHDRAWAL_REQUEST:
new(&createWithdrawalRequestResult_) CreateWithdrawalRequestResult{};
break;
      case (int32_t)OperationType::MANAGE_BALANCE:
new(&manageBalanceResult_) ManageBalanceResult{};
break;
      case (int32_t)OperationType::MANAGE_ASSET:
new(&manageAssetResult_) ManageAssetResult{};
break;
      case (int32_t)OperationType::CREATE_PREISSUANCE_REQUEST:
new(&createPreIssuanceRequestResult_) CreatePreIssuanceRequestResult{};
break;
      case (int32_t)OperationType::MANAGE_LIMITS:
new(&manageLimitsResult_) ManageLimitsResult{};
break;
      case (int32_t)OperationType::MANAGE_ASSET_PAIR:
new(&manageAssetPairResult_) ManageAssetPairResult{};
break;
      case (int32_t)OperationType::MANAGE_OFFER:
new(&manageOfferResult_) ManageOfferResult{};
break;
      case (int32_t)OperationType::MANAGE_INVOICE_REQUEST:
new(&manageInvoiceRequestResult_) ManageInvoiceRequestResult{};
break;
      case (int32_t)OperationType::REVIEW_REQUEST:
new(&reviewRequestResult_) ReviewRequestResult{};
break;
      case (int32_t)OperationType::CREATE_SALE_REQUEST:
new(&createSaleCreationRequestResult_) CreateSaleCreationRequestResult{};
break;
      case (int32_t)OperationType::CHECK_SALE_STATE:
new(&checkSaleStateResult_) CheckSaleStateResult{};
break;
      case (int32_t)OperationType::PAYOUT:
new(&payoutResult_) PayoutResult{};
break;
      case (int32_t)OperationType::CREATE_AML_ALERT:
new(&createAMLAlertRequestResult_) CreateAMLAlertRequestResult{};
break;
      case (int32_t)OperationType::MANAGE_KEY_VALUE:
new(&manageKeyValueResult_) ManageKeyValueResult{};
break;
      case (int32_t)OperationType::CREATE_CHANGE_ROLE_REQUEST:
new(&createChangeRoleRequestResult_) CreateChangeRoleRequestResult{};
break;
      case (int32_t)OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
new(&manageExternalSystemAccountIdPoolEntryResult_) ManageExternalSystemAccountIdPoolEntryResult{};
break;
      case (int32_t)OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID:
new(&bindExternalSystemAccountIdResult_) BindExternalSystemAccountIdResult{};
break;
      case (int32_t)OperationType::PAYMENT:
new(&paymentResult_) PaymentResult{};
break;
      case (int32_t)OperationType::MANAGE_SALE:
new(&manageSaleResult_) ManageSaleResult{};
break;
      case (int32_t)OperationType::CREATE_MANAGE_LIMITS_REQUEST:
new(&createManageLimitsRequestResult_) CreateManageLimitsRequestResult{};
break;
      case (int32_t)OperationType::MANAGE_CONTRACT_REQUEST:
new(&manageContractRequestResult_) ManageContractRequestResult{};
break;
      case (int32_t)OperationType::MANAGE_CONTRACT:
new(&manageContractResult_) ManageContractResult{};
break;
      case (int32_t)OperationType::CANCEL_SALE_REQUEST:
new(&cancelSaleCreationRequestResult_) CancelSaleCreationRequestResult{};
break;
      case (int32_t)OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST:
new(&createAtomicSwapAskRequestResult_) CreateAtomicSwapAskRequestResult{};
break;
      case (int32_t)OperationType::CANCEL_ATOMIC_SWAP_ASK:
new(&cancelAtomicSwapAskResult_) CancelAtomicSwapAskResult{};
break;
      case (int32_t)OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST:
new(&createAtomicSwapBidRequestResult_) CreateAtomicSwapBidRequestResult{};
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_ROLE:
new(&manageAccountRoleResult_) ManageAccountRoleResult{};
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_RULE:
new(&manageAccountRuleResult_) ManageAccountRuleResult{};
break;
      case (int32_t)OperationType::MANAGE_SIGNER:
new(&manageSignerResult_) ManageSignerResult{};
break;
      case (int32_t)OperationType::MANAGE_SIGNER_ROLE:
new(&manageSignerRoleResult_) ManageSignerRoleResult{};
break;
      case (int32_t)OperationType::MANAGE_SIGNER_RULE:
new(&manageSignerRuleResult_) ManageSignerRuleResult{};
break;
      case (int32_t)OperationType::STAMP:
new(&stampResult_) StampResult{};
break;
      case (int32_t)OperationType::LICENSE:
new(&licenseResult_) LicenseResult{};
break;
      case (int32_t)OperationType::MANAGE_POLL:
new(&managePollResult_) ManagePollResult{};
break;
      case (int32_t)OperationType::MANAGE_CREATE_POLL_REQUEST:
new(&manageCreatePollRequestResult_) ManageCreatePollRequestResult{};
break;
      case (int32_t)OperationType::MANAGE_VOTE:
new(&manageVoteResult_) ManageVoteResult{};
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE:
new(&manageAccountSpecificRuleResult_) ManageAccountSpecificRuleResult{};
break;
      case (int32_t)OperationType::CANCEL_CHANGE_ROLE_REQUEST:
new(&cancelChangeRoleRequestResult_) CancelChangeRoleRequestResult{};
break;
      case (int32_t)OperationType::REMOVE_ASSET_PAIR:
new(&removeAssetPairResult_) RemoveAssetPairResult{};
break;
      case (int32_t)OperationType::CREATE_KYC_RECOVERY_REQUEST:
new(&createKYCRecoveryRequestResult_) CreateKYCRecoveryRequestResult{};
break;
      case (int32_t)OperationType::INITIATE_KYC_RECOVERY:
new(&initiateKYCRecoveryResult_) InitiateKYCRecoveryResult{};
break;
      case (int32_t)OperationType::CREATE_MANAGE_OFFER_REQUEST:
new(&createManageOfferRequestResult_) CreateManageOfferRequestResult{};
break;
      case (int32_t)OperationType::CREATE_PAYMENT_REQUEST:
new(&createPaymentRequestResult_) CreatePaymentRequestResult{};
break;
      case (int32_t)OperationType::REMOVE_ASSET:
new(&removeAssetResult_) RemoveAssetResult{};
break;
      case (int32_t)OperationType::OPEN_SWAP:
new(&openSwapResult_) OpenSwapResult{};
break;
      case (int32_t)OperationType::CLOSE_SWAP:
new(&closeSwapResult_) CloseSwapResult{};
break;
      case (int32_t)OperationType::CREATE_REDEMPTION_REQUEST:
new(&createRedemptionRequestResult_) CreateRedemptionRequestResult{};
break;
      case (int32_t)OperationType::CREATE_DATA:
new(&createDataResult_) CreateDataResult{};
break;
      case (int32_t)OperationType::UPDATE_DATA:
new(&updateDataResult_) UpdateDataResult{};
break;
      case (int32_t)OperationType::REMOVE_DATA:
new(&removeDataResult_) RemoveDataResult{};
break;
      case (int32_t)OperationType::CREATE_DATA_REQUEST:
new(&createDataRequestResult_) CreateDataRequestResult{};
break;
      case (int32_t)OperationType::CREATE_DATA_CREATION_REQUEST:
new(&CreateDataCreationRequestResult_) CreateDataCreationRequestResult{};
break;
      case (int32_t)OperationType::CANCEL_DATA_CREATION_REQUEST:
new(&CancelDataCreationRequestResult_) CancelDataCreationRequestResult{};
break;
}

    }
    _tr_t(const _tr_t &source) : type_(source.type_) {
      switch (type_)
{
      case (int32_t)OperationType::CREATE_ACCOUNT:
new(&createAccountResult_) CreateAccountResult(source.createAccountResult_);
break;
      case (int32_t)OperationType::CREATE_ISSUANCE_REQUEST:
new(&createIssuanceRequestResult_) CreateIssuanceRequestResult(source.createIssuanceRequestResult_);
break;
      case (int32_t)OperationType::SET_FEES:
new(&setFeesResult_) SetFeesResult(source.setFeesResult_);
break;
      case (int32_t)OperationType::CREATE_WITHDRAWAL_REQUEST:
new(&createWithdrawalRequestResult_) CreateWithdrawalRequestResult(source.createWithdrawalRequestResult_);
break;
      case (int32_t)OperationType::MANAGE_BALANCE:
new(&manageBalanceResult_) ManageBalanceResult(source.manageBalanceResult_);
break;
      case (int32_t)OperationType::MANAGE_ASSET:
new(&manageAssetResult_) ManageAssetResult(source.manageAssetResult_);
break;
      case (int32_t)OperationType::CREATE_PREISSUANCE_REQUEST:
new(&createPreIssuanceRequestResult_) CreatePreIssuanceRequestResult(source.createPreIssuanceRequestResult_);
break;
      case (int32_t)OperationType::MANAGE_LIMITS:
new(&manageLimitsResult_) ManageLimitsResult(source.manageLimitsResult_);
break;
      case (int32_t)OperationType::MANAGE_ASSET_PAIR:
new(&manageAssetPairResult_) ManageAssetPairResult(source.manageAssetPairResult_);
break;
      case (int32_t)OperationType::MANAGE_OFFER:
new(&manageOfferResult_) ManageOfferResult(source.manageOfferResult_);
break;
      case (int32_t)OperationType::MANAGE_INVOICE_REQUEST:
new(&manageInvoiceRequestResult_) ManageInvoiceRequestResult(source.manageInvoiceRequestResult_);
break;
      case (int32_t)OperationType::REVIEW_REQUEST:
new(&reviewRequestResult_) ReviewRequestResult(source.reviewRequestResult_);
break;
      case (int32_t)OperationType::CREATE_SALE_REQUEST:
new(&createSaleCreationRequestResult_) CreateSaleCreationRequestResult(source.createSaleCreationRequestResult_);
break;
      case (int32_t)OperationType::CHECK_SALE_STATE:
new(&checkSaleStateResult_) CheckSaleStateResult(source.checkSaleStateResult_);
break;
      case (int32_t)OperationType::PAYOUT:
new(&payoutResult_) PayoutResult(source.payoutResult_);
break;
      case (int32_t)OperationType::CREATE_AML_ALERT:
new(&createAMLAlertRequestResult_) CreateAMLAlertRequestResult(source.createAMLAlertRequestResult_);
break;
      case (int32_t)OperationType::MANAGE_KEY_VALUE:
new(&manageKeyValueResult_) ManageKeyValueResult(source.manageKeyValueResult_);
break;
      case (int32_t)OperationType::CREATE_CHANGE_ROLE_REQUEST:
new(&createChangeRoleRequestResult_) CreateChangeRoleRequestResult(source.createChangeRoleRequestResult_);
break;
      case (int32_t)OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
new(&manageExternalSystemAccountIdPoolEntryResult_) ManageExternalSystemAccountIdPoolEntryResult(source.manageExternalSystemAccountIdPoolEntryResult_);
break;
      case (int32_t)OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID:
new(&bindExternalSystemAccountIdResult_) BindExternalSystemAccountIdResult(source.bindExternalSystemAccountIdResult_);
break;
      case (int32_t)OperationType::PAYMENT:
new(&paymentResult_) PaymentResult(source.paymentResult_);
break;
      case (int32_t)OperationType::MANAGE_SALE:
new(&manageSaleResult_) ManageSaleResult(source.manageSaleResult_);
break;
      case (int32_t)OperationType::CREATE_MANAGE_LIMITS_REQUEST:
new(&createManageLimitsRequestResult_) CreateManageLimitsRequestResult(source.createManageLimitsRequestResult_);
break;
      case (int32_t)OperationType::MANAGE_CONTRACT_REQUEST:
new(&manageContractRequestResult_) ManageContractRequestResult(source.manageContractRequestResult_);
break;
      case (int32_t)OperationType::MANAGE_CONTRACT:
new(&manageContractResult_) ManageContractResult(source.manageContractResult_);
break;
      case (int32_t)OperationType::CANCEL_SALE_REQUEST:
new(&cancelSaleCreationRequestResult_) CancelSaleCreationRequestResult(source.cancelSaleCreationRequestResult_);
break;
      case (int32_t)OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST:
new(&createAtomicSwapAskRequestResult_) CreateAtomicSwapAskRequestResult(source.createAtomicSwapAskRequestResult_);
break;
      case (int32_t)OperationType::CANCEL_ATOMIC_SWAP_ASK:
new(&cancelAtomicSwapAskResult_) CancelAtomicSwapAskResult(source.cancelAtomicSwapAskResult_);
break;
      case (int32_t)OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST:
new(&createAtomicSwapBidRequestResult_) CreateAtomicSwapBidRequestResult(source.createAtomicSwapBidRequestResult_);
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_ROLE:
new(&manageAccountRoleResult_) ManageAccountRoleResult(source.manageAccountRoleResult_);
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_RULE:
new(&manageAccountRuleResult_) ManageAccountRuleResult(source.manageAccountRuleResult_);
break;
      case (int32_t)OperationType::MANAGE_SIGNER:
new(&manageSignerResult_) ManageSignerResult(source.manageSignerResult_);
break;
      case (int32_t)OperationType::MANAGE_SIGNER_ROLE:
new(&manageSignerRoleResult_) ManageSignerRoleResult(source.manageSignerRoleResult_);
break;
      case (int32_t)OperationType::MANAGE_SIGNER_RULE:
new(&manageSignerRuleResult_) ManageSignerRuleResult(source.manageSignerRuleResult_);
break;
      case (int32_t)OperationType::STAMP:
new(&stampResult_) StampResult(source.stampResult_);
break;
      case (int32_t)OperationType::LICENSE:
new(&licenseResult_) LicenseResult(source.licenseResult_);
break;
      case (int32_t)OperationType::MANAGE_POLL:
new(&managePollResult_) ManagePollResult(source.managePollResult_);
break;
      case (int32_t)OperationType::MANAGE_CREATE_POLL_REQUEST:
new(&manageCreatePollRequestResult_) ManageCreatePollRequestResult(source.manageCreatePollRequestResult_);
break;
      case (int32_t)OperationType::MANAGE_VOTE:
new(&manageVoteResult_) ManageVoteResult(source.manageVoteResult_);
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE:
new(&manageAccountSpecificRuleResult_) ManageAccountSpecificRuleResult(source.manageAccountSpecificRuleResult_);
break;
      case (int32_t)OperationType::CANCEL_CHANGE_ROLE_REQUEST:
new(&cancelChangeRoleRequestResult_) CancelChangeRoleRequestResult(source.cancelChangeRoleRequestResult_);
break;
      case (int32_t)OperationType::REMOVE_ASSET_PAIR:
new(&removeAssetPairResult_) RemoveAssetPairResult(source.removeAssetPairResult_);
break;
      case (int32_t)OperationType::CREATE_KYC_RECOVERY_REQUEST:
new(&createKYCRecoveryRequestResult_) CreateKYCRecoveryRequestResult(source.createKYCRecoveryRequestResult_);
break;
      case (int32_t)OperationType::INITIATE_KYC_RECOVERY:
new(&initiateKYCRecoveryResult_) InitiateKYCRecoveryResult(source.initiateKYCRecoveryResult_);
break;
      case (int32_t)OperationType::CREATE_MANAGE_OFFER_REQUEST:
new(&createManageOfferRequestResult_) CreateManageOfferRequestResult(source.createManageOfferRequestResult_);
break;
      case (int32_t)OperationType::CREATE_PAYMENT_REQUEST:
new(&createPaymentRequestResult_) CreatePaymentRequestResult(source.createPaymentRequestResult_);
break;
      case (int32_t)OperationType::REMOVE_ASSET:
new(&removeAssetResult_) RemoveAssetResult(source.removeAssetResult_);
break;
      case (int32_t)OperationType::OPEN_SWAP:
new(&openSwapResult_) OpenSwapResult(source.openSwapResult_);
break;
      case (int32_t)OperationType::CLOSE_SWAP:
new(&closeSwapResult_) CloseSwapResult(source.closeSwapResult_);
break;
      case (int32_t)OperationType::CREATE_REDEMPTION_REQUEST:
new(&createRedemptionRequestResult_) CreateRedemptionRequestResult(source.createRedemptionRequestResult_);
break;
      case (int32_t)OperationType::CREATE_DATA:
new(&createDataResult_) CreateDataResult(source.createDataResult_);
break;
      case (int32_t)OperationType::UPDATE_DATA:
new(&updateDataResult_) UpdateDataResult(source.updateDataResult_);
break;
      case (int32_t)OperationType::REMOVE_DATA:
new(&removeDataResult_) RemoveDataResult(source.removeDataResult_);
break;
      case (int32_t)OperationType::CREATE_DATA_REQUEST:
new(&createDataRequestResult_) CreateDataRequestResult(source.createDataRequestResult_);
break;
      case (int32_t)OperationType::CREATE_DATA_CREATION_REQUEST:
new(&CreateDataCreationRequestResult_) CreateDataCreationRequestResult(source.CreateDataCreationRequestResult_);
break;
      case (int32_t)OperationType::CANCEL_DATA_CREATION_REQUEST:
new(&CancelDataCreationRequestResult_) CancelDataCreationRequestResult(source.CancelDataCreationRequestResult_);
break;
}

    }
    _tr_t(_tr_t &&source) : type_(source.type_) {
      switch (type_)
{
      case (int32_t)OperationType::CREATE_ACCOUNT:
new(&createAccountResult_) CreateAccountResult(std::move(source.createAccountResult_));
break;
      case (int32_t)OperationType::CREATE_ISSUANCE_REQUEST:
new(&createIssuanceRequestResult_) CreateIssuanceRequestResult(std::move(source.createIssuanceRequestResult_));
break;
      case (int32_t)OperationType::SET_FEES:
new(&setFeesResult_) SetFeesResult(std::move(source.setFeesResult_));
break;
      case (int32_t)OperationType::CREATE_WITHDRAWAL_REQUEST:
new(&createWithdrawalRequestResult_) CreateWithdrawalRequestResult(std::move(source.createWithdrawalRequestResult_));
break;
      case (int32_t)OperationType::MANAGE_BALANCE:
new(&manageBalanceResult_) ManageBalanceResult(std::move(source.manageBalanceResult_));
break;
      case (int32_t)OperationType::MANAGE_ASSET:
new(&manageAssetResult_) ManageAssetResult(std::move(source.manageAssetResult_));
break;
      case (int32_t)OperationType::CREATE_PREISSUANCE_REQUEST:
new(&createPreIssuanceRequestResult_) CreatePreIssuanceRequestResult(std::move(source.createPreIssuanceRequestResult_));
break;
      case (int32_t)OperationType::MANAGE_LIMITS:
new(&manageLimitsResult_) ManageLimitsResult(std::move(source.manageLimitsResult_));
break;
      case (int32_t)OperationType::MANAGE_ASSET_PAIR:
new(&manageAssetPairResult_) ManageAssetPairResult(std::move(source.manageAssetPairResult_));
break;
      case (int32_t)OperationType::MANAGE_OFFER:
new(&manageOfferResult_) ManageOfferResult(std::move(source.manageOfferResult_));
break;
      case (int32_t)OperationType::MANAGE_INVOICE_REQUEST:
new(&manageInvoiceRequestResult_) ManageInvoiceRequestResult(std::move(source.manageInvoiceRequestResult_));
break;
      case (int32_t)OperationType::REVIEW_REQUEST:
new(&reviewRequestResult_) ReviewRequestResult(std::move(source.reviewRequestResult_));
break;
      case (int32_t)OperationType::CREATE_SALE_REQUEST:
new(&createSaleCreationRequestResult_) CreateSaleCreationRequestResult(std::move(source.createSaleCreationRequestResult_));
break;
      case (int32_t)OperationType::CHECK_SALE_STATE:
new(&checkSaleStateResult_) CheckSaleStateResult(std::move(source.checkSaleStateResult_));
break;
      case (int32_t)OperationType::PAYOUT:
new(&payoutResult_) PayoutResult(std::move(source.payoutResult_));
break;
      case (int32_t)OperationType::CREATE_AML_ALERT:
new(&createAMLAlertRequestResult_) CreateAMLAlertRequestResult(std::move(source.createAMLAlertRequestResult_));
break;
      case (int32_t)OperationType::MANAGE_KEY_VALUE:
new(&manageKeyValueResult_) ManageKeyValueResult(std::move(source.manageKeyValueResult_));
break;
      case (int32_t)OperationType::CREATE_CHANGE_ROLE_REQUEST:
new(&createChangeRoleRequestResult_) CreateChangeRoleRequestResult(std::move(source.createChangeRoleRequestResult_));
break;
      case (int32_t)OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
new(&manageExternalSystemAccountIdPoolEntryResult_) ManageExternalSystemAccountIdPoolEntryResult(std::move(source.manageExternalSystemAccountIdPoolEntryResult_));
break;
      case (int32_t)OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID:
new(&bindExternalSystemAccountIdResult_) BindExternalSystemAccountIdResult(std::move(source.bindExternalSystemAccountIdResult_));
break;
      case (int32_t)OperationType::PAYMENT:
new(&paymentResult_) PaymentResult(std::move(source.paymentResult_));
break;
      case (int32_t)OperationType::MANAGE_SALE:
new(&manageSaleResult_) ManageSaleResult(std::move(source.manageSaleResult_));
break;
      case (int32_t)OperationType::CREATE_MANAGE_LIMITS_REQUEST:
new(&createManageLimitsRequestResult_) CreateManageLimitsRequestResult(std::move(source.createManageLimitsRequestResult_));
break;
      case (int32_t)OperationType::MANAGE_CONTRACT_REQUEST:
new(&manageContractRequestResult_) ManageContractRequestResult(std::move(source.manageContractRequestResult_));
break;
      case (int32_t)OperationType::MANAGE_CONTRACT:
new(&manageContractResult_) ManageContractResult(std::move(source.manageContractResult_));
break;
      case (int32_t)OperationType::CANCEL_SALE_REQUEST:
new(&cancelSaleCreationRequestResult_) CancelSaleCreationRequestResult(std::move(source.cancelSaleCreationRequestResult_));
break;
      case (int32_t)OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST:
new(&createAtomicSwapAskRequestResult_) CreateAtomicSwapAskRequestResult(std::move(source.createAtomicSwapAskRequestResult_));
break;
      case (int32_t)OperationType::CANCEL_ATOMIC_SWAP_ASK:
new(&cancelAtomicSwapAskResult_) CancelAtomicSwapAskResult(std::move(source.cancelAtomicSwapAskResult_));
break;
      case (int32_t)OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST:
new(&createAtomicSwapBidRequestResult_) CreateAtomicSwapBidRequestResult(std::move(source.createAtomicSwapBidRequestResult_));
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_ROLE:
new(&manageAccountRoleResult_) ManageAccountRoleResult(std::move(source.manageAccountRoleResult_));
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_RULE:
new(&manageAccountRuleResult_) ManageAccountRuleResult(std::move(source.manageAccountRuleResult_));
break;
      case (int32_t)OperationType::MANAGE_SIGNER:
new(&manageSignerResult_) ManageSignerResult(std::move(source.manageSignerResult_));
break;
      case (int32_t)OperationType::MANAGE_SIGNER_ROLE:
new(&manageSignerRoleResult_) ManageSignerRoleResult(std::move(source.manageSignerRoleResult_));
break;
      case (int32_t)OperationType::MANAGE_SIGNER_RULE:
new(&manageSignerRuleResult_) ManageSignerRuleResult(std::move(source.manageSignerRuleResult_));
break;
      case (int32_t)OperationType::STAMP:
new(&stampResult_) StampResult(std::move(source.stampResult_));
break;
      case (int32_t)OperationType::LICENSE:
new(&licenseResult_) LicenseResult(std::move(source.licenseResult_));
break;
      case (int32_t)OperationType::MANAGE_POLL:
new(&managePollResult_) ManagePollResult(std::move(source.managePollResult_));
break;
      case (int32_t)OperationType::MANAGE_CREATE_POLL_REQUEST:
new(&manageCreatePollRequestResult_) ManageCreatePollRequestResult(std::move(source.manageCreatePollRequestResult_));
break;
      case (int32_t)OperationType::MANAGE_VOTE:
new(&manageVoteResult_) ManageVoteResult(std::move(source.manageVoteResult_));
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE:
new(&manageAccountSpecificRuleResult_) ManageAccountSpecificRuleResult(std::move(source.manageAccountSpecificRuleResult_));
break;
      case (int32_t)OperationType::CANCEL_CHANGE_ROLE_REQUEST:
new(&cancelChangeRoleRequestResult_) CancelChangeRoleRequestResult(std::move(source.cancelChangeRoleRequestResult_));
break;
      case (int32_t)OperationType::REMOVE_ASSET_PAIR:
new(&removeAssetPairResult_) RemoveAssetPairResult(std::move(source.removeAssetPairResult_));
break;
      case (int32_t)OperationType::CREATE_KYC_RECOVERY_REQUEST:
new(&createKYCRecoveryRequestResult_) CreateKYCRecoveryRequestResult(std::move(source.createKYCRecoveryRequestResult_));
break;
      case (int32_t)OperationType::INITIATE_KYC_RECOVERY:
new(&initiateKYCRecoveryResult_) InitiateKYCRecoveryResult(std::move(source.initiateKYCRecoveryResult_));
break;
      case (int32_t)OperationType::CREATE_MANAGE_OFFER_REQUEST:
new(&createManageOfferRequestResult_) CreateManageOfferRequestResult(std::move(source.createManageOfferRequestResult_));
break;
      case (int32_t)OperationType::CREATE_PAYMENT_REQUEST:
new(&createPaymentRequestResult_) CreatePaymentRequestResult(std::move(source.createPaymentRequestResult_));
break;
      case (int32_t)OperationType::REMOVE_ASSET:
new(&removeAssetResult_) RemoveAssetResult(std::move(source.removeAssetResult_));
break;
      case (int32_t)OperationType::OPEN_SWAP:
new(&openSwapResult_) OpenSwapResult(std::move(source.openSwapResult_));
break;
      case (int32_t)OperationType::CLOSE_SWAP:
new(&closeSwapResult_) CloseSwapResult(std::move(source.closeSwapResult_));
break;
      case (int32_t)OperationType::CREATE_REDEMPTION_REQUEST:
new(&createRedemptionRequestResult_) CreateRedemptionRequestResult(std::move(source.createRedemptionRequestResult_));
break;
      case (int32_t)OperationType::CREATE_DATA:
new(&createDataResult_) CreateDataResult(std::move(source.createDataResult_));
break;
      case (int32_t)OperationType::UPDATE_DATA:
new(&updateDataResult_) UpdateDataResult(std::move(source.updateDataResult_));
break;
      case (int32_t)OperationType::REMOVE_DATA:
new(&removeDataResult_) RemoveDataResult(std::move(source.removeDataResult_));
break;
      case (int32_t)OperationType::CREATE_DATA_REQUEST:
new(&createDataRequestResult_) CreateDataRequestResult(std::move(source.createDataRequestResult_));
break;
      case (int32_t)OperationType::CREATE_DATA_CREATION_REQUEST:
new(&CreateDataCreationRequestResult_) CreateDataCreationRequestResult(std::move(source.CreateDataCreationRequestResult_));
break;
      case (int32_t)OperationType::CANCEL_DATA_CREATION_REQUEST:
new(&CancelDataCreationRequestResult_) CancelDataCreationRequestResult(std::move(source.CancelDataCreationRequestResult_));
break;
}

    }
    ~_tr_t() {
switch (type_)
{
    case (int32_t)OperationType::CREATE_ACCOUNT:
createAccountResult_.~CreateAccountResult();
break;
    case (int32_t)OperationType::CREATE_ISSUANCE_REQUEST:
createIssuanceRequestResult_.~CreateIssuanceRequestResult();
break;
    case (int32_t)OperationType::SET_FEES:
setFeesResult_.~SetFeesResult();
break;
    case (int32_t)OperationType::CREATE_WITHDRAWAL_REQUEST:
createWithdrawalRequestResult_.~CreateWithdrawalRequestResult();
break;
    case (int32_t)OperationType::MANAGE_BALANCE:
manageBalanceResult_.~ManageBalanceResult();
break;
    case (int32_t)OperationType::MANAGE_ASSET:
manageAssetResult_.~ManageAssetResult();
break;
    case (int32_t)OperationType::CREATE_PREISSUANCE_REQUEST:
createPreIssuanceRequestResult_.~CreatePreIssuanceRequestResult();
break;
    case (int32_t)OperationType::MANAGE_LIMITS:
manageLimitsResult_.~ManageLimitsResult();
break;
    case (int32_t)OperationType::MANAGE_ASSET_PAIR:
manageAssetPairResult_.~ManageAssetPairResult();
break;
    case (int32_t)OperationType::MANAGE_OFFER:
manageOfferResult_.~ManageOfferResult();
break;
    case (int32_t)OperationType::MANAGE_INVOICE_REQUEST:
manageInvoiceRequestResult_.~ManageInvoiceRequestResult();
break;
    case (int32_t)OperationType::REVIEW_REQUEST:
reviewRequestResult_.~ReviewRequestResult();
break;
    case (int32_t)OperationType::CREATE_SALE_REQUEST:
createSaleCreationRequestResult_.~CreateSaleCreationRequestResult();
break;
    case (int32_t)OperationType::CHECK_SALE_STATE:
checkSaleStateResult_.~CheckSaleStateResult();
break;
    case (int32_t)OperationType::PAYOUT:
payoutResult_.~PayoutResult();
break;
    case (int32_t)OperationType::CREATE_AML_ALERT:
createAMLAlertRequestResult_.~CreateAMLAlertRequestResult();
break;
    case (int32_t)OperationType::MANAGE_KEY_VALUE:
manageKeyValueResult_.~ManageKeyValueResult();
break;
    case (int32_t)OperationType::CREATE_CHANGE_ROLE_REQUEST:
createChangeRoleRequestResult_.~CreateChangeRoleRequestResult();
break;
    case (int32_t)OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
manageExternalSystemAccountIdPoolEntryResult_.~ManageExternalSystemAccountIdPoolEntryResult();
break;
    case (int32_t)OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID:
bindExternalSystemAccountIdResult_.~BindExternalSystemAccountIdResult();
break;
    case (int32_t)OperationType::PAYMENT:
paymentResult_.~PaymentResult();
break;
    case (int32_t)OperationType::MANAGE_SALE:
manageSaleResult_.~ManageSaleResult();
break;
    case (int32_t)OperationType::CREATE_MANAGE_LIMITS_REQUEST:
createManageLimitsRequestResult_.~CreateManageLimitsRequestResult();
break;
    case (int32_t)OperationType::MANAGE_CONTRACT_REQUEST:
manageContractRequestResult_.~ManageContractRequestResult();
break;
    case (int32_t)OperationType::MANAGE_CONTRACT:
manageContractResult_.~ManageContractResult();
break;
    case (int32_t)OperationType::CANCEL_SALE_REQUEST:
cancelSaleCreationRequestResult_.~CancelSaleCreationRequestResult();
break;
    case (int32_t)OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST:
createAtomicSwapAskRequestResult_.~CreateAtomicSwapAskRequestResult();
break;
    case (int32_t)OperationType::CANCEL_ATOMIC_SWAP_ASK:
cancelAtomicSwapAskResult_.~CancelAtomicSwapAskResult();
break;
    case (int32_t)OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST:
createAtomicSwapBidRequestResult_.~CreateAtomicSwapBidRequestResult();
break;
    case (int32_t)OperationType::MANAGE_ACCOUNT_ROLE:
manageAccountRoleResult_.~ManageAccountRoleResult();
break;
    case (int32_t)OperationType::MANAGE_ACCOUNT_RULE:
manageAccountRuleResult_.~ManageAccountRuleResult();
break;
    case (int32_t)OperationType::MANAGE_SIGNER:
manageSignerResult_.~ManageSignerResult();
break;
    case (int32_t)OperationType::MANAGE_SIGNER_ROLE:
manageSignerRoleResult_.~ManageSignerRoleResult();
break;
    case (int32_t)OperationType::MANAGE_SIGNER_RULE:
manageSignerRuleResult_.~ManageSignerRuleResult();
break;
    case (int32_t)OperationType::STAMP:
stampResult_.~StampResult();
break;
    case (int32_t)OperationType::LICENSE:
licenseResult_.~LicenseResult();
break;
    case (int32_t)OperationType::MANAGE_POLL:
managePollResult_.~ManagePollResult();
break;
    case (int32_t)OperationType::MANAGE_CREATE_POLL_REQUEST:
manageCreatePollRequestResult_.~ManageCreatePollRequestResult();
break;
    case (int32_t)OperationType::MANAGE_VOTE:
manageVoteResult_.~ManageVoteResult();
break;
    case (int32_t)OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE:
manageAccountSpecificRuleResult_.~ManageAccountSpecificRuleResult();
break;
    case (int32_t)OperationType::CANCEL_CHANGE_ROLE_REQUEST:
cancelChangeRoleRequestResult_.~CancelChangeRoleRequestResult();
break;
    case (int32_t)OperationType::REMOVE_ASSET_PAIR:
removeAssetPairResult_.~RemoveAssetPairResult();
break;
    case (int32_t)OperationType::CREATE_KYC_RECOVERY_REQUEST:
createKYCRecoveryRequestResult_.~CreateKYCRecoveryRequestResult();
break;
    case (int32_t)OperationType::INITIATE_KYC_RECOVERY:
initiateKYCRecoveryResult_.~InitiateKYCRecoveryResult();
break;
    case (int32_t)OperationType::CREATE_MANAGE_OFFER_REQUEST:
createManageOfferRequestResult_.~CreateManageOfferRequestResult();
break;
    case (int32_t)OperationType::CREATE_PAYMENT_REQUEST:
createPaymentRequestResult_.~CreatePaymentRequestResult();
break;
    case (int32_t)OperationType::REMOVE_ASSET:
removeAssetResult_.~RemoveAssetResult();
break;
    case (int32_t)OperationType::OPEN_SWAP:
openSwapResult_.~OpenSwapResult();
break;
    case (int32_t)OperationType::CLOSE_SWAP:
closeSwapResult_.~CloseSwapResult();
break;
    case (int32_t)OperationType::CREATE_REDEMPTION_REQUEST:
createRedemptionRequestResult_.~CreateRedemptionRequestResult();
break;
    case (int32_t)OperationType::CREATE_DATA:
createDataResult_.~CreateDataResult();
break;
    case (int32_t)OperationType::UPDATE_DATA:
updateDataResult_.~UpdateDataResult();
break;
    case (int32_t)OperationType::REMOVE_DATA:
removeDataResult_.~RemoveDataResult();
break;
    case (int32_t)OperationType::CREATE_DATA_REQUEST:
createDataRequestResult_.~CreateDataRequestResult();
break;
    case (int32_t)OperationType::CREATE_DATA_CREATION_REQUEST:
CreateDataCreationRequestResult_.~CreateDataCreationRequestResult();
break;
    case (int32_t)OperationType::CANCEL_DATA_CREATION_REQUEST:
CancelDataCreationRequestResult_.~CancelDataCreationRequestResult();
break;
}
}

    _tr_t &operator=(const _tr_t &source) {
      if (type_ == source.type_)
{
switch (type_)
{
      case (int32_t)OperationType::CREATE_ACCOUNT:
createAccountResult_ = source.createAccountResult_;
break;
      case (int32_t)OperationType::CREATE_ISSUANCE_REQUEST:
createIssuanceRequestResult_ = source.createIssuanceRequestResult_;
break;
      case (int32_t)OperationType::SET_FEES:
setFeesResult_ = source.setFeesResult_;
break;
      case (int32_t)OperationType::CREATE_WITHDRAWAL_REQUEST:
createWithdrawalRequestResult_ = source.createWithdrawalRequestResult_;
break;
      case (int32_t)OperationType::MANAGE_BALANCE:
manageBalanceResult_ = source.manageBalanceResult_;
break;
      case (int32_t)OperationType::MANAGE_ASSET:
manageAssetResult_ = source.manageAssetResult_;
break;
      case (int32_t)OperationType::CREATE_PREISSUANCE_REQUEST:
createPreIssuanceRequestResult_ = source.createPreIssuanceRequestResult_;
break;
      case (int32_t)OperationType::MANAGE_LIMITS:
manageLimitsResult_ = source.manageLimitsResult_;
break;
      case (int32_t)OperationType::MANAGE_ASSET_PAIR:
manageAssetPairResult_ = source.manageAssetPairResult_;
break;
      case (int32_t)OperationType::MANAGE_OFFER:
manageOfferResult_ = source.manageOfferResult_;
break;
      case (int32_t)OperationType::MANAGE_INVOICE_REQUEST:
manageInvoiceRequestResult_ = source.manageInvoiceRequestResult_;
break;
      case (int32_t)OperationType::REVIEW_REQUEST:
reviewRequestResult_ = source.reviewRequestResult_;
break;
      case (int32_t)OperationType::CREATE_SALE_REQUEST:
createSaleCreationRequestResult_ = source.createSaleCreationRequestResult_;
break;
      case (int32_t)OperationType::CHECK_SALE_STATE:
checkSaleStateResult_ = source.checkSaleStateResult_;
break;
      case (int32_t)OperationType::PAYOUT:
payoutResult_ = source.payoutResult_;
break;
      case (int32_t)OperationType::CREATE_AML_ALERT:
createAMLAlertRequestResult_ = source.createAMLAlertRequestResult_;
break;
      case (int32_t)OperationType::MANAGE_KEY_VALUE:
manageKeyValueResult_ = source.manageKeyValueResult_;
break;
      case (int32_t)OperationType::CREATE_CHANGE_ROLE_REQUEST:
createChangeRoleRequestResult_ = source.createChangeRoleRequestResult_;
break;
      case (int32_t)OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
manageExternalSystemAccountIdPoolEntryResult_ = source.manageExternalSystemAccountIdPoolEntryResult_;
break;
      case (int32_t)OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID:
bindExternalSystemAccountIdResult_ = source.bindExternalSystemAccountIdResult_;
break;
      case (int32_t)OperationType::PAYMENT:
paymentResult_ = source.paymentResult_;
break;
      case (int32_t)OperationType::MANAGE_SALE:
manageSaleResult_ = source.manageSaleResult_;
break;
      case (int32_t)OperationType::CREATE_MANAGE_LIMITS_REQUEST:
createManageLimitsRequestResult_ = source.createManageLimitsRequestResult_;
break;
      case (int32_t)OperationType::MANAGE_CONTRACT_REQUEST:
manageContractRequestResult_ = source.manageContractRequestResult_;
break;
      case (int32_t)OperationType::MANAGE_CONTRACT:
manageContractResult_ = source.manageContractResult_;
break;
      case (int32_t)OperationType::CANCEL_SALE_REQUEST:
cancelSaleCreationRequestResult_ = source.cancelSaleCreationRequestResult_;
break;
      case (int32_t)OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST:
createAtomicSwapAskRequestResult_ = source.createAtomicSwapAskRequestResult_;
break;
      case (int32_t)OperationType::CANCEL_ATOMIC_SWAP_ASK:
cancelAtomicSwapAskResult_ = source.cancelAtomicSwapAskResult_;
break;
      case (int32_t)OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST:
createAtomicSwapBidRequestResult_ = source.createAtomicSwapBidRequestResult_;
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_ROLE:
manageAccountRoleResult_ = source.manageAccountRoleResult_;
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_RULE:
manageAccountRuleResult_ = source.manageAccountRuleResult_;
break;
      case (int32_t)OperationType::MANAGE_SIGNER:
manageSignerResult_ = source.manageSignerResult_;
break;
      case (int32_t)OperationType::MANAGE_SIGNER_ROLE:
manageSignerRoleResult_ = source.manageSignerRoleResult_;
break;
      case (int32_t)OperationType::MANAGE_SIGNER_RULE:
manageSignerRuleResult_ = source.manageSignerRuleResult_;
break;
      case (int32_t)OperationType::STAMP:
stampResult_ = source.stampResult_;
break;
      case (int32_t)OperationType::LICENSE:
licenseResult_ = source.licenseResult_;
break;
      case (int32_t)OperationType::MANAGE_POLL:
managePollResult_ = source.managePollResult_;
break;
      case (int32_t)OperationType::MANAGE_CREATE_POLL_REQUEST:
manageCreatePollRequestResult_ = source.manageCreatePollRequestResult_;
break;
      case (int32_t)OperationType::MANAGE_VOTE:
manageVoteResult_ = source.manageVoteResult_;
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE:
manageAccountSpecificRuleResult_ = source.manageAccountSpecificRuleResult_;
break;
      case (int32_t)OperationType::CANCEL_CHANGE_ROLE_REQUEST:
cancelChangeRoleRequestResult_ = source.cancelChangeRoleRequestResult_;
break;
      case (int32_t)OperationType::REMOVE_ASSET_PAIR:
removeAssetPairResult_ = source.removeAssetPairResult_;
break;
      case (int32_t)OperationType::CREATE_KYC_RECOVERY_REQUEST:
createKYCRecoveryRequestResult_ = source.createKYCRecoveryRequestResult_;
break;
      case (int32_t)OperationType::INITIATE_KYC_RECOVERY:
initiateKYCRecoveryResult_ = source.initiateKYCRecoveryResult_;
break;
      case (int32_t)OperationType::CREATE_MANAGE_OFFER_REQUEST:
createManageOfferRequestResult_ = source.createManageOfferRequestResult_;
break;
      case (int32_t)OperationType::CREATE_PAYMENT_REQUEST:
createPaymentRequestResult_ = source.createPaymentRequestResult_;
break;
      case (int32_t)OperationType::REMOVE_ASSET:
removeAssetResult_ = source.removeAssetResult_;
break;
      case (int32_t)OperationType::OPEN_SWAP:
openSwapResult_ = source.openSwapResult_;
break;
      case (int32_t)OperationType::CLOSE_SWAP:
closeSwapResult_ = source.closeSwapResult_;
break;
      case (int32_t)OperationType::CREATE_REDEMPTION_REQUEST:
createRedemptionRequestResult_ = source.createRedemptionRequestResult_;
break;
      case (int32_t)OperationType::CREATE_DATA:
createDataResult_ = source.createDataResult_;
break;
      case (int32_t)OperationType::UPDATE_DATA:
updateDataResult_ = source.updateDataResult_;
break;
      case (int32_t)OperationType::REMOVE_DATA:
removeDataResult_ = source.removeDataResult_;
break;
      case (int32_t)OperationType::CREATE_DATA_REQUEST:
createDataRequestResult_ = source.createDataRequestResult_;
break;
      case (int32_t)OperationType::CREATE_DATA_CREATION_REQUEST:
CreateDataCreationRequestResult_ = source.CreateDataCreationRequestResult_;
break;
      case (int32_t)OperationType::CANCEL_DATA_CREATION_REQUEST:
CancelDataCreationRequestResult_ = source.CancelDataCreationRequestResult_;
break;
}
}
else {this->~_tr_t();
      type_ = source.type_;
switch (type_)
{
      case (int32_t)OperationType::CREATE_ACCOUNT:
new(&createAccountResult_) CreateAccountResult(source.createAccountResult_);
break;
      case (int32_t)OperationType::CREATE_ISSUANCE_REQUEST:
new(&createIssuanceRequestResult_) CreateIssuanceRequestResult(source.createIssuanceRequestResult_);
break;
      case (int32_t)OperationType::SET_FEES:
new(&setFeesResult_) SetFeesResult(source.setFeesResult_);
break;
      case (int32_t)OperationType::CREATE_WITHDRAWAL_REQUEST:
new(&createWithdrawalRequestResult_) CreateWithdrawalRequestResult(source.createWithdrawalRequestResult_);
break;
      case (int32_t)OperationType::MANAGE_BALANCE:
new(&manageBalanceResult_) ManageBalanceResult(source.manageBalanceResult_);
break;
      case (int32_t)OperationType::MANAGE_ASSET:
new(&manageAssetResult_) ManageAssetResult(source.manageAssetResult_);
break;
      case (int32_t)OperationType::CREATE_PREISSUANCE_REQUEST:
new(&createPreIssuanceRequestResult_) CreatePreIssuanceRequestResult(source.createPreIssuanceRequestResult_);
break;
      case (int32_t)OperationType::MANAGE_LIMITS:
new(&manageLimitsResult_) ManageLimitsResult(source.manageLimitsResult_);
break;
      case (int32_t)OperationType::MANAGE_ASSET_PAIR:
new(&manageAssetPairResult_) ManageAssetPairResult(source.manageAssetPairResult_);
break;
      case (int32_t)OperationType::MANAGE_OFFER:
new(&manageOfferResult_) ManageOfferResult(source.manageOfferResult_);
break;
      case (int32_t)OperationType::MANAGE_INVOICE_REQUEST:
new(&manageInvoiceRequestResult_) ManageInvoiceRequestResult(source.manageInvoiceRequestResult_);
break;
      case (int32_t)OperationType::REVIEW_REQUEST:
new(&reviewRequestResult_) ReviewRequestResult(source.reviewRequestResult_);
break;
      case (int32_t)OperationType::CREATE_SALE_REQUEST:
new(&createSaleCreationRequestResult_) CreateSaleCreationRequestResult(source.createSaleCreationRequestResult_);
break;
      case (int32_t)OperationType::CHECK_SALE_STATE:
new(&checkSaleStateResult_) CheckSaleStateResult(source.checkSaleStateResult_);
break;
      case (int32_t)OperationType::PAYOUT:
new(&payoutResult_) PayoutResult(source.payoutResult_);
break;
      case (int32_t)OperationType::CREATE_AML_ALERT:
new(&createAMLAlertRequestResult_) CreateAMLAlertRequestResult(source.createAMLAlertRequestResult_);
break;
      case (int32_t)OperationType::MANAGE_KEY_VALUE:
new(&manageKeyValueResult_) ManageKeyValueResult(source.manageKeyValueResult_);
break;
      case (int32_t)OperationType::CREATE_CHANGE_ROLE_REQUEST:
new(&createChangeRoleRequestResult_) CreateChangeRoleRequestResult(source.createChangeRoleRequestResult_);
break;
      case (int32_t)OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
new(&manageExternalSystemAccountIdPoolEntryResult_) ManageExternalSystemAccountIdPoolEntryResult(source.manageExternalSystemAccountIdPoolEntryResult_);
break;
      case (int32_t)OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID:
new(&bindExternalSystemAccountIdResult_) BindExternalSystemAccountIdResult(source.bindExternalSystemAccountIdResult_);
break;
      case (int32_t)OperationType::PAYMENT:
new(&paymentResult_) PaymentResult(source.paymentResult_);
break;
      case (int32_t)OperationType::MANAGE_SALE:
new(&manageSaleResult_) ManageSaleResult(source.manageSaleResult_);
break;
      case (int32_t)OperationType::CREATE_MANAGE_LIMITS_REQUEST:
new(&createManageLimitsRequestResult_) CreateManageLimitsRequestResult(source.createManageLimitsRequestResult_);
break;
      case (int32_t)OperationType::MANAGE_CONTRACT_REQUEST:
new(&manageContractRequestResult_) ManageContractRequestResult(source.manageContractRequestResult_);
break;
      case (int32_t)OperationType::MANAGE_CONTRACT:
new(&manageContractResult_) ManageContractResult(source.manageContractResult_);
break;
      case (int32_t)OperationType::CANCEL_SALE_REQUEST:
new(&cancelSaleCreationRequestResult_) CancelSaleCreationRequestResult(source.cancelSaleCreationRequestResult_);
break;
      case (int32_t)OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST:
new(&createAtomicSwapAskRequestResult_) CreateAtomicSwapAskRequestResult(source.createAtomicSwapAskRequestResult_);
break;
      case (int32_t)OperationType::CANCEL_ATOMIC_SWAP_ASK:
new(&cancelAtomicSwapAskResult_) CancelAtomicSwapAskResult(source.cancelAtomicSwapAskResult_);
break;
      case (int32_t)OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST:
new(&createAtomicSwapBidRequestResult_) CreateAtomicSwapBidRequestResult(source.createAtomicSwapBidRequestResult_);
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_ROLE:
new(&manageAccountRoleResult_) ManageAccountRoleResult(source.manageAccountRoleResult_);
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_RULE:
new(&manageAccountRuleResult_) ManageAccountRuleResult(source.manageAccountRuleResult_);
break;
      case (int32_t)OperationType::MANAGE_SIGNER:
new(&manageSignerResult_) ManageSignerResult(source.manageSignerResult_);
break;
      case (int32_t)OperationType::MANAGE_SIGNER_ROLE:
new(&manageSignerRoleResult_) ManageSignerRoleResult(source.manageSignerRoleResult_);
break;
      case (int32_t)OperationType::MANAGE_SIGNER_RULE:
new(&manageSignerRuleResult_) ManageSignerRuleResult(source.manageSignerRuleResult_);
break;
      case (int32_t)OperationType::STAMP:
new(&stampResult_) StampResult(source.stampResult_);
break;
      case (int32_t)OperationType::LICENSE:
new(&licenseResult_) LicenseResult(source.licenseResult_);
break;
      case (int32_t)OperationType::MANAGE_POLL:
new(&managePollResult_) ManagePollResult(source.managePollResult_);
break;
      case (int32_t)OperationType::MANAGE_CREATE_POLL_REQUEST:
new(&manageCreatePollRequestResult_) ManageCreatePollRequestResult(source.manageCreatePollRequestResult_);
break;
      case (int32_t)OperationType::MANAGE_VOTE:
new(&manageVoteResult_) ManageVoteResult(source.manageVoteResult_);
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE:
new(&manageAccountSpecificRuleResult_) ManageAccountSpecificRuleResult(source.manageAccountSpecificRuleResult_);
break;
      case (int32_t)OperationType::CANCEL_CHANGE_ROLE_REQUEST:
new(&cancelChangeRoleRequestResult_) CancelChangeRoleRequestResult(source.cancelChangeRoleRequestResult_);
break;
      case (int32_t)OperationType::REMOVE_ASSET_PAIR:
new(&removeAssetPairResult_) RemoveAssetPairResult(source.removeAssetPairResult_);
break;
      case (int32_t)OperationType::CREATE_KYC_RECOVERY_REQUEST:
new(&createKYCRecoveryRequestResult_) CreateKYCRecoveryRequestResult(source.createKYCRecoveryRequestResult_);
break;
      case (int32_t)OperationType::INITIATE_KYC_RECOVERY:
new(&initiateKYCRecoveryResult_) InitiateKYCRecoveryResult(source.initiateKYCRecoveryResult_);
break;
      case (int32_t)OperationType::CREATE_MANAGE_OFFER_REQUEST:
new(&createManageOfferRequestResult_) CreateManageOfferRequestResult(source.createManageOfferRequestResult_);
break;
      case (int32_t)OperationType::CREATE_PAYMENT_REQUEST:
new(&createPaymentRequestResult_) CreatePaymentRequestResult(source.createPaymentRequestResult_);
break;
      case (int32_t)OperationType::REMOVE_ASSET:
new(&removeAssetResult_) RemoveAssetResult(source.removeAssetResult_);
break;
      case (int32_t)OperationType::OPEN_SWAP:
new(&openSwapResult_) OpenSwapResult(source.openSwapResult_);
break;
      case (int32_t)OperationType::CLOSE_SWAP:
new(&closeSwapResult_) CloseSwapResult(source.closeSwapResult_);
break;
      case (int32_t)OperationType::CREATE_REDEMPTION_REQUEST:
new(&createRedemptionRequestResult_) CreateRedemptionRequestResult(source.createRedemptionRequestResult_);
break;
      case (int32_t)OperationType::CREATE_DATA:
new(&createDataResult_) CreateDataResult(source.createDataResult_);
break;
      case (int32_t)OperationType::UPDATE_DATA:
new(&updateDataResult_) UpdateDataResult(source.updateDataResult_);
break;
      case (int32_t)OperationType::REMOVE_DATA:
new(&removeDataResult_) RemoveDataResult(source.removeDataResult_);
break;
      case (int32_t)OperationType::CREATE_DATA_REQUEST:
new(&createDataRequestResult_) CreateDataRequestResult(source.createDataRequestResult_);
break;
      case (int32_t)OperationType::CREATE_DATA_CREATION_REQUEST:
new(&CreateDataCreationRequestResult_) CreateDataCreationRequestResult(source.CreateDataCreationRequestResult_);
break;
      case (int32_t)OperationType::CANCEL_DATA_CREATION_REQUEST:
new(&CancelDataCreationRequestResult_) CancelDataCreationRequestResult(source.CancelDataCreationRequestResult_);
break;
}
}
      return *this;
    }
    _tr_t &operator=(_tr_t &&source) {
      if (type_ == source.type_)
{
switch (type_)
{
      case (int32_t)OperationType::CREATE_ACCOUNT:
createAccountResult_ = std::move(source.createAccountResult_);
break;
      case (int32_t)OperationType::CREATE_ISSUANCE_REQUEST:
createIssuanceRequestResult_ = std::move(source.createIssuanceRequestResult_);
break;
      case (int32_t)OperationType::SET_FEES:
setFeesResult_ = std::move(source.setFeesResult_);
break;
      case (int32_t)OperationType::CREATE_WITHDRAWAL_REQUEST:
createWithdrawalRequestResult_ = std::move(source.createWithdrawalRequestResult_);
break;
      case (int32_t)OperationType::MANAGE_BALANCE:
manageBalanceResult_ = std::move(source.manageBalanceResult_);
break;
      case (int32_t)OperationType::MANAGE_ASSET:
manageAssetResult_ = std::move(source.manageAssetResult_);
break;
      case (int32_t)OperationType::CREATE_PREISSUANCE_REQUEST:
createPreIssuanceRequestResult_ = std::move(source.createPreIssuanceRequestResult_);
break;
      case (int32_t)OperationType::MANAGE_LIMITS:
manageLimitsResult_ = std::move(source.manageLimitsResult_);
break;
      case (int32_t)OperationType::MANAGE_ASSET_PAIR:
manageAssetPairResult_ = std::move(source.manageAssetPairResult_);
break;
      case (int32_t)OperationType::MANAGE_OFFER:
manageOfferResult_ = std::move(source.manageOfferResult_);
break;
      case (int32_t)OperationType::MANAGE_INVOICE_REQUEST:
manageInvoiceRequestResult_ = std::move(source.manageInvoiceRequestResult_);
break;
      case (int32_t)OperationType::REVIEW_REQUEST:
reviewRequestResult_ = std::move(source.reviewRequestResult_);
break;
      case (int32_t)OperationType::CREATE_SALE_REQUEST:
createSaleCreationRequestResult_ = std::move(source.createSaleCreationRequestResult_);
break;
      case (int32_t)OperationType::CHECK_SALE_STATE:
checkSaleStateResult_ = std::move(source.checkSaleStateResult_);
break;
      case (int32_t)OperationType::PAYOUT:
payoutResult_ = std::move(source.payoutResult_);
break;
      case (int32_t)OperationType::CREATE_AML_ALERT:
createAMLAlertRequestResult_ = std::move(source.createAMLAlertRequestResult_);
break;
      case (int32_t)OperationType::MANAGE_KEY_VALUE:
manageKeyValueResult_ = std::move(source.manageKeyValueResult_);
break;
      case (int32_t)OperationType::CREATE_CHANGE_ROLE_REQUEST:
createChangeRoleRequestResult_ = std::move(source.createChangeRoleRequestResult_);
break;
      case (int32_t)OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
manageExternalSystemAccountIdPoolEntryResult_ = std::move(source.manageExternalSystemAccountIdPoolEntryResult_);
break;
      case (int32_t)OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID:
bindExternalSystemAccountIdResult_ = std::move(source.bindExternalSystemAccountIdResult_);
break;
      case (int32_t)OperationType::PAYMENT:
paymentResult_ = std::move(source.paymentResult_);
break;
      case (int32_t)OperationType::MANAGE_SALE:
manageSaleResult_ = std::move(source.manageSaleResult_);
break;
      case (int32_t)OperationType::CREATE_MANAGE_LIMITS_REQUEST:
createManageLimitsRequestResult_ = std::move(source.createManageLimitsRequestResult_);
break;
      case (int32_t)OperationType::MANAGE_CONTRACT_REQUEST:
manageContractRequestResult_ = std::move(source.manageContractRequestResult_);
break;
      case (int32_t)OperationType::MANAGE_CONTRACT:
manageContractResult_ = std::move(source.manageContractResult_);
break;
      case (int32_t)OperationType::CANCEL_SALE_REQUEST:
cancelSaleCreationRequestResult_ = std::move(source.cancelSaleCreationRequestResult_);
break;
      case (int32_t)OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST:
createAtomicSwapAskRequestResult_ = std::move(source.createAtomicSwapAskRequestResult_);
break;
      case (int32_t)OperationType::CANCEL_ATOMIC_SWAP_ASK:
cancelAtomicSwapAskResult_ = std::move(source.cancelAtomicSwapAskResult_);
break;
      case (int32_t)OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST:
createAtomicSwapBidRequestResult_ = std::move(source.createAtomicSwapBidRequestResult_);
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_ROLE:
manageAccountRoleResult_ = std::move(source.manageAccountRoleResult_);
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_RULE:
manageAccountRuleResult_ = std::move(source.manageAccountRuleResult_);
break;
      case (int32_t)OperationType::MANAGE_SIGNER:
manageSignerResult_ = std::move(source.manageSignerResult_);
break;
      case (int32_t)OperationType::MANAGE_SIGNER_ROLE:
manageSignerRoleResult_ = std::move(source.manageSignerRoleResult_);
break;
      case (int32_t)OperationType::MANAGE_SIGNER_RULE:
manageSignerRuleResult_ = std::move(source.manageSignerRuleResult_);
break;
      case (int32_t)OperationType::STAMP:
stampResult_ = std::move(source.stampResult_);
break;
      case (int32_t)OperationType::LICENSE:
licenseResult_ = std::move(source.licenseResult_);
break;
      case (int32_t)OperationType::MANAGE_POLL:
managePollResult_ = std::move(source.managePollResult_);
break;
      case (int32_t)OperationType::MANAGE_CREATE_POLL_REQUEST:
manageCreatePollRequestResult_ = std::move(source.manageCreatePollRequestResult_);
break;
      case (int32_t)OperationType::MANAGE_VOTE:
manageVoteResult_ = std::move(source.manageVoteResult_);
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE:
manageAccountSpecificRuleResult_ = std::move(source.manageAccountSpecificRuleResult_);
break;
      case (int32_t)OperationType::CANCEL_CHANGE_ROLE_REQUEST:
cancelChangeRoleRequestResult_ = std::move(source.cancelChangeRoleRequestResult_);
break;
      case (int32_t)OperationType::REMOVE_ASSET_PAIR:
removeAssetPairResult_ = std::move(source.removeAssetPairResult_);
break;
      case (int32_t)OperationType::CREATE_KYC_RECOVERY_REQUEST:
createKYCRecoveryRequestResult_ = std::move(source.createKYCRecoveryRequestResult_);
break;
      case (int32_t)OperationType::INITIATE_KYC_RECOVERY:
initiateKYCRecoveryResult_ = std::move(source.initiateKYCRecoveryResult_);
break;
      case (int32_t)OperationType::CREATE_MANAGE_OFFER_REQUEST:
createManageOfferRequestResult_ = std::move(source.createManageOfferRequestResult_);
break;
      case (int32_t)OperationType::CREATE_PAYMENT_REQUEST:
createPaymentRequestResult_ = std::move(source.createPaymentRequestResult_);
break;
      case (int32_t)OperationType::REMOVE_ASSET:
removeAssetResult_ = std::move(source.removeAssetResult_);
break;
      case (int32_t)OperationType::OPEN_SWAP:
openSwapResult_ = std::move(source.openSwapResult_);
break;
      case (int32_t)OperationType::CLOSE_SWAP:
closeSwapResult_ = std::move(source.closeSwapResult_);
break;
      case (int32_t)OperationType::CREATE_REDEMPTION_REQUEST:
createRedemptionRequestResult_ = std::move(source.createRedemptionRequestResult_);
break;
      case (int32_t)OperationType::CREATE_DATA:
createDataResult_ = std::move(source.createDataResult_);
break;
      case (int32_t)OperationType::UPDATE_DATA:
updateDataResult_ = std::move(source.updateDataResult_);
break;
      case (int32_t)OperationType::REMOVE_DATA:
removeDataResult_ = std::move(source.removeDataResult_);
break;
      case (int32_t)OperationType::CREATE_DATA_REQUEST:
createDataRequestResult_ = std::move(source.createDataRequestResult_);
break;
      case (int32_t)OperationType::CREATE_DATA_CREATION_REQUEST:
CreateDataCreationRequestResult_ = std::move(source.CreateDataCreationRequestResult_);
break;
      case (int32_t)OperationType::CANCEL_DATA_CREATION_REQUEST:
CancelDataCreationRequestResult_ = std::move(source.CancelDataCreationRequestResult_);
break;
}
}
else {this->~_tr_t();
      type_ = std::move(source.type_);
switch (type_)
{
      case (int32_t)OperationType::CREATE_ACCOUNT:
new(&createAccountResult_) CreateAccountResult(std::move(source.createAccountResult_));
break;
      case (int32_t)OperationType::CREATE_ISSUANCE_REQUEST:
new(&createIssuanceRequestResult_) CreateIssuanceRequestResult(std::move(source.createIssuanceRequestResult_));
break;
      case (int32_t)OperationType::SET_FEES:
new(&setFeesResult_) SetFeesResult(std::move(source.setFeesResult_));
break;
      case (int32_t)OperationType::CREATE_WITHDRAWAL_REQUEST:
new(&createWithdrawalRequestResult_) CreateWithdrawalRequestResult(std::move(source.createWithdrawalRequestResult_));
break;
      case (int32_t)OperationType::MANAGE_BALANCE:
new(&manageBalanceResult_) ManageBalanceResult(std::move(source.manageBalanceResult_));
break;
      case (int32_t)OperationType::MANAGE_ASSET:
new(&manageAssetResult_) ManageAssetResult(std::move(source.manageAssetResult_));
break;
      case (int32_t)OperationType::CREATE_PREISSUANCE_REQUEST:
new(&createPreIssuanceRequestResult_) CreatePreIssuanceRequestResult(std::move(source.createPreIssuanceRequestResult_));
break;
      case (int32_t)OperationType::MANAGE_LIMITS:
new(&manageLimitsResult_) ManageLimitsResult(std::move(source.manageLimitsResult_));
break;
      case (int32_t)OperationType::MANAGE_ASSET_PAIR:
new(&manageAssetPairResult_) ManageAssetPairResult(std::move(source.manageAssetPairResult_));
break;
      case (int32_t)OperationType::MANAGE_OFFER:
new(&manageOfferResult_) ManageOfferResult(std::move(source.manageOfferResult_));
break;
      case (int32_t)OperationType::MANAGE_INVOICE_REQUEST:
new(&manageInvoiceRequestResult_) ManageInvoiceRequestResult(std::move(source.manageInvoiceRequestResult_));
break;
      case (int32_t)OperationType::REVIEW_REQUEST:
new(&reviewRequestResult_) ReviewRequestResult(std::move(source.reviewRequestResult_));
break;
      case (int32_t)OperationType::CREATE_SALE_REQUEST:
new(&createSaleCreationRequestResult_) CreateSaleCreationRequestResult(std::move(source.createSaleCreationRequestResult_));
break;
      case (int32_t)OperationType::CHECK_SALE_STATE:
new(&checkSaleStateResult_) CheckSaleStateResult(std::move(source.checkSaleStateResult_));
break;
      case (int32_t)OperationType::PAYOUT:
new(&payoutResult_) PayoutResult(std::move(source.payoutResult_));
break;
      case (int32_t)OperationType::CREATE_AML_ALERT:
new(&createAMLAlertRequestResult_) CreateAMLAlertRequestResult(std::move(source.createAMLAlertRequestResult_));
break;
      case (int32_t)OperationType::MANAGE_KEY_VALUE:
new(&manageKeyValueResult_) ManageKeyValueResult(std::move(source.manageKeyValueResult_));
break;
      case (int32_t)OperationType::CREATE_CHANGE_ROLE_REQUEST:
new(&createChangeRoleRequestResult_) CreateChangeRoleRequestResult(std::move(source.createChangeRoleRequestResult_));
break;
      case (int32_t)OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
new(&manageExternalSystemAccountIdPoolEntryResult_) ManageExternalSystemAccountIdPoolEntryResult(std::move(source.manageExternalSystemAccountIdPoolEntryResult_));
break;
      case (int32_t)OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID:
new(&bindExternalSystemAccountIdResult_) BindExternalSystemAccountIdResult(std::move(source.bindExternalSystemAccountIdResult_));
break;
      case (int32_t)OperationType::PAYMENT:
new(&paymentResult_) PaymentResult(std::move(source.paymentResult_));
break;
      case (int32_t)OperationType::MANAGE_SALE:
new(&manageSaleResult_) ManageSaleResult(std::move(source.manageSaleResult_));
break;
      case (int32_t)OperationType::CREATE_MANAGE_LIMITS_REQUEST:
new(&createManageLimitsRequestResult_) CreateManageLimitsRequestResult(std::move(source.createManageLimitsRequestResult_));
break;
      case (int32_t)OperationType::MANAGE_CONTRACT_REQUEST:
new(&manageContractRequestResult_) ManageContractRequestResult(std::move(source.manageContractRequestResult_));
break;
      case (int32_t)OperationType::MANAGE_CONTRACT:
new(&manageContractResult_) ManageContractResult(std::move(source.manageContractResult_));
break;
      case (int32_t)OperationType::CANCEL_SALE_REQUEST:
new(&cancelSaleCreationRequestResult_) CancelSaleCreationRequestResult(std::move(source.cancelSaleCreationRequestResult_));
break;
      case (int32_t)OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST:
new(&createAtomicSwapAskRequestResult_) CreateAtomicSwapAskRequestResult(std::move(source.createAtomicSwapAskRequestResult_));
break;
      case (int32_t)OperationType::CANCEL_ATOMIC_SWAP_ASK:
new(&cancelAtomicSwapAskResult_) CancelAtomicSwapAskResult(std::move(source.cancelAtomicSwapAskResult_));
break;
      case (int32_t)OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST:
new(&createAtomicSwapBidRequestResult_) CreateAtomicSwapBidRequestResult(std::move(source.createAtomicSwapBidRequestResult_));
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_ROLE:
new(&manageAccountRoleResult_) ManageAccountRoleResult(std::move(source.manageAccountRoleResult_));
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_RULE:
new(&manageAccountRuleResult_) ManageAccountRuleResult(std::move(source.manageAccountRuleResult_));
break;
      case (int32_t)OperationType::MANAGE_SIGNER:
new(&manageSignerResult_) ManageSignerResult(std::move(source.manageSignerResult_));
break;
      case (int32_t)OperationType::MANAGE_SIGNER_ROLE:
new(&manageSignerRoleResult_) ManageSignerRoleResult(std::move(source.manageSignerRoleResult_));
break;
      case (int32_t)OperationType::MANAGE_SIGNER_RULE:
new(&manageSignerRuleResult_) ManageSignerRuleResult(std::move(source.manageSignerRuleResult_));
break;
      case (int32_t)OperationType::STAMP:
new(&stampResult_) StampResult(std::move(source.stampResult_));
break;
      case (int32_t)OperationType::LICENSE:
new(&licenseResult_) LicenseResult(std::move(source.licenseResult_));
break;
      case (int32_t)OperationType::MANAGE_POLL:
new(&managePollResult_) ManagePollResult(std::move(source.managePollResult_));
break;
      case (int32_t)OperationType::MANAGE_CREATE_POLL_REQUEST:
new(&manageCreatePollRequestResult_) ManageCreatePollRequestResult(std::move(source.manageCreatePollRequestResult_));
break;
      case (int32_t)OperationType::MANAGE_VOTE:
new(&manageVoteResult_) ManageVoteResult(std::move(source.manageVoteResult_));
break;
      case (int32_t)OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE:
new(&manageAccountSpecificRuleResult_) ManageAccountSpecificRuleResult(std::move(source.manageAccountSpecificRuleResult_));
break;
      case (int32_t)OperationType::CANCEL_CHANGE_ROLE_REQUEST:
new(&cancelChangeRoleRequestResult_) CancelChangeRoleRequestResult(std::move(source.cancelChangeRoleRequestResult_));
break;
      case (int32_t)OperationType::REMOVE_ASSET_PAIR:
new(&removeAssetPairResult_) RemoveAssetPairResult(std::move(source.removeAssetPairResult_));
break;
      case (int32_t)OperationType::CREATE_KYC_RECOVERY_REQUEST:
new(&createKYCRecoveryRequestResult_) CreateKYCRecoveryRequestResult(std::move(source.createKYCRecoveryRequestResult_));
break;
      case (int32_t)OperationType::INITIATE_KYC_RECOVERY:
new(&initiateKYCRecoveryResult_) InitiateKYCRecoveryResult(std::move(source.initiateKYCRecoveryResult_));
break;
      case (int32_t)OperationType::CREATE_MANAGE_OFFER_REQUEST:
new(&createManageOfferRequestResult_) CreateManageOfferRequestResult(std::move(source.createManageOfferRequestResult_));
break;
      case (int32_t)OperationType::CREATE_PAYMENT_REQUEST:
new(&createPaymentRequestResult_) CreatePaymentRequestResult(std::move(source.createPaymentRequestResult_));
break;
      case (int32_t)OperationType::REMOVE_ASSET:
new(&removeAssetResult_) RemoveAssetResult(std::move(source.removeAssetResult_));
break;
      case (int32_t)OperationType::OPEN_SWAP:
new(&openSwapResult_) OpenSwapResult(std::move(source.openSwapResult_));
break;
      case (int32_t)OperationType::CLOSE_SWAP:
new(&closeSwapResult_) CloseSwapResult(std::move(source.closeSwapResult_));
break;
      case (int32_t)OperationType::CREATE_REDEMPTION_REQUEST:
new(&createRedemptionRequestResult_) CreateRedemptionRequestResult(std::move(source.createRedemptionRequestResult_));
break;
      case (int32_t)OperationType::CREATE_DATA:
new(&createDataResult_) CreateDataResult(std::move(source.createDataResult_));
break;
      case (int32_t)OperationType::UPDATE_DATA:
new(&updateDataResult_) UpdateDataResult(std::move(source.updateDataResult_));
break;
      case (int32_t)OperationType::REMOVE_DATA:
new(&removeDataResult_) RemoveDataResult(std::move(source.removeDataResult_));
break;
      case (int32_t)OperationType::CREATE_DATA_REQUEST:
new(&createDataRequestResult_) CreateDataRequestResult(std::move(source.createDataRequestResult_));
break;
      case (int32_t)OperationType::CREATE_DATA_CREATION_REQUEST:
new(&CreateDataCreationRequestResult_) CreateDataCreationRequestResult(std::move(source.CreateDataCreationRequestResult_));
break;
      case (int32_t)OperationType::CANCEL_DATA_CREATION_REQUEST:
new(&CancelDataCreationRequestResult_) CancelDataCreationRequestResult(std::move(source.CancelDataCreationRequestResult_));
break;
}
}
      return *this;
    }

    OperationType type() const { return OperationType(type_); }
    _tr_t &type(OperationType _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    CreateAccountResult &createAccountResult() {
      if (_xdr_field_number(type_) == 1)
        return createAccountResult_;
      throw xdr::xdr_wrong_union("_tr_t: createAccountResult accessed when not selected");
    }
    const CreateAccountResult &createAccountResult() const {
      if (_xdr_field_number(type_) == 1)
        return createAccountResult_;
      throw xdr::xdr_wrong_union("_tr_t: createAccountResult accessed when not selected");
    }
    CreateIssuanceRequestResult &createIssuanceRequestResult() {
      if (_xdr_field_number(type_) == 2)
        return createIssuanceRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: createIssuanceRequestResult accessed when not selected");
    }
    const CreateIssuanceRequestResult &createIssuanceRequestResult() const {
      if (_xdr_field_number(type_) == 2)
        return createIssuanceRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: createIssuanceRequestResult accessed when not selected");
    }
    SetFeesResult &setFeesResult() {
      if (_xdr_field_number(type_) == 3)
        return setFeesResult_;
      throw xdr::xdr_wrong_union("_tr_t: setFeesResult accessed when not selected");
    }
    const SetFeesResult &setFeesResult() const {
      if (_xdr_field_number(type_) == 3)
        return setFeesResult_;
      throw xdr::xdr_wrong_union("_tr_t: setFeesResult accessed when not selected");
    }
    CreateWithdrawalRequestResult &createWithdrawalRequestResult() {
      if (_xdr_field_number(type_) == 4)
        return createWithdrawalRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: createWithdrawalRequestResult accessed when not selected");
    }
    const CreateWithdrawalRequestResult &createWithdrawalRequestResult() const {
      if (_xdr_field_number(type_) == 4)
        return createWithdrawalRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: createWithdrawalRequestResult accessed when not selected");
    }
    ManageBalanceResult &manageBalanceResult() {
      if (_xdr_field_number(type_) == 5)
        return manageBalanceResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageBalanceResult accessed when not selected");
    }
    const ManageBalanceResult &manageBalanceResult() const {
      if (_xdr_field_number(type_) == 5)
        return manageBalanceResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageBalanceResult accessed when not selected");
    }
    ManageAssetResult &manageAssetResult() {
      if (_xdr_field_number(type_) == 6)
        return manageAssetResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageAssetResult accessed when not selected");
    }
    const ManageAssetResult &manageAssetResult() const {
      if (_xdr_field_number(type_) == 6)
        return manageAssetResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageAssetResult accessed when not selected");
    }
    CreatePreIssuanceRequestResult &createPreIssuanceRequestResult() {
      if (_xdr_field_number(type_) == 7)
        return createPreIssuanceRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: createPreIssuanceRequestResult accessed when not selected");
    }
    const CreatePreIssuanceRequestResult &createPreIssuanceRequestResult() const {
      if (_xdr_field_number(type_) == 7)
        return createPreIssuanceRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: createPreIssuanceRequestResult accessed when not selected");
    }
    ManageLimitsResult &manageLimitsResult() {
      if (_xdr_field_number(type_) == 8)
        return manageLimitsResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageLimitsResult accessed when not selected");
    }
    const ManageLimitsResult &manageLimitsResult() const {
      if (_xdr_field_number(type_) == 8)
        return manageLimitsResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageLimitsResult accessed when not selected");
    }
    ManageAssetPairResult &manageAssetPairResult() {
      if (_xdr_field_number(type_) == 9)
        return manageAssetPairResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageAssetPairResult accessed when not selected");
    }
    const ManageAssetPairResult &manageAssetPairResult() const {
      if (_xdr_field_number(type_) == 9)
        return manageAssetPairResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageAssetPairResult accessed when not selected");
    }
    ManageOfferResult &manageOfferResult() {
      if (_xdr_field_number(type_) == 10)
        return manageOfferResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageOfferResult accessed when not selected");
    }
    const ManageOfferResult &manageOfferResult() const {
      if (_xdr_field_number(type_) == 10)
        return manageOfferResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageOfferResult accessed when not selected");
    }
    ManageInvoiceRequestResult &manageInvoiceRequestResult() {
      if (_xdr_field_number(type_) == 11)
        return manageInvoiceRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageInvoiceRequestResult accessed when not selected");
    }
    const ManageInvoiceRequestResult &manageInvoiceRequestResult() const {
      if (_xdr_field_number(type_) == 11)
        return manageInvoiceRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageInvoiceRequestResult accessed when not selected");
    }
    ReviewRequestResult &reviewRequestResult() {
      if (_xdr_field_number(type_) == 12)
        return reviewRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: reviewRequestResult accessed when not selected");
    }
    const ReviewRequestResult &reviewRequestResult() const {
      if (_xdr_field_number(type_) == 12)
        return reviewRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: reviewRequestResult accessed when not selected");
    }
    CreateSaleCreationRequestResult &createSaleCreationRequestResult() {
      if (_xdr_field_number(type_) == 13)
        return createSaleCreationRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: createSaleCreationRequestResult accessed when not selected");
    }
    const CreateSaleCreationRequestResult &createSaleCreationRequestResult() const {
      if (_xdr_field_number(type_) == 13)
        return createSaleCreationRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: createSaleCreationRequestResult accessed when not selected");
    }
    CheckSaleStateResult &checkSaleStateResult() {
      if (_xdr_field_number(type_) == 14)
        return checkSaleStateResult_;
      throw xdr::xdr_wrong_union("_tr_t: checkSaleStateResult accessed when not selected");
    }
    const CheckSaleStateResult &checkSaleStateResult() const {
      if (_xdr_field_number(type_) == 14)
        return checkSaleStateResult_;
      throw xdr::xdr_wrong_union("_tr_t: checkSaleStateResult accessed when not selected");
    }
    PayoutResult &payoutResult() {
      if (_xdr_field_number(type_) == 15)
        return payoutResult_;
      throw xdr::xdr_wrong_union("_tr_t: payoutResult accessed when not selected");
    }
    const PayoutResult &payoutResult() const {
      if (_xdr_field_number(type_) == 15)
        return payoutResult_;
      throw xdr::xdr_wrong_union("_tr_t: payoutResult accessed when not selected");
    }
    CreateAMLAlertRequestResult &createAMLAlertRequestResult() {
      if (_xdr_field_number(type_) == 16)
        return createAMLAlertRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: createAMLAlertRequestResult accessed when not selected");
    }
    const CreateAMLAlertRequestResult &createAMLAlertRequestResult() const {
      if (_xdr_field_number(type_) == 16)
        return createAMLAlertRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: createAMLAlertRequestResult accessed when not selected");
    }
    ManageKeyValueResult &manageKeyValueResult() {
      if (_xdr_field_number(type_) == 17)
        return manageKeyValueResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageKeyValueResult accessed when not selected");
    }
    const ManageKeyValueResult &manageKeyValueResult() const {
      if (_xdr_field_number(type_) == 17)
        return manageKeyValueResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageKeyValueResult accessed when not selected");
    }
    CreateChangeRoleRequestResult &createChangeRoleRequestResult() {
      if (_xdr_field_number(type_) == 18)
        return createChangeRoleRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: createChangeRoleRequestResult accessed when not selected");
    }
    const CreateChangeRoleRequestResult &createChangeRoleRequestResult() const {
      if (_xdr_field_number(type_) == 18)
        return createChangeRoleRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: createChangeRoleRequestResult accessed when not selected");
    }
    ManageExternalSystemAccountIdPoolEntryResult &manageExternalSystemAccountIdPoolEntryResult() {
      if (_xdr_field_number(type_) == 19)
        return manageExternalSystemAccountIdPoolEntryResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageExternalSystemAccountIdPoolEntryResult accessed when not selected");
    }
    const ManageExternalSystemAccountIdPoolEntryResult &manageExternalSystemAccountIdPoolEntryResult() const {
      if (_xdr_field_number(type_) == 19)
        return manageExternalSystemAccountIdPoolEntryResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageExternalSystemAccountIdPoolEntryResult accessed when not selected");
    }
    BindExternalSystemAccountIdResult &bindExternalSystemAccountIdResult() {
      if (_xdr_field_number(type_) == 20)
        return bindExternalSystemAccountIdResult_;
      throw xdr::xdr_wrong_union("_tr_t: bindExternalSystemAccountIdResult accessed when not selected");
    }
    const BindExternalSystemAccountIdResult &bindExternalSystemAccountIdResult() const {
      if (_xdr_field_number(type_) == 20)
        return bindExternalSystemAccountIdResult_;
      throw xdr::xdr_wrong_union("_tr_t: bindExternalSystemAccountIdResult accessed when not selected");
    }
    PaymentResult &paymentResult() {
      if (_xdr_field_number(type_) == 21)
        return paymentResult_;
      throw xdr::xdr_wrong_union("_tr_t: paymentResult accessed when not selected");
    }
    const PaymentResult &paymentResult() const {
      if (_xdr_field_number(type_) == 21)
        return paymentResult_;
      throw xdr::xdr_wrong_union("_tr_t: paymentResult accessed when not selected");
    }
    ManageSaleResult &manageSaleResult() {
      if (_xdr_field_number(type_) == 22)
        return manageSaleResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageSaleResult accessed when not selected");
    }
    const ManageSaleResult &manageSaleResult() const {
      if (_xdr_field_number(type_) == 22)
        return manageSaleResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageSaleResult accessed when not selected");
    }
    CreateManageLimitsRequestResult &createManageLimitsRequestResult() {
      if (_xdr_field_number(type_) == 23)
        return createManageLimitsRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: createManageLimitsRequestResult accessed when not selected");
    }
    const CreateManageLimitsRequestResult &createManageLimitsRequestResult() const {
      if (_xdr_field_number(type_) == 23)
        return createManageLimitsRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: createManageLimitsRequestResult accessed when not selected");
    }
    ManageContractRequestResult &manageContractRequestResult() {
      if (_xdr_field_number(type_) == 24)
        return manageContractRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageContractRequestResult accessed when not selected");
    }
    const ManageContractRequestResult &manageContractRequestResult() const {
      if (_xdr_field_number(type_) == 24)
        return manageContractRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageContractRequestResult accessed when not selected");
    }
    ManageContractResult &manageContractResult() {
      if (_xdr_field_number(type_) == 25)
        return manageContractResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageContractResult accessed when not selected");
    }
    const ManageContractResult &manageContractResult() const {
      if (_xdr_field_number(type_) == 25)
        return manageContractResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageContractResult accessed when not selected");
    }
    CancelSaleCreationRequestResult &cancelSaleCreationRequestResult() {
      if (_xdr_field_number(type_) == 26)
        return cancelSaleCreationRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: cancelSaleCreationRequestResult accessed when not selected");
    }
    const CancelSaleCreationRequestResult &cancelSaleCreationRequestResult() const {
      if (_xdr_field_number(type_) == 26)
        return cancelSaleCreationRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: cancelSaleCreationRequestResult accessed when not selected");
    }
    CreateAtomicSwapAskRequestResult &createAtomicSwapAskRequestResult() {
      if (_xdr_field_number(type_) == 27)
        return createAtomicSwapAskRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: createAtomicSwapAskRequestResult accessed when not selected");
    }
    const CreateAtomicSwapAskRequestResult &createAtomicSwapAskRequestResult() const {
      if (_xdr_field_number(type_) == 27)
        return createAtomicSwapAskRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: createAtomicSwapAskRequestResult accessed when not selected");
    }
    CancelAtomicSwapAskResult &cancelAtomicSwapAskResult() {
      if (_xdr_field_number(type_) == 28)
        return cancelAtomicSwapAskResult_;
      throw xdr::xdr_wrong_union("_tr_t: cancelAtomicSwapAskResult accessed when not selected");
    }
    const CancelAtomicSwapAskResult &cancelAtomicSwapAskResult() const {
      if (_xdr_field_number(type_) == 28)
        return cancelAtomicSwapAskResult_;
      throw xdr::xdr_wrong_union("_tr_t: cancelAtomicSwapAskResult accessed when not selected");
    }
    CreateAtomicSwapBidRequestResult &createAtomicSwapBidRequestResult() {
      if (_xdr_field_number(type_) == 29)
        return createAtomicSwapBidRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: createAtomicSwapBidRequestResult accessed when not selected");
    }
    const CreateAtomicSwapBidRequestResult &createAtomicSwapBidRequestResult() const {
      if (_xdr_field_number(type_) == 29)
        return createAtomicSwapBidRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: createAtomicSwapBidRequestResult accessed when not selected");
    }
    ManageAccountRoleResult &manageAccountRoleResult() {
      if (_xdr_field_number(type_) == 30)
        return manageAccountRoleResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageAccountRoleResult accessed when not selected");
    }
    const ManageAccountRoleResult &manageAccountRoleResult() const {
      if (_xdr_field_number(type_) == 30)
        return manageAccountRoleResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageAccountRoleResult accessed when not selected");
    }
    ManageAccountRuleResult &manageAccountRuleResult() {
      if (_xdr_field_number(type_) == 31)
        return manageAccountRuleResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageAccountRuleResult accessed when not selected");
    }
    const ManageAccountRuleResult &manageAccountRuleResult() const {
      if (_xdr_field_number(type_) == 31)
        return manageAccountRuleResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageAccountRuleResult accessed when not selected");
    }
    ManageSignerResult &manageSignerResult() {
      if (_xdr_field_number(type_) == 32)
        return manageSignerResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageSignerResult accessed when not selected");
    }
    const ManageSignerResult &manageSignerResult() const {
      if (_xdr_field_number(type_) == 32)
        return manageSignerResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageSignerResult accessed when not selected");
    }
    ManageSignerRoleResult &manageSignerRoleResult() {
      if (_xdr_field_number(type_) == 33)
        return manageSignerRoleResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageSignerRoleResult accessed when not selected");
    }
    const ManageSignerRoleResult &manageSignerRoleResult() const {
      if (_xdr_field_number(type_) == 33)
        return manageSignerRoleResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageSignerRoleResult accessed when not selected");
    }
    ManageSignerRuleResult &manageSignerRuleResult() {
      if (_xdr_field_number(type_) == 34)
        return manageSignerRuleResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageSignerRuleResult accessed when not selected");
    }
    const ManageSignerRuleResult &manageSignerRuleResult() const {
      if (_xdr_field_number(type_) == 34)
        return manageSignerRuleResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageSignerRuleResult accessed when not selected");
    }
    StampResult &stampResult() {
      if (_xdr_field_number(type_) == 35)
        return stampResult_;
      throw xdr::xdr_wrong_union("_tr_t: stampResult accessed when not selected");
    }
    const StampResult &stampResult() const {
      if (_xdr_field_number(type_) == 35)
        return stampResult_;
      throw xdr::xdr_wrong_union("_tr_t: stampResult accessed when not selected");
    }
    LicenseResult &licenseResult() {
      if (_xdr_field_number(type_) == 36)
        return licenseResult_;
      throw xdr::xdr_wrong_union("_tr_t: licenseResult accessed when not selected");
    }
    const LicenseResult &licenseResult() const {
      if (_xdr_field_number(type_) == 36)
        return licenseResult_;
      throw xdr::xdr_wrong_union("_tr_t: licenseResult accessed when not selected");
    }
    ManagePollResult &managePollResult() {
      if (_xdr_field_number(type_) == 37)
        return managePollResult_;
      throw xdr::xdr_wrong_union("_tr_t: managePollResult accessed when not selected");
    }
    const ManagePollResult &managePollResult() const {
      if (_xdr_field_number(type_) == 37)
        return managePollResult_;
      throw xdr::xdr_wrong_union("_tr_t: managePollResult accessed when not selected");
    }
    ManageCreatePollRequestResult &manageCreatePollRequestResult() {
      if (_xdr_field_number(type_) == 38)
        return manageCreatePollRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageCreatePollRequestResult accessed when not selected");
    }
    const ManageCreatePollRequestResult &manageCreatePollRequestResult() const {
      if (_xdr_field_number(type_) == 38)
        return manageCreatePollRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageCreatePollRequestResult accessed when not selected");
    }
    ManageVoteResult &manageVoteResult() {
      if (_xdr_field_number(type_) == 39)
        return manageVoteResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageVoteResult accessed when not selected");
    }
    const ManageVoteResult &manageVoteResult() const {
      if (_xdr_field_number(type_) == 39)
        return manageVoteResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageVoteResult accessed when not selected");
    }
    ManageAccountSpecificRuleResult &manageAccountSpecificRuleResult() {
      if (_xdr_field_number(type_) == 40)
        return manageAccountSpecificRuleResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageAccountSpecificRuleResult accessed when not selected");
    }
    const ManageAccountSpecificRuleResult &manageAccountSpecificRuleResult() const {
      if (_xdr_field_number(type_) == 40)
        return manageAccountSpecificRuleResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageAccountSpecificRuleResult accessed when not selected");
    }
    CancelChangeRoleRequestResult &cancelChangeRoleRequestResult() {
      if (_xdr_field_number(type_) == 41)
        return cancelChangeRoleRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: cancelChangeRoleRequestResult accessed when not selected");
    }
    const CancelChangeRoleRequestResult &cancelChangeRoleRequestResult() const {
      if (_xdr_field_number(type_) == 41)
        return cancelChangeRoleRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: cancelChangeRoleRequestResult accessed when not selected");
    }
    RemoveAssetPairResult &removeAssetPairResult() {
      if (_xdr_field_number(type_) == 42)
        return removeAssetPairResult_;
      throw xdr::xdr_wrong_union("_tr_t: removeAssetPairResult accessed when not selected");
    }
    const RemoveAssetPairResult &removeAssetPairResult() const {
      if (_xdr_field_number(type_) == 42)
        return removeAssetPairResult_;
      throw xdr::xdr_wrong_union("_tr_t: removeAssetPairResult accessed when not selected");
    }
    CreateKYCRecoveryRequestResult &createKYCRecoveryRequestResult() {
      if (_xdr_field_number(type_) == 43)
        return createKYCRecoveryRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: createKYCRecoveryRequestResult accessed when not selected");
    }
    const CreateKYCRecoveryRequestResult &createKYCRecoveryRequestResult() const {
      if (_xdr_field_number(type_) == 43)
        return createKYCRecoveryRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: createKYCRecoveryRequestResult accessed when not selected");
    }
    InitiateKYCRecoveryResult &initiateKYCRecoveryResult() {
      if (_xdr_field_number(type_) == 44)
        return initiateKYCRecoveryResult_;
      throw xdr::xdr_wrong_union("_tr_t: initiateKYCRecoveryResult accessed when not selected");
    }
    const InitiateKYCRecoveryResult &initiateKYCRecoveryResult() const {
      if (_xdr_field_number(type_) == 44)
        return initiateKYCRecoveryResult_;
      throw xdr::xdr_wrong_union("_tr_t: initiateKYCRecoveryResult accessed when not selected");
    }
    CreateManageOfferRequestResult &createManageOfferRequestResult() {
      if (_xdr_field_number(type_) == 45)
        return createManageOfferRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: createManageOfferRequestResult accessed when not selected");
    }
    const CreateManageOfferRequestResult &createManageOfferRequestResult() const {
      if (_xdr_field_number(type_) == 45)
        return createManageOfferRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: createManageOfferRequestResult accessed when not selected");
    }
    CreatePaymentRequestResult &createPaymentRequestResult() {
      if (_xdr_field_number(type_) == 46)
        return createPaymentRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: createPaymentRequestResult accessed when not selected");
    }
    const CreatePaymentRequestResult &createPaymentRequestResult() const {
      if (_xdr_field_number(type_) == 46)
        return createPaymentRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: createPaymentRequestResult accessed when not selected");
    }
    RemoveAssetResult &removeAssetResult() {
      if (_xdr_field_number(type_) == 47)
        return removeAssetResult_;
      throw xdr::xdr_wrong_union("_tr_t: removeAssetResult accessed when not selected");
    }
    const RemoveAssetResult &removeAssetResult() const {
      if (_xdr_field_number(type_) == 47)
        return removeAssetResult_;
      throw xdr::xdr_wrong_union("_tr_t: removeAssetResult accessed when not selected");
    }
    OpenSwapResult &openSwapResult() {
      if (_xdr_field_number(type_) == 48)
        return openSwapResult_;
      throw xdr::xdr_wrong_union("_tr_t: openSwapResult accessed when not selected");
    }
    const OpenSwapResult &openSwapResult() const {
      if (_xdr_field_number(type_) == 48)
        return openSwapResult_;
      throw xdr::xdr_wrong_union("_tr_t: openSwapResult accessed when not selected");
    }
    CloseSwapResult &closeSwapResult() {
      if (_xdr_field_number(type_) == 49)
        return closeSwapResult_;
      throw xdr::xdr_wrong_union("_tr_t: closeSwapResult accessed when not selected");
    }
    const CloseSwapResult &closeSwapResult() const {
      if (_xdr_field_number(type_) == 49)
        return closeSwapResult_;
      throw xdr::xdr_wrong_union("_tr_t: closeSwapResult accessed when not selected");
    }
    CreateRedemptionRequestResult &createRedemptionRequestResult() {
      if (_xdr_field_number(type_) == 50)
        return createRedemptionRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: createRedemptionRequestResult accessed when not selected");
    }
    const CreateRedemptionRequestResult &createRedemptionRequestResult() const {
      if (_xdr_field_number(type_) == 50)
        return createRedemptionRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: createRedemptionRequestResult accessed when not selected");
    }
    CreateDataResult &createDataResult() {
      if (_xdr_field_number(type_) == 51)
        return createDataResult_;
      throw xdr::xdr_wrong_union("_tr_t: createDataResult accessed when not selected");
    }
    const CreateDataResult &createDataResult() const {
      if (_xdr_field_number(type_) == 51)
        return createDataResult_;
      throw xdr::xdr_wrong_union("_tr_t: createDataResult accessed when not selected");
    }
    UpdateDataResult &updateDataResult() {
      if (_xdr_field_number(type_) == 52)
        return updateDataResult_;
      throw xdr::xdr_wrong_union("_tr_t: updateDataResult accessed when not selected");
    }
    const UpdateDataResult &updateDataResult() const {
      if (_xdr_field_number(type_) == 52)
        return updateDataResult_;
      throw xdr::xdr_wrong_union("_tr_t: updateDataResult accessed when not selected");
    }
    RemoveDataResult &removeDataResult() {
      if (_xdr_field_number(type_) == 53)
        return removeDataResult_;
      throw xdr::xdr_wrong_union("_tr_t: removeDataResult accessed when not selected");
    }
    const RemoveDataResult &removeDataResult() const {
      if (_xdr_field_number(type_) == 53)
        return removeDataResult_;
      throw xdr::xdr_wrong_union("_tr_t: removeDataResult accessed when not selected");
    }
    CreateDataRequestResult &createDataRequestResult() {
      if (_xdr_field_number(type_) == 54)
        return createDataRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: createDataRequestResult accessed when not selected");
    }
    const CreateDataRequestResult &createDataRequestResult() const {
      if (_xdr_field_number(type_) == 54)
        return createDataRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: createDataRequestResult accessed when not selected");
    }
    CreateDataCreationRequestResult &CreateDataCreationRequestResult() {
      if (_xdr_field_number(type_) == 55)
        return CreateDataCreationRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: CreateDataCreationRequestResult accessed when not selected");
    }
    const CreateDataCreationRequestResult &CreateDataCreationRequestResult() const {
      if (_xdr_field_number(type_) == 55)
        return CreateDataCreationRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: CreateDataCreationRequestResult accessed when not selected");
    }
    CancelDataCreationRequestResult &CancelDataCreationRequestResult() {
      if (_xdr_field_number(type_) == 56)
        return CancelDataCreationRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: CancelDataCreationRequestResult accessed when not selected");
    }
    const CancelDataCreationRequestResult &CancelDataCreationRequestResult() const {
      if (_xdr_field_number(type_) == 56)
        return CancelDataCreationRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: CancelDataCreationRequestResult accessed when not selected");
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

  using _xdr_case_type = xdr::xdr_traits<OperationResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    _tr_t tr_;
    LedgerEntryType entryType_;
    AccountRuleRequirement requirement_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<OperationResultCode> &_xdr_case_values() {
    static const std::vector<OperationResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)OperationResultCode::opINNER ? 1
      : which == (int32_t)OperationResultCode::opNO_ENTRY ? 2
      : which == (int32_t)OperationResultCode::opNO_ROLE_PERMISSION ? 3
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)OperationResultCode::opINNER:
      _f(&OperationResult::tr_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)OperationResultCode::opNO_ENTRY:
      _f(&OperationResult::entryType_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)OperationResultCode::opNO_ROLE_PERMISSION:
      _f(&OperationResult::requirement_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in OperationResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~OperationResult();
      code_ = which;switch (code_)
{
      case (int32_t)OperationResultCode::opINNER:
new(&tr_) _tr_t{};
break;
      case (int32_t)OperationResultCode::opNO_ENTRY:
new(&entryType_) LedgerEntryType{};
break;
      case (int32_t)OperationResultCode::opNO_ROLE_PERMISSION:
new(&requirement_) AccountRuleRequirement{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit OperationResult(OperationResultCode which = OperationResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)OperationResultCode::opINNER:
new(&tr_) _tr_t{};
break;
    case (int32_t)OperationResultCode::opNO_ENTRY:
new(&entryType_) LedgerEntryType{};
break;
    case (int32_t)OperationResultCode::opNO_ROLE_PERMISSION:
new(&requirement_) AccountRuleRequirement{};
break;
    default:
      break;
}

  }
  OperationResult(const OperationResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)OperationResultCode::opINNER:
new(&tr_) _tr_t(source.tr_);
break;
    case (int32_t)OperationResultCode::opNO_ENTRY:
new(&entryType_) LedgerEntryType(source.entryType_);
break;
    case (int32_t)OperationResultCode::opNO_ROLE_PERMISSION:
new(&requirement_) AccountRuleRequirement(source.requirement_);
break;
    default:
      break;
}

  }
  OperationResult(OperationResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)OperationResultCode::opINNER:
new(&tr_) _tr_t(std::move(source.tr_));
break;
    case (int32_t)OperationResultCode::opNO_ENTRY:
new(&entryType_) LedgerEntryType(std::move(source.entryType_));
break;
    case (int32_t)OperationResultCode::opNO_ROLE_PERMISSION:
new(&requirement_) AccountRuleRequirement(std::move(source.requirement_));
break;
    default:
      break;
}

  }
  ~OperationResult() {
switch (code_)
{
  case (int32_t)OperationResultCode::opINNER:
tr_.~_tr_t();
break;
  case (int32_t)OperationResultCode::opNO_ENTRY:
entryType_.~LedgerEntryType();
break;
  case (int32_t)OperationResultCode::opNO_ROLE_PERMISSION:
requirement_.~AccountRuleRequirement();
break;
  default:
    break;
}
}

  OperationResult &operator=(const OperationResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)OperationResultCode::opINNER:
tr_ = source.tr_;
break;
    case (int32_t)OperationResultCode::opNO_ENTRY:
entryType_ = source.entryType_;
break;
    case (int32_t)OperationResultCode::opNO_ROLE_PERMISSION:
requirement_ = source.requirement_;
break;
    default:
      break;
}
}
else {this->~OperationResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)OperationResultCode::opINNER:
new(&tr_) _tr_t(source.tr_);
break;
    case (int32_t)OperationResultCode::opNO_ENTRY:
new(&entryType_) LedgerEntryType(source.entryType_);
break;
    case (int32_t)OperationResultCode::opNO_ROLE_PERMISSION:
new(&requirement_) AccountRuleRequirement(source.requirement_);
break;
    default:
      break;
}
}
    return *this;
  }
  OperationResult &operator=(OperationResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)OperationResultCode::opINNER:
tr_ = std::move(source.tr_);
break;
    case (int32_t)OperationResultCode::opNO_ENTRY:
entryType_ = std::move(source.entryType_);
break;
    case (int32_t)OperationResultCode::opNO_ROLE_PERMISSION:
requirement_ = std::move(source.requirement_);
break;
    default:
      break;
}
}
else {this->~OperationResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)OperationResultCode::opINNER:
new(&tr_) _tr_t(std::move(source.tr_));
break;
    case (int32_t)OperationResultCode::opNO_ENTRY:
new(&entryType_) LedgerEntryType(std::move(source.entryType_));
break;
    case (int32_t)OperationResultCode::opNO_ROLE_PERMISSION:
new(&requirement_) AccountRuleRequirement(std::move(source.requirement_));
break;
    default:
      break;
}
}
    return *this;
  }

  OperationResultCode code() const { return OperationResultCode(code_); }
  OperationResult &code(OperationResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  _tr_t &tr() {
    if (_xdr_field_number(code_) == 1)
      return tr_;
    throw xdr::xdr_wrong_union("OperationResult: tr accessed when not selected");
  }
  const _tr_t &tr() const {
    if (_xdr_field_number(code_) == 1)
      return tr_;
    throw xdr::xdr_wrong_union("OperationResult: tr accessed when not selected");
  }
  LedgerEntryType &entryType() {
    if (_xdr_field_number(code_) == 2)
      return entryType_;
    throw xdr::xdr_wrong_union("OperationResult: entryType accessed when not selected");
  }
  const LedgerEntryType &entryType() const {
    if (_xdr_field_number(code_) == 2)
      return entryType_;
    throw xdr::xdr_wrong_union("OperationResult: entryType accessed when not selected");
  }
  AccountRuleRequirement &requirement() {
    if (_xdr_field_number(code_) == 3)
      return requirement_;
    throw xdr::xdr_wrong_union("OperationResult: requirement accessed when not selected");
  }
  const AccountRuleRequirement &requirement() const {
    if (_xdr_field_number(code_) == 3)
      return requirement_;
    throw xdr::xdr_wrong_union("OperationResult: requirement accessed when not selected");
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

enum class TransactionResultCode : std::int32_t {
  txSUCCESS = 0,
  txFAILED = -1,
  txTOO_EARLY = -2,
  txTOO_LATE = -3,
  txMISSING_OPERATION = -4,
  txBAD_AUTH = -5,
  txNO_ACCOUNT = -6,
  txBAD_AUTH_EXTRA = -7,
  txINTERNAL_ERROR = -8,
  txACCOUNT_BLOCKED = -9,
  txDUPLICATION = -10,
  txINSUFFICIENT_FEE = -11,
  txSOURCE_UNDERFUNDED = -12,
  txCOMMISSION_LINE_FULL = -13,
  txFEE_INCORRECT_PRECISION = -14,
  txNO_ROLE_PERMISSION = -15,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TransactionResultCode>
  : xdr_integral_base<::stellar::TransactionResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::TransactionResultCode val) {
    switch (val) {
    case ::stellar::TransactionResultCode::txSUCCESS:
      return "txSUCCESS";
    case ::stellar::TransactionResultCode::txFAILED:
      return "txFAILED";
    case ::stellar::TransactionResultCode::txTOO_EARLY:
      return "txTOO_EARLY";
    case ::stellar::TransactionResultCode::txTOO_LATE:
      return "txTOO_LATE";
    case ::stellar::TransactionResultCode::txMISSING_OPERATION:
      return "txMISSING_OPERATION";
    case ::stellar::TransactionResultCode::txBAD_AUTH:
      return "txBAD_AUTH";
    case ::stellar::TransactionResultCode::txNO_ACCOUNT:
      return "txNO_ACCOUNT";
    case ::stellar::TransactionResultCode::txBAD_AUTH_EXTRA:
      return "txBAD_AUTH_EXTRA";
    case ::stellar::TransactionResultCode::txINTERNAL_ERROR:
      return "txINTERNAL_ERROR";
    case ::stellar::TransactionResultCode::txACCOUNT_BLOCKED:
      return "txACCOUNT_BLOCKED";
    case ::stellar::TransactionResultCode::txDUPLICATION:
      return "txDUPLICATION";
    case ::stellar::TransactionResultCode::txINSUFFICIENT_FEE:
      return "txINSUFFICIENT_FEE";
    case ::stellar::TransactionResultCode::txSOURCE_UNDERFUNDED:
      return "txSOURCE_UNDERFUNDED";
    case ::stellar::TransactionResultCode::txCOMMISSION_LINE_FULL:
      return "txCOMMISSION_LINE_FULL";
    case ::stellar::TransactionResultCode::txFEE_INCORRECT_PRECISION:
      return "txFEE_INCORRECT_PRECISION";
    case ::stellar::TransactionResultCode::txNO_ROLE_PERMISSION:
      return "txNO_ROLE_PERMISSION";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::TransactionResultCode::txSUCCESS,
      (int32_t)::stellar::TransactionResultCode::txFAILED,
      (int32_t)::stellar::TransactionResultCode::txTOO_EARLY,
      (int32_t)::stellar::TransactionResultCode::txTOO_LATE,
      (int32_t)::stellar::TransactionResultCode::txMISSING_OPERATION,
      (int32_t)::stellar::TransactionResultCode::txBAD_AUTH,
      (int32_t)::stellar::TransactionResultCode::txNO_ACCOUNT,
      (int32_t)::stellar::TransactionResultCode::txBAD_AUTH_EXTRA,
      (int32_t)::stellar::TransactionResultCode::txINTERNAL_ERROR,
      (int32_t)::stellar::TransactionResultCode::txACCOUNT_BLOCKED,
      (int32_t)::stellar::TransactionResultCode::txDUPLICATION,
      (int32_t)::stellar::TransactionResultCode::txINSUFFICIENT_FEE,
      (int32_t)::stellar::TransactionResultCode::txSOURCE_UNDERFUNDED,
      (int32_t)::stellar::TransactionResultCode::txCOMMISSION_LINE_FULL,
      (int32_t)::stellar::TransactionResultCode::txFEE_INCORRECT_PRECISION,
      (int32_t)::stellar::TransactionResultCode::txNO_ROLE_PERMISSION
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct OperationFee  : xdr::xdr_abstract {
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

  OperationType operationType{};
  uint64 amount{};
  _ext_t ext{};

  OperationFee() = default;
  template<typename _operationType_T,
           typename _amount_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<OperationType, _operationType_T>::value
                          && std::is_constructible<uint64, _amount_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit OperationFee(_operationType_T &&_operationType,
                        _amount_T &&_amount,
                        _ext_T &&_ext)
    : operationType(std::forward<_operationType_T>(_operationType)),
      amount(std::forward<_amount_T>(_amount)),
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

struct TransactionResult  : xdr::xdr_abstract {
  struct _result_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<TransactionResultCode>::case_type;
  private:
    _xdr_case_type code_;
    union {
      xdr::xvector<OperationResult> results_;
      AccountRuleRequirement requirement_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = true;
    static const std::vector<TransactionResultCode> &_xdr_case_values() {
      static const std::vector<TransactionResultCode> _xdr_disc_vec {};
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)TransactionResultCode::txSUCCESS || which == (int32_t)TransactionResultCode::txFAILED ? 1
        : which == (int32_t)TransactionResultCode::txNO_ROLE_PERMISSION ? 2
        : 0;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)TransactionResultCode::txSUCCESS:
      case (int32_t)TransactionResultCode::txFAILED:
        _f(&_result_t::results_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)TransactionResultCode::txNO_ROLE_PERMISSION:
        _f(&_result_t::requirement_, std::forward<_A>(_a)...);
        return true;
      default:
        return true;
      }
    }

    _xdr_case_type _xdr_discriminant() const { return code_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of code in _result_t");
      if (fnum != _xdr_field_number(code_)) {
        this->~_result_t();
        code_ = which;switch (code_)
{
        case (int32_t)TransactionResultCode::txSUCCESS:
        case (int32_t)TransactionResultCode::txFAILED:
new(&results_) xdr::xvector<OperationResult>{};
break;
        case (int32_t)TransactionResultCode::txNO_ROLE_PERMISSION:
new(&requirement_) AccountRuleRequirement{};
break;
        default:
          break;
}

      }
      else
        code_ = which;
    }
    explicit _result_t(TransactionResultCode which = TransactionResultCode{}) : code_((int32_t)which) {
      switch (code_)
{
      case (int32_t)TransactionResultCode::txSUCCESS:
      case (int32_t)TransactionResultCode::txFAILED:
new(&results_) xdr::xvector<OperationResult>{};
break;
      case (int32_t)TransactionResultCode::txNO_ROLE_PERMISSION:
new(&requirement_) AccountRuleRequirement{};
break;
      default:
        break;
}

    }
    _result_t(const _result_t &source) : code_(source.code_) {
      switch (code_)
{
      case (int32_t)TransactionResultCode::txSUCCESS:
      case (int32_t)TransactionResultCode::txFAILED:
new(&results_) xdr::xvector<OperationResult>(source.results_);
break;
      case (int32_t)TransactionResultCode::txNO_ROLE_PERMISSION:
new(&requirement_) AccountRuleRequirement(source.requirement_);
break;
      default:
        break;
}

    }
    _result_t(_result_t &&source) : code_(source.code_) {
      switch (code_)
{
      case (int32_t)TransactionResultCode::txSUCCESS:
      case (int32_t)TransactionResultCode::txFAILED:
new(&results_) xdr::xvector<OperationResult>(std::move(source.results_));
break;
      case (int32_t)TransactionResultCode::txNO_ROLE_PERMISSION:
new(&requirement_) AccountRuleRequirement(std::move(source.requirement_));
break;
      default:
        break;
}

    }
    ~_result_t() {
switch (code_)
{
    case (int32_t)TransactionResultCode::txSUCCESS:
    case (int32_t)TransactionResultCode::txFAILED:
results_.~xvector<OperationResult>();
break;
    case (int32_t)TransactionResultCode::txNO_ROLE_PERMISSION:
requirement_.~AccountRuleRequirement();
break;
    default:
      break;
}
}

    _result_t &operator=(const _result_t &source) {
      if (code_ == source.code_)
{
switch (code_)
{
      case (int32_t)TransactionResultCode::txSUCCESS:
      case (int32_t)TransactionResultCode::txFAILED:
results_ = source.results_;
break;
      case (int32_t)TransactionResultCode::txNO_ROLE_PERMISSION:
requirement_ = source.requirement_;
break;
      default:
        break;
}
}
else {this->~_result_t();
      code_ = source.code_;
switch (code_)
{
      case (int32_t)TransactionResultCode::txSUCCESS:
      case (int32_t)TransactionResultCode::txFAILED:
new(&results_) xdr::xvector<OperationResult>(source.results_);
break;
      case (int32_t)TransactionResultCode::txNO_ROLE_PERMISSION:
new(&requirement_) AccountRuleRequirement(source.requirement_);
break;
      default:
        break;
}
}
      return *this;
    }
    _result_t &operator=(_result_t &&source) {
      if (code_ == source.code_)
{
switch (code_)
{
      case (int32_t)TransactionResultCode::txSUCCESS:
      case (int32_t)TransactionResultCode::txFAILED:
results_ = std::move(source.results_);
break;
      case (int32_t)TransactionResultCode::txNO_ROLE_PERMISSION:
requirement_ = std::move(source.requirement_);
break;
      default:
        break;
}
}
else {this->~_result_t();
      code_ = std::move(source.code_);
switch (code_)
{
      case (int32_t)TransactionResultCode::txSUCCESS:
      case (int32_t)TransactionResultCode::txFAILED:
new(&results_) xdr::xvector<OperationResult>(std::move(source.results_));
break;
      case (int32_t)TransactionResultCode::txNO_ROLE_PERMISSION:
new(&requirement_) AccountRuleRequirement(std::move(source.requirement_));
break;
      default:
        break;
}
}
      return *this;
    }

    TransactionResultCode code() const { return TransactionResultCode(code_); }
    _result_t &code(TransactionResultCode _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    xdr::xvector<OperationResult> &results() {
      if (_xdr_field_number(code_) == 1)
        return results_;
      throw xdr::xdr_wrong_union("_result_t: results accessed when not selected");
    }
    const xdr::xvector<OperationResult> &results() const {
      if (_xdr_field_number(code_) == 1)
        return results_;
      throw xdr::xdr_wrong_union("_result_t: results accessed when not selected");
    }
    AccountRuleRequirement &requirement() {
      if (_xdr_field_number(code_) == 2)
        return requirement_;
      throw xdr::xdr_wrong_union("_result_t: requirement accessed when not selected");
    }
    const AccountRuleRequirement &requirement() const {
      if (_xdr_field_number(code_) == 2)
        return requirement_;
      throw xdr::xdr_wrong_union("_result_t: requirement accessed when not selected");
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

  int64 feeCharged{};
  _result_t result{};
  _ext_t ext{};

  TransactionResult() = default;
  template<typename _feeCharged_T,
           typename _result_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<int64, _feeCharged_T>::value
                          && std::is_constructible<_result_t, _result_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit TransactionResult(_feeCharged_T &&_feeCharged,
                             _result_T &&_result,
                             _ext_T &&_ext)
    : feeCharged(std::forward<_feeCharged_T>(_feeCharged)),
      result(std::forward<_result_T>(_result)),
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

#endif // !__XDR_TRANSACTION_H_INCLUDED__
