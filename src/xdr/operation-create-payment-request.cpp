#include "operation-create-payment-request.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
CreatePaymentRequestOp::from_bytes(xdr::unmarshaler& u) 
{
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
CreatePaymentRequestOp::to_bytes(xdr::marshaler& m) const 
{
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
CreatePaymentRequestOp::count_size(xdr::measurer& m) const 
{
m.count_size(request);
m.count_size(allTasks);
m.count_size(ext);
}
bool
CreatePaymentRequestOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CreatePaymentRequestOp const&>(other_abstract);return true
&& (request== other.request)
&& (allTasks== other.allTasks)
&& (ext== other.ext)
;}
bool
CreatePaymentRequestOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreatePaymentRequestOp const&>(other_abstract);
if (request < other.request) return true;
if (other.request < request) return false;
if (allTasks < other.allTasks) return true;
if (other.allTasks < allTasks) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
CreatePaymentRequestSuccessResult::from_bytes(xdr::unmarshaler& u) 
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
bool okext = u.from_bytes(ext);
if (!okext)
{
return false;
}
return true;
}
bool
CreatePaymentRequestSuccessResult::to_bytes(xdr::marshaler& m) const 
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
bool okext = m.to_bytes(ext);
if (!okext)
{
return false;
}
return true;
}
void
CreatePaymentRequestSuccessResult::count_size(xdr::measurer& m) const 
{
m.count_size(requestID);
m.count_size(fulfilled);
m.count_size(ext);
}
bool
CreatePaymentRequestSuccessResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CreatePaymentRequestSuccessResult const&>(other_abstract);return true
&& (requestID== other.requestID)
&& (fulfilled== other.fulfilled)
&& (ext== other.ext)
;}
bool
CreatePaymentRequestSuccessResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreatePaymentRequestSuccessResult const&>(other_abstract);
if (requestID < other.requestID) return true;
if (other.requestID < requestID) return false;
if (fulfilled < other.fulfilled) return true;
if (other.fulfilled < fulfilled) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
CreatePaymentRequestResult::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (code_)
{
  case (int32_t)CreatePaymentRequestResultCode::SUCCESS:
return u.from_bytes(success_);
  case (int32_t)CreatePaymentRequestResultCode::INVALID_PAYMENT:
return u.from_bytes(paymentCode_);
  default:
  
  return true;
}
return false;
}
bool
CreatePaymentRequestResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)CreatePaymentRequestResultCode::SUCCESS:
return m.to_bytes(success_);
  case (int32_t)CreatePaymentRequestResultCode::INVALID_PAYMENT:
return m.to_bytes(paymentCode_);
  default:
    return true;
}
return false;
}
void
CreatePaymentRequestResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)CreatePaymentRequestResultCode::SUCCESS:
return m.count_size(success_);
  case (int32_t)CreatePaymentRequestResultCode::INVALID_PAYMENT:
return m.count_size(paymentCode_);
  default:
  
  return;
}
}
bool
CreatePaymentRequestResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<CreatePaymentRequestResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)CreatePaymentRequestResultCode::SUCCESS:
return success_ == other.success_;
  case (int32_t)CreatePaymentRequestResultCode::INVALID_PAYMENT:
return paymentCode_ == other.paymentCode_;
  default:
  
  return true;
}
return false;
}
bool
CreatePaymentRequestResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreatePaymentRequestResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)CreatePaymentRequestResultCode::SUCCESS:
return success_ < other.success_;
  case (int32_t)CreatePaymentRequestResultCode::INVALID_PAYMENT:
return paymentCode_ < other.paymentCode_;
  default:
    return false;
}
return false;
}
}