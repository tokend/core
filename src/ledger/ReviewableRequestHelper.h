#pragma once

// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ledger/EntryHelper.h"
#include "ledger/LedgerManager.h"
#include <functional>
#include <unordered_map>
#include "ReviewableRequestFrame.h"

namespace soci
{
class session;
}

namespace stellar
{
class StatementContext;

class ReviewableRequestHelper : public EntryHelper {
public:

    virtual void dropAll() = 0;
    virtual void storeAdd(LedgerEntry const& entry) = 0;
    virtual void storeChange(LedgerEntry const& entry) = 0;
    virtual void storeDelete(LedgerKey const& key) = 0;
    virtual bool exists(LedgerKey const& key) = 0;
    virtual LedgerKey getLedgerKey(LedgerEntry const& from) = 0;
    virtual EntryFrame::pointer storeLoad(LedgerKey const& key) = 0;
    virtual EntryFrame::pointer fromXDR(LedgerEntry const& from) = 0;
    virtual uint64_t countObjects() = 0;

    virtual void loadRequests(StatementContext& prep, std::function<void(LedgerEntry const&)> requestsProcessor) = 0;

    virtual ReviewableRequestFrame::pointer loadRequest(uint64 requestID) = 0;
    virtual ReviewableRequestFrame::pointer loadRequest(AccountID& requestor, string64 reference) = 0;
    virtual ReviewableRequestFrame::pointer loadRequest(uint64 requestID, AccountID requestor) = 0;
    virtual ReviewableRequestFrame::pointer
    loadRequest(uint64 requestID, AccountID requestor, ReviewableRequestType requestType) = 0;

    virtual std::vector<ReviewableRequestFrame::pointer>
    loadRequests(AccountID const& requestor, ReviewableRequestType requestType) = 0;

    virtual std::vector<ReviewableRequestFrame::pointer> loadRequests(std::vector<uint64_t> requestIDs) = 0;

    virtual bool exists(AccountID const& requestor, string64 reference, uint64_t requestID) = 0;
    virtual bool isReferenceExist(AccountID const& requestor, string64 reference, uint64_t requestID) = 0;
};
}
