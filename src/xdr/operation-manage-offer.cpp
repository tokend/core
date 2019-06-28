#include "operation-manage-offer.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
ManageOfferOp::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ManageOfferOp::_ext_t::to_bytes(xdr::marshaler& m) const
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
ManageOfferOp::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
ManageOfferOp::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ManageOfferOp::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ManageOfferOp::from_bytes(xdr::unmarshaler& u) 
{
bool okbaseBalance = u.from_bytes(baseBalance);
if (!okbaseBalance)
{
return false;
}
bool okquoteBalance = u.from_bytes(quoteBalance);
if (!okquoteBalance)
{
return false;
}
bool okisBuy = u.from_bytes(isBuy);
if (!okisBuy)
{
return false;
}
bool okamount = u.from_bytes(amount);
if (!okamount)
{
return false;
}
bool okprice = u.from_bytes(price);
if (!okprice)
{
return false;
}
bool okfee = u.from_bytes(fee);
if (!okfee)
{
return false;
}
bool okofferID = u.from_bytes(offerID);
if (!okofferID)
{
return false;
}
bool okorderBookID = u.from_bytes(orderBookID);
if (!okorderBookID)
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
ManageOfferOp::to_bytes(xdr::marshaler& m) const 
{
bool okbaseBalance = m.to_bytes(baseBalance);
if (!okbaseBalance)
{
return false;
}
bool okquoteBalance = m.to_bytes(quoteBalance);
if (!okquoteBalance)
{
return false;
}
bool okisBuy = m.to_bytes(isBuy);
if (!okisBuy)
{
return false;
}
bool okamount = m.to_bytes(amount);
if (!okamount)
{
return false;
}
bool okprice = m.to_bytes(price);
if (!okprice)
{
return false;
}
bool okfee = m.to_bytes(fee);
if (!okfee)
{
return false;
}
bool okofferID = m.to_bytes(offerID);
if (!okofferID)
{
return false;
}
bool okorderBookID = m.to_bytes(orderBookID);
if (!okorderBookID)
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
ManageOfferOp::count_size(xdr::measurer& m) const 
{
m.count_size(baseBalance);
m.count_size(quoteBalance);
m.count_size(isBuy);
m.count_size(amount);
m.count_size(price);
m.count_size(fee);
m.count_size(offerID);
m.count_size(orderBookID);
m.count_size(ext);
}
bool
ManageOfferOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<ManageOfferOp const&>(other_abstract);return true
&& (baseBalance== other.baseBalance)
&& (quoteBalance== other.quoteBalance)
&& (isBuy== other.isBuy)
&& (amount== other.amount)
&& (price== other.price)
&& (fee== other.fee)
&& (offerID== other.offerID)
&& (orderBookID== other.orderBookID)
&& (ext== other.ext)
;}
bool
ManageOfferOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManageOfferOp const&>(other_abstract);
if (baseBalance < other.baseBalance) return true;
if (other.baseBalance < baseBalance) return false;
if (quoteBalance < other.quoteBalance) return true;
if (other.quoteBalance < quoteBalance) return false;
if (isBuy < other.isBuy) return true;
if (other.isBuy < isBuy) return false;
if (amount < other.amount) return true;
if (other.amount < amount) return false;
if (price < other.price) return true;
if (other.price < price) return false;
if (fee < other.fee) return true;
if (other.fee < fee) return false;
if (offerID < other.offerID) return true;
if (other.offerID < offerID) return false;
if (orderBookID < other.orderBookID) return true;
if (other.orderBookID < orderBookID) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ClaimOfferAtom::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ClaimOfferAtom::_ext_t::to_bytes(xdr::marshaler& m) const
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
ClaimOfferAtom::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
ClaimOfferAtom::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ClaimOfferAtom::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ClaimOfferAtom::from_bytes(xdr::unmarshaler& u) 
{
bool okbAccountID = u.from_bytes(bAccountID);
if (!okbAccountID)
{
return false;
}
bool okofferID = u.from_bytes(offerID);
if (!okofferID)
{
return false;
}
bool okbaseAmount = u.from_bytes(baseAmount);
if (!okbaseAmount)
{
return false;
}
bool okquoteAmount = u.from_bytes(quoteAmount);
if (!okquoteAmount)
{
return false;
}
bool okbFeePaid = u.from_bytes(bFeePaid);
if (!okbFeePaid)
{
return false;
}
bool okaFeePaid = u.from_bytes(aFeePaid);
if (!okaFeePaid)
{
return false;
}
bool okbaseBalance = u.from_bytes(baseBalance);
if (!okbaseBalance)
{
return false;
}
bool okquoteBalance = u.from_bytes(quoteBalance);
if (!okquoteBalance)
{
return false;
}
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
ClaimOfferAtom::to_bytes(xdr::marshaler& m) const 
{
bool okbAccountID = m.to_bytes(bAccountID);
if (!okbAccountID)
{
return false;
}
bool okofferID = m.to_bytes(offerID);
if (!okofferID)
{
return false;
}
bool okbaseAmount = m.to_bytes(baseAmount);
if (!okbaseAmount)
{
return false;
}
bool okquoteAmount = m.to_bytes(quoteAmount);
if (!okquoteAmount)
{
return false;
}
bool okbFeePaid = m.to_bytes(bFeePaid);
if (!okbFeePaid)
{
return false;
}
bool okaFeePaid = m.to_bytes(aFeePaid);
if (!okaFeePaid)
{
return false;
}
bool okbaseBalance = m.to_bytes(baseBalance);
if (!okbaseBalance)
{
return false;
}
bool okquoteBalance = m.to_bytes(quoteBalance);
if (!okquoteBalance)
{
return false;
}
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
ClaimOfferAtom::count_size(xdr::measurer& m) const 
{
m.count_size(bAccountID);
m.count_size(offerID);
m.count_size(baseAmount);
m.count_size(quoteAmount);
m.count_size(bFeePaid);
m.count_size(aFeePaid);
m.count_size(baseBalance);
m.count_size(quoteBalance);
m.count_size(currentPrice);
m.count_size(ext);
}
bool
ClaimOfferAtom::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<ClaimOfferAtom const&>(other_abstract);return true
&& (bAccountID== other.bAccountID)
&& (offerID== other.offerID)
&& (baseAmount== other.baseAmount)
&& (quoteAmount== other.quoteAmount)
&& (bFeePaid== other.bFeePaid)
&& (aFeePaid== other.aFeePaid)
&& (baseBalance== other.baseBalance)
&& (quoteBalance== other.quoteBalance)
&& (currentPrice== other.currentPrice)
&& (ext== other.ext)
;}
bool
ClaimOfferAtom::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ClaimOfferAtom const&>(other_abstract);
if (bAccountID < other.bAccountID) return true;
if (other.bAccountID < bAccountID) return false;
if (offerID < other.offerID) return true;
if (other.offerID < offerID) return false;
if (baseAmount < other.baseAmount) return true;
if (other.baseAmount < baseAmount) return false;
if (quoteAmount < other.quoteAmount) return true;
if (other.quoteAmount < quoteAmount) return false;
if (bFeePaid < other.bFeePaid) return true;
if (other.bFeePaid < bFeePaid) return false;
if (aFeePaid < other.aFeePaid) return true;
if (other.aFeePaid < aFeePaid) return false;
if (baseBalance < other.baseBalance) return true;
if (other.baseBalance < baseBalance) return false;
if (quoteBalance < other.quoteBalance) return true;
if (other.quoteBalance < quoteBalance) return false;
if (currentPrice < other.currentPrice) return true;
if (other.currentPrice < currentPrice) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageOfferSuccessResult::_offer_t::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (effect_)
{
    case (int32_t)ManageOfferEffect::CREATED:
    case (int32_t)ManageOfferEffect::UPDATED:
return u.from_bytes(offer_);
    default:
    
  return true;
}
return false;
}
bool
ManageOfferSuccessResult::_offer_t::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(effect_);
if (!ok)
{
return false;
}
switch (effect_)
{

    case (int32_t)ManageOfferEffect::CREATED:
    case (int32_t)ManageOfferEffect::UPDATED:
return m.to_bytes(offer_);
    default:
      return true;
}
return false;
}
void
ManageOfferSuccessResult::_offer_t::count_size(xdr::measurer& m) const
{
m.count_size(effect_);
switch (effect_)
{

    case (int32_t)ManageOfferEffect::CREATED:
    case (int32_t)ManageOfferEffect::UPDATED:
return m.count_size(offer_);
    default:
    
  return;
}
}
bool
ManageOfferSuccessResult::_offer_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_offer_t const&>(other_abstract);
if (other.effect_ != effect_) return false;
switch (effect_)
{
    case (int32_t)ManageOfferEffect::CREATED:
    case (int32_t)ManageOfferEffect::UPDATED:
return offer_ == other.offer_;
    default:
    
  return true;
}
return false;
}
bool
ManageOfferSuccessResult::_offer_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_offer_t const&>(other_abstract);
if (effect_ < other.effect_) return true;
if (other.effect_ < effect_) return false;
switch (effect_)
{
    case (int32_t)ManageOfferEffect::CREATED:
    case (int32_t)ManageOfferEffect::UPDATED:
return offer_ < other.offer_;
    default:
      return false;
}
return false;
}
bool
ManageOfferSuccessResult::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ManageOfferSuccessResult::_ext_t::to_bytes(xdr::marshaler& m) const
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
ManageOfferSuccessResult::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
ManageOfferSuccessResult::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ManageOfferSuccessResult::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ManageOfferSuccessResult::from_bytes(xdr::unmarshaler& u) 
{
bool okoffersClaimed = u.from_bytes(offersClaimed);
if (!okoffersClaimed)
{
return false;
}
bool okbaseAsset = u.from_bytes(baseAsset);
if (!okbaseAsset)
{
return false;
}
bool okquoteAsset = u.from_bytes(quoteAsset);
if (!okquoteAsset)
{
return false;
}
bool okoffer = u.from_bytes(offer);
if (!okoffer)
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
ManageOfferSuccessResult::to_bytes(xdr::marshaler& m) const 
{
bool okoffersClaimed = m.to_bytes(offersClaimed);
if (!okoffersClaimed)
{
return false;
}
bool okbaseAsset = m.to_bytes(baseAsset);
if (!okbaseAsset)
{
return false;
}
bool okquoteAsset = m.to_bytes(quoteAsset);
if (!okquoteAsset)
{
return false;
}
bool okoffer = m.to_bytes(offer);
if (!okoffer)
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
ManageOfferSuccessResult::count_size(xdr::measurer& m) const 
{
m.count_size(offersClaimed);
m.count_size(baseAsset);
m.count_size(quoteAsset);
m.count_size(offer);
m.count_size(ext);
}
bool
ManageOfferSuccessResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<ManageOfferSuccessResult const&>(other_abstract);return true
&& (offersClaimed== other.offersClaimed)
&& (baseAsset== other.baseAsset)
&& (quoteAsset== other.quoteAsset)
&& (offer== other.offer)
&& (ext== other.ext)
;}
bool
ManageOfferSuccessResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManageOfferSuccessResult const&>(other_abstract);
if (offersClaimed < other.offersClaimed) return true;
if (other.offersClaimed < offersClaimed) return false;
if (baseAsset < other.baseAsset) return true;
if (other.baseAsset < baseAsset) return false;
if (quoteAsset < other.quoteAsset) return true;
if (other.quoteAsset < quoteAsset) return false;
if (offer < other.offer) return true;
if (other.offer < offer) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageOfferResult::_physicalPriceRestriction_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ManageOfferResult::_physicalPriceRestriction_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
ManageOfferResult::_physicalPriceRestriction_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
ManageOfferResult::_physicalPriceRestriction_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ManageOfferResult::_physicalPriceRestriction_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ManageOfferResult::_physicalPriceRestriction_t::from_bytes(xdr::unmarshaler& u) 
{
bool okphysicalPrice = u.from_bytes(physicalPrice);
if (!okphysicalPrice)
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
ManageOfferResult::_physicalPriceRestriction_t::to_bytes(xdr::marshaler& m) const 
{
bool okphysicalPrice = m.to_bytes(physicalPrice);
if (!okphysicalPrice)
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
ManageOfferResult::_physicalPriceRestriction_t::count_size(xdr::measurer& m) const 
{
m.count_size(physicalPrice);
m.count_size(ext);
}
bool
ManageOfferResult::_physicalPriceRestriction_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_physicalPriceRestriction_t const&>(other_abstract);return true
&& (physicalPrice== other.physicalPrice)
&& (ext== other.ext)
;}
bool
ManageOfferResult::_physicalPriceRestriction_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_physicalPriceRestriction_t const&>(other_abstract);
if (physicalPrice < other.physicalPrice) return true;
if (other.physicalPrice < physicalPrice) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageOfferResult::_currentPriceRestriction_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ManageOfferResult::_currentPriceRestriction_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
ManageOfferResult::_currentPriceRestriction_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
ManageOfferResult::_currentPriceRestriction_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ManageOfferResult::_currentPriceRestriction_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ManageOfferResult::_currentPriceRestriction_t::from_bytes(xdr::unmarshaler& u) 
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
ManageOfferResult::_currentPriceRestriction_t::to_bytes(xdr::marshaler& m) const 
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
ManageOfferResult::_currentPriceRestriction_t::count_size(xdr::measurer& m) const 
{
m.count_size(currentPrice);
m.count_size(ext);
}
bool
ManageOfferResult::_currentPriceRestriction_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_currentPriceRestriction_t const&>(other_abstract);return true
&& (currentPrice== other.currentPrice)
&& (ext== other.ext)
;}
bool
ManageOfferResult::_currentPriceRestriction_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_currentPriceRestriction_t const&>(other_abstract);
if (currentPrice < other.currentPrice) return true;
if (other.currentPrice < currentPrice) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageOfferResult::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (code_)
{
  case (int32_t)ManageOfferResultCode::SUCCESS:
return u.from_bytes(success_);
  case (int32_t)ManageOfferResultCode::PHYSICAL_PRICE_RESTRICTION:
return u.from_bytes(physicalPriceRestriction_);
  case (int32_t)ManageOfferResultCode::CURRENT_PRICE_RESTRICTION:
return u.from_bytes(currentPriceRestriction_);
  default:
  
  return true;
}
return false;
}
bool
ManageOfferResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)ManageOfferResultCode::SUCCESS:
return m.to_bytes(success_);
  case (int32_t)ManageOfferResultCode::PHYSICAL_PRICE_RESTRICTION:
