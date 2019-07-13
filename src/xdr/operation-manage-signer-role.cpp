#include "operation-manage-signer-role.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
CreateSignerRoleData::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
CreateSignerRoleData::_ext_t::to_bytes(xdr::marshaler& m) const
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
CreateSignerRoleData::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
CreateSignerRoleData::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
CreateSignerRoleData::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
CreateSignerRoleData::from_bytes(xdr::unmarshaler& u) 
{
bool okruleIDs = u.from_bytes(ruleIDs);
if (!okruleIDs)
{
return false;
}
bool okisReadOnly = u.from_bytes(isReadOnly);
if (!okisReadOnly)
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
CreateSignerRoleData::to_bytes(xdr::marshaler& m) const 
{
bool okruleIDs = m.to_bytes(ruleIDs);
if (!okruleIDs)
{
return false;
}
bool okisReadOnly = m.to_bytes(isReadOnly);
if (!okisReadOnly)
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
CreateSignerRoleData::count_size(xdr::measurer& m) const 
{
m.count_size(ruleIDs);
m.count_size(isReadOnly);
m.count_size(details);
m.count_size(ext);
}
bool
CreateSignerRoleData::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CreateSignerRoleData const&>(other_abstract);return true
&& (ruleIDs== other.ruleIDs)
&& (isReadOnly== other.isReadOnly)
&& (details== other.details)
&& (ext== other.ext)
;}
bool
CreateSignerRoleData::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreateSignerRoleData const&>(other_abstract);
if (ruleIDs < other.ruleIDs) return true;
if (other.ruleIDs < ruleIDs) return false;
if (isReadOnly < other.isReadOnly) return true;
if (other.isReadOnly < isReadOnly) return false;
if (details < other.details) return true;
if (other.details < details) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
UpdateSignerRoleData::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
UpdateSignerRoleData::_ext_t::to_bytes(xdr::marshaler& m) const
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
UpdateSignerRoleData::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
UpdateSignerRoleData::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
UpdateSignerRoleData::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
UpdateSignerRoleData::from_bytes(xdr::unmarshaler& u) 
{
bool okroleID = u.from_bytes(roleID);
if (!okroleID)
{
return false;
}
bool okruleIDs = u.from_bytes(ruleIDs);
if (!okruleIDs)
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
UpdateSignerRoleData::to_bytes(xdr::marshaler& m) const 
{
bool okroleID = m.to_bytes(roleID);
if (!okroleID)
{
return false;
}
bool okruleIDs = m.to_bytes(ruleIDs);
if (!okruleIDs)
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
UpdateSignerRoleData::count_size(xdr::measurer& m) const 
{
m.count_size(roleID);
m.count_size(ruleIDs);
m.count_size(details);
m.count_size(ext);
}
bool
UpdateSignerRoleData::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<UpdateSignerRoleData const&>(other_abstract);return true
&& (roleID== other.roleID)
&& (ruleIDs== other.ruleIDs)
&& (details== other.details)
&& (ext== other.ext)
;}
bool
UpdateSignerRoleData::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<UpdateSignerRoleData const&>(other_abstract);
if (roleID < other.roleID) return true;
if (other.roleID < roleID) return false;
if (ruleIDs < other.ruleIDs) return true;
if (other.ruleIDs < ruleIDs) return false;
if (details < other.details) return true;
if (other.details < details) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
RemoveSignerRoleData::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
RemoveSignerRoleData::_ext_t::to_bytes(xdr::marshaler& m) const
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
RemoveSignerRoleData::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
RemoveSignerRoleData::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
RemoveSignerRoleData::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
RemoveSignerRoleData::from_bytes(xdr::unmarshaler& u) 
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
RemoveSignerRoleData::to_bytes(xdr::marshaler& m) const 
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
RemoveSignerRoleData::count_size(xdr::measurer& m) const 
{
m.count_size(roleID);
m.count_size(ext);
}
bool
RemoveSignerRoleData::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<RemoveSignerRoleData const&>(other_abstract);return true
&& (roleID== other.roleID)
&& (ext== other.ext)
;}
bool
RemoveSignerRoleData::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<RemoveSignerRoleData const&>(other_abstract);
if (roleID < other.roleID) return true;
if (other.roleID < roleID) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageSignerRoleOp::_data_t::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (action_)
{
    case (int32_t)ManageSignerRoleAction::CREATE:
return u.from_bytes(createData_);
    case (int32_t)ManageSignerRoleAction::UPDATE:
return u.from_bytes(updateData_);
    case (int32_t)ManageSignerRoleAction::REMOVE:
return u.from_bytes(removeData_);
}
return false;
}
bool
ManageSignerRoleOp::_data_t::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(action_);
if (!ok)
{
return false;
}
switch (action_)
{

    case (int32_t)ManageSignerRoleAction::CREATE:
return m.to_bytes(createData_);
    case (int32_t)ManageSignerRoleAction::UPDATE:
return m.to_bytes(updateData_);
    case (int32_t)ManageSignerRoleAction::REMOVE:
return m.to_bytes(removeData_);
}
return false;
}
void
ManageSignerRoleOp::_data_t::count_size(xdr::measurer& m) const
{
m.count_size(action_);
switch (action_)
{

    case (int32_t)ManageSignerRoleAction::CREATE:
return m.count_size(createData_);
    case (int32_t)ManageSignerRoleAction::UPDATE:
return m.count_size(updateData_);
    case (int32_t)ManageSignerRoleAction::REMOVE:
return m.count_size(removeData_);
}
}
bool
ManageSignerRoleOp::_data_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_data_t const&>(other_abstract);
if (other.action_ != action_) return false;
switch (action_)
{
    case (int32_t)ManageSignerRoleAction::CREATE:
return createData_ == other.createData_;
    case (int32_t)ManageSignerRoleAction::UPDATE:
return updateData_ == other.updateData_;
    case (int32_t)ManageSignerRoleAction::REMOVE:
return removeData_ == other.removeData_;
}
return false;
}
bool
ManageSignerRoleOp::_data_t::operator<(xdr_abstract const& other_abstract) const
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
    case (int32_t)ManageSignerRoleAction::CREATE:
