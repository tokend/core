// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "AssetFrame.h"
#include "util/types.h"
#include "xdrpp/printer.h"
#include <locale>

using namespace std;

namespace stellar
{
using xdr::operator<;

const uint32 AssetFrame::kMaximumTrailingDigits;

AssetFrame::AssetFrame() : EntryFrame(LedgerEntryType::ASSET)
                         , mAsset(mEntry.data.asset())
{
}

AssetFrame::AssetFrame(LedgerEntry const& from)
    : EntryFrame(from)
    , mAsset(mEntry.data.asset())
{
}

AssetFrame::AssetFrame(AssetFrame const& from) : AssetFrame(from.mEntry)
{
}

AssetFrame& AssetFrame::operator=(AssetFrame const& other)
{
    if (&other != this)
    {
        mAsset = other.mAsset;
        mKey = other.mKey;
        mKeyCalculated = other.mKeyCalculated;
    }
    return *this;
}

AssetFrame::pointer AssetFrame::create(AssetCreationRequest const& request,
                                       AccountID const& owner)
{
    LedgerEntry le;
    le.data.type(LedgerEntryType::ASSET);
    AssetEntry& asset = le.data.asset();
    asset.availableForIssueance = request.initialPreissuedAmount;
    asset.code = request.code;
    asset.details = request.creatorDetails;
    asset.issued = 0;
    asset.maxIssuanceAmount = request.maxIssuanceAmount;
    asset.owner = owner;
    asset.policies = request.policies;
    asset.type = request.type;
    asset.preissuedAssetSigner = request.preissuedAssetSigner;
    asset.pendingIssuance = 0;
    asset.trailingDigitsCount = request.trailingDigitsCount;

    return std::make_shared<AssetFrame>(le);
}

uint64_t AssetFrame::getPendingIssuance() const
{
    return mAsset.pendingIssuance;
}

bool AssetFrame::willExceedMaxIssuanceAmount(const uint64_t amount) const
{
    uint64_t issued;
    if (!safeSum(issued, {mAsset.issued, amount, mAsset.pendingIssuance}))
    {
        return true;
    }

    return issued > mAsset.maxIssuanceAmount;
}

bool AssetFrame::tryIssue(uint64_t amount)
{
    if (willExceedMaxIssuanceAmount(amount))
    {
        return false;
    }

    if (!isAvailableForIssuanceAmountSufficient(amount))
    {
        return false;
    }

    mAsset.availableForIssueance -= amount;
    mAsset.issued += amount;
    return true;
}

bool AssetFrame::tryUnIssue(uint64_t amount)
{
    if (mAsset.issued < amount) {
        return false;
    }

    mAsset.issued -= amount;
    return tryAddAvailableForIssuance(amount);
}

bool AssetFrame::canAddAvailableForIssuance(uint64_t amount)
{
    uint64_t availableForIssuance;
    if (!safeSum(availableForIssuance, {mAsset.availableForIssueance, mAsset.pendingIssuance, amount}))
        return false;

    uint64_t maxAmountCanBeIssuedAfterUpdate;
    if (!safeSum(mAsset.issued, availableForIssuance,
                 maxAmountCanBeIssuedAfterUpdate))
        return false;

    return maxAmountCanBeIssuedAfterUpdate <= mAsset.maxIssuanceAmount;
}

bool AssetFrame::tryAddAvailableForIssuance(uint64_t amount)
{
    if (!canAddAvailableForIssuance(amount))
        return false;

    mAsset.availableForIssueance += amount;
    return true;
}

bool AssetFrame::tryWithdraw(const uint64_t amount)
{
    if (mAsset.issued < amount)
    {
        return false;
    }

    mAsset.issued -= amount;
    return true;
}

bool AssetFrame::lockIssuedAmount(const uint64_t amount)
{
    if (willExceedMaxIssuanceAmount(amount))
    {
        return false;
    }

    if (!isAvailableForIssuanceAmountSufficient(amount))
    {
        return false;
    }

    mAsset.availableForIssueance -= amount;
    mAsset.pendingIssuance += amount;
    return true;
}

void AssetFrame::mustUnlockIssuedAmount(uint64_t const amount)
{
    if (mAsset.pendingIssuance < amount)
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER) << "Expected amount to be less then pending issuance; asset: " << xdr::xdr_to_string(mAsset) << "; amount: " << amount;
        throw runtime_error("Expected amount to be less then pending issuance");
    }

    mAsset.pendingIssuance -= amount;
    if (!safeSum(amount, mAsset.availableForIssueance, mAsset.availableForIssueance))
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER) << "Overflow on unlock issued amount. Failed to add availableForIssueance; asset: "
            << xdr::xdr_to_string(mAsset) << "; amount: " << amount;
        throw runtime_error("Overflow on unlock issued amount. Failed to add availableForIssueance");
    }
}

