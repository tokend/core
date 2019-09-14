#include "operation-close-swap.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
CloseSwapOp::from_bytes(xdr::unmarshaler& u) 
{
bool okswapID = u.from_bytes(swapID);
if (!okswapID)
{
return false;
}
bool oksecret = u.from_bytes(secret);
if (!oksecret)
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
CloseSwapOp::to_bytes(xdr::marshaler& m) const 
{
bool okswapID = m.to_bytes(swapID);
if (!okswapID)
{
return false;
}
bool oksecret = m.to_bytes(secret);
if (!oksecret)
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
CloseSwapOp::count_size(xdr::measurer& m) const 
{
m.count_size(swapID);
m.count_size(secret);
m.count_size(ext);
}
bool
CloseSwapOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CloseSwapOp const&>(other_abstract);return true
&& (swapID== other.swapID)
&& (secret== other.secret)
&& (ext== other.ext)
;}
bool
CloseSwapOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CloseSwapOp const&>(other_abstract);
if (swapID < other.swapID) return true;
if (other.swapID < swapID) return false;
if (secret < other.secret) return true;
if (other.secret < secret) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
CloseSwapSuccess::from_bytes(xdr::unmarshaler& u) 
{
bool okext = u.from_bytes(ext);
if (!okext)
{
return false;
}
return true;
}
bool
CloseSwapSuccess::to_bytes(xdr::marshaler& m) const 
{
bool okext = m.to_bytes(ext);
if (!okext)
{
return false;
}
return true;
}
void
CloseSwapSuccess::count_size(xdr::measurer& m) const 
{
m.count_size(ext);
}
bool
CloseSwapSuccess::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CloseSwapSuccess const&>(other_abstract);return true
&& (ext== other.ext)
;}
bool
CloseSwapSuccess::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CloseSwapSuccess const&>(other_abstract);
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
CloseSwapResult::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (code_)
{
  case (int32_t)CloseSwapResultCode::SUCCESS:
return u.from_bytes(success_);
  default:
  
  return true;
}
return false;
}
bool
CloseSwapResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)CloseSwapResultCode::SUCCESS:
return m.to_bytes(success_);
  default:
    return true;
}
return false;
}
void
CloseSwapResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)CloseSwapResultCode::SUCCESS:
return m.count_size(success_);
  default:
  
  return;
}
}
bool
CloseSwapResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<CloseSwapResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)CloseSwapResultCode::SUCCESS:
return success_ == other.success_;
  default:
  
  return true;
}
return false;
}
bool
CloseSwapResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CloseSwapResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)CloseSwapResultCode::SUCCESS:
return success_ < other.success_;
  default:
    return false;
}
return false;
}
}