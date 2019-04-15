#pragma once

#include "ledger/VoteHelper.h"

namespace stellar {

class MockVoteHelper : public VoteHelper {
 public:
  MOCK_METHOD2(loadVote,
      VoteFrame::pointer(uint64_t pollID, AccountID voterID));
  MOCK_METHOD2(exists,
      bool(uint64_t pollID, AccountID voterID));
  MOCK_METHOD1(deleteForPoll,
      void(uint64_t pollID));
};

}  // namespace stellar
