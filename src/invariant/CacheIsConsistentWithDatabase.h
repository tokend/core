// Copyright 2017 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#pragma once

#ifndef STELLAR_CACHEISCONSISTENTWITHDATABASE_H
#define STELLAR_CACHEISCONSISTENTWITHDATABASE_H

#include "invariant/Invariant.h"

namespace stellar {

    class Database;

    class LedgerDelta;

    class LedgerEntry;

    class LedgerKey;

    class CacheIsConsistentWithDatabase : public Invariant {
    public:
        explicit CacheIsConsistentWithDatabase(Database &db);

        virtual ~CacheIsConsistentWithDatabase() override;

        virtual std::string getName() const override;

        virtual std::string check(LedgerDelta const &delta) const override;

        std::string
        checkAgainstDatabase(LedgerEntry const& entry) const override;

    private:
        Database &mDb;
    };
}

#endif //STELLAR_CACHEISCONSISTENTWITHDATABASE_H
