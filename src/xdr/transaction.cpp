#include "transaction.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
Operation::_body_t::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (type_)
{
    case (int32_t)OperationType::CREATE_ACCOUNT:
return u.from_bytes(createAccountOp_);
    case (int32_t)OperationType::CREATE_ISSUANCE_REQUEST:
return u.from_bytes(createIssuanceRequestOp_);
    case (int32_t)OperationType::SET_FEES:
return u.from_bytes(setFeesOp_);
    case (int32_t)OperationType::CREATE_WITHDRAWAL_REQUEST:
return u.from_bytes(createWithdrawalRequestOp_);
    case (int32_t)OperationType::MANAGE_BALANCE:
return u.from_bytes(manageBalanceOp_);
    case (int32_t)OperationType::MANAGE_ASSET:
return u.from_bytes(manageAssetOp_);
    case (int32_t)OperationType::CREATE_PREISSUANCE_REQUEST:
return u.from_bytes(createPreIssuanceRequest_);
    case (int32_t)OperationType::MANAGE_LIMITS:
return u.from_bytes(manageLimitsOp_);
    case (int32_t)OperationType::MANAGE_ASSET_PAIR:
return u.from_bytes(manageAssetPairOp_);
    case (int32_t)OperationType::MANAGE_OFFER:
return u.from_bytes(manageOfferOp_);
    case (int32_t)OperationType::MANAGE_INVOICE_REQUEST:
return u.from_bytes(manageInvoiceRequestOp_);
    case (int32_t)OperationType::REVIEW_REQUEST:
return u.from_bytes(reviewRequestOp_);
    case (int32_t)OperationType::CREATE_SALE_REQUEST:
return u.from_bytes(createSaleCreationRequestOp_);
    case (int32_t)OperationType::CHECK_SALE_STATE:
return u.from_bytes(checkSaleStateOp_);
    case (int32_t)OperationType::PAYOUT:
return u.from_bytes(payoutOp_);
    case (int32_t)OperationType::CREATE_AML_ALERT:
return u.from_bytes(createAMLAlertRequestOp_);
    case (int32_t)OperationType::MANAGE_KEY_VALUE:
return u.from_bytes(manageKeyValueOp_);
    case (int32_t)OperationType::CREATE_CHANGE_ROLE_REQUEST:
return u.from_bytes(createChangeRoleRequestOp_);
    case (int32_t)OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
return u.from_bytes(manageExternalSystemAccountIdPoolEntryOp_);
    case (int32_t)OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID:
return u.from_bytes(bindExternalSystemAccountIdOp_);
    case (int32_t)OperationType::PAYMENT:
return u.from_bytes(paymentOp_);
    case (int32_t)OperationType::MANAGE_SALE:
return u.from_bytes(manageSaleOp_);
    case (int32_t)OperationType::CREATE_MANAGE_LIMITS_REQUEST:
return u.from_bytes(createManageLimitsRequestOp_);
    case (int32_t)OperationType::MANAGE_CONTRACT_REQUEST:
return u.from_bytes(manageContractRequestOp_);
    case (int32_t)OperationType::MANAGE_CONTRACT:
return u.from_bytes(manageContractOp_);
    case (int32_t)OperationType::CANCEL_SALE_REQUEST:
return u.from_bytes(cancelSaleCreationRequestOp_);
    case (int32_t)OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST:
return u.from_bytes(createAtomicSwapAskRequestOp_);
    case (int32_t)OperationType::CANCEL_ATOMIC_SWAP_ASK:
return u.from_bytes(cancelAtomicSwapAskOp_);
    case (int32_t)OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST:
return u.from_bytes(createAtomicSwapBidRequestOp_);
    case (int32_t)OperationType::MANAGE_ACCOUNT_ROLE:
return u.from_bytes(manageAccountRoleOp_);
    case (int32_t)OperationType::MANAGE_ACCOUNT_RULE:
return u.from_bytes(manageAccountRuleOp_);
    case (int32_t)OperationType::MANAGE_SIGNER:
return u.from_bytes(manageSignerOp_);
    case (int32_t)OperationType::MANAGE_SIGNER_ROLE:
return u.from_bytes(manageSignerRoleOp_);
    case (int32_t)OperationType::MANAGE_SIGNER_RULE:
return u.from_bytes(manageSignerRuleOp_);
    case (int32_t)OperationType::STAMP:
return u.from_bytes(stampOp_);
    case (int32_t)OperationType::LICENSE:
return u.from_bytes(licenseOp_);
    case (int32_t)OperationType::MANAGE_CREATE_POLL_REQUEST:
return u.from_bytes(manageCreatePollRequestOp_);
    case (int32_t)OperationType::MANAGE_POLL:
return u.from_bytes(managePollOp_);
    case (int32_t)OperationType::MANAGE_VOTE:
return u.from_bytes(manageVoteOp_);
    case (int32_t)OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE:
return u.from_bytes(manageAccountSpecificRuleOp_);
    case (int32_t)OperationType::CANCEL_CHANGE_ROLE_REQUEST:
return u.from_bytes(cancelChangeRoleRequestOp_);
    case (int32_t)OperationType::REMOVE_ASSET_PAIR:
return u.from_bytes(removeAssetPairOp_);
    case (int32_t)OperationType::INITIATE_KYC_RECOVERY:
return u.from_bytes(initiateKYCRecoveryOp_);
    case (int32_t)OperationType::CREATE_KYC_RECOVERY_REQUEST:
return u.from_bytes(createKYCRecoveryRequestOp_);
    case (int32_t)OperationType::CREATE_MANAGE_OFFER_REQUEST:
return u.from_bytes(createManageOfferRequestOp_);
    case (int32_t)OperationType::CREATE_PAYMENT_REQUEST:
return u.from_bytes(createPaymentRequestOp_);
    case (int32_t)OperationType::REMOVE_ASSET:
return u.from_bytes(removeAssetOp_);
    case (int32_t)OperationType::OPEN_SWAP:
return u.from_bytes(openSwapOp_);
    case (int32_t)OperationType::CLOSE_SWAP:
return u.from_bytes(closeSwapOp_);
    case (int32_t)OperationType::CREATE_REDEMPTION_REQUEST:
return u.from_bytes(createRedemptionRequestOp_);
    case (int32_t)OperationType::CREATE_DATA:
return u.from_bytes(createDataOp_);
    case (int32_t)OperationType::UPDATE_DATA:
return u.from_bytes(updateDataOp_);
    case (int32_t)OperationType::REMOVE_DATA:
return u.from_bytes(removeDataOp_);
    case (int32_t)OperationType::CREATE_DATA_CREATION_REQUEST:
return u.from_bytes(createDataCreationRequestOp_);
    case (int32_t)OperationType::CANCEL_DATA_CREATION_REQUEST:
return u.from_bytes(cancelDataCreationRequestOp_);
    case (int32_t)OperationType::CREATE_DATA_UPDATE_REQUEST:
return u.from_bytes(createDataUpdateRequestOp_);
    case (int32_t)OperationType::CREATE_DATA_REMOVE_REQUEST:
return u.from_bytes(createDataRemoveRequestOp_);
    case (int32_t)OperationType::CANCEL_DATA_UPDATE_REQUEST:
return u.from_bytes(cancelDataUpdateRequestOp_);
    case (int32_t)OperationType::CANCEL_DATA_REMOVE_REQUEST:
return u.from_bytes(cancelDataRemoveRequestOp_);
    case (int32_t)OperationType::CREATE_DEFERRED_PAYMENT_CREATION_REQUEST:
return u.from_bytes(createDeferredPaymentCreationRequestOp_);
    case (int32_t)OperationType::CANCEL_DEFERRED_PAYMENT_CREATION_REQUEST:
return u.from_bytes(cancelDeferredPaymentCreationRequestOp_);
    case (int32_t)OperationType::CREATE_CLOSE_DEFERRED_PAYMENT_REQUEST:
return u.from_bytes(createCloseDeferredPaymentRequestOp_);
    case (int32_t)OperationType::CANCEL_CLOSE_DEFERRED_PAYMENT_REQUEST:
return u.from_bytes(cancelCloseDeferredPaymentRequestOp_);
    case (int32_t)OperationType::UPDATE_DATA_OWNER:
return u.from_bytes(updateDataOwnerOp_);
    case (int32_t)OperationType::CREATE_DATA_OWNER_UPDATE_REQUEST:
return u.from_bytes(createDataOwnerUpdateRequestOp_);
    case (int32_t)OperationType::CANCEL_DATA_OWNER_UPDATE_REQUEST:
return u.from_bytes(cancelDataOwnerUpdateRequestOp_);
}
return false;
}
bool
Operation::_body_t::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(type_);
if (!ok)
{
return false;
}
switch (type_)
{

    case (int32_t)OperationType::CREATE_ACCOUNT:
return m.to_bytes(createAccountOp_);
    case (int32_t)OperationType::CREATE_ISSUANCE_REQUEST:
return m.to_bytes(createIssuanceRequestOp_);
    case (int32_t)OperationType::SET_FEES:
return m.to_bytes(setFeesOp_);
    case (int32_t)OperationType::CREATE_WITHDRAWAL_REQUEST:
return m.to_bytes(createWithdrawalRequestOp_);
    case (int32_t)OperationType::MANAGE_BALANCE:
return m.to_bytes(manageBalanceOp_);
    case (int32_t)OperationType::MANAGE_ASSET:
return m.to_bytes(manageAssetOp_);
    case (int32_t)OperationType::CREATE_PREISSUANCE_REQUEST:
return m.to_bytes(createPreIssuanceRequest_);
    case (int32_t)OperationType::MANAGE_LIMITS:
return m.to_bytes(manageLimitsOp_);
    case (int32_t)OperationType::MANAGE_ASSET_PAIR:
return m.to_bytes(manageAssetPairOp_);
    case (int32_t)OperationType::MANAGE_OFFER:
return m.to_bytes(manageOfferOp_);
    case (int32_t)OperationType::MANAGE_INVOICE_REQUEST:
return m.to_bytes(manageInvoiceRequestOp_);
    case (int32_t)OperationType::REVIEW_REQUEST:
return m.to_bytes(reviewRequestOp_);
    case (int32_t)OperationType::CREATE_SALE_REQUEST:
return m.to_bytes(createSaleCreationRequestOp_);
    case (int32_t)OperationType::CHECK_SALE_STATE:
return m.to_bytes(checkSaleStateOp_);
    case (int32_t)OperationType::PAYOUT:
return m.to_bytes(payoutOp_);
    case (int32_t)OperationType::CREATE_AML_ALERT:
return m.to_bytes(createAMLAlertRequestOp_);
    case (int32_t)OperationType::MANAGE_KEY_VALUE:
return m.to_bytes(manageKeyValueOp_);
    case (int32_t)OperationType::CREATE_CHANGE_ROLE_REQUEST:
return m.to_bytes(createChangeRoleRequestOp_);
    case (int32_t)OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
return m.to_bytes(manageExternalSystemAccountIdPoolEntryOp_);
    case (int32_t)OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID:
return m.to_bytes(bindExternalSystemAccountIdOp_);
    case (int32_t)OperationType::PAYMENT:
return m.to_bytes(paymentOp_);
    case (int32_t)OperationType::MANAGE_SALE:
return m.to_bytes(manageSaleOp_);
    case (int32_t)OperationType::CREATE_MANAGE_LIMITS_REQUEST:
return m.to_bytes(createManageLimitsRequestOp_);
    case (int32_t)OperationType::MANAGE_CONTRACT_REQUEST:
return m.to_bytes(manageContractRequestOp_);
    case (int32_t)OperationType::MANAGE_CONTRACT:
return m.to_bytes(manageContractOp_);
    case (int32_t)OperationType::CANCEL_SALE_REQUEST:
return m.to_bytes(cancelSaleCreationRequestOp_);
    case (int32_t)OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST:
return m.to_bytes(createAtomicSwapAskRequestOp_);
    case (int32_t)OperationType::CANCEL_ATOMIC_SWAP_ASK:
return m.to_bytes(cancelAtomicSwapAskOp_);
    case (int32_t)OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST:
return m.to_bytes(createAtomicSwapBidRequestOp_);
    case (int32_t)OperationType::MANAGE_ACCOUNT_ROLE:
return m.to_bytes(manageAccountRoleOp_);
    case (int32_t)OperationType::MANAGE_ACCOUNT_RULE:
return m.to_bytes(manageAccountRuleOp_);
    case (int32_t)OperationType::MANAGE_SIGNER:
return m.to_bytes(manageSignerOp_);
    case (int32_t)OperationType::MANAGE_SIGNER_ROLE:
return m.to_bytes(manageSignerRoleOp_);
    case (int32_t)OperationType::MANAGE_SIGNER_RULE:
return m.to_bytes(manageSignerRuleOp_);
    case (int32_t)OperationType::STAMP:
return m.to_bytes(stampOp_);
    case (int32_t)OperationType::LICENSE:
return m.to_bytes(licenseOp_);
    case (int32_t)OperationType::MANAGE_CREATE_POLL_REQUEST:
return m.to_bytes(manageCreatePollRequestOp_);
    case (int32_t)OperationType::MANAGE_POLL:
return m.to_bytes(managePollOp_);
    case (int32_t)OperationType::MANAGE_VOTE:
return m.to_bytes(manageVoteOp_);
    case (int32_t)OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE:
return m.to_bytes(manageAccountSpecificRuleOp_);
    case (int32_t)OperationType::CANCEL_CHANGE_ROLE_REQUEST:
return m.to_bytes(cancelChangeRoleRequestOp_);
    case (int32_t)OperationType::REMOVE_ASSET_PAIR:
return m.to_bytes(removeAssetPairOp_);
    case (int32_t)OperationType::INITIATE_KYC_RECOVERY:
return m.to_bytes(initiateKYCRecoveryOp_);
    case (int32_t)OperationType::CREATE_KYC_RECOVERY_REQUEST:
return m.to_bytes(createKYCRecoveryRequestOp_);
    case (int32_t)OperationType::CREATE_MANAGE_OFFER_REQUEST:
return m.to_bytes(createManageOfferRequestOp_);
    case (int32_t)OperationType::CREATE_PAYMENT_REQUEST:
return m.to_bytes(createPaymentRequestOp_);
    case (int32_t)OperationType::REMOVE_ASSET:
return m.to_bytes(removeAssetOp_);
    case (int32_t)OperationType::OPEN_SWAP:
return m.to_bytes(openSwapOp_);
    case (int32_t)OperationType::CLOSE_SWAP:
return m.to_bytes(closeSwapOp_);
    case (int32_t)OperationType::CREATE_REDEMPTION_REQUEST:
return m.to_bytes(createRedemptionRequestOp_);
    case (int32_t)OperationType::CREATE_DATA:
return m.to_bytes(createDataOp_);
    case (int32_t)OperationType::UPDATE_DATA:
return m.to_bytes(updateDataOp_);
    case (int32_t)OperationType::REMOVE_DATA:
return m.to_bytes(removeDataOp_);
    case (int32_t)OperationType::CREATE_DATA_CREATION_REQUEST:
return m.to_bytes(createDataCreationRequestOp_);
    case (int32_t)OperationType::CANCEL_DATA_CREATION_REQUEST:
return m.to_bytes(cancelDataCreationRequestOp_);
    case (int32_t)OperationType::CREATE_DATA_UPDATE_REQUEST:
return m.to_bytes(createDataUpdateRequestOp_);
    case (int32_t)OperationType::CREATE_DATA_REMOVE_REQUEST:
return m.to_bytes(createDataRemoveRequestOp_);
    case (int32_t)OperationType::CANCEL_DATA_UPDATE_REQUEST:
return m.to_bytes(cancelDataUpdateRequestOp_);
    case (int32_t)OperationType::CANCEL_DATA_REMOVE_REQUEST:
return m.to_bytes(cancelDataRemoveRequestOp_);
    case (int32_t)OperationType::CREATE_DEFERRED_PAYMENT_CREATION_REQUEST:
return m.to_bytes(createDeferredPaymentCreationRequestOp_);
    case (int32_t)OperationType::CANCEL_DEFERRED_PAYMENT_CREATION_REQUEST:
return m.to_bytes(cancelDeferredPaymentCreationRequestOp_);
    case (int32_t)OperationType::CREATE_CLOSE_DEFERRED_PAYMENT_REQUEST:
return m.to_bytes(createCloseDeferredPaymentRequestOp_);
    case (int32_t)OperationType::CANCEL_CLOSE_DEFERRED_PAYMENT_REQUEST:
return m.to_bytes(cancelCloseDeferredPaymentRequestOp_);
    case (int32_t)OperationType::UPDATE_DATA_OWNER:
return m.to_bytes(updateDataOwnerOp_);
    case (int32_t)OperationType::CREATE_DATA_OWNER_UPDATE_REQUEST:
return m.to_bytes(createDataOwnerUpdateRequestOp_);
    case (int32_t)OperationType::CANCEL_DATA_OWNER_UPDATE_REQUEST:
return m.to_bytes(cancelDataOwnerUpdateRequestOp_);
}
return false;
}
void
Operation::_body_t::count_size(xdr::measurer& m) const
{
m.count_size(type_);
switch (type_)
{

    case (int32_t)OperationType::CREATE_ACCOUNT:
return m.count_size(createAccountOp_);
    case (int32_t)OperationType::CREATE_ISSUANCE_REQUEST:
return m.count_size(createIssuanceRequestOp_);
    case (int32_t)OperationType::SET_FEES:
return m.count_size(setFeesOp_);
    case (int32_t)OperationType::CREATE_WITHDRAWAL_REQUEST:
return m.count_size(createWithdrawalRequestOp_);
    case (int32_t)OperationType::MANAGE_BALANCE:
return m.count_size(manageBalanceOp_);
    case (int32_t)OperationType::MANAGE_ASSET:
return m.count_size(manageAssetOp_);
    case (int32_t)OperationType::CREATE_PREISSUANCE_REQUEST:
return m.count_size(createPreIssuanceRequest_);
    case (int32_t)OperationType::MANAGE_LIMITS:
return m.count_size(manageLimitsOp_);
    case (int32_t)OperationType::MANAGE_ASSET_PAIR:
return m.count_size(manageAssetPairOp_);
    case (int32_t)OperationType::MANAGE_OFFER:
return m.count_size(manageOfferOp_);
    case (int32_t)OperationType::MANAGE_INVOICE_REQUEST:
return m.count_size(manageInvoiceRequestOp_);
    case (int32_t)OperationType::REVIEW_REQUEST:
return m.count_size(reviewRequestOp_);
    case (int32_t)OperationType::CREATE_SALE_REQUEST:
return m.count_size(createSaleCreationRequestOp_);
    case (int32_t)OperationType::CHECK_SALE_STATE:
return m.count_size(checkSaleStateOp_);
    case (int32_t)OperationType::PAYOUT:
return m.count_size(payoutOp_);
    case (int32_t)OperationType::CREATE_AML_ALERT:
return m.count_size(createAMLAlertRequestOp_);
    case (int32_t)OperationType::MANAGE_KEY_VALUE:
return m.count_size(manageKeyValueOp_);
    case (int32_t)OperationType::CREATE_CHANGE_ROLE_REQUEST:
return m.count_size(createChangeRoleRequestOp_);
    case (int32_t)OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
return m.count_size(manageExternalSystemAccountIdPoolEntryOp_);
    case (int32_t)OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID:
return m.count_size(bindExternalSystemAccountIdOp_);
    case (int32_t)OperationType::PAYMENT:
return m.count_size(paymentOp_);
    case (int32_t)OperationType::MANAGE_SALE:
return m.count_size(manageSaleOp_);
    case (int32_t)OperationType::CREATE_MANAGE_LIMITS_REQUEST:
return m.count_size(createManageLimitsRequestOp_);
    case (int32_t)OperationType::MANAGE_CONTRACT_REQUEST:
return m.count_size(manageContractRequestOp_);
    case (int32_t)OperationType::MANAGE_CONTRACT:
return m.count_size(manageContractOp_);
    case (int32_t)OperationType::CANCEL_SALE_REQUEST:
return m.count_size(cancelSaleCreationRequestOp_);
    case (int32_t)OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST:
return m.count_size(createAtomicSwapAskRequestOp_);
    case (int32_t)OperationType::CANCEL_ATOMIC_SWAP_ASK:
return m.count_size(cancelAtomicSwapAskOp_);
    case (int32_t)OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST:
return m.count_size(createAtomicSwapBidRequestOp_);
    case (int32_t)OperationType::MANAGE_ACCOUNT_ROLE:
return m.count_size(manageAccountRoleOp_);
    case (int32_t)OperationType::MANAGE_ACCOUNT_RULE:
return m.count_size(manageAccountRuleOp_);
    case (int32_t)OperationType::MANAGE_SIGNER:
return m.count_size(manageSignerOp_);
    case (int32_t)OperationType::MANAGE_SIGNER_ROLE:
return m.count_size(manageSignerRoleOp_);
    case (int32_t)OperationType::MANAGE_SIGNER_RULE:
return m.count_size(manageSignerRuleOp_);
    case (int32_t)OperationType::STAMP:
return m.count_size(stampOp_);
    case (int32_t)OperationType::LICENSE:
return m.count_size(licenseOp_);
    case (int32_t)OperationType::MANAGE_CREATE_POLL_REQUEST:
return m.count_size(manageCreatePollRequestOp_);
    case (int32_t)OperationType::MANAGE_POLL:
return m.count_size(managePollOp_);
    case (int32_t)OperationType::MANAGE_VOTE:
return m.count_size(manageVoteOp_);
    case (int32_t)OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE:
return m.count_size(manageAccountSpecificRuleOp_);
    case (int32_t)OperationType::CANCEL_CHANGE_ROLE_REQUEST:
return m.count_size(cancelChangeRoleRequestOp_);
    case (int32_t)OperationType::REMOVE_ASSET_PAIR:
return m.count_size(removeAssetPairOp_);
    case (int32_t)OperationType::INITIATE_KYC_RECOVERY:
return m.count_size(initiateKYCRecoveryOp_);
    case (int32_t)OperationType::CREATE_KYC_RECOVERY_REQUEST:
return m.count_size(createKYCRecoveryRequestOp_);
    case (int32_t)OperationType::CREATE_MANAGE_OFFER_REQUEST:
return m.count_size(createManageOfferRequestOp_);
    case (int32_t)OperationType::CREATE_PAYMENT_REQUEST:
return m.count_size(createPaymentRequestOp_);
    case (int32_t)OperationType::REMOVE_ASSET:
return m.count_size(removeAssetOp_);
    case (int32_t)OperationType::OPEN_SWAP:
return m.count_size(openSwapOp_);
    case (int32_t)OperationType::CLOSE_SWAP:
return m.count_size(closeSwapOp_);
    case (int32_t)OperationType::CREATE_REDEMPTION_REQUEST:
return m.count_size(createRedemptionRequestOp_);
    case (int32_t)OperationType::CREATE_DATA:
return m.count_size(createDataOp_);
    case (int32_t)OperationType::UPDATE_DATA:
return m.count_size(updateDataOp_);
    case (int32_t)OperationType::REMOVE_DATA:
return m.count_size(removeDataOp_);
    case (int32_t)OperationType::CREATE_DATA_CREATION_REQUEST:
return m.count_size(createDataCreationRequestOp_);
    case (int32_t)OperationType::CANCEL_DATA_CREATION_REQUEST:
return m.count_size(cancelDataCreationRequestOp_);
    case (int32_t)OperationType::CREATE_DATA_UPDATE_REQUEST:
return m.count_size(createDataUpdateRequestOp_);
    case (int32_t)OperationType::CREATE_DATA_REMOVE_REQUEST:
return m.count_size(createDataRemoveRequestOp_);
    case (int32_t)OperationType::CANCEL_DATA_UPDATE_REQUEST:
return m.count_size(cancelDataUpdateRequestOp_);
    case (int32_t)OperationType::CANCEL_DATA_REMOVE_REQUEST:
return m.count_size(cancelDataRemoveRequestOp_);
    case (int32_t)OperationType::CREATE_DEFERRED_PAYMENT_CREATION_REQUEST:
return m.count_size(createDeferredPaymentCreationRequestOp_);
    case (int32_t)OperationType::CANCEL_DEFERRED_PAYMENT_CREATION_REQUEST:
return m.count_size(cancelDeferredPaymentCreationRequestOp_);
    case (int32_t)OperationType::CREATE_CLOSE_DEFERRED_PAYMENT_REQUEST:
return m.count_size(createCloseDeferredPaymentRequestOp_);
    case (int32_t)OperationType::CANCEL_CLOSE_DEFERRED_PAYMENT_REQUEST:
return m.count_size(cancelCloseDeferredPaymentRequestOp_);
    case (int32_t)OperationType::UPDATE_DATA_OWNER:
return m.count_size(updateDataOwnerOp_);
    case (int32_t)OperationType::CREATE_DATA_OWNER_UPDATE_REQUEST:
return m.count_size(createDataOwnerUpdateRequestOp_);
    case (int32_t)OperationType::CANCEL_DATA_OWNER_UPDATE_REQUEST:
return m.count_size(cancelDataOwnerUpdateRequestOp_);
}
}
bool
Operation::_body_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_body_t const&>(other_abstract);
if (other.type_ != type_) return false;
switch (type_)
{
    case (int32_t)OperationType::CREATE_ACCOUNT:
return createAccountOp_ == other.createAccountOp_;
    case (int32_t)OperationType::CREATE_ISSUANCE_REQUEST:
return createIssuanceRequestOp_ == other.createIssuanceRequestOp_;
    case (int32_t)OperationType::SET_FEES:
return setFeesOp_ == other.setFeesOp_;
    case (int32_t)OperationType::CREATE_WITHDRAWAL_REQUEST:
return createWithdrawalRequestOp_ == other.createWithdrawalRequestOp_;
    case (int32_t)OperationType::MANAGE_BALANCE:
return manageBalanceOp_ == other.manageBalanceOp_;
    case (int32_t)OperationType::MANAGE_ASSET:
return manageAssetOp_ == other.manageAssetOp_;
    case (int32_t)OperationType::CREATE_PREISSUANCE_REQUEST:
return createPreIssuanceRequest_ == other.createPreIssuanceRequest_;
    case (int32_t)OperationType::MANAGE_LIMITS:
return manageLimitsOp_ == other.manageLimitsOp_;
    case (int32_t)OperationType::MANAGE_ASSET_PAIR:
return manageAssetPairOp_ == other.manageAssetPairOp_;
    case (int32_t)OperationType::MANAGE_OFFER:
return manageOfferOp_ == other.manageOfferOp_;
    case (int32_t)OperationType::MANAGE_INVOICE_REQUEST:
return manageInvoiceRequestOp_ == other.manageInvoiceRequestOp_;
    case (int32_t)OperationType::REVIEW_REQUEST:
return reviewRequestOp_ == other.reviewRequestOp_;
    case (int32_t)OperationType::CREATE_SALE_REQUEST:
return createSaleCreationRequestOp_ == other.createSaleCreationRequestOp_;
    case (int32_t)OperationType::CHECK_SALE_STATE:
return checkSaleStateOp_ == other.checkSaleStateOp_;
    case (int32_t)OperationType::PAYOUT:
return payoutOp_ == other.payoutOp_;
    case (int32_t)OperationType::CREATE_AML_ALERT:
return createAMLAlertRequestOp_ == other.createAMLAlertRequestOp_;
    case (int32_t)OperationType::MANAGE_KEY_VALUE:
return manageKeyValueOp_ == other.manageKeyValueOp_;
    case (int32_t)OperationType::CREATE_CHANGE_ROLE_REQUEST:
return createChangeRoleRequestOp_ == other.createChangeRoleRequestOp_;
    case (int32_t)OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
return manageExternalSystemAccountIdPoolEntryOp_ == other.manageExternalSystemAccountIdPoolEntryOp_;
    case (int32_t)OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID:
return bindExternalSystemAccountIdOp_ == other.bindExternalSystemAccountIdOp_;
    case (int32_t)OperationType::PAYMENT:
return paymentOp_ == other.paymentOp_;
    case (int32_t)OperationType::MANAGE_SALE:
return manageSaleOp_ == other.manageSaleOp_;
    case (int32_t)OperationType::CREATE_MANAGE_LIMITS_REQUEST:
return createManageLimitsRequestOp_ == other.createManageLimitsRequestOp_;
    case (int32_t)OperationType::MANAGE_CONTRACT_REQUEST:
return manageContractRequestOp_ == other.manageContractRequestOp_;
    case (int32_t)OperationType::MANAGE_CONTRACT:
return manageContractOp_ == other.manageContractOp_;
    case (int32_t)OperationType::CANCEL_SALE_REQUEST:
return cancelSaleCreationRequestOp_ == other.cancelSaleCreationRequestOp_;
    case (int32_t)OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST:
return createAtomicSwapAskRequestOp_ == other.createAtomicSwapAskRequestOp_;
    case (int32_t)OperationType::CANCEL_ATOMIC_SWAP_ASK:
return cancelAtomicSwapAskOp_ == other.cancelAtomicSwapAskOp_;
    case (int32_t)OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST:
return createAtomicSwapBidRequestOp_ == other.createAtomicSwapBidRequestOp_;
    case (int32_t)OperationType::MANAGE_ACCOUNT_ROLE:
return manageAccountRoleOp_ == other.manageAccountRoleOp_;
    case (int32_t)OperationType::MANAGE_ACCOUNT_RULE:
return manageAccountRuleOp_ == other.manageAccountRuleOp_;
    case (int32_t)OperationType::MANAGE_SIGNER:
return manageSignerOp_ == other.manageSignerOp_;
    case (int32_t)OperationType::MANAGE_SIGNER_ROLE:
return manageSignerRoleOp_ == other.manageSignerRoleOp_;
    case (int32_t)OperationType::MANAGE_SIGNER_RULE:
return manageSignerRuleOp_ == other.manageSignerRuleOp_;
    case (int32_t)OperationType::STAMP:
return stampOp_ == other.stampOp_;
    case (int32_t)OperationType::LICENSE:
return licenseOp_ == other.licenseOp_;
    case (int32_t)OperationType::MANAGE_CREATE_POLL_REQUEST:
return manageCreatePollRequestOp_ == other.manageCreatePollRequestOp_;
    case (int32_t)OperationType::MANAGE_POLL:
return managePollOp_ == other.managePollOp_;
    case (int32_t)OperationType::MANAGE_VOTE:
return manageVoteOp_ == other.manageVoteOp_;
    case (int32_t)OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE:
return manageAccountSpecificRuleOp_ == other.manageAccountSpecificRuleOp_;
    case (int32_t)OperationType::CANCEL_CHANGE_ROLE_REQUEST:
return cancelChangeRoleRequestOp_ == other.cancelChangeRoleRequestOp_;
    case (int32_t)OperationType::REMOVE_ASSET_PAIR:
return removeAssetPairOp_ == other.removeAssetPairOp_;
    case (int32_t)OperationType::INITIATE_KYC_RECOVERY:
return initiateKYCRecoveryOp_ == other.initiateKYCRecoveryOp_;
    case (int32_t)OperationType::CREATE_KYC_RECOVERY_REQUEST:
return createKYCRecoveryRequestOp_ == other.createKYCRecoveryRequestOp_;
    case (int32_t)OperationType::CREATE_MANAGE_OFFER_REQUEST:
return createManageOfferRequestOp_ == other.createManageOfferRequestOp_;
    case (int32_t)OperationType::CREATE_PAYMENT_REQUEST:
return createPaymentRequestOp_ == other.createPaymentRequestOp_;
    case (int32_t)OperationType::REMOVE_ASSET:
return removeAssetOp_ == other.removeAssetOp_;
    case (int32_t)OperationType::OPEN_SWAP:
return openSwapOp_ == other.openSwapOp_;
    case (int32_t)OperationType::CLOSE_SWAP:
return closeSwapOp_ == other.closeSwapOp_;
    case (int32_t)OperationType::CREATE_REDEMPTION_REQUEST:
return createRedemptionRequestOp_ == other.createRedemptionRequestOp_;
    case (int32_t)OperationType::CREATE_DATA:
return createDataOp_ == other.createDataOp_;
    case (int32_t)OperationType::UPDATE_DATA:
return updateDataOp_ == other.updateDataOp_;
    case (int32_t)OperationType::REMOVE_DATA:
return removeDataOp_ == other.removeDataOp_;
    case (int32_t)OperationType::CREATE_DATA_CREATION_REQUEST:
return createDataCreationRequestOp_ == other.createDataCreationRequestOp_;
    case (int32_t)OperationType::CANCEL_DATA_CREATION_REQUEST:
return cancelDataCreationRequestOp_ == other.cancelDataCreationRequestOp_;
    case (int32_t)OperationType::CREATE_DATA_UPDATE_REQUEST:
return createDataUpdateRequestOp_ == other.createDataUpdateRequestOp_;
    case (int32_t)OperationType::CREATE_DATA_REMOVE_REQUEST:
return createDataRemoveRequestOp_ == other.createDataRemoveRequestOp_;
    case (int32_t)OperationType::CANCEL_DATA_UPDATE_REQUEST:
return cancelDataUpdateRequestOp_ == other.cancelDataUpdateRequestOp_;
    case (int32_t)OperationType::CANCEL_DATA_REMOVE_REQUEST:
return cancelDataRemoveRequestOp_ == other.cancelDataRemoveRequestOp_;
    case (int32_t)OperationType::CREATE_DEFERRED_PAYMENT_CREATION_REQUEST:
return createDeferredPaymentCreationRequestOp_ == other.createDeferredPaymentCreationRequestOp_;
    case (int32_t)OperationType::CANCEL_DEFERRED_PAYMENT_CREATION_REQUEST:
return cancelDeferredPaymentCreationRequestOp_ == other.cancelDeferredPaymentCreationRequestOp_;
    case (int32_t)OperationType::CREATE_CLOSE_DEFERRED_PAYMENT_REQUEST:
return createCloseDeferredPaymentRequestOp_ == other.createCloseDeferredPaymentRequestOp_;
    case (int32_t)OperationType::CANCEL_CLOSE_DEFERRED_PAYMENT_REQUEST:
return cancelCloseDeferredPaymentRequestOp_ == other.cancelCloseDeferredPaymentRequestOp_;
    case (int32_t)OperationType::UPDATE_DATA_OWNER:
return updateDataOwnerOp_ == other.updateDataOwnerOp_;
    case (int32_t)OperationType::CREATE_DATA_OWNER_UPDATE_REQUEST:
return createDataOwnerUpdateRequestOp_ == other.createDataOwnerUpdateRequestOp_;
    case (int32_t)OperationType::CANCEL_DATA_OWNER_UPDATE_REQUEST:
return cancelDataOwnerUpdateRequestOp_ == other.cancelDataOwnerUpdateRequestOp_;
}
return false;
}
bool
Operation::_body_t::operator<(xdr_abstract const& other_abstract) const
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
    case (int32_t)OperationType::CREATE_ACCOUNT:
