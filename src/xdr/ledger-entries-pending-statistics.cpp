#include "ledger-entries-pending-statistics.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
PendingStatisticsEntry::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
PendingStatisticsEntry::_ext_t::to_bytes(xdr::marshaler& m) const
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
PendingStatisticsEntry::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
PendingStatisticsEntry::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
PendingStatisticsEntry::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
PendingStatisticsEntry::from_bytes(xdr::unmarshaler& u) 
{
bool okstatisticsID = u.from_bytes(statisticsID);
if (!okstatisticsID)
{
return false;
}
bool okrequestID = u.from_bytes(requestID);
if (!okrequestID)
{
return false;
}
bool okamount = u.from_bytes(amount);
if (!okamount)
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
PendingStatisticsEntry::to_bytes(xdr::marshaler& m) const 
{
bool okstatisticsID = m.to_bytes(statisticsID);
if (!okstatisticsID)
{
return false;
}
bool okrequestID = m.to_bytes(requestID);
if (!okrequestID)
{
return false;
}
bool okamount = m.to_bytes(amount);
if (!okamount)
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
PendingStatisticsEntry::count_size(xdr::measurer& m) const 
{
m.count_size(statisticsID);
m.count_size(requestID);
m.count_size(amount);
m.count_size(ext);
}
bool
PendingStatisticsEntry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<PendingStatisticsEntry const&>(other_abstract);return true
&& (statisticsID== other.statisticsID)
&& (requestID== other.requestID)
&& (amount== other.amount)
&& (ext== other.ext)
;}
bool
PendingStatisticsEntry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<PendingStatisticsEntry const&>(other_abstract);
if (statisticsID < other.statisticsID) return true;
if (other.statisticsID < statisticsID) return false;
if (requestID < other.requestID) return true;
if (other.requestID < requestID) return false;
if (amount < other.amount) return true;
if (other.amount < amount) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}