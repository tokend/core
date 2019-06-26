#include "ledger-entries-statistics.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
StatisticsEntry::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
StatisticsEntry::_ext_t::to_bytes(xdr::marshaler& m) const
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
StatisticsEntry::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
StatisticsEntry::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
StatisticsEntry::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
StatisticsEntry::from_bytes(xdr::unmarshaler& u) 
{
bool okaccountID = u.from_bytes(accountID);
if (!okaccountID)
{
return false;
}
bool okdailyOutcome = u.from_bytes(dailyOutcome);
if (!okdailyOutcome)
{
return false;
}
bool okweeklyOutcome = u.from_bytes(weeklyOutcome);
if (!okweeklyOutcome)
{
return false;
}
bool okmonthlyOutcome = u.from_bytes(monthlyOutcome);
if (!okmonthlyOutcome)
{
return false;
}
bool okannualOutcome = u.from_bytes(annualOutcome);
if (!okannualOutcome)
{
return false;
}
bool okupdatedAt = u.from_bytes(updatedAt);
if (!okupdatedAt)
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
StatisticsEntry::to_bytes(xdr::marshaler& m) const 
{
bool okaccountID = m.to_bytes(accountID);
if (!okaccountID)
{
return false;
}
bool okdailyOutcome = m.to_bytes(dailyOutcome);
if (!okdailyOutcome)
{
return false;
}
bool okweeklyOutcome = m.to_bytes(weeklyOutcome);
if (!okweeklyOutcome)
{
return false;
}
bool okmonthlyOutcome = m.to_bytes(monthlyOutcome);
if (!okmonthlyOutcome)
{
return false;
}
bool okannualOutcome = m.to_bytes(annualOutcome);
if (!okannualOutcome)
{
return false;
}
bool okupdatedAt = m.to_bytes(updatedAt);
if (!okupdatedAt)
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
StatisticsEntry::count_size(xdr::measurer& m) const 
{
m.count_size(accountID);
m.count_size(dailyOutcome);
m.count_size(weeklyOutcome);
m.count_size(monthlyOutcome);
m.count_size(annualOutcome);
m.count_size(updatedAt);
m.count_size(ext);
}
bool
StatisticsEntry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<StatisticsEntry const&>(other_abstract);return true
&& (accountID== other.accountID)
&& (dailyOutcome== other.dailyOutcome)
&& (weeklyOutcome== other.weeklyOutcome)
&& (monthlyOutcome== other.monthlyOutcome)
&& (annualOutcome== other.annualOutcome)
&& (updatedAt== other.updatedAt)
&& (ext== other.ext)
;}
bool
StatisticsEntry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<StatisticsEntry const&>(other_abstract);
if (accountID < other.accountID) return true;
if (other.accountID < accountID) return false;
if (dailyOutcome < other.dailyOutcome) return true;
if (other.dailyOutcome < dailyOutcome) return false;
if (weeklyOutcome < other.weeklyOutcome) return true;
if (other.weeklyOutcome < weeklyOutcome) return false;
if (monthlyOutcome < other.monthlyOutcome) return true;
if (other.monthlyOutcome < monthlyOutcome) return false;
if (annualOutcome < other.annualOutcome) return true;
if (other.annualOutcome < annualOutcome) return false;
if (updatedAt < other.updatedAt) return true;
if (other.updatedAt < updatedAt) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}