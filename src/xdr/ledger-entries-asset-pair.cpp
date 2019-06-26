#include "ledger-entries-asset-pair.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
AssetPairEntry::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
AssetPairEntry::_ext_t::to_bytes(xdr::marshaler& m) const
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
AssetPairEntry::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
AssetPairEntry::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
AssetPairEntry::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
AssetPairEntry::from_bytes(xdr::unmarshaler& u) 
{
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
bool okcurrentPrice = u.from_bytes(currentPrice);
if (!okcurrentPrice)
{
return false;
}
bool okphysicalPrice = u.from_bytes(physicalPrice);
if (!okphysicalPrice)
{
return false;
}
bool okphysicalPriceCorrection = u.from_bytes(physicalPriceCorrection);
if (!okphysicalPriceCorrection)
{
return false;
}
bool okmaxPriceStep = u.from_bytes(maxPriceStep);
if (!okmaxPriceStep)
{
return false;
}
bool okpolicies = u.from_bytes(policies);
if (!okpolicies)
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
AssetPairEntry::to_bytes(xdr::marshaler& m) const 
{
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
bool okcurrentPrice = m.to_bytes(currentPrice);
if (!okcurrentPrice)
{
return false;
}
bool okphysicalPrice = m.to_bytes(physicalPrice);
if (!okphysicalPrice)
{
return false;
}
bool okphysicalPriceCorrection = m.to_bytes(physicalPriceCorrection);
if (!okphysicalPriceCorrection)
{
return false;
}
bool okmaxPriceStep = m.to_bytes(maxPriceStep);
if (!okmaxPriceStep)
{
return false;
}
bool okpolicies = m.to_bytes(policies);
if (!okpolicies)
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
AssetPairEntry::count_size(xdr::measurer& m) const 
{
m.count_size(base);
m.count_size(quote);
m.count_size(currentPrice);
m.count_size(physicalPrice);
m.count_size(physicalPriceCorrection);
m.count_size(maxPriceStep);
m.count_size(policies);
m.count_size(ext);
}
bool
AssetPairEntry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<AssetPairEntry const&>(other_abstract);return true
&& (base== other.base)
&& (quote== other.quote)
&& (currentPrice== other.currentPrice)
&& (physicalPrice== other.physicalPrice)
&& (physicalPriceCorrection== other.physicalPriceCorrection)
&& (maxPriceStep== other.maxPriceStep)
&& (policies== other.policies)
&& (ext== other.ext)
;}
bool
AssetPairEntry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<AssetPairEntry const&>(other_abstract);
if (base < other.base) return true;
if (other.base < base) return false;
if (quote < other.quote) return true;
if (other.quote < quote) return false;
if (currentPrice < other.currentPrice) return true;
if (other.currentPrice < currentPrice) return false;
if (physicalPrice < other.physicalPrice) return true;
if (other.physicalPrice < physicalPrice) return false;
if (physicalPriceCorrection < other.physicalPriceCorrection) return true;
if (other.physicalPriceCorrection < physicalPriceCorrection) return false;
if (maxPriceStep < other.maxPriceStep) return true;
if (other.maxPriceStep < maxPriceStep) return false;
if (policies < other.policies) return true;
if (other.policies < policies) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}