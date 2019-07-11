// -*- C++ -*-
// Automatically generated from operation-manage-account-specific-rule.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_MANAGE_ACCOUNT_SPECIFIC_RULE_H_INCLUDED__
#define __XDR_OPERATION_MANAGE_ACCOUNT_SPECIFIC_RULE_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/ledger-keys.h"

namespace stellar {

enum class ManageAccountSpecificRuleAction : std::int32_t {
  CREATE = 0,
  REMOVE = 1,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageAccountSpecificRuleAction>
  : xdr_integral_base<::stellar::ManageAccountSpecificRuleAction, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageAccountSpecificRuleAction val) {
    switch (val) {
    case ::stellar::ManageAccountSpecificRuleAction::CREATE:
      return "CREATE";
    case ::stellar::ManageAccountSpecificRuleAction::REMOVE:
      return "REMOVE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageAccountSpecificRuleAction::CREATE,
      (int32_t)::stellar::ManageAccountSpecificRuleAction::REMOVE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateAccountSpecificRuleData  : xdr::xdr_abstract {
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

  LedgerKey ledgerKey{};
  xdr::pointer<AccountID> accountID{};
  bool forbids{};
  _ext_t ext{};

  CreateAccountSpecificRuleData() = default;
  template<typename _ledgerKey_T,
           typename _accountID_T,
           typename _forbids_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<LedgerKey, _ledgerKey_T>::value
                          && std::is_constructible<xdr::pointer<AccountID>, _accountID_T>::value
                          && std::is_constructible<bool, _forbids_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateAccountSpecificRuleData(_ledgerKey_T &&_ledgerKey,
                                         _accountID_T &&_accountID,
                                         _forbids_T &&_forbids,
                                         _ext_T &&_ext)
    : ledgerKey(std::forward<_ledgerKey_T>(_ledgerKey)),
      accountID(std::forward<_accountID_T>(_accountID)),
      forbids(std::forward<_forbids_T>(_forbids)),
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

struct RemoveAccountSpecificRuleData  : xdr::xdr_abstract {
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

  uint64 ruleID{};
  _ext_t ext{};

  RemoveAccountSpecificRuleData() = default;
  template<typename _ruleID_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _ruleID_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit RemoveAccountSpecificRuleData(_ruleID_T &&_ruleID,
                                         _ext_T &&_ext)
    : ruleID(std::forward<_ruleID_T>(_ruleID)),
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

struct ManageAccountSpecificRuleOp  : xdr::xdr_abstract {
  struct _data_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<ManageAccountSpecificRuleAction>::case_type;
  private:
    _xdr_case_type action_;
    union {
      CreateAccountSpecificRuleData createData_;
      RemoveAccountSpecificRuleData removeData_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<ManageAccountSpecificRuleAction> &_xdr_case_values() {
      static const std::vector<ManageAccountSpecificRuleAction> _xdr_disc_vec {
        ManageAccountSpecificRuleAction::CREATE,
        ManageAccountSpecificRuleAction::REMOVE
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)ManageAccountSpecificRuleAction::CREATE ? 1
        : which == (int32_t)ManageAccountSpecificRuleAction::REMOVE ? 2
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)ManageAccountSpecificRuleAction::CREATE:
        _f(&_data_t::createData_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ManageAccountSpecificRuleAction::REMOVE:
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
        case (int32_t)ManageAccountSpecificRuleAction::CREATE:
new(&createData_) CreateAccountSpecificRuleData{};
break;
        case (int32_t)ManageAccountSpecificRuleAction::REMOVE:
new(&removeData_) RemoveAccountSpecificRuleData{};
break;
}

      }
      else
        action_ = which;
    }
    explicit _data_t(ManageAccountSpecificRuleAction which = ManageAccountSpecificRuleAction{}) : action_((int32_t)which) {
      switch (action_)
{
      case (int32_t)ManageAccountSpecificRuleAction::CREATE:
new(&createData_) CreateAccountSpecificRuleData{};
break;
      case (int32_t)ManageAccountSpecificRuleAction::REMOVE:
new(&removeData_) RemoveAccountSpecificRuleData{};
break;
}

    }
    _data_t(const _data_t &source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageAccountSpecificRuleAction::CREATE:
new(&createData_) CreateAccountSpecificRuleData(source.createData_);
break;
      case (int32_t)ManageAccountSpecificRuleAction::REMOVE:
new(&removeData_) RemoveAccountSpecificRuleData(source.removeData_);
break;
}

    }
    _data_t(_data_t &&source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageAccountSpecificRuleAction::CREATE:
new(&createData_) CreateAccountSpecificRuleData(std::move(source.createData_));
break;
      case (int32_t)ManageAccountSpecificRuleAction::REMOVE:
new(&removeData_) RemoveAccountSpecificRuleData(std::move(source.removeData_));
break;
}

    }
    ~_data_t() {
switch (action_)
{
    case (int32_t)ManageAccountSpecificRuleAction::CREATE:
createData_.~CreateAccountSpecificRuleData();
break;
    case (int32_t)ManageAccountSpecificRuleAction::REMOVE:
removeData_.~RemoveAccountSpecificRuleData();
break;
}
}

    _data_t &operator=(const _data_t &source) {
      if (action_ == source.action_)
{
switch (action_)
{
      case (int32_t)ManageAccountSpecificRuleAction::CREATE:
createData_ = source.createData_;
break;
      case (int32_t)ManageAccountSpecificRuleAction::REMOVE:
removeData_ = source.removeData_;
break;
}
}
else {this->~_data_t();
      action_ = source.action_;
switch (action_)
{
      case (int32_t)ManageAccountSpecificRuleAction::CREATE:
new(&createData_) CreateAccountSpecificRuleData(source.createData_);
break;
      case (int32_t)ManageAccountSpecificRuleAction::REMOVE:
new(&removeData_) RemoveAccountSpecificRuleData(source.removeData_);
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
      case (int32_t)ManageAccountSpecificRuleAction::CREATE:
createData_ = std::move(source.createData_);
break;
      case (int32_t)ManageAccountSpecificRuleAction::REMOVE:
removeData_ = std::move(source.removeData_);
break;
}
}
else {this->~_data_t();
      action_ = std::move(source.action_);
switch (action_)
{
      case (int32_t)ManageAccountSpecificRuleAction::CREATE:
new(&createData_) CreateAccountSpecificRuleData(std::move(source.createData_));
break;
      case (int32_t)ManageAccountSpecificRuleAction::REMOVE:
new(&removeData_) RemoveAccountSpecificRuleData(std::move(source.removeData_));
break;
}
}
      return *this;
    }

    ManageAccountSpecificRuleAction action() const { return ManageAccountSpecificRuleAction(action_); }
    _data_t &action(ManageAccountSpecificRuleAction _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    CreateAccountSpecificRuleData &createData() {
      if (_xdr_field_number(action_) == 1)
        return createData_;
      throw xdr::xdr_wrong_union("_data_t: createData accessed when not selected");
    }
    const CreateAccountSpecificRuleData &createData() const {
      if (_xdr_field_number(action_) == 1)
        return createData_;
      throw xdr::xdr_wrong_union("_data_t: createData accessed when not selected");
    }
    RemoveAccountSpecificRuleData &removeData() {
      if (_xdr_field_number(action_) == 2)
        return removeData_;
      throw xdr::xdr_wrong_union("_data_t: removeData accessed when not selected");
    }
    const RemoveAccountSpecificRuleData &removeData() const {
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

  ManageAccountSpecificRuleOp() = default;
  template<typename _data_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<_data_t, _data_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ManageAccountSpecificRuleOp(_data_T &&_data,
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

enum class ManageAccountSpecificRuleResultCode : std::int32_t {
  SUCCESS = 0,
  NOT_FOUND = -1,
  SALE_NOT_FOUND = -2,
  NOT_AUTHORIZED = -3,
  ALREADY_EXISTS = -4,
  REVERSED_ALREADY_EXISTS = -5,
  ENTRY_TYPE_NOT_SUPPORTED = -6,
  ACCOUNT_NOT_FOUND = -7,
  SPECIFIC_RULE_NOT_SUPPORTED = -8,
  REMOVING_GLOBAL_RULE_FORBIDDEN = -9,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageAccountSpecificRuleResultCode>
  : xdr_integral_base<::stellar::ManageAccountSpecificRuleResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageAccountSpecificRuleResultCode val) {
    switch (val) {
    case ::stellar::ManageAccountSpecificRuleResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::ManageAccountSpecificRuleResultCode::NOT_FOUND:
      return "NOT_FOUND";
    case ::stellar::ManageAccountSpecificRuleResultCode::SALE_NOT_FOUND:
      return "SALE_NOT_FOUND";
    case ::stellar::ManageAccountSpecificRuleResultCode::NOT_AUTHORIZED:
      return "NOT_AUTHORIZED";
    case ::stellar::ManageAccountSpecificRuleResultCode::ALREADY_EXISTS:
      return "ALREADY_EXISTS";
    case ::stellar::ManageAccountSpecificRuleResultCode::REVERSED_ALREADY_EXISTS:
      return "REVERSED_ALREADY_EXISTS";
    case ::stellar::ManageAccountSpecificRuleResultCode::ENTRY_TYPE_NOT_SUPPORTED:
      return "ENTRY_TYPE_NOT_SUPPORTED";
    case ::stellar::ManageAccountSpecificRuleResultCode::ACCOUNT_NOT_FOUND:
      return "ACCOUNT_NOT_FOUND";
    case ::stellar::ManageAccountSpecificRuleResultCode::SPECIFIC_RULE_NOT_SUPPORTED:
      return "SPECIFIC_RULE_NOT_SUPPORTED";
    case ::stellar::ManageAccountSpecificRuleResultCode::REMOVING_GLOBAL_RULE_FORBIDDEN:
      return "REMOVING_GLOBAL_RULE_FORBIDDEN";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageAccountSpecificRuleResultCode::SUCCESS,
      (int32_t)::stellar::ManageAccountSpecificRuleResultCode::NOT_FOUND,
      (int32_t)::stellar::ManageAccountSpecificRuleResultCode::SALE_NOT_FOUND,
      (int32_t)::stellar::ManageAccountSpecificRuleResultCode::NOT_AUTHORIZED,
      (int32_t)::stellar::ManageAccountSpecificRuleResultCode::ALREADY_EXISTS,
      (int32_t)::stellar::ManageAccountSpecificRuleResultCode::REVERSED_ALREADY_EXISTS,
      (int32_t)::stellar::ManageAccountSpecificRuleResultCode::ENTRY_TYPE_NOT_SUPPORTED,
      (int32_t)::stellar::ManageAccountSpecificRuleResultCode::ACCOUNT_NOT_FOUND,
      (int32_t)::stellar::ManageAccountSpecificRuleResultCode::SPECIFIC_RULE_NOT_SUPPORTED,
      (int32_t)::stellar::ManageAccountSpecificRuleResultCode::REMOVING_GLOBAL_RULE_FORBIDDEN
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ManageAccountSpecificRuleResult : xdr::xdr_abstract {
  struct _success_t  : xdr::xdr_abstract {
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

    uint64 ruleID{};
    _ext_t ext{};

    _success_t() = default;
    template<typename _ruleID_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _ruleID_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _success_t(_ruleID_T &&_ruleID,
                        _ext_T &&_ext)
      : ruleID(std::forward<_ruleID_T>(_ruleID)),
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

  using _xdr_case_type = xdr::xdr_traits<ManageAccountSpecificRuleResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    _success_t success_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<ManageAccountSpecificRuleResultCode> &_xdr_case_values() {
    static const std::vector<ManageAccountSpecificRuleResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)ManageAccountSpecificRuleResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)ManageAccountSpecificRuleResultCode::SUCCESS:
      _f(&ManageAccountSpecificRuleResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in ManageAccountSpecificRuleResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~ManageAccountSpecificRuleResult();
      code_ = which;switch (code_)
{
      case (int32_t)ManageAccountSpecificRuleResultCode::SUCCESS:
new(&success_) _success_t{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit ManageAccountSpecificRuleResult(ManageAccountSpecificRuleResultCode which = ManageAccountSpecificRuleResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)ManageAccountSpecificRuleResultCode::SUCCESS:
new(&success_) _success_t{};
break;
    default:
      break;
}

  }
  ManageAccountSpecificRuleResult(const ManageAccountSpecificRuleResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManageAccountSpecificRuleResultCode::SUCCESS:
new(&success_) _success_t(source.success_);
break;
    default:
      break;
}

  }
  ManageAccountSpecificRuleResult(ManageAccountSpecificRuleResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManageAccountSpecificRuleResultCode::SUCCESS:
new(&success_) _success_t(std::move(source.success_));
break;
    default:
      break;
}

  }
  ~ManageAccountSpecificRuleResult() {
switch (code_)
{
  case (int32_t)ManageAccountSpecificRuleResultCode::SUCCESS:
success_.~_success_t();
break;
  default:
    break;
}
}

  ManageAccountSpecificRuleResult &operator=(const ManageAccountSpecificRuleResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManageAccountSpecificRuleResultCode::SUCCESS:
success_ = source.success_;
break;
    default:
      break;
}
}
else {this->~ManageAccountSpecificRuleResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)ManageAccountSpecificRuleResultCode::SUCCESS:
new(&success_) _success_t(source.success_);
break;
    default:
      break;
}
}
    return *this;
  }
  ManageAccountSpecificRuleResult &operator=(ManageAccountSpecificRuleResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManageAccountSpecificRuleResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    default:
      break;
}
}
else {this->~ManageAccountSpecificRuleResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)ManageAccountSpecificRuleResultCode::SUCCESS:
new(&success_) _success_t(std::move(source.success_));
break;
    default:
      break;
}
}
    return *this;
  }

  ManageAccountSpecificRuleResultCode code() const { return ManageAccountSpecificRuleResultCode(code_); }
  ManageAccountSpecificRuleResult &code(ManageAccountSpecificRuleResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  _success_t &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageAccountSpecificRuleResult: success accessed when not selected");
  }
  const _success_t &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageAccountSpecificRuleResult: success accessed when not selected");
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

#endif // !__XDR_OPERATION_MANAGE_ACCOUNT_SPECIFIC_RULE_H_INCLUDED__
