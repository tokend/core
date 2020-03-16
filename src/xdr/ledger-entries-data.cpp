#include "ledger-entries-data.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
DataEntry::from_bytes(xdr::unmarshaler& u) 
{
bool okid = u.from_bytes(id);
if (!okid)
{
return false;
}
bool oktype = u.from_bytes(type);
if (!oktype)
{
return false;
}
bool okvalue = u.from_bytes(value);
if (!okvalue)
{
return false;
}
bool okowner = u.from_bytes(owner);
if (!okowner)
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
DataEntry::to_bytes(xdr::marshaler& m) const 
{
bool okid = m.to_bytes(id);
if (!okid)
{
return false;
}
bool oktype = m.to_bytes(type);
if (!oktype)
{
return false;
}
bool okvalue = m.to_bytes(value);
if (!okvalue)
{
return false;
}
bool okowner = m.to_bytes(owner);
if (!okowner)
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
DataEntry::count_size(xdr::measurer& m) const 
{
m.count_size(id);
m.count_size(type);
m.count_size(value);
m.count_size(owner);
m.count_size(ext);
}
bool
DataEntry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<DataEntry const&>(other_abstract);return true
&& (id== other.id)
&& (type== other.type)
&& (value== other.value)
&& (owner== other.owner)
&& (ext== other.ext)
;}
bool
DataEntry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<DataEntry const&>(other_abstract);
if (id < other.id) return true;
if (other.id < id) return false;
if (type < other.type) return true;
if (other.type < type) return false;
if (value < other.value) return true;
if (other.value < value) return false;
if (owner < other.owner) return true;
if (other.owner < owner) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}