#include "operation-manage-signer-rule.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
CreateSignerRuleData::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
CreateSignerRuleData::_ext_t::to_bytes(xdr::marshaler& m) const
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
CreateSignerRuleData::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
CreateSignerRuleData::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
CreateSignerRuleData::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
CreateSignerRuleData::from_bytes(xdr::unmarshaler& u) 
{
bool okresource = u.from_bytes(resource);
if (!okresource)
{
return false;
}
bool okaction = u.from_bytes(action);
if (!okaction)
{
return false;
}
bool okforbids = u.from_bytes(forbids);
if (!okforbids)
{
return false;
}
bool okisDefault = u.from_bytes(isDefault);
if (!okisDefault)
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
CreateSignerRuleData::to_bytes(xdr::marshaler& m) const 
{
bool okresource = m.to_bytes(resource);
if (!okresource)
{
return false;
}
bool okaction = m.to_bytes(action);
if (!okaction)
{
return false;
}
bool okforbids = m.to_bytes(forbids);
if (!okforbids)
{
return false;
}
bool okisDefault = m.to_bytes(isDefault);
if (!okisDefault)
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
CreateSignerRuleData::count_size(xdr::measurer& m) const 
{
m.count_size(resource);
m.count_size(action);
m.count_size(forbids);
m.count_size(isDefault);
m.count_size(isReadOnly);
m.count_size(details);
m.count_size(ext);
}
bool
CreateSignerRuleData::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CreateSignerRuleData const&>(other_abstract);return true
&& (resource== other.resource)
&& (action== other.action)
&& (forbids== other.forbids)
&& (isDefault== other.isDefault)
&& (isReadOnly== other.isReadOnly)
&& (details== other.details)
&& (ext== other.ext)
;}
bool
CreateSignerRuleData::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreateSignerRuleData const&>(other_abstract);
if (resource < other.resource) return true;
if (other.resource < resource) return false;
if (action < other.action) return true;
if (other.action < action) return false;
if (forbids < other.forbids) return true;
if (other.forbids < forbids) return false;
if (isDefault < other.isDefault) return true;
if (other.isDefault < isDefault) return false;
if (isReadOnly < other.isReadOnly) return true;
if (other.isReadOnly < isReadOnly) return false;
if (details < other.details) return true;
if (other.details < details) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
UpdateSignerRuleData::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
UpdateSignerRuleData::_ext_t::to_bytes(xdr::marshaler& m) const
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
UpdateSignerRuleData::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
UpdateSignerRuleData::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
UpdateSignerRuleData::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
UpdateSignerRuleData::from_bytes(xdr::unmarshaler& u) 
{
bool okruleID = u.from_bytes(ruleID);
if (!okruleID)
{
return false;
}
bool okresource = u.from_bytes(resource);
if (!okresource)
{
return false;
}
bool okaction = u.from_bytes(action);
if (!okaction)
{
return false;
}
bool okforbids = u.from_bytes(forbids);
if (!okforbids)
{
return false;
}
bool okisDefault = u.from_bytes(isDefault);
if (!okisDefault)
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
UpdateSignerRuleData::to_bytes(xdr::marshaler& m) const 
{
bool okruleID = m.to_bytes(ruleID);
if (!okruleID)
{
return false;
}
bool okresource = m.to_bytes(resource);
if (!okresource)
{
return false;
}
bool okaction = m.to_bytes(action);
if (!okaction)
{
return false;
}
bool okforbids = m.to_bytes(forbids);
if (!okforbids)
{
return false;
}
bool okisDefault = m.to_bytes(isDefault);
if (!okisDefault)
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
UpdateSignerRuleData::count_size(xdr::measurer& m) const 
{
m.count_size(ruleID);
m.count_size(resource);
m.count_size(action);
m.count_size(forbids);
m.count_size(isDefault);
m.count_size(details);
m.count_size(ext);
}
bool
UpdateSignerRuleData::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<UpdateSignerRuleData const&>(other_abstract);return true
&& (ruleID== other.ruleID)
&& (resource== other.resource)
&& (action== other.action)
&& (forbids== other.forbids)
&& (isDefault== other.isDefault)
&& (details== other.details)
&& (ext== other.ext)
;}
bool
UpdateSignerRuleData::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<UpdateSignerRuleData const&>(other_abstract);
if (ruleID < other.ruleID) return true;
if (other.ruleID < ruleID) return false;
if (resource < other.resource) return true;
if (other.resource < resource) return false;
if (action < other.action) return true;
if (other.action < action) return false;
if (forbids < other.forbids) return true;
if (other.forbids < forbids) return false;
if (isDefault < other.isDefault) return true;
if (other.isDefault < isDefault) return false;
if (details < other.details) return true;
if (other.details < details) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
RemoveSignerRuleData::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
RemoveSignerRuleData::_ext_t::to_bytes(xdr::marshaler& m) const
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
RemoveSignerRuleData::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
RemoveSignerRuleData::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
RemoveSignerRuleData::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
RemoveSignerRuleData::from_bytes(xdr::unmarshaler& u) 
{
bool okruleID = u.from_bytes(ruleID);
if (!okruleID)
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
RemoveSignerRuleData::to_bytes(xdr::marshaler& m) const 
{
bool okruleID = m.to_bytes(ruleID);
if (!okruleID)
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
RemoveSignerRuleData::count_size(xdr::measurer& m) const 
{
m.count_size(ruleID);
m.count_size(ext);
}
bool
RemoveSignerRuleData::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<RemoveSignerRuleData const&>(other_abstract);return true
&& (ruleID== other.ruleID)
&& (ext== other.ext)
;}
bool
RemoveSignerRuleData::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<RemoveSignerRuleData const&>(other_abstract);
if (ruleID < other.ruleID) return true;
if (other.ruleID < ruleID) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageSignerRuleOp::_data_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(action_);
if (!ok)
{
return false;
}
switch (action_)
{

    case (int32_t)ManageSignerRuleAction::CREATE:
return u.from_bytes(createData_);
    case (int32_t)ManageSignerRuleAction::UPDATE:
return u.from_bytes(updateData_);
    case (int32_t)ManageSignerRuleAction::REMOVE:
return u.from_bytes(removeData_);
}
return false;
}
bool
ManageSignerRuleOp::_data_t::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(action_);
if (!ok)
{
return false;
}
switch (action_)
{

    case (int32_t)ManageSignerRuleAction::CREATE:
return m.to_bytes(createData_);
    case (int32_t)ManageSignerRuleAction::UPDATE:
return m.to_bytes(updateData_);
    case (int32_t)ManageSignerRuleAction::REMOVE:
return m.to_bytes(removeData_);
}
return false;
}
void
ManageSignerRuleOp::_data_t::count_size(xdr::measurer& m) const
{
m.count_size(action_);
switch (action_)
{

    case (int32_t)ManageSignerRuleAction::CREATE:
return m.count_size(createData_);
    case (int32_t)ManageSignerRuleAction::UPDATE:
return m.count_size(updateData_);
    case (int32_t)ManageSignerRuleAction::REMOVE:
return m.count_size(removeData_);
}
}
bool
ManageSignerRuleOp::_data_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_data_t const&>(other_abstract);
if (other.action_ != action_) return false;
switch (action_)
{
    case (int32_t)ManageSignerRuleAction::CREATE:
return createData_ == other.createData_;
    case (int32_t)ManageSignerRuleAction::UPDATE:
return updateData_ == other.updateData_;
    case (int32_t)ManageSignerRuleAction::REMOVE:
return removeData_ == other.removeData_;
}
return false;
}
bool
ManageSignerRuleOp::_data_t::operator<(xdr_abstract const& other_abstract) const
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
    case (int32_t)ManageSignerRuleAction::CREATE:
