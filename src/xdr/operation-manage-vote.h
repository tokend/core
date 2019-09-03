// -*- C++ -*-
// Automatically generated from operation-manage-vote.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_MANAGE_VOTE_H_INCLUDED__
#define __XDR_OPERATION_MANAGE_VOTE_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/ledger-entries-vote.h"

namespace stellar {

enum class ManageVoteAction : std::int32_t {
  CREATE = 0,
  REMOVE = 1,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageVoteAction>
  : xdr_integral_base<::stellar::ManageVoteAction, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageVoteAction val) {
    switch (val) {
    case ::stellar::ManageVoteAction::CREATE:
      return "CREATE";
    case ::stellar::ManageVoteAction::REMOVE:
      return "REMOVE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageVoteAction::CREATE,
      (int32_t)::stellar::ManageVoteAction::REMOVE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateVoteData  : xdr::xdr_abstract {
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
  VoteData data{};
  _ext_t ext{};

  CreateVoteData() = default;
  template<typename _pollID_T,
           typename _data_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _pollID_T>::value
                          && std::is_constructible<VoteData, _data_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateVoteData(_pollID_T &&_pollID,
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

struct RemoveVoteData  : xdr::xdr_abstract {
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
  _ext_t ext{};

  RemoveVoteData() = default;
  template<typename _pollID_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _pollID_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit RemoveVoteData(_pollID_T &&_pollID,
                          _ext_T &&_ext)
    : pollID(std::forward<_pollID_T>(_pollID)),
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

struct ManageVoteOp  : xdr::xdr_abstract {
  struct _data_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<ManageVoteAction>::case_type;
  private:
    _xdr_case_type action_;
    union {
      CreateVoteData createData_;
      RemoveVoteData removeData_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<ManageVoteAction> &_xdr_case_values() {
      static const std::vector<ManageVoteAction> _xdr_disc_vec {
        ManageVoteAction::CREATE,
        ManageVoteAction::REMOVE
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)ManageVoteAction::CREATE ? 1
        : which == (int32_t)ManageVoteAction::REMOVE ? 2
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)ManageVoteAction::CREATE:
        _f(&_data_t::createData_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ManageVoteAction::REMOVE:
        _f(&_data_t::removeData_, std::forward<_A>(_a)...);
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
        case (int32_t)ManageVoteAction::CREATE:
new(&createData_) CreateVoteData{};
break;
        case (int32_t)ManageVoteAction::REMOVE:
new(&removeData_) RemoveVoteData{};
break;
}

      }
      else
        action_ = which;
    }
    explicit _data_t(ManageVoteAction which = ManageVoteAction{}) : action_((int32_t)which) {
      switch (action_)
{
      case (int32_t)ManageVoteAction::CREATE:
new(&createData_) CreateVoteData{};
break;
      case (int32_t)ManageVoteAction::REMOVE:
new(&removeData_) RemoveVoteData{};
break;
}

    }
    _data_t(const _data_t &source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageVoteAction::CREATE:
new(&createData_) CreateVoteData(source.createData_);
break;
      case (int32_t)ManageVoteAction::REMOVE:
new(&removeData_) RemoveVoteData(source.removeData_);
break;
}

    }
    _data_t(_data_t &&source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageVoteAction::CREATE:
new(&createData_) CreateVoteData(std::move(source.createData_));
break;
      case (int32_t)ManageVoteAction::REMOVE:
new(&removeData_) RemoveVoteData(std::move(source.removeData_));
break;
}

    }
    ~_data_t() {
switch (action_)
{
    case (int32_t)ManageVoteAction::CREATE:
createData_.~CreateVoteData();
break;
    case (int32_t)ManageVoteAction::REMOVE:
removeData_.~RemoveVoteData();
break;
}
}

    _data_t &operator=(const _data_t &source) {
      if (action_ == source.action_)
{
switch (action_)
{
      case (int32_t)ManageVoteAction::CREATE:
createData_ = source.createData_;
break;
      case (int32_t)ManageVoteAction::REMOVE:
removeData_ = source.removeData_;
break;
}
}
else {this->~_data_t();
      action_ = source.action_;
switch (action_)
{
      case (int32_t)ManageVoteAction::CREATE:
new(&createData_) CreateVoteData(source.createData_);
break;
      case (int32_t)ManageVoteAction::REMOVE:
new(&removeData_) RemoveVoteData(source.removeData_);
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
      case (int32_t)ManageVoteAction::CREATE:
createData_ = std::move(source.createData_);
break;
      case (int32_t)ManageVoteAction::REMOVE:
removeData_ = std::move(source.removeData_);
break;
}
}
else {this->~_data_t();
      action_ = std::move(source.action_);
switch (action_)
{
      case (int32_t)ManageVoteAction::CREATE:
new(&createData_) CreateVoteData(std::move(source.createData_));
break;
      case (int32_t)ManageVoteAction::REMOVE:
new(&removeData_) RemoveVoteData(std::move(source.removeData_));
break;
}
}
      return *this;
    }

    ManageVoteAction action() const { return ManageVoteAction(action_); }
    _data_t &action(ManageVoteAction _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    CreateVoteData &createData() {
      if (_xdr_field_number(action_) == 1)
        return createData_;
      throw xdr::xdr_wrong_union("_data_t: createData accessed when not selected");
    }
    const CreateVoteData &createData() const {
      if (_xdr_field_number(action_) == 1)
        return createData_;
      throw xdr::xdr_wrong_union("_data_t: createData accessed when not selected");
    }
    RemoveVoteData &removeData() {
      if (_xdr_field_number(action_) == 2)
        return removeData_;
      throw xdr::xdr_wrong_union("_data_t: removeData accessed when not selected");
    }
    const RemoveVoteData &removeData() const {
      if (_xdr_field_number(action_) == 2)
        return removeData_;
      throw xdr::xdr_wrong_union("_data_t: removeData accessed when not selected");
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

  _data_t data{};
  _ext_t ext{};

  ManageVoteOp() = default;
  template<typename _data_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<_data_t, _data_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ManageVoteOp(_data_T &&_data,
                        _ext_T &&_ext)
    : data(std::forward<_data_T>(_data)),
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

enum class ManageVoteResultCode : std::int32_t {
  SUCCESS = 0,
  VOTE_NOT_FOUND = -1,
  POLL_NOT_FOUND = -2,
  VOTE_EXISTS = -3,
  POLL_TYPE_MISMATCHED = -4,
  POLL_NOT_STARTED = -5,
  POLL_ENDED = -6,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageVoteResultCode>
  : xdr_integral_base<::stellar::ManageVoteResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageVoteResultCode val) {
    switch (val) {
    case ::stellar::ManageVoteResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::ManageVoteResultCode::VOTE_NOT_FOUND:
      return "VOTE_NOT_FOUND";
    case ::stellar::ManageVoteResultCode::POLL_NOT_FOUND:
      return "POLL_NOT_FOUND";
    case ::stellar::ManageVoteResultCode::VOTE_EXISTS:
      return "VOTE_EXISTS";
    case ::stellar::ManageVoteResultCode::POLL_TYPE_MISMATCHED:
      return "POLL_TYPE_MISMATCHED";
    case ::stellar::ManageVoteResultCode::POLL_NOT_STARTED:
      return "POLL_NOT_STARTED";
    case ::stellar::ManageVoteResultCode::POLL_ENDED:
      return "POLL_ENDED";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageVoteResultCode::SUCCESS,
      (int32_t)::stellar::ManageVoteResultCode::VOTE_NOT_FOUND,
      (int32_t)::stellar::ManageVoteResultCode::POLL_NOT_FOUND,
      (int32_t)::stellar::ManageVoteResultCode::VOTE_EXISTS,
      (int32_t)::stellar::ManageVoteResultCode::POLL_TYPE_MISMATCHED,
      (int32_t)::stellar::ManageVoteResultCode::POLL_NOT_STARTED,
      (int32_t)::stellar::ManageVoteResultCode::POLL_ENDED
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ManageVoteResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<ManageVoteResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    EmptyExt ext_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<ManageVoteResultCode> &_xdr_case_values() {
    static const std::vector<ManageVoteResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)ManageVoteResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)ManageVoteResultCode::SUCCESS:
      _f(&ManageVoteResult::ext_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in ManageVoteResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~ManageVoteResult();
      code_ = which;switch (code_)
{
      case (int32_t)ManageVoteResultCode::SUCCESS:
new(&ext_) EmptyExt{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit ManageVoteResult(ManageVoteResultCode which = ManageVoteResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)ManageVoteResultCode::SUCCESS:
new(&ext_) EmptyExt{};
break;
    default:
      break;
}

  }
  ManageVoteResult(const ManageVoteResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManageVoteResultCode::SUCCESS:
new(&ext_) EmptyExt(source.ext_);
break;
    default:
      break;
}

  }
  ManageVoteResult(ManageVoteResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManageVoteResultCode::SUCCESS:
new(&ext_) EmptyExt(std::move(source.ext_));
break;
    default:
      break;
}

  }
  ~ManageVoteResult() {
switch (code_)
{
  case (int32_t)ManageVoteResultCode::SUCCESS:
ext_.~EmptyExt();
break;
  default:
    break;
}
}

  ManageVoteResult &operator=(const ManageVoteResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManageVoteResultCode::SUCCESS:
ext_ = source.ext_;
break;
    default:
      break;
}
}
else {this->~ManageVoteResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)ManageVoteResultCode::SUCCESS:
new(&ext_) EmptyExt(source.ext_);
break;
    default:
      break;
}
}
    return *this;
  }
  ManageVoteResult &operator=(ManageVoteResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManageVoteResultCode::SUCCESS:
ext_ = std::move(source.ext_);
break;
    default:
      break;
}
}
else {this->~ManageVoteResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)ManageVoteResultCode::SUCCESS:
new(&ext_) EmptyExt(std::move(source.ext_));
break;
    default:
      break;
}
}
    return *this;
  }

  ManageVoteResultCode code() const { return ManageVoteResultCode(code_); }
  ManageVoteResult &code(ManageVoteResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  EmptyExt &ext() {
    if (_xdr_field_number(code_) == 1)
      return ext_;
    throw xdr::xdr_wrong_union("ManageVoteResult: ext accessed when not selected");
  }
  const EmptyExt &ext() const {
    if (_xdr_field_number(code_) == 1)
      return ext_;
    throw xdr::xdr_wrong_union("ManageVoteResult: ext accessed when not selected");
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

#endif // !__XDR_OPERATION_MANAGE_VOTE_H_INCLUDED__
