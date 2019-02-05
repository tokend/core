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
