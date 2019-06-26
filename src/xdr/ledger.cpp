#include "ledger.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
StellarValue::_ext_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(v_);
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
bool
StellarValue::_ext_t::to_bytes(xdr::marshaler& m) const
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
StellarValue::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
StellarValue::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
StellarValue::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
StellarValue::from_bytes(xdr::unmarshaler& u) 
{
bool oktxSetHash = u.from_bytes(txSetHash);
if (!oktxSetHash)
{
return false;
}
bool okcloseTime = u.from_bytes(closeTime);
if (!okcloseTime)
{
return false;
}
bool okupgrades = u.from_bytes(upgrades);
if (!okupgrades)
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
StellarValue::to_bytes(xdr::marshaler& m) const 
{
bool oktxSetHash = m.to_bytes(txSetHash);
if (!oktxSetHash)
{
return false;
}
bool okcloseTime = m.to_bytes(closeTime);
if (!okcloseTime)
{
return false;
}
bool okupgrades = m.to_bytes(upgrades);
if (!okupgrades)
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
StellarValue::count_size(xdr::measurer& m) const 
{
m.count_size(txSetHash);
m.count_size(closeTime);
m.count_size(upgrades);
m.count_size(ext);
}
bool
StellarValue::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<StellarValue const&>(other_abstract);return true
&& (txSetHash== other.txSetHash)
&& (closeTime== other.closeTime)
&& (upgrades== other.upgrades)
&& (ext== other.ext)
;}
bool
StellarValue::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<StellarValue const&>(other_abstract);
if (txSetHash < other.txSetHash) return true;
if (other.txSetHash < txSetHash) return false;
if (closeTime < other.closeTime) return true;
if (other.closeTime < closeTime) return false;
if (upgrades < other.upgrades) return true;
if (other.upgrades < upgrades) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
IdGenerator::from_bytes(xdr::unmarshaler& u) 
{
bool okentryType = u.from_bytes(entryType);
if (!okentryType)
{
return false;
}
bool okidPool = u.from_bytes(idPool);
if (!okidPool)
{
return false;
}
return true;
}
bool
IdGenerator::to_bytes(xdr::marshaler& m) const 
{
bool okentryType = m.to_bytes(entryType);
if (!okentryType)
{
return false;
}
bool okidPool = m.to_bytes(idPool);
if (!okidPool)
{
return false;
}
return true;
}
void
IdGenerator::count_size(xdr::measurer& m) const 
{
m.count_size(entryType);
m.count_size(idPool);
}
bool
IdGenerator::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<IdGenerator const&>(other_abstract);return true
&& (entryType== other.entryType)
&& (idPool== other.idPool)
;}
bool
IdGenerator::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<IdGenerator const&>(other_abstract);
if (entryType < other.entryType) return true;
if (other.entryType < entryType) return false;
if (idPool < other.idPool) return true;
if (other.idPool < idPool) return false;
return false;
}bool
LedgerHeader::_ext_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(v_);
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
bool
LedgerHeader::_ext_t::to_bytes(xdr::marshaler& m) const
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
LedgerHeader::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
LedgerHeader::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
LedgerHeader::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
LedgerHeader::from_bytes(xdr::unmarshaler& u) 
{
bool okledgerVersion = u.from_bytes(ledgerVersion);
if (!okledgerVersion)
{
return false;
}
bool okpreviousLedgerHash = u.from_bytes(previousLedgerHash);
if (!okpreviousLedgerHash)
{
return false;
}
bool okscpValue = u.from_bytes(scpValue);
if (!okscpValue)
{
return false;
}
bool oktxSetResultHash = u.from_bytes(txSetResultHash);
if (!oktxSetResultHash)
{
return false;
}
bool okbucketListHash = u.from_bytes(bucketListHash);
if (!okbucketListHash)
{
return false;
}
bool okledgerSeq = u.from_bytes(ledgerSeq);
if (!okledgerSeq)
{
return false;
}
bool okidGenerators = u.from_bytes(idGenerators);
if (!okidGenerators)
{
return false;
}
bool okbaseFee = u.from_bytes(baseFee);
if (!okbaseFee)
{
return false;
}
bool okbaseReserve = u.from_bytes(baseReserve);
if (!okbaseReserve)
{
return false;
}
bool okmaxTxSetSize = u.from_bytes(maxTxSetSize);
if (!okmaxTxSetSize)
{
return false;
}
bool oktxExpirationPeriod = u.from_bytes(txExpirationPeriod);
if (!oktxExpirationPeriod)
{
return false;
}
bool okskipList = u.from_bytes(skipList);
if (!okskipList)
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
LedgerHeader::to_bytes(xdr::marshaler& m) const 
{
bool okledgerVersion = m.to_bytes(ledgerVersion);
if (!okledgerVersion)
{
return false;
}
bool okpreviousLedgerHash = m.to_bytes(previousLedgerHash);
if (!okpreviousLedgerHash)
{
return false;
}
bool okscpValue = m.to_bytes(scpValue);
if (!okscpValue)
{
return false;
}
bool oktxSetResultHash = m.to_bytes(txSetResultHash);
if (!oktxSetResultHash)
{
return false;
}
bool okbucketListHash = m.to_bytes(bucketListHash);
if (!okbucketListHash)
{
return false;
}
bool okledgerSeq = m.to_bytes(ledgerSeq);
if (!okledgerSeq)
{
return false;
}
bool okidGenerators = m.to_bytes(idGenerators);
if (!okidGenerators)
{
return false;
}
bool okbaseFee = m.to_bytes(baseFee);
if (!okbaseFee)
{
return false;
}
bool okbaseReserve = m.to_bytes(baseReserve);
if (!okbaseReserve)
{
return false;
}
bool okmaxTxSetSize = m.to_bytes(maxTxSetSize);
if (!okmaxTxSetSize)
{
return false;
}
bool oktxExpirationPeriod = m.to_bytes(txExpirationPeriod);
if (!oktxExpirationPeriod)
{
return false;
}
bool okskipList = m.to_bytes(skipList);
if (!okskipList)
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
LedgerHeader::count_size(xdr::measurer& m) const 
{
m.count_size(ledgerVersion);
m.count_size(previousLedgerHash);
m.count_size(scpValue);
m.count_size(txSetResultHash);
m.count_size(bucketListHash);
m.count_size(ledgerSeq);
m.count_size(idGenerators);
m.count_size(baseFee);
m.count_size(baseReserve);
m.count_size(maxTxSetSize);
m.count_size(txExpirationPeriod);
m.count_size(skipList);
m.count_size(ext);
}
bool
LedgerHeader::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<LedgerHeader const&>(other_abstract);return true
&& (ledgerVersion== other.ledgerVersion)
&& (previousLedgerHash== other.previousLedgerHash)
&& (scpValue== other.scpValue)
&& (txSetResultHash== other.txSetResultHash)
&& (bucketListHash== other.bucketListHash)
&& (ledgerSeq== other.ledgerSeq)
&& (idGenerators== other.idGenerators)
&& (baseFee== other.baseFee)
&& (baseReserve== other.baseReserve)
&& (maxTxSetSize== other.maxTxSetSize)
&& (txExpirationPeriod== other.txExpirationPeriod)
&& (skipList== other.skipList)
&& (ext== other.ext)
;}
bool
LedgerHeader::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<LedgerHeader const&>(other_abstract);
if (ledgerVersion < other.ledgerVersion) return true;
if (other.ledgerVersion < ledgerVersion) return false;
if (previousLedgerHash < other.previousLedgerHash) return true;
if (other.previousLedgerHash < previousLedgerHash) return false;
if (scpValue < other.scpValue) return true;
if (other.scpValue < scpValue) return false;
if (txSetResultHash < other.txSetResultHash) return true;
if (other.txSetResultHash < txSetResultHash) return false;
if (bucketListHash < other.bucketListHash) return true;
if (other.bucketListHash < bucketListHash) return false;
if (ledgerSeq < other.ledgerSeq) return true;
if (other.ledgerSeq < ledgerSeq) return false;
if (idGenerators < other.idGenerators) return true;
if (other.idGenerators < idGenerators) return false;
if (baseFee < other.baseFee) return true;
if (other.baseFee < baseFee) return false;
if (baseReserve < other.baseReserve) return true;
if (other.baseReserve < baseReserve) return false;
if (maxTxSetSize < other.maxTxSetSize) return true;
if (other.maxTxSetSize < maxTxSetSize) return false;
if (txExpirationPeriod < other.txExpirationPeriod) return true;
if (other.txExpirationPeriod < txExpirationPeriod) return false;
if (skipList < other.skipList) return true;
if (other.skipList < skipList) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LedgerUpgrade::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(type_);
if (!ok)
{
return false;
}
switch (type_)
{

  case (int32_t)LedgerUpgradeType::VERSION:
return u.from_bytes(newLedgerVersion_);
  case (int32_t)LedgerUpgradeType::MAX_TX_SET_SIZE:
return u.from_bytes(newMaxTxSetSize_);
  case (int32_t)LedgerUpgradeType::TX_EXPIRATION_PERIOD:
return u.from_bytes(newTxExpirationPeriod_);
}
return false;
}
bool
LedgerUpgrade::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(type_);
if (!ok)
{
return false;
}
switch (type_)
{

  case (int32_t)LedgerUpgradeType::VERSION:
return m.to_bytes(newLedgerVersion_);
  case (int32_t)LedgerUpgradeType::MAX_TX_SET_SIZE:
return m.to_bytes(newMaxTxSetSize_);
  case (int32_t)LedgerUpgradeType::TX_EXPIRATION_PERIOD:
return m.to_bytes(newTxExpirationPeriod_);
}
return false;
}
void
LedgerUpgrade::count_size(xdr::measurer& m) const
{
m.count_size(type_);
switch (type_)
{

  case (int32_t)LedgerUpgradeType::VERSION:
return m.count_size(newLedgerVersion_);
  case (int32_t)LedgerUpgradeType::MAX_TX_SET_SIZE:
return m.count_size(newMaxTxSetSize_);
  case (int32_t)LedgerUpgradeType::TX_EXPIRATION_PERIOD:
return m.count_size(newTxExpirationPeriod_);
}
}
bool
LedgerUpgrade::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<LedgerUpgrade const&>(other_abstract);
if (other.type_ != type_) return false;
switch (type_)
{
  case (int32_t)LedgerUpgradeType::VERSION:
return newLedgerVersion_ == other.newLedgerVersion_;
  case (int32_t)LedgerUpgradeType::MAX_TX_SET_SIZE:
return newMaxTxSetSize_ == other.newMaxTxSetSize_;
  case (int32_t)LedgerUpgradeType::TX_EXPIRATION_PERIOD:
return newTxExpirationPeriod_ == other.newTxExpirationPeriod_;
}
return false;
}
bool
LedgerUpgrade::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<LedgerUpgrade const&>(other_abstract);
if (type_ < other.type_) return true;
if (other.type_ < type_) return false;
switch (type_)
{
  case (int32_t)LedgerUpgradeType::VERSION:
return newLedgerVersion_ < other.newLedgerVersion_;
  case (int32_t)LedgerUpgradeType::MAX_TX_SET_SIZE:
return newMaxTxSetSize_ < other.newMaxTxSetSize_;
  case (int32_t)LedgerUpgradeType::TX_EXPIRATION_PERIOD:
return newTxExpirationPeriod_ < other.newTxExpirationPeriod_;
}
return false;
}
bool
BucketEntry::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(type_);
if (!ok)
{
return false;
}
switch (type_)
{

  case (int32_t)BucketEntryType::LIVEENTRY:
return u.from_bytes(liveEntry_);
  case (int32_t)BucketEntryType::DEADENTRY:
return u.from_bytes(deadEntry_);
}
return false;
}
bool
BucketEntry::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(type_);
if (!ok)
{
return false;
}
switch (type_)
{

  case (int32_t)BucketEntryType::LIVEENTRY:
return m.to_bytes(liveEntry_);
  case (int32_t)BucketEntryType::DEADENTRY:
return m.to_bytes(deadEntry_);
}
return false;
}
void
BucketEntry::count_size(xdr::measurer& m) const
{
m.count_size(type_);
switch (type_)
{

  case (int32_t)BucketEntryType::LIVEENTRY:
return m.count_size(liveEntry_);
  case (int32_t)BucketEntryType::DEADENTRY:
return m.count_size(deadEntry_);
}
}
bool
BucketEntry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<BucketEntry const&>(other_abstract);
if (other.type_ != type_) return false;
switch (type_)
{
  case (int32_t)BucketEntryType::LIVEENTRY:
return liveEntry_ == other.liveEntry_;
  case (int32_t)BucketEntryType::DEADENTRY:
return deadEntry_ == other.deadEntry_;
}
return false;
}
bool
BucketEntry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<BucketEntry const&>(other_abstract);
if (type_ < other.type_) return true;
if (other.type_ < type_) return false;
switch (type_)
{
  case (int32_t)BucketEntryType::LIVEENTRY:
return liveEntry_ < other.liveEntry_;
  case (int32_t)BucketEntryType::DEADENTRY:
return deadEntry_ < other.deadEntry_;
}
return false;
}
bool
TransactionSet::from_bytes(xdr::unmarshaler& u) 
{
bool okpreviousLedgerHash = u.from_bytes(previousLedgerHash);
if (!okpreviousLedgerHash)
{
return false;
}
bool oktxs = u.from_bytes(txs);
if (!oktxs)
{
return false;
}
return true;
}
bool
TransactionSet::to_bytes(xdr::marshaler& m) const 
{
bool okpreviousLedgerHash = m.to_bytes(previousLedgerHash);
if (!okpreviousLedgerHash)
{
return false;
}
bool oktxs = m.to_bytes(txs);
if (!oktxs)
{
return false;
}
return true;
}
void
TransactionSet::count_size(xdr::measurer& m) const 
{
m.count_size(previousLedgerHash);
m.count_size(txs);
}
bool
TransactionSet::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<TransactionSet const&>(other_abstract);return true
&& (previousLedgerHash== other.previousLedgerHash)
&& (txs== other.txs)
;}
bool
TransactionSet::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<TransactionSet const&>(other_abstract);
if (previousLedgerHash < other.previousLedgerHash) return true;
if (other.previousLedgerHash < previousLedgerHash) return false;
if (txs < other.txs) return true;
if (other.txs < txs) return false;
return false;
}bool
TransactionResultPair::from_bytes(xdr::unmarshaler& u) 
{
bool oktransactionHash = u.from_bytes(transactionHash);
if (!oktransactionHash)
{
return false;
}
bool okresult = u.from_bytes(result);
if (!okresult)
{
return false;
}
return true;
}
bool
TransactionResultPair::to_bytes(xdr::marshaler& m) const 
{
bool oktransactionHash = m.to_bytes(transactionHash);
if (!oktransactionHash)
{
return false;
}
bool okresult = m.to_bytes(result);
if (!okresult)
{
return false;
}
return true;
}
void
TransactionResultPair::count_size(xdr::measurer& m) const 
{
m.count_size(transactionHash);
m.count_size(result);
}
bool
TransactionResultPair::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<TransactionResultPair const&>(other_abstract);return true
&& (transactionHash== other.transactionHash)
&& (result== other.result)
;}
bool
TransactionResultPair::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<TransactionResultPair const&>(other_abstract);
if (transactionHash < other.transactionHash) return true;
if (other.transactionHash < transactionHash) return false;
if (result < other.result) return true;
if (other.result < result) return false;
return false;
}bool
TransactionResultSet::from_bytes(xdr::unmarshaler& u) 
{
bool okresults = u.from_bytes(results);
if (!okresults)
{
return false;
}
return true;
}
bool
TransactionResultSet::to_bytes(xdr::marshaler& m) const 
{
bool okresults = m.to_bytes(results);
if (!okresults)
{
return false;
}
return true;
}
void
TransactionResultSet::count_size(xdr::measurer& m) const 
{
m.count_size(results);
}
bool
TransactionResultSet::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<TransactionResultSet const&>(other_abstract);return true
&& (results== other.results)
;}
bool
TransactionResultSet::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<TransactionResultSet const&>(other_abstract);
if (results < other.results) return true;
if (other.results < results) return false;
return false;
}bool
TransactionHistoryEntry::_ext_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(v_);
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
bool
TransactionHistoryEntry::_ext_t::to_bytes(xdr::marshaler& m) const
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
TransactionHistoryEntry::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
TransactionHistoryEntry::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
TransactionHistoryEntry::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
TransactionHistoryEntry::from_bytes(xdr::unmarshaler& u) 
{
bool okledgerSeq = u.from_bytes(ledgerSeq);
if (!okledgerSeq)
{
return false;
}
bool oktxSet = u.from_bytes(txSet);
if (!oktxSet)
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
TransactionHistoryEntry::to_bytes(xdr::marshaler& m) const 
{
bool okledgerSeq = m.to_bytes(ledgerSeq);
if (!okledgerSeq)
{
return false;
}
bool oktxSet = m.to_bytes(txSet);
if (!oktxSet)
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
TransactionHistoryEntry::count_size(xdr::measurer& m) const 
{
m.count_size(ledgerSeq);
m.count_size(txSet);
m.count_size(ext);
}
bool
TransactionHistoryEntry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<TransactionHistoryEntry const&>(other_abstract);return true
&& (ledgerSeq== other.ledgerSeq)
&& (txSet== other.txSet)
&& (ext== other.ext)
;}
bool
TransactionHistoryEntry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<TransactionHistoryEntry const&>(other_abstract);
if (ledgerSeq < other.ledgerSeq) return true;
if (other.ledgerSeq < ledgerSeq) return false;
if (txSet < other.txSet) return true;
if (other.txSet < txSet) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
TransactionHistoryResultEntry::_ext_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(v_);
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
bool
TransactionHistoryResultEntry::_ext_t::to_bytes(xdr::marshaler& m) const
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
TransactionHistoryResultEntry::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
TransactionHistoryResultEntry::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
TransactionHistoryResultEntry::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
TransactionHistoryResultEntry::from_bytes(xdr::unmarshaler& u) 
{
bool okledgerSeq = u.from_bytes(ledgerSeq);
if (!okledgerSeq)
{
return false;
}
bool oktxResultSet = u.from_bytes(txResultSet);
if (!oktxResultSet)
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
TransactionHistoryResultEntry::to_bytes(xdr::marshaler& m) const 
{
bool okledgerSeq = m.to_bytes(ledgerSeq);
if (!okledgerSeq)
{
return false;
}
bool oktxResultSet = m.to_bytes(txResultSet);
if (!oktxResultSet)
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
TransactionHistoryResultEntry::count_size(xdr::measurer& m) const 
{
m.count_size(ledgerSeq);
m.count_size(txResultSet);
m.count_size(ext);
}
bool
TransactionHistoryResultEntry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<TransactionHistoryResultEntry const&>(other_abstract);return true
&& (ledgerSeq== other.ledgerSeq)
&& (txResultSet== other.txResultSet)
&& (ext== other.ext)
;}
bool
TransactionHistoryResultEntry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<TransactionHistoryResultEntry const&>(other_abstract);
if (ledgerSeq < other.ledgerSeq) return true;
if (other.ledgerSeq < ledgerSeq) return false;
if (txResultSet < other.txResultSet) return true;
if (other.txResultSet < txResultSet) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LedgerHeaderHistoryEntry::_ext_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(v_);
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
bool
LedgerHeaderHistoryEntry::_ext_t::to_bytes(xdr::marshaler& m) const
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
LedgerHeaderHistoryEntry::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
LedgerHeaderHistoryEntry::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
LedgerHeaderHistoryEntry::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
LedgerHeaderHistoryEntry::from_bytes(xdr::unmarshaler& u) 
{
bool okhash = u.from_bytes(hash);
if (!okhash)
{
return false;
}
bool okheader = u.from_bytes(header);
if (!okheader)
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
LedgerHeaderHistoryEntry::to_bytes(xdr::marshaler& m) const 
{
bool okhash = m.to_bytes(hash);
if (!okhash)
{
return false;
}
bool okheader = m.to_bytes(header);
if (!okheader)
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
LedgerHeaderHistoryEntry::count_size(xdr::measurer& m) const 
{
m.count_size(hash);
m.count_size(header);
m.count_size(ext);
}
bool
LedgerHeaderHistoryEntry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<LedgerHeaderHistoryEntry const&>(other_abstract);return true
&& (hash== other.hash)
&& (header== other.header)
&& (ext== other.ext)
;}
bool
LedgerHeaderHistoryEntry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<LedgerHeaderHistoryEntry const&>(other_abstract);
if (hash < other.hash) return true;
if (other.hash < hash) return false;
if (header < other.header) return true;
if (other.header < header) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LedgerSCPMessages::from_bytes(xdr::unmarshaler& u) 
{
bool okledgerSeq = u.from_bytes(ledgerSeq);
if (!okledgerSeq)
{
return false;
}
bool okmessages = u.from_bytes(messages);
if (!okmessages)
{
return false;
}
return true;
}
bool
LedgerSCPMessages::to_bytes(xdr::marshaler& m) const 
{
bool okledgerSeq = m.to_bytes(ledgerSeq);
if (!okledgerSeq)
{
return false;
}
bool okmessages = m.to_bytes(messages);
if (!okmessages)
{
return false;
}
return true;
}
void
LedgerSCPMessages::count_size(xdr::measurer& m) const 
{
m.count_size(ledgerSeq);
m.count_size(messages);
}
bool
LedgerSCPMessages::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<LedgerSCPMessages const&>(other_abstract);return true
&& (ledgerSeq== other.ledgerSeq)
&& (messages== other.messages)
;}
bool
LedgerSCPMessages::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<LedgerSCPMessages const&>(other_abstract);
if (ledgerSeq < other.ledgerSeq) return true;
if (other.ledgerSeq < ledgerSeq) return false;
if (messages < other.messages) return true;
if (other.messages < messages) return false;
return false;
}bool
SCPHistoryEntryV0::from_bytes(xdr::unmarshaler& u) 
{
bool okquorumSets = u.from_bytes(quorumSets);
if (!okquorumSets)
{
return false;
}
bool okledgerMessages = u.from_bytes(ledgerMessages);
if (!okledgerMessages)
{
return false;
}
return true;
}
bool
SCPHistoryEntryV0::to_bytes(xdr::marshaler& m) const 
{
bool okquorumSets = m.to_bytes(quorumSets);
if (!okquorumSets)
{
return false;
}
bool okledgerMessages = m.to_bytes(ledgerMessages);
if (!okledgerMessages)
{
return false;
}
return true;
}
void
SCPHistoryEntryV0::count_size(xdr::measurer& m) const 
{
m.count_size(quorumSets);
m.count_size(ledgerMessages);
}
bool
SCPHistoryEntryV0::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<SCPHistoryEntryV0 const&>(other_abstract);return true
&& (quorumSets== other.quorumSets)
&& (ledgerMessages== other.ledgerMessages)
;}
bool
SCPHistoryEntryV0::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<SCPHistoryEntryV0 const&>(other_abstract);
if (quorumSets < other.quorumSets) return true;
if (other.quorumSets < quorumSets) return false;
if (ledgerMessages < other.ledgerMessages) return true;
if (other.ledgerMessages < ledgerMessages) return false;
return false;
}bool
SCPHistoryEntry::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(v_);
if (!ok)
{
return false;
}
switch (v_)
{

  case (int32_t)LedgerVersion::EMPTY_VERSION:
return u.from_bytes(v0_);
}
return false;
}
bool
SCPHistoryEntry::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(v_);
if (!ok)
{
return false;
}
switch (v_)
{

  case (int32_t)LedgerVersion::EMPTY_VERSION:
return m.to_bytes(v0_);
}
return false;
}
void
SCPHistoryEntry::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

  case (int32_t)LedgerVersion::EMPTY_VERSION:
