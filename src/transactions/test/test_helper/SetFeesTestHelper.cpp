#include <lib/catch.hpp>
#include "SetFeesTestHelper.h"
#include "ledger/FeeHelper.h"
#include "ledger/StorageHelper.h"
#include "transactions/SetFeesOpFrame.h"

namespace stellar {
    namespace txtest {
        SetFeesTestHelper::SetFeesTestHelper(txtest::TestManager::pointer testManager) : TxHelper(testManager) {}

        TransactionFramePtr SetFeesTestHelper::createSetFeesTx(txtest::Account &source, FeeEntry *fee, bool isDelete) {
            Operation op;
            op.body.type(OperationType::SET_FEES);

            SetFeesOp &setFeesOp = op.body.setFeesOp();

            if (fee != nullptr)
                setFeesOp.fee.activate() = *fee;

            setFeesOp.isDelete = isDelete;

            return TxHelper::txFromOperation(source, op, nullptr);
        }

        void SetFeesTestHelper::applySetFeesTx(txtest::Account &source, FeeEntry *fee, bool isDelete,
                                               SetFeesResultCode expectedResult) {
            TransactionFramePtr txFrame;
            txFrame = createSetFeesTx(source, fee, isDelete);
            mTestManager->applyCheck(txFrame);

            auto actualResult = SetFeesOpFrame::getInnerCode(txFrame->getResult().result.results()[0]);

            REQUIRE(actualResult == expectedResult);

            if (actualResult != SetFeesResultCode::SUCCESS) {
                return;
            }

            if (fee) {
                auto storedFee = mTestManager->getStorageHelper().getFeeHelper().loadFee(fee->feeType, fee->asset,
                                                                fee->accountID.get(), fee->accountRole.get(),
                                                                fee->subtype, fee->lowerBound, fee->upperBound);
                if (isDelete)
                    REQUIRE(!storedFee);
                else {
                    REQUIRE(storedFee);
                    REQUIRE(storedFee->getFee() == *fee);
                }
            }
        }

        FeeEntry
        SetFeesTestHelper::createFeeEntry(FeeType type, AssetCode asset, int64_t fixed, int64_t percent,
                                          AccountID *accountID, uint64_t* accountType, int64_t subtype,
                                          int64_t lowerBound, int64_t upperBound) {
            FeeEntry fee;
            fee.feeType = type;
            fee.asset = asset;
            fee.fixedFee = fixed;
            fee.percentFee = percent;
            fee.subtype = subtype;

            if (accountID) {
                fee.accountID.activate() = *accountID;
            }
            if (accountType) {
                fee.accountRole.activate() = *accountType;
            }

            fee.lowerBound = lowerBound;
            fee.upperBound = upperBound;

            fee.hash = FeeFrame::calcHash(type, asset, accountID, accountType, subtype);

            return fee;
        }
    }
}