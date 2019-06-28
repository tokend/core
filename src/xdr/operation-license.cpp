#include "operation-license.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
LicenseOp::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
LicenseOp::_ext_t::to_bytes(xdr::marshaler& m) const
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
LicenseOp::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
LicenseOp::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
LicenseOp::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
LicenseOp::from_bytes(xdr::unmarshaler& u) 
{
bool okadminCount = u.from_bytes(adminCount);
if (!okadminCount)
{
return false;
}
bool okdueDate = u.from_bytes(dueDate);
if (!okdueDate)
{
return false;
}
bool okledgerHash = u.from_bytes(ledgerHash);
if (!okledgerHash)
{
return false;
}
bool okprevLicenseHash = u.from_bytes(prevLicenseHash);
if (!okprevLicenseHash)
{
return false;
}
bool oksignatures = u.from_bytes(signatures);
if (!oksignatures)
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
LicenseOp::to_bytes(xdr::marshaler& m) const 
{
bool okadminCount = m.to_bytes(adminCount);
if (!okadminCount)
{
return false;
}
bool okdueDate = m.to_bytes(dueDate);
if (!okdueDate)
{
return false;
}
bool okledgerHash = m.to_bytes(ledgerHash);
if (!okledgerHash)
{
return false;
}
bool okprevLicenseHash = m.to_bytes(prevLicenseHash);
if (!okprevLicenseHash)
{
return false;
}
bool oksignatures = m.to_bytes(signatures);
if (!oksignatures)
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
LicenseOp::count_size(xdr::measurer& m) const 
{
m.count_size(adminCount);
m.count_size(dueDate);
m.count_size(ledgerHash);
m.count_size(prevLicenseHash);
m.count_size(signatures);
m.count_size(ext);
}
bool
LicenseOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<LicenseOp const&>(other_abstract);return true
&& (adminCount== other.adminCount)
&& (dueDate== other.dueDate)
&& (ledgerHash== other.ledgerHash)
&& (prevLicenseHash== other.prevLicenseHash)
&& (signatures== other.signatures)
&& (ext== other.ext)
;}
bool
LicenseOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<LicenseOp const&>(other_abstract);
if (adminCount < other.adminCount) return true;
if (other.adminCount < adminCount) return false;
if (dueDate < other.dueDate) return true;
if (other.dueDate < dueDate) return false;
if (ledgerHash < other.ledgerHash) return true;
if (other.ledgerHash < ledgerHash) return false;
if (prevLicenseHash < other.prevLicenseHash) return true;
if (other.prevLicenseHash < prevLicenseHash) return false;
if (signatures < other.signatures) return true;
if (other.signatures < signatures) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LicenseSuccess::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
LicenseSuccess::_ext_t::to_bytes(xdr::marshaler& m) const
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
LicenseSuccess::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
LicenseSuccess::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
LicenseSuccess::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
LicenseSuccess::from_bytes(xdr::unmarshaler& u) 
{
bool okext = u.from_bytes(ext);
if (!okext)
{
return false;
}
return true;
}
bool
LicenseSuccess::to_bytes(xdr::marshaler& m) const 
{
bool okext = m.to_bytes(ext);
if (!okext)
{
return false;
}
return true;
}
void
LicenseSuccess::count_size(xdr::measurer& m) const 
{
m.count_size(ext);
}
bool
LicenseSuccess::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<LicenseSuccess const&>(other_abstract);return true
&& (ext== other.ext)
;}
bool
LicenseSuccess::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<LicenseSuccess const&>(other_abstract);
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LicenseResult::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (code_)
{
  case (int32_t)LicenseResultCode::SUCCESS:
return u.from_bytes(success_);
  default:
  
  return true;
}
return false;
}
bool
LicenseResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)LicenseResultCode::SUCCESS:
return m.to_bytes(success_);
  default:
    return true;
}
return false;
}
void
LicenseResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)LicenseResultCode::SUCCESS:
return m.count_size(success_);
  default:
  
  return;
}
}
bool
LicenseResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<LicenseResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)LicenseResultCode::SUCCESS:
return success_ == other.success_;
  default:
  
  return true;
}
return false;
}
bool
LicenseResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<LicenseResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)LicenseResultCode::SUCCESS:
return success_ < other.success_;
  default:
    return false;
}
return false;
}
}