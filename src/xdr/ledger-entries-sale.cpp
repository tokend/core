#include "ledger-entries-sale.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
FixedPriceSale::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
FixedPriceSale::_ext_t::to_bytes(xdr::marshaler& m) const
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
FixedPriceSale::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
FixedPriceSale::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
FixedPriceSale::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
FixedPriceSale::from_bytes(xdr::unmarshaler& u) 
{
bool okext = u.from_bytes(ext);
if (!okext)
{
return false;
}
return true;
}
bool
FixedPriceSale::to_bytes(xdr::marshaler& m) const 
{
bool okext = m.to_bytes(ext);
if (!okext)
{
return false;
}
return true;
}
void
FixedPriceSale::count_size(xdr::measurer& m) const 
{
m.count_size(ext);
}
bool
FixedPriceSale::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<FixedPriceSale const&>(other_abstract);return true
&& (ext== other.ext)
;}
bool
FixedPriceSale::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<FixedPriceSale const&>(other_abstract);
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
CrowdFundingSale::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
CrowdFundingSale::_ext_t::to_bytes(xdr::marshaler& m) const
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
CrowdFundingSale::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
CrowdFundingSale::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
CrowdFundingSale::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
CrowdFundingSale::from_bytes(xdr::unmarshaler& u) 
{
bool okext = u.from_bytes(ext);
if (!okext)
{
return false;
}
return true;
}
bool
CrowdFundingSale::to_bytes(xdr::marshaler& m) const 
{
bool okext = m.to_bytes(ext);
if (!okext)
{
return false;
}
return true;
}
void
CrowdFundingSale::count_size(xdr::measurer& m) const 
{
m.count_size(ext);
}
bool
CrowdFundingSale::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CrowdFundingSale const&>(other_abstract);return true
&& (ext== other.ext)
;}
bool
CrowdFundingSale::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CrowdFundingSale const&>(other_abstract);
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
BasicSale::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
BasicSale::_ext_t::to_bytes(xdr::marshaler& m) const
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
BasicSale::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
BasicSale::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
BasicSale::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
BasicSale::from_bytes(xdr::unmarshaler& u) 
{
bool okext = u.from_bytes(ext);
if (!okext)
{
return false;
}
return true;
}
bool
BasicSale::to_bytes(xdr::marshaler& m) const 
{
bool okext = m.to_bytes(ext);
if (!okext)
{
return false;
}
return true;
}
void
BasicSale::count_size(xdr::measurer& m) const 
{
m.count_size(ext);
}
bool
BasicSale::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<BasicSale const&>(other_abstract);return true
&& (ext== other.ext)
;}
bool
BasicSale::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<BasicSale const&>(other_abstract);
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ImmediateSale::from_bytes(xdr::unmarshaler& u) 
{
bool okext = u.from_bytes(ext);
if (!okext)
{
return false;
}
return true;
}
bool
ImmediateSale::to_bytes(xdr::marshaler& m) const 
{
bool okext = m.to_bytes(ext);
if (!okext)
{
return false;
}
return true;
}
void
ImmediateSale::count_size(xdr::measurer& m) const 
{
m.count_size(ext);
}
bool
ImmediateSale::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<ImmediateSale const&>(other_abstract);return true
&& (ext== other.ext)
;}
bool
ImmediateSale::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ImmediateSale const&>(other_abstract);
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
SaleTypeExt::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (saleType_)
{
  case (int32_t)SaleType::BASIC_SALE:
return u.from_bytes(basicSale_);
  case (int32_t)SaleType::CROWD_FUNDING:
return u.from_bytes(crowdFundingSale_);
  case (int32_t)SaleType::FIXED_PRICE:
return u.from_bytes(fixedPriceSale_);
  case (int32_t)SaleType::IMMEDIATE:
return u.from_bytes(immediateSale_);
}
return false;
}
bool
SaleTypeExt::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(saleType_);
if (!ok)
{
return false;
}
switch (saleType_)
{

  case (int32_t)SaleType::BASIC_SALE:
return m.to_bytes(basicSale_);
  case (int32_t)SaleType::CROWD_FUNDING:
return m.to_bytes(crowdFundingSale_);
  case (int32_t)SaleType::FIXED_PRICE:
return m.to_bytes(fixedPriceSale_);
  case (int32_t)SaleType::IMMEDIATE:
return m.to_bytes(immediateSale_);
}
return false;
}
void
SaleTypeExt::count_size(xdr::measurer& m) const
{
m.count_size(saleType_);
switch (saleType_)
{

  case (int32_t)SaleType::BASIC_SALE:
return m.count_size(basicSale_);
  case (int32_t)SaleType::CROWD_FUNDING:
return m.count_size(crowdFundingSale_);
  case (int32_t)SaleType::FIXED_PRICE:
return m.count_size(fixedPriceSale_);
  case (int32_t)SaleType::IMMEDIATE:
return m.count_size(immediateSale_);
}
}
bool
SaleTypeExt::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<SaleTypeExt const&>(other_abstract);
if (other.saleType_ != saleType_) return false;
switch (saleType_)
{
  case (int32_t)SaleType::BASIC_SALE:
return basicSale_ == other.basicSale_;
  case (int32_t)SaleType::CROWD_FUNDING:
return crowdFundingSale_ == other.crowdFundingSale_;
  case (int32_t)SaleType::FIXED_PRICE:
return fixedPriceSale_ == other.fixedPriceSale_;
  case (int32_t)SaleType::IMMEDIATE:
return immediateSale_ == other.immediateSale_;
}
return false;
}
bool
SaleTypeExt::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<SaleTypeExt const&>(other_abstract);
if (saleType_ < other.saleType_) return true;
if (other.saleType_ < saleType_) return false;
switch (saleType_)
{
  case (int32_t)SaleType::BASIC_SALE:
return basicSale_ < other.basicSale_;
  case (int32_t)SaleType::CROWD_FUNDING:
return crowdFundingSale_ < other.crowdFundingSale_;
  case (int32_t)SaleType::FIXED_PRICE:
return fixedPriceSale_ < other.fixedPriceSale_;
  case (int32_t)SaleType::IMMEDIATE:
return immediateSale_ < other.immediateSale_;
}
return false;
}
bool
SaleQuoteAsset::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
SaleQuoteAsset::_ext_t::to_bytes(xdr::marshaler& m) const
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
SaleQuoteAsset::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
SaleQuoteAsset::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
SaleQuoteAsset::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
SaleQuoteAsset::from_bytes(xdr::unmarshaler& u) 
{
bool okquoteAsset = u.from_bytes(quoteAsset);
if (!okquoteAsset)
{
return false;
}
bool okprice = u.from_bytes(price);
if (!okprice)
{
return false;
}
bool okquoteBalance = u.from_bytes(quoteBalance);
if (!okquoteBalance)
{
return false;
}
bool okcurrentCap = u.from_bytes(currentCap);
if (!okcurrentCap)
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
SaleQuoteAsset::to_bytes(xdr::marshaler& m) const 
{
bool okquoteAsset = m.to_bytes(quoteAsset);
if (!okquoteAsset)
{
return false;
}
bool okprice = m.to_bytes(price);
if (!okprice)
{
return false;
}
bool okquoteBalance = m.to_bytes(quoteBalance);
if (!okquoteBalance)
{
return false;
}
bool okcurrentCap = m.to_bytes(currentCap);
if (!okcurrentCap)
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
SaleQuoteAsset::count_size(xdr::measurer& m) const 
{
m.count_size(quoteAsset);
m.count_size(price);
m.count_size(quoteBalance);
m.count_size(currentCap);
m.count_size(ext);
}
bool
SaleQuoteAsset::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<SaleQuoteAsset const&>(other_abstract);return true
&& (quoteAsset== other.quoteAsset)
&& (price== other.price)
&& (quoteBalance== other.quoteBalance)
&& (currentCap== other.currentCap)
&& (ext== other.ext)
;}
bool
SaleQuoteAsset::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<SaleQuoteAsset const&>(other_abstract);
if (quoteAsset < other.quoteAsset) return true;
if (other.quoteAsset < quoteAsset) return false;
if (price < other.price) return true;
if (other.price < price) return false;
if (quoteBalance < other.quoteBalance) return true;
if (other.quoteBalance < quoteBalance) return false;
if (currentCap < other.currentCap) return true;
if (other.currentCap < currentCap) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
SaleEntry::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
    case (int32_t)LedgerVersion::ADD_SALE_WHITELISTS:
    
  return true;
}
return false;
}
bool
SaleEntry::_ext_t::to_bytes(xdr::marshaler& m) const
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
    case (int32_t)LedgerVersion::ADD_SALE_WHITELISTS:
      return true;
}
return false;
}
void
SaleEntry::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
    case (int32_t)LedgerVersion::ADD_SALE_WHITELISTS:
    
  return;
}
}
bool
SaleEntry::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
    case (int32_t)LedgerVersion::ADD_SALE_WHITELISTS:
    
  return true;
}
return false;
}
bool
SaleEntry::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
    case (int32_t)LedgerVersion::ADD_SALE_WHITELISTS:
      return false;
}
return false;
}
bool
SaleEntry::from_bytes(xdr::unmarshaler& u) 
{
bool oksaleID = u.from_bytes(saleID);
if (!oksaleID)
{
return false;
}
bool oksaleType = u.from_bytes(saleType);
if (!oksaleType)
{
return false;
}
bool okownerID = u.from_bytes(ownerID);
if (!okownerID)
{
return false;
}
bool okbaseAsset = u.from_bytes(baseAsset);
if (!okbaseAsset)
{
return false;
}
bool okstartTime = u.from_bytes(startTime);
if (!okstartTime)
{
return false;
}
bool okendTime = u.from_bytes(endTime);
if (!okendTime)
{
return false;
}
bool okdefaultQuoteAsset = u.from_bytes(defaultQuoteAsset);
if (!okdefaultQuoteAsset)
{
return false;
}
bool oksoftCap = u.from_bytes(softCap);
if (!oksoftCap)
{
return false;
}
bool okhardCap = u.from_bytes(hardCap);
if (!okhardCap)
{
return false;
}
bool okcurrentCapInBase = u.from_bytes(currentCapInBase);
if (!okcurrentCapInBase)
{
return false;
}
bool okmaxAmountToBeSold = u.from_bytes(maxAmountToBeSold);
if (!okmaxAmountToBeSold)
{
return false;
}
bool okdetails = u.from_bytes(details);
if (!okdetails)
{
return false;
}
bool okquoteAssets = u.from_bytes(quoteAssets);
if (!okquoteAssets)
{
return false;
}
bool okbaseBalance = u.from_bytes(baseBalance);
if (!okbaseBalance)
{
return false;
}
bool oksaleTypeExt = u.from_bytes(saleTypeExt);
if (!oksaleTypeExt)
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
SaleEntry::to_bytes(xdr::marshaler& m) const 
{
bool oksaleID = m.to_bytes(saleID);
if (!oksaleID)
{
return false;
}
bool oksaleType = m.to_bytes(saleType);
if (!oksaleType)
{
return false;
}
bool okownerID = m.to_bytes(ownerID);
if (!okownerID)
{
return false;
}
bool okbaseAsset = m.to_bytes(baseAsset);
if (!okbaseAsset)
{
return false;
}
bool okstartTime = m.to_bytes(startTime);
if (!okstartTime)
{
return false;
}
bool okendTime = m.to_bytes(endTime);
if (!okendTime)
{
return false;
}
bool okdefaultQuoteAsset = m.to_bytes(defaultQuoteAsset);
if (!okdefaultQuoteAsset)
{
return false;
}
bool oksoftCap = m.to_bytes(softCap);
if (!oksoftCap)
{
return false;
}
bool okhardCap = m.to_bytes(hardCap);
if (!okhardCap)
{
return false;
}
bool okcurrentCapInBase = m.to_bytes(currentCapInBase);
if (!okcurrentCapInBase)
{
return false;
}
bool okmaxAmountToBeSold = m.to_bytes(maxAmountToBeSold);
if (!okmaxAmountToBeSold)
{
return false;
}
bool okdetails = m.to_bytes(details);
if (!okdetails)
{
return false;
}
bool okquoteAssets = m.to_bytes(quoteAssets);
if (!okquoteAssets)
{
return false;
}
bool okbaseBalance = m.to_bytes(baseBalance);
if (!okbaseBalance)
{
return false;
}
bool oksaleTypeExt = m.to_bytes(saleTypeExt);
if (!oksaleTypeExt)
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
SaleEntry::count_size(xdr::measurer& m) const 
{
m.count_size(saleID);
m.count_size(saleType);
m.count_size(ownerID);
m.count_size(baseAsset);
m.count_size(startTime);
m.count_size(endTime);
m.count_size(defaultQuoteAsset);
m.count_size(softCap);
m.count_size(hardCap);
m.count_size(currentCapInBase);
m.count_size(maxAmountToBeSold);
m.count_size(details);
m.count_size(quoteAssets);
m.count_size(baseBalance);
m.count_size(saleTypeExt);
m.count_size(ext);
}
bool
SaleEntry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<SaleEntry const&>(other_abstract);return true
&& (saleID== other.saleID)
&& (saleType== other.saleType)
&& (ownerID== other.ownerID)
&& (baseAsset== other.baseAsset)
&& (startTime== other.startTime)
&& (endTime== other.endTime)
&& (defaultQuoteAsset== other.defaultQuoteAsset)
&& (softCap== other.softCap)
&& (hardCap== other.hardCap)
&& (currentCapInBase== other.currentCapInBase)
&& (maxAmountToBeSold== other.maxAmountToBeSold)
&& (details== other.details)
&& (quoteAssets== other.quoteAssets)
&& (baseBalance== other.baseBalance)
&& (saleTypeExt== other.saleTypeExt)
&& (ext== other.ext)
;}
bool
SaleEntry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<SaleEntry const&>(other_abstract);
if (saleID < other.saleID) return true;
if (other.saleID < saleID) return false;
if (saleType < other.saleType) return true;
if (other.saleType < saleType) return false;
if (ownerID < other.ownerID) return true;
if (other.ownerID < ownerID) return false;
if (baseAsset < other.baseAsset) return true;
if (other.baseAsset < baseAsset) return false;
if (startTime < other.startTime) return true;
if (other.startTime < startTime) return false;
if (endTime < other.endTime) return true;
if (other.endTime < endTime) return false;
if (defaultQuoteAsset < other.defaultQuoteAsset) return true;
if (other.defaultQuoteAsset < defaultQuoteAsset) return false;
if (softCap < other.softCap) return true;
if (other.softCap < softCap) return false;
if (hardCap < other.hardCap) return true;
if (other.hardCap < hardCap) return false;
if (currentCapInBase < other.currentCapInBase) return true;
if (other.currentCapInBase < currentCapInBase) return false;
if (maxAmountToBeSold < other.maxAmountToBeSold) return true;
if (other.maxAmountToBeSold < maxAmountToBeSold) return false;
if (details < other.details) return true;
if (other.details < details) return false;
if (quoteAssets < other.quoteAssets) return true;
if (other.quoteAssets < quoteAssets) return false;
if (baseBalance < other.baseBalance) return true;
if (other.baseBalance < baseBalance) return false;
if (saleTypeExt < other.saleTypeExt) return true;
if (other.saleTypeExt < saleTypeExt) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}