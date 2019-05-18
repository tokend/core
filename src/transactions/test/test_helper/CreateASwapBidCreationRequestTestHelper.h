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

static CreateAtomicSwapBidRequest createASwapBidCreationRequest(
        BalanceID baseBalance, uint64_t amount, std::string details,
        std::vector<AtomicSwapBidQuoteAsset> quoteAssets);

TransactionFramePtr
createCreateASwapBidCreationRequestTx(Account& source, CreateAtomicSwapBidRequest request);

CreateAtomicSwapBidRequestResult applyCreateASwapBidCreationRequest(
        Account& source, CreateAtomicSwapBidRequest request,
        CreateAtomicSwapBidRequestResultCode expectedResult =
        CreateAtomicSwapBidRequestResultCode::SUCCESS,
        OperationResultCode expectedOpResCode = OperationResultCode::opINNER);
};

}

}