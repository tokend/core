#include "CreatePaymentRequestOpFrame.h"

namespace stellar 
{
CreatePaymentRequestOpFrame::CreatePaymentRequestOpFrame(
        Operation const& op, OperationResult& res, TransactionFrame& tx)
        : OperationFrame(op, res, tx)
        , mCreatePaymentRequest(op.body.createPaymentRequestOp()) 
{
}

}