#pragma once

// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ReviewRequestOpFrame.h"
#include "ledger/ReviewableRequestFrame.h"

namespace stellar
{
class ReviewCreateDeferredPaymentRequestOpFrame : public ReviewRequestOpFrame
{
    bool tryGetSignerRequirements(StorageHelper& storageHelper,
                                  std::vector<SignerRequirement>& result,
                                  LedgerManager& lm) const override;

  protected:
    bool handleApprove(Application& app, StorageHelper& storageHelper,
                       LedgerManager& ledgerManager,
                       ReviewableRequestFrame::pointer request) override;

    bool
    handlePermanentReject(Application& app, StorageHelper& storageHelper,
                          LedgerManager& ledgerManager,
                          ReviewableRequestFrame::pointer request) override;
  public:
    ReviewCreateDeferredPaymentRequestOpFrame(Operation const& op,
                                              OperationResult& res,
                                              TransactionFrame& parentTx);

    bool doCheckValid(Application& app) override;
};
}
