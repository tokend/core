%#include "xdr/Stellar-types.h"

namespace stellar
{

//: Actions that can be applied to a poll
enum ManagePollAction
{
    CLOSE = 0
//    UPDATE_END_TIME = 1,
//    REMOVE = 2,
};


//: PollResult is used to specify result of voting
enum PollResult
{
    PASSED = 0,
    FAILED = 1
};

//: ClosePollData is used to submit poll results
struct ClosePollData
{
    //: result of voting
    PollResult result;

    //: Arbitrary stringified json object with details about the result
    longstring details;

    //: Reserved for future use
    union switch (LedgerVersion v)
    {
    case EMPTY_VERSION:
        void;
    }
    ext;
};

struct UpdatePollEndTimeData
{
    uint64 newEndTime;

    //: reserved for future use
    union switch (LedgerVersion v)
    {
    case EMPTY_VERSION:
        void;
    }
    ext;
};

//: ManagePollOp is used to close (in future: update end time or remove) the poll
struct ManagePollOp
{
    //: ID of poll to manage
    uint64 pollID;

    //: data is used to pass one of `ManagePollAction` with required params
    union switch (ManagePollAction action)
    {
    case CLOSE:
        ClosePollData closePollData;
//    case UPDATE_END_TIME:
//        UpdatePollEndTimeData updateTimeData;
//    case REMOVE:
//        EmptyExt ext;
    }
    data;

    //: reserved for future use
    union switch (LedgerVersion v)
    {
    case EMPTY_VERSION:
        void;
    }
    ext;
};

//: Result codes of ManagePollOp
enum ManagePollResultCode
{
    //: Specified action in `data` of ManagePollOp was successfully executed
    SUCCESS = 0,

    // codes considered as "failure" for the operation
    //: There is no poll with such id
    NOT_FOUND = -1,
    //: Not allowed to close poll which
    POLL_NOT_READY = -2,
    //: Only result provider is allowed to close poll
    NOT_AUTHORIZED_TO_CLOSE_POLL = -3
};

//: Result of operation application
union ManagePollResult switch (ManagePollResultCode code)
{
case SUCCESS:
    EmptyExt ext;
default:
    void;
};

}
