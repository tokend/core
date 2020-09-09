#pragma once

#include "ledger/StorageHelper.h"
#include "ledger/EntryHelper.h"
#include <unordered_map>
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
class EntryHelper;
class AccountRoleHelper;
class AccountRuleHelper;
class LicenseHelper;
class LicenseSignatureHelper;
class StampHelper;
class VoteHelper;
class PollHelper;
class ReviewableRequestHelper;
class SwapHelper;
class LimitsV2Helper;
class AccountKYCHelper;
class AssetPairHelper;
class AtomicSwapAskHelper;
class ContractHelper;
class FeeHelper;
class OfferHelper;
class ReferenceHelper;
class SaleHelper;
class PendingStatisticsHelper;
class StatisticsV2Helper;
class DataHelper;
class DeferredPaymentHelper;

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
    LimitsV2Helper& getLimitsV2Helper() override;
    AccountKYCHelper& getAccountKYCHelper() override;
    AssetPairHelper& getAssetPairHelper() override;
    AtomicSwapAskHelper& getAtomicSwapAskHelper() override;
    ContractHelper& getContractHelper() override;
    FeeHelper& getFeeHelper() override;
    OfferHelper& getOfferHelper() override;
    ReferenceHelper& getReferenceHelper() override;
    SaleHelper& getSaleHelper() override;
    PendingStatisticsHelper& getPendingStatisticsHelper() override;
    StatisticsV2Helper& getStatisticsV2Helper() override;
    DataHelper& getDataHelper() override;
    DeferredPaymentHelper& getDeferredPaymentHelper() override;

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
    std::unique_ptr<LimitsV2Helper> mLimitsV2Helper;
    std::unique_ptr<AccountKYCHelper> mAccountKYCHelper;
    std::unique_ptr<AssetPairHelper> mAssetPairHelper;
    std::unique_ptr<AtomicSwapAskHelper> mAtomicSwapAskHelper;
    std::unique_ptr<ContractHelper> mContractHelper;
    std::unique_ptr<FeeHelper> mFeeHelper;
    std::unique_ptr<OfferHelper> mOfferHelper;
    std::unique_ptr<ReferenceHelper> mReferenceHelper;
    std::unique_ptr<SaleHelper> mSaleHelper;
    std::unique_ptr<PendingStatisticsHelper> mPendingStatisticsHelper;
    std::unique_ptr<StatisticsV2Helper> mStatisticsV2Helper;
    std::unique_ptr<DataHelper> mDataHelper;
    std::unique_ptr<DeferredPaymentHelper> mDeferredPaymentHelper;
};
} // namespace stellar
