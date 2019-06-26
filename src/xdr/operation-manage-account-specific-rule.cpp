#include "operation-manage-account-specific-rule.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
CreateAccountSpecificRuleData::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
CreateAccountSpecificRuleData::_ext_t::to_bytes(xdr::marshaler& m) const
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
CreateAccountSpecificRuleData::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
CreateAccountSpecificRuleData::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
CreateAccountSpecificRuleData::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
CreateAccountSpecificRuleData::from_bytes(xdr::unmarshaler& u) 
{
bool okledgerKey = u.from_bytes(ledgerKey);
if (!okledgerKey)
{
return false;
}
bool okaccountID = u.from_bytes(accountID);
if (!okaccountID)
{
return false;
}
bool okforbids = u.from_bytes(forbids);
if (!okforbids)
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
CreateAccountSpecificRuleData::to_bytes(xdr::marshaler& m) const 
{
bool okledgerKey = m.to_bytes(ledgerKey);
if (!okledgerKey)
{
return false;
}
bool okaccountID = m.to_bytes(accountID);
if (!okaccountID)
{
return false;
}
bool okforbids = m.to_bytes(forbids);
if (!okforbids)
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
CreateAccountSpecificRuleData::count_size(xdr::measurer& m) const 
{
m.count_size(ledgerKey);
m.count_size(accountID);
m.count_size(forbids);
m.count_size(ext);
}
bool
CreateAccountSpecificRuleData::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CreateAccountSpecificRuleData const&>(other_abstract);return true
&& (ledgerKey== other.ledgerKey)
&& (accountID== other.accountID)
&& (forbids== other.forbids)
&& (ext== other.ext)
;}
bool
CreateAccountSpecificRuleData::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreateAccountSpecificRuleData const&>(other_abstract);
if (ledgerKey < other.ledgerKey) return true;
if (other.ledgerKey < ledgerKey) return false;
if (accountID < other.accountID) return true;
if (other.accountID < accountID) return false;
if (forbids < other.forbids) return true;
if (other.forbids < forbids) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
RemoveAccountSpecificRuleData::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
RemoveAccountSpecificRuleData::_ext_t::to_bytes(xdr::marshaler& m) const
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
RemoveAccountSpecificRuleData::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
RemoveAccountSpecificRuleData::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
RemoveAccountSpecificRuleData::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
RemoveAccountSpecificRuleData::from_bytes(xdr::unmarshaler& u) 
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
RemoveAccountSpecificRuleData::to_bytes(xdr::marshaler& m) const 
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
RemoveAccountSpecificRuleData::count_size(xdr::measurer& m) const 
{
m.count_size(ruleID);
m.count_size(ext);
}
bool
RemoveAccountSpecificRuleData::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<RemoveAccountSpecificRuleData const&>(other_abstract);return true
&& (ruleID== other.ruleID)
&& (ext== other.ext)
;}
bool
RemoveAccountSpecificRuleData::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<RemoveAccountSpecificRuleData const&>(other_abstract);
if (ruleID < other.ruleID) return true;
if (other.ruleID < ruleID) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageAccountSpecificRuleOp::_data_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(action_);
if (!ok)
{
return false;
}
switch (action_)
{

    case (int32_t)ManageAccountSpecificRuleAction::CREATE:
return u.from_bytes(createData_);
    case (int32_t)ManageAccountSpecificRuleAction::REMOVE:
return u.from_bytes(removeData_);
}
return false;
}
bool
ManageAccountSpecificRuleOp::_data_t::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(action_);
if (!ok)
{
return false;
}
switch (action_)
{

    case (int32_t)ManageAccountSpecificRuleAction::CREATE:
return m.to_bytes(createData_);
    case (int32_t)ManageAccountSpecificRuleAction::REMOVE:
return m.to_bytes(removeData_);
}
return false;
}
void
ManageAccountSpecificRuleOp::_data_t::count_size(xdr::measurer& m) const
{
m.count_size(action_);
switch (action_)
{

    case (int32_t)ManageAccountSpecificRuleAction::CREATE:
return m.count_size(createData_);
    case (int32_t)ManageAccountSpecificRuleAction::REMOVE:
return m.count_size(removeData_);
}
}
bool
ManageAccountSpecificRuleOp::_data_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_data_t const&>(other_abstract);
if (other.action_ != action_) return false;
switch (action_)
{
    case (int32_t)ManageAccountSpecificRuleAction::CREATE:
return createData_ == other.createData_;
    case (int32_t)ManageAccountSpecificRuleAction::REMOVE:
return removeData_ == other.removeData_;
}
return false;
}
bool
ManageAccountSpecificRuleOp::_data_t::operator<(xdr_abstract const& other_abstract) const
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
    case (int32_t)ManageAccountSpecificRuleAction::CREATE:
