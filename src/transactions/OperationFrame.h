#pragma once

// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <memory>
#include "transactions/AccountManager.h"
#include "ledger/LedgerManager.h"
#include "ledger/AccountFrame.h"
#include "ledger/AssetFrame.h"
#include "ledger/BalanceFrame.h"
#include "overlay/StellarXDR.h"
#include "util/types.h"
#include "ledger/FeeFrame.h"

namespace medida
{
class MetricsRegistry;
}

namespace stellar
{
class Application;
class LedgerManager;
class LedgerDelta;
class StorageHelper;
class KeyValueHelper;
class AccountRuleVerifier;

class TransactionFrame;

struct OperationCondition
{
    AccountRuleResource resource;
    AccountRuleAction action;
    AccountFrame::pointer account;

    OperationCondition(AccountRuleResource res, AccountRuleAction act, AccountFrame::pointer acc)
            : resource(res), action(act), account(acc)
    {
    }
};

struct SignerRequirement
{
    SignerRuleResource resource;
    SignerRuleAction action;

    SignerRequirement(SignerRuleResource res, SignerRuleAction act)
            : resource(res), action(act)
    {
    }
};

class OperationFrame
{
private:
	bool checkRolePermissions(StorageHelper& storageHelper, AccountRuleVerifier& accountRuleVerifier);

	bool canBeApplied(Application& app, StorageHelper& storageHelper);
    bool checkAdminCount(Application& app, StorageHelper& storageHelper);
    bool checkOp(Application& app, StorageHelper& storageHelper);

protected:

    Operation const& mOperation;
    TransactionFrame& mParentTx;
    AccountFrame::pointer mSourceAccount;
    OperationResult& mResult;

	// checks signature, if not valid - returns false and sets operation error code;
    bool doCheckSignature(Application& app, StorageHelper& storageHelper);

    virtual bool doCheckValid(Application& app) = 0;
    virtual bool doApply(Application& app, LedgerDelta& delta,
                         LedgerManager& ledgerManager);
    virtual bool doApply(Application& app, StorageHelper& storageHelper,
                         LedgerManager& ledgerManager);

  public:
    virtual ~OperationFrame() = default;

    virtual bool
    tryGetOperationConditions(StorageHelper &storageHelper,
                              std::vector<OperationCondition> &result) const = 0;

    virtual bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const = 0;

	// returns true if operation is allowed in the system
	virtual bool isSupported() const;

	// returns fee paid for operation.
	// default fee for all operations is 0, finantial operations must override this function
    virtual int64_t getPaidFee() const;

    virtual bool loadTasks(StorageHelper &storageHelper, uint32_t &allTasks, xdr::pointer<uint32> tasks);

    virtual std::vector<longstring> makeTasksKeyVector(StorageHelper &storageHelper);

    static std::shared_ptr<OperationFrame>
    makeHelper(Operation const& op, OperationResult& res,
               TransactionFrame& parentTx);

    OperationFrame(Operation const& op, OperationResult& res,
                   TransactionFrame& parentTx);
    OperationFrame(OperationFrame const&) = delete;

    AccountFrame&
    getSourceAccount() const
    {
        assert(mSourceAccount);
        return *mSourceAccount;
    }

    // overrides internal sourceAccount used by this operation
    // normally set automatically by checkValid
    void
    setSourceAccountPtr(AccountFrame::pointer sa)
    {
        mSourceAccount = sa;
    }
    
    AccountID const& getSourceID() const;

    // load account if needed
    // returns true on success
    bool loadAccount(LedgerDelta* delta, Database& db);

    void
    createReferenceEntry(std::string reference, AccountID sender, StorageHelper& storageHelper);

    OperationResult&
    getResult() const
    {
        return mResult;
    }
    OperationResultCode getResultCode() const;

    bool checkValid(Application& app, AccountRuleVerifier& accountRuleVerifier,
                    LedgerDelta* delta = nullptr);

    bool apply(StorageHelper& storageHelper, Application& app);

    Operation const&
    getOperation() const
    {
        return mOperation;
    }

	virtual std::string getInnerResultCodeAsStr();
};
}
