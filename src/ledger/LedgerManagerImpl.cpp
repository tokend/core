// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <numeric>
#include "ledger/LedgerManagerImpl.h"
#include "bucket/BucketManager.h"
#include "crypto/Hex.h"
#include "crypto/SHA.h"
#include "crypto/SecretKey.h"
#include "database/Database.h"
#include "herder/Herder.h"
#include "herder/HerderPersistence.h"
#include "herder/LedgerCloseData.h"
#include "herder/TxSetFrame.h"
#include "herder/Upgrades.h"
#include "history/HistoryManager.h"
#include "ledger/LedgerDeltaImpl.h"
#include "invariant/InvariantDoesNotHold.h"
#include "invariant/InvariantManager.h"
#include "ledger/LedgerHeaderUtils.h"
#include "ledger/LedgerRange.h"
#include "main/Application.h"
#include "main/Config.h"
#include "StorageHelperImpl.h"

#include "overlay/OverlayManager.h"
#include "util/XDROperators.h"
#include "util/format.h"

#include "medida/meter.h"
#include "medida/metrics_registry.h"
#include "xdrpp/printer.h"
#include "AccountRuleHelperImpl.h"
#include "AccountRoleHelperImpl.h"
#include "SignerRuleFrame.h"
#include "SignerRuleHelper.h"
#include "SignerRoleHelper.h"
#include "SignerHelper.h"
#include "AccountHelper.h"

/*
The ledger module:
    1) gets the externalized tx set
    2) applies this set to the last closed ledger
    3) sends the changed entries to the BucketList
    4) saves the changed entries to SQL
    5) saves the ledger hash and header to SQL
    6) sends the new ledger hash and the tx set to the history
    7) sends the new ledger hash and header to the Herder


catching up to network:
    1) Wait for SCP to tell us what the network is on now
    2) Pull history log or static deltas from history archive
    3) Replay or force-apply deltas, depending on catchup mode

*/
using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;
using namespace std;

