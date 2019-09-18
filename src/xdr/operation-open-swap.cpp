#include "operation-open-swap.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
OpenSwapOp::_destination_t::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (type_)
{
    case (int32_t)PaymentDestinationType::ACCOUNT:
return u.from_bytes(accountID_);
    case (int32_t)PaymentDestinationType::BALANCE:
return u.from_bytes(balanceID_);
}
return false;
}
bool
OpenSwapOp::_destination_t::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(type_);
if (!ok)
{
return false;
}
switch (type_)
{

    case (int32_t)PaymentDestinationType::ACCOUNT:
return m.to_bytes(accountID_);
    case (int32_t)PaymentDestinationType::BALANCE:
return m.to_bytes(balanceID_);
}
return false;
}
void
OpenSwapOp::_destination_t::count_size(xdr::measurer& m) const
{
m.count_size(type_);
switch (type_)
{

    case (int32_t)PaymentDestinationType::ACCOUNT:
return m.count_size(accountID_);
    case (int32_t)PaymentDestinationType::BALANCE:
return m.count_size(balanceID_);
}
}
bool
OpenSwapOp::_destination_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_destination_t const&>(other_abstract);
if (other.type_ != type_) return false;
switch (type_)
{
    case (int32_t)PaymentDestinationType::ACCOUNT:
return accountID_ == other.accountID_;
    case (int32_t)PaymentDestinationType::BALANCE:
return balanceID_ == other.balanceID_;
}
return false;
}
bool
OpenSwapOp::_destination_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_destination_t const&>(other_abstract);
if (type_ < other.type_) return true;
if (other.type_ < type_) return false;
switch (type_)
{
    case (int32_t)PaymentDestinationType::ACCOUNT:
return accountID_ < other.accountID_;
    case (int32_t)PaymentDestinationType::BALANCE:
return balanceID_ < other.balanceID_;
}
return false;
}
bool
OpenSwapOp::from_bytes(xdr::unmarshaler& u) 
{
bool oksourceBalance = u.from_bytes(sourceBalance);
if (!oksourceBalance)
{
return false;
}
bool okamount = u.from_bytes(amount);
if (!okamount)
{
return false;
}
bool okdestination = u.from_bytes(destination);
if (!okdestination)
{
return false;
}
bool okfeeData = u.from_bytes(feeData);
if (!okfeeData)
{
return false;
}
bool okdetails = u.from_bytes(details);
if (!okdetails)
{
return false;
}
bool oksecretHash = u.from_bytes(secretHash);
if (!oksecretHash)
{
return false;
}
bool oklockTime = u.from_bytes(lockTime);
if (!oklockTime)
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
OpenSwapOp::to_bytes(xdr::marshaler& m) const 
{
bool oksourceBalance = m.to_bytes(sourceBalance);
if (!oksourceBalance)
{
return false;
}
bool okamount = m.to_bytes(amount);
if (!okamount)
{
return false;
}
bool okdestination = m.to_bytes(destination);
if (!okdestination)
{
return false;
}
bool okfeeData = m.to_bytes(feeData);
if (!okfeeData)
{
return false;
}
bool okdetails = m.to_bytes(details);
if (!okdetails)
{
return false;
}
bool oksecretHash = m.to_bytes(secretHash);
if (!oksecretHash)
{
return false;
}
bool oklockTime = m.to_bytes(lockTime);
if (!oklockTime)
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
OpenSwapOp::count_size(xdr::measurer& m) const 
{
m.count_size(sourceBalance);
m.count_size(amount);
m.count_size(destination);
m.count_size(feeData);
m.count_size(details);
m.count_size(secretHash);
m.count_size(lockTime);
m.count_size(ext);
}
bool
OpenSwapOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<OpenSwapOp const&>(other_abstract);return true
&& (sourceBalance== other.sourceBalance)
&& (amount== other.amount)
&& (destination== other.destination)
&& (feeData== other.feeData)
&& (details== other.details)
&& (secretHash== other.secretHash)
&& (lockTime== other.lockTime)
&& (ext== other.ext)
;}
bool
OpenSwapOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<OpenSwapOp const&>(other_abstract);
if (sourceBalance < other.sourceBalance) return true;
if (other.sourceBalance < sourceBalance) return false;
if (amount < other.amount) return true;
if (other.amount < amount) return false;
if (destination < other.destination) return true;
if (other.destination < destination) return false;
if (feeData < other.feeData) return true;
if (other.feeData < feeData) return false;
if (details < other.details) return true;
if (other.details < details) return false;
if (secretHash < other.secretHash) return true;
if (other.secretHash < secretHash) return false;
if (lockTime < other.lockTime) return true;
if (other.lockTime < lockTime) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
OpenSwapSuccess::from_bytes(xdr::unmarshaler& u) 
{
bool okswapID = u.from_bytes(swapID);
if (!okswapID)
{
return false;
}
bool okdestination = u.from_bytes(destination);
if (!okdestination)
{
return false;
}
bool okdestinationBalance = u.from_bytes(destinationBalance);
if (!okdestinationBalance)
{
return false;
}
bool okasset = u.from_bytes(asset);
if (!okasset)
{
return false;
}
bool okactualSourceFee = u.from_bytes(actualSourceFee);
if (!okactualSourceFee)
{
return false;
}
bool okactualDestinationFee = u.from_bytes(actualDestinationFee);
if (!okactualDestinationFee)
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
OpenSwapSuccess::to_bytes(xdr::marshaler& m) const 
{
bool okswapID = m.to_bytes(swapID);
if (!okswapID)
{
return false;
}
bool okdestination = m.to_bytes(destination);
if (!okdestination)
{
return false;
}
bool okdestinationBalance = m.to_bytes(destinationBalance);
if (!okdestinationBalance)
{
return false;
}
bool okasset = m.to_bytes(asset);
if (!okasset)
{
return false;
}
bool okactualSourceFee = m.to_bytes(actualSourceFee);
if (!okactualSourceFee)
{
return false;
}
bool okactualDestinationFee = m.to_bytes(actualDestinationFee);
if (!okactualDestinationFee)
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
OpenSwapSuccess::count_size(xdr::measurer& m) const 
{
m.count_size(swapID);
m.count_size(destination);
m.count_size(destinationBalance);
m.count_size(asset);
m.count_size(actualSourceFee);
m.count_size(actualDestinationFee);
m.count_size(ext);
}
bool
OpenSwapSuccess::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<OpenSwapSuccess const&>(other_abstract);return true
&& (swapID== other.swapID)
&& (destination== other.destination)
&& (destinationBalance== other.destinationBalance)
&& (asset== other.asset)
&& (actualSourceFee== other.actualSourceFee)
&& (actualDestinationFee== other.actualDestinationFee)
&& (ext== other.ext)
;}
bool
OpenSwapSuccess::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<OpenSwapSuccess const&>(other_abstract);
if (swapID < other.swapID) return true;
if (other.swapID < swapID) return false;
if (destination < other.destination) return true;
if (other.destination < destination) return false;
if (destinationBalance < other.destinationBalance) return true;
if (other.destinationBalance < destinationBalance) return false;
if (asset < other.asset) return true;
if (other.asset < asset) return false;
if (actualSourceFee < other.actualSourceFee) return true;
if (other.actualSourceFee < actualSourceFee) return false;
if (actualDestinationFee < other.actualDestinationFee) return true;
if (other.actualDestinationFee < actualDestinationFee) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
OpenSwapResult::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (code_)
{
  case (int32_t)OpenSwapResultCode::SUCCESS:
return u.from_bytes(success_);
  default:
  
  return true;
}
return false;
}
bool
OpenSwapResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)OpenSwapResultCode::SUCCESS:
return m.to_bytes(success_);
  default:
    return true;
}
return false;
}
void
OpenSwapResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)OpenSwapResultCode::SUCCESS:
return m.count_size(success_);
  default:
  
  return;
}
}
bool
OpenSwapResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<OpenSwapResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)OpenSwapResultCode::SUCCESS:
return success_ == other.success_;
  default:
  
  return true;
}
return false;
}
bool
OpenSwapResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<OpenSwapResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)OpenSwapResultCode::SUCCESS:
return success_ < other.success_;
  default:
    return false;
}
return false;
}
}