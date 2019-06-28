#include "operation-create-account.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
CreateAccountOp::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
CreateAccountOp::_ext_t::to_bytes(xdr::marshaler& m) const
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
CreateAccountOp::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
CreateAccountOp::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
CreateAccountOp::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
CreateAccountOp::from_bytes(xdr::unmarshaler& u) 
{
bool okdestination = u.from_bytes(destination);
if (!okdestination)
{
return false;
}
bool okreferrer = u.from_bytes(referrer);
if (!okreferrer)
{
return false;
}
bool okroleID = u.from_bytes(roleID);
if (!okroleID)
{
return false;
}
bool oksignersData = u.from_bytes(signersData);
if (!oksignersData)
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
CreateAccountOp::to_bytes(xdr::marshaler& m) const 
{
bool okdestination = m.to_bytes(destination);
if (!okdestination)
{
return false;
}
bool okreferrer = m.to_bytes(referrer);
if (!okreferrer)
{
return false;
}
bool okroleID = m.to_bytes(roleID);
if (!okroleID)
{
return false;
}
bool oksignersData = m.to_bytes(signersData);
if (!oksignersData)
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
CreateAccountOp::count_size(xdr::measurer& m) const 
{
m.count_size(destination);
m.count_size(referrer);
m.count_size(roleID);
m.count_size(signersData);
m.count_size(ext);
}
bool
CreateAccountOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CreateAccountOp const&>(other_abstract);return true
&& (destination== other.destination)
&& (referrer== other.referrer)
&& (roleID== other.roleID)
&& (signersData== other.signersData)
&& (ext== other.ext)
;}
bool
CreateAccountOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreateAccountOp const&>(other_abstract);
if (destination < other.destination) return true;
if (other.destination < destination) return false;
if (referrer < other.referrer) return true;
if (other.referrer < referrer) return false;
if (roleID < other.roleID) return true;
if (other.roleID < roleID) return false;
if (signersData < other.signersData) return true;
if (other.signersData < signersData) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
CreateAccountSuccess::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
CreateAccountSuccess::_ext_t::to_bytes(xdr::marshaler& m) const
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
CreateAccountSuccess::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
CreateAccountSuccess::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
CreateAccountSuccess::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
CreateAccountSuccess::from_bytes(xdr::unmarshaler& u) 
{
bool oksequentialID = u.from_bytes(sequentialID);
if (!oksequentialID)
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
CreateAccountSuccess::to_bytes(xdr::marshaler& m) const 
{
bool oksequentialID = m.to_bytes(sequentialID);
if (!oksequentialID)
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
CreateAccountSuccess::count_size(xdr::measurer& m) const 
{
m.count_size(sequentialID);
m.count_size(ext);
}
bool
CreateAccountSuccess::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CreateAccountSuccess const&>(other_abstract);return true
&& (sequentialID== other.sequentialID)
&& (ext== other.ext)
;}
bool
CreateAccountSuccess::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreateAccountSuccess const&>(other_abstract);
if (sequentialID < other.sequentialID) return true;
if (other.sequentialID < sequentialID) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
CreateAccountResult::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (code_)
{
  case (int32_t)CreateAccountResultCode::SUCCESS:
return u.from_bytes(success_);
  case (int32_t)CreateAccountResultCode::INVALID_SIGNER_DATA:
return u.from_bytes(createSignerErrorCode_);
  default:
  
  return true;
}
return false;
}
bool
CreateAccountResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)CreateAccountResultCode::SUCCESS:
return m.to_bytes(success_);
  case (int32_t)CreateAccountResultCode::INVALID_SIGNER_DATA:
return m.to_bytes(createSignerErrorCode_);
  default:
    return true;
}
return false;
}
void
CreateAccountResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)CreateAccountResultCode::SUCCESS:
return m.count_size(success_);
  case (int32_t)CreateAccountResultCode::INVALID_SIGNER_DATA:
return m.count_size(createSignerErrorCode_);
  default:
  
  return;
}
}
bool
CreateAccountResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<CreateAccountResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)CreateAccountResultCode::SUCCESS:
return success_ == other.success_;
  case (int32_t)CreateAccountResultCode::INVALID_SIGNER_DATA:
return createSignerErrorCode_ == other.createSignerErrorCode_;
  default:
  
  return true;
}
return false;
}
bool
CreateAccountResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreateAccountResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)CreateAccountResultCode::SUCCESS:
return success_ < other.success_;
  case (int32_t)CreateAccountResultCode::INVALID_SIGNER_DATA:
return createSignerErrorCode_ < other.createSignerErrorCode_;
  default:
    return false;
}
return false;
}
}