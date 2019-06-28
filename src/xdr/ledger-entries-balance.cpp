#include "ledger-entries-balance.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
BalanceEntry::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
BalanceEntry::_ext_t::to_bytes(xdr::marshaler& m) const
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
BalanceEntry::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
BalanceEntry::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
BalanceEntry::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
BalanceEntry::from_bytes(xdr::unmarshaler& u) 
{
bool okbalanceID = u.from_bytes(balanceID);
if (!okbalanceID)
{
return false;
}
bool oksequentialID = u.from_bytes(sequentialID);
if (!oksequentialID)
{
return false;
}
bool okasset = u.from_bytes(asset);
if (!okasset)
{
return false;
}
bool okaccountID = u.from_bytes(accountID);
if (!okaccountID)
{
return false;
}
bool okamount = u.from_bytes(amount);
if (!okamount)
{
return false;
}
bool oklocked = u.from_bytes(locked);
if (!oklocked)
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
BalanceEntry::to_bytes(xdr::marshaler& m) const 
{
bool okbalanceID = m.to_bytes(balanceID);
if (!okbalanceID)
{
return false;
}
bool oksequentialID = m.to_bytes(sequentialID);
if (!oksequentialID)
{
return false;
}
bool okasset = m.to_bytes(asset);
if (!okasset)
{
return false;
}
bool okaccountID = m.to_bytes(accountID);
if (!okaccountID)
{
return false;
}
bool okamount = m.to_bytes(amount);
if (!okamount)
{
return false;
}
bool oklocked = m.to_bytes(locked);
if (!oklocked)
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
BalanceEntry::count_size(xdr::measurer& m) const 
{
m.count_size(balanceID);
m.count_size(sequentialID);
m.count_size(asset);
m.count_size(accountID);
m.count_size(amount);
m.count_size(locked);
m.count_size(ext);
}
bool
BalanceEntry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<BalanceEntry const&>(other_abstract);return true
&& (balanceID== other.balanceID)
&& (sequentialID== other.sequentialID)
&& (asset== other.asset)
&& (accountID== other.accountID)
&& (amount== other.amount)
&& (locked== other.locked)
&& (ext== other.ext)
;}
bool
BalanceEntry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<BalanceEntry const&>(other_abstract);
if (balanceID < other.balanceID) return true;
if (other.balanceID < balanceID) return false;
if (sequentialID < other.sequentialID) return true;
if (other.sequentialID < sequentialID) return false;
if (asset < other.asset) return true;
if (other.asset < asset) return false;
if (accountID < other.accountID) return true;
if (other.accountID < accountID) return false;
if (amount < other.amount) return true;
if (other.amount < amount) return false;
if (locked < other.locked) return true;
if (other.locked < locked) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}