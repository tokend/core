#include "operation-create-AML-alert-request.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
CreateAMLAlertRequestOp::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
CreateAMLAlertRequestOp::_ext_t::to_bytes(xdr::marshaler& m) const
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
CreateAMLAlertRequestOp::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
CreateAMLAlertRequestOp::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
CreateAMLAlertRequestOp::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
CreateAMLAlertRequestOp::from_bytes(xdr::unmarshaler& u) 
{
bool okreference = u.from_bytes(reference);
if (!okreference)
{
return false;
}
bool okamlAlertRequest = u.from_bytes(amlAlertRequest);
if (!okamlAlertRequest)
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
CreateAMLAlertRequestOp::to_bytes(xdr::marshaler& m) const 
{
bool okreference = m.to_bytes(reference);
if (!okreference)
{
return false;
}
bool okamlAlertRequest = m.to_bytes(amlAlertRequest);
if (!okamlAlertRequest)
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
CreateAMLAlertRequestOp::count_size(xdr::measurer& m) const 
{
m.count_size(reference);
m.count_size(amlAlertRequest);
m.count_size(allTasks);
m.count_size(ext);
}
bool
CreateAMLAlertRequestOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CreateAMLAlertRequestOp const&>(other_abstract);return true
&& (reference== other.reference)
&& (amlAlertRequest== other.amlAlertRequest)
&& (allTasks== other.allTasks)
&& (ext== other.ext)
;}
bool
CreateAMLAlertRequestOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreateAMLAlertRequestOp const&>(other_abstract);
if (reference < other.reference) return true;
if (other.reference < reference) return false;
if (amlAlertRequest < other.amlAlertRequest) return true;
if (other.amlAlertRequest < amlAlertRequest) return false;
if (allTasks < other.allTasks) return true;
if (other.allTasks < allTasks) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
CreateAMLAlertRequestSuccess::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
CreateAMLAlertRequestSuccess::_ext_t::to_bytes(xdr::marshaler& m) const
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
CreateAMLAlertRequestSuccess::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
CreateAMLAlertRequestSuccess::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
CreateAMLAlertRequestSuccess::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
CreateAMLAlertRequestSuccess::from_bytes(xdr::unmarshaler& u) 
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
CreateAMLAlertRequestSuccess::to_bytes(xdr::marshaler& m) const 
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
CreateAMLAlertRequestSuccess::count_size(xdr::measurer& m) const 
{
m.count_size(requestID);
m.count_size(fulfilled);
m.count_size(ext);
}
bool
CreateAMLAlertRequestSuccess::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CreateAMLAlertRequestSuccess const&>(other_abstract);return true
&& (requestID== other.requestID)
&& (fulfilled== other.fulfilled)
&& (ext== other.ext)
;}
bool
CreateAMLAlertRequestSuccess::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreateAMLAlertRequestSuccess const&>(other_abstract);
if (requestID < other.requestID) return true;
if (other.requestID < requestID) return false;
if (fulfilled < other.fulfilled) return true;
if (other.fulfilled < fulfilled) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
CreateAMLAlertRequestResult::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (code_)
{
  case (int32_t)CreateAMLAlertRequestResultCode::SUCCESS:
return u.from_bytes(success_);
  default:
  
  return true;
}
return false;
}
bool
CreateAMLAlertRequestResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)CreateAMLAlertRequestResultCode::SUCCESS:
return m.to_bytes(success_);
  default:
    return true;
}
return false;
}
void
CreateAMLAlertRequestResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)CreateAMLAlertRequestResultCode::SUCCESS:
return m.count_size(success_);
  default:
  
  return;
}
}
bool
CreateAMLAlertRequestResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<CreateAMLAlertRequestResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)CreateAMLAlertRequestResultCode::SUCCESS:
return success_ == other.success_;
  default:
  
  return true;
}
return false;
}
bool
CreateAMLAlertRequestResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreateAMLAlertRequestResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)CreateAMLAlertRequestResultCode::SUCCESS:
return success_ < other.success_;
  default:
    return false;
}
return false;
}
}