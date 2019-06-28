#include "reviewable-request-issuance.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
PreIssuanceRequest::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
PreIssuanceRequest::_ext_t::to_bytes(xdr::marshaler& m) const
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
PreIssuanceRequest::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
PreIssuanceRequest::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
PreIssuanceRequest::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
PreIssuanceRequest::from_bytes(xdr::unmarshaler& u) 
{
bool okasset = u.from_bytes(asset);
if (!okasset)
{
return false;
}
bool okamount = u.from_bytes(amount);
if (!okamount)
{
return false;
}
bool oksignature = u.from_bytes(signature);
if (!oksignature)
{
return false;
}
bool okreference = u.from_bytes(reference);
if (!okreference)
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
PreIssuanceRequest::to_bytes(xdr::marshaler& m) const 
{
bool okasset = m.to_bytes(asset);
if (!okasset)
{
return false;
}
bool okamount = m.to_bytes(amount);
if (!okamount)
{
return false;
}
bool oksignature = m.to_bytes(signature);
if (!oksignature)
{
return false;
}
bool okreference = m.to_bytes(reference);
if (!okreference)
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
PreIssuanceRequest::count_size(xdr::measurer& m) const 
{
m.count_size(asset);
m.count_size(amount);
m.count_size(signature);
m.count_size(reference);
m.count_size(creatorDetails);
m.count_size(ext);
}
bool
PreIssuanceRequest::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<PreIssuanceRequest const&>(other_abstract);return true
&& (asset== other.asset)
&& (amount== other.amount)
&& (signature== other.signature)
&& (reference== other.reference)
&& (creatorDetails== other.creatorDetails)
&& (ext== other.ext)
;}
bool
PreIssuanceRequest::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<PreIssuanceRequest const&>(other_abstract);
if (asset < other.asset) return true;
if (other.asset < asset) return false;
if (amount < other.amount) return true;
if (other.amount < amount) return false;
if (signature < other.signature) return true;
if (other.signature < signature) return false;
if (reference < other.reference) return true;
if (other.reference < reference) return false;
if (creatorDetails < other.creatorDetails) return true;
if (other.creatorDetails < creatorDetails) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
IssuanceRequest::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
IssuanceRequest::_ext_t::to_bytes(xdr::marshaler& m) const
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
IssuanceRequest::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
IssuanceRequest::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
IssuanceRequest::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
IssuanceRequest::from_bytes(xdr::unmarshaler& u) 
{
bool okasset = u.from_bytes(asset);
if (!okasset)
{
return false;
}
bool okamount = u.from_bytes(amount);
if (!okamount)
{
return false;
}
bool okreceiver = u.from_bytes(receiver);
if (!okreceiver)
{
return false;
}
bool okcreatorDetails = u.from_bytes(creatorDetails);
if (!okcreatorDetails)
{
return false;
}
bool okfee = u.from_bytes(fee);
if (!okfee)
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
IssuanceRequest::to_bytes(xdr::marshaler& m) const 
{
bool okasset = m.to_bytes(asset);
if (!okasset)
{
return false;
}
bool okamount = m.to_bytes(amount);
if (!okamount)
{
return false;
}
bool okreceiver = m.to_bytes(receiver);
if (!okreceiver)
{
return false;
}
bool okcreatorDetails = m.to_bytes(creatorDetails);
if (!okcreatorDetails)
{
return false;
}
bool okfee = m.to_bytes(fee);
if (!okfee)
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
IssuanceRequest::count_size(xdr::measurer& m) const 
{
m.count_size(asset);
m.count_size(amount);
m.count_size(receiver);
m.count_size(creatorDetails);
m.count_size(fee);
m.count_size(ext);
}
bool
IssuanceRequest::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<IssuanceRequest const&>(other_abstract);return true
&& (asset== other.asset)
&& (amount== other.amount)
&& (receiver== other.receiver)
&& (creatorDetails== other.creatorDetails)
&& (fee== other.fee)
&& (ext== other.ext)
;}
bool
IssuanceRequest::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<IssuanceRequest const&>(other_abstract);
if (asset < other.asset) return true;
if (other.asset < asset) return false;
if (amount < other.amount) return true;
if (other.amount < amount) return false;
if (receiver < other.receiver) return true;
if (other.receiver < receiver) return false;
if (creatorDetails < other.creatorDetails) return true;
if (other.creatorDetails < creatorDetails) return false;
if (fee < other.fee) return true;
if (other.fee < fee) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}