// -*- C++ -*-
// Automatically generated from operation-manage-account-rule.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_MANAGE_ACCOUNT_RULE_H_INCLUDED__
#define __XDR_OPERATION_MANAGE_ACCOUNT_RULE_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/ledger-entries.h"
#include "xdr/ledger-entries-account-rule.h"

namespace stellar {

enum class ManageAccountRuleAction : std::int32_t {
  CREATE = 0,
  UPDATE = 1,
  REMOVE = 2,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageAccountRuleAction>
  : xdr_integral_base<::stellar::ManageAccountRuleAction, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageAccountRuleAction val) {
    switch (val) {
    case ::stellar::ManageAccountRuleAction::CREATE:
      return "CREATE";
    case ::stellar::ManageAccountRuleAction::UPDATE:
      return "UPDATE";
    case ::stellar::ManageAccountRuleAction::REMOVE:
      return "REMOVE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageAccountRuleAction::CREATE,
      (int32_t)::stellar::ManageAccountRuleAction::UPDATE,
      (int32_t)::stellar::ManageAccountRuleAction::REMOVE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateAccountRuleData  : xdr::xdr_abstract {
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

  AccountRuleResource resource{};
  AccountRuleAction action{};
  bool forbids{};
  longstring details{};
  _ext_t ext{};

  CreateAccountRuleData() = default;
  template<typename _resource_T,
           typename _action_T,
           typename _forbids_T,
           typename _details_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<AccountRuleResource, _resource_T>::value
                          && std::is_constructible<AccountRuleAction, _action_T>::value
                          && std::is_constructible<bool, _forbids_T>::value
                          && std::is_constructible<longstring, _details_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateAccountRuleData(_resource_T &&_resource,
                                 _action_T &&_action,
                                 _forbids_T &&_forbids,
                                 _details_T &&_details,
                                 _ext_T &&_ext)
    : resource(std::forward<_resource_T>(_resource)),
      action(std::forward<_action_T>(_action)),
      forbids(std::forward<_forbids_T>(_forbids)),
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

struct UpdateAccountRuleData  : xdr::xdr_abstract {
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
  AccountRuleResource resource{};
  AccountRuleAction action{};
  bool forbids{};
  longstring details{};
  _ext_t ext{};

  UpdateAccountRuleData() = default;
  template<typename _ruleID_T,
           typename _resource_T,
           typename _action_T,
           typename _forbids_T,
           typename _details_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _ruleID_T>::value
                          && std::is_constructible<AccountRuleResource, _resource_T>::value
                          && std::is_constructible<AccountRuleAction, _action_T>::value
                          && std::is_constructible<bool, _forbids_T>::value
                          && std::is_constructible<longstring, _details_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit UpdateAccountRuleData(_ruleID_T &&_ruleID,
                                 _resource_T &&_resource,
                                 _action_T &&_action,
                                 _forbids_T &&_forbids,
                                 _details_T &&_details,
                                 _ext_T &&_ext)
    : ruleID(std::forward<_ruleID_T>(_ruleID)),
      resource(std::forward<_resource_T>(_resource)),
      action(std::forward<_action_T>(_action)),
      forbids(std::forward<_forbids_T>(_forbids)),
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

struct RemoveAccountRuleData  : xdr::xdr_abstract {
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

  RemoveAccountRuleData() = default;
  template<typename _ruleID_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _ruleID_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit RemoveAccountRuleData(_ruleID_T &&_ruleID,
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

struct ManageAccountRuleOp  : xdr::xdr_abstract {
  struct _data_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<ManageAccountRuleAction>::case_type;
  private:
    _xdr_case_type action_;
    union {
      CreateAccountRuleData createData_;
      UpdateAccountRuleData updateData_;
      RemoveAccountRuleData removeData_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<ManageAccountRuleAction> &_xdr_case_values() {
      static const std::vector<ManageAccountRuleAction> _xdr_disc_vec {
        ManageAccountRuleAction::CREATE,
        ManageAccountRuleAction::UPDATE,
        ManageAccountRuleAction::REMOVE
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)ManageAccountRuleAction::CREATE ? 1
        : which == (int32_t)ManageAccountRuleAction::UPDATE ? 2
        : which == (int32_t)ManageAccountRuleAction::REMOVE ? 3
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)ManageAccountRuleAction::CREATE:
        _f(&_data_t::createData_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ManageAccountRuleAction::UPDATE:
        _f(&_data_t::updateData_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ManageAccountRuleAction::REMOVE:
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
        case (int32_t)ManageAccountRuleAction::CREATE:
new(&createData_) CreateAccountRuleData{};
break;
        case (int32_t)ManageAccountRuleAction::UPDATE:
new(&updateData_) UpdateAccountRuleData{};
break;
        case (int32_t)ManageAccountRuleAction::REMOVE:
new(&removeData_) RemoveAccountRuleData{};
break;
}

      }
      else
        action_ = which;
    }
    explicit _data_t(ManageAccountRuleAction which = ManageAccountRuleAction{}) : action_((int32_t)which) {
      switch (action_)
{
      case (int32_t)ManageAccountRuleAction::CREATE:
new(&createData_) CreateAccountRuleData{};
break;
      case (int32_t)ManageAccountRuleAction::UPDATE:
new(&updateData_) UpdateAccountRuleData{};
break;
      case (int32_t)ManageAccountRuleAction::REMOVE:
new(&removeData_) RemoveAccountRuleData{};
break;
}

    }
    _data_t(const _data_t &source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageAccountRuleAction::CREATE:
new(&createData_) CreateAccountRuleData(source.createData_);
break;
      case (int32_t)ManageAccountRuleAction::UPDATE:
new(&updateData_) UpdateAccountRuleData(source.updateData_);
break;
      case (int32_t)ManageAccountRuleAction::REMOVE:
new(&removeData_) RemoveAccountRuleData(source.removeData_);
break;
}

    }
    _data_t(_data_t &&source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageAccountRuleAction::CREATE:
new(&createData_) CreateAccountRuleData(std::move(source.createData_));
break;
      case (int32_t)ManageAccountRuleAction::UPDATE:
new(&updateData_) UpdateAccountRuleData(std::move(source.updateData_));
break;
      case (int32_t)ManageAccountRuleAction::REMOVE:
new(&removeData_) RemoveAccountRuleData(std::move(source.removeData_));
break;
}

    }
    ~_data_t() {
switch (action_)
{
    case (int32_t)ManageAccountRuleAction::CREATE:
createData_.~CreateAccountRuleData();
break;
    case (int32_t)ManageAccountRuleAction::UPDATE:
updateData_.~UpdateAccountRuleData();
break;
    case (int32_t)ManageAccountRuleAction::REMOVE:
removeData_.~RemoveAccountRuleData();
break;
}
}

    _data_t &operator=(const _data_t &source) {
      if (action_ == source.action_)
{
switch (action_)
{
      case (int32_t)ManageAccountRuleAction::CREATE:
createData_ = source.createData_;
break;
      case (int32_t)ManageAccountRuleAction::UPDATE:
updateData_ = source.updateData_;
break;
      case (int32_t)ManageAccountRuleAction::REMOVE:
removeData_ = source.removeData_;
break;
}
}
else {this->~_data_t();
      action_ = source.action_;
switch (action_)
{
      case (int32_t)ManageAccountRuleAction::CREATE:
new(&createData_) CreateAccountRuleData(source.createData_);
break;
      case (int32_t)ManageAccountRuleAction::UPDATE:
new(&updateData_) UpdateAccountRuleData(source.updateData_);
break;
      case (int32_t)ManageAccountRuleAction::REMOVE:
new(&removeData_) RemoveAccountRuleData(source.removeData_);
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
      case (int32_t)ManageAccountRuleAction::CREATE:
createData_ = std::move(source.createData_);
break;
      case (int32_t)ManageAccountRuleAction::UPDATE:
updateData_ = std::move(source.updateData_);
break;
      case (int32_t)ManageAccountRuleAction::REMOVE:
removeData_ = std::move(source.removeData_);
break;
}
}
else {this->~_data_t();
      action_ = std::move(source.action_);
switch (action_)
{
      case (int32_t)ManageAccountRuleAction::CREATE:
new(&createData_) CreateAccountRuleData(std::move(source.createData_));
break;
      case (int32_t)ManageAccountRuleAction::UPDATE:
new(&updateData_) UpdateAccountRuleData(std::move(source.updateData_));
break;
      case (int32_t)ManageAccountRuleAction::REMOVE:
new(&removeData_) RemoveAccountRuleData(std::move(source.removeData_));
break;
}
}
      return *this;
    }

    ManageAccountRuleAction action() const { return ManageAccountRuleAction(action_); }
    _data_t &action(ManageAccountRuleAction _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    CreateAccountRuleData &createData() {
      if (_xdr_field_number(action_) == 1)
        return createData_;
      throw xdr::xdr_wrong_union("_data_t: createData accessed when not selected");
    }
    const CreateAccountRuleData &createData() const {
      if (_xdr_field_number(action_) == 1)
        return createData_;
      throw xdr::xdr_wrong_union("_data_t: createData accessed when not selected");
    }
    UpdateAccountRuleData &updateData() {
      if (_xdr_field_number(action_) == 2)
        return updateData_;
      throw xdr::xdr_wrong_union("_data_t: updateData accessed when not selected");
    }
    const UpdateAccountRuleData &updateData() const {
      if (_xdr_field_number(action_) == 2)
        return updateData_;
      throw xdr::xdr_wrong_union("_data_t: updateData accessed when not selected");
    }
    RemoveAccountRuleData &removeData() {
      if (_xdr_field_number(action_) == 3)
        return removeData_;
      throw xdr::xdr_wrong_union("_data_t: removeData accessed when not selected");
    }
    const RemoveAccountRuleData &removeData() const {
      if (_xdr_field_number(action_) == 3)
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

  ManageAccountRuleOp() = default;
  template<typename _data_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<_data_t, _data_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ManageAccountRuleOp(_data_T &&_data,
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

enum class ManageAccountRuleResultCode : std::int32_t {
  SUCCESS = 0,
  NOT_FOUND = -1,
  RULE_IS_USED = -2,
  INVALID_DETAILS = -3,
  INVALID_ACTION = -4,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageAccountRuleResultCode>
  : xdr_integral_base<::stellar::ManageAccountRuleResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageAccountRuleResultCode val) {
    switch (val) {
    case ::stellar::ManageAccountRuleResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::ManageAccountRuleResultCode::NOT_FOUND:
      return "NOT_FOUND";
    case ::stellar::ManageAccountRuleResultCode::RULE_IS_USED:
      return "RULE_IS_USED";
    case ::stellar::ManageAccountRuleResultCode::INVALID_DETAILS:
      return "INVALID_DETAILS";
    case ::stellar::ManageAccountRuleResultCode::INVALID_ACTION:
      return "INVALID_ACTION";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageAccountRuleResultCode::SUCCESS,
      (int32_t)::stellar::ManageAccountRuleResultCode::NOT_FOUND,
      (int32_t)::stellar::ManageAccountRuleResultCode::RULE_IS_USED,
      (int32_t)::stellar::ManageAccountRuleResultCode::INVALID_DETAILS,
      (int32_t)::stellar::ManageAccountRuleResultCode::INVALID_ACTION
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ManageAccountRuleResult : xdr::xdr_abstract {
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

  using _xdr_case_type = xdr::xdr_traits<ManageAccountRuleResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    _success_t success_;
    xdr::xvector<uint64> roleIDs_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<ManageAccountRuleResultCode> &_xdr_case_values() {
    static const std::vector<ManageAccountRuleResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)ManageAccountRuleResultCode::SUCCESS ? 1
      : which == (int32_t)ManageAccountRuleResultCode::RULE_IS_USED ? 2
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)ManageAccountRuleResultCode::SUCCESS:
      _f(&ManageAccountRuleResult::success_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)ManageAccountRuleResultCode::RULE_IS_USED:
      _f(&ManageAccountRuleResult::roleIDs_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in ManageAccountRuleResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~ManageAccountRuleResult();
      code_ = which;switch (code_)
{
      case (int32_t)ManageAccountRuleResultCode::SUCCESS:
new(&success_) _success_t{};
break;
      case (int32_t)ManageAccountRuleResultCode::RULE_IS_USED:
new(&roleIDs_) xdr::xvector<uint64>{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit ManageAccountRuleResult(ManageAccountRuleResultCode which = ManageAccountRuleResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)ManageAccountRuleResultCode::SUCCESS:
new(&success_) _success_t{};
break;
    case (int32_t)ManageAccountRuleResultCode::RULE_IS_USED:
new(&roleIDs_) xdr::xvector<uint64>{};
break;
    default:
      break;
}

  }
  ManageAccountRuleResult(const ManageAccountRuleResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManageAccountRuleResultCode::SUCCESS:
new(&success_) _success_t(source.success_);
break;
    case (int32_t)ManageAccountRuleResultCode::RULE_IS_USED:
new(&roleIDs_) xdr::xvector<uint64>(source.roleIDs_);
break;
    default:
      break;
}

  }
  ManageAccountRuleResult(ManageAccountRuleResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManageAccountRuleResultCode::SUCCESS:
new(&success_) _success_t(std::move(source.success_));
break;
    case (int32_t)ManageAccountRuleResultCode::RULE_IS_USED:
new(&roleIDs_) xdr::xvector<uint64>(std::move(source.roleIDs_));
break;
    default:
      break;
}

  }
  ~ManageAccountRuleResult() {
switch (code_)
{
  case (int32_t)ManageAccountRuleResultCode::SUCCESS:
success_.~_success_t();
break;
  case (int32_t)ManageAccountRuleResultCode::RULE_IS_USED:
roleIDs_.~xvector<uint64>();
break;
  default:
    break;
}
}

  ManageAccountRuleResult &operator=(const ManageAccountRuleResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManageAccountRuleResultCode::SUCCESS:
success_ = source.success_;
break;
    case (int32_t)ManageAccountRuleResultCode::RULE_IS_USED:
roleIDs_ = source.roleIDs_;
break;
    default:
      break;
}
}
else {this->~ManageAccountRuleResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)ManageAccountRuleResultCode::SUCCESS:
new(&success_) _success_t(source.success_);
break;
    case (int32_t)ManageAccountRuleResultCode::RULE_IS_USED:
new(&roleIDs_) xdr::xvector<uint64>(source.roleIDs_);
break;
    default:
      break;
}
}
    return *this;
  }
  ManageAccountRuleResult &operator=(ManageAccountRuleResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManageAccountRuleResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    case (int32_t)ManageAccountRuleResultCode::RULE_IS_USED:
roleIDs_ = std::move(source.roleIDs_);
break;
    default:
      break;
}
}
else {this->~ManageAccountRuleResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)ManageAccountRuleResultCode::SUCCESS:
new(&success_) _success_t(std::move(source.success_));
break;
    case (int32_t)ManageAccountRuleResultCode::RULE_IS_USED:
new(&roleIDs_) xdr::xvector<uint64>(std::move(source.roleIDs_));
break;
    default:
      break;
}
}
    return *this;
  }

  ManageAccountRuleResultCode code() const { return ManageAccountRuleResultCode(code_); }
  ManageAccountRuleResult &code(ManageAccountRuleResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  _success_t &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageAccountRuleResult: success accessed when not selected");
  }
  const _success_t &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageAccountRuleResult: success accessed when not selected");
  }
  xdr::xvector<uint64> &roleIDs() {
    if (_xdr_field_number(code_) == 2)
      return roleIDs_;
    throw xdr::xdr_wrong_union("ManageAccountRuleResult: roleIDs accessed when not selected");
  }
  const xdr::xvector<uint64> &roleIDs() const {
    if (_xdr_field_number(code_) == 2)
      return roleIDs_;
    throw xdr::xdr_wrong_union("ManageAccountRuleResult: roleIDs accessed when not selected");
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

#endif // !__XDR_OPERATION_MANAGE_ACCOUNT_RULE_H_INCLUDED__
