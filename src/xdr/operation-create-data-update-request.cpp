#include "operation-create-data-update-request.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
CreateDataUpdateRequestOp::from_bytes(xdr::unmarshaler& u) 
{
bool okrequestID = u.from_bytes(requestID);
if (!okrequestID)
{
return false;
}
bool okdataUpdateRequest = u.from_bytes(dataUpdateRequest);
if (!okdataUpdateRequest)
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
CreateDataUpdateRequestOp::to_bytes(xdr::marshaler& m) const 
{
bool okrequestID = m.to_bytes(requestID);
if (!okrequestID)
{
return false;
}
bool okdataUpdateRequest = m.to_bytes(dataUpdateRequest);
if (!okdataUpdateRequest)
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
CreateDataUpdateRequestOp::count_size(xdr::measurer& m) const 
{
m.count_size(requestID);
m.count_size(dataUpdateRequest);
m.count_size(allTasks);
m.count_size(ext);
}
bool
CreateDataUpdateRequestOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CreateDataUpdateRequestOp const&>(other_abstract);return true
&& (requestID== other.requestID)
&& (dataUpdateRequest== other.dataUpdateRequest)
&& (allTasks== other.allTasks)
&& (ext== other.ext)
;}
bool
CreateDataUpdateRequestOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreateDataUpdateRequestOp const&>(other_abstract);
if (requestID < other.requestID) return true;
if (other.requestID < requestID) return false;
if (dataUpdateRequest < other.dataUpdateRequest) return true;
if (other.dataUpdateRequest < dataUpdateRequest) return false;
if (allTasks < other.allTasks) return true;
if (other.allTasks < allTasks) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
CreateDataUpdateRequestResponse::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
CreateDataUpdateRequestResponse::_ext_t::to_bytes(xdr::marshaler& m) const
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
CreateDataUpdateRequestResponse::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
CreateDataUpdateRequestResponse::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
CreateDataUpdateRequestResponse::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
CreateDataUpdateRequestResponse::from_bytes(xdr::unmarshaler& u) 
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
bool okowner = u.from_bytes(owner);
if (!okowner)
{
return false;
}
bool okid = u.from_bytes(id);
if (!okid)
{
return false;
}
bool oktype = u.from_bytes(type);
if (!oktype)
{
return false;
}
bool okvalue = u.from_bytes(value);
if (!okvalue)
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
CreateDataUpdateRequestResponse::to_bytes(xdr::marshaler& m) const 
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
bool okowner = m.to_bytes(owner);
if (!okowner)
{
return false;
}
bool okid = m.to_bytes(id);
if (!okid)
{
return false;
}
bool oktype = m.to_bytes(type);
if (!oktype)
{
return false;
}
bool okvalue = m.to_bytes(value);
if (!okvalue)
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
CreateDataUpdateRequestResponse::count_size(xdr::measurer& m) const 
{
m.count_size(requestID);
m.count_size(fulfilled);
m.count_size(owner);
m.count_size(id);
m.count_size(type);
m.count_size(value);
m.count_size(ext);
}
bool
CreateDataUpdateRequestResponse::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CreateDataUpdateRequestResponse const&>(other_abstract);return true
&& (requestID== other.requestID)
&& (fulfilled== other.fulfilled)
&& (owner== other.owner)
&& (id== other.id)
&& (type== other.type)
&& (value== other.value)
&& (ext== other.ext)
;}
bool
CreateDataUpdateRequestResponse::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreateDataUpdateRequestResponse const&>(other_abstract);
if (requestID < other.requestID) return true;
if (other.requestID < requestID) return false;
if (fulfilled < other.fulfilled) return true;
if (other.fulfilled < fulfilled) return false;
if (owner < other.owner) return true;
if (other.owner < owner) return false;
if (id < other.id) return true;
if (other.id < id) return false;
if (type < other.type) return true;
if (other.type < type) return false;
if (value < other.value) return true;
if (other.value < value) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
CreateDataUpdateRequestResult::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (code_)
{
  case (int32_t)CreateDataUpdateRequestResultCode::SUCCESS:
return u.from_bytes(createDataUpdateRequestResponse_);
  default:
  
  return true;
}
return false;
}
bool
CreateDataUpdateRequestResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)CreateDataUpdateRequestResultCode::SUCCESS:
return m.to_bytes(createDataUpdateRequestResponse_);
  default:
    return true;
}
return false;
}
void
CreateDataUpdateRequestResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)CreateDataUpdateRequestResultCode::SUCCESS:
return m.count_size(createDataUpdateRequestResponse_);
  default:
  
  return;
}
}
bool
CreateDataUpdateRequestResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<CreateDataUpdateRequestResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)CreateDataUpdateRequestResultCode::SUCCESS:
return createDataUpdateRequestResponse_ == other.createDataUpdateRequestResponse_;
  default:
  
  return true;
}
return false;
}
bool
CreateDataUpdateRequestResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreateDataUpdateRequestResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)CreateDataUpdateRequestResultCode::SUCCESS:
return createDataUpdateRequestResponse_ < other.createDataUpdateRequestResponse_;
  default:
    return false;
}
return false;
}
}