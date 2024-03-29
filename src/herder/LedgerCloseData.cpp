﻿#include "LedgerCloseData.h"
#include "main/Application.h"
#include "crypto/Hex.h"
#include <overlay/OverlayManager.h>
#include "herder/Upgrades.h"
#include <xdrpp/marshal.h>
#include "util/Logging.h"
#include "util/asio.h"
#include "util/XDROperators.h"

using namespace std;

namespace stellar
{

LedgerCloseData::LedgerCloseData(uint32_t ledgerSeq, TxSetFramePtr txSet,
                                 StellarValue const& v)
    : mLedgerSeq(ledgerSeq), mTxSet(txSet), mValue(v)
{
    Value x;
    Value y(x.begin(), x.end());

    assert(txSet->getContentsHash() == mValue.txSetHash);
}

std::string
StellarValueToString(StellarValue const& sv)
{
    std::stringstream res;

    res << "[ "
        << " txH: " << hexAbbrev(sv.txSetHash) << ", ct: " << sv.closeTime
        << ", upgrades: [";
    for (auto const& upgrade : sv.upgrades)
    {
        if (upgrade.empty())
        {
            // should not happen as this is not valid
            res << "<empty>";
        }
        else
        {
            try
            {
                LedgerUpgrade lupgrade;
                xdr::xdr_from_opaque(upgrade, lupgrade);
                res << Upgrades::toString(lupgrade);
            }
            catch (std::exception&)
            {
                res << "<unknown>";
            }
        }
        res << ", ";
    }
    res << " ] ]";

    return res.str();
}
}
