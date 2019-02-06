#pragma once

#include "EntryHelper.h"
#include "SignerRuleFrame.h"

namespace stellar
{

class SignerRuleHelper : public EntryHelper
{
public:
    virtual bool
    exists(uint64_t const ruleID) = 0;

    virtual SignerRuleFrame::pointer
    loadSignerRule(uint64_t const ruleID) = 0;

    virtual std::vector<SignerRuleFrame::pointer>
    loadSignerRules(std::vector<uint64_t> const ruleIDs) = 0;

    virtual std::vector<uint64_t>
    loadDefaultRuleIDs() = 0;
};
}