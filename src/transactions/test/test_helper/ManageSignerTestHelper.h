#pragma once

#include "TxHelper.h"

namespace stellar
{
namespace txtest
{
class ManageSignerTestHelper : TxHelper
{
public:
    ManageSignerTestHelper(TestManager::pointer testManager);

    ManageSignerOp buildCreateOp(PublicKey key, uint32_t weight,
                                 uint32_t identity, uint64_t roleID);

    ManageSignerOp buildUpdateOp(PublicKey key, uint32_t wight,
                                 uint32_t identity, uint64_t roleID);

    ManageSignerOp buildRemoveOp(PublicKey key);

    TransactionFramePtr
    buildTx(Account &source, const ManageSignerOp &op, Account* signer = nullptr);

    TransactionFramePtr
    buildTx(Account &source, std::vector<ManageSignerOp> ops, Account* signer);

    ManageSignerResult applyTx(Account &source, const ManageSignerOp &op,
                               ManageSignerResultCode expectedResultCode =
                                       ManageSignerResultCode::SUCCESS,
                               OperationResultCode expectedOpCode =
                                       OperationResultCode::opINNER,
                               TransactionResultCode expectedTxResult =
                                       TransactionResultCode::txSUCCESS,
                               Account* signer = nullptr);

    ManageSignerResult applyTx(Account &source, std::vector<ManageSignerOp> ops,
                               ManageSignerResultCode expectedResultCode =
                               ManageSignerResultCode::SUCCESS,
                               OperationResultCode expectedOpCode =
                               OperationResultCode::opINNER,
                               TransactionResultCode expectedTxResult =
                               TransactionResultCode::txSUCCESS,
                               Account* signer = nullptr);

    void applyCreateOperationalSigner(Account& source, PublicKey signerKey);
};
} // namespace txtest
} // namespace stellar
