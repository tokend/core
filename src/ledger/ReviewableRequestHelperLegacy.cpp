#include "ReviewableRequestHelperLegacy.h"
#include "xdrpp/marshal.h"
#include "xdrpp/printer.h"
#include "StorageHelperImpl.h"
#include "ReviewableRequestHelper.h"

using namespace soci;
using namespace std;

namespace stellar
{

void ReviewableRequestHelperLegacy::dropAll(Database& db)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, nullptr));
    storageHelper->release();
    storageHelper->getReviewableRequestHelper().dropAll();
}

void ReviewableRequestHelperLegacy::storeAdd(LedgerDelta& delta, Database& db, LedgerEntry const& entry)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, &delta));
    storageHelper->release();
    storageHelper->getReviewableRequestHelper().storeAdd(entry);
}

void ReviewableRequestHelperLegacy::storeChange(LedgerDelta& delta, Database& db, LedgerEntry const& entry)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, &delta));
    storageHelper->release();
    storageHelper->getReviewableRequestHelper().storeChange(entry);
}

void ReviewableRequestHelperLegacy::storeDelete(LedgerDelta& delta, Database& db, LedgerKey const& key)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, &delta));
    storageHelper->release();
    storageHelper->getReviewableRequestHelper().storeDelete(key);
}

bool ReviewableRequestHelperLegacy::exists(Database& db, LedgerKey const& key)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, nullptr));
    storageHelper->release();
    return storageHelper->getReviewableRequestHelper().exists(key);
}

LedgerKey ReviewableRequestHelperLegacy::getLedgerKey(LedgerEntry const& from)
{
    LedgerKey ledgerKey;
    ledgerKey.type(from.data.type());
    ledgerKey.reviewableRequest().requestID = from.data.reviewableRequest().requestID;
    return ledgerKey;
}

EntryFrame::pointer ReviewableRequestHelperLegacy::fromXDR(LedgerEntry const& from)
{
    return std::make_shared<ReviewableRequestFrame>(from);
}

uint64_t ReviewableRequestHelperLegacy::countObjects(soci::session& sess)
{
    uint64_t count = 0;
    sess << "SELECT COUNT(*) FROM reviewable_request;", into(count);
    return count;
}

bool
ReviewableRequestHelperLegacy::exists(Database& db, AccountID const& rawRequestor, stellar::string64 reference, uint64_t requestID)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, nullptr));
    storageHelper->release();
    return storageHelper->getReviewableRequestHelper().exists(rawRequestor, reference, requestID);
}

bool
ReviewableRequestHelperLegacy::isReferenceExist(Database& db, AccountID const& requestor, string64 reference, const uint64_t requestID)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, nullptr));
    storageHelper->release();
    return storageHelper->getReviewableRequestHelper().isReferenceExist(requestor, reference, requestID);
}

ReviewableRequestFrame::pointer
ReviewableRequestHelperLegacy::loadRequest(uint64 requestID, Database& db, LedgerDelta *delta)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, delta));
    storageHelper->release();
    return storageHelper->getReviewableRequestHelper().loadRequest(requestID);
}

ReviewableRequestFrame::pointer
ReviewableRequestHelperLegacy::loadRequest(uint64 requestID, AccountID requestor, ReviewableRequestType requestType,
                                           Database& db, LedgerDelta *delta)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, delta));
    storageHelper->release();
    return storageHelper->getReviewableRequestHelper().loadRequest(requestID, requestor, requestType);
}

vector<ReviewableRequestFrame::pointer> ReviewableRequestHelperLegacy::
loadRequests(AccountID const& rawRequestor, ReviewableRequestType requestType,
             Database& db)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, nullptr));
    storageHelper->release();
    return storageHelper->getReviewableRequestHelper().loadRequests(rawRequestor, requestType);
}

vector<ReviewableRequestFrame::pointer>
ReviewableRequestHelperLegacy::loadRequests(std::vector<uint64_t> requestIDs, Database& db)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, nullptr));
    storageHelper->release();
    return storageHelper->getReviewableRequestHelper().loadRequests(requestIDs);
}

ReviewableRequestFrame::pointer
ReviewableRequestHelperLegacy::loadRequest(uint64 requestID, AccountID requestor, Database& db, LedgerDelta *delta)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, delta));
    storageHelper->release();
    storageHelper->getReviewableRequestHelper().loadRequest(requestID, requestor);
}

EntryFrame::pointer ReviewableRequestHelperLegacy::storeLoad(LedgerKey const& key, Database& db)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, nullptr));
    storageHelper->release();
    return storageHelper->getReviewableRequestHelper().storeLoad(key);
}

ReviewableRequestFrame::pointer
ReviewableRequestHelperLegacy::loadRequest(AccountID& rawRequestor, string64 reference, Database& db, LedgerDelta *delta)
{

    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, delta));
    storageHelper->release();
    return storageHelper->getReviewableRequestHelper().loadRequest(rawRequestor, reference);
}
}
