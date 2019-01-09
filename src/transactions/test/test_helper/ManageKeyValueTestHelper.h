#ifndef STELLAR_MANAGEKEYVALUETESTHELPER_H
#define STELLAR_MANAGEKEYVALUETESTHELPER_H


#include <transactions/ManageKeyValueOpFrame.h>
#include "TxHelper.h"



namespace stellar{
    namespace txtest{

        class ManageKeyValueTestHelper : public TxHelper
        {
        public:

            explicit ManageKeyValueTestHelper(TestManager::pointer testManager);

            ManageKeyValueTestHelper copy();

            ManageKeyValueTestHelper* setKey(longstring key);

            ManageKeyValueTestHelper* setUi32Value(uint32 value);
            ManageKeyValueTestHelper* setUi64Value(uint64 value);
            ManageKeyValueTestHelper* setValue(std::string value);

            ManageKeyValueTestHelper* setResult(ManageKeyValueResultCode resultCode);

            TransactionFramePtr createManageKVTx(Account& source, const ManageKeyValueOp& op);

            void doApply(Application &app, ManageKVAction action, bool require, KeyValueEntryType type =
                                                                                KeyValueEntryType::UINT32);

            void assetOpWithoutReview();
            void applyTx(Account& source, const ManageKeyValueOp& op,
                         ManageKeyValueResultCode expectedResultCode = ManageKeyValueResultCode::SUCCESS);

        private:

            KeyValueEntryValue value;
            longstring key;
            ManageKeyValueResultCode expectedResult = ManageKeyValueResultCode ::SUCCESS;
        };

        class ManageKeyValueTestBuilder :public OperationBuilder<ManageKeyValueTestBuilder>
        {
        public:


            ManageKeyValueTestBuilder(string256 key, TestManager::pointer &testManager,
                                                    ManageKVAction action, KeyValueEntryValue value,
                                                    KeyValueEntryType type = KeyValueEntryType::UINT32);

            ManageKeyValueTestBuilder copy() override
            {
                return *this;
            }

            Operation buildOp() override;

            longstring key;
            KeyValueEntryValue value;
            KeyValueEntryType type;
            ManageKVAction kvAction;
            ManageKeyValueOpFrame* kvManager;
            Operation op;
            TransactionFramePtr tx;
            OperationResult res;
        };
    }
}


#endif //STELLAR_MANAGEKEYVALUETESTHELPER_H
