#include "operation-create-redemption-request.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
CreateRedemptionRequestOp::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
CreateRedemptionRequestOp::_ext_t::to_bytes(xdr::marshaler& m) const
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
CreateRedemptionRequestOp::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
CreateRedemptionRequestOp::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
CreateRedemptionRequestOp::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
CreateRedemptionRequestOp::from_bytes(xdr::unmarshaler& u) 
{
bool okreference = u.from_bytes(reference);
if (!okreference)
{
return false;
}
bool okredemptionRequest = u.from_bytes(redemptionRequest);
if (!okredemptionRequest)
{
return false;
}
bool okallTasks = u.from_bytes(allTasks);
if (!okallTasks)
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
CreateRedemptionRequestOp::to_bytes(xdr::marshaler& m) const 
{
bool okreference = m.to_bytes(reference);
if (!okreference)
{
return false;
}
bool okredemptionRequest = m.to_bytes(redemptionRequest);
if (!okredemptionRequest)
{
return false;
}
bool okallTasks = m.to_bytes(allTasks);
if (!okallTasks)
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
CreateRedemptionRequestOp::count_size(xdr::measurer& m) const 
{
m.count_size(reference);
m.count_size(redemptionRequest);
m.count_size(allTasks);
m.count_size(ext);
}
bool
CreateRedemptionRequestOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CreateRedemptionRequestOp const&>(other_abstract);return true
&& (reference== other.reference)
&& (redemptionRequest== other.redemptionRequest)
&& (allTasks== other.allTasks)
&& (ext== other.ext)
;}
bool
CreateRedemptionRequestOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreateRedemptionRequestOp const&>(other_abstract);
if (reference < other.reference) return true;
if (other.reference < reference) return false;
if (redemptionRequest < other.redemptionRequest) return true;
if (other.redemptionRequest < redemptionRequest) return false;
if (allTasks < other.allTasks) return true;
if (other.allTasks < allTasks) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
RedemptionRequestResponse::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
RedemptionRequestResponse::_ext_t::to_bytes(xdr::marshaler& m) const
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
RedemptionRequestResponse::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
RedemptionRequestResponse::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
RedemptionRequestResponse::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
RedemptionRequestResponse::from_bytes(xdr::unmarshaler& u) 
{
bool okrequestID = u.from_bytes(requestID);
if (!okrequestID)
{
return false;
}
bool okfulfilled = u.from_bytes(fulfilled);
if (!okfulfilled)
{
return false;
}
bool okdestinationBalanceID = u.from_bytes(destinationBalanceID);
if (!okdestinationBalanceID)
{
return false;
}
bool okasset = u.from_bytes(asset);
if (!okasset)
{
return false;
}
bool oksourceSentUniversal = u.from_bytes(sourceSentUniversal);
if (!oksourceSentUniversal)
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
RedemptionRequestResponse::to_bytes(xdr::marshaler& m) const 
{
bool okrequestID = m.to_bytes(requestID);
if (!okrequestID)
{
return false;
}
bool okfulfilled = m.to_bytes(fulfilled);
if (!okfulfilled)
{
return false;
}
bool okdestinationBalanceID = m.to_bytes(destinationBalanceID);
if (!okdestinationBalanceID)
{
return false;
}
bool okasset = m.to_bytes(asset);
if (!okasset)
{
return false;
}
bool oksourceSentUniversal = m.to_bytes(sourceSentUniversal);
if (!oksourceSentUniversal)
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
RedemptionRequestResponse::count_size(xdr::measurer& m) const 
{
m.count_size(requestID);
m.count_size(fulfilled);
m.count_size(destinationBalanceID);
m.count_size(asset);
m.count_size(sourceSentUniversal);
m.count_size(ext);
}
bool
RedemptionRequestResponse::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<RedemptionRequestResponse const&>(other_abstract);return true
&& (requestID== other.requestID)
&& (fulfilled== other.fulfilled)
&& (destinationBalanceID== other.destinationBalanceID)
&& (asset== other.asset)
&& (sourceSentUniversal== other.sourceSentUniversal)
&& (ext== other.ext)
;}
bool
RedemptionRequestResponse::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<RedemptionRequestResponse const&>(other_abstract);
if (requestID < other.requestID) return true;
if (other.requestID < requestID) return false;
if (fulfilled < other.fulfilled) return true;
if (other.fulfilled < fulfilled) return false;
if (destinationBalanceID < other.destinationBalanceID) return true;
if (other.destinationBalanceID < destinationBalanceID) return false;
if (asset < other.asset) return true;
if (other.asset < asset) return false;
if (sourceSentUniversal < other.sourceSentUniversal) return true;
if (other.sourceSentUniversal < sourceSentUniversal) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
CreateRedemptionRequestResult::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (code_)
{
  case (int32_t)CreateRedemptionRequestResultCode::SUCCESS:
return u.from_bytes(redemptionResponse_);
  default:
  
  return true;
}
return false;
}
bool
CreateRedemptionRequestResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)CreateRedemptionRequestResultCode::SUCCESS:
return m.to_bytes(redemptionResponse_);
  default:
    return true;
}
return false;
}
void
CreateRedemptionRequestResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)CreateRedemptionRequestResultCode::SUCCESS:
return m.count_size(redemptionResponse_);
  default:
  
  return;
}
}
bool
CreateRedemptionRequestResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<CreateRedemptionRequestResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)CreateRedemptionRequestResultCode::SUCCESS:
return redemptionResponse_ == other.redemptionResponse_;
  default:
  
  return true;
}
return false;
}
bool
CreateRedemptionRequestResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreateRedemptionRequestResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)CreateRedemptionRequestResultCode::SUCCESS:
return redemptionResponse_ < other.redemptionResponse_;
  default:
    return false;
}
return false;
}
}