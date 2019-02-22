#include "ledger/LicenseHelper.h"

namespace stellar {

class MockLicenseHelper : public LicenseHelper {
 public:
  MOCK_METHOD1(getLedgerKey,
      LedgerKey(LedgerEntry const &from));
  MOCK_METHOD1(fromXDR,
      EntryFrame::pointer(LedgerEntry const &from));
  MOCK_METHOD0(getDatabase,
      Database&());
  MOCK_METHOD1(exists,
      bool(LedgerKey const &key));
  MOCK_METHOD1(storeAdd,
      void(LedgerEntry const &entry));
  MOCK_METHOD1(storeDelete,
      void(LedgerKey const &key));
  MOCK_METHOD1(storeLoad,
      EntryFrame::pointer(LedgerKey const &ledgerKey));
  MOCK_METHOD0(loadCurrentLicense,
      EntryFrame::pointer());
  MOCK_METHOD1(getAllowedAdmins,
      uint64_t(Application& app));
  MOCK_METHOD0(countObjects,
      uint64_t());
  MOCK_METHOD1(loadLicense,
      EntryFrame::pointer(LedgerKey const &key));
  MOCK_METHOD0(dropAll,
      void());
};

}  // namespace stellar
