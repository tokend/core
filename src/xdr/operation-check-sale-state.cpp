#include "operation-check-sale-state.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
CheckSaleStateOp::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
CheckSaleStateOp::_ext_t::to_bytes(xdr::marshaler& m) const
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
CheckSaleStateOp::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
CheckSaleStateOp::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
CheckSaleStateOp::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
CheckSaleStateOp::from_bytes(xdr::unmarshaler& u) 
{
bool oksaleID = u.from_bytes(saleID);
if (!oksaleID)
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
CheckSaleStateOp::to_bytes(xdr::marshaler& m) const 
{
bool oksaleID = m.to_bytes(saleID);
if (!oksaleID)
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
CheckSaleStateOp::count_size(xdr::measurer& m) const 
{
m.count_size(saleID);
m.count_size(ext);
}
bool
CheckSaleStateOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CheckSaleStateOp const&>(other_abstract);return true
&& (saleID== other.saleID)
&& (ext== other.ext)
;}
bool
CheckSaleStateOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CheckSaleStateOp const&>(other_abstract);
if (saleID < other.saleID) return true;
if (other.saleID < saleID) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
SaleCanceled::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
SaleCanceled::_ext_t::to_bytes(xdr::marshaler& m) const
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
SaleCanceled::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
SaleCanceled::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
SaleCanceled::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
SaleCanceled::from_bytes(xdr::unmarshaler& u) 
{
bool okext = u.from_bytes(ext);
if (!okext)
{
return false;
}
return true;
}
bool
SaleCanceled::to_bytes(xdr::marshaler& m) const 
{
bool okext = m.to_bytes(ext);
if (!okext)
{
return false;
}
return true;
}
void
SaleCanceled::count_size(xdr::measurer& m) const 
{
m.count_size(ext);
}
bool
SaleCanceled::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<SaleCanceled const&>(other_abstract);return true
&& (ext== other.ext)
;}
bool
SaleCanceled::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<SaleCanceled const&>(other_abstract);
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
SaleUpdated::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
SaleUpdated::_ext_t::to_bytes(xdr::marshaler& m) const
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
SaleUpdated::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
SaleUpdated::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
SaleUpdated::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
SaleUpdated::from_bytes(xdr::unmarshaler& u) 
{
bool okext = u.from_bytes(ext);
if (!okext)
{
return false;
}
return true;
}
bool
SaleUpdated::to_bytes(xdr::marshaler& m) const 
{
bool okext = m.to_bytes(ext);
if (!okext)
{
return false;
}
return true;
}
void
SaleUpdated::count_size(xdr::measurer& m) const 
{
m.count_size(ext);
}
bool
SaleUpdated::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<SaleUpdated const&>(other_abstract);return true
&& (ext== other.ext)
;}
bool
SaleUpdated::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<SaleUpdated const&>(other_abstract);
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
CheckSubSaleClosedResult::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
CheckSubSaleClosedResult::_ext_t::to_bytes(xdr::marshaler& m) const
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
CheckSubSaleClosedResult::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
CheckSubSaleClosedResult::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
CheckSubSaleClosedResult::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
CheckSubSaleClosedResult::from_bytes(xdr::unmarshaler& u) 
{
bool oksaleBaseBalance = u.from_bytes(saleBaseBalance);
if (!oksaleBaseBalance)
{
return false;
}
bool oksaleQuoteBalance = u.from_bytes(saleQuoteBalance);
if (!oksaleQuoteBalance)
{
return false;
}
bool oksaleDetails = u.from_bytes(saleDetails);
if (!oksaleDetails)
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
CheckSubSaleClosedResult::to_bytes(xdr::marshaler& m) const 
{
bool oksaleBaseBalance = m.to_bytes(saleBaseBalance);
if (!oksaleBaseBalance)
{
return false;
}
bool oksaleQuoteBalance = m.to_bytes(saleQuoteBalance);
if (!oksaleQuoteBalance)
{
return false;
}
bool oksaleDetails = m.to_bytes(saleDetails);
if (!oksaleDetails)
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
CheckSubSaleClosedResult::count_size(xdr::measurer& m) const 
{
m.count_size(saleBaseBalance);
m.count_size(saleQuoteBalance);
m.count_size(saleDetails);
m.count_size(ext);
}
bool
CheckSubSaleClosedResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CheckSubSaleClosedResult const&>(other_abstract);return true
&& (saleBaseBalance== other.saleBaseBalance)
&& (saleQuoteBalance== other.saleQuoteBalance)
&& (saleDetails== other.saleDetails)
&& (ext== other.ext)
;}
bool
CheckSubSaleClosedResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CheckSubSaleClosedResult const&>(other_abstract);
if (saleBaseBalance < other.saleBaseBalance) return true;
if (other.saleBaseBalance < saleBaseBalance) return false;
if (saleQuoteBalance < other.saleQuoteBalance) return true;
if (other.saleQuoteBalance < saleQuoteBalance) return false;
if (saleDetails < other.saleDetails) return true;
if (other.saleDetails < saleDetails) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
CheckSaleClosedResult::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
CheckSaleClosedResult::_ext_t::to_bytes(xdr::marshaler& m) const
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
CheckSaleClosedResult::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
CheckSaleClosedResult::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
CheckSaleClosedResult::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
CheckSaleClosedResult::from_bytes(xdr::unmarshaler& u) 
{
bool oksaleOwner = u.from_bytes(saleOwner);
if (!oksaleOwner)
{
return false;
}
bool okresults = u.from_bytes(results);
if (!okresults)
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
CheckSaleClosedResult::to_bytes(xdr::marshaler& m) const 
{
bool oksaleOwner = m.to_bytes(saleOwner);
if (!oksaleOwner)
{
return false;
}
bool okresults = m.to_bytes(results);
if (!okresults)
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
CheckSaleClosedResult::count_size(xdr::measurer& m) const 
{
m.count_size(saleOwner);
m.count_size(results);
m.count_size(ext);
}
bool
CheckSaleClosedResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CheckSaleClosedResult const&>(other_abstract);return true
&& (saleOwner== other.saleOwner)
&& (results== other.results)
&& (ext== other.ext)
;}
bool
CheckSaleClosedResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CheckSaleClosedResult const&>(other_abstract);
if (saleOwner < other.saleOwner) return true;
if (other.saleOwner < saleOwner) return false;
if (results < other.results) return true;
if (other.results < results) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
CheckSaleStateSuccess::_effect_t::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (effect_)
{
    case (int32_t)CheckSaleStateEffect::CANCELED:
return u.from_bytes(saleCanceled_);
    case (int32_t)CheckSaleStateEffect::CLOSED:
return u.from_bytes(saleClosed_);
    case (int32_t)CheckSaleStateEffect::UPDATED:
return u.from_bytes(saleUpdated_);
}
return false;
}
bool
CheckSaleStateSuccess::_effect_t::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(effect_);
if (!ok)
{
return false;
}
switch (effect_)
{

    case (int32_t)CheckSaleStateEffect::CANCELED:
return m.to_bytes(saleCanceled_);
    case (int32_t)CheckSaleStateEffect::CLOSED:
return m.to_bytes(saleClosed_);
    case (int32_t)CheckSaleStateEffect::UPDATED:
return m.to_bytes(saleUpdated_);
}
return false;
}
void
CheckSaleStateSuccess::_effect_t::count_size(xdr::measurer& m) const
{
m.count_size(effect_);
switch (effect_)
{

    case (int32_t)CheckSaleStateEffect::CANCELED:
return m.count_size(saleCanceled_);
    case (int32_t)CheckSaleStateEffect::CLOSED:
return m.count_size(saleClosed_);
    case (int32_t)CheckSaleStateEffect::UPDATED:
return m.count_size(saleUpdated_);
}
}
bool
CheckSaleStateSuccess::_effect_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_effect_t const&>(other_abstract);
if (other.effect_ != effect_) return false;
switch (effect_)
{
    case (int32_t)CheckSaleStateEffect::CANCELED:
return saleCanceled_ == other.saleCanceled_;
    case (int32_t)CheckSaleStateEffect::CLOSED:
return saleClosed_ == other.saleClosed_;
    case (int32_t)CheckSaleStateEffect::UPDATED:
return saleUpdated_ == other.saleUpdated_;
}
return false;
}
bool
CheckSaleStateSuccess::_effect_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_effect_t const&>(other_abstract);
if (effect_ < other.effect_) return true;
if (other.effect_ < effect_) return false;
switch (effect_)
{
    case (int32_t)CheckSaleStateEffect::CANCELED:
return saleCanceled_ < other.saleCanceled_;
    case (int32_t)CheckSaleStateEffect::CLOSED:
return saleClosed_ < other.saleClosed_;
    case (int32_t)CheckSaleStateEffect::UPDATED:
return saleUpdated_ < other.saleUpdated_;
}
return false;
}
bool
CheckSaleStateSuccess::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
CheckSaleStateSuccess::_ext_t::to_bytes(xdr::marshaler& m) const
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
CheckSaleStateSuccess::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
CheckSaleStateSuccess::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
CheckSaleStateSuccess::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
CheckSaleStateSuccess::from_bytes(xdr::unmarshaler& u) 
{
bool oksaleID = u.from_bytes(saleID);
if (!oksaleID)
{
return false;
}
bool okeffect = u.from_bytes(effect);
if (!okeffect)
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
CheckSaleStateSuccess::to_bytes(xdr::marshaler& m) const 
{
bool oksaleID = m.to_bytes(saleID);
if (!oksaleID)
{
return false;
}
bool okeffect = m.to_bytes(effect);
if (!okeffect)
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
CheckSaleStateSuccess::count_size(xdr::measurer& m) const 
{
m.count_size(saleID);
m.count_size(effect);
m.count_size(ext);
}
bool
CheckSaleStateSuccess::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CheckSaleStateSuccess const&>(other_abstract);return true
&& (saleID== other.saleID)
&& (effect== other.effect)
&& (ext== other.ext)
;}
bool
CheckSaleStateSuccess::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CheckSaleStateSuccess const&>(other_abstract);
if (saleID < other.saleID) return true;
if (other.saleID < saleID) return false;
if (effect < other.effect) return true;
if (other.effect < effect) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
CheckSaleStateResult::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (code_)
{
  case (int32_t)CheckSaleStateResultCode::SUCCESS:
return u.from_bytes(success_);
  default:
  
  return true;
}
return false;
}
bool
CheckSaleStateResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)CheckSaleStateResultCode::SUCCESS:
return m.to_bytes(success_);
  default:
    return true;
}
return false;
}
void
CheckSaleStateResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)CheckSaleStateResultCode::SUCCESS:
return m.count_size(success_);
  default:
  
  return;
}
}
bool
CheckSaleStateResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<CheckSaleStateResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)CheckSaleStateResultCode::SUCCESS:
return success_ == other.success_;
  default:
  
  return true;
}
return false;
}
bool
CheckSaleStateResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CheckSaleStateResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)CheckSaleStateResultCode::SUCCESS:
return success_ < other.success_;
  default:
    return false;
}
return false;
}
}