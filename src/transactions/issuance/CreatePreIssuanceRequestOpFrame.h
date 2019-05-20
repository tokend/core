#pragma once

// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "transactions/OperationFrame.h"
#include "ledger/AssetFrame.h"

namespace stellar
{
class CreatePreIssuanceRequestOpFrame : public OperationFrame
{
    CreatePreIssuanceRequestResult&
    innerResult()
    {
        return mResult.tr().createPreIssuanceRequestResult();
    }

	CreatePreIssuanceRequestOp const& mCreatePreIssuanceRequest;

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result,
                              LedgerManager& ledgerManager) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;

	bool isSignatureValid(AssetFrame::pointer asset, LedgerVersion version);

public:

    CreatePreIssuanceRequestOpFrame(Operation const& op, OperationResult& res,
                       TransactionFrame& parentTx);

    bool doApply(Application& app, StorageHelper &storageHelper,
                 LedgerManager& ledgerManager) override;
    bool doCheckValid(Application& app) override;

    static CreatePreIssuanceRequestResultCode
    getInnerCode(OperationResult const& res)
    {
        return res.tr().createPreIssuanceRequestResult().code();
    }

	std::string getInnerResultCodeAsStr() override {
		return xdr::xdr_traits<CreatePreIssuanceRequestResultCode>::enum_name(innerResult().code());
	}

	static Hash getSignatureData(stellar::string64 const& reference, uint64_t const& amount, AssetCode const& assetCode);

    std::vector<std::string> makeTasksKeyVector();
};
}
