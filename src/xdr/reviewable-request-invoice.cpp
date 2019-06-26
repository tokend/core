#include "reviewable-request-invoice.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
InvoiceRequest::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
InvoiceRequest::_ext_t::to_bytes(xdr::marshaler& m) const
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
InvoiceRequest::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
InvoiceRequest::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
InvoiceRequest::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
InvoiceRequest::from_bytes(xdr::unmarshaler& u) 
{
bool okasset = u.from_bytes(asset);
if (!okasset)
{
return false;
}
bool okamount = u.from_bytes(amount);
if (!okamount)
{
return false;
}
bool oksenderBalance = u.from_bytes(senderBalance);
if (!oksenderBalance)
{
return false;
}
bool okreceiverBalance = u.from_bytes(receiverBalance);
if (!okreceiverBalance)
{
return false;
}
bool okcontractID = u.from_bytes(contractID);
if (!okcontractID)
{
return false;
}
bool okisApproved = u.from_bytes(isApproved);
if (!okisApproved)
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
InvoiceRequest::to_bytes(xdr::marshaler& m) const 
{
bool okasset = m.to_bytes(asset);
if (!okasset)
{
return false;
}
bool okamount = m.to_bytes(amount);
if (!okamount)
{
return false;
}
bool oksenderBalance = m.to_bytes(senderBalance);
if (!oksenderBalance)
{
return false;
}
bool okreceiverBalance = m.to_bytes(receiverBalance);
if (!okreceiverBalance)
{
return false;
}
bool okcontractID = m.to_bytes(contractID);
if (!okcontractID)
{
return false;
}
bool okisApproved = m.to_bytes(isApproved);
if (!okisApproved)
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
InvoiceRequest::count_size(xdr::measurer& m) const 
{
m.count_size(asset);
m.count_size(amount);
m.count_size(senderBalance);
m.count_size(receiverBalance);
m.count_size(contractID);
m.count_size(isApproved);
m.count_size(creatorDetails);
m.count_size(ext);
}
bool
InvoiceRequest::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<InvoiceRequest const&>(other_abstract);return true
&& (asset== other.asset)
&& (amount== other.amount)
&& (senderBalance== other.senderBalance)
&& (receiverBalance== other.receiverBalance)
&& (contractID== other.contractID)
&& (isApproved== other.isApproved)
&& (creatorDetails== other.creatorDetails)
&& (ext== other.ext)
;}
bool
InvoiceRequest::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<InvoiceRequest const&>(other_abstract);
if (asset < other.asset) return true;
if (other.asset < asset) return false;
if (amount < other.amount) return true;
if (other.amount < amount) return false;
if (senderBalance < other.senderBalance) return true;
if (other.senderBalance < senderBalance) return false;
if (receiverBalance < other.receiverBalance) return true;
if (other.receiverBalance < receiverBalance) return false;
if (contractID < other.contractID) return true;
if (other.contractID < contractID) return false;
if (isApproved < other.isApproved) return true;
if (other.isApproved < isApproved) return false;
if (creatorDetails < other.creatorDetails) return true;
if (other.creatorDetails < creatorDetails) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}