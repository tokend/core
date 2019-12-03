#pragma once

#include <unordered_map>
#include "EntryHelper.h"
#include "AtomicSwapAskFrame.h"

namespace soci
{
class session;
}

namespace stellar
{

class StatementContext;

class AtomicSwapAskHelper : public EntryHelper
{
public:
    virtual bool
    existForAsset(const AssetCode& code) = 0;

    virtual AtomicSwapAskFrame::pointer
    loadAtomicSwapAsk(AccountID const& ownerID, uint64_t bidID) = 0;

    virtual AtomicSwapAskFrame::pointer
    loadAtomicSwapAsk(uint64_t bidID) = 0;

    virtual std::unordered_map<AccountID, std::vector<AtomicSwapAskFrame::pointer>>
    loadAllAtomicSwapAsks() = 0;
};

}