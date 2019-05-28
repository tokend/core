#pragma once

// Copyright 2016 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "crypto/SecretKey.h"
#include "transactions/TransactionFrame.h"
#include "xdr/Tokend-ledger-entries.h"
#include "xdr/Tokend-transaction.h"

namespace stellar
{

class Application;

namespace txtest
{
struct SetOptionsArguments;
}

class TestAccount
{
  public:
    static TestAccount createRoot(Application& app);

    explicit TestAccount(Application& app, SecretKey sk, int64_t sn = 0)
        : mApp(app), mSk{std::move(sk)}, mSn{sn}
    {
        mAccountID = PubKeyUtils::toStrKey(mSk.getPublicKey());
    }

    TransactionFramePtr tx(std::vector<Operation> const& ops,
                           int64_t sn = 0);
    Operation op(Operation operation);

    TestAccount create(SecretKey const& secretKey, uint64_t initialBalance);
    TestAccount create(std::string const& name, uint64_t initialBalance);
    void merge(PublicKey const& into);
    void inflation();

    void setOptions(txtest::SetOptionsArguments const& arguments);

    void manageData(std::string const& name, DataValue* value);

    void bumpSequence(int64_t to);

    void pay(PublicKey const& destination, int64_t amount);

    operator SecretKey() const
    {
        return getSecretKey();
    }
    operator PublicKey() const
    {
        return getPublicKey();
    }

    const SecretKey&
    getSecretKey() const
    {
        return mSk;
    }
    PublicKey
    getPublicKey() const
    {
        return mSk.getPublicKey();
    }

    void
    setSequenceNumber(int64_t sn)
    {
        mSn = sn;
    }

    int64_t
    getLastSequenceNumber()
    {
        //updateSequenceNumber();
        return mSn;
    }

    int64_t
    nextSequenceNumber()
    {
        updateSequenceNumber();
        return ++mSn;
    }
    int64_t loadSequenceNumber();

    std::string
    getAccountId()
    {
        return mAccountID;
    }

    int64_t getBalance() const;

    bool exists() const;

  private:
    Application& mApp;
    SecretKey mSk;
    std::string mAccountID;
    int64_t mSn;

    void updateSequenceNumber();
};
}
