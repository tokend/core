#include "ManageKeyValueOpFrame.h"
#include "ledger/StorageHelper.h"
#include "ledger/AccountHelper.h"
#include "ledger/KeyValueHelper.h"
#include "main/Application.h"
#include "xdrpp/printer.h"

namespace stellar
{
    using namespace std;
    using xdr::operator==;

    char const * ManageKeyValueOpFrame::changeRoleTasks = "change_role_tasks";
    char const * ManageKeyValueOpFrame::externalSystemPrefix = "ext_sys_exp_period";
    char const * ManageKeyValueOpFrame::issuanceTasksPrefix = "issuance_tasks";
    char const * ManageKeyValueOpFrame::withdrawalTasksPrefix = "withdrawal_tasks";
    char const * ManageKeyValueOpFrame::feeCollectionBalancePrefix = "fee_collection_balance";
    char const * ManageKeyValueOpFrame::preIssuanceTasksPrefix = "preissuance_tasks";
    char const * ManageKeyValueOpFrame::assetCreateTasks = "asset_create_tasks";
    char const * ManageKeyValueOpFrame::assetUpdateTasks = "asset_update_tasks";
    char const * ManageKeyValueOpFrame::saleUpdateDetailsTasksPrefix = "sale_update_tasks";
    char const * ManageKeyValueOpFrame::saleCreateTasksPrefix = "sale_create_tasks";
    char const * ManageKeyValueOpFrame::invoiceCreateTasks = "invoice_create_tasks";
    char const * ManageKeyValueOpFrame::contractCreateTasks = "contract_create_tasks";
    char const * ManageKeyValueOpFrame::amlAlertCreateTasks = "aml_alert_create";
    char const * ManageKeyValueOpFrame::maxContractDetailLengthPrefix = "max_contract_detail_length";
    char const * ManageKeyValueOpFrame::maxContractInitialDetailLengthPrefix = "max_contract_initial_detail_length";
    char const * ManageKeyValueOpFrame::maxContractsCountPrefix = "max_contracts_count";
    char const * ManageKeyValueOpFrame::maxInvoicesCountPrefix = "max_invoices_count";
    char const * ManageKeyValueOpFrame::maxInvoiceDetailLengthPrefix = "max_invoice_detail_length";
    char const* ManageKeyValueOpFrame::limitsUpdateTasks = "limits_update_tasks";
    char const* ManageKeyValueOpFrame::atomicSwapTasksPrefix = "atomic_swap_bid_tasks";
    char const* ManageKeyValueOpFrame::atomicSwapAskTasks = "atomic_swap_ask_tasks";
    char const* ManageKeyValueOpFrame::withdrawLowerBoundPrefix = "withdraw_lower_bound";
    char const* ManageKeyValueOpFrame::maxSaleRulesNumbersKey = "max_sale_rules_number";
    char const* ManageKeyValueOpFrame::createPollTasks = "create_poll_tasks";
    char const* ManageKeyValueOpFrame::createKycRecoveryTasks = "create_kyc_recovery_tasks";
    char const* ManageKeyValueOpFrame::kycRecoveryEnabled = "kyc_recovery_enabled";
    char const* ManageKeyValueOpFrame::kycRecoverySignerRole = "kyc_recovery_signer_role";
    char const* ManageKeyValueOpFrame::createOfferTasks = "create_offer_tasks";
    char const* ManageKeyValueOpFrame::removeOfferTasks = "remove_offer_tasks";
    char const* ManageKeyValueOpFrame::createSaleParticipationTasks = "create_sale_participation_tasks";
    char const* ManageKeyValueOpFrame::removeSaleParticipationTasks = "remove_sale_participation_tasks";
    char const* ManageKeyValueOpFrame::paymentTasks = "payment_tasks";
    char const* ManageKeyValueOpFrame::redemptionTasks = "redemption_tasks";
    char const* ManageKeyValueOpFrame::createDataCreationRequestTasks = "create_data_creation_request_tasks";
    char const* ManageKeyValueOpFrame::createDataUpdateRequestTasks = "create_data_update_request_tasks";
    char const* ManageKeyValueOpFrame::createDataRemoveRequestTasks = "create_data_remove_request_tasks";
    char const* ManageKeyValueOpFrame::createDeferredPaymentCreationTasks = "create_deferred_payment_creation_tasks";
    char const* ManageKeyValueOpFrame::createDeferredPaymentCloseTasks = "create_deferred_payment_close_tasks";

ManageKeyValueOpFrame::ManageKeyValueOpFrame(const stellar::Operation &op, stellar::OperationResult &res,
                                             stellar::TransactionFrame &parentTx)
        : OperationFrame(op, res, parentTx),
          mManageKeyValue(mOperation.body.manageKeyValueOp())
{
    // is used for validation type
    mValueTypes =
    {
        {changeRoleTasks, KeyValueEntryType::UINT32},
        {externalSystemPrefix, KeyValueEntryType::UINT32},
        {issuanceTasksPrefix, KeyValueEntryType::UINT32},
        {maxContractDetailLengthPrefix, KeyValueEntryType::UINT32},
        {maxContractInitialDetailLengthPrefix, KeyValueEntryType::UINT32},
        {maxContractsCountPrefix, KeyValueEntryType::UINT32},
        {maxInvoiceDetailLengthPrefix, KeyValueEntryType::UINT32},
        {maxInvoicesCountPrefix, KeyValueEntryType::UINT32},
        {atomicSwapTasksPrefix, KeyValueEntryType::UINT32},
        {withdrawLowerBoundPrefix, KeyValueEntryType::UINT64},
        {limitsUpdateTasks, KeyValueEntryType::UINT32},
        {withdrawalTasksPrefix, KeyValueEntryType::UINT32},
        {assetCreateTasks, KeyValueEntryType::UINT32},
        {assetUpdateTasks, KeyValueEntryType::UINT32},
        {preIssuanceTasksPrefix, KeyValueEntryType::UINT32},
        {atomicSwapAskTasks, KeyValueEntryType::UINT32},
        {atomicSwapTasksPrefix, KeyValueEntryType::UINT32},
        {createPollTasks, KeyValueEntryType::UINT32},
        {createKycRecoveryTasks, KeyValueEntryType::UINT32},
        {kycRecoverySignerRole, KeyValueEntryType::UINT64},
        {kycRecoveryEnabled, KeyValueEntryType::UINT32},
        {createOfferTasks, KeyValueEntryType::UINT32},
        {removeOfferTasks, KeyValueEntryType::UINT32},
        {createSaleParticipationTasks, KeyValueEntryType::UINT32},
        {removeSaleParticipationTasks, KeyValueEntryType::UINT32},
        {paymentTasks, KeyValueEntryType::UINT32},
        {redemptionTasks, KeyValueEntryType::UINT32},
        {createDataCreationRequestTasks, KeyValueEntryType::UINT32},
        {createDataUpdateRequestTasks, KeyValueEntryType::UINT32},
        {createDataRemoveRequestTasks, KeyValueEntryType::UINT32},
        {createDeferredPaymentCreationTasks, KeyValueEntryType::UINT32},
        {createDeferredPaymentCloseTasks, KeyValueEntryType::UINT32},

    };
}

bool
ManageKeyValueOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                                                 std::vector<OperationCondition>& result) const
{
    AccountRuleResource resource(LedgerEntryType::KEY_VALUE);
    resource.keyValue().keyPrefix = getPrefix();
    result.emplace_back(resource, AccountRuleAction::MANAGE, mSourceAccount);
    return true;
}

