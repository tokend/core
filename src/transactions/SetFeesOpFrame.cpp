// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "transactions/SetFeesOpFrame.h"
#include "ledger/StorageHelperImpl.h"
#include "ledger/AssetHelper.h"
#include "ledger/LedgerDeltaImpl.h"
#include "ledger/FeeHelper.h"
#include "ledger/AssetHelperLegacy.h"
#include "ledger/AccountHelper.h"
#include "ledger/AccountRoleHelper.h"
#include "medida/meter.h"
#include "main/Application.h"
#include "medida/metrics_registry.h"

namespace stellar {

using namespace std;
using xdr::operator==;

SetFeesOpFrame::SetFeesOpFrame(Operation const &op, OperationResult &res,
                               TransactionFrame &parentTx)
        : OperationFrame(op, res, parentTx)
        , mSetFees(mOperation.body.setFeesOp())
{
}

bool
SetFeesOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                                std::vector<OperationCondition>& result) const
{
    result.emplace_back(AccountRuleResource(LedgerEntryType::FEE),
                        AccountRuleAction::MANAGE, mSourceAccount);

    return true;
}

bool
SetFeesOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                std::vector<SignerRequirement>& result) const
{
    result.emplace_back(SignerRuleResource(LedgerEntryType::FEE),
                        SignerRuleAction::MANAGE);

    return true;
}

    bool SetFeesOpFrame::trySetFee(LedgerManager &ledgerManager, Database &db, LedgerDelta &delta) {
        assert(mSetFees.fee);
        if (mSetFees.fee->feeType == FeeType::WITHDRAWAL_FEE && !doCheckForfeitFee(db, delta))
            return false;

        if (mSetFees.fee->feeType == FeeType::PAYMENT_FEE && !doCheckPaymentFee(db, delta))
            return false;

        StorageHelperImpl storageHelperImpl(db, &delta);
        if (!checkAccountRoleExisting(storageHelperImpl, ledgerManager))
        {
            return false;
        }

        Hash hash = FeeFrame::calcHash(mSetFees.fee->feeType, mSetFees.fee->asset, mSetFees.fee->accountID.get(),
                                       mSetFees.fee->accountRole.get(), mSetFees.fee->subtype);

        auto actualHashValue = mSetFees.fee.get()->hash;
        if (actualHashValue != hash) {
            innerResult().code(SetFeesResultCode::INVALID_FEE_HASH);
            return false;
        }

        auto feeHelper = FeeHelper::Instance();
        auto feeFrame = feeHelper->loadFee(hash, mSetFees.fee->lowerBound, mSetFees.fee->upperBound, db, &delta);

        // delete
        if (mSetFees.isDelete) {
            if (!feeFrame) {
                innerResult().code(SetFeesResultCode::NOT_FOUND);
                return false;
            }

            EntryHelperProvider::storeDeleteEntry(delta, db, feeFrame->getKey());
            return true;
        }

        // update
        if (feeFrame) {
            auto &fee = feeFrame->getFee();
            fee.percentFee = mSetFees.fee->percentFee;
            fee.fixedFee = mSetFees.fee->fixedFee;
            EntryHelperProvider::storeChangeEntry(delta, db, feeFrame->mEntry);
            return true;
        }

        // create
        auto assetHelper = AssetHelperLegacy::Instance();
        if (!assetHelper->exists(db, mSetFees.fee->asset)) {
            innerResult().code(SetFeesResultCode::ASSET_NOT_FOUND);
            return false;
        }

        if (feeHelper->isBoundariesOverlap(hash, mSetFees.fee->lowerBound, mSetFees.fee->upperBound, db)) {
            innerResult().code(SetFeesResultCode::RANGE_OVERLAP);
            return false;
        }

        LedgerEntry le;
        le.data.type(LedgerEntryType::FEE);
        le.data.feeState() = *mSetFees.fee;
        feeFrame = make_shared<FeeFrame>(le);

        StorageHelper& storageHelper = storageHelperImpl;
        if (!storageHelper.getAssetHelper().doesAmountFitAssetPrecision(
                feeFrame->getFeeAsset(), feeFrame->getFixedFee()))
        {
            innerResult().code(SetFeesResultCode::INVALID_AMOUNT_PRECISION);
            return false;
        }

        EntryHelperProvider::storeAddEntry(delta, db, feeFrame->mEntry);
        return true;
    }

