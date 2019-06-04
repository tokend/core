#pragma once

#include "TxHelper.h"

namespace stellar
{

namespace txtest
{

class CreateASwapAskRequestHelper : TxHelper
{
public:
explicit CreateASwapAskRequestHelper(TestManager::pointer testManager);

static CreateAtomicSwapAskRequest createASwapAskCreationRequest(
        BalanceID baseBalance, uint64_t amount, std::string details,
        std::vector<AtomicSwapAskQuoteAsset> quoteAssets);

TransactionFramePtr
createCreateASwapAskCreationRequestTx(Account &source,
                                      CreateAtomicSwapAskRequest request);

CreateAtomicSwapAskRequestResult applyCreateASwapAskCreationRequest(
        Account &source, CreateAtomicSwapAskRequest request,
        CreateAtomicSwapAskRequestResultCode expectedResult =
        CreateAtomicSwapAskRequestResultCode::SUCCESS,
        OperationResultCode expectedOpResCode = OperationResultCode::opINNER);
};

}

}