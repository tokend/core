#include "ledger-entries-vote.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
SingleChoiceVote::from_bytes(xdr::unmarshaler& u) 
{
bool okchoice = u.from_bytes(choice);
if (!okchoice)
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
SingleChoiceVote::to_bytes(xdr::marshaler& m) const 
{
bool okchoice = m.to_bytes(choice);
if (!okchoice)
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
SingleChoiceVote::count_size(xdr::measurer& m) const 
{
m.count_size(choice);
m.count_size(ext);
}
bool
SingleChoiceVote::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<SingleChoiceVote const&>(other_abstract);return true
&& (choice== other.choice)
&& (ext== other.ext)
;}
bool
SingleChoiceVote::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<SingleChoiceVote const&>(other_abstract);
if (choice < other.choice) return true;
if (other.choice < choice) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
VoteData::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (pollType_)
{
  case (int32_t)PollType::SINGLE_CHOICE:
return u.from_bytes(single_);
  case (int32_t)PollType::CUSTOM_CHOICE:
return u.from_bytes(custom_);
}
return false;
}
bool
VoteData::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(pollType_);
if (!ok)
{
return false;
}
switch (pollType_)
{

  case (int32_t)PollType::SINGLE_CHOICE:
return m.to_bytes(single_);
  case (int32_t)PollType::CUSTOM_CHOICE:
return m.to_bytes(custom_);
}
return false;
}
void
VoteData::count_size(xdr::measurer& m) const
{
m.count_size(pollType_);
switch (pollType_)
{

  case (int32_t)PollType::SINGLE_CHOICE:
return m.count_size(single_);
  case (int32_t)PollType::CUSTOM_CHOICE:
return m.count_size(custom_);
}
}
bool
VoteData::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<VoteData const&>(other_abstract);
if (other.pollType_ != pollType_) return false;
switch (pollType_)
{
  case (int32_t)PollType::SINGLE_CHOICE:
return single_ == other.single_;
  case (int32_t)PollType::CUSTOM_CHOICE:
return custom_ == other.custom_;
}
return false;
}
bool
VoteData::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<VoteData const&>(other_abstract);
if (pollType_ < other.pollType_) return true;
if (other.pollType_ < pollType_) return false;
switch (pollType_)
{
  case (int32_t)PollType::SINGLE_CHOICE:
return single_ < other.single_;
  case (int32_t)PollType::CUSTOM_CHOICE:
return custom_ < other.custom_;
}
return false;
}
bool
VoteEntry::from_bytes(xdr::unmarshaler& u) 
{
bool okpollID = u.from_bytes(pollID);
if (!okpollID)
{
return false;
}
bool okvoterID = u.from_bytes(voterID);
if (!okvoterID)
{
return false;
}
bool okdata = u.from_bytes(data);
if (!okdata)
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
VoteEntry::to_bytes(xdr::marshaler& m) const 
{
bool okpollID = m.to_bytes(pollID);
if (!okpollID)
{
return false;
}
bool okvoterID = m.to_bytes(voterID);
if (!okvoterID)
{
return false;
}
bool okdata = m.to_bytes(data);
if (!okdata)
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
VoteEntry::count_size(xdr::measurer& m) const 
{
m.count_size(pollID);
m.count_size(voterID);
m.count_size(data);
m.count_size(ext);
}
bool
VoteEntry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<VoteEntry const&>(other_abstract);return true
&& (pollID== other.pollID)
&& (voterID== other.voterID)
&& (data== other.data)
&& (ext== other.ext)
;}
bool
VoteEntry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<VoteEntry const&>(other_abstract);
if (pollID < other.pollID) return true;
if (other.pollID < pollID) return false;
if (voterID < other.voterID) return true;
if (other.voterID < voterID) return false;
if (data < other.data) return true;
if (other.data < data) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}