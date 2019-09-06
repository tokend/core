#include "SCP.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
SCPBallot::from_bytes(xdr::unmarshaler& u) 
{
bool okcounter = u.from_bytes(counter);
if (!okcounter)
{
return false;
}
bool okvalue = u.from_bytes(value);
if (!okvalue)
{
return false;
}
return true;
}
bool
SCPBallot::to_bytes(xdr::marshaler& m) const 
{
bool okcounter = m.to_bytes(counter);
if (!okcounter)
{
return false;
}
bool okvalue = m.to_bytes(value);
if (!okvalue)
{
return false;
}
return true;
}
void
SCPBallot::count_size(xdr::measurer& m) const 
{
m.count_size(counter);
m.count_size(value);
}
bool
SCPBallot::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<SCPBallot const&>(other_abstract);return true
&& (counter== other.counter)
&& (value== other.value)
;}
bool
SCPBallot::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<SCPBallot const&>(other_abstract);
if (counter < other.counter) return true;
if (other.counter < counter) return false;
if (value < other.value) return true;
if (other.value < value) return false;
return false;
}bool
SCPNomination::from_bytes(xdr::unmarshaler& u) 
{
bool okquorumSetHash = u.from_bytes(quorumSetHash);
if (!okquorumSetHash)
{
return false;
}
bool okvotes = u.from_bytes(votes);
if (!okvotes)
{
return false;
}
bool okaccepted = u.from_bytes(accepted);
if (!okaccepted)
{
return false;
}
return true;
}
bool
SCPNomination::to_bytes(xdr::marshaler& m) const 
{
bool okquorumSetHash = m.to_bytes(quorumSetHash);
if (!okquorumSetHash)
{
return false;
}
bool okvotes = m.to_bytes(votes);
if (!okvotes)
{
return false;
}
bool okaccepted = m.to_bytes(accepted);
if (!okaccepted)
{
return false;
}
return true;
}
void
SCPNomination::count_size(xdr::measurer& m) const 
{
m.count_size(quorumSetHash);
m.count_size(votes);
m.count_size(accepted);
}
bool
SCPNomination::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<SCPNomination const&>(other_abstract);return true
&& (quorumSetHash== other.quorumSetHash)
&& (votes== other.votes)
&& (accepted== other.accepted)
;}
bool
SCPNomination::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<SCPNomination const&>(other_abstract);
if (quorumSetHash < other.quorumSetHash) return true;
if (other.quorumSetHash < quorumSetHash) return false;
if (votes < other.votes) return true;
if (other.votes < votes) return false;
if (accepted < other.accepted) return true;
if (other.accepted < accepted) return false;
return false;
}bool
SCPStatement::_pledges_t::_prepare_t::from_bytes(xdr::unmarshaler& u) 
{
bool okquorumSetHash = u.from_bytes(quorumSetHash);
if (!okquorumSetHash)
{
return false;
}
bool okballot = u.from_bytes(ballot);
if (!okballot)
{
return false;
}
bool okprepared = u.from_bytes(prepared);
if (!okprepared)
{
return false;
}
bool okpreparedPrime = u.from_bytes(preparedPrime);
if (!okpreparedPrime)
{
return false;
}
bool oknC = u.from_bytes(nC);
if (!oknC)
{
return false;
}
bool oknH = u.from_bytes(nH);
if (!oknH)
{
return false;
}
return true;
}
bool
SCPStatement::_pledges_t::_prepare_t::to_bytes(xdr::marshaler& m) const 
{
bool okquorumSetHash = m.to_bytes(quorumSetHash);
if (!okquorumSetHash)
{
return false;
}
bool okballot = m.to_bytes(ballot);
if (!okballot)
{
return false;
}
bool okprepared = m.to_bytes(prepared);
if (!okprepared)
{
return false;
}
bool okpreparedPrime = m.to_bytes(preparedPrime);
if (!okpreparedPrime)
{
return false;
}
bool oknC = m.to_bytes(nC);
if (!oknC)
{
return false;
}
bool oknH = m.to_bytes(nH);
if (!oknH)
{
return false;
}
return true;
}
void
SCPStatement::_pledges_t::_prepare_t::count_size(xdr::measurer& m) const 
{
m.count_size(quorumSetHash);
m.count_size(ballot);
m.count_size(prepared);
m.count_size(preparedPrime);
m.count_size(nC);
m.count_size(nH);
}
bool
SCPStatement::_pledges_t::_prepare_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_prepare_t const&>(other_abstract);return true
&& (quorumSetHash== other.quorumSetHash)
&& (ballot== other.ballot)
&& (prepared== other.prepared)
&& (preparedPrime== other.preparedPrime)
&& (nC== other.nC)
&& (nH== other.nH)
;}
bool
SCPStatement::_pledges_t::_prepare_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_prepare_t const&>(other_abstract);
if (quorumSetHash < other.quorumSetHash) return true;
if (other.quorumSetHash < quorumSetHash) return false;
if (ballot < other.ballot) return true;
if (other.ballot < ballot) return false;
if (prepared < other.prepared) return true;
if (other.prepared < prepared) return false;
if (preparedPrime < other.preparedPrime) return true;
if (other.preparedPrime < preparedPrime) return false;
if (nC < other.nC) return true;
if (other.nC < nC) return false;
if (nH < other.nH) return true;
if (other.nH < nH) return false;
return false;
}bool
SCPStatement::_pledges_t::_confirm_t::from_bytes(xdr::unmarshaler& u) 
{
bool okballot = u.from_bytes(ballot);
if (!okballot)
{
return false;
}
bool oknPrepared = u.from_bytes(nPrepared);
if (!oknPrepared)
{
return false;
}
bool oknCommit = u.from_bytes(nCommit);
if (!oknCommit)
{
return false;
}
bool oknH = u.from_bytes(nH);
if (!oknH)
{
return false;
}
bool okquorumSetHash = u.from_bytes(quorumSetHash);
if (!okquorumSetHash)
{
return false;
}
return true;
}
bool
SCPStatement::_pledges_t::_confirm_t::to_bytes(xdr::marshaler& m) const 
{
bool okballot = m.to_bytes(ballot);
if (!okballot)
{
return false;
}
bool oknPrepared = m.to_bytes(nPrepared);
if (!oknPrepared)
{
return false;
}
bool oknCommit = m.to_bytes(nCommit);
if (!oknCommit)
{
return false;
}
bool oknH = m.to_bytes(nH);
if (!oknH)
{
return false;
}
bool okquorumSetHash = m.to_bytes(quorumSetHash);
if (!okquorumSetHash)
{
return false;
}
return true;
}
void
SCPStatement::_pledges_t::_confirm_t::count_size(xdr::measurer& m) const 
{
m.count_size(ballot);
m.count_size(nPrepared);
m.count_size(nCommit);
m.count_size(nH);
m.count_size(quorumSetHash);
}
bool
SCPStatement::_pledges_t::_confirm_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_confirm_t const&>(other_abstract);return true
&& (ballot== other.ballot)
&& (nPrepared== other.nPrepared)
&& (nCommit== other.nCommit)
&& (nH== other.nH)
&& (quorumSetHash== other.quorumSetHash)
;}
bool
SCPStatement::_pledges_t::_confirm_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_confirm_t const&>(other_abstract);
if (ballot < other.ballot) return true;
if (other.ballot < ballot) return false;
if (nPrepared < other.nPrepared) return true;
if (other.nPrepared < nPrepared) return false;
if (nCommit < other.nCommit) return true;
if (other.nCommit < nCommit) return false;
if (nH < other.nH) return true;
if (other.nH < nH) return false;
if (quorumSetHash < other.quorumSetHash) return true;
if (other.quorumSetHash < quorumSetHash) return false;
return false;
}bool
SCPStatement::_pledges_t::_externalize_t::from_bytes(xdr::unmarshaler& u) 
{
bool okcommit = u.from_bytes(commit);
if (!okcommit)
{
return false;
}
bool oknH = u.from_bytes(nH);
if (!oknH)
{
return false;
}
bool okcommitQuorumSetHash = u.from_bytes(commitQuorumSetHash);
if (!okcommitQuorumSetHash)
{
return false;
}
return true;
}
bool
SCPStatement::_pledges_t::_externalize_t::to_bytes(xdr::marshaler& m) const 
{
bool okcommit = m.to_bytes(commit);
if (!okcommit)
{
return false;
}
bool oknH = m.to_bytes(nH);
if (!oknH)
{
return false;
}
bool okcommitQuorumSetHash = m.to_bytes(commitQuorumSetHash);
if (!okcommitQuorumSetHash)
{
return false;
}
return true;
}
void
SCPStatement::_pledges_t::_externalize_t::count_size(xdr::measurer& m) const 
{
m.count_size(commit);
m.count_size(nH);
m.count_size(commitQuorumSetHash);
}
bool
SCPStatement::_pledges_t::_externalize_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_externalize_t const&>(other_abstract);return true
&& (commit== other.commit)
&& (nH== other.nH)
&& (commitQuorumSetHash== other.commitQuorumSetHash)
;}
bool
SCPStatement::_pledges_t::_externalize_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_externalize_t const&>(other_abstract);
if (commit < other.commit) return true;
if (other.commit < commit) return false;
if (nH < other.nH) return true;
if (other.nH < nH) return false;
if (commitQuorumSetHash < other.commitQuorumSetHash) return true;
if (other.commitQuorumSetHash < commitQuorumSetHash) return false;
return false;
}bool
SCPStatement::_pledges_t::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (type_)
{
    case (int32_t)SCPStatementType::PREPARE:
return u.from_bytes(prepare_);
    case (int32_t)SCPStatementType::CONFIRM:
return u.from_bytes(confirm_);
    case (int32_t)SCPStatementType::EXTERNALIZE:
return u.from_bytes(externalize_);
    case (int32_t)SCPStatementType::NOMINATE:
return u.from_bytes(nominate_);
}
return false;
}
bool
SCPStatement::_pledges_t::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(type_);
if (!ok)
{
return false;
}
switch (type_)
{

    case (int32_t)SCPStatementType::PREPARE:
return m.to_bytes(prepare_);
    case (int32_t)SCPStatementType::CONFIRM:
return m.to_bytes(confirm_);
    case (int32_t)SCPStatementType::EXTERNALIZE:
return m.to_bytes(externalize_);
    case (int32_t)SCPStatementType::NOMINATE:
return m.to_bytes(nominate_);
}
return false;
}
void
SCPStatement::_pledges_t::count_size(xdr::measurer& m) const
{
m.count_size(type_);
switch (type_)
{

    case (int32_t)SCPStatementType::PREPARE:
return m.count_size(prepare_);
    case (int32_t)SCPStatementType::CONFIRM:
return m.count_size(confirm_);
    case (int32_t)SCPStatementType::EXTERNALIZE:
return m.count_size(externalize_);
    case (int32_t)SCPStatementType::NOMINATE:
return m.count_size(nominate_);
}
}
bool
SCPStatement::_pledges_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_pledges_t const&>(other_abstract);
if (other.type_ != type_) return false;
switch (type_)
{
    case (int32_t)SCPStatementType::PREPARE:
return prepare_ == other.prepare_;
    case (int32_t)SCPStatementType::CONFIRM:
return confirm_ == other.confirm_;
    case (int32_t)SCPStatementType::EXTERNALIZE:
return externalize_ == other.externalize_;
    case (int32_t)SCPStatementType::NOMINATE:
return nominate_ == other.nominate_;
}
return false;
}
bool
SCPStatement::_pledges_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_pledges_t const&>(other_abstract);
if (type_ < other.type_) return true;
if (other.type_ < type_) return false;
switch (type_)
{
    case (int32_t)SCPStatementType::PREPARE:
return prepare_ < other.prepare_;
    case (int32_t)SCPStatementType::CONFIRM:
return confirm_ < other.confirm_;
    case (int32_t)SCPStatementType::EXTERNALIZE:
return externalize_ < other.externalize_;
    case (int32_t)SCPStatementType::NOMINATE:
return nominate_ < other.nominate_;
}
return false;
}
bool
SCPStatement::from_bytes(xdr::unmarshaler& u) 
{
bool oknodeID = u.from_bytes(nodeID);
if (!oknodeID)
{
return false;
}
bool okslotIndex = u.from_bytes(slotIndex);
if (!okslotIndex)
{
return false;
}
bool okpledges = u.from_bytes(pledges);
if (!okpledges)
{
return false;
}
return true;
}
bool
SCPStatement::to_bytes(xdr::marshaler& m) const 
{
bool oknodeID = m.to_bytes(nodeID);
if (!oknodeID)
{
return false;
}
bool okslotIndex = m.to_bytes(slotIndex);
if (!okslotIndex)
{
return false;
}
bool okpledges = m.to_bytes(pledges);
if (!okpledges)
{
return false;
}
return true;
}
void
SCPStatement::count_size(xdr::measurer& m) const 
{
m.count_size(nodeID);
m.count_size(slotIndex);
m.count_size(pledges);
}
bool
SCPStatement::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<SCPStatement const&>(other_abstract);return true
&& (nodeID== other.nodeID)
&& (slotIndex== other.slotIndex)
&& (pledges== other.pledges)
;}
bool
SCPStatement::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<SCPStatement const&>(other_abstract);
if (nodeID < other.nodeID) return true;
if (other.nodeID < nodeID) return false;
if (slotIndex < other.slotIndex) return true;
if (other.slotIndex < slotIndex) return false;
if (pledges < other.pledges) return true;
if (other.pledges < pledges) return false;
return false;
}bool
SCPEnvelope::from_bytes(xdr::unmarshaler& u) 
{
bool okstatement = u.from_bytes(statement);
if (!okstatement)
{
return false;
}
bool oksignature = u.from_bytes(signature);
if (!oksignature)
{
return false;
}
return true;
}
bool
SCPEnvelope::to_bytes(xdr::marshaler& m) const 
{
bool okstatement = m.to_bytes(statement);
if (!okstatement)
{
return false;
}
bool oksignature = m.to_bytes(signature);
if (!oksignature)
{
return false;
}
return true;
}
void
SCPEnvelope::count_size(xdr::measurer& m) const 
{
m.count_size(statement);
m.count_size(signature);
}
bool
SCPEnvelope::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<SCPEnvelope const&>(other_abstract);return true
&& (statement== other.statement)
&& (signature== other.signature)
;}
bool
SCPEnvelope::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<SCPEnvelope const&>(other_abstract);
if (statement < other.statement) return true;
if (other.statement < statement) return false;
if (signature < other.signature) return true;
if (other.signature < signature) return false;
return false;
}bool
SCPQuorumSet::from_bytes(xdr::unmarshaler& u) 
{
bool okthreshold = u.from_bytes(threshold);
if (!okthreshold)
{
return false;
}
bool okvalidators = u.from_bytes(validators);
if (!okvalidators)
{
return false;
}
bool okinnerSets = u.from_bytes(innerSets);
if (!okinnerSets)
{
return false;
}
return true;
}
bool
SCPQuorumSet::to_bytes(xdr::marshaler& m) const 
{
bool okthreshold = m.to_bytes(threshold);
if (!okthreshold)
{
return false;
}
bool okvalidators = m.to_bytes(validators);
if (!okvalidators)
{
return false;
}
bool okinnerSets = m.to_bytes(innerSets);
if (!okinnerSets)
{
return false;
}
return true;
}
void
SCPQuorumSet::count_size(xdr::measurer& m) const 
{
m.count_size(threshold);
m.count_size(validators);
m.count_size(innerSets);
}
bool
SCPQuorumSet::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<SCPQuorumSet const&>(other_abstract);return true
&& (threshold== other.threshold)
&& (validators== other.validators)
&& (innerSets== other.innerSets)
;}
bool
SCPQuorumSet::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<SCPQuorumSet const&>(other_abstract);
if (threshold < other.threshold) return true;
if (other.threshold < threshold) return false;
if (validators < other.validators) return true;
if (other.validators < validators) return false;
if (innerSets < other.innerSets) return true;
if (other.innerSets < innerSets) return false;
return false;
}}