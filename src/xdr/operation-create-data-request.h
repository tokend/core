// -*- C++ -*-
// Automatically generated from operation-create-data-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_CREATE_DATA_REQUEST_H_INCLUDED__
#define __XDR_OPERATION_CREATE_DATA_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/reviewable-request-create-data.h"

namespace stellar {

struct CreateDataRequestOp  : xdr::xdr_abstract {
  CreateDataRequest createDataRequest{};
  xdr::pointer<uint32> allTasks{};
  EmptyExt ext{};

  CreateDataRequestOp() = default;
  template<typename _createDataRequest_T,
           typename _allTasks_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<CreateDataRequest, _createDataRequest_T>::value
                          && std::is_constructible<xdr::pointer<uint32>, _allTasks_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit CreateDataRequestOp(_createDataRequest_T &&_createDataRequest,
                               _allTasks_T &&_allTasks,
                               _ext_T &&_ext)
    : createDataRequest(std::forward<_createDataRequest_T>(_createDataRequest)),
      allTasks(std::forward<_allTasks_T>(_allTasks)),
      ext(std::forward<_ext_T>(_ext)) {}
  bool
operator==(xdr::xdr_abstract const& other) const override;bool
operator<(xdr::xdr_abstract const& other) const override;private:
  bool
from_bytes(xdr::unmarshaler& u) override;
bool
to_bytes(xdr::marshaler& m) const override;
void
count_size(xdr::measurer& m) const override;

};

}

#endif // !__XDR_OPERATION_CREATE_DATA_REQUEST_H_INCLUDED__
