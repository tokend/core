#include "types.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
EmptyExt::from_bytes(xdr::unmarshaler& u) 
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
EmptyExt::to_bytes(xdr::marshaler& m) const
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
EmptyExt::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

  case (int32_t)LedgerVersion::EMPTY_VERSION:
  
  return;
}
}
bool
EmptyExt::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<EmptyExt const&>(other_abstract);
if (other.v_ != v_) return false;
switch (v_)
{
  case (int32_t)LedgerVersion::EMPTY_VERSION:
  
  return true;
}
return false;
}
bool
EmptyExt::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<EmptyExt const&>(other_abstract);
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
PublicKey::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(type_);
if (!ok)
{
return false;
}
switch (type_)
{

  case (int32_t)CryptoKeyType::KEY_TYPE_ED25519:
return u.from_bytes(ed25519_);
}
return false;
}
bool
PublicKey::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(type_);
if (!ok)
{
return false;
}
switch (type_)
{

  case (int32_t)CryptoKeyType::KEY_TYPE_ED25519:
return m.to_bytes(ed25519_);
}
return false;
}
void
PublicKey::count_size(xdr::measurer& m) const
{
m.count_size(type_);
switch (type_)
{

  case (int32_t)CryptoKeyType::KEY_TYPE_ED25519:
return m.count_size(ed25519_);
}
}
bool
PublicKey::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<PublicKey const&>(other_abstract);
if (other.type_ != type_) return false;
switch (type_)
{
  case (int32_t)CryptoKeyType::KEY_TYPE_ED25519:
return ed25519_ == other.ed25519_;
}
return false;
}
bool
PublicKey::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<PublicKey const&>(other_abstract);
if (type_ < other.type_) return true;
if (other.type_ < type_) return false;
switch (type_)
{
  case (int32_t)CryptoKeyType::KEY_TYPE_ED25519:
return ed25519_ < other.ed25519_;
}
return false;
}
bool
Curve25519Secret::from_bytes(xdr::unmarshaler& u) 
{
bool okkey = u.from_bytes(key);
if (!okkey)
{
return false;
}
return true;
}
bool
Curve25519Secret::to_bytes(xdr::marshaler& m) const 
{
bool okkey = m.to_bytes(key);
if (!okkey)
{
return false;
}
return true;
}
void
Curve25519Secret::count_size(xdr::measurer& m) const 
{
m.count_size(key);
}
bool
Curve25519Secret::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<Curve25519Secret const&>(other_abstract);return true
&& (key== other.key)
;}
bool
Curve25519Secret::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<Curve25519Secret const&>(other_abstract);
if (key < other.key) return true;
if (other.key < key) return false;
return false;
}bool
Curve25519Public::from_bytes(xdr::unmarshaler& u) 
{
bool okkey = u.from_bytes(key);
if (!okkey)
{
return false;
}
return true;
}
bool
Curve25519Public::to_bytes(xdr::marshaler& m) const 
{
bool okkey = m.to_bytes(key);
if (!okkey)
{
return false;
}
return true;
}
void
Curve25519Public::count_size(xdr::measurer& m) const 
{
m.count_size(key);
}
bool
Curve25519Public::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<Curve25519Public const&>(other_abstract);return true
&& (key== other.key)
;}
bool
Curve25519Public::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<Curve25519Public const&>(other_abstract);
if (key < other.key) return true;
if (other.key < key) return false;
return false;
}bool
HmacSha256Key::from_bytes(xdr::unmarshaler& u) 
{
bool okkey = u.from_bytes(key);
if (!okkey)
{
return false;
}
return true;
}
bool
HmacSha256Key::to_bytes(xdr::marshaler& m) const 
{
bool okkey = m.to_bytes(key);
if (!okkey)
{
return false;
}
return true;
}
void
HmacSha256Key::count_size(xdr::measurer& m) const 
{
m.count_size(key);
}
bool
HmacSha256Key::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<HmacSha256Key const&>(other_abstract);return true
&& (key== other.key)
;}
bool
HmacSha256Key::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<HmacSha256Key const&>(other_abstract);
if (key < other.key) return true;
if (other.key < key) return false;
return false;
}bool
HmacSha256Mac::from_bytes(xdr::unmarshaler& u) 
{
bool okmac = u.from_bytes(mac);
if (!okmac)
{
return false;
}
return true;
}
bool
HmacSha256Mac::to_bytes(xdr::marshaler& m) const 
{
bool okmac = m.to_bytes(mac);
if (!okmac)
{
return false;
}
return true;
}
void
HmacSha256Mac::count_size(xdr::measurer& m) const 
{
m.count_size(mac);
}
bool
HmacSha256Mac::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<HmacSha256Mac const&>(other_abstract);return true
&& (mac== other.mac)
;}
bool
HmacSha256Mac::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<HmacSha256Mac const&>(other_abstract);
if (mac < other.mac) return true;
if (other.mac < mac) return false;
return false;
}bool
Fee::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
Fee::_ext_t::to_bytes(xdr::marshaler& m) const
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
Fee::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
Fee::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
Fee::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
Fee::from_bytes(xdr::unmarshaler& u) 
{
bool okfixed = u.from_bytes(fixed);
if (!okfixed)
{
return false;
}
bool okpercent = u.from_bytes(percent);
if (!okpercent)
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
Fee::to_bytes(xdr::marshaler& m) const 
{
bool okfixed = m.to_bytes(fixed);
if (!okfixed)
{
return false;
}
bool okpercent = m.to_bytes(percent);
if (!okpercent)
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
Fee::count_size(xdr::measurer& m) const 
{
m.count_size(fixed);
m.count_size(percent);
m.count_size(ext);
}
bool
Fee::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<Fee const&>(other_abstract);return true
&& (fixed== other.fixed)
&& (percent== other.percent)
&& (ext== other.ext)
;}
bool
Fee::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<Fee const&>(other_abstract);
if (fixed < other.fixed) return true;
if (other.fixed < fixed) return false;
if (percent < other.percent) return true;
if (other.percent < percent) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}bool
DecoratedSignature::from_bytes(xdr::unmarshaler& u) 
{
bool okhint = u.from_bytes(hint);
if (!okhint)
{
return false;
}
bool oksignature = u.from_bytes(signature);
if (!oksignature)
{
return false;
}
return true;
}
bool
DecoratedSignature::to_bytes(xdr::marshaler& m) const 
{
bool okhint = m.to_bytes(hint);
if (!okhint)
{
return false;
}
bool oksignature = m.to_bytes(signature);
if (!oksignature)
{
return false;
}
return true;
}
void
DecoratedSignature::count_size(xdr::measurer& m) const 
{
m.count_size(hint);
m.count_size(signature);
}
bool
DecoratedSignature::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<DecoratedSignature const&>(other_abstract);return true
&& (hint== other.hint)
&& (signature== other.signature)
;}
bool
DecoratedSignature::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<DecoratedSignature const&>(other_abstract);
if (hint < other.hint) return true;
if (other.hint < hint) return false;
if (signature < other.signature) return true;
if (other.signature < signature) return false;
return false;
}}