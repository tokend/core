#pragma once

#include "ContractHelper.h"
#include "StorageHelper.h"

namespace soci
{
    class session;
}

namespace stellar
{
class StatementContext;

class ContractHelperImpl : public ContractHelper
{
public:
    explicit ContractHelperImpl(StorageHelper &storageHelper);
    ContractHelperImpl(ContractHelperImpl const&) = delete;
    ContractHelperImpl& operator=(ContractHelperImpl const&) = delete;

    void addCustomerDetails() override;
    void dropAll() override;
    void storeAdd(LedgerEntry const& entry) override;
    void storeChange(LedgerEntry const& entry) override;
    void storeDelete(LedgerKey const& key) override;
    bool exists(LedgerKey const& from) override;
    LedgerKey getLedgerKey(LedgerEntry const& from) override;
    EntryFrame::pointer storeLoad(LedgerKey const& key) override;
    EntryFrame::pointer fromXDR(LedgerEntry const& from) override;
    uint64_t countObjects() override;
    ContractFrame::pointer loadContract(uint64_t id) override;
    uint64_t countContracts(AccountID const& contractor) override;
    virtual Database& getDatabase() override;
    virtual LedgerDelta* getLedgerDelta() override;

private:
    StorageHelper& mStorageHelper;
    const char* mContractColumnSelector;

    void load(StatementContext & prep, std::function<void(LedgerEntry const&)> processor) override;
    void storeUpdateHelper(bool insert, LedgerEntry const& entry) override;
};

}