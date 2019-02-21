// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <ledger/BalanceHelperLegacy.h>
#include "main/Application.h"
#include "invariant/Invariants.h"
#include "overlay/LoopbackPeer.h"
#include "util/make_unique.h"
#include "main/test.h"
#include "test/test_marshaler.h"
#include "TxTests.h"
#include "ledger/LedgerDeltaImpl.h"
#include "transactions/CreateAccountOpFrame.h"
#include "transactions/ManageBalanceOpFrame.h"
#include "transactions/payment/PaymentOpFrame.h"
#include "transactions/ManageLimitsOpFrame.h"
#include "transactions/deprecated/ManageInvoiceRequestOpFrame.h"
#include "ledger/AccountHelperLegacy.h"
#include "ledger/AssetHelperLegacy.h"
#include "ledger/FeeHelper.h"
#include "ledger/StatisticsHelper.h"
#include "crypto/SHA.h"
#include "test_helper/TestManager.h"

using namespace stellar;
using namespace stellar::txtest;

typedef std::unique_ptr<Application> appPtr;
namespace stellar
{
using xdr::operator==;

namespace txtest
{
	auto accountHelper = AccountHelperLegacy::Instance();
	auto assetHelper = AssetHelperLegacy::Instance();
	auto balanceHelper = BalanceHelperLegacy::Instance();
	auto feeHelper = FeeHelper::Instance();
	auto statisticsHelper = StatisticsHelper::Instance();


FeeEntry createFeeEntry(FeeType type, int64_t fixed, int64_t percent,
    AssetCode asset, AccountID* accountID, uint64_t* accountType, int64_t subtype,
    int64_t lowerBound, int64_t upperBound)
{
	FeeEntry fee;
	fee.feeType = type;
	fee.fixedFee = fixed;
	fee.percentFee = percent;
	fee.asset = asset;
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

PaymentFeeData getNoPaymentFee() {
    return getGeneralPaymentFee(0, 0);
}

PaymentFeeData getGeneralPaymentFee(uint64 fixedFee, uint64 paymentFee) {
    PaymentFeeData paymentFeeData;
    Fee generalFeeData;
    generalFeeData.fixed = fixedFee;
    generalFeeData.percent = paymentFee;
    paymentFeeData.sourceFee = generalFeeData;
    paymentFeeData.destinationFee = generalFeeData;
    paymentFeeData.sourcePaysForDest = true;
    
    return paymentFeeData;
}

[[deprecated("Use TxHelper")]]
bool applyCheck(TransactionFramePtr tx, LedgerDelta& delta, Application& app)
{
    auto txSet = std::make_shared<TxSetFrame>(
            app.getLedgerManager().getLastClosedLedgerHeader().hash);
    txSet->add(tx);

	tx->clearCached();
    bool check = tx->checkValid(app);
    TransactionResult checkResult = tx->getResult();
    REQUIRE((!check || checkResult.result.code() == TransactionResultCode::txSUCCESS));
    
    bool res;
    auto code = checkResult.result.code();

    if (code != TransactionResultCode::txNO_ACCOUNT && code != TransactionResultCode::txDUPLICATION)
    {
        tx->processSeqNum();
    }

    bool doApply = (code != TransactionResultCode::txDUPLICATION);

    if (doApply)
    {
        res = tx->apply(delta, app);


        REQUIRE((!res || tx->getResultCode() == TransactionResultCode::txSUCCESS));

        if (!check)
        {
            REQUIRE(checkResult == tx->getResult());
        }

		if (res)
		{
			delta.commit();
		}
    }
    else
    {
        res = check;
    }

    // verify modified accounts invariants
    auto const& changes = delta.getChanges();
    for (auto const& c : changes)
    {
        switch (c.type())
        {
        case LedgerEntryChangeType::CREATED:
            checkEntry(c.created(), app);
            break;
        case LedgerEntryChangeType::UPDATED:
            checkEntry(c.updated(), app);
            break;
        default:
            break;
        }
    }

    // validates db state
    app.getLedgerManager().checkDbState();
    app.getInvariants().check(txSet, delta);
    return res;
}

void
checkEntry(LedgerEntry const& le, Application& app)
{
    auto& d = le.data;
    switch (d.type())
    {
    case LedgerEntryType::ACCOUNT:
        checkAccount(d.account().accountID, app);
        break;
    default:
        break;
    }
}


void
checkAccount(AccountID const& id, Application& app)
{
    AccountFrame::pointer res =
        accountHelper->loadAccount(id, app.getDatabase());
    REQUIRE(!!res);
}

time_t
getTestDate(int day, int month, int year)
{
    std::tm tm = {0};
    tm.tm_hour = 0;
    tm.tm_min = 0;
    tm.tm_sec = 0;
    tm.tm_mday = day;
    tm.tm_mon = month - 1; // 0 based
    tm.tm_year = year - 1900;

    VirtualClock::time_point tp = VirtualClock::tmToPoint(tm);
    time_t t = VirtualClock::to_time_t(tp);

    return t;
}

TxSetResultMeta closeLedgerOn(Application& app, uint32 ledgerSeq, time_t closeTime)
{

	TxSetFramePtr txSet = std::make_shared<TxSetFrame>(
		app.getLedgerManager().getLastClosedLedgerHeader().hash);
	return closeLedgerOn(app, ledgerSeq, closeTime, txSet);
}

TxSetResultMeta
closeLedgerOn(Application& app, uint32 ledgerSeq, int day, int month, int year,
              TransactionFramePtr tx)
{
    TxSetFramePtr txSet = std::make_shared<TxSetFrame>(
        app.getLedgerManager().getLastClosedLedgerHeader().hash);

    if (tx)
    {
        txSet->add(tx);
        txSet->sortForHash();
    }

    return closeLedgerOn(app, ledgerSeq, day, month, year, txSet);
}

TxSetResultMeta closeLedgerOn(Application& app, uint32 ledgerSeq, time_t closeTime, TxSetFramePtr txSet)
{
	StellarValue sv(txSet->getContentsHash(), closeTime,
		emptyUpgradeSteps, StellarValue::_ext_t(LedgerVersion::EMPTY_VERSION));
	LedgerCloseData ledgerData(ledgerSeq, txSet, sv);
	app.getLedgerManager().closeLedger(ledgerData);

	auto z1 = TransactionFrame::getTransactionHistoryResults(app.getDatabase(),
		ledgerSeq);
	auto z2 =
		TransactionFrame::getTransactionFeeMeta(app.getDatabase(), ledgerSeq);

	REQUIRE(app.getLedgerManager().getLedgerNum() == (ledgerSeq + 1));

	TxSetResultMeta res;
	std::transform(z1.results.begin(), z1.results.end(), z2.begin(),
		std::back_inserter(res), [](TransactionResultPair const& r1,
			LedgerEntryChanges const& r2)
	{
		return std::make_pair(r1, r2);
	});

	return res;
}

TxSetResultMeta
closeLedgerOn(Application& app, uint32 ledgerSeq, int day, int month, int year,
              TxSetFramePtr txSet)
{
	return closeLedgerOn(app, ledgerSeq, getTestDate(day, month, year), txSet);
    
}

[[deprecated("Use TestManager")]]
void upgradeToCurrentLedgerVersion(Application& app)
{
	TestManager::upgradeToCurrentLedgerVersion(app);
}

SecretKey
getRoot()
{
	return getMasterKP();
}

SecretKey
getIssuanceKey()
{
	return getIssuanceKP();
}

SecretKey
getAccount(const char* n)
{
	return getAccountSecret(n);
}


AccountFrame::pointer
loadAccount(SecretKey const& k, Application& app, bool mustExist)
{
	return loadAccount(k.getPublicKey(), app, mustExist);
}

AccountFrame::pointer
loadAccount(PublicKey const& k, Application& app, bool mustExist)
{
	AccountFrame::pointer res = accountHelper->loadAccount(k, app.getDatabase());
	if (mustExist)
	{
		REQUIRE(res);
	}
	return res;
}

BalanceFrame::pointer
loadBalance(BalanceID bid, Application& app, bool mustExist)
{
	BalanceFrame::pointer res =
		balanceHelper->loadBalance(bid, app.getDatabase());
	if (mustExist)
	{
		REQUIRE(res);
	}
	return res;
}

int64_t
getBalance(BalanceID const& k, Application& app)
{
    
    auto balance = balanceHelper->loadBalance(k, app.getDatabase());
    assert(balance);
    return balance->getAmount();
}

void
checkTransaction(TransactionFrame& txFrame)
{
    REQUIRE(txFrame.getResult().feeCharged == 0); // default fee
    REQUIRE((txFrame.getResultCode() == TransactionResultCode::txSUCCESS ||
             txFrame.getResultCode() == TransactionResultCode::txFAILED));
}

[[deprecated("Use txHelper")]]
TransactionFramePtr transactionFromOperation(Hash const& networkID, SecretKey& from,
                         Salt salt, Operation const& op, SecretKey* signer = nullptr, TimeBounds* timeBounds = nullptr)
{
    if (!signer)
        signer = &from;
    TransactionEnvelope e;

    e.tx.sourceAccount = from.getPublicKey();
    e.tx.salt = salt;
    e.tx.operations.push_back(op);

    e.tx.timeBounds.minTime = 0;
    e.tx.timeBounds.maxTime = INT64_MAX / 2;
	if (timeBounds)
	{
		e.tx.timeBounds = *timeBounds;
	}

    TransactionFramePtr res =
        TransactionFrame::makeTransactionFromWire(networkID, e);

    res->addSignature(*signer);

    return res;
}


TransactionFramePtr
createCreateAccountTx(Hash const& networkID, SecretKey& from, SecretKey& to,
                      Salt seq, AccountID* referrer,
					  TimeBounds* timeBounds, int32 policies)
{
    Operation op;
    op.body.type(OperationType::CREATE_ACCOUNT);
    op.body.createAccountOp().destination = to.getPublicKey();

    return transactionFromOperation(networkID, from, seq, op, nullptr, timeBounds);
}


void
applyCreateAccountTx(Application& app, SecretKey& from, SecretKey& to,
                     Salt seq, SecretKey* signer,
                     AccountID* referrer, CreateAccountResultCode result, int32 policies)
{
    TransactionFramePtr txFrame;

    AccountFrame::pointer fromAccount, toAccount;
    toAccount = loadAccount(to, app, false);

    fromAccount = loadAccount(from, app);

    txFrame = createCreateAccountTx(app.getNetworkID(), from, to, seq,
            referrer, nullptr, policies);
	if (signer)
	{
		txFrame->getEnvelope().signatures.clear();
		txFrame->addSignature(*signer);
	}

    LedgerDeltaImpl delta(app.getLedgerManager().getCurrentLedgerHeader(),
                          app.getDatabase());
    applyCheck(txFrame, delta, app);

    checkTransaction(*txFrame);
    auto txResult = txFrame->getResult();
    auto innerCode =
        CreateAccountOpFrame::getInnerCode(txResult.result.results()[0]);
    REQUIRE(innerCode == result);

    REQUIRE(txResult.feeCharged == app.getLedgerManager().getTxFee());

    AccountFrame::pointer toAccountAfter;
    toAccountAfter = loadAccount(to, app, false);

    if (innerCode != CreateAccountResultCode::SUCCESS)
    {
        // check that the target account didn't change
        REQUIRE(!!toAccount == !!toAccountAfter);
        if (toAccount && toAccountAfter)
        {
            REQUIRE(toAccount->getAccount() == toAccountAfter->getAccount());
        }
    }
    else
    {
        REQUIRE(toAccountAfter);
        
        auto statisticsFrame = statisticsHelper->loadStatistics(to.getPublicKey(), app.getDatabase());
        REQUIRE(statisticsFrame);
        auto statistics = statisticsFrame->getStatistics();
        REQUIRE(statistics.dailyOutcome == 0);
        REQUIRE(statistics.weeklyOutcome == 0);
        REQUIRE(statistics.monthlyOutcome == 0);
        REQUIRE(statistics.annualOutcome == 0);
        
        if (!toAccount) {
            std::vector<BalanceFrame::pointer> balances;
            balanceHelper->loadBalances(toAccountAfter->getAccount().accountID, balances, app.getDatabase());
			for (BalanceFrame::pointer balance : balances)
			{
				REQUIRE(balance->getBalance().amount == 0);
				REQUIRE(balance->getAccountID() == toAccountAfter->getAccount().accountID);
			}
        }
    }
}

void applyManageAssetTx(Application & app, SecretKey & source, Salt seq, AssetCode asset, int32 policies, ManageAssetAction action, ManageAssetResultCode result)
{
	throw std::runtime_error("use manageAssetHelper");
}

// For base balance
TransactionFramePtr
createPaymentTx(Hash const& networkID, SecretKey& from, SecretKey& to,
                Salt seq, int64_t amount, PaymentFeeData paymentFee, bool isSourceFee, std::string subject, std::string reference, TimeBounds* timeBounds)
{
    return createPaymentTx(networkID, from, from.getPublicKey(), to.getPublicKey(), seq, amount,paymentFee,
        isSourceFee, subject, reference, timeBounds);
}

TransactionFramePtr
createPaymentTx(Hash const& networkID, SecretKey& from, BalanceID fromBalanceID, BalanceID toBalanceID,
                Salt seq, int64_t amount, PaymentFeeData paymentFee, bool isSourceFee, std::string subject, std::string reference, TimeBounds* timeBounds)
{
    Operation op;
    op.body.type(OperationType::PAYMENT);
    op.body.paymentOp().amount = amount;
	op.body.paymentOp().feeData = paymentFee;
    op.body.paymentOp().subject = subject;
    op.body.paymentOp().sourceBalanceID = fromBalanceID;
    op.body.paymentOp().reference = reference;

    return transactionFromOperation(networkID, from, seq, op, nullptr, timeBounds);
}

TransactionFramePtr createSetFees(Hash const& networkID, SecretKey& source, Salt seq, FeeEntry* fee, bool isDelete)
{
	Operation op;
	op.body.type(OperationType::SET_FEES);
	auto& opBody = op.body.setFeesOp();
	if (fee)
		opBody.fee.activate() = *fee;
	opBody.isDelete = isDelete;

	return transactionFromOperation(networkID, source, seq, op);
}

void applySetFees(Application& app, SecretKey& source, Salt seq, FeeEntry* fee, bool isDelete, SecretKey* signer, SetFeesResultCode targetResult)
{
	auto txFrame = createSetFees(app.getNetworkID(), source, seq, fee, isDelete);
	if (signer)
	{
		txFrame->getEnvelope().signatures.clear();
		txFrame->addSignature(*signer);
	}

	LedgerDeltaImpl delta(app.getLedgerManager().getCurrentLedgerHeader(),
		app.getDatabase());

	applyCheck(txFrame, delta, app);

	auto result = txFrame->getResult().result.results()[0].tr().setFeesResult();
	REQUIRE(result.code() == targetResult);
	if (result.code() == SetFeesResultCode::SUCCESS)
	{
		if (fee)
		{
			auto storedFee = feeHelper->loadFee(fee->feeType, fee->asset,
				fee->accountID.get(), fee->accountRole.get(), fee->subtype, fee->lowerBound, fee->upperBound, app.getDatabase(), nullptr);
			if (isDelete)
				REQUIRE(!storedFee);
			else {
				REQUIRE(storedFee);
				REQUIRE(storedFee->getFee() == *fee);
			}
		}
	}
}

void fundAccount(Application& app, SecretKey& source, SecretKey& issuance,
    Salt& sourceSeq, BalanceID to, int64 amount, AssetCode asset)
{
}

[[deprecated]]
TransactionFramePtr createFundAccount(Hash const& networkID, SecretKey& source, SecretKey& issuance, Salt& sourceSeq, BalanceID to, int64 amount, AssetCode asset, uint32_t preemissionsPerOp, uint32_t emissionUnit, TimeBounds* timeBounds) {
	return nullptr;
}


OperationFrame const&
getFirstOperationFrame(TransactionFrame const& tx)
{
    return *(tx.getOperations()[0]);
}

OperationResult const&
getFirstResult(TransactionFrame const& tx)
{
    return getFirstOperationFrame(tx).getResult();
}

}
}
