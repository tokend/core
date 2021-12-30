#include "ledger-entries-liquidity-pool.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
LPAssetPair::from_bytes(xdr::unmarshaler& u) 
{
bool okfirstAsset = u.from_bytes(firstAsset);
if (!okfirstAsset)
{
return false;
}
bool okfirtsAssetAmount = u.from_bytes(firtsAssetAmount);
if (!okfirtsAssetAmount)
{
return false;
}
bool okfirstAssetBalance = u.from_bytes(firstAssetBalance);
if (!okfirstAssetBalance)
{
return false;
}
bool oksecondAsset = u.from_bytes(secondAsset);
if (!oksecondAsset)
{
return false;
}
bool oksecondAssetAmount = u.from_bytes(secondAssetAmount);
if (!oksecondAssetAmount)
{
return false;
}
bool oksecondAssetID = u.from_bytes(secondAssetID);
if (!oksecondAssetID)
{
return false;
}
return true;
}
bool
LPAssetPair::to_bytes(xdr::marshaler& m) const 
{
bool okfirstAsset = m.to_bytes(firstAsset);
if (!okfirstAsset)
{
return false;
}
bool okfirtsAssetAmount = m.to_bytes(firtsAssetAmount);
if (!okfirtsAssetAmount)
{
return false;
}
bool okfirstAssetBalance = m.to_bytes(firstAssetBalance);
if (!okfirstAssetBalance)
{
return false;
}
bool oksecondAsset = m.to_bytes(secondAsset);
if (!oksecondAsset)
{
return false;
}
bool oksecondAssetAmount = m.to_bytes(secondAssetAmount);
if (!oksecondAssetAmount)
{
return false;
}
bool oksecondAssetID = m.to_bytes(secondAssetID);
if (!oksecondAssetID)
{
return false;
}
return true;
}
void
LPAssetPair::count_size(xdr::measurer& m) const 
{
m.count_size(firstAsset);
m.count_size(firtsAssetAmount);
m.count_size(firstAssetBalance);
m.count_size(secondAsset);
m.count_size(secondAssetAmount);
m.count_size(secondAssetID);
}
bool
LPAssetPair::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<LPAssetPair const&>(other_abstract);return true
&& (firstAsset== other.firstAsset)
&& (firtsAssetAmount== other.firtsAssetAmount)
&& (firstAssetBalance== other.firstAssetBalance)
&& (secondAsset== other.secondAsset)
&& (secondAssetAmount== other.secondAssetAmount)
&& (secondAssetID== other.secondAssetID)
;}
bool
LPAssetPair::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<LPAssetPair const&>(other_abstract);
if (firstAsset < other.firstAsset) return true;
if (other.firstAsset < firstAsset) return false;
if (firtsAssetAmount < other.firtsAssetAmount) return true;
if (other.firtsAssetAmount < firtsAssetAmount) return false;
if (firstAssetBalance < other.firstAssetBalance) return true;
if (other.firstAssetBalance < firstAssetBalance) return false;
if (secondAsset < other.secondAsset) return true;
if (other.secondAsset < secondAsset) return false;
if (secondAssetAmount < other.secondAssetAmount) return true;
if (other.secondAssetAmount < secondAssetAmount) return false;
if (secondAssetID < other.secondAssetID) return true;
if (other.secondAssetID < secondAssetID) return false;
return false;
}bool
LiquidityPoolEntry::from_bytes(xdr::unmarshaler& u) 
{
bool oksequentialID = u.from_bytes(sequentialID);
if (!oksequentialID)
{
return false;
}
bool okliquidityPoolOwner = u.from_bytes(liquidityPoolOwner);
if (!okliquidityPoolOwner)
{
return false;
}
bool oklpTokensBalance = u.from_bytes(lpTokensBalance);
if (!oklpTokensBalance)
{
return false;
}
bool oklpTokensAmount = u.from_bytes(lpTokensAmount);
if (!oklpTokensAmount)
{
return false;
}
bool okassetPair = u.from_bytes(assetPair);
if (!okassetPair)
{
return false;
}
bool okext = u.from_bytes(ext);
if (!okext)
{
return false;
}
return true;
}
bool
LiquidityPoolEntry::to_bytes(xdr::marshaler& m) const 
{
bool oksequentialID = m.to_bytes(sequentialID);
if (!oksequentialID)
{
return false;
}
bool okliquidityPoolOwner = m.to_bytes(liquidityPoolOwner);
if (!okliquidityPoolOwner)
{
return false;
}
bool oklpTokensBalance = m.to_bytes(lpTokensBalance);
if (!oklpTokensBalance)
{
return false;
}
bool oklpTokensAmount = m.to_bytes(lpTokensAmount);
if (!oklpTokensAmount)
{
return false;
}
bool okassetPair = m.to_bytes(assetPair);
if (!okassetPair)
{
return false;
}
bool okext = m.to_bytes(ext);
if (!okext)
{
return false;
}
return true;
}
void
LiquidityPoolEntry::count_size(xdr::measurer& m) const 
{
m.count_size(sequentialID);
m.count_size(liquidityPoolOwner);
m.count_size(lpTokensBalance);
m.count_size(lpTokensAmount);
m.count_size(assetPair);
m.count_size(ext);
}
bool
LiquidityPoolEntry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<LiquidityPoolEntry const&>(other_abstract);return true
&& (sequentialID== other.sequentialID)
&& (liquidityPoolOwner== other.liquidityPoolOwner)
&& (lpTokensBalance== other.lpTokensBalance)
&& (lpTokensAmount== other.lpTokensAmount)
&& (assetPair== other.assetPair)
&& (ext== other.ext)
;}
bool
LiquidityPoolEntry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<LiquidityPoolEntry const&>(other_abstract);
if (sequentialID < other.sequentialID) return true;
if (other.sequentialID < sequentialID) return false;
if (liquidityPoolOwner < other.liquidityPoolOwner) return true;
if (other.liquidityPoolOwner < liquidityPoolOwner) return false;
if (lpTokensBalance < other.lpTokensBalance) return true;
if (other.lpTokensBalance < lpTokensBalance) return false;
if (lpTokensAmount < other.lpTokensAmount) return true;
if (other.lpTokensAmount < lpTokensAmount) return false;
if (assetPair < other.assetPair) return true;
if (other.assetPair < assetPair) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}