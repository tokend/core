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
class StampHelper : public EntryHelper {

public:
    bool exists(LedgerKey const &key) override = 0;
    virtual bool exists(Hash ledgerHash, Hash licenseHash) = 0;
    virtual void storeLoad(LedgerEntry const& entry) = 0;
    virtual void storeDelete(LedgerEntry const& entry) = 0;
};
}
