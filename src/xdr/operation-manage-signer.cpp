#include "operation-manage-signer.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
UpdateSignerData::from_bytes(xdr::unmarshaler& u) 
{
bool okpublicKey = u.from_bytes(publicKey);
if (!okpublicKey)
{
return false;
}
bool okroleID = u.from_bytes(roleID);
if (!okroleID)
{
return false;
}
bool okweight = u.from_bytes(weight);
if (!okweight)
{
return false;
}
bool okidentity = u.from_bytes(identity);
if (!okidentity)
{
return false;
}
bool okdetails = u.from_bytes(details);
if (!okdetails)
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
UpdateSignerData::to_bytes(xdr::marshaler& m) const 
{
bool okpublicKey = m.to_bytes(publicKey);
if (!okpublicKey)
{
return false;
}
bool okroleID = m.to_bytes(roleID);
if (!okroleID)
{
return false;
}
bool okweight = m.to_bytes(weight);
if (!okweight)
{
return false;
}
bool okidentity = m.to_bytes(identity);
if (!okidentity)
{
return false;
}
bool okdetails = m.to_bytes(details);
if (!okdetails)
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
UpdateSignerData::count_size(xdr::measurer& m) const 
{
m.count_size(publicKey);
m.count_size(roleID);
m.count_size(weight);
m.count_size(identity);
m.count_size(details);
m.count_size(ext);
}
bool
UpdateSignerData::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<UpdateSignerData const&>(other_abstract);return true
&& (publicKey== other.publicKey)
&& (roleID== other.roleID)
&& (weight== other.weight)
&& (identity== other.identity)
&& (details== other.details)
&& (ext== other.ext)
;}
bool
UpdateSignerData::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<UpdateSignerData const&>(other_abstract);
if (publicKey < other.publicKey) return true;
if (other.publicKey < publicKey) return false;
if (roleID < other.roleID) return true;
if (other.roleID < roleID) return false;
if (weight < other.weight) return true;
if (other.weight < weight) return false;
if (identity < other.identity) return true;
if (other.identity < identity) return false;
if (details < other.details) return true;
if (other.details < details) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
RemoveSignerData::from_bytes(xdr::unmarshaler& u) 
{
bool okpublicKey = u.from_bytes(publicKey);
if (!okpublicKey)
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
RemoveSignerData::to_bytes(xdr::marshaler& m) const 
{
bool okpublicKey = m.to_bytes(publicKey);
if (!okpublicKey)
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
RemoveSignerData::count_size(xdr::measurer& m) const 
{
m.count_size(publicKey);
m.count_size(ext);
}
bool
RemoveSignerData::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<RemoveSignerData const&>(other_abstract);return true
&& (publicKey== other.publicKey)
&& (ext== other.ext)
;}
bool
RemoveSignerData::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<RemoveSignerData const&>(other_abstract);
if (publicKey < other.publicKey) return true;
if (other.publicKey < publicKey) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageSignerOp::_data_t::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (action_)
{
    case (int32_t)ManageSignerAction::CREATE:
return u.from_bytes(createData_);
    case (int32_t)ManageSignerAction::UPDATE:
return u.from_bytes(updateData_);
    case (int32_t)ManageSignerAction::REMOVE:
return u.from_bytes(removeData_);
}
return false;
}
bool
ManageSignerOp::_data_t::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(action_);
if (!ok)
{
return false;
}
switch (action_)
{

    case (int32_t)ManageSignerAction::CREATE:
return m.to_bytes(createData_);
    case (int32_t)ManageSignerAction::UPDATE:
return m.to_bytes(updateData_);
    case (int32_t)ManageSignerAction::REMOVE:
return m.to_bytes(removeData_);
}
return false;
}
void
ManageSignerOp::_data_t::count_size(xdr::measurer& m) const
{
m.count_size(action_);
switch (action_)
{

    case (int32_t)ManageSignerAction::CREATE:
return m.count_size(createData_);
    case (int32_t)ManageSignerAction::UPDATE:
return m.count_size(updateData_);
    case (int32_t)ManageSignerAction::REMOVE:
return m.count_size(removeData_);
}
}
bool
ManageSignerOp::_data_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_data_t const&>(other_abstract);
if (other.action_ != action_) return false;
switch (action_)
{
    case (int32_t)ManageSignerAction::CREATE:
return createData_ == other.createData_;
    case (int32_t)ManageSignerAction::UPDATE:
return updateData_ == other.updateData_;
    case (int32_t)ManageSignerAction::REMOVE:
return removeData_ == other.removeData_;
}
return false;
}
bool
ManageSignerOp::_data_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_data_t const&>(other_abstract);
if (action_ < other.action_) return true;
if (other.action_ < action_) return false;
switch (action_)
{
    case (int32_t)ManageSignerAction::CREATE:
return createData_ < other.createData_;
    case (int32_t)ManageSignerAction::UPDATE:
return updateData_ < other.updateData_;
    case (int32_t)ManageSignerAction::REMOVE:
return removeData_ < other.removeData_;
}
return false;
}
bool
ManageSignerOp::from_bytes(xdr::unmarshaler& u) 
{
bool okdata = u.from_bytes(data);
if (!okdata)
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
ManageSignerOp::to_bytes(xdr::marshaler& m) const 
{
bool okdata = m.to_bytes(data);
if (!okdata)
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
ManageSignerOp::count_size(xdr::measurer& m) const 
{
m.count_size(data);
m.count_size(ext);
}
bool
ManageSignerOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<ManageSignerOp const&>(other_abstract);return true
&& (data== other.data)
&& (ext== other.ext)
;}
bool
ManageSignerOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManageSignerOp const&>(other_abstract);
if (data < other.data) return true;
if (other.data < data) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageSignerResult::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (code_)
{
  case (int32_t)ManageSignerResultCode::SUCCESS:
return u.from_bytes(ext_);
  default:
  
  return true;
}
return false;
}
bool
ManageSignerResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)ManageSignerResultCode::SUCCESS:
return m.to_bytes(ext_);
  default:
    return true;
}
return false;
}
void
ManageSignerResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)ManageSignerResultCode::SUCCESS:
return m.count_size(ext_);
  default:
  
  return;
}
}
bool
ManageSignerResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<ManageSignerResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)ManageSignerResultCode::SUCCESS:
return ext_ == other.ext_;
  default:
  
  return true;
}
return false;
}
bool
ManageSignerResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManageSignerResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)ManageSignerResultCode::SUCCESS:
return ext_ < other.ext_;
  default:
    return false;
}
return false;
}
}