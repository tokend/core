#include "ledger-entries.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
LedgerEntry::_data_t::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (type_)
{
    case (int32_t)LedgerEntryType::ACCOUNT:
return u.from_bytes(account_);
    case (int32_t)LedgerEntryType::SIGNER:
return u.from_bytes(signer_);
    case (int32_t)LedgerEntryType::FEE:
return u.from_bytes(feeState_);
    case (int32_t)LedgerEntryType::BALANCE:
return u.from_bytes(balance_);
    case (int32_t)LedgerEntryType::ASSET:
return u.from_bytes(asset_);
    case (int32_t)LedgerEntryType::REFERENCE_ENTRY:
return u.from_bytes(reference_);
    case (int32_t)LedgerEntryType::STATISTICS:
return u.from_bytes(stats_);
    case (int32_t)LedgerEntryType::ACCOUNT_LIMITS:
return u.from_bytes(accountLimits_);
    case (int32_t)LedgerEntryType::ASSET_PAIR:
return u.from_bytes(assetPair_);
    case (int32_t)LedgerEntryType::OFFER_ENTRY:
return u.from_bytes(offer_);
    case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
return u.from_bytes(reviewableRequest_);
    case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
return u.from_bytes(externalSystemAccountID_);
    case (int32_t)LedgerEntryType::SALE:
return u.from_bytes(sale_);
    case (int32_t)LedgerEntryType::KEY_VALUE:
return u.from_bytes(keyValue_);
    case (int32_t)LedgerEntryType::ACCOUNT_KYC:
return u.from_bytes(accountKYC_);
    case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
return u.from_bytes(externalSystemAccountIDPoolEntry_);
    case (int32_t)LedgerEntryType::LIMITS_V2:
return u.from_bytes(limitsV2_);
    case (int32_t)LedgerEntryType::STATISTICS_V2:
return u.from_bytes(statisticsV2_);
    case (int32_t)LedgerEntryType::PENDING_STATISTICS:
return u.from_bytes(pendingStatistics_);
    case (int32_t)LedgerEntryType::CONTRACT:
return u.from_bytes(contract_);
    case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
return u.from_bytes(atomicSwapAsk_);
    case (int32_t)LedgerEntryType::ACCOUNT_ROLE:
return u.from_bytes(accountRole_);
    case (int32_t)LedgerEntryType::ACCOUNT_RULE:
return u.from_bytes(accountRule_);
    case (int32_t)LedgerEntryType::SIGNER_RULE:
return u.from_bytes(signerRule_);
    case (int32_t)LedgerEntryType::SIGNER_ROLE:
return u.from_bytes(signerRole_);
    case (int32_t)LedgerEntryType::LICENSE:
return u.from_bytes(license_);
    case (int32_t)LedgerEntryType::STAMP:
return u.from_bytes(stamp_);
    case (int32_t)LedgerEntryType::POLL:
return u.from_bytes(poll_);
    case (int32_t)LedgerEntryType::VOTE:
return u.from_bytes(vote_);
    case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
return u.from_bytes(accountSpecificRule_);
    case (int32_t)LedgerEntryType::SWAP:
return u.from_bytes(swap_);
    case (int32_t)LedgerEntryType::DATA:
return u.from_bytes(data_);
}
return false;
}
bool
LedgerEntry::_data_t::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(type_);
if (!ok)
{
return false;
}
switch (type_)
{

    case (int32_t)LedgerEntryType::ACCOUNT:
return m.to_bytes(account_);
    case (int32_t)LedgerEntryType::SIGNER:
return m.to_bytes(signer_);
    case (int32_t)LedgerEntryType::FEE:
return m.to_bytes(feeState_);
    case (int32_t)LedgerEntryType::BALANCE:
return m.to_bytes(balance_);
    case (int32_t)LedgerEntryType::ASSET:
return m.to_bytes(asset_);
    case (int32_t)LedgerEntryType::REFERENCE_ENTRY:
return m.to_bytes(reference_);
    case (int32_t)LedgerEntryType::STATISTICS:
return m.to_bytes(stats_);
    case (int32_t)LedgerEntryType::ACCOUNT_LIMITS:
return m.to_bytes(accountLimits_);
    case (int32_t)LedgerEntryType::ASSET_PAIR:
return m.to_bytes(assetPair_);
    case (int32_t)LedgerEntryType::OFFER_ENTRY:
return m.to_bytes(offer_);
    case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
return m.to_bytes(reviewableRequest_);
    case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
return m.to_bytes(externalSystemAccountID_);
    case (int32_t)LedgerEntryType::SALE:
return m.to_bytes(sale_);
    case (int32_t)LedgerEntryType::KEY_VALUE:
return m.to_bytes(keyValue_);
    case (int32_t)LedgerEntryType::ACCOUNT_KYC:
return m.to_bytes(accountKYC_);
    case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
return m.to_bytes(externalSystemAccountIDPoolEntry_);
    case (int32_t)LedgerEntryType::LIMITS_V2:
return m.to_bytes(limitsV2_);
    case (int32_t)LedgerEntryType::STATISTICS_V2:
return m.to_bytes(statisticsV2_);
    case (int32_t)LedgerEntryType::PENDING_STATISTICS:
return m.to_bytes(pendingStatistics_);
    case (int32_t)LedgerEntryType::CONTRACT:
return m.to_bytes(contract_);
    case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
return m.to_bytes(atomicSwapAsk_);
    case (int32_t)LedgerEntryType::ACCOUNT_ROLE:
return m.to_bytes(accountRole_);
    case (int32_t)LedgerEntryType::ACCOUNT_RULE:
return m.to_bytes(accountRule_);
    case (int32_t)LedgerEntryType::SIGNER_RULE:
return m.to_bytes(signerRule_);
    case (int32_t)LedgerEntryType::SIGNER_ROLE:
return m.to_bytes(signerRole_);
    case (int32_t)LedgerEntryType::LICENSE:
return m.to_bytes(license_);
    case (int32_t)LedgerEntryType::STAMP:
return m.to_bytes(stamp_);
    case (int32_t)LedgerEntryType::POLL:
return m.to_bytes(poll_);
    case (int32_t)LedgerEntryType::VOTE:
return m.to_bytes(vote_);
    case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
return m.to_bytes(accountSpecificRule_);
    case (int32_t)LedgerEntryType::SWAP:
return m.to_bytes(swap_);
    case (int32_t)LedgerEntryType::DATA:
return m.to_bytes(data_);
}
return false;
}
void
LedgerEntry::_data_t::count_size(xdr::measurer& m) const
{
m.count_size(type_);
switch (type_)
{

    case (int32_t)LedgerEntryType::ACCOUNT:
return m.count_size(account_);
    case (int32_t)LedgerEntryType::SIGNER:
return m.count_size(signer_);
    case (int32_t)LedgerEntryType::FEE:
return m.count_size(feeState_);
    case (int32_t)LedgerEntryType::BALANCE:
return m.count_size(balance_);
    case (int32_t)LedgerEntryType::ASSET:
return m.count_size(asset_);
    case (int32_t)LedgerEntryType::REFERENCE_ENTRY:
return m.count_size(reference_);
    case (int32_t)LedgerEntryType::STATISTICS:
return m.count_size(stats_);
    case (int32_t)LedgerEntryType::ACCOUNT_LIMITS:
return m.count_size(accountLimits_);
    case (int32_t)LedgerEntryType::ASSET_PAIR:
return m.count_size(assetPair_);
    case (int32_t)LedgerEntryType::OFFER_ENTRY:
return m.count_size(offer_);
    case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
return m.count_size(reviewableRequest_);
    case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
return m.count_size(externalSystemAccountID_);
    case (int32_t)LedgerEntryType::SALE:
return m.count_size(sale_);
    case (int32_t)LedgerEntryType::KEY_VALUE:
return m.count_size(keyValue_);
    case (int32_t)LedgerEntryType::ACCOUNT_KYC:
return m.count_size(accountKYC_);
    case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
return m.count_size(externalSystemAccountIDPoolEntry_);
    case (int32_t)LedgerEntryType::LIMITS_V2:
return m.count_size(limitsV2_);
    case (int32_t)LedgerEntryType::STATISTICS_V2:
return m.count_size(statisticsV2_);
    case (int32_t)LedgerEntryType::PENDING_STATISTICS:
return m.count_size(pendingStatistics_);
    case (int32_t)LedgerEntryType::CONTRACT:
return m.count_size(contract_);
    case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
return m.count_size(atomicSwapAsk_);
    case (int32_t)LedgerEntryType::ACCOUNT_ROLE:
return m.count_size(accountRole_);
    case (int32_t)LedgerEntryType::ACCOUNT_RULE:
return m.count_size(accountRule_);
    case (int32_t)LedgerEntryType::SIGNER_RULE:
return m.count_size(signerRule_);
    case (int32_t)LedgerEntryType::SIGNER_ROLE:
return m.count_size(signerRole_);
    case (int32_t)LedgerEntryType::LICENSE:
return m.count_size(license_);
    case (int32_t)LedgerEntryType::STAMP:
return m.count_size(stamp_);
    case (int32_t)LedgerEntryType::POLL:
return m.count_size(poll_);
    case (int32_t)LedgerEntryType::VOTE:
return m.count_size(vote_);
    case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
return m.count_size(accountSpecificRule_);
    case (int32_t)LedgerEntryType::SWAP:
return m.count_size(swap_);
    case (int32_t)LedgerEntryType::DATA:
return m.count_size(data_);
}
}
bool
LedgerEntry::_data_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_data_t const&>(other_abstract);
if (other.type_ != type_) return false;
switch (type_)
{
    case (int32_t)LedgerEntryType::ACCOUNT:
return account_ == other.account_;
    case (int32_t)LedgerEntryType::SIGNER:
return signer_ == other.signer_;
    case (int32_t)LedgerEntryType::FEE:
return feeState_ == other.feeState_;
    case (int32_t)LedgerEntryType::BALANCE:
return balance_ == other.balance_;
    case (int32_t)LedgerEntryType::ASSET:
return asset_ == other.asset_;
    case (int32_t)LedgerEntryType::REFERENCE_ENTRY:
return reference_ == other.reference_;
    case (int32_t)LedgerEntryType::STATISTICS:
return stats_ == other.stats_;
    case (int32_t)LedgerEntryType::ACCOUNT_LIMITS:
return accountLimits_ == other.accountLimits_;
    case (int32_t)LedgerEntryType::ASSET_PAIR:
return assetPair_ == other.assetPair_;
    case (int32_t)LedgerEntryType::OFFER_ENTRY:
return offer_ == other.offer_;
    case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
return reviewableRequest_ == other.reviewableRequest_;
    case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
return externalSystemAccountID_ == other.externalSystemAccountID_;
    case (int32_t)LedgerEntryType::SALE:
return sale_ == other.sale_;
    case (int32_t)LedgerEntryType::KEY_VALUE:
return keyValue_ == other.keyValue_;
    case (int32_t)LedgerEntryType::ACCOUNT_KYC:
return accountKYC_ == other.accountKYC_;
    case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
return externalSystemAccountIDPoolEntry_ == other.externalSystemAccountIDPoolEntry_;
    case (int32_t)LedgerEntryType::LIMITS_V2:
return limitsV2_ == other.limitsV2_;
    case (int32_t)LedgerEntryType::STATISTICS_V2:
return statisticsV2_ == other.statisticsV2_;
    case (int32_t)LedgerEntryType::PENDING_STATISTICS:
return pendingStatistics_ == other.pendingStatistics_;
    case (int32_t)LedgerEntryType::CONTRACT:
return contract_ == other.contract_;
    case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
return atomicSwapAsk_ == other.atomicSwapAsk_;
    case (int32_t)LedgerEntryType::ACCOUNT_ROLE:
return accountRole_ == other.accountRole_;
    case (int32_t)LedgerEntryType::ACCOUNT_RULE:
return accountRule_ == other.accountRule_;
    case (int32_t)LedgerEntryType::SIGNER_RULE:
return signerRule_ == other.signerRule_;
    case (int32_t)LedgerEntryType::SIGNER_ROLE:
return signerRole_ == other.signerRole_;
    case (int32_t)LedgerEntryType::LICENSE:
return license_ == other.license_;
    case (int32_t)LedgerEntryType::STAMP:
return stamp_ == other.stamp_;
    case (int32_t)LedgerEntryType::POLL:
return poll_ == other.poll_;
    case (int32_t)LedgerEntryType::VOTE:
return vote_ == other.vote_;
    case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
return accountSpecificRule_ == other.accountSpecificRule_;
    case (int32_t)LedgerEntryType::SWAP:
return swap_ == other.swap_;
    case (int32_t)LedgerEntryType::DATA:
return data_ == other.data_;
}
return false;
}
bool
LedgerEntry::_data_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_data_t const&>(other_abstract);
if (type_ < other.type_) return true;
if (other.type_ < type_) return false;
switch (type_)
{
    case (int32_t)LedgerEntryType::ACCOUNT:
return account_ < other.account_;
    case (int32_t)LedgerEntryType::SIGNER:
return signer_ < other.signer_;
    case (int32_t)LedgerEntryType::FEE:
return feeState_ < other.feeState_;
    case (int32_t)LedgerEntryType::BALANCE:
return balance_ < other.balance_;
    case (int32_t)LedgerEntryType::ASSET:
return asset_ < other.asset_;
    case (int32_t)LedgerEntryType::REFERENCE_ENTRY:
return reference_ < other.reference_;
    case (int32_t)LedgerEntryType::STATISTICS:
return stats_ < other.stats_;
    case (int32_t)LedgerEntryType::ACCOUNT_LIMITS:
return accountLimits_ < other.accountLimits_;
    case (int32_t)LedgerEntryType::ASSET_PAIR:
return assetPair_ < other.assetPair_;
    case (int32_t)LedgerEntryType::OFFER_ENTRY:
return offer_ < other.offer_;
    case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
return reviewableRequest_ < other.reviewableRequest_;
    case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
return externalSystemAccountID_ < other.externalSystemAccountID_;
    case (int32_t)LedgerEntryType::SALE:
return sale_ < other.sale_;
    case (int32_t)LedgerEntryType::KEY_VALUE:
return keyValue_ < other.keyValue_;
    case (int32_t)LedgerEntryType::ACCOUNT_KYC:
return accountKYC_ < other.accountKYC_;
    case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
return externalSystemAccountIDPoolEntry_ < other.externalSystemAccountIDPoolEntry_;
    case (int32_t)LedgerEntryType::LIMITS_V2:
return limitsV2_ < other.limitsV2_;
    case (int32_t)LedgerEntryType::STATISTICS_V2:
return statisticsV2_ < other.statisticsV2_;
    case (int32_t)LedgerEntryType::PENDING_STATISTICS:
return pendingStatistics_ < other.pendingStatistics_;
    case (int32_t)LedgerEntryType::CONTRACT:
return contract_ < other.contract_;
    case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
return atomicSwapAsk_ < other.atomicSwapAsk_;
    case (int32_t)LedgerEntryType::ACCOUNT_ROLE:
return accountRole_ < other.accountRole_;
    case (int32_t)LedgerEntryType::ACCOUNT_RULE:
return accountRule_ < other.accountRule_;
    case (int32_t)LedgerEntryType::SIGNER_RULE:
return signerRule_ < other.signerRule_;
    case (int32_t)LedgerEntryType::SIGNER_ROLE:
return signerRole_ < other.signerRole_;
    case (int32_t)LedgerEntryType::LICENSE:
return license_ < other.license_;
    case (int32_t)LedgerEntryType::STAMP:
return stamp_ < other.stamp_;
    case (int32_t)LedgerEntryType::POLL:
return poll_ < other.poll_;
    case (int32_t)LedgerEntryType::VOTE:
return vote_ < other.vote_;
    case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
return accountSpecificRule_ < other.accountSpecificRule_;
    case (int32_t)LedgerEntryType::SWAP:
return swap_ < other.swap_;
    case (int32_t)LedgerEntryType::DATA:
return data_ < other.data_;
}
return false;
}
bool
LedgerEntry::_ext_t::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return true;
}
return false;
}
bool
LedgerEntry::_ext_t::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(v_);
if (!ok)
{
return false;
}
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
      return true;
}
return false;
}
void
LedgerEntry::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
LedgerEntry::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (other.v_ != v_) return false;
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return true;
}
return false;
}
bool
LedgerEntry::_ext_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (v_ < other.v_) return true;
if (other.v_ < v_) return false;
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
      return false;
}
return false;
}
bool
LedgerEntry::from_bytes(xdr::unmarshaler& u) 
{
bool oklastModifiedLedgerSeq = u.from_bytes(lastModifiedLedgerSeq);
if (!oklastModifiedLedgerSeq)
{
return false;
}
bool okdata = u.from_bytes(data);
if (!okdata)
{
return false;
}
bool okext = u.from_bytes(ext);
if (!okext)
{
return false;
}
return true;
}
bool
LedgerEntry::to_bytes(xdr::marshaler& m) const 
{
bool oklastModifiedLedgerSeq = m.to_bytes(lastModifiedLedgerSeq);
if (!oklastModifiedLedgerSeq)
{
return false;
}
bool okdata = m.to_bytes(data);
if (!okdata)
{
return false;
}
bool okext = m.to_bytes(ext);
if (!okext)
{
return false;
}
return true;
}
void
LedgerEntry::count_size(xdr::measurer& m) const 
{
m.count_size(lastModifiedLedgerSeq);
m.count_size(data);
m.count_size(ext);
}
bool
LedgerEntry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<LedgerEntry const&>(other_abstract);return true
&& (lastModifiedLedgerSeq== other.lastModifiedLedgerSeq)
&& (data== other.data)
&& (ext== other.ext)
;}
bool
LedgerEntry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<LedgerEntry const&>(other_abstract);
if (lastModifiedLedgerSeq < other.lastModifiedLedgerSeq) return true;
if (other.lastModifiedLedgerSeq < lastModifiedLedgerSeq) return false;
if (data < other.data) return true;
if (other.data < data) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}