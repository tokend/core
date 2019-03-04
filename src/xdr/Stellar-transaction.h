// -*- C++ -*-
// Automatically generated from Stellar-transaction.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_TRANSACTION_H_INCLUDED__
#define __XDR_STELLAR_TRANSACTION_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-ledger-entries.h"
#include "xdr/Stellar-operation-create-account.h"
#include "xdr/Stellar-operation-set-fees.h"
#include "xdr/Stellar-operation-create-withdrawal-request.h"
#include "xdr/Stellar-operation-manage-balance.h"
#include "xdr/Stellar-operation-manage-asset.h"
#include "xdr/Stellar-operation-create-preissuance-request.h"
#include "xdr/Stellar-operation-create-issuance-request.h"
#include "xdr/Stellar-operation-manage-limits.h"
#include "xdr/Stellar-operation-manage-asset-pair.h"
#include "xdr/Stellar-operation-manage-offer.h"
#include "xdr/Stellar-operation-manage-invoice-request.h"
#include "xdr/Stellar-operation-review-request.h"
#include "xdr/Stellar-operation-create-sale-creation-request.h"
#include "xdr/Stellar-operation-cancel-sale-creation-request.h"
#include "xdr/Stellar-operation-check-sale-state.h"
#include "xdr/Stellar-operation-payout.h"
#include "xdr/Stellar-operation-create-AML-alert-request.h"
#include "xdr/Stellar-operation-manage-key-value.h"
#include "xdr/Stellar-operation-create-change-role-request.h"
#include "xdr/Stellar-operation-manage-external-system-id-pool-entry.h"
#include "xdr/Stellar-operation-bind-external-system-id.h"
#include "xdr/Stellar-operation-payment.h"
#include "xdr/Stellar-operation-manage-sale.h"
#include "xdr/Stellar-operation-create-manage-limits-request.h"
#include "xdr/Stellar-operation-manage-contract.h"
#include "xdr/Stellar-operation-manage-contract-request.h"
#include "xdr/Stellar-operation-create-aswap-bid-creation-request.h"
#include "xdr/Stellar-operation-cancel-atomic-swap-bid.h"
#include "xdr/Stellar-operation-create-aswap-request.h"
#include "xdr/Stellar-operation-manage-account-role.h"
#include "xdr/Stellar-operation-manage-account-rule.h"
#include "xdr/Stellar-operation-manage-signer-role.h"
#include "xdr/Stellar-operation-manage-signer-rule.h"
#include "xdr/Stellar-operation-manage-signer.h"
#include "xdr/Stellar-operation-license.h"
#include "xdr/Stellar-operation-stamp.h"