return createData_ < other.createData_;
    case (int32_t)ManageAccountSpecificRuleAction::REMOVE:
return removeData_ < other.removeData_;
}
return false;
}
bool
ManageAccountSpecificRuleOp::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ManageAccountSpecificRuleOp::_ext_t::to_bytes(xdr::marshaler& m) const
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
ManageAccountSpecificRuleOp::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
ManageAccountSpecificRuleOp::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ManageAccountSpecificRuleOp::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ManageAccountSpecificRuleOp::from_bytes(xdr::unmarshaler& u) 
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
ManageAccountSpecificRuleOp::to_bytes(xdr::marshaler& m) const 
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
ManageAccountSpecificRuleOp::count_size(xdr::measurer& m) const 
{
m.count_size(data);
m.count_size(ext);
}
bool
ManageAccountSpecificRuleOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<ManageAccountSpecificRuleOp const&>(other_abstract);return true
&& (data== other.data)
&& (ext== other.ext)
;}
bool
ManageAccountSpecificRuleOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManageAccountSpecificRuleOp const&>(other_abstract);
if (data < other.data) return true;
if (other.data < data) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageAccountSpecificRuleResult::_success_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ManageAccountSpecificRuleResult::_success_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
ManageAccountSpecificRuleResult::_success_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
ManageAccountSpecificRuleResult::_success_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ManageAccountSpecificRuleResult::_success_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ManageAccountSpecificRuleResult::_success_t::from_bytes(xdr::unmarshaler& u) 
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
ManageAccountSpecificRuleResult::_success_t::to_bytes(xdr::marshaler& m) const 
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
ManageAccountSpecificRuleResult::_success_t::count_size(xdr::measurer& m) const 
{
m.count_size(ruleID);
m.count_size(ext);
}
bool
ManageAccountSpecificRuleResult::_success_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_success_t const&>(other_abstract);return true
&& (ruleID== other.ruleID)
&& (ext== other.ext)
;}
bool
ManageAccountSpecificRuleResult::_success_t::operator<(xdr_abstract const& other_abstract) const
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
ManageAccountSpecificRuleResult::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)ManageAccountSpecificRuleResultCode::SUCCESS:
return u.from_bytes(success_);
  default:
    return true;
}
return false;
}
bool
ManageAccountSpecificRuleResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)ManageAccountSpecificRuleResultCode::SUCCESS:
return m.to_bytes(success_);
  default:
    return true;
}
return false;
}
void
ManageAccountSpecificRuleResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)ManageAccountSpecificRuleResultCode::SUCCESS:
return m.count_size(success_);
  default:
  
  return;
}
}
bool
ManageAccountSpecificRuleResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<ManageAccountSpecificRuleResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)ManageAccountSpecificRuleResultCode::SUCCESS:
return success_ == other.success_;
  default:
  
  return true;
}
return false;
}
bool
ManageAccountSpecificRuleResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManageAccountSpecificRuleResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)ManageAccountSpecificRuleResultCode::SUCCESS:
return success_ < other.success_;
  default:
    return false;
}
return false;
}
}