bool
ManageKeyValueOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                                std::vector<SignerRequirement>& result) const
{
    SignerRuleResource resource(LedgerEntryType::KEY_VALUE);
    resource.keyValue().keyPrefix = getPrefix();
    result.emplace_back(resource, SignerRuleAction::MANAGE);
    return true;
}

bool ManageKeyValueOpFrame::doApply(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager)
{
    innerResult().code(ManageKeyValueResultCode::SUCCESS);
    auto& keyValueHelper = storageHelper.getKeyValueHelper();
    auto keyValueFrame = keyValueHelper.loadKeyValue(this->mManageKeyValue.key);
    if (mManageKeyValue.action.action() == ManageKVAction::REMOVE)
    {
        if (!keyValueFrame)
        {
            innerResult().code(ManageKeyValueResultCode::NOT_FOUND);
            return false;
        }
        auto ledgerKey = keyValueFrame->getKey();
        keyValueHelper.storeDelete(ledgerKey);
        return true;
    }
    if (!keyValueFrame)
    {
        LedgerEntry mEntry;
        mEntry.data.type(LedgerEntryType::KEY_VALUE);
        mEntry.data.keyValue().key = mManageKeyValue.key;
        mEntry.data.keyValue().value = mManageKeyValue.action.value();
        keyValueHelper.storeAdd(mEntry);
        return true;
    }
    keyValueFrame->mEntry.data.keyValue().value = mManageKeyValue.action.value();
    keyValueHelper.storeChange(keyValueFrame->mEntry);
    return true;

}