namespace stellar {

struct Operation {
  struct _body_t {
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
      CreateASwapBidCreationRequestOp createASwapBidCreationRequestOp_;
      CancelASwapBidOp cancelASwapBidOp_;
      CreateASwapRequestOp createASwapRequestOp_;
      ManageAccountRoleOp manageAccountRoleOp_;
      ManageAccountRuleOp manageAccountRuleOp_;
      ManageSignerOp manageSignerOp_;
      ManageSignerRoleOp manageSignerRoleOp_;
      ManageSignerRuleOp manageSignerRuleOp_;
      StampOp stampOp_;
      LicenseOp licenseOp_;
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
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
        OperationType::CREATE_ASWAP_BID_REQUEST,
        OperationType::CANCEL_ASWAP_BID,
        OperationType::CREATE_ASWAP_REQUEST,
        OperationType::MANAGE_ACCOUNT_ROLE,
        OperationType::MANAGE_ACCOUNT_RULE,
        OperationType::MANAGE_SIGNER,
        OperationType::MANAGE_SIGNER_ROLE,
        OperationType::MANAGE_SIGNER_RULE,
        OperationType::STAMP,
        OperationType::LICENSE
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
        : which == (int32_t)OperationType::CREATE_ASWAP_BID_REQUEST ? 27
        : which == (int32_t)OperationType::CANCEL_ASWAP_BID ? 28
        : which == (int32_t)OperationType::CREATE_ASWAP_REQUEST ? 29
        : which == (int32_t)OperationType::MANAGE_ACCOUNT_ROLE ? 30
        : which == (int32_t)OperationType::MANAGE_ACCOUNT_RULE ? 31
        : which == (int32_t)OperationType::MANAGE_SIGNER ? 32
        : which == (int32_t)OperationType::MANAGE_SIGNER_ROLE ? 33
        : which == (int32_t)OperationType::MANAGE_SIGNER_RULE ? 34
        : which == (int32_t)OperationType::STAMP ? 35
        : which == (int32_t)OperationType::LICENSE ? 36
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
      case (int32_t)OperationType::CREATE_ASWAP_BID_REQUEST:
        _f(&_body_t::createASwapBidCreationRequestOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CANCEL_ASWAP_BID:
        _f(&_body_t::cancelASwapBidOp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CREATE_ASWAP_REQUEST:
        _f(&_body_t::createASwapRequestOp_, std::forward<_A>(_a)...);
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
    explicit _body_t(OperationType which = OperationType{}) : type_((int32_t)which) {
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
    CreateASwapBidCreationRequestOp &createASwapBidCreationRequestOp() {
      if (_xdr_field_number(type_) == 27)
        return createASwapBidCreationRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: createASwapBidCreationRequestOp accessed when not selected");
    }
    const CreateASwapBidCreationRequestOp &createASwapBidCreationRequestOp() const {
      if (_xdr_field_number(type_) == 27)
        return createASwapBidCreationRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: createASwapBidCreationRequestOp accessed when not selected");
    }
    CancelASwapBidOp &cancelASwapBidOp() {
      if (_xdr_field_number(type_) == 28)
        return cancelASwapBidOp_;
      throw xdr::xdr_wrong_union("_body_t: cancelASwapBidOp accessed when not selected");
    }
    const CancelASwapBidOp &cancelASwapBidOp() const {
      if (_xdr_field_number(type_) == 28)
        return cancelASwapBidOp_;
      throw xdr::xdr_wrong_union("_body_t: cancelASwapBidOp accessed when not selected");
    }
    CreateASwapRequestOp &createASwapRequestOp() {
      if (_xdr_field_number(type_) == 29)
        return createASwapRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: createASwapRequestOp accessed when not selected");
    }
    const CreateASwapRequestOp &createASwapRequestOp() const {
      if (_xdr_field_number(type_) == 29)
        return createASwapRequestOp_;
      throw xdr::xdr_wrong_union("_body_t: createASwapRequestOp accessed when not selected");
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::Operation::_body_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::Operation::_body_t;
  using case_type = ::stellar::Operation::_body_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "createAccountOp";
    case 2:
      return "createIssuanceRequestOp";
    case 3:
      return "setFeesOp";
    case 4:
      return "createWithdrawalRequestOp";
    case 5:
      return "manageBalanceOp";
    case 6:
      return "manageAssetOp";
    case 7:
      return "createPreIssuanceRequest";
    case 8:
      return "manageLimitsOp";
    case 9:
      return "manageAssetPairOp";
    case 10:
      return "manageOfferOp";
    case 11:
      return "manageInvoiceRequestOp";
    case 12:
      return "reviewRequestOp";
    case 13:
      return "createSaleCreationRequestOp";
    case 14:
      return "checkSaleStateOp";
    case 15:
      return "payoutOp";
    case 16:
      return "createAMLAlertRequestOp";
    case 17:
      return "manageKeyValueOp";
    case 18:
      return "createChangeRoleRequestOp";
    case 19:
      return "manageExternalSystemAccountIdPoolEntryOp";
    case 20:
      return "bindExternalSystemAccountIdOp";
    case 21:
      return "paymentOp";
    case 22:
      return "manageSaleOp";
    case 23:
      return "createManageLimitsRequestOp";
    case 24:
      return "manageContractRequestOp";
    case 25:
      return "manageContractOp";
    case 26:
      return "cancelSaleCreationRequestOp";
    case 27:
      return "createASwapBidCreationRequestOp";
    case 28:
      return "cancelASwapBidOp";
    case 29:
      return "createASwapRequestOp";
    case 30:
      return "manageAccountRoleOp";
    case 31:
      return "manageAccountRuleOp";
    case 32:
      return "manageSignerOp";
    case 33:
      return "manageSignerRoleOp";
    case 34:
      return "manageSignerRuleOp";
    case 35:
      return "stampOp";
    case 36:
      return "licenseOp";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::Operation::_body_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in _body_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::Operation::_body_t &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in _body_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::Operation::_body_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.type(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::Operation>
  : xdr_struct_base<field_ptr<::stellar::Operation,
                              decltype(::stellar::Operation::sourceAccount),
                              &::stellar::Operation::sourceAccount>,
                    field_ptr<::stellar::Operation,
                              decltype(::stellar::Operation::body),
                              &::stellar::Operation::body>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::Operation &obj) {
    archive(ar, obj.sourceAccount, "sourceAccount");
    archive(ar, obj.body, "body");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::Operation &obj) {
    archive(ar, obj.sourceAccount, "sourceAccount");
    archive(ar, obj.body, "body");
    xdr::validate(obj);
  }
};
} namespace stellar {

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
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
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

struct Memo {
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
  static Constexpr const bool _xdr_has_default_case = false;
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
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
      type_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    else
      type_ = which;
  }
  explicit Memo(MemoType which = MemoType{}) : type_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
  }
  Memo(const Memo &source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
  }
  Memo(Memo &&source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                      std::move(source));
  }
  ~Memo() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
  Memo &operator=(const Memo &source) {
    if (_xdr_field_number(type_)
        == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
    else {
      this->~Memo();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
    }
    type_ = source.type_;
    return *this;
  }
  Memo &operator=(Memo &&source) {
    if (_xdr_field_number(type_)
         == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                        std::move(source));
    else {
      this->~Memo();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                        std::move(source));
    }
    type_ = source.type_;
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
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::Memo> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::Memo;
  using case_type = ::stellar::Memo::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "text";
    case 2:
      return "id";
    case 3:
      return "hash";
    case 4:
      return "retHash";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::Memo &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in Memo");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::Memo &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in Memo");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::Memo &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.type(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
} namespace stellar {

struct TimeBounds {
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TimeBounds>
  : xdr_struct_base<field_ptr<::stellar::TimeBounds,
                              decltype(::stellar::TimeBounds::minTime),
                              &::stellar::TimeBounds::minTime>,
                    field_ptr<::stellar::TimeBounds,
                              decltype(::stellar::TimeBounds::maxTime),
                              &::stellar::TimeBounds::maxTime>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TimeBounds &obj) {
    archive(ar, obj.minTime, "minTime");
    archive(ar, obj.maxTime, "maxTime");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TimeBounds &obj) {
    archive(ar, obj.minTime, "minTime");
    archive(ar, obj.maxTime, "maxTime");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct Transaction {
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::Transaction::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::Transaction::_ext_t;
  using case_type = ::stellar::Transaction::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::Transaction::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::Transaction::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::Transaction::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::Transaction>
  : xdr_struct_base<field_ptr<::stellar::Transaction,
                              decltype(::stellar::Transaction::sourceAccount),
                              &::stellar::Transaction::sourceAccount>,
                    field_ptr<::stellar::Transaction,
                              decltype(::stellar::Transaction::salt),
                              &::stellar::Transaction::salt>,
                    field_ptr<::stellar::Transaction,
                              decltype(::stellar::Transaction::timeBounds),
                              &::stellar::Transaction::timeBounds>,
                    field_ptr<::stellar::Transaction,
                              decltype(::stellar::Transaction::memo),
                              &::stellar::Transaction::memo>,
                    field_ptr<::stellar::Transaction,
                              decltype(::stellar::Transaction::operations),
                              &::stellar::Transaction::operations>,
                    field_ptr<::stellar::Transaction,
                              decltype(::stellar::Transaction::ext),
                              &::stellar::Transaction::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::Transaction &obj) {
    archive(ar, obj.sourceAccount, "sourceAccount");
    archive(ar, obj.salt, "salt");
    archive(ar, obj.timeBounds, "timeBounds");
    archive(ar, obj.memo, "memo");
    archive(ar, obj.operations, "operations");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::Transaction &obj) {
    archive(ar, obj.sourceAccount, "sourceAccount");
    archive(ar, obj.salt, "salt");
    archive(ar, obj.timeBounds, "timeBounds");
    archive(ar, obj.memo, "memo");
    archive(ar, obj.operations, "operations");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct TransactionEnvelope {
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TransactionEnvelope>
  : xdr_struct_base<field_ptr<::stellar::TransactionEnvelope,
                              decltype(::stellar::TransactionEnvelope::tx),
                              &::stellar::TransactionEnvelope::tx>,
                    field_ptr<::stellar::TransactionEnvelope,
                              decltype(::stellar::TransactionEnvelope::signatures),
                              &::stellar::TransactionEnvelope::signatures>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionEnvelope &obj) {
    archive(ar, obj.tx, "tx");
    archive(ar, obj.signatures, "signatures");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionEnvelope &obj) {
    archive(ar, obj.tx, "tx");
    archive(ar, obj.signatures, "signatures");
    xdr::validate(obj);
  }
};
} namespace stellar {

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
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
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

struct AccountRuleRequirement {
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::AccountRuleRequirement>
  : xdr_struct_base<field_ptr<::stellar::AccountRuleRequirement,
                              decltype(::stellar::AccountRuleRequirement::resource),
                              &::stellar::AccountRuleRequirement::resource>,
                    field_ptr<::stellar::AccountRuleRequirement,
                              decltype(::stellar::AccountRuleRequirement::action),
                              &::stellar::AccountRuleRequirement::action>,
                    field_ptr<::stellar::AccountRuleRequirement,
                              decltype(::stellar::AccountRuleRequirement::account),
                              &::stellar::AccountRuleRequirement::account>,
                    field_ptr<::stellar::AccountRuleRequirement,
                              decltype(::stellar::AccountRuleRequirement::ext),
                              &::stellar::AccountRuleRequirement::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::AccountRuleRequirement &obj) {
    archive(ar, obj.resource, "resource");
    archive(ar, obj.action, "action");
    archive(ar, obj.account, "account");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::AccountRuleRequirement &obj) {
    archive(ar, obj.resource, "resource");
    archive(ar, obj.action, "action");
    archive(ar, obj.account, "account");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct OperationResult {
  struct _tr_t {
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
      CreateASwapBidCreationRequestResult createASwapBidCreationRequestResult_;
      CancelASwapBidResult cancelASwapBidResult_;
      CreateASwapRequestResult createASwapRequestResult_;
      ManageAccountRoleResult manageAccountRoleResult_;
      ManageAccountRuleResult manageAccountRuleResult_;
      ManageSignerResult manageSignerResult_;
      ManageSignerRoleResult manageSignerRoleResult_;
      ManageSignerRuleResult manageSignerRuleResult_;
      StampResult stampResult_;
      LicenseResult licenseResult_;
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
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
        OperationType::CREATE_ASWAP_BID_REQUEST,
        OperationType::CANCEL_ASWAP_BID,
        OperationType::CREATE_ASWAP_REQUEST,
        OperationType::MANAGE_ACCOUNT_ROLE,
        OperationType::MANAGE_ACCOUNT_RULE,
        OperationType::MANAGE_SIGNER,
        OperationType::MANAGE_SIGNER_ROLE,
        OperationType::MANAGE_SIGNER_RULE,
        OperationType::STAMP,
        OperationType::LICENSE
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
        : which == (int32_t)OperationType::CREATE_ASWAP_BID_REQUEST ? 27
        : which == (int32_t)OperationType::CANCEL_ASWAP_BID ? 28
        : which == (int32_t)OperationType::CREATE_ASWAP_REQUEST ? 29
        : which == (int32_t)OperationType::MANAGE_ACCOUNT_ROLE ? 30
        : which == (int32_t)OperationType::MANAGE_ACCOUNT_RULE ? 31
        : which == (int32_t)OperationType::MANAGE_SIGNER ? 32
        : which == (int32_t)OperationType::MANAGE_SIGNER_ROLE ? 33
        : which == (int32_t)OperationType::MANAGE_SIGNER_RULE ? 34
        : which == (int32_t)OperationType::STAMP ? 35
        : which == (int32_t)OperationType::LICENSE ? 36
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
      case (int32_t)OperationType::CREATE_ASWAP_BID_REQUEST:
        _f(&_tr_t::createASwapBidCreationRequestResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CANCEL_ASWAP_BID:
        _f(&_tr_t::cancelASwapBidResult_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)OperationType::CREATE_ASWAP_REQUEST:
        _f(&_tr_t::createASwapRequestResult_, std::forward<_A>(_a)...);
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
        type_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
      }
      else
        type_ = which;
    }
    explicit _tr_t(OperationType which = OperationType{}) : type_((int32_t)which) {
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    _tr_t(const _tr_t &source) : type_(source.type_) {
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
    }
    _tr_t(_tr_t &&source) : type_(source.type_) {
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                        std::move(source));
    }
    ~_tr_t() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
    _tr_t &operator=(const _tr_t &source) {
      if (_xdr_field_number(type_)
          == _xdr_field_number(source.type_))
        _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
      else {
        this->~_tr_t();
        type_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
      }
      type_ = source.type_;
      return *this;
    }
    _tr_t &operator=(_tr_t &&source) {
      if (_xdr_field_number(type_)
           == _xdr_field_number(source.type_))
        _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                          std::move(source));
      else {
        this->~_tr_t();
        type_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                          std::move(source));
      }
      type_ = source.type_;
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
    CreateASwapBidCreationRequestResult &createASwapBidCreationRequestResult() {
      if (_xdr_field_number(type_) == 27)
        return createASwapBidCreationRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: createASwapBidCreationRequestResult accessed when not selected");
    }
    const CreateASwapBidCreationRequestResult &createASwapBidCreationRequestResult() const {
      if (_xdr_field_number(type_) == 27)
        return createASwapBidCreationRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: createASwapBidCreationRequestResult accessed when not selected");
    }
    CancelASwapBidResult &cancelASwapBidResult() {
      if (_xdr_field_number(type_) == 28)
        return cancelASwapBidResult_;
      throw xdr::xdr_wrong_union("_tr_t: cancelASwapBidResult accessed when not selected");
    }
    const CancelASwapBidResult &cancelASwapBidResult() const {
      if (_xdr_field_number(type_) == 28)
        return cancelASwapBidResult_;
      throw xdr::xdr_wrong_union("_tr_t: cancelASwapBidResult accessed when not selected");
    }
    CreateASwapRequestResult &createASwapRequestResult() {
      if (_xdr_field_number(type_) == 29)
        return createASwapRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: createASwapRequestResult accessed when not selected");
    }
    const CreateASwapRequestResult &createASwapRequestResult() const {
      if (_xdr_field_number(type_) == 29)
        return createASwapRequestResult_;
      throw xdr::xdr_wrong_union("_tr_t: createASwapRequestResult accessed when not selected");
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
  static Constexpr const bool _xdr_has_default_case = true;
  static const std::vector<OperationResultCode> &_xdr_case_values() {
    static const std::vector<OperationResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit OperationResult(OperationResultCode which = OperationResultCode{}) : code_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  OperationResult(const OperationResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  OperationResult(OperationResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~OperationResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  OperationResult &operator=(const OperationResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~OperationResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  OperationResult &operator=(OperationResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~OperationResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
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
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::OperationResult::_tr_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::OperationResult::_tr_t;
  using case_type = ::stellar::OperationResult::_tr_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "createAccountResult";
    case 2:
      return "createIssuanceRequestResult";
    case 3:
      return "setFeesResult";
    case 4:
      return "createWithdrawalRequestResult";
    case 5:
      return "manageBalanceResult";
    case 6:
      return "manageAssetResult";
    case 7:
      return "createPreIssuanceRequestResult";
    case 8:
      return "manageLimitsResult";
    case 9:
      return "manageAssetPairResult";
    case 10:
      return "manageOfferResult";
    case 11:
      return "manageInvoiceRequestResult";
    case 12:
      return "reviewRequestResult";
    case 13:
      return "createSaleCreationRequestResult";
    case 14:
      return "checkSaleStateResult";
    case 15:
      return "payoutResult";
    case 16:
      return "createAMLAlertRequestResult";
    case 17:
      return "manageKeyValueResult";
    case 18:
      return "createChangeRoleRequestResult";
    case 19:
      return "manageExternalSystemAccountIdPoolEntryResult";
    case 20:
      return "bindExternalSystemAccountIdResult";
    case 21:
      return "paymentResult";
    case 22:
      return "manageSaleResult";
    case 23:
      return "createManageLimitsRequestResult";
    case 24:
      return "manageContractRequestResult";
    case 25:
      return "manageContractResult";
    case 26:
      return "cancelSaleCreationRequestResult";
    case 27:
      return "createASwapBidCreationRequestResult";
    case 28:
      return "cancelASwapBidResult";
    case 29:
      return "createASwapRequestResult";
    case 30:
      return "manageAccountRoleResult";
    case 31:
      return "manageAccountRuleResult";
    case 32:
      return "manageSignerResult";
    case 33:
      return "manageSignerRoleResult";
    case 34:
      return "manageSignerRuleResult";
    case 35:
      return "stampResult";
    case 36:
      return "licenseResult";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::OperationResult::_tr_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in _tr_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::OperationResult::_tr_t &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in _tr_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::OperationResult::_tr_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.type(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::OperationResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::OperationResult;
  using case_type = ::stellar::OperationResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "tr";
    case 2:
      return "entryType";
    case 3:
      return "requirement";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::OperationResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in OperationResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::OperationResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in OperationResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::OperationResult &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.code(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
} namespace stellar {

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
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
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

struct OperationFee {
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::OperationFee::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::OperationFee::_ext_t;
  using case_type = ::stellar::OperationFee::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::OperationFee::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::OperationFee::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::OperationFee::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::OperationFee>
  : xdr_struct_base<field_ptr<::stellar::OperationFee,
                              decltype(::stellar::OperationFee::operationType),
                              &::stellar::OperationFee::operationType>,
                    field_ptr<::stellar::OperationFee,
                              decltype(::stellar::OperationFee::amount),
                              &::stellar::OperationFee::amount>,
                    field_ptr<::stellar::OperationFee,
                              decltype(::stellar::OperationFee::ext),
                              &::stellar::OperationFee::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::OperationFee &obj) {
    archive(ar, obj.operationType, "operationType");
    archive(ar, obj.amount, "amount");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::OperationFee &obj) {
    archive(ar, obj.operationType, "operationType");
    archive(ar, obj.amount, "amount");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct TransactionResult {
  struct _result_t {
    using _xdr_case_type = xdr::xdr_traits<TransactionResultCode>::case_type;
  private:
    _xdr_case_type code_;
    union {
      xdr::xvector<OperationResult> results_;
      AccountRuleRequirement requirement_;
    };

  public:
    static Constexpr const bool _xdr_has_default_case = true;
    static const std::vector<TransactionResultCode> &_xdr_case_values() {
      static const std::vector<TransactionResultCode> _xdr_disc_vec {};
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
        code_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
      }
      else
        code_ = which;
    }
    explicit _result_t(TransactionResultCode which = TransactionResultCode{}) : code_((int32_t)which) {
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    _result_t(const _result_t &source) : code_(source.code_) {
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
    }
    _result_t(_result_t &&source) : code_(source.code_) {
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                        std::move(source));
    }
    ~_result_t() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
    _result_t &operator=(const _result_t &source) {
      if (_xdr_field_number(code_)
          == _xdr_field_number(source.code_))
        _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
      else {
        this->~_result_t();
        code_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
      }
      code_ = source.code_;
      return *this;
    }
    _result_t &operator=(_result_t &&source) {
      if (_xdr_field_number(code_)
           == _xdr_field_number(source.code_))
        _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                          std::move(source));
      else {
        this->~_result_t();
        code_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                          std::move(source));
      }
      code_ = source.code_;
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TransactionResult::_result_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::TransactionResult::_result_t;
  using case_type = ::stellar::TransactionResult::_result_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "results";
    case 2:
      return "requirement";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::TransactionResult::_result_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in _result_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionResult::_result_t &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in _result_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionResult::_result_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.code(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::TransactionResult::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::TransactionResult::_ext_t;
  using case_type = ::stellar::TransactionResult::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::TransactionResult::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionResult::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionResult::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::TransactionResult>
  : xdr_struct_base<field_ptr<::stellar::TransactionResult,
                              decltype(::stellar::TransactionResult::feeCharged),
                              &::stellar::TransactionResult::feeCharged>,
                    field_ptr<::stellar::TransactionResult,
                              decltype(::stellar::TransactionResult::result),
                              &::stellar::TransactionResult::result>,
                    field_ptr<::stellar::TransactionResult,
                              decltype(::stellar::TransactionResult::ext),
                              &::stellar::TransactionResult::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionResult &obj) {
    archive(ar, obj.feeCharged, "feeCharged");
    archive(ar, obj.result, "result");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionResult &obj) {
    archive(ar, obj.feeCharged, "feeCharged");
    archive(ar, obj.result, "result");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

}

#endif // !__XDR_STELLAR_TRANSACTION_H_INCLUDED__
