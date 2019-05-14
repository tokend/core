#pragma once

#include <ledger/ReviewableRequestFrame.h>
#include "transactions/OperationFrame.h"

namespace stellar
{

class InitiateKYCRecoveryOpFrame : public OperationFrame
{
    InitiateKYCRecoveryOp mInitiateKYCRecoveryOp;

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;

    InitiateKYCRecoveryResult&
    innerResult()
    {
        return mResult.tr().initiateKYCRecoveryResult();
    }

    void clearSigners(StorageHelper& signerHelper);

    void createSigner(StorageHelper& signerHelper, AccountFrame& accountFrame);

    void deletePendingRecoveryRequests(Application& app, StorageHelper& storageHelper);

public:
    InitiateKYCRecoveryOpFrame(Operation const &op, OperationResult &res, TransactionFrame &parentTx);

    bool doApply(Application &app, StorageHelper& storageHelper, LedgerManager &ledgerManager) override;

    bool doCheckValid(Application &app) override;

    static InitiateKYCRecoveryResultCode getInnerCode(OperationResult const &res)
    {
        return res.tr().initiateKYCRecoveryResult().code();
    }

    std::string getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<InitiateKYCRecoveryResultCode>::enum_name(innerResult().code());
    }

    static bool isRecoveryAllowed(StorageHelper& storageHelper);

    static bool getRecoveryAccountRole(StorageHelper& storageHelper, uint64_t& roleID);
};
}
