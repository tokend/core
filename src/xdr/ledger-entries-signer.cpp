#include "ledger-entries-signer.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
SignerEntry::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
SignerEntry::_ext_t::to_bytes(xdr::marshaler& m) const
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
SignerEntry::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
SignerEntry::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
SignerEntry::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
SignerEntry::from_bytes(xdr::unmarshaler& u) 
{
bool okpubKey = u.from_bytes(pubKey);
if (!okpubKey)
{
return false;
}
bool okaccountID = u.from_bytes(accountID);
if (!okaccountID)
{
return false;
}
bool okweight = u.from_bytes(weight);
if (!okweight)
{
return false;
}
bool okidentity = u.from_bytes(identity);
if (!okidentity)
{
return false;
}
bool okdetails = u.from_bytes(details);
if (!okdetails)
{
return false;
}
bool okroleID = u.from_bytes(roleID);
if (!okroleID)
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
SignerEntry::to_bytes(xdr::marshaler& m) const 
{
bool okpubKey = m.to_bytes(pubKey);
if (!okpubKey)
{
return false;
}
bool okaccountID = m.to_bytes(accountID);
if (!okaccountID)
{
return false;
}
bool okweight = m.to_bytes(weight);
if (!okweight)
{
return false;
}
bool okidentity = m.to_bytes(identity);
if (!okidentity)
{
return false;
}
bool okdetails = m.to_bytes(details);
if (!okdetails)
{
return false;
}
bool okroleID = m.to_bytes(roleID);
if (!okroleID)
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
SignerEntry::count_size(xdr::measurer& m) const 
{
m.count_size(pubKey);
m.count_size(accountID);
m.count_size(weight);
m.count_size(identity);
m.count_size(details);
m.count_size(roleID);
m.count_size(ext);
}
bool
SignerEntry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<SignerEntry const&>(other_abstract);return true
&& (pubKey== other.pubKey)
&& (accountID== other.accountID)
&& (weight== other.weight)
&& (identity== other.identity)
&& (details== other.details)
&& (roleID== other.roleID)
&& (ext== other.ext)
;}
bool
SignerEntry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<SignerEntry const&>(other_abstract);
if (pubKey < other.pubKey) return true;
if (other.pubKey < pubKey) return false;
if (accountID < other.accountID) return true;
if (other.accountID < accountID) return false;
if (weight < other.weight) return true;
if (other.weight < weight) return false;
if (identity < other.identity) return true;
if (other.identity < identity) return false;
if (details < other.details) return true;
if (other.details < details) return false;
if (roleID < other.roleID) return true;
if (other.roleID < roleID) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}