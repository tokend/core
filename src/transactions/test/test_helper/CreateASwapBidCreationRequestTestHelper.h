#pragma once

#include "TxHelper.h"

namespace stellar
{

namespace txtest
{

class CreateASwapBidCreationRequestHelper : TxHelper
{
public:
explicit CreateASwapBidCreationRequestHelper(TestManager::pointer testManager);

static AtomicSwapBidCreationRequest createASwapBidCreationRequest(
        BalanceID baseBalance, uint64_t amount, std::string details,
        std::vector<AtomicSwapBidQuoteAsset> quoteAssets);

TransactionFramePtr
createCreateASwapBidCreationRequestTx(Account& source, AtomicSwapBidCreationRequest request);

CreateAtomicSwapBidCreationRequestResult applyCreateASwapBidCreationRequest(
        Account& source, AtomicSwapBidCreationRequest request,
        CreateAtomicSwapBidCreationRequestResultCode expectedResult =
        CreateAtomicSwapBidCreationRequestResultCode::SUCCESS,
        OperationResultCode expectedOpResCode = OperationResultCode::opINNER);
};

}

}