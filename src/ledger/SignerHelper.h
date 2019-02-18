#pragma once

#include "EntryHelper.h"
#include "SignerFrame.h"

namespace stellar
{

class SignerHelper : public EntryHelper
{
public:
    using EntryHelper::exists;

    virtual SignerFrame::pointer
    loadSigner(PublicKey const& publicKey, AccountID const& accountID) = 0;

    virtual std::vector<SignerFrame::pointer>
    loadSigners(AccountID const& accountID) = 0;

    virtual bool
    isRoleIDUsed(uint64_t roleID) = 0;

    virtual bool
    exists(PublicKey const& publicKey, AccountID const& accountID) = 0;
};
}