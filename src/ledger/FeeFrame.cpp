#include "ledger/FeeFrame.h"
#include "crypto/SecretKey.h"
#include "crypto/SHA.h"
#include "LedgerDelta.h"
#include "util/types.h"

using namespace std;
using namespace soci;

namespace stellar
{

FeeFrame::FeeFrame() : EntryFrame(LedgerEntryType::FEE), mFee(mEntry.data.feeState())
{
}

FeeFrame::FeeFrame(LedgerEntry const& from)
: EntryFrame(from), mFee(mEntry.data.feeState())
{
}

FeeFrame::FeeFrame(FeeFrame const& from) : FeeFrame(from.mEntry)
{
}

FeeFrame& FeeFrame::operator=(FeeFrame const& other)
{
    if (&other != this)
    {
        mFee = other.mFee;
        mKey = other.mKey;
        mKeyCalculated = other.mKeyCalculated;
    }
    return *this;
}

FeeFrame::pointer FeeFrame::create(FeeType feeType, int64_t fixedFee,
    int64_t percentFee, AssetCode asset, AccountID* accountID, uint64_t assetPrecision)
{
    LedgerEntry le;
    le.data.type(LedgerEntryType::FEE);
    FeeEntry& entry = le.data.feeState();
    entry.fixedFee = fixedFee;
    entry.percentFee = percentFee;
    entry.feeType = feeType;
    entry.asset = asset;
    entry.subtype = SUBTYPE_ANY;
    if (accountID)
        entry.accountID.activate() = *accountID;

    entry.lowerBound = 0;
    entry.upperBound = INT64_MAX - (INT64_MAX % assetPrecision);

    entry.hash = calcHash(feeType, asset, accountID, nullptr, entry.subtype);
    return std::make_shared<FeeFrame>(le);
}

bool FeeFrame::isInRange(int64_t a, int64_t b, int64_t point)
{
    return a <= point && point <= b;
}

bool FeeFrame::calculatePercentFee(const uint64_t amount, uint64_t& result,
                                   const Rounding rounding, uint64_t roundingStep) const
{
    result = 0;
    if (mFee.percentFee == 0)
    {
        return true;
    }

    return bigDivide(result, amount, mFee.percentFee, 100 * ONE, rounding, roundingStep);
}

AssetCode FeeFrame::getFeeAsset() const
{
    return mFee.asset;
}

bool
FeeFrame::isValid(FeeEntry const& oe)
{
    auto res = oe.fixedFee >= 0
               && oe.percentFee >= 0
               && oe.percentFee <= 100 * ONE
               && isFeeTypeValid(oe.feeType)
               && oe.lowerBound <= oe.upperBound;
    return res;
}

Hash
FeeFrame::calcHash(FeeType feeType, AssetCode asset, AccountID* accountID, uint64_t* accountRole, int64_t subtype)
{
    std::string data = "";

    char buff[100];
    snprintf(buff, sizeof(buff), "type:%i", static_cast<int32_t>(feeType));
    std::string buffAsStdStr = buff;
    data += buffAsStdStr;

    snprintf(buff, sizeof(buff), "asset:%s", asset.c_str());
    buffAsStdStr = buff;
    data += buffAsStdStr;

    snprintf(buff, sizeof(buff), "subtype:%s", std::to_string(subtype).c_str());
    buffAsStdStr = buff;
    data += buffAsStdStr;

    if (accountID != nullptr) {
        std::string actIDStrKey = PubKeyUtils::toStrKey(*accountID);
        snprintf(buff, sizeof(buff), "accountID:%s", actIDStrKey.c_str());
        buffAsStdStr = buff;
        data += buffAsStdStr;
    }
    if (accountRole != nullptr) {
        snprintf(buff, sizeof(buff), "accountRole:%lu", *accountRole);
        buffAsStdStr = buff;
        data += buffAsStdStr;
    }

    return Hash(sha256(data));
}

bool
FeeFrame::isValid() const
{
    return isValid(mFee);
}

void FeeFrame::checkFeeType(FeeEntry const& feeEntry, FeeType feeType)
{
    if (feeEntry.feeType != feeType)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected fee type. Expected: "
                                               << xdr::xdr_traits<FeeType>::enum_name(feeType)
                                               << " but was: "
                                               << xdr::xdr_traits<FeeType>::enum_name(feeEntry.feeType);
        throw std::runtime_error("Unexpected fee type");
    }
}

LedgerKey const &
FeeFrame::getKey() const
{
    if (!mKeyCalculated) {
        mKey = LedgerKey(LedgerEntryType::FEE);
        mKey.feeState().hash = mFee.hash;
        mKey.feeState().lowerBound = mFee.lowerBound;
        mKey.feeState().upperBound = mFee.upperBound;
        mKeyCalculated = true;
    }
    return mKey;
}

}