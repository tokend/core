#include "ledger-entries-offer.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
OfferEntry::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
OfferEntry::_ext_t::to_bytes(xdr::marshaler& m) const
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
OfferEntry::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
OfferEntry::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
OfferEntry::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
OfferEntry::from_bytes(xdr::unmarshaler& u) 
{
bool okofferID = u.from_bytes(offerID);
if (!okofferID)
{
return false;
}
bool okorderBookID = u.from_bytes(orderBookID);
if (!okorderBookID)
{
return false;
}
bool okownerID = u.from_bytes(ownerID);
if (!okownerID)
{
return false;
}
bool okisBuy = u.from_bytes(isBuy);
if (!okisBuy)
{
return false;
}
bool okbase = u.from_bytes(base);
if (!okbase)
{
return false;
}
bool okquote = u.from_bytes(quote);
if (!okquote)
{
return false;
}
bool okbaseBalance = u.from_bytes(baseBalance);
if (!okbaseBalance)
{
return false;
}
bool okquoteBalance = u.from_bytes(quoteBalance);
if (!okquoteBalance)
{
return false;
}
bool okbaseAmount = u.from_bytes(baseAmount);
if (!okbaseAmount)
{
return false;
}
bool okquoteAmount = u.from_bytes(quoteAmount);
if (!okquoteAmount)
{
return false;
}
bool okcreatedAt = u.from_bytes(createdAt);
if (!okcreatedAt)
{
return false;
}
bool okfee = u.from_bytes(fee);
if (!okfee)
{
return false;
}
bool okpercentFee = u.from_bytes(percentFee);
if (!okpercentFee)
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
OfferEntry::to_bytes(xdr::marshaler& m) const 
{
bool okofferID = m.to_bytes(offerID);
if (!okofferID)
{
return false;
}
bool okorderBookID = m.to_bytes(orderBookID);
if (!okorderBookID)
{
return false;
}
bool okownerID = m.to_bytes(ownerID);
if (!okownerID)
{
return false;
}
bool okisBuy = m.to_bytes(isBuy);
if (!okisBuy)
{
return false;
}
bool okbase = m.to_bytes(base);
if (!okbase)
{
return false;
}
bool okquote = m.to_bytes(quote);
if (!okquote)
{
return false;
}
bool okbaseBalance = m.to_bytes(baseBalance);
if (!okbaseBalance)
{
return false;
}
bool okquoteBalance = m.to_bytes(quoteBalance);
if (!okquoteBalance)
{
return false;
}
bool okbaseAmount = m.to_bytes(baseAmount);
if (!okbaseAmount)
{
return false;
}
bool okquoteAmount = m.to_bytes(quoteAmount);
if (!okquoteAmount)
{
return false;
}
bool okcreatedAt = m.to_bytes(createdAt);
if (!okcreatedAt)
{
return false;
}
bool okfee = m.to_bytes(fee);
if (!okfee)
{
return false;
}
bool okpercentFee = m.to_bytes(percentFee);
if (!okpercentFee)
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
OfferEntry::count_size(xdr::measurer& m) const 
{
m.count_size(offerID);
m.count_size(orderBookID);
m.count_size(ownerID);
m.count_size(isBuy);
m.count_size(base);
m.count_size(quote);
m.count_size(baseBalance);
m.count_size(quoteBalance);
m.count_size(baseAmount);
m.count_size(quoteAmount);
m.count_size(createdAt);
m.count_size(fee);
m.count_size(percentFee);
m.count_size(price);
m.count_size(ext);
}
bool
OfferEntry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<OfferEntry const&>(other_abstract);return true
&& (offerID== other.offerID)
&& (orderBookID== other.orderBookID)
&& (ownerID== other.ownerID)
&& (isBuy== other.isBuy)
&& (base== other.base)
&& (quote== other.quote)
&& (baseBalance== other.baseBalance)
&& (quoteBalance== other.quoteBalance)
&& (baseAmount== other.baseAmount)
&& (quoteAmount== other.quoteAmount)
&& (createdAt== other.createdAt)
&& (fee== other.fee)
&& (percentFee== other.percentFee)
&& (price== other.price)
&& (ext== other.ext)
;}
bool
OfferEntry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<OfferEntry const&>(other_abstract);
if (offerID < other.offerID) return true;
if (other.offerID < offerID) return false;
if (orderBookID < other.orderBookID) return true;
if (other.orderBookID < orderBookID) return false;
if (ownerID < other.ownerID) return true;
if (other.ownerID < ownerID) return false;
if (isBuy < other.isBuy) return true;
if (other.isBuy < isBuy) return false;
if (base < other.base) return true;
if (other.base < base) return false;
if (quote < other.quote) return true;
if (other.quote < quote) return false;
if (baseBalance < other.baseBalance) return true;
if (other.baseBalance < baseBalance) return false;
if (quoteBalance < other.quoteBalance) return true;
if (other.quoteBalance < quoteBalance) return false;
if (baseAmount < other.baseAmount) return true;
if (other.baseAmount < baseAmount) return false;
if (quoteAmount < other.quoteAmount) return true;
if (other.quoteAmount < quoteAmount) return false;
if (createdAt < other.createdAt) return true;
if (other.createdAt < createdAt) return false;
if (fee < other.fee) return true;
if (other.fee < fee) return false;
if (percentFee < other.percentFee) return true;
if (other.percentFee < percentFee) return false;
if (price < other.price) return true;
if (other.price < price) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}