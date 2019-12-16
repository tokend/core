#include "reviewable-request-redemption.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
RedemptionRequest::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
RedemptionRequest::_ext_t::to_bytes(xdr::marshaler& m) const
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
RedemptionRequest::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
RedemptionRequest::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
RedemptionRequest::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
RedemptionRequest::from_bytes(xdr::unmarshaler& u) 
{
bool oksourceBalanceID = u.from_bytes(sourceBalanceID);
if (!oksourceBalanceID)
{
return false;
}
bool okdestination = u.from_bytes(destination);
if (!okdestination)
{
return false;
}
bool okamount = u.from_bytes(amount);
if (!okamount)
{
return false;
}
bool okcreatorDetails = u.from_bytes(creatorDetails);
if (!okcreatorDetails)
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
RedemptionRequest::to_bytes(xdr::marshaler& m) const 
{
bool oksourceBalanceID = m.to_bytes(sourceBalanceID);
if (!oksourceBalanceID)
{
return false;
}
bool okdestination = m.to_bytes(destination);
if (!okdestination)
{
return false;
}
bool okamount = m.to_bytes(amount);
if (!okamount)
{
return false;
}
bool okcreatorDetails = m.to_bytes(creatorDetails);
if (!okcreatorDetails)
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
RedemptionRequest::count_size(xdr::measurer& m) const 
{
m.count_size(sourceBalanceID);
m.count_size(destination);
m.count_size(amount);
m.count_size(creatorDetails);
m.count_size(ext);
}
bool
RedemptionRequest::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<RedemptionRequest const&>(other_abstract);return true
&& (sourceBalanceID== other.sourceBalanceID)
&& (destination== other.destination)
&& (amount== other.amount)
&& (creatorDetails== other.creatorDetails)
&& (ext== other.ext)
;}
bool
RedemptionRequest::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<RedemptionRequest const&>(other_abstract);
if (sourceBalanceID < other.sourceBalanceID) return true;
if (other.sourceBalanceID < sourceBalanceID) return false;
if (destination < other.destination) return true;
if (other.destination < destination) return false;
if (amount < other.amount) return true;
if (other.amount < amount) return false;
if (creatorDetails < other.creatorDetails) return true;
if (other.creatorDetails < creatorDetails) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}