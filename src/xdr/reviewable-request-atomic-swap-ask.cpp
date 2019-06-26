#include "reviewable-request-atomic-swap-ask.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
CreateAtomicSwapAskRequest::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
CreateAtomicSwapAskRequest::_ext_t::to_bytes(xdr::marshaler& m) const
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
CreateAtomicSwapAskRequest::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
CreateAtomicSwapAskRequest::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
CreateAtomicSwapAskRequest::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
CreateAtomicSwapAskRequest::from_bytes(xdr::unmarshaler& u) 
{
bool okbaseBalance = u.from_bytes(baseBalance);
if (!okbaseBalance)
{
return false;
}
bool okamount = u.from_bytes(amount);
if (!okamount)
{
return false;
}
bool okcreatorDetails = u.from_bytes(creatorDetails);
if (!okcreatorDetails)
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
CreateAtomicSwapAskRequest::to_bytes(xdr::marshaler& m) const 
{
bool okbaseBalance = m.to_bytes(baseBalance);
if (!okbaseBalance)
{
return false;
}
bool okamount = m.to_bytes(amount);
if (!okamount)
{
return false;
}
bool okcreatorDetails = m.to_bytes(creatorDetails);
if (!okcreatorDetails)
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
CreateAtomicSwapAskRequest::count_size(xdr::measurer& m) const 
{
m.count_size(baseBalance);
m.count_size(amount);
m.count_size(creatorDetails);
m.count_size(quoteAssets);
m.count_size(ext);
}
bool
CreateAtomicSwapAskRequest::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CreateAtomicSwapAskRequest const&>(other_abstract);return true
&& (baseBalance== other.baseBalance)
&& (amount== other.amount)
&& (creatorDetails== other.creatorDetails)
&& (quoteAssets== other.quoteAssets)
&& (ext== other.ext)
;}
bool
CreateAtomicSwapAskRequest::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreateAtomicSwapAskRequest const&>(other_abstract);
if (baseBalance < other.baseBalance) return true;
if (other.baseBalance < baseBalance) return false;
if (amount < other.amount) return true;
if (other.amount < amount) return false;
if (creatorDetails < other.creatorDetails) return true;
if (other.creatorDetails < creatorDetails) return false;
if (quoteAssets < other.quoteAssets) return true;
if (other.quoteAssets < quoteAssets) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}