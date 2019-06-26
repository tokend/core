#include "operation-create-sale-creation-request.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
CreateSaleCreationRequestOp::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
CreateSaleCreationRequestOp::_ext_t::to_bytes(xdr::marshaler& m) const
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
CreateSaleCreationRequestOp::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
CreateSaleCreationRequestOp::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
CreateSaleCreationRequestOp::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
CreateSaleCreationRequestOp::from_bytes(xdr::unmarshaler& u) 
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
CreateSaleCreationRequestOp::to_bytes(xdr::marshaler& m) const 
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
CreateSaleCreationRequestOp::count_size(xdr::measurer& m) const 
{
m.count_size(requestID);
m.count_size(request);
m.count_size(allTasks);
m.count_size(ext);
}
bool
CreateSaleCreationRequestOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CreateSaleCreationRequestOp const&>(other_abstract);return true
&& (requestID== other.requestID)
&& (request== other.request)
&& (allTasks== other.allTasks)
&& (ext== other.ext)
;}
bool
CreateSaleCreationRequestOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreateSaleCreationRequestOp const&>(other_abstract);
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
CreateSaleCreationSuccess::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
CreateSaleCreationSuccess::_ext_t::to_bytes(xdr::marshaler& m) const
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
CreateSaleCreationSuccess::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
CreateSaleCreationSuccess::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
CreateSaleCreationSuccess::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
CreateSaleCreationSuccess::from_bytes(xdr::unmarshaler& u) 
{
bool okrequestID = u.from_bytes(requestID);
if (!okrequestID)
{
return false;
}
bool oksaleID = u.from_bytes(saleID);
if (!oksaleID)
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
CreateSaleCreationSuccess::to_bytes(xdr::marshaler& m) const 
{
bool okrequestID = m.to_bytes(requestID);
if (!okrequestID)
{
return false;
}
bool oksaleID = m.to_bytes(saleID);
if (!oksaleID)
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
CreateSaleCreationSuccess::count_size(xdr::measurer& m) const 
{
m.count_size(requestID);
m.count_size(saleID);
m.count_size(fulfilled);
m.count_size(ext);
}
bool
CreateSaleCreationSuccess::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CreateSaleCreationSuccess const&>(other_abstract);return true
&& (requestID== other.requestID)
&& (saleID== other.saleID)
&& (fulfilled== other.fulfilled)
&& (ext== other.ext)
;}
bool
CreateSaleCreationSuccess::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreateSaleCreationSuccess const&>(other_abstract);
if (requestID < other.requestID) return true;
if (other.requestID < requestID) return false;
if (saleID < other.saleID) return true;
if (other.saleID < saleID) return false;
if (fulfilled < other.fulfilled) return true;
if (other.fulfilled < fulfilled) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
CreateSaleCreationAutoReviewFailed::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
CreateSaleCreationAutoReviewFailed::_ext_t::to_bytes(xdr::marshaler& m) const
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
CreateSaleCreationAutoReviewFailed::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
CreateSaleCreationAutoReviewFailed::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
CreateSaleCreationAutoReviewFailed::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
CreateSaleCreationAutoReviewFailed::from_bytes(xdr::unmarshaler& u) 
{
bool okreviewRequestRequest = u.from_bytes(reviewRequestRequest);
if (!okreviewRequestRequest)
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
CreateSaleCreationAutoReviewFailed::to_bytes(xdr::marshaler& m) const 
{
bool okreviewRequestRequest = m.to_bytes(reviewRequestRequest);
if (!okreviewRequestRequest)
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
CreateSaleCreationAutoReviewFailed::count_size(xdr::measurer& m) const 
{
m.count_size(reviewRequestRequest);
m.count_size(ext);
}
bool
CreateSaleCreationAutoReviewFailed::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CreateSaleCreationAutoReviewFailed const&>(other_abstract);return true
&& (reviewRequestRequest== other.reviewRequestRequest)
&& (ext== other.ext)
;}
bool
CreateSaleCreationAutoReviewFailed::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreateSaleCreationAutoReviewFailed const&>(other_abstract);
if (reviewRequestRequest < other.reviewRequestRequest) return true;
if (other.reviewRequestRequest < reviewRequestRequest) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
CreateSaleCreationRequestResult::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)CreateSaleCreationRequestResultCode::SUCCESS:
return u.from_bytes(success_);
  case (int32_t)CreateSaleCreationRequestResultCode::AUTO_REVIEW_FAILED:
return u.from_bytes(autoReviewFailed_);
  default:
    return true;
}
return false;
}
bool
CreateSaleCreationRequestResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)CreateSaleCreationRequestResultCode::SUCCESS:
return m.to_bytes(success_);
  case (int32_t)CreateSaleCreationRequestResultCode::AUTO_REVIEW_FAILED:
return m.to_bytes(autoReviewFailed_);
  default:
    return true;
}
return false;
}
void
CreateSaleCreationRequestResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)CreateSaleCreationRequestResultCode::SUCCESS:
return m.count_size(success_);
  case (int32_t)CreateSaleCreationRequestResultCode::AUTO_REVIEW_FAILED:
return m.count_size(autoReviewFailed_);
  default:
  
  return;
}
}
bool
CreateSaleCreationRequestResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<CreateSaleCreationRequestResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)CreateSaleCreationRequestResultCode::SUCCESS:
return success_ == other.success_;
  case (int32_t)CreateSaleCreationRequestResultCode::AUTO_REVIEW_FAILED:
return autoReviewFailed_ == other.autoReviewFailed_;
  default:
  
  return true;
}
return false;
}
bool
CreateSaleCreationRequestResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreateSaleCreationRequestResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)CreateSaleCreationRequestResultCode::SUCCESS:
return success_ < other.success_;
  case (int32_t)CreateSaleCreationRequestResultCode::AUTO_REVIEW_FAILED:
return autoReviewFailed_ < other.autoReviewFailed_;
  default:
    return false;
}
return false;
}
}