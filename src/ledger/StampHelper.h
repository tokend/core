// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0
#pragma once

#include "ledger/LedgerManager.h"
#include "ledger/EntryHelper.h"
#include "ledger/StorageHelper.h"
#include "StampFrame.h"


namespace stellar
{
    class StatementContext;


    class StampHelper : EntryHelper {

        StorageHelper& mStorageHelper;

    public:
        StampHelper(StorageHelper& storageHelper);
        static void clearAll(Database& db);
        static void dropAll(Database& db);
        uint64_t countObjects() override;
        bool exists(LedgerKey const &key) override;
        bool exists(Hash ledgerHash, Hash licenseHash);
        LedgerKey getLedgerKey(LedgerEntry const &from) override;
        EntryFrame::pointer fromXDR(LedgerEntry const &from) override;
        Database &getDatabase() override;
        void storeAdd(LedgerEntry const &entry) override;

    private:
        virtual void storeDelete(LedgerKey const &key);

        virtual void dropAll();

        virtual void storeChange(LedgerEntry const &entry);

        virtual EntryFrame::pointer storeLoad(LedgerKey const &ledgerKey);
    };
}