// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "CheckLicenseStateOpFrame.h"
#include "ledger/LedgerDelta.h"
#include "ledger/LicenseHelper.h"
#include "database/Database.h"
#include "main/Application.h"
#include "xdrpp/printer.h"

namespace stellar
{
using namespace std;
using xdr::operator==;


unordered_map<AccountID, CounterpartyDetails> CheckLicenseStateOpFrame::
getCounterpartyDetails(Database& db, LedgerDelta* delta) const
{
    // no counterparties
    return {};
}

SourceDetails CheckLicenseStateOpFrame::getSourceAccountDetails(std::unordered_map<AccountID, CounterpartyDetails>, int32_t ledgerVersion)
const
{
    return SourceDetails({ AccountType::MASTER }, mSourceAccount->getLowThreshold(), int32_t(SignerType::EVENTS_CHECKER));
}


CheckLicenseStateOpFrame::CheckLicenseStateOpFrame(Operation const& op,
    OperationResult& res, TransactionFrame& parentTx) : OperationFrame(op, res, parentTx), mCheckLicenseState(mOperation.body.checkLicenseStateOp())
{
}

bool
CheckLicenseStateOpFrame::doApply(Application &app, StorageHelper &storageHelper, LedgerManager &ledgerManager)
{
    LicenseHelper licenseHelper(storageHelper);

    auto licenseFrame = licenseHelper.loadCurrentLicense();
    if (!licenseFrame)
    {
        //todo inner code
        return false;
    }

    innerResult().code(CheckLicenseStateResultCode::SUCCESS);
    innerResult().success().dueDate = licenseFrame->mEntry.data.license().dueDate;
    innerResult().success().adminCount = licenseFrame->mEntry.data.license().adminCount;
    return true;
}

    bool CheckLicenseStateOpFrame::doCheckValid(Application& app)
{
    return true;
}

std::string CheckLicenseStateOpFrame::getInnerResultCodeAsStr()
{
    const auto code = getInnerCode(mResult);
    return xdr::xdr_traits<CheckLicenseStateResultCode>::enum_name(code);
}

}
