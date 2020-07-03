#include "RemoveDataOpFrame.h"
#include "ledger/DataHelper.h"
#include "ledger/StorageHelper.h"
#include "main/Application.h"

namespace stellar 
{
RemoveDataOpFrame::RemoveDataOpFrame(Operation const& op, 
        OperationResult& res, TransactionFrame& parentTx)
        : OperationFrame(op, res, parentTx)
        , mRemoveData(mOperation.body.removeDataOp())
{
}

bool
RemoveDataOpFrame::tryGetOperationConditions(StorageHelper &storageHelper,
                                    std::vector<OperationCondition> &result) const
{
    auto dataFrame = storageHelper.getDataHelper().loadData(mRemoveData.dataID);
    if (!dataFrame) 
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::DATA;
        return false;
    }

    AccountRuleResource resource(LedgerEntryType::DATA);
    resource.data().type = dataFrame->getData().type;

    result.emplace_back(resource, AccountRuleAction::REMOVE, mSourceAccount);

    return true;
}

bool
RemoveDataOpFrame::tryGetSignerRequirements(StorageHelper &storageHelper,
                                   std::vector<SignerRequirement> &result) const
{
    auto dataFrame = storageHelper.getDataHelper().loadData(mRemoveData.dataID);
    if (!dataFrame) 
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::DATA;
        return false;
    }

    SignerRuleResource resource(LedgerEntryType::DATA);
    resource.data().type = dataFrame->getData().type;

    result.emplace_back(resource, SignerRuleAction::REMOVE);

    return true;
}

bool
RemoveDataOpFrame::doApply(Application& app, StorageHelper& storageHelper,
                           LedgerManager& ledgerManager)
{
    innerResult().code(RemoveDataResultCode::SUCCESS);

    LedgerKey key(LedgerEntryType::DATA);
    key.data().id = mRemoveData.dataID;
    auto& helper = storageHelper.getDataHelper();

    auto dataFrame = helper.loadData(mRemoveData.dataID);
    if (!dataFrame)
    {
        innerResult().code(RemoveDataResultCode::NOT_FOUND);
        return false;
    }

    if (!isAuthorized(dataFrame, app.getAdminID()))
    {
        innerResult().code(RemoveDataResultCode::NOT_AUTHORIZED);
        return false;
    }


    helper.storeDelete(key);
    
    return true;
}

bool
RemoveDataOpFrame::doCheckValid(Application& app) 
{
    if (mRemoveData.dataID == 0) 
    {
        innerResult().code(RemoveDataResultCode::NOT_FOUND);
        return false;
    }

    return true;
}

bool
RemoveDataOpFrame::isAuthorized(DataFrame::pointer dataFrame, AccountID admin)
{
    return (getSourceID() == dataFrame->getData().owner) ||
           (getSourceID() == admin);
}

std::string
RemoveDataOpFrame::getInnerResultCodeAsStr()
{
    return xdr::xdr_traits<RemoveDataResultCode>::enum_name(innerResult().code());
}

}