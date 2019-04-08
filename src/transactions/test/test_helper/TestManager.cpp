// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <herder/LedgerCloseData.h>
#include <ledger/StorageHelperImpl.h>
#include "ledger/AssetHelperLegacy.h"
#include "TestManager.h"
#include "ledger/LedgerDeltaImpl.h"
#include "invariant/Invariants.h"
#include "test/test_marshaler.h"
#include "xdrpp/marshal.h"

namespace stellar {

    namespace txtest {
        TestManager::TestManager(Application &app, Database &db, LedgerManager &lm) :
                mApp(app), mDB(db), mLm(lm), mSh(*(new StorageHelperImpl(db, nullptr)))
        {
            mApp.stopCheckingPolicies();
        }

        TestManager::~TestManager()
        {
            mApp.resumeCheckingPolicies();
        }

        TestManager::pointer TestManager::make(Application &app) {
            Database &db = app.getDatabase();
            LedgerManager &lm = app.getLedgerManager();
            return std::make_shared<TestManager>(app, db, lm);
        }

        void TestManager::upgradeToCurrentLedgerVersion(Application& app) {
            upgradeToLedgerVersion(app, static_cast<LedgerVersion>(app.getConfig().LEDGER_PROTOCOL_VERSION));
        }

        void TestManager::upgradeToLedgerVersion(Application& app, LedgerVersion ledgerVersion) {
            auto const &lcl = app.getLedgerManager().getLastClosedLedgerHeader();
            auto const &lastHash = lcl.hash;
            TxSetFramePtr txSet = std::make_shared<TxSetFrame>(lastHash);

            xdr::xvector<UpgradeType, 6> upgrades;
            auto ledgerVersionValue = TestManager::ledgerVersion(app, ledgerVersion);
            upgrades.emplace_back(ledgerVersionValue.begin(), ledgerVersionValue.end());

            StellarValue sv(txSet->getContentsHash(), 1, upgrades, StellarValue::_ext_t(LedgerVersion::EMPTY_VERSION));
            LedgerCloseData ledgerData(1, txSet, sv);
            app.getLedgerManager().closeLedger(ledgerData);
        }

        bool TestManager::apply(TransactionFramePtr tx, std::vector<LedgerDelta::KeyEntryMap> &stateBeforeOp, LedgerDelta &txDelta) {
            tx->clearCached();
            bool isTxValid = tx->checkValid(mApp);
            auto validationResult = tx->getResult();
            checkResult(validationResult, isTxValid);

            const auto code = validationResult.result.code();
            if (code == TransactionResultCode::txDUPLICATION) {
                return false;
            }

            if (code != TransactionResultCode::txNO_ACCOUNT) {
                tx->processSeqNum();
            }

            TransactionMeta txMeta;
            bool isApplied = tx->apply(txDelta, txMeta, mApp, stateBeforeOp);
            auto applyResult = tx->getResult();
            checkResult(applyResult, isApplied);

            if (!isTxValid) {
                REQUIRE(validationResult == applyResult);
            }

            if (isApplied) {
                txDelta.commit();
            }

            return isApplied;
        }

        void TestManager::checkResult(TransactionResult result, bool mustSuccess) {
            if (mustSuccess) {
                REQUIRE(result.result.code() == TransactionResultCode::txSUCCESS);
                return;
            }

            REQUIRE(result.result.code() != TransactionResultCode::txSUCCESS);
        }

        Value TestManager::ledgerVersion(Application& application, LedgerVersion version) {
            LedgerUpgrade upgrade(LedgerUpgradeType::VERSION);
            upgrade.newLedgerVersion() = static_cast<uint32>(version);
            Value v(xdr::xdr_to_opaque(upgrade));
            return v;
        }

        bool TestManager::applyCheck(TransactionFramePtr tx) {
            std::vector<LedgerDelta::KeyEntryMap> stateBeforeOp;
            return applyCheck(tx, stateBeforeOp);
        }

        bool TestManager::applyCheck(TransactionFramePtr tx, std::vector<LedgerDelta::KeyEntryMap> &stateBeforeOp) {
            LedgerDeltaImpl delta(mLm.getCurrentLedgerHeader(), mDB);
            const bool isApplied = apply(tx, stateBeforeOp, delta);
            // validates db state
            checkDbState();
            auto txSet = std::make_shared<TxSetFrame>(mLm.getLastClosedLedgerHeader().hash);
            txSet->add(tx);
            //mApp.getInvariantManager().check(txSet, delta); // TODO
            return isApplied;
        }

        void
        TestManager::checkDbState()
        {
            Database& db = mDB;

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
        }


        void TestManager::advanceToTime(uint64_t closeTime) {
            // can't get to the past
            REQUIRE(closeTime >= mLm.getCloseTime());

            // create an empty txSet
            auto txSet = std::make_shared<TxSetFrame>(mLm.getLastClosedLedgerHeader().hash);

            // prepare data for ledger close
            StellarValue sv(txSet->getContentsHash(), closeTime, emptyUpgradeSteps, StellarValue::_ext_t{});
            LedgerCloseData ledgerCloseData(mLm.getLastClosedLedgerNum() + 1, txSet, sv);

            // close ledger
            mLm.closeLedger(ledgerCloseData);
        }
    }

}
