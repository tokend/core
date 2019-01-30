#include "LimitsV2Frame.h"


using namespace std;
using namespace soci;

namespace stellar
{
    LimitsV2Frame::LimitsV2Frame() : EntryFrame(LedgerEntryType::LIMITS_V2), mLimitsV2(mEntry.data.limitsV2()){}

    LimitsV2Frame::LimitsV2Frame(LedgerEntry const& from) : EntryFrame(from), mLimitsV2(mEntry.data.limitsV2()) {}

    LimitsV2Frame::LimitsV2Frame(LimitsV2Frame const& from) : LimitsV2Frame(from.mEntry){}

    LimitsV2Frame& LimitsV2Frame::operator=(LimitsV2Frame const& other)
    {
        if (&other != this)
        {
            mLimitsV2 = other.mLimitsV2;
            mKey = other.mKey;
            mKeyCalculated = other.mKeyCalculated;
        }
        return *this;
    }

    bool
    LimitsV2Frame::isValid(LimitsV2Entry const& limitsV2)
    {
        if (limitsV2.dailyOut > limitsV2.weeklyOut)
            return false;
        if (limitsV2.weeklyOut > limitsV2.monthlyOut)
            return false;
        return limitsV2.monthlyOut <= limitsV2.annualOut;
    }

    bool LimitsV2Frame::isValid() const
    {
        return isValid(mLimitsV2);
    }

    void LimitsV2Frame::changeLimits(ManageLimitsOp const& manageLimitsOp)
    {
        mLimitsV2.dailyOut = manageLimitsOp.details.limitsCreateDetails().dailyOut;
        mLimitsV2.weeklyOut = manageLimitsOp.details.limitsCreateDetails().weeklyOut;
        mLimitsV2.monthlyOut = manageLimitsOp.details.limitsCreateDetails().monthlyOut;
        mLimitsV2.annualOut = manageLimitsOp.details.limitsCreateDetails().annualOut;
    }

    LimitsV2Frame::pointer
    LimitsV2Frame::createNew(uint64_t id, ManageLimitsOp const& manageLimitsOp)
    {
        LedgerEntry le;
        le.data.type(LedgerEntryType::LIMITS_V2);
        LimitsV2Entry& entry = le.data.limitsV2();

        entry.id = id;
        entry.accountRole = manageLimitsOp.details.limitsCreateDetails().accountRole;
        entry.accountID = manageLimitsOp.details.limitsCreateDetails().accountID;
        entry.statsOpType = manageLimitsOp.details.limitsCreateDetails().statsOpType;
        entry.assetCode = manageLimitsOp.details.limitsCreateDetails().assetCode;
        entry.isConvertNeeded = manageLimitsOp.details.limitsCreateDetails().isConvertNeeded;

        auto limitsV2Frame = std::make_shared<LimitsV2Frame>(le);
        limitsV2Frame->changeLimits(manageLimitsOp);

        return limitsV2Frame;
    }
}
