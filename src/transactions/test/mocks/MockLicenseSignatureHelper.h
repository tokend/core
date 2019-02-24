#include "ledger/LicenseSignatureHelper.h"

namespace stellar {

class MockLicenseSignatureHelper : public LicenseSignatureHelper {
 public:
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
  MOCK_METHOD1(fromXDR,
      EntryFrame::pointer(LedgerEntry const& from));
  MOCK_METHOD1(storeLoad,
      EntryFrame::pointer(LedgerKey const& ledgerKey));
  MOCK_METHOD0(getDatabase,
      Database&());
  MOCK_METHOD3(storeAdd,
      void(std::string licenseHash, uint8_t ID, DecoratedSignature sig));
  MOCK_METHOD1(loadSignatures,
      xdr::xvector<DecoratedSignature>(std::string licenseHash));
  MOCK_METHOD0(dropAll,
      void());
  MOCK_METHOD2(loadSignatures,
      void(StatementContext& prep, std::function<void(DecoratedSignature const&)> processor));
  MOCK_METHOD0(countObjects,
      uint64_t());
};

}  // namespace stellar
