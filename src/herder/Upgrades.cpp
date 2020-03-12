// Copyright 2017 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "herder/Upgrades.h"
#include "database/Database.h"
#include "database/DatabaseUtils.h"
//#include "ledger/LedgerTxnEntry.h"
//#include "ledger/LedgerTxnHeader.h"
#include "main/Config.h"
#include "util/Decoder.h"
#include "util/Logging.h"
#include "util/Timer.h"
#include "util/types.h"
#include <cereal/archives/json.hpp>
#include <cereal/cereal.hpp>
#include <lib/util/format.h>
#include <xdrpp/marshal.h>
#include <ledger/LedgerDelta.h>

namespace cereal
{
template <class Archive>
void
save(Archive& ar, stellar::Upgrades::UpgradeParameters const& p)
{
    ar(make_nvp("time", stellar::VirtualClock::to_time_t(p.mUpgradeTime)));
    ar(make_nvp("version", p.mProtocolVersion));
    ar(make_nvp("maxtxsize", p.mMaxTxSize));
    ar(make_nvp("txexpirationperiod", p.mTxExpirationPeriod));
}

template <class Archive>
void
load(Archive& ar, stellar::Upgrades::UpgradeParameters& o)
{
    time_t t;
    ar(make_nvp("time", t));
    o.mUpgradeTime = stellar::VirtualClock::from_time_t(t);
    ar(make_nvp("version", o.mProtocolVersion));
    ar(make_nvp("maxtxsize", o.mMaxTxSize));
    ar(make_nvp("txexpirationperiod", o.mTxExpirationPeriod));
}
} // namespace cereal

