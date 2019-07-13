#include "operation-manage-account-role.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
CreateAccountRoleData::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
CreateAccountRoleData::_ext_t::to_bytes(xdr::marshaler& m) const
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
CreateAccountRoleData::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
CreateAccountRoleData::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
CreateAccountRoleData::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
CreateAccountRoleData::from_bytes(xdr::unmarshaler& u) 
{
bool okdetails = u.from_bytes(details);
if (!okdetails)
{
return false;
}
bool okruleIDs = u.from_bytes(ruleIDs);
if (!okruleIDs)
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
CreateAccountRoleData::to_bytes(xdr::marshaler& m) const 
{
bool okdetails = m.to_bytes(details);
if (!okdetails)
{
return false;
}
bool okruleIDs = m.to_bytes(ruleIDs);
if (!okruleIDs)
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
CreateAccountRoleData::count_size(xdr::measurer& m) const 
{
m.count_size(details);
m.count_size(ruleIDs);
m.count_size(ext);
}
bool
CreateAccountRoleData::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CreateAccountRoleData const&>(other_abstract);return true
&& (details== other.details)
&& (ruleIDs== other.ruleIDs)
&& (ext== other.ext)
;}
bool
CreateAccountRoleData::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreateAccountRoleData const&>(other_abstract);
if (details < other.details) return true;
if (other.details < details) return false;
if (ruleIDs < other.ruleIDs) return true;
if (other.ruleIDs < ruleIDs) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
UpdateAccountRoleData::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
UpdateAccountRoleData::_ext_t::to_bytes(xdr::marshaler& m) const
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
UpdateAccountRoleData::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
UpdateAccountRoleData::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
UpdateAccountRoleData::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
UpdateAccountRoleData::from_bytes(xdr::unmarshaler& u) 
{
bool okroleID = u.from_bytes(roleID);
if (!okroleID)
{
return false;
}
bool okdetails = u.from_bytes(details);
if (!okdetails)
{
return false;
}
bool okruleIDs = u.from_bytes(ruleIDs);
if (!okruleIDs)
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
UpdateAccountRoleData::to_bytes(xdr::marshaler& m) const 
{
bool okroleID = m.to_bytes(roleID);
if (!okroleID)
{
return false;
}
bool okdetails = m.to_bytes(details);
if (!okdetails)
{
return false;
}
bool okruleIDs = m.to_bytes(ruleIDs);
if (!okruleIDs)
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
UpdateAccountRoleData::count_size(xdr::measurer& m) const 
{
m.count_size(roleID);
m.count_size(details);
m.count_size(ruleIDs);
m.count_size(ext);
}
bool
UpdateAccountRoleData::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<UpdateAccountRoleData const&>(other_abstract);return true
&& (roleID== other.roleID)
&& (details== other.details)
&& (ruleIDs== other.ruleIDs)
&& (ext== other.ext)
;}
bool
UpdateAccountRoleData::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<UpdateAccountRoleData const&>(other_abstract);
if (roleID < other.roleID) return true;
if (other.roleID < roleID) return false;
if (details < other.details) return true;
if (other.details < details) return false;
if (ruleIDs < other.ruleIDs) return true;
if (other.ruleIDs < ruleIDs) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
RemoveAccountRoleData::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
RemoveAccountRoleData::_ext_t::to_bytes(xdr::marshaler& m) const
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
RemoveAccountRoleData::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
RemoveAccountRoleData::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
RemoveAccountRoleData::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
RemoveAccountRoleData::from_bytes(xdr::unmarshaler& u) 
{
bool okroleID = u.from_bytes(roleID);
if (!okroleID)
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
RemoveAccountRoleData::to_bytes(xdr::marshaler& m) const 
{
bool okroleID = m.to_bytes(roleID);
if (!okroleID)
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
RemoveAccountRoleData::count_size(xdr::measurer& m) const 
{
m.count_size(roleID);
m.count_size(ext);
}
bool
RemoveAccountRoleData::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<RemoveAccountRoleData const&>(other_abstract);return true
&& (roleID== other.roleID)
&& (ext== other.ext)
;}
bool
RemoveAccountRoleData::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<RemoveAccountRoleData const&>(other_abstract);
if (roleID < other.roleID) return true;
if (other.roleID < roleID) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageAccountRoleOp::_data_t::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (action_)
{
    case (int32_t)ManageAccountRoleAction::CREATE:
return u.from_bytes(createData_);
    case (int32_t)ManageAccountRoleAction::UPDATE:
return u.from_bytes(updateData_);
    case (int32_t)ManageAccountRoleAction::REMOVE:
return u.from_bytes(removeData_);
}
return false;
}
bool
ManageAccountRoleOp::_data_t::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(action_);
if (!ok)
{
return false;
}
switch (action_)
{

    case (int32_t)ManageAccountRoleAction::CREATE:
return m.to_bytes(createData_);
    case (int32_t)ManageAccountRoleAction::UPDATE:
return m.to_bytes(updateData_);
    case (int32_t)ManageAccountRoleAction::REMOVE:
return m.to_bytes(removeData_);
}
return false;
}
void
ManageAccountRoleOp::_data_t::count_size(xdr::measurer& m) const
{
m.count_size(action_);
switch (action_)
{

    case (int32_t)ManageAccountRoleAction::CREATE:
return m.count_size(createData_);
    case (int32_t)ManageAccountRoleAction::UPDATE:
return m.count_size(updateData_);
    case (int32_t)ManageAccountRoleAction::REMOVE:
return m.count_size(removeData_);
}
}
bool
ManageAccountRoleOp::_data_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_data_t const&>(other_abstract);
if (other.action_ != action_) return false;
switch (action_)
{
    case (int32_t)ManageAccountRoleAction::CREATE:
return createData_ == other.createData_;
    case (int32_t)ManageAccountRoleAction::UPDATE:
return updateData_ == other.updateData_;
    case (int32_t)ManageAccountRoleAction::REMOVE:
return removeData_ == other.removeData_;
}
return false;
}
bool
ManageAccountRoleOp::_data_t::operator<(xdr_abstract const& other_abstract) const
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
    case (int32_t)ManageAccountRoleAction::CREATE:
