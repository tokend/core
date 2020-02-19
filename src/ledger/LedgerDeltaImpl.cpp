// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ledger/LedgerDeltaImpl.h"
#include "LedgerDeltaImpl.h"
#include "ledger/EntryHelper.h"
#include "ledger/KeyValueEntryFrame.h"
#include "ledger/StorageHelperImpl.h"
#include "main/Application.h"
#include "main/Config.h"
#include "medida/meter.h"
#include "medida/metrics_registry.h"
#include "xdr/ledger.h"
#include "xdrpp/printer.h"

namespace stellar {
    using xdr::operator==;

LedgerDeltaImpl::LedgerDeltaImpl(LedgerDelta &outerDelta)
        : mOuterDelta(&outerDelta), mHeader(&outerDelta.getHeader()), mCurrentHeader(outerDelta.getHeader()),
          mPreviousHeaderValue(outerDelta.getHeader()), mDb(outerDelta.getDatabase()),
          mUpdateLastModified(outerDelta.updateLastModified()) {
}

LedgerDeltaImpl::LedgerDeltaImpl(LedgerDeltaImpl &outerDelta)
        : mOuterDelta(&outerDelta), mHeader(&outerDelta.getHeader()), mCurrentHeader(outerDelta.getHeader()),
          mPreviousHeaderValue(outerDelta.getHeader()), mDb(outerDelta.getDatabase()),
          mUpdateLastModified(outerDelta.updateLastModified()) {
}

LedgerDeltaImpl::LedgerDeltaImpl(LedgerHeader &header, Database &db,
                                 bool updateLastModified)
        : mOuterDelta(nullptr), mHeader(&header), mCurrentHeader(header), mPreviousHeaderValue(header), mDb(db),
          mUpdateLastModified(updateLastModified) {
}

LedgerDeltaImpl::~LedgerDeltaImpl() {
    if (mHeader) {
        rollback();
    }
}

LedgerHeader &
LedgerDeltaImpl::getHeader() {
    return mCurrentHeader.getHeader();
}

LedgerHeader const &
LedgerDeltaImpl::getHeader() const {
    return mCurrentHeader.getHeader();
}

LedgerHeaderFrame &
LedgerDeltaImpl::getHeaderFrame() {
    return mCurrentHeader;
}

void
LedgerDeltaImpl::checkState() {
    if (mHeader == nullptr) {
        throw std::runtime_error(
                "Invalid operation: delta is already committed");
    }
}

void
LedgerDeltaImpl::addEntry(EntryFrame const &entry) {
    addEntry(entry.copy());
}

void
LedgerDeltaImpl::deleteEntry(EntryFrame const &entry) {
    deleteEntry(entry.copy());
}

void
LedgerDeltaImpl::modEntry(EntryFrame const &entry) {
    modEntry(entry.copy());
}

void
LedgerDeltaImpl::recordEntry(EntryFrame const &entry) {
    recordEntry(entry.copy());
}

void
LedgerDeltaImpl::deleteEntryDuplicate() {
      xdr::xvector<LedgerEntryChange> vector;
      std::set<LedgerEntryChange> set;
      for(auto& changes : mAllChanges) {
          if (changes.type() == LedgerEntryChangeType::STATE) {
              set.emplace(changes);
          } else {
              vector.emplace_back(changes);
          }
      }

      for(auto& s : set) {
          vector.emplace_back(s);
      }
      mAllChanges = std::move(vector);
}

void
LedgerDeltaImpl::addEntry(EntryFrame::pointer entry, bool mustAddToAllChanges) {
    checkState();
    auto k = entry->getKey();
    auto del_it = mDelete.find(k);
    if (del_it != mDelete.end()) {
        // delete + new is an update
        mDelete.erase(del_it);
        mMod[k] = entry;
    } else {
        assert(mNew.find(k) == mNew.end()); // double new
        assert(mMod.find(k) == mMod.end()); // mod + new is invalid
        mNew[k] = entry;
    }

    if (mustAddToAllChanges) {
        // add to detailed changes
        mAllChanges.emplace_back(LedgerEntryChangeType::CREATED);
        mAllChanges.back().created() = entry->mEntry;
    }
}

void
LedgerDeltaImpl::deleteEntry(EntryFrame::pointer entry) {
    auto k = entry->getKey();
    deleteEntry(k, true);
}

void LedgerDeltaImpl::deleteEntry(LedgerKey const &k, bool mustAddToAllChanges) {
    checkState();
    auto new_it = mNew.find(k);
    if (new_it != mNew.end()) {
        // new + delete -> don't add it in the first place
        mNew.erase(new_it);
    } else {
        if (mDelete.find(k) == mDelete.end()) {
            mDelete.insert(k);
        } // else already being deleted

        mMod.erase(k);
    }

    if (mustAddToAllChanges) {
        // add key to detailed changes
        mAllChanges.emplace_back(LedgerEntryChangeType::REMOVED);
        mAllChanges.back().removed() = k;
    }
}

void
LedgerDeltaImpl::deleteEntry(LedgerKey const &k) {
    deleteEntry(k, true);
}

void
LedgerDeltaImpl::modEntry(EntryFrame::pointer entry, bool mustAddToAllChanges) {
    checkState();
    auto k = entry->getKey();
    auto mod_it = mMod.find(k);
    if (mod_it != mMod.end()) {
        // collapse mod
        mod_it->second = entry;
    } else {
        auto new_it = mNew.find(k);
        if (new_it != mNew.end()) {
            // new + mod = new (with latest value)
            new_it->second = entry;
        } else {
            assert(mDelete.find(k) == mDelete.end()); // delete + mod is illegal
            mMod[k] = entry;
        }
    }

    if (mustAddToAllChanges) {
        // add to detailed changes
        mAllChanges.emplace_back(LedgerEntryChangeType::UPDATED);
        mAllChanges.back().updated() = entry->mEntry;
    }
}

void
LedgerDeltaImpl::recordEntry(EntryFrame::pointer entry) {
    checkState();
    // keeps the old one around
    mPrevious.insert(std::make_pair(entry->getKey(), entry));

    mAllChanges.emplace_back(LedgerEntryChangeType::STATE);
    mAllChanges.back().state() = entry->mEntry;
}

void
LedgerDeltaImpl::mergeEntries(LedgerDelta &other) {
    checkState();

    // propagates mPrevious for deleted & modified entries
    for (auto &d : other.getDeletionFramesSet()) {
        deleteEntry(d, false);
        auto it = other.getPreviousFrames().find(d);
        if (it != other.getPreviousFrames().end()) {
            recordEntry(*it->second);
        }
    }
    for (auto &n : other.getCreationFrames()) {
        addEntry(n.second, false);
    }
    for (auto &m : other.getModificationFrames()) {
        modEntry(m.second, false);
        auto it = other.getPreviousFrames().find(m.first);
        if (it != other.getPreviousFrames().end()) {
            recordEntry(*it->second);
        }
    }

    for (auto &ch : other.getAllChanges()) {
        mAllChanges.push_back(ch);
    }
}

void
LedgerDeltaImpl::commit() {
    checkState();
    // checks if we about to override changes that were made
    // outside of this LedgerDelta
    if (!(mPreviousHeaderValue == *mHeader)) {
        throw std::runtime_error("unexpected header state");
    }

    if (mOuterDelta) {
        mOuterDelta->mergeEntries(*this);
        mOuterDelta = nullptr;
    }
    *mHeader = mCurrentHeader.getHeader();
    mHeader = nullptr;
}

void
LedgerDeltaImpl::rollback() {
    checkState();
    mHeader = nullptr;
    StorageHelperImpl storageHelperImpl(mDb, nullptr);
    StorageHelper &storageHelper = storageHelperImpl;

    for (auto &d : mDelete) {
        auto helper = storageHelper.getHelper(d.type());
        helper->flushCachedEntry(d);
    }
    for (auto &n : mNew) {
        auto helper = storageHelper.getHelper(n.first.type());
        helper->flushCachedEntry(n.first);
    }
    for (auto &m : mMod) {
        auto helper = storageHelper.getHelper(m.first.type());
        helper->flushCachedEntry(m.first);
    }
}

void
LedgerDeltaImpl::addCurrentMeta(LedgerEntryChanges &changes,
                                LedgerKey const &key) const {
    auto it = mPrevious.find(key);
    if (it != mPrevious.end()) {
        // if the old value is from a previous ledger we emit it
        auto const &e = it->second->mEntry;
        if (e.lastModifiedLedgerSeq != mCurrentHeader.getHeader().ledgerSeq) {
            changes.emplace_back(LedgerEntryChangeType::STATE);
            changes.back().state() = e;
        }
    }
}

LedgerEntryChanges
LedgerDeltaImpl::getChanges() const {
    LedgerEntryChanges changes;

    for (auto const &k : mNew) {
        changes.emplace_back(LedgerEntryChangeType::CREATED);
        changes.back().created() = k.second->mEntry;
    }
    for (auto const &k : mMod) {
        addCurrentMeta(changes, k.first);
        changes.emplace_back(LedgerEntryChangeType::UPDATED);
        changes.back().updated() = k.second->mEntry;
    }

    for (auto const &k : mDelete) {
        addCurrentMeta(changes, k);
        changes.emplace_back(LedgerEntryChangeType::REMOVED);
        changes.back().removed() = k;
    }

    return changes;
}

const LedgerEntryChanges &
LedgerDeltaImpl::getAllChanges() const {
    return mAllChanges;
}

std::vector<LedgerEntry>
LedgerDeltaImpl::getLiveEntries() const {
    std::vector<LedgerEntry> live;

    live.reserve(mNew.size() + mMod.size());

    for (auto const &k : mNew) {
        live.push_back(k.second->mEntry);
    }
    for (auto const &k : mMod) {
        live.push_back(k.second->mEntry);
    }

    return live;
}

std::vector<LedgerKey>
LedgerDeltaImpl::getDeadEntries() const {
    std::vector<LedgerKey> dead;

    dead.reserve(mDelete.size());

    for (auto const &k : mDelete) {
        dead.push_back(k);
    }
    return dead;
}

bool
LedgerDeltaImpl::updateLastModified() const {
    return mUpdateLastModified;
}

void
LedgerDeltaImpl::markMeters(Application &app) const {
    for (auto const &ke : mNew) {
        app.getMetrics()
                .NewMeter(
                        {"ledger",
                         xdr::xdr_traits<LedgerEntryType>::enum_name(ke.first.type()),
                         "add"},
                        "entry")
                .Mark();
    }

    for (auto const &ke : mMod) {
        app.getMetrics()
                .NewMeter(
                        {"ledger",
                         xdr::xdr_traits<LedgerEntryType>::enum_name(ke.first.type()),
                         "modify"},
                        "entry")
                .Mark();
    }

    for (auto const &ke : mDelete) {
        app.getMetrics()
                .NewMeter({"ledger",
                           xdr::xdr_traits<LedgerEntryType>::enum_name(ke.type()),
                           "delete"},
                          "entry")
                .Mark();
    }
}



bool
LedgerDeltaImpl::isStateActive() const {
    return static_cast<bool>(mHeader);
}

Database &
LedgerDeltaImpl::getDatabase() {
    return mDb;
}

const LedgerDeltaImpl::KeyEntryMap &
LedgerDeltaImpl::getPreviousFrames() const {
    return mPrevious;
}

const std::set<LedgerKey, LedgerEntryIdCmp> &
LedgerDeltaImpl::getDeletionFramesSet() const {
    return mDelete;
}

const LedgerDeltaImpl::KeyEntryMap &
LedgerDeltaImpl::getCreationFrames() const {
    return mNew;
}

const LedgerDeltaImpl::KeyEntryMap &
LedgerDeltaImpl::getModificationFrames() const {
    return mMod;
}

} // namespace stellar