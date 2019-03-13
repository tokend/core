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

static ASwapBidCreationRequest createASwapBidCreationRequest(
        BalanceID baseBalance, uint64_t amount, std::string details,
        std::vector<ASwapBidQuoteAsset> quoteAssets);

TransactionFramePtr
createCreateASwapBidCreationRequestTx(Account& source, ASwapBidCreationRequest request);

CreateASwapBidCreationRequestResult applyCreateASwapBidCreationRequest(
        Account& source, ASwapBidCreationRequest request,
        CreateASwapBidCreationRequestResultCode expectedResult =
        CreateASwapBidCreationRequestResultCode::SUCCESS,
        OperationResultCode expectedOpResCode = OperationResultCode::opINNER);
};

}

}