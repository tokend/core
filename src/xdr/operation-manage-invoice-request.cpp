#include "operation-manage-invoice-request.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
InvoiceCreationRequest::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
InvoiceCreationRequest::_ext_t::to_bytes(xdr::marshaler& m) const
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
InvoiceCreationRequest::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
InvoiceCreationRequest::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
InvoiceCreationRequest::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
InvoiceCreationRequest::from_bytes(xdr::unmarshaler& u) 
{
bool okasset = u.from_bytes(asset);
if (!okasset)
{
return false;
}
bool oksender = u.from_bytes(sender);
if (!oksender)
{
return false;
}
bool okamount = u.from_bytes(amount);
if (!okamount)
{
return false;
}
bool okcontractID = u.from_bytes(contractID);
if (!okcontractID)
{
return false;
}
bool okdetails = u.from_bytes(details);
if (!okdetails)
{
return false;
}
bool okallTasks = u.from_bytes(allTasks);
if (!okallTasks)
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
InvoiceCreationRequest::to_bytes(xdr::marshaler& m) const 
{
bool okasset = m.to_bytes(asset);
if (!okasset)
{
return false;
}
bool oksender = m.to_bytes(sender);
if (!oksender)
{
return false;
}
bool okamount = m.to_bytes(amount);
if (!okamount)
{
return false;
}
bool okcontractID = m.to_bytes(contractID);
if (!okcontractID)
{
return false;
}
bool okdetails = m.to_bytes(details);
if (!okdetails)
{
return false;
}
bool okallTasks = m.to_bytes(allTasks);
if (!okallTasks)
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
InvoiceCreationRequest::count_size(xdr::measurer& m) const 
{
m.count_size(asset);
m.count_size(sender);
m.count_size(amount);
m.count_size(contractID);
m.count_size(details);
m.count_size(allTasks);
m.count_size(ext);
}
bool
InvoiceCreationRequest::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<InvoiceCreationRequest const&>(other_abstract);return true
&& (asset== other.asset)
&& (sender== other.sender)
&& (amount== other.amount)
&& (contractID== other.contractID)
&& (details== other.details)
&& (allTasks== other.allTasks)
&& (ext== other.ext)
;}
bool
InvoiceCreationRequest::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<InvoiceCreationRequest const&>(other_abstract);
if (asset < other.asset) return true;
if (other.asset < asset) return false;
if (sender < other.sender) return true;
if (other.sender < sender) return false;
if (amount < other.amount) return true;
if (other.amount < amount) return false;
if (contractID < other.contractID) return true;
if (other.contractID < contractID) return false;
if (details < other.details) return true;
if (other.details < details) return false;
if (allTasks < other.allTasks) return true;
if (other.allTasks < allTasks) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageInvoiceRequestOp::_details_t::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (action_)
{
    case (int32_t)ManageInvoiceRequestAction::CREATE:
return u.from_bytes(invoiceRequest_);
    case (int32_t)ManageInvoiceRequestAction::REMOVE:
return u.from_bytes(requestID_);
}
return false;
}
bool
ManageInvoiceRequestOp::_details_t::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(action_);
if (!ok)
{
return false;
}
switch (action_)
{

    case (int32_t)ManageInvoiceRequestAction::CREATE:
return m.to_bytes(invoiceRequest_);
    case (int32_t)ManageInvoiceRequestAction::REMOVE:
return m.to_bytes(requestID_);
}
return false;
}
void
ManageInvoiceRequestOp::_details_t::count_size(xdr::measurer& m) const
{
m.count_size(action_);
switch (action_)
{

    case (int32_t)ManageInvoiceRequestAction::CREATE:
return m.count_size(invoiceRequest_);
    case (int32_t)ManageInvoiceRequestAction::REMOVE:
return m.count_size(requestID_);
}
}
bool
ManageInvoiceRequestOp::_details_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_details_t const&>(other_abstract);
if (other.action_ != action_) return false;
switch (action_)
{
    case (int32_t)ManageInvoiceRequestAction::CREATE:
return invoiceRequest_ == other.invoiceRequest_;
    case (int32_t)ManageInvoiceRequestAction::REMOVE:
return requestID_ == other.requestID_;
}
return false;
}
bool
ManageInvoiceRequestOp::_details_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_details_t const&>(other_abstract);
if (action_ < other.action_) return true;
if (other.action_ < action_) return false;
switch (action_)
{
    case (int32_t)ManageInvoiceRequestAction::CREATE:
return invoiceRequest_ < other.invoiceRequest_;
    case (int32_t)ManageInvoiceRequestAction::REMOVE:
return requestID_ < other.requestID_;
}
return false;
}
bool
ManageInvoiceRequestOp::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ManageInvoiceRequestOp::_ext_t::to_bytes(xdr::marshaler& m) const
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
ManageInvoiceRequestOp::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
ManageInvoiceRequestOp::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ManageInvoiceRequestOp::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ManageInvoiceRequestOp::from_bytes(xdr::unmarshaler& u) 
{
bool okdetails = u.from_bytes(details);
if (!okdetails)
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
ManageInvoiceRequestOp::to_bytes(xdr::marshaler& m) const 
{
bool okdetails = m.to_bytes(details);
if (!okdetails)
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
ManageInvoiceRequestOp::count_size(xdr::measurer& m) const 
{
m.count_size(details);
m.count_size(ext);
}
bool
ManageInvoiceRequestOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<ManageInvoiceRequestOp const&>(other_abstract);return true
&& (details== other.details)
&& (ext== other.ext)
;}
bool
ManageInvoiceRequestOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManageInvoiceRequestOp const&>(other_abstract);
if (details < other.details) return true;
if (other.details < details) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
CreateInvoiceRequestResponse::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
CreateInvoiceRequestResponse::_ext_t::to_bytes(xdr::marshaler& m) const
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
CreateInvoiceRequestResponse::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
CreateInvoiceRequestResponse::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
CreateInvoiceRequestResponse::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
CreateInvoiceRequestResponse::from_bytes(xdr::unmarshaler& u) 
{
bool okreceiverBalance = u.from_bytes(receiverBalance);
if (!okreceiverBalance)
{
return false;
}
bool oksenderBalance = u.from_bytes(senderBalance);
if (!oksenderBalance)
{
return false;
}
bool okrequestID = u.from_bytes(requestID);
if (!okrequestID)
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
CreateInvoiceRequestResponse::to_bytes(xdr::marshaler& m) const 
{
bool okreceiverBalance = m.to_bytes(receiverBalance);
if (!okreceiverBalance)
{
return false;
}
bool oksenderBalance = m.to_bytes(senderBalance);
if (!oksenderBalance)
{
return false;
}
bool okrequestID = m.to_bytes(requestID);
if (!okrequestID)
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
CreateInvoiceRequestResponse::count_size(xdr::measurer& m) const 
{
m.count_size(receiverBalance);
m.count_size(senderBalance);
m.count_size(requestID);
m.count_size(ext);
}
bool
CreateInvoiceRequestResponse::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CreateInvoiceRequestResponse const&>(other_abstract);return true
&& (receiverBalance== other.receiverBalance)
&& (senderBalance== other.senderBalance)
&& (requestID== other.requestID)
&& (ext== other.ext)
;}
bool
CreateInvoiceRequestResponse::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreateInvoiceRequestResponse const&>(other_abstract);
if (receiverBalance < other.receiverBalance) return true;
if (other.receiverBalance < receiverBalance) return false;
if (senderBalance < other.senderBalance) return true;
if (other.senderBalance < senderBalance) return false;
if (requestID < other.requestID) return true;
if (other.requestID < requestID) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageInvoiceRequestResult::_success_t::_details_t::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (action_)
{
      case (int32_t)ManageInvoiceRequestAction::CREATE:
return u.from_bytes(response_);
      case (int32_t)ManageInvoiceRequestAction::REMOVE:
      
  return true;
}
return false;
}
bool
ManageInvoiceRequestResult::_success_t::_details_t::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(action_);
if (!ok)
{
return false;
}
switch (action_)
{

      case (int32_t)ManageInvoiceRequestAction::CREATE:
return m.to_bytes(response_);
      case (int32_t)ManageInvoiceRequestAction::REMOVE:
        return true;
}
return false;
}
void
ManageInvoiceRequestResult::_success_t::_details_t::count_size(xdr::measurer& m) const
{
m.count_size(action_);
switch (action_)
{

      case (int32_t)ManageInvoiceRequestAction::CREATE:
return m.count_size(response_);
      case (int32_t)ManageInvoiceRequestAction::REMOVE:
      
  return;
}
}
bool
ManageInvoiceRequestResult::_success_t::_details_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_details_t const&>(other_abstract);
if (other.action_ != action_) return false;
switch (action_)
{
      case (int32_t)ManageInvoiceRequestAction::CREATE:
return response_ == other.response_;
      case (int32_t)ManageInvoiceRequestAction::REMOVE:
      
  return true;
}
return false;
}
bool
ManageInvoiceRequestResult::_success_t::_details_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_details_t const&>(other_abstract);
if (action_ < other.action_) return true;
if (other.action_ < action_) return false;
switch (action_)
{
      case (int32_t)ManageInvoiceRequestAction::CREATE:
return response_ < other.response_;
      case (int32_t)ManageInvoiceRequestAction::REMOVE:
        return false;
}
return false;
}
bool
ManageInvoiceRequestResult::_success_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ManageInvoiceRequestResult::_success_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
ManageInvoiceRequestResult::_success_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
ManageInvoiceRequestResult::_success_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ManageInvoiceRequestResult::_success_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ManageInvoiceRequestResult::_success_t::from_bytes(xdr::unmarshaler& u) 
{
bool okfulfilled = u.from_bytes(fulfilled);
if (!okfulfilled)
{
return false;
}
bool okdetails = u.from_bytes(details);
if (!okdetails)
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
ManageInvoiceRequestResult::_success_t::to_bytes(xdr::marshaler& m) const 
{
bool okfulfilled = m.to_bytes(fulfilled);
if (!okfulfilled)
{
return false;
}
bool okdetails = m.to_bytes(details);
if (!okdetails)
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
ManageInvoiceRequestResult::_success_t::count_size(xdr::measurer& m) const 
{
m.count_size(fulfilled);
m.count_size(details);
m.count_size(ext);
}
bool
ManageInvoiceRequestResult::_success_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_success_t const&>(other_abstract);return true
&& (fulfilled== other.fulfilled)
&& (details== other.details)
&& (ext== other.ext)
;}
bool
ManageInvoiceRequestResult::_success_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_success_t const&>(other_abstract);
if (fulfilled < other.fulfilled) return true;
if (other.fulfilled < fulfilled) return false;
if (details < other.details) return true;
if (other.details < details) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageInvoiceRequestResult::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (code_)
{
  case (int32_t)ManageInvoiceRequestResultCode::SUCCESS:
return u.from_bytes(success_);
  default:
  
  return true;
}
return false;
}
bool
ManageInvoiceRequestResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)ManageInvoiceRequestResultCode::SUCCESS:
return m.to_bytes(success_);
  default:
    return true;
}
return false;
}
void
ManageInvoiceRequestResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)ManageInvoiceRequestResultCode::SUCCESS:
return m.count_size(success_);
  default:
  
  return;
}
}
bool
ManageInvoiceRequestResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<ManageInvoiceRequestResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)ManageInvoiceRequestResultCode::SUCCESS:
return success_ == other.success_;
  default:
  
  return true;
}
return false;
}
bool
ManageInvoiceRequestResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManageInvoiceRequestResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)ManageInvoiceRequestResultCode::SUCCESS:
return success_ < other.success_;
  default:
    return false;
}
return false;
}
}