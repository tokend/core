// -*- C++ -*-
// Automatically generated from operation-manage-create-poll-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_MANAGE_CREATE_POLL_REQUEST_H_INCLUDED__
#define __XDR_OPERATION_MANAGE_CREATE_POLL_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/reviewable-request-create-poll.h"

namespace stellar {

enum class ManageCreatePollRequestAction : std::int32_t {
  CREATE = 0,
  CANCEL = 1,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageCreatePollRequestAction>
  : xdr_integral_base<::stellar::ManageCreatePollRequestAction, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageCreatePollRequestAction val) {
    switch (val) {
    case ::stellar::ManageCreatePollRequestAction::CREATE:
      return "CREATE";
    case ::stellar::ManageCreatePollRequestAction::CANCEL:
      return "CANCEL";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageCreatePollRequestAction::CREATE,
      (int32_t)::stellar::ManageCreatePollRequestAction::CANCEL
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreatePollRequestData  : xdr::xdr_abstract {
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

  CreatePollRequest request{};
  xdr::pointer<uint32> allTasks{};
  _ext_t ext{};

  CreatePollRequestData() = default;
  template<typename _request_T,
           typename _allTasks_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<CreatePollRequest, _request_T>::value
                          && std::is_constructible<xdr::pointer<uint32>, _allTasks_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreatePollRequestData(_request_T &&_request,
                                 _allTasks_T &&_allTasks,
                                 _ext_T &&_ext)
    : request(std::forward<_request_T>(_request)),
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

struct CancelPollRequestData  : xdr::xdr_abstract {
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

  uint64 requestID{};
  _ext_t ext{};

  CancelPollRequestData() = default;
  template<typename _requestID_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CancelPollRequestData(_requestID_T &&_requestID,
                                 _ext_T &&_ext)
    : requestID(std::forward<_requestID_T>(_requestID)),
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

struct ManageCreatePollRequestOp  : xdr::xdr_abstract {
  struct _data_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<ManageCreatePollRequestAction>::case_type;
  private:
    _xdr_case_type action_;
    union {
      CreatePollRequestData createData_;
      CancelPollRequestData cancelData_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<ManageCreatePollRequestAction> &_xdr_case_values() {
      static const std::vector<ManageCreatePollRequestAction> _xdr_disc_vec {
        ManageCreatePollRequestAction::CREATE,
        ManageCreatePollRequestAction::CANCEL
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)ManageCreatePollRequestAction::CREATE ? 1
        : which == (int32_t)ManageCreatePollRequestAction::CANCEL ? 2
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)ManageCreatePollRequestAction::CREATE:
        _f(&_data_t::createData_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ManageCreatePollRequestAction::CANCEL:
        _f(&_data_t::cancelData_, std::forward<_A>(_a)...);
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
        case (int32_t)ManageCreatePollRequestAction::CREATE:
new(&createData_) CreatePollRequestData{};
break;
        case (int32_t)ManageCreatePollRequestAction::CANCEL:
new(&cancelData_) CancelPollRequestData{};
break;
}

      }
      else
        action_ = which;
    }
    explicit _data_t(ManageCreatePollRequestAction which = ManageCreatePollRequestAction{}) : action_((int32_t)which) {
      switch (action_)
{
      case (int32_t)ManageCreatePollRequestAction::CREATE:
new(&createData_) CreatePollRequestData{};
break;
      case (int32_t)ManageCreatePollRequestAction::CANCEL:
new(&cancelData_) CancelPollRequestData{};
break;
}

    }
    _data_t(const _data_t &source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageCreatePollRequestAction::CREATE:
new(&createData_) CreatePollRequestData(source.createData_);
break;
      case (int32_t)ManageCreatePollRequestAction::CANCEL:
new(&cancelData_) CancelPollRequestData(source.cancelData_);
break;
}

    }
    _data_t(_data_t &&source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageCreatePollRequestAction::CREATE:
new(&createData_) CreatePollRequestData(std::move(source.createData_));
break;
      case (int32_t)ManageCreatePollRequestAction::CANCEL:
new(&cancelData_) CancelPollRequestData(std::move(source.cancelData_));
break;
}

    }
    ~_data_t() {
switch (action_)
{
    case (int32_t)ManageCreatePollRequestAction::CREATE:
createData_.~CreatePollRequestData();
break;
    case (int32_t)ManageCreatePollRequestAction::CANCEL:
cancelData_.~CancelPollRequestData();
break;
}
}

    _data_t &operator=(const _data_t &source) {
      if (action_ == source.action_)
{
switch (action_)
{
      case (int32_t)ManageCreatePollRequestAction::CREATE:
createData_ = source.createData_;
break;
      case (int32_t)ManageCreatePollRequestAction::CANCEL:
cancelData_ = source.cancelData_;
break;
}
}
else {this->~_data_t();
      action_ = source.action_;
switch (action_)
{
      case (int32_t)ManageCreatePollRequestAction::CREATE:
new(&createData_) CreatePollRequestData(source.createData_);
break;
      case (int32_t)ManageCreatePollRequestAction::CANCEL:
new(&cancelData_) CancelPollRequestData(source.cancelData_);
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
      case (int32_t)ManageCreatePollRequestAction::CREATE:
createData_ = std::move(source.createData_);
break;
      case (int32_t)ManageCreatePollRequestAction::CANCEL:
cancelData_ = std::move(source.cancelData_);
break;
}
}
else {this->~_data_t();
      action_ = std::move(source.action_);
switch (action_)
{
      case (int32_t)ManageCreatePollRequestAction::CREATE:
new(&createData_) CreatePollRequestData(std::move(source.createData_));
break;
      case (int32_t)ManageCreatePollRequestAction::CANCEL:
new(&cancelData_) CancelPollRequestData(std::move(source.cancelData_));
break;
}
}
      return *this;
    }

    ManageCreatePollRequestAction action() const { return ManageCreatePollRequestAction(action_); }
    _data_t &action(ManageCreatePollRequestAction _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    CreatePollRequestData &createData() {
      if (_xdr_field_number(action_) == 1)
        return createData_;
      throw xdr::xdr_wrong_union("_data_t: createData accessed when not selected");
    }
    const CreatePollRequestData &createData() const {
      if (_xdr_field_number(action_) == 1)
        return createData_;
      throw xdr::xdr_wrong_union("_data_t: createData accessed when not selected");
    }
    CancelPollRequestData &cancelData() {
      if (_xdr_field_number(action_) == 2)
        return cancelData_;
      throw xdr::xdr_wrong_union("_data_t: cancelData accessed when not selected");
    }
    const CancelPollRequestData &cancelData() const {
      if (_xdr_field_number(action_) == 2)
        return cancelData_;
      throw xdr::xdr_wrong_union("_data_t: cancelData accessed when not selected");
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

  ManageCreatePollRequestOp() = default;
  template<typename _data_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<_data_t, _data_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ManageCreatePollRequestOp(_data_T &&_data,
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

enum class ManageCreatePollRequestResultCode : std::int32_t {
  SUCCESS = 0,
  INVALID_CREATOR_DETAILS = -1,
  NOT_FOUND = -2,
  INVALID_DATES = -3,
  INVALID_END_TIME = -4,
  RESULT_PROVIDER_NOT_FOUND = -5,
  CREATE_POLL_TASKS_NOT_FOUND = -6,
  INVALID_NUMBER_OF_CHOICES = -7,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageCreatePollRequestResultCode>
  : xdr_integral_base<::stellar::ManageCreatePollRequestResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageCreatePollRequestResultCode val) {
    switch (val) {
    case ::stellar::ManageCreatePollRequestResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::ManageCreatePollRequestResultCode::INVALID_CREATOR_DETAILS:
      return "INVALID_CREATOR_DETAILS";
    case ::stellar::ManageCreatePollRequestResultCode::NOT_FOUND:
      return "NOT_FOUND";
    case ::stellar::ManageCreatePollRequestResultCode::INVALID_DATES:
      return "INVALID_DATES";
    case ::stellar::ManageCreatePollRequestResultCode::INVALID_END_TIME:
      return "INVALID_END_TIME";
    case ::stellar::ManageCreatePollRequestResultCode::RESULT_PROVIDER_NOT_FOUND:
      return "RESULT_PROVIDER_NOT_FOUND";
    case ::stellar::ManageCreatePollRequestResultCode::CREATE_POLL_TASKS_NOT_FOUND:
      return "CREATE_POLL_TASKS_NOT_FOUND";
    case ::stellar::ManageCreatePollRequestResultCode::INVALID_NUMBER_OF_CHOICES:
      return "INVALID_NUMBER_OF_CHOICES";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageCreatePollRequestResultCode::SUCCESS,
      (int32_t)::stellar::ManageCreatePollRequestResultCode::INVALID_CREATOR_DETAILS,
      (int32_t)::stellar::ManageCreatePollRequestResultCode::NOT_FOUND,
      (int32_t)::stellar::ManageCreatePollRequestResultCode::INVALID_DATES,
      (int32_t)::stellar::ManageCreatePollRequestResultCode::INVALID_END_TIME,
      (int32_t)::stellar::ManageCreatePollRequestResultCode::RESULT_PROVIDER_NOT_FOUND,
      (int32_t)::stellar::ManageCreatePollRequestResultCode::CREATE_POLL_TASKS_NOT_FOUND,
      (int32_t)::stellar::ManageCreatePollRequestResultCode::INVALID_NUMBER_OF_CHOICES
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreatePollRequestResponse  : xdr::xdr_abstract {
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

  uint64 requestID{};
  bool fulfilled{};
  xdr::pointer<uint64> pollID{};
  _ext_t ext{};

  CreatePollRequestResponse() = default;
  template<typename _requestID_T,
           typename _fulfilled_T,
           typename _pollID_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<bool, _fulfilled_T>::value
                          && std::is_constructible<xdr::pointer<uint64>, _pollID_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreatePollRequestResponse(_requestID_T &&_requestID,
                                     _fulfilled_T &&_fulfilled,
                                     _pollID_T &&_pollID,
                                     _ext_T &&_ext)
    : requestID(std::forward<_requestID_T>(_requestID)),
      fulfilled(std::forward<_fulfilled_T>(_fulfilled)),
      pollID(std::forward<_pollID_T>(_pollID)),
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

struct ManageCreatePollRequestSuccessResult  : xdr::xdr_abstract {
  struct _details_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<ManageCreatePollRequestAction>::case_type;
  private:
    _xdr_case_type action_;
    union {
      CreatePollRequestResponse response_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<ManageCreatePollRequestAction> &_xdr_case_values() {
      static const std::vector<ManageCreatePollRequestAction> _xdr_disc_vec {
        ManageCreatePollRequestAction::CREATE,
        ManageCreatePollRequestAction::CANCEL
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)ManageCreatePollRequestAction::CREATE ? 1
        : which == (int32_t)ManageCreatePollRequestAction::CANCEL ? 0
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)ManageCreatePollRequestAction::CREATE:
        _f(&_details_t::response_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ManageCreatePollRequestAction::CANCEL:
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return action_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of action in _details_t");
      if (fnum != _xdr_field_number(action_)) {
        this->~_details_t();
        action_ = which;switch (action_)
{
        case (int32_t)ManageCreatePollRequestAction::CREATE:
new(&response_) CreatePollRequestResponse{};
break;
        case (int32_t)ManageCreatePollRequestAction::CANCEL:
          break;
}

      }
      else
        action_ = which;
    }
    explicit _details_t(ManageCreatePollRequestAction which = ManageCreatePollRequestAction{}) : action_((int32_t)which) {
      switch (action_)
{
      case (int32_t)ManageCreatePollRequestAction::CREATE:
new(&response_) CreatePollRequestResponse{};
break;
      case (int32_t)ManageCreatePollRequestAction::CANCEL:
        break;
}

    }
    _details_t(const _details_t &source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageCreatePollRequestAction::CREATE:
new(&response_) CreatePollRequestResponse(source.response_);
break;
      case (int32_t)ManageCreatePollRequestAction::CANCEL:
        break;
}

    }
    _details_t(_details_t &&source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageCreatePollRequestAction::CREATE:
new(&response_) CreatePollRequestResponse(std::move(source.response_));
break;
      case (int32_t)ManageCreatePollRequestAction::CANCEL:
        break;
}

    }
    ~_details_t() {
switch (action_)
{
    case (int32_t)ManageCreatePollRequestAction::CREATE:
response_.~CreatePollRequestResponse();
break;
    case (int32_t)ManageCreatePollRequestAction::CANCEL:
      break;
}
}

    _details_t &operator=(const _details_t &source) {
      if (action_ == source.action_)
{
switch (action_)
{
      case (int32_t)ManageCreatePollRequestAction::CREATE:
response_ = source.response_;
break;
      case (int32_t)ManageCreatePollRequestAction::CANCEL:
        break;
}
}
else {this->~_details_t();
      action_ = source.action_;
switch (action_)
{
      case (int32_t)ManageCreatePollRequestAction::CREATE:
new(&response_) CreatePollRequestResponse(source.response_);
break;
      case (int32_t)ManageCreatePollRequestAction::CANCEL:
        break;
}
}
      return *this;
    }
    _details_t &operator=(_details_t &&source) {
      if (action_ == source.action_)
{
switch (action_)
{
      case (int32_t)ManageCreatePollRequestAction::CREATE:
response_ = std::move(source.response_);
break;
      case (int32_t)ManageCreatePollRequestAction::CANCEL:
        break;
}
}
else {this->~_details_t();
      action_ = std::move(source.action_);
switch (action_)
{
      case (int32_t)ManageCreatePollRequestAction::CREATE:
new(&response_) CreatePollRequestResponse(std::move(source.response_));
break;
      case (int32_t)ManageCreatePollRequestAction::CANCEL:
        break;
}
}
      return *this;
    }

    ManageCreatePollRequestAction action() const { return ManageCreatePollRequestAction(action_); }
    _details_t &action(ManageCreatePollRequestAction _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    CreatePollRequestResponse &response() {
      if (_xdr_field_number(action_) == 1)
        return response_;
      throw xdr::xdr_wrong_union("_details_t: response accessed when not selected");
    }
    const CreatePollRequestResponse &response() const {
      if (_xdr_field_number(action_) == 1)
        return response_;
      throw xdr::xdr_wrong_union("_details_t: response accessed when not selected");
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

  _details_t details{};
  _ext_t ext{};

  ManageCreatePollRequestSuccessResult() = default;
  template<typename _details_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<_details_t, _details_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ManageCreatePollRequestSuccessResult(_details_T &&_details,
                                                _ext_T &&_ext)
    : details(std::forward<_details_T>(_details)),
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

struct ManageCreatePollRequestResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<ManageCreatePollRequestResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    ManageCreatePollRequestSuccessResult success_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<ManageCreatePollRequestResultCode> &_xdr_case_values() {
    static const std::vector<ManageCreatePollRequestResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)ManageCreatePollRequestResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)ManageCreatePollRequestResultCode::SUCCESS:
      _f(&ManageCreatePollRequestResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in ManageCreatePollRequestResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~ManageCreatePollRequestResult();
      code_ = which;switch (code_)
{
      case (int32_t)ManageCreatePollRequestResultCode::SUCCESS:
new(&success_) ManageCreatePollRequestSuccessResult{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit ManageCreatePollRequestResult(ManageCreatePollRequestResultCode which = ManageCreatePollRequestResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)ManageCreatePollRequestResultCode::SUCCESS:
new(&success_) ManageCreatePollRequestSuccessResult{};
break;
    default:
      break;
}

  }
  ManageCreatePollRequestResult(const ManageCreatePollRequestResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManageCreatePollRequestResultCode::SUCCESS:
new(&success_) ManageCreatePollRequestSuccessResult(source.success_);
break;
    default:
      break;
}

  }
  ManageCreatePollRequestResult(ManageCreatePollRequestResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManageCreatePollRequestResultCode::SUCCESS:
new(&success_) ManageCreatePollRequestSuccessResult(std::move(source.success_));
break;
    default:
      break;
}

  }
  ~ManageCreatePollRequestResult() {
switch (code_)
{
  case (int32_t)ManageCreatePollRequestResultCode::SUCCESS:
success_.~ManageCreatePollRequestSuccessResult();
break;
  default:
    break;
}
}

  ManageCreatePollRequestResult &operator=(const ManageCreatePollRequestResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManageCreatePollRequestResultCode::SUCCESS:
success_ = source.success_;
break;
    default:
      break;
}
}
else {this->~ManageCreatePollRequestResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)ManageCreatePollRequestResultCode::SUCCESS:
new(&success_) ManageCreatePollRequestSuccessResult(source.success_);
break;
    default:
      break;
}
}
    return *this;
  }
  ManageCreatePollRequestResult &operator=(ManageCreatePollRequestResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManageCreatePollRequestResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    default:
      break;
}
}
else {this->~ManageCreatePollRequestResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)ManageCreatePollRequestResultCode::SUCCESS:
new(&success_) ManageCreatePollRequestSuccessResult(std::move(source.success_));
break;
    default:
      break;
}
}
    return *this;
  }

  ManageCreatePollRequestResultCode code() const { return ManageCreatePollRequestResultCode(code_); }
  ManageCreatePollRequestResult &code(ManageCreatePollRequestResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  ManageCreatePollRequestSuccessResult &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageCreatePollRequestResult: success accessed when not selected");
  }
  const ManageCreatePollRequestSuccessResult &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageCreatePollRequestResult: success accessed when not selected");
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

#endif // !__XDR_OPERATION_MANAGE_CREATE_POLL_REQUEST_H_INCLUDED__
