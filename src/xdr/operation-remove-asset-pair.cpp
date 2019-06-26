#include "operation-remove-asset-pair.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
RemoveAssetPairOp::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
RemoveAssetPairOp::_ext_t::to_bytes(xdr::marshaler& m) const
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
RemoveAssetPairOp::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
RemoveAssetPairOp::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
RemoveAssetPairOp::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
RemoveAssetPairOp::from_bytes(xdr::unmarshaler& u) 
{
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
bool okext = u.from_bytes(ext);
if (!okext)
{
return false;
}
return true;
}
bool
RemoveAssetPairOp::to_bytes(xdr::marshaler& m) const 
{
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
bool okext = m.to_bytes(ext);
if (!okext)
{
return false;
}
return true;
}
void
RemoveAssetPairOp::count_size(xdr::measurer& m) const 
{
m.count_size(base);
m.count_size(quote);
m.count_size(ext);
}
bool
RemoveAssetPairOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<RemoveAssetPairOp const&>(other_abstract);return true
&& (base== other.base)
&& (quote== other.quote)
&& (ext== other.ext)
;}
bool
RemoveAssetPairOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<RemoveAssetPairOp const&>(other_abstract);
if (base < other.base) return true;
if (other.base < base) return false;
if (quote < other.quote) return true;
if (other.quote < quote) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
RemoveAssetPairSuccess::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
RemoveAssetPairSuccess::_ext_t::to_bytes(xdr::marshaler& m) const
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
RemoveAssetPairSuccess::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
RemoveAssetPairSuccess::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
RemoveAssetPairSuccess::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
RemoveAssetPairSuccess::from_bytes(xdr::unmarshaler& u) 
{
bool okext = u.from_bytes(ext);
if (!okext)
{
return false;
}
return true;
}
bool
RemoveAssetPairSuccess::to_bytes(xdr::marshaler& m) const 
{
bool okext = m.to_bytes(ext);
if (!okext)
{
return false;
}
return true;
}
void
RemoveAssetPairSuccess::count_size(xdr::measurer& m) const 
{
m.count_size(ext);
}
bool
RemoveAssetPairSuccess::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<RemoveAssetPairSuccess const&>(other_abstract);return true
&& (ext== other.ext)
;}
bool
RemoveAssetPairSuccess::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<RemoveAssetPairSuccess const&>(other_abstract);
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
RemoveAssetPairResult::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)RemoveAssetPairResultCode::SUCCESS:
return u.from_bytes(success_);
  default:
    return true;
}
return false;
}
bool
RemoveAssetPairResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)RemoveAssetPairResultCode::SUCCESS:
return m.to_bytes(success_);
  default:
    return true;
}
return false;
}
void
RemoveAssetPairResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)RemoveAssetPairResultCode::SUCCESS:
return m.count_size(success_);
  default:
  
  return;
}
}
bool
RemoveAssetPairResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<RemoveAssetPairResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)RemoveAssetPairResultCode::SUCCESS:
return success_ == other.success_;
  default:
  
  return true;
}
return false;
}
bool
RemoveAssetPairResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<RemoveAssetPairResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)RemoveAssetPairResultCode::SUCCESS:
return success_ < other.success_;
  default:
    return false;
}
return false;
}
}