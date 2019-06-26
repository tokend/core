#include "reviewable-request-withdrawal.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
WithdrawalRequest::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
WithdrawalRequest::_ext_t::to_bytes(xdr::marshaler& m) const
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
WithdrawalRequest::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
WithdrawalRequest::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
WithdrawalRequest::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
WithdrawalRequest::from_bytes(xdr::unmarshaler& u) 
{
bool okbalance = u.from_bytes(balance);
if (!okbalance)
{
return false;
}
bool okamount = u.from_bytes(amount);
if (!okamount)
{
return false;
}
bool okuniversalAmount = u.from_bytes(universalAmount);
if (!okuniversalAmount)
{
return false;
}
bool okfee = u.from_bytes(fee);
if (!okfee)
{
return false;
}
bool okcreatorDetails = u.from_bytes(creatorDetails);
if (!okcreatorDetails)
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
WithdrawalRequest::to_bytes(xdr::marshaler& m) const 
{
bool okbalance = m.to_bytes(balance);
if (!okbalance)
{
return false;
}
bool okamount = m.to_bytes(amount);
if (!okamount)
{
return false;
}
bool okuniversalAmount = m.to_bytes(universalAmount);
if (!okuniversalAmount)
{
return false;
}
bool okfee = m.to_bytes(fee);
if (!okfee)
{
return false;
}
bool okcreatorDetails = m.to_bytes(creatorDetails);
if (!okcreatorDetails)
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
WithdrawalRequest::count_size(xdr::measurer& m) const 
{
m.count_size(balance);
m.count_size(amount);
m.count_size(universalAmount);
m.count_size(fee);
m.count_size(creatorDetails);
m.count_size(ext);
}
bool
WithdrawalRequest::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<WithdrawalRequest const&>(other_abstract);return true
&& (balance== other.balance)
&& (amount== other.amount)
&& (universalAmount== other.universalAmount)
&& (fee== other.fee)
&& (creatorDetails== other.creatorDetails)
&& (ext== other.ext)
;}
bool
WithdrawalRequest::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<WithdrawalRequest const&>(other_abstract);
if (balance < other.balance) return true;
if (other.balance < balance) return false;
if (amount < other.amount) return true;
if (other.amount < amount) return false;
if (universalAmount < other.universalAmount) return true;
if (other.universalAmount < universalAmount) return false;
if (fee < other.fee) return true;
if (other.fee < fee) return false;
if (creatorDetails < other.creatorDetails) return true;
if (other.creatorDetails < creatorDetails) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}