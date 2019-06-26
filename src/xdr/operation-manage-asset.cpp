#include "operation-manage-asset.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
CancelAssetRequest::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
CancelAssetRequest::_ext_t::to_bytes(xdr::marshaler& m) const
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
CancelAssetRequest::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
CancelAssetRequest::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
CancelAssetRequest::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
CancelAssetRequest::from_bytes(xdr::unmarshaler& u) 
{
bool okext = u.from_bytes(ext);
if (!okext)
{
return false;
}
return true;
}
bool
CancelAssetRequest::to_bytes(xdr::marshaler& m) const 
{
bool okext = m.to_bytes(ext);
if (!okext)
{
return false;
}
return true;
}
void
CancelAssetRequest::count_size(xdr::measurer& m) const 
{
m.count_size(ext);
}
bool
CancelAssetRequest::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CancelAssetRequest const&>(other_abstract);return true
&& (ext== other.ext)
;}
bool
CancelAssetRequest::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CancelAssetRequest const&>(other_abstract);
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
UpdateMaxIssuance::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
UpdateMaxIssuance::_ext_t::to_bytes(xdr::marshaler& m) const
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
UpdateMaxIssuance::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
UpdateMaxIssuance::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
UpdateMaxIssuance::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
UpdateMaxIssuance::from_bytes(xdr::unmarshaler& u) 
{
bool okassetCode = u.from_bytes(assetCode);
if (!okassetCode)
{
return false;
}
bool okmaxIssuanceAmount = u.from_bytes(maxIssuanceAmount);
if (!okmaxIssuanceAmount)
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
UpdateMaxIssuance::to_bytes(xdr::marshaler& m) const 
{
bool okassetCode = m.to_bytes(assetCode);
if (!okassetCode)
{
return false;
}
bool okmaxIssuanceAmount = m.to_bytes(maxIssuanceAmount);
if (!okmaxIssuanceAmount)
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
UpdateMaxIssuance::count_size(xdr::measurer& m) const 
{
m.count_size(assetCode);
m.count_size(maxIssuanceAmount);
m.count_size(ext);
}
bool
UpdateMaxIssuance::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<UpdateMaxIssuance const&>(other_abstract);return true
&& (assetCode== other.assetCode)
&& (maxIssuanceAmount== other.maxIssuanceAmount)
&& (ext== other.ext)
;}
bool
UpdateMaxIssuance::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<UpdateMaxIssuance const&>(other_abstract);
if (assetCode < other.assetCode) return true;
if (other.assetCode < assetCode) return false;
if (maxIssuanceAmount < other.maxIssuanceAmount) return true;
if (other.maxIssuanceAmount < maxIssuanceAmount) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageAssetOp::_request_t::_createAssetCreationRequest_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ManageAssetOp::_request_t::_createAssetCreationRequest_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
ManageAssetOp::_request_t::_createAssetCreationRequest_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

        case (int32_t)LedgerVersion::EMPTY_VERSION:
        
  return;
}
}
bool
ManageAssetOp::_request_t::_createAssetCreationRequest_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ManageAssetOp::_request_t::_createAssetCreationRequest_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ManageAssetOp::_request_t::_createAssetCreationRequest_t::from_bytes(xdr::unmarshaler& u) 
{
bool okcreateAsset = u.from_bytes(createAsset);
if (!okcreateAsset)
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
ManageAssetOp::_request_t::_createAssetCreationRequest_t::to_bytes(xdr::marshaler& m) const 
{
bool okcreateAsset = m.to_bytes(createAsset);
if (!okcreateAsset)
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
ManageAssetOp::_request_t::_createAssetCreationRequest_t::count_size(xdr::measurer& m) const 
{
m.count_size(createAsset);
m.count_size(allTasks);
m.count_size(ext);
}
bool
ManageAssetOp::_request_t::_createAssetCreationRequest_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_createAssetCreationRequest_t const&>(other_abstract);return true
&& (createAsset== other.createAsset)
&& (allTasks== other.allTasks)
&& (ext== other.ext)
;}
bool
ManageAssetOp::_request_t::_createAssetCreationRequest_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_createAssetCreationRequest_t const&>(other_abstract);
if (createAsset < other.createAsset) return true;
if (other.createAsset < createAsset) return false;
if (allTasks < other.allTasks) return true;
if (other.allTasks < allTasks) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageAssetOp::_request_t::_createAssetUpdateRequest_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ManageAssetOp::_request_t::_createAssetUpdateRequest_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
ManageAssetOp::_request_t::_createAssetUpdateRequest_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

        case (int32_t)LedgerVersion::EMPTY_VERSION:
        
  return;
}
}
bool
ManageAssetOp::_request_t::_createAssetUpdateRequest_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ManageAssetOp::_request_t::_createAssetUpdateRequest_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ManageAssetOp::_request_t::_createAssetUpdateRequest_t::from_bytes(xdr::unmarshaler& u) 
{
bool okupdateAsset = u.from_bytes(updateAsset);
if (!okupdateAsset)
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
ManageAssetOp::_request_t::_createAssetUpdateRequest_t::to_bytes(xdr::marshaler& m) const 
{
bool okupdateAsset = m.to_bytes(updateAsset);
if (!okupdateAsset)
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
ManageAssetOp::_request_t::_createAssetUpdateRequest_t::count_size(xdr::measurer& m) const 
{
m.count_size(updateAsset);
m.count_size(allTasks);
m.count_size(ext);
}
bool
ManageAssetOp::_request_t::_createAssetUpdateRequest_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_createAssetUpdateRequest_t const&>(other_abstract);return true
&& (updateAsset== other.updateAsset)
&& (allTasks== other.allTasks)
&& (ext== other.ext)
;}
bool
ManageAssetOp::_request_t::_createAssetUpdateRequest_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_createAssetUpdateRequest_t const&>(other_abstract);
if (updateAsset < other.updateAsset) return true;
if (other.updateAsset < updateAsset) return false;
if (allTasks < other.allTasks) return true;
if (other.allTasks < allTasks) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageAssetOp::_request_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(action_);
if (!ok)
{
return false;
}
switch (action_)
{

    case (int32_t)ManageAssetAction::CREATE_ASSET_CREATION_REQUEST:
return u.from_bytes(createAssetCreationRequest_);
    case (int32_t)ManageAssetAction::CREATE_ASSET_UPDATE_REQUEST:
return u.from_bytes(createAssetUpdateRequest_);
    case (int32_t)ManageAssetAction::CANCEL_ASSET_REQUEST:
return u.from_bytes(cancelRequest_);
    case (int32_t)ManageAssetAction::CHANGE_PREISSUED_ASSET_SIGNER:
return u.from_bytes(changePreissuedSigner_);
    case (int32_t)ManageAssetAction::UPDATE_MAX_ISSUANCE:
return u.from_bytes(updateMaxIssuance_);
}
return false;
}
bool
ManageAssetOp::_request_t::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(action_);
if (!ok)
{
return false;
}
switch (action_)
{

    case (int32_t)ManageAssetAction::CREATE_ASSET_CREATION_REQUEST:
return m.to_bytes(createAssetCreationRequest_);
    case (int32_t)ManageAssetAction::CREATE_ASSET_UPDATE_REQUEST:
return m.to_bytes(createAssetUpdateRequest_);
    case (int32_t)ManageAssetAction::CANCEL_ASSET_REQUEST:
return m.to_bytes(cancelRequest_);
    case (int32_t)ManageAssetAction::CHANGE_PREISSUED_ASSET_SIGNER:
return m.to_bytes(changePreissuedSigner_);
    case (int32_t)ManageAssetAction::UPDATE_MAX_ISSUANCE:
return m.to_bytes(updateMaxIssuance_);
}
return false;
}
void
ManageAssetOp::_request_t::count_size(xdr::measurer& m) const
{
m.count_size(action_);
switch (action_)
{

    case (int32_t)ManageAssetAction::CREATE_ASSET_CREATION_REQUEST:
return m.count_size(createAssetCreationRequest_);
    case (int32_t)ManageAssetAction::CREATE_ASSET_UPDATE_REQUEST:
return m.count_size(createAssetUpdateRequest_);
    case (int32_t)ManageAssetAction::CANCEL_ASSET_REQUEST:
return m.count_size(cancelRequest_);
    case (int32_t)ManageAssetAction::CHANGE_PREISSUED_ASSET_SIGNER:
return m.count_size(changePreissuedSigner_);
    case (int32_t)ManageAssetAction::UPDATE_MAX_ISSUANCE:
return m.count_size(updateMaxIssuance_);
}
}
bool
ManageAssetOp::_request_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_request_t const&>(other_abstract);
if (other.action_ != action_) return false;
switch (action_)
{
    case (int32_t)ManageAssetAction::CREATE_ASSET_CREATION_REQUEST:
return createAssetCreationRequest_ == other.createAssetCreationRequest_;
    case (int32_t)ManageAssetAction::CREATE_ASSET_UPDATE_REQUEST:
return createAssetUpdateRequest_ == other.createAssetUpdateRequest_;
    case (int32_t)ManageAssetAction::CANCEL_ASSET_REQUEST:
return cancelRequest_ == other.cancelRequest_;
    case (int32_t)ManageAssetAction::CHANGE_PREISSUED_ASSET_SIGNER:
return changePreissuedSigner_ == other.changePreissuedSigner_;
    case (int32_t)ManageAssetAction::UPDATE_MAX_ISSUANCE:
return updateMaxIssuance_ == other.updateMaxIssuance_;
}
return false;
}
bool
ManageAssetOp::_request_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_request_t const&>(other_abstract);
if (action_ < other.action_) return true;
if (other.action_ < action_) return false;
switch (action_)
{
    case (int32_t)ManageAssetAction::CREATE_ASSET_CREATION_REQUEST:
return createAssetCreationRequest_ < other.createAssetCreationRequest_;
    case (int32_t)ManageAssetAction::CREATE_ASSET_UPDATE_REQUEST:
return createAssetUpdateRequest_ < other.createAssetUpdateRequest_;
    case (int32_t)ManageAssetAction::CANCEL_ASSET_REQUEST:
return cancelRequest_ < other.cancelRequest_;
    case (int32_t)ManageAssetAction::CHANGE_PREISSUED_ASSET_SIGNER:
return changePreissuedSigner_ < other.changePreissuedSigner_;
    case (int32_t)ManageAssetAction::UPDATE_MAX_ISSUANCE:
return updateMaxIssuance_ < other.updateMaxIssuance_;
}
return false;
}
bool
ManageAssetOp::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ManageAssetOp::_ext_t::to_bytes(xdr::marshaler& m) const
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
ManageAssetOp::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
ManageAssetOp::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ManageAssetOp::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ManageAssetOp::from_bytes(xdr::unmarshaler& u) 
{
bool okrequestID = u.from_bytes(requestID);
if (!okrequestID)
{
return false;
}
bool okrequest = u.from_bytes(request);
if (!okrequest)
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
ManageAssetOp::to_bytes(xdr::marshaler& m) const 
{
bool okrequestID = m.to_bytes(requestID);
if (!okrequestID)
{
return false;
}
bool okrequest = m.to_bytes(request);
if (!okrequest)
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
ManageAssetOp::count_size(xdr::measurer& m) const 
{
m.count_size(requestID);
m.count_size(request);
m.count_size(ext);
}
bool
ManageAssetOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<ManageAssetOp const&>(other_abstract);return true
&& (requestID== other.requestID)
&& (request== other.request)
&& (ext== other.ext)
;}
bool
ManageAssetOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManageAssetOp const&>(other_abstract);
if (requestID < other.requestID) return true;
if (other.requestID < requestID) return false;
if (request < other.request) return true;
if (other.request < request) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageAssetSuccess::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ManageAssetSuccess::_ext_t::to_bytes(xdr::marshaler& m) const
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
ManageAssetSuccess::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
ManageAssetSuccess::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ManageAssetSuccess::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ManageAssetSuccess::from_bytes(xdr::unmarshaler& u) 
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
bool okext = u.from_bytes(ext);
if (!okext)
{
return false;
}
return true;
}
bool
ManageAssetSuccess::to_bytes(xdr::marshaler& m) const 
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
bool okext = m.to_bytes(ext);
if (!okext)
{
return false;
}
return true;
}
void
ManageAssetSuccess::count_size(xdr::measurer& m) const 
{
m.count_size(requestID);
m.count_size(fulfilled);
m.count_size(ext);
}
bool
ManageAssetSuccess::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<ManageAssetSuccess const&>(other_abstract);return true
&& (requestID== other.requestID)
&& (fulfilled== other.fulfilled)
&& (ext== other.ext)
;}
bool
ManageAssetSuccess::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManageAssetSuccess const&>(other_abstract);
if (requestID < other.requestID) return true;
if (other.requestID < requestID) return false;
if (fulfilled < other.fulfilled) return true;
if (other.fulfilled < fulfilled) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageAssetResult::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)ManageAssetResultCode::SUCCESS:
return u.from_bytes(success_);
  default:
    return true;
}
return false;
}
bool
ManageAssetResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)ManageAssetResultCode::SUCCESS:
return m.to_bytes(success_);
  default:
    return true;
}
return false;
}
void
ManageAssetResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)ManageAssetResultCode::SUCCESS:
return m.count_size(success_);
  default:
  
  return;
}
}
bool
ManageAssetResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<ManageAssetResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)ManageAssetResultCode::SUCCESS:
return success_ == other.success_;
  default:
  
  return true;
}
return false;
}
bool
ManageAssetResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManageAssetResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)ManageAssetResultCode::SUCCESS:
return success_ < other.success_;
  default:
    return false;
}
return false;
}
}