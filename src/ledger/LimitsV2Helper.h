#pragma once

#include "EntryHelper.h"
#include "LimitsV2Frame.h"

namespace soci
{
    class session;
}

namespace stellar
{
class StatementContext;


class LimitsV2Helper : public EntryHelper
{
public:
    virtual std::vector<LimitsV2Frame::pointer> loadLimits(std::vector<StatsOpType> statsOpTypes,
                                                   AssetCode assetCode, xdr::pointer<AccountID> accountID = nullptr,
                                                   uint64_t* accountType = nullptr) = 0;
    virtual LimitsV2Frame::pointer loadLimits(StatsOpType statsOpType, AssetCode assetCode,
                                      xdr::pointer<AccountID> accountID, uint64_t* accountType,
                                      bool isConvertNeeded) = 0;
    virtual LimitsV2Frame::pointer loadLimits(uint64_t id) = 0;

    virtual std::vector<LimitsV2Frame::pointer> loadLimitsForAsset(AssetCode const& code) = 0;
};

}