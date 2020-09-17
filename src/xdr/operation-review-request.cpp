#include "operation-review-request.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
LimitsUpdateDetails::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
LimitsUpdateDetails::_ext_t::to_bytes(xdr::marshaler& m) const
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
LimitsUpdateDetails::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
LimitsUpdateDetails::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
LimitsUpdateDetails::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
LimitsUpdateDetails::from_bytes(xdr::unmarshaler& u) 
{
bool oknewLimitsV2 = u.from_bytes(newLimitsV2);
if (!oknewLimitsV2)
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
LimitsUpdateDetails::to_bytes(xdr::marshaler& m) const 
{
bool oknewLimitsV2 = m.to_bytes(newLimitsV2);
if (!oknewLimitsV2)
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
LimitsUpdateDetails::count_size(xdr::measurer& m) const 
{
m.count_size(newLimitsV2);
m.count_size(ext);
}
bool
LimitsUpdateDetails::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<LimitsUpdateDetails const&>(other_abstract);return true
&& (newLimitsV2== other.newLimitsV2)
&& (ext== other.ext)
;}
bool
LimitsUpdateDetails::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<LimitsUpdateDetails const&>(other_abstract);
if (newLimitsV2 < other.newLimitsV2) return true;
if (other.newLimitsV2 < newLimitsV2) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
WithdrawalDetails::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
WithdrawalDetails::_ext_t::to_bytes(xdr::marshaler& m) const
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
WithdrawalDetails::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
WithdrawalDetails::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
WithdrawalDetails::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
WithdrawalDetails::from_bytes(xdr::unmarshaler& u) 
{
bool okexternalDetails = u.from_bytes(externalDetails);
if (!okexternalDetails)
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
WithdrawalDetails::to_bytes(xdr::marshaler& m) const 
{
bool okexternalDetails = m.to_bytes(externalDetails);
if (!okexternalDetails)
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
WithdrawalDetails::count_size(xdr::measurer& m) const 
{
m.count_size(externalDetails);
m.count_size(ext);
}
bool
WithdrawalDetails::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<WithdrawalDetails const&>(other_abstract);return true
&& (externalDetails== other.externalDetails)
&& (ext== other.ext)
;}
bool
WithdrawalDetails::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<WithdrawalDetails const&>(other_abstract);
if (externalDetails < other.externalDetails) return true;
if (other.externalDetails < externalDetails) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
AMLAlertDetails::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
AMLAlertDetails::_ext_t::to_bytes(xdr::marshaler& m) const
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
AMLAlertDetails::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
AMLAlertDetails::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
AMLAlertDetails::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
AMLAlertDetails::from_bytes(xdr::unmarshaler& u) 
{
bool okcomment = u.from_bytes(comment);
if (!okcomment)
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
AMLAlertDetails::to_bytes(xdr::marshaler& m) const 
{
bool okcomment = m.to_bytes(comment);
if (!okcomment)
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
AMLAlertDetails::count_size(xdr::measurer& m) const 
{
m.count_size(comment);
m.count_size(ext);
}
bool
AMLAlertDetails::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<AMLAlertDetails const&>(other_abstract);return true
&& (comment== other.comment)
&& (ext== other.ext)
;}
bool
AMLAlertDetails::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<AMLAlertDetails const&>(other_abstract);
if (comment < other.comment) return true;
if (other.comment < comment) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ContractDetails::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ContractDetails::_ext_t::to_bytes(xdr::marshaler& m) const
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
ContractDetails::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
ContractDetails::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ContractDetails::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ContractDetails::from_bytes(xdr::unmarshaler& u) 
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
ContractDetails::to_bytes(xdr::marshaler& m) const 
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
ContractDetails::count_size(xdr::measurer& m) const 
{
m.count_size(details);
m.count_size(ext);
}
bool
ContractDetails::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<ContractDetails const&>(other_abstract);return true
&& (details== other.details)
&& (ext== other.ext)
;}
bool
ContractDetails::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ContractDetails const&>(other_abstract);
if (details < other.details) return true;
if (other.details < details) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
BillPayDetails::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
BillPayDetails::_ext_t::to_bytes(xdr::marshaler& m) const
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
BillPayDetails::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
BillPayDetails::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
BillPayDetails::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
BillPayDetails::from_bytes(xdr::unmarshaler& u) 
{
bool okpaymentDetails = u.from_bytes(paymentDetails);
if (!okpaymentDetails)
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
BillPayDetails::to_bytes(xdr::marshaler& m) const 
{
bool okpaymentDetails = m.to_bytes(paymentDetails);
if (!okpaymentDetails)
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
BillPayDetails::count_size(xdr::measurer& m) const 
{
m.count_size(paymentDetails);
m.count_size(ext);
}
bool
BillPayDetails::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<BillPayDetails const&>(other_abstract);return true
&& (paymentDetails== other.paymentDetails)
&& (ext== other.ext)
;}
bool
BillPayDetails::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<BillPayDetails const&>(other_abstract);
if (paymentDetails < other.paymentDetails) return true;
if (other.paymentDetails < paymentDetails) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ReviewDetails::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ReviewDetails::_ext_t::to_bytes(xdr::marshaler& m) const
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
ReviewDetails::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
ReviewDetails::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ReviewDetails::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ReviewDetails::from_bytes(xdr::unmarshaler& u) 
{
bool oktasksToAdd = u.from_bytes(tasksToAdd);
if (!oktasksToAdd)
{
return false;
}
bool oktasksToRemove = u.from_bytes(tasksToRemove);
if (!oktasksToRemove)
{
return false;
}
bool okexternalDetails = u.from_bytes(externalDetails);
if (!okexternalDetails)
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
ReviewDetails::to_bytes(xdr::marshaler& m) const 
{
bool oktasksToAdd = m.to_bytes(tasksToAdd);
if (!oktasksToAdd)
{
return false;
}
bool oktasksToRemove = m.to_bytes(tasksToRemove);
if (!oktasksToRemove)
{
return false;
}
bool okexternalDetails = m.to_bytes(externalDetails);
if (!okexternalDetails)
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
ReviewDetails::count_size(xdr::measurer& m) const 
{
m.count_size(tasksToAdd);
m.count_size(tasksToRemove);
m.count_size(externalDetails);
m.count_size(ext);
}
bool
ReviewDetails::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<ReviewDetails const&>(other_abstract);return true
&& (tasksToAdd== other.tasksToAdd)
&& (tasksToRemove== other.tasksToRemove)
&& (externalDetails== other.externalDetails)
&& (ext== other.ext)
;}
bool
ReviewDetails::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ReviewDetails const&>(other_abstract);
if (tasksToAdd < other.tasksToAdd) return true;
if (other.tasksToAdd < tasksToAdd) return false;
if (tasksToRemove < other.tasksToRemove) return true;
if (other.tasksToRemove < tasksToRemove) return false;
if (externalDetails < other.externalDetails) return true;
if (other.externalDetails < externalDetails) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
SaleExtended::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
SaleExtended::_ext_t::to_bytes(xdr::marshaler& m) const
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
SaleExtended::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
SaleExtended::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
SaleExtended::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
SaleExtended::from_bytes(xdr::unmarshaler& u) 
{
bool oksaleID = u.from_bytes(saleID);
if (!oksaleID)
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
SaleExtended::to_bytes(xdr::marshaler& m) const 
{
bool oksaleID = m.to_bytes(saleID);
if (!oksaleID)
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
SaleExtended::count_size(xdr::measurer& m) const 
{
m.count_size(saleID);
m.count_size(ext);
}
bool
SaleExtended::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<SaleExtended const&>(other_abstract);return true
&& (saleID== other.saleID)
&& (ext== other.ext)
;}
bool
SaleExtended::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<SaleExtended const&>(other_abstract);
if (saleID < other.saleID) return true;
if (other.saleID < saleID) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
AtomicSwapAskExtended::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
AtomicSwapAskExtended::_ext_t::to_bytes(xdr::marshaler& m) const
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
AtomicSwapAskExtended::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
AtomicSwapAskExtended::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
AtomicSwapAskExtended::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
AtomicSwapAskExtended::from_bytes(xdr::unmarshaler& u) 
{
bool okaskID = u.from_bytes(askID);
if (!okaskID)
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
AtomicSwapAskExtended::to_bytes(xdr::marshaler& m) const 
{
bool okaskID = m.to_bytes(askID);
if (!okaskID)
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
AtomicSwapAskExtended::count_size(xdr::measurer& m) const 
{
m.count_size(askID);
m.count_size(ext);
}
bool
AtomicSwapAskExtended::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<AtomicSwapAskExtended const&>(other_abstract);return true
&& (askID== other.askID)
&& (ext== other.ext)
;}
bool
AtomicSwapAskExtended::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<AtomicSwapAskExtended const&>(other_abstract);
if (askID < other.askID) return true;
if (other.askID < askID) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
CreatePollExtended::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
CreatePollExtended::_ext_t::to_bytes(xdr::marshaler& m) const
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
CreatePollExtended::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
CreatePollExtended::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
CreatePollExtended::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
CreatePollExtended::from_bytes(xdr::unmarshaler& u) 
{
bool okpollID = u.from_bytes(pollID);
if (!okpollID)
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
CreatePollExtended::to_bytes(xdr::marshaler& m) const 
{
bool okpollID = m.to_bytes(pollID);
if (!okpollID)
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
CreatePollExtended::count_size(xdr::measurer& m) const 
{
m.count_size(pollID);
m.count_size(ext);
}
bool
CreatePollExtended::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CreatePollExtended const&>(other_abstract);return true
&& (pollID== other.pollID)
&& (ext== other.ext)
;}
bool
CreatePollExtended::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreatePollExtended const&>(other_abstract);
if (pollID < other.pollID) return true;
if (other.pollID < pollID) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
AtomicSwapBidExtended::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
AtomicSwapBidExtended::_ext_t::to_bytes(xdr::marshaler& m) const
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
AtomicSwapBidExtended::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
AtomicSwapBidExtended::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
AtomicSwapBidExtended::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
AtomicSwapBidExtended::from_bytes(xdr::unmarshaler& u) 
{
bool okaskID = u.from_bytes(askID);
if (!okaskID)
{
return false;
}
bool okaskOwnerID = u.from_bytes(askOwnerID);
if (!okaskOwnerID)
{
return false;
}
bool okbidOwnerID = u.from_bytes(bidOwnerID);
if (!okbidOwnerID)
{
return false;
}
bool okbaseAsset = u.from_bytes(baseAsset);
if (!okbaseAsset)
{
return false;
}
bool okquoteAsset = u.from_bytes(quoteAsset);
if (!okquoteAsset)
{
return false;
}
bool okbaseAmount = u.from_bytes(baseAmount);
if (!okbaseAmount)
{
return false;
}
bool okquoteAmount = u.from_bytes(quoteAmount);
if (!okquoteAmount)
{
return false;
}
bool okprice = u.from_bytes(price);
if (!okprice)
{
return false;
}
bool okaskOwnerBaseBalanceID = u.from_bytes(askOwnerBaseBalanceID);
if (!okaskOwnerBaseBalanceID)
{
return false;
}
bool okbidOwnerBaseBalanceID = u.from_bytes(bidOwnerBaseBalanceID);
if (!okbidOwnerBaseBalanceID)
{
return false;
}
bool okunlockedAmount = u.from_bytes(unlockedAmount);
if (!okunlockedAmount)
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
AtomicSwapBidExtended::to_bytes(xdr::marshaler& m) const 
{
bool okaskID = m.to_bytes(askID);
if (!okaskID)
{
return false;
}
bool okaskOwnerID = m.to_bytes(askOwnerID);
if (!okaskOwnerID)
{
return false;
}
bool okbidOwnerID = m.to_bytes(bidOwnerID);
if (!okbidOwnerID)
{
return false;
}
bool okbaseAsset = m.to_bytes(baseAsset);
if (!okbaseAsset)
{
return false;
}
bool okquoteAsset = m.to_bytes(quoteAsset);
if (!okquoteAsset)
{
return false;
}
bool okbaseAmount = m.to_bytes(baseAmount);
if (!okbaseAmount)
{
return false;
}
bool okquoteAmount = m.to_bytes(quoteAmount);
if (!okquoteAmount)
{
return false;
}
bool okprice = m.to_bytes(price);
if (!okprice)
{
return false;
}
bool okaskOwnerBaseBalanceID = m.to_bytes(askOwnerBaseBalanceID);
if (!okaskOwnerBaseBalanceID)
{
return false;
}
bool okbidOwnerBaseBalanceID = m.to_bytes(bidOwnerBaseBalanceID);
if (!okbidOwnerBaseBalanceID)
{
return false;
}
bool okunlockedAmount = m.to_bytes(unlockedAmount);
if (!okunlockedAmount)
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
AtomicSwapBidExtended::count_size(xdr::measurer& m) const 
{
m.count_size(askID);
m.count_size(askOwnerID);
m.count_size(bidOwnerID);
m.count_size(baseAsset);
m.count_size(quoteAsset);
m.count_size(baseAmount);
m.count_size(quoteAmount);
m.count_size(price);
m.count_size(askOwnerBaseBalanceID);
m.count_size(bidOwnerBaseBalanceID);
m.count_size(unlockedAmount);
m.count_size(ext);
}
bool
AtomicSwapBidExtended::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<AtomicSwapBidExtended const&>(other_abstract);return true
&& (askID== other.askID)
&& (askOwnerID== other.askOwnerID)
&& (bidOwnerID== other.bidOwnerID)
&& (baseAsset== other.baseAsset)
&& (quoteAsset== other.quoteAsset)
&& (baseAmount== other.baseAmount)
&& (quoteAmount== other.quoteAmount)
&& (price== other.price)
&& (askOwnerBaseBalanceID== other.askOwnerBaseBalanceID)
&& (bidOwnerBaseBalanceID== other.bidOwnerBaseBalanceID)
&& (unlockedAmount== other.unlockedAmount)
&& (ext== other.ext)
;}
bool
AtomicSwapBidExtended::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<AtomicSwapBidExtended const&>(other_abstract);
if (askID < other.askID) return true;
if (other.askID < askID) return false;
if (askOwnerID < other.askOwnerID) return true;
if (other.askOwnerID < askOwnerID) return false;
if (bidOwnerID < other.bidOwnerID) return true;
if (other.bidOwnerID < bidOwnerID) return false;
if (baseAsset < other.baseAsset) return true;
if (other.baseAsset < baseAsset) return false;
if (quoteAsset < other.quoteAsset) return true;
if (other.quoteAsset < quoteAsset) return false;
if (baseAmount < other.baseAmount) return true;
if (other.baseAmount < baseAmount) return false;
if (quoteAmount < other.quoteAmount) return true;
if (other.quoteAmount < quoteAmount) return false;
if (price < other.price) return true;
if (other.price < price) return false;
if (askOwnerBaseBalanceID < other.askOwnerBaseBalanceID) return true;
if (other.askOwnerBaseBalanceID < askOwnerBaseBalanceID) return false;
if (bidOwnerBaseBalanceID < other.bidOwnerBaseBalanceID) return true;
if (other.bidOwnerBaseBalanceID < bidOwnerBaseBalanceID) return false;
if (unlockedAmount < other.unlockedAmount) return true;
if (other.unlockedAmount < unlockedAmount) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
CreateDeferredPaymentResult::from_bytes(xdr::unmarshaler& u) 
{
bool okdeferredPaymentID = u.from_bytes(deferredPaymentID);
if (!okdeferredPaymentID)
{
return false;
}
bool okdestination = u.from_bytes(destination);
if (!okdestination)
{
return false;
}
bool oksource = u.from_bytes(source);
if (!oksource)
{
return false;
}
bool oktotalFee = u.from_bytes(totalFee);
if (!oktotalFee)
{
return false;
}
bool oktotalAmount = u.from_bytes(totalAmount);
if (!oktotalAmount)
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
CreateDeferredPaymentResult::to_bytes(xdr::marshaler& m) const 
{
bool okdeferredPaymentID = m.to_bytes(deferredPaymentID);
if (!okdeferredPaymentID)
{
return false;
}
bool okdestination = m.to_bytes(destination);
if (!okdestination)
{
return false;
}
bool oksource = m.to_bytes(source);
if (!oksource)
{
return false;
}
bool oktotalFee = m.to_bytes(totalFee);
if (!oktotalFee)
{
return false;
}
bool oktotalAmount = m.to_bytes(totalAmount);
if (!oktotalAmount)
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
CreateDeferredPaymentResult::count_size(xdr::measurer& m) const 
{
m.count_size(deferredPaymentID);
m.count_size(destination);
m.count_size(source);
m.count_size(totalFee);
m.count_size(totalAmount);
m.count_size(ext);
}
bool
CreateDeferredPaymentResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CreateDeferredPaymentResult const&>(other_abstract);return true
&& (deferredPaymentID== other.deferredPaymentID)
&& (destination== other.destination)
&& (source== other.source)
&& (totalFee== other.totalFee)
&& (totalAmount== other.totalAmount)
&& (ext== other.ext)
;}
bool
CreateDeferredPaymentResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreateDeferredPaymentResult const&>(other_abstract);
if (deferredPaymentID < other.deferredPaymentID) return true;
if (other.deferredPaymentID < deferredPaymentID) return false;
if (destination < other.destination) return true;
if (other.destination < destination) return false;
if (source < other.source) return true;
if (other.source < source) return false;
if (totalFee < other.totalFee) return true;
if (other.totalFee < totalFee) return false;
if (totalAmount < other.totalAmount) return true;
if (other.totalAmount < totalAmount) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
DataCreationExtended::from_bytes(xdr::unmarshaler& u) 
{
bool okowner = u.from_bytes(owner);
if (!okowner)
{
return false;
}
bool okid = u.from_bytes(id);
if (!okid)
{
return false;
}
bool oktype = u.from_bytes(type);
if (!oktype)
{
return false;
}
return true;
}
bool
DataCreationExtended::to_bytes(xdr::marshaler& m) const 
{
bool okowner = m.to_bytes(owner);
if (!okowner)
{
return false;
}
bool okid = m.to_bytes(id);
if (!okid)
{
return false;
}
bool oktype = m.to_bytes(type);
if (!oktype)
{
return false;
}
return true;
}
void
DataCreationExtended::count_size(xdr::measurer& m) const 
{
m.count_size(owner);
m.count_size(id);
m.count_size(type);
}
bool
DataCreationExtended::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<DataCreationExtended const&>(other_abstract);return true
&& (owner== other.owner)
&& (id== other.id)
&& (type== other.type)
;}
bool
DataCreationExtended::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<DataCreationExtended const&>(other_abstract);
if (owner < other.owner) return true;
if (other.owner < owner) return false;
if (id < other.id) return true;
if (other.id < id) return false;
if (type < other.type) return true;
if (other.type < type) return false;
return false;
}bool
ExtendedResult::_typeExt_t::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (requestType_)
{
    case (int32_t)ReviewableRequestType::CREATE_SALE:
return u.from_bytes(saleExtended_);
    case (int32_t)ReviewableRequestType::NONE:
    
  return true;
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
return u.from_bytes(atomicSwapBidExtended_);
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
return u.from_bytes(atomicSwapAskExtended_);
    case (int32_t)ReviewableRequestType::CREATE_POLL:
return u.from_bytes(createPoll_);
    case (int32_t)ReviewableRequestType::MANAGE_OFFER:
return u.from_bytes(manageOfferResult_);
    case (int32_t)ReviewableRequestType::CREATE_PAYMENT:
return u.from_bytes(paymentResult_);
    case (int32_t)ReviewableRequestType::PERFORM_REDEMPTION:
return u.from_bytes(createRedemptionResult_);
    case (int32_t)ReviewableRequestType::DATA_CREATION:
return u.from_bytes(dataCreationExtended_);
    case (int32_t)ReviewableRequestType::CREATE_DEFERRED_PAYMENT:
return u.from_bytes(createDeferredPaymentResult_);
    case (int32_t)ReviewableRequestType::CLOSE_DEFERRED_PAYMENT:
return u.from_bytes(closeDeferredPaymentResult_);
}
return false;
}
bool
ExtendedResult::_typeExt_t::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(requestType_);
if (!ok)
{
return false;
}
switch (requestType_)
{

    case (int32_t)ReviewableRequestType::CREATE_SALE:
return m.to_bytes(saleExtended_);
    case (int32_t)ReviewableRequestType::NONE:
      return true;
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
return m.to_bytes(atomicSwapBidExtended_);
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
return m.to_bytes(atomicSwapAskExtended_);
    case (int32_t)ReviewableRequestType::CREATE_POLL:
return m.to_bytes(createPoll_);
    case (int32_t)ReviewableRequestType::MANAGE_OFFER:
return m.to_bytes(manageOfferResult_);
    case (int32_t)ReviewableRequestType::CREATE_PAYMENT:
return m.to_bytes(paymentResult_);
    case (int32_t)ReviewableRequestType::PERFORM_REDEMPTION:
return m.to_bytes(createRedemptionResult_);
    case (int32_t)ReviewableRequestType::DATA_CREATION:
return m.to_bytes(dataCreationExtended_);
    case (int32_t)ReviewableRequestType::CREATE_DEFERRED_PAYMENT:
return m.to_bytes(createDeferredPaymentResult_);
    case (int32_t)ReviewableRequestType::CLOSE_DEFERRED_PAYMENT:
return m.to_bytes(closeDeferredPaymentResult_);
}
return false;
}
void
ExtendedResult::_typeExt_t::count_size(xdr::measurer& m) const
{
m.count_size(requestType_);
switch (requestType_)
{

    case (int32_t)ReviewableRequestType::CREATE_SALE:
return m.count_size(saleExtended_);
    case (int32_t)ReviewableRequestType::NONE:
    
  return;
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
return m.count_size(atomicSwapBidExtended_);
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
return m.count_size(atomicSwapAskExtended_);
    case (int32_t)ReviewableRequestType::CREATE_POLL:
return m.count_size(createPoll_);
    case (int32_t)ReviewableRequestType::MANAGE_OFFER:
return m.count_size(manageOfferResult_);
    case (int32_t)ReviewableRequestType::CREATE_PAYMENT:
return m.count_size(paymentResult_);
    case (int32_t)ReviewableRequestType::PERFORM_REDEMPTION:
return m.count_size(createRedemptionResult_);
    case (int32_t)ReviewableRequestType::DATA_CREATION:
return m.count_size(dataCreationExtended_);
    case (int32_t)ReviewableRequestType::CREATE_DEFERRED_PAYMENT:
return m.count_size(createDeferredPaymentResult_);
    case (int32_t)ReviewableRequestType::CLOSE_DEFERRED_PAYMENT:
return m.count_size(closeDeferredPaymentResult_);
}
}
bool
ExtendedResult::_typeExt_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_typeExt_t const&>(other_abstract);
if (other.requestType_ != requestType_) return false;
switch (requestType_)
{
    case (int32_t)ReviewableRequestType::CREATE_SALE:
return saleExtended_ == other.saleExtended_;
    case (int32_t)ReviewableRequestType::NONE:
    
  return true;
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
return atomicSwapBidExtended_ == other.atomicSwapBidExtended_;
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
return atomicSwapAskExtended_ == other.atomicSwapAskExtended_;
    case (int32_t)ReviewableRequestType::CREATE_POLL:
return createPoll_ == other.createPoll_;
    case (int32_t)ReviewableRequestType::MANAGE_OFFER:
return manageOfferResult_ == other.manageOfferResult_;
    case (int32_t)ReviewableRequestType::CREATE_PAYMENT:
return paymentResult_ == other.paymentResult_;
    case (int32_t)ReviewableRequestType::PERFORM_REDEMPTION:
return createRedemptionResult_ == other.createRedemptionResult_;
    case (int32_t)ReviewableRequestType::DATA_CREATION:
return dataCreationExtended_ == other.dataCreationExtended_;
    case (int32_t)ReviewableRequestType::CREATE_DEFERRED_PAYMENT:
return createDeferredPaymentResult_ == other.createDeferredPaymentResult_;
    case (int32_t)ReviewableRequestType::CLOSE_DEFERRED_PAYMENT:
return closeDeferredPaymentResult_ == other.closeDeferredPaymentResult_;
}
return false;
}
bool
ExtendedResult::_typeExt_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_typeExt_t const&>(other_abstract);
if (requestType_ < other.requestType_) return true;
if (other.requestType_ < requestType_) return false;
switch (requestType_)
{
    case (int32_t)ReviewableRequestType::CREATE_SALE:
return saleExtended_ < other.saleExtended_;
    case (int32_t)ReviewableRequestType::NONE:
      return false;
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
return atomicSwapBidExtended_ < other.atomicSwapBidExtended_;
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
return atomicSwapAskExtended_ < other.atomicSwapAskExtended_;
    case (int32_t)ReviewableRequestType::CREATE_POLL:
return createPoll_ < other.createPoll_;
    case (int32_t)ReviewableRequestType::MANAGE_OFFER:
return manageOfferResult_ < other.manageOfferResult_;
    case (int32_t)ReviewableRequestType::CREATE_PAYMENT:
return paymentResult_ < other.paymentResult_;
    case (int32_t)ReviewableRequestType::PERFORM_REDEMPTION:
return createRedemptionResult_ < other.createRedemptionResult_;
    case (int32_t)ReviewableRequestType::DATA_CREATION:
return dataCreationExtended_ < other.dataCreationExtended_;
    case (int32_t)ReviewableRequestType::CREATE_DEFERRED_PAYMENT:
return createDeferredPaymentResult_ < other.createDeferredPaymentResult_;
    case (int32_t)ReviewableRequestType::CLOSE_DEFERRED_PAYMENT:
return closeDeferredPaymentResult_ < other.closeDeferredPaymentResult_;
}
return false;
}
bool
ExtendedResult::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ExtendedResult::_ext_t::to_bytes(xdr::marshaler& m) const
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
ExtendedResult::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
ExtendedResult::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ExtendedResult::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ExtendedResult::from_bytes(xdr::unmarshaler& u) 
{
bool okfulfilled = u.from_bytes(fulfilled);
if (!okfulfilled)
{
return false;
}
bool oktypeExt = u.from_bytes(typeExt);
if (!oktypeExt)
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
ExtendedResult::to_bytes(xdr::marshaler& m) const 
{
bool okfulfilled = m.to_bytes(fulfilled);
if (!okfulfilled)
{
return false;
}
bool oktypeExt = m.to_bytes(typeExt);
if (!oktypeExt)
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
ExtendedResult::count_size(xdr::measurer& m) const 
{
m.count_size(fulfilled);
m.count_size(typeExt);
m.count_size(ext);
}
bool
ExtendedResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<ExtendedResult const&>(other_abstract);return true
&& (fulfilled== other.fulfilled)
&& (typeExt== other.typeExt)
&& (ext== other.ext)
;}
bool
ExtendedResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ExtendedResult const&>(other_abstract);
if (fulfilled < other.fulfilled) return true;
if (other.fulfilled < fulfilled) return false;
if (typeExt < other.typeExt) return true;
if (other.typeExt < typeExt) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ReviewRequestOp::_requestDetails_t::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (requestType_)
{
    case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
return u.from_bytes(withdrawal_);
    case (int32_t)ReviewableRequestType::UPDATE_LIMITS:
return u.from_bytes(limitsUpdate_);
    case (int32_t)ReviewableRequestType::CREATE_AML_ALERT:
return u.from_bytes(amlAlertDetails_);
    case (int32_t)ReviewableRequestType::CREATE_INVOICE:
return u.from_bytes(billPay_);
    case (int32_t)ReviewableRequestType::MANAGE_CONTRACT:
return u.from_bytes(contract_);
    default:
    
  return true;
}
return false;
}
bool
ReviewRequestOp::_requestDetails_t::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(requestType_);
if (!ok)
{
return false;
}
switch (requestType_)
{

    case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
return m.to_bytes(withdrawal_);
    case (int32_t)ReviewableRequestType::UPDATE_LIMITS:
return m.to_bytes(limitsUpdate_);
    case (int32_t)ReviewableRequestType::CREATE_AML_ALERT:
return m.to_bytes(amlAlertDetails_);
    case (int32_t)ReviewableRequestType::CREATE_INVOICE:
return m.to_bytes(billPay_);
    case (int32_t)ReviewableRequestType::MANAGE_CONTRACT:
return m.to_bytes(contract_);
    default:
      return true;
}
return false;
}
void
ReviewRequestOp::_requestDetails_t::count_size(xdr::measurer& m) const
{
m.count_size(requestType_);
switch (requestType_)
{

    case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
return m.count_size(withdrawal_);
    case (int32_t)ReviewableRequestType::UPDATE_LIMITS:
return m.count_size(limitsUpdate_);
    case (int32_t)ReviewableRequestType::CREATE_AML_ALERT:
return m.count_size(amlAlertDetails_);
    case (int32_t)ReviewableRequestType::CREATE_INVOICE:
return m.count_size(billPay_);
    case (int32_t)ReviewableRequestType::MANAGE_CONTRACT:
return m.count_size(contract_);
    default:
    
  return;
}
}
bool
ReviewRequestOp::_requestDetails_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_requestDetails_t const&>(other_abstract);
if (other.requestType_ != requestType_) return false;
switch (requestType_)
{
    case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
return withdrawal_ == other.withdrawal_;
    case (int32_t)ReviewableRequestType::UPDATE_LIMITS:
return limitsUpdate_ == other.limitsUpdate_;
    case (int32_t)ReviewableRequestType::CREATE_AML_ALERT:
return amlAlertDetails_ == other.amlAlertDetails_;
    case (int32_t)ReviewableRequestType::CREATE_INVOICE:
return billPay_ == other.billPay_;
    case (int32_t)ReviewableRequestType::MANAGE_CONTRACT:
return contract_ == other.contract_;
    default:
    
  return true;
}
return false;
}
bool
ReviewRequestOp::_requestDetails_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_requestDetails_t const&>(other_abstract);
if (requestType_ < other.requestType_) return true;
if (other.requestType_ < requestType_) return false;
switch (requestType_)
{
    case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
return withdrawal_ < other.withdrawal_;
    case (int32_t)ReviewableRequestType::UPDATE_LIMITS:
return limitsUpdate_ < other.limitsUpdate_;
    case (int32_t)ReviewableRequestType::CREATE_AML_ALERT:
return amlAlertDetails_ < other.amlAlertDetails_;
    case (int32_t)ReviewableRequestType::CREATE_INVOICE:
return billPay_ < other.billPay_;
    case (int32_t)ReviewableRequestType::MANAGE_CONTRACT:
return contract_ < other.contract_;
    default:
      return false;
}
return false;
}
bool
ReviewRequestOp::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ReviewRequestOp::_ext_t::to_bytes(xdr::marshaler& m) const
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
ReviewRequestOp::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
ReviewRequestOp::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ReviewRequestOp::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ReviewRequestOp::from_bytes(xdr::unmarshaler& u) 
{
bool okrequestID = u.from_bytes(requestID);
if (!okrequestID)
{
return false;
}
bool okrequestHash = u.from_bytes(requestHash);
if (!okrequestHash)
{
return false;
}
bool okrequestDetails = u.from_bytes(requestDetails);
if (!okrequestDetails)
{
return false;
}
bool okaction = u.from_bytes(action);
if (!okaction)
{
return false;
}
bool okreason = u.from_bytes(reason);
if (!okreason)
{
return false;
}
bool okreviewDetails = u.from_bytes(reviewDetails);
if (!okreviewDetails)
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
ReviewRequestOp::to_bytes(xdr::marshaler& m) const 
{
bool okrequestID = m.to_bytes(requestID);
if (!okrequestID)
{
return false;
}
bool okrequestHash = m.to_bytes(requestHash);
if (!okrequestHash)
{
return false;
}
bool okrequestDetails = m.to_bytes(requestDetails);
if (!okrequestDetails)
{
return false;
}
bool okaction = m.to_bytes(action);
if (!okaction)
{
return false;
}
bool okreason = m.to_bytes(reason);
if (!okreason)
{
return false;
}
bool okreviewDetails = m.to_bytes(reviewDetails);
if (!okreviewDetails)
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
ReviewRequestOp::count_size(xdr::measurer& m) const 
{
m.count_size(requestID);
m.count_size(requestHash);
m.count_size(requestDetails);
m.count_size(action);
m.count_size(reason);
m.count_size(reviewDetails);
m.count_size(ext);
}
bool
ReviewRequestOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<ReviewRequestOp const&>(other_abstract);return true
&& (requestID== other.requestID)
&& (requestHash== other.requestHash)
&& (requestDetails== other.requestDetails)
&& (action== other.action)
&& (reason== other.reason)
&& (reviewDetails== other.reviewDetails)
&& (ext== other.ext)
;}
bool
ReviewRequestOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ReviewRequestOp const&>(other_abstract);
if (requestID < other.requestID) return true;
if (other.requestID < requestID) return false;
if (requestHash < other.requestHash) return true;
if (other.requestHash < requestHash) return false;
if (requestDetails < other.requestDetails) return true;
if (other.requestDetails < requestDetails) return false;
if (action < other.action) return true;
if (other.action < action) return false;
if (reason < other.reason) return true;
if (other.reason < reason) return false;
if (reviewDetails < other.reviewDetails) return true;
if (other.reviewDetails < reviewDetails) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ReviewRequestResult::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (code_)
{
  case (int32_t)ReviewRequestResultCode::SUCCESS:
return u.from_bytes(success_);
  case (int32_t)ReviewRequestResultCode::MANAGE_OFFER_FAILED:
return u.from_bytes(manageOfferCode_);
  case (int32_t)ReviewRequestResultCode::PAYMENT_FAILED:
return u.from_bytes(paymentCode_);
  default:
  
  return true;
}
return false;
}
bool
ReviewRequestResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)ReviewRequestResultCode::SUCCESS:
return m.to_bytes(success_);
  case (int32_t)ReviewRequestResultCode::MANAGE_OFFER_FAILED:
