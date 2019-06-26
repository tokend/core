#include "reviewable-request-contract.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
ContractRequest::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ContractRequest::_ext_t::to_bytes(xdr::marshaler& m) const
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
ContractRequest::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
ContractRequest::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ContractRequest::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ContractRequest::from_bytes(xdr::unmarshaler& u) 
{
bool okcustomer = u.from_bytes(customer);
if (!okcustomer)
{
return false;
}
bool okescrow = u.from_bytes(escrow);
if (!okescrow)
{
return false;
}
bool okcreatorDetails = u.from_bytes(creatorDetails);
if (!okcreatorDetails)
{
return false;
}
bool okstartTime = u.from_bytes(startTime);
if (!okstartTime)
{
return false;
}
bool okendTime = u.from_bytes(endTime);
if (!okendTime)
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
ContractRequest::to_bytes(xdr::marshaler& m) const 
{
bool okcustomer = m.to_bytes(customer);
if (!okcustomer)
{
return false;
}
bool okescrow = m.to_bytes(escrow);
if (!okescrow)
{
return false;
}
bool okcreatorDetails = m.to_bytes(creatorDetails);
if (!okcreatorDetails)
{
return false;
}
bool okstartTime = m.to_bytes(startTime);
if (!okstartTime)
{
return false;
}
bool okendTime = m.to_bytes(endTime);
if (!okendTime)
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
ContractRequest::count_size(xdr::measurer& m) const 
{
m.count_size(customer);
m.count_size(escrow);
m.count_size(creatorDetails);
m.count_size(startTime);
m.count_size(endTime);
m.count_size(ext);
}
bool
ContractRequest::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<ContractRequest const&>(other_abstract);return true
&& (customer== other.customer)
&& (escrow== other.escrow)
&& (creatorDetails== other.creatorDetails)
&& (startTime== other.startTime)
&& (endTime== other.endTime)
&& (ext== other.ext)
;}
bool
ContractRequest::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ContractRequest const&>(other_abstract);
if (customer < other.customer) return true;
if (other.customer < customer) return false;
if (escrow < other.escrow) return true;
if (other.escrow < escrow) return false;
if (creatorDetails < other.creatorDetails) return true;
if (other.creatorDetails < creatorDetails) return false;
if (startTime < other.startTime) return true;
if (other.startTime < startTime) return false;
if (endTime < other.endTime) return true;
if (other.endTime < endTime) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}