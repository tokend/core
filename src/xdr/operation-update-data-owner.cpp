#include "operation-update-data-owner.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
UpdateDataOwnerOp::from_bytes(xdr::unmarshaler& u) 
{
bool okdataID = u.from_bytes(dataID);
if (!okdataID)
{
return false;
}
bool oknewOwner = u.from_bytes(newOwner);
if (!oknewOwner)
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
UpdateDataOwnerOp::to_bytes(xdr::marshaler& m) const 
{
bool okdataID = m.to_bytes(dataID);
if (!okdataID)
{
return false;
}
bool oknewOwner = m.to_bytes(newOwner);
if (!oknewOwner)
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
UpdateDataOwnerOp::count_size(xdr::measurer& m) const 
{
m.count_size(dataID);
m.count_size(newOwner);
m.count_size(ext);
}
bool
UpdateDataOwnerOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<UpdateDataOwnerOp const&>(other_abstract);return true
&& (dataID== other.dataID)
&& (newOwner== other.newOwner)
&& (ext== other.ext)
;}
bool
UpdateDataOwnerOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<UpdateDataOwnerOp const&>(other_abstract);
if (dataID < other.dataID) return true;
if (other.dataID < dataID) return false;
if (newOwner < other.newOwner) return true;
if (other.newOwner < newOwner) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
UpdateDataOwnerSuccess::from_bytes(xdr::unmarshaler& u) 
{
bool okowner = u.from_bytes(owner);
if (!okowner)
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
UpdateDataOwnerSuccess::to_bytes(xdr::marshaler& m) const 
{
bool okowner = m.to_bytes(owner);
if (!okowner)
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
UpdateDataOwnerSuccess::count_size(xdr::measurer& m) const 
{
m.count_size(owner);
m.count_size(ext);
}
bool
UpdateDataOwnerSuccess::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<UpdateDataOwnerSuccess const&>(other_abstract);return true
&& (owner== other.owner)
&& (ext== other.ext)
;}
bool
UpdateDataOwnerSuccess::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<UpdateDataOwnerSuccess const&>(other_abstract);
if (owner < other.owner) return true;
if (other.owner < owner) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
UpdateDataOwnerResult::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (code_)
{
  case (int32_t)UpdateDataOwnerResultCode::SUCCESS:
return u.from_bytes(success_);
  default:
  
  return true;
}
return false;
}
bool
UpdateDataOwnerResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)UpdateDataOwnerResultCode::SUCCESS:
return m.to_bytes(success_);
  default:
    return true;
}
return false;
}
void
UpdateDataOwnerResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)UpdateDataOwnerResultCode::SUCCESS:
return m.count_size(success_);
  default:
  
  return;
}
}
bool
UpdateDataOwnerResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<UpdateDataOwnerResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)UpdateDataOwnerResultCode::SUCCESS:
return success_ == other.success_;
  default:
  
  return true;
}
return false;
}
bool
UpdateDataOwnerResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<UpdateDataOwnerResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)UpdateDataOwnerResultCode::SUCCESS:
return success_ < other.success_;
  default:
    return false;
}
return false;
}
}