bool ManageKeyValueOpFrame::doCheckValid(Application& app)
{
    if (mManageKeyValue.action.action() != ManageKVAction::PUT)
    {
        return true;
    }
    auto prefix = getPrefix();
    auto valueTypesIter = mValueTypes.find(prefix);
    if (valueTypesIter != mValueTypes.end())
    {
        if (mManageKeyValue.action.value().type() != mValueTypes[prefix])
        {
            innerResult().code(ManageKeyValueResultCode::INVALID_TYPE);
            return false;
        }
        if ((prefix == withdrawalTasksPrefix) &&
            (mManageKeyValue.action.value().ui32Value() == 0))
        {
            innerResult().code(ManageKeyValueResultCode::ZERO_VALUE_NOT_ALLOWED);
            return false;
        }
    }
    return true;
}

longstring
ManageKeyValueOpFrame::makeChangeRoleKey(string currentRoleID, string roleIDToSet)
{
    return string(changeRoleTasks) + ":" + currentRoleID + ":" + roleIDToSet;
}

longstring
ManageKeyValueOpFrame::makeLimitsUpdateTasksKey()
{
    return limitsUpdateTasks;
}

longstring
ManageKeyValueOpFrame::makeExternalSystemExpirationPeriodKey(int32 externalSystemType)
{
    return string(externalSystemPrefix) + ":" + to_string(externalSystemType);
}

longstring
ManageKeyValueOpFrame::makeMaxContractDetailLengthKey()
{
    return maxContractDetailLengthPrefix;
}

longstring
ManageKeyValueOpFrame::makeMaxContractsCountKey()
{
    return maxContractsCountPrefix;
}

longstring
ManageKeyValueOpFrame::makeMaxInvoicesCountKey()
{
    return maxInvoicesCountPrefix;
}

longstring
ManageKeyValueOpFrame::makeMaxInvoiceDetailLengthKey()
{
    return maxInvoiceDetailLengthPrefix;
}

longstring
ManageKeyValueOpFrame::makeMaxContractInitialDetailLengthKey()
{
    return maxContractInitialDetailLengthPrefix;
}

longstring ManageKeyValueOpFrame::makeIssuanceTasksKey(AssetCode assetCode)
{
    return string(issuanceTasksPrefix) + ":" + assetCode;
}

longstring ManageKeyValueOpFrame::makeAtomicSwapBidTasksKey(AssetCode assetCode)
{
    return string(atomicSwapTasksPrefix) + ":" + assetCode;
}

longstring ManageKeyValueOpFrame::makeWithdrawLowerBoundKey(AssetCode assetCode)
{
    return string(withdrawLowerBoundPrefix) + ":" + assetCode;
}

longstring ManageKeyValueOpFrame::makeWithdrawalTasksKey(AssetCode assetCode)
{
    longstring key;
    key = key + withdrawalTasksPrefix + ":" + assetCode;
    return key;
}

longstring ManageKeyValueOpFrame::makeFeeCollectionBalanceKey(AssetCode assetCode)
{
    longstring key;
    key = key + feeCollectionBalancePrefix + ":" + assetCode;
    return key;
}

longstring ManageKeyValueOpFrame::makePreIssuanceTasksKey(AssetCode assetCode)
{
    longstring key;
    key = key + preIssuanceTasksPrefix + ":" + assetCode;
    return key;
}