return createData_ < other.createData_;
    case (int32_t)ManageAccountRoleAction::UPDATE:
return updateData_ < other.updateData_;
    case (int32_t)ManageAccountRoleAction::REMOVE:
return removeData_ < other.removeData_;
}
return false;
}
bool
ManageAccountRoleOp::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ManageAccountRoleOp::_ext_t::to_bytes(xdr::marshaler& m) const
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
ManageAccountRoleOp::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
ManageAccountRoleOp::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ManageAccountRoleOp::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ManageAccountRoleOp::from_bytes(xdr::unmarshaler& u) 
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
ManageAccountRoleOp::to_bytes(xdr::marshaler& m) const 
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
ManageAccountRoleOp::count_size(xdr::measurer& m) const 
{
m.count_size(data);
m.count_size(ext);
}
bool
ManageAccountRoleOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<ManageAccountRoleOp const&>(other_abstract);return true
&& (data== other.data)
&& (ext== other.ext)
;}
bool
ManageAccountRoleOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManageAccountRoleOp const&>(other_abstract);
if (data < other.data) return true;
if (other.data < data) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageAccountRoleResult::_success_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ManageAccountRoleResult::_success_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
ManageAccountRoleResult::_success_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
ManageAccountRoleResult::_success_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ManageAccountRoleResult::_success_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ManageAccountRoleResult::_success_t::from_bytes(xdr::unmarshaler& u) 
{
bool okroleID = u.from_bytes(roleID);
if (!okroleID)
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
ManageAccountRoleResult::_success_t::to_bytes(xdr::marshaler& m) const 
{
bool okroleID = m.to_bytes(roleID);
if (!okroleID)
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
ManageAccountRoleResult::_success_t::count_size(xdr::measurer& m) const 
{
m.count_size(roleID);
m.count_size(ext);
}
bool
ManageAccountRoleResult::_success_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_success_t const&>(other_abstract);return true
&& (roleID== other.roleID)
&& (ext== other.ext)
;}
bool
ManageAccountRoleResult::_success_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_success_t const&>(other_abstract);
if (roleID < other.roleID) return true;
if (other.roleID < roleID) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageAccountRoleResult::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (code_)
{
  case (int32_t)ManageAccountRoleResultCode::SUCCESS:
return u.from_bytes(success_);
  case (int32_t)ManageAccountRoleResultCode::RULE_ID_DUPLICATION:
  case (int32_t)ManageAccountRoleResultCode::NO_SUCH_RULE:
return u.from_bytes(ruleID_);
  default:
  
  return true;
}
return false;
}
bool
ManageAccountRoleResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)ManageAccountRoleResultCode::SUCCESS:
return m.to_bytes(success_);
  case (int32_t)ManageAccountRoleResultCode::RULE_ID_DUPLICATION:
  case (int32_t)ManageAccountRoleResultCode::NO_SUCH_RULE:
return m.to_bytes(ruleID_);
  default:
    return true;
}
return false;
}
void
ManageAccountRoleResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)ManageAccountRoleResultCode::SUCCESS:
return m.count_size(success_);
  case (int32_t)ManageAccountRoleResultCode::RULE_ID_DUPLICATION:
  case (int32_t)ManageAccountRoleResultCode::NO_SUCH_RULE:
return m.count_size(ruleID_);
  default:
  
  return;
}
}
bool
ManageAccountRoleResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<ManageAccountRoleResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)ManageAccountRoleResultCode::SUCCESS:
return success_ == other.success_;
  case (int32_t)ManageAccountRoleResultCode::RULE_ID_DUPLICATION:
  case (int32_t)ManageAccountRoleResultCode::NO_SUCH_RULE:
return ruleID_ == other.ruleID_;
  default:
  
  return true;
}
return false;
}
bool
ManageAccountRoleResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManageAccountRoleResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)ManageAccountRoleResultCode::SUCCESS:
return success_ < other.success_;
  case (int32_t)ManageAccountRoleResultCode::RULE_ID_DUPLICATION:
  case (int32_t)ManageAccountRoleResultCode::NO_SUCH_RULE:
return ruleID_ < other.ruleID_;
  default:
    return false;
}
return false;
}
}