namespace stellar
{
std::string
Upgrades::UpgradeParameters::toJson() const
{
    std::ostringstream out;
    {
        cereal::JSONOutputArchive ar(out);
        cereal::save(ar, *this);
    }
    return out.str();
}

void
Upgrades::UpgradeParameters::fromJson(std::string const& s)
{
    std::istringstream in(s);
    {
        cereal::JSONInputArchive ar(in);
        cereal::load(ar, *this);
    }
}

Upgrades::Upgrades(UpgradeParameters const& params) : mParams(params)
{
}

void
Upgrades::setParameters(UpgradeParameters const& params, Config const& cfg)
{
    if (params.mProtocolVersion &&
        *params.mProtocolVersion > cfg.LEDGER_PROTOCOL_VERSION)
    {
        throw std::invalid_argument(fmt::format(
            "Protocol version error: supported is up to {}, passed is {}",
            cfg.LEDGER_PROTOCOL_VERSION, *params.mProtocolVersion));
    }
    mParams = params;
}

Upgrades::UpgradeParameters const&
Upgrades::getParameters() const
{
    return mParams;
}

std::vector<LedgerUpgrade>
Upgrades::createUpgradesFor(LedgerHeader const& header) const
{
    auto result = std::vector<LedgerUpgrade>{};
    if (!timeForUpgrade(header.scpValue.closeTime))
    {
        return result;
    }

    if (mParams.mProtocolVersion &&
        (header.ledgerVersion != *mParams.mProtocolVersion))
    {
        result.emplace_back(LedgerUpgradeType::VERSION);
        result.back().newLedgerVersion() = *mParams.mProtocolVersion;
    }
    if (mParams.mMaxTxSize && (header.maxTxSetSize != *mParams.mMaxTxSize))
    {
        result.emplace_back(LedgerUpgradeType::MAX_TX_SET_SIZE);
        result.back().newMaxTxSetSize() = *mParams.mMaxTxSize;
    }
    if (mParams.mTxExpirationPeriod && (header.txExpirationPeriod != *mParams.mTxExpirationPeriod))
    {
        result.emplace_back(LedgerUpgradeType::TX_EXPIRATION_PERIOD);
        result.back().newTxExpirationPeriod() = *mParams.mTxExpirationPeriod;
    }

    return result;
}

void
Upgrades::applyTo(LedgerUpgrade const& upgrade, LedgerDelta& delta)
{
    switch (upgrade.type())
    {
    case LedgerUpgradeType::VERSION:
        delta.getHeader().ledgerVersion = upgrade.newLedgerVersion();

        //set version for comparator
        LedgerEntryIdCmp::currVersion = LedgerVersion(upgrade.newLedgerVersion());
        break;
    case LedgerUpgradeType::MAX_TX_SET_SIZE:
        delta.getHeader().maxTxSetSize = upgrade.newMaxTxSetSize();
        break;
    case LedgerUpgradeType::TX_EXPIRATION_PERIOD:
        delta.getHeader().txExpirationPeriod = upgrade.newTxExpirationPeriod();
        break;
    default:
    {
        auto s = fmt::format("Unknown upgrade type: {0}", static_cast<int32_t>(upgrade.type()));
        throw std::runtime_error(s);
    }
    }
}

std::string
Upgrades::toString(LedgerUpgrade const& upgrade)
{
    switch (upgrade.type())
    {
    case LedgerUpgradeType::VERSION:
        return fmt::format("protocolversion={0}", upgrade.newLedgerVersion());
    case LedgerUpgradeType::MAX_TX_SET_SIZE:
        return fmt::format("maxtxsetsize={0}", upgrade.newMaxTxSetSize());
    case LedgerUpgradeType::TX_EXPIRATION_PERIOD:
        return fmt::format("txexpirationperiod={0}", upgrade.newTxExpirationPeriod());
    default:
        return "<unsupported>";
    }
}

std::string
Upgrades::toString() const
{
    fmt::MemoryWriter r;

    auto appendInfo = [&](std::string const& s, optional<uint32> const& o) {
        if (o)
        {
            if (!r.size())
            {
                r << "upgradetime="
                  << VirtualClock::pointToISOString(mParams.mUpgradeTime);
            }
            r << ", " << s << "=" << *o;
        }
    };
    appendInfo("protocolversion", mParams.mProtocolVersion);
    appendInfo("txexpirationperiod", mParams.mTxExpirationPeriod);
    appendInfo("maxtxsize", mParams.mMaxTxSize);

    return r.str();
}

Upgrades::UpgradeParameters
Upgrades::removeUpgrades(std::vector<UpgradeType>::const_iterator beginUpdates,
                         std::vector<UpgradeType>::const_iterator endUpdates,
                         bool& updated)
{
    updated = false;
    UpgradeParameters res = mParams;

    auto resetParam = [&](optional<uint32>& o, uint32 v) {
        if (o && *o == v)
        {
            o.reset();
            updated = true;
        }
    };

    for (auto it = beginUpdates; it != endUpdates; it++)
    {
        auto& u = *it;
        LedgerUpgrade lu;
        try
        {
            xdr::xdr_from_opaque(u, lu);
        }
        catch (xdr::xdr_runtime_error&)
        {
            continue;
        }
        switch (lu.type())
        {
        case LedgerUpgradeType::VERSION:
            resetParam(res.mProtocolVersion, lu.newLedgerVersion());
            break;
        case LedgerUpgradeType::MAX_TX_SET_SIZE:
            resetParam(res.mMaxTxSize, lu.newMaxTxSetSize());
            break;
        case LedgerUpgradeType::TX_EXPIRATION_PERIOD:
            resetParam(res.mTxExpirationPeriod, lu.newTxExpirationPeriod());
            break;
        default:
            // skip unknown
            break;
        }
    }
    return res;
}

bool
Upgrades::isValid(UpgradeType const& upgrade, LedgerUpgradeType& upgradeType,
                  bool nomination, Config const& cfg,
                  LedgerHeader const& header) const
{
    if (nomination && !timeForUpgrade(header.scpValue.closeTime))
    {
        return false;
    }

    LedgerUpgrade lupgrade;

    try
    {
        xdr::xdr_from_opaque(upgrade, lupgrade);
    }
    catch (xdr::xdr_runtime_error&)
    {
        return false;
    }

    bool res = true;
    switch (lupgrade.type())
    {
    case LedgerUpgradeType::VERSION:
    {
        uint32 newVersion = lupgrade.newLedgerVersion();
        if (nomination)
        {
            res = mParams.mProtocolVersion &&
                  (newVersion == *mParams.mProtocolVersion);
        }
        // only allow upgrades to a supported version of the protocol
        res = res && (newVersion <= cfg.LEDGER_PROTOCOL_VERSION);
        // and enforce versions to be strictly monotonic
        res = res && (newVersion > header.ledgerVersion);
    }
    break;
    case LedgerUpgradeType::MAX_TX_SET_SIZE:
    {
        uint32 newMax = lupgrade.newMaxTxSetSize();
        if (nomination)
        {
            res = mParams.mMaxTxSize && (newMax == *mParams.mMaxTxSize);
        }
        res = res && (newMax != 0);
    }
    break;
    case LedgerUpgradeType::TX_EXPIRATION_PERIOD:
    {
        uint32 txExpPer = lupgrade.newTxExpirationPeriod();
        if (nomination)
        {
            res = mParams.mTxExpirationPeriod && (txExpPer == *mParams.mTxExpirationPeriod);
        }
        res = res && (txExpPer != 0);
    }
    break;
    default:
        res = false;
    }
    if (res)
    {
        upgradeType = lupgrade.type();
    }
    return res;
}

bool
Upgrades::timeForUpgrade(uint64_t time) const
{
    return mParams.mUpgradeTime <= VirtualClock::from_time_t(time);
}

void
Upgrades::dropAll(Database& db)
{
    db.getSession() << "DROP TABLE IF EXISTS upgradehistory";
    createIfNotExists(db);
}

void
Upgrades::createIfNotExists(Database& db)
{
    db.getSession() << "CREATE TABLE IF NOT EXISTS upgradehistory ("
                       "ledgerseq    INT NOT NULL CHECK (ledgerseq >= 0), "
                       "upgradeindex INT NOT NULL, "
                       "upgrade      TEXT NOT NULL, "
                       "changes      TEXT NOT NULL, "
                       "PRIMARY KEY (ledgerseq, upgradeindex)"
                       ")";
    db.getSession()
            << "CREATE INDEX IF NOT EXISTS upgradehistbyseq ON upgradehistory (ledgerseq);";
}

void
Upgrades::storeUpgradeHistory(Database& db, uint32_t ledgerSeq,
                              LedgerUpgrade const& upgrade,
                              LedgerEntryChanges const& changes, int index)
{
    xdr::opaque_vec<> upgradeContent(xdr::xdr_to_opaque(upgrade));
    std::string upgradeContent64 = decoder::encode_b64(upgradeContent);

    xdr::opaque_vec<> upgradeChanges(xdr::xdr_to_opaque(changes));
    std::string upgradeChanges64 = decoder::encode_b64(upgradeChanges);

    auto prep = db.getPreparedStatement(
        "INSERT INTO upgradehistory "
        "(ledgerseq, upgradeindex,  upgrade,  changes) VALUES "
        "(:seq,      :upgradeindex, :upgrade, :changes)");

    auto& st = prep.statement();
    st.exchange(soci::use(ledgerSeq));
    st.exchange(soci::use(index));
    st.exchange(soci::use(upgradeContent64));
    st.exchange(soci::use(upgradeChanges64));
    st.define_and_bind();
    {
        auto timer = db.getInsertTimer("upgradehistory");
        st.execute(true);
    }

    if (st.get_affected_rows() != 1)
    {
        throw std::runtime_error("Could not update data in SQL");
    }
}

void
Upgrades::deleteOldEntries(Database& db, uint32_t ledgerSeq, uint32_t count)
{
    DatabaseUtils::deleteOldEntriesHelper(db.getSession(), ledgerSeq, count,
                                          "upgradehistory", "ledgerseq");
}
}