longstring ManageKeyValueOpFrame::makeAssetCreateTasksKey()
{
    return assetCreateTasks;
}

longstring ManageKeyValueOpFrame::makeAssetUpdateTasksKey()
{
    return assetUpdateTasks;
}

longstring ManageKeyValueOpFrame::makeSaleUpdateTasksKey(longstring ID)
{
    longstring key;
    key = key + saleUpdateDetailsTasksPrefix + ":" + ID;
    return key;
}

longstring ManageKeyValueOpFrame::makeInvoiceCreateTasksKey()
{
    return invoiceCreateTasks;
}

longstring ManageKeyValueOpFrame::makeContractCreateTasksKey()
{
    return contractCreateTasks;
}

longstring ManageKeyValueOpFrame::makeSaleCreateTasksKey(AssetCode assetCode)
{
    longstring key;
    key = key + saleCreateTasksPrefix + ":" + assetCode;
    return key;
}

longstring ManageKeyValueOpFrame::makeAmlAlertCreateTasksKey()
{
    return amlAlertCreateTasks;
}

longstring ManageKeyValueOpFrame::makeAtomicSwapAskTasksKey()
{
    return atomicSwapAskTasks;
}

longstring
ManageKeyValueOpFrame::makeMaxSaleRulesNumberKey()
{
    return maxSaleRulesNumbersKey;
}

longstring
ManageKeyValueOpFrame::makeCreatePollKey(std::string type)
{
    return string(createPollTasks) + ":" + type;
}

longstring
ManageKeyValueOpFrame::makeCreateKYCRecoveryTasksKey()
{
    return createKycRecoveryTasks;
}

longstring
ManageKeyValueOpFrame::makeKYCRecoveryKey()
{
    return kycRecoveryEnabled;
}

    longstring
    ManageKeyValueOpFrame::makeKYCRecoverySignerRoleKey()
    {
        return kycRecoverySignerRole;
    }

    longstring
    ManageKeyValueOpFrame::makeCreateOfferKey(AssetCode const& base, AssetCode const& quote)
    {
        return string(createOfferTasks) + ":" + base + ":" + quote;
    }

    longstring
    ManageKeyValueOpFrame::makeDeleteOfferKey(AssetCode const& base, AssetCode const& quote)
    {
        return string(removeOfferTasks) + ":" + base + ":" + quote;
    }

    longstring
    ManageKeyValueOpFrame::makeCreateSaleParticipationKey(AssetCode const& base, AssetCode const& quote)
    {
        return string(createSaleParticipationTasks) + ":" + base + ":" + quote;
    }

    longstring
    ManageKeyValueOpFrame::makeDeleteSaleParticipationKey(AssetCode const& base, AssetCode const& quote)
    {
        return string(removeSaleParticipationTasks) + ":" + base + ":" + quote;
    }

    longstring
    ManageKeyValueOpFrame::makePaymentTasksKey(AssetCode const& code)
    {
        return string(paymentTasks) + ":" + code;
    }

    longstring
    ManageKeyValueOpFrame::makeRedemptionTasksKey()
    {
        return string(redemptionTasks);
    }


    longstring
    ManageKeyValueOpFrame::makeCreateDataCreationRequestTasksKey(string type)
    {
        return string(createDataCreationRequestTasks) + ":" + type;
    }

    longstring
    ManageKeyValueOpFrame::makeCreateDataUpdateRequestTasksKey(string type)
    {
        return string(createDataUpdateRequestTasks) + ":" + type;
    }

    longstring
    ManageKeyValueOpFrame::makeCreateDataRemoveRequestTasksKey(string type)
    {
        return string(createDataRemoveRequestTasks) + ":" + type;
    }

    longstring
    ManageKeyValueOpFrame::makeCreateDeferredPaymentCreationTasksKey(AssetCode const& code)
    {
        return string(createDeferredPaymentCreationTasks) + ":" + code;
    }

    longstring
    ManageKeyValueOpFrame::makeCreateDeferredPaymentCloseTasksKey(AssetCode const& code)
    {
        return string(createDeferredPaymentCloseTasks) + ":" + code;
    }
}
