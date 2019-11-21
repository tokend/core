#include "ledger/StorageHelperImpl.h"
#include "ledger/ExternalSystemAccountIDHelperImpl.h"
#include "ledger/ExternalSystemAccountIDPoolEntryHelperImpl.h"
#include "ledger/KeyValueHelperImpl.h"
#include "ledger/LedgerDeltaImpl.h"
#include "ledger/LicenseHelperImpl.h"
#include "ledger/StampHelperImpl.h"
#include "ledger/LicenseSignatureHelperImpl.h"
#include "ledger/LimitsV2HelperImpl.h"
#include "BalanceHelperImpl.h"
#include "AssetHelperImpl.h"
#include "AccountRuleHelperImpl.h"
#include "AccountRoleHelperImpl.h"
#include "AccountHelperImpl.h"
#include "SignerHelperImpl.h"
#include "SignerRuleHelperImpl.h"
#include "SignerRoleHelperImpl.h"
#include "VoteHelperImpl.h"
#include "PollHelperImpl.h"
#include "LicenseHelperImpl.h"
#include "StampHelperImpl.h"
#include "AccountSpecificRuleHelperImpl.h"
#include "ReviewableRequestHelperImpl.h"
#include "SwapHelperImpl.h"


namespace stellar
{

StorageHelperImpl::StorageHelperImpl(Database& db, LedgerDelta* ledgerDelta)
    : mDatabase(db)
    , mLedgerDelta(ledgerDelta)
    , mTransaction(nullptr)
    , mIsReleased(true)
{
    mHelpers =
    {
        {LedgerEntryType::ACCOUNT, &getAccountHelper()},
        {LedgerEntryType::ACCOUNT_ROLE, &getAccountRoleHelper()},
        {LedgerEntryType::ACCOUNT_RULE, &getAccountRuleHelper()},
        {LedgerEntryType::SIGNER, &getSignerHelper()},
        {LedgerEntryType::SIGNER_ROLE, &getSignerRoleHelper()},
        {LedgerEntryType::SIGNER_RULE, &getSignerRuleHelper()},
        {LedgerEntryType::KEY_VALUE, &getKeyValueHelper()},
        {LedgerEntryType::BALANCE, &getBalanceHelper()},
        {LedgerEntryType::ASSET, &getAssetHelper()},
        {LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY, &getExternalSystemAccountIDPoolEntryHelper()},
        {LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID, &getExternalSystemAccountIDHelper()},
        {LedgerEntryType::STAMP, &getStampHelper()},
        {LedgerEntryType::LICENSE, &getLicenseHelper()},
        {LedgerEntryType::VOTE, &getVoteHelper()},
        {LedgerEntryType::POLL, &getPollHelper()},
        {LedgerEntryType ::ACCOUNT_SPECIFIC_RULE, &getAccountSpecificRuleHelper()},
        {LedgerEntryType::REVIEWABLE_REQUEST,                    &getReviewableRequestHelper()},
        {LedgerEntryType::SWAP, &getSwapHelper()},


    };
}

StorageHelperImpl::~StorageHelperImpl()
{
    if (mTransaction)
    {
        try
        {
            mTransaction->rollback();
        }
        catch (...)
        {
        }
    }
}

Database&
StorageHelperImpl::getDatabase()
{
    return mDatabase;
}

const Database&
StorageHelperImpl::getDatabase() const
{
    return mDatabase;
}

LedgerDelta *
StorageHelperImpl::getLedgerDelta()
{
    return mLedgerDelta;
}

const LedgerDelta *
StorageHelperImpl::getLedgerDelta() const
{
    return mLedgerDelta;
}

LedgerDelta&
StorageHelperImpl::mustGetLedgerDelta()
{
    if (mLedgerDelta != nullptr)
    {
        return *mLedgerDelta;
    }

    throw std::runtime_error("Expected ledger delta to exists");
}

const LedgerDelta&
StorageHelperImpl::mustGetLedgerDelta() const
{
    if (mLedgerDelta != nullptr)
    {
        return *mLedgerDelta;
    }

    throw std::runtime_error("Expected ledger delta to exists");
}

void
StorageHelperImpl::begin()
{
    mIsReleased = false;
    mTransaction.reset();
    mTransaction = std::make_unique<soci::transaction>(mDatabase.getSession());
}

void
StorageHelperImpl::commit()
{
    if (mIsReleased)
    {
        throw std::runtime_error("Cannot commit a released StorageHelper.");
    }
    if (mLedgerDelta)
    {
        mLedgerDelta->commit();
    }
    if (mTransaction)
    {
        mTransaction->commit();
        mTransaction = nullptr;
        mIsReleased = true;
    }
}

void
StorageHelperImpl::rollback()
{
    if (mIsReleased)
    {
        throw std::runtime_error("Cannot rollback a released StorageHelper.");
    }
    if (mLedgerDelta)
    {
        mLedgerDelta->rollback();
    }
    if (mTransaction)
    {
        mTransaction->rollback();
        mTransaction = nullptr;
        mIsReleased = true;
    }
}

void
StorageHelperImpl::release()
{
    if (!mIsReleased)
    {
        mIsReleased = true;
        mTransaction->rollback();
        mTransaction = nullptr;
    }
}

std::unique_ptr<StorageHelper>
StorageHelperImpl::startNestedTransaction()
{
    if (!mLedgerDelta)
    {
        throw std::runtime_error(
            "This StorageHelper has empty ledger delta and "
            "cannot create nested transactions.");
    }
    if (mNestedDelta && mNestedDelta->isStateActive())
    {
        throw std::runtime_error("Invalid operation: this StorageHelper "
                                 "already has an active nested StorageHelper");
    }
    mNestedDelta = std::make_unique<LedgerDeltaImpl>(*mLedgerDelta);
    return std::make_unique<StorageHelperImpl>(mDatabase, mNestedDelta.get());
}

EntryHelper *
StorageHelperImpl::getHelper(LedgerEntryType type)
{
    return mHelpers[type];
}

std::vector<EntryHelper *>
StorageHelperImpl::getEntryHelpers()
{
    std::vector<EntryHelper *> result;
    for (auto& helper : mHelpers)
    {
        result.emplace_back(helper.second);
    }

    return result;
}

KeyValueHelper&
StorageHelperImpl::getKeyValueHelper()
{
    if (!mKeyValueHelper)
    {
        mKeyValueHelper = std::make_unique<KeyValueHelperImpl>(*this);
    }
    return *mKeyValueHelper;
}

BalanceHelper&
StorageHelperImpl::getBalanceHelper()
{
    if (!mBalanceHelper)
    {
        mBalanceHelper = std::make_unique<BalanceHelperImpl>(*this);
    }
    return *mBalanceHelper;
}

AssetHelper&
StorageHelperImpl::getAssetHelper()
{
    if (!mAssetHelper)
    {
        mAssetHelper = std::make_unique<AssetHelperImpl>(*this);
    }
    return *mAssetHelper;
}

ExternalSystemAccountIDHelper&
StorageHelperImpl::getExternalSystemAccountIDHelper()
{
    if (!mExternalSystemAccountIDHelper)
    {
        mExternalSystemAccountIDHelper =
            std::make_unique<ExternalSystemAccountIDHelperImpl>(*this);
    }
    return *mExternalSystemAccountIDHelper;
}

ExternalSystemAccountIDPoolEntryHelper&
StorageHelperImpl::getExternalSystemAccountIDPoolEntryHelper()
{
    if (!mExternalSystemAccountIDPoolEntryHelper)
    {
        mExternalSystemAccountIDPoolEntryHelper =
            std::make_unique<ExternalSystemAccountIDPoolEntryHelperImpl>(*this);
    }
    return *mExternalSystemAccountIDPoolEntryHelper;
}

AccountHelper&
StorageHelperImpl::getAccountHelper()
{
    if (!mAccountHelper)
    {
        mAccountHelper = std::make_unique<AccountHelperImpl>(*this);
    }
    return *mAccountHelper;
}

AccountRoleHelper&
StorageHelperImpl::getAccountRoleHelper()
{
    if (!mAccountRoleHelper)
    {
        mAccountRoleHelper = std::make_unique<AccountRoleHelperImpl>(*this);
    }
    return *mAccountRoleHelper;
}

AccountRuleHelper&
StorageHelperImpl::getAccountRuleHelper()
{
    if (!mAccountRuleHelper)
    {
        mAccountRuleHelper = std::make_unique<AccountRuleHelperImpl>(*this);
    }
    return *mAccountRuleHelper;
}

SignerHelper&
StorageHelperImpl::getSignerHelper()
{
    if (!mSignerHelper)
    {
        mSignerHelper = std::make_unique<SignerHelperImpl>(*this);
    }
    return *mSignerHelper;
}

SignerRuleHelper&
StorageHelperImpl::getSignerRuleHelper()
{
    if (!mSignerRuleHelper)
    {
        mSignerRuleHelper = std::make_unique<SignerRuleHelperImpl>(*this);
    }
    return *mSignerRuleHelper;
}

SignerRoleHelper&
StorageHelperImpl::getSignerRoleHelper()
{
    if (!mSignerRoleHelper)
    {
        mSignerRoleHelper = std::make_unique<SignerRoleHelperImpl>(*this);
    }
    return *mSignerRoleHelper;
}

LicenseHelper&
StorageHelperImpl::getLicenseHelper()
{
    if (!mLicenseHelper)
    {
        mLicenseHelper = std::make_unique<LicenseHelperImpl>(*this);
    }
    return *mLicenseHelper;
}

LicenseSignatureHelper&
StorageHelperImpl::getLicenseSignatureHelper()
{
    if (!mLicenseSignatureHelper)
    {
        mLicenseSignatureHelper =
            std::make_unique<LicenseSignatureHelperImpl>(*this);
    }
    return *mLicenseSignatureHelper;
}

StampHelper&
StorageHelperImpl::getStampHelper()
{
    if (!mStampHelper)
    {
        mStampHelper = std::make_unique<StampHelperImpl>(*this);
    }
    return *mStampHelper;
}

VoteHelper&
StorageHelperImpl::getVoteHelper()
{
    if (!mVoteHelper)
    {
        mVoteHelper = std::make_unique<VoteHelperImpl>(*this);
    }
    return *mVoteHelper;
}

PollHelper&
StorageHelperImpl::getPollHelper()
{
    if (!mPollHelper)
    {
        mPollHelper = std::make_unique<PollHelperImpl>(*this);
    }
    return *mPollHelper;
}

SwapHelper&
StorageHelperImpl::getSwapHelper()
{
    if (!mSwapHelper)
    {
        mSwapHelper = std::make_unique<SwapHelperImpl>(*this);
    }
    return *mSwapHelper;
}

AccountSpecificRuleHelper&
StorageHelperImpl::getAccountSpecificRuleHelper()
{
    if (!mAccountSpecificRuleHelper)
    {
        mAccountSpecificRuleHelper =
            std::make_unique<AccountSpecificRuleHelperImpl>(*this);
    }
    return *mAccountSpecificRuleHelper;
}

ReviewableRequestHelper&
StorageHelperImpl::getReviewableRequestHelper()
{
    if (!mReviewableRequestHelper)
    {
        mReviewableRequestHelper = std::make_unique<ReviewableRequestHelperImpl>(*this);
    }

    return *mReviewableRequestHelper;
}

LimitsV2Helper&
StorageHelperImpl::getLimitsV2Helper()
{
    if(!mLimitsV2Helper)
    {
        mLimitsV2Helper = std::make_unique<LimitsV2HelperImpl>(*this);
    }

    return *mLimitsV2Helper;
}

} // namespace stellar