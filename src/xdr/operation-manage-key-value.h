// -*- C++ -*-
// Automatically generated from operation-manage-key-value.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_MANAGE_KEY_VALUE_H_INCLUDED__
#define __XDR_OPERATION_MANAGE_KEY_VALUE_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/ledger-entries.h"

namespace stellar {

enum class ManageKVAction : std::int32_t {
  PUT = 1,
  REMOVE = 2,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageKVAction>
  : xdr_integral_base<::stellar::ManageKVAction, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageKVAction val) {
    switch (val) {
    case ::stellar::ManageKVAction::PUT:
      return "PUT";
    case ::stellar::ManageKVAction::REMOVE:
      return "REMOVE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageKVAction::PUT,
      (int32_t)::stellar::ManageKVAction::REMOVE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ManageKeyValueOp  : xdr::xdr_abstract {
  struct _action_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<ManageKVAction>::case_type;
  private:
    _xdr_case_type action_;
    union {
      KeyValueEntryValue value_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<ManageKVAction> &_xdr_case_values() {
      static const std::vector<ManageKVAction> _xdr_disc_vec {
        ManageKVAction::PUT,
        ManageKVAction::REMOVE
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)ManageKVAction::PUT ? 1
        : which == (int32_t)ManageKVAction::REMOVE ? 0
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)ManageKVAction::PUT:
        _f(&_action_t::value_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ManageKVAction::REMOVE:
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return action_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of action in _action_t");
      if (fnum != _xdr_field_number(action_)) {
        this->~_action_t();
        action_ = which;switch (action_)
{
        case (int32_t)ManageKVAction::PUT:
new(&value_) KeyValueEntryValue{};
break;
        case (int32_t)ManageKVAction::REMOVE:
          break;
}

      }
      else
        action_ = which;
    }
    explicit _action_t(ManageKVAction which = ManageKVAction{}) : action_((int32_t)which) {
      switch (action_)
{
      case (int32_t)ManageKVAction::PUT:
new(&value_) KeyValueEntryValue{};
break;
      case (int32_t)ManageKVAction::REMOVE:
        break;
}

    }
    _action_t(const _action_t &source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageKVAction::PUT:
new(&value_) KeyValueEntryValue(source.value_);
break;
      case (int32_t)ManageKVAction::REMOVE:
        break;
}

    }
    _action_t(_action_t &&source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageKVAction::PUT:
new(&value_) KeyValueEntryValue(std::move(source.value_));
break;
      case (int32_t)ManageKVAction::REMOVE:
        break;
}

    }
    ~_action_t() {
switch (action_)
{
    case (int32_t)ManageKVAction::PUT:
value_.~KeyValueEntryValue();
break;
    case (int32_t)ManageKVAction::REMOVE:
      break;
}
}

    _action_t &operator=(const _action_t &source) {
      if (action_ == source.action_)
{
switch (action_)
{
      case (int32_t)ManageKVAction::PUT:
value_ = source.value_;
break;
      case (int32_t)ManageKVAction::REMOVE:
        break;
}
}
else {this->~_action_t();
      action_ = source.action_;
switch (action_)
{
      case (int32_t)ManageKVAction::PUT:
new(&value_) KeyValueEntryValue(source.value_);
break;
      case (int32_t)ManageKVAction::REMOVE:
        break;
}
}
      return *this;
    }
    _action_t &operator=(_action_t &&source) {
      if (action_ == source.action_)
{
switch (action_)
{
      case (int32_t)ManageKVAction::PUT:
value_ = std::move(source.value_);
break;
      case (int32_t)ManageKVAction::REMOVE:
        break;
}
}
else {this->~_action_t();
      action_ = std::move(source.action_);
switch (action_)
{
      case (int32_t)ManageKVAction::PUT:
new(&value_) KeyValueEntryValue(std::move(source.value_));
break;
      case (int32_t)ManageKVAction::REMOVE:
        break;
}
}
      return *this;
    }

    ManageKVAction action() const { return ManageKVAction(action_); }
    _action_t &action(ManageKVAction _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    KeyValueEntryValue &value() {
      if (_xdr_field_number(action_) == 1)
        return value_;
      throw xdr::xdr_wrong_union("_action_t: value accessed when not selected");
    }
    const KeyValueEntryValue &value() const {
      if (_xdr_field_number(action_) == 1)
        return value_;
      throw xdr::xdr_wrong_union("_action_t: value accessed when not selected");
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

  longstring key{};
  _action_t action{};
  _ext_t ext{};

  ManageKeyValueOp() = default;
  template<typename _key_T,
           typename _action_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<longstring, _key_T>::value
                          && std::is_constructible<_action_t, _action_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ManageKeyValueOp(_key_T &&_key,
                            _action_T &&_action,
                            _ext_T &&_ext)
    : key(std::forward<_key_T>(_key)),
      action(std::forward<_action_T>(_action)),
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

struct ManageKeyValueSuccess  : xdr::xdr_abstract {
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

  _ext_t ext{};

  ManageKeyValueSuccess() = default;
  template<typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ManageKeyValueSuccess(_ext_T &&_ext)
    : ext(std::forward<_ext_T>(_ext)) {}
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

enum class ManageKeyValueResultCode : std::int32_t {
  SUCCESS = 0,
  NOT_FOUND = -1,
  INVALID_TYPE = -2,
  ZERO_VALUE_NOT_ALLOWED = -3,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageKeyValueResultCode>
  : xdr_integral_base<::stellar::ManageKeyValueResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageKeyValueResultCode val) {
    switch (val) {
    case ::stellar::ManageKeyValueResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::ManageKeyValueResultCode::NOT_FOUND:
      return "NOT_FOUND";
    case ::stellar::ManageKeyValueResultCode::INVALID_TYPE:
      return "INVALID_TYPE";
    case ::stellar::ManageKeyValueResultCode::ZERO_VALUE_NOT_ALLOWED:
      return "ZERO_VALUE_NOT_ALLOWED";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageKeyValueResultCode::SUCCESS,
      (int32_t)::stellar::ManageKeyValueResultCode::NOT_FOUND,
      (int32_t)::stellar::ManageKeyValueResultCode::INVALID_TYPE,
      (int32_t)::stellar::ManageKeyValueResultCode::ZERO_VALUE_NOT_ALLOWED
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ManageKeyValueResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<ManageKeyValueResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    ManageKeyValueSuccess success_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<ManageKeyValueResultCode> &_xdr_case_values() {
    static const std::vector<ManageKeyValueResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)ManageKeyValueResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)ManageKeyValueResultCode::SUCCESS:
      _f(&ManageKeyValueResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in ManageKeyValueResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~ManageKeyValueResult();
      code_ = which;switch (code_)
{
      case (int32_t)ManageKeyValueResultCode::SUCCESS:
new(&success_) ManageKeyValueSuccess{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit ManageKeyValueResult(ManageKeyValueResultCode which = ManageKeyValueResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)ManageKeyValueResultCode::SUCCESS:
new(&success_) ManageKeyValueSuccess{};
break;
    default:
      break;
}

  }
  ManageKeyValueResult(const ManageKeyValueResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManageKeyValueResultCode::SUCCESS:
new(&success_) ManageKeyValueSuccess(source.success_);
break;
    default:
      break;
}

  }
  ManageKeyValueResult(ManageKeyValueResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManageKeyValueResultCode::SUCCESS:
new(&success_) ManageKeyValueSuccess(std::move(source.success_));
break;
    default:
      break;
}

  }
  ~ManageKeyValueResult() {
switch (code_)
{
  case (int32_t)ManageKeyValueResultCode::SUCCESS:
success_.~ManageKeyValueSuccess();
break;
  default:
    break;
}
}

  ManageKeyValueResult &operator=(const ManageKeyValueResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManageKeyValueResultCode::SUCCESS:
success_ = source.success_;
break;
    default:
      break;
}
}
else {this->~ManageKeyValueResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)ManageKeyValueResultCode::SUCCESS:
new(&success_) ManageKeyValueSuccess(source.success_);
break;
    default:
      break;
}
}
    return *this;
  }
  ManageKeyValueResult &operator=(ManageKeyValueResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManageKeyValueResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    default:
      break;
}
}
else {this->~ManageKeyValueResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)ManageKeyValueResultCode::SUCCESS:
new(&success_) ManageKeyValueSuccess(std::move(source.success_));
break;
    default:
      break;
}
}
    return *this;
  }

  ManageKeyValueResultCode code() const { return ManageKeyValueResultCode(code_); }
  ManageKeyValueResult &code(ManageKeyValueResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  ManageKeyValueSuccess &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageKeyValueResult: success accessed when not selected");
  }
  const ManageKeyValueSuccess &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageKeyValueResult: success accessed when not selected");
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

#endif // !__XDR_OPERATION_MANAGE_KEY_VALUE_H_INCLUDED__
