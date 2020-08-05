#include "operation-update-data-request.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
UpdateDataRequestOp::from_bytes(xdr::unmarshaler& u) 
{
bool okupdateDataRequest = u.from_bytes(updateDataRequest);
if (!okupdateDataRequest)
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
UpdateDataRequestOp::to_bytes(xdr::marshaler& m) const 
{
bool okupdateDataRequest = m.to_bytes(updateDataRequest);
if (!okupdateDataRequest)
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
UpdateDataRequestOp::count_size(xdr::measurer& m) const 
{
m.count_size(updateDataRequest);
m.count_size(allTasks);
m.count_size(ext);
}
bool
UpdateDataRequestOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<UpdateDataRequestOp const&>(other_abstract);return true
&& (updateDataRequest== other.updateDataRequest)
&& (allTasks== other.allTasks)
&& (ext== other.ext)
;}
bool
UpdateDataRequestOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<UpdateDataRequestOp const&>(other_abstract);
if (updateDataRequest < other.updateDataRequest) return true;
if (other.updateDataRequest < updateDataRequest) return false;
if (allTasks < other.allTasks) return true;
if (other.allTasks < allTasks) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}