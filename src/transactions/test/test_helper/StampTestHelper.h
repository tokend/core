#pragma once

#include "TxHelper.h"

namespace stellar
{

namespace txtest
{

class StampTestHelper : TxHelper
{
public:
explicit StampTestHelper(TestManager::pointer testManager);

TransactionFramePtr stamp(Account& source);

StampResult applyStamp(Account& source, StampResultCode expectedResult =
                                         StampResultCode::SUCCESS);
};

}

}