return createAccountOp_ < other.createAccountOp_;
    case (int32_t)OperationType::CREATE_ISSUANCE_REQUEST:
return createIssuanceRequestOp_ < other.createIssuanceRequestOp_;
    case (int32_t)OperationType::SET_FEES:
return setFeesOp_ < other.setFeesOp_;
    case (int32_t)OperationType::CREATE_WITHDRAWAL_REQUEST:
return createWithdrawalRequestOp_ < other.createWithdrawalRequestOp_;
    case (int32_t)OperationType::MANAGE_BALANCE:
return manageBalanceOp_ < other.manageBalanceOp_;
    case (int32_t)OperationType::MANAGE_ASSET:
return manageAssetOp_ < other.manageAssetOp_;
    case (int32_t)OperationType::CREATE_PREISSUANCE_REQUEST:
return createPreIssuanceRequest_ < other.createPreIssuanceRequest_;
    case (int32_t)OperationType::MANAGE_LIMITS:
return manageLimitsOp_ < other.manageLimitsOp_;
    case (int32_t)OperationType::MANAGE_ASSET_PAIR:
return manageAssetPairOp_ < other.manageAssetPairOp_;
    case (int32_t)OperationType::MANAGE_OFFER:
return manageOfferOp_ < other.manageOfferOp_;
    case (int32_t)OperationType::MANAGE_INVOICE_REQUEST:
return manageInvoiceRequestOp_ < other.manageInvoiceRequestOp_;
    case (int32_t)OperationType::REVIEW_REQUEST:
return reviewRequestOp_ < other.reviewRequestOp_;
    case (int32_t)OperationType::CREATE_SALE_REQUEST:
return createSaleCreationRequestOp_ < other.createSaleCreationRequestOp_;
    case (int32_t)OperationType::CHECK_SALE_STATE:
return checkSaleStateOp_ < other.checkSaleStateOp_;
    case (int32_t)OperationType::PAYOUT:
return payoutOp_ < other.payoutOp_;
    case (int32_t)OperationType::CREATE_AML_ALERT:
return createAMLAlertRequestOp_ < other.createAMLAlertRequestOp_;
    case (int32_t)OperationType::MANAGE_KEY_VALUE:
return manageKeyValueOp_ < other.manageKeyValueOp_;
    case (int32_t)OperationType::CREATE_CHANGE_ROLE_REQUEST:
return createChangeRoleRequestOp_ < other.createChangeRoleRequestOp_;
    case (int32_t)OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
return manageExternalSystemAccountIdPoolEntryOp_ < other.manageExternalSystemAccountIdPoolEntryOp_;
    case (int32_t)OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID:
return bindExternalSystemAccountIdOp_ < other.bindExternalSystemAccountIdOp_;
    case (int32_t)OperationType::PAYMENT:
return paymentOp_ < other.paymentOp_;
    case (int32_t)OperationType::MANAGE_SALE:
return manageSaleOp_ < other.manageSaleOp_;
    case (int32_t)OperationType::CREATE_MANAGE_LIMITS_REQUEST:
return createManageLimitsRequestOp_ < other.createManageLimitsRequestOp_;
    case (int32_t)OperationType::MANAGE_CONTRACT_REQUEST:
return manageContractRequestOp_ < other.manageContractRequestOp_;
    case (int32_t)OperationType::MANAGE_CONTRACT:
return manageContractOp_ < other.manageContractOp_;
    case (int32_t)OperationType::CANCEL_SALE_REQUEST:
return cancelSaleCreationRequestOp_ < other.cancelSaleCreationRequestOp_;
    case (int32_t)OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST:
return createAtomicSwapAskRequestOp_ < other.createAtomicSwapAskRequestOp_;
    case (int32_t)OperationType::CANCEL_ATOMIC_SWAP_ASK:
return cancelAtomicSwapAskOp_ < other.cancelAtomicSwapAskOp_;
    case (int32_t)OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST:
return createAtomicSwapBidRequestOp_ < other.createAtomicSwapBidRequestOp_;
    case (int32_t)OperationType::MANAGE_ACCOUNT_ROLE:
return manageAccountRoleOp_ < other.manageAccountRoleOp_;
    case (int32_t)OperationType::MANAGE_ACCOUNT_RULE:
return manageAccountRuleOp_ < other.manageAccountRuleOp_;
    case (int32_t)OperationType::MANAGE_SIGNER:
return manageSignerOp_ < other.manageSignerOp_;
    case (int32_t)OperationType::MANAGE_SIGNER_ROLE:
return manageSignerRoleOp_ < other.manageSignerRoleOp_;
    case (int32_t)OperationType::MANAGE_SIGNER_RULE:
return manageSignerRuleOp_ < other.manageSignerRuleOp_;
    case (int32_t)OperationType::STAMP:
return stampOp_ < other.stampOp_;
    case (int32_t)OperationType::LICENSE:
return licenseOp_ < other.licenseOp_;
    case (int32_t)OperationType::MANAGE_CREATE_POLL_REQUEST:
return manageCreatePollRequestOp_ < other.manageCreatePollRequestOp_;
    case (int32_t)OperationType::MANAGE_POLL:
return managePollOp_ < other.managePollOp_;
    case (int32_t)OperationType::MANAGE_VOTE:
return manageVoteOp_ < other.manageVoteOp_;
    case (int32_t)OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE:
return manageAccountSpecificRuleOp_ < other.manageAccountSpecificRuleOp_;
    case (int32_t)OperationType::CANCEL_CHANGE_ROLE_REQUEST:
return cancelChangeRoleRequestOp_ < other.cancelChangeRoleRequestOp_;
    case (int32_t)OperationType::REMOVE_ASSET_PAIR:
return removeAssetPairOp_ < other.removeAssetPairOp_;
    case (int32_t)OperationType::INITIATE_KYC_RECOVERY:
return initiateKYCRecoveryOp_ < other.initiateKYCRecoveryOp_;
    case (int32_t)OperationType::CREATE_KYC_RECOVERY_REQUEST:
return createKYCRecoveryRequestOp_ < other.createKYCRecoveryRequestOp_;
    case (int32_t)OperationType::CREATE_MANAGE_OFFER_REQUEST:
return createManageOfferRequestOp_ < other.createManageOfferRequestOp_;
    case (int32_t)OperationType::CREATE_PAYMENT_REQUEST:
return createPaymentRequestOp_ < other.createPaymentRequestOp_;
    case (int32_t)OperationType::REMOVE_ASSET:
return removeAssetOp_ < other.removeAssetOp_;
    case (int32_t)OperationType::OPEN_SWAP:
return openSwapOp_ < other.openSwapOp_;
    case (int32_t)OperationType::CLOSE_SWAP:
return closeSwapOp_ < other.closeSwapOp_;
    case (int32_t)OperationType::CREATE_REDEMPTION_REQUEST:
return createRedemptionRequestOp_ < other.createRedemptionRequestOp_;
    case (int32_t)OperationType::CREATE_DATA:
return createDataOp_ < other.createDataOp_;
    case (int32_t)OperationType::UPDATE_DATA:
return updateDataOp_ < other.updateDataOp_;
    case (int32_t)OperationType::REMOVE_DATA:
return removeDataOp_ < other.removeDataOp_;
    case (int32_t)OperationType::CREATE_DATA_CREATION_REQUEST:
return createDataCreationRequestOp_ < other.createDataCreationRequestOp_;
    case (int32_t)OperationType::CANCEL_DATA_CREATION_REQUEST:
return cancelDataCreationRequestOp_ < other.cancelDataCreationRequestOp_;
    case (int32_t)OperationType::CREATE_DATA_UPDATE_REQUEST:
return createDataUpdateRequestOp_ < other.createDataUpdateRequestOp_;
    case (int32_t)OperationType::CREATE_DATA_REMOVE_REQUEST:
return createDataRemoveRequestOp_ < other.createDataRemoveRequestOp_;
    case (int32_t)OperationType::CANCEL_DATA_UPDATE_REQUEST:
return cancelDataUpdateRequestOp_ < other.cancelDataUpdateRequestOp_;
    case (int32_t)OperationType::CANCEL_DATA_REMOVE_REQUEST:
return cancelDataRemoveRequestOp_ < other.cancelDataRemoveRequestOp_;
    case (int32_t)OperationType::CREATE_DEFERRED_PAYMENT_CREATION_REQUEST:
return createDeferredPaymentCreationRequestOp_ < other.createDeferredPaymentCreationRequestOp_;
    case (int32_t)OperationType::CANCEL_DEFERRED_PAYMENT_CREATION_REQUEST:
return cancelDeferredPaymentCreationRequestOp_ < other.cancelDeferredPaymentCreationRequestOp_;
    case (int32_t)OperationType::CREATE_CLOSE_DEFERRED_PAYMENT_REQUEST:
return createCloseDeferredPaymentRequestOp_ < other.createCloseDeferredPaymentRequestOp_;
    case (int32_t)OperationType::CANCEL_CLOSE_DEFERRED_PAYMENT_REQUEST:
return cancelCloseDeferredPaymentRequestOp_ < other.cancelCloseDeferredPaymentRequestOp_;
    case (int32_t)OperationType::UPDATE_DATA_OWNER:
return updateDataOwnerOp_ < other.updateDataOwnerOp_;
    case (int32_t)OperationType::CREATE_DATA_OWNER_UPDATE_REQUEST:
return createDataOwnerUpdateRequestOp_ < other.createDataOwnerUpdateRequestOp_;
    case (int32_t)OperationType::CANCEL_DATA_OWNER_UPDATE_REQUEST:
return cancelDataOwnerUpdateRequestOp_ < other.cancelDataOwnerUpdateRequestOp_;
}
return false;
}
bool
Operation::from_bytes(xdr::unmarshaler& u) 
{
bool oksourceAccount = u.from_bytes(sourceAccount);
if (!oksourceAccount)
{
return false;
}
bool okbody = u.from_bytes(body);
if (!okbody)
{
return false;
}
return true;
}
bool
Operation::to_bytes(xdr::marshaler& m) const 
{
bool oksourceAccount = m.to_bytes(sourceAccount);
if (!oksourceAccount)
{
return false;
}
bool okbody = m.to_bytes(body);
if (!okbody)
{
return false;
}
return true;
}
void
Operation::count_size(xdr::measurer& m) const 
{
m.count_size(sourceAccount);
m.count_size(body);
}
bool
Operation::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<Operation const&>(other_abstract);return true
&& (sourceAccount== other.sourceAccount)
&& (body== other.body)
;}
bool
Operation::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<Operation const&>(other_abstract);
if (sourceAccount < other.sourceAccount) return true;
if (other.sourceAccount < sourceAccount) return false;
if (body < other.body) return true;
if (other.body < body) return false;
return false;
}bool
Memo::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (type_)
{
  case (int32_t)MemoType::MEMO_NONE:
  
  return true;
  case (int32_t)MemoType::MEMO_TEXT:
return u.from_bytes(text_);
  case (int32_t)MemoType::MEMO_ID:
return u.from_bytes(id_);
  case (int32_t)MemoType::MEMO_HASH:
return u.from_bytes(hash_);
  case (int32_t)MemoType::MEMO_RETURN:
return u.from_bytes(retHash_);
}
return false;
}
bool
Memo::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(type_);
if (!ok)
{
return false;
}
switch (type_)
{

  case (int32_t)MemoType::MEMO_NONE:
    return true;
  case (int32_t)MemoType::MEMO_TEXT:
return m.to_bytes(text_);
  case (int32_t)MemoType::MEMO_ID:
return m.to_bytes(id_);
  case (int32_t)MemoType::MEMO_HASH:
return m.to_bytes(hash_);
  case (int32_t)MemoType::MEMO_RETURN:
return m.to_bytes(retHash_);
}
return false;
}
void
Memo::count_size(xdr::measurer& m) const
{
m.count_size(type_);
switch (type_)
{

  case (int32_t)MemoType::MEMO_NONE:
  
  return;
  case (int32_t)MemoType::MEMO_TEXT:
return m.count_size(text_);
  case (int32_t)MemoType::MEMO_ID:
return m.count_size(id_);
  case (int32_t)MemoType::MEMO_HASH:
return m.count_size(hash_);
  case (int32_t)MemoType::MEMO_RETURN:
return m.count_size(retHash_);
}
}
bool
Memo::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<Memo const&>(other_abstract);
if (other.type_ != type_) return false;
switch (type_)
{
  case (int32_t)MemoType::MEMO_NONE:
  
  return true;
  case (int32_t)MemoType::MEMO_TEXT:
return text_ == other.text_;
  case (int32_t)MemoType::MEMO_ID:
return id_ == other.id_;
  case (int32_t)MemoType::MEMO_HASH:
return hash_ == other.hash_;
  case (int32_t)MemoType::MEMO_RETURN:
return retHash_ == other.retHash_;
}
return false;
}
bool
Memo::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<Memo const&>(other_abstract);
if (type_ < other.type_) return true;
if (other.type_ < type_) return false;
switch (type_)
{
  case (int32_t)MemoType::MEMO_NONE:
    return false;
  case (int32_t)MemoType::MEMO_TEXT:
return text_ < other.text_;
  case (int32_t)MemoType::MEMO_ID:
return id_ < other.id_;
  case (int32_t)MemoType::MEMO_HASH:
return hash_ < other.hash_;
  case (int32_t)MemoType::MEMO_RETURN:
return retHash_ < other.retHash_;
}
return false;
}
bool
TimeBounds::from_bytes(xdr::unmarshaler& u) 
{
bool okminTime = u.from_bytes(minTime);
if (!okminTime)
{
return false;
}
bool okmaxTime = u.from_bytes(maxTime);
if (!okmaxTime)
{
return false;
}
return true;
}
bool
TimeBounds::to_bytes(xdr::marshaler& m) const 
{
bool okminTime = m.to_bytes(minTime);
if (!okminTime)
{
return false;
}
bool okmaxTime = m.to_bytes(maxTime);
if (!okmaxTime)
{
return false;
}
return true;
}
void
TimeBounds::count_size(xdr::measurer& m) const 
{
m.count_size(minTime);
m.count_size(maxTime);
}
bool
TimeBounds::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<TimeBounds const&>(other_abstract);return true
&& (minTime== other.minTime)
&& (maxTime== other.maxTime)
;}
bool
TimeBounds::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<TimeBounds const&>(other_abstract);
if (minTime < other.minTime) return true;
if (other.minTime < minTime) return false;
if (maxTime < other.maxTime) return true;
if (other.maxTime < maxTime) return false;
return false;
}bool
Transaction::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
Transaction::_ext_t::to_bytes(xdr::marshaler& m) const
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
Transaction::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
Transaction::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
Transaction::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
Transaction::from_bytes(xdr::unmarshaler& u) 
{
bool oksourceAccount = u.from_bytes(sourceAccount);
if (!oksourceAccount)
{
return false;
}
bool oksalt = u.from_bytes(salt);
if (!oksalt)
{
return false;
}
bool oktimeBounds = u.from_bytes(timeBounds);
if (!oktimeBounds)
{
return false;
}
bool okmemo = u.from_bytes(memo);
if (!okmemo)
{
return false;
}
bool okoperations = u.from_bytes(operations);
if (!okoperations)
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
Transaction::to_bytes(xdr::marshaler& m) const 
{
bool oksourceAccount = m.to_bytes(sourceAccount);
if (!oksourceAccount)
{
return false;
}
bool oksalt = m.to_bytes(salt);
if (!oksalt)
{
return false;
}
bool oktimeBounds = m.to_bytes(timeBounds);
if (!oktimeBounds)
{
return false;
}
bool okmemo = m.to_bytes(memo);
if (!okmemo)
{
return false;
}
bool okoperations = m.to_bytes(operations);
if (!okoperations)
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
Transaction::count_size(xdr::measurer& m) const 
{
m.count_size(sourceAccount);
m.count_size(salt);
m.count_size(timeBounds);
m.count_size(memo);
m.count_size(operations);
m.count_size(ext);
}
bool
Transaction::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<Transaction const&>(other_abstract);return true
&& (sourceAccount== other.sourceAccount)
&& (salt== other.salt)
&& (timeBounds== other.timeBounds)
&& (memo== other.memo)
&& (operations== other.operations)
&& (ext== other.ext)
;}
bool
Transaction::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<Transaction const&>(other_abstract);
if (sourceAccount < other.sourceAccount) return true;
if (other.sourceAccount < sourceAccount) return false;
if (salt < other.salt) return true;
if (other.salt < salt) return false;
if (timeBounds < other.timeBounds) return true;
if (other.timeBounds < timeBounds) return false;
if (memo < other.memo) return true;
if (other.memo < memo) return false;
if (operations < other.operations) return true;
if (other.operations < operations) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
TransactionEnvelope::from_bytes(xdr::unmarshaler& u) 
{
bool oktx = u.from_bytes(tx);
if (!oktx)
{
return false;
}
bool oksignatures = u.from_bytes(signatures);
if (!oksignatures)
{
return false;
}
return true;
}
bool
TransactionEnvelope::to_bytes(xdr::marshaler& m) const 
{
bool oktx = m.to_bytes(tx);
if (!oktx)
{
return false;
}
bool oksignatures = m.to_bytes(signatures);
if (!oksignatures)
{
return false;
}
return true;
}
void
TransactionEnvelope::count_size(xdr::measurer& m) const 
{
m.count_size(tx);
m.count_size(signatures);
}
bool
TransactionEnvelope::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<TransactionEnvelope const&>(other_abstract);return true
&& (tx== other.tx)
&& (signatures== other.signatures)
;}
bool
TransactionEnvelope::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<TransactionEnvelope const&>(other_abstract);
if (tx < other.tx) return true;
if (other.tx < tx) return false;
if (signatures < other.signatures) return true;
if (other.signatures < signatures) return false;
return false;
}bool
AccountRuleRequirement::from_bytes(xdr::unmarshaler& u) 
{
bool okresource = u.from_bytes(resource);
if (!okresource)
{
return false;
}
bool okaction = u.from_bytes(action);
if (!okaction)
{
return false;
}
bool okaccount = u.from_bytes(account);
if (!okaccount)
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
AccountRuleRequirement::to_bytes(xdr::marshaler& m) const 
{
bool okresource = m.to_bytes(resource);
if (!okresource)
{
return false;
}
bool okaction = m.to_bytes(action);
if (!okaction)
{
return false;
}
bool okaccount = m.to_bytes(account);
if (!okaccount)
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
AccountRuleRequirement::count_size(xdr::measurer& m) const 
{
m.count_size(resource);
m.count_size(action);
m.count_size(account);
m.count_size(ext);
}
bool
AccountRuleRequirement::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<AccountRuleRequirement const&>(other_abstract);return true
&& (resource== other.resource)
&& (action== other.action)
&& (account== other.account)
&& (ext== other.ext)
;}
bool
AccountRuleRequirement::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<AccountRuleRequirement const&>(other_abstract);
if (resource < other.resource) return true;
if (other.resource < resource) return false;
if (action < other.action) return true;
if (other.action < action) return false;
if (account < other.account) return true;
if (other.account < account) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
OperationResult::_tr_t::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (type_)
{
    case (int32_t)OperationType::CREATE_ACCOUNT:
return u.from_bytes(createAccountResult_);
    case (int32_t)OperationType::CREATE_ISSUANCE_REQUEST:
return u.from_bytes(createIssuanceRequestResult_);
    case (int32_t)OperationType::SET_FEES:
return u.from_bytes(setFeesResult_);
    case (int32_t)OperationType::CREATE_WITHDRAWAL_REQUEST:
return u.from_bytes(createWithdrawalRequestResult_);
    case (int32_t)OperationType::MANAGE_BALANCE:
return u.from_bytes(manageBalanceResult_);
    case (int32_t)OperationType::MANAGE_ASSET:
return u.from_bytes(manageAssetResult_);
    case (int32_t)OperationType::CREATE_PREISSUANCE_REQUEST:
return u.from_bytes(createPreIssuanceRequestResult_);
    case (int32_t)OperationType::MANAGE_LIMITS:
return u.from_bytes(manageLimitsResult_);
    case (int32_t)OperationType::MANAGE_ASSET_PAIR:
return u.from_bytes(manageAssetPairResult_);
    case (int32_t)OperationType::MANAGE_OFFER:
return u.from_bytes(manageOfferResult_);
    case (int32_t)OperationType::MANAGE_INVOICE_REQUEST:
return u.from_bytes(manageInvoiceRequestResult_);
    case (int32_t)OperationType::REVIEW_REQUEST:
return u.from_bytes(reviewRequestResult_);
    case (int32_t)OperationType::CREATE_SALE_REQUEST:
return u.from_bytes(createSaleCreationRequestResult_);
    case (int32_t)OperationType::CHECK_SALE_STATE:
return u.from_bytes(checkSaleStateResult_);
    case (int32_t)OperationType::PAYOUT:
return u.from_bytes(payoutResult_);
    case (int32_t)OperationType::CREATE_AML_ALERT:
return u.from_bytes(createAMLAlertRequestResult_);
    case (int32_t)OperationType::MANAGE_KEY_VALUE:
return u.from_bytes(manageKeyValueResult_);
    case (int32_t)OperationType::CREATE_CHANGE_ROLE_REQUEST:
return u.from_bytes(createChangeRoleRequestResult_);
    case (int32_t)OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
return u.from_bytes(manageExternalSystemAccountIdPoolEntryResult_);
    case (int32_t)OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID:
return u.from_bytes(bindExternalSystemAccountIdResult_);
    case (int32_t)OperationType::PAYMENT:
return u.from_bytes(paymentResult_);
    case (int32_t)OperationType::MANAGE_SALE:
return u.from_bytes(manageSaleResult_);
    case (int32_t)OperationType::CREATE_MANAGE_LIMITS_REQUEST:
return u.from_bytes(createManageLimitsRequestResult_);
    case (int32_t)OperationType::MANAGE_CONTRACT_REQUEST:
return u.from_bytes(manageContractRequestResult_);
    case (int32_t)OperationType::MANAGE_CONTRACT:
return u.from_bytes(manageContractResult_);
    case (int32_t)OperationType::CANCEL_SALE_REQUEST:
return u.from_bytes(cancelSaleCreationRequestResult_);
    case (int32_t)OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST:
return u.from_bytes(createAtomicSwapAskRequestResult_);
    case (int32_t)OperationType::CANCEL_ATOMIC_SWAP_ASK:
return u.from_bytes(cancelAtomicSwapAskResult_);
    case (int32_t)OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST:
return u.from_bytes(createAtomicSwapBidRequestResult_);
    case (int32_t)OperationType::MANAGE_ACCOUNT_ROLE:
return u.from_bytes(manageAccountRoleResult_);
    case (int32_t)OperationType::MANAGE_ACCOUNT_RULE:
return u.from_bytes(manageAccountRuleResult_);
    case (int32_t)OperationType::MANAGE_SIGNER:
return u.from_bytes(manageSignerResult_);
    case (int32_t)OperationType::MANAGE_SIGNER_ROLE:
return u.from_bytes(manageSignerRoleResult_);
    case (int32_t)OperationType::MANAGE_SIGNER_RULE:
return u.from_bytes(manageSignerRuleResult_);
    case (int32_t)OperationType::STAMP:
return u.from_bytes(stampResult_);
    case (int32_t)OperationType::LICENSE:
return u.from_bytes(licenseResult_);
    case (int32_t)OperationType::MANAGE_POLL:
return u.from_bytes(managePollResult_);
    case (int32_t)OperationType::MANAGE_CREATE_POLL_REQUEST:
return u.from_bytes(manageCreatePollRequestResult_);
    case (int32_t)OperationType::MANAGE_VOTE:
return u.from_bytes(manageVoteResult_);
    case (int32_t)OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE:
return u.from_bytes(manageAccountSpecificRuleResult_);
    case (int32_t)OperationType::CANCEL_CHANGE_ROLE_REQUEST:
return u.from_bytes(cancelChangeRoleRequestResult_);
    case (int32_t)OperationType::REMOVE_ASSET_PAIR:
return u.from_bytes(removeAssetPairResult_);
    case (int32_t)OperationType::CREATE_KYC_RECOVERY_REQUEST:
return u.from_bytes(createKYCRecoveryRequestResult_);
    case (int32_t)OperationType::INITIATE_KYC_RECOVERY:
return u.from_bytes(initiateKYCRecoveryResult_);
    case (int32_t)OperationType::CREATE_MANAGE_OFFER_REQUEST:
return u.from_bytes(createManageOfferRequestResult_);
    case (int32_t)OperationType::CREATE_PAYMENT_REQUEST:
return u.from_bytes(createPaymentRequestResult_);
    case (int32_t)OperationType::REMOVE_ASSET:
return u.from_bytes(removeAssetResult_);
    case (int32_t)OperationType::OPEN_SWAP:
return u.from_bytes(openSwapResult_);
    case (int32_t)OperationType::CLOSE_SWAP:
return u.from_bytes(closeSwapResult_);
    case (int32_t)OperationType::CREATE_REDEMPTION_REQUEST:
return u.from_bytes(createRedemptionRequestResult_);
    case (int32_t)OperationType::CREATE_DATA:
return u.from_bytes(createDataResult_);
    case (int32_t)OperationType::UPDATE_DATA:
return u.from_bytes(updateDataResult_);
    case (int32_t)OperationType::REMOVE_DATA:
return u.from_bytes(removeDataResult_);
    case (int32_t)OperationType::CREATE_DATA_CREATION_REQUEST:
return u.from_bytes(createDataCreationRequestResult_);
    case (int32_t)OperationType::CANCEL_DATA_CREATION_REQUEST:
return u.from_bytes(cancelDataCreationRequestResult_);
    case (int32_t)OperationType::CREATE_DATA_UPDATE_REQUEST:
return u.from_bytes(createDataUpdateRequestResult_);
    case (int32_t)OperationType::CREATE_DATA_REMOVE_REQUEST:
return u.from_bytes(createDataRemoveRequestResult_);
    case (int32_t)OperationType::CANCEL_DATA_UPDATE_REQUEST:
return u.from_bytes(cancelDataUpdateRequestResult_);
    case (int32_t)OperationType::CANCEL_DATA_REMOVE_REQUEST:
return u.from_bytes(cancelDataRemoveRequestResult_);
    case (int32_t)OperationType::CREATE_DEFERRED_PAYMENT_CREATION_REQUEST:
return u.from_bytes(createDeferredPaymentCreationRequestResult_);
    case (int32_t)OperationType::CANCEL_DEFERRED_PAYMENT_CREATION_REQUEST:
return u.from_bytes(cancelDeferredPaymentCreationRequestResult_);
    case (int32_t)OperationType::CREATE_CLOSE_DEFERRED_PAYMENT_REQUEST:
return u.from_bytes(createCloseDeferredPaymentRequestResult_);
    case (int32_t)OperationType::CANCEL_CLOSE_DEFERRED_PAYMENT_REQUEST:
return u.from_bytes(cancelCloseDeferredPaymentRequestResult_);
    case (int32_t)OperationType::UPDATE_DATA_OWNER:
return u.from_bytes(updateDataOwnerResult_);
    case (int32_t)OperationType::CREATE_DATA_OWNER_UPDATE_REQUEST:
return u.from_bytes(createDataOwnerUpdateRequestResult_);
    case (int32_t)OperationType::CANCEL_DATA_OWNER_UPDATE_REQUEST:
return u.from_bytes(cancelDataOwnerUpdateRequestResult_);
}
return false;
}
bool
OperationResult::_tr_t::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(type_);
if (!ok)
{
return false;
}
switch (type_)
{

    case (int32_t)OperationType::CREATE_ACCOUNT:
return m.to_bytes(createAccountResult_);
    case (int32_t)OperationType::CREATE_ISSUANCE_REQUEST:
return m.to_bytes(createIssuanceRequestResult_);
    case (int32_t)OperationType::SET_FEES:
return m.to_bytes(setFeesResult_);
    case (int32_t)OperationType::CREATE_WITHDRAWAL_REQUEST:
return m.to_bytes(createWithdrawalRequestResult_);
    case (int32_t)OperationType::MANAGE_BALANCE:
return m.to_bytes(manageBalanceResult_);
    case (int32_t)OperationType::MANAGE_ASSET:
return m.to_bytes(manageAssetResult_);
    case (int32_t)OperationType::CREATE_PREISSUANCE_REQUEST:
return m.to_bytes(createPreIssuanceRequestResult_);
    case (int32_t)OperationType::MANAGE_LIMITS:
return m.to_bytes(manageLimitsResult_);
    case (int32_t)OperationType::MANAGE_ASSET_PAIR:
return m.to_bytes(manageAssetPairResult_);
    case (int32_t)OperationType::MANAGE_OFFER:
return m.to_bytes(manageOfferResult_);
    case (int32_t)OperationType::MANAGE_INVOICE_REQUEST:
return m.to_bytes(manageInvoiceRequestResult_);
    case (int32_t)OperationType::REVIEW_REQUEST:
return m.to_bytes(reviewRequestResult_);
    case (int32_t)OperationType::CREATE_SALE_REQUEST:
return m.to_bytes(createSaleCreationRequestResult_);
    case (int32_t)OperationType::CHECK_SALE_STATE:
return m.to_bytes(checkSaleStateResult_);
    case (int32_t)OperationType::PAYOUT:
return m.to_bytes(payoutResult_);
    case (int32_t)OperationType::CREATE_AML_ALERT:
return m.to_bytes(createAMLAlertRequestResult_);
    case (int32_t)OperationType::MANAGE_KEY_VALUE:
return m.to_bytes(manageKeyValueResult_);
    case (int32_t)OperationType::CREATE_CHANGE_ROLE_REQUEST:
return m.to_bytes(createChangeRoleRequestResult_);
    case (int32_t)OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
return m.to_bytes(manageExternalSystemAccountIdPoolEntryResult_);
    case (int32_t)OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID:
return m.to_bytes(bindExternalSystemAccountIdResult_);
    case (int32_t)OperationType::PAYMENT:
return m.to_bytes(paymentResult_);
    case (int32_t)OperationType::MANAGE_SALE:
return m.to_bytes(manageSaleResult_);
    case (int32_t)OperationType::CREATE_MANAGE_LIMITS_REQUEST:
return m.to_bytes(createManageLimitsRequestResult_);
    case (int32_t)OperationType::MANAGE_CONTRACT_REQUEST:
return m.to_bytes(manageContractRequestResult_);
    case (int32_t)OperationType::MANAGE_CONTRACT:
return m.to_bytes(manageContractResult_);
    case (int32_t)OperationType::CANCEL_SALE_REQUEST:
return m.to_bytes(cancelSaleCreationRequestResult_);
    case (int32_t)OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST:
return m.to_bytes(createAtomicSwapAskRequestResult_);
    case (int32_t)OperationType::CANCEL_ATOMIC_SWAP_ASK:
return m.to_bytes(cancelAtomicSwapAskResult_);
    case (int32_t)OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST:
return m.to_bytes(createAtomicSwapBidRequestResult_);
    case (int32_t)OperationType::MANAGE_ACCOUNT_ROLE:
return m.to_bytes(manageAccountRoleResult_);
    case (int32_t)OperationType::MANAGE_ACCOUNT_RULE:
return m.to_bytes(manageAccountRuleResult_);
    case (int32_t)OperationType::MANAGE_SIGNER:
return m.to_bytes(manageSignerResult_);
    case (int32_t)OperationType::MANAGE_SIGNER_ROLE:
return m.to_bytes(manageSignerRoleResult_);
    case (int32_t)OperationType::MANAGE_SIGNER_RULE:
return m.to_bytes(manageSignerRuleResult_);
    case (int32_t)OperationType::STAMP:
return m.to_bytes(stampResult_);
    case (int32_t)OperationType::LICENSE:
return m.to_bytes(licenseResult_);
    case (int32_t)OperationType::MANAGE_POLL:
return m.to_bytes(managePollResult_);
    case (int32_t)OperationType::MANAGE_CREATE_POLL_REQUEST:
return m.to_bytes(manageCreatePollRequestResult_);
    case (int32_t)OperationType::MANAGE_VOTE:
return m.to_bytes(manageVoteResult_);
    case (int32_t)OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE:
return m.to_bytes(manageAccountSpecificRuleResult_);
    case (int32_t)OperationType::CANCEL_CHANGE_ROLE_REQUEST:
return m.to_bytes(cancelChangeRoleRequestResult_);
    case (int32_t)OperationType::REMOVE_ASSET_PAIR:
return m.to_bytes(removeAssetPairResult_);
    case (int32_t)OperationType::CREATE_KYC_RECOVERY_REQUEST:
return m.to_bytes(createKYCRecoveryRequestResult_);
    case (int32_t)OperationType::INITIATE_KYC_RECOVERY:
return m.to_bytes(initiateKYCRecoveryResult_);
    case (int32_t)OperationType::CREATE_MANAGE_OFFER_REQUEST:
return m.to_bytes(createManageOfferRequestResult_);
    case (int32_t)OperationType::CREATE_PAYMENT_REQUEST:
return m.to_bytes(createPaymentRequestResult_);
    case (int32_t)OperationType::REMOVE_ASSET:
return m.to_bytes(removeAssetResult_);
    case (int32_t)OperationType::OPEN_SWAP:
return m.to_bytes(openSwapResult_);
    case (int32_t)OperationType::CLOSE_SWAP:
return m.to_bytes(closeSwapResult_);
    case (int32_t)OperationType::CREATE_REDEMPTION_REQUEST:
return m.to_bytes(createRedemptionRequestResult_);
    case (int32_t)OperationType::CREATE_DATA:
return m.to_bytes(createDataResult_);
    case (int32_t)OperationType::UPDATE_DATA:
return m.to_bytes(updateDataResult_);
    case (int32_t)OperationType::REMOVE_DATA:
return m.to_bytes(removeDataResult_);
    case (int32_t)OperationType::CREATE_DATA_CREATION_REQUEST:
return m.to_bytes(createDataCreationRequestResult_);
    case (int32_t)OperationType::CANCEL_DATA_CREATION_REQUEST:
return m.to_bytes(cancelDataCreationRequestResult_);
    case (int32_t)OperationType::CREATE_DATA_UPDATE_REQUEST:
return m.to_bytes(createDataUpdateRequestResult_);
    case (int32_t)OperationType::CREATE_DATA_REMOVE_REQUEST:
return m.to_bytes(createDataRemoveRequestResult_);
    case (int32_t)OperationType::CANCEL_DATA_UPDATE_REQUEST:
return m.to_bytes(cancelDataUpdateRequestResult_);
    case (int32_t)OperationType::CANCEL_DATA_REMOVE_REQUEST:
return m.to_bytes(cancelDataRemoveRequestResult_);
    case (int32_t)OperationType::CREATE_DEFERRED_PAYMENT_CREATION_REQUEST:
return m.to_bytes(createDeferredPaymentCreationRequestResult_);
    case (int32_t)OperationType::CANCEL_DEFERRED_PAYMENT_CREATION_REQUEST:
return m.to_bytes(cancelDeferredPaymentCreationRequestResult_);
    case (int32_t)OperationType::CREATE_CLOSE_DEFERRED_PAYMENT_REQUEST:
return m.to_bytes(createCloseDeferredPaymentRequestResult_);
    case (int32_t)OperationType::CANCEL_CLOSE_DEFERRED_PAYMENT_REQUEST:
return m.to_bytes(cancelCloseDeferredPaymentRequestResult_);
    case (int32_t)OperationType::UPDATE_DATA_OWNER:
return m.to_bytes(updateDataOwnerResult_);
    case (int32_t)OperationType::CREATE_DATA_OWNER_UPDATE_REQUEST:
return m.to_bytes(createDataOwnerUpdateRequestResult_);
    case (int32_t)OperationType::CANCEL_DATA_OWNER_UPDATE_REQUEST:
return m.to_bytes(cancelDataOwnerUpdateRequestResult_);
}
return false;
}
void
OperationResult::_tr_t::count_size(xdr::measurer& m) const
{
m.count_size(type_);
switch (type_)
{

    case (int32_t)OperationType::CREATE_ACCOUNT:
return m.count_size(createAccountResult_);
    case (int32_t)OperationType::CREATE_ISSUANCE_REQUEST:
return m.count_size(createIssuanceRequestResult_);
    case (int32_t)OperationType::SET_FEES:
return m.count_size(setFeesResult_);
    case (int32_t)OperationType::CREATE_WITHDRAWAL_REQUEST:
return m.count_size(createWithdrawalRequestResult_);
    case (int32_t)OperationType::MANAGE_BALANCE:
return m.count_size(manageBalanceResult_);
    case (int32_t)OperationType::MANAGE_ASSET:
return m.count_size(manageAssetResult_);
    case (int32_t)OperationType::CREATE_PREISSUANCE_REQUEST:
return m.count_size(createPreIssuanceRequestResult_);
    case (int32_t)OperationType::MANAGE_LIMITS:
return m.count_size(manageLimitsResult_);
    case (int32_t)OperationType::MANAGE_ASSET_PAIR:
return m.count_size(manageAssetPairResult_);
    case (int32_t)OperationType::MANAGE_OFFER:
return m.count_size(manageOfferResult_);
    case (int32_t)OperationType::MANAGE_INVOICE_REQUEST:
return m.count_size(manageInvoiceRequestResult_);
    case (int32_t)OperationType::REVIEW_REQUEST:
return m.count_size(reviewRequestResult_);
    case (int32_t)OperationType::CREATE_SALE_REQUEST:
return m.count_size(createSaleCreationRequestResult_);
    case (int32_t)OperationType::CHECK_SALE_STATE:
return m.count_size(checkSaleStateResult_);
    case (int32_t)OperationType::PAYOUT:
return m.count_size(payoutResult_);
    case (int32_t)OperationType::CREATE_AML_ALERT:
return m.count_size(createAMLAlertRequestResult_);
    case (int32_t)OperationType::MANAGE_KEY_VALUE:
return m.count_size(manageKeyValueResult_);
    case (int32_t)OperationType::CREATE_CHANGE_ROLE_REQUEST:
return m.count_size(createChangeRoleRequestResult_);
    case (int32_t)OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
return m.count_size(manageExternalSystemAccountIdPoolEntryResult_);
    case (int32_t)OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID:
return m.count_size(bindExternalSystemAccountIdResult_);
    case (int32_t)OperationType::PAYMENT:
return m.count_size(paymentResult_);
    case (int32_t)OperationType::MANAGE_SALE:
return m.count_size(manageSaleResult_);
    case (int32_t)OperationType::CREATE_MANAGE_LIMITS_REQUEST:
return m.count_size(createManageLimitsRequestResult_);
    case (int32_t)OperationType::MANAGE_CONTRACT_REQUEST:
return m.count_size(manageContractRequestResult_);
    case (int32_t)OperationType::MANAGE_CONTRACT:
return m.count_size(manageContractResult_);
    case (int32_t)OperationType::CANCEL_SALE_REQUEST:
return m.count_size(cancelSaleCreationRequestResult_);
    case (int32_t)OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST:
return m.count_size(createAtomicSwapAskRequestResult_);
    case (int32_t)OperationType::CANCEL_ATOMIC_SWAP_ASK:
return m.count_size(cancelAtomicSwapAskResult_);
    case (int32_t)OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST:
return m.count_size(createAtomicSwapBidRequestResult_);
    case (int32_t)OperationType::MANAGE_ACCOUNT_ROLE:
return m.count_size(manageAccountRoleResult_);
    case (int32_t)OperationType::MANAGE_ACCOUNT_RULE:
return m.count_size(manageAccountRuleResult_);
    case (int32_t)OperationType::MANAGE_SIGNER:
return m.count_size(manageSignerResult_);
    case (int32_t)OperationType::MANAGE_SIGNER_ROLE:
return m.count_size(manageSignerRoleResult_);
    case (int32_t)OperationType::MANAGE_SIGNER_RULE:
return m.count_size(manageSignerRuleResult_);
    case (int32_t)OperationType::STAMP:
return m.count_size(stampResult_);
    case (int32_t)OperationType::LICENSE:
return m.count_size(licenseResult_);
    case (int32_t)OperationType::MANAGE_POLL:
return m.count_size(managePollResult_);
    case (int32_t)OperationType::MANAGE_CREATE_POLL_REQUEST:
return m.count_size(manageCreatePollRequestResult_);
    case (int32_t)OperationType::MANAGE_VOTE:
return m.count_size(manageVoteResult_);
    case (int32_t)OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE:
return m.count_size(manageAccountSpecificRuleResult_);
    case (int32_t)OperationType::CANCEL_CHANGE_ROLE_REQUEST:
return m.count_size(cancelChangeRoleRequestResult_);
    case (int32_t)OperationType::REMOVE_ASSET_PAIR:
return m.count_size(removeAssetPairResult_);
    case (int32_t)OperationType::CREATE_KYC_RECOVERY_REQUEST:
return m.count_size(createKYCRecoveryRequestResult_);
    case (int32_t)OperationType::INITIATE_KYC_RECOVERY:
return m.count_size(initiateKYCRecoveryResult_);
    case (int32_t)OperationType::CREATE_MANAGE_OFFER_REQUEST:
return m.count_size(createManageOfferRequestResult_);
    case (int32_t)OperationType::CREATE_PAYMENT_REQUEST:
return m.count_size(createPaymentRequestResult_);
    case (int32_t)OperationType::REMOVE_ASSET:
return m.count_size(removeAssetResult_);
    case (int32_t)OperationType::OPEN_SWAP:
return m.count_size(openSwapResult_);
    case (int32_t)OperationType::CLOSE_SWAP:
return m.count_size(closeSwapResult_);
    case (int32_t)OperationType::CREATE_REDEMPTION_REQUEST:
return m.count_size(createRedemptionRequestResult_);
    case (int32_t)OperationType::CREATE_DATA:
return m.count_size(createDataResult_);
    case (int32_t)OperationType::UPDATE_DATA:
return m.count_size(updateDataResult_);
    case (int32_t)OperationType::REMOVE_DATA:
return m.count_size(removeDataResult_);
    case (int32_t)OperationType::CREATE_DATA_CREATION_REQUEST:
return m.count_size(createDataCreationRequestResult_);
    case (int32_t)OperationType::CANCEL_DATA_CREATION_REQUEST:
return m.count_size(cancelDataCreationRequestResult_);
    case (int32_t)OperationType::CREATE_DATA_UPDATE_REQUEST:
return m.count_size(createDataUpdateRequestResult_);
    case (int32_t)OperationType::CREATE_DATA_REMOVE_REQUEST:
return m.count_size(createDataRemoveRequestResult_);
    case (int32_t)OperationType::CANCEL_DATA_UPDATE_REQUEST:
return m.count_size(cancelDataUpdateRequestResult_);
    case (int32_t)OperationType::CANCEL_DATA_REMOVE_REQUEST:
return m.count_size(cancelDataRemoveRequestResult_);
    case (int32_t)OperationType::CREATE_DEFERRED_PAYMENT_CREATION_REQUEST:
return m.count_size(createDeferredPaymentCreationRequestResult_);
    case (int32_t)OperationType::CANCEL_DEFERRED_PAYMENT_CREATION_REQUEST:
return m.count_size(cancelDeferredPaymentCreationRequestResult_);
    case (int32_t)OperationType::CREATE_CLOSE_DEFERRED_PAYMENT_REQUEST:
return m.count_size(createCloseDeferredPaymentRequestResult_);
    case (int32_t)OperationType::CANCEL_CLOSE_DEFERRED_PAYMENT_REQUEST:
return m.count_size(cancelCloseDeferredPaymentRequestResult_);
    case (int32_t)OperationType::UPDATE_DATA_OWNER:
return m.count_size(updateDataOwnerResult_);
    case (int32_t)OperationType::CREATE_DATA_OWNER_UPDATE_REQUEST:
return m.count_size(createDataOwnerUpdateRequestResult_);
    case (int32_t)OperationType::CANCEL_DATA_OWNER_UPDATE_REQUEST:
return m.count_size(cancelDataOwnerUpdateRequestResult_);
}
}
bool
OperationResult::_tr_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_tr_t const&>(other_abstract);
if (other.type_ != type_) return false;
switch (type_)
{
    case (int32_t)OperationType::CREATE_ACCOUNT:
return createAccountResult_ == other.createAccountResult_;
    case (int32_t)OperationType::CREATE_ISSUANCE_REQUEST:
return createIssuanceRequestResult_ == other.createIssuanceRequestResult_;
    case (int32_t)OperationType::SET_FEES:
return setFeesResult_ == other.setFeesResult_;
    case (int32_t)OperationType::CREATE_WITHDRAWAL_REQUEST:
return createWithdrawalRequestResult_ == other.createWithdrawalRequestResult_;
    case (int32_t)OperationType::MANAGE_BALANCE:
return manageBalanceResult_ == other.manageBalanceResult_;
    case (int32_t)OperationType::MANAGE_ASSET:
return manageAssetResult_ == other.manageAssetResult_;
    case (int32_t)OperationType::CREATE_PREISSUANCE_REQUEST:
return createPreIssuanceRequestResult_ == other.createPreIssuanceRequestResult_;
    case (int32_t)OperationType::MANAGE_LIMITS:
return manageLimitsResult_ == other.manageLimitsResult_;
    case (int32_t)OperationType::MANAGE_ASSET_PAIR:
return manageAssetPairResult_ == other.manageAssetPairResult_;
    case (int32_t)OperationType::MANAGE_OFFER:
return manageOfferResult_ == other.manageOfferResult_;
    case (int32_t)OperationType::MANAGE_INVOICE_REQUEST:
return manageInvoiceRequestResult_ == other.manageInvoiceRequestResult_;
    case (int32_t)OperationType::REVIEW_REQUEST:
return reviewRequestResult_ == other.reviewRequestResult_;
    case (int32_t)OperationType::CREATE_SALE_REQUEST:
return createSaleCreationRequestResult_ == other.createSaleCreationRequestResult_;
    case (int32_t)OperationType::CHECK_SALE_STATE:
return checkSaleStateResult_ == other.checkSaleStateResult_;
    case (int32_t)OperationType::PAYOUT:
return payoutResult_ == other.payoutResult_;
    case (int32_t)OperationType::CREATE_AML_ALERT:
return createAMLAlertRequestResult_ == other.createAMLAlertRequestResult_;
    case (int32_t)OperationType::MANAGE_KEY_VALUE:
return manageKeyValueResult_ == other.manageKeyValueResult_;
    case (int32_t)OperationType::CREATE_CHANGE_ROLE_REQUEST:
return createChangeRoleRequestResult_ == other.createChangeRoleRequestResult_;
    case (int32_t)OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
return manageExternalSystemAccountIdPoolEntryResult_ == other.manageExternalSystemAccountIdPoolEntryResult_;
    case (int32_t)OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID:
return bindExternalSystemAccountIdResult_ == other.bindExternalSystemAccountIdResult_;
    case (int32_t)OperationType::PAYMENT:
return paymentResult_ == other.paymentResult_;
    case (int32_t)OperationType::MANAGE_SALE:
return manageSaleResult_ == other.manageSaleResult_;
    case (int32_t)OperationType::CREATE_MANAGE_LIMITS_REQUEST:
return createManageLimitsRequestResult_ == other.createManageLimitsRequestResult_;
    case (int32_t)OperationType::MANAGE_CONTRACT_REQUEST:
return manageContractRequestResult_ == other.manageContractRequestResult_;
    case (int32_t)OperationType::MANAGE_CONTRACT:
return manageContractResult_ == other.manageContractResult_;
    case (int32_t)OperationType::CANCEL_SALE_REQUEST:
return cancelSaleCreationRequestResult_ == other.cancelSaleCreationRequestResult_;
    case (int32_t)OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST:
return createAtomicSwapAskRequestResult_ == other.createAtomicSwapAskRequestResult_;
    case (int32_t)OperationType::CANCEL_ATOMIC_SWAP_ASK:
return cancelAtomicSwapAskResult_ == other.cancelAtomicSwapAskResult_;
    case (int32_t)OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST:
return createAtomicSwapBidRequestResult_ == other.createAtomicSwapBidRequestResult_;
    case (int32_t)OperationType::MANAGE_ACCOUNT_ROLE:
return manageAccountRoleResult_ == other.manageAccountRoleResult_;
    case (int32_t)OperationType::MANAGE_ACCOUNT_RULE:
return manageAccountRuleResult_ == other.manageAccountRuleResult_;
    case (int32_t)OperationType::MANAGE_SIGNER:
return manageSignerResult_ == other.manageSignerResult_;
    case (int32_t)OperationType::MANAGE_SIGNER_ROLE:
return manageSignerRoleResult_ == other.manageSignerRoleResult_;
    case (int32_t)OperationType::MANAGE_SIGNER_RULE:
return manageSignerRuleResult_ == other.manageSignerRuleResult_;
    case (int32_t)OperationType::STAMP:
return stampResult_ == other.stampResult_;
    case (int32_t)OperationType::LICENSE:
return licenseResult_ == other.licenseResult_;
    case (int32_t)OperationType::MANAGE_POLL:
return managePollResult_ == other.managePollResult_;
    case (int32_t)OperationType::MANAGE_CREATE_POLL_REQUEST:
return manageCreatePollRequestResult_ == other.manageCreatePollRequestResult_;
    case (int32_t)OperationType::MANAGE_VOTE:
return manageVoteResult_ == other.manageVoteResult_;
    case (int32_t)OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE:
return manageAccountSpecificRuleResult_ == other.manageAccountSpecificRuleResult_;
    case (int32_t)OperationType::CANCEL_CHANGE_ROLE_REQUEST:
return cancelChangeRoleRequestResult_ == other.cancelChangeRoleRequestResult_;
    case (int32_t)OperationType::REMOVE_ASSET_PAIR:
return removeAssetPairResult_ == other.removeAssetPairResult_;
    case (int32_t)OperationType::CREATE_KYC_RECOVERY_REQUEST:
return createKYCRecoveryRequestResult_ == other.createKYCRecoveryRequestResult_;
    case (int32_t)OperationType::INITIATE_KYC_RECOVERY:
return initiateKYCRecoveryResult_ == other.initiateKYCRecoveryResult_;
    case (int32_t)OperationType::CREATE_MANAGE_OFFER_REQUEST:
return createManageOfferRequestResult_ == other.createManageOfferRequestResult_;
    case (int32_t)OperationType::CREATE_PAYMENT_REQUEST:
return createPaymentRequestResult_ == other.createPaymentRequestResult_;
    case (int32_t)OperationType::REMOVE_ASSET:
return removeAssetResult_ == other.removeAssetResult_;
    case (int32_t)OperationType::OPEN_SWAP:
return openSwapResult_ == other.openSwapResult_;
    case (int32_t)OperationType::CLOSE_SWAP:
return closeSwapResult_ == other.closeSwapResult_;
    case (int32_t)OperationType::CREATE_REDEMPTION_REQUEST:
return createRedemptionRequestResult_ == other.createRedemptionRequestResult_;
    case (int32_t)OperationType::CREATE_DATA:
return createDataResult_ == other.createDataResult_;
    case (int32_t)OperationType::UPDATE_DATA:
return updateDataResult_ == other.updateDataResult_;
    case (int32_t)OperationType::REMOVE_DATA:
return removeDataResult_ == other.removeDataResult_;
    case (int32_t)OperationType::CREATE_DATA_CREATION_REQUEST:
return createDataCreationRequestResult_ == other.createDataCreationRequestResult_;
    case (int32_t)OperationType::CANCEL_DATA_CREATION_REQUEST:
return cancelDataCreationRequestResult_ == other.cancelDataCreationRequestResult_;
    case (int32_t)OperationType::CREATE_DATA_UPDATE_REQUEST:
return createDataUpdateRequestResult_ == other.createDataUpdateRequestResult_;
    case (int32_t)OperationType::CREATE_DATA_REMOVE_REQUEST:
return createDataRemoveRequestResult_ == other.createDataRemoveRequestResult_;
    case (int32_t)OperationType::CANCEL_DATA_UPDATE_REQUEST:
return cancelDataUpdateRequestResult_ == other.cancelDataUpdateRequestResult_;
    case (int32_t)OperationType::CANCEL_DATA_REMOVE_REQUEST:
return cancelDataRemoveRequestResult_ == other.cancelDataRemoveRequestResult_;
    case (int32_t)OperationType::CREATE_DEFERRED_PAYMENT_CREATION_REQUEST:
return createDeferredPaymentCreationRequestResult_ == other.createDeferredPaymentCreationRequestResult_;
    case (int32_t)OperationType::CANCEL_DEFERRED_PAYMENT_CREATION_REQUEST:
return cancelDeferredPaymentCreationRequestResult_ == other.cancelDeferredPaymentCreationRequestResult_;
    case (int32_t)OperationType::CREATE_CLOSE_DEFERRED_PAYMENT_REQUEST:
return createCloseDeferredPaymentRequestResult_ == other.createCloseDeferredPaymentRequestResult_;
    case (int32_t)OperationType::CANCEL_CLOSE_DEFERRED_PAYMENT_REQUEST:
return cancelCloseDeferredPaymentRequestResult_ == other.cancelCloseDeferredPaymentRequestResult_;
    case (int32_t)OperationType::UPDATE_DATA_OWNER:
return updateDataOwnerResult_ == other.updateDataOwnerResult_;
    case (int32_t)OperationType::CREATE_DATA_OWNER_UPDATE_REQUEST:
return createDataOwnerUpdateRequestResult_ == other.createDataOwnerUpdateRequestResult_;
    case (int32_t)OperationType::CANCEL_DATA_OWNER_UPDATE_REQUEST:
return cancelDataOwnerUpdateRequestResult_ == other.cancelDataOwnerUpdateRequestResult_;
}
return false;
}
bool
OperationResult::_tr_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_tr_t const&>(other_abstract);
if (type_ < other.type_) return true;
if (other.type_ < type_) return false;
switch (type_)
{
    case (int32_t)OperationType::CREATE_ACCOUNT:
return createAccountResult_ < other.createAccountResult_;
    case (int32_t)OperationType::CREATE_ISSUANCE_REQUEST:
return createIssuanceRequestResult_ < other.createIssuanceRequestResult_;
    case (int32_t)OperationType::SET_FEES:
return setFeesResult_ < other.setFeesResult_;
    case (int32_t)OperationType::CREATE_WITHDRAWAL_REQUEST:
return createWithdrawalRequestResult_ < other.createWithdrawalRequestResult_;
    case (int32_t)OperationType::MANAGE_BALANCE:
return manageBalanceResult_ < other.manageBalanceResult_;
    case (int32_t)OperationType::MANAGE_ASSET:
return manageAssetResult_ < other.manageAssetResult_;
    case (int32_t)OperationType::CREATE_PREISSUANCE_REQUEST:
return createPreIssuanceRequestResult_ < other.createPreIssuanceRequestResult_;
    case (int32_t)OperationType::MANAGE_LIMITS:
return manageLimitsResult_ < other.manageLimitsResult_;
    case (int32_t)OperationType::MANAGE_ASSET_PAIR:
return manageAssetPairResult_ < other.manageAssetPairResult_;
    case (int32_t)OperationType::MANAGE_OFFER:
return manageOfferResult_ < other.manageOfferResult_;
    case (int32_t)OperationType::MANAGE_INVOICE_REQUEST:
return manageInvoiceRequestResult_ < other.manageInvoiceRequestResult_;
    case (int32_t)OperationType::REVIEW_REQUEST:
return reviewRequestResult_ < other.reviewRequestResult_;
    case (int32_t)OperationType::CREATE_SALE_REQUEST:
return createSaleCreationRequestResult_ < other.createSaleCreationRequestResult_;
    case (int32_t)OperationType::CHECK_SALE_STATE:
return checkSaleStateResult_ < other.checkSaleStateResult_;
    case (int32_t)OperationType::PAYOUT:
return payoutResult_ < other.payoutResult_;
    case (int32_t)OperationType::CREATE_AML_ALERT:
return createAMLAlertRequestResult_ < other.createAMLAlertRequestResult_;
    case (int32_t)OperationType::MANAGE_KEY_VALUE:
return manageKeyValueResult_ < other.manageKeyValueResult_;
    case (int32_t)OperationType::CREATE_CHANGE_ROLE_REQUEST:
return createChangeRoleRequestResult_ < other.createChangeRoleRequestResult_;
    case (int32_t)OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
return manageExternalSystemAccountIdPoolEntryResult_ < other.manageExternalSystemAccountIdPoolEntryResult_;
    case (int32_t)OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID:
return bindExternalSystemAccountIdResult_ < other.bindExternalSystemAccountIdResult_;
    case (int32_t)OperationType::PAYMENT:
return paymentResult_ < other.paymentResult_;
    case (int32_t)OperationType::MANAGE_SALE:
return manageSaleResult_ < other.manageSaleResult_;
    case (int32_t)OperationType::CREATE_MANAGE_LIMITS_REQUEST:
return createManageLimitsRequestResult_ < other.createManageLimitsRequestResult_;
    case (int32_t)OperationType::MANAGE_CONTRACT_REQUEST:
return manageContractRequestResult_ < other.manageContractRequestResult_;
    case (int32_t)OperationType::MANAGE_CONTRACT:
return manageContractResult_ < other.manageContractResult_;
    case (int32_t)OperationType::CANCEL_SALE_REQUEST:
return cancelSaleCreationRequestResult_ < other.cancelSaleCreationRequestResult_;
    case (int32_t)OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST:
return createAtomicSwapAskRequestResult_ < other.createAtomicSwapAskRequestResult_;
    case (int32_t)OperationType::CANCEL_ATOMIC_SWAP_ASK:
return cancelAtomicSwapAskResult_ < other.cancelAtomicSwapAskResult_;
    case (int32_t)OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST:
return createAtomicSwapBidRequestResult_ < other.createAtomicSwapBidRequestResult_;
    case (int32_t)OperationType::MANAGE_ACCOUNT_ROLE:
return manageAccountRoleResult_ < other.manageAccountRoleResult_;
    case (int32_t)OperationType::MANAGE_ACCOUNT_RULE:
return manageAccountRuleResult_ < other.manageAccountRuleResult_;
    case (int32_t)OperationType::MANAGE_SIGNER:
return manageSignerResult_ < other.manageSignerResult_;
    case (int32_t)OperationType::MANAGE_SIGNER_ROLE:
return manageSignerRoleResult_ < other.manageSignerRoleResult_;
    case (int32_t)OperationType::MANAGE_SIGNER_RULE:
return manageSignerRuleResult_ < other.manageSignerRuleResult_;
    case (int32_t)OperationType::STAMP:
return stampResult_ < other.stampResult_;
    case (int32_t)OperationType::LICENSE:
return licenseResult_ < other.licenseResult_;
    case (int32_t)OperationType::MANAGE_POLL:
return managePollResult_ < other.managePollResult_;
    case (int32_t)OperationType::MANAGE_CREATE_POLL_REQUEST:
return manageCreatePollRequestResult_ < other.manageCreatePollRequestResult_;
    case (int32_t)OperationType::MANAGE_VOTE:
return manageVoteResult_ < other.manageVoteResult_;
    case (int32_t)OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE:
return manageAccountSpecificRuleResult_ < other.manageAccountSpecificRuleResult_;
    case (int32_t)OperationType::CANCEL_CHANGE_ROLE_REQUEST:
return cancelChangeRoleRequestResult_ < other.cancelChangeRoleRequestResult_;
    case (int32_t)OperationType::REMOVE_ASSET_PAIR:
return removeAssetPairResult_ < other.removeAssetPairResult_;
    case (int32_t)OperationType::CREATE_KYC_RECOVERY_REQUEST:
return createKYCRecoveryRequestResult_ < other.createKYCRecoveryRequestResult_;
    case (int32_t)OperationType::INITIATE_KYC_RECOVERY:
return initiateKYCRecoveryResult_ < other.initiateKYCRecoveryResult_;
    case (int32_t)OperationType::CREATE_MANAGE_OFFER_REQUEST:
return createManageOfferRequestResult_ < other.createManageOfferRequestResult_;
    case (int32_t)OperationType::CREATE_PAYMENT_REQUEST:
return createPaymentRequestResult_ < other.createPaymentRequestResult_;
    case (int32_t)OperationType::REMOVE_ASSET:
return removeAssetResult_ < other.removeAssetResult_;
    case (int32_t)OperationType::OPEN_SWAP:
return openSwapResult_ < other.openSwapResult_;
    case (int32_t)OperationType::CLOSE_SWAP:
return closeSwapResult_ < other.closeSwapResult_;
    case (int32_t)OperationType::CREATE_REDEMPTION_REQUEST:
return createRedemptionRequestResult_ < other.createRedemptionRequestResult_;
    case (int32_t)OperationType::CREATE_DATA:
return createDataResult_ < other.createDataResult_;
    case (int32_t)OperationType::UPDATE_DATA:
return updateDataResult_ < other.updateDataResult_;
    case (int32_t)OperationType::REMOVE_DATA:
return removeDataResult_ < other.removeDataResult_;
    case (int32_t)OperationType::CREATE_DATA_CREATION_REQUEST:
return createDataCreationRequestResult_ < other.createDataCreationRequestResult_;
    case (int32_t)OperationType::CANCEL_DATA_CREATION_REQUEST:
return cancelDataCreationRequestResult_ < other.cancelDataCreationRequestResult_;
    case (int32_t)OperationType::CREATE_DATA_UPDATE_REQUEST:
return createDataUpdateRequestResult_ < other.createDataUpdateRequestResult_;
    case (int32_t)OperationType::CREATE_DATA_REMOVE_REQUEST:
return createDataRemoveRequestResult_ < other.createDataRemoveRequestResult_;
    case (int32_t)OperationType::CANCEL_DATA_UPDATE_REQUEST:
return cancelDataUpdateRequestResult_ < other.cancelDataUpdateRequestResult_;
    case (int32_t)OperationType::CANCEL_DATA_REMOVE_REQUEST:
return cancelDataRemoveRequestResult_ < other.cancelDataRemoveRequestResult_;
    case (int32_t)OperationType::CREATE_DEFERRED_PAYMENT_CREATION_REQUEST:
return createDeferredPaymentCreationRequestResult_ < other.createDeferredPaymentCreationRequestResult_;
    case (int32_t)OperationType::CANCEL_DEFERRED_PAYMENT_CREATION_REQUEST:
return cancelDeferredPaymentCreationRequestResult_ < other.cancelDeferredPaymentCreationRequestResult_;
    case (int32_t)OperationType::CREATE_CLOSE_DEFERRED_PAYMENT_REQUEST:
return createCloseDeferredPaymentRequestResult_ < other.createCloseDeferredPaymentRequestResult_;
    case (int32_t)OperationType::CANCEL_CLOSE_DEFERRED_PAYMENT_REQUEST:
return cancelCloseDeferredPaymentRequestResult_ < other.cancelCloseDeferredPaymentRequestResult_;
    case (int32_t)OperationType::UPDATE_DATA_OWNER:
return updateDataOwnerResult_ < other.updateDataOwnerResult_;
    case (int32_t)OperationType::CREATE_DATA_OWNER_UPDATE_REQUEST:
return createDataOwnerUpdateRequestResult_ < other.createDataOwnerUpdateRequestResult_;
    case (int32_t)OperationType::CANCEL_DATA_OWNER_UPDATE_REQUEST:
return cancelDataOwnerUpdateRequestResult_ < other.cancelDataOwnerUpdateRequestResult_;
}
return false;
}
bool
OperationResult::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (code_)
{
  case (int32_t)OperationResultCode::opINNER:
return u.from_bytes(tr_);
  case (int32_t)OperationResultCode::opNO_ENTRY:
return u.from_bytes(entryType_);
  case (int32_t)OperationResultCode::opNO_ROLE_PERMISSION:
return u.from_bytes(requirement_);
  default:
  
  return true;
}
return false;
}
bool
OperationResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)OperationResultCode::opINNER:
return m.to_bytes(tr_);
  case (int32_t)OperationResultCode::opNO_ENTRY:
return m.to_bytes(entryType_);
  case (int32_t)OperationResultCode::opNO_ROLE_PERMISSION:
return m.to_bytes(requirement_);
  default:
    return true;
}
return false;
}
void
OperationResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)OperationResultCode::opINNER:
return m.count_size(tr_);
  case (int32_t)OperationResultCode::opNO_ENTRY:
return m.count_size(entryType_);
  case (int32_t)OperationResultCode::opNO_ROLE_PERMISSION:
return m.count_size(requirement_);
  default:
  
  return;
}
}
bool
OperationResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<OperationResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)OperationResultCode::opINNER:
return tr_ == other.tr_;
  case (int32_t)OperationResultCode::opNO_ENTRY:
return entryType_ == other.entryType_;
  case (int32_t)OperationResultCode::opNO_ROLE_PERMISSION:
return requirement_ == other.requirement_;
  default:
  
  return true;
}
return false;
}
bool
OperationResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<OperationResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)OperationResultCode::opINNER:
return tr_ < other.tr_;
  case (int32_t)OperationResultCode::opNO_ENTRY:
return entryType_ < other.entryType_;
  case (int32_t)OperationResultCode::opNO_ROLE_PERMISSION:
return requirement_ < other.requirement_;
  default:
    return false;
}
return false;
}
bool
OperationFee::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
OperationFee::_ext_t::to_bytes(xdr::marshaler& m) const
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
OperationFee::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
OperationFee::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
OperationFee::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
OperationFee::from_bytes(xdr::unmarshaler& u) 
{
bool okoperationType = u.from_bytes(operationType);
if (!okoperationType)
{
return false;
}
bool okamount = u.from_bytes(amount);
if (!okamount)
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
OperationFee::to_bytes(xdr::marshaler& m) const 
{
bool okoperationType = m.to_bytes(operationType);
if (!okoperationType)
{
return false;
}
bool okamount = m.to_bytes(amount);
if (!okamount)
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
OperationFee::count_size(xdr::measurer& m) const 
{
m.count_size(operationType);
m.count_size(amount);
m.count_size(ext);
}
bool
OperationFee::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<OperationFee const&>(other_abstract);return true
&& (operationType== other.operationType)
&& (amount== other.amount)
&& (ext== other.ext)
;}
bool
OperationFee::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<OperationFee const&>(other_abstract);
if (operationType < other.operationType) return true;
if (other.operationType < operationType) return false;
if (amount < other.amount) return true;
if (other.amount < amount) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
TransactionResult::_result_t::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (code_)
{
    case (int32_t)TransactionResultCode::txSUCCESS:
    case (int32_t)TransactionResultCode::txFAILED:
return u.from_bytes(results_);
    case (int32_t)TransactionResultCode::txNO_ROLE_PERMISSION:
return u.from_bytes(requirement_);
    default:
    
  return true;
}
return false;
}
bool
TransactionResult::_result_t::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

    case (int32_t)TransactionResultCode::txSUCCESS:
    case (int32_t)TransactionResultCode::txFAILED:
