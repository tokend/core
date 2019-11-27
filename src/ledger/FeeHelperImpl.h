#pragma once

// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ledger/EntryHelper.h"
#include "ledger/LedgerManager.h"
#include <functional>
#include <unordered_map>
#include "FeeFrame.h"
#include "FeeHelper.h"
#include "StorageHelperImpl.h"

namespace soci
{
class session;
}

namespace stellar
{

class StatementContext;

class FeeHelperImpl : public FeeHelper, NonCopyable
 {
public:
    explicit FeeHelperImpl(StorageHelper &storageHelper);
    void dropAll() override;
    void storeAdd(LedgerEntry const& entry) override;
    void storeChange(LedgerEntry const& entry) override;
    void storeDelete(LedgerKey const& key) override;
    bool exists(LedgerKey const& key) override;
    LedgerKey getLedgerKey(LedgerEntry const& from) override;
    EntryFrame::pointer fromXDR(LedgerEntry const& from) override;
    EntryFrame::pointer storeLoad(LedgerKey const& ledgerKey) override;
    uint64_t countObjects() override;
    Database& getDatabase() override;
    LedgerDelta* getLedgerDelta() override;

private:
    FeeFrame::pointer
    loadFee(FeeType feeType, AssetCode asset, AccountID *accountID,
            uint64_t* accountType, int64_t subtype, int64_t lowerBound,
            int64_t upperBound) override;

    FeeFrame::pointer
    loadFee(Hash hash, int64_t lowerBound, int64_t upperBound) override;

    FeeFrame::pointer
    loadForAccount(FeeType feeType, AssetCode asset, int64_t subtype,
                   AccountFrame::pointer accountFrame, int64_t amount) override;

    std::vector<FeeFrame::pointer> loadFees(Hash hash) override;

    void storeUpdateHelper(bool insert, LedgerEntry const &entry) override;

    void loadFees(StatementContext &prep, std::function<void(LedgerEntry const &)> feeProcessor) override;

    void checkAmounts(const FeeFrame::pointer &frame) const override;

    bool isBoundariesOverlap(Hash hash, int64_t lowerBound, int64_t upperBound) override;

    bool exists(Hash hash, int64_t lowerBound, int64_t upperBound) override;

    StorageHelper& mStorageHelper;
    const char* mFeeColumnSelector;
};
}