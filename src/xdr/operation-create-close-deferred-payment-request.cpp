#include "operation-create-close-deferred-payment-request.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
CreateCloseDeferredPaymentRequestOp::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
CreateCloseDeferredPaymentRequestOp::_ext_t::to_bytes(xdr::marshaler& m) const
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
CreateCloseDeferredPaymentRequestOp::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
CreateCloseDeferredPaymentRequestOp::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
CreateCloseDeferredPaymentRequestOp::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
CreateCloseDeferredPaymentRequestOp::from_bytes(xdr::unmarshaler& u) 
{
bool okrequestID = u.from_bytes(requestID);
if (!okrequestID)
{
return false;
}
bool okrequest = u.from_bytes(request);
if (!okrequest)
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
CreateCloseDeferredPaymentRequestOp::to_bytes(xdr::marshaler& m) const 
{
bool okrequestID = m.to_bytes(requestID);
if (!okrequestID)
{
return false;
}
bool okrequest = m.to_bytes(request);
if (!okrequest)
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
CreateCloseDeferredPaymentRequestOp::count_size(xdr::measurer& m) const 
{
m.count_size(requestID);
m.count_size(request);
m.count_size(allTasks);
m.count_size(ext);
}
bool
CreateCloseDeferredPaymentRequestOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CreateCloseDeferredPaymentRequestOp const&>(other_abstract);return true
&& (requestID== other.requestID)
&& (request== other.request)
&& (allTasks== other.allTasks)
&& (ext== other.ext)
;}
bool
CreateCloseDeferredPaymentRequestOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreateCloseDeferredPaymentRequestOp const&>(other_abstract);
if (requestID < other.requestID) return true;
if (other.requestID < requestID) return false;
if (request < other.request) return true;
if (other.request < request) return false;
if (allTasks < other.allTasks) return true;
if (other.allTasks < allTasks) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
CloseDeferredPaymentResult::from_bytes(xdr::unmarshaler& u) 
{
bool okdeferredPaymentID = u.from_bytes(deferredPaymentID);
if (!okdeferredPaymentID)
{
return false;
}
bool okdestination = u.from_bytes(destination);
if (!okdestination)
{
return false;
}
bool okdestinationBalance = u.from_bytes(destinationBalance);
if (!okdestinationBalance)
{
return false;
}
bool okeffect = u.from_bytes(effect);
if (!okeffect)
{
return false;
}
bool okdeferredPaymentRemainder = u.from_bytes(deferredPaymentRemainder);
if (!okdeferredPaymentRemainder)
{
return false;
}
bool oktotalFee = u.from_bytes(totalFee);
if (!oktotalFee)
{
return false;
}
bool oktotalAmount = u.from_bytes(totalAmount);
if (!oktotalAmount)
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
CloseDeferredPaymentResult::to_bytes(xdr::marshaler& m) const 
{
bool okdeferredPaymentID = m.to_bytes(deferredPaymentID);
if (!okdeferredPaymentID)
{
return false;
}
bool okdestination = m.to_bytes(destination);
if (!okdestination)
{
return false;
}
bool okdestinationBalance = m.to_bytes(destinationBalance);
if (!okdestinationBalance)
{
return false;
}
bool okeffect = m.to_bytes(effect);
if (!okeffect)
{
return false;
}
bool okdeferredPaymentRemainder = m.to_bytes(deferredPaymentRemainder);
if (!okdeferredPaymentRemainder)
{
return false;
}
bool oktotalFee = m.to_bytes(totalFee);
if (!oktotalFee)
{
return false;
}
bool oktotalAmount = m.to_bytes(totalAmount);
if (!oktotalAmount)
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
CloseDeferredPaymentResult::count_size(xdr::measurer& m) const 
{
m.count_size(deferredPaymentID);
m.count_size(destination);
m.count_size(destinationBalance);
m.count_size(effect);
m.count_size(deferredPaymentRemainder);
m.count_size(totalFee);
m.count_size(totalAmount);
m.count_size(ext);
}
bool
CloseDeferredPaymentResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CloseDeferredPaymentResult const&>(other_abstract);return true
&& (deferredPaymentID== other.deferredPaymentID)
&& (destination== other.destination)
&& (destinationBalance== other.destinationBalance)
&& (effect== other.effect)
&& (deferredPaymentRemainder== other.deferredPaymentRemainder)
&& (totalFee== other.totalFee)
&& (totalAmount== other.totalAmount)
&& (ext== other.ext)
;}
bool
CloseDeferredPaymentResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CloseDeferredPaymentResult const&>(other_abstract);
if (deferredPaymentID < other.deferredPaymentID) return true;
if (other.deferredPaymentID < deferredPaymentID) return false;
if (destination < other.destination) return true;
if (other.destination < destination) return false;
if (destinationBalance < other.destinationBalance) return true;
if (other.destinationBalance < destinationBalance) return false;
if (effect < other.effect) return true;
if (other.effect < effect) return false;
if (deferredPaymentRemainder < other.deferredPaymentRemainder) return true;
if (other.deferredPaymentRemainder < deferredPaymentRemainder) return false;
if (totalFee < other.totalFee) return true;
if (other.totalFee < totalFee) return false;
if (totalAmount < other.totalAmount) return true;
if (other.totalAmount < totalAmount) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
CreateCloseDeferredPaymentRequestSuccess::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
CreateCloseDeferredPaymentRequestSuccess::_ext_t::to_bytes(xdr::marshaler& m) const
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
CreateCloseDeferredPaymentRequestSuccess::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
CreateCloseDeferredPaymentRequestSuccess::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
CreateCloseDeferredPaymentRequestSuccess::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
CreateCloseDeferredPaymentRequestSuccess::from_bytes(xdr::unmarshaler& u) 
{
bool okrequestID = u.from_bytes(requestID);
if (!okrequestID)
{
return false;
}
bool okfulfilled = u.from_bytes(fulfilled);
if (!okfulfilled)
{
return false;
}
bool okdeferredPaymentID = u.from_bytes(deferredPaymentID);
if (!okdeferredPaymentID)
{
return false;
}
bool okextendedResult = u.from_bytes(extendedResult);
if (!okextendedResult)
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
CreateCloseDeferredPaymentRequestSuccess::to_bytes(xdr::marshaler& m) const 
{
bool okrequestID = m.to_bytes(requestID);
if (!okrequestID)
{
return false;
}
bool okfulfilled = m.to_bytes(fulfilled);
if (!okfulfilled)
{
return false;
}
bool okdeferredPaymentID = m.to_bytes(deferredPaymentID);
if (!okdeferredPaymentID)
{
return false;
}
bool okextendedResult = m.to_bytes(extendedResult);
if (!okextendedResult)
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
CreateCloseDeferredPaymentRequestSuccess::count_size(xdr::measurer& m) const 
{
m.count_size(requestID);
m.count_size(fulfilled);
m.count_size(deferredPaymentID);
m.count_size(extendedResult);
m.count_size(ext);
}
bool
CreateCloseDeferredPaymentRequestSuccess::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CreateCloseDeferredPaymentRequestSuccess const&>(other_abstract);return true
&& (requestID== other.requestID)
&& (fulfilled== other.fulfilled)
&& (deferredPaymentID== other.deferredPaymentID)
&& (extendedResult== other.extendedResult)
&& (ext== other.ext)
;}
bool
CreateCloseDeferredPaymentRequestSuccess::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreateCloseDeferredPaymentRequestSuccess const&>(other_abstract);
if (requestID < other.requestID) return true;
if (other.requestID < requestID) return false;
if (fulfilled < other.fulfilled) return true;
if (other.fulfilled < fulfilled) return false;
if (deferredPaymentID < other.deferredPaymentID) return true;
if (other.deferredPaymentID < deferredPaymentID) return false;
if (extendedResult < other.extendedResult) return true;
if (other.extendedResult < extendedResult) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
CreateCloseDeferredPaymentRequestResult::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (code_)
{
  case (int32_t)CreateCloseDeferredPaymentRequestResultCode::SUCCESS:
return u.from_bytes(success_);
  default:
  
  return true;
}
return false;
}
bool
CreateCloseDeferredPaymentRequestResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)CreateCloseDeferredPaymentRequestResultCode::SUCCESS:
return m.to_bytes(success_);
  default:
    return true;
}
return false;
}
void
CreateCloseDeferredPaymentRequestResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)CreateCloseDeferredPaymentRequestResultCode::SUCCESS:
return m.count_size(success_);
  default:
  
  return;
}
}
bool
CreateCloseDeferredPaymentRequestResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<CreateCloseDeferredPaymentRequestResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)CreateCloseDeferredPaymentRequestResultCode::SUCCESS:
return success_ == other.success_;
  default:
  
  return true;
}
return false;
}
bool
CreateCloseDeferredPaymentRequestResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreateCloseDeferredPaymentRequestResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)CreateCloseDeferredPaymentRequestResultCode::SUCCESS:
return success_ < other.success_;
  default:
    return false;
}
return false;
}
}