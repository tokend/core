#include "ledger-entries-key-value.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
KeyValueEntryValue::from_bytes(xdr::unmarshaler& u) 
{
bool ok = u.from_bytes(type_);
if (!ok)
{
return false;
}
switch (type_)
{

  case (int32_t)KeyValueEntryType::UINT32:
return u.from_bytes(ui32Value_);
  case (int32_t)KeyValueEntryType::STRING:
return u.from_bytes(stringValue_);
  case (int32_t)KeyValueEntryType::UINT64:
return u.from_bytes(ui64Value_);
}
return false;
}
bool
KeyValueEntryValue::to_bytes(xdr::marshaler& m) const
{
bool ok = m.to_bytes(type_);
if (!ok)
{
return false;
}
switch (type_)
{

  case (int32_t)KeyValueEntryType::UINT32:
return m.to_bytes(ui32Value_);
  case (int32_t)KeyValueEntryType::STRING:
return m.to_bytes(stringValue_);
  case (int32_t)KeyValueEntryType::UINT64:
return m.to_bytes(ui64Value_);
}
return false;
}
void
KeyValueEntryValue::count_size(xdr::measurer& m) const
{
m.count_size(type_);
switch (type_)
{

  case (int32_t)KeyValueEntryType::UINT32:
return m.count_size(ui32Value_);
  case (int32_t)KeyValueEntryType::STRING:
return m.count_size(stringValue_);
  case (int32_t)KeyValueEntryType::UINT64:
return m.count_size(ui64Value_);
}
}
bool
KeyValueEntryValue::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}
auto& other = dynamic_cast<KeyValueEntryValue const&>(other_abstract);
if (other.type_ != type_) return false;
switch (type_)
{
  case (int32_t)KeyValueEntryType::UINT32:
return ui32Value_ == other.ui32Value_;
  case (int32_t)KeyValueEntryType::STRING:
return stringValue_ == other.stringValue_;
  case (int32_t)KeyValueEntryType::UINT64:
return ui64Value_ == other.ui64Value_;
}
return false;
}
bool
KeyValueEntryValue::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<KeyValueEntryValue const&>(other_abstract);
if (type_ < other.type_) return true;
if (other.type_ < type_) return false;
switch (type_)
{
  case (int32_t)KeyValueEntryType::UINT32:
return ui32Value_ < other.ui32Value_;
  case (int32_t)KeyValueEntryType::STRING:
return stringValue_ < other.stringValue_;
  case (int32_t)KeyValueEntryType::UINT64:
return ui64Value_ < other.ui64Value_;
}
return false;
}
bool
KeyValueEntry::_ext_t::from_bytes(xdr::unmarshaler& u) 
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
KeyValueEntry::_ext_t::to_bytes(xdr::marshaler& m) const
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
KeyValueEntry::_ext_t::count_size(xdr::measurer& m) const
{
m.count_size(v_);
switch (v_)
{

    case (int32_t)LedgerVersion::EMPTY_VERSION:
    
  return;
}
}
bool
KeyValueEntry::_ext_t::operator==(xdr::xdr_abstract const& other_abstract) const 
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
KeyValueEntry::_ext_t::operator<(xdr_abstract const& other_abstract) const
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
KeyValueEntry::from_bytes(xdr::unmarshaler& u) 
{
bool okkey = u.from_bytes(key);
if (!okkey)
{
return false;
}
bool okvalue = u.from_bytes(value);
if (!okvalue)
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
KeyValueEntry::to_bytes(xdr::marshaler& m) const 
{
bool okkey = m.to_bytes(key);
if (!okkey)
{
return false;
}
bool okvalue = m.to_bytes(value);
if (!okvalue)
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
KeyValueEntry::count_size(xdr::measurer& m) const 
{
m.count_size(key);
m.count_size(value);
m.count_size(ext);
}
bool
KeyValueEntry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<KeyValueEntry const&>(other_abstract);return true
&& (key== other.key)
&& (value== other.value)
&& (ext== other.ext)
;}
bool
KeyValueEntry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<KeyValueEntry const&>(other_abstract);
if (key < other.key) return true;
if (other.key < key) return false;
if (value < other.value) return true;
if (other.value < value) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}