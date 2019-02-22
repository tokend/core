// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0
#pragma once

#include "ledger/LedgerManager.h"
#include "ledger/StampHelper.h"
#include "ledger/StorageHelper.h"
#include "StampFrame.h"
#include "database/Database.h"


namespace stellar
{
    class StatementContext;


    class StampHelperImpl : public StampHelper, NonCopyable{

        StorageHelper& mStorageHelper;

    public:
        explicit StampHelperImpl(StorageHelper& storageHelper);
    private:
        void clearAll() override;
        void dropAll() override;
        uint64_t countObjects() override;
        bool exists(LedgerKey const &key) override;
        bool exists(Hash ledgerHash, Hash licenseHash) override;
        LedgerKey getLedgerKey(LedgerEntry const &from) override;
        EntryFrame::pointer fromXDR(LedgerEntry const &from) override;
        Database &getDatabase() override;
        void storeAdd(LedgerEntry const &entry) override;
        void storeChange(LedgerEntry const& entry) override;
        void storeLoad(LedgerEntry const& entry) override;
        void storeDelete(LedgerEntry const& entry) override;
        virtual void storeDelete(LedgerKey const& key);
        virtual EntryFrame::pointer storeLoad(LedgerKey const& ledgerKey);
    };
}
