#include "operation-manage-poll.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
ClosePollData::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ClosePollData::_ext_t::to_bytes(xdr::marshaler& m) const
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
ClosePollData::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
ClosePollData::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ClosePollData::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ClosePollData::from_bytes(xdr::unmarshaler& u) 
{
bool okresult = u.from_bytes(result);
if (!okresult)
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
ClosePollData::to_bytes(xdr::marshaler& m) const 
{
bool okresult = m.to_bytes(result);
if (!okresult)
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
ClosePollData::count_size(xdr::measurer& m) const 
{
m.count_size(result);
m.count_size(details);
m.count_size(ext);
}
bool
ClosePollData::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<ClosePollData const&>(other_abstract);return true
&& (result== other.result)
&& (details== other.details)
&& (ext== other.ext)
;}
bool
ClosePollData::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ClosePollData const&>(other_abstract);
if (result < other.result) return true;
if (other.result < result) return false;
if (details < other.details) return true;
if (other.details < details) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
UpdatePollEndTimeData::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
UpdatePollEndTimeData::_ext_t::to_bytes(xdr::marshaler& m) const
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
UpdatePollEndTimeData::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
UpdatePollEndTimeData::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
UpdatePollEndTimeData::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
UpdatePollEndTimeData::from_bytes(xdr::unmarshaler& u) 
{
bool oknewEndTime = u.from_bytes(newEndTime);
if (!oknewEndTime)
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
UpdatePollEndTimeData::to_bytes(xdr::marshaler& m) const 
{
bool oknewEndTime = m.to_bytes(newEndTime);
if (!oknewEndTime)
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
UpdatePollEndTimeData::count_size(xdr::measurer& m) const 
{
m.count_size(newEndTime);
m.count_size(ext);
}
bool
UpdatePollEndTimeData::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<UpdatePollEndTimeData const&>(other_abstract);return true
&& (newEndTime== other.newEndTime)
&& (ext== other.ext)
;}
bool
UpdatePollEndTimeData::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<UpdatePollEndTimeData const&>(other_abstract);
if (newEndTime < other.newEndTime) return true;
if (other.newEndTime < newEndTime) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManagePollOp::_data_t::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (action_)
{
    case (int32_t)ManagePollAction::CLOSE:
return u.from_bytes(closePollData_);
    case (int32_t)ManagePollAction::UPDATE_END_TIME:
return u.from_bytes(updateTimeData_);
    case (int32_t)ManagePollAction::CANCEL:
return u.from_bytes(ext_);
}
return false;
}
bool
ManagePollOp::_data_t::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(action_);
if (!ok)
{
return false;
}
switch (action_)
{

    case (int32_t)ManagePollAction::CLOSE:
return m.to_bytes(closePollData_);
    case (int32_t)ManagePollAction::UPDATE_END_TIME:
return m.to_bytes(updateTimeData_);
    case (int32_t)ManagePollAction::CANCEL:
return m.to_bytes(ext_);
}
return false;
}
void
ManagePollOp::_data_t::count_size(xdr::measurer& m) const
{
m.count_size(action_);
switch (action_)
{

    case (int32_t)ManagePollAction::CLOSE:
return m.count_size(closePollData_);
    case (int32_t)ManagePollAction::UPDATE_END_TIME:
return m.count_size(updateTimeData_);
    case (int32_t)ManagePollAction::CANCEL:
return m.count_size(ext_);
}
}
bool
ManagePollOp::_data_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_data_t const&>(other_abstract);
if (other.action_ != action_) return false;
switch (action_)
{
    case (int32_t)ManagePollAction::CLOSE:
return closePollData_ == other.closePollData_;
    case (int32_t)ManagePollAction::UPDATE_END_TIME:
return updateTimeData_ == other.updateTimeData_;
    case (int32_t)ManagePollAction::CANCEL:
return ext_ == other.ext_;
}
return false;
}
bool
ManagePollOp::_data_t::operator<(xdr_abstract const& other_abstract) const
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
    case (int32_t)ManagePollAction::CLOSE:
return closePollData_ < other.closePollData_;
    case (int32_t)ManagePollAction::UPDATE_END_TIME:
return updateTimeData_ < other.updateTimeData_;
    case (int32_t)ManagePollAction::CANCEL:
return ext_ < other.ext_;
}
return false;
}
bool
ManagePollOp::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ManagePollOp::_ext_t::to_bytes(xdr::marshaler& m) const
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
ManagePollOp::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
ManagePollOp::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ManagePollOp::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ManagePollOp::from_bytes(xdr::unmarshaler& u) 
{
bool okpollID = u.from_bytes(pollID);
if (!okpollID)
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
ManagePollOp::to_bytes(xdr::marshaler& m) const 
{
bool okpollID = m.to_bytes(pollID);
if (!okpollID)
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
ManagePollOp::count_size(xdr::measurer& m) const 
{
m.count_size(pollID);
m.count_size(data);
m.count_size(ext);
}
bool
ManagePollOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<ManagePollOp const&>(other_abstract);return true
&& (pollID== other.pollID)
&& (data== other.data)
&& (ext== other.ext)
;}
bool
ManagePollOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManagePollOp const&>(other_abstract);
if (pollID < other.pollID) return true;
if (other.pollID < pollID) return false;
if (data < other.data) return true;
if (other.data < data) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManagePollResult::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (code_)
{
  case (int32_t)ManagePollResultCode::SUCCESS:
return u.from_bytes(ext_);
  default:
  
  return true;
}
return false;
}
bool
ManagePollResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)ManagePollResultCode::SUCCESS:
return m.to_bytes(ext_);
  default:
    return true;
}
return false;
}
void
ManagePollResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)ManagePollResultCode::SUCCESS:
return m.count_size(ext_);
  default:
  
  return;
}
}
bool
ManagePollResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<ManagePollResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)ManagePollResultCode::SUCCESS:
return ext_ == other.ext_;
  default:
  
  return true;
}
return false;
}
bool
ManagePollResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManagePollResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)ManagePollResultCode::SUCCESS:
return ext_ < other.ext_;
  default:
    return false;
}
return false;
}
}