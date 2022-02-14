#include "operation-lp-add-liquidity.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
LPAddLiquidityOp::from_bytes(xdr::unmarshaler& u) 
{
bool okfirstAssetBalanceID = u.from_bytes(firstAssetBalanceID);
if (!okfirstAssetBalanceID)
{
return false;
}
bool oksecondAssetBalanceID = u.from_bytes(secondAssetBalanceID);
if (!oksecondAssetBalanceID)
{
return false;
}
bool okfirstAssetDesiredAmount = u.from_bytes(firstAssetDesiredAmount);
if (!okfirstAssetDesiredAmount)
{
return false;
}
bool oksecondAssetDesiredAmount = u.from_bytes(secondAssetDesiredAmount);
if (!oksecondAssetDesiredAmount)
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
LPAddLiquidityOp::to_bytes(xdr::marshaler& m) const 
{
bool okfirstAssetBalanceID = m.to_bytes(firstAssetBalanceID);
if (!okfirstAssetBalanceID)
{
return false;
}
bool oksecondAssetBalanceID = m.to_bytes(secondAssetBalanceID);
if (!oksecondAssetBalanceID)
{
return false;
}
bool okfirstAssetDesiredAmount = m.to_bytes(firstAssetDesiredAmount);
if (!okfirstAssetDesiredAmount)
{
return false;
}
bool oksecondAssetDesiredAmount = m.to_bytes(secondAssetDesiredAmount);
if (!oksecondAssetDesiredAmount)
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
LPAddLiquidityOp::count_size(xdr::measurer& m) const 
{
m.count_size(firstAssetBalanceID);
m.count_size(secondAssetBalanceID);
m.count_size(firstAssetDesiredAmount);
m.count_size(secondAssetDesiredAmount);
m.count_size(firstAssetMinAmount);
m.count_size(secondAssetMinAmount);
m.count_size(ext);
}
bool
LPAddLiquidityOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<LPAddLiquidityOp const&>(other_abstract);return true
&& (firstAssetBalanceID== other.firstAssetBalanceID)
&& (secondAssetBalanceID== other.secondAssetBalanceID)
&& (firstAssetDesiredAmount== other.firstAssetDesiredAmount)
&& (secondAssetDesiredAmount== other.secondAssetDesiredAmount)
&& (firstAssetMinAmount== other.firstAssetMinAmount)
&& (secondAssetMinAmount== other.secondAssetMinAmount)
&& (ext== other.ext)
;}
bool
LPAddLiquidityOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<LPAddLiquidityOp const&>(other_abstract);
if (firstAssetBalanceID < other.firstAssetBalanceID) return true;
if (other.firstAssetBalanceID < firstAssetBalanceID) return false;
if (secondAssetBalanceID < other.secondAssetBalanceID) return true;
if (other.secondAssetBalanceID < secondAssetBalanceID) return false;
if (firstAssetDesiredAmount < other.firstAssetDesiredAmount) return true;
if (other.firstAssetDesiredAmount < firstAssetDesiredAmount) return false;
if (secondAssetDesiredAmount < other.secondAssetDesiredAmount) return true;
if (other.secondAssetDesiredAmount < secondAssetDesiredAmount) return false;
if (firstAssetMinAmount < other.firstAssetMinAmount) return true;
if (other.firstAssetMinAmount < firstAssetMinAmount) return false;
if (secondAssetMinAmount < other.secondAssetMinAmount) return true;
if (other.secondAssetMinAmount < secondAssetMinAmount) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LPAddLiquiditySuccess::from_bytes(xdr::unmarshaler& u) 
{
bool okliquidityPoolID = u.from_bytes(liquidityPoolID);
if (!okliquidityPoolID)
{
return false;
}
bool oklpAccountID = u.from_bytes(lpAccountID);
if (!oklpAccountID)
{
return false;
}
bool okfirstAssetBalanceID = u.from_bytes(firstAssetBalanceID);
if (!okfirstAssetBalanceID)
{
return false;
}
bool oksecondAssetBalanceID = u.from_bytes(secondAssetBalanceID);
if (!oksecondAssetBalanceID)
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
bool oklpTokensBalanceID = u.from_bytes(lpTokensBalanceID);
if (!oklpTokensBalanceID)
{
return false;
}
bool oklpTokensAmount = u.from_bytes(lpTokensAmount);
if (!oklpTokensAmount)
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
LPAddLiquiditySuccess::to_bytes(xdr::marshaler& m) const 
{
bool okliquidityPoolID = m.to_bytes(liquidityPoolID);
if (!okliquidityPoolID)
{
return false;
}
bool oklpAccountID = m.to_bytes(lpAccountID);
if (!oklpAccountID)
{
return false;
}
bool okfirstAssetBalanceID = m.to_bytes(firstAssetBalanceID);
if (!okfirstAssetBalanceID)
{
return false;
}
bool oksecondAssetBalanceID = m.to_bytes(secondAssetBalanceID);
if (!oksecondAssetBalanceID)
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
bool oklpTokensBalanceID = m.to_bytes(lpTokensBalanceID);
if (!oklpTokensBalanceID)
{
return false;
}
bool oklpTokensAmount = m.to_bytes(lpTokensAmount);
if (!oklpTokensAmount)
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
LPAddLiquiditySuccess::count_size(xdr::measurer& m) const 
{
m.count_size(liquidityPoolID);
m.count_size(lpAccountID);
m.count_size(firstAssetBalanceID);
m.count_size(secondAssetBalanceID);
m.count_size(firstAssetAmount);
m.count_size(secondAssetAmount);
m.count_size(lpTokensBalanceID);
m.count_size(lpTokensAmount);
m.count_size(ext);
}
bool
LPAddLiquiditySuccess::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<LPAddLiquiditySuccess const&>(other_abstract);return true
&& (liquidityPoolID== other.liquidityPoolID)
&& (lpAccountID== other.lpAccountID)
&& (firstAssetBalanceID== other.firstAssetBalanceID)
&& (secondAssetBalanceID== other.secondAssetBalanceID)
&& (firstAssetAmount== other.firstAssetAmount)
&& (secondAssetAmount== other.secondAssetAmount)
&& (lpTokensBalanceID== other.lpTokensBalanceID)
&& (lpTokensAmount== other.lpTokensAmount)
&& (ext== other.ext)
;}
bool
LPAddLiquiditySuccess::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<LPAddLiquiditySuccess const&>(other_abstract);
if (liquidityPoolID < other.liquidityPoolID) return true;
if (other.liquidityPoolID < liquidityPoolID) return false;
if (lpAccountID < other.lpAccountID) return true;
if (other.lpAccountID < lpAccountID) return false;
if (firstAssetBalanceID < other.firstAssetBalanceID) return true;
if (other.firstAssetBalanceID < firstAssetBalanceID) return false;
if (secondAssetBalanceID < other.secondAssetBalanceID) return true;
if (other.secondAssetBalanceID < secondAssetBalanceID) return false;
if (firstAssetAmount < other.firstAssetAmount) return true;
if (other.firstAssetAmount < firstAssetAmount) return false;
if (secondAssetAmount < other.secondAssetAmount) return true;
if (other.secondAssetAmount < secondAssetAmount) return false;
if (lpTokensBalanceID < other.lpTokensBalanceID) return true;
if (other.lpTokensBalanceID < lpTokensBalanceID) return false;
if (lpTokensAmount < other.lpTokensAmount) return true;
if (other.lpTokensAmount < lpTokensAmount) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LPAddLiquidityResult::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (code_)
{
  case (int32_t)LPAddLiquidityResultCode::SUCCESS:
return u.from_bytes(success_);
  default:
  
  return true;
}
return false;
}
bool
LPAddLiquidityResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)LPAddLiquidityResultCode::SUCCESS:
return m.to_bytes(success_);
  default:
    return true;
}
return false;
}
void
LPAddLiquidityResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)LPAddLiquidityResultCode::SUCCESS:
return m.count_size(success_);
  default:
  
  return;
}
}
bool
LPAddLiquidityResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<LPAddLiquidityResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)LPAddLiquidityResultCode::SUCCESS:
return success_ == other.success_;
  default:
  
  return true;
}
return false;
}
bool
LPAddLiquidityResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<LPAddLiquidityResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)LPAddLiquidityResultCode::SUCCESS:
return success_ < other.success_;
  default:
    return false;
}
return false;
}
}