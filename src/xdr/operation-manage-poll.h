// -*- C++ -*-
// Automatically generated from operation-manage-poll.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_MANAGE_POLL_H_INCLUDED__
#define __XDR_OPERATION_MANAGE_POLL_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"

namespace stellar {

enum class ManagePollAction : std::int32_t {
  CLOSE = 0,
  UPDATE_END_TIME = 1,
  CANCEL = 2,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManagePollAction>
  : xdr_integral_base<::stellar::ManagePollAction, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManagePollAction val) {
    switch (val) {
    case ::stellar::ManagePollAction::CLOSE:
      return "CLOSE";
    case ::stellar::ManagePollAction::UPDATE_END_TIME:
      return "UPDATE_END_TIME";
    case ::stellar::ManagePollAction::CANCEL:
      return "CANCEL";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManagePollAction::CLOSE,
      (int32_t)::stellar::ManagePollAction::UPDATE_END_TIME,
      (int32_t)::stellar::ManagePollAction::CANCEL
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

enum class PollResult : std::int32_t {
  PASSED = 0,
  FAILED = 1,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::PollResult>
  : xdr_integral_base<::stellar::PollResult, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::PollResult val) {
    switch (val) {
    case ::stellar::PollResult::PASSED:
      return "PASSED";
    case ::stellar::PollResult::FAILED:
      return "FAILED";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::PollResult::PASSED,
      (int32_t)::stellar::PollResult::FAILED
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ClosePollData  : xdr::xdr_abstract {
  struct _ext_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
  private:
    _xdr_case_type v_;
    union {
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<LedgerVersion> &_xdr_case_values() {
      static const std::vector<LedgerVersion> _xdr_disc_vec {
        LedgerVersion::EMPTY_VERSION
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)LedgerVersion::EMPTY_VERSION ? 0
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return v_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of v in _ext_t");
      if (fnum != _xdr_field_number(v_)) {
        this->~_ext_t();
        v_ = which;switch (v_)
{
        case (int32_t)LedgerVersion::EMPTY_VERSION:
          break;
}

      }
      else
        v_ = which;
    }
    explicit _ext_t(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}

    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}

    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}

    }
    ~_ext_t() {
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
      break;
}
}

    _ext_t &operator=(const _ext_t &source) {
      if (v_ == source.v_)
{
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
else {this->~_ext_t();
      v_ = source.v_;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
      return *this;
    }
    _ext_t &operator=(_ext_t &&source) {
      if (v_ == source.v_)
{
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
else {this->~_ext_t();
      v_ = std::move(source.v_);
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
      return *this;
    }

    LedgerVersion v() const { return LedgerVersion(v_); }
    _ext_t &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }
bool
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

  PollResult result{};
  longstring details{};
  _ext_t ext{};

  ClosePollData() = default;
  template<typename _result_T,
           typename _details_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<PollResult, _result_T>::value
                          && std::is_constructible<longstring, _details_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ClosePollData(_result_T &&_result,
                         _details_T &&_details,
                         _ext_T &&_ext)
    : result(std::forward<_result_T>(_result)),
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

struct UpdatePollEndTimeData  : xdr::xdr_abstract {
  struct _ext_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
  private:
    _xdr_case_type v_;
    union {
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<LedgerVersion> &_xdr_case_values() {
      static const std::vector<LedgerVersion> _xdr_disc_vec {
        LedgerVersion::EMPTY_VERSION
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)LedgerVersion::EMPTY_VERSION ? 0
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return v_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of v in _ext_t");
      if (fnum != _xdr_field_number(v_)) {
        this->~_ext_t();
        v_ = which;switch (v_)
{
        case (int32_t)LedgerVersion::EMPTY_VERSION:
          break;
}

      }
      else
        v_ = which;
    }
    explicit _ext_t(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}

    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}

    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}

    }
    ~_ext_t() {
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
      break;
}
}

    _ext_t &operator=(const _ext_t &source) {
      if (v_ == source.v_)
{
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
else {this->~_ext_t();
      v_ = source.v_;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
      return *this;
    }
    _ext_t &operator=(_ext_t &&source) {
      if (v_ == source.v_)
{
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
else {this->~_ext_t();
      v_ = std::move(source.v_);
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
      return *this;
    }

    LedgerVersion v() const { return LedgerVersion(v_); }
    _ext_t &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }
bool
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

  uint64 newEndTime{};
  _ext_t ext{};

  UpdatePollEndTimeData() = default;
  template<typename _newEndTime_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _newEndTime_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit UpdatePollEndTimeData(_newEndTime_T &&_newEndTime,
                                 _ext_T &&_ext)
    : newEndTime(std::forward<_newEndTime_T>(_newEndTime)),
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

struct ManagePollOp  : xdr::xdr_abstract {
  struct _data_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<ManagePollAction>::case_type;
  private:
    _xdr_case_type action_;
    union {
      ClosePollData closePollData_;
      UpdatePollEndTimeData updateTimeData_;
      EmptyExt ext_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<ManagePollAction> &_xdr_case_values() {
      static const std::vector<ManagePollAction> _xdr_disc_vec {
        ManagePollAction::CLOSE,
        ManagePollAction::UPDATE_END_TIME,
        ManagePollAction::CANCEL
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)ManagePollAction::CLOSE ? 1
        : which == (int32_t)ManagePollAction::UPDATE_END_TIME ? 2
        : which == (int32_t)ManagePollAction::CANCEL ? 3
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)ManagePollAction::CLOSE:
        _f(&_data_t::closePollData_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ManagePollAction::UPDATE_END_TIME:
        _f(&_data_t::updateTimeData_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ManagePollAction::CANCEL:
        _f(&_data_t::ext_, std::forward<_A>(_a)...);
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return action_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of action in _data_t");
      if (fnum != _xdr_field_number(action_)) {
        this->~_data_t();
        action_ = which;switch (action_)
{
        case (int32_t)ManagePollAction::CLOSE:
new(&closePollData_) ClosePollData{};
break;
        case (int32_t)ManagePollAction::UPDATE_END_TIME:
new(&updateTimeData_) UpdatePollEndTimeData{};
break;
        case (int32_t)ManagePollAction::CANCEL:
new(&ext_) EmptyExt{};
break;
}

      }
      else
        action_ = which;
    }
    explicit _data_t(ManagePollAction which = ManagePollAction{}) : action_((int32_t)which) {
      switch (action_)
{
      case (int32_t)ManagePollAction::CLOSE:
new(&closePollData_) ClosePollData{};
break;
      case (int32_t)ManagePollAction::UPDATE_END_TIME:
new(&updateTimeData_) UpdatePollEndTimeData{};
break;
      case (int32_t)ManagePollAction::CANCEL:
new(&ext_) EmptyExt{};
break;
}

    }
    _data_t(const _data_t &source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManagePollAction::CLOSE:
new(&closePollData_) ClosePollData(source.closePollData_);
break;
      case (int32_t)ManagePollAction::UPDATE_END_TIME:
new(&updateTimeData_) UpdatePollEndTimeData(source.updateTimeData_);
break;
      case (int32_t)ManagePollAction::CANCEL:
new(&ext_) EmptyExt(source.ext_);
break;
}

    }
    _data_t(_data_t &&source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManagePollAction::CLOSE:
new(&closePollData_) ClosePollData(std::move(source.closePollData_));
break;
      case (int32_t)ManagePollAction::UPDATE_END_TIME:
new(&updateTimeData_) UpdatePollEndTimeData(std::move(source.updateTimeData_));
break;
      case (int32_t)ManagePollAction::CANCEL:
new(&ext_) EmptyExt(std::move(source.ext_));
break;
}

    }
    ~_data_t() {
switch (action_)
{
    case (int32_t)ManagePollAction::CLOSE:
closePollData_.~ClosePollData();
break;
    case (int32_t)ManagePollAction::UPDATE_END_TIME:
updateTimeData_.~UpdatePollEndTimeData();
break;
    case (int32_t)ManagePollAction::CANCEL:
ext_.~EmptyExt();
break;
}
}

    _data_t &operator=(const _data_t &source) {
      if (action_ == source.action_)
{
switch (action_)
{
      case (int32_t)ManagePollAction::CLOSE:
closePollData_ = source.closePollData_;
break;
      case (int32_t)ManagePollAction::UPDATE_END_TIME:
updateTimeData_ = source.updateTimeData_;
break;
      case (int32_t)ManagePollAction::CANCEL:
ext_ = source.ext_;
break;
}
}
else {this->~_data_t();
      action_ = source.action_;
switch (action_)
{
      case (int32_t)ManagePollAction::CLOSE:
new(&closePollData_) ClosePollData(source.closePollData_);
break;
      case (int32_t)ManagePollAction::UPDATE_END_TIME:
new(&updateTimeData_) UpdatePollEndTimeData(source.updateTimeData_);
break;
      case (int32_t)ManagePollAction::CANCEL:
new(&ext_) EmptyExt(source.ext_);
break;
}
}
      return *this;
    }
    _data_t &operator=(_data_t &&source) {
      if (action_ == source.action_)
{
switch (action_)
{
      case (int32_t)ManagePollAction::CLOSE:
closePollData_ = std::move(source.closePollData_);
break;
      case (int32_t)ManagePollAction::UPDATE_END_TIME:
updateTimeData_ = std::move(source.updateTimeData_);
break;
      case (int32_t)ManagePollAction::CANCEL:
ext_ = std::move(source.ext_);
break;
}
}
else {this->~_data_t();
      action_ = std::move(source.action_);
switch (action_)
{
      case (int32_t)ManagePollAction::CLOSE:
new(&closePollData_) ClosePollData(std::move(source.closePollData_));
break;
      case (int32_t)ManagePollAction::UPDATE_END_TIME:
new(&updateTimeData_) UpdatePollEndTimeData(std::move(source.updateTimeData_));
break;
      case (int32_t)ManagePollAction::CANCEL:
new(&ext_) EmptyExt(std::move(source.ext_));
break;
}
}
      return *this;
    }

    ManagePollAction action() const { return ManagePollAction(action_); }
    _data_t &action(ManagePollAction _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    ClosePollData &closePollData() {
      if (_xdr_field_number(action_) == 1)
        return closePollData_;
      throw xdr::xdr_wrong_union("_data_t: closePollData accessed when not selected");
    }
    const ClosePollData &closePollData() const {
      if (_xdr_field_number(action_) == 1)
        return closePollData_;
      throw xdr::xdr_wrong_union("_data_t: closePollData accessed when not selected");
    }
    UpdatePollEndTimeData &updateTimeData() {
      if (_xdr_field_number(action_) == 2)
        return updateTimeData_;
      throw xdr::xdr_wrong_union("_data_t: updateTimeData accessed when not selected");
    }
    const UpdatePollEndTimeData &updateTimeData() const {
      if (_xdr_field_number(action_) == 2)
        return updateTimeData_;
      throw xdr::xdr_wrong_union("_data_t: updateTimeData accessed when not selected");
    }
    EmptyExt &ext() {
      if (_xdr_field_number(action_) == 3)
        return ext_;
      throw xdr::xdr_wrong_union("_data_t: ext accessed when not selected");
    }
    const EmptyExt &ext() const {
      if (_xdr_field_number(action_) == 3)
        return ext_;
      throw xdr::xdr_wrong_union("_data_t: ext accessed when not selected");
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
  struct _ext_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
  private:
    _xdr_case_type v_;
    union {
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<LedgerVersion> &_xdr_case_values() {
      static const std::vector<LedgerVersion> _xdr_disc_vec {
        LedgerVersion::EMPTY_VERSION
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)LedgerVersion::EMPTY_VERSION ? 0
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return v_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of v in _ext_t");
      if (fnum != _xdr_field_number(v_)) {
        this->~_ext_t();
        v_ = which;switch (v_)
{
        case (int32_t)LedgerVersion::EMPTY_VERSION:
          break;
}

      }
      else
        v_ = which;
    }
    explicit _ext_t(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}

    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}

    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}

    }
    ~_ext_t() {
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
      break;
}
}

    _ext_t &operator=(const _ext_t &source) {
      if (v_ == source.v_)
{
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
else {this->~_ext_t();
      v_ = source.v_;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
      return *this;
    }
    _ext_t &operator=(_ext_t &&source) {
      if (v_ == source.v_)
{
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
else {this->~_ext_t();
      v_ = std::move(source.v_);
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
      return *this;
    }

    LedgerVersion v() const { return LedgerVersion(v_); }
    _ext_t &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }
bool
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

  uint64 pollID{};
  _data_t data{};
  _ext_t ext{};

  ManagePollOp() = default;
  template<typename _pollID_T,
           typename _data_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _pollID_T>::value
                          && std::is_constructible<_data_t, _data_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ManagePollOp(_pollID_T &&_pollID,
                        _data_T &&_data,
                        _ext_T &&_ext)
    : pollID(std::forward<_pollID_T>(_pollID)),
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

enum class ManagePollResultCode : std::int32_t {
  SUCCESS = 0,
  NOT_FOUND = -1,
  POLL_NOT_READY = -2,
  NOT_AUTHORIZED_TO_CLOSE_POLL = -3,
  INVALID_END_TIME = -4,
  NOT_AUTHORIZED = -5,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManagePollResultCode>
  : xdr_integral_base<::stellar::ManagePollResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManagePollResultCode val) {
    switch (val) {
    case ::stellar::ManagePollResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::ManagePollResultCode::NOT_FOUND:
      return "NOT_FOUND";
    case ::stellar::ManagePollResultCode::POLL_NOT_READY:
      return "POLL_NOT_READY";
    case ::stellar::ManagePollResultCode::NOT_AUTHORIZED_TO_CLOSE_POLL:
      return "NOT_AUTHORIZED_TO_CLOSE_POLL";
    case ::stellar::ManagePollResultCode::INVALID_END_TIME:
      return "INVALID_END_TIME";
    case ::stellar::ManagePollResultCode::NOT_AUTHORIZED:
      return "NOT_AUTHORIZED";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManagePollResultCode::SUCCESS,
      (int32_t)::stellar::ManagePollResultCode::NOT_FOUND,
      (int32_t)::stellar::ManagePollResultCode::POLL_NOT_READY,
      (int32_t)::stellar::ManagePollResultCode::NOT_AUTHORIZED_TO_CLOSE_POLL,
      (int32_t)::stellar::ManagePollResultCode::INVALID_END_TIME,
      (int32_t)::stellar::ManagePollResultCode::NOT_AUTHORIZED
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ManagePollResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<ManagePollResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    EmptyExt ext_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<ManagePollResultCode> &_xdr_case_values() {
    static const std::vector<ManagePollResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)ManagePollResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)ManagePollResultCode::SUCCESS:
      _f(&ManagePollResult::ext_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in ManagePollResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~ManagePollResult();
      code_ = which;switch (code_)
{
      case (int32_t)ManagePollResultCode::SUCCESS:
new(&ext_) EmptyExt{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit ManagePollResult(ManagePollResultCode which = ManagePollResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)ManagePollResultCode::SUCCESS:
new(&ext_) EmptyExt{};
break;
    default:
      break;
}

  }
  ManagePollResult(const ManagePollResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManagePollResultCode::SUCCESS:
new(&ext_) EmptyExt(source.ext_);
break;
    default:
      break;
}

  }
  ManagePollResult(ManagePollResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManagePollResultCode::SUCCESS:
new(&ext_) EmptyExt(std::move(source.ext_));
break;
    default:
      break;
}

  }
  ~ManagePollResult() {
switch (code_)
{
  case (int32_t)ManagePollResultCode::SUCCESS:
ext_.~EmptyExt();
break;
  default:
    break;
}
}

  ManagePollResult &operator=(const ManagePollResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManagePollResultCode::SUCCESS:
ext_ = source.ext_;
break;
    default:
      break;
}
}
else {this->~ManagePollResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)ManagePollResultCode::SUCCESS:
new(&ext_) EmptyExt(source.ext_);
break;
    default:
      break;
}
}
    return *this;
  }
  ManagePollResult &operator=(ManagePollResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManagePollResultCode::SUCCESS:
ext_ = std::move(source.ext_);
break;
    default:
      break;
}
}
else {this->~ManagePollResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)ManagePollResultCode::SUCCESS:
new(&ext_) EmptyExt(std::move(source.ext_));
break;
    default:
      break;
}
}
    return *this;
  }

  ManagePollResultCode code() const { return ManagePollResultCode(code_); }
  ManagePollResult &code(ManagePollResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  EmptyExt &ext() {
    if (_xdr_field_number(code_) == 1)
      return ext_;
    throw xdr::xdr_wrong_union("ManagePollResult: ext accessed when not selected");
  }
  const EmptyExt &ext() const {
    if (_xdr_field_number(code_) == 1)
      return ext_;
    throw xdr::xdr_wrong_union("ManagePollResult: ext accessed when not selected");
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

}

#endif // !__XDR_OPERATION_MANAGE_POLL_H_INCLUDED__
