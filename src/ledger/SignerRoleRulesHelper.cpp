#include "SignerRoleRulesHelper.h"
#include "database/Database.h"
#include "StorageHelper.h"
#include "util/Logging.h"

using namespace soci;

namespace stellar
{

SignerRoleRulesHelper::SignerRoleRulesHelper(StorageHelper& storageHelper)
        : mDatabase(storageHelper.getDatabase())
{
}

void
SignerRoleRulesHelper::dropAll()
{
    mDatabase.getSession() << "DROP TABLE IF EXISTS signer_role_rules;";
    mDatabase.getSession() << "CREATE TABLE signer_role_rules"
                       "("
                       "role_id BIGINT NOT NULL, "
                       "rule_id BIGINT NOT NULL, "
                       "PRIMARY KEY (role_id, rule_id)"
                       ");";
}

void
SignerRoleRulesHelper::storeDelete(const uint64_t roleID)
{
    auto prep = mDatabase.getPreparedStatement(
            "DELETE FROM signer_role_rules WHERE role_id=:id");
    auto& st = prep.statement();
    st.exchange(use(roleID));
    st.define_and_bind();
    st.execute(true);
}

void
SignerRoleRulesHelper::storeUpdate(uint64_t const roleID,
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
SignerRoleRulesHelper::storeAdd(uint64_t const roleID,
                                 std::vector<uint64_t> const ruleIDs)
{
    std::string sql = "INSERT INTO signer_role_rules (role_id, rule_id) "
                      "VALUES " + craftRowsValues(roleID, ruleIDs);


    auto prep = mDatabase.getPreparedStatement(sql);
    auto& st = prep.statement();
    st.execute(false);

    if (st.get_affected_rows() != ruleIDs.size())
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER) << "Failed to insert into signer_role_rules with role id: "
                                           << std::to_string(roleID);
        throw std::runtime_error("Failed to insert into signer_role_rules");
    }
}

std::string
SignerRoleRulesHelper::craftRowsValues(uint64_t const roleID,
                                        const std::vector<uint64_t> ruleIDs)
{
    if (ruleIDs.empty())
    {
        throw std::runtime_error("Expected signer rule ids not be empty");
    }

    std::stringstream ss;

    for (auto const ruleID : ruleIDs)
    {
        ss << "(" << roleID << ", " << ruleID << ")" << ", ";
    }

    auto result = ss.str();

    return result.erase(result.size()-2);
}

void
SignerRoleRulesHelper::load(StatementContext& prep,
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
SignerRoleRulesHelper::loadRuleIDs(uint64_t const roleID)
{
    auto prep = mDatabase.getPreparedStatement(
            "SELECT rule_id FROM signer_role_rules WHERE role_id = :id");
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

std::vector<uint64_t>
SignerRoleRulesHelper::loadRolesByRule(uint64_t const ruleID)
{
    auto prep = mDatabase.getPreparedStatement(
            "SELECT role_id FROM signer_role_rules WHERE rule_id = :id");
    auto& st = prep.statement();
    st.exchange(use(ruleID, "id"));

    std::vector<uint64_t> result;
    auto timer = mDatabase.getSelectTimer("select_role_ids");
    load(prep, [&result](uint64_t const& ruleID)
    {
        result.emplace_back(ruleID);
    });

    return result;
}

}
