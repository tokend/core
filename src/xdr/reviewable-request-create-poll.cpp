#include "reviewable-request-create-poll.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
CreatePollRequest::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
CreatePollRequest::_ext_t::to_bytes(xdr::marshaler& m) const
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
CreatePollRequest::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
CreatePollRequest::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
CreatePollRequest::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
CreatePollRequest::from_bytes(xdr::unmarshaler& u) 
{
bool okpermissionType = u.from_bytes(permissionType);
if (!okpermissionType)
{
return false;
}
bool oknumberOfChoices = u.from_bytes(numberOfChoices);
if (!oknumberOfChoices)
{
return false;
}
bool okdata = u.from_bytes(data);
if (!okdata)
{
return false;
}
bool okcreatorDetails = u.from_bytes(creatorDetails);
if (!okcreatorDetails)
{
return false;
}
bool okstartTime = u.from_bytes(startTime);
if (!okstartTime)
{
return false;
}
bool okendTime = u.from_bytes(endTime);
if (!okendTime)
{
return false;
}
bool okresultProviderID = u.from_bytes(resultProviderID);
if (!okresultProviderID)
{
return false;
}
bool okvoteConfirmationRequired = u.from_bytes(voteConfirmationRequired);
if (!okvoteConfirmationRequired)
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
CreatePollRequest::to_bytes(xdr::marshaler& m) const 
{
bool okpermissionType = m.to_bytes(permissionType);
if (!okpermissionType)
{
return false;
}
bool oknumberOfChoices = m.to_bytes(numberOfChoices);
if (!oknumberOfChoices)
{
return false;
}
bool okdata = m.to_bytes(data);
if (!okdata)
{
return false;
}
bool okcreatorDetails = m.to_bytes(creatorDetails);
if (!okcreatorDetails)
{
return false;
}
bool okstartTime = m.to_bytes(startTime);
if (!okstartTime)
{
return false;
}
bool okendTime = m.to_bytes(endTime);
if (!okendTime)
{
return false;
}
bool okresultProviderID = m.to_bytes(resultProviderID);
if (!okresultProviderID)
{
return false;
}
bool okvoteConfirmationRequired = m.to_bytes(voteConfirmationRequired);
if (!okvoteConfirmationRequired)
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
CreatePollRequest::count_size(xdr::measurer& m) const 
{
m.count_size(permissionType);
m.count_size(numberOfChoices);
m.count_size(data);
m.count_size(creatorDetails);
m.count_size(startTime);
m.count_size(endTime);
m.count_size(resultProviderID);
m.count_size(voteConfirmationRequired);
m.count_size(ext);
}
bool
CreatePollRequest::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CreatePollRequest const&>(other_abstract);return true
&& (permissionType== other.permissionType)
&& (numberOfChoices== other.numberOfChoices)
&& (data== other.data)
&& (creatorDetails== other.creatorDetails)
&& (startTime== other.startTime)
&& (endTime== other.endTime)
&& (resultProviderID== other.resultProviderID)
&& (voteConfirmationRequired== other.voteConfirmationRequired)
&& (ext== other.ext)
;}
bool
CreatePollRequest::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreatePollRequest const&>(other_abstract);
if (permissionType < other.permissionType) return true;
if (other.permissionType < permissionType) return false;
if (numberOfChoices < other.numberOfChoices) return true;
if (other.numberOfChoices < numberOfChoices) return false;
if (data < other.data) return true;
if (other.data < data) return false;
if (creatorDetails < other.creatorDetails) return true;
if (other.creatorDetails < creatorDetails) return false;
if (startTime < other.startTime) return true;
if (other.startTime < startTime) return false;
if (endTime < other.endTime) return true;
if (other.endTime < endTime) return false;
if (resultProviderID < other.resultProviderID) return true;
if (other.resultProviderID < resultProviderID) return false;
if (voteConfirmationRequired < other.voteConfirmationRequired) return true;
if (other.voteConfirmationRequired < voteConfirmationRequired) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}