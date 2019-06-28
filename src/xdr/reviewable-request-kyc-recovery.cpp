#include "reviewable-request-kyc-recovery.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
KYCRecoveryRequest::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
KYCRecoveryRequest::_ext_t::to_bytes(xdr::marshaler& m) const
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
KYCRecoveryRequest::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
KYCRecoveryRequest::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
KYCRecoveryRequest::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
KYCRecoveryRequest::from_bytes(xdr::unmarshaler& u) 
{
bool oktargetAccount = u.from_bytes(targetAccount);
if (!oktargetAccount)
{
return false;
}
bool oksignersData = u.from_bytes(signersData);
if (!oksignersData)
{
return false;
}
bool okcreatorDetails = u.from_bytes(creatorDetails);
if (!okcreatorDetails)
{
return false;
}
bool oksequenceNumber = u.from_bytes(sequenceNumber);
if (!oksequenceNumber)
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
KYCRecoveryRequest::to_bytes(xdr::marshaler& m) const 
{
bool oktargetAccount = m.to_bytes(targetAccount);
if (!oktargetAccount)
{
return false;
}
bool oksignersData = m.to_bytes(signersData);
if (!oksignersData)
{
return false;
}
bool okcreatorDetails = m.to_bytes(creatorDetails);
if (!okcreatorDetails)
{
return false;
}
bool oksequenceNumber = m.to_bytes(sequenceNumber);
if (!oksequenceNumber)
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
KYCRecoveryRequest::count_size(xdr::measurer& m) const 
{
m.count_size(targetAccount);
m.count_size(signersData);
m.count_size(creatorDetails);
m.count_size(sequenceNumber);
m.count_size(ext);
}
bool
KYCRecoveryRequest::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<KYCRecoveryRequest const&>(other_abstract);return true
&& (targetAccount== other.targetAccount)
&& (signersData== other.signersData)
&& (creatorDetails== other.creatorDetails)
&& (sequenceNumber== other.sequenceNumber)
&& (ext== other.ext)
;}
bool
KYCRecoveryRequest::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<KYCRecoveryRequest const&>(other_abstract);
if (targetAccount < other.targetAccount) return true;
if (other.targetAccount < targetAccount) return false;
if (signersData < other.signersData) return true;
if (other.signersData < signersData) return false;
if (creatorDetails < other.creatorDetails) return true;
if (other.creatorDetails < creatorDetails) return false;
if (sequenceNumber < other.sequenceNumber) return true;
if (other.sequenceNumber < sequenceNumber) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}