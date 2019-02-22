#pragma once

// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "overlay/StellarXDR.h"
#include "crypto/SecretKey.h"
#include "ledger/AccountFrame.h"
#include "util/optional.h"
#include "ledger/FeeFrame.h"
#include "herder/LedgerCloseData.h"

namespace stellar
{
class TransactionFrame;
class LedgerDelta;
class OperationFrame;
class TxSetFrame;

namespace txtest
{

typedef std::vector<std::pair<TransactionResultPair, LedgerEntryChanges>>
    TxSetResultMeta;

FeeEntry createFeeEntry(FeeType type, int64_t fixed, int64_t percent,
    AssetCode asset, AccountID* accountID = nullptr, uint64_t* accountType = nullptr,
    int64_t subtype = FeeFrame::SUBTYPE_ANY, int64_t lowerBound = 0, int64_t upperBound = INT64_MAX);

PaymentFeeData getNoPaymentFee();
PaymentFeeData getGeneralPaymentFee(uint64 fixedFee, uint64 paymentFee);
    
bool applyCheck(TransactionFramePtr tx, LedgerDelta& delta, Application& app);

void checkEntry(LedgerEntry const& le, Application& app);
void checkAccount(AccountID const& id, Application& app);

time_t getTestDate(int day, int month, int year);

TxSetResultMeta closeLedgerOn(Application& app, uint32 ledgerSeq, int day,
                              int month, int year,
                              TransactionFramePtr tx = nullptr);

TxSetResultMeta closeLedgerOn(Application& app, uint32 ledgerSeq, time_t closeTime);

TxSetResultMeta
closeLedgerOn(Application& app, uint32 ledgerSeq, time_t closeTime, TxSetFramePtr txSet);

TxSetResultMeta closeLedgerOn(Application& app, uint32 ledgerSeq, int day,
                              int month, int year, TxSetFramePtr txSet);

void upgradeToCurrentLedgerVersion(Application& app);

SecretKey getRoot();
SecretKey getIssuanceKey();

SecretKey getAccount(const char* n);

// shorthand to load an existing account
AccountFrame::pointer loadAccount(SecretKey const& k, Application& app,
                                  bool mustExist = true);

// shorthand to load an existing account
AccountFrame::pointer loadAccount(PublicKey const& k, Application& app,
	bool mustExist = true);

BalanceFrame::pointer loadBalance(BalanceID bid, Application& app,
                                  bool mustExist = true);

int64_t getBalance(BalanceID const& k, Application& app);

TransactionFramePtr createCreateAccountTx(Hash const& networkID,
                                          SecretKey& from, SecretKey& to,
                                          Salt seq,
                                          AccountID* referrer = nullptr, TimeBounds* timeBounds = nullptr, int32 policies = -1);

void
applyCreateAccountTx(Application& app, SecretKey& from, SecretKey& to,
                     Salt seq,
                     SecretKey* signer = nullptr, AccountID* referrer = nullptr,
                     CreateAccountResultCode result = CreateAccountResultCode::SUCCESS, int32 policies = -1);

void
applyManageAssetTx(Application& app, SecretKey& source, Salt seq,
				   AssetCode asset, int32 policies = 1,
				   ManageAssetAction action  = ManageAssetAction::CREATE_ASSET_CREATION_REQUEST,
				   ManageAssetResultCode result = ManageAssetResultCode::SUCCESS);

TransactionFramePtr createPaymentTx(Hash const& networkID, SecretKey& from,
    BalanceID fromBalanceID, BalanceID toBalanceID, Salt seq, int64_t amount,
    PaymentFeeData paymentFee, bool isSourceFee = false, std::string subject = "",
    std::string reference="", TimeBounds* timeBounds = nullptr);


TransactionFramePtr createPaymentTx(Hash const& networkID, SecretKey& from, SecretKey& to,
    Salt seq, int64_t amount, PaymentFeeData paymentFee, bool isSourceFee = false,
    std::string subject = "", std::string reference="", TimeBounds* timeBounds = nullptr);

TransactionFramePtr createSetFees(Hash const& networkID,
	SecretKey& source, Salt seq, FeeEntry* fee, bool isDelete);

void applySetFees(Application& app, SecretKey& source, Salt seq, FeeEntry* fees, bool isDelete, SecretKey* signer = nullptr,
				  SetFeesResultCode result = SetFeesResultCode::SUCCESS);

void fundAccount(Application& app, SecretKey& source, SecretKey& issuance,
    Salt& sourceSeq, BalanceID to, int64 amount, AssetCode asset = "XAAU");

TransactionFramePtr createFundAccount(Hash const& networkID, SecretKey& source, SecretKey& issuance,
	Salt& sourceSeq, BalanceID to, int64 amount, AssetCode asset, uint32_t preemissionsPerOp, uint32_t emissionUnit, TimeBounds* timeBounds = nullptr);


OperationFrame const& getFirstOperationFrame(TransactionFrame const& tx);
OperationResult const& getFirstResult(TransactionFrame const& tx);

} // end txtest namespace
}
