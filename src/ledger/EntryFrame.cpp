// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ledger/EntryFrame.h"
#include "ledger/LedgerDelta.h"
#include "xdrpp/printer.h"
#include "xdrpp/marshal.h"

namespace stellar {
    using xdr::operator==;

	EntryFrame::EntryFrame(LedgerEntryType type) : mKeyCalculated(false) {
		mEntry.data.type(type);
	}

	EntryFrame::EntryFrame(LedgerEntry const &from)
		: mKeyCalculated(false), mEntry(from) {
	}

	LedgerKey const &
		EntryFrame::getKey() const {
		if (!mKeyCalculated) {
			mKey = LedgerEntryKey(mEntry);
			mKeyCalculated = true;
		}
		return mKey;
	}

    uint32
    EntryFrame::getLastModified() const {
        return mEntry.lastModifiedLedgerSeq;
    }

    uint32 &
    EntryFrame::getLastModified() {
        return mEntry.lastModifiedLedgerSeq;
    }

    void
    EntryFrame::touch(uint32 ledgerSeq) {
        assert(ledgerSeq != 0);
        getLastModified() = ledgerSeq;
    }

    void
    EntryFrame::touch(LedgerDelta const &delta) {
        uint32 ledgerSeq = delta.getHeader().ledgerSeq;
        if (delta.updateLastModified()) {
            touch(ledgerSeq);
        }
    }

}
