
#include "ManageKeyValueOpFrame.h"
#include "ledger/LedgerDelta.h"
#include "ledger/KeyValueHelperLegacy.h"
#include "database/Database.h"
#include "main/Application.h"
#include "medida/meter.h"
#include "medida/metrics_registry.h"
#include <string>
#include <ledger/AccountHelper.h>
#include <transactions/kyc/CreateKYCReviewableRequestOpFrame.h>
#include "xdrpp/printer.h"
#include <map>

namespace stellar {
    using namespace std;
    using xdr::operator==;

    char const * ManageKeyValueOpFrame::kycRulesPrefix = "kyc_lvlup_rules";
    char const * ManageKeyValueOpFrame::externalSystemPrefix = "ext_sys_exp_period";
    char const * ManageKeyValueOpFrame::transactionFeeAssetKey = "tx_fee_asset";
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
    char const* ManageKeyValueOpFrame::transactionFeeAssetPrefix =
        "tx_fee_asset";
    char const* ManageKeyValueOpFrame::atomicSwapTasksPrefix =
        "atomic_swap_tasks";
    char const* ManageKeyValueOpFrame::withdrawLowerBoundPrefix =
        "withdraw_lower_bound";


    map<std::string, KeyValueEntryType> ManageKeyValueOpFrame::valueTypes = {
        {kycRulesPrefix, KeyValueEntryType::UINT32},
        {externalSystemPrefix, KeyValueEntryType::UINT32},
        {issuanceTasksPrefix, KeyValueEntryType::UINT32},
        {maxContractDetailLengthPrefix, KeyValueEntryType::UINT32},
        {maxContractInitialDetailLengthPrefix, KeyValueEntryType::UINT32},
        {maxContractsCountPrefix, KeyValueEntryType::UINT32},
        {maxInvoiceDetailLengthPrefix, KeyValueEntryType::UINT32},
        {maxInvoicesCountPrefix, KeyValueEntryType::UINT32},
        {atomicSwapTasksPrefix, KeyValueEntryType::UINT32},
        {withdrawLowerBoundPrefix, KeyValueEntryType::UINT64},
        {transactionFeeAssetPrefix, KeyValueEntryType::STRING},
    };

    ManageKeyValueOpFrame::ManageKeyValueOpFrame(const stellar::Operation &op, stellar::OperationResult &res,
                                                 stellar::TransactionFrame &parentTx)
            : OperationFrame(op, res, parentTx),
              mManageKeyValue(mOperation.body.manageKeyValueOp())
    {
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

    bool ManageKeyValueOpFrame::doCheckValid(Application &app) {
        auto prefix = getPrefix();

        auto valueTypesIter = valueTypes.find(prefix);
        if (valueTypesIter != valueTypes.end()) {
            if (mManageKeyValue.action.value().type() != valueTypes[prefix]) {
                innerResult().code(ManageKeyValueResultCode::INVALID_TYPE);
                return false;
            }
        }
        return true;
    }

    std::unordered_map<AccountID, CounterpartyDetails>
    ManageKeyValueOpFrame::getCounterpartyDetails(Database &db, LedgerDelta *delta) const {
        return unordered_map<AccountID, CounterpartyDetails>();
    }

    SourceDetails ManageKeyValueOpFrame::getSourceAccountDetails(
            std::unordered_map<AccountID, CounterpartyDetails> counterpartiesDetails, int32_t ledgerVersion) const
    {
        auto prefix = getPrefix();

        if(strcmp(prefix.c_str(),kycRulesPrefix) == 0) {
            return SourceDetails({AccountType::MASTER}, mSourceAccount->getHighThreshold(),
                                 static_cast<int32_t>(SignerType::KYC_SUPER_ADMIN));
        }

        return SourceDetails({AccountType::MASTER}, mSourceAccount->getHighThreshold(),
                             static_cast<int32_t>(SignerType::KEY_VALUE_MANAGER));
    }

    longstring
    ManageKeyValueOpFrame::makeKYCRuleKey(AccountType accountType, uint32 kycLevel, AccountType accountTypeToSet,
                                          uint32 kycLevelToSet) {
        return string(kycRulesPrefix) + ":" + to_string(static_cast<uint32 >(accountType)) + ":" + to_string(kycLevel) + ":"
               + to_string(static_cast<uint32>(accountTypeToSet)) + ":" + to_string(kycLevelToSet);
    }

    longstring
    ManageKeyValueOpFrame::makeExternalSystemExpirationPeriodKey(int32 externalSystemType)
    {
        return string(externalSystemPrefix) + ":" + to_string(externalSystemType);
    }

    longstring
    ManageKeyValueOpFrame::makeTransactionFeeAssetKey() {
        return transactionFeeAssetPrefix;
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


}
