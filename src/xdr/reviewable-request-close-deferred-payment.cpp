#include "reviewable-request-close-deferred-payment.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
CloseDeferredPaymentRequest::from_bytes(xdr::unmarshaler& u) 
{
bool okdeferredPaymentID = u.from_bytes(deferredPaymentID);
if (!okdeferredPaymentID)
{
return false;
}
bool okdestination = u.from_bytes(destination);
if (!okdestination)
{
return false;
}
bool okdestinationBalance = u.from_bytes(destinationBalance);
if (!okdestinationBalance)
{
return false;
}
bool okcreatorDetails = u.from_bytes(creatorDetails);
if (!okcreatorDetails)
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
bool oksequenceNumber = u.from_bytes(sequenceNumber);
if (!oksequenceNumber)
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
CloseDeferredPaymentRequest::to_bytes(xdr::marshaler& m) const 
{
bool okdeferredPaymentID = m.to_bytes(deferredPaymentID);
if (!okdeferredPaymentID)
{
return false;
}
bool okdestination = m.to_bytes(destination);
if (!okdestination)
{
return false;
}
bool okdestinationBalance = m.to_bytes(destinationBalance);
if (!okdestinationBalance)
{
return false;
}
bool okcreatorDetails = m.to_bytes(creatorDetails);
if (!okcreatorDetails)
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
bool oksequenceNumber = m.to_bytes(sequenceNumber);
if (!oksequenceNumber)
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
CloseDeferredPaymentRequest::count_size(xdr::measurer& m) const 
{
m.count_size(deferredPaymentID);
m.count_size(destination);
m.count_size(destinationBalance);
m.count_size(creatorDetails);
m.count_size(amount);
m.count_size(feeData);
m.count_size(sequenceNumber);
m.count_size(ext);
}
bool
CloseDeferredPaymentRequest::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CloseDeferredPaymentRequest const&>(other_abstract);return true
&& (deferredPaymentID== other.deferredPaymentID)
&& (destination== other.destination)
&& (destinationBalance== other.destinationBalance)
&& (creatorDetails== other.creatorDetails)
&& (amount== other.amount)
&& (feeData== other.feeData)
&& (sequenceNumber== other.sequenceNumber)
&& (ext== other.ext)
;}
bool
CloseDeferredPaymentRequest::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CloseDeferredPaymentRequest const&>(other_abstract);
if (deferredPaymentID < other.deferredPaymentID) return true;
if (other.deferredPaymentID < deferredPaymentID) return false;
if (destination < other.destination) return true;
if (other.destination < destination) return false;
if (destinationBalance < other.destinationBalance) return true;
if (other.destinationBalance < destinationBalance) return false;
if (creatorDetails < other.creatorDetails) return true;
if (other.creatorDetails < creatorDetails) return false;
if (amount < other.amount) return true;
if (other.amount < amount) return false;
if (feeData < other.feeData) return true;
if (other.feeData < feeData) return false;
if (sequenceNumber < other.sequenceNumber) return true;
if (other.sequenceNumber < sequenceNumber) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}