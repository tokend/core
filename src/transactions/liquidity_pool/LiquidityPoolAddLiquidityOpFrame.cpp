#include "LiquidityPoolAddLiquidityOpFrame.h"

#include <main/Application.h>

#include <ledger/StorageHelper.h>
#include <ledger/BalanceHelper.h>
#include <ledger/AssetHelper.h>
#include <ledger/LiquidityPoolHelper.h>
#include <ledger/LedgerDelta.h>
#include <ledger/AccountHelper.h>

#include <transactions/managers/BalanceManager.h>
#include <transactions/issuance/CreateIssuanceRequestOpFrame.h>

#include <crypto/StrKey.h>

namespace stellar
{
    LiquidityPoolAddLiquidityOpFrame::
    LiquidityPoolAddLiquidityOpFrame(const Operation& op, OperationResult& opRes, TransactionFrame& parentTx)
        : OperationFrame(op, opRes, parentTx),
          mAddLiquidity(const_cast<LPAddLiquidityOp&>(mOperation.body.lpAddLiquidityOp()))
    {
    }

    bool LiquidityPoolAddLiquidityOpFrame::tryGetOperationConditions(StorageHelper& sh,
        std::vector<OperationCondition>& result) const
    {
        auto& balanceHelper = sh.getBalanceHelper();
        auto firstBalanceFrame = balanceHelper.loadBalance(mAddLiquidity.firstAssetBalance);
        auto secondBalanceFrame = balanceHelper.loadBalance(mAddLiquidity.secondAssetBalance);
        if (!firstBalanceFrame || !secondBalanceFrame)
        {
            mResult.code(OperationResultCode::opNO_ENTRY);
            mResult.entryType() = LedgerEntryType::BALANCE;

            return false;
        }

        auto& assetHelper = sh.getAssetHelper();
        auto firstAssetFrame = assetHelper.mustLoadAsset(firstBalanceFrame->getAsset());
        auto secondAssetFrame = assetHelper.mustLoadAsset(secondBalanceFrame->getAsset());

        AccountRuleResource resource(LedgerEntryType::LIQUIDITY_POOL);
        resource.liquidityPool().firstAsset = firstAssetFrame->getCode();
        resource.liquidityPool().firstAssetType = firstAssetFrame->getType();
        resource.liquidityPool().secondAsset = secondAssetFrame->getCode();
        resource.liquidityPool().secondAssetType = secondAssetFrame->getType();

        result.emplace_back(resource, AccountRuleAction::MANAGE_LIQUIDITY, mSourceAccount);

        return true;
    }

    bool LiquidityPoolAddLiquidityOpFrame::tryGetSignerRequirements(StorageHelper& sh,
        std::vector<SignerRequirement>& result) const
    {
        auto& balanceHelper = sh.getBalanceHelper();
        auto firstBalanceFrame = balanceHelper.loadBalance(mAddLiquidity.firstAssetBalance);
        auto secondBalanceFrame = balanceHelper.loadBalance(mAddLiquidity.secondAssetBalance);
        if (!firstBalanceFrame || !secondBalanceFrame)
        {
            mResult.code(OperationResultCode::opNO_ENTRY);
            mResult.entryType() = LedgerEntryType::BALANCE;

            return false;
        }

        auto& assetHelper = sh.getAssetHelper();
        auto firstAssetFrame = assetHelper.mustLoadAsset(firstBalanceFrame->getAsset());
        auto secondAssetFrame = assetHelper.mustLoadAsset(secondBalanceFrame->getAsset());

        SignerRuleResource resource(LedgerEntryType::LIQUIDITY_POOL);
        resource.liquidityPool().firstAsset = firstAssetFrame->getCode();
        resource.liquidityPool().firstAssetType = firstAssetFrame->getType();
        resource.liquidityPool().secondAsset = secondAssetFrame->getCode();
        resource.liquidityPool().secondAssetType = secondAssetFrame->getType();

        result.emplace_back(resource, SignerRuleAction::MANAGE_LIQUIDITY);

        return true;
    }