return m.count_size(v0_);
}
}
bool
SCPHistoryEntry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<SCPHistoryEntry const&>(other_abstract);
if (other.v_ != v_) return false;
switch (v_)
{
  case (int32_t)LedgerVersion::EMPTY_VERSION:
return v0_ == other.v0_;
}
return false;
}
bool
SCPHistoryEntry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<SCPHistoryEntry const&>(other_abstract);
if (v_ < other.v_) return true;
if (other.v_ < v_) return false;
switch (v_)
{
  case (int32_t)LedgerVersion::EMPTY_VERSION:
return v0_ < other.v0_;
}
return false;
}
bool
LedgerEntryChange::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(type_);
if (!ok)
{
return false;
}
switch (type_)
{

  case (int32_t)LedgerEntryChangeType::CREATED:
return u.from_bytes(created_);
  case (int32_t)LedgerEntryChangeType::UPDATED:
return u.from_bytes(updated_);
  case (int32_t)LedgerEntryChangeType::REMOVED:
return u.from_bytes(removed_);
  case (int32_t)LedgerEntryChangeType::STATE:
return u.from_bytes(state_);
}
return false;
}
bool
LedgerEntryChange::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(type_);
if (!ok)
{
return false;
}
switch (type_)
{

  case (int32_t)LedgerEntryChangeType::CREATED:
return m.to_bytes(created_);
  case (int32_t)LedgerEntryChangeType::UPDATED:
return m.to_bytes(updated_);
  case (int32_t)LedgerEntryChangeType::REMOVED:
return m.to_bytes(removed_);
  case (int32_t)LedgerEntryChangeType::STATE:
return m.to_bytes(state_);
}
return false;
}
void
LedgerEntryChange::count_size(xdr::measurer& m) const
{
m.count_size(type_);
switch (type_)
{

  case (int32_t)LedgerEntryChangeType::CREATED:
return m.count_size(created_);
  case (int32_t)LedgerEntryChangeType::UPDATED:
return m.count_size(updated_);
  case (int32_t)LedgerEntryChangeType::REMOVED:
return m.count_size(removed_);
  case (int32_t)LedgerEntryChangeType::STATE:
return m.count_size(state_);
}
}
bool
LedgerEntryChange::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<LedgerEntryChange const&>(other_abstract);
if (other.type_ != type_) return false;
switch (type_)
{
  case (int32_t)LedgerEntryChangeType::CREATED:
return created_ == other.created_;
  case (int32_t)LedgerEntryChangeType::UPDATED:
return updated_ == other.updated_;
  case (int32_t)LedgerEntryChangeType::REMOVED:
return removed_ == other.removed_;
  case (int32_t)LedgerEntryChangeType::STATE:
return state_ == other.state_;
}
return false;
}
bool
LedgerEntryChange::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<LedgerEntryChange const&>(other_abstract);
if (type_ < other.type_) return true;
if (other.type_ < type_) return false;
switch (type_)
{
  case (int32_t)LedgerEntryChangeType::CREATED:
return created_ < other.created_;
  case (int32_t)LedgerEntryChangeType::UPDATED:
return updated_ < other.updated_;
  case (int32_t)LedgerEntryChangeType::REMOVED:
return removed_ < other.removed_;
  case (int32_t)LedgerEntryChangeType::STATE:
return state_ < other.state_;
}
return false;
}
bool
OperationMeta::from_bytes(xdr::unmarshaler& u) 
{
bool okchanges = u.from_bytes(changes);
if (!okchanges)
{
return false;
}
return true;
}
bool
OperationMeta::to_bytes(xdr::marshaler& m) const 
{
bool okchanges = m.to_bytes(changes);
if (!okchanges)
{
return false;
}
return true;
}
void
OperationMeta::count_size(xdr::measurer& m) const 
{
m.count_size(changes);
}
bool
OperationMeta::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<OperationMeta const&>(other_abstract);return true
&& (changes== other.changes)
;}
bool
OperationMeta::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<OperationMeta const&>(other_abstract);
if (changes < other.changes) return true;
if (other.changes < changes) return false;
return false;
}bool
TransactionMeta::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(v_);
if (!ok)
{
return false;
}
switch (v_)
{

  case (int32_t)LedgerVersion::EMPTY_VERSION:
return u.from_bytes(operations_);
}
return false;
}
bool
TransactionMeta::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(v_);
if (!ok)
{
return false;
}
switch (v_)
{

  case (int32_t)LedgerVersion::EMPTY_VERSION:
return m.to_bytes(operations_);
}
return false;
}
void
TransactionMeta::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

  case (int32_t)LedgerVersion::EMPTY_VERSION:
return m.count_size(operations_);
}
}
bool
TransactionMeta::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<TransactionMeta const&>(other_abstract);
if (other.v_ != v_) return false;
switch (v_)
{
  case (int32_t)LedgerVersion::EMPTY_VERSION:
return operations_ == other.operations_;
}
return false;
}
bool
TransactionMeta::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<TransactionMeta const&>(other_abstract);
if (v_ < other.v_) return true;
if (other.v_ < v_) return false;
switch (v_)
{
  case (int32_t)LedgerVersion::EMPTY_VERSION:
return operations_ < other.operations_;
}
return false;
}
}