return m.to_bytes(physicalPriceRestriction_);
  case (int32_t)ManageOfferResultCode::CURRENT_PRICE_RESTRICTION:
return m.to_bytes(currentPriceRestriction_);
  default:
    return true;
}
return false;
}
void
ManageOfferResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)ManageOfferResultCode::SUCCESS:
return m.count_size(success_);
  case (int32_t)ManageOfferResultCode::PHYSICAL_PRICE_RESTRICTION:
return m.count_size(physicalPriceRestriction_);
  case (int32_t)ManageOfferResultCode::CURRENT_PRICE_RESTRICTION:
return m.count_size(currentPriceRestriction_);
  default:
  
  return;
}
}
bool
ManageOfferResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<ManageOfferResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)ManageOfferResultCode::SUCCESS:
return success_ == other.success_;
  case (int32_t)ManageOfferResultCode::PHYSICAL_PRICE_RESTRICTION:
return physicalPriceRestriction_ == other.physicalPriceRestriction_;
  case (int32_t)ManageOfferResultCode::CURRENT_PRICE_RESTRICTION:
return currentPriceRestriction_ == other.currentPriceRestriction_;
  default:
  
  return true;
}
return false;
}
bool
ManageOfferResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManageOfferResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)ManageOfferResultCode::SUCCESS:
return success_ < other.success_;
  case (int32_t)ManageOfferResultCode::PHYSICAL_PRICE_RESTRICTION:
return physicalPriceRestriction_ < other.physicalPriceRestriction_;
  case (int32_t)ManageOfferResultCode::CURRENT_PRICE_RESTRICTION:
return currentPriceRestriction_ < other.currentPriceRestriction_;
  default:
    return false;
}
return false;
}
}