#include "ledger-entries-limits-v2.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
LimitsV2Entry::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
LimitsV2Entry::_ext_t::to_bytes(xdr::marshaler& m) const
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
LimitsV2Entry::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
LimitsV2Entry::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
LimitsV2Entry::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
LimitsV2Entry::from_bytes(xdr::unmarshaler& u) 
{
bool okid = u.from_bytes(id);
if (!okid)
{
return false;
}
bool okaccountRole = u.from_bytes(accountRole);
if (!okaccountRole)
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
LimitsV2Entry::to_bytes(xdr::marshaler& m) const 
{
bool okid = m.to_bytes(id);
if (!okid)
{
return false;
}
bool okaccountRole = m.to_bytes(accountRole);
if (!okaccountRole)
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
LimitsV2Entry::count_size(xdr::measurer& m) const 
{
m.count_size(id);
m.count_size(accountRole);
m.count_size(accountID);
m.count_size(statsOpType);
m.count_size(assetCode);
m.count_size(isConvertNeeded);
m.count_size(dailyOut);
m.count_size(weeklyOut);
m.count_size(monthlyOut);
m.count_size(annualOut);
m.count_size(ext);
}
bool
LimitsV2Entry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<LimitsV2Entry const&>(other_abstract);return true
&& (id== other.id)
&& (accountRole== other.accountRole)
&& (accountID== other.accountID)
&& (statsOpType== other.statsOpType)
&& (assetCode== other.assetCode)
&& (isConvertNeeded== other.isConvertNeeded)
&& (dailyOut== other.dailyOut)
&& (weeklyOut== other.weeklyOut)
&& (monthlyOut== other.monthlyOut)
&& (annualOut== other.annualOut)
&& (ext== other.ext)
;}
bool
LimitsV2Entry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<LimitsV2Entry const&>(other_abstract);
if (id < other.id) return true;
if (other.id < id) return false;
if (accountRole < other.accountRole) return true;
if (other.accountRole < accountRole) return false;
if (accountID < other.accountID) return true;
if (other.accountID < accountID) return false;
if (statsOpType < other.statsOpType) return true;
if (other.statsOpType < statsOpType) return false;
if (assetCode < other.assetCode) return true;
if (other.assetCode < assetCode) return false;
if (isConvertNeeded < other.isConvertNeeded) return true;
if (other.isConvertNeeded < isConvertNeeded) return false;
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
}}