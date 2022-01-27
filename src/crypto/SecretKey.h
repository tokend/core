#pragma once

// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "xdr/types.h"
#include <ostream>
#include <functional>
#include <array>

namespace stellar
{

using xdr::operator==;

class ByteSlice;
struct SecretValue;

class SecretKey
{
    using uint512 = xdr::opaque_array<64>;
    CryptoKeyType mKeyType;
    uint512 mSecretKey;
    PublicKey mPublicKey;

    struct Seed
    {
        CryptoKeyType mKeyType;
        uint256 mSeed;
        ~Seed();
    };

    // Get the seed portion of this secret key.
    Seed getSeed() const;

  public:
    SecretKey();
    ~SecretKey();

    // Get the public key portion of this secret key.
    PublicKey const& getPublicKey() const;

    // Get the seed portion of this secret key as a StrKey string.
    SecretValue getStrKeySeed() const;

    // Get the public key portion of this secret key as a StrKey string.
    std::string getStrKeyPublic() const;

    // Return true iff this key is all-zero.
    bool isZero() const;

    // Produce a signature of `bin` using this secret key.
    Signature sign(ByteSlice const& bin) const;

    // Create a new, random secret key.
    static SecretKey random();

    // Decode a secret key from a provided StrKey seed value.
    static SecretKey fromStrKeySeed(std::string const& strKeySeed);
    static SecretKey
    fromStrKeySeed(std::string&& strKeySeed)
    {
        SecretKey ret = fromStrKeySeed(strKeySeed);
        for (std::size_t i = 0; i < strKeySeed.size(); ++i)
            strKeySeed[i] = 0;
        return ret;
    }

    // Decode a secret key from a binary seed value.
    static SecretKey fromSeed(ByteSlice const& seed);

    bool
    operator==(SecretKey const& rh) const
    {
        return (mKeyType == rh.mKeyType) && (mSecretKey == rh.mSecretKey);
    }
};

// public key utility functions
namespace PubKeyUtils
{
// Return true iff `signature` is valid for `bin` under `key`.
bool verifySig(PublicKey const& key, Signature const& signature,
               ByteSlice const& bin);

void clearVerifySigCache();
void flushVerifySigCacheCounts(uint64_t& hits, uint64_t& misses);

std::string toShortString(PublicKey const& pk);

std::string toStrKey(PublicKey const& pk);

PublicKey fromStrKey(std::string const& s);

// returns hint from key
SignatureHint getHint(PublicKey const& pk);
// returns true if the hint matches the key
bool hasHint(PublicKey const& pk, SignatureHint const& hint);

PublicKey random();
}

namespace BalanceKeyUtils
{
std::string toStrKey(PublicKey const& pk);
PublicKey fromStrKey(std::string const& s);
BalanceID forAccount(AccountID const& owner, uint64_t id);
}

namespace StrKeyUtils
{
// logs a key (can be a public or private key) in all
// known formats
void logKey(std::ostream& s, std::string const& key);
PublicKey fromStrKey(std::string const& s, int expectedKeyType);
PublicKey fromStrKey(std::string const& s);
PublicKey fromStr(std::string const& s, uint8_t& keyType);
}

namespace HashUtils
{
Hash random();
Hash fromStr(std::string const& s);
}
}

namespace std
{
template <> struct hash<stellar::PublicKey>
{
    size_t operator()(stellar::PublicKey const& x) const noexcept;
};
}
