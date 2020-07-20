#include "UpdateDataOpFrame.h"
#include "ledger/StorageHelper.h"
#include "ledger/DataHelper.h"
#include "main/Application.h"

namespace stellar
{
UpdateDataOpFrame::UpdateDataOpFrame(Operation const& op,
        OperationResult& res, TransactionFrame& parentTx)
        : OperationFrame(op, res, parentTx)
        , mUpdateData(mOperation.body.updateDataOp())
{
}

bool
UpdateDataOpFrame::tryGetOperationConditions(StorageHelper &storageHelper,
                                    std::vector<OperationCondition> &result) const
{
    auto dataFrame = storageHelper.getDataHelper().loadData(mUpdateData.dataID);
    if (!dataFrame)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::DATA;
        return false;
    }

    AccountRuleResource resource(LedgerEntryType::DATA);
    resource.data().type = dataFrame->getData().type;

    result.emplace_back(resource, AccountRuleAction::UPDATE, mSourceAccount);

    return true;
}

bool
UpdateDataOpFrame::tryGetSignerRequirements(StorageHelper &storageHelper,
                                   std::vector<SignerRequirement> &result) const
{
    auto dataFrame = storageHelper.getDataHelper().loadData(mUpdateData.dataID);
    if (!dataFrame)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::DATA;
        return false;
    }

    SignerRuleResource resource(LedgerEntryType::DATA);
    resource.data().type = dataFrame->getData().type;

    result.emplace_back(resource, SignerRuleAction::UPDATE);

    return true;
}

bool
UpdateDataOpFrame::doApply(Application& app, StorageHelper& storageHelper,
                           LedgerManager& ledgerManager)
{
    innerResult().code(UpdateDataResultCode::SUCCESS);

    auto& helper = storageHelper.getDataHelper();
    auto dataFrame = helper.loadData(mUpdateData.dataID);
    if (!dataFrame)
    {
        innerResult().code(UpdateDataResultCode::NOT_FOUND);
        return false;
    }

    if (!isAuthorized(dataFrame, app.getAdminID()))
    {
        innerResult().code(UpdateDataResultCode::NOT_AUTHORIZED);
        return false;
    }

    auto& data = dataFrame->getData();
    data.value = mUpdateData.value;

    helper.storeChange(dataFrame->mEntry);

    return true;
}

bool
UpdateDataOpFrame::doCheckValid(Application& app)
{
    if (mUpdateData.dataID == 0)
    {
        innerResult().code(UpdateDataResultCode::NOT_FOUND);
        return false;
    }

    if (!isValidJson(mUpdateData.value))
    {
        innerResult().code(UpdateDataResultCode::INVALID_DATA);
        return false;
    }

    return true;
}

bool
UpdateDataOpFrame::isAuthorized(DataFrame::pointer dataFrame, AccountID admin) {
    return (getSourceID() == dataFrame->getData().owner) || (getSourceID() == admin);
}

std::string
UpdateDataOpFrame::getInnerResultCodeAsStr()
{
    return xdr::xdr_traits<UpdateDataResultCode>::enum_name(innerResult().code());
}

}