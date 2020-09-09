#include "ledger-entries-deferred-payment.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
DeferredPaymentEntry::from_bytes(xdr::unmarshaler& u) 
{
bool okid = u.from_bytes(id);
if (!okid)
{
return false;
}
bool okamount = u.from_bytes(amount);
if (!okamount)
{
return false;
}
bool okfeeData = u.from_bytes(feeData);
if (!okfeeData)
{
return false;
}
bool oksource = u.from_bytes(source);
if (!oksource)
{
return false;
}
bool oksourceBalance = u.from_bytes(sourceBalance);
if (!oksourceBalance)
{
return false;
}
bool okdestination = u.from_bytes(destination);
if (!okdestination)
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
DeferredPaymentEntry::to_bytes(xdr::marshaler& m) const 
{
bool okid = m.to_bytes(id);
if (!okid)
{
return false;
}
bool okamount = m.to_bytes(amount);
if (!okamount)
{
return false;
}
bool okfeeData = m.to_bytes(feeData);
if (!okfeeData)
{
return false;
}
bool oksource = m.to_bytes(source);
if (!oksource)
{
return false;
}
bool oksourceBalance = m.to_bytes(sourceBalance);
if (!oksourceBalance)
{
return false;
}
bool okdestination = m.to_bytes(destination);
if (!okdestination)
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
DeferredPaymentEntry::count_size(xdr::measurer& m) const 
{
m.count_size(id);
m.count_size(amount);
m.count_size(feeData);
m.count_size(source);
m.count_size(sourceBalance);
m.count_size(destination);
m.count_size(ext);
}
bool
DeferredPaymentEntry::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<DeferredPaymentEntry const&>(other_abstract);return true
&& (id== other.id)
&& (amount== other.amount)
&& (feeData== other.feeData)
&& (source== other.source)
&& (sourceBalance== other.sourceBalance)
&& (destination== other.destination)
&& (ext== other.ext)
;}
bool
DeferredPaymentEntry::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<DeferredPaymentEntry const&>(other_abstract);
if (id < other.id) return true;
if (other.id < id) return false;
if (amount < other.amount) return true;
if (other.amount < amount) return false;
if (feeData < other.feeData) return true;
if (other.feeData < feeData) return false;
if (source < other.source) return true;
if (other.source < source) return false;
if (sourceBalance < other.sourceBalance) return true;
if (other.sourceBalance < sourceBalance) return false;
if (destination < other.destination) return true;
if (other.destination < destination) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}