bool AssetFrame::isAssetCodeValid(AssetCode const& code)
{
    bool zeros = false;
    bool onechar = false; // at least one non zero character
    for (uint8_t b : code)
    {
        if (b == 0)
        {
            zeros = true;
        }
        else if (zeros)
        {
            // zeros can only be trailing
            return false;
        }
        else
        {
            auto bAsChar = (char)b;
            if (b > 0x7F || !std::isalnum(bAsChar, std::locale::classic()))
            {
                return false;
            }
            onechar = true;
        }
    }
    return onechar;
}

uint32 AssetFrame::getTrailingDigitsCount() const
{
    return mAsset.trailingDigitsCount;
}

void AssetFrame::setTrailingDigitsCount(uint32 trailingDigitsCount)
{
    mAsset.trailingDigitsCount = trailingDigitsCount;
}

uint64 AssetFrame::getMinimumAmount() const
{
    return getMinimumAmountFromTrailingDigits(mAsset.trailingDigitsCount);
}

uint64 AssetFrame::getMinimumAmountFromTrailingDigits(stellar::uint32 trailingDigitsCount)
{
    const int nullDigits = AssetFrame::kMaximumTrailingDigits - trailingDigitsCount;
    if (nullDigits < 0)
    {
        throw std::runtime_error("Unexpected error: more trailing digits than maximum");
    }
    uint64 result = 1;
    for (int i = 0; i < nullDigits; i++)
    {
        result *= 10;
    }
    return result;
}

void AssetFrame::ensureValid(AssetEntry const& oe)
{
    try
    {
        uint64_t totalIssuedOrLocked;
        if (!safeSum(totalIssuedOrLocked, { oe.issued, oe.pendingIssuance, oe.availableForIssueance }))
        {
            throw runtime_error("Overflow during calculation of totalIssuedOrLocked");
        }

        if (oe.maxIssuanceAmount < totalIssuedOrLocked)
        {
            throw runtime_error("totalIssuedOrLocked exceeds max issuance amount");
        }

        if (!isAssetCodeValid(oe.code))
        {
            throw runtime_error("asset code is invalid");
        }

        if (!isValidJson(oe.details))
        {
            throw runtime_error("details is invalid");
        }

        if (oe.trailingDigitsCount > kMaximumTrailingDigits)
        {
            throw runtime_error("Too many trailing digits");
        }
        const uint64_t precision = getMinimumAmountFromTrailingDigits(oe.trailingDigitsCount);
        if (oe.availableForIssueance % precision != 0)
        {
            throw runtime_error("Invalid available for issuance amount");
        }
        if (oe.issued % precision != 0)
        {
            throw runtime_error("Invalid issued amount");
        }
        if (oe.pendingIssuance % precision != 0)
        {
            throw runtime_error("Invalid pending issuance amount");
        }
    }
    catch (...)
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER) << "Unexpected asset entry is invalid: " << xdr::xdr_to_string(oe);
        throw_with_nested(runtime_error("Asset entry is invalid"));
    }
}

void AssetFrame::ensureValid() const
{
    ensureValid(mAsset);
}
}
