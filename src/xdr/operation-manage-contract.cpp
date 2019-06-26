#include "operation-manage-contract.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
ManageContractOp::_data_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(action_);
if (!ok)
{
return false;
}
switch (action_)
{

    case (int32_t)ManageContractAction::ADD_DETAILS:
return u.from_bytes(details_);
    case (int32_t)ManageContractAction::CONFIRM_COMPLETED:
      return true;
    case (int32_t)ManageContractAction::START_DISPUTE:
return u.from_bytes(disputeReason_);
    case (int32_t)ManageContractAction::RESOLVE_DISPUTE:
return u.from_bytes(isRevert_);
}
return false;
}
bool
ManageContractOp::_data_t::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(action_);
if (!ok)
{
return false;
}
switch (action_)
{

    case (int32_t)ManageContractAction::ADD_DETAILS:
return m.to_bytes(details_);
    case (int32_t)ManageContractAction::CONFIRM_COMPLETED:
      return true;
    case (int32_t)ManageContractAction::START_DISPUTE:
return m.to_bytes(disputeReason_);
    case (int32_t)ManageContractAction::RESOLVE_DISPUTE:
return m.to_bytes(isRevert_);
}
return false;
}
void
ManageContractOp::_data_t::count_size(xdr::measurer& m) const
{
m.count_size(action_);
switch (action_)
{

    case (int32_t)ManageContractAction::ADD_DETAILS:
return m.count_size(details_);
    case (int32_t)ManageContractAction::CONFIRM_COMPLETED:
    
  return;
    case (int32_t)ManageContractAction::START_DISPUTE:
return m.count_size(disputeReason_);
    case (int32_t)ManageContractAction::RESOLVE_DISPUTE:
return m.count_size(isRevert_);
}
}
bool
ManageContractOp::_data_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_data_t const&>(other_abstract);
if (other.action_ != action_) return false;
switch (action_)
{
    case (int32_t)ManageContractAction::ADD_DETAILS:
return details_ == other.details_;
    case (int32_t)ManageContractAction::CONFIRM_COMPLETED:
    
  return true;
    case (int32_t)ManageContractAction::START_DISPUTE:
return disputeReason_ == other.disputeReason_;
    case (int32_t)ManageContractAction::RESOLVE_DISPUTE:
return isRevert_ == other.isRevert_;
}
return false;
}
bool
ManageContractOp::_data_t::operator<(xdr_abstract const& other_abstract) const
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
    case (int32_t)ManageContractAction::ADD_DETAILS:
return details_ < other.details_;
    case (int32_t)ManageContractAction::CONFIRM_COMPLETED:
      return false;
    case (int32_t)ManageContractAction::START_DISPUTE:
return disputeReason_ < other.disputeReason_;
    case (int32_t)ManageContractAction::RESOLVE_DISPUTE:
return isRevert_ < other.isRevert_;
}
return false;
}
bool
ManageContractOp::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ManageContractOp::_ext_t::to_bytes(xdr::marshaler& m) const
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
ManageContractOp::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
ManageContractOp::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ManageContractOp::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ManageContractOp::from_bytes(xdr::unmarshaler& u) 
{
bool okcontractID = u.from_bytes(contractID);
if (!okcontractID)
{
return false;
}
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
ManageContractOp::to_bytes(xdr::marshaler& m) const 
{
bool okcontractID = m.to_bytes(contractID);
if (!okcontractID)
{
return false;
}
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
ManageContractOp::count_size(xdr::measurer& m) const 
{
m.count_size(contractID);
m.count_size(data);
m.count_size(ext);
}
bool
ManageContractOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<ManageContractOp const&>(other_abstract);return true
&& (contractID== other.contractID)
&& (data== other.data)
&& (ext== other.ext)
;}
bool
ManageContractOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManageContractOp const&>(other_abstract);
if (contractID < other.contractID) return true;
if (other.contractID < contractID) return false;
if (data < other.data) return true;
if (other.data < data) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageContractResponse::_data_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(action_);
if (!ok)
{
return false;
}
switch (action_)
{

    case (int32_t)ManageContractAction::CONFIRM_COMPLETED:
return u.from_bytes(isCompleted_);
    default:
      return true;
}
return false;
}
bool
ManageContractResponse::_data_t::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(action_);
if (!ok)
{
return false;
}
switch (action_)
{

    case (int32_t)ManageContractAction::CONFIRM_COMPLETED:
return m.to_bytes(isCompleted_);
    default:
      return true;
}
return false;
}
void
ManageContractResponse::_data_t::count_size(xdr::measurer& m) const
{
m.count_size(action_);
switch (action_)
{

    case (int32_t)ManageContractAction::CONFIRM_COMPLETED:
return m.count_size(isCompleted_);
    default:
    
  return;
}
}
bool
ManageContractResponse::_data_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_data_t const&>(other_abstract);
if (other.action_ != action_) return false;
switch (action_)
{
    case (int32_t)ManageContractAction::CONFIRM_COMPLETED:
return isCompleted_ == other.isCompleted_;
    default:
    
  return true;
}
return false;
}
bool
ManageContractResponse::_data_t::operator<(xdr_abstract const& other_abstract) const
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
    case (int32_t)ManageContractAction::CONFIRM_COMPLETED:
return isCompleted_ < other.isCompleted_;
    default:
      return false;
}
return false;
}
bool
ManageContractResponse::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ManageContractResponse::_ext_t::to_bytes(xdr::marshaler& m) const
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
ManageContractResponse::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
ManageContractResponse::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ManageContractResponse::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ManageContractResponse::from_bytes(xdr::unmarshaler& u) 
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
ManageContractResponse::to_bytes(xdr::marshaler& m) const 
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
ManageContractResponse::count_size(xdr::measurer& m) const 
{
m.count_size(data);
m.count_size(ext);
}
bool
ManageContractResponse::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<ManageContractResponse const&>(other_abstract);return true
&& (data== other.data)
&& (ext== other.ext)
;}
bool
ManageContractResponse::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManageContractResponse const&>(other_abstract);
if (data < other.data) return true;
if (other.data < data) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageContractResult::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)ManageContractResultCode::SUCCESS:
return u.from_bytes(response_);
  default:
    return true;
}
return false;
}
bool
ManageContractResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)ManageContractResultCode::SUCCESS:
return m.to_bytes(response_);
  default:
    return true;
}
return false;
}
void
ManageContractResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)ManageContractResultCode::SUCCESS:
return m.count_size(response_);
  default:
  
  return;
}
}
bool
ManageContractResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<ManageContractResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)ManageContractResultCode::SUCCESS:
return response_ == other.response_;
  default:
  
  return true;
}
return false;
}
bool
ManageContractResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManageContractResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)ManageContractResultCode::SUCCESS:
return response_ < other.response_;
  default:
    return false;
}
return false;
}
}