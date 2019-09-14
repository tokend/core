#include "operation-create-manage-offer-request.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
CreateManageOfferRequestOp::from_bytes(xdr::unmarshaler& u) 
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
CreateManageOfferRequestOp::to_bytes(xdr::marshaler& m) const 
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
CreateManageOfferRequestOp::count_size(xdr::measurer& m) const 
{
m.count_size(request);
m.count_size(allTasks);
m.count_size(ext);
}
bool
CreateManageOfferRequestOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CreateManageOfferRequestOp const&>(other_abstract);return true
&& (request== other.request)
&& (allTasks== other.allTasks)
&& (ext== other.ext)
;}
bool
CreateManageOfferRequestOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreateManageOfferRequestOp const&>(other_abstract);
if (request < other.request) return true;
if (other.request < request) return false;
if (allTasks < other.allTasks) return true;
if (other.allTasks < allTasks) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
CreateManagerOfferRequestSuccessResult::from_bytes(xdr::unmarshaler& u) 
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
bool okmanageOfferResult = u.from_bytes(manageOfferResult);
if (!okmanageOfferResult)
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
CreateManagerOfferRequestSuccessResult::to_bytes(xdr::marshaler& m) const 
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
bool okmanageOfferResult = m.to_bytes(manageOfferResult);
if (!okmanageOfferResult)
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
CreateManagerOfferRequestSuccessResult::count_size(xdr::measurer& m) const 
{
m.count_size(requestID);
m.count_size(fulfilled);
m.count_size(manageOfferResult);
m.count_size(ext);
}
bool
CreateManagerOfferRequestSuccessResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CreateManagerOfferRequestSuccessResult const&>(other_abstract);return true
&& (requestID== other.requestID)
&& (fulfilled== other.fulfilled)
&& (manageOfferResult== other.manageOfferResult)
&& (ext== other.ext)
;}
bool
CreateManagerOfferRequestSuccessResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreateManagerOfferRequestSuccessResult const&>(other_abstract);
if (requestID < other.requestID) return true;
if (other.requestID < requestID) return false;
if (fulfilled < other.fulfilled) return true;
if (other.fulfilled < fulfilled) return false;
if (manageOfferResult < other.manageOfferResult) return true;
if (other.manageOfferResult < manageOfferResult) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
CreateManageOfferRequestResult::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (code_)
{
  case (int32_t)CreateManageOfferRequestResultCode::SUCCESS:
return u.from_bytes(success_);
  case (int32_t)CreateManageOfferRequestResultCode::INVALID_OFFER:
return u.from_bytes(manageOfferCode_);
  default:
  
  return true;
}
return false;
}
bool
CreateManageOfferRequestResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)CreateManageOfferRequestResultCode::SUCCESS:
return m.to_bytes(success_);
  case (int32_t)CreateManageOfferRequestResultCode::INVALID_OFFER:
return m.to_bytes(manageOfferCode_);
  default:
    return true;
}
return false;
}
void
CreateManageOfferRequestResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)CreateManageOfferRequestResultCode::SUCCESS:
return m.count_size(success_);
  case (int32_t)CreateManageOfferRequestResultCode::INVALID_OFFER:
return m.count_size(manageOfferCode_);
  default:
  
  return;
}
}
bool
CreateManageOfferRequestResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<CreateManageOfferRequestResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)CreateManageOfferRequestResultCode::SUCCESS:
return success_ == other.success_;
  case (int32_t)CreateManageOfferRequestResultCode::INVALID_OFFER:
return manageOfferCode_ == other.manageOfferCode_;
  default:
  
  return true;
}
return false;
}
bool
CreateManageOfferRequestResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreateManageOfferRequestResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)CreateManageOfferRequestResultCode::SUCCESS:
return success_ < other.success_;
  case (int32_t)CreateManageOfferRequestResultCode::INVALID_OFFER:
return manageOfferCode_ < other.manageOfferCode_;
  default:
    return false;
}
return false;
}
}