// -*- C++ -*-
// Automatically generated from ledger-entries.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_LEDGER_ENTRIES_H_INCLUDED__
#define __XDR_LEDGER_ENTRIES_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"
#include "xdr/ledger-entries-account.h"
#include "xdr/ledger-entries-signer.h"
#include "xdr/ledger-entries-fee.h"
#include "xdr/ledger-entries-balance.h"
#include "xdr/ledger-entries-asset.h"
#include "xdr/ledger-entries-asset-pair.h"
#include "xdr/ledger-entries-reference.h"
#include "xdr/ledger-entries-statistics.h"
#include "xdr/ledger-entries-offer.h"
#include "xdr/ledger-entries-account-limits.h"
#include "xdr/ledger-entries-reviewable-request.h"
#include "xdr/ledger-entries-external-system-id.h"
#include "xdr/ledger-entries-sale.h"
#include "xdr/ledger-entries-key-value.h"
#include "xdr/ledger-entries-account-KYC.h"
#include "xdr/ledger-entries-external-system-id-pool-entry.h"
#include "xdr/ledger-entries-statistics-v2.h"
#include "xdr/ledger-entries-pending-statistics.h"
#include "xdr/ledger-entries-contract.h"
#include "xdr/ledger-entries-atomic-swap-ask.h"
#include "xdr/ledger-entries-account-role.h"
#include "xdr/ledger-entries-account-rule.h"
#include "xdr/ledger-entries-signer-role.h"
#include "xdr/ledger-entries-signer-rule.h"
#include "xdr/ledger-entries-license.h"
#include "xdr/ledger-entries-stamp.h"
#include "xdr/ledger-entries-poll.h"
#include "xdr/ledger-entries-vote.h"
#include "xdr/ledger-entries-account-specific-rule.h"
#include "xdr/ledger-entries-swap.h"
#include "xdr/ledger-entries-data.h"
#include "xdr/ledger-entries-deferred-payment.h"
#include "xdr/ledger-entries-liquidity-pool.h"

