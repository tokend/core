#include "ledger-entries-contract.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
ContractEntry::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ContractEntry::_ext_t::to_bytes(xdr::marshaler& m) const
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
ContractEntry::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
ContractEntry::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ContractEntry::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ContractEntry::from_bytes(xdr::unmarshaler& u) 
{
bool okcontractID = u.from_bytes(contractID);
if (!okcontractID)
{
return false;
}
bool okcontractor = u.from_bytes(contractor);
if (!okcontractor)
{
return false;
}
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
bool okinvoiceRequestsIDs = u.from_bytes(invoiceRequestsIDs);
if (!okinvoiceRequestsIDs)
{
return false;
}
bool okinitialDetails = u.from_bytes(initialDetails);
if (!okinitialDetails)
{
return false;
}
bool okstate = u.from_bytes(state);
if (!okstate)
{
return false;
}
bool okcustomerDetails = u.from_bytes(customerDetails);
if (!okcustomerDetails)
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
ContractEntry::to_bytes(xdr::marshaler& m) const 
{
bool okcontractID = m.to_bytes(contractID);
if (!okcontractID)
{
return false;
}
bool okcontractor = m.to_bytes(contractor);
if (!okcontractor)
{
return false;
}
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
bool okinvoiceRequestsIDs = m.to_bytes(invoiceRequestsIDs);
if (!okinvoiceRequestsIDs)
{
return false;
}
bool okinitialDetails = m.to_bytes(initialDetails);
if (!okinitialDetails)
{
return false;
}
bool okstate = m.to_bytes(state);
if (!okstate)
{
return false;
}
bool okcustomerDetails = m.to_bytes(customerDetails);
if (!okcustomerDetails)
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
ContractEntry::count_size(xdr::measurer& m) const 
{
m.count_size(contractID);
m.count_size(contractor);
m.count_size(customer);
m.count_size(escrow);
m.count_size(startTime);
m.count_size(endTime);
m.count_size(invoiceRequestsIDs);
m.count_size(initialDetails);
m.count_size(state);
m.count_size(customerDetails);
m.count_size(ext);
}
bool
ContractEntry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<ContractEntry const&>(other_abstract);return true
&& (contractID== other.contractID)
&& (contractor== other.contractor)
&& (customer== other.customer)
&& (escrow== other.escrow)
&& (startTime== other.startTime)
&& (endTime== other.endTime)
&& (invoiceRequestsIDs== other.invoiceRequestsIDs)
&& (initialDetails== other.initialDetails)
&& (state== other.state)
&& (customerDetails== other.customerDetails)
&& (ext== other.ext)
;}
bool
ContractEntry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ContractEntry const&>(other_abstract);
if (contractID < other.contractID) return true;
if (other.contractID < contractID) return false;
if (contractor < other.contractor) return true;
if (other.contractor < contractor) return false;
if (customer < other.customer) return true;
if (other.customer < customer) return false;
if (escrow < other.escrow) return true;
if (other.escrow < escrow) return false;
if (startTime < other.startTime) return true;
if (other.startTime < startTime) return false;
if (endTime < other.endTime) return true;
if (other.endTime < endTime) return false;
if (invoiceRequestsIDs < other.invoiceRequestsIDs) return true;
if (other.invoiceRequestsIDs < invoiceRequestsIDs) return false;
if (initialDetails < other.initialDetails) return true;
if (other.initialDetails < initialDetails) return false;
if (state < other.state) return true;
if (other.state < state) return false;
if (customerDetails < other.customerDetails) return true;
if (other.customerDetails < customerDetails) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}