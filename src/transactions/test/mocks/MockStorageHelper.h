#pragma once

#include "ledger/StorageHelper.h"
#include "ledger/KeyValueHelper.h"
#include "ledger/ExternalSystemAccountIDHelper.h"
#include "ledger/ExternalSystemAccountIDPoolEntryHelper.h"
#include "ledger/AccountRoleHelper.h"
#include "ledger/AccountRolePermissionHelperImpl.h"
#include "ledger/StampHelper.h"
#include "ledger/LicenseHelper.h"
#include "ledger/LicenseSignatureHelper.h"

namespace stellar {

class MockStorageHelper : public StorageHelper {
 public:
  MOCK_METHOD0(getDatabase,
      Database&());
  MOCK_CONST_METHOD0(getDatabase,
      const Database&());
  MOCK_METHOD0(getLedgerDelta,
      LedgerDelta*());
  MOCK_CONST_METHOD0(getLedgerDelta,
      const LedgerDelta*());
  MOCK_METHOD0(commit,
      void());
  MOCK_METHOD0(rollback,
      void());
  MOCK_METHOD0(release,
      void());
  MOCK_METHOD0(begin,
      void());
  MOCK_METHOD0(startNestedTransaction,
      std::unique_ptr<StorageHelper>());
  MOCK_METHOD0(getKeyValueHelper,
      KeyValueHelper&());
  MOCK_METHOD0(getBalanceHelper,
      BalanceHelper&());
  MOCK_METHOD0(getAssetHelper,
      AssetHelper&());
  MOCK_METHOD0(getExternalSystemAccountIDHelper,
      ExternalSystemAccountIDHelper&());
  MOCK_METHOD0(getExternalSystemAccountIDPoolEntryHelper,
      ExternalSystemAccountIDPoolEntryHelper&());
  MOCK_METHOD0(getAccountRoleHelper,
      EntryHelper&());
  MOCK_METHOD0(getAccountRolePermissionHelper,
      AccountRolePermissionHelper&());
  MOCK_METHOD0(getLicenseHelper,
      LicenseHelper&());
  MOCK_METHOD0(getLicenseSignatureHelper,
      LicenseSignatureHelper&());
  MOCK_METHOD0(getStampHelper,
      StampHelper&());
};

}  // namespace stellar
