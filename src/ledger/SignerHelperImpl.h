#pragma once

#include "SignerHelper.h"
#include "util/NonCopyable.h"

namespace stellar
{
class StorageHelper;
class StatementContext;

class SignerHelperImpl : public SignerHelper, NonCopyable
{
public:
    SignerHelperImpl(StorageHelper& storageHelper);

private:
    void
    dropAll() override;

    Database&
    getDatabase() override;

    LedgerDelta*
    getLedgerDelta() override;

    std::string const
    getTableName() const override;

    void
    storeAdd(LedgerEntry const& entry) override;

    void
    storeChange(LedgerEntry const& entry) override;

    void
    storeDelete(LedgerKey const& key) override;

    bool
    exists(LedgerKey const& key) override;

    LedgerKey
    getLedgerKey(LedgerEntry const& key) override;

    EntryFrame::pointer
    fromXDR(LedgerEntry const& entry) override;

    EntryFrame::pointer
    storeLoad(LedgerKey const& key) override;

    uint64_t
    countObjects() override;

    std::vector<SignerFrame::pointer>
    loadSigners(AccountID const& accountID);

    SignerFrame::pointer
    loadSigner(PublicKey const& publicKey,  AccountID const& accountID);

    bool
    exists(PublicKey const &rawPubKey, AccountID const& accountID);

    bool
    isRoleIDUsed(uint64_t roleID);

    void
    storeUpdate(LedgerEntry const& entry, bool insert);

    void
    load(StatementContext& prep, std::function<void(LedgerEntry const&)> processor);

    StorageHelper& mStorageHelper;
    const char* mSignerColumnSelector;

};
}
