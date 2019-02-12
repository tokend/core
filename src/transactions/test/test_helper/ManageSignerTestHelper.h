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

    ManageSignerOp buildCreateOp(PublicKey& key, uint32_t weight,
                                 uint32_t identity, uint64_t roleID);

    ManageSignerOp buildUpdateOp(PublicKey& key, uint32_t wight,
                                 uint32_t identity, uint64_t roleID);

    ManageSignerOp buildRemoveOp(PublicKey& key);

    TransactionFramePtr buildTx(Account &source,
                                const ManageSignerOp &op);

    ManageSignerResult applyTx(Account &source, const ManageSignerOp &op,
                               ManageSignerResultCode expectedResultCode =
                                       ManageSignerResultCode::SUCCESS,
                               OperationResultCode expectedOpCode =
                                       OperationResultCode::opINNER);

    void applyCreateOperationalSigner(Account& source, PublicKey signerKey);
};
} // namespace txtest
} // namespace stellar
