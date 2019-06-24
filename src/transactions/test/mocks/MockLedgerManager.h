#pragma once

#include "ledger/LedgerManager.h"

namespace stellar
{
class MockLedgerManager : public LedgerManager
{
public:
	MOCK_METHOD0(bootstrap,void());
	MOCK_CONST_METHOD0(getState,
					   State());
	MOCK_CONST_METHOD0(getCatchupState,
					   CatchupState());
	MOCK_CONST_METHOD0(getStateHuman,
					   std::string());
	MOCK_METHOD1(valueExternalized,
				 void(LedgerCloseData const& ledgerData));
	MOCK_CONST_METHOD0(getLastClosedLedgerHeader,
					   const LedgerHeaderHistoryEntry&());
	MOCK_METHOD0(getLastClosedLedgerHAS,
				 HistoryArchiveState());
	MOCK_CONST_METHOD0(getLastClosedLedgerNum,
					   uint32_t());
	MOCK_CONST_METHOD1(getLastMinBalance,
					   int64_t(uint32_t ownerCount));
	MOCK_CONST_METHOD0(getLastReserve,
					   uint32_t());
	MOCK_CONST_METHOD0(getCloseTime,
					   uint64_t());
	MOCK_CONST_METHOD0(getTmCloseTime,
					   tm());
	MOCK_CONST_METHOD0(getLastTxFee,
					   uint32_t());
	MOCK_CONST_METHOD0(getLastMaxTxSetSize,
					   uint32_t());
	MOCK_CONST_METHOD0(getTxExpirationPeriod,
					   uint64());
	MOCK_CONST_METHOD0(secondsSinceLastLedgerClose,
					   uint64_t());
	MOCK_METHOD0(syncMetrics,
				 void());
	MOCK_METHOD0(getCurrentLedgerHeader,
				 LedgerHeader&());
	MOCK_METHOD0(getDatabase,
				 Database&());
	MOCK_METHOD0(startNewLedger,
				 void());
	MOCK_METHOD1(loadLastKnownLedger,
				 void(std::function<void(asio::error_code const& ec)> handler));
	MOCK_METHOD2(startCatchup,
				 void(CatchupConfiguration configuration, bool manualCatchup));
	MOCK_METHOD1(closeLedger,
				 void(LedgerCloseData const& ledgerData));
	MOCK_METHOD3(deleteOldEntries,
				 void(Database& db, uint32_t ledgerSeq, uint32_t count));
	MOCK_METHOD1(shouldUse,
				 bool(const LedgerVersion version));
	MOCK_METHOD0(getLedgerVersion,
				 LedgerVersion());
	MOCK_METHOD0(getNotExistingAccountID, AccountID());
};
}
