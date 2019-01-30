#pragma once

// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "overlay/StellarXDR.h"
#include "ledger/EntryFrame.h"
#include "crypto/Hex.h"

namespace stellar
{
using xdr::operator<;

/**
 * Compare two LedgerEntries or LedgerKeys for 'identity', not content.
 *
 * LedgerEntries are identified iff they have:
 *
 *   - The same type
 *     - If accounts, then with same accountID
 *     - If trustlines, then with same (accountID, asset) pair
 *     - If offers, then with same (sellerID, sequence) pair
 *
 * Equivalently: Two LedgerEntries have the same 'identity' iff their
 * corresponding LedgerKeys are exactly equal. This operator _could_ be
 * implemented in terms of extracting 2 LedgerKeys from 2 LedgerEntries and
 * doing operator< on them, but that would be comparatively inefficient.
 */
struct LedgerEntryIdCmp
{
    template <typename T, typename U>
    auto operator()(T const& a, U const& b) const -> decltype(a.type(),
                                                              b.type(), bool())
    {
        LedgerEntryType aty = a.type();
        LedgerEntryType bty = b.type();

        if (aty < bty)
            return true;

        if (aty > bty)
            return false;

        switch (aty) {

            case LedgerEntryType::ACCOUNT:
                return a.account().accountID < b.account().accountID;
            case LedgerEntryType::SIGNER:
                return a.signer().pubKey < b.signer().pubKey;
            case LedgerEntryType::FEE: {
                auto const &af = a.feeState();
                auto const &bf = b.feeState();
                auto hashAStr = binToHex(af.hash);
                auto hashBStr = binToHex(bf.hash);
                if (hashAStr < hashBStr)
                    return true;
                if (hashBStr < hashAStr)
                    return false;
                if (af.lowerBound < bf.lowerBound)
                    return true;
                if (bf.lowerBound < af.lowerBound)
                    return false;
                return af.upperBound < bf.upperBound;
            }
            case LedgerEntryType::BALANCE: {
                auto const &ab = a.balance();
                auto const &bb = b.balance();
                return ab.balanceID < bb.balanceID;
            }
            case LedgerEntryType::ASSET: {
                auto const &aa = a.asset();
                auto const &ba = b.asset();
                return aa.code < ba.code;
            }
            case LedgerEntryType::ACCOUNT_TYPE_LIMITS: {
                auto const &aatl = a.accountTypeLimits();
                auto const &batl = b.accountTypeLimits();
                return aatl.accountType < batl.accountType;
            }
            case LedgerEntryType::STATISTICS: {
                auto const &as = a.stats();
                auto const &bs = b.stats();
                return as.accountID < bs.accountID;
            }
            case LedgerEntryType::REFERENCE_ENTRY: {
                auto const &ap = a.reference();
                auto const &bp = b.reference();
                return ap.reference < bp.reference;
            }
            case LedgerEntryType::TRUST: {
                auto const &at = a.trust();
                auto const &bt = b.trust();
                if (at.balanceToUse < bt.balanceToUse)
                    return true;
                if (bt.balanceToUse < at.balanceToUse)
                    return false;
                return at.allowedAccount < bt.allowedAccount;
            }
            case LedgerEntryType::ACCOUNT_LIMITS: {
                auto const &al = a.accountLimits();
                auto const &bl = b.accountLimits();
                return al.accountID < bl.accountID;
            }
            case LedgerEntryType::ASSET_PAIR: {
                auto const &ap = a.assetPair();
                auto const &bp = b.assetPair();
                if (ap.base < bp.base)
                    return true;
                if (bp.base < ap.base)
                    return false;
                return ap.quote < bp.quote;
            }
            case LedgerEntryType::OFFER_ENTRY: {
                auto const &ap = a.offer();
                auto const &bp = b.offer();
                if (ap.offerID < bp.offerID)
                    return true;
                if (bp.offerID < ap.offerID)
                    return false;
                return ap.ownerID < bp.ownerID;
            }
            case LedgerEntryType::REVIEWABLE_REQUEST: {
                auto const &ar = a.reviewableRequest();
                auto const &br = b.reviewableRequest();
                return ar.requestID < br.requestID;
            }
            case LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID: {
                auto const &ae = a.externalSystemAccountID();
                auto const &be = b.externalSystemAccountID();
                if (ae.accountID < be.accountID)
                    return true;
                if (be.accountID < ae.accountID)
                    return false;
                return ae.externalSystemType < be.externalSystemType;
            }
            case LedgerEntryType::SALE: {
                auto const &as = a.sale();
                auto const &bs = b.sale();
                return as.saleID < bs.saleID;
            }
            case LedgerEntryType::KEY_VALUE: {
                auto const &akv = a.keyValue();
                auto const &bkv = b.keyValue();
                return akv.key < bkv.key;
            }
            case LedgerEntryType::ACCOUNT_KYC: {
                auto const &akyc = a.accountKYC();
                auto const &bkyc = b.accountKYC();
                return akyc.accountID < bkyc.accountID;
            }
            case LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
            {
                auto const& apool = a.externalSystemAccountIDPoolEntry();
                auto const& bpool = b.externalSystemAccountIDPoolEntry();
                return apool.poolEntryID < bpool.poolEntryID;
            }
            case LedgerEntryType::LIMITS_V2:
            {
                auto const& alim = a.limitsV2();
                auto const& blim = b.limitsV2();
                return alim.id < blim.id;
            }
            case LedgerEntryType::STATISTICS_V2:
            {
                auto const& astats = a.statisticsV2();
                auto const& bstats = b.statisticsV2();
                return astats.id < bstats.id;
            }
            case LedgerEntryType::PENDING_STATISTICS:
            {
                auto const& apend = a.pendingStatistics();
                auto const& bpend = b.pendingStatistics();
                if (apend.requestID < bpend.requestID)
                    return true;
                if (bpend.requestID < apend.requestID)
                    return false;
                return apend.statisticsID < bpend.statisticsID;
            }
            case LedgerEntryType::CONTRACT:
            {
                auto const& acon = a.contract();
                auto const& bcon = b.contract();
                return acon.contractID < bcon.contractID;
            }
            case LedgerEntryType::ATOMIC_SWAP_BID:
            {
                auto const& abid = a.atomicSwapBid();
                auto const& bbid = b.atomicSwapBid();
                return abid.bidID < bbid.bidID;
            }
            case LedgerEntryType::ACCOUNT_ROLE:
            {
                auto const& arole = a.accountRole();
                auto const& brole = b.accountRole();

                return arole.id < brole.id;
            }
            case LedgerEntryType::ACCOUNT_RULE:
            {
                auto const& aarp = a.accountRule();
                auto const& barp = b.accountRule();
                return aarp.id < barp.id;
            }
            default:
            {
                throw std::runtime_error("Unexpected state. LedgerCmp cannot compare structures. Unknown ledger entry type");
            }
        }
    }

