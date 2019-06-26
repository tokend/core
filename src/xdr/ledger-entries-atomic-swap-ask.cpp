#include "ledger-entries-atomic-swap-ask.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
AtomicSwapAskQuoteAsset::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
AtomicSwapAskQuoteAsset::_ext_t::to_bytes(xdr::marshaler& m) const
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
AtomicSwapAskQuoteAsset::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
AtomicSwapAskQuoteAsset::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
AtomicSwapAskQuoteAsset::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
AtomicSwapAskQuoteAsset::from_bytes(xdr::unmarshaler& u) 
{
bool okquoteAsset = u.from_bytes(quoteAsset);
if (!okquoteAsset)
{
return false;
}
bool okprice = u.from_bytes(price);
if (!okprice)
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
AtomicSwapAskQuoteAsset::to_bytes(xdr::marshaler& m) const 
{
bool okquoteAsset = m.to_bytes(quoteAsset);
if (!okquoteAsset)
{
return false;
}
bool okprice = m.to_bytes(price);
if (!okprice)
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
AtomicSwapAskQuoteAsset::count_size(xdr::measurer& m) const 
{
m.count_size(quoteAsset);
m.count_size(price);
m.count_size(ext);
}
bool
AtomicSwapAskQuoteAsset::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<AtomicSwapAskQuoteAsset const&>(other_abstract);return true
&& (quoteAsset== other.quoteAsset)
&& (price== other.price)
&& (ext== other.ext)
;}
bool
AtomicSwapAskQuoteAsset::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<AtomicSwapAskQuoteAsset const&>(other_abstract);
if (quoteAsset < other.quoteAsset) return true;
if (other.quoteAsset < quoteAsset) return false;
if (price < other.price) return true;
if (other.price < price) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
AtomicSwapAskEntry::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
AtomicSwapAskEntry::_ext_t::to_bytes(xdr::marshaler& m) const
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
AtomicSwapAskEntry::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
AtomicSwapAskEntry::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
AtomicSwapAskEntry::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
AtomicSwapAskEntry::from_bytes(xdr::unmarshaler& u) 
{
bool okid = u.from_bytes(id);
if (!okid)
{
return false;
}
bool okownerID = u.from_bytes(ownerID);
if (!okownerID)
{
return false;
}
bool okbaseAsset = u.from_bytes(baseAsset);
if (!okbaseAsset)
{
return false;
}
bool okbaseBalance = u.from_bytes(baseBalance);
if (!okbaseBalance)
{
return false;
}
bool okamount = u.from_bytes(amount);
if (!okamount)
{
return false;
}
bool oklockedAmount = u.from_bytes(lockedAmount);
if (!oklockedAmount)
{
return false;
}
bool okcreatedAt = u.from_bytes(createdAt);
if (!okcreatedAt)
{
return false;
}
bool okisCancelled = u.from_bytes(isCancelled);
if (!okisCancelled)
{
return false;
}
bool okdetails = u.from_bytes(details);
if (!okdetails)
{
return false;
}
bool okquoteAssets = u.from_bytes(quoteAssets);
if (!okquoteAssets)
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
AtomicSwapAskEntry::to_bytes(xdr::marshaler& m) const 
{
bool okid = m.to_bytes(id);
if (!okid)
{
return false;
}
bool okownerID = m.to_bytes(ownerID);
if (!okownerID)
{
return false;
}
bool okbaseAsset = m.to_bytes(baseAsset);
if (!okbaseAsset)
{
return false;
}
bool okbaseBalance = m.to_bytes(baseBalance);
if (!okbaseBalance)
{
return false;
}
bool okamount = m.to_bytes(amount);
if (!okamount)
{
return false;
}
bool oklockedAmount = m.to_bytes(lockedAmount);
if (!oklockedAmount)
{
return false;
}
bool okcreatedAt = m.to_bytes(createdAt);
if (!okcreatedAt)
{
return false;
}
bool okisCancelled = m.to_bytes(isCancelled);
if (!okisCancelled)
{
return false;
}
bool okdetails = m.to_bytes(details);
if (!okdetails)
{
return false;
}
bool okquoteAssets = m.to_bytes(quoteAssets);
if (!okquoteAssets)
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
AtomicSwapAskEntry::count_size(xdr::measurer& m) const 
{
m.count_size(id);
m.count_size(ownerID);
m.count_size(baseAsset);
m.count_size(baseBalance);
m.count_size(amount);
m.count_size(lockedAmount);
m.count_size(createdAt);
m.count_size(isCancelled);
m.count_size(details);
m.count_size(quoteAssets);
m.count_size(ext);
}
bool
AtomicSwapAskEntry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<AtomicSwapAskEntry const&>(other_abstract);return true
&& (id== other.id)
&& (ownerID== other.ownerID)
&& (baseAsset== other.baseAsset)
&& (baseBalance== other.baseBalance)
&& (amount== other.amount)
&& (lockedAmount== other.lockedAmount)
&& (createdAt== other.createdAt)
&& (isCancelled== other.isCancelled)
&& (details== other.details)
&& (quoteAssets== other.quoteAssets)
&& (ext== other.ext)
;}
bool
AtomicSwapAskEntry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<AtomicSwapAskEntry const&>(other_abstract);
if (id < other.id) return true;
if (other.id < id) return false;
if (ownerID < other.ownerID) return true;
if (other.ownerID < ownerID) return false;
if (baseAsset < other.baseAsset) return true;
if (other.baseAsset < baseAsset) return false;
if (baseBalance < other.baseBalance) return true;
if (other.baseBalance < baseBalance) return false;
if (amount < other.amount) return true;
if (other.amount < amount) return false;
if (lockedAmount < other.lockedAmount) return true;
if (other.lockedAmount < lockedAmount) return false;
if (createdAt < other.createdAt) return true;
if (other.createdAt < createdAt) return false;
if (isCancelled < other.isCancelled) return true;
if (other.isCancelled < isCancelled) return false;
if (details < other.details) return true;
if (other.details < details) return false;
if (quoteAssets < other.quoteAssets) return true;
if (other.quoteAssets < quoteAssets) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}