#include "ledger-keys.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
LedgerKey::_account_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(v_);
if (!ok)
{
return false;
}
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
}
return false;
}
bool
LedgerKey::_account_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
}
return false;
}
void
LedgerKey::_account_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
LedgerKey::_account_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (other.v_ != v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return true;
}
return false;
}
bool
LedgerKey::_account_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (v_ < other.v_) return true;
if (other.v_ < v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return false;
}
return false;
}
bool
LedgerKey::_account_t::from_bytes(xdr::unmarshaler& u) 
{
bool okaccountID = u.from_bytes(accountID);
if (!okaccountID)
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
LedgerKey::_account_t::to_bytes(xdr::marshaler& m) const 
{
bool okaccountID = m.to_bytes(accountID);
if (!okaccountID)
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
LedgerKey::_account_t::count_size(xdr::measurer& m) const 
{
m.count_size(accountID);
m.count_size(ext);
}
bool
LedgerKey::_account_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_account_t const&>(other_abstract);return true
&& (accountID== other.accountID)
&& (ext== other.ext)
;}
bool
LedgerKey::_account_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_account_t const&>(other_abstract);
if (accountID < other.accountID) return true;
if (other.accountID < accountID) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LedgerKey::_signer_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(v_);
if (!ok)
{
return false;
}
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
}
return false;
}
bool
LedgerKey::_signer_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
}
return false;
}
void
LedgerKey::_signer_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
LedgerKey::_signer_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (other.v_ != v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return true;
}
return false;
}
bool
LedgerKey::_signer_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (v_ < other.v_) return true;
if (other.v_ < v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return false;
}
return false;
}
bool
LedgerKey::_signer_t::from_bytes(xdr::unmarshaler& u) 
{
bool okpubKey = u.from_bytes(pubKey);
if (!okpubKey)
{
return false;
}
bool okaccountID = u.from_bytes(accountID);
if (!okaccountID)
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
LedgerKey::_signer_t::to_bytes(xdr::marshaler& m) const 
{
bool okpubKey = m.to_bytes(pubKey);
if (!okpubKey)
{
return false;
}
bool okaccountID = m.to_bytes(accountID);
if (!okaccountID)
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
LedgerKey::_signer_t::count_size(xdr::measurer& m) const 
{
m.count_size(pubKey);
m.count_size(accountID);
m.count_size(ext);
}
bool
LedgerKey::_signer_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_signer_t const&>(other_abstract);return true
&& (pubKey== other.pubKey)
&& (accountID== other.accountID)
&& (ext== other.ext)
;}
bool
LedgerKey::_signer_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_signer_t const&>(other_abstract);
if (pubKey < other.pubKey) return true;
if (other.pubKey < pubKey) return false;
if (accountID < other.accountID) return true;
if (other.accountID < accountID) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LedgerKey::_feeState_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(v_);
if (!ok)
{
return false;
}
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
}
return false;
}
bool
LedgerKey::_feeState_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
}
return false;
}
void
LedgerKey::_feeState_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
LedgerKey::_feeState_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (other.v_ != v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return true;
}
return false;
}
bool
LedgerKey::_feeState_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (v_ < other.v_) return true;
if (other.v_ < v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return false;
}
return false;
}
bool
LedgerKey::_feeState_t::from_bytes(xdr::unmarshaler& u) 
{
bool okhash = u.from_bytes(hash);
if (!okhash)
{
return false;
}
bool oklowerBound = u.from_bytes(lowerBound);
if (!oklowerBound)
{
return false;
}
bool okupperBound = u.from_bytes(upperBound);
if (!okupperBound)
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
LedgerKey::_feeState_t::to_bytes(xdr::marshaler& m) const 
{
bool okhash = m.to_bytes(hash);
if (!okhash)
{
return false;
}
bool oklowerBound = m.to_bytes(lowerBound);
if (!oklowerBound)
{
return false;
}
bool okupperBound = m.to_bytes(upperBound);
if (!okupperBound)
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
LedgerKey::_feeState_t::count_size(xdr::measurer& m) const 
{
m.count_size(hash);
m.count_size(lowerBound);
m.count_size(upperBound);
m.count_size(ext);
}
bool
LedgerKey::_feeState_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_feeState_t const&>(other_abstract);return true
&& (hash== other.hash)
&& (lowerBound== other.lowerBound)
&& (upperBound== other.upperBound)
&& (ext== other.ext)
;}
bool
LedgerKey::_feeState_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_feeState_t const&>(other_abstract);
if (hash < other.hash) return true;
if (other.hash < hash) return false;
if (lowerBound < other.lowerBound) return true;
if (other.lowerBound < lowerBound) return false;
if (upperBound < other.upperBound) return true;
if (other.upperBound < upperBound) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LedgerKey::_balance_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(v_);
if (!ok)
{
return false;
}
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
}
return false;
}
bool
LedgerKey::_balance_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
}
return false;
}
void
LedgerKey::_balance_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
LedgerKey::_balance_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (other.v_ != v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return true;
}
return false;
}
bool
LedgerKey::_balance_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (v_ < other.v_) return true;
if (other.v_ < v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return false;
}
return false;
}
bool
LedgerKey::_balance_t::from_bytes(xdr::unmarshaler& u) 
{
bool okbalanceID = u.from_bytes(balanceID);
if (!okbalanceID)
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
LedgerKey::_balance_t::to_bytes(xdr::marshaler& m) const 
{
bool okbalanceID = m.to_bytes(balanceID);
if (!okbalanceID)
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
LedgerKey::_balance_t::count_size(xdr::measurer& m) const 
{
m.count_size(balanceID);
m.count_size(ext);
}
bool
LedgerKey::_balance_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_balance_t const&>(other_abstract);return true
&& (balanceID== other.balanceID)
&& (ext== other.ext)
;}
bool
LedgerKey::_balance_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_balance_t const&>(other_abstract);
if (balanceID < other.balanceID) return true;
if (other.balanceID < balanceID) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LedgerKey::_asset_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(v_);
if (!ok)
{
return false;
}
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
}
return false;
}
bool
LedgerKey::_asset_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
}
return false;
}
void
LedgerKey::_asset_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
LedgerKey::_asset_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (other.v_ != v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return true;
}
return false;
}
bool
LedgerKey::_asset_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (v_ < other.v_) return true;
if (other.v_ < v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return false;
}
return false;
}
bool
LedgerKey::_asset_t::from_bytes(xdr::unmarshaler& u) 
{
bool okcode = u.from_bytes(code);
if (!okcode)
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
LedgerKey::_asset_t::to_bytes(xdr::marshaler& m) const 
{
bool okcode = m.to_bytes(code);
if (!okcode)
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
LedgerKey::_asset_t::count_size(xdr::measurer& m) const 
{
m.count_size(code);
m.count_size(ext);
}
bool
LedgerKey::_asset_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_asset_t const&>(other_abstract);return true
&& (code== other.code)
&& (ext== other.ext)
;}
bool
LedgerKey::_asset_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_asset_t const&>(other_abstract);
if (code < other.code) return true;
if (other.code < code) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LedgerKey::_reference_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(v_);
if (!ok)
{
return false;
}
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
}
return false;
}
bool
LedgerKey::_reference_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
}
return false;
}
void
LedgerKey::_reference_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
LedgerKey::_reference_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (other.v_ != v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return true;
}
return false;
}
bool
LedgerKey::_reference_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (v_ < other.v_) return true;
if (other.v_ < v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return false;
}
return false;
}
bool
LedgerKey::_reference_t::from_bytes(xdr::unmarshaler& u) 
{
bool oksender = u.from_bytes(sender);
if (!oksender)
{
return false;
}
bool okreference = u.from_bytes(reference);
if (!okreference)
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
LedgerKey::_reference_t::to_bytes(xdr::marshaler& m) const 
{
bool oksender = m.to_bytes(sender);
if (!oksender)
{
return false;
}
bool okreference = m.to_bytes(reference);
if (!okreference)
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
LedgerKey::_reference_t::count_size(xdr::measurer& m) const 
{
m.count_size(sender);
m.count_size(reference);
m.count_size(ext);
}
bool
LedgerKey::_reference_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_reference_t const&>(other_abstract);return true
&& (sender== other.sender)
&& (reference== other.reference)
&& (ext== other.ext)
;}
bool
LedgerKey::_reference_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_reference_t const&>(other_abstract);
if (sender < other.sender) return true;
if (other.sender < sender) return false;
if (reference < other.reference) return true;
if (other.reference < reference) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LedgerKey::_stats_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(v_);
if (!ok)
{
return false;
}
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
}
return false;
}
bool
LedgerKey::_stats_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
}
return false;
}
void
LedgerKey::_stats_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
LedgerKey::_stats_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (other.v_ != v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return true;
}
return false;
}
bool
LedgerKey::_stats_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (v_ < other.v_) return true;
if (other.v_ < v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return false;
}
return false;
}
bool
LedgerKey::_stats_t::from_bytes(xdr::unmarshaler& u) 
{
bool okaccountID = u.from_bytes(accountID);
if (!okaccountID)
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
LedgerKey::_stats_t::to_bytes(xdr::marshaler& m) const 
{
bool okaccountID = m.to_bytes(accountID);
if (!okaccountID)
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
LedgerKey::_stats_t::count_size(xdr::measurer& m) const 
{
m.count_size(accountID);
m.count_size(ext);
}
bool
LedgerKey::_stats_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_stats_t const&>(other_abstract);return true
&& (accountID== other.accountID)
&& (ext== other.ext)
;}
bool
LedgerKey::_stats_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_stats_t const&>(other_abstract);
if (accountID < other.accountID) return true;
if (other.accountID < accountID) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LedgerKey::_accountLimits_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(v_);
if (!ok)
{
return false;
}
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
}
return false;
}
bool
LedgerKey::_accountLimits_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
}
return false;
}
void
LedgerKey::_accountLimits_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
LedgerKey::_accountLimits_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (other.v_ != v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return true;
}
return false;
}
bool
LedgerKey::_accountLimits_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (v_ < other.v_) return true;
if (other.v_ < v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return false;
}
return false;
}
bool
LedgerKey::_accountLimits_t::from_bytes(xdr::unmarshaler& u) 
{
bool okaccountID = u.from_bytes(accountID);
if (!okaccountID)
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
LedgerKey::_accountLimits_t::to_bytes(xdr::marshaler& m) const 
{
bool okaccountID = m.to_bytes(accountID);
if (!okaccountID)
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
LedgerKey::_accountLimits_t::count_size(xdr::measurer& m) const 
{
m.count_size(accountID);
m.count_size(ext);
}
bool
LedgerKey::_accountLimits_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_accountLimits_t const&>(other_abstract);return true
&& (accountID== other.accountID)
&& (ext== other.ext)
;}
bool
LedgerKey::_accountLimits_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_accountLimits_t const&>(other_abstract);
if (accountID < other.accountID) return true;
if (other.accountID < accountID) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LedgerKey::_assetPair_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(v_);
if (!ok)
{
return false;
}
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
}
return false;
}
bool
LedgerKey::_assetPair_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
}
return false;
}
void
LedgerKey::_assetPair_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
LedgerKey::_assetPair_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (other.v_ != v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return true;
}
return false;
}
bool
LedgerKey::_assetPair_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (v_ < other.v_) return true;
if (other.v_ < v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return false;
}
return false;
}
bool
LedgerKey::_assetPair_t::from_bytes(xdr::unmarshaler& u) 
{
bool okbase = u.from_bytes(base);
if (!okbase)
{
return false;
}
bool okquote = u.from_bytes(quote);
if (!okquote)
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
LedgerKey::_assetPair_t::to_bytes(xdr::marshaler& m) const 
{
bool okbase = m.to_bytes(base);
if (!okbase)
{
return false;
}
bool okquote = m.to_bytes(quote);
if (!okquote)
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
LedgerKey::_assetPair_t::count_size(xdr::measurer& m) const 
{
m.count_size(base);
m.count_size(quote);
m.count_size(ext);
}
bool
LedgerKey::_assetPair_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_assetPair_t const&>(other_abstract);return true
&& (base== other.base)
&& (quote== other.quote)
&& (ext== other.ext)
;}
bool
LedgerKey::_assetPair_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_assetPair_t const&>(other_abstract);
if (base < other.base) return true;
if (other.base < base) return false;
if (quote < other.quote) return true;
if (other.quote < quote) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LedgerKey::_offer_t::from_bytes(xdr::unmarshaler& u) 
{
bool okofferID = u.from_bytes(offerID);
if (!okofferID)
{
return false;
}
bool okownerID = u.from_bytes(ownerID);
if (!okownerID)
{
return false;
}
return true;
}
bool
LedgerKey::_offer_t::to_bytes(xdr::marshaler& m) const 
{
bool okofferID = m.to_bytes(offerID);
if (!okofferID)
{
return false;
}
bool okownerID = m.to_bytes(ownerID);
if (!okownerID)
{
return false;
}
return true;
}
void
LedgerKey::_offer_t::count_size(xdr::measurer& m) const 
{
m.count_size(offerID);
m.count_size(ownerID);
}
bool
LedgerKey::_offer_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_offer_t const&>(other_abstract);return true
&& (offerID== other.offerID)
&& (ownerID== other.ownerID)
;}
bool
LedgerKey::_offer_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_offer_t const&>(other_abstract);
if (offerID < other.offerID) return true;
if (other.offerID < offerID) return false;
if (ownerID < other.ownerID) return true;
if (other.ownerID < ownerID) return false;
return false;
}bool
LedgerKey::_reviewableRequest_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(v_);
if (!ok)
{
return false;
}
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
}
return false;
}
bool
LedgerKey::_reviewableRequest_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
}
return false;
}
void
LedgerKey::_reviewableRequest_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
LedgerKey::_reviewableRequest_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (other.v_ != v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return true;
}
return false;
}
bool
LedgerKey::_reviewableRequest_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (v_ < other.v_) return true;
if (other.v_ < v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return false;
}
return false;
}
bool
LedgerKey::_reviewableRequest_t::from_bytes(xdr::unmarshaler& u) 
{
bool okrequestID = u.from_bytes(requestID);
if (!okrequestID)
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
LedgerKey::_reviewableRequest_t::to_bytes(xdr::marshaler& m) const 
{
bool okrequestID = m.to_bytes(requestID);
if (!okrequestID)
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
LedgerKey::_reviewableRequest_t::count_size(xdr::measurer& m) const 
{
m.count_size(requestID);
m.count_size(ext);
}
bool
LedgerKey::_reviewableRequest_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_reviewableRequest_t const&>(other_abstract);return true
&& (requestID== other.requestID)
&& (ext== other.ext)
;}
bool
LedgerKey::_reviewableRequest_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_reviewableRequest_t const&>(other_abstract);
if (requestID < other.requestID) return true;
if (other.requestID < requestID) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LedgerKey::_externalSystemAccountID_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(v_);
if (!ok)
{
return false;
}
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
}
return false;
}
bool
LedgerKey::_externalSystemAccountID_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
}
return false;
}
void
LedgerKey::_externalSystemAccountID_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
LedgerKey::_externalSystemAccountID_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (other.v_ != v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return true;
}
return false;
}
bool
LedgerKey::_externalSystemAccountID_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (v_ < other.v_) return true;
if (other.v_ < v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return false;
}
return false;
}
bool
LedgerKey::_externalSystemAccountID_t::from_bytes(xdr::unmarshaler& u) 
{
bool okaccountID = u.from_bytes(accountID);
if (!okaccountID)
{
return false;
}
bool okexternalSystemType = u.from_bytes(externalSystemType);
if (!okexternalSystemType)
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
LedgerKey::_externalSystemAccountID_t::to_bytes(xdr::marshaler& m) const 
{
bool okaccountID = m.to_bytes(accountID);
if (!okaccountID)
{
return false;
}
bool okexternalSystemType = m.to_bytes(externalSystemType);
if (!okexternalSystemType)
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
LedgerKey::_externalSystemAccountID_t::count_size(xdr::measurer& m) const 
{
m.count_size(accountID);
m.count_size(externalSystemType);
m.count_size(ext);
}
bool
LedgerKey::_externalSystemAccountID_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_externalSystemAccountID_t const&>(other_abstract);return true
&& (accountID== other.accountID)
&& (externalSystemType== other.externalSystemType)
&& (ext== other.ext)
;}
bool
LedgerKey::_externalSystemAccountID_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_externalSystemAccountID_t const&>(other_abstract);
if (accountID < other.accountID) return true;
if (other.accountID < accountID) return false;
if (externalSystemType < other.externalSystemType) return true;
if (other.externalSystemType < externalSystemType) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LedgerKey::_sale_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(v_);
if (!ok)
{
return false;
}
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
}
return false;
}
bool
LedgerKey::_sale_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
}
return false;
}
void
LedgerKey::_sale_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
LedgerKey::_sale_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (other.v_ != v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return true;
}
return false;
}
bool
LedgerKey::_sale_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (v_ < other.v_) return true;
if (other.v_ < v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return false;
}
return false;
}
bool
LedgerKey::_sale_t::from_bytes(xdr::unmarshaler& u) 
{
bool oksaleID = u.from_bytes(saleID);
if (!oksaleID)
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
LedgerKey::_sale_t::to_bytes(xdr::marshaler& m) const 
{
bool oksaleID = m.to_bytes(saleID);
if (!oksaleID)
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
LedgerKey::_sale_t::count_size(xdr::measurer& m) const 
{
m.count_size(saleID);
m.count_size(ext);
}
bool
LedgerKey::_sale_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_sale_t const&>(other_abstract);return true
&& (saleID== other.saleID)
&& (ext== other.ext)
;}
bool
LedgerKey::_sale_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_sale_t const&>(other_abstract);
if (saleID < other.saleID) return true;
if (other.saleID < saleID) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LedgerKey::_keyValue_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(v_);
if (!ok)
{
return false;
}
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
}
return false;
}
bool
LedgerKey::_keyValue_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
}
return false;
}
void
LedgerKey::_keyValue_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
LedgerKey::_keyValue_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (other.v_ != v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return true;
}
return false;
}
bool
LedgerKey::_keyValue_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (v_ < other.v_) return true;
if (other.v_ < v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return false;
}
return false;
}
bool
LedgerKey::_keyValue_t::from_bytes(xdr::unmarshaler& u) 
{
bool okkey = u.from_bytes(key);
if (!okkey)
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
LedgerKey::_keyValue_t::to_bytes(xdr::marshaler& m) const 
{
bool okkey = m.to_bytes(key);
if (!okkey)
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
LedgerKey::_keyValue_t::count_size(xdr::measurer& m) const 
{
m.count_size(key);
m.count_size(ext);
}
bool
LedgerKey::_keyValue_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_keyValue_t const&>(other_abstract);return true
&& (key== other.key)
&& (ext== other.ext)
;}
bool
LedgerKey::_keyValue_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_keyValue_t const&>(other_abstract);
if (key < other.key) return true;
if (other.key < key) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LedgerKey::_accountKYC_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(v_);
if (!ok)
{
return false;
}
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
}
return false;
}
bool
LedgerKey::_accountKYC_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
}
return false;
}
void
LedgerKey::_accountKYC_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
LedgerKey::_accountKYC_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (other.v_ != v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return true;
}
return false;
}
bool
LedgerKey::_accountKYC_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (v_ < other.v_) return true;
if (other.v_ < v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return false;
}
return false;
}
bool
LedgerKey::_accountKYC_t::from_bytes(xdr::unmarshaler& u) 
{
bool okaccountID = u.from_bytes(accountID);
if (!okaccountID)
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
LedgerKey::_accountKYC_t::to_bytes(xdr::marshaler& m) const 
{
bool okaccountID = m.to_bytes(accountID);
if (!okaccountID)
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
LedgerKey::_accountKYC_t::count_size(xdr::measurer& m) const 
{
m.count_size(accountID);
m.count_size(ext);
}
bool
LedgerKey::_accountKYC_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_accountKYC_t const&>(other_abstract);return true
&& (accountID== other.accountID)
&& (ext== other.ext)
;}
bool
LedgerKey::_accountKYC_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_accountKYC_t const&>(other_abstract);
if (accountID < other.accountID) return true;
if (other.accountID < accountID) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LedgerKey::_externalSystemAccountIDPoolEntry_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(v_);
if (!ok)
{
return false;
}
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
}
return false;
}
bool
LedgerKey::_externalSystemAccountIDPoolEntry_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
}
return false;
}
void
LedgerKey::_externalSystemAccountIDPoolEntry_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
LedgerKey::_externalSystemAccountIDPoolEntry_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (other.v_ != v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return true;
}
return false;
}
bool
LedgerKey::_externalSystemAccountIDPoolEntry_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (v_ < other.v_) return true;
if (other.v_ < v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return false;
}
return false;
}
bool
LedgerKey::_externalSystemAccountIDPoolEntry_t::from_bytes(xdr::unmarshaler& u) 
{
bool okpoolEntryID = u.from_bytes(poolEntryID);
if (!okpoolEntryID)
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
LedgerKey::_externalSystemAccountIDPoolEntry_t::to_bytes(xdr::marshaler& m) const 
{
bool okpoolEntryID = m.to_bytes(poolEntryID);
if (!okpoolEntryID)
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
LedgerKey::_externalSystemAccountIDPoolEntry_t::count_size(xdr::measurer& m) const 
{
m.count_size(poolEntryID);
m.count_size(ext);
}
bool
LedgerKey::_externalSystemAccountIDPoolEntry_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_externalSystemAccountIDPoolEntry_t const&>(other_abstract);return true
&& (poolEntryID== other.poolEntryID)
&& (ext== other.ext)
;}
bool
LedgerKey::_externalSystemAccountIDPoolEntry_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_externalSystemAccountIDPoolEntry_t const&>(other_abstract);
if (poolEntryID < other.poolEntryID) return true;
if (other.poolEntryID < poolEntryID) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LedgerKey::_limitsV2_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(v_);
if (!ok)
{
return false;
}
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
}
return false;
}
bool
LedgerKey::_limitsV2_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
}
return false;
}
void
LedgerKey::_limitsV2_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
LedgerKey::_limitsV2_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (other.v_ != v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return true;
}
return false;
}
bool
LedgerKey::_limitsV2_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (v_ < other.v_) return true;
if (other.v_ < v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return false;
}
return false;
}
bool
LedgerKey::_limitsV2_t::from_bytes(xdr::unmarshaler& u) 
{
bool okid = u.from_bytes(id);
if (!okid)
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
LedgerKey::_limitsV2_t::to_bytes(xdr::marshaler& m) const 
{
bool okid = m.to_bytes(id);
if (!okid)
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
LedgerKey::_limitsV2_t::count_size(xdr::measurer& m) const 
{
m.count_size(id);
m.count_size(ext);
}
bool
LedgerKey::_limitsV2_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_limitsV2_t const&>(other_abstract);return true
&& (id== other.id)
&& (ext== other.ext)
;}
bool
LedgerKey::_limitsV2_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_limitsV2_t const&>(other_abstract);
if (id < other.id) return true;
if (other.id < id) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LedgerKey::_statisticsV2_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(v_);
if (!ok)
{
return false;
}
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
}
return false;
}
bool
LedgerKey::_statisticsV2_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
}
return false;
}
void
LedgerKey::_statisticsV2_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
LedgerKey::_statisticsV2_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (other.v_ != v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return true;
}
return false;
}
bool
LedgerKey::_statisticsV2_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (v_ < other.v_) return true;
if (other.v_ < v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return false;
}
return false;
}
bool
LedgerKey::_statisticsV2_t::from_bytes(xdr::unmarshaler& u) 
{
bool okid = u.from_bytes(id);
if (!okid)
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
LedgerKey::_statisticsV2_t::to_bytes(xdr::marshaler& m) const 
{
bool okid = m.to_bytes(id);
if (!okid)
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
LedgerKey::_statisticsV2_t::count_size(xdr::measurer& m) const 
{
m.count_size(id);
m.count_size(ext);
}
bool
LedgerKey::_statisticsV2_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_statisticsV2_t const&>(other_abstract);return true
&& (id== other.id)
&& (ext== other.ext)
;}
bool
LedgerKey::_statisticsV2_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_statisticsV2_t const&>(other_abstract);
if (id < other.id) return true;
if (other.id < id) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LedgerKey::_pendingStatistics_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(v_);
if (!ok)
{
return false;
}
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
}
return false;
}
bool
LedgerKey::_pendingStatistics_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
}
return false;
}
void
LedgerKey::_pendingStatistics_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
LedgerKey::_pendingStatistics_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (other.v_ != v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return true;
}
return false;
}
bool
LedgerKey::_pendingStatistics_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (v_ < other.v_) return true;
if (other.v_ < v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return false;
}
return false;
}
bool
LedgerKey::_pendingStatistics_t::from_bytes(xdr::unmarshaler& u) 
{
bool okstatisticsID = u.from_bytes(statisticsID);
if (!okstatisticsID)
{
return false;
}
bool okrequestID = u.from_bytes(requestID);
if (!okrequestID)
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
LedgerKey::_pendingStatistics_t::to_bytes(xdr::marshaler& m) const 
{
bool okstatisticsID = m.to_bytes(statisticsID);
if (!okstatisticsID)
{
return false;
}
bool okrequestID = m.to_bytes(requestID);
if (!okrequestID)
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
LedgerKey::_pendingStatistics_t::count_size(xdr::measurer& m) const 
{
m.count_size(statisticsID);
m.count_size(requestID);
m.count_size(ext);
}
bool
LedgerKey::_pendingStatistics_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_pendingStatistics_t const&>(other_abstract);return true
&& (statisticsID== other.statisticsID)
&& (requestID== other.requestID)
&& (ext== other.ext)
;}
bool
LedgerKey::_pendingStatistics_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_pendingStatistics_t const&>(other_abstract);
if (statisticsID < other.statisticsID) return true;
if (other.statisticsID < statisticsID) return false;
if (requestID < other.requestID) return true;
if (other.requestID < requestID) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LedgerKey::_contract_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(v_);
if (!ok)
{
return false;
}
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
}
return false;
}
bool
LedgerKey::_contract_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
}
return false;
}
void
LedgerKey::_contract_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
LedgerKey::_contract_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (other.v_ != v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return true;
}
return false;
}
bool
LedgerKey::_contract_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (v_ < other.v_) return true;
if (other.v_ < v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return false;
}
return false;
}
bool
LedgerKey::_contract_t::from_bytes(xdr::unmarshaler& u) 
{
bool okcontractID = u.from_bytes(contractID);
if (!okcontractID)
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
LedgerKey::_contract_t::to_bytes(xdr::marshaler& m) const 
{
bool okcontractID = m.to_bytes(contractID);
if (!okcontractID)
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
LedgerKey::_contract_t::count_size(xdr::measurer& m) const 
{
m.count_size(contractID);
m.count_size(ext);
}
bool
LedgerKey::_contract_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_contract_t const&>(other_abstract);return true
&& (contractID== other.contractID)
&& (ext== other.ext)
;}
bool
LedgerKey::_contract_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_contract_t const&>(other_abstract);
if (contractID < other.contractID) return true;
if (other.contractID < contractID) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LedgerKey::_atomicSwapAsk_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(v_);
if (!ok)
{
return false;
}
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
}
return false;
}
bool
LedgerKey::_atomicSwapAsk_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
}
return false;
}
void
LedgerKey::_atomicSwapAsk_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
LedgerKey::_atomicSwapAsk_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (other.v_ != v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return true;
}
return false;
}
bool
LedgerKey::_atomicSwapAsk_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (v_ < other.v_) return true;
if (other.v_ < v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return false;
}
return false;
}
bool
LedgerKey::_atomicSwapAsk_t::from_bytes(xdr::unmarshaler& u) 
{
bool okid = u.from_bytes(id);
if (!okid)
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
LedgerKey::_atomicSwapAsk_t::to_bytes(xdr::marshaler& m) const 
{
bool okid = m.to_bytes(id);
if (!okid)
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
LedgerKey::_atomicSwapAsk_t::count_size(xdr::measurer& m) const 
{
m.count_size(id);
m.count_size(ext);
}
bool
LedgerKey::_atomicSwapAsk_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_atomicSwapAsk_t const&>(other_abstract);return true
&& (id== other.id)
&& (ext== other.ext)
;}
bool
LedgerKey::_atomicSwapAsk_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_atomicSwapAsk_t const&>(other_abstract);
if (id < other.id) return true;
if (other.id < id) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LedgerKey::_accountRole_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(v_);
if (!ok)
{
return false;
}
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
}
return false;
}
bool
LedgerKey::_accountRole_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
}
return false;
}
void
LedgerKey::_accountRole_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
LedgerKey::_accountRole_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (other.v_ != v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return true;
}
return false;
}
bool
LedgerKey::_accountRole_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (v_ < other.v_) return true;
if (other.v_ < v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return false;
}
return false;
}
bool
LedgerKey::_accountRole_t::from_bytes(xdr::unmarshaler& u) 
{
bool okid = u.from_bytes(id);
if (!okid)
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
LedgerKey::_accountRole_t::to_bytes(xdr::marshaler& m) const 
{
bool okid = m.to_bytes(id);
if (!okid)
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
LedgerKey::_accountRole_t::count_size(xdr::measurer& m) const 
{
m.count_size(id);
m.count_size(ext);
}
bool
LedgerKey::_accountRole_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_accountRole_t const&>(other_abstract);return true
&& (id== other.id)
&& (ext== other.ext)
;}
bool
LedgerKey::_accountRole_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_accountRole_t const&>(other_abstract);
if (id < other.id) return true;
if (other.id < id) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LedgerKey::_accountRule_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(v_);
if (!ok)
{
return false;
}
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
}
return false;
}
bool
LedgerKey::_accountRule_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
}
return false;
}
void
LedgerKey::_accountRule_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
LedgerKey::_accountRule_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (other.v_ != v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return true;
}
return false;
}
bool
LedgerKey::_accountRule_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (v_ < other.v_) return true;
if (other.v_ < v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return false;
}
return false;
}
bool
LedgerKey::_accountRule_t::from_bytes(xdr::unmarshaler& u) 
{
bool okid = u.from_bytes(id);
if (!okid)
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
LedgerKey::_accountRule_t::to_bytes(xdr::marshaler& m) const 
{
bool okid = m.to_bytes(id);
if (!okid)
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
LedgerKey::_accountRule_t::count_size(xdr::measurer& m) const 
{
m.count_size(id);
m.count_size(ext);
}
bool
LedgerKey::_accountRule_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_accountRule_t const&>(other_abstract);return true
&& (id== other.id)
&& (ext== other.ext)
;}
bool
LedgerKey::_accountRule_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_accountRule_t const&>(other_abstract);
if (id < other.id) return true;
if (other.id < id) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LedgerKey::_signerRole_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(v_);
if (!ok)
{
return false;
}
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
}
return false;
}
bool
LedgerKey::_signerRole_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
}
return false;
}
void
LedgerKey::_signerRole_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
LedgerKey::_signerRole_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (other.v_ != v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return true;
}
return false;
}
bool
LedgerKey::_signerRole_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (v_ < other.v_) return true;
if (other.v_ < v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return false;
}
return false;
}
bool
LedgerKey::_signerRole_t::from_bytes(xdr::unmarshaler& u) 
{
bool okid = u.from_bytes(id);
if (!okid)
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
LedgerKey::_signerRole_t::to_bytes(xdr::marshaler& m) const 
{
bool okid = m.to_bytes(id);
if (!okid)
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
LedgerKey::_signerRole_t::count_size(xdr::measurer& m) const 
{
m.count_size(id);
m.count_size(ext);
}
bool
LedgerKey::_signerRole_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_signerRole_t const&>(other_abstract);return true
&& (id== other.id)
&& (ext== other.ext)
;}
bool
LedgerKey::_signerRole_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_signerRole_t const&>(other_abstract);
if (id < other.id) return true;
if (other.id < id) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LedgerKey::_signerRule_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(v_);
if (!ok)
{
return false;
}
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
}
return false;
}
bool
LedgerKey::_signerRule_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
}
return false;
}
void
LedgerKey::_signerRule_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
LedgerKey::_signerRule_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (other.v_ != v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return true;
}
return false;
}
bool
LedgerKey::_signerRule_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (v_ < other.v_) return true;
if (other.v_ < v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return false;
}
return false;
}
bool
LedgerKey::_signerRule_t::from_bytes(xdr::unmarshaler& u) 
{
bool okid = u.from_bytes(id);
if (!okid)
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
LedgerKey::_signerRule_t::to_bytes(xdr::marshaler& m) const 
{
bool okid = m.to_bytes(id);
if (!okid)
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
LedgerKey::_signerRule_t::count_size(xdr::measurer& m) const 
{
m.count_size(id);
m.count_size(ext);
}
bool
LedgerKey::_signerRule_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_signerRule_t const&>(other_abstract);return true
&& (id== other.id)
&& (ext== other.ext)
;}
bool
LedgerKey::_signerRule_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_signerRule_t const&>(other_abstract);
if (id < other.id) return true;
if (other.id < id) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LedgerKey::_stamp_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(v_);
if (!ok)
{
return false;
}
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
}
return false;
}
bool
LedgerKey::_stamp_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
}
return false;
}
void
LedgerKey::_stamp_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
LedgerKey::_stamp_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (other.v_ != v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return true;
}
return false;
}
bool
LedgerKey::_stamp_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (v_ < other.v_) return true;
if (other.v_ < v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return false;
}
return false;
}
bool
LedgerKey::_stamp_t::from_bytes(xdr::unmarshaler& u) 
{
bool okledgerHash = u.from_bytes(ledgerHash);
if (!okledgerHash)
{
return false;
}
bool oklicenseHash = u.from_bytes(licenseHash);
if (!oklicenseHash)
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
LedgerKey::_stamp_t::to_bytes(xdr::marshaler& m) const 
{
bool okledgerHash = m.to_bytes(ledgerHash);
if (!okledgerHash)
{
return false;
}
bool oklicenseHash = m.to_bytes(licenseHash);
if (!oklicenseHash)
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
LedgerKey::_stamp_t::count_size(xdr::measurer& m) const 
{
m.count_size(ledgerHash);
m.count_size(licenseHash);
m.count_size(ext);
}
bool
LedgerKey::_stamp_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_stamp_t const&>(other_abstract);return true
&& (ledgerHash== other.ledgerHash)
&& (licenseHash== other.licenseHash)
&& (ext== other.ext)
;}
bool
LedgerKey::_stamp_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_stamp_t const&>(other_abstract);
if (ledgerHash < other.ledgerHash) return true;
if (other.ledgerHash < ledgerHash) return false;
if (licenseHash < other.licenseHash) return true;
if (other.licenseHash < licenseHash) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LedgerKey::_license_t::_ext_t::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(v_);
if (!ok)
{
return false;
}
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
}
return false;
}
bool
LedgerKey::_license_t::_ext_t::to_bytes(xdr::marshaler& m) const
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
}
return false;
}
void
LedgerKey::_license_t::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return;
}
}
bool
LedgerKey::_license_t::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (other.v_ != v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
      
  return true;
}
return false;
}
bool
LedgerKey::_license_t::_ext_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_ext_t const&>(other_abstract);
if (v_ < other.v_) return true;
if (other.v_ < v_) return false;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return false;
}
return false;
}
bool
LedgerKey::_license_t::from_bytes(xdr::unmarshaler& u) 
{
bool oklicenseHash = u.from_bytes(licenseHash);
if (!oklicenseHash)
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
LedgerKey::_license_t::to_bytes(xdr::marshaler& m) const 
{
bool oklicenseHash = m.to_bytes(licenseHash);
if (!oklicenseHash)
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
LedgerKey::_license_t::count_size(xdr::measurer& m) const 
{
m.count_size(licenseHash);
m.count_size(ext);
}
bool
LedgerKey::_license_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_license_t const&>(other_abstract);return true
&& (licenseHash== other.licenseHash)
&& (ext== other.ext)
;}
bool
LedgerKey::_license_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_license_t const&>(other_abstract);
if (licenseHash < other.licenseHash) return true;
if (other.licenseHash < licenseHash) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LedgerKey::_poll_t::from_bytes(xdr::unmarshaler& u) 
{
bool okid = u.from_bytes(id);
if (!okid)
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
LedgerKey::_poll_t::to_bytes(xdr::marshaler& m) const 
{
bool okid = m.to_bytes(id);
if (!okid)
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
LedgerKey::_poll_t::count_size(xdr::measurer& m) const 
{
m.count_size(id);
m.count_size(ext);
}
bool
LedgerKey::_poll_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_poll_t const&>(other_abstract);return true
&& (id== other.id)
&& (ext== other.ext)
;}
bool
LedgerKey::_poll_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_poll_t const&>(other_abstract);
if (id < other.id) return true;
if (other.id < id) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LedgerKey::_vote_t::from_bytes(xdr::unmarshaler& u) 
{
bool okpollID = u.from_bytes(pollID);
if (!okpollID)
{
return false;
}
bool okvoterID = u.from_bytes(voterID);
if (!okvoterID)
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
LedgerKey::_vote_t::to_bytes(xdr::marshaler& m) const 
{
bool okpollID = m.to_bytes(pollID);
if (!okpollID)
{
return false;
}
bool okvoterID = m.to_bytes(voterID);
if (!okvoterID)
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
LedgerKey::_vote_t::count_size(xdr::measurer& m) const 
{
m.count_size(pollID);
m.count_size(voterID);
m.count_size(ext);
}
bool
LedgerKey::_vote_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_vote_t const&>(other_abstract);return true
&& (pollID== other.pollID)
&& (voterID== other.voterID)
&& (ext== other.ext)
;}
bool
LedgerKey::_vote_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_vote_t const&>(other_abstract);
if (pollID < other.pollID) return true;
if (other.pollID < pollID) return false;
if (voterID < other.voterID) return true;
if (other.voterID < voterID) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LedgerKey::_accountSpecificRule_t::from_bytes(xdr::unmarshaler& u) 
{
bool okid = u.from_bytes(id);
if (!okid)
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
LedgerKey::_accountSpecificRule_t::to_bytes(xdr::marshaler& m) const 
{
bool okid = m.to_bytes(id);
if (!okid)
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
LedgerKey::_accountSpecificRule_t::count_size(xdr::measurer& m) const 
{
m.count_size(id);
m.count_size(ext);
}
bool
LedgerKey::_accountSpecificRule_t::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<_accountSpecificRule_t const&>(other_abstract);return true
&& (id== other.id)
&& (ext== other.ext)
;}
bool
LedgerKey::_accountSpecificRule_t::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<_accountSpecificRule_t const&>(other_abstract);
if (id < other.id) return true;
if (other.id < id) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
LedgerKey::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(type_);
if (!ok)
{
return false;
}
switch (type_)
{

  case (int32_t)LedgerEntryType::ACCOUNT:
return u.from_bytes(account_);
  case (int32_t)LedgerEntryType::SIGNER:
return u.from_bytes(signer_);
  case (int32_t)LedgerEntryType::FEE:
return u.from_bytes(feeState_);
  case (int32_t)LedgerEntryType::BALANCE:
return u.from_bytes(balance_);
  case (int32_t)LedgerEntryType::ASSET:
return u.from_bytes(asset_);
  case (int32_t)LedgerEntryType::REFERENCE_ENTRY:
return u.from_bytes(reference_);
  case (int32_t)LedgerEntryType::STATISTICS:
return u.from_bytes(stats_);
  case (int32_t)LedgerEntryType::ACCOUNT_LIMITS:
return u.from_bytes(accountLimits_);
  case (int32_t)LedgerEntryType::ASSET_PAIR:
return u.from_bytes(assetPair_);
  case (int32_t)LedgerEntryType::OFFER_ENTRY:
return u.from_bytes(offer_);
  case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
return u.from_bytes(reviewableRequest_);
  case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
return u.from_bytes(externalSystemAccountID_);
  case (int32_t)LedgerEntryType::SALE:
return u.from_bytes(sale_);
  case (int32_t)LedgerEntryType::KEY_VALUE:
return u.from_bytes(keyValue_);
  case (int32_t)LedgerEntryType::ACCOUNT_KYC:
return u.from_bytes(accountKYC_);
  case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
return u.from_bytes(externalSystemAccountIDPoolEntry_);
  case (int32_t)LedgerEntryType::LIMITS_V2:
return u.from_bytes(limitsV2_);
  case (int32_t)LedgerEntryType::STATISTICS_V2:
return u.from_bytes(statisticsV2_);
  case (int32_t)LedgerEntryType::PENDING_STATISTICS:
return u.from_bytes(pendingStatistics_);
  case (int32_t)LedgerEntryType::CONTRACT:
return u.from_bytes(contract_);
  case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
return u.from_bytes(atomicSwapAsk_);
  case (int32_t)LedgerEntryType::ACCOUNT_ROLE:
return u.from_bytes(accountRole_);
  case (int32_t)LedgerEntryType::ACCOUNT_RULE:
return u.from_bytes(accountRule_);
  case (int32_t)LedgerEntryType::SIGNER_ROLE:
return u.from_bytes(signerRole_);
  case (int32_t)LedgerEntryType::SIGNER_RULE:
return u.from_bytes(signerRule_);
  case (int32_t)LedgerEntryType::STAMP:
return u.from_bytes(stamp_);
  case (int32_t)LedgerEntryType::LICENSE:
return u.from_bytes(license_);
  case (int32_t)LedgerEntryType::POLL:
return u.from_bytes(poll_);
  case (int32_t)LedgerEntryType::VOTE:
return u.from_bytes(vote_);
  case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
return u.from_bytes(accountSpecificRule_);
}
return false;
}
bool
LedgerKey::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(type_);
if (!ok)
{
return false;
}
switch (type_)
{

  case (int32_t)LedgerEntryType::ACCOUNT:
return m.to_bytes(account_);
  case (int32_t)LedgerEntryType::SIGNER:
return m.to_bytes(signer_);
  case (int32_t)LedgerEntryType::FEE:
return m.to_bytes(feeState_);
  case (int32_t)LedgerEntryType::BALANCE:
return m.to_bytes(balance_);
  case (int32_t)LedgerEntryType::ASSET:
return m.to_bytes(asset_);
  case (int32_t)LedgerEntryType::REFERENCE_ENTRY:
return m.to_bytes(reference_);
  case (int32_t)LedgerEntryType::STATISTICS:
return m.to_bytes(stats_);
  case (int32_t)LedgerEntryType::ACCOUNT_LIMITS:
return m.to_bytes(accountLimits_);
  case (int32_t)LedgerEntryType::ASSET_PAIR:
return m.to_bytes(assetPair_);
  case (int32_t)LedgerEntryType::OFFER_ENTRY:
return m.to_bytes(offer_);
  case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
return m.to_bytes(reviewableRequest_);
  case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
return m.to_bytes(externalSystemAccountID_);
  case (int32_t)LedgerEntryType::SALE:
return m.to_bytes(sale_);
  case (int32_t)LedgerEntryType::KEY_VALUE:
return m.to_bytes(keyValue_);
  case (int32_t)LedgerEntryType::ACCOUNT_KYC:
return m.to_bytes(accountKYC_);
  case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
return m.to_bytes(externalSystemAccountIDPoolEntry_);
  case (int32_t)LedgerEntryType::LIMITS_V2:
return m.to_bytes(limitsV2_);
  case (int32_t)LedgerEntryType::STATISTICS_V2:
return m.to_bytes(statisticsV2_);
  case (int32_t)LedgerEntryType::PENDING_STATISTICS:
return m.to_bytes(pendingStatistics_);
  case (int32_t)LedgerEntryType::CONTRACT:
return m.to_bytes(contract_);
  case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
return m.to_bytes(atomicSwapAsk_);
  case (int32_t)LedgerEntryType::ACCOUNT_ROLE:
return m.to_bytes(accountRole_);
  case (int32_t)LedgerEntryType::ACCOUNT_RULE:
return m.to_bytes(accountRule_);
  case (int32_t)LedgerEntryType::SIGNER_ROLE:
return m.to_bytes(signerRole_);
  case (int32_t)LedgerEntryType::SIGNER_RULE:
return m.to_bytes(signerRule_);
  case (int32_t)LedgerEntryType::STAMP:
return m.to_bytes(stamp_);
  case (int32_t)LedgerEntryType::LICENSE:
return m.to_bytes(license_);
  case (int32_t)LedgerEntryType::POLL:
return m.to_bytes(poll_);
  case (int32_t)LedgerEntryType::VOTE:
return m.to_bytes(vote_);
  case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
return m.to_bytes(accountSpecificRule_);
}
return false;
}
void
LedgerKey::count_size(xdr::measurer& m) const
{
m.count_size(type_);
switch (type_)
{

  case (int32_t)LedgerEntryType::ACCOUNT:
return m.count_size(account_);
  case (int32_t)LedgerEntryType::SIGNER:
return m.count_size(signer_);
  case (int32_t)LedgerEntryType::FEE:
return m.count_size(feeState_);
  case (int32_t)LedgerEntryType::BALANCE:
return m.count_size(balance_);
  case (int32_t)LedgerEntryType::ASSET:
return m.count_size(asset_);
  case (int32_t)LedgerEntryType::REFERENCE_ENTRY:
return m.count_size(reference_);
  case (int32_t)LedgerEntryType::STATISTICS:
return m.count_size(stats_);
  case (int32_t)LedgerEntryType::ACCOUNT_LIMITS:
return m.count_size(accountLimits_);
  case (int32_t)LedgerEntryType::ASSET_PAIR:
return m.count_size(assetPair_);
  case (int32_t)LedgerEntryType::OFFER_ENTRY:
return m.count_size(offer_);
  case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
return m.count_size(reviewableRequest_);
  case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
return m.count_size(externalSystemAccountID_);
  case (int32_t)LedgerEntryType::SALE:
return m.count_size(sale_);
  case (int32_t)LedgerEntryType::KEY_VALUE:
return m.count_size(keyValue_);
  case (int32_t)LedgerEntryType::ACCOUNT_KYC:
return m.count_size(accountKYC_);
  case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
return m.count_size(externalSystemAccountIDPoolEntry_);
  case (int32_t)LedgerEntryType::LIMITS_V2:
return m.count_size(limitsV2_);
  case (int32_t)LedgerEntryType::STATISTICS_V2:
return m.count_size(statisticsV2_);
  case (int32_t)LedgerEntryType::PENDING_STATISTICS:
return m.count_size(pendingStatistics_);
  case (int32_t)LedgerEntryType::CONTRACT:
return m.count_size(contract_);
  case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
return m.count_size(atomicSwapAsk_);
  case (int32_t)LedgerEntryType::ACCOUNT_ROLE:
return m.count_size(accountRole_);
  case (int32_t)LedgerEntryType::ACCOUNT_RULE:
return m.count_size(accountRule_);
  case (int32_t)LedgerEntryType::SIGNER_ROLE:
return m.count_size(signerRole_);
  case (int32_t)LedgerEntryType::SIGNER_RULE:
return m.count_size(signerRule_);
  case (int32_t)LedgerEntryType::STAMP:
return m.count_size(stamp_);
  case (int32_t)LedgerEntryType::LICENSE:
return m.count_size(license_);
  case (int32_t)LedgerEntryType::POLL:
return m.count_size(poll_);
  case (int32_t)LedgerEntryType::VOTE:
return m.count_size(vote_);
  case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
return m.count_size(accountSpecificRule_);
}
}
bool
LedgerKey::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<LedgerKey const&>(other_abstract);
if (other.type_ != type_) return false;
switch (type_)
{
  case (int32_t)LedgerEntryType::ACCOUNT:
return account_ == other.account_;
  case (int32_t)LedgerEntryType::SIGNER:
return signer_ == other.signer_;
  case (int32_t)LedgerEntryType::FEE:
return feeState_ == other.feeState_;
  case (int32_t)LedgerEntryType::BALANCE:
return balance_ == other.balance_;
  case (int32_t)LedgerEntryType::ASSET:
return asset_ == other.asset_;
  case (int32_t)LedgerEntryType::REFERENCE_ENTRY:
return reference_ == other.reference_;
  case (int32_t)LedgerEntryType::STATISTICS:
return stats_ == other.stats_;
  case (int32_t)LedgerEntryType::ACCOUNT_LIMITS:
return accountLimits_ == other.accountLimits_;
  case (int32_t)LedgerEntryType::ASSET_PAIR:
return assetPair_ == other.assetPair_;
  case (int32_t)LedgerEntryType::OFFER_ENTRY:
return offer_ == other.offer_;
  case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
return reviewableRequest_ == other.reviewableRequest_;
  case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
return externalSystemAccountID_ == other.externalSystemAccountID_;
  case (int32_t)LedgerEntryType::SALE:
return sale_ == other.sale_;
  case (int32_t)LedgerEntryType::KEY_VALUE:
return keyValue_ == other.keyValue_;
  case (int32_t)LedgerEntryType::ACCOUNT_KYC:
return accountKYC_ == other.accountKYC_;
  case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
return externalSystemAccountIDPoolEntry_ == other.externalSystemAccountIDPoolEntry_;
  case (int32_t)LedgerEntryType::LIMITS_V2:
return limitsV2_ == other.limitsV2_;
  case (int32_t)LedgerEntryType::STATISTICS_V2:
return statisticsV2_ == other.statisticsV2_;
  case (int32_t)LedgerEntryType::PENDING_STATISTICS:
return pendingStatistics_ == other.pendingStatistics_;
  case (int32_t)LedgerEntryType::CONTRACT:
return contract_ == other.contract_;
  case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
return atomicSwapAsk_ == other.atomicSwapAsk_;
  case (int32_t)LedgerEntryType::ACCOUNT_ROLE:
return accountRole_ == other.accountRole_;
  case (int32_t)LedgerEntryType::ACCOUNT_RULE:
return accountRule_ == other.accountRule_;
  case (int32_t)LedgerEntryType::SIGNER_ROLE:
return signerRole_ == other.signerRole_;
  case (int32_t)LedgerEntryType::SIGNER_RULE:
return signerRule_ == other.signerRule_;
  case (int32_t)LedgerEntryType::STAMP:
return stamp_ == other.stamp_;
  case (int32_t)LedgerEntryType::LICENSE:
return license_ == other.license_;
  case (int32_t)LedgerEntryType::POLL:
return poll_ == other.poll_;
  case (int32_t)LedgerEntryType::VOTE:
return vote_ == other.vote_;
  case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
return accountSpecificRule_ == other.accountSpecificRule_;
}
return false;
}
bool
LedgerKey::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<LedgerKey const&>(other_abstract);
if (type_ < other.type_) return true;
if (other.type_ < type_) return false;
switch (type_)
{
  case (int32_t)LedgerEntryType::ACCOUNT:
return account_ < other.account_;
  case (int32_t)LedgerEntryType::SIGNER:
return signer_ < other.signer_;
  case (int32_t)LedgerEntryType::FEE:
return feeState_ < other.feeState_;
  case (int32_t)LedgerEntryType::BALANCE:
return balance_ < other.balance_;
  case (int32_t)LedgerEntryType::ASSET:
return asset_ < other.asset_;
  case (int32_t)LedgerEntryType::REFERENCE_ENTRY:
return reference_ < other.reference_;
  case (int32_t)LedgerEntryType::STATISTICS:
return stats_ < other.stats_;
  case (int32_t)LedgerEntryType::ACCOUNT_LIMITS:
return accountLimits_ < other.accountLimits_;
  case (int32_t)LedgerEntryType::ASSET_PAIR:
return assetPair_ < other.assetPair_;
  case (int32_t)LedgerEntryType::OFFER_ENTRY:
return offer_ < other.offer_;
  case (int32_t)LedgerEntryType::REVIEWABLE_REQUEST:
return reviewableRequest_ < other.reviewableRequest_;
  case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
return externalSystemAccountID_ < other.externalSystemAccountID_;
  case (int32_t)LedgerEntryType::SALE:
return sale_ < other.sale_;
  case (int32_t)LedgerEntryType::KEY_VALUE:
return keyValue_ < other.keyValue_;
  case (int32_t)LedgerEntryType::ACCOUNT_KYC:
return accountKYC_ < other.accountKYC_;
  case (int32_t)LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
return externalSystemAccountIDPoolEntry_ < other.externalSystemAccountIDPoolEntry_;
  case (int32_t)LedgerEntryType::LIMITS_V2:
return limitsV2_ < other.limitsV2_;
  case (int32_t)LedgerEntryType::STATISTICS_V2:
return statisticsV2_ < other.statisticsV2_;
  case (int32_t)LedgerEntryType::PENDING_STATISTICS:
return pendingStatistics_ < other.pendingStatistics_;
  case (int32_t)LedgerEntryType::CONTRACT:
return contract_ < other.contract_;
  case (int32_t)LedgerEntryType::ATOMIC_SWAP_ASK:
return atomicSwapAsk_ < other.atomicSwapAsk_;
  case (int32_t)LedgerEntryType::ACCOUNT_ROLE:
return accountRole_ < other.accountRole_;
  case (int32_t)LedgerEntryType::ACCOUNT_RULE:
return accountRule_ < other.accountRule_;
  case (int32_t)LedgerEntryType::SIGNER_ROLE:
return signerRole_ < other.signerRole_;
  case (int32_t)LedgerEntryType::SIGNER_RULE:
return signerRule_ < other.signerRule_;
  case (int32_t)LedgerEntryType::STAMP:
return stamp_ < other.stamp_;
  case (int32_t)LedgerEntryType::LICENSE:
return license_ < other.license_;
  case (int32_t)LedgerEntryType::POLL:
return poll_ < other.poll_;
  case (int32_t)LedgerEntryType::VOTE:
return vote_ < other.vote_;
  case (int32_t)LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
return accountSpecificRule_ < other.accountSpecificRule_;
}
return false;
}
}