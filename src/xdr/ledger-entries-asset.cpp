#include "ledger-entries-asset.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
AssetEntry::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
AssetEntry::_ext_t::to_bytes(xdr::marshaler& m) const
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
AssetEntry::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
AssetEntry::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
AssetEntry::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
AssetEntry::from_bytes(xdr::unmarshaler& u) 
{
bool okcode = u.from_bytes(code);
if (!okcode)
{
return false;
}
bool okowner = u.from_bytes(owner);
if (!okowner)
{
return false;
}
bool okpreissuedAssetSigner = u.from_bytes(preissuedAssetSigner);
if (!okpreissuedAssetSigner)
{
return false;
}
bool okdetails = u.from_bytes(details);
if (!okdetails)
{
return false;
}
bool okmaxIssuanceAmount = u.from_bytes(maxIssuanceAmount);
if (!okmaxIssuanceAmount)
{
return false;
}
bool okavailableForIssueance = u.from_bytes(availableForIssueance);
if (!okavailableForIssueance)
{
return false;
}
bool okissued = u.from_bytes(issued);
if (!okissued)
{
return false;
}
bool okpendingIssuance = u.from_bytes(pendingIssuance);
if (!okpendingIssuance)
{
return false;
}
bool okpolicies = u.from_bytes(policies);
if (!okpolicies)
{
return false;
}
bool oktype = u.from_bytes(type);
if (!oktype)
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
AssetEntry::to_bytes(xdr::marshaler& m) const 
{
bool okcode = m.to_bytes(code);
if (!okcode)
{
return false;
}
bool okowner = m.to_bytes(owner);
if (!okowner)
{
return false;
}
bool okpreissuedAssetSigner = m.to_bytes(preissuedAssetSigner);
if (!okpreissuedAssetSigner)
{
return false;
}
bool okdetails = m.to_bytes(details);
if (!okdetails)
{
return false;
}
bool okmaxIssuanceAmount = m.to_bytes(maxIssuanceAmount);
if (!okmaxIssuanceAmount)
{
return false;
}
bool okavailableForIssueance = m.to_bytes(availableForIssueance);
if (!okavailableForIssueance)
{
return false;
}
bool okissued = m.to_bytes(issued);
if (!okissued)
{
return false;
}
bool okpendingIssuance = m.to_bytes(pendingIssuance);
if (!okpendingIssuance)
{
return false;
}
bool okpolicies = m.to_bytes(policies);
if (!okpolicies)
{
return false;
}
bool oktype = m.to_bytes(type);
if (!oktype)
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
AssetEntry::count_size(xdr::measurer& m) const 
{
m.count_size(code);
m.count_size(owner);
m.count_size(preissuedAssetSigner);
m.count_size(details);
m.count_size(maxIssuanceAmount);
m.count_size(availableForIssueance);
m.count_size(issued);
m.count_size(pendingIssuance);
m.count_size(policies);
m.count_size(type);
m.count_size(trailingDigitsCount);
m.count_size(ext);
}
bool
AssetEntry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<AssetEntry const&>(other_abstract);return true
&& (code== other.code)
&& (owner== other.owner)
&& (preissuedAssetSigner== other.preissuedAssetSigner)
&& (details== other.details)
&& (maxIssuanceAmount== other.maxIssuanceAmount)
&& (availableForIssueance== other.availableForIssueance)
&& (issued== other.issued)
&& (pendingIssuance== other.pendingIssuance)
&& (policies== other.policies)
&& (type== other.type)
&& (trailingDigitsCount== other.trailingDigitsCount)
&& (ext== other.ext)
;}
bool
AssetEntry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<AssetEntry const&>(other_abstract);
if (code < other.code) return true;
if (other.code < code) return false;
if (owner < other.owner) return true;
if (other.owner < owner) return false;
if (preissuedAssetSigner < other.preissuedAssetSigner) return true;
if (other.preissuedAssetSigner < preissuedAssetSigner) return false;
if (details < other.details) return true;
if (other.details < details) return false;
if (maxIssuanceAmount < other.maxIssuanceAmount) return true;
if (other.maxIssuanceAmount < maxIssuanceAmount) return false;
if (availableForIssueance < other.availableForIssueance) return true;
if (other.availableForIssueance < availableForIssueance) return false;
if (issued < other.issued) return true;
if (other.issued < issued) return false;
if (pendingIssuance < other.pendingIssuance) return true;
if (other.pendingIssuance < pendingIssuance) return false;
if (policies < other.policies) return true;
if (other.policies < policies) return false;
if (type < other.type) return true;
if (other.type < type) return false;
if (trailingDigitsCount < other.trailingDigitsCount) return true;
if (other.trailingDigitsCount < trailingDigitsCount) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}