#include "operation-update-data.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
UpdateDataOp::from_bytes(xdr::unmarshaler& u) 
{
bool okdataID = u.from_bytes(dataID);
if (!okdataID)
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
UpdateDataOp::to_bytes(xdr::marshaler& m) const 
{
bool okdataID = m.to_bytes(dataID);
if (!okdataID)
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
UpdateDataOp::count_size(xdr::measurer& m) const 
{
m.count_size(dataID);
m.count_size(value);
m.count_size(ext);
}
bool
UpdateDataOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<UpdateDataOp const&>(other_abstract);return true
&& (dataID== other.dataID)
&& (value== other.value)
&& (ext== other.ext)
;}
bool
UpdateDataOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<UpdateDataOp const&>(other_abstract);
if (dataID < other.dataID) return true;
if (other.dataID < dataID) return false;
if (value < other.value) return true;
if (other.value < value) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
UpdateDataResult::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (code_)
{
  case (int32_t)UpdateDataResultCode::SUCCESS:
return u.from_bytes(ext_);
  default:
  
  return true;
}
return false;
}
bool
UpdateDataResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)UpdateDataResultCode::SUCCESS:
return m.to_bytes(ext_);
  default:
    return true;
}
return false;
}
void
UpdateDataResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)UpdateDataResultCode::SUCCESS:
return m.count_size(ext_);
  default:
  
  return;
}
}
bool
UpdateDataResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<UpdateDataResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)UpdateDataResultCode::SUCCESS:
return ext_ == other.ext_;
  default:
  
  return true;
}
return false;
}
bool
UpdateDataResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<UpdateDataResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)UpdateDataResultCode::SUCCESS:
return ext_ < other.ext_;
  default:
    return false;
}
return false;
}
}