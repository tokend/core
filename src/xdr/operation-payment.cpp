#include "operation-payment.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
PaymentFeeData::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
PaymentFeeData::_ext_t::to_bytes(xdr::marshaler& m) const
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
PaymentFeeData::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
PaymentFeeData::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
PaymentFeeData::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
PaymentFeeData::from_bytes(xdr::unmarshaler& u) 
{
bool oksourceFee = u.from_bytes(sourceFee);
if (!oksourceFee)
{
return false;
}
bool okdestinationFee = u.from_bytes(destinationFee);
if (!okdestinationFee)
{
return false;
}
bool oksourcePaysForDest = u.from_bytes(sourcePaysForDest);
if (!oksourcePaysForDest)
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
PaymentFeeData::to_bytes(xdr::marshaler& m) const 
{
bool oksourceFee = m.to_bytes(sourceFee);
if (!oksourceFee)
{
return false;
}
bool okdestinationFee = m.to_bytes(destinationFee);
if (!okdestinationFee)
{
return false;
}
bool oksourcePaysForDest = m.to_bytes(sourcePaysForDest);
if (!oksourcePaysForDest)
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
PaymentFeeData::count_size(xdr::measurer& m) const 
{
m.count_size(sourceFee);
m.count_size(destinationFee);
m.count_size(sourcePaysForDest);
m.count_size(ext);
}
bool
PaymentFeeData::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<PaymentFeeData const&>(other_abstract);return true
&& (sourceFee== other.sourceFee)
&& (destinationFee== other.destinationFee)
&& (sourcePaysForDest== other.sourcePaysForDest)
&& (ext== other.ext)
;}
bool
PaymentFeeData::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<PaymentFeeData const&>(other_abstract);
if (sourceFee < other.sourceFee) return true;
if (other.sourceFee < sourceFee) return false;
if (destinationFee < other.destinationFee) return true;
if (other.destinationFee < destinationFee) return false;
if (sourcePaysForDest < other.sourcePaysForDest) return true;
if (other.sourcePaysForDest < sourcePaysForDest) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
PaymentOp::_destination_t::from_bytes(xdr::unmarshaler& u) 
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
PaymentOp::_destination_t::to_bytes(xdr::marshaler& m) const
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
PaymentOp::_destination_t::count_size(xdr::measurer& m) const
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
PaymentOp::_destination_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
PaymentOp::_destination_t::operator<(xdr_abstract const& other_abstract) const
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
PaymentOp::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
PaymentOp::_ext_t::to_bytes(xdr::marshaler& m) const
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
PaymentOp::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
PaymentOp::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
PaymentOp::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
PaymentOp::from_bytes(xdr::unmarshaler& u) 
{
bool oksourceBalanceID = u.from_bytes(sourceBalanceID);
if (!oksourceBalanceID)
{
return false;
}
bool okdestination = u.from_bytes(destination);
if (!okdestination)
{
return false;
}
bool okamount = u.from_bytes(amount);
if (!okamount)
{
return false;
}
bool okfeeData = u.from_bytes(feeData);
if (!okfeeData)
{
return false;
}
bool oksubject = u.from_bytes(subject);
if (!oksubject)
{
return false;
}
bool okreference = u.from_bytes(reference);
if (!okreference)
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
PaymentOp::to_bytes(xdr::marshaler& m) const 
{
bool oksourceBalanceID = m.to_bytes(sourceBalanceID);
if (!oksourceBalanceID)
{
return false;
}
bool okdestination = m.to_bytes(destination);
if (!okdestination)
{
return false;
}
bool okamount = m.to_bytes(amount);
if (!okamount)
{
return false;
}
bool okfeeData = m.to_bytes(feeData);
if (!okfeeData)
{
return false;
}
bool oksubject = m.to_bytes(subject);
if (!oksubject)
{
return false;
}
bool okreference = m.to_bytes(reference);
if (!okreference)
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
PaymentOp::count_size(xdr::measurer& m) const 
{
m.count_size(sourceBalanceID);
m.count_size(destination);
m.count_size(amount);
m.count_size(feeData);
m.count_size(subject);
m.count_size(reference);
m.count_size(ext);
}
bool
PaymentOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<PaymentOp const&>(other_abstract);return true
&& (sourceBalanceID== other.sourceBalanceID)
&& (destination== other.destination)
&& (amount== other.amount)
&& (feeData== other.feeData)
&& (subject== other.subject)
&& (reference== other.reference)
&& (ext== other.ext)
;}
bool
PaymentOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<PaymentOp const&>(other_abstract);
if (sourceBalanceID < other.sourceBalanceID) return true;
if (other.sourceBalanceID < sourceBalanceID) return false;
if (destination < other.destination) return true;
if (other.destination < destination) return false;
if (amount < other.amount) return true;
if (other.amount < amount) return false;
if (feeData < other.feeData) return true;
if (other.feeData < feeData) return false;
if (subject < other.subject) return true;
if (other.subject < subject) return false;
if (reference < other.reference) return true;
if (other.reference < reference) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
PaymentResponse::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
PaymentResponse::_ext_t::to_bytes(xdr::marshaler& m) const
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
PaymentResponse::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
PaymentResponse::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
PaymentResponse::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
PaymentResponse::from_bytes(xdr::unmarshaler& u) 
{
bool okdestination = u.from_bytes(destination);
if (!okdestination)
{
return false;
}
bool okdestinationBalanceID = u.from_bytes(destinationBalanceID);
if (!okdestinationBalanceID)
{
return false;
}
bool okasset = u.from_bytes(asset);
if (!okasset)
{
return false;
}
bool oksourceSentUniversal = u.from_bytes(sourceSentUniversal);
if (!oksourceSentUniversal)
{
return false;
}
bool okpaymentID = u.from_bytes(paymentID);
if (!okpaymentID)
{
return false;
}
bool okactualSourcePaymentFee = u.from_bytes(actualSourcePaymentFee);
if (!okactualSourcePaymentFee)
{
return false;
}
bool okactualDestinationPaymentFee = u.from_bytes(actualDestinationPaymentFee);
if (!okactualDestinationPaymentFee)
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
PaymentResponse::to_bytes(xdr::marshaler& m) const 
{
bool okdestination = m.to_bytes(destination);
if (!okdestination)
{
return false;
}
bool okdestinationBalanceID = m.to_bytes(destinationBalanceID);
if (!okdestinationBalanceID)
{
return false;
}
bool okasset = m.to_bytes(asset);
if (!okasset)
{
return false;
}
bool oksourceSentUniversal = m.to_bytes(sourceSentUniversal);
if (!oksourceSentUniversal)
{
return false;
}
bool okpaymentID = m.to_bytes(paymentID);
if (!okpaymentID)
{
return false;
}
bool okactualSourcePaymentFee = m.to_bytes(actualSourcePaymentFee);
if (!okactualSourcePaymentFee)
{
return false;
}
bool okactualDestinationPaymentFee = m.to_bytes(actualDestinationPaymentFee);
if (!okactualDestinationPaymentFee)
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
PaymentResponse::count_size(xdr::measurer& m) const 
{
m.count_size(destination);
m.count_size(destinationBalanceID);
m.count_size(asset);
m.count_size(sourceSentUniversal);
m.count_size(paymentID);
m.count_size(actualSourcePaymentFee);
m.count_size(actualDestinationPaymentFee);
m.count_size(ext);
}
bool
PaymentResponse::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<PaymentResponse const&>(other_abstract);return true
&& (destination== other.destination)
&& (destinationBalanceID== other.destinationBalanceID)
&& (asset== other.asset)
&& (sourceSentUniversal== other.sourceSentUniversal)
&& (paymentID== other.paymentID)
&& (actualSourcePaymentFee== other.actualSourcePaymentFee)
&& (actualDestinationPaymentFee== other.actualDestinationPaymentFee)
&& (ext== other.ext)
;}
bool
PaymentResponse::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<PaymentResponse const&>(other_abstract);
if (destination < other.destination) return true;
if (other.destination < destination) return false;
if (destinationBalanceID < other.destinationBalanceID) return true;
if (other.destinationBalanceID < destinationBalanceID) return false;
if (asset < other.asset) return true;
if (other.asset < asset) return false;
if (sourceSentUniversal < other.sourceSentUniversal) return true;
if (other.sourceSentUniversal < sourceSentUniversal) return false;
if (paymentID < other.paymentID) return true;
if (other.paymentID < paymentID) return false;
if (actualSourcePaymentFee < other.actualSourcePaymentFee) return true;
if (other.actualSourcePaymentFee < actualSourcePaymentFee) return false;
if (actualDestinationPaymentFee < other.actualDestinationPaymentFee) return true;
if (other.actualDestinationPaymentFee < actualDestinationPaymentFee) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
PaymentResult::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (code_)
{
  case (int32_t)PaymentResultCode::SUCCESS:
return u.from_bytes(paymentResponse_);
  default:
  
  return true;
}
return false;
}
bool
PaymentResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)PaymentResultCode::SUCCESS:
return m.to_bytes(paymentResponse_);
  default:
    return true;
}
return false;
}
void
PaymentResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)PaymentResultCode::SUCCESS:
return m.count_size(paymentResponse_);
  default:
  
  return;
}
}
bool
PaymentResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<PaymentResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)PaymentResultCode::SUCCESS:
return paymentResponse_ == other.paymentResponse_;
  default:
  
  return true;
}
return false;
}
bool
PaymentResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<PaymentResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)PaymentResultCode::SUCCESS:
return paymentResponse_ < other.paymentResponse_;
  default:
    return false;
}
return false;
}
}