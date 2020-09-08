#include "resource-signer-rule.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
SignerRuleResource::_reviewableRequest_t::from_bytes(xdr::unmarshaler& u) 
{
bool okdetails = u.from_bytes(details);
if (!okdetails)
{
return false;
}
bool oktasksToAdd = u.from_bytes(tasksToAdd);
if (!oktasksToAdd)
{
return false;
}
bool oktasksToRemove = u.from_bytes(tasksToRemove);
if (!oktasksToRemove)
{
return false;
}
bool okallTasks = u.from_bytes(allTasks);
if (!okallTasks)
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
SignerRuleResource::_reviewableRequest_t::to_bytes(xdr::marshaler& m) const 
{
bool okdetails = m.to_bytes(details);
if (!okdetails)
{
return false;
}
bool oktasksToAdd = m.to_bytes(tasksToAdd);
if (!oktasksToAdd)
{
return false;
}
bool oktasksToRemove = m.to_bytes(tasksToRemove);
if (!oktasksToRemove)
{
return false;
}
bool okallTasks = m.to_bytes(allTasks);
if (!okallTasks)
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
SignerRuleResource::_reviewableRequest_t::count_size(xdr::measurer& m) const 
{
m.count_size(details);
m.count_size(tasksToAdd);
m.count_size(tasksToRemove);
m.count_size(allTasks);
m.count_size(ext);
}
bool
SignerRuleResource::_reviewableRequest_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_reviewableRequest_t const&>(other_abstract);return true
&& (details== other.details)
&& (tasksToAdd== other.tasksToAdd)
&& (tasksToRemove== other.tasksToRemove)
&& (allTasks== other.allTasks)
&& (ext== other.ext)
;}
bool
SignerRuleResource::_reviewableRequest_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_reviewableRequest_t const&>(other_abstract);
if (details < other.details) return true;
if (other.details < details) return false;
if (tasksToAdd < other.tasksToAdd) return true;
if (other.tasksToAdd < tasksToAdd) return false;
if (tasksToRemove < other.tasksToRemove) return true;
if (other.tasksToRemove < tasksToRemove) return false;
if (allTasks < other.allTasks) return true;
if (other.allTasks < allTasks) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
SignerRuleResource::_asset_t::from_bytes(xdr::unmarshaler& u) 
{
bool okassetCode = u.from_bytes(assetCode);
if (!okassetCode)
{
return false;
}
bool okassetType = u.from_bytes(assetType);
if (!okassetType)
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
SignerRuleResource::_asset_t::to_bytes(xdr::marshaler& m) const 
{
bool okassetCode = m.to_bytes(assetCode);
if (!okassetCode)
{
return false;
}
bool okassetType = m.to_bytes(assetType);
if (!okassetType)
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
SignerRuleResource::_asset_t::count_size(xdr::measurer& m) const 
{
m.count_size(assetCode);
m.count_size(assetType);
m.count_size(ext);
}
bool
SignerRuleResource::_asset_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_asset_t const&>(other_abstract);return true
&& (assetCode== other.assetCode)
&& (assetType== other.assetType)
&& (ext== other.ext)
;}
bool
SignerRuleResource::_asset_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_asset_t const&>(other_abstract);
if (assetCode < other.assetCode) return true;
if (other.assetCode < assetCode) return false;
if (assetType < other.assetType) return true;
if (other.assetType < assetType) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
SignerRuleResource::_offer_t::from_bytes(xdr::unmarshaler& u) 
{
bool okbaseAssetType = u.from_bytes(baseAssetType);
if (!okbaseAssetType)
{
return false;
}
bool okquoteAssetType = u.from_bytes(quoteAssetType);
if (!okquoteAssetType)
{
return false;
}
bool okbaseAssetCode = u.from_bytes(baseAssetCode);
if (!okbaseAssetCode)
{
return false;
}
bool okquoteAssetCode = u.from_bytes(quoteAssetCode);
if (!okquoteAssetCode)
{
return false;
}
bool okisBuy = u.from_bytes(isBuy);
if (!okisBuy)
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
SignerRuleResource::_offer_t::to_bytes(xdr::marshaler& m) const 
{
bool okbaseAssetType = m.to_bytes(baseAssetType);
if (!okbaseAssetType)
{
return false;
}
bool okquoteAssetType = m.to_bytes(quoteAssetType);
if (!okquoteAssetType)
{
return false;
}
bool okbaseAssetCode = m.to_bytes(baseAssetCode);
if (!okbaseAssetCode)
{
return false;
}
bool okquoteAssetCode = m.to_bytes(quoteAssetCode);
if (!okquoteAssetCode)
{
return false;
}
bool okisBuy = m.to_bytes(isBuy);
if (!okisBuy)
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
SignerRuleResource::_offer_t::count_size(xdr::measurer& m) const 
{
m.count_size(baseAssetType);
m.count_size(quoteAssetType);
m.count_size(baseAssetCode);
m.count_size(quoteAssetCode);
m.count_size(isBuy);
m.count_size(ext);
}
bool
SignerRuleResource::_offer_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_offer_t const&>(other_abstract);return true
&& (baseAssetType== other.baseAssetType)
&& (quoteAssetType== other.quoteAssetType)
&& (baseAssetCode== other.baseAssetCode)
&& (quoteAssetCode== other.quoteAssetCode)
&& (isBuy== other.isBuy)
&& (ext== other.ext)
;}
bool
SignerRuleResource::_offer_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_offer_t const&>(other_abstract);
if (baseAssetType < other.baseAssetType) return true;
if (other.baseAssetType < baseAssetType) return false;
if (quoteAssetType < other.quoteAssetType) return true;
if (other.quoteAssetType < quoteAssetType) return false;
if (baseAssetCode < other.baseAssetCode) return true;
if (other.baseAssetCode < baseAssetCode) return false;
if (quoteAssetCode < other.quoteAssetCode) return true;
if (other.quoteAssetCode < quoteAssetCode) return false;
if (isBuy < other.isBuy) return true;
if (other.isBuy < isBuy) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
SignerRuleResource::_sale_t::from_bytes(xdr::unmarshaler& u) 
{
bool oksaleID = u.from_bytes(saleID);
if (!oksaleID)
{
return false;
}
bool oksaleType = u.from_bytes(saleType);
if (!oksaleType)
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
SignerRuleResource::_sale_t::to_bytes(xdr::marshaler& m) const 
{
bool oksaleID = m.to_bytes(saleID);
if (!oksaleID)
{
return false;
}
bool oksaleType = m.to_bytes(saleType);
if (!oksaleType)
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
SignerRuleResource::_sale_t::count_size(xdr::measurer& m) const 
{
m.count_size(saleID);
m.count_size(saleType);
m.count_size(ext);
}
bool
SignerRuleResource::_sale_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_sale_t const&>(other_abstract);return true
&& (saleID== other.saleID)
&& (saleType== other.saleType)
&& (ext== other.ext)
;}
bool
SignerRuleResource::_sale_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_sale_t const&>(other_abstract);
if (saleID < other.saleID) return true;
if (other.saleID < saleID) return false;
if (saleType < other.saleType) return true;
if (other.saleType < saleType) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
SignerRuleResource::_atomicSwapAsk_t::from_bytes(xdr::unmarshaler& u) 
{
bool okassetType = u.from_bytes(assetType);
if (!okassetType)
{
return false;
}
bool okassetCode = u.from_bytes(assetCode);
if (!okassetCode)
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
SignerRuleResource::_atomicSwapAsk_t::to_bytes(xdr::marshaler& m) const 
{
bool okassetType = m.to_bytes(assetType);
if (!okassetType)
{
return false;
}
bool okassetCode = m.to_bytes(assetCode);
if (!okassetCode)
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
SignerRuleResource::_atomicSwapAsk_t::count_size(xdr::measurer& m) const 
{
m.count_size(assetType);
m.count_size(assetCode);
m.count_size(ext);
}
bool
SignerRuleResource::_atomicSwapAsk_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_atomicSwapAsk_t const&>(other_abstract);return true
&& (assetType== other.assetType)
&& (assetCode== other.assetCode)
&& (ext== other.ext)
;}
bool
SignerRuleResource::_atomicSwapAsk_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_atomicSwapAsk_t const&>(other_abstract);
if (assetType < other.assetType) return true;
if (other.assetType < assetType) return false;
if (assetCode < other.assetCode) return true;
if (other.assetCode < assetCode) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
SignerRuleResource::_signerRule_t::from_bytes(xdr::unmarshaler& u) 
{
bool okisDefault = u.from_bytes(isDefault);
if (!okisDefault)
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
SignerRuleResource::_signerRule_t::to_bytes(xdr::marshaler& m) const 
{
bool okisDefault = m.to_bytes(isDefault);
if (!okisDefault)
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
SignerRuleResource::_signerRule_t::count_size(xdr::measurer& m) const 
{
m.count_size(isDefault);
m.count_size(ext);
}
bool
SignerRuleResource::_signerRule_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_signerRule_t const&>(other_abstract);return true
&& (isDefault== other.isDefault)
&& (ext== other.ext)
;}
bool
SignerRuleResource::_signerRule_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_signerRule_t const&>(other_abstract);
if (isDefault < other.isDefault) return true;
if (other.isDefault < isDefault) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
SignerRuleResource::_signerRole_t::from_bytes(xdr::unmarshaler& u) 
{
bool okroleID = u.from_bytes(roleID);
if (!okroleID)
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
SignerRuleResource::_signerRole_t::to_bytes(xdr::marshaler& m) const 
{
bool okroleID = m.to_bytes(roleID);
if (!okroleID)
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
SignerRuleResource::_signerRole_t::count_size(xdr::measurer& m) const 
{
m.count_size(roleID);
m.count_size(ext);
}
bool
SignerRuleResource::_signerRole_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_signerRole_t const&>(other_abstract);return true
&& (roleID== other.roleID)
&& (ext== other.ext)
;}
bool
SignerRuleResource::_signerRole_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_signerRole_t const&>(other_abstract);
if (roleID < other.roleID) return true;
if (other.roleID < roleID) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
SignerRuleResource::_signer_t::from_bytes(xdr::unmarshaler& u) 
{
bool okroleID = u.from_bytes(roleID);
if (!okroleID)
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
SignerRuleResource::_signer_t::to_bytes(xdr::marshaler& m) const 
{
bool okroleID = m.to_bytes(roleID);
if (!okroleID)
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
SignerRuleResource::_signer_t::count_size(xdr::measurer& m) const 
{
m.count_size(roleID);
m.count_size(ext);
}
bool
SignerRuleResource::_signer_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_signer_t const&>(other_abstract);return true
&& (roleID== other.roleID)
&& (ext== other.ext)
;}
bool
SignerRuleResource::_signer_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_signer_t const&>(other_abstract);
if (roleID < other.roleID) return true;
if (other.roleID < roleID) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
SignerRuleResource::_keyValue_t::from_bytes(xdr::unmarshaler& u) 
{
bool okkeyPrefix = u.from_bytes(keyPrefix);
if (!okkeyPrefix)
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
SignerRuleResource::_keyValue_t::to_bytes(xdr::marshaler& m) const 
{
bool okkeyPrefix = m.to_bytes(keyPrefix);
if (!okkeyPrefix)
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
SignerRuleResource::_keyValue_t::count_size(xdr::measurer& m) const 
{
m.count_size(keyPrefix);
m.count_size(ext);
}
bool
SignerRuleResource::_keyValue_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_keyValue_t const&>(other_abstract);return true
&& (keyPrefix== other.keyPrefix)
&& (ext== other.ext)
;}
bool
SignerRuleResource::_keyValue_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_keyValue_t const&>(other_abstract);
if (keyPrefix < other.keyPrefix) return true;
if (other.keyPrefix < keyPrefix) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
SignerRuleResource::_poll_t::from_bytes(xdr::unmarshaler& u) 
{
bool okpollID = u.from_bytes(pollID);
if (!okpollID)
{
return false;
}
bool okpermissionType = u.from_bytes(permissionType);
if (!okpermissionType)
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
SignerRuleResource::_poll_t::to_bytes(xdr::marshaler& m) const 
{
bool okpollID = m.to_bytes(pollID);
if (!okpollID)
{
return false;
}
bool okpermissionType = m.to_bytes(permissionType);
if (!okpermissionType)
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
SignerRuleResource::_poll_t::count_size(xdr::measurer& m) const 
{
m.count_size(pollID);
m.count_size(permissionType);
m.count_size(ext);
}
bool
SignerRuleResource::_poll_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_poll_t const&>(other_abstract);return true
&& (pollID== other.pollID)
&& (permissionType== other.permissionType)
&& (ext== other.ext)
;}
bool
SignerRuleResource::_poll_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_poll_t const&>(other_abstract);
if (pollID < other.pollID) return true;
if (other.pollID < pollID) return false;
if (permissionType < other.permissionType) return true;
if (other.permissionType < permissionType) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
SignerRuleResource::_vote_t::from_bytes(xdr::unmarshaler& u) 
{
bool okpollID = u.from_bytes(pollID);
if (!okpollID)
{
return false;
}
bool okpermissionType = u.from_bytes(permissionType);
if (!okpermissionType)
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
SignerRuleResource::_vote_t::to_bytes(xdr::marshaler& m) const 
{
bool okpollID = m.to_bytes(pollID);
if (!okpollID)
{
return false;
}
bool okpermissionType = m.to_bytes(permissionType);
if (!okpermissionType)
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
SignerRuleResource::_vote_t::count_size(xdr::measurer& m) const 
{
m.count_size(pollID);
m.count_size(permissionType);
m.count_size(ext);
}
bool
SignerRuleResource::_vote_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_vote_t const&>(other_abstract);return true
&& (pollID== other.pollID)
&& (permissionType== other.permissionType)
&& (ext== other.ext)
;}
bool
SignerRuleResource::_vote_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_vote_t const&>(other_abstract);
if (pollID < other.pollID) return true;
if (other.pollID < pollID) return false;
if (permissionType < other.permissionType) return true;
if (other.permissionType < permissionType) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
SignerRuleResource::_initiateKYCRecovery_t::from_bytes(xdr::unmarshaler& u) 
{
bool okroleID = u.from_bytes(roleID);
if (!okroleID)
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
SignerRuleResource::_initiateKYCRecovery_t::to_bytes(xdr::marshaler& m) const 
{
bool okroleID = m.to_bytes(roleID);
if (!okroleID)
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
SignerRuleResource::_initiateKYCRecovery_t::count_size(xdr::measurer& m) const 
{
m.count_size(roleID);
m.count_size(ext);
}
bool
SignerRuleResource::_initiateKYCRecovery_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_initiateKYCRecovery_t const&>(other_abstract);return true
&& (roleID== other.roleID)
&& (ext== other.ext)
;}
bool
SignerRuleResource::_initiateKYCRecovery_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_initiateKYCRecovery_t const&>(other_abstract);
if (roleID < other.roleID) return true;
if (other.roleID < roleID) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
SignerRuleResource::_accountSpecificRuleExt_t::_accountSpecificRule_t::from_bytes(xdr::unmarshaler& u) 
{
bool okledgerKey = u.from_bytes(ledgerKey);
if (!okledgerKey)
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
SignerRuleResource::_accountSpecificRuleExt_t::_accountSpecificRule_t::to_bytes(xdr::marshaler& m) const 
{
bool okledgerKey = m.to_bytes(ledgerKey);
if (!okledgerKey)
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
SignerRuleResource::_accountSpecificRuleExt_t::_accountSpecificRule_t::count_size(xdr::measurer& m) const 
{
m.count_size(ledgerKey);
m.count_size(ext);
}
bool
SignerRuleResource::_accountSpecificRuleExt_t::_accountSpecificRule_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_accountSpecificRule_t const&>(other_abstract);return true
&& (ledgerKey== other.ledgerKey)
&& (ext== other.ext)
;}
bool
SignerRuleResource::_accountSpecificRuleExt_t::_accountSpecificRule_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_accountSpecificRule_t const&>(other_abstract);
if (ledgerKey < other.ledgerKey) return true;
if (other.ledgerKey < ledgerKey) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
SignerRuleResource::_accountSpecificRuleExt_t::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return true;
    case (int32_t)LedgerVersion::ADD_ACC_SPECIFIC_RULE_RESOURCE:
return u.from_bytes(accountSpecificRule_);
}
return false;
}
bool
SignerRuleResource::_accountSpecificRuleExt_t::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(v_);
if (!ok)
{
return false;
}
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
      return true;
    case (int32_t)LedgerVersion::ADD_ACC_SPECIFIC_RULE_RESOURCE:
return m.to_bytes(accountSpecificRule_);
}
return false;
}
void
SignerRuleResource::_accountSpecificRuleExt_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
    case (int32_t)LedgerVersion::ADD_ACC_SPECIFIC_RULE_RESOURCE:
return m.count_size(accountSpecificRule_);
}
}
bool
SignerRuleResource::_accountSpecificRuleExt_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_accountSpecificRuleExt_t const&>(other_abstract);
if (other.v_ != v_) return false;
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return true;
    case (int32_t)LedgerVersion::ADD_ACC_SPECIFIC_RULE_RESOURCE:
return accountSpecificRule_ == other.accountSpecificRule_;
}
return false;
}
bool
SignerRuleResource::_accountSpecificRuleExt_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_accountSpecificRuleExt_t const&>(other_abstract);
if (v_ < other.v_) return true;
if (other.v_ < v_) return false;
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
      return false;
    case (int32_t)LedgerVersion::ADD_ACC_SPECIFIC_RULE_RESOURCE:
return accountSpecificRule_ < other.accountSpecificRule_;
}
return false;
}
bool
SignerRuleResource::_swap_t::from_bytes(xdr::unmarshaler& u) 
{
bool okassetCode = u.from_bytes(assetCode);
if (!okassetCode)
{
return false;
}
bool okassetType = u.from_bytes(assetType);
if (!okassetType)
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
SignerRuleResource::_swap_t::to_bytes(xdr::marshaler& m) const 
{
bool okassetCode = m.to_bytes(assetCode);
if (!okassetCode)
{
return false;
}
bool okassetType = m.to_bytes(assetType);
if (!okassetType)
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
SignerRuleResource::_swap_t::count_size(xdr::measurer& m) const 
{
m.count_size(assetCode);
m.count_size(assetType);
m.count_size(ext);
}
bool
SignerRuleResource::_swap_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_swap_t const&>(other_abstract);return true
&& (assetCode== other.assetCode)
&& (assetType== other.assetType)
&& (ext== other.ext)
;}
bool
SignerRuleResource::_swap_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_swap_t const&>(other_abstract);
if (assetCode < other.assetCode) return true;
if (other.assetCode < assetCode) return false;
if (assetType < other.assetType) return true;
if (other.assetType < assetType) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
SignerRuleResource::_data_t::from_bytes(xdr::unmarshaler& u) 
{
bool oktype = u.from_bytes(type);
if (!oktype)
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
SignerRuleResource::_data_t::to_bytes(xdr::marshaler& m) const 
{
bool oktype = m.to_bytes(type);
if (!oktype)
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
SignerRuleResource::_data_t::count_size(xdr::measurer& m) const 
{
m.count_size(type);
m.count_size(ext);
}
bool
SignerRuleResource::_data_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_data_t const&>(other_abstract);return true
&& (type== other.type)
&& (ext== other.ext)
;}
bool
SignerRuleResource::_data_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_data_t const&>(other_abstract);
if (type < other.type) return true;
if (other.type < type) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
SignerRuleResource::from_bytes(xdr::unmarshaler& u) 
{
int32_t disc;bool ok = u.from_bytes(disc);
if (!ok)
{
return false;
}
_xdr_discriminant(disc, true);switch (type_)
{
  case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
return u.from_bytes(reviewableRequest_);
  case (int32_t)LedgerEntryType::ASSET:
return u.from_bytes(asset_);
  case (int32_t)LedgerEntryType::ANY:
  
  return true;
  case (int32_t)LedgerEntryType::OFFER_ENTRY:
return u.from_bytes(offer_);
  case (int32_t)LedgerEntryType::SALE:
return u.from_bytes(sale_);
  case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
return u.from_bytes(atomicSwapAsk_);
  case (int32_t)LedgerEntryType::SIGNER_RULE:
return u.from_bytes(signerRule_);
  case (int32_t)LedgerEntryType::SIGNER_ROLE:
return u.from_bytes(signerRole_);
  case (int32_t)LedgerEntryType::SIGNER:
return u.from_bytes(signer_);
  case (int32_t)LedgerEntryType::KEY_VALUE:
return u.from_bytes(keyValue_);
  case (int32_t)LedgerEntryType::POLL:
return u.from_bytes(poll_);
  case (int32_t)LedgerEntryType::VOTE:
return u.from_bytes(vote_);
  case (int32_t)LedgerEntryType::INITIATE_KYC_RECOVERY:
return u.from_bytes(initiateKYCRecovery_);
  case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
return u.from_bytes(accountSpecificRuleExt_);
  case (int32_t)LedgerEntryType::SWAP:
return u.from_bytes(swap_);
  case (int32_t)LedgerEntryType::DATA:
return u.from_bytes(data_);
  case (int32_t)LedgerEntryType::CUSTOM:
return u.from_bytes(custom_);
  default:
return u.from_bytes(ext_);
}
return false;
}
bool
SignerRuleResource::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(type_);
if (!ok)
{
return false;
}
switch (type_)
{

  case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
return m.to_bytes(reviewableRequest_);
  case (int32_t)LedgerEntryType::ASSET:
return m.to_bytes(asset_);
  case (int32_t)LedgerEntryType::ANY:
    return true;
  case (int32_t)LedgerEntryType::OFFER_ENTRY:
return m.to_bytes(offer_);
  case (int32_t)LedgerEntryType::SALE:
return m.to_bytes(sale_);
  case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
return m.to_bytes(atomicSwapAsk_);
  case (int32_t)LedgerEntryType::SIGNER_RULE:
return m.to_bytes(signerRule_);
  case (int32_t)LedgerEntryType::SIGNER_ROLE:
return m.to_bytes(signerRole_);
  case (int32_t)LedgerEntryType::SIGNER:
return m.to_bytes(signer_);
  case (int32_t)LedgerEntryType::KEY_VALUE:
return m.to_bytes(keyValue_);
  case (int32_t)LedgerEntryType::POLL:
return m.to_bytes(poll_);
  case (int32_t)LedgerEntryType::VOTE:
return m.to_bytes(vote_);
  case (int32_t)LedgerEntryType::INITIATE_KYC_RECOVERY:
return m.to_bytes(initiateKYCRecovery_);
  case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
return m.to_bytes(accountSpecificRuleExt_);
  case (int32_t)LedgerEntryType::SWAP:
return m.to_bytes(swap_);
  case (int32_t)LedgerEntryType::DATA:
return m.to_bytes(data_);
  case (int32_t)LedgerEntryType::CUSTOM:
return m.to_bytes(custom_);
  default:
return m.to_bytes(ext_);
}
return false;
}
void
SignerRuleResource::count_size(xdr::measurer& m) const
{
m.count_size(type_);
switch (type_)
{

  case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
return m.count_size(reviewableRequest_);
  case (int32_t)LedgerEntryType::ASSET:
return m.count_size(asset_);
  case (int32_t)LedgerEntryType::ANY:
  
  return;
  case (int32_t)LedgerEntryType::OFFER_ENTRY:
return m.count_size(offer_);
  case (int32_t)LedgerEntryType::SALE:
return m.count_size(sale_);
  case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
return m.count_size(atomicSwapAsk_);
  case (int32_t)LedgerEntryType::SIGNER_RULE:
return m.count_size(signerRule_);
  case (int32_t)LedgerEntryType::SIGNER_ROLE:
return m.count_size(signerRole_);
  case (int32_t)LedgerEntryType::SIGNER:
return m.count_size(signer_);
  case (int32_t)LedgerEntryType::KEY_VALUE:
return m.count_size(keyValue_);
  case (int32_t)LedgerEntryType::POLL:
return m.count_size(poll_);
  case (int32_t)LedgerEntryType::VOTE:
return m.count_size(vote_);
  case (int32_t)LedgerEntryType::INITIATE_KYC_RECOVERY:
return m.count_size(initiateKYCRecovery_);
  case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
return m.count_size(accountSpecificRuleExt_);
  case (int32_t)LedgerEntryType::SWAP:
return m.count_size(swap_);
  case (int32_t)LedgerEntryType::DATA:
return m.count_size(data_);
  case (int32_t)LedgerEntryType::CUSTOM:
return m.count_size(custom_);
  default:
return m.count_size(ext_);
}
}
bool
SignerRuleResource::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<SignerRuleResource const&>(other_abstract);
if (other.type_ != type_) return false;
switch (type_)
{
  case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
return reviewableRequest_ == other.reviewableRequest_;
  case (int32_t)LedgerEntryType::ASSET:
return asset_ == other.asset_;
  case (int32_t)LedgerEntryType::ANY:
  
  return true;
  case (int32_t)LedgerEntryType::OFFER_ENTRY:
return offer_ == other.offer_;
  case (int32_t)LedgerEntryType::SALE:
return sale_ == other.sale_;
  case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
return atomicSwapAsk_ == other.atomicSwapAsk_;
  case (int32_t)LedgerEntryType::SIGNER_RULE:
return signerRule_ == other.signerRule_;
  case (int32_t)LedgerEntryType::SIGNER_ROLE:
return signerRole_ == other.signerRole_;
  case (int32_t)LedgerEntryType::SIGNER:
return signer_ == other.signer_;
  case (int32_t)LedgerEntryType::KEY_VALUE:
return keyValue_ == other.keyValue_;
  case (int32_t)LedgerEntryType::POLL:
return poll_ == other.poll_;
  case (int32_t)LedgerEntryType::VOTE:
return vote_ == other.vote_;
  case (int32_t)LedgerEntryType::INITIATE_KYC_RECOVERY:
return initiateKYCRecovery_ == other.initiateKYCRecovery_;
  case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
return accountSpecificRuleExt_ == other.accountSpecificRuleExt_;
  case (int32_t)LedgerEntryType::SWAP:
return swap_ == other.swap_;
  case (int32_t)LedgerEntryType::DATA:
return data_ == other.data_;
  case (int32_t)LedgerEntryType::CUSTOM:
return custom_ == other.custom_;
  default:
return ext_ == other.ext_;
}
return false;
}
bool
SignerRuleResource::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<SignerRuleResource const&>(other_abstract);
if (type_ < other.type_) return true;
if (other.type_ < type_) return false;
switch (type_)
{
  case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
return reviewableRequest_ < other.reviewableRequest_;
  case (int32_t)LedgerEntryType::ASSET:
return asset_ < other.asset_;
  case (int32_t)LedgerEntryType::ANY:
    return false;
  case (int32_t)LedgerEntryType::OFFER_ENTRY:
return offer_ < other.offer_;
  case (int32_t)LedgerEntryType::SALE:
return sale_ < other.sale_;
  case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
return atomicSwapAsk_ < other.atomicSwapAsk_;
  case (int32_t)LedgerEntryType::SIGNER_RULE:
return signerRule_ < other.signerRule_;
  case (int32_t)LedgerEntryType::SIGNER_ROLE:
return signerRole_ < other.signerRole_;
  case (int32_t)LedgerEntryType::SIGNER:
return signer_ < other.signer_;
  case (int32_t)LedgerEntryType::KEY_VALUE:
return keyValue_ < other.keyValue_;
  case (int32_t)LedgerEntryType::POLL:
return poll_ < other.poll_;
  case (int32_t)LedgerEntryType::VOTE:
return vote_ < other.vote_;
  case (int32_t)LedgerEntryType::INITIATE_KYC_RECOVERY:
return initiateKYCRecovery_ < other.initiateKYCRecovery_;
  case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
return accountSpecificRuleExt_ < other.accountSpecificRuleExt_;
  case (int32_t)LedgerEntryType::SWAP:
return swap_ < other.swap_;
  case (int32_t)LedgerEntryType::DATA:
return data_ < other.data_;
  case (int32_t)LedgerEntryType::CUSTOM:
return custom_ < other.custom_;
  default:
return ext_ < other.ext_;
}
return false;
}
}