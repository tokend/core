#include "reviewable-request-manage-offer.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
ManageOfferRequest::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ManageOfferRequest::_ext_t::to_bytes(xdr::marshaler& m) const
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
ManageOfferRequest::_ext_t::count_size(xdr::measurer& m) const
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
ManageOfferRequest::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ManageOfferRequest::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ManageOfferRequest::from_bytes(xdr::unmarshaler& u) 
{
bool okop = u.from_bytes(op);
if (!okop)
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
ManageOfferRequest::to_bytes(xdr::marshaler& m) const 
{
bool okop = m.to_bytes(op);
if (!okop)
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
ManageOfferRequest::count_size(xdr::measurer& m) const 
{
m.count_size(op);
m.count_size(ext);
}
bool
ManageOfferRequest::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<ManageOfferRequest const&>(other_abstract);return true
&& (op== other.op)
&& (ext== other.ext)
;}
bool
ManageOfferRequest::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManageOfferRequest const&>(other_abstract);
if (op < other.op) return true;
if (other.op < op) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}