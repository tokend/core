#include "operation-lp-swap.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
LPSwapOp::_lpSwapRequest_t::_swapExactOutTokensForInTokens_t::from_bytes(xdr::unmarshaler& u) 
{
bool okamountInMax = u.from_bytes(amountInMax);
if (!okamountInMax)
{
return false;
}
bool okamountOut = u.from_bytes(amountOut);
if (!okamountOut)
{
return false;
}
return true;
}
bool
LPSwapOp::_lpSwapRequest_t::_swapExactOutTokensForInTokens_t::to_bytes(xdr::marshaler& m) const 
{
bool okamountInMax = m.to_bytes(amountInMax);
if (!okamountInMax)
{
return false;
}
bool okamountOut = m.to_bytes(amountOut);
if (!okamountOut)
{
return false;
}
return true;
}
void
LPSwapOp::_lpSwapRequest_t::_swapExactOutTokensForInTokens_t::count_size(xdr::measurer& m) const 
{
m.count_size(amountInMax);
m.count_size(amountOut);
}
bool
LPSwapOp::_lpSwapRequest_t::_swapExactOutTokensForInTokens_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_swapExactOutTokensForInTokens_t const&>(other_abstract);return true
&& (amountInMax== other.amountInMax)
&& (amountOut== other.amountOut)
;}
bool
LPSwapOp::_lpSwapRequest_t::_swapExactOutTokensForInTokens_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_swapExactOutTokensForInTokens_t const&>(other_abstract);
if (amountInMax < other.amountInMax) return true;
if (other.amountInMax < amountInMax) return false;
if (amountOut < other.amountOut) return true;
if (other.amountOut < amountOut) return false;
return false;
}bool
LPSwapOp::_lpSwapRequest_t::_swapExactInTokensForOutTokens_t::from_bytes(xdr::unmarshaler& u) 
{
bool okamountIn = u.from_bytes(amountIn);
if (!okamountIn)
{
return false;
}
bool okamountOutMin = u.from_bytes(amountOutMin);
if (!okamountOutMin)
{
return false;
}
return true;
}
bool
LPSwapOp::_lpSwapRequest_t::_swapExactInTokensForOutTokens_t::to_bytes(xdr::marshaler& m) const 
{
bool okamountIn = m.to_bytes(amountIn);
if (!okamountIn)
{
return false;
}
bool okamountOutMin = m.to_bytes(amountOutMin);
if (!okamountOutMin)
{
return false;
}
return true;
}
void
LPSwapOp::_lpSwapRequest_t::_swapExactInTokensForOutTokens_t::count_size(xdr::measurer& m) const 
{
m.count_size(amountIn);
m.count_size(amountOutMin);
}
bool
LPSwapOp::_lpSwapRequest_t::_swapExactInTokensForOutTokens_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_swapExactInTokensForOutTokens_t const&>(other_abstract);return true
&& (amountIn== other.amountIn)
&& (amountOutMin== other.amountOutMin)
;}
bool
LPSwapOp::_lpSwapRequest_t::_swapExactInTokensForOutTokens_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_swapExactInTokensForOutTokens_t const&>(other_abstract);
if (amountIn < other.amountIn) return true;
if (other.amountIn < amountIn) return false;
if (amountOutMin < other.amountOutMin) return true;
if (other.amountOutMin < amountOutMin) return false;
return false;
}bool
LPSwapOp::_lpSwapRequest_t::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (type_)
{
    case (int32_t)LPSwapType::EXACT_OUT_TOKENS_FOR_IN_TOKENS:
return u.from_bytes(swapExactOutTokensForInTokens_);
    case (int32_t)LPSwapType::EXACT_IN_TOKENS_FOR_OUT_TOKENS:
return u.from_bytes(swapExactInTokensForOutTokens_);
}
return false;
}
bool
LPSwapOp::_lpSwapRequest_t::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(type_);
if (!ok)
{
return false;
}
switch (type_)
{

    case (int32_t)LPSwapType::EXACT_OUT_TOKENS_FOR_IN_TOKENS:
return m.to_bytes(swapExactOutTokensForInTokens_);
    case (int32_t)LPSwapType::EXACT_IN_TOKENS_FOR_OUT_TOKENS:
return m.to_bytes(swapExactInTokensForOutTokens_);
}
return false;
}
void
LPSwapOp::_lpSwapRequest_t::count_size(xdr::measurer& m) const
{
m.count_size(type_);
switch (type_)
{

    case (int32_t)LPSwapType::EXACT_OUT_TOKENS_FOR_IN_TOKENS:
return m.count_size(swapExactOutTokensForInTokens_);
    case (int32_t)LPSwapType::EXACT_IN_TOKENS_FOR_OUT_TOKENS:
return m.count_size(swapExactInTokensForOutTokens_);
}
}
bool
LPSwapOp::_lpSwapRequest_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_lpSwapRequest_t const&>(other_abstract);
if (other.type_ != type_) return false;
switch (type_)
{
    case (int32_t)LPSwapType::EXACT_OUT_TOKENS_FOR_IN_TOKENS:
return swapExactOutTokensForInTokens_ == other.swapExactOutTokensForInTokens_;
    case (int32_t)LPSwapType::EXACT_IN_TOKENS_FOR_OUT_TOKENS:
return swapExactInTokensForOutTokens_ == other.swapExactInTokensForOutTokens_;
}
return false;
}
bool
LPSwapOp::_lpSwapRequest_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_lpSwapRequest_t const&>(other_abstract);
if (type_ < other.type_) return true;
if (other.type_ < type_) return false;
switch (type_)
{
    case (int32_t)LPSwapType::EXACT_OUT_TOKENS_FOR_IN_TOKENS:
return swapExactOutTokensForInTokens_ < other.swapExactOutTokensForInTokens_;
    case (int32_t)LPSwapType::EXACT_IN_TOKENS_FOR_OUT_TOKENS:
return swapExactInTokensForOutTokens_ < other.swapExactInTokensForOutTokens_;
}
return false;
}
bool
LPSwapOp::from_bytes(xdr::unmarshaler& u) 
{
bool okfromBalance = u.from_bytes(fromBalance);
if (!okfromBalance)
{
return false;
}
bool oktoBalance = u.from_bytes(toBalance);
if (!oktoBalance)
{
return false;
}
bool oklpSwapRequest = u.from_bytes(lpSwapRequest);
if (!oklpSwapRequest)
{
return false;
}
bool okfeeData = u.from_bytes(feeData);
if (!okfeeData)
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
LPSwapOp::to_bytes(xdr::marshaler& m) const 
{
bool okfromBalance = m.to_bytes(fromBalance);
if (!okfromBalance)
{
return false;
}
bool oktoBalance = m.to_bytes(toBalance);
if (!oktoBalance)
{
return false;
}
bool oklpSwapRequest = m.to_bytes(lpSwapRequest);
if (!oklpSwapRequest)
{
return false;
}
bool okfeeData = m.to_bytes(feeData);
if (!okfeeData)
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
LPSwapOp::count_size(xdr::measurer& m) const 
{
m.count_size(fromBalance);
m.count_size(toBalance);
m.count_size(lpSwapRequest);
m.count_size(feeData);
m.count_size(ext);
}
bool
LPSwapOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<LPSwapOp const&>(other_abstract);return true
&& (fromBalance== other.fromBalance)
&& (toBalance== other.toBalance)
&& (lpSwapRequest== other.lpSwapRequest)
&& (feeData== other.feeData)
&& (ext== other.ext)
;}
bool
LPSwapOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<LPSwapOp const&>(other_abstract);
if (fromBalance < other.fromBalance) return true;
if (other.fromBalance < fromBalance) return false;
if (toBalance < other.toBalance) return true;
if (other.toBalance < toBalance) return false;
if (lpSwapRequest < other.lpSwapRequest) return true;
if (other.lpSwapRequest < lpSwapRequest) return false;
if (feeData < other.feeData) return true;
if (other.feeData < feeData) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LPSwapSuccess::from_bytes(xdr::unmarshaler& u) 
{
bool okliquidityPoolID = u.from_bytes(liquidityPoolID);
if (!okliquidityPoolID)
{
return false;
}
bool okpoolAccount = u.from_bytes(poolAccount);
if (!okpoolAccount)
{
return false;
}
bool oklpInBalanceID = u.from_bytes(lpInBalanceID);
if (!oklpInBalanceID)
{
return false;
}
bool oklpOutBalanceID = u.from_bytes(lpOutBalanceID);
if (!oklpOutBalanceID)
{
return false;
}
bool oksourceInBalanceID = u.from_bytes(sourceInBalanceID);
if (!oksourceInBalanceID)
{
return false;
}
bool oksourceOutBalanceID = u.from_bytes(sourceOutBalanceID);
if (!oksourceOutBalanceID)
{
return false;
}
bool okswapInAmount = u.from_bytes(swapInAmount);
if (!okswapInAmount)
{
return false;
}
bool okswapOutAmount = u.from_bytes(swapOutAmount);
if (!okswapOutAmount)
{
return false;
}
bool okactualSourcePaymentFee = u.from_bytes(actualSourcePaymentFee);
if (!okactualSourcePaymentFee)
{
return false;
}
bool okactualDestinationPaymentFee = u.from_bytes(actualDestinationPaymentFee);
if (!okactualDestinationPaymentFee)
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
LPSwapSuccess::to_bytes(xdr::marshaler& m) const 
{
bool okliquidityPoolID = m.to_bytes(liquidityPoolID);
if (!okliquidityPoolID)
{
return false;
}
bool okpoolAccount = m.to_bytes(poolAccount);
if (!okpoolAccount)
{
return false;
}
bool oklpInBalanceID = m.to_bytes(lpInBalanceID);
if (!oklpInBalanceID)
{
return false;
}
bool oklpOutBalanceID = m.to_bytes(lpOutBalanceID);
if (!oklpOutBalanceID)
{
return false;
}
bool oksourceInBalanceID = m.to_bytes(sourceInBalanceID);
if (!oksourceInBalanceID)
{
return false;
}
bool oksourceOutBalanceID = m.to_bytes(sourceOutBalanceID);
if (!oksourceOutBalanceID)
{
return false;
}
bool okswapInAmount = m.to_bytes(swapInAmount);
if (!okswapInAmount)
{
return false;
}
bool okswapOutAmount = m.to_bytes(swapOutAmount);
if (!okswapOutAmount)
{
return false;
}
bool okactualSourcePaymentFee = m.to_bytes(actualSourcePaymentFee);
if (!okactualSourcePaymentFee)
{
return false;
}
bool okactualDestinationPaymentFee = m.to_bytes(actualDestinationPaymentFee);
if (!okactualDestinationPaymentFee)
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
LPSwapSuccess::count_size(xdr::measurer& m) const 
{
m.count_size(liquidityPoolID);
m.count_size(poolAccount);
m.count_size(lpInBalanceID);
m.count_size(lpOutBalanceID);
m.count_size(sourceInBalanceID);
m.count_size(sourceOutBalanceID);
m.count_size(swapInAmount);
m.count_size(swapOutAmount);
m.count_size(actualSourcePaymentFee);
m.count_size(actualDestinationPaymentFee);
m.count_size(ext);
}
bool
LPSwapSuccess::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<LPSwapSuccess const&>(other_abstract);return true
&& (liquidityPoolID== other.liquidityPoolID)
&& (poolAccount== other.poolAccount)
&& (lpInBalanceID== other.lpInBalanceID)
&& (lpOutBalanceID== other.lpOutBalanceID)
&& (sourceInBalanceID== other.sourceInBalanceID)
&& (sourceOutBalanceID== other.sourceOutBalanceID)
&& (swapInAmount== other.swapInAmount)
&& (swapOutAmount== other.swapOutAmount)
&& (actualSourcePaymentFee== other.actualSourcePaymentFee)
&& (actualDestinationPaymentFee== other.actualDestinationPaymentFee)
&& (ext== other.ext)
;}
bool
LPSwapSuccess::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<LPSwapSuccess const&>(other_abstract);
if (liquidityPoolID < other.liquidityPoolID) return true;
if (other.liquidityPoolID < liquidityPoolID) return false;
if (poolAccount < other.poolAccount) return true;
if (other.poolAccount < poolAccount) return false;
if (lpInBalanceID < other.lpInBalanceID) return true;
if (other.lpInBalanceID < lpInBalanceID) return false;
if (lpOutBalanceID < other.lpOutBalanceID) return true;
if (other.lpOutBalanceID < lpOutBalanceID) return false;
if (sourceInBalanceID < other.sourceInBalanceID) return true;
if (other.sourceInBalanceID < sourceInBalanceID) return false;
if (sourceOutBalanceID < other.sourceOutBalanceID) return true;
if (other.sourceOutBalanceID < sourceOutBalanceID) return false;
if (swapInAmount < other.swapInAmount) return true;
if (other.swapInAmount < swapInAmount) return false;
if (swapOutAmount < other.swapOutAmount) return true;
if (other.swapOutAmount < swapOutAmount) return false;
if (actualSourcePaymentFee < other.actualSourcePaymentFee) return true;
if (other.actualSourcePaymentFee < actualSourcePaymentFee) return false;
if (actualDestinationPaymentFee < other.actualDestinationPaymentFee) return true;
if (other.actualDestinationPaymentFee < actualDestinationPaymentFee) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LPSwapResult::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (code_)
{
  case (int32_t)LPSwapResultCode::SUCCESS:
return u.from_bytes(success_);
  default:
  
  return true;
}
return false;
}
bool
LPSwapResult::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(code_);
if (!ok)
{
return false;
}
switch (code_)
{

  case (int32_t)LPSwapResultCode::SUCCESS:
return m.to_bytes(success_);
  default:
    return true;
}
return false;
}
void
LPSwapResult::count_size(xdr::measurer& m) const
{
m.count_size(code_);
switch (code_)
{

  case (int32_t)LPSwapResultCode::SUCCESS:
return m.count_size(success_);
  default:
  
  return;
}
}
bool
LPSwapResult::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<LPSwapResult const&>(other_abstract);
if (other.code_ != code_) return false;
switch (code_)
{
  case (int32_t)LPSwapResultCode::SUCCESS:
return success_ == other.success_;
  default:
  
  return true;
}
return false;
}
bool
LPSwapResult::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<LPSwapResult const&>(other_abstract);
if (code_ < other.code_) return true;
if (other.code_ < code_) return false;
switch (code_)
{
  case (int32_t)LPSwapResultCode::SUCCESS:
return success_ < other.success_;
  default:
    return false;
}
return false;
}
}