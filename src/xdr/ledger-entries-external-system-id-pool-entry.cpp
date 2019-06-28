#include "ledger-entries-external-system-id-pool-entry.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
ExternalSystemAccountIDPoolEntry::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ExternalSystemAccountIDPoolEntry::_ext_t::to_bytes(xdr::marshaler& m) const
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
ExternalSystemAccountIDPoolEntry::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
ExternalSystemAccountIDPoolEntry::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ExternalSystemAccountIDPoolEntry::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ExternalSystemAccountIDPoolEntry::from_bytes(xdr::unmarshaler& u) 
{
bool okpoolEntryID = u.from_bytes(poolEntryID);
if (!okpoolEntryID)
{
return false;
}
bool okexternalSystemType = u.from_bytes(externalSystemType);
if (!okexternalSystemType)
{
return false;
}
bool okdata = u.from_bytes(data);
if (!okdata)
{
return false;
}
bool okaccountID = u.from_bytes(accountID);
if (!okaccountID)
{
return false;
}
bool okexpiresAt = u.from_bytes(expiresAt);
if (!okexpiresAt)
{
return false;
}
bool okbindedAt = u.from_bytes(bindedAt);
if (!okbindedAt)
{
return false;
}
bool okparent = u.from_bytes(parent);
if (!okparent)
{
return false;
}
bool okisDeleted = u.from_bytes(isDeleted);
if (!okisDeleted)
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
ExternalSystemAccountIDPoolEntry::to_bytes(xdr::marshaler& m) const 
{
bool okpoolEntryID = m.to_bytes(poolEntryID);
if (!okpoolEntryID)
{
return false;
}
bool okexternalSystemType = m.to_bytes(externalSystemType);
if (!okexternalSystemType)
{
return false;
}
bool okdata = m.to_bytes(data);
if (!okdata)
{
return false;
}
bool okaccountID = m.to_bytes(accountID);
if (!okaccountID)
{
return false;
}
bool okexpiresAt = m.to_bytes(expiresAt);
if (!okexpiresAt)
{
return false;
}
bool okbindedAt = m.to_bytes(bindedAt);
if (!okbindedAt)
{
return false;
}
bool okparent = m.to_bytes(parent);
if (!okparent)
{
return false;
}
bool okisDeleted = m.to_bytes(isDeleted);
if (!okisDeleted)
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
ExternalSystemAccountIDPoolEntry::count_size(xdr::measurer& m) const 
{
m.count_size(poolEntryID);
m.count_size(externalSystemType);
m.count_size(data);
m.count_size(accountID);
m.count_size(expiresAt);
m.count_size(bindedAt);
m.count_size(parent);
m.count_size(isDeleted);
m.count_size(ext);
}
bool
ExternalSystemAccountIDPoolEntry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<ExternalSystemAccountIDPoolEntry const&>(other_abstract);return true
&& (poolEntryID== other.poolEntryID)
&& (externalSystemType== other.externalSystemType)
&& (data== other.data)
&& (accountID== other.accountID)
&& (expiresAt== other.expiresAt)
&& (bindedAt== other.bindedAt)
&& (parent== other.parent)
&& (isDeleted== other.isDeleted)
&& (ext== other.ext)
;}
bool
ExternalSystemAccountIDPoolEntry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ExternalSystemAccountIDPoolEntry const&>(other_abstract);
if (poolEntryID < other.poolEntryID) return true;
if (other.poolEntryID < poolEntryID) return false;
if (externalSystemType < other.externalSystemType) return true;
if (other.externalSystemType < externalSystemType) return false;
if (data < other.data) return true;
if (other.data < data) return false;
if (accountID < other.accountID) return true;
if (other.accountID < accountID) return false;
if (expiresAt < other.expiresAt) return true;
if (other.expiresAt < expiresAt) return false;
if (bindedAt < other.bindedAt) return true;
if (other.bindedAt < bindedAt) return false;
if (parent < other.parent) return true;
if (other.parent < parent) return false;
if (isDeleted < other.isDeleted) return true;
if (other.isDeleted < isDeleted) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}