    bool LiquidityPoolAddLiquidityOpFrame::doCheckValid(Application &app)
    {
        if (mAddLiquidity.firstAssetDesiredAmount == 0 ||
            mAddLiquidity.secondAssetDesiredAmount == 0)
        {
            innerResult().code(LPAddLiquidityResultCode::INVALID_DESIRED_AMOUNT);
            return false;
        }

        if (mAddLiquidity.firstAssetMinAmount == 0 ||
            mAddLiquidity.secondAssetMinAmount == 0)
        {
            innerResult().code(LPAddLiquidityResultCode::INVALID_MIN_AMOUNT);
            return false;
        }

        if (mAddLiquidity.firstAssetBalance.operator==(mAddLiquidity.secondAssetBalance))
        {
            innerResult().code(LPAddLiquidityResultCode::MALFORMED);
            return false;
        }

        if (mAddLiquidity.firstAssetMinAmount > mAddLiquidity.firstAssetDesiredAmount ||
            mAddLiquidity.secondAssetMinAmount > mAddLiquidity.secondAssetDesiredAmount)
        {
            innerResult().code(LPAddLiquidityResultCode::MIN_AMOUNT_BIGGER_THAN_DESIRED);
            return false;
        }

        return true;
    }

    bool LiquidityPoolAddLiquidityOpFrame::doApply(Application& app, StorageHelper& sh, LedgerManager& lm)
    {
        auto& balanceHelper = sh.getBalanceHelper();
        auto& accountHelper = sh.getAccountHelper();
        auto& assetHelper = sh.getAssetHelper();

        auto sourceAccountID = mSourceAccount->getID();

        mSourceFirstBalance = balanceHelper.loadBalance(mAddLiquidity.firstAssetBalance, sourceAccountID);
        mSourceSecondBalance = balanceHelper.loadBalance(mAddLiquidity.secondAssetBalance, sourceAccountID);

        if (!mSourceFirstBalance || !mSourceSecondBalance)
        {
            innerResult().code(LPAddLiquidityResultCode::SRC_BALANCE_NOT_FOUND);
            return false;
        }

        auto firstAsset = assetHelper.mustLoadAsset(mSourceFirstBalance->getAsset());
        auto secondAsset = assetHelper.mustLoadAsset(mSourceSecondBalance->getAsset());
        if (firstAsset->getTrailingDigitsCount() != secondAsset->getTrailingDigitsCount())
        {
            innerResult().code(LPAddLiquidityResultCode::INCORRECT_AMOUNT_PRECISION);
            return false;
        }

        auto const& firstAssetCode = firstAsset->getCode();
        auto const& secondAssetCode = secondAsset->getCode();

        if (firstAssetCode == secondAssetCode)
        {
            innerResult().code(LPAddLiquidityResultCode::MALFORMED);
            return false;
        }

        normalize(firstAssetCode, secondAssetCode);

        uint64_t firstReserveDiff, secondReserveDiff;

        auto& lpHelper = sh.getLiquidityPoolHelper();
        auto poolFrame = lpHelper.loadPool(mSourceFirstBalance->getAsset(), mSourceSecondBalance->getAsset());
        if (!poolFrame)
        {
            mLPTokenAssetCode = calculateLPAssetCode(mSourceFirstBalance->getAsset(), mSourceSecondBalance->getAsset());

            poolFrame = mustCreateLiquidityPool(app, sh);

            mFromFirstAssetAmount = mAddLiquidity.firstAssetDesiredAmount;
            mFromSecondAssetAmount = mAddLiquidity.secondAssetDesiredAmount;

            mLPTokensAmountToIssue = std::sqrt(mAddLiquidity.firstAssetDesiredAmount *
                mAddLiquidity.secondAssetDesiredAmount);

            firstReserveDiff = mFromFirstAssetAmount;
            secondReserveDiff = mFromSecondAssetAmount;
        }
        else
        {
            uint64_t firstAssetReserve = poolFrame->getFirstReserve();
            uint64_t secondAssetReserve = poolFrame->getSecondReserve();

            mLPFirstBalance = balanceHelper.loadFirstBalance(poolFrame->getAccountID(),
                mSourceFirstBalance->getAsset());
            mLPSecondBalance = balanceHelper.loadFirstBalance(poolFrame->getAccountID(),
                mSourceSecondBalance->getAsset());

            if (!calculateLPOutputs(firstAssetReserve, secondAssetReserve))
            {
                return false;
            }

            uint64_t lpTokensAmount = poolFrame->getLPTokensAmount();
            firstReserveDiff = mLPFirstBalance->getAmount() + mFromFirstAssetAmount - firstAssetReserve;
            secondReserveDiff = mLPSecondBalance->getAmount() + mFromSecondAssetAmount - secondAssetReserve;

            uint64_t fromFirstAsset, fromSecondAsset;
            if (!bigDivide(fromFirstAsset, firstReserveDiff, lpTokensAmount, firstAssetReserve, ROUND_DOWN) ||
                !bigDivide(fromSecondAsset, secondReserveDiff, lpTokensAmount, secondAssetReserve, ROUND_DOWN))
            {
                CLOG(ERROR, Logging::OPERATION_LOGGER)
                    << "Unexpected state: LP tokens calculated amount overflows UINT64_MAX, "
                    << "liquidity pool id: "
                    << poolFrame->getPoolID();
                throw std::runtime_error("Unexpected state: LP tokens calculated amount overflows UINT64_MAX");
            }

            mLPTokensAmountToIssue = std::min(fromFirstAsset, fromSecondAsset);
            mLPAccountID = poolFrame->getAccountID();
            mSourceLPTokensBalance = balanceHelper.loadBalance(sourceAccountID, poolFrame->getLpTokenAsset());
        }

        if (mLPTokensAmountToIssue == 0)
        {
            innerResult().code(LPAddLiquidityResultCode::INSUFFICIENT_LIQUIDITY_PROVIDED);
            return false;
        }

        if (!mSourceLPTokensBalance)
        {
            auto balanceManager = BalanceManager(app, sh);

            mSourceLPTokensBalance = balanceManager.loadOrCreateBalance(mSourceAccount->getID(),
                poolFrame->getLpTokenAsset());
        }

        mLiquidityPoolID = poolFrame->getKey().liquidityPool().id;

        if (!transferAssets(app, sh, lm))
        {
            return false;
        }

        auto lpEntry = poolFrame->getLiquidityPoolEntry();
        lpEntry.lpTokensTotalCap += mLPTokensAmountToIssue;
        lpEntry.firstReserve += firstReserveDiff;
        lpEntry.secondReserve += secondReserveDiff;

        LedgerEntry entry;
        entry.data.type(LedgerEntryType::LIQUIDITY_POOL);
        entry.data.liquidityPool() = lpEntry;
        lpHelper.storeChange(entry);

        innerResult().code(LPAddLiquidityResultCode::SUCCESS);
        innerResult().success().liquidityPoolID = mLiquidityPoolID;
        innerResult().success().lpAccountID = mLPAccountID;
        innerResult().success().firstAssetBalanceID = mLPFirstBalance->getBalanceID();
        innerResult().success().secondAssetBalanceID = mLPSecondBalance->getBalanceID();
        innerResult().success().lpAsset = mLPTokenAssetCode;
        innerResult().success().lpTokensAmount = lpEntry.lpTokensTotalCap;

        return true;
    }

