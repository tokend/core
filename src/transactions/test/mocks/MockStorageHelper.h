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
class StampHelper;
class LicenseHelper;
class LicenseSignatureHelper;
class PollHelper;
class VoteHelper;
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
class ReferenceHelper;
class SaleHelper;
class PendingStatisticsHelper;
class StatisticsV2Helper;
class DataHelper;
class DeferredPaymentHelper;
class LiquidityPoolHelper;

enum class LedgerEntryType;

class MockStorageHelper : public StorageHelper {
public:
    MOCK_METHOD0(getDatabase, Database & ());
    MOCK_CONST_METHOD0(getDatabase, const Database&());
    MOCK_METHOD0(getLedgerDelta, LedgerDelta*());
    MOCK_CONST_METHOD0(getLedgerDelta, const LedgerDelta*());
    MOCK_METHOD0(mustGetLedgerDelta, LedgerDelta & ());
    MOCK_CONST_METHOD0(mustGetLedgerDelta, const LedgerDelta&());
    MOCK_METHOD0(commit, void());
    MOCK_METHOD0(rollback, void());
    MOCK_METHOD0(release, void());
    MOCK_METHOD0(begin, void());
    MOCK_METHOD0(startNestedTransaction, std::unique_ptr<StorageHelper>());
    MOCK_METHOD0(getKeyValueHelper, KeyValueHelper & ());
    MOCK_METHOD0(getBalanceHelper, BalanceHelper & ());
    MOCK_METHOD0(getAssetHelper, AssetHelper & ());
    MOCK_METHOD0(getExternalSystemAccountIDHelper,
                 ExternalSystemAccountIDHelper & ());
    MOCK_METHOD0(getExternalSystemAccountIDPoolEntryHelper,
                 ExternalSystemAccountIDPoolEntryHelper & ());
    MOCK_METHOD0(getAccountHelper, AccountHelper & ());
    MOCK_METHOD0(getAccountRoleHelper, AccountRoleHelper & ());
    MOCK_METHOD0(getAccountRuleHelper, AccountRuleHelper & ());
    MOCK_METHOD0(getSignerHelper, SignerHelper & ());
    MOCK_METHOD0(getSignerRuleHelper, SignerRuleHelper & ());
    MOCK_METHOD0(getSignerRoleHelper, SignerRoleHelper & ());
    MOCK_METHOD0(getEntryHelpers, std::vector<EntryHelper *>());
    MOCK_METHOD1(getHelper, EntryHelper *(LedgerEntryType
        type));
    MOCK_METHOD0(getLicenseHelper,
                 LicenseHelper & ());
    MOCK_METHOD0(getLicenseSignatureHelper,
                 LicenseSignatureHelper & ());
    MOCK_METHOD0(getStampHelper,
                 StampHelper & ());
    MOCK_METHOD0(getVoteHelper,
                 VoteHelper & ());
    MOCK_METHOD0(getPollHelper,
                 PollHelper&());
    MOCK_METHOD0(getAccountSpecificRuleHelper, AccountSpecificRuleHelper&());
    MOCK_METHOD0(getReviewableRequestHelper, ReviewableRequestHelper & ());
    MOCK_METHOD0(getSwapHelper, SwapHelper&());
    MOCK_METHOD0(getLimitsV2Helper, LimitsV2Helper&());
    MOCK_METHOD0(getAccountKYCHelper, AccountKYCHelper&());
    MOCK_METHOD0(getAssetPairHelper, AssetPairHelper&());
    MOCK_METHOD0(getAtomicSwapAskHelper, AtomicSwapAskHelper&());
    MOCK_METHOD0(getContractHelper, ContractHelper&());
    MOCK_METHOD0(getFeeHelper, FeeHelper&());
    MOCK_METHOD0(getOfferHelper, OfferHelper&());
    MOCK_METHOD0(getReferenceHelper, ReferenceHelper&());
    MOCK_METHOD0(getSaleHelper, SaleHelper&());
    MOCK_METHOD0(getPendingStatisticsHelper, PendingStatisticsHelper&());
    MOCK_METHOD0(getStatisticsV2Helper, StatisticsV2Helper&());
    MOCK_METHOD0(getDataHelper, DataHelper&());
    MOCK_METHOD0(getDeferredPaymentHelper, DeferredPaymentHelper&());
    MOCK_METHOD0(getLiquidityPoolHelper, LiquidityPoolHelper&());
};

}  // namespace stellar
