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
LiquidityPoolEntry::from_bytes(xdr::unmarshaler& u) 
{
bool okid = u.from_bytes(id);
if (!okid)
{
return false;
}
bool okliquidityPoolAcount = u.from_bytes(liquidityPoolAcount);
if (!okliquidityPoolAcount)
{
return false;
}
bool oklpTokenAssetCode = u.from_bytes(lpTokenAssetCode);
if (!oklpTokenAssetCode)
{
return false;
}
bool okfirstAssetBalance = u.from_bytes(firstAssetBalance);
if (!okfirstAssetBalance)
{
return false;
}
bool oksecondAssetBalance = u.from_bytes(secondAssetBalance);
if (!oksecondAssetBalance)
{
return false;
}
bool oklpTokensTotalCap = u.from_bytes(lpTokensTotalCap);
if (!oklpTokensTotalCap)
{
return false;
}
bool okfirstReserve = u.from_bytes(firstReserve);
if (!okfirstReserve)
{
return false;
}
bool oksecondReserve = u.from_bytes(secondReserve);
if (!oksecondReserve)
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
bool okid = m.to_bytes(id);
if (!okid)
{
return false;
}
bool okliquidityPoolAcount = m.to_bytes(liquidityPoolAcount);
if (!okliquidityPoolAcount)
{
return false;
}
bool oklpTokenAssetCode = m.to_bytes(lpTokenAssetCode);
if (!oklpTokenAssetCode)
{
return false;
}
bool okfirstAssetBalance = m.to_bytes(firstAssetBalance);
if (!okfirstAssetBalance)
{
return false;
}
bool oksecondAssetBalance = m.to_bytes(secondAssetBalance);
if (!oksecondAssetBalance)
{
return false;
}
bool oklpTokensTotalCap = m.to_bytes(lpTokensTotalCap);
if (!oklpTokensTotalCap)
{
return false;
}
bool okfirstReserve = m.to_bytes(firstReserve);
if (!okfirstReserve)
{
return false;
}
bool oksecondReserve = m.to_bytes(secondReserve);
if (!oksecondReserve)
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
m.count_size(id);
m.count_size(liquidityPoolAcount);
m.count_size(lpTokenAssetCode);
m.count_size(firstAssetBalance);
m.count_size(secondAssetBalance);
m.count_size(lpTokensTotalCap);
m.count_size(firstReserve);
m.count_size(secondReserve);
m.count_size(ext);
}
bool
LiquidityPoolEntry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<LiquidityPoolEntry const&>(other_abstract);return true
&& (id== other.id)
&& (liquidityPoolAcount== other.liquidityPoolAcount)
&& (lpTokenAssetCode== other.lpTokenAssetCode)
&& (firstAssetBalance== other.firstAssetBalance)
&& (secondAssetBalance== other.secondAssetBalance)
&& (lpTokensTotalCap== other.lpTokensTotalCap)
&& (firstReserve== other.firstReserve)
&& (secondReserve== other.secondReserve)
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
if (id < other.id) return true;
if (other.id < id) return false;
if (liquidityPoolAcount < other.liquidityPoolAcount) return true;
if (other.liquidityPoolAcount < liquidityPoolAcount) return false;
if (lpTokenAssetCode < other.lpTokenAssetCode) return true;
if (other.lpTokenAssetCode < lpTokenAssetCode) return false;
if (firstAssetBalance < other.firstAssetBalance) return true;
if (other.firstAssetBalance < firstAssetBalance) return false;
if (secondAssetBalance < other.secondAssetBalance) return true;
if (other.secondAssetBalance < secondAssetBalance) return false;
if (lpTokensTotalCap < other.lpTokensTotalCap) return true;
if (other.lpTokensTotalCap < lpTokensTotalCap) return false;
if (firstReserve < other.firstReserve) return true;
if (other.firstReserve < firstReserve) return false;
if (secondReserve < other.secondReserve) return true;
if (other.secondReserve < secondReserve) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}