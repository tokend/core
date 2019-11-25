#include "AccountKYCHelper.h"
#include "StorageHelper.h"

namespace soci
{
    class session;
}

namespace stellar
{

class StatementContext;

class AccountKYCHelperImpl : public AccountKYCHelper
{
public:
    explicit AccountKYCHelperImpl(StorageHelper &storageHelper);

    AccountKYCHelperImpl(AccountKYCHelperImpl const&) = delete;

    AccountKYCHelperImpl& operator=(AccountKYCHelperImpl const&) = delete;

    void dropAll() override;
    void storeAdd(LedgerEntry const& entry) override;
    void storeChange(LedgerEntry const& entry) override;
    void storeDelete(LedgerKey const& key) override;
    bool exists(LedgerKey const& key) override;
    LedgerKey getLedgerKey(LedgerEntry const& from) override;
    EntryFrame::pointer storeLoad(LedgerKey const& ledgerKey) override;
    EntryFrame::pointer fromXDR(LedgerEntry const& from) override;
    uint64_t countObjects() override;
    Database& getDatabase() override;
    LedgerDelta* getLedgerDelta() override;

private:
    StorageHelper& mStorageHelper;
    const char* mAccountKYCHColumnSelector;

    void storeUpdate(const LedgerEntry &entry, bool insert) override;
    AccountKYCFrame::pointer loadAccountKYC(const AccountID &accountID) override;
};

}