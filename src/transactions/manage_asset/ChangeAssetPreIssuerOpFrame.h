#pragma once

// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ManageAssetOpFrame.h"
#include "ledger/ReviewableRequestFrame.h"

namespace stellar
{

class ChangeAssetPreIssuerOpFrame : public ManageAssetOpFrame {

    AssetChangePreissuedSigner const& mAssetChangePreissuedSigner;

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;

    bool
    isSignatureValid(AssetFrame::pointer asset, LedgerVersion version);

    Hash
    getSignatureData(AssetCode const& assetCode, AccountID const& newPreIssuer);

public:
    ChangeAssetPreIssuerOpFrame(Operation const& op, OperationResult& res,
                                TransactionFrame& parentTx);

    bool doApply(Application& app, StorageHelper& storageHelper,
                 LedgerManager& ledgerManager) override;

    bool doCheckValid(Application& app) override;

protected:
    std::string getAssetCode() const override;
};
}
