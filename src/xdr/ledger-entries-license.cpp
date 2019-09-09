#include "ledger-entries-license.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
LicenseEntry::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
LicenseEntry::_ext_t::to_bytes(xdr::marshaler& m) const
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
LicenseEntry::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
LicenseEntry::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
LicenseEntry::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
LicenseEntry::from_bytes(xdr::unmarshaler& u) 
{
bool okadminCount = u.from_bytes(adminCount);
if (!okadminCount)
{
return false;
}
bool okdueDate = u.from_bytes(dueDate);
if (!okdueDate)
{
return false;
}
bool okledgerHash = u.from_bytes(ledgerHash);
if (!okledgerHash)
{
return false;
}
bool okprevLicenseHash = u.from_bytes(prevLicenseHash);
if (!okprevLicenseHash)
{
return false;
}
bool oksignatures = u.from_bytes(signatures);
if (!oksignatures)
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
LicenseEntry::to_bytes(xdr::marshaler& m) const 
{
bool okadminCount = m.to_bytes(adminCount);
if (!okadminCount)
{
return false;
}
bool okdueDate = m.to_bytes(dueDate);
if (!okdueDate)
{
return false;
}
bool okledgerHash = m.to_bytes(ledgerHash);
if (!okledgerHash)
{
return false;
}
bool okprevLicenseHash = m.to_bytes(prevLicenseHash);
if (!okprevLicenseHash)
{
return false;
}
bool oksignatures = m.to_bytes(signatures);
if (!oksignatures)
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
LicenseEntry::count_size(xdr::measurer& m) const 
{
m.count_size(adminCount);
m.count_size(dueDate);
m.count_size(ledgerHash);
m.count_size(prevLicenseHash);
m.count_size(signatures);
m.count_size(ext);
}
bool
LicenseEntry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<LicenseEntry const&>(other_abstract);return true
&& (adminCount== other.adminCount)
&& (dueDate== other.dueDate)
&& (ledgerHash== other.ledgerHash)
&& (prevLicenseHash== other.prevLicenseHash)
&& (signatures== other.signatures)
&& (ext== other.ext)
;}
bool
LicenseEntry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<LicenseEntry const&>(other_abstract);
if (adminCount < other.adminCount) return true;
if (other.adminCount < adminCount) return false;
if (dueDate < other.dueDate) return true;
if (other.dueDate < dueDate) return false;
if (ledgerHash < other.ledgerHash) return true;
if (other.ledgerHash < ledgerHash) return false;
if (prevLicenseHash < other.prevLicenseHash) return true;
if (other.prevLicenseHash < prevLicenseHash) return false;
if (signatures < other.signatures) return true;
if (other.signatures < signatures) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}