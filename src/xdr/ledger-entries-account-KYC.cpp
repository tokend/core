#include "ledger-entries-account-KYC.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
AccountKYCEntry::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
AccountKYCEntry::_ext_t::to_bytes(xdr::marshaler& m) const
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
AccountKYCEntry::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
AccountKYCEntry::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
AccountKYCEntry::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
AccountKYCEntry::from_bytes(xdr::unmarshaler& u) 
{
bool okaccountID = u.from_bytes(accountID);
if (!okaccountID)
{
return false;
}
bool okKYCData = u.from_bytes(KYCData);
if (!okKYCData)
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
AccountKYCEntry::to_bytes(xdr::marshaler& m) const 
{
bool okaccountID = m.to_bytes(accountID);
if (!okaccountID)
{
return false;
}
bool okKYCData = m.to_bytes(KYCData);
if (!okKYCData)
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
AccountKYCEntry::count_size(xdr::measurer& m) const 
{
m.count_size(accountID);
m.count_size(KYCData);
m.count_size(ext);
}
bool
AccountKYCEntry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<AccountKYCEntry const&>(other_abstract);return true
&& (accountID== other.accountID)
&& (KYCData== other.KYCData)
&& (ext== other.ext)
;}
bool
AccountKYCEntry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<AccountKYCEntry const&>(other_abstract);
if (accountID < other.accountID) return true;
if (other.accountID < accountID) return false;
if (KYCData < other.KYCData) return true;
if (other.KYCData < KYCData) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}