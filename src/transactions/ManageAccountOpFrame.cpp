// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "transactions/ManageAccountOpFrame.h"
#include "ledger/LedgerDelta.h"
#include "ledger/AccountHelperLegacy.h"
#include "database/Database.h"

#include "main/Application.h"
#include "medida/meter.h"
#include "medida/metrics_registry.h"

namespace stellar
{

using namespace std;
using xdr::operator==;
    
std::unordered_map<AccountID, CounterpartyDetails> ManageAccountOpFrame::getCounterpartyDetails(Database & db, LedgerDelta * delta) const
{
	return{ 
		{ mManageAccount.account, CounterpartyDetails({ AccountType::GENERAL, AccountType::NOT_VERIFIED, AccountType::EXCHANGE,
                                                        AccountType::SYNDICATE, AccountType::VERIFIED,
														AccountType::ACCREDITED_INVESTOR, AccountType::INSTITUTIONAL_INVESTOR},
													  true, true) }
	};
}

SourceDetails ManageAccountOpFrame::getSourceAccountDetails(std::unordered_map<AccountID, CounterpartyDetails> counterpartiesDetails,
                                                            int32_t ledgerVersion) const
{
	int32_t threshold = 0;

	uint32_t allowedSignerClass = 0;
	// check for account type mismatched performed in doApply
	switch (mManageAccount.accountType)
	{
	case AccountType::NOT_VERIFIED:
		allowedSignerClass = static_cast<int32_t>(SignerType::NOT_VERIFIED_ACC_MANAGER);
		break;
	case AccountType::ACCREDITED_INVESTOR:
	case AccountType::INSTITUTIONAL_INVESTOR:
	case AccountType::VERIFIED:
	case AccountType::GENERAL:
		// not verified account manager is needed here to allow automatic account blocking on KYC update
		allowedSignerClass = static_cast<int32_t>(SignerType::NOT_VERIFIED_ACC_MANAGER) |
											static_cast<int32_t>(SignerType::GENERAL_ACC_MANAGER);
		break;
    case AccountType::EXCHANGE:
        allowedSignerClass = static_cast<int32_t>(SignerType::EXCHANGE_ACC_MANAGER);
        break;
    case AccountType::SYNDICATE:
        allowedSignerClass = static_cast<int32_t>(SignerType::SYNDICATE_ACC_MANAGER);
        break;
	default:
		// it is not allowed to block/unblock any other account types
		allowedSignerClass = 0;
		break;
	}
	return SourceDetails({ AccountType::MASTER }, threshold, allowedSignerClass);
}

ManageAccountOpFrame::ManageAccountOpFrame(Operation const& op,
                                           OperationResult& res,
                                           TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx)
    , mManageAccount(mOperation.body.manageAccountOp())
{
}

bool
ManageAccountOpFrame::doApply(Application& app,
                              LedgerDelta& delta, LedgerManager& ledgerManager)
{
    Database& db = ledgerManager.getDatabase();

	auto accountHelper = AccountHelperLegacy::Instance();
	auto account = accountHelper->loadAccount(delta, mManageAccount.account, db);
	assert(account);

    account->setBlockReasons(mManageAccount.blockReasonsToAdd, mManageAccount.blockReasonsToRemove);
	EntryHelperProvider::storeChangeEntry(delta, db, account->mEntry);

	app.getMetrics().NewMeter({"op-manage-account", "success", "apply"},
	                          "operation").Mark();
    innerResult().success().blockReasons = account->getBlockReasons();
	innerResult().code(ManageAccountResultCode::SUCCESS);
	return true;
}

bool
ManageAccountOpFrame::doCheckValid(Application& app)
{
	if (mManageAccount.accountType == AccountType::MASTER)
	{
		app.getMetrics().NewMeter({ "op-manage-account", "failure", "not-allowed" }, "operation").Mark();
		innerResult().code(ManageAccountResultCode::NOT_ALLOWED);
		return false;
	}

	if ((mManageAccount.blockReasonsToAdd && mManageAccount.blockReasonsToRemove) != 0)
	{
		app.getMetrics().NewMeter({ "op-manage-account", "failure", "malformed" }, "operation").Mark();
		innerResult().code(ManageAccountResultCode::MALFORMED);
		return false;
	}


    return true;
}
}
