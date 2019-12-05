#include "ReferenceHelper.h"
#include <functional>
#include <unordered_map>
#include "AccountLimitsFrame.h"
#include "AccountFrame.h"
#include "BalanceFrame.h"
#include "StorageHelper.h"

namespace soci
{
    class session;
}

namespace stellar
{
class StatementContext;


class ReferenceHelperImpl : public ReferenceHelper, NonCopyable
{
public:
    explicit ReferenceHelperImpl(StorageHelper &storageHelper);


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
    void addVersion() override ;
private:
    StorageHelper& mStorageHelper;
    const char* mReferenceColumnSelector;
    ReferenceFrame::pointer loadReference(AccountID exchange, std::string reference) override;
    void storeUpdateHelper(bool insert, const LedgerEntry& entry);
    void loadReferences(StatementContext &prep, std::function<void(LedgerEntry const &)> referenceProcessor);
    bool exists(std::string reference, AccountID exchange) override;
};

}