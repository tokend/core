// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "LedgerTestUtils.h"
#include "crypto/SHA.h"
#include "crypto/SecretKey.h"
#include "main/Config.h"
#include "util/Logging.h"
#include "util/Math.h"
#include "util/types.h"
#include <locale>
#include <string>
//#include <xdrpp/autocheck.h>
#include <xdrpp/marshal.h>

namespace stellar
{
namespace LedgerTestUtils
{

template <typename T>
void
clampLow(T low, T& v)
{
    if (v < low)
    {
        v = low;
    }
}

template <typename T>
void
clampHigh(T high, T& v)
{
    if (v > high)
    {
        v = high;
    }
}

// mutate string such that it doesn't contain control characters
// and is at least minSize characters long
template <typename T>
void
replaceControlCharacters(T& s, int minSize)
{
    auto& loc = std::locale::classic();
    if (static_cast<int>(s.size()) < minSize)
    {
        s.resize(minSize);
    }
    for (auto it = s.begin(); it != s.end(); it++)
    {
        char c = static_cast<char>(*it);
        if (c < 0 || std::iscntrl(c, loc))
        {
            /*auto b = autocheck::generator<char>{}(autocheck::detail::nalnums);
            *it = b;*/
        }
    }
}


void
makeValid(AccountEntry& a)
{
}

void
makeValid(OfferEntry& o)
{
    o.offerID = o.offerID & INT64_MAX;
}

void
makeValid(std::vector<LedgerHeaderHistoryEntry>& lhv,
          LedgerHeaderHistoryEntry firstLedger,
          HistoryManager::LedgerVerificationStatus state)
{
    auto randomIndex = rand_uniform<size_t>(1, lhv.size() - 1);
    auto prevHash = firstLedger.header.previousLedgerHash;
    auto ledgerSeq = firstLedger.header.ledgerSeq;

    for (auto i = 0; i < lhv.size(); i++)
    {
        auto& lh = lhv[i];

        lh.header.ledgerVersion = Config::CURRENT_LEDGER_PROTOCOL_VERSION;
        lh.header.previousLedgerHash = prevHash;
        lh.header.ledgerSeq = ledgerSeq;

        if (i == randomIndex && state != HistoryManager::VERIFY_STATUS_OK)
        {
            switch (state)
            {
            case HistoryManager::VERIFY_STATUS_ERR_BAD_LEDGER_VERSION:
                lh.header.ledgerVersion += 1;
                break;
            case HistoryManager::VERIFY_STATUS_ERR_BAD_HASH:
                lh.header.previousLedgerHash = HashUtils::random();
                break;
            case HistoryManager::VERIFY_STATUS_ERR_UNDERSHOT:
                lh.header.ledgerSeq -= 1;
                break;
            case HistoryManager::VERIFY_STATUS_ERR_OVERSHOT:
                lh.header.ledgerSeq += 1;
                break;
            default:
                break;
            }
        }
        // On a coin flip, corrupt header content rather than previous link
        //autocheck::generator<bool> flip;
        if (i == randomIndex /*&&
            state == HistoryManager::VERIFY_STATUS_ERR_BAD_HASH && flip()*/)
        {
            lh.hash = HashUtils::random();
        }
        else
        {
            lh.hash = sha256(xdr::xdr_to_opaque(lh.header));
        }

        prevHash = lh.hash;
        ledgerSeq = lh.header.ledgerSeq + 1;
    }

    if (state == HistoryManager::VERIFY_STATUS_ERR_MISSING_ENTRIES)
    {
        // Delete last element
        lhv.erase(lhv.begin() + lhv.size() - 1);
    }
}

LedgerEntry
generateValidLedgerEntry(size_t b)
{
    return {};
}

std::vector<LedgerEntry>
generateValidLedgerEntries(size_t n)
{
    return {};
}

AccountEntry
generateValidAccountEntry(size_t b)
{
    return {};
}

std::vector<AccountEntry>
generateValidAccountEntries(size_t n)
{
    return {};
}
std::vector<LedgerHeaderHistoryEntry>
generateLedgerHeadersForCheckpoint(
    LedgerHeaderHistoryEntry firstLedger, uint32_t freq,
    HistoryManager::LedgerVerificationStatus state)
{
    /*static auto vecgen =
        autocheck::list_of(autocheck::generator<LedgerHeaderHistoryEntry>());
    auto res = vecgen(freq);
    makeValid(res, firstLedger, state);*/
    return {};
}
}
}