    void LiquidityPoolAddLiquidityOpFrame::normalize(AssetCode const& firstAsset, AssetCode const& secondAsset)
    {
        if (firstAsset > secondAsset)
        {
            std::swap(mAddLiquidity.firstAssetDesiredAmount, mAddLiquidity.secondAssetDesiredAmount);
            std::swap(mAddLiquidity.firstAssetMinAmount, mAddLiquidity.secondAssetMinAmount);
            std::swap(mAddLiquidity.firstAssetBalance, mAddLiquidity.secondAssetBalance);
            std::swap(mSourceFirstBalance, mSourceSecondBalance);
        }
    }

    bool LiquidityPoolAddLiquidityOpFrame::calculateLPOutputs(uint64_t const firstAssetReserve,
        uint64_t const secondAssetReserve)
    {
        auto secondAmountOptimal = quote(mAddLiquidity.firstAssetDesiredAmount,
            firstAssetReserve, secondAssetReserve);
        if (secondAmountOptimal <= mAddLiquidity.secondAssetDesiredAmount)
        {
            if (secondAmountOptimal < mAddLiquidity.secondAssetMinAmount)
            {
                innerResult().code(LPAddLiquidityResultCode::INSUFFICIENT_SECOND_ASSET_AMOUNT);
                return false;
            }

            mFromFirstAssetAmount = mAddLiquidity.firstAssetDesiredAmount;
            mFromSecondAssetAmount = secondAmountOptimal;
        }
        else
        {
            auto firstAmountOptimal = quote(mAddLiquidity.secondAssetDesiredAmount,
                secondAssetReserve, firstAssetReserve);
            if (firstAmountOptimal <= mAddLiquidity.firstAssetDesiredAmount &&
                firstAmountOptimal >= mAddLiquidity.firstAssetMinAmount)
            {
                mFromFirstAssetAmount = firstAmountOptimal;
                mFromSecondAssetAmount = mAddLiquidity.secondAssetDesiredAmount;
            }
            else
            {
                innerResult().code(LPAddLiquidityResultCode::INSUFFICIENT_FIRST_ASSET_AMOUNT);
                return false;
            }
        }

        return true;
    }

