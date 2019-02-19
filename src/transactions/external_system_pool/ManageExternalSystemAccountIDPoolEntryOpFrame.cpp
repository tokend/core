#include "ManageExternalSystemAccountIDPoolEntryOpFrame.h"
#include "CreateExternalSystemAccountIDPoolEntryOpFrame.h"
#include "DeleteExternalSystemAccountIDPoolEntryOpFrame.h"

namespace stellar
{
using namespace std;
using xdr::operator==;

bool
ManageExternalSystemAccountIdPoolEntryOpFrame::tryGetOperationConditions(
                                StorageHelper& storageHelper,
                                std::vector<OperationCondition>& result) const
{
    result.emplace_back(AccountRuleResource(LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY),
                        AccountRuleAction::MANAGE, mSourceAccount);

    return true;
}

bool
ManageExternalSystemAccountIdPoolEntryOpFrame::tryGetSignerRequirements(
        StorageHelper& storageHelper, std::vector<SignerRequirement>& result) const
{
    result.emplace_back(SignerRuleResource(LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY), "manage");

    return true;
}

    ManageExternalSystemAccountIdPoolEntryOpFrame::ManageExternalSystemAccountIdPoolEntryOpFrame(Operation const &op,
                                                                                                 OperationResult &res,
                                                                             TransactionFrame &parentTx)
            : OperationFrame(op, res, parentTx),
              mManageExternalSystemAccountIdPoolEntryOp(mOperation.body.manageExternalSystemAccountIdPoolEntryOp())
    {
    }

    ManageExternalSystemAccountIdPoolEntryOpFrame * ManageExternalSystemAccountIdPoolEntryOpFrame::makeHelper(
            Operation const &op, OperationResult &res, TransactionFrame &parentTx)
    {
        switch (op.body.manageExternalSystemAccountIdPoolEntryOp().actionInput.action()) {
            case ManageExternalSystemAccountIdPoolEntryAction::CREATE:
                return new CreateExternalSystemAccountIDPoolEntryOpFrame(op, res, parentTx);
            case ManageExternalSystemAccountIdPoolEntryAction::REMOVE:
                return new DeleteExternalSystemAccountIDPoolEntryOpFrame(op, res, parentTx);
            default:
                throw runtime_error("Unexpected action in manage external system account id pool entry op");
        }
    }
}
