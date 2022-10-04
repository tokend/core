#include "operation-lp-remove-liquidity.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
LPRemoveLiquidityOp::from_bytes(xdr::unmarshaler& u) 
{
bool oklpTokenBalance = u.from_bytes(lpTokenBalance);
if (!oklpTokenBalance)
{
return false;
}
bool oklpTokensAmount = u.from_bytes(lpTokensAmount);
if (!oklpTokensAmount)
{
return false;
}
bool okfirstAssetMinAmount = u.from_bytes(firstAssetMinAmount);
if (!okfirstAssetMinAmount)
{
return false;
}
bool oksecondAssetMinAmount = u.from_bytes(secondAssetMinAmount);
if (!oksecondAssetMinAmount)
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
LPRemoveLiquidityOp::to_bytes(xdr::marshaler& m) const 
{
bool oklpTokenBalance = m.to_bytes(lpTokenBalance);
if (!oklpTokenBalance)
{
return false;
}
bool oklpTokensAmount = m.to_bytes(lpTokensAmount);
if (!oklpTokensAmount)
{
return false;
}
bool okfirstAssetMinAmount = m.to_bytes(firstAssetMinAmount);
if (!okfirstAssetMinAmount)
{
return false;
}
bool oksecondAssetMinAmount = m.to_bytes(secondAssetMinAmount);
if (!oksecondAssetMinAmount)
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
LPRemoveLiquidityOp::count_size(xdr::measurer& m) const 
{
m.count_size(lpTokenBalance);
m.count_size(lpTokensAmount);
m.count_size(firstAssetMinAmount);
m.count_size(secondAssetMinAmount);
m.count_size(ext);
}
bool
LPRemoveLiquidityOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<LPRemoveLiquidityOp const&>(other_abstract);return true
&& (lpTokenBalance== other.lpTokenBalance)
&& (lpTokensAmount== other.lpTokensAmount)
&& (firstAssetMinAmount== other.firstAssetMinAmount)
&& (secondAssetMinAmount== other.secondAssetMinAmount)
&& (ext== other.ext)
;}
bool
LPRemoveLiquidityOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<LPRemoveLiquidityOp const&>(other_abstract);
if (lpTokenBalance < other.lpTokenBalance) return true;
if (other.lpTokenBalance < lpTokenBalance) return false;
if (lpTokensAmount < other.lpTokensAmount) return true;
if (other.lpTokensAmount < lpTokensAmount) return false;
if (firstAssetMinAmount < other.firstAssetMinAmount) return true;
if (other.firstAssetMinAmount < firstAssetMinAmount) return false;
if (secondAssetMinAmount < other.secondAssetMinAmount) return true;
if (other.secondAssetMinAmount < secondAssetMinAmount) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LPRemoveLiquiditySuccess::from_bytes(xdr::unmarshaler& u) 
{
bool okliquidityPoolID = u.from_bytes(liquidityPoolID);
if (!okliquidityPoolID)
{
return false;
}
bool oklpFirstAssetBalanceID = u.from_bytes(lpFirstAssetBalanceID);
if (!oklpFirstAssetBalanceID)
{
return false;
}
bool oklpSecondAssetBalanceID = u.from_bytes(lpSecondAssetBalanceID);
if (!oklpSecondAssetBalanceID)
{
return false;
}
bool oksourceFirstAssetBalanceID = u.from_bytes(sourceFirstAssetBalanceID);
if (!oksourceFirstAssetBalanceID)
{
return false;
}
bool oksourceSecondAssetBalanceID = u.from_bytes(sourceSecondAssetBalanceID);
if (!oksourceSecondAssetBalanceID)
{
return false;
}
bool okfirstAssetAmount = u.from_bytes(firstAssetAmount);
if (!okfirstAssetAmount)
{
return false;
}
bool oksecondAssetAmount = u.from_bytes(secondAssetAmount);
if (!oksecondAssetAmount)
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
LPRemoveLiquiditySuccess::to_bytes(xdr::marshaler& m) const 
{
bool okliquidityPoolID = m.to_bytes(liquidityPoolID);
if (!okliquidityPoolID)
{
return false;
}
bool oklpFirstAssetBalanceID = m.to_bytes(lpFirstAssetBalanceID);
if (!oklpFirstAssetBalanceID)
{
return false;
}
bool oklpSecondAssetBalanceID = m.to_bytes(lpSecondAssetBalanceID);
if (!oklpSecondAssetBalanceID)
{
return false;
}
bool oksourceFirstAssetBalanceID = m.to_bytes(sourceFirstAssetBalanceID);
if (!oksourceFirstAssetBalanceID)
{
return false;
}
bool oksourceSecondAssetBalanceID = m.to_bytes(sourceSecondAssetBalanceID);
if (!oksourceSecondAssetBalanceID)
{
return false;
}
bool okfirstAssetAmount = m.to_bytes(firstAssetAmount);
if (!okfirstAssetAmount)
{
return false;
}
bool oksecondAssetAmount = m.to_bytes(secondAssetAmount);
if (!oksecondAssetAmount)
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
LPRemoveLiquiditySuccess::count_size(xdr::measurer& m) const 
{
m.count_size(liquidityPoolID);
m.count_size(lpFirstAssetBalanceID);
m.count_size(lpSecondAssetBalanceID);
m.count_size(sourceFirstAssetBalanceID);
m.count_size(sourceSecondAssetBalanceID);
m.count_size(firstAssetAmount);
m.count_size(secondAssetAmount);
m.count_size(ext);
}
bool
LPRemoveLiquiditySuccess::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<LPRemoveLiquiditySuccess const&>(other_abstract);return true
&& (liquidityPoolID== other.liquidityPoolID)
&& (lpFirstAssetBalanceID== other.lpFirstAssetBalanceID)
&& (lpSecondAssetBalanceID== other.lpSecondAssetBalanceID)
&& (sourceFirstAssetBalanceID== other.sourceFirstAssetBalanceID)
&& (sourceSecondAssetBalanceID== other.sourceSecondAssetBalanceID)
&& (firstAssetAmount== other.firstAssetAmount)
&& (secondAssetAmount== other.secondAssetAmount)
&& (ext== other.ext)
;}
bool
LPRemoveLiquiditySuccess::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<LPRemoveLiquiditySuccess const&>(other_abstract);
if (liquidityPoolID < other.liquidityPoolID) return true;
if (other.liquidityPoolID < liquidityPoolID) return false;
if (lpFirstAssetBalanceID < other.lpFirstAssetBalanceID) return true;
if (other.lpFirstAssetBalanceID < lpFirstAssetBalanceID) return false;
if (lpSecondAssetBalanceID < other.lpSecondAssetBalanceID) return true;
if (other.lpSecondAssetBalanceID < lpSecondAssetBalanceID) return false;
if (sourceFirstAssetBalanceID < other.sourceFirstAssetBalanceID) return true;
if (other.sourceFirstAssetBalanceID < sourceFirstAssetBalanceID) return false;
if (sourceSecondAssetBalanceID < other.sourceSecondAssetBalanceID) return true;
if (other.sourceSecondAssetBalanceID < sourceSecondAssetBalanceID) return false;
if (firstAssetAmount < other.firstAssetAmount) return true;
if (other.firstAssetAmount < firstAssetAmount) return false;
if (secondAssetAmount < other.secondAssetAmount) return true;
if (other.secondAssetAmount < secondAssetAmount) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LPRemoveLiquidityResult::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (code_)
{
  case (int32_t)LPRemoveLiquidityResultCode::SUCCESS:
return u.from_bytes(success_);
  default:
  
  return true;
}
return false;
}
bool
LPRemoveLiquidityResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)LPRemoveLiquidityResultCode::SUCCESS:
return m.to_bytes(success_);
  default:
    return true;
}
return false;
}
void
LPRemoveLiquidityResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)LPRemoveLiquidityResultCode::SUCCESS:
return m.count_size(success_);
  default:
  
  return;
}
}
bool
LPRemoveLiquidityResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<LPRemoveLiquidityResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)LPRemoveLiquidityResultCode::SUCCESS:
return success_ == other.success_;
  default:
  
  return true;
}
return false;
}
bool
LPRemoveLiquidityResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<LPRemoveLiquidityResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)LPRemoveLiquidityResultCode::SUCCESS:
return success_ < other.success_;
  default:
    return false;
}
return false;
}
}