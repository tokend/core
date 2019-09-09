#include "operation-manage-limits.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
LimitsCreateDetails::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
LimitsCreateDetails::_ext_t::to_bytes(xdr::marshaler& m) const
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
LimitsCreateDetails::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
LimitsCreateDetails::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
LimitsCreateDetails::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
LimitsCreateDetails::from_bytes(xdr::unmarshaler& u) 
{
bool okaccountRole = u.from_bytes(accountRole);
if (!okaccountRole)
{
return false;
}
bool okaccountID = u.from_bytes(accountID);
if (!okaccountID)
{
return false;
}
bool okstatsOpType = u.from_bytes(statsOpType);
if (!okstatsOpType)
{
return false;
}
bool okassetCode = u.from_bytes(assetCode);
if (!okassetCode)
{
return false;
}
bool okisConvertNeeded = u.from_bytes(isConvertNeeded);
if (!okisConvertNeeded)
{
return false;
}
bool okdailyOut = u.from_bytes(dailyOut);
if (!okdailyOut)
{
return false;
}
bool okweeklyOut = u.from_bytes(weeklyOut);
if (!okweeklyOut)
{
return false;
}
bool okmonthlyOut = u.from_bytes(monthlyOut);
if (!okmonthlyOut)
{
return false;
}
bool okannualOut = u.from_bytes(annualOut);
if (!okannualOut)
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
LimitsCreateDetails::to_bytes(xdr::marshaler& m) const 
{
bool okaccountRole = m.to_bytes(accountRole);
if (!okaccountRole)
{
return false;
}
bool okaccountID = m.to_bytes(accountID);
if (!okaccountID)
{
return false;
}
bool okstatsOpType = m.to_bytes(statsOpType);
if (!okstatsOpType)
{
return false;
}
bool okassetCode = m.to_bytes(assetCode);
if (!okassetCode)
{
return false;
}
bool okisConvertNeeded = m.to_bytes(isConvertNeeded);
if (!okisConvertNeeded)
{
return false;
}
bool okdailyOut = m.to_bytes(dailyOut);
if (!okdailyOut)
{
return false;
}
bool okweeklyOut = m.to_bytes(weeklyOut);
if (!okweeklyOut)
{
return false;
}
bool okmonthlyOut = m.to_bytes(monthlyOut);
if (!okmonthlyOut)
{
return false;
}
bool okannualOut = m.to_bytes(annualOut);
if (!okannualOut)
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
LimitsCreateDetails::count_size(xdr::measurer& m) const 
{
m.count_size(accountRole);
m.count_size(accountID);
m.count_size(statsOpType);
m.count_size(assetCode);
m.count_size(isConvertNeeded);
m.count_size(dailyOut);
m.count_size(weeklyOut);
m.count_size(monthlyOut);
m.count_size(annualOut);
m.count_size(ext);
}
bool
LimitsCreateDetails::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<LimitsCreateDetails const&>(other_abstract);return true
&& (accountRole== other.accountRole)
&& (accountID== other.accountID)
&& (statsOpType== other.statsOpType)
&& (assetCode== other.assetCode)
&& (isConvertNeeded== other.isConvertNeeded)
&& (dailyOut== other.dailyOut)
&& (weeklyOut== other.weeklyOut)
&& (monthlyOut== other.monthlyOut)
&& (annualOut== other.annualOut)
&& (ext== other.ext)
;}
bool
LimitsCreateDetails::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<LimitsCreateDetails const&>(other_abstract);
if (accountRole < other.accountRole) return true;
if (other.accountRole < accountRole) return false;
if (accountID < other.accountID) return true;
if (other.accountID < accountID) return false;
if (statsOpType < other.statsOpType) return true;
if (other.statsOpType < statsOpType) return false;
if (assetCode < other.assetCode) return true;
if (other.assetCode < assetCode) return false;
if (isConvertNeeded < other.isConvertNeeded) return true;
if (other.isConvertNeeded < isConvertNeeded) return false;
if (dailyOut < other.dailyOut) return true;
if (other.dailyOut < dailyOut) return false;
if (weeklyOut < other.weeklyOut) return true;
if (other.weeklyOut < weeklyOut) return false;
if (monthlyOut < other.monthlyOut) return true;
if (other.monthlyOut < monthlyOut) return false;
if (annualOut < other.annualOut) return true;
if (other.annualOut < annualOut) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageLimitsOp::_details_t::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (action_)
{
    case (int32_t)ManageLimitsAction::CREATE:
return u.from_bytes(limitsCreateDetails_);
    case (int32_t)ManageLimitsAction::REMOVE:
return u.from_bytes(id_);
}
return false;
}
bool
ManageLimitsOp::_details_t::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(action_);
if (!ok)
{
return false;
}
switch (action_)
{

    case (int32_t)ManageLimitsAction::CREATE:
return m.to_bytes(limitsCreateDetails_);
    case (int32_t)ManageLimitsAction::REMOVE:
return m.to_bytes(id_);
}
return false;
}
void
ManageLimitsOp::_details_t::count_size(xdr::measurer& m) const
{
m.count_size(action_);
switch (action_)
{

    case (int32_t)ManageLimitsAction::CREATE:
return m.count_size(limitsCreateDetails_);
    case (int32_t)ManageLimitsAction::REMOVE:
return m.count_size(id_);
}
}
bool
ManageLimitsOp::_details_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_details_t const&>(other_abstract);
if (other.action_ != action_) return false;
switch (action_)
{
    case (int32_t)ManageLimitsAction::CREATE:
return limitsCreateDetails_ == other.limitsCreateDetails_;
    case (int32_t)ManageLimitsAction::REMOVE:
return id_ == other.id_;
}
return false;
}
bool
ManageLimitsOp::_details_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_details_t const&>(other_abstract);
if (action_ < other.action_) return true;
if (other.action_ < action_) return false;
switch (action_)
{
    case (int32_t)ManageLimitsAction::CREATE:
return limitsCreateDetails_ < other.limitsCreateDetails_;
    case (int32_t)ManageLimitsAction::REMOVE:
return id_ < other.id_;
}
return false;
}
bool
ManageLimitsOp::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ManageLimitsOp::_ext_t::to_bytes(xdr::marshaler& m) const
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
ManageLimitsOp::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
ManageLimitsOp::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ManageLimitsOp::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ManageLimitsOp::from_bytes(xdr::unmarshaler& u) 
{
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
ManageLimitsOp::to_bytes(xdr::marshaler& m) const 
{
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
ManageLimitsOp::count_size(xdr::measurer& m) const 
{
m.count_size(details);
m.count_size(ext);
}
bool
ManageLimitsOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<ManageLimitsOp const&>(other_abstract);return true
&& (details== other.details)
&& (ext== other.ext)
;}
bool
ManageLimitsOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManageLimitsOp const&>(other_abstract);
if (details < other.details) return true;
if (other.details < details) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageLimitsResult::_success_t::_details_t::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (action_)
{
      case (int32_t)ManageLimitsAction::CREATE:
return u.from_bytes(id_);
      case (int32_t)ManageLimitsAction::REMOVE:
      
  return true;
}
return false;
}
bool
ManageLimitsResult::_success_t::_details_t::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(action_);
if (!ok)
{
return false;
}
switch (action_)
{

      case (int32_t)ManageLimitsAction::CREATE:
return m.to_bytes(id_);
      case (int32_t)ManageLimitsAction::REMOVE:
        return true;
}
return false;
}
void
ManageLimitsResult::_success_t::_details_t::count_size(xdr::measurer& m) const
{
m.count_size(action_);
switch (action_)
{

      case (int32_t)ManageLimitsAction::CREATE:
return m.count_size(id_);
      case (int32_t)ManageLimitsAction::REMOVE:
      
  return;
}
}
bool
ManageLimitsResult::_success_t::_details_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_details_t const&>(other_abstract);
if (other.action_ != action_) return false;
switch (action_)
{
      case (int32_t)ManageLimitsAction::CREATE:
return id_ == other.id_;
      case (int32_t)ManageLimitsAction::REMOVE:
      
  return true;
}
return false;
}
bool
ManageLimitsResult::_success_t::_details_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_details_t const&>(other_abstract);
if (action_ < other.action_) return true;
if (other.action_ < action_) return false;
switch (action_)
{
      case (int32_t)ManageLimitsAction::CREATE:
return id_ < other.id_;
      case (int32_t)ManageLimitsAction::REMOVE:
        return false;
}
return false;
}
bool
ManageLimitsResult::_success_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ManageLimitsResult::_success_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
ManageLimitsResult::_success_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
ManageLimitsResult::_success_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ManageLimitsResult::_success_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ManageLimitsResult::_success_t::from_bytes(xdr::unmarshaler& u) 
{
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
ManageLimitsResult::_success_t::to_bytes(xdr::marshaler& m) const 
{
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
ManageLimitsResult::_success_t::count_size(xdr::measurer& m) const 
{
m.count_size(details);
m.count_size(ext);
}
bool
ManageLimitsResult::_success_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_success_t const&>(other_abstract);return true
&& (details== other.details)
&& (ext== other.ext)
;}
bool
ManageLimitsResult::_success_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_success_t const&>(other_abstract);
if (details < other.details) return true;
if (other.details < details) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageLimitsResult::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (code_)
{
  case (int32_t)ManageLimitsResultCode::SUCCESS:
return u.from_bytes(success_);
  default:
  
  return true;
}
return false;
}
bool
ManageLimitsResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)ManageLimitsResultCode::SUCCESS:
return m.to_bytes(success_);
  default:
    return true;
}
return false;
}
void
ManageLimitsResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)ManageLimitsResultCode::SUCCESS:
return m.count_size(success_);
  default:
  
  return;
}
}
bool
ManageLimitsResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<ManageLimitsResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)ManageLimitsResultCode::SUCCESS:
return success_ == other.success_;
  default:
  
  return true;
}
return false;
}
bool
ManageLimitsResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManageLimitsResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)ManageLimitsResultCode::SUCCESS:
return success_ < other.success_;
  default:
    return false;
}
return false;
}
}