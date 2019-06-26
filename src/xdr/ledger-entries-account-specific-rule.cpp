#include "ledger-entries-account-specific-rule.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
AccountSpecificRuleEntry::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
AccountSpecificRuleEntry::_ext_t::to_bytes(xdr::marshaler& m) const
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
AccountSpecificRuleEntry::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
AccountSpecificRuleEntry::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
AccountSpecificRuleEntry::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
AccountSpecificRuleEntry::from_bytes(xdr::unmarshaler& u) 
{
bool okid = u.from_bytes(id);
if (!okid)
{
return false;
}
bool okledgerKey = u.from_bytes(ledgerKey);
if (!okledgerKey)
{
return false;
}
bool okaccountID = u.from_bytes(accountID);
if (!okaccountID)
{
return false;
}
bool okforbids = u.from_bytes(forbids);
if (!okforbids)
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
AccountSpecificRuleEntry::to_bytes(xdr::marshaler& m) const 
{
bool okid = m.to_bytes(id);
if (!okid)
{
return false;
}
bool okledgerKey = m.to_bytes(ledgerKey);
if (!okledgerKey)
{
return false;
}
bool okaccountID = m.to_bytes(accountID);
if (!okaccountID)
{
return false;
}
bool okforbids = m.to_bytes(forbids);
if (!okforbids)
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
AccountSpecificRuleEntry::count_size(xdr::measurer& m) const 
{
m.count_size(id);
m.count_size(ledgerKey);
m.count_size(accountID);
m.count_size(forbids);
m.count_size(ext);
}
bool
AccountSpecificRuleEntry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<AccountSpecificRuleEntry const&>(other_abstract);return true
&& (id== other.id)
&& (ledgerKey== other.ledgerKey)
&& (accountID== other.accountID)
&& (forbids== other.forbids)
&& (ext== other.ext)
;}
bool
AccountSpecificRuleEntry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<AccountSpecificRuleEntry const&>(other_abstract);
if (id < other.id) return true;
if (other.id < id) return false;
if (ledgerKey < other.ledgerKey) return true;
if (other.ledgerKey < ledgerKey) return false;
if (accountID < other.accountID) return true;
if (other.accountID < accountID) return false;
if (forbids < other.forbids) return true;
if (other.forbids < forbids) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}