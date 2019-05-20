#include "BindExternalSystemAccountIdOpFrame.h"
#include "transactions/ManageKeyValueOpFrame.h"
#include "ledger/AccountHelperLegacy.h"
#include "ledger/ExternalSystemAccountID.h"
#include "ledger/ExternalSystemAccountIDHelper.h"
#include "ledger/ExternalSystemAccountIDPoolEntryHelper.h"
#include "ledger/KeyValueHelper.h"
#include "ledger/LedgerDelta.h"
#include "ledger/StorageHelper.h"
#include "main/Application.h"

namespace stellar
{

using namespace std;
using xdr::operator==;

bool
BindExternalSystemAccountIdOpFrame::tryGetOperationConditions(StorageHelper& sh,
                                  std::vector<OperationCondition>& result) const
{
    AccountRuleResource poolResource(LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY);

    result.emplace_back(poolResource, AccountRuleAction::BIND, mSourceAccount);

    return true;
}

bool
BindExternalSystemAccountIdOpFrame::tryGetSignerRequirements(
        StorageHelper& storageHelper, std::vector<SignerRequirement>& result) const
{
    result.emplace_back(SignerRuleResource(LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY),
                        SignerRuleAction::BIND);

    return true;
}

BindExternalSystemAccountIdOpFrame::BindExternalSystemAccountIdOpFrame(
    Operation const& op, OperationResult& res, TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx)
    , mBindExternalSystemAccountId(
          mOperation.body.bindExternalSystemAccountIdOp())
{
}

bool
BindExternalSystemAccountIdOpFrame::doApply(Application& app,
                                            StorageHelper& storageHelper,
                                            LedgerManager& ledgerManager)
{
    auto& externalSystemAccountIDHelper =
        storageHelper.getExternalSystemAccountIDHelper();
    auto& externalSystemAccountIDPoolEntryHelper =
        storageHelper.getExternalSystemAccountIDPoolEntryHelper();

    auto existingPoolEntryFrame = externalSystemAccountIDPoolEntryHelper.load(
        mBindExternalSystemAccountId.externalSystemType,
        mSourceAccount->getID());
    if (!!existingPoolEntryFrame)
    {
        int expiresAt = ledgerManager.shouldUse(LedgerVersion::FIX_EXT_SYS_ACC_EXPIRATION_TIME)
                ? getExpiresAt(storageHelper, ledgerManager, mBindExternalSystemAccountId.externalSystemType)
                : dayInSeconds;
        existingPoolEntryFrame->getExternalSystemAccountIDPoolEntry()
            .expiresAt = ledgerManager.getCloseTime() + expiresAt;
        externalSystemAccountIDPoolEntryHelper.storeChange(
            existingPoolEntryFrame->mEntry);
        innerResult().code(BindExternalSystemAccountIdResultCode::SUCCESS);
        innerResult().success().data =
            existingPoolEntryFrame->getExternalSystemAccountIDPoolEntry().data;
        return true;
    }

    auto poolEntryToBindFrame =
        externalSystemAccountIDPoolEntryHelper.loadAvailablePoolEntry(
            ledgerManager, mBindExternalSystemAccountId.externalSystemType);
    if (!poolEntryToBindFrame)
    {
        innerResult().code(
            BindExternalSystemAccountIdResultCode::NO_AVAILABLE_ID);
        return false;
    }

    ExternalSystemAccountIDPoolEntry& poolEntryToBind =
        poolEntryToBindFrame->getExternalSystemAccountIDPoolEntry();

    if (poolEntryToBind.accountID)
    {
        auto existingExternalSystemAccountIDFrame =
            externalSystemAccountIDHelper.load(
                *poolEntryToBind.accountID,
                mBindExternalSystemAccountId.externalSystemType);
        if (!existingExternalSystemAccountIDFrame)
        {
            auto accIDStr = PubKeyUtils::toStrKey(*poolEntryToBind.accountID);
            CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Failed to load existing external system account id for "
                   "account id:"
                << accIDStr;
            throw runtime_error("Unexpected state: external system account id "
                                "expected to exist");
        }

        externalSystemAccountIDHelper.storeDelete(
            existingExternalSystemAccountIDFrame->getKey());
    }

    poolEntryToBind.accountID.activate() = mSourceAccount->getID();

    int expiresAt =
        getExpiresAt(storageHelper, ledgerManager,
                     mBindExternalSystemAccountId.externalSystemType);
    poolEntryToBind.expiresAt = ledgerManager.getCloseTime() + expiresAt;

    poolEntryToBind.bindedAt = ledgerManager.getCloseTime();

    auto externalSystemAccountIDFrame = ExternalSystemAccountIDFrame::createNew(
        mSourceAccount->getID(),
        mBindExternalSystemAccountId.externalSystemType, poolEntryToBind.data);

    externalSystemAccountIDPoolEntryHelper.storeChange(
        poolEntryToBindFrame->mEntry);
    externalSystemAccountIDHelper.storeAdd(
        externalSystemAccountIDFrame->mEntry);
    innerResult().code(BindExternalSystemAccountIdResultCode::SUCCESS);
    innerResult().success().data = poolEntryToBind.data;
    return true;
}

bool
BindExternalSystemAccountIdOpFrame::doCheckValid(Application& app)
{
    return true;
}

int
BindExternalSystemAccountIdOpFrame::getExpiresAt(StorageHelper& storageHelper,
                                                 LedgerManager& ledgerManager,
                                                 int32 externalSystemType)
{
    auto key = ManageKeyValueOpFrame::makeExternalSystemExpirationPeriodKey(
        externalSystemType);

    auto kvEntry = storageHelper.getKeyValueHelper().loadKeyValue(key);

    if (!kvEntry)
    {
        return dayInSeconds;
    }

    if (kvEntry.get()->getKeyValue().value.type() != KeyValueEntryType::UINT32)
    {
        CLOG(WARNING, "BindExternalSystemAccountId")
            << "KeyValueEntryType: "
            << to_string(static_cast<int32>(
                   kvEntry.get()->getKeyValue().value.type()));
        return dayInSeconds;
    }

    return kvEntry.get()->getKeyValue().value.ui32Value();
}

} // namespace stellar
