#pragma once

#include "SignerHelper.h"
#include "util/NonCopyable.h"
#include "SignerFrame.h"

namespace stellar
{
class StorageHelper;

class SignerHelperImpl : public SignerHelper, NonCopyable
{
public:
    SignerHelperImpl(StorageHelper& storageHelper);

private:
    void
    dropAll() override;

    Database&
    getDatabase();

    void
    storeAdd(LedgerEntry const& entry) override;

    void
    storeChange(LedgerEntry const& entry) override;

    void
    storeDelete(LedgerKey const& key) override;


    void
    storeUpdate(LedgerEntry const& entry, bool insert);

    std::vector<SignerFrame::pointer>
    loadAccountSigners(AccountID const& accountID);

    void
    load(StatementContext& prep, std::function<void(LedgerEntry const&)> processor);

    StorageHelper& mStorageHelper;
    const char* mSignerColumnSelector;

};
}
