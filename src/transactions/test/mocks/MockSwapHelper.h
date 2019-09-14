#include "ledger/SwapHelper.h"

namespace stellar {

class MockSwapHelper : public SwapHelper {
 public:
  MOCK_METHOD1(exists,
      bool(uint64_t id));
  MOCK_METHOD1(loadSwap,
      SwapFrame::pointer(uint64_t swapID));
  MOCK_METHOD1(mustLoadSwap,
      SwapFrame::pointer(uint64_t swapID));
};

}  // namespace stellar
