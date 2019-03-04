// -*- C++ -*-
// Automatically generated from Stellar-ledger-entries.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_LEDGER_ENTRIES_H_INCLUDED__
#define __XDR_STELLAR_LEDGER_ENTRIES_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-types.h"
#include "xdr/Stellar-ledger-entries-account.h"
#include "xdr/Stellar-ledger-entries-signer.h"
#include "xdr/Stellar-ledger-entries-fee.h"
#include "xdr/Stellar-ledger-entries-balance.h"
#include "xdr/Stellar-ledger-entries-asset.h"
#include "xdr/Stellar-ledger-entries-asset-pair.h"
#include "xdr/Stellar-ledger-entries-reference.h"
#include "xdr/Stellar-ledger-entries-statistics.h"
#include "xdr/Stellar-ledger-entries-offer.h"
#include "xdr/Stellar-ledger-entries-account-limits.h"
#include "xdr/Stellar-ledger-entries-reviewable-request.h"
#include "xdr/Stellar-ledger-entries-external-system-id.h"
#include "xdr/Stellar-ledger-entries-sale.h"
#include "xdr/Stellar-ledger-entries-key-value.h"
#include "xdr/Stellar-ledger-entries-account-KYC.h"
#include "xdr/Stellar-ledger-entries-external-system-id-pool-entry.h"
#include "xdr/Stellar-ledger-entries-statistics-v2.h"
#include "xdr/Stellar-ledger-entries-pending-statistics.h"
#include "xdr/Stellar-ledger-entries-contract.h"
#include "xdr/Stellar-ledger-entries-atomic-swap-bid.h"
#include "xdr/Stellar-ledger-entries-account-role.h"
#include "xdr/Stellar-ledger-entries-account-rule.h"
#include "xdr/Stellar-ledger-entries-signer-role.h"
#include "xdr/Stellar-ledger-entries-signer-rule.h"
#include "xdr/Stellar-ledger-entries-license.h"
#include "xdr/Stellar-ledger-entries-stamp.h"

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
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
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

struct LedgerEntry {
  struct _data_t {
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
      AtomicSwapBidEntry atomicSwapBid_;
      AccountRoleEntry accountRole_;
      AccountRuleEntry accountRule_;
      SignerRuleEntry signerRule_;
      SignerRoleEntry signerRole_;
      LicenseEntry license_;
      StampEntry stamp_;
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
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
        LedgerEntryType::ATOMIC_SWAP_BID,
        LedgerEntryType::ACCOUNT_ROLE,
        LedgerEntryType::ACCOUNT_RULE,
        LedgerEntryType::SIGNER_RULE,
        LedgerEntryType::SIGNER_ROLE,
        LedgerEntryType::LICENSE,
        LedgerEntryType::STAMP
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
        : which == (int32_t)LedgerEntryType::ATOMIC_SWAP_BID ? 21
        : which == (int32_t)LedgerEntryType::ACCOUNT_ROLE ? 22
        : which == (int32_t)LedgerEntryType::ACCOUNT_RULE ? 23
        : which == (int32_t)LedgerEntryType::SIGNER_RULE ? 24
        : which == (int32_t)LedgerEntryType::SIGNER_ROLE ? 25
        : which == (int32_t)LedgerEntryType::LICENSE ? 26
        : which == (int32_t)LedgerEntryType::STAMP ? 27
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
      case (int32_t)LedgerEntryType::ATOMIC_SWAP_BID:
        _f(&_data_t::atomicSwapBid_, std::forward<_A>(_a)...);
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
        type_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
      }
      else
        type_ = which;
    }
    explicit _data_t(LedgerEntryType which = LedgerEntryType{}) : type_((int32_t)which) {
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    _data_t(const _data_t &source) : type_(source.type_) {
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
    }
    _data_t(_data_t &&source) : type_(source.type_) {
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                        std::move(source));
    }
    ~_data_t() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
    _data_t &operator=(const _data_t &source) {
      if (_xdr_field_number(type_)
          == _xdr_field_number(source.type_))
        _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
      else {
        this->~_data_t();
        type_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
      }
      type_ = source.type_;
      return *this;
    }
    _data_t &operator=(_data_t &&source) {
      if (_xdr_field_number(type_)
           == _xdr_field_number(source.type_))
        _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                          std::move(source));
      else {
        this->~_data_t();
        type_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                          std::move(source));
      }
      type_ = source.type_;
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
    AtomicSwapBidEntry &atomicSwapBid() {
      if (_xdr_field_number(type_) == 21)
        return atomicSwapBid_;
      throw xdr::xdr_wrong_union("_data_t: atomicSwapBid accessed when not selected");
    }
    const AtomicSwapBidEntry &atomicSwapBid() const {
      if (_xdr_field_number(type_) == 21)
        return atomicSwapBid_;
      throw xdr::xdr_wrong_union("_data_t: atomicSwapBid accessed when not selected");
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LedgerEntry::_data_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerEntry::_data_t;
  using case_type = ::stellar::LedgerEntry::_data_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "account";
    case 2:
      return "signer";
    case 3:
      return "feeState";
    case 4:
      return "balance";
    case 5:
      return "asset";
    case 6:
      return "reference";
    case 7:
      return "stats";
    case 8:
      return "accountLimits";
    case 9:
      return "assetPair";
    case 10:
      return "offer";
    case 11:
      return "reviewableRequest";
    case 12:
      return "externalSystemAccountID";
    case 13:
      return "sale";
    case 14:
      return "keyValue";
    case 15:
      return "accountKYC";
    case 16:
      return "externalSystemAccountIDPoolEntry";
    case 17:
      return "limitsV2";
    case 18:
      return "statisticsV2";
    case 19:
      return "pendingStatistics";
    case 20:
      return "contract";
    case 21:
      return "atomicSwapBid";
    case 22:
      return "accountRole";
    case 23:
      return "accountRule";
    case 24:
      return "signerRule";
    case 25:
      return "signerRole";
    case 26:
      return "license";
    case 27:
      return "stamp";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerEntry::_data_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in _data_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerEntry::_data_t &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in _data_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerEntry::_data_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.type(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerEntry::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerEntry::_ext_t;
  using case_type = ::stellar::LedgerEntry::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerEntry::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerEntry::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerEntry::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerEntry>
  : xdr_struct_base<field_ptr<::stellar::LedgerEntry,
                              decltype(::stellar::LedgerEntry::lastModifiedLedgerSeq),
                              &::stellar::LedgerEntry::lastModifiedLedgerSeq>,
                    field_ptr<::stellar::LedgerEntry,
                              decltype(::stellar::LedgerEntry::data),
                              &::stellar::LedgerEntry::data>,
                    field_ptr<::stellar::LedgerEntry,
                              decltype(::stellar::LedgerEntry::ext),
                              &::stellar::LedgerEntry::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerEntry &obj) {
    archive(ar, obj.lastModifiedLedgerSeq, "lastModifiedLedgerSeq");
    archive(ar, obj.data, "data");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerEntry &obj) {
    archive(ar, obj.lastModifiedLedgerSeq, "lastModifiedLedgerSeq");
    archive(ar, obj.data, "data");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum class EnvelopeType : std::int32_t {
  SCP = 1,
  TX = 2,
  AUTH = 3,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::EnvelopeType>
  : xdr_integral_base<::stellar::EnvelopeType, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
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

#endif // !__XDR_STELLAR_LEDGER_ENTRIES_H_INCLUDED__
