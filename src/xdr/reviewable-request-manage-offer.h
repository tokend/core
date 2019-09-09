// -*- C++ -*-
// Automatically generated from reviewable-request-manage-offer.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_REVIEWABLE_REQUEST_MANAGE_OFFER_H_INCLUDED__
#define __XDR_REVIEWABLE_REQUEST_MANAGE_OFFER_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/operation-manage-offer.h"

namespace stellar {

struct ManageOfferRequest  : xdr::xdr_abstract {
  ManageOfferOp op{};
  EmptyExt ext{};

  ManageOfferRequest() = default;
  template<typename _op_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<ManageOfferOp, _op_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit ManageOfferRequest(_op_T &&_op,
                              _ext_T &&_ext)
    : op(std::forward<_op_T>(_op)),
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

#endif // !__XDR_REVIEWABLE_REQUEST_MANAGE_OFFER_H_INCLUDED__
