#include "reviewable-request-asset.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
AssetCreationRequest::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
AssetCreationRequest::_ext_t::to_bytes(xdr::marshaler& m) const
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
AssetCreationRequest::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
AssetCreationRequest::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
AssetCreationRequest::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
AssetCreationRequest::from_bytes(xdr::unmarshaler& u) 
{
bool okcode = u.from_bytes(code);
if (!okcode)
{
return false;
}
bool okpreissuedAssetSigner = u.from_bytes(preissuedAssetSigner);
if (!okpreissuedAssetSigner)
{
return false;
}
bool okmaxIssuanceAmount = u.from_bytes(maxIssuanceAmount);
if (!okmaxIssuanceAmount)
{
return false;
}
bool okinitialPreissuedAmount = u.from_bytes(initialPreissuedAmount);
if (!okinitialPreissuedAmount)
{
return false;
}
bool okpolicies = u.from_bytes(policies);
if (!okpolicies)
{
return false;
}
bool okcreatorDetails = u.from_bytes(creatorDetails);
if (!okcreatorDetails)
{
return false;
}
bool oktype = u.from_bytes(type);
if (!oktype)
{
return false;
}
bool oksequenceNumber = u.from_bytes(sequenceNumber);
if (!oksequenceNumber)
{
return false;
}
bool oktrailingDigitsCount = u.from_bytes(trailingDigitsCount);
if (!oktrailingDigitsCount)
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
AssetCreationRequest::to_bytes(xdr::marshaler& m) const 
{
bool okcode = m.to_bytes(code);
if (!okcode)
{
return false;
}
bool okpreissuedAssetSigner = m.to_bytes(preissuedAssetSigner);
if (!okpreissuedAssetSigner)
{
return false;
}
bool okmaxIssuanceAmount = m.to_bytes(maxIssuanceAmount);
if (!okmaxIssuanceAmount)
{
return false;
}
bool okinitialPreissuedAmount = m.to_bytes(initialPreissuedAmount);
if (!okinitialPreissuedAmount)
{
return false;
}
bool okpolicies = m.to_bytes(policies);
if (!okpolicies)
{
return false;
}
bool okcreatorDetails = m.to_bytes(creatorDetails);
if (!okcreatorDetails)
{
return false;
}
bool oktype = m.to_bytes(type);
if (!oktype)
{
return false;
}
bool oksequenceNumber = m.to_bytes(sequenceNumber);
if (!oksequenceNumber)
{
return false;
}
bool oktrailingDigitsCount = m.to_bytes(trailingDigitsCount);
if (!oktrailingDigitsCount)
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
AssetCreationRequest::count_size(xdr::measurer& m) const 
{
m.count_size(code);
m.count_size(preissuedAssetSigner);
m.count_size(maxIssuanceAmount);
m.count_size(initialPreissuedAmount);
m.count_size(policies);
m.count_size(creatorDetails);
m.count_size(type);
m.count_size(sequenceNumber);
m.count_size(trailingDigitsCount);
m.count_size(ext);
}
bool
AssetCreationRequest::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<AssetCreationRequest const&>(other_abstract);return true
&& (code== other.code)
&& (preissuedAssetSigner== other.preissuedAssetSigner)
&& (maxIssuanceAmount== other.maxIssuanceAmount)
&& (initialPreissuedAmount== other.initialPreissuedAmount)
&& (policies== other.policies)
&& (creatorDetails== other.creatorDetails)
&& (type== other.type)
&& (sequenceNumber== other.sequenceNumber)
&& (trailingDigitsCount== other.trailingDigitsCount)
&& (ext== other.ext)
;}
bool
AssetCreationRequest::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<AssetCreationRequest const&>(other_abstract);
if (code < other.code) return true;
if (other.code < code) return false;
if (preissuedAssetSigner < other.preissuedAssetSigner) return true;
if (other.preissuedAssetSigner < preissuedAssetSigner) return false;
if (maxIssuanceAmount < other.maxIssuanceAmount) return true;
if (other.maxIssuanceAmount < maxIssuanceAmount) return false;
if (initialPreissuedAmount < other.initialPreissuedAmount) return true;
if (other.initialPreissuedAmount < initialPreissuedAmount) return false;
if (policies < other.policies) return true;
if (other.policies < policies) return false;
if (creatorDetails < other.creatorDetails) return true;
if (other.creatorDetails < creatorDetails) return false;
if (type < other.type) return true;
if (other.type < type) return false;
if (sequenceNumber < other.sequenceNumber) return true;
if (other.sequenceNumber < sequenceNumber) return false;
if (trailingDigitsCount < other.trailingDigitsCount) return true;
if (other.trailingDigitsCount < trailingDigitsCount) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
AssetUpdateRequest::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
AssetUpdateRequest::_ext_t::to_bytes(xdr::marshaler& m) const
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
AssetUpdateRequest::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
AssetUpdateRequest::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
AssetUpdateRequest::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
AssetUpdateRequest::from_bytes(xdr::unmarshaler& u) 
{
bool okcode = u.from_bytes(code);
if (!okcode)
{
return false;
}
bool okcreatorDetails = u.from_bytes(creatorDetails);
if (!okcreatorDetails)
{
return false;
}
bool okpolicies = u.from_bytes(policies);
if (!okpolicies)
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
AssetUpdateRequest::to_bytes(xdr::marshaler& m) const 
{
bool okcode = m.to_bytes(code);
if (!okcode)
{
return false;
}
bool okcreatorDetails = m.to_bytes(creatorDetails);
if (!okcreatorDetails)
{
return false;
}
bool okpolicies = m.to_bytes(policies);
if (!okpolicies)
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
AssetUpdateRequest::count_size(xdr::measurer& m) const 
{
m.count_size(code);
m.count_size(creatorDetails);
m.count_size(policies);
m.count_size(sequenceNumber);
m.count_size(ext);
}
bool
AssetUpdateRequest::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<AssetUpdateRequest const&>(other_abstract);return true
&& (code== other.code)
&& (creatorDetails== other.creatorDetails)
&& (policies== other.policies)
&& (sequenceNumber== other.sequenceNumber)
&& (ext== other.ext)
;}
bool
AssetUpdateRequest::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<AssetUpdateRequest const&>(other_abstract);
if (code < other.code) return true;
if (other.code < code) return false;
if (creatorDetails < other.creatorDetails) return true;
if (other.creatorDetails < creatorDetails) return false;
if (policies < other.policies) return true;
if (other.policies < policies) return false;
if (sequenceNumber < other.sequenceNumber) return true;
if (other.sequenceNumber < sequenceNumber) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
AssetChangePreissuedSigner::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
AssetChangePreissuedSigner::_ext_t::to_bytes(xdr::marshaler& m) const
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
AssetChangePreissuedSigner::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
AssetChangePreissuedSigner::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
AssetChangePreissuedSigner::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
AssetChangePreissuedSigner::from_bytes(xdr::unmarshaler& u) 
{
bool okcode = u.from_bytes(code);
if (!okcode)
{
return false;
}
bool okaccountID = u.from_bytes(accountID);
if (!okaccountID)
{
return false;
}
bool oksignature = u.from_bytes(signature);
if (!oksignature)
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
AssetChangePreissuedSigner::to_bytes(xdr::marshaler& m) const 
{
bool okcode = m.to_bytes(code);
if (!okcode)
{
return false;
}
bool okaccountID = m.to_bytes(accountID);
if (!okaccountID)
{
return false;
}
bool oksignature = m.to_bytes(signature);
if (!oksignature)
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
AssetChangePreissuedSigner::count_size(xdr::measurer& m) const 
{
m.count_size(code);
m.count_size(accountID);
m.count_size(signature);
m.count_size(ext);
}
bool
AssetChangePreissuedSigner::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<AssetChangePreissuedSigner const&>(other_abstract);return true
&& (code== other.code)
&& (accountID== other.accountID)
&& (signature== other.signature)
&& (ext== other.ext)
;}
bool
AssetChangePreissuedSigner::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<AssetChangePreissuedSigner const&>(other_abstract);
if (code < other.code) return true;
if (other.code < code) return false;
if (accountID < other.accountID) return true;
if (other.accountID < accountID) return false;
if (signature < other.signature) return true;
if (other.signature < signature) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}