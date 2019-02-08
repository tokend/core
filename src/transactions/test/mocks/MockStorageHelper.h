#pragma once

#include "ledger/StorageHelper.h"

namespace stellar
{
class KeyValueHelper;
class AccountHelper;
class AssetHelper;
class BalanceHelper;
class AccountRuleHelper;
class AccountRoleHelper;
class ExternalSystemAccountIDHelper;
class ExternalSystemAccountIDPoolEntryHelper;

class MockStorageHelper : public StorageHelper
{
public:
    MOCK_METHOD0(getDatabase, Database&());
    MOCK_CONST_METHOD0(getDatabase, const Database&());
    MOCK_METHOD0(getLedgerDelta, LedgerDelta*());
    MOCK_CONST_METHOD0(getLedgerDelta, const LedgerDelta*());
    MOCK_METHOD0(mustGetLedgerDelta, LedgerDelta&());
    MOCK_CONST_METHOD0(mustGetLedgerDelta, const LedgerDelta&());
    MOCK_METHOD0(commit, void());
    MOCK_METHOD0(rollback, void());
    MOCK_METHOD0(release, void());
    MOCK_METHOD0(begin, void());
    MOCK_METHOD0(startNestedTransaction, std::unique_ptr<StorageHelper>());
    MOCK_METHOD0(getKeyValueHelper, KeyValueHelper&());
    MOCK_METHOD0(getBalanceHelper, BalanceHelper&());
    MOCK_METHOD0(getAssetHelper, AssetHelper&());
    MOCK_METHOD0(getExternalSystemAccountIDHelper,
                 ExternalSystemAccountIDHelper&());
    MOCK_METHOD0(getExternalSystemAccountIDPoolEntryHelper,
                 ExternalSystemAccountIDPoolEntryHelper&());
    MOCK_METHOD0(getAccountHelper, AccountHelper&());
    MOCK_METHOD0(getAccountRoleHelper, AccountRoleHelper&());
    MOCK_METHOD0(getAccountRuleHelper, AccountRuleHelper&());
    MOCK_METHOD0(getSignerHelper, SignerHelper&());
    MOCK_METHOD0(getSignerRuleHelper, SignerRuleHelper&());
    MOCK_METHOD0(getSignerRoleHelper, SignerRoleHelper&());
    MOCK_METHOD0(getEntryHelpers, std::vector<EntryHelper*>());

};

}  // namespace stellar
