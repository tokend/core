#include "ledger/EntryHelper.h"
#include "ledger/LedgerManager.h"
#include <functional>
#include <unordered_map>
#include "FeeFrame.h"

namespace soci
{
class session;
}

namespace stellar {
class StatementContext;

class FeeHelper : public EntryHelper
{
public:

    virtual FeeFrame::pointer
    loadFee(FeeType feeType, AssetCode asset, AccountID *accountID,
                              uint64_t* accountType, int64_t subtype, int64_t lowerBound,
                              int64_t upperBound) = 0;

    virtual FeeFrame::pointer
    loadFee(Hash hash, int64_t lowerBound, int64_t upperBound) = 0;

    virtual FeeFrame::pointer
    loadForAccount(FeeType feeType, AssetCode asset, int64_t subtype,
                                     AccountFrame::pointer accountFrame, int64_t amount) = 0;

    virtual std::vector<FeeFrame::pointer> loadFees(Hash hash) = 0;

    virtual void storeUpdateHelper(bool insert, LedgerEntry const &entry) = 0;

    virtual void loadFees(StatementContext &prep, std::function<void(LedgerEntry const &)> feeProcessor) = 0;

    virtual void checkAmounts(const FeeFrame::pointer &frame) const = 0;

    virtual bool isBoundariesOverlap(Hash hash, int64_t lowerBound, int64_t upperBound) = 0;

    virtual  bool exists(Hash hash, int64_t lowerBound, int64_t upperBound) = 0;
};
}