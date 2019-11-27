#include "ledger/EntryHelper.h"
#include "ledger/LedgerManager.h"
#include <functional>
#include <unordered_map>
#include "ReferenceFrame.h"

namespace soci {
    class session;
}

namespace stellar {
class StatementContext;

class ReferenceHelper : public EntryHelper {
public:

    virtual ReferenceFrame::pointer
    loadReference(AccountID exchange, std::string reference) = 0;
    virtual bool exists(LedgerKey const &key) = 0;
    virtual bool exists(std::string reference, AccountID exchange) = 0;
    virtual void addVersion() = 0;
private:
    virtual void storeUpdateHelper(bool insert, const LedgerEntry& entry) = 0;
    virtual void loadReferences(StatementContext &prep, std::function<void(LedgerEntry const &)> referenceProcessor) = 0;
};
}