return m.to_bytes(manageOfferCode_);
  case (int32_t)ReviewRequestResultCode::PAYMENT_FAILED:
return m.to_bytes(paymentCode_);
  default:
    return true;
}
return false;
}
void
ReviewRequestResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)ReviewRequestResultCode::SUCCESS:
return m.count_size(success_);
  case (int32_t)ReviewRequestResultCode::MANAGE_OFFER_FAILED:
return m.count_size(manageOfferCode_);
  case (int32_t)ReviewRequestResultCode::PAYMENT_FAILED:
return m.count_size(paymentCode_);
  default:
  
  return;
}
}
bool
ReviewRequestResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<ReviewRequestResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)ReviewRequestResultCode::SUCCESS:
return success_ == other.success_;
  case (int32_t)ReviewRequestResultCode::MANAGE_OFFER_FAILED:
return manageOfferCode_ == other.manageOfferCode_;
  case (int32_t)ReviewRequestResultCode::PAYMENT_FAILED:
return paymentCode_ == other.paymentCode_;
  default:
  
  return true;
}
return false;
}
bool
ReviewRequestResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ReviewRequestResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)ReviewRequestResultCode::SUCCESS:
return success_ < other.success_;
  case (int32_t)ReviewRequestResultCode::MANAGE_OFFER_FAILED:
return manageOfferCode_ < other.manageOfferCode_;
  case (int32_t)ReviewRequestResultCode::PAYMENT_FAILED:
return paymentCode_ < other.paymentCode_;
  default:
    return false;
}
return false;
}
}