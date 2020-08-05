// -*- C++ -*-
// Automatically generated from operation-remove-data-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_REMOVE_DATA_REQUEST_H_INCLUDED__
#define __XDR_OPERATION_REMOVE_DATA_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/reviewable-request-remove-data.h"

namespace stellar {

struct RemoveDataRequestOp  : xdr::xdr_abstract {
  RemoveDataRequest removeDataRequest{};
  xdr::pointer<uint32> allTasks{};
  EmptyExt ext{};

  RemoveDataRequestOp() = default;
  template<typename _removeDataRequest_T,
           typename _allTasks_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<RemoveDataRequest, _removeDataRequest_T>::value
                          && std::is_constructible<xdr::pointer<uint32>, _allTasks_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit RemoveDataRequestOp(_removeDataRequest_T &&_removeDataRequest,
                               _allTasks_T &&_allTasks,
                               _ext_T &&_ext)
    : removeDataRequest(std::forward<_removeDataRequest_T>(_removeDataRequest)),
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

#endif // !__XDR_OPERATION_REMOVE_DATA_REQUEST_H_INCLUDED__