    LiquidityPoolFrame::pointer
    LiquidityPoolAddLiquidityOpFrame::mustCreateLiquidityPool(Application& app, StorageHelper& sh)
    {
        mustCreateLiquidityPoolAccount(sh);
        mustCreateLiquidityPoolBalances(app, sh);

        LiquidityPoolEntry lpEntry;
        uint64_t lpID = sh.mustGetLedgerDelta().getHeaderFrame().generateID(LedgerEntryType::LIQUIDITY_POOL);
        lpEntry.id = lpID;
        lpEntry.liquidityPoolAcount = mLPAccountID;
        lpEntry.firstAssetBalance = mLPFirstBalance->getBalanceID();
        lpEntry.secondAssetBalance = mLPSecondBalance->getBalanceID();
        lpEntry.lpTokenAssetCode = mLPTokenAssetCode;

        LedgerEntry entry;
        entry.data.type(LedgerEntryType::LIQUIDITY_POOL);
        entry.data.liquidityPool() = lpEntry;
        sh.getLiquidityPoolHelper().storeAdd(entry);

        return std::make_shared<LiquidityPoolFrame>(entry);
    }

    void LiquidityPoolAddLiquidityOpFrame::mustCreateLiquidityPoolAccount(StorageHelper& sh)
    {
        uint64_t accountSeqID = sh.mustGetLedgerDelta().getHeaderFrame().generateID(LedgerEntryType::ACCOUNT);

        AccountEntry accountEntry;
        accountEntry.accountID = AccountKeyUtils::forLiquidityPoolAsset(mLPTokenAssetCode);
        accountEntry.sequentialID = accountSeqID;

        LedgerEntry entry;
        entry.data.type(LedgerEntryType::ACCOUNT);
        entry.data.account() = accountEntry;
        sh.getAccountHelper().storeAdd(entry);

        mLPAccountID = accountEntry.accountID;
    }

    void LiquidityPoolAddLiquidityOpFrame::mustCreateLiquidityPoolBalances(Application& app, StorageHelper& sh)
    {
        auto& balanceHelper = sh.getBalanceHelper();
        auto sourceFirstBalanceFrame = balanceHelper.loadBalance(mAddLiquidity.firstAssetBalance);
        auto sourceSecondBalanceFrame = balanceHelper.loadBalance(mAddLiquidity.secondAssetBalance);

        auto& assetHelper = sh.getAssetHelper();
        auto firstAssetFrame = assetHelper.mustLoadAsset(sourceFirstBalanceFrame->getAsset());
        auto secondAssetFrame = assetHelper.mustLoadAsset(sourceSecondBalanceFrame->getAsset());

        BalanceManager balanceManager(app, sh);

        auto lpFirstBalanceFrame = balanceManager.loadOrCreateBalance(mLPAccountID, firstAssetFrame->getCode());
        auto lpSecondBalanceFrame = balanceManager.loadOrCreateBalance(mLPAccountID, secondAssetFrame->getCode());

        AssetEntry assetEntry;
        assetEntry.code = mLPTokenAssetCode;
        assetEntry.details = R"({"name":"LP:)"+firstAssetFrame->getCode()+":"+secondAssetFrame->getCode()+R"("})";
        assetEntry.trailingDigitsCount = AssetFrame::kMaximumTrailingDigits;
        assetEntry.owner = mLPAccountID;
        assetEntry.maxIssuanceAmount = UINT64_MAX;
        assetEntry.availableForIssueance = UINT64_MAX;

        AssetFrame::ensureValid(assetEntry);

        LedgerEntry entry;
        entry.data.type(LedgerEntryType::ASSET);
        entry.data.asset() = assetEntry;
        assetHelper.storeAdd(entry);

        mSourceLPTokensBalance = balanceManager.loadOrCreateBalance(mSourceAccount->getID(), assetEntry.code);

        mSourceFirstBalance = sourceFirstBalanceFrame;
        mSourceSecondBalance = sourceSecondBalanceFrame;
        mLPFirstBalance = lpFirstBalanceFrame;
        mLPSecondBalance = lpSecondBalanceFrame;
    }

