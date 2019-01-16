#include "AccountRoleRulesHelper.h"
#include "database/Database.h"
#include "StorageHelper.h"
#include "util/Logging.h"

using namespace soci;

namespace stellar
{

AccountRoleRulesHelper::AccountRoleRulesHelper(StorageHelper& storageHelper)
        : mDatabase(storageHelper.getDatabase())
{
}

void
AccountRoleRulesHelper::dropAll()
{
    mDatabase.getSession() << "DROP TABLE IF EXISTS account_role_rules;";
    mDatabase.getSession() << "CREATE TABLE account_role_rules"
                       "("
                       "role_id BIGINT NOT NULL CHECK (role_id > 0),"
                       "rule_id BIGINT NOT NULL CHECK (rule_id > 0),"
                       "PRIMARY KEY (role_id, rule_id)"
                       ");";
}

void
AccountRoleRulesHelper::storeDelete(const uint64_t roleID)
{
    auto prep = mDatabase.getPreparedStatement(
            "DELETE FROM account_role_rules WHERE role_id=:id");
    auto& st = prep.statement();
    st.exchange(use(roleID));
    st.define_and_bind();
    st.execute(true);
}

void
AccountRoleRulesHelper::storeUpdate(uint64_t const roleID,
                                    std::vector<uint64_t> const ruleIDs,
                                    const bool insert)
{
    if (!insert)
    {
        storeDelete(roleID);
    }

    if (ruleIDs.empty())
    {
        return;
    }

    storeAdd(roleID, ruleIDs);
}

void
AccountRoleRulesHelper::storeAdd(uint64_t const roleID,
                                 std::vector<uint64_t> const ruleIDs)
{
    std::string sql = "INSERT INTO account_role_rules (role_id, rule_id) "
                      "VALUES " + craftRowsValues(roleID, ruleIDs);


    auto prep = mDatabase.getPreparedStatement(sql);
    auto& st = prep.statement();
    st.execute(false);

    if (st.get_affected_rows() != ruleIDs.size())
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER) << "Failed to insert into account_role_rules with role id: "
                                           << std::to_string(roleID);
        throw std::runtime_error("Failed to insert into account_role_rules with role id");
    }
}

std::string
AccountRoleRulesHelper::craftRowsValues(uint64_t const roleID,
                                        const std::vector<uint64_t> ruleIDs)
{
    if (ruleIDs.empty())
    {
        throw std::runtime_error("Expected rule ids not be empty");
    }

    std::string result = "";

    for (auto const ruleID : ruleIDs)
    {
        result += "(" + std::to_string(roleID) + ", " + std::to_string(ruleID) + "), ";
    }

    return result.substr(0, result.size() - 2);
}

void
AccountRoleRulesHelper::load(StatementContext& prep,
                             const std::function<void(uint64_t const&)> processor)
{
    uint64_t ruleID;

    statement& st = prep.statement();
    st.exchange(into(ruleID));
    st.define_and_bind();
    st.execute(true);

    while (st.got_data())
    {
        processor(ruleID);
        st.fetch();
    }
}

std::vector<uint64_t>
AccountRoleRulesHelper::loadRuleIDs(uint64_t const roleID)
{
    auto prep = mDatabase.getPreparedStatement(
            "SELECT rule_id FROM account_role_rules WHERE role_id = :id");
    auto& st = prep.statement();
    st.exchange(use(roleID, "id"));

    std::vector<uint64_t> result;
    auto timer = mDatabase.getSelectTimer("select_rule_ids");
    load(prep, [&result](uint64_t const& ruleID)
    {
        result.emplace_back(ruleID);
    });

    return result;
}

bool
AccountRoleRulesHelper::isRuleUsed(uint64_t const ruleID)
{
    int exists = 0;
    auto timer = mDatabase.getSelectTimer("account-rule-used");
    auto prep = mDatabase.getPreparedStatement(
            "SELECT EXISTS (SELECT NULL FROM account_role_rules WHERE "
            "rule_id = :id)");
    auto& st = prep.statement();
    st.exchange(use(ruleID, "id"));
    st.exchange(into(exists));
    st.define_and_bind();
    st.execute(true);

    return exists != 0;
}

}