return createData_ < other.createData_;
    case (int32_t)ManageSignerRoleAction::UPDATE:
return updateData_ < other.updateData_;
    case (int32_t)ManageSignerRoleAction::REMOVE:
return removeData_ < other.removeData_;
}
return false;
}
bool
ManageSignerRoleOp::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ManageSignerRoleOp::_ext_t::to_bytes(xdr::marshaler& m) const
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
ManageSignerRoleOp::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
ManageSignerRoleOp::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ManageSignerRoleOp::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ManageSignerRoleOp::from_bytes(xdr::unmarshaler& u) 
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
ManageSignerRoleOp::to_bytes(xdr::marshaler& m) const 
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
ManageSignerRoleOp::count_size(xdr::measurer& m) const 
{
m.count_size(data);
m.count_size(ext);
}
bool
ManageSignerRoleOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<ManageSignerRoleOp const&>(other_abstract);return true
&& (data== other.data)
&& (ext== other.ext)
;}
bool
ManageSignerRoleOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManageSignerRoleOp const&>(other_abstract);
if (data < other.data) return true;
if (other.data < data) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageSignerRoleResult::_success_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ManageSignerRoleResult::_success_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
ManageSignerRoleResult::_success_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
ManageSignerRoleResult::_success_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ManageSignerRoleResult::_success_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ManageSignerRoleResult::_success_t::from_bytes(xdr::unmarshaler& u) 
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
ManageSignerRoleResult::_success_t::to_bytes(xdr::marshaler& m) const 
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
ManageSignerRoleResult::_success_t::count_size(xdr::measurer& m) const 
{
m.count_size(roleID);
m.count_size(ext);
}
bool
ManageSignerRoleResult::_success_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_success_t const&>(other_abstract);return true
&& (roleID== other.roleID)
&& (ext== other.ext)
;}
bool
ManageSignerRoleResult::_success_t::operator<(xdr_abstract const& other_abstract) const
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
ManageSignerRoleResult::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (code_)
{
  case (int32_t)ManageSignerRoleResultCode::SUCCESS:
return u.from_bytes(success_);
  case (int32_t)ManageSignerRoleResultCode::RULE_ID_DUPLICATION:
  case (int32_t)ManageSignerRoleResultCode::DEFAULT_RULE_ID_DUPLICATION:
  case (int32_t)ManageSignerRoleResultCode::NO_SUCH_RULE:
return u.from_bytes(ruleID_);
  case (int32_t)ManageSignerRoleResultCode::TOO_MANY_RULE_IDS:
return u.from_bytes(maxRuleIDsCount_);
  default:
  
  return true;
}
return false;
}
bool
ManageSignerRoleResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)ManageSignerRoleResultCode::SUCCESS:
return m.to_bytes(success_);
  case (int32_t)ManageSignerRoleResultCode::RULE_ID_DUPLICATION:
  case (int32_t)ManageSignerRoleResultCode::DEFAULT_RULE_ID_DUPLICATION:
  case (int32_t)ManageSignerRoleResultCode::NO_SUCH_RULE:
return m.to_bytes(ruleID_);
  case (int32_t)ManageSignerRoleResultCode::TOO_MANY_RULE_IDS:
return m.to_bytes(maxRuleIDsCount_);
  default:
    return true;
}
return false;
}
void
ManageSignerRoleResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)ManageSignerRoleResultCode::SUCCESS:
return m.count_size(success_);
  case (int32_t)ManageSignerRoleResultCode::RULE_ID_DUPLICATION:
  case (int32_t)ManageSignerRoleResultCode::DEFAULT_RULE_ID_DUPLICATION:
  case (int32_t)ManageSignerRoleResultCode::NO_SUCH_RULE:
return m.count_size(ruleID_);
  case (int32_t)ManageSignerRoleResultCode::TOO_MANY_RULE_IDS:
return m.count_size(maxRuleIDsCount_);
  default:
  
  return;
}
}
bool
ManageSignerRoleResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<ManageSignerRoleResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)ManageSignerRoleResultCode::SUCCESS:
return success_ == other.success_;
  case (int32_t)ManageSignerRoleResultCode::RULE_ID_DUPLICATION:
  case (int32_t)ManageSignerRoleResultCode::DEFAULT_RULE_ID_DUPLICATION:
  case (int32_t)ManageSignerRoleResultCode::NO_SUCH_RULE:
return ruleID_ == other.ruleID_;
  case (int32_t)ManageSignerRoleResultCode::TOO_MANY_RULE_IDS:
return maxRuleIDsCount_ == other.maxRuleIDsCount_;
  default:
  
  return true;
}
return false;
}
bool
ManageSignerRoleResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManageSignerRoleResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)ManageSignerRoleResultCode::SUCCESS:
return success_ < other.success_;
  case (int32_t)ManageSignerRoleResultCode::RULE_ID_DUPLICATION:
  case (int32_t)ManageSignerRoleResultCode::DEFAULT_RULE_ID_DUPLICATION:
  case (int32_t)ManageSignerRoleResultCode::NO_SUCH_RULE:
return ruleID_ < other.ruleID_;
  case (int32_t)ManageSignerRoleResultCode::TOO_MANY_RULE_IDS:
return maxRuleIDsCount_ < other.maxRuleIDsCount_;
  default:
    return false;
}
return false;
}
}