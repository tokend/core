#include "operation-create-manage-limits-request.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
CreateManageLimitsRequestOp::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
CreateManageLimitsRequestOp::_ext_t::to_bytes(xdr::marshaler& m) const
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
CreateManageLimitsRequestOp::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
CreateManageLimitsRequestOp::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
CreateManageLimitsRequestOp::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
CreateManageLimitsRequestOp::from_bytes(xdr::unmarshaler& u) 
{
bool okmanageLimitsRequest = u.from_bytes(manageLimitsRequest);
if (!okmanageLimitsRequest)
{
return false;
}
bool okallTasks = u.from_bytes(allTasks);
if (!okallTasks)
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
CreateManageLimitsRequestOp::to_bytes(xdr::marshaler& m) const 
{
bool okmanageLimitsRequest = m.to_bytes(manageLimitsRequest);
if (!okmanageLimitsRequest)
{
return false;
}
bool okallTasks = m.to_bytes(allTasks);
if (!okallTasks)
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
CreateManageLimitsRequestOp::count_size(xdr::measurer& m) const 
{
m.count_size(manageLimitsRequest);
m.count_size(allTasks);
m.count_size(requestID);
m.count_size(ext);
}
bool
CreateManageLimitsRequestOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CreateManageLimitsRequestOp const&>(other_abstract);return true
&& (manageLimitsRequest== other.manageLimitsRequest)
&& (allTasks== other.allTasks)
&& (requestID== other.requestID)
&& (ext== other.ext)
;}
bool
CreateManageLimitsRequestOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreateManageLimitsRequestOp const&>(other_abstract);
if (manageLimitsRequest < other.manageLimitsRequest) return true;
if (other.manageLimitsRequest < manageLimitsRequest) return false;
if (allTasks < other.allTasks) return true;
if (other.allTasks < allTasks) return false;
if (requestID < other.requestID) return true;
if (other.requestID < requestID) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
CreateManageLimitsRequestResult::_success_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
CreateManageLimitsRequestResult::_success_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
CreateManageLimitsRequestResult::_success_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
CreateManageLimitsRequestResult::_success_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
CreateManageLimitsRequestResult::_success_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
CreateManageLimitsRequestResult::_success_t::from_bytes(xdr::unmarshaler& u) 
{
bool okmanageLimitsRequestID = u.from_bytes(manageLimitsRequestID);
if (!okmanageLimitsRequestID)
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
CreateManageLimitsRequestResult::_success_t::to_bytes(xdr::marshaler& m) const 
{
bool okmanageLimitsRequestID = m.to_bytes(manageLimitsRequestID);
if (!okmanageLimitsRequestID)
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
CreateManageLimitsRequestResult::_success_t::count_size(xdr::measurer& m) const 
{
m.count_size(manageLimitsRequestID);
m.count_size(fulfilled);
m.count_size(ext);
}
bool
CreateManageLimitsRequestResult::_success_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_success_t const&>(other_abstract);return true
&& (manageLimitsRequestID== other.manageLimitsRequestID)
&& (fulfilled== other.fulfilled)
&& (ext== other.ext)
;}
bool
CreateManageLimitsRequestResult::_success_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_success_t const&>(other_abstract);
if (manageLimitsRequestID < other.manageLimitsRequestID) return true;
if (other.manageLimitsRequestID < manageLimitsRequestID) return false;
if (fulfilled < other.fulfilled) return true;
if (other.fulfilled < fulfilled) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
CreateManageLimitsRequestResult::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)CreateManageLimitsRequestResultCode::SUCCESS:
return u.from_bytes(success_);
  default:
    return true;
}
return false;
}
bool
CreateManageLimitsRequestResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)CreateManageLimitsRequestResultCode::SUCCESS:
return m.to_bytes(success_);
  default:
    return true;
}
return false;
}
void
CreateManageLimitsRequestResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)CreateManageLimitsRequestResultCode::SUCCESS:
return m.count_size(success_);
  default:
  
  return;
}
}
bool
CreateManageLimitsRequestResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<CreateManageLimitsRequestResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)CreateManageLimitsRequestResultCode::SUCCESS:
return success_ == other.success_;
  default:
  
  return true;
}
return false;
}
bool
CreateManageLimitsRequestResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreateManageLimitsRequestResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)CreateManageLimitsRequestResultCode::SUCCESS:
return success_ < other.success_;
  default:
    return false;
}
return false;
}
}