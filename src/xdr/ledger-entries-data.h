// -*- C++ -*-
// Automatically generated from ledger-entries-data.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_LEDGER_ENTRIES_DATA_H_INCLUDED__
#define __XDR_LEDGER_ENTRIES_DATA_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"

namespace stellar {

struct DataEntry  : xdr::xdr_abstract {
  uint64 id{};
  uint64 type{};
  longstring value{};
  AccountID owner{};
  EmptyExt ext{};

  DataEntry() = default;
  template<typename _id_T,
           typename _type_T,
           typename _value_T,
           typename _owner_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _id_T>::value
                          && std::is_constructible<uint64, _type_T>::value
                          && std::is_constructible<longstring, _value_T>::value
                          && std::is_constructible<AccountID, _owner_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit DataEntry(_id_T &&_id,
                     _type_T &&_type,
                     _value_T &&_value,
                     _owner_T &&_owner,
                     _ext_T &&_ext)
    : id(std::forward<_id_T>(_id)),
      type(std::forward<_type_T>(_type)),
      value(std::forward<_value_T>(_value)),
      owner(std::forward<_owner_T>(_owner)),
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

#endif // !__XDR_LEDGER_ENTRIES_DATA_H_INCLUDED__
