#include "reviewable-request-sale.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
SaleCreationRequestQuoteAsset::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
SaleCreationRequestQuoteAsset::_ext_t::to_bytes(xdr::marshaler& m) const
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
SaleCreationRequestQuoteAsset::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
SaleCreationRequestQuoteAsset::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
SaleCreationRequestQuoteAsset::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
SaleCreationRequestQuoteAsset::from_bytes(xdr::unmarshaler& u) 
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
bool okext = u.from_bytes(ext);
if (!okext)
{
return false;
}
return true;
}
bool
SaleCreationRequestQuoteAsset::to_bytes(xdr::marshaler& m) const 
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
bool okext = m.to_bytes(ext);
if (!okext)
{
return false;
}
return true;
}
void
SaleCreationRequestQuoteAsset::count_size(xdr::measurer& m) const 
{
m.count_size(quoteAsset);
m.count_size(price);
m.count_size(ext);
}
bool
SaleCreationRequestQuoteAsset::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<SaleCreationRequestQuoteAsset const&>(other_abstract);return true
&& (quoteAsset== other.quoteAsset)
&& (price== other.price)
&& (ext== other.ext)
;}
bool
SaleCreationRequestQuoteAsset::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<SaleCreationRequestQuoteAsset const&>(other_abstract);
if (quoteAsset < other.quoteAsset) return true;
if (other.quoteAsset < quoteAsset) return false;
if (price < other.price) return true;
if (other.price < price) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
CreateAccountSaleRuleData::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
CreateAccountSaleRuleData::_ext_t::to_bytes(xdr::marshaler& m) const
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
CreateAccountSaleRuleData::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
CreateAccountSaleRuleData::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
CreateAccountSaleRuleData::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
CreateAccountSaleRuleData::from_bytes(xdr::unmarshaler& u) 
{
bool okaccountID = u.from_bytes(accountID);
if (!okaccountID)
{
return false;
}
bool okforbids = u.from_bytes(forbids);
if (!okforbids)
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
CreateAccountSaleRuleData::to_bytes(xdr::marshaler& m) const 
{
bool okaccountID = m.to_bytes(accountID);
if (!okaccountID)
{
return false;
}
bool okforbids = m.to_bytes(forbids);
if (!okforbids)
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
CreateAccountSaleRuleData::count_size(xdr::measurer& m) const 
{
m.count_size(accountID);
m.count_size(forbids);
m.count_size(ext);
}
bool
CreateAccountSaleRuleData::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CreateAccountSaleRuleData const&>(other_abstract);return true
&& (accountID== other.accountID)
&& (forbids== other.forbids)
&& (ext== other.ext)
;}
bool
CreateAccountSaleRuleData::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreateAccountSaleRuleData const&>(other_abstract);
if (accountID < other.accountID) return true;
if (other.accountID < accountID) return false;
if (forbids < other.forbids) return true;
if (other.forbids < forbids) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
SaleCreationRequest::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
    case (int32_t)LedgerVersion::ADD_SALE_WHITELISTS:
return u.from_bytes(saleRules_);
}
return false;
}
bool
SaleCreationRequest::_ext_t::to_bytes(xdr::marshaler& m) const
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
return m.to_bytes(saleRules_);
}
return false;
}
void
SaleCreationRequest::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
    case (int32_t)LedgerVersion::ADD_SALE_WHITELISTS:
