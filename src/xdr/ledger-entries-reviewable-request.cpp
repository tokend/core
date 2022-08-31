#include "ledger-entries-reviewable-request.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
TasksExt::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
TasksExt::_ext_t::to_bytes(xdr::marshaler& m) const
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
TasksExt::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
TasksExt::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
TasksExt::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
TasksExt::from_bytes(xdr::unmarshaler& u) 
{
bool okallTasks = u.from_bytes(allTasks);
if (!okallTasks)
{
return false;
}
bool okpendingTasks = u.from_bytes(pendingTasks);
if (!okpendingTasks)
{
return false;
}
bool okexternalDetails = u.from_bytes(externalDetails);
if (!okexternalDetails)
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
TasksExt::to_bytes(xdr::marshaler& m) const 
{
bool okallTasks = m.to_bytes(allTasks);
if (!okallTasks)
{
return false;
}
bool okpendingTasks = m.to_bytes(pendingTasks);
if (!okpendingTasks)
{
return false;
}
bool okexternalDetails = m.to_bytes(externalDetails);
if (!okexternalDetails)
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
TasksExt::count_size(xdr::measurer& m) const 
{
m.count_size(allTasks);
m.count_size(pendingTasks);
m.count_size(externalDetails);
m.count_size(ext);
}
bool
TasksExt::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<TasksExt const&>(other_abstract);return true
&& (allTasks== other.allTasks)
&& (pendingTasks== other.pendingTasks)
&& (externalDetails== other.externalDetails)
&& (ext== other.ext)
;}
bool
TasksExt::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<TasksExt const&>(other_abstract);
if (allTasks < other.allTasks) return true;
if (other.allTasks < allTasks) return false;
if (pendingTasks < other.pendingTasks) return true;
if (other.pendingTasks < pendingTasks) return false;
if (externalDetails < other.externalDetails) return true;
if (other.externalDetails < externalDetails) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
ReviewableRequestEntry::_body_t::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (type_)
{
    case (int32_t)ReviewableRequestType::CREATE_ASSET:
return u.from_bytes(assetCreationRequest_);
    case (int32_t)ReviewableRequestType::UPDATE_ASSET:
return u.from_bytes(assetUpdateRequest_);
    case (int32_t)ReviewableRequestType::CREATE_PRE_ISSUANCE:
return u.from_bytes(preIssuanceRequest_);
    case (int32_t)ReviewableRequestType::CREATE_ISSUANCE:
return u.from_bytes(issuanceRequest_);
    case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
return u.from_bytes(withdrawalRequest_);
    case (int32_t)ReviewableRequestType::CREATE_SALE:
return u.from_bytes(saleCreationRequest_);
    case (int32_t)ReviewableRequestType::UPDATE_LIMITS:
return u.from_bytes(limitsUpdateRequest_);
    case (int32_t)ReviewableRequestType::CREATE_AML_ALERT:
return u.from_bytes(amlAlertRequest_);
    case (int32_t)ReviewableRequestType::CHANGE_ROLE:
return u.from_bytes(changeRoleRequest_);
    case (int32_t)ReviewableRequestType::UPDATE_SALE_DETAILS:
return u.from_bytes(updateSaleDetailsRequest_);
    case (int32_t)ReviewableRequestType::CREATE_INVOICE:
return u.from_bytes(invoiceRequest_);
    case (int32_t)ReviewableRequestType::MANAGE_CONTRACT:
return u.from_bytes(contractRequest_);
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
return u.from_bytes(createAtomicSwapAskRequest_);
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
return u.from_bytes(createAtomicSwapBidRequest_);
    case (int32_t)ReviewableRequestType::CREATE_POLL:
return u.from_bytes(createPollRequest_);
    case (int32_t)ReviewableRequestType::KYC_RECOVERY:
return u.from_bytes(kycRecoveryRequest_);
    case (int32_t)ReviewableRequestType::MANAGE_OFFER:
return u.from_bytes(manageOfferRequest_);
    case (int32_t)ReviewableRequestType::CREATE_PAYMENT:
return u.from_bytes(createPaymentRequest_);
    case (int32_t)ReviewableRequestType::PERFORM_REDEMPTION:
return u.from_bytes(redemptionRequest_);
    case (int32_t)ReviewableRequestType::DATA_CREATION:
return u.from_bytes(dataCreationRequest_);
    case (int32_t)ReviewableRequestType::DATA_UPDATE:
return u.from_bytes(dataUpdateRequest_);
    case (int32_t)ReviewableRequestType::DATA_REMOVE:
return u.from_bytes(dataRemoveRequest_);
    case (int32_t)ReviewableRequestType::CREATE_DEFERRED_PAYMENT:
return u.from_bytes(createDeferredPaymentRequest_);
    case (int32_t)ReviewableRequestType::CLOSE_DEFERRED_PAYMENT:
return u.from_bytes(closeDeferredPaymentRequest_);
    case (int32_t)ReviewableRequestType::DATA_OWNER_UPDATE:
return u.from_bytes(dataOwnerUpdateRequest_);
}
return false;
}
bool
ReviewableRequestEntry::_body_t::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(type_);
if (!ok)
{
return false;
}
switch (type_)
{

    case (int32_t)ReviewableRequestType::CREATE_ASSET:
return m.to_bytes(assetCreationRequest_);
    case (int32_t)ReviewableRequestType::UPDATE_ASSET:
return m.to_bytes(assetUpdateRequest_);
    case (int32_t)ReviewableRequestType::CREATE_PRE_ISSUANCE:
return m.to_bytes(preIssuanceRequest_);
    case (int32_t)ReviewableRequestType::CREATE_ISSUANCE:
return m.to_bytes(issuanceRequest_);
    case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
return m.to_bytes(withdrawalRequest_);
    case (int32_t)ReviewableRequestType::CREATE_SALE:
return m.to_bytes(saleCreationRequest_);
    case (int32_t)ReviewableRequestType::UPDATE_LIMITS:
return m.to_bytes(limitsUpdateRequest_);
    case (int32_t)ReviewableRequestType::CREATE_AML_ALERT:
return m.to_bytes(amlAlertRequest_);
    case (int32_t)ReviewableRequestType::CHANGE_ROLE:
return m.to_bytes(changeRoleRequest_);
    case (int32_t)ReviewableRequestType::UPDATE_SALE_DETAILS:
return m.to_bytes(updateSaleDetailsRequest_);
    case (int32_t)ReviewableRequestType::CREATE_INVOICE:
return m.to_bytes(invoiceRequest_);
    case (int32_t)ReviewableRequestType::MANAGE_CONTRACT:
return m.to_bytes(contractRequest_);
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
return m.to_bytes(createAtomicSwapAskRequest_);
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
return m.to_bytes(createAtomicSwapBidRequest_);
    case (int32_t)ReviewableRequestType::CREATE_POLL:
return m.to_bytes(createPollRequest_);
    case (int32_t)ReviewableRequestType::KYC_RECOVERY:
return m.to_bytes(kycRecoveryRequest_);
    case (int32_t)ReviewableRequestType::MANAGE_OFFER:
return m.to_bytes(manageOfferRequest_);
    case (int32_t)ReviewableRequestType::CREATE_PAYMENT:
return m.to_bytes(createPaymentRequest_);
    case (int32_t)ReviewableRequestType::PERFORM_REDEMPTION:
return m.to_bytes(redemptionRequest_);
    case (int32_t)ReviewableRequestType::DATA_CREATION:
return m.to_bytes(dataCreationRequest_);
    case (int32_t)ReviewableRequestType::DATA_UPDATE:
return m.to_bytes(dataUpdateRequest_);
    case (int32_t)ReviewableRequestType::DATA_REMOVE:
return m.to_bytes(dataRemoveRequest_);
    case (int32_t)ReviewableRequestType::CREATE_DEFERRED_PAYMENT:
return m.to_bytes(createDeferredPaymentRequest_);
    case (int32_t)ReviewableRequestType::CLOSE_DEFERRED_PAYMENT:
return m.to_bytes(closeDeferredPaymentRequest_);
    case (int32_t)ReviewableRequestType::DATA_OWNER_UPDATE:
return m.to_bytes(dataOwnerUpdateRequest_);
}
return false;
}
void
ReviewableRequestEntry::_body_t::count_size(xdr::measurer& m) const
{
m.count_size(type_);
switch (type_)
{

    case (int32_t)ReviewableRequestType::CREATE_ASSET:
return m.count_size(assetCreationRequest_);
    case (int32_t)ReviewableRequestType::UPDATE_ASSET:
return m.count_size(assetUpdateRequest_);
    case (int32_t)ReviewableRequestType::CREATE_PRE_ISSUANCE:
return m.count_size(preIssuanceRequest_);
    case (int32_t)ReviewableRequestType::CREATE_ISSUANCE:
return m.count_size(issuanceRequest_);
    case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
return m.count_size(withdrawalRequest_);
    case (int32_t)ReviewableRequestType::CREATE_SALE:
return m.count_size(saleCreationRequest_);
    case (int32_t)ReviewableRequestType::UPDATE_LIMITS:
return m.count_size(limitsUpdateRequest_);
    case (int32_t)ReviewableRequestType::CREATE_AML_ALERT:
return m.count_size(amlAlertRequest_);
    case (int32_t)ReviewableRequestType::CHANGE_ROLE:
return m.count_size(changeRoleRequest_);
    case (int32_t)ReviewableRequestType::UPDATE_SALE_DETAILS:
return m.count_size(updateSaleDetailsRequest_);
    case (int32_t)ReviewableRequestType::CREATE_INVOICE:
return m.count_size(invoiceRequest_);
    case (int32_t)ReviewableRequestType::MANAGE_CONTRACT:
return m.count_size(contractRequest_);
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
return m.count_size(createAtomicSwapAskRequest_);
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
return m.count_size(createAtomicSwapBidRequest_);
    case (int32_t)ReviewableRequestType::CREATE_POLL:
return m.count_size(createPollRequest_);
    case (int32_t)ReviewableRequestType::KYC_RECOVERY:
return m.count_size(kycRecoveryRequest_);
    case (int32_t)ReviewableRequestType::MANAGE_OFFER:
return m.count_size(manageOfferRequest_);
    case (int32_t)ReviewableRequestType::CREATE_PAYMENT:
return m.count_size(createPaymentRequest_);
    case (int32_t)ReviewableRequestType::PERFORM_REDEMPTION:
return m.count_size(redemptionRequest_);
    case (int32_t)ReviewableRequestType::DATA_CREATION:
return m.count_size(dataCreationRequest_);
    case (int32_t)ReviewableRequestType::DATA_UPDATE:
return m.count_size(dataUpdateRequest_);
    case (int32_t)ReviewableRequestType::DATA_REMOVE:
return m.count_size(dataRemoveRequest_);
    case (int32_t)ReviewableRequestType::CREATE_DEFERRED_PAYMENT:
return m.count_size(createDeferredPaymentRequest_);
    case (int32_t)ReviewableRequestType::CLOSE_DEFERRED_PAYMENT:
return m.count_size(closeDeferredPaymentRequest_);
    case (int32_t)ReviewableRequestType::DATA_OWNER_UPDATE:
return m.count_size(dataOwnerUpdateRequest_);
}
}
bool
ReviewableRequestEntry::_body_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_body_t const&>(other_abstract);
if (other.type_ != type_) return false;
switch (type_)
{
    case (int32_t)ReviewableRequestType::CREATE_ASSET:
return assetCreationRequest_ == other.assetCreationRequest_;
    case (int32_t)ReviewableRequestType::UPDATE_ASSET:
return assetUpdateRequest_ == other.assetUpdateRequest_;
    case (int32_t)ReviewableRequestType::CREATE_PRE_ISSUANCE:
return preIssuanceRequest_ == other.preIssuanceRequest_;
    case (int32_t)ReviewableRequestType::CREATE_ISSUANCE:
return issuanceRequest_ == other.issuanceRequest_;
    case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
return withdrawalRequest_ == other.withdrawalRequest_;
    case (int32_t)ReviewableRequestType::CREATE_SALE:
return saleCreationRequest_ == other.saleCreationRequest_;
    case (int32_t)ReviewableRequestType::UPDATE_LIMITS:
return limitsUpdateRequest_ == other.limitsUpdateRequest_;
    case (int32_t)ReviewableRequestType::CREATE_AML_ALERT:
return amlAlertRequest_ == other.amlAlertRequest_;
    case (int32_t)ReviewableRequestType::CHANGE_ROLE:
return changeRoleRequest_ == other.changeRoleRequest_;
    case (int32_t)ReviewableRequestType::UPDATE_SALE_DETAILS:
return updateSaleDetailsRequest_ == other.updateSaleDetailsRequest_;
    case (int32_t)ReviewableRequestType::CREATE_INVOICE:
return invoiceRequest_ == other.invoiceRequest_;
    case (int32_t)ReviewableRequestType::MANAGE_CONTRACT:
return contractRequest_ == other.contractRequest_;
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
return createAtomicSwapAskRequest_ == other.createAtomicSwapAskRequest_;
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
return createAtomicSwapBidRequest_ == other.createAtomicSwapBidRequest_;
    case (int32_t)ReviewableRequestType::CREATE_POLL:
return createPollRequest_ == other.createPollRequest_;
    case (int32_t)ReviewableRequestType::KYC_RECOVERY:
return kycRecoveryRequest_ == other.kycRecoveryRequest_;
    case (int32_t)ReviewableRequestType::MANAGE_OFFER:
return manageOfferRequest_ == other.manageOfferRequest_;
    case (int32_t)ReviewableRequestType::CREATE_PAYMENT:
return createPaymentRequest_ == other.createPaymentRequest_;
    case (int32_t)ReviewableRequestType::PERFORM_REDEMPTION:
return redemptionRequest_ == other.redemptionRequest_;
    case (int32_t)ReviewableRequestType::DATA_CREATION:
return dataCreationRequest_ == other.dataCreationRequest_;
    case (int32_t)ReviewableRequestType::DATA_UPDATE:
return dataUpdateRequest_ == other.dataUpdateRequest_;
    case (int32_t)ReviewableRequestType::DATA_REMOVE:
return dataRemoveRequest_ == other.dataRemoveRequest_;
    case (int32_t)ReviewableRequestType::CREATE_DEFERRED_PAYMENT:
return createDeferredPaymentRequest_ == other.createDeferredPaymentRequest_;
    case (int32_t)ReviewableRequestType::CLOSE_DEFERRED_PAYMENT:
return closeDeferredPaymentRequest_ == other.closeDeferredPaymentRequest_;
    case (int32_t)ReviewableRequestType::DATA_OWNER_UPDATE:
return dataOwnerUpdateRequest_ == other.dataOwnerUpdateRequest_;
}
return false;
}
bool
ReviewableRequestEntry::_body_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_body_t const&>(other_abstract);
if (type_ < other.type_) return true;
if (other.type_ < type_) return false;
switch (type_)
{
    case (int32_t)ReviewableRequestType::CREATE_ASSET:
return assetCreationRequest_ < other.assetCreationRequest_;
    case (int32_t)ReviewableRequestType::UPDATE_ASSET:
return assetUpdateRequest_ < other.assetUpdateRequest_;
    case (int32_t)ReviewableRequestType::CREATE_PRE_ISSUANCE:
return preIssuanceRequest_ < other.preIssuanceRequest_;
    case (int32_t)ReviewableRequestType::CREATE_ISSUANCE:
return issuanceRequest_ < other.issuanceRequest_;
    case (int32_t)ReviewableRequestType::CREATE_WITHDRAW:
return withdrawalRequest_ < other.withdrawalRequest_;
    case (int32_t)ReviewableRequestType::CREATE_SALE:
return saleCreationRequest_ < other.saleCreationRequest_;
    case (int32_t)ReviewableRequestType::UPDATE_LIMITS:
return limitsUpdateRequest_ < other.limitsUpdateRequest_;
    case (int32_t)ReviewableRequestType::CREATE_AML_ALERT:
return amlAlertRequest_ < other.amlAlertRequest_;
    case (int32_t)ReviewableRequestType::CHANGE_ROLE:
return changeRoleRequest_ < other.changeRoleRequest_;
    case (int32_t)ReviewableRequestType::UPDATE_SALE_DETAILS:
return updateSaleDetailsRequest_ < other.updateSaleDetailsRequest_;
    case (int32_t)ReviewableRequestType::CREATE_INVOICE:
return invoiceRequest_ < other.invoiceRequest_;
    case (int32_t)ReviewableRequestType::MANAGE_CONTRACT:
return contractRequest_ < other.contractRequest_;
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
return createAtomicSwapAskRequest_ < other.createAtomicSwapAskRequest_;
    case (int32_t)ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
return createAtomicSwapBidRequest_ < other.createAtomicSwapBidRequest_;
    case (int32_t)ReviewableRequestType::CREATE_POLL:
return createPollRequest_ < other.createPollRequest_;
    case (int32_t)ReviewableRequestType::KYC_RECOVERY:
return kycRecoveryRequest_ < other.kycRecoveryRequest_;
    case (int32_t)ReviewableRequestType::MANAGE_OFFER:
return manageOfferRequest_ < other.manageOfferRequest_;
    case (int32_t)ReviewableRequestType::CREATE_PAYMENT:
return createPaymentRequest_ < other.createPaymentRequest_;
    case (int32_t)ReviewableRequestType::PERFORM_REDEMPTION:
return redemptionRequest_ < other.redemptionRequest_;
    case (int32_t)ReviewableRequestType::DATA_CREATION:
return dataCreationRequest_ < other.dataCreationRequest_;
    case (int32_t)ReviewableRequestType::DATA_UPDATE:
return dataUpdateRequest_ < other.dataUpdateRequest_;
    case (int32_t)ReviewableRequestType::DATA_REMOVE:
return dataRemoveRequest_ < other.dataRemoveRequest_;
    case (int32_t)ReviewableRequestType::CREATE_DEFERRED_PAYMENT:
return createDeferredPaymentRequest_ < other.createDeferredPaymentRequest_;
    case (int32_t)ReviewableRequestType::CLOSE_DEFERRED_PAYMENT:
return closeDeferredPaymentRequest_ < other.closeDeferredPaymentRequest_;
    case (int32_t)ReviewableRequestType::DATA_OWNER_UPDATE:
return dataOwnerUpdateRequest_ < other.dataOwnerUpdateRequest_;
}
return false;
}
bool
ReviewableRequestEntry::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
ReviewableRequestEntry::_ext_t::to_bytes(xdr::marshaler& m) const
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
ReviewableRequestEntry::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
ReviewableRequestEntry::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
ReviewableRequestEntry::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
ReviewableRequestEntry::from_bytes(xdr::unmarshaler& u) 
{
bool okrequestID = u.from_bytes(requestID);
if (!okrequestID)
{
return false;
}
bool okhash = u.from_bytes(hash);
if (!okhash)
{
return false;
}
bool okrequestor = u.from_bytes(requestor);
if (!okrequestor)
{
return false;
}
bool okrejectReason = u.from_bytes(rejectReason);
if (!okrejectReason)
{
return false;
}
bool okreviewer = u.from_bytes(reviewer);
if (!okreviewer)
{
return false;
}
bool okreference = u.from_bytes(reference);
if (!okreference)
{
return false;
}
bool okcreatedAt = u.from_bytes(createdAt);
if (!okcreatedAt)
{
return false;
}
bool okbody = u.from_bytes(body);
if (!okbody)
{
return false;
}
bool oktasks = u.from_bytes(tasks);
if (!oktasks)
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
ReviewableRequestEntry::to_bytes(xdr::marshaler& m) const 
{
bool okrequestID = m.to_bytes(requestID);
if (!okrequestID)
{
return false;
}
bool okhash = m.to_bytes(hash);
if (!okhash)
{
return false;
}
bool okrequestor = m.to_bytes(requestor);
if (!okrequestor)
{
return false;
}
bool okrejectReason = m.to_bytes(rejectReason);
if (!okrejectReason)
{
return false;
}
bool okreviewer = m.to_bytes(reviewer);
if (!okreviewer)
{
return false;
}
bool okreference = m.to_bytes(reference);
if (!okreference)
{
return false;
}
bool okcreatedAt = m.to_bytes(createdAt);
if (!okcreatedAt)
{
return false;
}
bool okbody = m.to_bytes(body);
if (!okbody)
{
return false;
}
bool oktasks = m.to_bytes(tasks);
if (!oktasks)
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
ReviewableRequestEntry::count_size(xdr::measurer& m) const 
{
m.count_size(requestID);
m.count_size(hash);
m.count_size(requestor);
m.count_size(rejectReason);
m.count_size(reviewer);
m.count_size(reference);
m.count_size(createdAt);
m.count_size(body);
m.count_size(tasks);
m.count_size(ext);
}
bool
ReviewableRequestEntry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<ReviewableRequestEntry const&>(other_abstract);return true
&& (requestID== other.requestID)
&& (hash== other.hash)
&& (requestor== other.requestor)
&& (rejectReason== other.rejectReason)
&& (reviewer== other.reviewer)
&& (reference== other.reference)
&& (createdAt== other.createdAt)
&& (body== other.body)
&& (tasks== other.tasks)
&& (ext== other.ext)
;}
bool
ReviewableRequestEntry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<ReviewableRequestEntry const&>(other_abstract);
if (requestID < other.requestID) return true;
if (other.requestID < requestID) return false;
if (hash < other.hash) return true;
if (other.hash < hash) return false;
if (requestor < other.requestor) return true;
if (other.requestor < requestor) return false;
if (rejectReason < other.rejectReason) return true;
if (other.rejectReason < rejectReason) return false;
if (reviewer < other.reviewer) return true;
if (other.reviewer < reviewer) return false;
if (reference < other.reference) return true;
if (other.reference < reference) return false;
if (createdAt < other.createdAt) return true;
if (other.createdAt < createdAt) return false;
if (body < other.body) return true;
if (other.body < body) return false;
if (tasks < other.tasks) return true;
if (other.tasks < tasks) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}