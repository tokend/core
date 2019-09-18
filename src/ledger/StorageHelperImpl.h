#pragma once

#include "ledger/StorageHelper.h"
#include "BalanceHelperLegacy.h"
#include <memory>

namespace soci
{
class transaction;
}

namespace stellar
{

class KeyValueHelper;
class BalanceHelper;
class AssetHelper;
class ExternalSystemAccountIDHelper;
class ExternalSystemAccountIDPoolEntryHelper;
class AccountRoleHelper;
class AccountRuleHelper;
class LicenseHelper;
class LicenseSignatureHelper;
class StampHelper;
class VoteHelper;
class PollHelper;
class ReviewableRequestHelper;
class SwapHelper;


class StorageHelperImpl : public StorageHelper {
public:
    StorageHelperImpl(Database& db, LedgerDelta *ledgerDelta);

    virtual ~StorageHelperImpl();

private:
    virtual Database& getDatabase();
    virtual const Database& getDatabase() const;
    virtual LedgerDelta *getLedgerDelta();
    virtual const LedgerDelta *getLedgerDelta() const;
    LedgerDelta& mustGetLedgerDelta() override;
    const LedgerDelta& mustGetLedgerDelta() const override;

    virtual void commit();
    virtual void rollback();
    virtual void release();
    virtual void begin();

    virtual std::unique_ptr<StorageHelper> startNestedTransaction();

    std::vector<EntryHelper *> getEntryHelpers() override;
    EntryHelper *getHelper(LedgerEntryType type) override;

    KeyValueHelper& getKeyValueHelper() override;
    BalanceHelper& getBalanceHelper() override;
    AssetHelper& getAssetHelper() override;
    ExternalSystemAccountIDHelper& getExternalSystemAccountIDHelper() override;
    ExternalSystemAccountIDPoolEntryHelper&
    getExternalSystemAccountIDPoolEntryHelper() override;
    AccountHelper& getAccountHelper() override;
    AccountRoleHelper& getAccountRoleHelper() override;
    AccountRuleHelper& getAccountRuleHelper() override;
    SignerHelper& getSignerHelper() override;
    SignerRuleHelper& getSignerRuleHelper() override;
    SignerRoleHelper& getSignerRoleHelper() override;
    LicenseHelper& getLicenseHelper() override;
    LicenseSignatureHelper& getLicenseSignatureHelper() override;
    StampHelper& getStampHelper() override;
    VoteHelper& getVoteHelper() override;
    PollHelper& getPollHelper() override;
    AccountSpecificRuleHelper& getAccountSpecificRuleHelper() override;
    ReviewableRequestHelper& getReviewableRequestHelper() override;
    SwapHelper& getSwapHelper() override;

    Database& mDatabase;
    LedgerDelta *mLedgerDelta;
    bool mIsReleased = true;
    std::unique_ptr<LedgerDelta> mNestedDelta;
    std::unique_ptr<soci::transaction> mTransaction;

    std::unique_ptr<KeyValueHelper> mKeyValueHelper;
    std::unique_ptr<BalanceHelper> mBalanceHelper;
    std::unique_ptr<AssetHelper> mAssetHelper;
    std::unique_ptr<ExternalSystemAccountIDHelper>
        mExternalSystemAccountIDHelper;
    std::unique_ptr<ExternalSystemAccountIDPoolEntryHelper>
        mExternalSystemAccountIDPoolEntryHelper;
    std::unique_ptr<AccountHelper> mAccountHelper;
    std::unique_ptr<AccountRoleHelper> mAccountRoleHelper;
    std::unique_ptr<AccountRuleHelper> mAccountRuleHelper;
    std::unique_ptr<SignerHelper> mSignerHelper;
    std::unique_ptr<SignerRuleHelper> mSignerRuleHelper;
    std::unique_ptr<SignerRoleHelper> mSignerRoleHelper;

    std::map<LedgerEntryType, EntryHelper *> mHelpers;
    std::unique_ptr<LicenseHelper> mLicenseHelper;
    std::unique_ptr<LicenseSignatureHelper> mLicenseSignatureHelper;
    std::unique_ptr<StampHelper> mStampHelper;
    std::unique_ptr<VoteHelper> mVoteHelper;
    std::unique_ptr<PollHelper> mPollHelper;
    std::unique_ptr<AccountSpecificRuleHelper> mAccountSpecificRuleHelper;
    std::unique_ptr<ReviewableRequestHelper> mReviewableRequestHelper;
    std::unique_ptr<SwapHelper> mSwapHelper;
};
} // namespace stellar