bool SetFeesOpFrame::checkAccountRoleExisting(StorageHelper &storageHelper,
                                              LedgerManager &ledgerManager)
{
    if (!ledgerManager.shouldUse(LedgerVersion::CHECK_SET_FEE_ACCOUNT_EXISTING))
    {
        return true;
    }

    if (!mSetFees.fee)
    {
        throw std::runtime_error("Expected fee to exists");
    }

    auto fee = *mSetFees.fee;

    if (fee.accountID)
    {
        if (!storageHelper.getAccountHelper().exists(*fee.accountID))
        {
            innerResult().code(SetFeesResultCode::ACCOUNT_NOT_FOUND);
            return false;
        }
    }

    if (fee.accountRole)
    {
        if (!storageHelper.getAccountRoleHelper().exists(*fee.accountRole))
        {
            innerResult().code(SetFeesResultCode::ROLE_NOT_FOUND);
            return false;
        }
    }

    return true;
}

    bool SetFeesOpFrame::doCheckForfeitFee(Database &db, LedgerDelta &delta) {
        auto asset = AssetHelperLegacy::Instance()->loadAsset(mSetFees.fee->asset, db);
        if (!asset) {
            innerResult().code(SetFeesResultCode::ASSET_NOT_FOUND);
            return false;
        }

        return true;
    }

    bool SetFeesOpFrame::doCheckPaymentFee(stellar::Database &db, stellar::LedgerDelta &delta) {
        if (!AssetHelperLegacy::Instance()->exists(db, mSetFees.fee->asset)) {
            innerResult().code(SetFeesResultCode::ASSET_NOT_FOUND);
            return false;
        }
        return true;
    }

    bool
    SetFeesOpFrame::doApply(Application &app, LedgerDelta &delta, LedgerManager &ledgerManager) {
        Database &db = ledgerManager.getDatabase();
        innerResult().code(SetFeesResultCode::SUCCESS);

        LedgerDeltaImpl setFeesDeltaImpl(delta);
        LedgerDelta& setFeesDelta = setFeesDeltaImpl;

        LedgerHeader &ledgerHeader = setFeesDelta.getHeader();

        if (mSetFees.fee) {
            if (!trySetFee(ledgerManager, db, setFeesDelta))
                return false;
        }

        app.getMetrics().NewMeter({"op-set-fees", "success", "apply"}, "operation").Mark();

        setFeesDelta.commit();

        return true;
    }

    bool SetFeesOpFrame::mustFullRange(FeeEntry const &fee, medida::MetricsRegistry &metrics) {
        if (fee.lowerBound == 0 && fee.upperBound == INT64_MAX) {
            return true;
        }

        innerResult().code(SetFeesResultCode::MALFORMED_RANGE);
        metrics.NewMeter({"op-set-fees", "invalid", "invalid-range"}, "operation").Mark();
        return false;
    }

    bool SetFeesOpFrame::mustDefaultSubtype(FeeEntry const &fee, medida::MetricsRegistry &metrics) {
        if (fee.subtype == 0)
            return true;

        innerResult().code(SetFeesResultCode::SUB_TYPE_NOT_EXIST);
        metrics.NewMeter({"op-set-fees", "invalid", "invalid-sub-type-not-exist"}, "operation").Mark();
        return false;
    }

    bool SetFeesOpFrame::mustBaseAsset(FeeEntry const &fee, Application &app) {
        vector<AssetFrame::pointer> baseAssets;
        auto assetHelper = AssetHelperLegacy::Instance();
        assetHelper->loadBaseAssets(baseAssets, app.getDatabase());
        if (baseAssets.empty())
            throw std::runtime_error("Unable to create referral fee - there is no base assets in the system");

        if (fee.asset == baseAssets[0]->getCode())
            return true;

        innerResult().code(SetFeesResultCode::SUB_TYPE_NOT_EXIST);
        app.getMetrics().NewMeter({"op-set-fees", "invalid", "must-be-base-asset"}, "operation").Mark();
        return false;
    }

    bool SetFeesOpFrame::mustValidFeeAmounts(FeeEntry const &fee, medida::MetricsRegistry &metrics) {
        if (fee.fixedFee >= 0 && fee.percentFee >= 0 && fee.percentFee <= 100 * ONE) {
            return true;
        }

        innerResult().code(SetFeesResultCode::INVALID_AMOUNT);
        metrics.NewMeter({"op-set-fees", "invalid", "invalid-fee-amount"}, "operation").Mark();
        return false;
    }

    bool SetFeesOpFrame::isPaymentFeeValid(FeeEntry const &fee, medida::MetricsRegistry &metrics) {
        FeeFrame::checkFeeType(fee, FeeType::PAYMENT_FEE);

        if (!mustValidFeeAmounts(fee, metrics))
            return false;

        return true;
    }

    bool SetFeesOpFrame::isForfeitFeeValid(FeeEntry const &fee, medida::MetricsRegistry &metrics) {
        FeeFrame::checkFeeType(fee, FeeType::WITHDRAWAL_FEE);

        if (!mustValidFeeAmounts(fee, metrics))
            return false;

        return true;
    }

    bool SetFeesOpFrame::isOfferFeeValid(FeeEntry const &fee, medida::MetricsRegistry &metrics) {
        FeeFrame::checkFeeType(fee, FeeType::OFFER_FEE);

        if (!mustValidFeeAmounts(fee, metrics))
            return false;

        if (!mustEmptyFixed(fee, metrics))
            return false;

        if (!mustDefaultSubtype(fee, metrics))
            return false;

        return true;
    }

    bool SetFeesOpFrame::isCapitalDeploymentFeeValid(FeeEntry const &fee, medida::MetricsRegistry &metrics) {
        FeeFrame::checkFeeType(fee, FeeType::CAPITAL_DEPLOYMENT_FEE);

        if (!mustValidFeeAmounts(fee, metrics))
            return false;

        if (!mustEmptyFixed(fee, metrics))
            return false;

        return mustDefaultSubtype(fee, metrics);
    }

    bool SetFeesOpFrame::isEmissionFeeValid(FeeEntry const &fee, medida::MetricsRegistry &metrics) {
        FeeFrame::checkFeeType(fee, FeeType::ISSUANCE_FEE);

        if (!mustValidFeeAmounts(fee, metrics))
            return false;

        return true;
    }

    bool SetFeesOpFrame::isInvestFeeValid(FeeEntry const &fee, medida::MetricsRegistry &metrics) {
        FeeFrame::checkFeeType(fee, FeeType::INVEST_FEE);

        if (!mustValidFeeAmounts(fee, metrics))
            return false;

        return mustDefaultSubtype(fee, metrics);
    }

    bool SetFeesOpFrame::isOperationFeeValid(FeeEntry const &fee, medida::MetricsRegistry &metrics) {
        FeeFrame::checkFeeType(fee, FeeType::OPERATION_FEE);

        if (!mustValidFeeAmounts(fee, metrics))
            return false;

        if (!mustEmptyPercent(fee, metrics))
            return false;

        auto operationTypes = xdr::xdr_traits<OperationType>::enum_values();

        return fee.subtype >= 0 &&
               (std::find(operationTypes.begin(), operationTypes.end(), fee.subtype) != operationTypes.end());
    }

    bool
    SetFeesOpFrame::isPayoutFeeValid(FeeEntry const &fee, medida::MetricsRegistry &metrics) {
        FeeFrame::checkFeeType(fee, FeeType::PAYOUT_FEE);

        if (!mustValidFeeAmounts(fee, metrics))
            return false;

        return mustDefaultSubtype(fee, metrics);
    }

    bool SetFeesOpFrame::mustEmptyFixed(FeeEntry const &fee, medida::MetricsRegistry &metrics) {
        if (fee.fixedFee == 0)
            return true;

        innerResult().code(SetFeesResultCode::INVALID_AMOUNT);
        metrics.NewMeter({"op-set-fees", "invalid", "fixed-fee-must-be-empty"}, "operation").Mark();
        return false;
    }

    bool SetFeesOpFrame::mustEmptyPercent(FeeEntry const &fee, medida::MetricsRegistry &metrics) {
        if (fee.percentFee == 0) {
            return true;
        }

        innerResult().code(SetFeesResultCode::INVALID_AMOUNT);
        return false;
    }

    bool
    SetFeesOpFrame::doCheckValid(Application &app) {
        if (!mSetFees.fee) {
            return true;
        }

        if (!AssetFrame::isAssetCodeValid(mSetFees.fee->asset)) {
            innerResult().code(SetFeesResultCode::INVALID_ASSET);
            app.getMetrics().NewMeter({"op-set-fees", "invalid", "invalid-asset"}, "operation").Mark();
            return false;
        }

        if (mSetFees.fee->accountID && mSetFees.fee->accountRole) {
            innerResult().code(SetFeesResultCode::MALFORMED);
            app.getMetrics().NewMeter({"op-set-fees", "invalid", "malformed-both-set"}, "operation").Mark();
            return false;
        }

        if (mSetFees.fee->lowerBound > mSetFees.fee->upperBound) {
            innerResult().code(SetFeesResultCode::MALFORMED);
            app.getMetrics().NewMeter({"op-set-fees", "invalid", "malformed-boundaries"}, "operation").Mark();
            return false;
        }

        if (!app.getLedgerManager().shouldUse(mSetFees.fee->ext.v())) {
            innerResult().code(SetFeesResultCode::INVALID_FEE_VERSION);
            return false;
        }

        bool isValidFee;
        switch (mSetFees.fee->feeType) {
            case FeeType::PAYMENT_FEE:
                isValidFee = isPaymentFeeValid(*mSetFees.fee, app.getMetrics());
                break;
            case FeeType::OFFER_FEE:
                isValidFee = isOfferFeeValid(*mSetFees.fee, app.getMetrics());
                break;
            case FeeType::WITHDRAWAL_FEE:
                isValidFee = isForfeitFeeValid(*mSetFees.fee, app.getMetrics());
                break;
            case FeeType::ISSUANCE_FEE:
                isValidFee = isEmissionFeeValid(*mSetFees.fee, app.getMetrics());
                break;
            case FeeType::INVEST_FEE:
                isValidFee = isInvestFeeValid(*mSetFees.fee, app.getMetrics());
                break;
            case FeeType::OPERATION_FEE:
                isValidFee = isOperationFeeValid(*mSetFees.fee, app.getMetrics());
                break;
            case FeeType::CAPITAL_DEPLOYMENT_FEE:
                isValidFee = isCapitalDeploymentFeeValid(*mSetFees.fee, app.getMetrics());
                break;
            case FeeType::PAYOUT_FEE:
                isValidFee = isPayoutFeeValid(*mSetFees.fee, app.getMetrics());
                break;
            default:
                innerResult().code(SetFeesResultCode::INVALID_FEE_TYPE);
                app.getMetrics().NewMeter({"op-set-fees", "invalid", "invalid-operation-type"}, "operation").Mark();
                return false;
        }

        return isValidFee;
    }
}
