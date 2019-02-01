#pragma once

#include "EntryHelper.h"
#include "SignerRuleFrame.h"

namespace stellar
{

class SignerRuleHelper : public EntryHelper
{
public:
    virtual std::vector<SignerRuleFrame::pointer>
    loadSignerRules(std::vector<uint64_t> const ruleIDs) = 0;
};
}