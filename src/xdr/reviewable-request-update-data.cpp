#include "reviewable-request-update-data.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
DataUpdateRequest::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
DataUpdateRequest::_ext_t::to_bytes(xdr::marshaler& m) const
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
DataUpdateRequest::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
DataUpdateRequest::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
DataUpdateRequest::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
DataUpdateRequest::from_bytes(xdr::unmarshaler& u) 
{
bool okid = u.from_bytes(id);
if (!okid)
{
return false;
}
bool oksequenceNumber = u.from_bytes(sequenceNumber);
if (!oksequenceNumber)
{
return false;
}
bool okvalue = u.from_bytes(value);
if (!okvalue)
{
return false;
}
bool okcreatorDetails = u.from_bytes(creatorDetails);
if (!okcreatorDetails)
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
DataUpdateRequest::to_bytes(xdr::marshaler& m) const 
{
bool okid = m.to_bytes(id);
if (!okid)
{
return false;
}
bool oksequenceNumber = m.to_bytes(sequenceNumber);
if (!oksequenceNumber)
{
return false;
}
bool okvalue = m.to_bytes(value);
if (!okvalue)
{
return false;
}
bool okcreatorDetails = m.to_bytes(creatorDetails);
if (!okcreatorDetails)
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
DataUpdateRequest::count_size(xdr::measurer& m) const 
{
m.count_size(id);
m.count_size(sequenceNumber);
m.count_size(value);
m.count_size(creatorDetails);
m.count_size(ext);
}
bool
DataUpdateRequest::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<DataUpdateRequest const&>(other_abstract);return true
&& (id== other.id)
&& (sequenceNumber== other.sequenceNumber)
&& (value== other.value)
&& (creatorDetails== other.creatorDetails)
&& (ext== other.ext)
;}
bool
DataUpdateRequest::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<DataUpdateRequest const&>(other_abstract);
if (id < other.id) return true;
if (other.id < id) return false;
if (sequenceNumber < other.sequenceNumber) return true;
if (other.sequenceNumber < sequenceNumber) return false;
if (value < other.value) return true;
if (other.value < value) return false;
if (creatorDetails < other.creatorDetails) return true;
if (other.creatorDetails < creatorDetails) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}