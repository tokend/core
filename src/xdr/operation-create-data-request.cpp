#include "operation-create-data-request.h"
#include "cpp-serialize/src/unmarshaler.h"
#include "cpp-serialize/src/marshaler.h"
#include "cpp-serialize/src/measurer.h"
#include "cpp-serialize/src/unmarshaler.t.hpp"
#include "cpp-serialize/src/marshaler.t.hpp"
#include "cpp-serialize/src/measurer.t.hpp"
using namespace xdr;
namespace stellar {
bool
CreateDataRequestOp::from_bytes(xdr::unmarshaler& u) 
{
bool okcreateDataRequest = u.from_bytes(createDataRequest);
if (!okcreateDataRequest)
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
CreateDataRequestOp::to_bytes(xdr::marshaler& m) const 
{
bool okcreateDataRequest = m.to_bytes(createDataRequest);
if (!okcreateDataRequest)
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
CreateDataRequestOp::count_size(xdr::measurer& m) const 
{
m.count_size(createDataRequest);
m.count_size(allTasks);
m.count_size(ext);
}
bool
CreateDataRequestOp::operator==(xdr::xdr_abstract const& other_abstract) const 
{
if (typeid(*this) != typeid(other_abstract))
{
return false;
}auto& other = dynamic_cast<CreateDataRequestOp const&>(other_abstract);return true
&& (createDataRequest== other.createDataRequest)
&& (allTasks== other.allTasks)
&& (ext== other.ext)
;}
bool
CreateDataRequestOp::operator<(xdr_abstract const& other_abstract) const
{
if (typeid(*this) != typeid(other_abstract))
{
throw std::runtime_error("unexpected operator< invoke");
}
auto& other = dynamic_cast<CreateDataRequestOp const&>(other_abstract);
if (createDataRequest < other.createDataRequest) return true;
if (other.createDataRequest < createDataRequest) return false;
if (allTasks < other.allTasks) return true;
if (other.allTasks < allTasks) return false;
if (ext < other.ext) return true;
if (other.ext < ext) return false;
return false;
}}