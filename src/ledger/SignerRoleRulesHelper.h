#pragma once

#include <string>
#include <vector>
#include <functional>

namespace soci
{
    class session;
}

namespace stellar
{
class Database;
class LedgerDelta;
class StorageHelper;
class StatementContext;

class SignerRoleRulesHelper
{
public:
    SignerRoleRulesHelper(StorageHelper& storageHelper);

    void
    dropAll();

    void
    storeUpdate(uint64_t const roleID, std::vector<uint64_t> const ruleIDs,
                const bool insert);

    std::vector<uint64_t> loadRuleIDs(uint64_t const roleID);

    void
    storeDelete(uint64_t const roleID);

    std::vector<uint64_t>
    loadRolesByRule(uint64_t const ruleID);
private:

    void
    storeAdd(uint64_t const roleID,  std::vector<uint64_t> const ruleIDs);

    std::string
    craftRowsValues(uint64_t const roleID,  std::vector<uint64_t> const ruleIDs);

    void
    load(StatementContext& prep, const std::function<void(uint64_t const&)> processor);

    Database& mDatabase;
};

} // namespace stellar
