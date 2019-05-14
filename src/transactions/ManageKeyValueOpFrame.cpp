#include "ManageKeyValueOpFrame.h"
#include "ledger/LedgerDelta.h"
#include "ledger/KeyValueHelperLegacy.h"
#include "main/Application.h"
#include <ledger/AccountHelperLegacy.h>
#include "xdrpp/printer.h"

namespace stellar
{
    using namespace std;
    using xdr::operator==;

    char const * ManageKeyValueOpFrame::changeRoleTasks = "change_role_tasks";
    char const * ManageKeyValueOpFrame::externalSystemPrefix = "ext_sys_exp_period";
    char const * ManageKeyValueOpFrame::issuanceTasksPrefix = "issuance_tasks";
    char const * ManageKeyValueOpFrame::withdrawalTasksPrefix = "withdrawal_tasks";
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
    char const* ManageKeyValueOpFrame::limitsUpdateTasks =
        "limits_update_tasks";
    char const* ManageKeyValueOpFrame::atomicSwapTasksPrefix =
        "atomic_swap_tasks";
    char const* ManageKeyValueOpFrame::withdrawLowerBoundPrefix =
        "withdraw_lower_bound";
    char const* ManageKeyValueOpFrame::maxSaleRulesNumbersKey = "max_sale_rules_number";
    char const* ManageKeyValueOpFrame::createPollTasks = "create_poll_tasks";
    char const* ManageKeyValueOpFrame::createKycRecoveryTasks = "create_kyc_recovery_tasks";
    char const* ManageKeyValueOpFrame::kycRecoveryEnabled = "kyc_recovery_enabled";
    char const* ManageKeyValueOpFrame::kycRecoveryAccountRole = "kyc_recovery_account_role";

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
        {createPollTasks, KeyValueEntryType::UINT32},
        {createKycRecoveryTasks, KeyValueEntryType::UINT32},
        {kycRecoveryAccountRole, KeyValueEntryType::UINT64},
        {kycRecoveryEnabled, KeyValueEntryType::UINT32},
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
ManageKeyValueOpFrame::tryGetSignerRequirements(StorageHelper &storageHelper,
                                std::vector<SignerRequirement> &result) const
{
    SignerRuleResource resource(LedgerEntryType::KEY_VALUE);
    resource.keyValue().keyPrefix = getPrefix();

    result.emplace_back(resource, SignerRuleAction::MANAGE);

    return true;
}

    bool ManageKeyValueOpFrame::doApply(Application &app, LedgerDelta &delta, LedgerManager &ledgerManager) {
        innerResult().code(ManageKeyValueResultCode::SUCCESS);

        Database &db = ledgerManager.getDatabase();
        auto keyValueHelper = KeyValueHelperLegacy::Instance();
        auto keyValueFrame = keyValueHelper->loadKeyValue(this->mManageKeyValue.key, db, &delta);

        if (mManageKeyValue.action.action() == ManageKVAction::REMOVE) {
            if (!keyValueFrame) {
                innerResult().code(ManageKeyValueResultCode::NOT_FOUND);
                return false;
            }

            auto ledgerKey = keyValueFrame->getKey();
            keyValueHelper->storeDelete(delta, db, ledgerKey);

            return true;
        }

        if (!keyValueFrame) {
            LedgerEntry mEntry;
            mEntry.data.type(LedgerEntryType::KEY_VALUE);
            mEntry.data.keyValue().key = mManageKeyValue.key;
            mEntry.data.keyValue().value = mManageKeyValue.action.value();
            keyValueHelper->storeAdd(delta, db, mEntry);

            return true;
        }

        keyValueFrame->mEntry.data.keyValue().value = mManageKeyValue.action.value();
        keyValueHelper->storeChange(delta, db, keyValueFrame->mEntry);

        return true;

    }

    bool ManageKeyValueOpFrame::doCheckValid(Application &app)
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

    longstring ManageKeyValueOpFrame::makeAtomicSwapTasksKey()
    {
        return atomicSwapTasksPrefix;
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
    ManageKeyValueOpFrame::makeKYCRecoveryAccountRoleKey()
    {
        return kycRecoveryAccountRole;
    }
}
