#pragma once

#include "ReviewableRequestHelper.h"
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
class StorageHelper;

class ReviewableRequestHelperImpl : public ReviewableRequestHelper, NonCopyable {
public:
    ReviewableRequestHelperImpl(StorageHelper& storageHelper);

private:
    StorageHelper& mStorageHelper;

    void storeUpdateHelper(bool insert, LedgerEntry const& entry);

    std::string obtainSqlRequestIDsString(std::vector<uint64_t> requestIDs);

    void dropAll() override;
    void storeAdd(LedgerEntry const& entry) override;
    void storeChange(LedgerEntry const& entry) override;
    void storeDelete(LedgerKey const& key) override;
    bool exists(LedgerKey const& key) override;
    LedgerKey getLedgerKey(LedgerEntry const& from) override;
    EntryFrame::pointer storeLoad(LedgerKey const& key) override;
    EntryFrame::pointer fromXDR(LedgerEntry const& from) override;
    uint64_t countObjects() override;
    void loadRequests(StatementContext& prep, std::function<void(const LedgerEntry&)> requestsProcessor) override;
    ReviewableRequestFrame::pointer loadRequest(uint64 requestID) override;
    ReviewableRequestFrame::pointer loadRequest(AccountID& requestor, string64 reference) override;
    ReviewableRequestFrame::pointer loadRequest(uint64 requestID, AccountID requestor) override;
    ReviewableRequestFrame::pointer
    loadRequest(uint64 requestID, AccountID requestor, ReviewableRequestType requestType) override;
    std::vector<ReviewableRequestFrame::pointer>
    loadRequests(AccountID const& requestor, ReviewableRequestType requestType) override;
    std::vector<ReviewableRequestFrame::pointer> loadRequests(std::vector<uint64_t> requestIDs) override;
    bool exists(AccountID const& requestor, string64 reference, uint64_t requestID) override;
    bool isReferenceExist(AccountID const& requestor, string64 reference, uint64_t requestID) override;
    Database& getDatabase() override;
    LedgerDelta *getLedgerDelta() override;
};
}