    template <typename T>
    bool operator()(T const& a, LedgerEntry const& b) const
    {
        return (*this)(a, b.data);
    }

    template <typename T, typename = typename std::enable_if<
                              !std::is_same<T, LedgerEntry>::value>::type>
    bool operator()(LedgerEntry const& a, T const& b) const
    {
        return (*this)(a.data, b);
    }
};

/**
 * Compare two BucketEntries for identity by comparing their respective
 * LedgerEntries (ignoring their hashes, as the LedgerEntryIdCmp ignores their
 * bodies).
 */
struct BucketEntryIdCmp
{
    LedgerEntryIdCmp mCmp;
    bool operator()(BucketEntry const& a, BucketEntry const& b) const
    {
        BucketEntryType aty = a.type();
        BucketEntryType bty = b.type();

        if (aty == BucketEntryType::LIVEENTRY)
        {
            if (bty == BucketEntryType::LIVEENTRY)
            {
                return mCmp(a.liveEntry(), b.liveEntry());
            }
            else
            {
                return mCmp(a.liveEntry(), b.deadEntry());
            }
        }
        else
        {
            if (bty == BucketEntryType::LIVEENTRY)
            {
                return mCmp(a.deadEntry(), b.liveEntry());
            }
            else
            {
                return mCmp(a.deadEntry(), b.deadEntry());
            }
        }
    }
};
}
