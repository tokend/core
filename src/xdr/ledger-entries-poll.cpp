#include "ledger-entries-poll.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
PollData::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (type_)
{
  case (int32_t)PollType::SINGLE_CHOICE:
return u.from_bytes(ext_);
}
return false;
}
bool
PollData::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(type_);
if (!ok)
{
return false;
}
switch (type_)
{

  case (int32_t)PollType::SINGLE_CHOICE:
return m.to_bytes(ext_);
}
return false;
}
void
PollData::count_size(xdr::measurer& m) const
{
m.count_size(type_);
switch (type_)
{

  case (int32_t)PollType::SINGLE_CHOICE:
return m.count_size(ext_);
}
}
bool
PollData::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<PollData const&>(other_abstract);
if (other.type_ != type_) return false;
switch (type_)
{
  case (int32_t)PollType::SINGLE_CHOICE:
return ext_ == other.ext_;
}
return false;
}
bool
PollData::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<PollData const&>(other_abstract);
if (type_ < other.type_) return true;
if (other.type_ < type_) return false;
switch (type_)
{
  case (int32_t)PollType::SINGLE_CHOICE:
return ext_ < other.ext_;
}
return false;
}
bool
PollEntry::from_bytes(xdr::unmarshaler& u) 
{
bool okid = u.from_bytes(id);
if (!okid)
{
return false;
}
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
bool okownerID = u.from_bytes(ownerID);
if (!okownerID)
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
PollEntry::to_bytes(xdr::marshaler& m) const 
{
bool okid = m.to_bytes(id);
if (!okid)
{
return false;
}
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
bool okownerID = m.to_bytes(ownerID);
if (!okownerID)
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
PollEntry::count_size(xdr::measurer& m) const 
{
m.count_size(id);
m.count_size(permissionType);
m.count_size(numberOfChoices);
m.count_size(data);
m.count_size(startTime);
m.count_size(endTime);
m.count_size(ownerID);
m.count_size(resultProviderID);
m.count_size(voteConfirmationRequired);
m.count_size(details);
m.count_size(ext);
}
bool
PollEntry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<PollEntry const&>(other_abstract);return true
&& (id== other.id)
&& (permissionType== other.permissionType)
&& (numberOfChoices== other.numberOfChoices)
&& (data== other.data)
&& (startTime== other.startTime)
&& (endTime== other.endTime)
&& (ownerID== other.ownerID)
&& (resultProviderID== other.resultProviderID)
&& (voteConfirmationRequired== other.voteConfirmationRequired)
&& (details== other.details)
&& (ext== other.ext)
;}
bool
PollEntry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<PollEntry const&>(other_abstract);
if (id < other.id) return true;
if (other.id < id) return false;
if (permissionType < other.permissionType) return true;
if (other.permissionType < permissionType) return false;
if (numberOfChoices < other.numberOfChoices) return true;
if (other.numberOfChoices < numberOfChoices) return false;
if (data < other.data) return true;
if (other.data < data) return false;
if (startTime < other.startTime) return true;
if (other.startTime < startTime) return false;
if (endTime < other.endTime) return true;
if (other.endTime < endTime) return false;
if (ownerID < other.ownerID) return true;
if (other.ownerID < ownerID) return false;
if (resultProviderID < other.resultProviderID) return true;
if (other.resultProviderID < resultProviderID) return false;
if (voteConfirmationRequired < other.voteConfirmationRequired) return true;
if (other.voteConfirmationRequired < voteConfirmationRequired) return false;
if (details < other.details) return true;
if (other.details < details) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}