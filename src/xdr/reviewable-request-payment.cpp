#include "reviewable-request-payment.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
CreatePaymentRequest::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
    case (int32_t)LedgerVersion::MOVEMENT_REQUESTS_DETAILS:
return u.from_bytes(creatorDetails_);
}
return false;
}
bool
CreatePaymentRequest::_ext_t::to_bytes(xdr::marshaler& m) const
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
    case (int32_t)LedgerVersion::MOVEMENT_REQUESTS_DETAILS:
return m.to_bytes(creatorDetails_);
}
return false;
}
void
CreatePaymentRequest::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
    case (int32_t)LedgerVersion::MOVEMENT_REQUESTS_DETAILS:
return m.count_size(creatorDetails_);
}
}
bool
CreatePaymentRequest::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
    case (int32_t)LedgerVersion::MOVEMENT_REQUESTS_DETAILS:
return creatorDetails_ == other.creatorDetails_;
}
return false;
}
bool
CreatePaymentRequest::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
    case (int32_t)LedgerVersion::MOVEMENT_REQUESTS_DETAILS:
return creatorDetails_ < other.creatorDetails_;
}
return false;
}
bool
CreatePaymentRequest::from_bytes(xdr::unmarshaler& u) 
{
bool okpaymentOp = u.from_bytes(paymentOp);
if (!okpaymentOp)
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
CreatePaymentRequest::to_bytes(xdr::marshaler& m) const 
{
bool okpaymentOp = m.to_bytes(paymentOp);
if (!okpaymentOp)
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
CreatePaymentRequest::count_size(xdr::measurer& m) const 
{
m.count_size(paymentOp);
m.count_size(ext);
}
bool
CreatePaymentRequest::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CreatePaymentRequest const&>(other_abstract);return true
&& (paymentOp== other.paymentOp)
&& (ext== other.ext)
;}
bool
CreatePaymentRequest::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreatePaymentRequest const&>(other_abstract);
if (paymentOp < other.paymentOp) return true;
if (other.paymentOp < paymentOp) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}