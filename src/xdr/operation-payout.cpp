#include "operation-payout.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
PayoutOp::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
PayoutOp::_ext_t::to_bytes(xdr::marshaler& m) const
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
PayoutOp::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
PayoutOp::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
PayoutOp::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
PayoutOp::from_bytes(xdr::unmarshaler& u) 
{
bool okasset = u.from_bytes(asset);
if (!okasset)
{
return false;
}
bool oksourceBalanceID = u.from_bytes(sourceBalanceID);
if (!oksourceBalanceID)
{
return false;
}
bool okmaxPayoutAmount = u.from_bytes(maxPayoutAmount);
if (!okmaxPayoutAmount)
{
return false;
}
bool okminPayoutAmount = u.from_bytes(minPayoutAmount);
if (!okminPayoutAmount)
{
return false;
}
bool okminAssetHolderAmount = u.from_bytes(minAssetHolderAmount);
if (!okminAssetHolderAmount)
{
return false;
}
bool okfee = u.from_bytes(fee);
if (!okfee)
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
PayoutOp::to_bytes(xdr::marshaler& m) const 
{
bool okasset = m.to_bytes(asset);
if (!okasset)
{
return false;
}
bool oksourceBalanceID = m.to_bytes(sourceBalanceID);
if (!oksourceBalanceID)
{
return false;
}
bool okmaxPayoutAmount = m.to_bytes(maxPayoutAmount);
if (!okmaxPayoutAmount)
{
return false;
}
bool okminPayoutAmount = m.to_bytes(minPayoutAmount);
if (!okminPayoutAmount)
{
return false;
}
bool okminAssetHolderAmount = m.to_bytes(minAssetHolderAmount);
if (!okminAssetHolderAmount)
{
return false;
}
bool okfee = m.to_bytes(fee);
if (!okfee)
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
PayoutOp::count_size(xdr::measurer& m) const 
{
m.count_size(asset);
m.count_size(sourceBalanceID);
m.count_size(maxPayoutAmount);
m.count_size(minPayoutAmount);
m.count_size(minAssetHolderAmount);
m.count_size(fee);
m.count_size(ext);
}
bool
PayoutOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<PayoutOp const&>(other_abstract);return true
&& (asset== other.asset)
&& (sourceBalanceID== other.sourceBalanceID)
&& (maxPayoutAmount== other.maxPayoutAmount)
&& (minPayoutAmount== other.minPayoutAmount)
&& (minAssetHolderAmount== other.minAssetHolderAmount)
&& (fee== other.fee)
&& (ext== other.ext)
;}
bool
PayoutOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<PayoutOp const&>(other_abstract);
if (asset < other.asset) return true;
if (other.asset < asset) return false;
if (sourceBalanceID < other.sourceBalanceID) return true;
if (other.sourceBalanceID < sourceBalanceID) return false;
if (maxPayoutAmount < other.maxPayoutAmount) return true;
if (other.maxPayoutAmount < maxPayoutAmount) return false;
if (minPayoutAmount < other.minPayoutAmount) return true;
if (other.minPayoutAmount < minPayoutAmount) return false;
if (minAssetHolderAmount < other.minAssetHolderAmount) return true;
if (other.minAssetHolderAmount < minAssetHolderAmount) return false;
if (fee < other.fee) return true;
if (other.fee < fee) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
PayoutResponse::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
PayoutResponse::_ext_t::to_bytes(xdr::marshaler& m) const
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
PayoutResponse::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
PayoutResponse::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
PayoutResponse::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
PayoutResponse::from_bytes(xdr::unmarshaler& u) 
{
bool okreceiverID = u.from_bytes(receiverID);
if (!okreceiverID)
{
return false;
}
bool okreceiverBalanceID = u.from_bytes(receiverBalanceID);
if (!okreceiverBalanceID)
{
return false;
}
bool okreceivedAmount = u.from_bytes(receivedAmount);
if (!okreceivedAmount)
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
PayoutResponse::to_bytes(xdr::marshaler& m) const 
{
bool okreceiverID = m.to_bytes(receiverID);
if (!okreceiverID)
{
return false;
}
bool okreceiverBalanceID = m.to_bytes(receiverBalanceID);
if (!okreceiverBalanceID)
{
return false;
}
bool okreceivedAmount = m.to_bytes(receivedAmount);
if (!okreceivedAmount)
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
PayoutResponse::count_size(xdr::measurer& m) const 
{
m.count_size(receiverID);
m.count_size(receiverBalanceID);
m.count_size(receivedAmount);
m.count_size(ext);
}
bool
PayoutResponse::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<PayoutResponse const&>(other_abstract);return true
&& (receiverID== other.receiverID)
&& (receiverBalanceID== other.receiverBalanceID)
&& (receivedAmount== other.receivedAmount)
&& (ext== other.ext)
;}
bool
PayoutResponse::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<PayoutResponse const&>(other_abstract);
if (receiverID < other.receiverID) return true;
if (other.receiverID < receiverID) return false;
if (receiverBalanceID < other.receiverBalanceID) return true;
if (other.receiverBalanceID < receiverBalanceID) return false;
if (receivedAmount < other.receivedAmount) return true;
if (other.receivedAmount < receivedAmount) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
PayoutSuccessResult::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
PayoutSuccessResult::_ext_t::to_bytes(xdr::marshaler& m) const
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
PayoutSuccessResult::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
PayoutSuccessResult::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
PayoutSuccessResult::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
PayoutSuccessResult::from_bytes(xdr::unmarshaler& u) 
{
bool okpayoutResponses = u.from_bytes(payoutResponses);
if (!okpayoutResponses)
{
return false;
}
bool okactualPayoutAmount = u.from_bytes(actualPayoutAmount);
if (!okactualPayoutAmount)
{
return false;
}
bool okactualFee = u.from_bytes(actualFee);
if (!okactualFee)
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
PayoutSuccessResult::to_bytes(xdr::marshaler& m) const 
{
bool okpayoutResponses = m.to_bytes(payoutResponses);
if (!okpayoutResponses)
{
return false;
}
bool okactualPayoutAmount = m.to_bytes(actualPayoutAmount);
if (!okactualPayoutAmount)
{
return false;
}
bool okactualFee = m.to_bytes(actualFee);
if (!okactualFee)
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
PayoutSuccessResult::count_size(xdr::measurer& m) const 
{
m.count_size(payoutResponses);
m.count_size(actualPayoutAmount);
m.count_size(actualFee);
m.count_size(ext);
}
bool
PayoutSuccessResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<PayoutSuccessResult const&>(other_abstract);return true
&& (payoutResponses== other.payoutResponses)
&& (actualPayoutAmount== other.actualPayoutAmount)
&& (actualFee== other.actualFee)
&& (ext== other.ext)
;}
bool
PayoutSuccessResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<PayoutSuccessResult const&>(other_abstract);
if (payoutResponses < other.payoutResponses) return true;
if (other.payoutResponses < payoutResponses) return false;
if (actualPayoutAmount < other.actualPayoutAmount) return true;
if (other.actualPayoutAmount < actualPayoutAmount) return false;
if (actualFee < other.actualFee) return true;
if (other.actualFee < actualFee) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
PayoutResult::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)PayoutResultCode::SUCCESS:
return u.from_bytes(success_);
  default:
    return true;
}
return false;
}
bool
PayoutResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)PayoutResultCode::SUCCESS:
return m.to_bytes(success_);
  default:
    return true;
}
return false;
}
void
PayoutResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)PayoutResultCode::SUCCESS:
return m.count_size(success_);
  default:
  
  return;
}
}
bool
PayoutResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<PayoutResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)PayoutResultCode::SUCCESS:
return success_ == other.success_;
  default:
  
  return true;
}
return false;
}
bool
PayoutResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<PayoutResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)PayoutResultCode::SUCCESS:
return success_ < other.success_;
  default:
    return false;
}
return false;
}
}