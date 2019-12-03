#include "ledger/ExternalSystemAccountID.h"
#include "xdrpp/printer.h"

namespace stellar
{
using xdr::operator<;

ExternalSystemAccountIDFrame::
ExternalSystemAccountIDFrame() : EntryFrame(LedgerEntryType::
                                            EXTERNAL_SYSTEM_ACCOUNT_ID)
                               , mExternalSystemAccountID(mEntry.data.
                                                                 externalSystemAccountID())
{
}

ExternalSystemAccountIDFrame::ExternalSystemAccountIDFrame(
    LedgerEntry const& from)
    : EntryFrame(from)
    , mExternalSystemAccountID(mEntry.data.externalSystemAccountID())
{
}

ExternalSystemAccountIDFrame::ExternalSystemAccountIDFrame(
    ExternalSystemAccountIDFrame const&
    from) : ExternalSystemAccountIDFrame(from.mEntry)
{
}

ExternalSystemAccountIDFrame& ExternalSystemAccountIDFrame::operator=(
    ExternalSystemAccountIDFrame const& other)
{
    if (&other != this)
    {
        mExternalSystemAccountID = other.mExternalSystemAccountID;
        mKey = other.mKey;
        mKeyCalculated = other.mKeyCalculated;
    }
    return *this;
}

ExternalSystemAccountIDFrame::pointer ExternalSystemAccountIDFrame::createNew(
    AccountID const accountID, int32 const externalSystemType,
    std::string const data)
{
    LedgerEntry le;
    le.data.type(LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID);
    auto& externalSystemAccountID = le.data.externalSystemAccountID();
    externalSystemAccountID.accountID = accountID;
    externalSystemAccountID.externalSystemType = externalSystemType;
    externalSystemAccountID.data = data;
    return std::make_shared<ExternalSystemAccountIDFrame>(le);
}

bool ExternalSystemAccountIDFrame::isValid(ExternalSystemAccountID const& oe)
{
    return !oe.data.empty();
}

bool ExternalSystemAccountIDFrame::isValid() const
{
    return isValid(mExternalSystemAccountID);
}

LedgerKey const &
ExternalSystemAccountIDFrame::getKey() const
{
    if (!mKeyCalculated) {
        mKey = LedgerKey(LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID);
        mKey.externalSystemAccountID().accountID = mExternalSystemAccountID.accountID;
        mKey.externalSystemAccountID().externalSystemType = mExternalSystemAccountID.externalSystemType;
        mKeyCalculated = true;
    }
    return mKey;
}

}