#include "operation-manage-sale.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
UpdateSaleDetailsData::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
UpdateSaleDetailsData::_ext_t::to_bytes(xdr::marshaler& m) const
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
UpdateSaleDetailsData::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
UpdateSaleDetailsData::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
UpdateSaleDetailsData::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
UpdateSaleDetailsData::from_bytes(xdr::unmarshaler& u) 
{
bool okrequestID = u.from_bytes(requestID);
if (!okrequestID)
{
return false;
}
bool okcreatorDetails = u.from_bytes(creatorDetails);
if (!okcreatorDetails)
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
UpdateSaleDetailsData::to_bytes(xdr::marshaler& m) const 
{
bool okrequestID = m.to_bytes(requestID);
if (!okrequestID)
{
return false;
}
bool okcreatorDetails = m.to_bytes(creatorDetails);
if (!okcreatorDetails)
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
UpdateSaleDetailsData::count_size(xdr::measurer& m) const 
{
m.count_size(requestID);
m.count_size(creatorDetails);
m.count_size(allTasks);
m.count_size(ext);
}
bool
UpdateSaleDetailsData::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<UpdateSaleDetailsData const&>(other_abstract);return true
&& (requestID== other.requestID)
&& (creatorDetails== other.creatorDetails)
&& (allTasks== other.allTasks)
&& (ext== other.ext)
;}
bool
UpdateSaleDetailsData::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<UpdateSaleDetailsData const&>(other_abstract);
if (requestID < other.requestID) return true;
if (other.requestID < requestID) return false;
if (creatorDetails < other.creatorDetails) return true;
if (other.creatorDetails < creatorDetails) return false;
if (allTasks < other.allTasks) return true;
if (other.allTasks < allTasks) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageSaleOp::_data_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(action_);
if (!ok)
{
return false;
}
switch (action_)
{

    case (int32_t)ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
return u.from_bytes(updateSaleDetailsData_);
    case (int32_t)ManageSaleAction::CANCEL:
      return true;
}
return false;
}
bool
ManageSaleOp::_data_t::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(action_);
if (!ok)
{
return false;
}
switch (action_)
{

    case (int32_t)ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
return m.to_bytes(updateSaleDetailsData_);
    case (int32_t)ManageSaleAction::CANCEL:
      return true;
}
return false;
}
void
ManageSaleOp::_data_t::count_size(xdr::measurer& m) const
{
m.count_size(action_);
switch (action_)
{

    case (int32_t)ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
return m.count_size(updateSaleDetailsData_);
    case (int32_t)ManageSaleAction::CANCEL:
    
  return;
}
}
bool
ManageSaleOp::_data_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_data_t const&>(other_abstract);
if (other.action_ != action_) return false;
switch (action_)
{
    case (int32_t)ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
return updateSaleDetailsData_ == other.updateSaleDetailsData_;
    case (int32_t)ManageSaleAction::CANCEL:
    
  return true;
}
return false;
}
bool
ManageSaleOp::_data_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_data_t const&>(other_abstract);
if (action_ < other.action_) return true;
if (other.action_ < action_) return false;
switch (action_)
{
    case (int32_t)ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
return updateSaleDetailsData_ < other.updateSaleDetailsData_;
    case (int32_t)ManageSaleAction::CANCEL:
      return false;
}
return false;
}
bool
ManageSaleOp::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ManageSaleOp::_ext_t::to_bytes(xdr::marshaler& m) const
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
ManageSaleOp::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
ManageSaleOp::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ManageSaleOp::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ManageSaleOp::from_bytes(xdr::unmarshaler& u) 
{
bool oksaleID = u.from_bytes(saleID);
if (!oksaleID)
{
return false;
}
bool okdata = u.from_bytes(data);
if (!okdata)
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
ManageSaleOp::to_bytes(xdr::marshaler& m) const 
{
bool oksaleID = m.to_bytes(saleID);
if (!oksaleID)
{
return false;
}
bool okdata = m.to_bytes(data);
if (!okdata)
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
ManageSaleOp::count_size(xdr::measurer& m) const 
{
m.count_size(saleID);
m.count_size(data);
m.count_size(ext);
}
bool
ManageSaleOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<ManageSaleOp const&>(other_abstract);return true
&& (saleID== other.saleID)
&& (data== other.data)
&& (ext== other.ext)
;}
bool
ManageSaleOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManageSaleOp const&>(other_abstract);
if (saleID < other.saleID) return true;
if (other.saleID < saleID) return false;
if (data < other.data) return true;
if (other.data < data) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageSaleResultSuccess::_response_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(action_);
if (!ok)
{
return false;
}
switch (action_)
{

    case (int32_t)ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
return u.from_bytes(requestID_);
    case (int32_t)ManageSaleAction::CANCEL:
      return true;
}
return false;
}
bool
ManageSaleResultSuccess::_response_t::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(action_);
if (!ok)
{
return false;
}
switch (action_)
{

    case (int32_t)ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
return m.to_bytes(requestID_);
    case (int32_t)ManageSaleAction::CANCEL:
      return true;
}
return false;
}
void
ManageSaleResultSuccess::_response_t::count_size(xdr::measurer& m) const
{
m.count_size(action_);
switch (action_)
{

    case (int32_t)ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
return m.count_size(requestID_);
    case (int32_t)ManageSaleAction::CANCEL:
    
  return;
}
}
bool
ManageSaleResultSuccess::_response_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_response_t const&>(other_abstract);
if (other.action_ != action_) return false;
switch (action_)
{
    case (int32_t)ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
return requestID_ == other.requestID_;
    case (int32_t)ManageSaleAction::CANCEL:
    
  return true;
}
return false;
}
bool
ManageSaleResultSuccess::_response_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_response_t const&>(other_abstract);
if (action_ < other.action_) return true;
if (other.action_ < action_) return false;
switch (action_)
{
    case (int32_t)ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST:
return requestID_ < other.requestID_;
    case (int32_t)ManageSaleAction::CANCEL:
      return false;
}
return false;
}
bool
ManageSaleResultSuccess::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ManageSaleResultSuccess::_ext_t::to_bytes(xdr::marshaler& m) const
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
ManageSaleResultSuccess::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
ManageSaleResultSuccess::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ManageSaleResultSuccess::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ManageSaleResultSuccess::from_bytes(xdr::unmarshaler& u) 
{
bool okfulfilled = u.from_bytes(fulfilled);
if (!okfulfilled)
{
return false;
}
bool okresponse = u.from_bytes(response);
if (!okresponse)
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
ManageSaleResultSuccess::to_bytes(xdr::marshaler& m) const 
{
bool okfulfilled = m.to_bytes(fulfilled);
if (!okfulfilled)
{
return false;
}
bool okresponse = m.to_bytes(response);
if (!okresponse)
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
ManageSaleResultSuccess::count_size(xdr::measurer& m) const 
{
m.count_size(fulfilled);
m.count_size(response);
m.count_size(ext);
}
bool
ManageSaleResultSuccess::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<ManageSaleResultSuccess const&>(other_abstract);return true
&& (fulfilled== other.fulfilled)
&& (response== other.response)
&& (ext== other.ext)
;}
bool
ManageSaleResultSuccess::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManageSaleResultSuccess const&>(other_abstract);
if (fulfilled < other.fulfilled) return true;
if (other.fulfilled < fulfilled) return false;
if (response < other.response) return true;
if (other.response < response) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ManageSaleResult::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)ManageSaleResultCode::SUCCESS:
return u.from_bytes(success_);
  default:
    return true;
}
return false;
}
bool
ManageSaleResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)ManageSaleResultCode::SUCCESS:
return m.to_bytes(success_);
  default:
    return true;
}
return false;
}
void
ManageSaleResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)ManageSaleResultCode::SUCCESS:
return m.count_size(success_);
  default:
  
  return;
}
}
bool
ManageSaleResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<ManageSaleResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)ManageSaleResultCode::SUCCESS:
return success_ == other.success_;
  default:
  
  return true;
}
return false;
}
bool
ManageSaleResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ManageSaleResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)ManageSaleResultCode::SUCCESS:
return success_ < other.success_;
  default:
    return false;
}
return false;
}
}