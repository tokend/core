// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "bucket/Bucket.h"
#include "bucket/BucketApplicator.h"
#include "ledger/LedgerDeltaImpl.h"
#include "ledger/LedgerTxn.h"
#include "ledger/LedgerTxnEntry.h"
#include "main/Application.h"

namespace stellar
{

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
    LedgerTxn ltx(mApp.getLedgerTxnRoot(), false);
    for (; mBucketIter; ++mBucketIter)
    {
        BucketEntry const& e = *mBucketIter;
        if (e.type() == LIVEENTRY)
        {
            ltx.createOrUpdateWithoutLoading(e.liveEntry());
        }
        else
        {
            ltx.eraseWithoutLoading(e.deadEntry());
        }

        if ((++count > LEDGER_ENTRY_BATCH_COMMIT_SIZE))
        {
            break;
        }
    }
    ltx.commit();

    mCount += count;
    return count;
}
}
