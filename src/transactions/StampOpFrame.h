#pragma once

#include <xdr/Stellar-operation-stamp.h>
#include "transactions/OperationFrame.h"

namespace stellar
{

class StampOpFrame : public OperationFrame
{
    StampResult&
    innerResult()
    {
        return mResult.tr().stampResult();
    }
    StampOp const& mStamp;

    std::unordered_map<AccountID, CounterpartyDetails> getCounterpartyDetails(Database& db, LedgerDelta* delta) const override;
    SourceDetails getSourceAccountDetails(std::unordered_map<AccountID, CounterpartyDetails> counterpartiesDetails,
                                          int32_t ledgerVersion) const override;
    int64_t getExpiresAt(StorageHelper& storageHelper, LedgerManager &ledgerManager, int32 externalSystemType);

public:
    StampOpFrame(Operation const& op, OperationResult& res,
                                       TransactionFrame& parentTx);

    bool doApply(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager) override;
    bool doCheckValid(Application& app) override;

    static StampResultCode
    getInnerCode(OperationResult const& res)
    {
        return res.tr().stampResult().code();
    }

    std::string getInnerResultCodeAsStr() override {
        return xdr::xdr_traits<StampResultCode >::enum_name(innerResult().code());
    }
};
}