return m.to_bytes(results_);
    case (int32_t)TransactionResultCode::txNO_ROLE_PERMISSION:
return m.to_bytes(requirement_);
    default:
      return true;
}
return false;
}
void
TransactionResult::_result_t::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

    case (int32_t)TransactionResultCode::txSUCCESS:
    case (int32_t)TransactionResultCode::txFAILED:
return m.count_size(results_);
    case (int32_t)TransactionResultCode::txNO_ROLE_PERMISSION:
return m.count_size(requirement_);
    default:
    
  return;
}
}
bool
TransactionResult::_result_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_result_t const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
    case (int32_t)TransactionResultCode::txSUCCESS:
    case (int32_t)TransactionResultCode::txFAILED:
return results_ == other.results_;
    case (int32_t)TransactionResultCode::txNO_ROLE_PERMISSION:
return requirement_ == other.requirement_;
    default:
    
  return true;
}
return false;
}
bool
TransactionResult::_result_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_result_t const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
    case (int32_t)TransactionResultCode::txSUCCESS:
    case (int32_t)TransactionResultCode::txFAILED:
return results_ < other.results_;
    case (int32_t)TransactionResultCode::txNO_ROLE_PERMISSION:
return requirement_ < other.requirement_;
    default:
      return false;
}
return false;
}
bool
TransactionResult::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
TransactionResult::_ext_t::to_bytes(xdr::marshaler& m) const
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
TransactionResult::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
TransactionResult::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
TransactionResult::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
TransactionResult::from_bytes(xdr::unmarshaler& u) 
{
bool okfeeCharged = u.from_bytes(feeCharged);
if (!okfeeCharged)
{
return false;
}
bool okresult = u.from_bytes(result);
if (!okresult)
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
TransactionResult::to_bytes(xdr::marshaler& m) const 
{
bool okfeeCharged = m.to_bytes(feeCharged);
if (!okfeeCharged)
{
return false;
}
bool okresult = m.to_bytes(result);
if (!okresult)
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
TransactionResult::count_size(xdr::measurer& m) const 
{
m.count_size(feeCharged);
m.count_size(result);
m.count_size(ext);
}
bool
TransactionResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<TransactionResult const&>(other_abstract);return true
&& (feeCharged== other.feeCharged)
&& (result== other.result)
&& (ext== other.ext)
;}
bool
TransactionResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<TransactionResult const&>(other_abstract);
if (feeCharged < other.feeCharged) return true;
if (other.feeCharged < feeCharged) return false;
if (result < other.result) return true;
if (other.result < result) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}