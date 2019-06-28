#include "reviewable-request-change-role.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
ChangeRoleRequest::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ChangeRoleRequest::_ext_t::to_bytes(xdr::marshaler& m) const
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
ChangeRoleRequest::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
ChangeRoleRequest::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ChangeRoleRequest::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ChangeRoleRequest::from_bytes(xdr::unmarshaler& u) 
{
bool okdestinationAccount = u.from_bytes(destinationAccount);
if (!okdestinationAccount)
{
return false;
}
bool okaccountRoleToSet = u.from_bytes(accountRoleToSet);
if (!okaccountRoleToSet)
{
return false;
}
bool oksequenceNumber = u.from_bytes(sequenceNumber);
if (!oksequenceNumber)
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
ChangeRoleRequest::to_bytes(xdr::marshaler& m) const 
{
bool okdestinationAccount = m.to_bytes(destinationAccount);
if (!okdestinationAccount)
{
return false;
}
bool okaccountRoleToSet = m.to_bytes(accountRoleToSet);
if (!okaccountRoleToSet)
{
return false;
}
bool oksequenceNumber = m.to_bytes(sequenceNumber);
if (!oksequenceNumber)
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
ChangeRoleRequest::count_size(xdr::measurer& m) const 
{
m.count_size(destinationAccount);
m.count_size(accountRoleToSet);
m.count_size(sequenceNumber);
m.count_size(creatorDetails);
m.count_size(ext);
}
bool
ChangeRoleRequest::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<ChangeRoleRequest const&>(other_abstract);return true
&& (destinationAccount== other.destinationAccount)
&& (accountRoleToSet== other.accountRoleToSet)
&& (sequenceNumber== other.sequenceNumber)
&& (creatorDetails== other.creatorDetails)
&& (ext== other.ext)
;}
bool
ChangeRoleRequest::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ChangeRoleRequest const&>(other_abstract);
if (destinationAccount < other.destinationAccount) return true;
if (other.destinationAccount < destinationAccount) return false;
if (accountRoleToSet < other.accountRoleToSet) return true;
if (other.accountRoleToSet < accountRoleToSet) return false;
if (sequenceNumber < other.sequenceNumber) return true;
if (other.sequenceNumber < sequenceNumber) return false;
if (creatorDetails < other.creatorDetails) return true;
if (other.creatorDetails < creatorDetails) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}