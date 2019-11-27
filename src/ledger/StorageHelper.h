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
enum class LedgerEntryType;
class LicenseHelper;
class LicenseSignatureHelper;
class StampHelper;
class VoteHelper;
class PollHelper;
class AccountSpecificRuleHelper;
class ReviewableRequestHelper;
class SwapHelper;
class LimitsV2Helper;
class AccountKYCHelper;
class AssetPairHelper;
class AtomicSwapAskHelper;
class ContractHelper;
class FeeHelper;
class OfferHelper;

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

    virtual EntryHelper* getHelper(LedgerEntryType type) = 0;
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
    virtual LicenseHelper& getLicenseHelper() = 0;
    virtual LicenseSignatureHelper& getLicenseSignatureHelper() = 0;
    virtual StampHelper& getStampHelper() = 0;
    virtual VoteHelper& getVoteHelper() = 0;
    virtual PollHelper& getPollHelper() = 0;
    virtual AccountSpecificRuleHelper& getAccountSpecificRuleHelper() = 0;
    virtual ReviewableRequestHelper& getReviewableRequestHelper() = 0;
    virtual SwapHelper& getSwapHelper() = 0;
    virtual LimitsV2Helper& getLimitsV2Helper() = 0;
    virtual AccountKYCHelper& getAccountKYCHelper() = 0;
    virtual AssetPairHelper& getAssetPairHelper() = 0;
    virtual AtomicSwapAskHelper& getAtomicSwapAskHelper() = 0;
    virtual ContractHelper& getContractHelper() = 0;
    virtual FeeHelper& getFeeHelper() = 0;
    virtual OfferHelper& getOfferHelper() = 0;

};
} // namespace stellar