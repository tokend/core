#include "ledger-entries-signer-rule.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
SignerRuleEntry::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
SignerRuleEntry::_ext_t::to_bytes(xdr::marshaler& m) const
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
SignerRuleEntry::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
SignerRuleEntry::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
SignerRuleEntry::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
SignerRuleEntry::from_bytes(xdr::unmarshaler& u) 
{
bool okid = u.from_bytes(id);
if (!okid)
{
return false;
}
bool okresource = u.from_bytes(resource);
if (!okresource)
{
return false;
}
bool okaction = u.from_bytes(action);
if (!okaction)
{
return false;
}
bool okforbids = u.from_bytes(forbids);
if (!okforbids)
{
return false;
}
bool okisDefault = u.from_bytes(isDefault);
if (!okisDefault)
{
return false;
}
bool okdetails = u.from_bytes(details);
if (!okdetails)
{
return false;
}
bool okownerID = u.from_bytes(ownerID);
if (!okownerID)
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
SignerRuleEntry::to_bytes(xdr::marshaler& m) const 
{
bool okid = m.to_bytes(id);
if (!okid)
{
return false;
}
bool okresource = m.to_bytes(resource);
if (!okresource)
{
return false;
}
bool okaction = m.to_bytes(action);
if (!okaction)
{
return false;
}
bool okforbids = m.to_bytes(forbids);
if (!okforbids)
{
return false;
}
bool okisDefault = m.to_bytes(isDefault);
if (!okisDefault)
{
return false;
}
bool okdetails = m.to_bytes(details);
if (!okdetails)
{
return false;
}
bool okownerID = m.to_bytes(ownerID);
if (!okownerID)
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
SignerRuleEntry::count_size(xdr::measurer& m) const 
{
m.count_size(id);
m.count_size(resource);
m.count_size(action);
m.count_size(forbids);
m.count_size(isDefault);
m.count_size(details);
m.count_size(ownerID);
m.count_size(ext);
}
bool
SignerRuleEntry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<SignerRuleEntry const&>(other_abstract);return true
&& (id== other.id)
&& (resource== other.resource)
&& (action== other.action)
&& (forbids== other.forbids)
&& (isDefault== other.isDefault)
&& (details== other.details)
&& (ownerID== other.ownerID)
&& (ext== other.ext)
;}
bool
SignerRuleEntry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<SignerRuleEntry const&>(other_abstract);
if (id < other.id) return true;
if (other.id < id) return false;
if (resource < other.resource) return true;
if (other.resource < resource) return false;
if (action < other.action) return true;
if (other.action < action) return false;
if (forbids < other.forbids) return true;
if (other.forbids < forbids) return false;
if (isDefault < other.isDefault) return true;
if (other.isDefault < isDefault) return false;
if (details < other.details) return true;
if (other.details < details) return false;
if (ownerID < other.ownerID) return true;
if (other.ownerID < ownerID) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}