#include "ledger-entries-stamp.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
StampEntry::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
StampEntry::_ext_t::to_bytes(xdr::marshaler& m) const
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
StampEntry::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
StampEntry::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
StampEntry::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
StampEntry::from_bytes(xdr::unmarshaler& u) 
{
bool okledgerHash = u.from_bytes(ledgerHash);
if (!okledgerHash)
{
return false;
}
bool oklicenseHash = u.from_bytes(licenseHash);
if (!oklicenseHash)
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
StampEntry::to_bytes(xdr::marshaler& m) const 
{
bool okledgerHash = m.to_bytes(ledgerHash);
if (!okledgerHash)
{
return false;
}
bool oklicenseHash = m.to_bytes(licenseHash);
if (!oklicenseHash)
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
StampEntry::count_size(xdr::measurer& m) const 
{
m.count_size(ledgerHash);
m.count_size(licenseHash);
m.count_size(ext);
}
bool
StampEntry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<StampEntry const&>(other_abstract);return true
&& (ledgerHash== other.ledgerHash)
&& (licenseHash== other.licenseHash)
&& (ext== other.ext)
;}
bool
StampEntry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<StampEntry const&>(other_abstract);
if (ledgerHash < other.ledgerHash) return true;
if (other.ledgerHash < ledgerHash) return false;
if (licenseHash < other.licenseHash) return true;
if (other.licenseHash < licenseHash) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}