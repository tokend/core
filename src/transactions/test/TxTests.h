#pragma once

// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "overlay/StellarXDR.h"
#include "crypto/SecretKey.h"
#include "ledger/AccountFrame.h"
#include "ledger/AccountTypeLimitsFrame.h"
#include "util/optional.h"
#include "ledger/FeeFrame.h"
#include "herder/LedgerCloseData.h"
#include "test_helper/SetOptionsTestHelper.h"

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
    AssetCode asset, AccountID* accountID = nullptr, AccountType* accountType = nullptr,
    int64_t subtype = FeeFrame::SUBTYPE_ANY, int64_t lowerBound = 0, int64_t upperBound = INT64_MAX);

PaymentFeeDataV2 getNoPaymentFee();
PaymentFeeDataV2 getGeneralPaymentFee(uint64 fixedFee, uint64 paymentFee);
    
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


// short hand to check that an account does not exist
void requireNoAccount(SecretKey const& k, Application& app);

int64_t getAccountBalance(SecretKey const& k, Application& app);
int64_t getAccountBalance(PublicKey const& k, Application& app);
int64_t getBalance(BalanceID const& k, Application& app);

void
checkTransactionForOpResult(TransactionFramePtr txFrame, Application& app, OperationResultCode opCode);

TransactionFramePtr createCreateAccountTx(Hash const& networkID,
                                          SecretKey& from, SecretKey& to,
                                          Salt seq, AccountType accountType,
                                          AccountID* referrer = nullptr, TimeBounds* timeBounds = nullptr, int32 policies = -1);

void
applyCreateAccountTx(Application& app, SecretKey& from, SecretKey& to,
                     Salt seq, AccountType accountType,
                     SecretKey* signer = nullptr, AccountID* referrer = nullptr,
                     CreateAccountResultCode result = CreateAccountResultCode::SUCCESS, int32 policies = -1);



TransactionFramePtr createManageBalanceTx(Hash const& networkID,
                                          SecretKey& from, SecretKey& account,
                                          Salt seq, AssetCode asset, ManageBalanceAction action);

ManageBalanceResult
applyManageBalanceTx(Application& app, SecretKey& from, SecretKey& account, Salt seq,
        AssetCode asset = "AETH",
        ManageBalanceAction action  = ManageBalanceAction::CREATE, ManageBalanceResultCode result = ManageBalanceResultCode::SUCCESS);


TransactionFramePtr createManageAssetTx(Hash const& networkID, SecretKey& source,
										Salt seq, AssetCode code,
										int32 policies, ManageAssetAction action);

void
applyManageAssetTx(Application& app, SecretKey& source, Salt seq,
				   AssetCode asset, int32 policies = 1,
				   ManageAssetAction action  = ManageAssetAction::CREATE_ASSET_CREATION_REQUEST,
				   ManageAssetResultCode result = ManageAssetResultCode::SUCCESS);

TransactionFramePtr createPaymentTx(Hash const& networkID, SecretKey& from,
    BalanceID fromBalanceID, BalanceID toBalanceID, Salt seq, int64_t amount,
    PaymentFeeDataV2 paymentFee, bool isSourceFee = false, std::string subject = "",
    std::string reference="", TimeBounds* timeBounds = nullptr);


TransactionFramePtr createPaymentTx(Hash const& networkID, SecretKey& from, SecretKey& to,
    Salt seq, int64_t amount, PaymentFeeDataV2 paymentFee, bool isSourceFee = false,
    std::string subject = "", std::string reference="", TimeBounds* timeBounds = nullptr);

PaymentV2Result applyPaymentTx(Application& app, SecretKey& from, BalanceID fromBalanceID, BalanceID toBalanceID,
    Salt seq, int64_t amount, PaymentFeeDataV2 paymentFee, bool isSourceFee,
    std::string subject = "", std::string reference="",
    PaymentV2ResultCode result = PaymentV2ResultCode::SUCCESS);

