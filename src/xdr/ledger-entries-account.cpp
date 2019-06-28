#include "ledger-entries-account.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
Limits::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
Limits::_ext_t::to_bytes(xdr::marshaler& m) const
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
Limits::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
Limits::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
Limits::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
Limits::from_bytes(xdr::unmarshaler& u) 
{
bool okdailyOut = u.from_bytes(dailyOut);
if (!okdailyOut)
{
return false;
}
bool okweeklyOut = u.from_bytes(weeklyOut);
if (!okweeklyOut)
{
return false;
}
bool okmonthlyOut = u.from_bytes(monthlyOut);
if (!okmonthlyOut)
{
return false;
}
bool okannualOut = u.from_bytes(annualOut);
if (!okannualOut)
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
Limits::to_bytes(xdr::marshaler& m) const 
{
bool okdailyOut = m.to_bytes(dailyOut);
if (!okdailyOut)
{
return false;
}
bool okweeklyOut = m.to_bytes(weeklyOut);
if (!okweeklyOut)
{
return false;
}
bool okmonthlyOut = m.to_bytes(monthlyOut);
if (!okmonthlyOut)
{
return false;
}
bool okannualOut = m.to_bytes(annualOut);
if (!okannualOut)
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
Limits::count_size(xdr::measurer& m) const 
{
m.count_size(dailyOut);
m.count_size(weeklyOut);
m.count_size(monthlyOut);
m.count_size(annualOut);
m.count_size(ext);
}
bool
Limits::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<Limits const&>(other_abstract);return true
&& (dailyOut== other.dailyOut)
&& (weeklyOut== other.weeklyOut)
&& (monthlyOut== other.monthlyOut)
&& (annualOut== other.annualOut)
&& (ext== other.ext)
;}
bool
Limits::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<Limits const&>(other_abstract);
if (dailyOut < other.dailyOut) return true;
if (other.dailyOut < dailyOut) return false;
if (weeklyOut < other.weeklyOut) return true;
if (other.weeklyOut < weeklyOut) return false;
if (monthlyOut < other.monthlyOut) return true;
if (other.monthlyOut < monthlyOut) return false;
if (annualOut < other.annualOut) return true;
if (other.annualOut < annualOut) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
AccountEntry::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
AccountEntry::_ext_t::to_bytes(xdr::marshaler& m) const
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
AccountEntry::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
AccountEntry::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
AccountEntry::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
AccountEntry::from_bytes(xdr::unmarshaler& u) 
{
bool okaccountID = u.from_bytes(accountID);
if (!okaccountID)
{
return false;
}
bool okreferrer = u.from_bytes(referrer);
if (!okreferrer)
{
return false;
}
bool oksequentialID = u.from_bytes(sequentialID);
if (!oksequentialID)
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
AccountEntry::to_bytes(xdr::marshaler& m) const 
{
bool okaccountID = m.to_bytes(accountID);
if (!okaccountID)
{
return false;
}
bool okreferrer = m.to_bytes(referrer);
if (!okreferrer)
{
return false;
}
bool oksequentialID = m.to_bytes(sequentialID);
if (!oksequentialID)
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
AccountEntry::count_size(xdr::measurer& m) const 
{
m.count_size(accountID);
m.count_size(referrer);
m.count_size(sequentialID);
m.count_size(roleID);
m.count_size(ext);
}
bool
AccountEntry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<AccountEntry const&>(other_abstract);return true
&& (accountID== other.accountID)
&& (referrer== other.referrer)
&& (sequentialID== other.sequentialID)
&& (roleID== other.roleID)
&& (ext== other.ext)
;}
bool
AccountEntry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<AccountEntry const&>(other_abstract);
if (accountID < other.accountID) return true;
if (other.accountID < accountID) return false;
if (referrer < other.referrer) return true;
if (other.referrer < referrer) return false;
if (sequentialID < other.sequentialID) return true;
if (other.sequentialID < sequentialID) return false;
if (roleID < other.roleID) return true;
if (other.roleID < roleID) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}