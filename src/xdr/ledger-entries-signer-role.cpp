#include "ledger-entries-signer-role.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
SignerRoleEntry::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
SignerRoleEntry::_ext_t::to_bytes(xdr::marshaler& m) const
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
SignerRoleEntry::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
SignerRoleEntry::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
SignerRoleEntry::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
SignerRoleEntry::from_bytes(xdr::unmarshaler& u) 
{
bool okid = u.from_bytes(id);
if (!okid)
{
return false;
}
bool okruleIDs = u.from_bytes(ruleIDs);
if (!okruleIDs)
{
return false;
}
bool okownerID = u.from_bytes(ownerID);
if (!okownerID)
{
return false;
}
bool okdetails = u.from_bytes(details);
if (!okdetails)
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
SignerRoleEntry::to_bytes(xdr::marshaler& m) const 
{
bool okid = m.to_bytes(id);
if (!okid)
{
return false;
}
bool okruleIDs = m.to_bytes(ruleIDs);
if (!okruleIDs)
{
return false;
}
bool okownerID = m.to_bytes(ownerID);
if (!okownerID)
{
return false;
}
bool okdetails = m.to_bytes(details);
if (!okdetails)
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
SignerRoleEntry::count_size(xdr::measurer& m) const 
{
m.count_size(id);
m.count_size(ruleIDs);
m.count_size(ownerID);
m.count_size(details);
m.count_size(ext);
}
bool
SignerRoleEntry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<SignerRoleEntry const&>(other_abstract);return true
&& (id== other.id)
&& (ruleIDs== other.ruleIDs)
&& (ownerID== other.ownerID)
&& (details== other.details)
&& (ext== other.ext)
;}
bool
SignerRoleEntry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<SignerRoleEntry const&>(other_abstract);
if (id < other.id) return true;
if (other.id < id) return false;
if (ruleIDs < other.ruleIDs) return true;
if (other.ruleIDs < ruleIDs) return false;
if (ownerID < other.ownerID) return true;
if (other.ownerID < ownerID) return false;
if (details < other.details) return true;
if (other.details < details) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}