#pragma once

// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ledger/OfferFrame.h"
#include "ledger/AssetPairFrame.h"
#include "ledger/BalanceFrame.h"
#include <functional>
#include <vector>

namespace stellar
{
enum class ExchangeResultType
{
    NORMAL,
    RESULT_OVERFLOW
};

struct ExchangeResult
{
    int64_t baseDelta;
    int64_t quoteDelta;

    int64_t buyerFee;
    int64_t sellerFee;

    int64_t matchPrice;

    ExchangeResultType type;
};

class OfferExchange
{
    uint64_t mOrderBookID;
    LedgerDelta& mDelta;
    LedgerManager& mLedgerManager;
    int64_t mNow;

    AssetPairFrame::pointer mAssetPair;

    BalanceFrame::pointer mCommissionBalance;

    std::vector<ClaimOfferAtom> mOfferTrail;
    int64_t mFeePaidByA;

    ClaimOfferAtom createOfferClaim(OfferEntry const& offerB,
                                    ExchangeResult const& match);

    int64 getMatchPrice(OfferEntry const& buy, OfferEntry const& sell);

public:
    enum CrossOfferResult
    {
        eOfferPartial,
        eOfferTaken,
        eOfferCantConvert
    };

private:

    bool getQuoteAmountBasedOnFee(OfferEntry const& offer,
                                  int64_t& quoteAmountBasedOnFee,
                                  uint64_t quotePrecisionStep);

    ExchangeResult exchange(OfferEntry& offerA, OfferEntry& offerB,
                            uint64_t basePrecisionStep, uint64_t quotePrecisionStep);
    ExchangeResult exchange(int64_t buyerBase, int64_t buyerQuote,
                            int64_t sellerBase, int64_t sellerQuote,
                            int64_t matchPrice, uint64_t basePrecisionStep,
                            uint64_t quotePrecisionStep);

    BalanceFrame::pointer loadBalance(BalanceID& balanceID, Database& db);

    // deletes offer and unlockes locked amount
    void markOfferAsTaken(OfferFrame& offer, BalanceFrame::pointer baseBalance,
                          BalanceFrame::pointer quoteBalance, Database& db);

public:
    OfferExchange(LedgerDelta& delta,LedgerManager& ledgerManager,
                  AssetPairFrame::pointer assetPair,
                  BalanceFrame::pointer commissionBalance, uint64_t orderBookID);

    CrossOfferResult crossOffer(OfferEntry& offerA,
                                BalanceFrame::pointer baseBalanceA,
                                BalanceFrame::pointer quoteBalanceA,
                                OfferFrame& offerB);

    enum OfferFilterResult
    {
        eKeep,
        eStop,
        eSkip
    };

    enum ConvertResult
    {
        eOK,
        ePartial,
        eFilterStop
    };

    // buys wheat with sheep, crossing as many offers as necessary
    ConvertResult convertWithOffers(OfferEntry& offerA,
                                    BalanceFrame::pointer baseBalanceA,
                                    BalanceFrame::pointer quoteBalanceA,
                                    std::function<OfferFilterResult(
                                        OfferFrame const& offer)> filter);

    std::vector<ClaimOfferAtom> const& getOfferTrail() const
    {
        return mOfferTrail;
    }

    int64_t getFeePaidByA() const
    {
        return mFeePaidByA;
    }

    bool offerNeedsMore(OfferEntry& offer, uint64_t quotePrecisionStep);

    static bool isOfferPriceMeetAssetPairRestrictions(
        AssetPairFrame::pointer assetPair, int64_t offerPrice);

    static void unlockBalancesForTakenOffer(OfferFrame& offer,
                                            BalanceFrame::pointer baseBalance,
                                            BalanceFrame::pointer quoteBalance);

    static void offerMatched(OfferEntry& offer,
                             BalanceFrame::pointer baseBalance,
                             BalanceFrame::pointer quoteBalance,
                             ExchangeResult match);

    static bool setFeeToPay(int64_t& feeToPay, int64_t quoteAmount,
                            int64_t percentFee);
};
}
