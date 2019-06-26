#include "ledger-entries-statistics-v2.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
StatisticsV2Entry::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
StatisticsV2Entry::_ext_t::to_bytes(xdr::marshaler& m) const
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
StatisticsV2Entry::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
StatisticsV2Entry::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
StatisticsV2Entry::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
StatisticsV2Entry::from_bytes(xdr::unmarshaler& u) 
{
bool okid = u.from_bytes(id);
if (!okid)
{
return false;
}
bool okaccountID = u.from_bytes(accountID);
if (!okaccountID)
{
return false;
}
bool okstatsOpType = u.from_bytes(statsOpType);
if (!okstatsOpType)
{
return false;
}
bool okassetCode = u.from_bytes(assetCode);
if (!okassetCode)
{
return false;
}
bool okisConvertNeeded = u.from_bytes(isConvertNeeded);
if (!okisConvertNeeded)
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
StatisticsV2Entry::to_bytes(xdr::marshaler& m) const 
{
bool okid = m.to_bytes(id);
if (!okid)
{
return false;
}
bool okaccountID = m.to_bytes(accountID);
if (!okaccountID)
{
return false;
}
bool okstatsOpType = m.to_bytes(statsOpType);
if (!okstatsOpType)
{
return false;
}
bool okassetCode = m.to_bytes(assetCode);
if (!okassetCode)
{
return false;
}
bool okisConvertNeeded = m.to_bytes(isConvertNeeded);
if (!okisConvertNeeded)
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
StatisticsV2Entry::count_size(xdr::measurer& m) const 
{
m.count_size(id);
m.count_size(accountID);
m.count_size(statsOpType);
m.count_size(assetCode);
m.count_size(isConvertNeeded);
m.count_size(dailyOutcome);
m.count_size(weeklyOutcome);
m.count_size(monthlyOutcome);
m.count_size(annualOutcome);
m.count_size(updatedAt);
m.count_size(ext);
}
bool
StatisticsV2Entry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<StatisticsV2Entry const&>(other_abstract);return true
&& (id== other.id)
&& (accountID== other.accountID)
&& (statsOpType== other.statsOpType)
&& (assetCode== other.assetCode)
&& (isConvertNeeded== other.isConvertNeeded)
&& (dailyOutcome== other.dailyOutcome)
&& (weeklyOutcome== other.weeklyOutcome)
&& (monthlyOutcome== other.monthlyOutcome)
&& (annualOutcome== other.annualOutcome)
&& (updatedAt== other.updatedAt)
&& (ext== other.ext)
;}
bool
StatisticsV2Entry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<StatisticsV2Entry const&>(other_abstract);
if (id < other.id) return true;
if (other.id < id) return false;
if (accountID < other.accountID) return true;
if (other.accountID < accountID) return false;
if (statsOpType < other.statsOpType) return true;
if (other.statsOpType < statsOpType) return false;
if (assetCode < other.assetCode) return true;
if (other.assetCode < assetCode) return false;
if (isConvertNeeded < other.isConvertNeeded) return true;
if (other.isConvertNeeded < isConvertNeeded) return false;
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