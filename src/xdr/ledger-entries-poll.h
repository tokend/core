// -*- C++ -*-
// Automatically generated from ledger-entries-poll.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_LEDGER_ENTRIES_POLL_H_INCLUDED__
#define __XDR_LEDGER_ENTRIES_POLL_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"

namespace stellar {

enum class PollType : std::int32_t {
  SINGLE_CHOICE = 0,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::PollType>
  : xdr_integral_base<::stellar::PollType, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::PollType val) {
    switch (val) {
    case ::stellar::PollType::SINGLE_CHOICE:
      return "SINGLE_CHOICE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::PollType::SINGLE_CHOICE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct PollData : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<PollType>::case_type;
private:
  _xdr_case_type type_;
  union {
    EmptyExt ext_;
  };

public:
  static constexpr const bool _xdr_has_default_case = false;
  static const std::vector<PollType> &_xdr_case_values() {
    static const std::vector<PollType> _xdr_disc_vec {
      PollType::SINGLE_CHOICE
    };
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)PollType::SINGLE_CHOICE ? 1
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)PollType::SINGLE_CHOICE:
      _f(&PollData::ext_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return type_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of type in PollData");
    if (fnum != _xdr_field_number(type_)) {
      this->~PollData();
      type_ = which;switch (type_)
{
      case (int32_t)PollType::SINGLE_CHOICE:
new(&ext_) EmptyExt{};
break;
}

    }
    else
      type_ = which;
  }
  explicit PollData(PollType which = PollType{}) : type_((int32_t)which) {
    switch (type_)
{
    case (int32_t)PollType::SINGLE_CHOICE:
new(&ext_) EmptyExt{};
break;
}

  }
  PollData(const PollData &source) : type_(source.type_) {
    switch (type_)
{
    case (int32_t)PollType::SINGLE_CHOICE:
new(&ext_) EmptyExt(source.ext_);
break;
}

  }
  PollData(PollData &&source) : type_(source.type_) {
    switch (type_)
{
    case (int32_t)PollType::SINGLE_CHOICE:
new(&ext_) EmptyExt(std::move(source.ext_));
break;
}

  }
  ~PollData() {
switch (type_)
{
  case (int32_t)PollType::SINGLE_CHOICE:
ext_.~EmptyExt();
break;
}
}

  PollData &operator=(const PollData &source) {
    if (type_ == source.type_)
{
switch (type_)
{
    case (int32_t)PollType::SINGLE_CHOICE:
ext_ = source.ext_;
break;
}
}
else {this->~PollData();
    type_ = source.type_;
switch (type_)
{
    case (int32_t)PollType::SINGLE_CHOICE:
new(&ext_) EmptyExt(source.ext_);
break;
}
}
    return *this;
  }
  PollData &operator=(PollData &&source) {
    if (type_ == source.type_)
{
switch (type_)
{
    case (int32_t)PollType::SINGLE_CHOICE:
ext_ = std::move(source.ext_);
break;
}
}
else {this->~PollData();
    type_ = std::move(source.type_);
switch (type_)
{
    case (int32_t)PollType::SINGLE_CHOICE:
new(&ext_) EmptyExt(std::move(source.ext_));
break;
}
}
    return *this;
  }

  PollType type() const { return PollType(type_); }
  PollData &type(PollType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  EmptyExt &ext() {
    if (_xdr_field_number(type_) == 1)
      return ext_;
    throw xdr::xdr_wrong_union("PollData: ext accessed when not selected");
  }
  const EmptyExt &ext() const {
    if (_xdr_field_number(type_) == 1)
      return ext_;
    throw xdr::xdr_wrong_union("PollData: ext accessed when not selected");
  }bool
operator==(xdr::xdr_abstract const& other) const override;
bool
operator<(xdr::xdr_abstract const& other) const override;
private:
  bool
from_bytes(xdr::unmarshaler& u) override;
bool
to_bytes(xdr::marshaler& m) const override;
void
count_size(xdr::measurer& m) const override;

};

struct PollEntry  : xdr::xdr_abstract {
  uint64 id{};
  uint32 permissionType{};
  uint32 numberOfChoices{};
  PollData data{};
  uint64 startTime{};
  uint64 endTime{};
  AccountID ownerID{};
  AccountID resultProviderID{};
  bool voteConfirmationRequired{};
  longstring details{};
  EmptyExt ext{};

  PollEntry() = default;
  template<typename _id_T,
           typename _permissionType_T,
           typename _numberOfChoices_T,
           typename _data_T,
           typename _startTime_T,
           typename _endTime_T,
           typename _ownerID_T,
           typename _resultProviderID_T,
           typename _voteConfirmationRequired_T,
           typename _details_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _id_T>::value
                          && std::is_constructible<uint32, _permissionType_T>::value
                          && std::is_constructible<uint32, _numberOfChoices_T>::value
                          && std::is_constructible<PollData, _data_T>::value
                          && std::is_constructible<uint64, _startTime_T>::value
                          && std::is_constructible<uint64, _endTime_T>::value
                          && std::is_constructible<AccountID, _ownerID_T>::value
                          && std::is_constructible<AccountID, _resultProviderID_T>::value
                          && std::is_constructible<bool, _voteConfirmationRequired_T>::value
                          && std::is_constructible<longstring, _details_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit PollEntry(_id_T &&_id,
                     _permissionType_T &&_permissionType,
                     _numberOfChoices_T &&_numberOfChoices,
                     _data_T &&_data,
                     _startTime_T &&_startTime,
                     _endTime_T &&_endTime,
                     _ownerID_T &&_ownerID,
                     _resultProviderID_T &&_resultProviderID,
                     _voteConfirmationRequired_T &&_voteConfirmationRequired,
                     _details_T &&_details,
                     _ext_T &&_ext)
    : id(std::forward<_id_T>(_id)),
      permissionType(std::forward<_permissionType_T>(_permissionType)),
      numberOfChoices(std::forward<_numberOfChoices_T>(_numberOfChoices)),
      data(std::forward<_data_T>(_data)),
      startTime(std::forward<_startTime_T>(_startTime)),
      endTime(std::forward<_endTime_T>(_endTime)),
      ownerID(std::forward<_ownerID_T>(_ownerID)),
      resultProviderID(std::forward<_resultProviderID_T>(_resultProviderID)),
      voteConfirmationRequired(std::forward<_voteConfirmationRequired_T>(_voteConfirmationRequired)),
      details(std::forward<_details_T>(_details)),
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

#endif // !__XDR_LEDGER_ENTRIES_POLL_H_INCLUDED__