PaymentV2Result applyPaymentTx(Application& app, SecretKey& from, SecretKey& to,
                    Salt seq, int64_t amount, PaymentFeeDataV2 paymentFee, bool isSourceFee,
                    std::string subject = "", std::string reference="",
                    PaymentV2ResultCode result = PaymentV2ResultCode::SUCCESS);

TransactionFramePtr
createReviewPaymentRequestTx(Hash const& networkID, SecretKey& exchange,
                Salt seq, int64 paymentID,  bool accept = true);

TransactionFramePtr createSetOptions(Hash const& networkID, SecretKey& source, Salt seq,
                                     ThresholdSetter* thrs, Signer* signer,
                                     TrustData* trustData = nullptr);

void applySetOptions(Application& app, SecretKey& source, Salt seq, ThresholdSetter* thrs,
                     Signer* signer, TrustData* trustData = nullptr,
                     SetOptionsResultCode targetResult = SetOptionsResultCode::SUCCESS, SecretKey* txSiger = nullptr);

/*TransactionFramePtr createUploadPreemissions(Hash const& networkID, SecretKey& source, Salt seq,
	std::vector<PreEmission> preEmissions);

void applyUploadPreemissions(Application& app, SecretKey& source, Salt seq,
	std::vector<PreEmission> preEmissions,
	UploadPreemissionsResultCode targetResult = UPLOAD_PREEMISSIONS_SUCCESS);*/


TransactionFramePtr createManageAccount(Hash const& networkID,
	SecretKey& source, SecretKey& account,
	Salt seq, uint32 blockReasonsToAdd, uint32 blockReasonsToRemove, AccountType accountType = AccountType::GENERAL);

void
applyManageAccountTx(Application& app, SecretKey& source, SecretKey& account,
	Salt seq, uint32 blockReasonsToAdd = 0, uint32 blockReasonsToRemove = 0,
    AccountType accountType = AccountType::GENERAL,
    ManageAccountResultCode result = ManageAccountResultCode::SUCCESS);

TransactionFramePtr createSetFees(Hash const& networkID,
	SecretKey& source, Salt seq, FeeEntry* fee, bool isDelete);

void applySetFees(Application& app, SecretKey& source, Salt seq, FeeEntry* fees, bool isDelete, SecretKey* signer = nullptr,
				  SetFeesResultCode result = SetFeesResultCode::SUCCESS);

void uploadPreemissions(Application& app, SecretKey& source, SecretKey& issuance,
	Salt sourceSeq, int64 amount, AssetCode asset);
void fundAccount(Application& app, SecretKey& source, SecretKey& issuance,
    Salt& sourceSeq, BalanceID to, int64 amount, AssetCode asset = "XAAU");

TransactionFramePtr createFundAccount(Hash const& networkID, SecretKey& source, SecretKey& issuance,
	Salt& sourceSeq, BalanceID to, int64 amount, AssetCode asset, uint32_t preemissionsPerOp, uint32_t emissionUnit, TimeBounds* timeBounds = nullptr);


OperationFrame const& getFirstOperationFrame(TransactionFrame const& tx);
OperationResult const& getFirstResult(TransactionFrame const& tx);
OperationResultCode getFirstResultCode(TransactionFrame const& tx);

// modifying the type of the operation will lead to undefined behavior
Operation& getFirstOperation(TransactionFrame& tx);

void reSignTransaction(TransactionFrame& tx, SecretKey& source);

// checks that b-maxd <= a <= b
// bias towards seller means
//    * amount left in an offer should be higher than the exact calculation
//    * amount received by a seller should be higher than the exact calculation
void checkAmounts(int64_t a, int64_t b, int64_t maxd = 1);

// methods to check results based off meta data
void checkTx(int index, TxSetResultMeta& r, TransactionResultCode expected);

void checkTx(int index, TxSetResultMeta& r, TransactionResultCode expected,
             OperationResultCode code);

} // end txtest namespace
}
