// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "bucket/Bucket.h"
#include "bucket/BucketApplicator.h"
#include "ledger/LedgerDeltaImpl.h"
#include "main/Application.h"
#include "ledger/StorageHelperImpl.h"
#include "ledger/EntryFrame.h"

namespace stellar
{

static const size_t LEDGER_ENTRY_BATCH_COMMIT_SIZE = 0xfff;

BucketApplicator::BucketApplicator(Application& app,
                                   std::shared_ptr<const Bucket> bucket)
    : mApp(app), mBucketIter(bucket)
{
}

BucketApplicator::operator bool() const
{
    return (bool)mBucketIter;
}

size_t
BucketApplicator::pos()
{
    return mBucketIter.pos();
}

size_t
BucketApplicator::size() const
{
    return mBucketIter.size();
}

size_t
BucketApplicator::advance()
{
    size_t count = 0;
    Database& db = mApp.getDatabase();
    soci::transaction sqlTx(db.getSession());

    for (; mBucketIter; ++mBucketIter)
    {
        LedgerHeader lh;
        LedgerDeltaImpl delta(lh, db, false);
        StorageHelperImpl storageHelperImpl(db, &delta);
        StorageHelper& storageHelper = storageHelperImpl;
        BucketEntry const& e = *mBucketIter;
        if (e.type() == BucketEntryType::LIVEENTRY)
        {
            auto key = storageHelper.getHelper(e.liveEntry().data.type())->getLedgerKey(e.liveEntry());
            if(storageHelper.getHelper(key.type())->exists(key))
            {
                storageHelper.getHelper(e.liveEntry().data.type())->storeChange(e.liveEntry());
            }
            else
            {
                storageHelper.getHelper(e.liveEntry().data.type())->storeAdd(e.liveEntry());
            }

        }
        else
        {
            storageHelper.getHelper(e.deadEntry().type())->storeDelete(e.deadEntry());
        }

        // No-op, just to avoid needless rollback.
        static_cast<LedgerDelta&>(delta).commit();
        if ((++count > LEDGER_ENTRY_BATCH_COMMIT_SIZE))
        {
            break;
        }
    }
    sqlTx.commit();
    db.clearPreparedStatementCache();

    mCount += count;

    if (!mBucketIter || (mCount & LEDGER_ENTRY_BATCH_COMMIT_SIZE) == LEDGER_ENTRY_BATCH_COMMIT_SIZE)
    {
        CLOG(INFO, "Bucket") << "Bucket-apply: committed " << mCount << " entries";
    }

    return count;
}
}
