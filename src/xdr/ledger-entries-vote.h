// -*- C++ -*-
// Automatically generated from ledger-entries-vote.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_LEDGER_ENTRIES_VOTE_H_INCLUDED__
#define __XDR_LEDGER_ENTRIES_VOTE_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"
#include "xdr/ledger-entries-poll.h"

namespace stellar {

struct SingleChoiceVote  : xdr::xdr_abstract {
  uint32 choice{};
  EmptyExt ext{};

  SingleChoiceVote() = default;
  template<typename _choice_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint32, _choice_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit SingleChoiceVote(_choice_T &&_choice,
                            _ext_T &&_ext)
    : choice(std::forward<_choice_T>(_choice)),
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

struct VoteData : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<PollType>::case_type;
private:
  _xdr_case_type pollType_;
  union {
    SingleChoiceVote single_;
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
      _f(&VoteData::single_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return pollType_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of pollType in VoteData");
    if (fnum != _xdr_field_number(pollType_)) {
      this->~VoteData();
      pollType_ = which;switch (pollType_)
{
      case (int32_t)PollType::SINGLE_CHOICE:
new(&single_) SingleChoiceVote{};
break;
}

    }
    else
      pollType_ = which;
  }
  explicit VoteData(PollType which = PollType{}) : pollType_((int32_t)which) {
    switch (pollType_)
{
    case (int32_t)PollType::SINGLE_CHOICE:
new(&single_) SingleChoiceVote{};
break;
}

  }
  VoteData(const VoteData &source) : pollType_(source.pollType_) {
    switch (pollType_)
{
    case (int32_t)PollType::SINGLE_CHOICE:
new(&single_) SingleChoiceVote(source.single_);
break;
}

  }
  VoteData(VoteData &&source) : pollType_(source.pollType_) {
    switch (pollType_)
{
    case (int32_t)PollType::SINGLE_CHOICE:
new(&single_) SingleChoiceVote(std::move(source.single_));
break;
}

  }
  ~VoteData() {
switch (pollType_)
{
  case (int32_t)PollType::SINGLE_CHOICE:
single_.~SingleChoiceVote();
break;
}
}

  VoteData &operator=(const VoteData &source) {
    if (pollType_ == source.pollType_)
{
switch (pollType_)
{
    case (int32_t)PollType::SINGLE_CHOICE:
single_ = source.single_;
break;
}
}
else {this->~VoteData();
    pollType_ = source.pollType_;
switch (pollType_)
{
    case (int32_t)PollType::SINGLE_CHOICE:
new(&single_) SingleChoiceVote(source.single_);
break;
}
}
    return *this;
  }
  VoteData &operator=(VoteData &&source) {
    if (pollType_ == source.pollType_)
{
switch (pollType_)
{
    case (int32_t)PollType::SINGLE_CHOICE:
single_ = std::move(source.single_);
break;
}
}
else {this->~VoteData();
    pollType_ = std::move(source.pollType_);
switch (pollType_)
{
    case (int32_t)PollType::SINGLE_CHOICE:
new(&single_) SingleChoiceVote(std::move(source.single_));
break;
}
}
    return *this;
  }

  PollType pollType() const { return PollType(pollType_); }
  VoteData &pollType(PollType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  SingleChoiceVote &single() {
    if (_xdr_field_number(pollType_) == 1)
      return single_;
    throw xdr::xdr_wrong_union("VoteData: single accessed when not selected");
  }
  const SingleChoiceVote &single() const {
    if (_xdr_field_number(pollType_) == 1)
      return single_;
    throw xdr::xdr_wrong_union("VoteData: single accessed when not selected");
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

struct VoteEntry  : xdr::xdr_abstract {
  uint64 pollID{};
  AccountID voterID{};
  VoteData data{};
  EmptyExt ext{};

  VoteEntry() = default;
  template<typename _pollID_T,
           typename _voterID_T,
           typename _data_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _pollID_T>::value
                          && std::is_constructible<AccountID, _voterID_T>::value
                          && std::is_constructible<VoteData, _data_T>::value
                          && std::is_constructible<EmptyExt, _ext_T>::value
                         >::type>
  explicit VoteEntry(_pollID_T &&_pollID,
                     _voterID_T &&_voterID,
                     _data_T &&_data,
                     _ext_T &&_ext)
    : pollID(std::forward<_pollID_T>(_pollID)),
      voterID(std::forward<_voterID_T>(_voterID)),
      data(std::forward<_data_T>(_data)),
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

#endif // !__XDR_LEDGER_ENTRIES_VOTE_H_INCLUDED__
