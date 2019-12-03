#include "AtomicSwapAskHelper.h"
#include "StorageHelper.h"

namespace soci
{
    class session;
}

namespace stellar
{

class StatementContext;

class AtomicSwapAskHelperImpl : public AtomicSwapAskHelper
{
public:
    explicit AtomicSwapAskHelperImpl(StorageHelper &storageHelper);

    AtomicSwapAskHelperImpl(AtomicSwapAskHelperImpl const&) = delete;

    AtomicSwapAskHelperImpl& operator=(AtomicSwapAskHelperImpl const&) = delete;

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

    AtomicSwapAskFrame::pointer
    loadAtomicSwapAsk(AccountID const& ownerID, uint64_t bidID) override;

    AtomicSwapAskFrame::pointer
    loadAtomicSwapAsk(uint64_t bidID) override;

    std::unordered_map<AccountID, std::vector<AtomicSwapAskFrame::pointer>>
    loadAllAtomicSwapAsks() override;

    bool
    existForAsset(const AssetCode& code) override;

private:
    StorageHelper& mStorageHelper;
    const char* mAtomicSwapColumnSelector;

    void storeUpdateHelper(bool insert, LedgerEntry const& entry);

    void loadAtomicSwapAsks(StatementContext& prep,std::function<void(LedgerEntry const&)>
                                    atomicSwapBidProcessor);
};

}