    bool LiquidityPoolAddLiquidityOpFrame::transferAssets(Application& app, StorageHelper& sh, LedgerManager& lm)
    {
        auto& accountHelper = sh.getAccountHelper();
        auto lpAccountFrame = accountHelper.loadAccount(mLPAccountID);

        uint32_t allTasks = 0;
        const auto lpTokensIssuanceRequestOp = CreateIssuanceRequestOpFrame::build(mSourceLPTokensBalance->getAsset(),
            mLPTokensAmountToIssue, mSourceLPTokensBalance->getBalanceID(), lm, allTasks);

        Operation op;
        op.sourceAccount.activate() = mLPAccountID;
        op.body.type(OperationType::CREATE_ISSUANCE_REQUEST);
        op.body.createIssuanceRequestOp() = lpTokensIssuanceRequestOp;

        OperationResult opRes;
        opRes.code(OperationResultCode::opINNER);
        opRes.tr().type(OperationType::CREATE_ISSUANCE_REQUEST);
        CreateIssuanceRequestOpFrame createIssuanceRequestOpFrame(op, opRes, mParentTx);
        createIssuanceRequestOpFrame.doNotRequireFee();
        createIssuanceRequestOpFrame.setSourceAccountPtr(lpAccountFrame);

        if (!createIssuanceRequestOpFrame.doCheckValid(app) ||
            !createIssuanceRequestOpFrame.doApply(app, sh, lm))
        {
            CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: failed to apply create issuance request on provide liquidity to pool: "
                << mLiquidityPoolID;
            throw std::runtime_error("Unexpected state: failed to create issuance request on provide liquidity");
        }

        auto issuanceResult = createIssuanceRequestOpFrame.getResult().tr().createIssuanceRequestResult();

        if (issuanceResult.code() != CreateIssuanceRequestResultCode::SUCCESS)
        {
            CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state. Create issuance request returned unexpected result!"
                << xdr::xdr_traits<CreateIssuanceRequestResultCode>::enum_name(issuanceResult.code())
                << "; liquidityPoolID: " << mLiquidityPoolID;
            throw std::runtime_error("Unexpected state. Create issuance request returned unexpected result!");
        }

        BalanceManager balanceManager(app, sh);
        auto res = balanceManager.transfer(mSourceAccount, mSourceFirstBalance, mLPFirstBalance, mFromFirstAssetAmount);
        if (res != BalanceManager::Result::SUCCESS)
        {
            setTransferCode(res);
            return false;
        }

        res = balanceManager.transfer(mSourceAccount, mSourceSecondBalance, mLPSecondBalance, mFromSecondAssetAmount);
        if (res != BalanceManager::Result::SUCCESS)
        {
            setTransferCode(res);
            return false;
        }

        return true;
    }

    void LiquidityPoolAddLiquidityOpFrame::setTransferCode(BalanceManager::Result transferResult)
    {
        switch (transferResult)
        {
        case BalanceManager::UNDERFUNDED:
            innerResult().code(LPAddLiquidityResultCode::UNDERFUNDED);
            return;
        case BalanceManager::LINE_FULL:
            innerResult().code(LPAddLiquidityResultCode::LINE_FULL);
            return;
        case BalanceManager::INCORRECT_PRECISION:
            innerResult().code(LPAddLiquidityResultCode::INCORRECT_AMOUNT_PRECISION);
            return;
        default:
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected result code from transfer: " << transferResult;
            throw std::runtime_error("Unexpected result code from balance manager transfers");
        }
    }

    AssetCode LiquidityPoolAddLiquidityOpFrame::calculateLPAssetCode(AssetCode const& first, AssetCode const& second)
    {
        AssetCode lFirst = first, lSecond = second;
        if (first > second)
        {
            lFirst.swap(lSecond);
        }

        std::string lpTokenCodeStr = "LP:" + lFirst + ":" + lSecond;
        Hash lpTokenHash = HashUtils::fromStr(lpTokenCodeStr);
        auto key = strKey::toStrKey(strKey::STRKEY_BALANCE_ED25519, lpTokenHash).value;

        return {std::begin(key), std::begin(key) + 16};
    }

    uint64 LiquidityPoolAddLiquidityOpFrame::quote(uint64_t firstAmount, uint64_t firstReserve, uint64_t secondReserve)
    {
        if (!firstAmount || !firstReserve || !secondReserve)
        {
            return 0;
        }

        return firstAmount * secondReserve / firstReserve;
    }
}
