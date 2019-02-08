#pragma once

#include <memory>
#include <vector>

namespace stellar
{
class Database;
class LedgerDelta;
class KeyValueHelper;
class BalanceHelper;
class AssetHelper;
class ExternalSystemAccountIDHelper;
class ExternalSystemAccountIDPoolEntryHelper;
class EntryHelper;
class AccountHelper;
class AccountRoleHelper;
class AccountRuleHelper;
class SignerHelper;
class SignerRuleHelper;
class SignerRoleHelper;

class StorageHelper
{
  public:
    virtual ~StorageHelper()
    {
    }

    virtual Database& getDatabase() = 0;
    virtual const Database& getDatabase() const = 0;
    virtual LedgerDelta* getLedgerDelta() = 0;
    virtual const LedgerDelta* getLedgerDelta() const = 0;
    virtual LedgerDelta& mustGetLedgerDelta() = 0;
    virtual const LedgerDelta& mustGetLedgerDelta() const = 0;

    virtual void commit() = 0;
    virtual void rollback() = 0;
    virtual void release() = 0;
    virtual void begin() = 0;

    virtual std::unique_ptr<StorageHelper> startNestedTransaction() = 0;

    virtual std::vector<EntryHelper*> getEntryHelpers() = 0;

    virtual KeyValueHelper& getKeyValueHelper() = 0;
    virtual BalanceHelper& getBalanceHelper() = 0;
    virtual AssetHelper& getAssetHelper() = 0;
    virtual ExternalSystemAccountIDHelper&
    getExternalSystemAccountIDHelper() = 0;
    virtual ExternalSystemAccountIDPoolEntryHelper&
    getExternalSystemAccountIDPoolEntryHelper() = 0;
    virtual AccountHelper& getAccountHelper() = 0;
    virtual AccountRoleHelper& getAccountRoleHelper() = 0;
    virtual AccountRuleHelper& getAccountRuleHelper() = 0;
    virtual SignerHelper& getSignerHelper() = 0;
    virtual SignerRuleHelper& getSignerRuleHelper() = 0;
    virtual SignerRoleHelper& getSignerRoleHelper() = 0;
};
} // namespace stellar