return createData_ < other.createData_;
    case (int32_t)ManageSignerRuleAction::UPDATE:
return updateData_ < other.updateData_;
    case (int32_t)ManageSignerRuleAction::REMOVE:
return removeData_ < other.removeData_;
}
return false;
}
bool
ManageSignerRuleOp::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ManageSignerRuleOp::_ext_t::to_bytes(xdr::marshaler& m) const
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
ManageSignerRuleOp::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
ManageSignerRuleOp::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ManageSignerRuleOp::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ManageSignerRuleOp::from_bytes(xdr::unmarshaler& u) 
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
ManageSignerRuleOp::to_bytes(xdr::marshaler& m) const 
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
ManageSignerRuleOp::count_size(xdr::measurer& m) const 
{
m.count_size(data);
m.count_size(ext);
}
bool
ManageSignerRuleOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<ManageSignerRuleOp const&>(other_abstract);return true
&& (data== other.data)
&& (ext== other.ext)
;}
bool
ManageSignerRuleOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManageSignerRuleOp const&>(other_abstract);
if (data < other.data) return true;
if (other.data < data) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageSignerRuleResult::_success_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ManageSignerRuleResult::_success_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
ManageSignerRuleResult::_success_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
ManageSignerRuleResult::_success_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ManageSignerRuleResult::_success_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ManageSignerRuleResult::_success_t::from_bytes(xdr::unmarshaler& u) 
{
bool okruleID = u.from_bytes(ruleID);
if (!okruleID)
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
ManageSignerRuleResult::_success_t::to_bytes(xdr::marshaler& m) const 
{
bool okruleID = m.to_bytes(ruleID);
if (!okruleID)
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
ManageSignerRuleResult::_success_t::count_size(xdr::measurer& m) const 
{
m.count_size(ruleID);
m.count_size(ext);
}
bool
ManageSignerRuleResult::_success_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_success_t const&>(other_abstract);return true
&& (ruleID== other.ruleID)
&& (ext== other.ext)
;}
bool
ManageSignerRuleResult::_success_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_success_t const&>(other_abstract);
if (ruleID < other.ruleID) return true;
if (other.ruleID < ruleID) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageSignerRuleResult::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)ManageSignerRuleResultCode::SUCCESS:
return u.from_bytes(success_);
  case (int32_t)ManageSignerRuleResultCode::RULE_IS_USED:
return u.from_bytes(roleIDs_);
  default:
    return true;
}
return false;
}
bool
ManageSignerRuleResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)ManageSignerRuleResultCode::SUCCESS:
return m.to_bytes(success_);
  case (int32_t)ManageSignerRuleResultCode::RULE_IS_USED:
return m.to_bytes(roleIDs_);
  default:
    return true;
}
return false;
}
void
ManageSignerRuleResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)ManageSignerRuleResultCode::SUCCESS:
return m.count_size(success_);
  case (int32_t)ManageSignerRuleResultCode::RULE_IS_USED:
return m.count_size(roleIDs_);
  default:
  
  return;
}
}
bool
ManageSignerRuleResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<ManageSignerRuleResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)ManageSignerRuleResultCode::SUCCESS:
return success_ == other.success_;
  case (int32_t)ManageSignerRuleResultCode::RULE_IS_USED:
return roleIDs_ == other.roleIDs_;
  default:
  
  return true;
}
return false;
}
bool
ManageSignerRuleResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManageSignerRuleResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)ManageSignerRuleResultCode::SUCCESS:
return success_ < other.success_;
  case (int32_t)ManageSignerRuleResultCode::RULE_IS_USED:
return roleIDs_ < other.roleIDs_;
  default:
    return false;
}
return false;
}
}