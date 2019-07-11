// -*- C++ -*-
// Automatically generated from operation-manage-external-system-id-pool-entry.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_MANAGE_EXTERNAL_SYSTEM_ID_POOL_ENTRY_H_INCLUDED__
#define __XDR_OPERATION_MANAGE_EXTERNAL_SYSTEM_ID_POOL_ENTRY_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/ledger-entries.h"

namespace stellar {

enum class ManageExternalSystemAccountIdPoolEntryAction : std::int32_t {
  CREATE = 0,
  REMOVE = 1,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageExternalSystemAccountIdPoolEntryAction>
  : xdr_integral_base<::stellar::ManageExternalSystemAccountIdPoolEntryAction, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageExternalSystemAccountIdPoolEntryAction val) {
    switch (val) {
    case ::stellar::ManageExternalSystemAccountIdPoolEntryAction::CREATE:
      return "CREATE";
    case ::stellar::ManageExternalSystemAccountIdPoolEntryAction::REMOVE:
      return "REMOVE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageExternalSystemAccountIdPoolEntryAction::CREATE,
      (int32_t)::stellar::ManageExternalSystemAccountIdPoolEntryAction::REMOVE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateExternalSystemAccountIdPoolEntryActionInput  : xdr::xdr_abstract {
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

  int32 externalSystemType{};
  longstring data{};
  uint64 parent{};
  _ext_t ext{};

  CreateExternalSystemAccountIdPoolEntryActionInput() = default;
  template<typename _externalSystemType_T,
           typename _data_T,
           typename _parent_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<int32, _externalSystemType_T>::value
                          && std::is_constructible<longstring, _data_T>::value
                          && std::is_constructible<uint64, _parent_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateExternalSystemAccountIdPoolEntryActionInput(_externalSystemType_T &&_externalSystemType,
                                                             _data_T &&_data,
                                                             _parent_T &&_parent,
                                                             _ext_T &&_ext)
    : externalSystemType(std::forward<_externalSystemType_T>(_externalSystemType)),
      data(std::forward<_data_T>(_data)),
      parent(std::forward<_parent_T>(_parent)),
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

struct DeleteExternalSystemAccountIdPoolEntryActionInput  : xdr::xdr_abstract {
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

  uint64 poolEntryID{};
  _ext_t ext{};

  DeleteExternalSystemAccountIdPoolEntryActionInput() = default;
  template<typename _poolEntryID_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _poolEntryID_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit DeleteExternalSystemAccountIdPoolEntryActionInput(_poolEntryID_T &&_poolEntryID,
                                                             _ext_T &&_ext)
    : poolEntryID(std::forward<_poolEntryID_T>(_poolEntryID)),
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

struct ManageExternalSystemAccountIdPoolEntryOp  : xdr::xdr_abstract {
  struct _actionInput_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<ManageExternalSystemAccountIdPoolEntryAction>::case_type;
  private:
    _xdr_case_type action_;
    union {
      CreateExternalSystemAccountIdPoolEntryActionInput createExternalSystemAccountIdPoolEntryActionInput_;
      DeleteExternalSystemAccountIdPoolEntryActionInput deleteExternalSystemAccountIdPoolEntryActionInput_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<ManageExternalSystemAccountIdPoolEntryAction> &_xdr_case_values() {
      static const std::vector<ManageExternalSystemAccountIdPoolEntryAction> _xdr_disc_vec {
        ManageExternalSystemAccountIdPoolEntryAction::CREATE,
        ManageExternalSystemAccountIdPoolEntryAction::REMOVE
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)ManageExternalSystemAccountIdPoolEntryAction::CREATE ? 1
        : which == (int32_t)ManageExternalSystemAccountIdPoolEntryAction::REMOVE ? 2
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)ManageExternalSystemAccountIdPoolEntryAction::CREATE:
        _f(&_actionInput_t::createExternalSystemAccountIdPoolEntryActionInput_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ManageExternalSystemAccountIdPoolEntryAction::REMOVE:
        _f(&_actionInput_t::deleteExternalSystemAccountIdPoolEntryActionInput_, std::forward<_A>(_a)...);
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return action_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of action in _actionInput_t");
      if (fnum != _xdr_field_number(action_)) {
        this->~_actionInput_t();
        action_ = which;switch (action_)
{
        case (int32_t)ManageExternalSystemAccountIdPoolEntryAction::CREATE:
new(&createExternalSystemAccountIdPoolEntryActionInput_) CreateExternalSystemAccountIdPoolEntryActionInput{};
break;
        case (int32_t)ManageExternalSystemAccountIdPoolEntryAction::REMOVE:
new(&deleteExternalSystemAccountIdPoolEntryActionInput_) DeleteExternalSystemAccountIdPoolEntryActionInput{};
break;
}

      }
      else
        action_ = which;
    }
    explicit _actionInput_t(ManageExternalSystemAccountIdPoolEntryAction which = ManageExternalSystemAccountIdPoolEntryAction{}) : action_((int32_t)which) {
      switch (action_)
{
      case (int32_t)ManageExternalSystemAccountIdPoolEntryAction::CREATE:
new(&createExternalSystemAccountIdPoolEntryActionInput_) CreateExternalSystemAccountIdPoolEntryActionInput{};
break;
      case (int32_t)ManageExternalSystemAccountIdPoolEntryAction::REMOVE:
new(&deleteExternalSystemAccountIdPoolEntryActionInput_) DeleteExternalSystemAccountIdPoolEntryActionInput{};
break;
}

    }
    _actionInput_t(const _actionInput_t &source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageExternalSystemAccountIdPoolEntryAction::CREATE:
new(&createExternalSystemAccountIdPoolEntryActionInput_) CreateExternalSystemAccountIdPoolEntryActionInput(source.createExternalSystemAccountIdPoolEntryActionInput_);
break;
      case (int32_t)ManageExternalSystemAccountIdPoolEntryAction::REMOVE:
new(&deleteExternalSystemAccountIdPoolEntryActionInput_) DeleteExternalSystemAccountIdPoolEntryActionInput(source.deleteExternalSystemAccountIdPoolEntryActionInput_);
break;
}

    }
    _actionInput_t(_actionInput_t &&source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageExternalSystemAccountIdPoolEntryAction::CREATE:
new(&createExternalSystemAccountIdPoolEntryActionInput_) CreateExternalSystemAccountIdPoolEntryActionInput(std::move(source.createExternalSystemAccountIdPoolEntryActionInput_));
break;
      case (int32_t)ManageExternalSystemAccountIdPoolEntryAction::REMOVE:
new(&deleteExternalSystemAccountIdPoolEntryActionInput_) DeleteExternalSystemAccountIdPoolEntryActionInput(std::move(source.deleteExternalSystemAccountIdPoolEntryActionInput_));
break;
}

    }
    ~_actionInput_t() {
switch (action_)
{
    case (int32_t)ManageExternalSystemAccountIdPoolEntryAction::CREATE:
createExternalSystemAccountIdPoolEntryActionInput_.~CreateExternalSystemAccountIdPoolEntryActionInput();
break;
    case (int32_t)ManageExternalSystemAccountIdPoolEntryAction::REMOVE:
deleteExternalSystemAccountIdPoolEntryActionInput_.~DeleteExternalSystemAccountIdPoolEntryActionInput();
break;
}
}

    _actionInput_t &operator=(const _actionInput_t &source) {
      if (action_ == source.action_)
{
switch (action_)
{
      case (int32_t)ManageExternalSystemAccountIdPoolEntryAction::CREATE:
createExternalSystemAccountIdPoolEntryActionInput_ = source.createExternalSystemAccountIdPoolEntryActionInput_;
break;
      case (int32_t)ManageExternalSystemAccountIdPoolEntryAction::REMOVE:
deleteExternalSystemAccountIdPoolEntryActionInput_ = source.deleteExternalSystemAccountIdPoolEntryActionInput_;
break;
}
}
else {this->~_actionInput_t();
      action_ = source.action_;
switch (action_)
{
      case (int32_t)ManageExternalSystemAccountIdPoolEntryAction::CREATE:
new(&createExternalSystemAccountIdPoolEntryActionInput_) CreateExternalSystemAccountIdPoolEntryActionInput(source.createExternalSystemAccountIdPoolEntryActionInput_);
break;
      case (int32_t)ManageExternalSystemAccountIdPoolEntryAction::REMOVE:
new(&deleteExternalSystemAccountIdPoolEntryActionInput_) DeleteExternalSystemAccountIdPoolEntryActionInput(source.deleteExternalSystemAccountIdPoolEntryActionInput_);
break;
}
}
      return *this;
    }
    _actionInput_t &operator=(_actionInput_t &&source) {
      if (action_ == source.action_)
{
switch (action_)
{
      case (int32_t)ManageExternalSystemAccountIdPoolEntryAction::CREATE:
createExternalSystemAccountIdPoolEntryActionInput_ = std::move(source.createExternalSystemAccountIdPoolEntryActionInput_);
break;
      case (int32_t)ManageExternalSystemAccountIdPoolEntryAction::REMOVE:
deleteExternalSystemAccountIdPoolEntryActionInput_ = std::move(source.deleteExternalSystemAccountIdPoolEntryActionInput_);
break;
}
}
else {this->~_actionInput_t();
      action_ = std::move(source.action_);
switch (action_)
{
      case (int32_t)ManageExternalSystemAccountIdPoolEntryAction::CREATE:
new(&createExternalSystemAccountIdPoolEntryActionInput_) CreateExternalSystemAccountIdPoolEntryActionInput(std::move(source.createExternalSystemAccountIdPoolEntryActionInput_));
break;
      case (int32_t)ManageExternalSystemAccountIdPoolEntryAction::REMOVE:
new(&deleteExternalSystemAccountIdPoolEntryActionInput_) DeleteExternalSystemAccountIdPoolEntryActionInput(std::move(source.deleteExternalSystemAccountIdPoolEntryActionInput_));
break;
}
}
      return *this;
    }

    ManageExternalSystemAccountIdPoolEntryAction action() const { return ManageExternalSystemAccountIdPoolEntryAction(action_); }
    _actionInput_t &action(ManageExternalSystemAccountIdPoolEntryAction _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    CreateExternalSystemAccountIdPoolEntryActionInput &createExternalSystemAccountIdPoolEntryActionInput() {
      if (_xdr_field_number(action_) == 1)
        return createExternalSystemAccountIdPoolEntryActionInput_;
      throw xdr::xdr_wrong_union("_actionInput_t: createExternalSystemAccountIdPoolEntryActionInput accessed when not selected");
    }
    const CreateExternalSystemAccountIdPoolEntryActionInput &createExternalSystemAccountIdPoolEntryActionInput() const {
      if (_xdr_field_number(action_) == 1)
        return createExternalSystemAccountIdPoolEntryActionInput_;
      throw xdr::xdr_wrong_union("_actionInput_t: createExternalSystemAccountIdPoolEntryActionInput accessed when not selected");
    }
    DeleteExternalSystemAccountIdPoolEntryActionInput &deleteExternalSystemAccountIdPoolEntryActionInput() {
      if (_xdr_field_number(action_) == 2)
        return deleteExternalSystemAccountIdPoolEntryActionInput_;
      throw xdr::xdr_wrong_union("_actionInput_t: deleteExternalSystemAccountIdPoolEntryActionInput accessed when not selected");
    }
    const DeleteExternalSystemAccountIdPoolEntryActionInput &deleteExternalSystemAccountIdPoolEntryActionInput() const {
      if (_xdr_field_number(action_) == 2)
        return deleteExternalSystemAccountIdPoolEntryActionInput_;
      throw xdr::xdr_wrong_union("_actionInput_t: deleteExternalSystemAccountIdPoolEntryActionInput accessed when not selected");
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

  _actionInput_t actionInput{};
  _ext_t ext{};

  ManageExternalSystemAccountIdPoolEntryOp() = default;
  template<typename _actionInput_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<_actionInput_t, _actionInput_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ManageExternalSystemAccountIdPoolEntryOp(_actionInput_T &&_actionInput,
                                                    _ext_T &&_ext)
    : actionInput(std::forward<_actionInput_T>(_actionInput)),
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

enum class ManageExternalSystemAccountIdPoolEntryResultCode : std::int32_t {
  SUCCESS = 0,
  MALFORMED = -1,
  ALREADY_EXISTS = -2,
  NOT_FOUND = -3,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageExternalSystemAccountIdPoolEntryResultCode>
  : xdr_integral_base<::stellar::ManageExternalSystemAccountIdPoolEntryResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageExternalSystemAccountIdPoolEntryResultCode val) {
    switch (val) {
    case ::stellar::ManageExternalSystemAccountIdPoolEntryResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::ManageExternalSystemAccountIdPoolEntryResultCode::MALFORMED:
      return "MALFORMED";
    case ::stellar::ManageExternalSystemAccountIdPoolEntryResultCode::ALREADY_EXISTS:
      return "ALREADY_EXISTS";
    case ::stellar::ManageExternalSystemAccountIdPoolEntryResultCode::NOT_FOUND:
      return "NOT_FOUND";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageExternalSystemAccountIdPoolEntryResultCode::SUCCESS,
      (int32_t)::stellar::ManageExternalSystemAccountIdPoolEntryResultCode::MALFORMED,
      (int32_t)::stellar::ManageExternalSystemAccountIdPoolEntryResultCode::ALREADY_EXISTS,
      (int32_t)::stellar::ManageExternalSystemAccountIdPoolEntryResultCode::NOT_FOUND
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ManageExternalSystemAccountIdPoolEntrySuccess  : xdr::xdr_abstract {
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

  uint64 poolEntryID{};
  _ext_t ext{};

  ManageExternalSystemAccountIdPoolEntrySuccess() = default;
  template<typename _poolEntryID_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _poolEntryID_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ManageExternalSystemAccountIdPoolEntrySuccess(_poolEntryID_T &&_poolEntryID,
                                                         _ext_T &&_ext)
    : poolEntryID(std::forward<_poolEntryID_T>(_poolEntryID)),
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

struct ManageExternalSystemAccountIdPoolEntryResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<ManageExternalSystemAccountIdPoolEntryResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    ManageExternalSystemAccountIdPoolEntrySuccess success_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<ManageExternalSystemAccountIdPoolEntryResultCode> &_xdr_case_values() {
    static const std::vector<ManageExternalSystemAccountIdPoolEntryResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)ManageExternalSystemAccountIdPoolEntryResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)ManageExternalSystemAccountIdPoolEntryResultCode::SUCCESS:
      _f(&ManageExternalSystemAccountIdPoolEntryResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in ManageExternalSystemAccountIdPoolEntryResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~ManageExternalSystemAccountIdPoolEntryResult();
      code_ = which;switch (code_)
{
      case (int32_t)ManageExternalSystemAccountIdPoolEntryResultCode::SUCCESS:
new(&success_) ManageExternalSystemAccountIdPoolEntrySuccess{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit ManageExternalSystemAccountIdPoolEntryResult(ManageExternalSystemAccountIdPoolEntryResultCode which = ManageExternalSystemAccountIdPoolEntryResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)ManageExternalSystemAccountIdPoolEntryResultCode::SUCCESS:
new(&success_) ManageExternalSystemAccountIdPoolEntrySuccess{};
break;
    default:
      break;
}

  }
  ManageExternalSystemAccountIdPoolEntryResult(const ManageExternalSystemAccountIdPoolEntryResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManageExternalSystemAccountIdPoolEntryResultCode::SUCCESS:
new(&success_) ManageExternalSystemAccountIdPoolEntrySuccess(source.success_);
break;
    default:
      break;
}

  }
  ManageExternalSystemAccountIdPoolEntryResult(ManageExternalSystemAccountIdPoolEntryResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManageExternalSystemAccountIdPoolEntryResultCode::SUCCESS:
new(&success_) ManageExternalSystemAccountIdPoolEntrySuccess(std::move(source.success_));
break;
    default:
      break;
}

  }
  ~ManageExternalSystemAccountIdPoolEntryResult() {
switch (code_)
{
  case (int32_t)ManageExternalSystemAccountIdPoolEntryResultCode::SUCCESS:
success_.~ManageExternalSystemAccountIdPoolEntrySuccess();
break;
  default:
    break;
}
}

  ManageExternalSystemAccountIdPoolEntryResult &operator=(const ManageExternalSystemAccountIdPoolEntryResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManageExternalSystemAccountIdPoolEntryResultCode::SUCCESS:
success_ = source.success_;
break;
    default:
      break;
}
}
else {this->~ManageExternalSystemAccountIdPoolEntryResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)ManageExternalSystemAccountIdPoolEntryResultCode::SUCCESS:
new(&success_) ManageExternalSystemAccountIdPoolEntrySuccess(source.success_);
break;
    default:
      break;
}
}
    return *this;
  }
  ManageExternalSystemAccountIdPoolEntryResult &operator=(ManageExternalSystemAccountIdPoolEntryResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManageExternalSystemAccountIdPoolEntryResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    default:
      break;
}
}
else {this->~ManageExternalSystemAccountIdPoolEntryResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)ManageExternalSystemAccountIdPoolEntryResultCode::SUCCESS:
new(&success_) ManageExternalSystemAccountIdPoolEntrySuccess(std::move(source.success_));
break;
    default:
      break;
}
}
    return *this;
  }

  ManageExternalSystemAccountIdPoolEntryResultCode code() const { return ManageExternalSystemAccountIdPoolEntryResultCode(code_); }
  ManageExternalSystemAccountIdPoolEntryResult &code(ManageExternalSystemAccountIdPoolEntryResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  ManageExternalSystemAccountIdPoolEntrySuccess &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageExternalSystemAccountIdPoolEntryResult: success accessed when not selected");
  }
  const ManageExternalSystemAccountIdPoolEntrySuccess &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageExternalSystemAccountIdPoolEntryResult: success accessed when not selected");
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

#endif // !__XDR_OPERATION_MANAGE_EXTERNAL_SYSTEM_ID_POOL_ENTRY_H_INCLUDED__
