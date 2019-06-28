#include "operation-manage-external-system-id-pool-entry.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
CreateExternalSystemAccountIdPoolEntryActionInput::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
CreateExternalSystemAccountIdPoolEntryActionInput::_ext_t::to_bytes(xdr::marshaler& m) const
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
CreateExternalSystemAccountIdPoolEntryActionInput::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
CreateExternalSystemAccountIdPoolEntryActionInput::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
CreateExternalSystemAccountIdPoolEntryActionInput::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
CreateExternalSystemAccountIdPoolEntryActionInput::from_bytes(xdr::unmarshaler& u) 
{
bool okexternalSystemType = u.from_bytes(externalSystemType);
if (!okexternalSystemType)
{
return false;
}
bool okdata = u.from_bytes(data);
if (!okdata)
{
return false;
}
bool okparent = u.from_bytes(parent);
if (!okparent)
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
CreateExternalSystemAccountIdPoolEntryActionInput::to_bytes(xdr::marshaler& m) const 
{
bool okexternalSystemType = m.to_bytes(externalSystemType);
if (!okexternalSystemType)
{
return false;
}
bool okdata = m.to_bytes(data);
if (!okdata)
{
return false;
}
bool okparent = m.to_bytes(parent);
if (!okparent)
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
CreateExternalSystemAccountIdPoolEntryActionInput::count_size(xdr::measurer& m) const 
{
m.count_size(externalSystemType);
m.count_size(data);
m.count_size(parent);
m.count_size(ext);
}
bool
CreateExternalSystemAccountIdPoolEntryActionInput::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CreateExternalSystemAccountIdPoolEntryActionInput const&>(other_abstract);return true
&& (externalSystemType== other.externalSystemType)
&& (data== other.data)
&& (parent== other.parent)
&& (ext== other.ext)
;}
bool
CreateExternalSystemAccountIdPoolEntryActionInput::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreateExternalSystemAccountIdPoolEntryActionInput const&>(other_abstract);
if (externalSystemType < other.externalSystemType) return true;
if (other.externalSystemType < externalSystemType) return false;
if (data < other.data) return true;
if (other.data < data) return false;
if (parent < other.parent) return true;
if (other.parent < parent) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
DeleteExternalSystemAccountIdPoolEntryActionInput::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
DeleteExternalSystemAccountIdPoolEntryActionInput::_ext_t::to_bytes(xdr::marshaler& m) const
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
DeleteExternalSystemAccountIdPoolEntryActionInput::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
DeleteExternalSystemAccountIdPoolEntryActionInput::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
DeleteExternalSystemAccountIdPoolEntryActionInput::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
DeleteExternalSystemAccountIdPoolEntryActionInput::from_bytes(xdr::unmarshaler& u) 
{
bool okpoolEntryID = u.from_bytes(poolEntryID);
if (!okpoolEntryID)
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
DeleteExternalSystemAccountIdPoolEntryActionInput::to_bytes(xdr::marshaler& m) const 
{
bool okpoolEntryID = m.to_bytes(poolEntryID);
if (!okpoolEntryID)
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
DeleteExternalSystemAccountIdPoolEntryActionInput::count_size(xdr::measurer& m) const 
{
m.count_size(poolEntryID);
m.count_size(ext);
}
bool
DeleteExternalSystemAccountIdPoolEntryActionInput::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<DeleteExternalSystemAccountIdPoolEntryActionInput const&>(other_abstract);return true
&& (poolEntryID== other.poolEntryID)
&& (ext== other.ext)
;}
bool
DeleteExternalSystemAccountIdPoolEntryActionInput::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<DeleteExternalSystemAccountIdPoolEntryActionInput const&>(other_abstract);
if (poolEntryID < other.poolEntryID) return true;
if (other.poolEntryID < poolEntryID) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageExternalSystemAccountIdPoolEntryOp::_actionInput_t::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (action_)
{
    case (int32_t)ManageExternalSystemAccountIdPoolEntryAction::CREATE:
return u.from_bytes(createExternalSystemAccountIdPoolEntryActionInput_);
    case (int32_t)ManageExternalSystemAccountIdPoolEntryAction::REMOVE:
return u.from_bytes(deleteExternalSystemAccountIdPoolEntryActionInput_);
}
return false;
}
bool
ManageExternalSystemAccountIdPoolEntryOp::_actionInput_t::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(action_);
if (!ok)
{
return false;
}
switch (action_)
{

    case (int32_t)ManageExternalSystemAccountIdPoolEntryAction::CREATE:
return m.to_bytes(createExternalSystemAccountIdPoolEntryActionInput_);
    case (int32_t)ManageExternalSystemAccountIdPoolEntryAction::REMOVE:
return m.to_bytes(deleteExternalSystemAccountIdPoolEntryActionInput_);
}
return false;
}
void
ManageExternalSystemAccountIdPoolEntryOp::_actionInput_t::count_size(xdr::measurer& m) const
{
m.count_size(action_);
switch (action_)
{

    case (int32_t)ManageExternalSystemAccountIdPoolEntryAction::CREATE:
return m.count_size(createExternalSystemAccountIdPoolEntryActionInput_);
    case (int32_t)ManageExternalSystemAccountIdPoolEntryAction::REMOVE:
return m.count_size(deleteExternalSystemAccountIdPoolEntryActionInput_);
}
}
bool
ManageExternalSystemAccountIdPoolEntryOp::_actionInput_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_actionInput_t const&>(other_abstract);
if (other.action_ != action_) return false;
switch (action_)
{
    case (int32_t)ManageExternalSystemAccountIdPoolEntryAction::CREATE:
return createExternalSystemAccountIdPoolEntryActionInput_ == other.createExternalSystemAccountIdPoolEntryActionInput_;
    case (int32_t)ManageExternalSystemAccountIdPoolEntryAction::REMOVE:
return deleteExternalSystemAccountIdPoolEntryActionInput_ == other.deleteExternalSystemAccountIdPoolEntryActionInput_;
}
return false;
}
bool
ManageExternalSystemAccountIdPoolEntryOp::_actionInput_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_actionInput_t const&>(other_abstract);
if (action_ < other.action_) return true;
if (other.action_ < action_) return false;
switch (action_)
{
    case (int32_t)ManageExternalSystemAccountIdPoolEntryAction::CREATE:
return createExternalSystemAccountIdPoolEntryActionInput_ < other.createExternalSystemAccountIdPoolEntryActionInput_;
    case (int32_t)ManageExternalSystemAccountIdPoolEntryAction::REMOVE:
return deleteExternalSystemAccountIdPoolEntryActionInput_ < other.deleteExternalSystemAccountIdPoolEntryActionInput_;
}
return false;
}
bool
ManageExternalSystemAccountIdPoolEntryOp::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ManageExternalSystemAccountIdPoolEntryOp::_ext_t::to_bytes(xdr::marshaler& m) const
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
ManageExternalSystemAccountIdPoolEntryOp::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
ManageExternalSystemAccountIdPoolEntryOp::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ManageExternalSystemAccountIdPoolEntryOp::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ManageExternalSystemAccountIdPoolEntryOp::from_bytes(xdr::unmarshaler& u) 
{
bool okactionInput = u.from_bytes(actionInput);
if (!okactionInput)
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
ManageExternalSystemAccountIdPoolEntryOp::to_bytes(xdr::marshaler& m) const 
{
bool okactionInput = m.to_bytes(actionInput);
if (!okactionInput)
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
ManageExternalSystemAccountIdPoolEntryOp::count_size(xdr::measurer& m) const 
{
m.count_size(actionInput);
m.count_size(ext);
}
bool
ManageExternalSystemAccountIdPoolEntryOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<ManageExternalSystemAccountIdPoolEntryOp const&>(other_abstract);return true
&& (actionInput== other.actionInput)
&& (ext== other.ext)
;}
bool
ManageExternalSystemAccountIdPoolEntryOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManageExternalSystemAccountIdPoolEntryOp const&>(other_abstract);
if (actionInput < other.actionInput) return true;
if (other.actionInput < actionInput) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageExternalSystemAccountIdPoolEntrySuccess::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ManageExternalSystemAccountIdPoolEntrySuccess::_ext_t::to_bytes(xdr::marshaler& m) const
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
ManageExternalSystemAccountIdPoolEntrySuccess::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
ManageExternalSystemAccountIdPoolEntrySuccess::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ManageExternalSystemAccountIdPoolEntrySuccess::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ManageExternalSystemAccountIdPoolEntrySuccess::from_bytes(xdr::unmarshaler& u) 
{
bool okpoolEntryID = u.from_bytes(poolEntryID);
if (!okpoolEntryID)
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
ManageExternalSystemAccountIdPoolEntrySuccess::to_bytes(xdr::marshaler& m) const 
{
bool okpoolEntryID = m.to_bytes(poolEntryID);
if (!okpoolEntryID)
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
ManageExternalSystemAccountIdPoolEntrySuccess::count_size(xdr::measurer& m) const 
{
m.count_size(poolEntryID);
m.count_size(ext);
}
bool
ManageExternalSystemAccountIdPoolEntrySuccess::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<ManageExternalSystemAccountIdPoolEntrySuccess const&>(other_abstract);return true
&& (poolEntryID== other.poolEntryID)
&& (ext== other.ext)
;}
bool
ManageExternalSystemAccountIdPoolEntrySuccess::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManageExternalSystemAccountIdPoolEntrySuccess const&>(other_abstract);
if (poolEntryID < other.poolEntryID) return true;
if (other.poolEntryID < poolEntryID) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageExternalSystemAccountIdPoolEntryResult::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (code_)
{
  case (int32_t)ManageExternalSystemAccountIdPoolEntryResultCode::SUCCESS:
return u.from_bytes(success_);
  default:
  
  return true;
}
return false;
}
bool
ManageExternalSystemAccountIdPoolEntryResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)ManageExternalSystemAccountIdPoolEntryResultCode::SUCCESS:
return m.to_bytes(success_);
  default:
    return true;
}
return false;
}
void
ManageExternalSystemAccountIdPoolEntryResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)ManageExternalSystemAccountIdPoolEntryResultCode::SUCCESS:
return m.count_size(success_);
  default:
  
  return;
}
}
bool
ManageExternalSystemAccountIdPoolEntryResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<ManageExternalSystemAccountIdPoolEntryResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)ManageExternalSystemAccountIdPoolEntryResultCode::SUCCESS:
return success_ == other.success_;
  default:
  
  return true;
}
return false;
}
bool
ManageExternalSystemAccountIdPoolEntryResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManageExternalSystemAccountIdPoolEntryResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)ManageExternalSystemAccountIdPoolEntryResultCode::SUCCESS:
return success_ < other.success_;
  default:
    return false;
}
return false;
}
}