namespace stellar
{

const uint32_t LedgerManager::GENESIS_LEDGER_SEQ = 1;

std::unique_ptr<LedgerManager>
LedgerManager::create(Application& app)
{
    return std::make_unique<LedgerManagerImpl>(app);
}

std::string
LedgerManager::ledgerAbbrev(LedgerHeader const& header)
{
    return ledgerAbbrev(header, sha256(xdr::xdr_to_opaque(header)));
}

std::string
LedgerManager::ledgerAbbrev(uint32_t seq, uint256 const& hash)
{
    std::ostringstream oss;
    oss << "[seq=" << seq << ", hash=" << hexAbbrev(hash) << "]";
    return oss.str();
}

std::string
LedgerManager::ledgerAbbrev(LedgerHeader const& header, uint256 const& hash)
{
    return ledgerAbbrev(header.ledgerSeq, hash);
}

std::string
LedgerManager::ledgerAbbrev(LedgerHeaderHistoryEntry he)
{
    return ledgerAbbrev(he.header, he.hash);
}

std::string
LedgerManager::ledgerAbbrev(LedgerHeaderFrame::pointer p)
{
    if (!p)
    {
        return "[empty]";
    }
    return ledgerAbbrev(p->getHeader(), p->getHash());
}

LedgerManagerImpl::LedgerManagerImpl(Application& app)
    : mApp(app)
    , mTransactionApply(
          app.getMetrics().NewTimer({"ledger", "transaction", "apply"}))
    , mTransactionCount(
            app.getMetrics().NewHistogram({"ledger", "transaction", "count"}))
    , mOperationCount(
            app.getMetrics().NewHistogram({"ledger", "operation", "count"}))
    , mInternalErrorCount(app.getMetrics().NewCounter(
          {"ledger", "transaction", "internal-error"}))
    , mLedgerClose(app.getMetrics().NewTimer({"ledger", "ledger", "close"}))
    , mLedgerAgeClosed(app.getMetrics().NewTimer({"ledger", "age", "closed"}))
    , mLedgerAge(
          app.getMetrics().NewCounter({"ledger", "age", "current-seconds"}))
    , mLastClose(mApp.getClock().now())
    , mSyncingLedgersSize(
            app.getMetrics().NewCounter({"ledger", "memory", "queued-ledgers"}))
    , mState(LM_BOOTING_STATE)

{
    std::string raw = "GAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAWHF";
    mNotExistingAccount = PubKeyUtils::fromStrKey(raw);
}

void
LedgerManagerImpl::bootstrap()
{
    setState(LM_SYNCED_STATE);
}

AccountID
LedgerManagerImpl::getNotExistingAccountID()
{
    return mNotExistingAccount;
}

void
LedgerManagerImpl::setState(State s)
{
    if (s != getState())
    {
        std::string oldState = getStateHuman();
        mState = s;
        mApp.syncOwnMetrics();
        CLOG(INFO, "Ledger") << "Changing state " << oldState << " -> "
                             << getStateHuman();
        if (mState != LM_CATCHING_UP_STATE)
        {
            mCatchupState = CatchupState::NONE;
            mApp.getCatchupManager().logAndUpdateCatchupStatus(true);
        }
    }
}

LedgerManager::State
LedgerManagerImpl::getState() const
{
    return mState;
}

void
LedgerManagerImpl::setCatchupState(CatchupState s)
{
    mCatchupState = s;
    setState(LM_CATCHING_UP_STATE);
}

LedgerManager::CatchupState
LedgerManagerImpl::getCatchupState() const
{
    return mCatchupState;
}

std::string
LedgerManagerImpl::getStateHuman() const
{
    static const char* stateStrings[LM_NUM_STATE] = {
        "LM_BOOTING_STATE", "LM_SYNCED_STATE", "LM_CATCHING_UP_STATE"};
    return std::string(stateStrings[getState()]);
}

void
LedgerManagerImpl::createDefaultSignerRules(StorageHelper &storageHelper,
                                            uint64_t const ownerRoleID)
{
    auto& ledgerHeader = storageHelper.mustGetLedgerDelta().getHeaderFrame();

    // restrict any operations with default signer rule
    LedgerEntry firstSignerRuleEntry;
    firstSignerRuleEntry.data.type(LedgerEntryType::SIGNER_RULE);
    auto& firstSignerRule = firstSignerRuleEntry.data.signerRule();
    SignerRuleResource ruleResource(LedgerEntryType::SIGNER_RULE);
    ruleResource.signerRule().isDefault = true;
    firstSignerRule.resource = ruleResource;
    firstSignerRule.action = SignerRuleAction::ANY;
    firstSignerRule.id = ledgerHeader.generateID(LedgerEntryType::SIGNER_RULE);
    firstSignerRule.isDefault = true;
    firstSignerRule.forbids = true;
    firstSignerRule.ownerID = mNotExistingAccount;
    firstSignerRule.details = "{}";

    auto& helper = storageHelper.getSignerRuleHelper();
    helper.storeAdd(firstSignerRuleEntry);

    // restric any operations with default role
    LedgerEntry secondSignerRuleEntry;
    secondSignerRuleEntry.data.type(LedgerEntryType::SIGNER_RULE);
    auto& secondSignerRule = secondSignerRuleEntry.data.signerRule();
    SignerRuleResource roleResource(LedgerEntryType::SIGNER_ROLE);
    roleResource.signerRole().roleID = ownerRoleID;
    secondSignerRule.resource = roleResource;
    secondSignerRule.action = SignerRuleAction::ANY;
    secondSignerRule.id = ledgerHeader.generateID(LedgerEntryType::SIGNER_RULE);
    secondSignerRule.isDefault = true;
    secondSignerRule.forbids = true;
    secondSignerRule.ownerID = mNotExistingAccount;
    secondSignerRule.details = "{}";

    helper.storeAdd(secondSignerRuleEntry);

    // restric any operations with recovery signer
    LedgerEntry thirdSignerRuleEntry;
    thirdSignerRuleEntry.data.type(LedgerEntryType::SIGNER_RULE);
    auto& thirdSignerRule = thirdSignerRuleEntry.data.signerRule();
    SignerRuleResource signerResource(LedgerEntryType::SIGNER);
    signerResource.signer().roleID = ownerRoleID;
    thirdSignerRule.resource = signerResource;
    thirdSignerRule.action = SignerRuleAction::ANY;
    thirdSignerRule.id = ledgerHeader.generateID(LedgerEntryType::SIGNER_RULE);
    thirdSignerRule.isDefault = true;
    thirdSignerRule.forbids = true;
    thirdSignerRule.ownerID = mNotExistingAccount;
    thirdSignerRule.details = "{}";

    helper.storeAdd(thirdSignerRuleEntry);
}

uint64_t
LedgerManagerImpl::createAdminSigner(StorageHelper &storageHelper)
{
    auto& ledgerHeader = storageHelper.mustGetLedgerDelta().getHeaderFrame();

    LedgerEntry signerRuleEntry;
    signerRuleEntry.data.type(LedgerEntryType::SIGNER_RULE);
    auto& signerRule = signerRuleEntry.data.signerRule();
    signerRule.resource = SignerRuleResource(LedgerEntryType::ANY);
    signerRule.action = SignerRuleAction::ANY;
    signerRule.id = ledgerHeader.generateID(LedgerEntryType::SIGNER_RULE);
    signerRule.isDefault = false;
    signerRule.forbids = false;
    signerRule.ownerID = mNotExistingAccount;
    signerRule.details = "{}";

    storageHelper.getSignerRuleHelper().storeAdd(signerRuleEntry);

    LedgerEntry signerRoleEntry;
    signerRoleEntry.data.type(LedgerEntryType::SIGNER_ROLE);
    auto& signerRole = signerRoleEntry.data.signerRole();
    signerRole.id = ledgerHeader.generateID(LedgerEntryType::SIGNER_ROLE);
    signerRole.ownerID = mNotExistingAccount;
    signerRole.details = "{}";
    signerRole.ruleIDs = {signerRule.id};

    storageHelper.getSignerRoleHelper().storeAdd(signerRoleEntry);

    LedgerEntry signerEntry;
    signerEntry.data.type(LedgerEntryType::SIGNER);
    auto& signer = signerEntry.data.signer();
    signer.accountID = mApp.getAdminID();
    signer.pubKey = mApp.getAdminID();
    signer.details = "{}";
    signer.weight = SignerRuleFrame::threshold;
    signer.identity = 0;
    signer.roleID = signerRole.id;

    storageHelper.getSignerHelper().storeAdd(signerEntry);

    return signerRole.id;
}

uint64_t
LedgerManagerImpl::createAdminRole(StorageHelper& storageHelper)
{
    auto& ledgerHeader = storageHelper.mustGetLedgerDelta().getHeaderFrame();

    AccountRuleEntry adminRule;
    adminRule.resource = AccountRuleResource(LedgerEntryType::ANY);
    adminRule.action = AccountRuleAction::ANY;
    adminRule.details = "{}";
    adminRule.forbids = false;
    adminRule.id = ledgerHeader.generateID(LedgerEntryType::ACCOUNT_RULE);

    LedgerEntry ledgerRuleEntry;
    ledgerRuleEntry.data.type(LedgerEntryType::ACCOUNT_RULE);
    ledgerRuleEntry.data.accountRule() = adminRule;

    storageHelper.getAccountRuleHelper().storeAdd(ledgerRuleEntry);

    AccountRoleEntry adminRole;
    adminRole.ruleIDs = {adminRule.id};
    adminRole.details = "{}";
    adminRole.id = ledgerHeader.generateID(LedgerEntryType::ACCOUNT_ROLE);

    LedgerEntry ledgerRoleEntry;
    ledgerRoleEntry.data.type(LedgerEntryType::ACCOUNT_ROLE);
    ledgerRoleEntry.data.accountRole() = adminRole;

    storageHelper.getAccountRoleHelper().storeAdd(ledgerRoleEntry);

    return adminRole.id;
}

void
LedgerManagerImpl::startNewLedger()
{
    DBTimeExcluder qtExclude(mApp);
    auto ledgerTime = mLedgerClose.TimeScope();

    LedgerHeader genesisHeader;
    // all fields are initialized by default to 0
    // set the ones that are not 0
    genesisHeader.baseFee = 0;
    genesisHeader.baseReserve = 0;
    genesisHeader.maxTxSetSize = 100; // 100 tx/ledger max
    genesisHeader.ledgerSeq = 1;
   
    genesisHeader.txExpirationPeriod = mApp.getConfig().TX_EXPIRATION_PERIOD;

    LedgerDeltaImpl deltaImpl(genesisHeader, getDatabase());
    LedgerDelta& delta = deltaImpl;
    StorageHelperImpl storageHelperImpl(getDatabase(), &delta);
    StorageHelper& storageHelper = storageHelperImpl;
    storageHelper.begin();

    auto adminAccount = std::make_shared<AccountFrame>(mApp.getAdminID());
    auto& accountEntry = adminAccount->getAccount();
    accountEntry.accountID = mApp.getAdminID();
    accountEntry.roleID = createAdminRole(storageHelperImpl);
    accountEntry.sequentialID = delta.getHeaderFrame().generateID(LedgerEntryType::ACCOUNT);

    // use new account helper, when it will be possible
    storageHelper.getAccountHelper().storeAdd(adminAccount->mEntry);
    auto ownerRoleID = createAdminSigner(storageHelper);
    createDefaultSignerRules(storageHelper, ownerRoleID);
    storageHelper.commit();

    mCurrentLedger = make_shared<LedgerHeaderFrameImpl>(genesisHeader);
	
	CLOG(INFO, "Ledger") << "Established genesis ledger, ";
    CLOG(INFO, "Ledger") << "Admin account id: " << PubKeyUtils::toStrKey(mApp.getAdminID());
    ledgerClosed(delta);
}

void
LedgerManagerImpl::loadLastKnownLedger(
    function<void(asio::error_code const& ec)> handler)
{
    DBTimeExcluder qtExclude(mApp);
    auto ledgerTime = mLedgerClose.TimeScope();

    string lastLedger =
        mApp.getPersistentState().getState(PersistentState::kLastClosedLedger);

    if (lastLedger.empty())
    {
        throw std::runtime_error("No ledger in the DB");
    }
    else
    {
        LOG(INFO) << "Loading last known ledger";
        Hash lastLedgerHash = hexToBin256(lastLedger);

        auto currentLedger =
            LedgerHeaderUtils::loadByHash(getDatabase(), lastLedgerHash);
        if (!currentLedger)
        {
            throw std::runtime_error("Could not load ledger from database");
        }

        mCurrentLedger = std::make_shared<LedgerHeaderFrameImpl>(*currentLedger);

        if (handler)
        {
            HistoryArchiveState has = getLastClosedLedgerHAS();

            auto continuation = [this, handler,
                                 has](asio::error_code const& ec) {
                if (ec)
                {
                    handler(ec);
                }
                else
                {
                    mApp.getBucketManager().assumeState(has);
                    {
                        CLOG(INFO, "Ledger") << "Loaded last known ledger: "
                                             << ledgerAbbrev(mCurrentLedger->getHeader());
                        advanceLedgerPointers();
                    }
                    handler(ec);
                }
            };

            auto missing =
                mApp.getBucketManager().checkForMissingBucketsFiles(has);
            auto pubmissing = mApp.getHistoryManager()
                                  .getMissingBucketsReferencedByPublishQueue();
            missing.insert(missing.end(), pubmissing.begin(), pubmissing.end());
            if (!missing.empty())
            {
                CLOG(WARNING, "Ledger")
                    << "Some buckets are missing in '"
                    << mApp.getBucketManager().getBucketDir() << "'.";
                CLOG(WARNING, "Ledger")
                    << "Attempting to recover from the history store.";
                mApp.getHistoryManager().downloadMissingBuckets(has,
                                                                continuation);
            }
            else
            {
                continuation(asio::error_code());
            }
        }
        else
        {
            advanceLedgerPointers();
        }
    }
}

Database&
LedgerManagerImpl::getDatabase()
{
    return mApp.getDatabase();
}

uint32_t
LedgerManagerImpl::getLastMaxTxSetSize() const
{
    return mLastClosedLedger.header.maxTxSetSize;
}

int64_t
LedgerManagerImpl::getLastMinBalance(uint32_t ownerCount) const
{
    auto& lh = mLastClosedLedger.header;
    if (lh.ledgerVersion <= 8)
        return (2 + ownerCount) * lh.baseReserve;
    else
        return (2 + ownerCount) * int64_t(lh.baseReserve);
}

uint32_t
LedgerManagerImpl::getLastReserve() const
{
    return mLastClosedLedger.header.baseReserve;
}


uint32_t
LedgerManagerImpl::getLastTxFee() const
{
    return mLastClosedLedger.header.baseFee;
}

uint64
LedgerManagerImpl::getTxExpirationPeriod() const
{
	assert(mLastClosedLedger.header.txExpirationPeriod >= 0);
    return mLastClosedLedger.header.txExpirationPeriod;
}

uint64_t
LedgerManagerImpl::getCloseTime() const
{
    return mCurrentLedger->getHeader().scpValue.closeTime;
}

tm
LedgerManagerImpl::getTmCloseTime() const
{
    return VirtualClock::tm_from_time_t(mCurrentLedger->getHeader().scpValue.closeTime);
}

LedgerHeaderHistoryEntry const&
LedgerManagerImpl::getLastClosedLedgerHeader() const
{
    return mLastClosedLedger;
}

LedgerHeader&
LedgerManagerImpl::getCurrentLedgerHeader()
{
    return mCurrentLedger->getHeader();
}

HistoryArchiveState
LedgerManagerImpl::getLastClosedLedgerHAS()
{
    string hasString = mApp.getPersistentState().getState(
        PersistentState::kHistoryArchiveState);
    HistoryArchiveState has;
    has.fromString(hasString);
    return has;
}

uint32_t
LedgerManagerImpl::getLastClosedLedgerNum() const
{
    return mLastClosedLedger.header.ledgerSeq;
}

uint32_t
getCatchupCount(Application& app)
{
    return app.getConfig().CATCHUP_COMPLETE
               ? std::numeric_limits<uint32_t>::max()
               : app.getConfig().CATCHUP_RECENT;
}

// called by txherder
void
LedgerManagerImpl::valueExternalized(LedgerCloseData const& ledgerData)
{
    CLOG(INFO, "Ledger")
        << "Got consensus: "
        << "[seq=" << ledgerData.getLedgerSeq()
        << ", prev=" << hexAbbrev(ledgerData.getTxSet()->previousLedgerHash())
        << ", tx_count=" << ledgerData.getTxSet()->size()
        << ", sv: " << StellarValueToString(ledgerData.getValue()) << "]";

    auto st = getState();
    switch (st)
    {
    case LedgerManager::LM_BOOTING_STATE:
    case LedgerManager::LM_SYNCED_STATE:
    {
        switch (closeLedgerIf(ledgerData))
        {
        case CloseLedgerIfResult::CLOSED:
        {
            setState(LM_SYNCED_STATE);
        }
        break;
        case CloseLedgerIfResult::TOO_OLD:
            // nothing to do
            break;
        case CloseLedgerIfResult::TOO_NEW:
        {
            initializeCatchup(ledgerData);
        }
        break;
        }
    }
    break;

    case LedgerManager::LM_CATCHING_UP_STATE:
    {
        switch (mCatchupState)
        {
        case CatchupState::WAITING_FOR_CLOSING_LEDGER:
        {
            finalizeCatchup(ledgerData);
        }
        break;

        default:
        {
            continueCatchup(ledgerData);
        }
        break;
        }
    }
    break;

    default:
        assert(false);
    }
}

LedgerManagerImpl::CloseLedgerIfResult
LedgerManagerImpl::closeLedgerIf(LedgerCloseData const& ledgerData)
{
    if (mLastClosedLedger.header.ledgerSeq + 1 == ledgerData.getLedgerSeq())
    {
        if (mLastClosedLedger.hash ==
            ledgerData.getTxSet()->previousLedgerHash())
        {
            closeLedger(ledgerData);
            CLOG(INFO, "Ledger")
                    << "Closed ledger: " << ledgerAbbrev(mLastClosedLedger);
            return CloseLedgerIfResult::CLOSED;
        }
        else
        {
            CLOG(FATAL, "Ledger") << "Network consensus for ledger "
                                  << mLastClosedLedger.header.ledgerSeq
                                  << " changed; this should never happen";
            throw std::runtime_error("Network consensus inconsistency");
        }
    }
    else if (ledgerData.getLedgerSeq() <= mLastClosedLedger.header.ledgerSeq)
    {
        CLOG(INFO, "Ledger")
                << "Skipping close ledger: local state is "
                << mLastClosedLedger.header.ledgerSeq << ", more recent than "
                << ledgerData.getLedgerSeq();
        return CloseLedgerIfResult::TOO_OLD;
    }
    else
    {
        // Out of sync, buffer what we just heard and start catchup.
        CLOG(INFO, "Ledger")
                << "Lost sync, local LCL is " << mLastClosedLedger.header.ledgerSeq
                << ", network closed ledger " << ledgerData.getLedgerSeq();
        return CloseLedgerIfResult::TOO_NEW;
    }
}

void
LedgerManagerImpl::initializeCatchup(LedgerCloseData const& ledgerData)
{
    assert(mState != LM_CATCHING_UP_STATE);
    assert(mCatchupState == CatchupState::NONE);
    assert(mSyncingLedgers.empty());

    setState(LM_CATCHING_UP_STATE);
    mCatchupTriggerLedger = mApp.getHistoryManager().nextCheckpointLedger(
            ledgerData.getLedgerSeq()) +
                            1;
    setCatchupState(CatchupState::WAITING_FOR_TRIGGER_LEDGER);
    addToSyncingLedgers(ledgerData);
    startCatchupIf(ledgerData.getLedgerSeq());
}

void
LedgerManagerImpl::continueCatchup(LedgerCloseData const& ledgerData)
{
    assert(mState == LM_CATCHING_UP_STATE);

    addToSyncingLedgers(ledgerData);
    startCatchupIf(ledgerData.getLedgerSeq());
}

void
LedgerManagerImpl::finalizeCatchup(LedgerCloseData const& ledgerData)
{
    assert(mState == LM_CATCHING_UP_STATE);
    assert(mCatchupState == CatchupState::WAITING_FOR_CLOSING_LEDGER);
    assert(mSyncingLedgers.empty());

    switch (closeLedgerIf(ledgerData))
    {
        case CloseLedgerIfResult::CLOSED:
        {
            CLOG(INFO, "Ledger") << "Catchup final ledger closed: "
                                 << ledgerAbbrev(mLastClosedLedger);
            setState(LM_SYNCED_STATE);
        }
            break;
        case CloseLedgerIfResult::TOO_OLD:
            // nothing to do
            break;
        case CloseLedgerIfResult::TOO_NEW:
        {
            setState(LM_BOOTING_STATE);
            initializeCatchup(ledgerData);
        }
            break;
    }
}

void
LedgerManagerImpl::addToSyncingLedgers(LedgerCloseData const& ledgerData)
{
    switch (mSyncingLedgers.push(ledgerData))
    {
        case SyncingLedgerChainAddResult::CONTIGUOUS:
            // Normal close while catching up
            CLOG(INFO, "Ledger")
                    << "Close of ledger " << ledgerData.getLedgerSeq() << " buffered";
            return;
        case SyncingLedgerChainAddResult::TOO_OLD:
            CLOG(INFO, "Ledger")
                    << "Skipping close ledger: latest known is "
                    << mSyncingLedgers.back().getLedgerSeq() << ", more recent than "
                    << ledgerData.getLedgerSeq();
            return;
        case SyncingLedgerChainAddResult::TOO_NEW:
            // Out-of-order close while catching up; timeout / network failure?
            CLOG(WARNING, "Ledger")
                    << "Out-of-order close during catchup, buffered to "
                    << mSyncingLedgers.back().getLedgerSeq() << " but network closed "
                    << ledgerData.getLedgerSeq();

            CLOG(WARNING, "Ledger")
                    << "this round of catchup will fail and restart.";
            return;
        default:
            assert(false);
    }
}

void
LedgerManagerImpl::startCatchupIf(uint32_t lastReceivedLedgerSeq)
{
    assert(!mSyncingLedgers.empty());
    assert(mCatchupState != CatchupState::NONE);

    auto contiguous =
            lastReceivedLedgerSeq == mSyncingLedgers.back().getLedgerSeq();
    if (mCatchupState != CatchupState::WAITING_FOR_TRIGGER_LEDGER)
    {
        mApp.getCatchupManager().logAndUpdateCatchupStatus(contiguous);
        return;
    }

    if (lastReceivedLedgerSeq >= mCatchupTriggerLedger)
    {
        setCatchupState(CatchupState::APPLYING_HISTORY);

        auto message = fmt::format("Starting catchup after ensuring checkpoint "
                                   "ledger {} was closed on network",
                                   mCatchupTriggerLedger);
        mApp.getCatchupManager().logAndUpdateCatchupStatus(contiguous, message);

        // catchup just before first buffered ledger that way we will have a way
        // to verify history consistency - compare previousLedgerHash of
        // buffered ledger with last one downloaded from history
        auto firstBufferedLedgerSeq = mSyncingLedgers.front().getLedgerSeq();
        auto hash = make_optional<Hash>(
                mSyncingLedgers.front().getTxSet()->previousLedgerHash());
        startCatchup({LedgerNumHashPair(firstBufferedLedgerSeq - 1, hash),
                      getCatchupCount(mApp)},
                     false);
    }
    else
    {
        auto eta = (mCatchupTriggerLedger - lastReceivedLedgerSeq) *
                   mApp.getConfig().getExpectedLedgerCloseTime();
        auto message = fmt::format(
                "Waiting for trigger ledger: {}/{}, ETA: {}s",
                lastReceivedLedgerSeq, mCatchupTriggerLedger, eta.count());
        mApp.getCatchupManager().logAndUpdateCatchupStatus(contiguous, message);
    }
}

void
LedgerManagerImpl::startCatchup(CatchupConfiguration configuration,
                                bool manualCatchup)
{
    auto lastClosedLedger = getLastClosedLedgerNum();
    if ((configuration.toLedger() != CatchupConfiguration::CURRENT) &&
        (configuration.toLedger() <= lastClosedLedger))
    {
        throw std::invalid_argument("Target ledger is not newer than LCL");
    }

    setCatchupState(CatchupState::APPLYING_HISTORY);
    assert(manualCatchup == mSyncingLedgers.empty());

    mApp.getCatchupManager().catchupHistory(
            configuration,
            std::bind(&LedgerManagerImpl::historyCaughtup, this, _1, _2, _3));
}

void
LedgerManagerImpl::historyCaughtup(asio::error_code const& ec,
                                   CatchupWork::ProgressState progressState,
                                   LedgerHeaderHistoryEntry const& lastClosed)
{
    assert(mCatchupState == CatchupState::APPLYING_HISTORY);

    if (ec)
    {
        CLOG(ERROR, "Ledger") << "Error catching up: " << ec.message();
        CLOG(ERROR, "Ledger") << "Catchup will restart at next close.";
        setState(LM_BOOTING_STATE);
        mApp.getCatchupManager().historyCaughtup();
        mSyncingLedgers = {};
        mSyncingLedgersSize.set_count(mSyncingLedgers.size());
    }
    else
    {
        switch (progressState)
        {
            case CatchupWork::ProgressState::APPLIED_BUCKETS:
            {
                mLastClosedLedger = lastClosed;
                mCurrentLedger = make_shared<LedgerHeaderFrameImpl>(lastClosed);
                storeCurrentLedger();
                return;
            }
            case CatchupWork::ProgressState::APPLIED_TRANSACTIONS:
            {
                // In this case we should actually have been caught-up during the
                // replay process and, if judged successful, our LCL should be the
                // one provided as well.
                assert(lastClosed.hash == mLastClosedLedger.hash);
                assert(lastClosed.header == mLastClosedLedger.header);
                return;
            }
            case CatchupWork::ProgressState::FINISHED:
            {
                break;
            }
            default:
            {
                assert(false);
            }
        }

        CLOG(INFO, "Ledger") << "Caught up to LCL from history: "
                             << ledgerAbbrev(mLastClosedLedger);
        mApp.getCatchupManager().historyCaughtup();

        setCatchupState(CatchupState::APPLYING_BUFFERED_LEDGERS);
        applyBufferedLedgers();
    }
}

void
LedgerManagerImpl::applyBufferedLedgers()
{
    assert(mCatchupState == CatchupState::APPLYING_BUFFERED_LEDGERS);
    if (mSyncingLedgers.empty())
    {
        CLOG(INFO, "Ledger")
                << "Caught up to LCL including recent network activity: "
                << ledgerAbbrev(mLastClosedLedger)
                << "; waiting for closing ledger";
        setCatchupState(CatchupState::WAITING_FOR_CLOSING_LEDGER);
        return;
    }

    mApp.postOnMainThreadWithDelay(
            [&] {
                auto lcd = mSyncingLedgers.front();
                mSyncingLedgers.pop();
                mSyncingLedgersSize.set_count(mSyncingLedgers.size());

                assert(lcd.getLedgerSeq() ==
                       mLastClosedLedger.header.ledgerSeq + 1);
                CLOG(INFO, "Ledger")
                        << "Replaying buffered ledger-close: "
                        << "[seq=" << lcd.getLedgerSeq()
                        << ", prev=" << hexAbbrev(lcd.getTxSet()->previousLedgerHash())
                        << ", tx_count=" << lcd.getTxSet()->size()
                        << ", sv: " << StellarValueToString(lcd.getValue()) << "]";
                closeLedger(lcd);

                applyBufferedLedgers();
            },
            "LedgerManager: applyBufferedLedgers");
}

uint64_t
LedgerManagerImpl::secondsSinceLastLedgerClose() const
{
    uint64_t ct = getLastClosedLedgerHeader().header.scpValue.closeTime;
    uint64_t now = mApp.timeNow();
    return (now > ct) ? (now - ct) : 0;
}

void
LedgerManagerImpl::syncMetrics()
{
    mSyncingLedgersSize.set_count(mSyncingLedgers.size());
    mLedgerAge.set_count(secondsSinceLastLedgerClose());
    mApp.syncOwnMetrics();
}

/*
    This is the main method that closes the current ledger based on
the close context that was computed by SCP or by the historical module
during replays.

*/
void
LedgerManagerImpl::closeLedger(LedgerCloseData const& ledgerData)
{
    DBTimeExcluder qtExclude(mApp);
    CLOG(DEBUG, "Ledger") << "starting closeLedger() on ledgerSeq="
                          << mCurrentLedger->getHeader().ledgerSeq;

    auto now = mApp.getClock().now();
    mLedgerAgeClosed.Update(now - mLastClose);
    mLastClose = now;
    mLedgerAge.set_count(0);

    if (ledgerData.getTxSet()->previousLedgerHash() !=
        getLastClosedLedgerHeader().hash)
    {
        CLOG(ERROR, "Ledger")
                << "TxSet mismatch: LCD wants "
                << ledgerAbbrev(ledgerData.getLedgerSeq() - 1,
                                ledgerData.getTxSet()->previousLedgerHash())
                << ", LCL is " << ledgerAbbrev(getLastClosedLedgerHeader());

        CLOG(ERROR, "Ledger")
                << "Full LCL: " << xdr::xdr_to_string(getLastClosedLedgerHeader());

        throw std::runtime_error("txset mismatch");
    }

    if (ledgerData.getTxSet()->getContentsHash() !=
        ledgerData.getValue().txSetHash)
    {
        throw std::runtime_error("corrupt transaction set");
    }

    soci::transaction txscope(getDatabase().getSession());

    auto ledgerTime = mLedgerClose.TimeScope();

    auto const& sv = ledgerData.getValue();
    mCurrentLedger->getHeader().scpValue = sv;

    LedgerDeltaImpl ledgerDeltaImpl(mCurrentLedger->getHeader(), getDatabase());
    LedgerDelta& ledgerDelta = ledgerDeltaImpl;

    // the transaction set that was agreed upon by consensus
    // was sorted by hash; we reorder it so that transactions are
    // sorted such that sequence numbers are respected
    vector<TransactionFramePtr> txs = ledgerData.getTxSet()->sortForApply();

    // first, charge fees
    processFeesSeqNums(txs, ledgerDelta);

    TransactionResultSet txResultSet;
    txResultSet.results.reserve(txs.size());

    applyTransactions(txs, ledgerDelta, txResultSet);

    ledgerDelta.getHeader().txSetResultHash =
        sha256(xdr::xdr_to_opaque(txResultSet));

    // apply any upgrades that were decided during consensus
    // this must be done after applying transactions as the txset
    // was validated before upgrades
    for (size_t i = 0; i < sv.upgrades.size(); i++)
    {
        LedgerUpgrade lupgrade;
        try
        {
            xdr::xdr_from_opaque(sv.upgrades[i], lupgrade);
        }
        catch (xdr::xdr_runtime_error)
        {
            CLOG(FATAL, "Ledger") << "Unknown upgrade step at index " << i;
            throw;
        }

        try
        {
            LedgerDeltaImpl deltaImpl(ledgerDelta);
            LedgerDelta& delta = deltaImpl;
            Upgrades::applyTo(lupgrade, delta);

            auto ledgerSeq = delta.getHeader().ledgerSeq;
            // Note: Index from 1 rather than 0 to match the behavior of
            // storeTransaction and storeTransactionFee.
            Upgrades::storeUpgradeHistory(getDatabase(), ledgerSeq, lupgrade,
                                          delta.getChanges(),
                                          static_cast<int>(i + 1));
            delta.commit();
        }
        catch (std::runtime_error& e)
        {
            CLOG(ERROR, "Ledger") << "Exception during upgrade: " << e.what();
        }
        catch (...)
        {
            CLOG(ERROR, "Ledger") << "Unknown exception during upgrade";
        }
    }

    ledgerDelta.commit();
    ledgerClosed(ledgerDelta);

    // The next 4 steps happen in a relatively non-obvious, subtle order.
    // This is unfortunate and it would be nice if we could make it not
    // be so subtle, but for the time being this is where we are.
    //
    // 1. Queue any history-checkpoint to the database, _within_ the current
    //    transaction. This way if there's a crash after commit and before
    //    we've published successfully, we'll re-publish on restart.
    //
    // 2. Commit the current transaction.
    //
    // 3. Start any queued checkpoint publishing, _after_ the commit so that
    //    it takes its snapshot of history-rows from the committed state, but
    //    _before_ we GC any buckets (because this is the step where the
    //    bucket refcounts are incremented for the duration of the publish).
    //
    // 4. GC unreferenced buckets. Only do this once publishes are in progress.

    // step 1
    auto& hm = mApp.getHistoryManager();
    hm.maybeQueueHistoryCheckpoint();

    // step 2
    mApp.getDatabase().clearPreparedStatementCache();
    txscope.commit();

    // step 3
    hm.publishQueuedHistory();
    hm.logAndUpdatePublishStatus();

    // step 4
    mApp.getBucketManager().forgetUnreferencedBuckets();
}

void
LedgerManagerImpl::deleteOldEntries(Database& db, uint32_t ledgerSeq, uint32_t count)
{
    soci::transaction txscope(db.getSession());
    db.clearPreparedStatementCache();
    LedgerHeaderUtils::deleteOldEntries(db, ledgerSeq, count);
    TransactionFrame::deleteOldEntries(db, ledgerSeq, count);
    HerderPersistence::deleteOldEntries(db, ledgerSeq, count);
    db.clearPreparedStatementCache();
    txscope.commit();
}

// move to invariants
/*void
LedgerManagerImpl::checkDbState()
{
    Database& db = getDatabase();

    auto allAssetsWithIssued = AssetHelperLegacy::Instance()->loadIssuedForAssets(db);

    for (const auto& item : allAssetsWithIssued)
    {
        auto totalAssetAmount = BalanceHelperLegacy::Instance()->loadTotalAssetAmount(
                db, item.first);

        if (totalAssetAmount != item.second)
        {
            throw std::runtime_error("Total asset amount on all balances not equal to "
                                     "total issued amount of asset");
        }
    }
}*/

void
LedgerManagerImpl::advanceLedgerPointers()
{
    CLOG(DEBUG, "Ledger") << "Advancing LCL: "
                          << ledgerAbbrev(mLastClosedLedger) << " -> "
                          << ledgerAbbrev(mCurrentLedger);

    mLastClosedLedger.hash = mCurrentLedger->getHash();
    mLastClosedLedger.header = mCurrentLedger->getHeader();
    mCurrentLedger = make_shared<LedgerHeaderFrameImpl>(mLastClosedLedger);
    CLOG(DEBUG, "Ledger") << "New current ledger: seq="
                          << mCurrentLedger->getHeader().ledgerSeq;
}

void
LedgerManagerImpl::processFeesSeqNums(std::vector<TransactionFramePtr>& txs,
                                      LedgerDelta& delta)
{
    CLOG(DEBUG, "Ledger") << "processing fees and sequence numbers";
    int index = 0;
    try
    {
        soci::transaction sqlTx(mApp.getDatabase().getSession());
        for (auto tx : txs)
        {
            LedgerDeltaImpl thisTxDeltaImpl(delta);
            LedgerDelta& thisTxDelta = thisTxDeltaImpl;
            tx->storeTransactionFee(*this, thisTxDelta.getChanges(), ++index);
            tx->processSeqNum();
            tx->storeTransactionTiming(*this, tx->getTimeBounds().maxTime);
            thisTxDelta.commit();
        }
        sqlTx.commit();
    }
    catch (std::exception& e)
    {
        CLOG(FATAL, "Ledger") << "processFeesSeqNums error @ " << index << " : "
                              << e.what();
        throw;
    }
}

void handle_eptr(std::exception_ptr eptr) // passing by value is ok
{
    try {
        if (eptr) {
            std::rethrow_exception(eptr);
        }
    }
    catch (const std::exception& e) {
        CLOG(ERROR, "Ledger") << "Caught exception during tx apply " << e.what();
    }
}

void
LedgerManagerImpl::applyTransactions(std::vector<TransactionFramePtr>& txs,
                                     LedgerDelta& ledgerDelta,
                                     TransactionResultSet& txResultSet)
{
    int index = 0;

    // Record counts
    auto numTxs = txs.size();
    if (numTxs > 0)
    {
        mTransactionCount.Update(static_cast<int64_t>(numTxs));
        size_t numOps =
                std::accumulate(txs.begin(), txs.end(), size_t(0),
                                [](size_t s, TransactionFramePtr const& v) {
                                    return s + v->getOperations().size();
                                });
        mOperationCount.Update(static_cast<int64_t>(numOps));
        CLOG(INFO, "Tx") << fmt::format("applying ledger {} (txs:{}, ops:{})",
                                        mCurrentLedger->getHeader().ledgerSeq,
                                        numTxs, numOps);
    }

    for (auto tx : txs)
    {
        auto txTime = mTransactionApply.TimeScope();
        LedgerDeltaImpl deltaImpl(ledgerDelta);
        LedgerDelta& delta = deltaImpl;
        TransactionMeta tm;
        try
        {
            CLOG(DEBUG, "Tx")
                    << " tx#" << index << " = " << hexAbbrev(tx->getFullHash())
                    << " txsalt=" << tx->getSalt()
                    << " ops=" << tx->getOperations().size() << " (@ "
                    << mApp.getConfig().toShortString(tx->getSourceID()) << ")";
            vector<LedgerDelta::KeyEntryMap> stateBeforeOp;
            if (tx->apply(delta, tm, mApp, stateBeforeOp))
            {
                delta.commit();
            }
            else
            {
                // failure means there should be no side effects
                assert(delta.getChanges().size() == 0);
                assert(delta.getHeader() == ledgerDelta.getHeader());
            }
        }
        catch (InvariantDoesNotHold&)
        {
            CLOG(ERROR, "Ledger")
                    << "Invariant failure during tx->apply for tx "
                    << tx->getFullHash();
            throw;
        }
        catch (std::runtime_error& e)
        {
            CLOG(ERROR, "Ledger") << "Exception during tx->apply for tx "
                                  << tx->getFullHash() << " : " << e.what();
            std::exception_ptr eptr = std::current_exception();
            handle_eptr(eptr);
            mInternalErrorCount.inc();
            tx->getResult().result.code(TransactionResultCode::txINTERNAL_ERROR);
        }
        catch (...)
        {
            CLOG(ERROR, "Ledger")
                    << "Unknown exception during tx->apply for tx "
                    << tx->getFullHash();
            std::exception_ptr eptr = std::current_exception();
            handle_eptr(eptr);
            mInternalErrorCount.inc();
            tx->getResult().result.code(TransactionResultCode::txINTERNAL_ERROR);
        }
        tx->storeTransaction(*this, tm, ++index, txResultSet);
    }
}

void
LedgerManagerImpl::storeCurrentLedger()
{
    LedgerHeaderUtils::storeInDatabase(mApp.getDatabase(), mCurrentLedger->getHeader());

    Hash hash = sha256(xdr::xdr_to_opaque(mCurrentLedger->getHeader()));
    assert(!isZero(hash));
    mApp.getPersistentState().setState(PersistentState::kLastClosedLedger,
                                       binToHex(hash));

    // Store the current HAS in the database; this is really just to checkpoint
    // the bucketlist so we can survive a restart and re-attach to the buckets.
    HistoryArchiveState has(mCurrentLedger->getHeader().ledgerSeq,
                            mApp.getBucketManager().getBucketList());

    // We almost always want to try to resolve completed merges to single
    // buckets, as it makes restarts less fragile: fewer saved/restored shadows,
    // fewer buckets for the user to accidentally delete from their buckets
    // dir. But we support the option of not-doing so, only for the sake of
    // testing. Note: this is nonblocking in any case.
    if (!mApp.getConfig().ARTIFICIALLY_PESSIMIZE_MERGES_FOR_TESTING)
    {
        has.resolveAnyReadyFutures();
    }

    mApp.getPersistentState().setState(PersistentState::kHistoryArchiveState,
                                       has.toString());
}

void
LedgerManagerImpl::ledgerClosed(LedgerDelta const& delta)
{
    auto ledgerSeq = delta.getHeader().ledgerSeq;
    mApp.getBucketManager().addBatch(mApp, ledgerSeq, delta.getLiveEntries(),
                                     delta.getDeadEntries());

    mApp.getBucketManager().snapshotLedger(mCurrentLedger->getHeader());
    storeCurrentLedger();
    advanceLedgerPointers();
}

LedgerVersion
LedgerManagerImpl::getLedgerVersion()
{
    return static_cast<LedgerVersion>(getCurrentLedgerHeader().ledgerVersion);
}

bool LedgerManagerImpl::shouldUse(const LedgerVersion version) {
    return getCurrentLedgerHeader().ledgerVersion >= static_cast<int32_t>(version);
}
}