return m.count_size(saleRules_);
}
}
bool
SaleCreationRequest::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
return saleRules_ == other.saleRules_;
}
return false;
}
bool
SaleCreationRequest::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
return saleRules_ < other.saleRules_;
}
return false;
}
bool
SaleCreationRequest::from_bytes(xdr::unmarshaler& u) 
{
bool oksaleType = u.from_bytes(saleType);
if (!oksaleType)
{
return false;
}
bool okbaseAsset = u.from_bytes(baseAsset);
if (!okbaseAsset)
{
return false;
}
bool okdefaultQuoteAsset = u.from_bytes(defaultQuoteAsset);
if (!okdefaultQuoteAsset)
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
bool okcreatorDetails = u.from_bytes(creatorDetails);
if (!okcreatorDetails)
{
return false;
}
bool oksaleTypeExt = u.from_bytes(saleTypeExt);
if (!oksaleTypeExt)
{
return false;
}
bool okrequiredBaseAssetForHardCap = u.from_bytes(requiredBaseAssetForHardCap);
if (!okrequiredBaseAssetForHardCap)
{
return false;
}
bool oksequenceNumber = u.from_bytes(sequenceNumber);
if (!oksequenceNumber)
{
return false;
}
bool okquoteAssets = u.from_bytes(quoteAssets);
if (!okquoteAssets)
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
SaleCreationRequest::to_bytes(xdr::marshaler& m) const 
{
bool oksaleType = m.to_bytes(saleType);
if (!oksaleType)
{
return false;
}
bool okbaseAsset = m.to_bytes(baseAsset);
if (!okbaseAsset)
{
return false;
}
bool okdefaultQuoteAsset = m.to_bytes(defaultQuoteAsset);
if (!okdefaultQuoteAsset)
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
bool okcreatorDetails = m.to_bytes(creatorDetails);
if (!okcreatorDetails)
{
return false;
}
bool oksaleTypeExt = m.to_bytes(saleTypeExt);
if (!oksaleTypeExt)
{
return false;
}
bool okrequiredBaseAssetForHardCap = m.to_bytes(requiredBaseAssetForHardCap);
if (!okrequiredBaseAssetForHardCap)
{
return false;
}
bool oksequenceNumber = m.to_bytes(sequenceNumber);
if (!oksequenceNumber)
{
return false;
}
bool okquoteAssets = m.to_bytes(quoteAssets);
if (!okquoteAssets)
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
SaleCreationRequest::count_size(xdr::measurer& m) const 
{
m.count_size(saleType);
m.count_size(baseAsset);
m.count_size(defaultQuoteAsset);
m.count_size(startTime);
m.count_size(endTime);
m.count_size(softCap);
m.count_size(hardCap);
m.count_size(creatorDetails);
m.count_size(saleTypeExt);
m.count_size(requiredBaseAssetForHardCap);
m.count_size(sequenceNumber);
m.count_size(quoteAssets);
m.count_size(ext);
}
bool
SaleCreationRequest::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<SaleCreationRequest const&>(other_abstract);return true
&& (saleType== other.saleType)
&& (baseAsset== other.baseAsset)
&& (defaultQuoteAsset== other.defaultQuoteAsset)
&& (startTime== other.startTime)
&& (endTime== other.endTime)
&& (softCap== other.softCap)
&& (hardCap== other.hardCap)
&& (creatorDetails== other.creatorDetails)
&& (saleTypeExt== other.saleTypeExt)
&& (requiredBaseAssetForHardCap== other.requiredBaseAssetForHardCap)
&& (sequenceNumber== other.sequenceNumber)
&& (quoteAssets== other.quoteAssets)
&& (ext== other.ext)
;}
bool
SaleCreationRequest::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<SaleCreationRequest const&>(other_abstract);
if (saleType < other.saleType) return true;
if (other.saleType < saleType) return false;
if (baseAsset < other.baseAsset) return true;
if (other.baseAsset < baseAsset) return false;
if (defaultQuoteAsset < other.defaultQuoteAsset) return true;
if (other.defaultQuoteAsset < defaultQuoteAsset) return false;
if (startTime < other.startTime) return true;
if (other.startTime < startTime) return false;
if (endTime < other.endTime) return true;
if (other.endTime < endTime) return false;
if (softCap < other.softCap) return true;
if (other.softCap < softCap) return false;
if (hardCap < other.hardCap) return true;
if (other.hardCap < hardCap) return false;
if (creatorDetails < other.creatorDetails) return true;
if (other.creatorDetails < creatorDetails) return false;
if (saleTypeExt < other.saleTypeExt) return true;
if (other.saleTypeExt < saleTypeExt) return false;
if (requiredBaseAssetForHardCap < other.requiredBaseAssetForHardCap) return true;
if (other.requiredBaseAssetForHardCap < requiredBaseAssetForHardCap) return false;
if (sequenceNumber < other.sequenceNumber) return true;
if (other.sequenceNumber < sequenceNumber) return false;
if (quoteAssets < other.quoteAssets) return true;
if (other.quoteAssets < quoteAssets) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}