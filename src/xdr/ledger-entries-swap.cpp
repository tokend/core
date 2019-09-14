#include "ledger-entries-swap.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
SwapEntry::from_bytes(xdr::unmarshaler& u) 
{
bool okswapID = u.from_bytes(swapID);
if (!okswapID)
{
return false;
}
bool oksecretHash = u.from_bytes(secretHash);
if (!oksecretHash)
{
return false;
}
bool oksourceAccount = u.from_bytes(sourceAccount);
if (!oksourceAccount)
{
return false;
}
bool oksourceBalance = u.from_bytes(sourceBalance);
if (!oksourceBalance)
{
return false;
}
bool okdestinationAccount = u.from_bytes(destinationAccount);
if (!okdestinationAccount)
{
return false;
}
bool okdestinationBalance = u.from_bytes(destinationBalance);
if (!okdestinationBalance)
{
return false;
}
bool okassetCode = u.from_bytes(assetCode);
if (!okassetCode)
{
return false;
}
bool okamount = u.from_bytes(amount);
if (!okamount)
{
return false;
}
bool okcreatedAt = u.from_bytes(createdAt);
if (!okcreatedAt)
{
return false;
}
bool oklockTime = u.from_bytes(lockTime);
if (!oklockTime)
{
return false;
}
bool okfee = u.from_bytes(fee);
if (!okfee)
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
SwapEntry::to_bytes(xdr::marshaler& m) const 
{
bool okswapID = m.to_bytes(swapID);
if (!okswapID)
{
return false;
}
bool oksecretHash = m.to_bytes(secretHash);
if (!oksecretHash)
{
return false;
}
bool oksourceAccount = m.to_bytes(sourceAccount);
if (!oksourceAccount)
{
return false;
}
bool oksourceBalance = m.to_bytes(sourceBalance);
if (!oksourceBalance)
{
return false;
}
bool okdestinationAccount = m.to_bytes(destinationAccount);
if (!okdestinationAccount)
{
return false;
}
bool okdestinationBalance = m.to_bytes(destinationBalance);
if (!okdestinationBalance)
{
return false;
}
bool okassetCode = m.to_bytes(assetCode);
if (!okassetCode)
{
return false;
}
bool okamount = m.to_bytes(amount);
if (!okamount)
{
return false;
}
bool okcreatedAt = m.to_bytes(createdAt);
if (!okcreatedAt)
{
return false;
}
bool oklockTime = m.to_bytes(lockTime);
if (!oklockTime)
{
return false;
}
bool okfee = m.to_bytes(fee);
if (!okfee)
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
SwapEntry::count_size(xdr::measurer& m) const 
{
m.count_size(swapID);
m.count_size(secretHash);
m.count_size(sourceAccount);
m.count_size(sourceBalance);
m.count_size(destinationAccount);
m.count_size(destinationBalance);
m.count_size(assetCode);
m.count_size(amount);
m.count_size(createdAt);
m.count_size(lockTime);
m.count_size(fee);
m.count_size(ext);
}
bool
SwapEntry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<SwapEntry const&>(other_abstract);return true
&& (swapID== other.swapID)
&& (secretHash== other.secretHash)
&& (sourceAccount== other.sourceAccount)
&& (sourceBalance== other.sourceBalance)
&& (destinationAccount== other.destinationAccount)
&& (destinationBalance== other.destinationBalance)
&& (assetCode== other.assetCode)
&& (amount== other.amount)
&& (createdAt== other.createdAt)
&& (lockTime== other.lockTime)
&& (fee== other.fee)
&& (ext== other.ext)
;}
bool
SwapEntry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<SwapEntry const&>(other_abstract);
if (swapID < other.swapID) return true;
if (other.swapID < swapID) return false;
if (secretHash < other.secretHash) return true;
if (other.secretHash < secretHash) return false;
if (sourceAccount < other.sourceAccount) return true;
if (other.sourceAccount < sourceAccount) return false;
if (sourceBalance < other.sourceBalance) return true;
if (other.sourceBalance < sourceBalance) return false;
if (destinationAccount < other.destinationAccount) return true;
if (other.destinationAccount < destinationAccount) return false;
if (destinationBalance < other.destinationBalance) return true;
if (other.destinationBalance < destinationBalance) return false;
if (assetCode < other.assetCode) return true;
if (other.assetCode < assetCode) return false;
if (amount < other.amount) return true;
if (other.amount < amount) return false;
if (createdAt < other.createdAt) return true;
if (other.createdAt < createdAt) return false;
if (lockTime < other.lockTime) return true;
if (other.lockTime < lockTime) return false;
if (fee < other.fee) return true;
if (other.fee < fee) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}