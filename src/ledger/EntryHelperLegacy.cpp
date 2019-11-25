// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "LedgerManager.h"
#include "ledger/ReferenceFrame.h"
#include "ledger/ReferenceHelper.h"
#include "ledger/AssetPairHelper.h"
#include "ledger/AtomicSwapAskHelper.h"
#include "ledger/LedgerDelta.h"
#include "ledger/FeeHelper.h"
#include "ledger/StorageHelperImpl.h"
#include "ledger/OfferHelper.h"
#include "ledger/ExternalSystemAccountIDHelperLegacy.h"
#include "ledger/KeyValueHelperLegacy.h"
#include "ledger/ExternalSystemAccountIDPoolEntryHelperLegacy.h"
#include "xdrpp/printer.h"
#include "xdrpp/marshal.h"
#include "SaleHelper.h"
#include "StatisticsV2Helper.h"
#include "PendingStatisticsHelper.h"
#include "ContractHelper.h"
#include "EntryHelperLegacyImpl.h"

namespace stellar
{
using xdr::operator==;

LedgerKey LedgerEntryKey(LedgerEntry const& e)
{
    EntryHelperLegacy *helper = EntryHelperProvider::getHelper(e.data.type());
    return helper->getLedgerKey(e);
}

void EntryHelperLegacy::flushCachedEntry(LedgerKey const& key, Database& db)
{
    auto s = binToHex(xdr::xdr_to_opaque(key));
    db.getEntryCache().erase_if_exists(s);
}

bool EntryHelperLegacy::cachedEntryExists(LedgerKey const& key, Database& db)
{
    auto s = binToHex(xdr::xdr_to_opaque(key));
    return db.getEntryCache().exists(s);
}

std::shared_ptr<LedgerEntry const>
EntryHelperLegacy::getCachedEntry(LedgerKey const& key, Database& db)
{
    auto s = binToHex(xdr::xdr_to_opaque(key));
    return db.getEntryCache().get(s);
}

void EntryHelperLegacy::putCachedEntry(LedgerKey const& key,
                                       std::shared_ptr<LedgerEntry const> p, Database& db)
{
    auto s = binToHex(xdr::xdr_to_opaque(key));
    db.getEntryCache().put(s, p);
}

void 
EntryHelperLegacy::tryRecordEntry(EntryFrame::pointer frame, LedgerDelta *delta) 
{
    if (frame && (delta != nullptr))
    {
        delta->recordEntry(*frame);
    }
}

uint64_t
EntryHelperLegacy::countObjects(Database& db)
{
    return countObjects(db.getSession());
}

void
EntryHelperProvider::checkAgainstDatabase(LedgerEntry const& entry, Database& db)
{
    LedgerKey key = LedgerEntryKey(entry);
    auto legacyHelper = getHelper(entry.data.type()); // helper existing handled above
    legacyHelper->flushCachedEntry(key, db);
    EntryFrame::pointer fromDb = legacyHelper->storeLoad(key, db);

    if (!fromDb || !(fromDb->mEntry == entry))
    {
        std::string s;
        s = "Inconsistent state between objects: ";
        s += !!fromDb ? xdr::xdr_to_string(fromDb->mEntry, "db") : "db: nullptr\n";
        s += xdr::xdr_to_string(entry, "live");
        throw std::runtime_error(s);
    }
}

void
EntryHelperProvider::storeAddEntry(LedgerDelta& delta, Database& db, LedgerEntry const& entry)
{
    EntryHelperLegacy *helper = getHelper(entry.data.type());
    return helper->storeAdd(delta, db, entry);
}

void
EntryHelperProvider::storeChangeEntry(LedgerDelta& delta, Database& db, LedgerEntry const& entry)
{
    EntryHelperLegacy *helper = getHelper(entry.data.type());
    return helper->storeChange(delta, db, entry);
}

void
EntryHelperProvider::storeAddOrChangeEntry(LedgerDelta& delta, Database& db, LedgerEntry const& entry)
{
    auto key = LedgerEntryKey(entry);
    if (existsEntry(db, key))
    {
        storeChangeEntry(delta, db, entry);
    }
    else
    {
        storeAddEntry(delta, db, entry);
    }
}

void
EntryHelperProvider::storeDeleteEntry(LedgerDelta& delta, Database& db, LedgerKey const& key)
{
    EntryHelperLegacy *helper = getHelper(key.type());
    helper->storeDelete(delta, db, key);
}

bool
EntryHelperProvider::existsEntry(Database& db, LedgerKey const& key)
{
    EntryHelperLegacy *helper = getHelper(key.type());
    return helper->exists(db, key);
}

EntryFrame::pointer
EntryHelperProvider::storeLoadEntry(LedgerKey const& key, Database& db)
{
    EntryHelperLegacy *helper = getHelper(key.type());
    return helper->storeLoad(key, db);
}

uint64_t
EntryHelperProvider::countObjectsEntry(Database& db, LedgerEntryType const& type)
{
    EntryHelperLegacy *helper = getHelper(type);
    return helper->countObjects(db);
}

void EntryHelperProvider::dropAll(Database& db)
{
    for (auto& it : helpers)
    {
        it.second->dropAll(db);
    }
}

EntryHelperProvider::helperMap EntryHelperProvider::helpers = {
    {LedgerEntryType::ACCOUNT,                               EntryHelperLegacyImpl::Instance(LedgerEntryType::ACCOUNT)},
    {LedgerEntryType::ASSET,                                 EntryHelperLegacyImpl::Instance(LedgerEntryType::ASSET)},
    {LedgerEntryType::ASSET_PAIR,                            EntryHelperLegacyImpl::Instance(LedgerEntryType::ASSET_PAIR)},
    {LedgerEntryType::BALANCE,                               BalanceHelperLegacy::Instance()},
    {LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID,            ExternalSystemAccountIDHelperLegacy::Instance()},
    {LedgerEntryType::FEE,                                   FeeHelper::Instance()},
    {LedgerEntryType::OFFER_ENTRY,                           OfferHelper::Instance()},
    {LedgerEntryType::REFERENCE_ENTRY,                       ReferenceHelper::Instance()},
    {LedgerEntryType::REVIEWABLE_REQUEST,                    EntryHelperLegacyImpl::Instance(LedgerEntryType::REVIEWABLE_REQUEST)},
    {LedgerEntryType::KEY_VALUE,                             KeyValueHelperLegacy::Instance()},
    {LedgerEntryType::ACCOUNT_KYC,                           EntryHelperLegacyImpl::Instance(LedgerEntryType::ACCOUNT_KYC)},
    {LedgerEntryType::SALE,                                  SaleHelper::Instance()},
    {LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY, ExternalSystemAccountIDPoolEntryHelperLegacy::Instance()},
    {LedgerEntryType::LIMITS_V2,                             EntryHelperLegacyImpl::Instance(LedgerEntryType::LIMITS_V2) },
    {LedgerEntryType::STATISTICS_V2,                         StatisticsV2Helper::Instance()},
    {LedgerEntryType::PENDING_STATISTICS,                    PendingStatisticsHelper::Instance()},
    {LedgerEntryType::CONTRACT,                              ContractHelper::Instance()},
    {LedgerEntryType::ATOMIC_SWAP_ASK,                       AtomicSwapAskHelper::Instance()},
    {LedgerEntryType::SIGNER,                                EntryHelperLegacyImpl::Instance(LedgerEntryType::SIGNER)},
    {LedgerEntryType::ACCOUNT_RULE,                          EntryHelperLegacyImpl::Instance(LedgerEntryType::ACCOUNT_RULE)},
    {LedgerEntryType::ACCOUNT_ROLE,                          EntryHelperLegacyImpl::Instance(LedgerEntryType::ACCOUNT_ROLE)},
    {LedgerEntryType::SIGNER_RULE,                           EntryHelperLegacyImpl::Instance(LedgerEntryType::SIGNER_RULE)},
    {LedgerEntryType::SIGNER_ROLE,                           EntryHelperLegacyImpl::Instance(LedgerEntryType::SIGNER_ROLE)},
    {LedgerEntryType::STAMP,                                 EntryHelperLegacyImpl::Instance(LedgerEntryType::STAMP)},
    {LedgerEntryType::LICENSE,                               EntryHelperLegacyImpl::Instance(LedgerEntryType::LICENSE)},
    {LedgerEntryType::VOTE,                                  EntryHelperLegacyImpl::Instance(LedgerEntryType::VOTE)},
    {LedgerEntryType::POLL,                                  EntryHelperLegacyImpl::Instance(LedgerEntryType::POLL)},
    {LedgerEntryType::ACCOUNT_SPECIFIC_RULE,                 EntryHelperLegacyImpl::Instance(LedgerEntryType::ACCOUNT_SPECIFIC_RULE)}
};
}
