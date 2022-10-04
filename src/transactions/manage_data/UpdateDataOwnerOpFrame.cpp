#include "UpdateDataOwnerOpFrame.h"
#include "ledger/DataHelper.h"
#include "ledger/AccountHelper.h"
#include "ledger/StorageHelper.h"
#include "main/Application.h"

namespace stellar
{
UpdateDataOwnerOpFrame::UpdateDataOwnerOpFrame(Operation const& op, OperationResult& res,
                                     TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx)
    , mUpdateDataOwner(mOperation.body.updateDataOwnerOp())
{
}

bool
UpdateDataOwnerOpFrame::tryGetOperationConditions(
    StorageHelper& storageHelper, std::vector<OperationCondition>& result) const
{
    auto dataFrame = storageHelper.getDataHelper().loadData(mUpdateDataOwner.dataID);
    if (!dataFrame)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::DATA;
        return false;
    }

    auto action = AccountRuleAction::TRANSFER_OWNERSHIP;

    AccountRuleResource resource(LedgerEntryType::DATA);
    resource.data().type = dataFrame->getData().type;

    result.emplace_back(resource, action, mSourceAccount);

    return true;
}

bool
UpdateDataOwnerOpFrame::tryGetSignerRequirements(
    StorageHelper& storageHelper, std::vector<SignerRequirement>& result) const
{
    auto dataFrame = storageHelper.getDataHelper().loadData(mUpdateDataOwner.dataID);
    if (!dataFrame)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::DATA;
        return false;
    }

    auto action = SignerRuleAction::TRANSFER_OWNERSHIP;

    SignerRuleResource resource(LedgerEntryType::DATA);
    resource.data().type = dataFrame->getData().type;

    result.emplace_back(resource, action);

    return true;
}

bool
UpdateDataOwnerOpFrame::doApply(Application& app, StorageHelper& storageHelper,
                           LedgerManager& ledgerManager)
{
    innerResult().code(UpdateDataOwnerResultCode::SUCCESS);

    auto& helper = storageHelper.getDataHelper();
    auto dataFrame = helper.loadData(mUpdateDataOwner.dataID);
    if (!dataFrame)
    {
        innerResult().code(UpdateDataOwnerResultCode::NOT_FOUND);
        return false;
    }

    auto& data = dataFrame->getData();
    if (!(mSourceAccount->getID() == data.owner))
    {
        innerResult().code(UpdateDataOwnerResultCode::NOT_AUTHORIZED);
        return false;
    }
    
    if (data.owner == mUpdateDataOwner.newOwner)
    {
        innerResult().code(UpdateDataOwnerResultCode::OLD_AND_NEW_USERS_ARE_SAME);
        return false;
    }

    if (!storageHelper.getAccountHelper().exists(mUpdateDataOwner.newOwner))
    {
        innerResult().code(UpdateDataOwnerResultCode::USER_NOT_FOUND);
        return false;
    }
    
    data.owner = mUpdateDataOwner.newOwner;

    helper.storeChange(dataFrame->mEntry);

    return true;
}

bool
UpdateDataOwnerOpFrame::doCheckValid(Application& app)
{
    if (mUpdateDataOwner.dataID == 0)
    {
        innerResult().code(UpdateDataOwnerResultCode::NOT_FOUND);
        return false;
    }

    return true;
}

std::string
UpdateDataOwnerOpFrame::getInnerResultCodeAsStr()
{
    return xdr::xdr_traits<UpdateDataOwnerResultCode>::enum_name(
        innerResult().code());
}

}