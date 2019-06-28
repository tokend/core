#include "ledger-entries-fee.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
FeeEntry::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
FeeEntry::_ext_t::to_bytes(xdr::marshaler& m) const
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
FeeEntry::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
FeeEntry::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
FeeEntry::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
FeeEntry::from_bytes(xdr::unmarshaler& u) 
{
bool okfeeType = u.from_bytes(feeType);
if (!okfeeType)
{
return false;
}
bool okasset = u.from_bytes(asset);
if (!okasset)
{
return false;
}
bool okfixedFee = u.from_bytes(fixedFee);
if (!okfixedFee)
{
return false;
}
bool okpercentFee = u.from_bytes(percentFee);
if (!okpercentFee)
{
return false;
}
bool okaccountID = u.from_bytes(accountID);
if (!okaccountID)
{
return false;
}
bool okaccountRole = u.from_bytes(accountRole);
if (!okaccountRole)
{
return false;
}
bool oksubtype = u.from_bytes(subtype);
if (!oksubtype)
{
return false;
}
bool oklowerBound = u.from_bytes(lowerBound);
if (!oklowerBound)
{
return false;
}
bool okupperBound = u.from_bytes(upperBound);
if (!okupperBound)
{
return false;
}
bool okhash = u.from_bytes(hash);
if (!okhash)
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
FeeEntry::to_bytes(xdr::marshaler& m) const 
{
bool okfeeType = m.to_bytes(feeType);
if (!okfeeType)
{
return false;
}
bool okasset = m.to_bytes(asset);
if (!okasset)
{
return false;
}
bool okfixedFee = m.to_bytes(fixedFee);
if (!okfixedFee)
{
return false;
}
bool okpercentFee = m.to_bytes(percentFee);
if (!okpercentFee)
{
return false;
}
bool okaccountID = m.to_bytes(accountID);
if (!okaccountID)
{
return false;
}
bool okaccountRole = m.to_bytes(accountRole);
if (!okaccountRole)
{
return false;
}
bool oksubtype = m.to_bytes(subtype);
if (!oksubtype)
{
return false;
}
bool oklowerBound = m.to_bytes(lowerBound);
if (!oklowerBound)
{
return false;
}
bool okupperBound = m.to_bytes(upperBound);
if (!okupperBound)
{
return false;
}
bool okhash = m.to_bytes(hash);
if (!okhash)
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
FeeEntry::count_size(xdr::measurer& m) const 
{
m.count_size(feeType);
m.count_size(asset);
m.count_size(fixedFee);
m.count_size(percentFee);
m.count_size(accountID);
m.count_size(accountRole);
m.count_size(subtype);
m.count_size(lowerBound);
m.count_size(upperBound);
m.count_size(hash);
m.count_size(ext);
}
bool
FeeEntry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<FeeEntry const&>(other_abstract);return true
&& (feeType== other.feeType)
&& (asset== other.asset)
&& (fixedFee== other.fixedFee)
&& (percentFee== other.percentFee)
&& (accountID== other.accountID)
&& (accountRole== other.accountRole)
&& (subtype== other.subtype)
&& (lowerBound== other.lowerBound)
&& (upperBound== other.upperBound)
&& (hash== other.hash)
&& (ext== other.ext)
;}
bool
FeeEntry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<FeeEntry const&>(other_abstract);
if (feeType < other.feeType) return true;
if (other.feeType < feeType) return false;
if (asset < other.asset) return true;
if (other.asset < asset) return false;
if (fixedFee < other.fixedFee) return true;
if (other.fixedFee < fixedFee) return false;
if (percentFee < other.percentFee) return true;
if (other.percentFee < percentFee) return false;
if (accountID < other.accountID) return true;
if (other.accountID < accountID) return false;
if (accountRole < other.accountRole) return true;
if (other.accountRole < accountRole) return false;
if (subtype < other.subtype) return true;
if (other.subtype < subtype) return false;
if (lowerBound < other.lowerBound) return true;
if (other.lowerBound < lowerBound) return false;
if (upperBound < other.upperBound) return true;
if (other.upperBound < upperBound) return false;
if (hash < other.hash) return true;
if (other.hash < hash) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}