namespace stellar {

enum class ThresholdIndexes : std::int32_t {
  MASTER_WEIGHT = 0,
  LOW = 1,
  MED = 2,
  HIGH = 3,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ThresholdIndexes>
  : xdr_integral_base<::stellar::ThresholdIndexes, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ThresholdIndexes val) {
    switch (val) {
    case ::stellar::ThresholdIndexes::MASTER_WEIGHT:
      return "MASTER_WEIGHT";
    case ::stellar::ThresholdIndexes::LOW:
      return "LOW";
    case ::stellar::ThresholdIndexes::MED:
      return "MED";
    case ::stellar::ThresholdIndexes::HIGH:
      return "HIGH";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ThresholdIndexes::MASTER_WEIGHT,
      (int32_t)::stellar::ThresholdIndexes::LOW,
      (int32_t)::stellar::ThresholdIndexes::MED,
      (int32_t)::stellar::ThresholdIndexes::HIGH
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct LedgerEntry  : xdr::xdr_abstract {
  struct _data_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<LedgerEntryType>::case_type;
  private:
    _xdr_case_type type_;
    union {
      AccountEntry account_;
      SignerEntry signer_;
      FeeEntry feeState_;
      BalanceEntry balance_;
      AssetEntry asset_;
      ReferenceEntry reference_;
      StatisticsEntry stats_;
      AccountLimitsEntry accountLimits_;
      AssetPairEntry assetPair_;
      OfferEntry offer_;
      ReviewableRequestEntry reviewableRequest_;
      ExternalSystemAccountID externalSystemAccountID_;
      SaleEntry sale_;
      KeyValueEntry keyValue_;
      AccountKYCEntry accountKYC_;
      ExternalSystemAccountIDPoolEntry externalSystemAccountIDPoolEntry_;
      LimitsV2Entry limitsV2_;
      StatisticsV2Entry statisticsV2_;
      PendingStatisticsEntry pendingStatistics_;
      ContractEntry contract_;
      AtomicSwapAskEntry atomicSwapAsk_;
      AccountRoleEntry accountRole_;
      AccountRuleEntry accountRule_;
      SignerRuleEntry signerRule_;
      SignerRoleEntry signerRole_;
      LicenseEntry license_;
      StampEntry stamp_;
      PollEntry poll_;
      VoteEntry vote_;
      AccountSpecificRuleEntry accountSpecificRule_;
      SwapEntry swap_;
      DataEntry data_;
      DeferredPaymentEntry deferredPayment_;
      LiquidityPoolEntry liquidityPool_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<LedgerEntryType> &_xdr_case_values() {
      static const std::vector<LedgerEntryType> _xdr_disc_vec {
        LedgerEntryType::ACCOUNT,
        LedgerEntryType::SIGNER,
        LedgerEntryType::FEE,
        LedgerEntryType::BALANCE,
        LedgerEntryType::ASSET,
        LedgerEntryType::REFERENCE_ENTRY,
        LedgerEntryType::STATISTICS,
        LedgerEntryType::ACCOUNT_LIMITS,
        LedgerEntryType::ASSET_PAIR,
        LedgerEntryType::OFFER_ENTRY,
        LedgerEntryType::REVIEWABLE_REQUEST,
        LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID,
        LedgerEntryType::SALE,
        LedgerEntryType::KEY_VALUE,
        LedgerEntryType::ACCOUNT_KYC,
        LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY,
        LedgerEntryType::LIMITS_V2,
        LedgerEntryType::STATISTICS_V2,
        LedgerEntryType::PENDING_STATISTICS,
        LedgerEntryType::CONTRACT,
        LedgerEntryType::ATOMIC_SWAP_ASK,
        LedgerEntryType::ACCOUNT_ROLE,
        LedgerEntryType::ACCOUNT_RULE,
        LedgerEntryType::SIGNER_RULE,
        LedgerEntryType::SIGNER_ROLE,
        LedgerEntryType::LICENSE,
        LedgerEntryType::STAMP,
        LedgerEntryType::POLL,
        LedgerEntryType::VOTE,
        LedgerEntryType::ACCOUNT_SPECIFIC_RULE,
        LedgerEntryType::SWAP,
        LedgerEntryType::DATA,
        LedgerEntryType::DEFERRED_PAYMENT,
        LedgerEntryType::LIQUIDITY_POOL
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)LedgerEntryType::ACCOUNT ? 1
        : which == (int32_t)LedgerEntryType::SIGNER ? 2
        : which == (int32_t)LedgerEntryType::FEE ? 3
        : which == (int32_t)LedgerEntryType::BALANCE ? 4
        : which == (int32_t)LedgerEntryType::ASSET ? 5
        : which == (int32_t)LedgerEntryType::REFERENCE_ENTRY ? 6
        : which == (int32_t)LedgerEntryType::STATISTICS ? 7
        : which == (int32_t)LedgerEntryType::ACCOUNT_LIMITS ? 8
        : which == (int32_t)LedgerEntryType::ASSET_PAIR ? 9
        : which == (int32_t)LedgerEntryType::OFFER_ENTRY ? 10
        : which == (int32_t)LedgerEntryType::REVIEWABLE_REQUEST ? 11
        : which == (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID ? 12
        : which == (int32_t)LedgerEntryType::SALE ? 13
        : which == (int32_t)LedgerEntryType::KEY_VALUE ? 14
        : which == (int32_t)LedgerEntryType::ACCOUNT_KYC ? 15
        : which == (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY ? 16
        : which == (int32_t)LedgerEntryType::LIMITS_V2 ? 17
        : which == (int32_t)LedgerEntryType::STATISTICS_V2 ? 18
        : which == (int32_t)LedgerEntryType::PENDING_STATISTICS ? 19
        : which == (int32_t)LedgerEntryType::CONTRACT ? 20
        : which == (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK ? 21
        : which == (int32_t)LedgerEntryType::ACCOUNT_ROLE ? 22
        : which == (int32_t)LedgerEntryType::ACCOUNT_RULE ? 23
        : which == (int32_t)LedgerEntryType::SIGNER_RULE ? 24
        : which == (int32_t)LedgerEntryType::SIGNER_ROLE ? 25
        : which == (int32_t)LedgerEntryType::LICENSE ? 26
        : which == (int32_t)LedgerEntryType::STAMP ? 27
        : which == (int32_t)LedgerEntryType::POLL ? 28
        : which == (int32_t)LedgerEntryType::VOTE ? 29
        : which == (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE ? 30
        : which == (int32_t)LedgerEntryType::SWAP ? 31
        : which == (int32_t)LedgerEntryType::DATA ? 32
        : which == (int32_t)LedgerEntryType::DEFERRED_PAYMENT ? 33
        : which == (int32_t)LedgerEntryType::LIQUIDITY_POOL ? 34
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)LedgerEntryType::ACCOUNT:
        _f(&_data_t::account_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)LedgerEntryType::SIGNER:
        _f(&_data_t::signer_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)LedgerEntryType::FEE:
        _f(&_data_t::feeState_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)LedgerEntryType::BALANCE:
        _f(&_data_t::balance_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)LedgerEntryType::ASSET:
        _f(&_data_t::asset_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)LedgerEntryType::REFERENCE_ENTRY:
        _f(&_data_t::reference_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)LedgerEntryType::STATISTICS:
        _f(&_data_t::stats_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)LedgerEntryType::ACCOUNT_LIMITS:
        _f(&_data_t::accountLimits_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)LedgerEntryType::ASSET_PAIR:
        _f(&_data_t::assetPair_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)LedgerEntryType::OFFER_ENTRY:
        _f(&_data_t::offer_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
        _f(&_data_t::reviewableRequest_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
        _f(&_data_t::externalSystemAccountID_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)LedgerEntryType::SALE:
        _f(&_data_t::sale_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)LedgerEntryType::KEY_VALUE:
        _f(&_data_t::keyValue_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)LedgerEntryType::ACCOUNT_KYC:
        _f(&_data_t::accountKYC_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
        _f(&_data_t::externalSystemAccountIDPoolEntry_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)LedgerEntryType::LIMITS_V2:
        _f(&_data_t::limitsV2_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)LedgerEntryType::STATISTICS_V2:
        _f(&_data_t::statisticsV2_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)LedgerEntryType::PENDING_STATISTICS:
        _f(&_data_t::pendingStatistics_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)LedgerEntryType::CONTRACT:
        _f(&_data_t::contract_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
        _f(&_data_t::atomicSwapAsk_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)LedgerEntryType::ACCOUNT_ROLE:
        _f(&_data_t::accountRole_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)LedgerEntryType::ACCOUNT_RULE:
        _f(&_data_t::accountRule_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)LedgerEntryType::SIGNER_RULE:
        _f(&_data_t::signerRule_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)LedgerEntryType::SIGNER_ROLE:
        _f(&_data_t::signerRole_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)LedgerEntryType::LICENSE:
        _f(&_data_t::license_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)LedgerEntryType::STAMP:
        _f(&_data_t::stamp_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)LedgerEntryType::POLL:
        _f(&_data_t::poll_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)LedgerEntryType::VOTE:
        _f(&_data_t::vote_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
        _f(&_data_t::accountSpecificRule_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)LedgerEntryType::SWAP:
        _f(&_data_t::swap_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)LedgerEntryType::DATA:
        _f(&_data_t::data_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)LedgerEntryType::DEFERRED_PAYMENT:
        _f(&_data_t::deferredPayment_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)LedgerEntryType::LIQUIDITY_POOL:
        _f(&_data_t::liquidityPool_, std::forward<_A>(_a)...);
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return type_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of type in _data_t");
      if (fnum != _xdr_field_number(type_)) {
        this->~_data_t();
        type_ = which;switch (type_)
{
        case (int32_t)LedgerEntryType::ACCOUNT:
new(&account_) AccountEntry{};
break;
        case (int32_t)LedgerEntryType::SIGNER:
new(&signer_) SignerEntry{};
break;
        case (int32_t)LedgerEntryType::FEE:
new(&feeState_) FeeEntry{};
break;
        case (int32_t)LedgerEntryType::BALANCE:
new(&balance_) BalanceEntry{};
break;
        case (int32_t)LedgerEntryType::ASSET:
new(&asset_) AssetEntry{};
break;
        case (int32_t)LedgerEntryType::REFERENCE_ENTRY:
new(&reference_) ReferenceEntry{};
break;
        case (int32_t)LedgerEntryType::STATISTICS:
new(&stats_) StatisticsEntry{};
break;
        case (int32_t)LedgerEntryType::ACCOUNT_LIMITS:
new(&accountLimits_) AccountLimitsEntry{};
break;
        case (int32_t)LedgerEntryType::ASSET_PAIR:
new(&assetPair_) AssetPairEntry{};
break;
        case (int32_t)LedgerEntryType::OFFER_ENTRY:
new(&offer_) OfferEntry{};
break;
        case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
new(&reviewableRequest_) ReviewableRequestEntry{};
break;
        case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
new(&externalSystemAccountID_) ExternalSystemAccountID{};
break;
        case (int32_t)LedgerEntryType::SALE:
new(&sale_) SaleEntry{};
break;
        case (int32_t)LedgerEntryType::KEY_VALUE:
new(&keyValue_) KeyValueEntry{};
break;
        case (int32_t)LedgerEntryType::ACCOUNT_KYC:
new(&accountKYC_) AccountKYCEntry{};
break;
        case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
new(&externalSystemAccountIDPoolEntry_) ExternalSystemAccountIDPoolEntry{};
break;
        case (int32_t)LedgerEntryType::LIMITS_V2:
new(&limitsV2_) LimitsV2Entry{};
break;
        case (int32_t)LedgerEntryType::STATISTICS_V2:
new(&statisticsV2_) StatisticsV2Entry{};
break;
        case (int32_t)LedgerEntryType::PENDING_STATISTICS:
new(&pendingStatistics_) PendingStatisticsEntry{};
break;
        case (int32_t)LedgerEntryType::CONTRACT:
new(&contract_) ContractEntry{};
break;
        case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
new(&atomicSwapAsk_) AtomicSwapAskEntry{};
break;
        case (int32_t)LedgerEntryType::ACCOUNT_ROLE:
new(&accountRole_) AccountRoleEntry{};
break;
        case (int32_t)LedgerEntryType::ACCOUNT_RULE:
new(&accountRule_) AccountRuleEntry{};
break;
        case (int32_t)LedgerEntryType::SIGNER_RULE:
new(&signerRule_) SignerRuleEntry{};
break;
        case (int32_t)LedgerEntryType::SIGNER_ROLE:
new(&signerRole_) SignerRoleEntry{};
break;
        case (int32_t)LedgerEntryType::LICENSE:
new(&license_) LicenseEntry{};
break;
        case (int32_t)LedgerEntryType::STAMP:
new(&stamp_) StampEntry{};
break;
        case (int32_t)LedgerEntryType::POLL:
new(&poll_) PollEntry{};
break;
        case (int32_t)LedgerEntryType::VOTE:
new(&vote_) VoteEntry{};
break;
        case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
new(&accountSpecificRule_) AccountSpecificRuleEntry{};
break;
        case (int32_t)LedgerEntryType::SWAP:
new(&swap_) SwapEntry{};
break;
        case (int32_t)LedgerEntryType::DATA:
new(&data_) DataEntry{};
break;
        case (int32_t)LedgerEntryType::DEFERRED_PAYMENT:
new(&deferredPayment_) DeferredPaymentEntry{};
break;
        case (int32_t)LedgerEntryType::LIQUIDITY_POOL:
new(&liquidityPool_) LiquidityPoolEntry{};
break;
}

      }
      else
        type_ = which;
    }
    explicit _data_t(LedgerEntryType which = LedgerEntryType{}) : type_((int32_t)which) {
      switch (type_)
{
      case (int32_t)LedgerEntryType::ACCOUNT:
new(&account_) AccountEntry{};
break;
      case (int32_t)LedgerEntryType::SIGNER:
new(&signer_) SignerEntry{};
break;
      case (int32_t)LedgerEntryType::FEE:
new(&feeState_) FeeEntry{};
break;
      case (int32_t)LedgerEntryType::BALANCE:
new(&balance_) BalanceEntry{};
break;
      case (int32_t)LedgerEntryType::ASSET:
new(&asset_) AssetEntry{};
break;
      case (int32_t)LedgerEntryType::REFERENCE_ENTRY:
new(&reference_) ReferenceEntry{};
break;
      case (int32_t)LedgerEntryType::STATISTICS:
new(&stats_) StatisticsEntry{};
break;
      case (int32_t)LedgerEntryType::ACCOUNT_LIMITS:
new(&accountLimits_) AccountLimitsEntry{};
break;
      case (int32_t)LedgerEntryType::ASSET_PAIR:
new(&assetPair_) AssetPairEntry{};
break;
      case (int32_t)LedgerEntryType::OFFER_ENTRY:
new(&offer_) OfferEntry{};
break;
      case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
new(&reviewableRequest_) ReviewableRequestEntry{};
break;
      case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
new(&externalSystemAccountID_) ExternalSystemAccountID{};
break;
      case (int32_t)LedgerEntryType::SALE:
new(&sale_) SaleEntry{};
break;
      case (int32_t)LedgerEntryType::KEY_VALUE:
new(&keyValue_) KeyValueEntry{};
break;
      case (int32_t)LedgerEntryType::ACCOUNT_KYC:
new(&accountKYC_) AccountKYCEntry{};
break;
      case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
new(&externalSystemAccountIDPoolEntry_) ExternalSystemAccountIDPoolEntry{};
break;
      case (int32_t)LedgerEntryType::LIMITS_V2:
new(&limitsV2_) LimitsV2Entry{};
break;
      case (int32_t)LedgerEntryType::STATISTICS_V2:
new(&statisticsV2_) StatisticsV2Entry{};
break;
      case (int32_t)LedgerEntryType::PENDING_STATISTICS:
new(&pendingStatistics_) PendingStatisticsEntry{};
break;
      case (int32_t)LedgerEntryType::CONTRACT:
new(&contract_) ContractEntry{};
break;
      case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
new(&atomicSwapAsk_) AtomicSwapAskEntry{};
break;
      case (int32_t)LedgerEntryType::ACCOUNT_ROLE:
new(&accountRole_) AccountRoleEntry{};
break;
      case (int32_t)LedgerEntryType::ACCOUNT_RULE:
new(&accountRule_) AccountRuleEntry{};
break;
      case (int32_t)LedgerEntryType::SIGNER_RULE:
new(&signerRule_) SignerRuleEntry{};
break;
      case (int32_t)LedgerEntryType::SIGNER_ROLE:
new(&signerRole_) SignerRoleEntry{};
break;
      case (int32_t)LedgerEntryType::LICENSE:
new(&license_) LicenseEntry{};
break;
      case (int32_t)LedgerEntryType::STAMP:
new(&stamp_) StampEntry{};
break;
      case (int32_t)LedgerEntryType::POLL:
new(&poll_) PollEntry{};
break;
      case (int32_t)LedgerEntryType::VOTE:
new(&vote_) VoteEntry{};
break;
      case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
new(&accountSpecificRule_) AccountSpecificRuleEntry{};
break;
      case (int32_t)LedgerEntryType::SWAP:
new(&swap_) SwapEntry{};
break;
      case (int32_t)LedgerEntryType::DATA:
new(&data_) DataEntry{};
break;
      case (int32_t)LedgerEntryType::DEFERRED_PAYMENT:
new(&deferredPayment_) DeferredPaymentEntry{};
break;
      case (int32_t)LedgerEntryType::LIQUIDITY_POOL:
new(&liquidityPool_) LiquidityPoolEntry{};
break;
}

    }
    _data_t(const _data_t &source) : type_(source.type_) {
      switch (type_)
{
      case (int32_t)LedgerEntryType::ACCOUNT:
new(&account_) AccountEntry(source.account_);
break;
      case (int32_t)LedgerEntryType::SIGNER:
new(&signer_) SignerEntry(source.signer_);
break;
      case (int32_t)LedgerEntryType::FEE:
new(&feeState_) FeeEntry(source.feeState_);
break;
      case (int32_t)LedgerEntryType::BALANCE:
new(&balance_) BalanceEntry(source.balance_);
break;
      case (int32_t)LedgerEntryType::ASSET:
new(&asset_) AssetEntry(source.asset_);
break;
      case (int32_t)LedgerEntryType::REFERENCE_ENTRY:
new(&reference_) ReferenceEntry(source.reference_);
break;
      case (int32_t)LedgerEntryType::STATISTICS:
new(&stats_) StatisticsEntry(source.stats_);
break;
      case (int32_t)LedgerEntryType::ACCOUNT_LIMITS:
new(&accountLimits_) AccountLimitsEntry(source.accountLimits_);
break;
      case (int32_t)LedgerEntryType::ASSET_PAIR:
new(&assetPair_) AssetPairEntry(source.assetPair_);
break;
      case (int32_t)LedgerEntryType::OFFER_ENTRY:
new(&offer_) OfferEntry(source.offer_);
break;
      case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
new(&reviewableRequest_) ReviewableRequestEntry(source.reviewableRequest_);
break;
      case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
new(&externalSystemAccountID_) ExternalSystemAccountID(source.externalSystemAccountID_);
break;
      case (int32_t)LedgerEntryType::SALE:
new(&sale_) SaleEntry(source.sale_);
break;
      case (int32_t)LedgerEntryType::KEY_VALUE:
new(&keyValue_) KeyValueEntry(source.keyValue_);
break;
      case (int32_t)LedgerEntryType::ACCOUNT_KYC:
new(&accountKYC_) AccountKYCEntry(source.accountKYC_);
break;
      case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
new(&externalSystemAccountIDPoolEntry_) ExternalSystemAccountIDPoolEntry(source.externalSystemAccountIDPoolEntry_);
break;
      case (int32_t)LedgerEntryType::LIMITS_V2:
new(&limitsV2_) LimitsV2Entry(source.limitsV2_);
break;
      case (int32_t)LedgerEntryType::STATISTICS_V2:
new(&statisticsV2_) StatisticsV2Entry(source.statisticsV2_);
break;
      case (int32_t)LedgerEntryType::PENDING_STATISTICS:
new(&pendingStatistics_) PendingStatisticsEntry(source.pendingStatistics_);
break;
      case (int32_t)LedgerEntryType::CONTRACT:
new(&contract_) ContractEntry(source.contract_);
break;
      case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
new(&atomicSwapAsk_) AtomicSwapAskEntry(source.atomicSwapAsk_);
break;
      case (int32_t)LedgerEntryType::ACCOUNT_ROLE:
new(&accountRole_) AccountRoleEntry(source.accountRole_);
break;
      case (int32_t)LedgerEntryType::ACCOUNT_RULE:
new(&accountRule_) AccountRuleEntry(source.accountRule_);
break;
      case (int32_t)LedgerEntryType::SIGNER_RULE:
new(&signerRule_) SignerRuleEntry(source.signerRule_);
break;
      case (int32_t)LedgerEntryType::SIGNER_ROLE:
new(&signerRole_) SignerRoleEntry(source.signerRole_);
break;
      case (int32_t)LedgerEntryType::LICENSE:
new(&license_) LicenseEntry(source.license_);
break;
      case (int32_t)LedgerEntryType::STAMP:
new(&stamp_) StampEntry(source.stamp_);
break;
      case (int32_t)LedgerEntryType::POLL:
new(&poll_) PollEntry(source.poll_);
break;
      case (int32_t)LedgerEntryType::VOTE:
new(&vote_) VoteEntry(source.vote_);
break;
      case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
new(&accountSpecificRule_) AccountSpecificRuleEntry(source.accountSpecificRule_);
break;
      case (int32_t)LedgerEntryType::SWAP:
new(&swap_) SwapEntry(source.swap_);
break;
      case (int32_t)LedgerEntryType::DATA:
new(&data_) DataEntry(source.data_);
break;
      case (int32_t)LedgerEntryType::DEFERRED_PAYMENT:
new(&deferredPayment_) DeferredPaymentEntry(source.deferredPayment_);
break;
      case (int32_t)LedgerEntryType::LIQUIDITY_POOL:
new(&liquidityPool_) LiquidityPoolEntry(source.liquidityPool_);
break;
}

    }
    _data_t(_data_t &&source) : type_(source.type_) {
      switch (type_)
{
      case (int32_t)LedgerEntryType::ACCOUNT:
new(&account_) AccountEntry(std::move(source.account_));
break;
      case (int32_t)LedgerEntryType::SIGNER:
new(&signer_) SignerEntry(std::move(source.signer_));
break;
      case (int32_t)LedgerEntryType::FEE:
new(&feeState_) FeeEntry(std::move(source.feeState_));
break;
      case (int32_t)LedgerEntryType::BALANCE:
new(&balance_) BalanceEntry(std::move(source.balance_));
break;
      case (int32_t)LedgerEntryType::ASSET:
new(&asset_) AssetEntry(std::move(source.asset_));
break;
      case (int32_t)LedgerEntryType::REFERENCE_ENTRY:
new(&reference_) ReferenceEntry(std::move(source.reference_));
break;
      case (int32_t)LedgerEntryType::STATISTICS:
new(&stats_) StatisticsEntry(std::move(source.stats_));
break;
      case (int32_t)LedgerEntryType::ACCOUNT_LIMITS:
new(&accountLimits_) AccountLimitsEntry(std::move(source.accountLimits_));
break;
      case (int32_t)LedgerEntryType::ASSET_PAIR:
new(&assetPair_) AssetPairEntry(std::move(source.assetPair_));
break;
      case (int32_t)LedgerEntryType::OFFER_ENTRY:
new(&offer_) OfferEntry(std::move(source.offer_));
break;
      case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
new(&reviewableRequest_) ReviewableRequestEntry(std::move(source.reviewableRequest_));
break;
      case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
new(&externalSystemAccountID_) ExternalSystemAccountID(std::move(source.externalSystemAccountID_));
break;
      case (int32_t)LedgerEntryType::SALE:
new(&sale_) SaleEntry(std::move(source.sale_));
break;
      case (int32_t)LedgerEntryType::KEY_VALUE:
new(&keyValue_) KeyValueEntry(std::move(source.keyValue_));
break;
      case (int32_t)LedgerEntryType::ACCOUNT_KYC:
new(&accountKYC_) AccountKYCEntry(std::move(source.accountKYC_));
break;
      case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
new(&externalSystemAccountIDPoolEntry_) ExternalSystemAccountIDPoolEntry(std::move(source.externalSystemAccountIDPoolEntry_));
break;
      case (int32_t)LedgerEntryType::LIMITS_V2:
new(&limitsV2_) LimitsV2Entry(std::move(source.limitsV2_));
break;
      case (int32_t)LedgerEntryType::STATISTICS_V2:
new(&statisticsV2_) StatisticsV2Entry(std::move(source.statisticsV2_));
break;
      case (int32_t)LedgerEntryType::PENDING_STATISTICS:
new(&pendingStatistics_) PendingStatisticsEntry(std::move(source.pendingStatistics_));
break;
      case (int32_t)LedgerEntryType::CONTRACT:
new(&contract_) ContractEntry(std::move(source.contract_));
break;
      case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
new(&atomicSwapAsk_) AtomicSwapAskEntry(std::move(source.atomicSwapAsk_));
break;
      case (int32_t)LedgerEntryType::ACCOUNT_ROLE:
new(&accountRole_) AccountRoleEntry(std::move(source.accountRole_));
break;
      case (int32_t)LedgerEntryType::ACCOUNT_RULE:
new(&accountRule_) AccountRuleEntry(std::move(source.accountRule_));
break;
      case (int32_t)LedgerEntryType::SIGNER_RULE:
new(&signerRule_) SignerRuleEntry(std::move(source.signerRule_));
break;
      case (int32_t)LedgerEntryType::SIGNER_ROLE:
new(&signerRole_) SignerRoleEntry(std::move(source.signerRole_));
break;
      case (int32_t)LedgerEntryType::LICENSE:
new(&license_) LicenseEntry(std::move(source.license_));
break;
      case (int32_t)LedgerEntryType::STAMP:
new(&stamp_) StampEntry(std::move(source.stamp_));
break;
      case (int32_t)LedgerEntryType::POLL:
new(&poll_) PollEntry(std::move(source.poll_));
break;
      case (int32_t)LedgerEntryType::VOTE:
new(&vote_) VoteEntry(std::move(source.vote_));
break;
      case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
new(&accountSpecificRule_) AccountSpecificRuleEntry(std::move(source.accountSpecificRule_));
break;
      case (int32_t)LedgerEntryType::SWAP:
new(&swap_) SwapEntry(std::move(source.swap_));
break;
      case (int32_t)LedgerEntryType::DATA:
new(&data_) DataEntry(std::move(source.data_));
break;
      case (int32_t)LedgerEntryType::DEFERRED_PAYMENT:
new(&deferredPayment_) DeferredPaymentEntry(std::move(source.deferredPayment_));
break;
      case (int32_t)LedgerEntryType::LIQUIDITY_POOL:
new(&liquidityPool_) LiquidityPoolEntry(std::move(source.liquidityPool_));
break;
}

    }
    ~_data_t() {
switch (type_)
{
    case (int32_t)LedgerEntryType::ACCOUNT:
account_.~AccountEntry();
break;
    case (int32_t)LedgerEntryType::SIGNER:
signer_.~SignerEntry();
break;
    case (int32_t)LedgerEntryType::FEE:
feeState_.~FeeEntry();
break;
    case (int32_t)LedgerEntryType::BALANCE:
balance_.~BalanceEntry();
break;
    case (int32_t)LedgerEntryType::ASSET:
asset_.~AssetEntry();
break;
    case (int32_t)LedgerEntryType::REFERENCE_ENTRY:
reference_.~ReferenceEntry();
break;
    case (int32_t)LedgerEntryType::STATISTICS:
stats_.~StatisticsEntry();
break;
    case (int32_t)LedgerEntryType::ACCOUNT_LIMITS:
accountLimits_.~AccountLimitsEntry();
break;
    case (int32_t)LedgerEntryType::ASSET_PAIR:
assetPair_.~AssetPairEntry();
break;
    case (int32_t)LedgerEntryType::OFFER_ENTRY:
offer_.~OfferEntry();
break;
    case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
reviewableRequest_.~ReviewableRequestEntry();
break;
    case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
externalSystemAccountID_.~ExternalSystemAccountID();
break;
    case (int32_t)LedgerEntryType::SALE:
sale_.~SaleEntry();
break;
    case (int32_t)LedgerEntryType::KEY_VALUE:
keyValue_.~KeyValueEntry();
break;
    case (int32_t)LedgerEntryType::ACCOUNT_KYC:
accountKYC_.~AccountKYCEntry();
break;
    case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
externalSystemAccountIDPoolEntry_.~ExternalSystemAccountIDPoolEntry();
break;
    case (int32_t)LedgerEntryType::LIMITS_V2:
limitsV2_.~LimitsV2Entry();
break;
    case (int32_t)LedgerEntryType::STATISTICS_V2:
statisticsV2_.~StatisticsV2Entry();
break;
    case (int32_t)LedgerEntryType::PENDING_STATISTICS:
pendingStatistics_.~PendingStatisticsEntry();
break;
    case (int32_t)LedgerEntryType::CONTRACT:
contract_.~ContractEntry();
break;
    case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
atomicSwapAsk_.~AtomicSwapAskEntry();
break;
    case (int32_t)LedgerEntryType::ACCOUNT_ROLE:
accountRole_.~AccountRoleEntry();
break;
    case (int32_t)LedgerEntryType::ACCOUNT_RULE:
accountRule_.~AccountRuleEntry();
break;
    case (int32_t)LedgerEntryType::SIGNER_RULE:
signerRule_.~SignerRuleEntry();
break;
    case (int32_t)LedgerEntryType::SIGNER_ROLE:
signerRole_.~SignerRoleEntry();
break;
    case (int32_t)LedgerEntryType::LICENSE:
license_.~LicenseEntry();
break;
    case (int32_t)LedgerEntryType::STAMP:
stamp_.~StampEntry();
break;
    case (int32_t)LedgerEntryType::POLL:
poll_.~PollEntry();
break;
    case (int32_t)LedgerEntryType::VOTE:
vote_.~VoteEntry();
break;
    case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
accountSpecificRule_.~AccountSpecificRuleEntry();
break;
    case (int32_t)LedgerEntryType::SWAP:
swap_.~SwapEntry();
break;
    case (int32_t)LedgerEntryType::DATA:
data_.~DataEntry();
break;
    case (int32_t)LedgerEntryType::DEFERRED_PAYMENT:
deferredPayment_.~DeferredPaymentEntry();
break;
    case (int32_t)LedgerEntryType::LIQUIDITY_POOL:
liquidityPool_.~LiquidityPoolEntry();
break;
}
}

    _data_t &operator=(const _data_t &source) {
      if (type_ == source.type_)
{
switch (type_)
{
      case (int32_t)LedgerEntryType::ACCOUNT:
account_ = source.account_;
break;
      case (int32_t)LedgerEntryType::SIGNER:
signer_ = source.signer_;
break;
      case (int32_t)LedgerEntryType::FEE:
feeState_ = source.feeState_;
break;
      case (int32_t)LedgerEntryType::BALANCE:
balance_ = source.balance_;
break;
      case (int32_t)LedgerEntryType::ASSET:
asset_ = source.asset_;
break;
      case (int32_t)LedgerEntryType::REFERENCE_ENTRY:
reference_ = source.reference_;
break;
      case (int32_t)LedgerEntryType::STATISTICS:
stats_ = source.stats_;
break;
      case (int32_t)LedgerEntryType::ACCOUNT_LIMITS:
accountLimits_ = source.accountLimits_;
break;
      case (int32_t)LedgerEntryType::ASSET_PAIR:
assetPair_ = source.assetPair_;
break;
      case (int32_t)LedgerEntryType::OFFER_ENTRY:
offer_ = source.offer_;
break;
      case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
reviewableRequest_ = source.reviewableRequest_;
break;
      case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
externalSystemAccountID_ = source.externalSystemAccountID_;
break;
      case (int32_t)LedgerEntryType::SALE:
sale_ = source.sale_;
break;
      case (int32_t)LedgerEntryType::KEY_VALUE:
keyValue_ = source.keyValue_;
break;
      case (int32_t)LedgerEntryType::ACCOUNT_KYC:
accountKYC_ = source.accountKYC_;
break;
      case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
externalSystemAccountIDPoolEntry_ = source.externalSystemAccountIDPoolEntry_;
break;
      case (int32_t)LedgerEntryType::LIMITS_V2:
limitsV2_ = source.limitsV2_;
break;
      case (int32_t)LedgerEntryType::STATISTICS_V2:
statisticsV2_ = source.statisticsV2_;
break;
      case (int32_t)LedgerEntryType::PENDING_STATISTICS:
pendingStatistics_ = source.pendingStatistics_;
break;
      case (int32_t)LedgerEntryType::CONTRACT:
contract_ = source.contract_;
break;
      case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
atomicSwapAsk_ = source.atomicSwapAsk_;
break;
      case (int32_t)LedgerEntryType::ACCOUNT_ROLE:
accountRole_ = source.accountRole_;
break;
      case (int32_t)LedgerEntryType::ACCOUNT_RULE:
accountRule_ = source.accountRule_;
break;
      case (int32_t)LedgerEntryType::SIGNER_RULE:
signerRule_ = source.signerRule_;
break;
      case (int32_t)LedgerEntryType::SIGNER_ROLE:
signerRole_ = source.signerRole_;
break;
      case (int32_t)LedgerEntryType::LICENSE:
license_ = source.license_;
break;
      case (int32_t)LedgerEntryType::STAMP:
stamp_ = source.stamp_;
break;
      case (int32_t)LedgerEntryType::POLL:
poll_ = source.poll_;
break;
      case (int32_t)LedgerEntryType::VOTE:
vote_ = source.vote_;
break;
      case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
accountSpecificRule_ = source.accountSpecificRule_;
break;
      case (int32_t)LedgerEntryType::SWAP:
swap_ = source.swap_;
break;
      case (int32_t)LedgerEntryType::DATA:
data_ = source.data_;
break;
      case (int32_t)LedgerEntryType::DEFERRED_PAYMENT:
deferredPayment_ = source.deferredPayment_;
break;
      case (int32_t)LedgerEntryType::LIQUIDITY_POOL:
liquidityPool_ = source.liquidityPool_;
break;
}
}
else {this->~_data_t();
      type_ = source.type_;
switch (type_)
{
      case (int32_t)LedgerEntryType::ACCOUNT:
new(&account_) AccountEntry(source.account_);
break;
      case (int32_t)LedgerEntryType::SIGNER:
new(&signer_) SignerEntry(source.signer_);
break;
      case (int32_t)LedgerEntryType::FEE:
new(&feeState_) FeeEntry(source.feeState_);
break;
      case (int32_t)LedgerEntryType::BALANCE:
new(&balance_) BalanceEntry(source.balance_);
break;
      case (int32_t)LedgerEntryType::ASSET:
new(&asset_) AssetEntry(source.asset_);
break;
      case (int32_t)LedgerEntryType::REFERENCE_ENTRY:
new(&reference_) ReferenceEntry(source.reference_);
break;
      case (int32_t)LedgerEntryType::STATISTICS:
new(&stats_) StatisticsEntry(source.stats_);
break;
      case (int32_t)LedgerEntryType::ACCOUNT_LIMITS:
new(&accountLimits_) AccountLimitsEntry(source.accountLimits_);
break;
      case (int32_t)LedgerEntryType::ASSET_PAIR:
new(&assetPair_) AssetPairEntry(source.assetPair_);
break;
      case (int32_t)LedgerEntryType::OFFER_ENTRY:
new(&offer_) OfferEntry(source.offer_);
break;
      case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
new(&reviewableRequest_) ReviewableRequestEntry(source.reviewableRequest_);
break;
      case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
new(&externalSystemAccountID_) ExternalSystemAccountID(source.externalSystemAccountID_);
break;
      case (int32_t)LedgerEntryType::SALE:
new(&sale_) SaleEntry(source.sale_);
break;
      case (int32_t)LedgerEntryType::KEY_VALUE:
new(&keyValue_) KeyValueEntry(source.keyValue_);
break;
      case (int32_t)LedgerEntryType::ACCOUNT_KYC:
new(&accountKYC_) AccountKYCEntry(source.accountKYC_);
break;
      case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
new(&externalSystemAccountIDPoolEntry_) ExternalSystemAccountIDPoolEntry(source.externalSystemAccountIDPoolEntry_);
break;
      case (int32_t)LedgerEntryType::LIMITS_V2:
new(&limitsV2_) LimitsV2Entry(source.limitsV2_);
break;
      case (int32_t)LedgerEntryType::STATISTICS_V2:
new(&statisticsV2_) StatisticsV2Entry(source.statisticsV2_);
break;
      case (int32_t)LedgerEntryType::PENDING_STATISTICS:
new(&pendingStatistics_) PendingStatisticsEntry(source.pendingStatistics_);
break;
      case (int32_t)LedgerEntryType::CONTRACT:
new(&contract_) ContractEntry(source.contract_);
break;
      case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
new(&atomicSwapAsk_) AtomicSwapAskEntry(source.atomicSwapAsk_);
break;
      case (int32_t)LedgerEntryType::ACCOUNT_ROLE:
new(&accountRole_) AccountRoleEntry(source.accountRole_);
break;
      case (int32_t)LedgerEntryType::ACCOUNT_RULE:
new(&accountRule_) AccountRuleEntry(source.accountRule_);
break;
      case (int32_t)LedgerEntryType::SIGNER_RULE:
new(&signerRule_) SignerRuleEntry(source.signerRule_);
break;
      case (int32_t)LedgerEntryType::SIGNER_ROLE:
new(&signerRole_) SignerRoleEntry(source.signerRole_);
break;
      case (int32_t)LedgerEntryType::LICENSE:
new(&license_) LicenseEntry(source.license_);
break;
      case (int32_t)LedgerEntryType::STAMP:
new(&stamp_) StampEntry(source.stamp_);
break;
      case (int32_t)LedgerEntryType::POLL:
new(&poll_) PollEntry(source.poll_);
break;
      case (int32_t)LedgerEntryType::VOTE:
new(&vote_) VoteEntry(source.vote_);
break;
      case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
new(&accountSpecificRule_) AccountSpecificRuleEntry(source.accountSpecificRule_);
break;
      case (int32_t)LedgerEntryType::SWAP:
new(&swap_) SwapEntry(source.swap_);
break;
      case (int32_t)LedgerEntryType::DATA:
new(&data_) DataEntry(source.data_);
break;
      case (int32_t)LedgerEntryType::DEFERRED_PAYMENT:
new(&deferredPayment_) DeferredPaymentEntry(source.deferredPayment_);
break;
      case (int32_t)LedgerEntryType::LIQUIDITY_POOL:
new(&liquidityPool_) LiquidityPoolEntry(source.liquidityPool_);
break;
}
}
      return *this;
    }
    _data_t &operator=(_data_t &&source) {
      if (type_ == source.type_)
{
switch (type_)
{
      case (int32_t)LedgerEntryType::ACCOUNT:
account_ = std::move(source.account_);
break;
      case (int32_t)LedgerEntryType::SIGNER:
signer_ = std::move(source.signer_);
break;
      case (int32_t)LedgerEntryType::FEE:
feeState_ = std::move(source.feeState_);
break;
      case (int32_t)LedgerEntryType::BALANCE:
balance_ = std::move(source.balance_);
break;
      case (int32_t)LedgerEntryType::ASSET:
asset_ = std::move(source.asset_);
break;
      case (int32_t)LedgerEntryType::REFERENCE_ENTRY:
reference_ = std::move(source.reference_);
break;
      case (int32_t)LedgerEntryType::STATISTICS:
stats_ = std::move(source.stats_);
break;
      case (int32_t)LedgerEntryType::ACCOUNT_LIMITS:
accountLimits_ = std::move(source.accountLimits_);
break;
      case (int32_t)LedgerEntryType::ASSET_PAIR:
assetPair_ = std::move(source.assetPair_);
break;
      case (int32_t)LedgerEntryType::OFFER_ENTRY:
offer_ = std::move(source.offer_);
break;
      case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
reviewableRequest_ = std::move(source.reviewableRequest_);
break;
      case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
externalSystemAccountID_ = std::move(source.externalSystemAccountID_);
break;
      case (int32_t)LedgerEntryType::SALE:
sale_ = std::move(source.sale_);
break;
      case (int32_t)LedgerEntryType::KEY_VALUE:
keyValue_ = std::move(source.keyValue_);
break;
      case (int32_t)LedgerEntryType::ACCOUNT_KYC:
accountKYC_ = std::move(source.accountKYC_);
break;
      case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
externalSystemAccountIDPoolEntry_ = std::move(source.externalSystemAccountIDPoolEntry_);
break;
      case (int32_t)LedgerEntryType::LIMITS_V2:
limitsV2_ = std::move(source.limitsV2_);
break;
      case (int32_t)LedgerEntryType::STATISTICS_V2:
statisticsV2_ = std::move(source.statisticsV2_);
break;
      case (int32_t)LedgerEntryType::PENDING_STATISTICS:
pendingStatistics_ = std::move(source.pendingStatistics_);
break;
      case (int32_t)LedgerEntryType::CONTRACT:
contract_ = std::move(source.contract_);
break;
      case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
atomicSwapAsk_ = std::move(source.atomicSwapAsk_);
break;
      case (int32_t)LedgerEntryType::ACCOUNT_ROLE:
accountRole_ = std::move(source.accountRole_);
break;
      case (int32_t)LedgerEntryType::ACCOUNT_RULE:
accountRule_ = std::move(source.accountRule_);
break;
      case (int32_t)LedgerEntryType::SIGNER_RULE:
signerRule_ = std::move(source.signerRule_);
break;
      case (int32_t)LedgerEntryType::SIGNER_ROLE:
signerRole_ = std::move(source.signerRole_);
break;
      case (int32_t)LedgerEntryType::LICENSE:
license_ = std::move(source.license_);
break;
      case (int32_t)LedgerEntryType::STAMP:
stamp_ = std::move(source.stamp_);
break;
      case (int32_t)LedgerEntryType::POLL:
poll_ = std::move(source.poll_);
break;
      case (int32_t)LedgerEntryType::VOTE:
vote_ = std::move(source.vote_);
break;
      case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
accountSpecificRule_ = std::move(source.accountSpecificRule_);
break;
      case (int32_t)LedgerEntryType::SWAP:
swap_ = std::move(source.swap_);
break;
      case (int32_t)LedgerEntryType::DATA:
data_ = std::move(source.data_);
break;
      case (int32_t)LedgerEntryType::DEFERRED_PAYMENT:
deferredPayment_ = std::move(source.deferredPayment_);
break;
      case (int32_t)LedgerEntryType::LIQUIDITY_POOL:
liquidityPool_ = std::move(source.liquidityPool_);
break;
}
}
else {this->~_data_t();
      type_ = std::move(source.type_);
switch (type_)
{
      case (int32_t)LedgerEntryType::ACCOUNT:
new(&account_) AccountEntry(std::move(source.account_));
break;
      case (int32_t)LedgerEntryType::SIGNER:
new(&signer_) SignerEntry(std::move(source.signer_));
break;
      case (int32_t)LedgerEntryType::FEE:
new(&feeState_) FeeEntry(std::move(source.feeState_));
break;
      case (int32_t)LedgerEntryType::BALANCE:
new(&balance_) BalanceEntry(std::move(source.balance_));
break;
      case (int32_t)LedgerEntryType::ASSET:
new(&asset_) AssetEntry(std::move(source.asset_));
break;
      case (int32_t)LedgerEntryType::REFERENCE_ENTRY:
new(&reference_) ReferenceEntry(std::move(source.reference_));
break;
      case (int32_t)LedgerEntryType::STATISTICS:
new(&stats_) StatisticsEntry(std::move(source.stats_));
break;
      case (int32_t)LedgerEntryType::ACCOUNT_LIMITS:
new(&accountLimits_) AccountLimitsEntry(std::move(source.accountLimits_));
break;
      case (int32_t)LedgerEntryType::ASSET_PAIR:
new(&assetPair_) AssetPairEntry(std::move(source.assetPair_));
break;
      case (int32_t)LedgerEntryType::OFFER_ENTRY:
new(&offer_) OfferEntry(std::move(source.offer_));
break;
      case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
new(&reviewableRequest_) ReviewableRequestEntry(std::move(source.reviewableRequest_));
break;
      case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
new(&externalSystemAccountID_) ExternalSystemAccountID(std::move(source.externalSystemAccountID_));
break;
      case (int32_t)LedgerEntryType::SALE:
new(&sale_) SaleEntry(std::move(source.sale_));
break;
      case (int32_t)LedgerEntryType::KEY_VALUE:
new(&keyValue_) KeyValueEntry(std::move(source.keyValue_));
break;
      case (int32_t)LedgerEntryType::ACCOUNT_KYC:
new(&accountKYC_) AccountKYCEntry(std::move(source.accountKYC_));
break;
      case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
new(&externalSystemAccountIDPoolEntry_) ExternalSystemAccountIDPoolEntry(std::move(source.externalSystemAccountIDPoolEntry_));
break;
      case (int32_t)LedgerEntryType::LIMITS_V2:
new(&limitsV2_) LimitsV2Entry(std::move(source.limitsV2_));
break;
      case (int32_t)LedgerEntryType::STATISTICS_V2:
new(&statisticsV2_) StatisticsV2Entry(std::move(source.statisticsV2_));
break;
      case (int32_t)LedgerEntryType::PENDING_STATISTICS:
new(&pendingStatistics_) PendingStatisticsEntry(std::move(source.pendingStatistics_));
break;
      case (int32_t)LedgerEntryType::CONTRACT:
new(&contract_) ContractEntry(std::move(source.contract_));
break;
      case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
new(&atomicSwapAsk_) AtomicSwapAskEntry(std::move(source.atomicSwapAsk_));
break;
      case (int32_t)LedgerEntryType::ACCOUNT_ROLE:
new(&accountRole_) AccountRoleEntry(std::move(source.accountRole_));
break;
      case (int32_t)LedgerEntryType::ACCOUNT_RULE:
new(&accountRule_) AccountRuleEntry(std::move(source.accountRule_));
break;
      case (int32_t)LedgerEntryType::SIGNER_RULE:
new(&signerRule_) SignerRuleEntry(std::move(source.signerRule_));
break;
      case (int32_t)LedgerEntryType::SIGNER_ROLE:
new(&signerRole_) SignerRoleEntry(std::move(source.signerRole_));
break;
      case (int32_t)LedgerEntryType::LICENSE:
new(&license_) LicenseEntry(std::move(source.license_));
break;
      case (int32_t)LedgerEntryType::STAMP:
new(&stamp_) StampEntry(std::move(source.stamp_));
break;
      case (int32_t)LedgerEntryType::POLL:
new(&poll_) PollEntry(std::move(source.poll_));
break;
      case (int32_t)LedgerEntryType::VOTE:
new(&vote_) VoteEntry(std::move(source.vote_));
break;
      case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
new(&accountSpecificRule_) AccountSpecificRuleEntry(std::move(source.accountSpecificRule_));
break;
      case (int32_t)LedgerEntryType::SWAP:
new(&swap_) SwapEntry(std::move(source.swap_));
break;
      case (int32_t)LedgerEntryType::DATA:
new(&data_) DataEntry(std::move(source.data_));
break;
      case (int32_t)LedgerEntryType::DEFERRED_PAYMENT:
new(&deferredPayment_) DeferredPaymentEntry(std::move(source.deferredPayment_));
break;
      case (int32_t)LedgerEntryType::LIQUIDITY_POOL:
new(&liquidityPool_) LiquidityPoolEntry(std::move(source.liquidityPool_));
break;
}
}
      return *this;
    }

    LedgerEntryType type() const { return LedgerEntryType(type_); }
    _data_t &type(LedgerEntryType _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    AccountEntry &account() {
      if (_xdr_field_number(type_) == 1)
        return account_;
      throw xdr::xdr_wrong_union("_data_t: account accessed when not selected");
    }
    const AccountEntry &account() const {
      if (_xdr_field_number(type_) == 1)
        return account_;
      throw xdr::xdr_wrong_union("_data_t: account accessed when not selected");
    }
    SignerEntry &signer() {
      if (_xdr_field_number(type_) == 2)
        return signer_;
      throw xdr::xdr_wrong_union("_data_t: signer accessed when not selected");
    }
    const SignerEntry &signer() const {
      if (_xdr_field_number(type_) == 2)
        return signer_;
      throw xdr::xdr_wrong_union("_data_t: signer accessed when not selected");
    }
    FeeEntry &feeState() {
      if (_xdr_field_number(type_) == 3)
        return feeState_;
      throw xdr::xdr_wrong_union("_data_t: feeState accessed when not selected");
    }
    const FeeEntry &feeState() const {
      if (_xdr_field_number(type_) == 3)
        return feeState_;
      throw xdr::xdr_wrong_union("_data_t: feeState accessed when not selected");
    }
    BalanceEntry &balance() {
      if (_xdr_field_number(type_) == 4)
        return balance_;
      throw xdr::xdr_wrong_union("_data_t: balance accessed when not selected");
    }
    const BalanceEntry &balance() const {
      if (_xdr_field_number(type_) == 4)
        return balance_;
      throw xdr::xdr_wrong_union("_data_t: balance accessed when not selected");
    }
    AssetEntry &asset() {
      if (_xdr_field_number(type_) == 5)
        return asset_;
      throw xdr::xdr_wrong_union("_data_t: asset accessed when not selected");
    }
    const AssetEntry &asset() const {
      if (_xdr_field_number(type_) == 5)
        return asset_;
      throw xdr::xdr_wrong_union("_data_t: asset accessed when not selected");
    }
    ReferenceEntry &reference() {
      if (_xdr_field_number(type_) == 6)
        return reference_;
      throw xdr::xdr_wrong_union("_data_t: reference accessed when not selected");
    }
    const ReferenceEntry &reference() const {
      if (_xdr_field_number(type_) == 6)
        return reference_;
      throw xdr::xdr_wrong_union("_data_t: reference accessed when not selected");
    }
    StatisticsEntry &stats() {
      if (_xdr_field_number(type_) == 7)
        return stats_;
      throw xdr::xdr_wrong_union("_data_t: stats accessed when not selected");
    }
    const StatisticsEntry &stats() const {
      if (_xdr_field_number(type_) == 7)
        return stats_;
      throw xdr::xdr_wrong_union("_data_t: stats accessed when not selected");
    }
    AccountLimitsEntry &accountLimits() {
      if (_xdr_field_number(type_) == 8)
        return accountLimits_;
      throw xdr::xdr_wrong_union("_data_t: accountLimits accessed when not selected");
    }
    const AccountLimitsEntry &accountLimits() const {
      if (_xdr_field_number(type_) == 8)
        return accountLimits_;
      throw xdr::xdr_wrong_union("_data_t: accountLimits accessed when not selected");
    }
    AssetPairEntry &assetPair() {
      if (_xdr_field_number(type_) == 9)
        return assetPair_;
      throw xdr::xdr_wrong_union("_data_t: assetPair accessed when not selected");
    }
    const AssetPairEntry &assetPair() const {
      if (_xdr_field_number(type_) == 9)
        return assetPair_;
      throw xdr::xdr_wrong_union("_data_t: assetPair accessed when not selected");
    }
    OfferEntry &offer() {
      if (_xdr_field_number(type_) == 10)
        return offer_;
      throw xdr::xdr_wrong_union("_data_t: offer accessed when not selected");
    }
    const OfferEntry &offer() const {
      if (_xdr_field_number(type_) == 10)
        return offer_;
      throw xdr::xdr_wrong_union("_data_t: offer accessed when not selected");
    }
    ReviewableRequestEntry &reviewableRequest() {
      if (_xdr_field_number(type_) == 11)
        return reviewableRequest_;
      throw xdr::xdr_wrong_union("_data_t: reviewableRequest accessed when not selected");
    }
    const ReviewableRequestEntry &reviewableRequest() const {
      if (_xdr_field_number(type_) == 11)
        return reviewableRequest_;
      throw xdr::xdr_wrong_union("_data_t: reviewableRequest accessed when not selected");
    }
    ExternalSystemAccountID &externalSystemAccountID() {
      if (_xdr_field_number(type_) == 12)
        return externalSystemAccountID_;
      throw xdr::xdr_wrong_union("_data_t: externalSystemAccountID accessed when not selected");
    }
    const ExternalSystemAccountID &externalSystemAccountID() const {
      if (_xdr_field_number(type_) == 12)
        return externalSystemAccountID_;
      throw xdr::xdr_wrong_union("_data_t: externalSystemAccountID accessed when not selected");
    }
    SaleEntry &sale() {
      if (_xdr_field_number(type_) == 13)
        return sale_;
      throw xdr::xdr_wrong_union("_data_t: sale accessed when not selected");
    }
    const SaleEntry &sale() const {
      if (_xdr_field_number(type_) == 13)
        return sale_;
      throw xdr::xdr_wrong_union("_data_t: sale accessed when not selected");
    }
    KeyValueEntry &keyValue() {
      if (_xdr_field_number(type_) == 14)
        return keyValue_;
      throw xdr::xdr_wrong_union("_data_t: keyValue accessed when not selected");
    }
    const KeyValueEntry &keyValue() const {
      if (_xdr_field_number(type_) == 14)
        return keyValue_;
      throw xdr::xdr_wrong_union("_data_t: keyValue accessed when not selected");
    }
    AccountKYCEntry &accountKYC() {
      if (_xdr_field_number(type_) == 15)
        return accountKYC_;
      throw xdr::xdr_wrong_union("_data_t: accountKYC accessed when not selected");
    }
    const AccountKYCEntry &accountKYC() const {
      if (_xdr_field_number(type_) == 15)
        return accountKYC_;
      throw xdr::xdr_wrong_union("_data_t: accountKYC accessed when not selected");
    }
    ExternalSystemAccountIDPoolEntry &externalSystemAccountIDPoolEntry() {
      if (_xdr_field_number(type_) == 16)
        return externalSystemAccountIDPoolEntry_;
      throw xdr::xdr_wrong_union("_data_t: externalSystemAccountIDPoolEntry accessed when not selected");
    }
    const ExternalSystemAccountIDPoolEntry &externalSystemAccountIDPoolEntry() const {
      if (_xdr_field_number(type_) == 16)
        return externalSystemAccountIDPoolEntry_;
      throw xdr::xdr_wrong_union("_data_t: externalSystemAccountIDPoolEntry accessed when not selected");
    }
    LimitsV2Entry &limitsV2() {
      if (_xdr_field_number(type_) == 17)
        return limitsV2_;
      throw xdr::xdr_wrong_union("_data_t: limitsV2 accessed when not selected");
    }
    const LimitsV2Entry &limitsV2() const {
      if (_xdr_field_number(type_) == 17)
        return limitsV2_;
      throw xdr::xdr_wrong_union("_data_t: limitsV2 accessed when not selected");
    }
    StatisticsV2Entry &statisticsV2() {
      if (_xdr_field_number(type_) == 18)
        return statisticsV2_;
      throw xdr::xdr_wrong_union("_data_t: statisticsV2 accessed when not selected");
    }
    const StatisticsV2Entry &statisticsV2() const {
      if (_xdr_field_number(type_) == 18)
        return statisticsV2_;
      throw xdr::xdr_wrong_union("_data_t: statisticsV2 accessed when not selected");
    }
    PendingStatisticsEntry &pendingStatistics() {
      if (_xdr_field_number(type_) == 19)
        return pendingStatistics_;
      throw xdr::xdr_wrong_union("_data_t: pendingStatistics accessed when not selected");
    }
    const PendingStatisticsEntry &pendingStatistics() const {
      if (_xdr_field_number(type_) == 19)
        return pendingStatistics_;
      throw xdr::xdr_wrong_union("_data_t: pendingStatistics accessed when not selected");
    }
    ContractEntry &contract() {
      if (_xdr_field_number(type_) == 20)
        return contract_;
      throw xdr::xdr_wrong_union("_data_t: contract accessed when not selected");
    }
    const ContractEntry &contract() const {
      if (_xdr_field_number(type_) == 20)
        return contract_;
      throw xdr::xdr_wrong_union("_data_t: contract accessed when not selected");
    }
    AtomicSwapAskEntry &atomicSwapAsk() {
      if (_xdr_field_number(type_) == 21)
        return atomicSwapAsk_;
      throw xdr::xdr_wrong_union("_data_t: atomicSwapAsk accessed when not selected");
    }
    const AtomicSwapAskEntry &atomicSwapAsk() const {
      if (_xdr_field_number(type_) == 21)
        return atomicSwapAsk_;
      throw xdr::xdr_wrong_union("_data_t: atomicSwapAsk accessed when not selected");
    }
    AccountRoleEntry &accountRole() {
      if (_xdr_field_number(type_) == 22)
        return accountRole_;
      throw xdr::xdr_wrong_union("_data_t: accountRole accessed when not selected");
    }
    const AccountRoleEntry &accountRole() const {
      if (_xdr_field_number(type_) == 22)
        return accountRole_;
      throw xdr::xdr_wrong_union("_data_t: accountRole accessed when not selected");
    }
    AccountRuleEntry &accountRule() {
      if (_xdr_field_number(type_) == 23)
        return accountRule_;
      throw xdr::xdr_wrong_union("_data_t: accountRule accessed when not selected");
    }
    const AccountRuleEntry &accountRule() const {
      if (_xdr_field_number(type_) == 23)
        return accountRule_;
      throw xdr::xdr_wrong_union("_data_t: accountRule accessed when not selected");
    }
    SignerRuleEntry &signerRule() {
      if (_xdr_field_number(type_) == 24)
        return signerRule_;
      throw xdr::xdr_wrong_union("_data_t: signerRule accessed when not selected");
    }
    const SignerRuleEntry &signerRule() const {
      if (_xdr_field_number(type_) == 24)
        return signerRule_;
      throw xdr::xdr_wrong_union("_data_t: signerRule accessed when not selected");
    }
    SignerRoleEntry &signerRole() {
      if (_xdr_field_number(type_) == 25)
        return signerRole_;
      throw xdr::xdr_wrong_union("_data_t: signerRole accessed when not selected");
    }
    const SignerRoleEntry &signerRole() const {
      if (_xdr_field_number(type_) == 25)
        return signerRole_;
      throw xdr::xdr_wrong_union("_data_t: signerRole accessed when not selected");
    }
    LicenseEntry &license() {
      if (_xdr_field_number(type_) == 26)
        return license_;
      throw xdr::xdr_wrong_union("_data_t: license accessed when not selected");
    }
    const LicenseEntry &license() const {
      if (_xdr_field_number(type_) == 26)
        return license_;
      throw xdr::xdr_wrong_union("_data_t: license accessed when not selected");
    }
    StampEntry &stamp() {
      if (_xdr_field_number(type_) == 27)
        return stamp_;
      throw xdr::xdr_wrong_union("_data_t: stamp accessed when not selected");
    }
    const StampEntry &stamp() const {
      if (_xdr_field_number(type_) == 27)
        return stamp_;
      throw xdr::xdr_wrong_union("_data_t: stamp accessed when not selected");
    }
    PollEntry &poll() {
      if (_xdr_field_number(type_) == 28)
        return poll_;
      throw xdr::xdr_wrong_union("_data_t: poll accessed when not selected");
    }
    const PollEntry &poll() const {
      if (_xdr_field_number(type_) == 28)
        return poll_;
      throw xdr::xdr_wrong_union("_data_t: poll accessed when not selected");
    }
    VoteEntry &vote() {
      if (_xdr_field_number(type_) == 29)
        return vote_;
      throw xdr::xdr_wrong_union("_data_t: vote accessed when not selected");
    }
    const VoteEntry &vote() const {
      if (_xdr_field_number(type_) == 29)
        return vote_;
      throw xdr::xdr_wrong_union("_data_t: vote accessed when not selected");
    }
    AccountSpecificRuleEntry &accountSpecificRule() {
      if (_xdr_field_number(type_) == 30)
        return accountSpecificRule_;
      throw xdr::xdr_wrong_union("_data_t: accountSpecificRule accessed when not selected");
    }
    const AccountSpecificRuleEntry &accountSpecificRule() const {
      if (_xdr_field_number(type_) == 30)
        return accountSpecificRule_;
      throw xdr::xdr_wrong_union("_data_t: accountSpecificRule accessed when not selected");
    }
    SwapEntry &swap() {
      if (_xdr_field_number(type_) == 31)
        return swap_;
      throw xdr::xdr_wrong_union("_data_t: swap accessed when not selected");
    }
    const SwapEntry &swap() const {
      if (_xdr_field_number(type_) == 31)
        return swap_;
      throw xdr::xdr_wrong_union("_data_t: swap accessed when not selected");
    }
    DataEntry &data() {
      if (_xdr_field_number(type_) == 32)
        return data_;
      throw xdr::xdr_wrong_union("_data_t: data accessed when not selected");
    }
    const DataEntry &data() const {
      if (_xdr_field_number(type_) == 32)
        return data_;
      throw xdr::xdr_wrong_union("_data_t: data accessed when not selected");
    }
    DeferredPaymentEntry &deferredPayment() {
      if (_xdr_field_number(type_) == 33)
        return deferredPayment_;
      throw xdr::xdr_wrong_union("_data_t: deferredPayment accessed when not selected");
    }
    const DeferredPaymentEntry &deferredPayment() const {
      if (_xdr_field_number(type_) == 33)
        return deferredPayment_;
      throw xdr::xdr_wrong_union("_data_t: deferredPayment accessed when not selected");
    }
    LiquidityPoolEntry &liquidityPool() {
      if (_xdr_field_number(type_) == 34)
        return liquidityPool_;
      throw xdr::xdr_wrong_union("_data_t: liquidityPool accessed when not selected");
    }
    const LiquidityPoolEntry &liquidityPool() const {
      if (_xdr_field_number(type_) == 34)
        return liquidityPool_;
      throw xdr::xdr_wrong_union("_data_t: liquidityPool accessed when not selected");
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

  uint32 lastModifiedLedgerSeq{};
  _data_t data{};
  _ext_t ext{};

  LedgerEntry() = default;
  template<typename _lastModifiedLedgerSeq_T,
           typename _data_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint32, _lastModifiedLedgerSeq_T>::value
                          && std::is_constructible<_data_t, _data_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit LedgerEntry(_lastModifiedLedgerSeq_T &&_lastModifiedLedgerSeq,
                       _data_T &&_data,
                       _ext_T &&_ext)
    : lastModifiedLedgerSeq(std::forward<_lastModifiedLedgerSeq_T>(_lastModifiedLedgerSeq)),
      data(std::forward<_data_T>(_data)),
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

enum class EnvelopeType : std::int32_t {
  SCP = 1,
  TX = 2,
  AUTH = 3,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::EnvelopeType>
  : xdr_integral_base<::stellar::EnvelopeType, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::EnvelopeType val) {
    switch (val) {
    case ::stellar::EnvelopeType::SCP:
      return "SCP";
    case ::stellar::EnvelopeType::TX:
      return "TX";
    case ::stellar::EnvelopeType::AUTH:
      return "AUTH";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::EnvelopeType::SCP,
      (int32_t)::stellar::EnvelopeType::TX,
      (int32_t)::stellar::EnvelopeType::AUTH
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

}

#endif // !__XDR_LEDGER_ENTRIES_H_INCLUDED__
