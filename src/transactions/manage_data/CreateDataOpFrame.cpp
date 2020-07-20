#include "CreateDataOpFrame.h"
#include "ledger/DataHelper.h"
#include "ledger/LedgerDelta.h"
#include "ledger/LedgerHeaderFrame.h"
#include "ledger/StorageHelper.h"

namespace stellar
{
CreateDataOpFrame::CreateDataOpFrame(Operation const& op, OperationResult& res,
                                     TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx)
    , mCreateData(mOperation.body.createDataOp())
{
}

bool
CreateDataOpFrame::tryGetOperationConditions(
    StorageHelper& storageHelper, std::vector<OperationCondition>& result) const
{
    AccountRuleResource resource(LedgerEntryType::DATA);
    resource.data().type = mCreateData.type;
    result.emplace_back(resource, AccountRuleAction::CREATE, mSourceAccount);

    return true;
}

bool
CreateDataOpFrame::tryGetSignerRequirements(
    StorageHelper& storageHelper, std::vector<SignerRequirement>& result) const
{
    SignerRuleResource resource(LedgerEntryType::DATA);
    resource.data().type = mCreateData.type;
    result.emplace_back(resource, SignerRuleAction::CREATE);

    return true;
}

bool
CreateDataOpFrame::doApply(Application& app, StorageHelper& storageHelper,
                           LedgerManager& ledgerManager)
{
    innerResult().code(CreateDataResultCode::SUCCESS);

    auto& header = storageHelper.mustGetLedgerDelta().getHeaderFrame();
    LedgerEntry le;
    le.data.type(LedgerEntryType::DATA);
    auto& data = le.data.data();
    data.id = header.generateID(LedgerEntryType::DATA);
    data.type = mCreateData.type;
    data.value = mCreateData.value;
    data.owner = getSourceID();

    storageHelper.getDataHelper().storeAdd(le);

    innerResult().success().dataID = data.id;
    return true;
}

bool
CreateDataOpFrame::doCheckValid(Application& app)
{
    if (!isValidJson(mCreateData.value))
    {
        innerResult().code(CreateDataResultCode::INVALID_DATA);
        return false;
    }

    return true;
}

std::string
CreateDataOpFrame::getInnerResultCodeAsStr()
{
    return xdr::xdr_traits<CreateDataResultCode>::enum_name(
        innerResult().code());
}

}