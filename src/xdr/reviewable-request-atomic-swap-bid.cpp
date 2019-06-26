#include "reviewable-request-atomic-swap-bid.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
CreateAtomicSwapBidRequest::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
CreateAtomicSwapBidRequest::_ext_t::to_bytes(xdr::marshaler& m) const
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
CreateAtomicSwapBidRequest::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
CreateAtomicSwapBidRequest::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
CreateAtomicSwapBidRequest::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
CreateAtomicSwapBidRequest::from_bytes(xdr::unmarshaler& u) 
{
bool okaskID = u.from_bytes(askID);
if (!okaskID)
{
return false;
}
bool okbaseAmount = u.from_bytes(baseAmount);
if (!okbaseAmount)
{
return false;
}
bool okquoteAsset = u.from_bytes(quoteAsset);
if (!okquoteAsset)
{
return false;
}
bool okcreatorDetails = u.from_bytes(creatorDetails);
if (!okcreatorDetails)
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
CreateAtomicSwapBidRequest::to_bytes(xdr::marshaler& m) const 
{
bool okaskID = m.to_bytes(askID);
if (!okaskID)
{
return false;
}
bool okbaseAmount = m.to_bytes(baseAmount);
if (!okbaseAmount)
{
return false;
}
bool okquoteAsset = m.to_bytes(quoteAsset);
if (!okquoteAsset)
{
return false;
}
bool okcreatorDetails = m.to_bytes(creatorDetails);
if (!okcreatorDetails)
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
CreateAtomicSwapBidRequest::count_size(xdr::measurer& m) const 
{
m.count_size(askID);
m.count_size(baseAmount);
m.count_size(quoteAsset);
m.count_size(creatorDetails);
m.count_size(ext);
}
bool
CreateAtomicSwapBidRequest::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CreateAtomicSwapBidRequest const&>(other_abstract);return true
&& (askID== other.askID)
&& (baseAmount== other.baseAmount)
&& (quoteAsset== other.quoteAsset)
&& (creatorDetails== other.creatorDetails)
&& (ext== other.ext)
;}
bool
CreateAtomicSwapBidRequest::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreateAtomicSwapBidRequest const&>(other_abstract);
if (askID < other.askID) return true;
if (other.askID < askID) return false;
if (baseAmount < other.baseAmount) return true;
if (other.baseAmount < baseAmount) return false;
if (quoteAsset < other.quoteAsset) return true;
if (other.quoteAsset < quoteAsset) return false;
if (creatorDetails < other.creatorDetails) return true;
if (other.creatorDetails < creatorDetails) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}