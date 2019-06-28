#include "operation-manage-asset-pair.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
ManageAssetPairOp::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ManageAssetPairOp::_ext_t::to_bytes(xdr::marshaler& m) const
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
ManageAssetPairOp::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
ManageAssetPairOp::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ManageAssetPairOp::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ManageAssetPairOp::from_bytes(xdr::unmarshaler& u) 
{
bool okaction = u.from_bytes(action);
if (!okaction)
{
return false;
}
bool okbase = u.from_bytes(base);
if (!okbase)
{
return false;
}
bool okquote = u.from_bytes(quote);
if (!okquote)
{
return false;
}
bool okphysicalPrice = u.from_bytes(physicalPrice);
if (!okphysicalPrice)
{
return false;
}
bool okphysicalPriceCorrection = u.from_bytes(physicalPriceCorrection);
if (!okphysicalPriceCorrection)
{
return false;
}
bool okmaxPriceStep = u.from_bytes(maxPriceStep);
if (!okmaxPriceStep)
{
return false;
}
bool okpolicies = u.from_bytes(policies);
if (!okpolicies)
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
ManageAssetPairOp::to_bytes(xdr::marshaler& m) const 
{
bool okaction = m.to_bytes(action);
if (!okaction)
{
return false;
}
bool okbase = m.to_bytes(base);
if (!okbase)
{
return false;
}
bool okquote = m.to_bytes(quote);
if (!okquote)
{
return false;
}
bool okphysicalPrice = m.to_bytes(physicalPrice);
if (!okphysicalPrice)
{
return false;
}
bool okphysicalPriceCorrection = m.to_bytes(physicalPriceCorrection);
if (!okphysicalPriceCorrection)
{
return false;
}
bool okmaxPriceStep = m.to_bytes(maxPriceStep);
if (!okmaxPriceStep)
{
return false;
}
bool okpolicies = m.to_bytes(policies);
if (!okpolicies)
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
ManageAssetPairOp::count_size(xdr::measurer& m) const 
{
m.count_size(action);
m.count_size(base);
m.count_size(quote);
m.count_size(physicalPrice);
m.count_size(physicalPriceCorrection);
m.count_size(maxPriceStep);
m.count_size(policies);
m.count_size(ext);
}
bool
ManageAssetPairOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<ManageAssetPairOp const&>(other_abstract);return true
&& (action== other.action)
&& (base== other.base)
&& (quote== other.quote)
&& (physicalPrice== other.physicalPrice)
&& (physicalPriceCorrection== other.physicalPriceCorrection)
&& (maxPriceStep== other.maxPriceStep)
&& (policies== other.policies)
&& (ext== other.ext)
;}
bool
ManageAssetPairOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManageAssetPairOp const&>(other_abstract);
if (action < other.action) return true;
if (other.action < action) return false;
if (base < other.base) return true;
if (other.base < base) return false;
if (quote < other.quote) return true;
if (other.quote < quote) return false;
if (physicalPrice < other.physicalPrice) return true;
if (other.physicalPrice < physicalPrice) return false;
if (physicalPriceCorrection < other.physicalPriceCorrection) return true;
if (other.physicalPriceCorrection < physicalPriceCorrection) return false;
if (maxPriceStep < other.maxPriceStep) return true;
if (other.maxPriceStep < maxPriceStep) return false;
if (policies < other.policies) return true;
if (other.policies < policies) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageAssetPairSuccess::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ManageAssetPairSuccess::_ext_t::to_bytes(xdr::marshaler& m) const
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
ManageAssetPairSuccess::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
ManageAssetPairSuccess::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ManageAssetPairSuccess::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ManageAssetPairSuccess::from_bytes(xdr::unmarshaler& u) 
{
bool okcurrentPrice = u.from_bytes(currentPrice);
if (!okcurrentPrice)
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
ManageAssetPairSuccess::to_bytes(xdr::marshaler& m) const 
{
bool okcurrentPrice = m.to_bytes(currentPrice);
if (!okcurrentPrice)
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
ManageAssetPairSuccess::count_size(xdr::measurer& m) const 
{
m.count_size(currentPrice);
m.count_size(ext);
}
bool
ManageAssetPairSuccess::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<ManageAssetPairSuccess const&>(other_abstract);return true
&& (currentPrice== other.currentPrice)
&& (ext== other.ext)
;}
bool
ManageAssetPairSuccess::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManageAssetPairSuccess const&>(other_abstract);
if (currentPrice < other.currentPrice) return true;
if (other.currentPrice < currentPrice) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageAssetPairResult::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (code_)
{
  case (int32_t)ManageAssetPairResultCode::SUCCESS:
return u.from_bytes(success_);
  default:
  
  return true;
}
return false;
}
bool
ManageAssetPairResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)ManageAssetPairResultCode::SUCCESS:
return m.to_bytes(success_);
  default:
    return true;
}
return false;
}
void
ManageAssetPairResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)ManageAssetPairResultCode::SUCCESS:
return m.count_size(success_);
  default:
  
  return;
}
}
bool
ManageAssetPairResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<ManageAssetPairResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)ManageAssetPairResultCode::SUCCESS:
return success_ == other.success_;
  default:
  
  return true;
}
return false;
}
bool
ManageAssetPairResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManageAssetPairResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)ManageAssetPairResultCode::SUCCESS:
return success_ < other.success_;
  default:
    return false;
}
return false;
}
}