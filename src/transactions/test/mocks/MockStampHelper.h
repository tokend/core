#include "ledger/StampHelper.h"

namespace stellar {

class MockStampHelper : public StampHelper {
 public:
    MOCK_CONST_METHOD0(getTableName, const std::string());
  MOCK_METHOD0(clearAll,
      void());
  MOCK_METHOD0(dropAll,
      void());
  MOCK_METHOD0(countObjects,
      uint64_t());
  MOCK_METHOD1(exists,
      bool(LedgerKey const &key));
  MOCK_METHOD2(exists,
      bool(Hash ledgerHash, Hash licenseHash));
  MOCK_METHOD1(getLedgerKey,
      LedgerKey(LedgerEntry const &from));
  MOCK_METHOD1(fromXDR,
      EntryFrame::pointer(LedgerEntry const &from));
  MOCK_METHOD0(getDatabase,
      Database&());
  MOCK_METHOD1(storeAdd,
      void(LedgerEntry const &entry));
  MOCK_METHOD1(storeChange,
      void(LedgerEntry const& entry));
  MOCK_METHOD1(storeLoad,
      void(LedgerEntry const& entry));
  MOCK_METHOD1(storeDelete,
      void(LedgerEntry const& entry));
};

}  // namespace stellar
