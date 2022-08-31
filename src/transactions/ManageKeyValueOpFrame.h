#pragma once

#include "transactions/OperationFrame.h"

namespace stellar {

class ManageKeyValueOpFrame : public OperationFrame
{
    ManageKeyValueOp const& mManageKeyValue;

    std::map<std::string, KeyValueEntryType> mValueTypes;

    ManageKeyValueResult& innerResult()
    {
        return mResult.tr().manageKeyValueResult();
    }

    bool
    tryGetOperationConditions(StorageHelper& sh,
                              std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;

public:

    ManageKeyValueOpFrame(Operation const& op, OperationResult& res,
                          TransactionFrame& parentTx);

    bool doApply(Application& app, StorageHelper& storageHelper,
                 LedgerManager& ledgerManager) override;

    bool doCheckValid(Application& app) override;

    static ManageKeyValueResultCode
    getInnerCode(OperationResult const& res)
    {
        return res.tr().manageKeyValueResult().code();
    }

    std::string getInnerResultCodeAsStr() override
    {
        const auto result = getResult();
        const auto code = getInnerCode(result);
        return xdr::xdr_traits<ManageKeyValueResultCode>::enum_name(code);
    }

    longstring getPrefix() const {
        longstring prefix;
        std::istringstream from(mManageKeyValue.key);
        std::getline(from,prefix,':');

        return prefix;
    }

    static longstring
    makeChangeRoleKey(std::string currentRoleID, std::string roleIDToSet);

    static longstring makeLimitsUpdateTasksKey();

    static longstring makeExternalSystemExpirationPeriodKey(int32 type);
    static longstring makeIssuanceTasksKey(AssetCode assetCode);
    static longstring makeWithdrawalTasksKey(AssetCode assetCode);

    static longstring makeMaxContractDetailLengthKey();
    static longstring makeFeeCollectionBalanceKey(AssetCode assetCode);

    static longstring makeMaxContractInitialDetailLengthKey();

    static longstring makeMaxContractsCountKey();

    static longstring makeMaxInvoicesCountKey();

    static longstring makeMaxInvoiceDetailLengthKey();

    static longstring makeAtomicSwapBidTasksKey(AssetCode assetCode);
    static longstring makeAtomicSwapAskTasksKey();
    static longstring makePreIssuanceTasksKey(AssetCode assetCode);
    static longstring makeAssetCreateTasksKey();

    static longstring makeWithdrawLowerBoundKey(AssetCode assetCode);

    static longstring makeAssetUpdateTasksKey();

    static longstring makeSaleUpdateTasksKey(longstring ID);

    static longstring makeSaleCreateTasksKey(AssetCode assetCode);

    static longstring makeInvoiceCreateTasksKey();

    static longstring makeContractCreateTasksKey();

    static longstring makeAmlAlertCreateTasksKey();

    static longstring makeMaxSaleRulesNumberKey();

    static longstring makeCreatePollKey(std::string type);

    static longstring makeCreateKYCRecoveryTasksKey();

    static longstring makeKYCRecoveryKey();

    static longstring makeKYCRecoverySignerRoleKey();

    static longstring makeCreateOfferKey(AssetCode const& base, AssetCode const& quote);
    static longstring makeDeleteOfferKey(AssetCode const& base, AssetCode const& quote);
    static longstring makeCreateSaleParticipationKey(AssetCode const& base, AssetCode const& quote);
    static longstring makeDeleteSaleParticipationKey(AssetCode const& base, AssetCode const& quote);

    static longstring makePaymentTasksKey(AssetCode const& code);
    static longstring makeRedemptionTasksKey();
    static longstring makeCreateDataCreationRequestTasksKey(std::string type);
    static longstring makeCreateDataUpdateRequestTasksKey(std::string type);
    static longstring makeCreateDataRemoveRequestTasksKey(std::string type);
    static longstring
        makeCreateDeferredPaymentCreationTasksKey(AssetCode const& code);
    static longstring
        makeCreateDeferredPaymentCloseTasksKey(AssetCode const& code);
    static longstring makeCreateDataOwnerUpdateRequestTasksKey(std::string type);

    static const char * changeRoleTasks;
    static const char * externalSystemPrefix;
    static const char * issuanceTasksPrefix;
    static const char * withdrawalTasksPrefix;
    static const char * maxContractDetailLengthPrefix;
    static const char * maxContractInitialDetailLengthPrefix;
    static const char * maxContractsCountPrefix;
    static const char * maxInvoicesCountPrefix;
    static const char * maxInvoiceDetailLengthPrefix;
    static const char * atomicSwapTasksPrefix;
    static const char * atomicSwapAskTasks;
    static const char * withdrawLowerBoundPrefix;
    static const char * feeCollectionBalancePrefix;
    static char const * preIssuanceTasksPrefix;
    static char const * assetCreateTasks;
    static char const * assetUpdateTasks;
    static char const * saleUpdateDetailsTasksPrefix;
    static char const * saleCreateTasksPrefix;
    static char const * invoiceCreateTasks;
    static char const * contractCreateTasks;
    static char const * amlAlertCreateTasks;
    static char const * limitsUpdateTasks;
    static char const * maxSaleRulesNumbersKey;
    static char const * createPollTasks;
    static char const * createKycRecoveryTasks;
    static char const * kycRecoveryEnabled;
    static char const * kycRecoverySignerRole;
    static char const * createOfferTasks;
    static char const * removeOfferTasks;
    static char const * createSaleParticipationTasks;
    static char const * removeSaleParticipationTasks;
    static char const * paymentTasks;
    static char const * redemptionTasks;
    static char const * createDataCreationRequestTasks;
    static char const * createDataUpdateRequestTasks;
    static char const * createDataRemoveRequestTasks;
    static char const * createDeferredPaymentCreationTasks;
    static char const * createDeferredPaymentCloseTasks;
    static char const * createDataOwnerUpdateRequestTasks;
};
}
