#pragma once

namespace stellar
{

class MockAccountHelper : public AccountHelper
{
public:
    MOCK_METHOD1(loadAccount,
            AccountFrame::pointer(AccountID const& accountID));
};

}  // namespace stellar

