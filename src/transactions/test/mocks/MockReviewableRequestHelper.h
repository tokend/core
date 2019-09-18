#include "ledger/ReviewableRequestHelper.h"

namespace stellar
{

class MockReviewableRequestHelper : public ReviewableRequestHelper {
public:
    MOCK_METHOD0(dropAll,
                 void());

    MOCK_METHOD1(storeAdd,
                 void(LedgerEntry const& entry));

    MOCK_METHOD1(storeChange,
                 void(LedgerEntry const& entry));

    MOCK_METHOD1(storeDelete,
                 void(LedgerKey const& key));

    MOCK_METHOD1(exists,
                 bool(LedgerKey const& key));

    MOCK_METHOD1(getLedgerKey,
                 LedgerKey(LedgerEntry const& from));

    MOCK_METHOD1(storeLoad,
                 EntryFrame::pointer(LedgerKey const& key));

    MOCK_METHOD1(fromXDR,
                 EntryFrame::pointer(LedgerEntry const& from));

    MOCK_METHOD0(countObjects,
                 uint64_t());

    MOCK_METHOD2(loadRequests,
                 void(StatementContext
                     &prep, std::function<void(LedgerEntry const&)>
                     requestsProcessor));

    MOCK_METHOD1(loadRequest,
                 ReviewableRequestFrame::pointer(uint64
                     requestID));

    MOCK_METHOD2(loadRequest,
                 ReviewableRequestFrame::pointer(AccountID & requestor, string64
                     reference));

    MOCK_METHOD2(loadRequest,
                 ReviewableRequestFrame::pointer(uint64
                     requestID, AccountID
                     requestor));

    MOCK_METHOD3(loadRequest,
                 ReviewableRequestFrame::pointer(uint64
                     requestID, AccountID
                     requestor, ReviewableRequestType
                     requestType));

    MOCK_METHOD2(loadRequests,
                 std::vector<ReviewableRequestFrame::pointer>(AccountID const& requestor, ReviewableRequestType requestType));

    MOCK_METHOD1(loadRequests,
                 std::vector<ReviewableRequestFrame::pointer>(std::vector<uint64_t>
                     requestIDs));

    MOCK_METHOD3(exists,
                 bool(AccountID, string64, uint64_t));

    MOCK_METHOD3(isReferenceExist,
                 bool(AccountID, string64, uint64_t));
};

}  // namespace stellar
