#include <xdrpp/marshal.h>
#include "ledger/EntryHelper.h"
#include "database/Database.h"

namespace stellar
{

void
EntryHelper::flushCachedEntry(LedgerKey const& key)
{
    auto s = binToHex(xdr::xdr_to_opaque(key));
    getDatabase().getEntryCache().erase_if_exists(s);
}

bool
EntryHelper::cachedEntryExists(LedgerKey const& key)
{
    auto s = binToHex(xdr::xdr_to_opaque(key));
    return getDatabase().getEntryCache().exists(s);
}

std::shared_ptr<LedgerEntry const>
EntryHelper::getCachedEntry(LedgerKey const& key)
{
    auto s = binToHex(xdr::xdr_to_opaque(key));
    return getDatabase().getEntryCache().get(s);
}

void
EntryHelper::putCachedEntry(LedgerKey const& key,
                            std::shared_ptr<LedgerEntry const> p)
{
    if (getLedgerDelta() == nullptr)
    {
        return;
    }

    auto s = binToHex(xdr::xdr_to_opaque(key));
    getDatabase().getEntryCache().put(s, p);
}

std::string
EntryHelper::obtainSqlIDsString(std::vector<uint64_t> ids)
{
    if (ids.empty())
    {
        return "";
    }

    std::string result;
    for (auto id : ids)
    {
        result += std::to_string(id);
        result += ", ";
    }

    return result.substr(0, result.size() - 2);
}

} // namespace stellar