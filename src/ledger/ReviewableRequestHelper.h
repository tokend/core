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
    virtual ReviewableRequestFrame::pointer loadRequest(uint64 requestID) = 0;
    virtual ReviewableRequestFrame::pointer loadRequest(AccountID& requestor, string64 reference) = 0;
    virtual ReviewableRequestFrame::pointer loadRequest(uint64 requestID, AccountID requestor) = 0;
    virtual ReviewableRequestFrame::pointer
    loadRequest(uint64 requestID, AccountID requestor, ReviewableRequestType requestType) = 0;

    virtual std::vector<ReviewableRequestFrame::pointer>
    loadRequests(AccountID const& requestor, ReviewableRequestType requestType) = 0;

    virtual std::vector<ReviewableRequestFrame::pointer> loadRequests(std::vector<uint64_t> requestIDs) = 0;

    virtual bool exists(AccountID const& requestor, string64 reference, uint64_t requestID = 0) = 0;
    virtual bool requestExistsByReference(string64 reference, uint64_t requestID = 0) = 0;
    virtual bool isReferenceExist(AccountID const& requestor, string64 reference, uint64_t requestID= 0) = 0;
};
}