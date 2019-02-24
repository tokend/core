// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <transactions/rule_verifing/SignerRuleVerifierImpl.h>
#include "TransactionFrameImpl.h"
#include "crypto/SHA.h"
#include "database/Database.h"
#include "herder/TxSetFrame.h"
#include "ledger/AccountHelperLegacy.h"
#include "ledger/BalanceHelperLegacy.h"
#include "ledger/FeeHelper.h"
#include "ledger/KeyValueHelperLegacy.h"
#include "ledger/LedgerDeltaImpl.h"
#include "ledger/StorageHelperImpl.h"
#include "main/Application.h"
#include "transactions/ManageKeyValueOpFrame.h"
#include "util/basen.h"

#include "medida/meter.h"
#include "medida/metrics_registry.h"
#include "transactions/rule_verifing/AccountRuleVerifierImpl.h"

namespace stellar
{

using namespace std;
using xdr::operator==;

TransactionFrameImpl::TransactionFrameImpl(Hash const& networkID,
                                           TransactionEnvelope const& envelope)
    : mEnvelope(envelope), mNetworkID(networkID)
{
}

Hash const&
TransactionFrameImpl::getFullHash() const
{
    if (isZero(mFullHash))
    {
        mFullHash = sha256(xdr::xdr_to_opaque(mEnvelope));
    }
    return (mFullHash);
}

Hash const&
TransactionFrameImpl::getContentsHash() const
{
    if (isZero(mContentsHash))
    {
        mContentsHash = sha256(
            xdr::xdr_to_opaque(mNetworkID, EnvelopeType::TX, mEnvelope.tx));
    }
    return (mContentsHash);
}

void
TransactionFrameImpl::clearCached()
{
    mSignatureValidator = nullptr;
    Hash zero;
    mContentsHash = zero;
    mFullHash = zero;
}

TransactionResultPair
TransactionFrameImpl::getResultPair() const
{
    TransactionResultPair trp;
    trp.transactionHash = getContentsHash();
    trp.result = mResult;
    return trp;
}

TransactionEnvelope const&
TransactionFrameImpl::getEnvelope() const
{
    return mEnvelope;
}

TransactionEnvelope&
TransactionFrameImpl::getEnvelope()
{
    return mEnvelope;
}

int64_t
TransactionFrameImpl::getPaidFee() const
{
    int64_t fee = 0;
    for (auto op : mOperations)
    {
        // tx is malformed in some way, return 0 to lower its piority
        if (fee + op->getPaidFee() < 0)
            return 0;
        fee += op->getPaidFee();
    }
    return fee;
}

void
TransactionFrameImpl::addSignature(SecretKey const& secretKey)
{
    clearCached();
    DecoratedSignature sig;
    sig.signature = secretKey.sign(getContentsHash());
    sig.hint = PubKeyUtils::getHint(secretKey.getPublicKey());
    mEnvelope.signatures.push_back(sig);
}

AccountFrame::pointer
TransactionFrameImpl::loadAccount(LedgerDelta* delta, Database& db,
                                  AccountID const& accountID)
{
    AccountFrame::pointer res;
    auto accountHelper = AccountHelperLegacy::Instance();

    if (mSigningAccount && mSigningAccount->getID() == accountID)
    {
        res = mSigningAccount;
    }
    else if (delta)
    {
        res = accountHelper->loadAccount(*delta, accountID, db);
    }
    else
    {
        res = accountHelper->loadAccount(accountID, db);
    }
    return res;
}

bool
TransactionFrameImpl::loadAccount(LedgerDelta* delta, Database& db)
{
    mSigningAccount = loadAccount(delta, db, getSourceID());
    return !!mSigningAccount;
}

void
TransactionFrameImpl::resetResults()
{
    // pre-allocates the results for all operations
    getResult().result.code(TransactionResultCode::txSUCCESS);
    getResult().result.results().resize(
        (uint32_t)mEnvelope.tx.operations.size());

    mOperations.clear();

    // bind operations to the results
    for (size_t i = 0; i < mEnvelope.tx.operations.size(); i++)
    {
        mOperations.push_back(
            OperationFrame::makeHelper(mEnvelope.tx.operations[i],
                                       getResult().result.results()[i], *this));
    }
    // feeCharged is updated accordingly to represent the cost of the
    // transaction regardless of the failure modes.
    getResult().feeCharged = getPaidFee();
}

bool
TransactionFrameImpl::doCheckSignature(Application& app,
                                       StorageHelper& storageHelper,
                                       AccountID const& accountID)
{
    SignerRuleVerifierImpl signerRuleVerifier;
    auto result = getSignatureValidator()->check(app, storageHelper,
            signerRuleVerifier, accountID, {});
    switch (result)
    {
    case SignatureValidator::Result::SUCCESS:
        return true;
    case SignatureValidator::Result::INVALID_ACCOUNT_TYPE:
        throw runtime_error("Did not expect INVALID_ACCOUNT_TYPE error for tx");
    case SignatureValidator::Result::NOT_ENOUGH_WEIGHT:
        app.getMetrics()
            .NewMeter({"transaction", "invalid", "bad-auth"}, "transaction")
            .Mark();
        getResult().result.code(TransactionResultCode::txBAD_AUTH);
        return false;
    case SignatureValidator::Result::EXTRA:
        app.getMetrics()
            .NewMeter({"transaction", "invalid", "bad-auth-extra"},
                      "transaction")
            .Mark();
        getResult().result.code(TransactionResultCode::txBAD_AUTH_EXTRA);
        return false;
    case SignatureValidator::Result::ACCOUNT_BLOCKED:
        app.getMetrics()
            .NewMeter({"transaction", "invalid", "account-blocked"},
                      "transaction")
            .Mark();
        getResult().result.code(TransactionResultCode::txACCOUNT_BLOCKED);
        return false;
    }

    throw runtime_error("Unexpected error code from signatureValidator");
}

bool
TransactionFrameImpl::isLicenseOp()
{
    return mEnvelope.tx.operations.size() == 1
    && mEnvelope.tx.operations[0].body.type() == OperationType::LICENSE;
}

bool
TransactionFrameImpl::commonValid(Application& app, LedgerDelta* delta)
{
    if (mOperations.size() == 0)
    {
        app.getMetrics()
            .NewMeter({"transaction", "invalid", "missing-operation"},
                      "transaction")
            .Mark();
        getResult().result.code(TransactionResultCode::txMISSING_OPERATION);
        return false;
    }

    auto& lm = app.getLedgerManager();

    uint64 closeTime = lm.getCurrentLedgerHeader().scpValue.closeTime;

    if (mEnvelope.tx.timeBounds.minTime > closeTime)
    {
        app.getMetrics()
            .NewMeter({"transaction", "invalid", "too-early"}, "transaction")
            .Mark();
        getResult().result.code(TransactionResultCode::txTOO_EARLY);
        return false;
    }
    if (mEnvelope.tx.timeBounds.maxTime < closeTime ||
            (!isLicenseOp() && mEnvelope.tx.timeBounds.maxTime - closeTime >
            lm.getTxExpirationPeriod())
            )
    {
        app.getMetrics()
            .NewMeter({"transaction", "invalid", "too-late"}, "transaction")
            .Mark();
        getResult().result.code(TransactionResultCode::txTOO_LATE);
        return false;
    }

    auto& db = app.getDatabase();

    if (!loadAccount(delta, db))
    {
        app.getMetrics()
            .NewMeter({"transaction", "invalid", "no-account"}, "transaction")
            .Mark();
        getResult().result.code(TransactionResultCode::txNO_ACCOUNT);
        return false;
    }

    StorageHelperImpl storageHelper(db, delta);
    AccountRuleVerifierImpl accountRuleVerifier;
    if (!checkSendTxRule(accountRuleVerifier, storageHelper))
    {
        return false;
    }

    // error code already set
    return doCheckSignature(app, storageHelper, getSourceID());
}

bool
TransactionFrameImpl::checkSendTxRule(AccountRuleVerifier& accountRuleVerifier,
                                      StorageHelper& storageHelper)
{
    AccountRuleResource resource(LedgerEntryType::TRANSACTION);
    AccountRuleAction action(AccountRuleAction::SEND);
    
    OperationCondition operationCondition(resource, action, mSigningAccount);

    if (!accountRuleVerifier.isAllowed(operationCondition, storageHelper)) 
    {
        getResult().result.code(TransactionResultCode::txNO_ROLE_PERMISSION);
        auto& requirement = getResult().result.requirement();
        requirement.resource = resource;
        requirement.action = action;
        requirement.account = mSigningAccount->getID();
        return false;
    }
    
    return true;
}

void
TransactionFrameImpl::setSourceAccountPtr(AccountFrame::pointer signingAccount)
{
    if (!signingAccount)
    {
        if (!(mEnvelope.tx.sourceAccount == signingAccount->getID()))
        {
            throw std::invalid_argument("wrong account");
        }
    }
    mSigningAccount = signingAccount;
}

void
TransactionFrameImpl::resetSignatureTracker()
{
    mSigningAccount.reset();
    auto signatureValidator = getSignatureValidator();
    signatureValidator->resetSignatureTracker();
}

bool
TransactionFrameImpl::checkAllSignaturesUsed()
{
    auto signatureValidator = getSignatureValidator();
    if (signatureValidator->checkAllSignaturesUsed())
        return true;

    getResult().result.code(TransactionResultCode::txBAD_AUTH_EXTRA);
    return false;
}

bool
TransactionFrameImpl::checkValid(Application& app)
{
    resetSignatureTracker();
    resetResults();
    bool res = commonValid(app, nullptr);
    if (!res)
    {
        return res;
    }

    AccountRuleVerifierImpl accountRuleVerifier;
    for (auto& op : mOperations)
    {
        if (!op->checkValid(app, accountRuleVerifier))
        {
            // it's OK to just fast fail here and not try to call
            // checkValid on all operations as the resulting object
            // is only used by applications
            app.getMetrics()
                .NewMeter({"transaction", "invalid", "invalid-op"},
                          "transaction")
                .Mark();
            markResultFailed();
            return false;
        }
    }
    res = checkAllSignaturesUsed();
    if (!res)
    {
        app.getMetrics()
            .NewMeter({"transaction", "invalid", "bad-auth-extra"},
                      "transaction")
            .Mark();
        return false;
    }

    string txIDString(binToHex(getContentsHash()));
    if (TransactionFrame::timingExists(app.getDatabase(), txIDString))
    {
        app.getMetrics()
            .NewMeter({"transaction", "invalid", "duplication"}, "transaction")
            .Mark();
        getResult().result.code(TransactionResultCode::txDUPLICATION);
        return false;
    }

    return res;
}

void
TransactionFrameImpl::markResultFailed()
{
    // changing "code" causes the xdr struct to be deleted/re-created
    // As we want to preserve the results, we save them inside a temp object
    // Also, note that because we're using move operators
    // mOperations are still valid (they have pointers to the individual
    // results elements)
    xdr::xvector<OperationResult> t(std::move(getResult().result.results()));
    getResult().result.code(TransactionResultCode::txFAILED);
    getResult().result.results() = std::move(t);

    // sanity check in case some implementations decide
    // to not implement std::move properly
    auto const& allResults = getResult().result.results();
    assert(allResults.size() == mOperations.size());
    for (size_t i = 0; i < mOperations.size(); i++)
    {
        assert(&mOperations[i]->getResult() == &allResults[i]);
    }
}

bool
TransactionFrameImpl::applyTx(LedgerDelta& delta, TransactionMeta& meta,
                              Application& app,
                              vector<LedgerDelta::KeyEntryMap>& stateBeforeOp)
{
    resetSignatureTracker();
    if (!commonValid(app, &delta))
    {
        return false;
    }

    bool errorEncountered = false;

    {
        // shield outer scope of any side effects by using
        // a sql transaction for ledger state and LedgerDelta
        soci::transaction sqlTx(app.getDatabase().getSession());
        LedgerDeltaImpl thisTxDelta(delta);

        string txIDString(binToHex(getContentsHash()));
        auto& txInternal = app.getConfig().TX_INTERNAL_ERROR;
        if (txInternal.find(txIDString) != txInternal.end())
        {
            throw runtime_error(
                "Throwing exception to have consistent blockchain");
        }

        auto& opTimer =
            app.getMetrics().NewTimer({"transaction", "op", "apply"});

        for (auto& op : mOperations)
        {
            auto time = opTimer.TimeScope();
            LedgerDeltaImpl opDeltaImpl(thisTxDelta);
            LedgerDelta& opDelta = opDeltaImpl;
            StorageHelperImpl storageHelperImpl(app.getDatabase(), &opDelta);
            StorageHelper& storageHelper = storageHelperImpl;
            storageHelper.begin();

            bool txRes = op->apply(storageHelper, app);

            if (!txRes)
            {
                errorEncountered = true;
            }
            stateBeforeOp.push_back(opDelta.getState());
            meta.operations().emplace_back(opDelta.getAllChanges());

            storageHelper.commit();
        }

        if (!errorEncountered)
        {
            if (!checkAllSignaturesUsed())
            {
                // this should never happen: malformed transaction should not be
                // accepted by nodes
                return false;
            }

            sqlTx.commit();
            static_cast<LedgerDelta&>(thisTxDelta).commit();
        }
    }

    if (errorEncountered)
    {
        meta.operations().clear();
        markResultFailed();
    }

    return !errorEncountered;
}

void
TransactionFrameImpl::unwrapNestedException(const exception& e,
                                            stringstream& str)
{
    str << e.what();
    try
    {
        rethrow_if_nested(e);
    }
    catch (const exception& nested)
    {
        str << "->";
        unwrapNestedException(nested, str);
    }
}

bool
TransactionFrameImpl::apply(LedgerDelta& delta, Application& app)
{
    TransactionMeta tm;
    vector<LedgerDelta::KeyEntryMap> stateBeforeOp;
    return apply(delta, tm, app, stateBeforeOp);
}

bool
TransactionFrameImpl::apply(LedgerDelta& delta, TransactionMeta& meta,
                            Application& app,
                            vector<LedgerDelta::KeyEntryMap>& stateBeforeOp)
{
    try
    {
        return applyTx(delta, meta, app, stateBeforeOp);
    }
    catch (exception& e)
    {
        stringstream details;
        unwrapNestedException(e, details);
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Failed to apply tx: " << details.str();
        throw;
    }
}

StellarMessage
TransactionFrameImpl::toStellarMessage() const
{
    StellarMessage msg;
    msg.type(MessageType::TRANSACTION);
    msg.transaction() = mEnvelope;
    return msg;
}

void
TransactionFrameImpl::storeTransaction(LedgerManager& ledgerManager,
                                       TransactionMeta& tm, int txindex,
                                       TransactionResultSet& resultSet) const
{
    auto txBytes(xdr::xdr_to_opaque(mEnvelope));

    resultSet.results.emplace_back(getResultPair());
    auto txResultBytes(xdr::xdr_to_opaque(resultSet.results.back()));

    std::string txBody;
    txBody = bn::encode_b64(txBytes);

    std::string txResult;
    txResult = bn::encode_b64(txResultBytes);

    xdr::opaque_vec<> txMeta(xdr::xdr_to_opaque(tm));

    std::string meta;
    meta = bn::encode_b64(txMeta);

    string txIDString(binToHex(getContentsHash()));

    auto& db = ledgerManager.getDatabase();
    auto prep = db.getPreparedStatement(
        "INSERT INTO txhistory "
        "( txid, ledgerseq, txindex,  txbody, txresult, txmeta) VALUES "
        "(:id,  :seq,      :txindex, :txb,   :txres,   :meta)");

    auto& st = prep.statement();
    st.exchange(soci::use(txIDString));
    st.exchange(soci::use(ledgerManager.getCurrentLedgerHeader().ledgerSeq));
    st.exchange(soci::use(txindex));
    st.exchange(soci::use(txBody));
    st.exchange(soci::use(txResult));
    st.exchange(soci::use(meta));
    st.define_and_bind();
    {
        auto timer = db.getInsertTimer("txhistory");
        st.execute(true);
    }

    if (st.get_affected_rows() != 1)
    {
        throw std::runtime_error("Could not update data in SQL");
    }
}

void
TransactionFrameImpl::processSeqNum()
{
    resetSignatureTracker();
    resetResults();
}

void
TransactionFrameImpl::storeTransactionTiming(LedgerManager& ledgerManager,
                                             uint64 maxTime) const
{
    string txIDString(binToHex(getContentsHash()));

    auto& db = ledgerManager.getDatabase();
    auto prep = db.getPreparedStatement("INSERT INTO txtiming "
                                        "( txid, valid_before) VALUES "
                                        "(:id,  :vb)");

    auto& st = prep.statement();
    st.exchange(soci::use(txIDString));
    st.exchange(soci::use(maxTime));
    st.define_and_bind();
    {
        auto timer = db.getInsertTimer("txtiming");
        st.execute(true);
    }

    if (st.get_affected_rows() != 1)
    {
        throw std::runtime_error("Could not update data in SQL");
    }
}

void
TransactionFrameImpl::storeTransactionFee(LedgerManager& ledgerManager,
                                          LedgerEntryChanges const& changes,
                                          int txindex) const
{
    xdr::opaque_vec<> txChanges(xdr::xdr_to_opaque(changes));

    std::string txChanges64;
    txChanges64 = bn::encode_b64(txChanges);

    string txIDString(binToHex(getContentsHash()));

    auto& db = ledgerManager.getDatabase();
    auto prep = db.getPreparedStatement(
        "INSERT INTO txfeehistory "
        "( txid, ledgerseq, txindex,  txchanges) VALUES "
        "(:id,  :seq,      :txindex, :txchanges)");

    auto& st = prep.statement();
    st.exchange(soci::use(txIDString));
    st.exchange(soci::use(ledgerManager.getCurrentLedgerHeader().ledgerSeq));
    st.exchange(soci::use(txindex));
    st.exchange(soci::use(txChanges64));
    st.define_and_bind();
    {
        auto timer = db.getInsertTimer("txfeehistory");
        st.execute(true);
    }

    if (st.get_affected_rows() != 1)
    {
        throw std::runtime_error("Could not update data in SQL");
    }
}
} // namespace stellar
