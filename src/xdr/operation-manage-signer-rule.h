// -*- C++ -*-
// Automatically generated from operation-manage-signer-rule.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_MANAGE_SIGNER_RULE_H_INCLUDED__
#define __XDR_OPERATION_MANAGE_SIGNER_RULE_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/ledger-entries.h"
#include "xdr/resource-signer-rule.h"

namespace stellar {

enum class ManageSignerRuleAction : std::int32_t {
  CREATE = 0,
  UPDATE = 1,
  REMOVE = 2,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageSignerRuleAction>
  : xdr_integral_base<::stellar::ManageSignerRuleAction, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageSignerRuleAction val) {
    switch (val) {
    case ::stellar::ManageSignerRuleAction::CREATE:
      return "CREATE";
    case ::stellar::ManageSignerRuleAction::UPDATE:
      return "UPDATE";
    case ::stellar::ManageSignerRuleAction::REMOVE:
      return "REMOVE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageSignerRuleAction::CREATE,
      (int32_t)::stellar::ManageSignerRuleAction::UPDATE,
      (int32_t)::stellar::ManageSignerRuleAction::REMOVE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateSignerRuleData  : xdr::xdr_abstract {
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

  SignerRuleResource resource{};
  SignerRuleAction action{};
  bool forbids{};
  bool isDefault{};
  bool isReadOnly{};
  longstring details{};
  _ext_t ext{};

  CreateSignerRuleData() = default;
  template<typename _resource_T,
           typename _action_T,
           typename _forbids_T,
           typename _isDefault_T,
           typename _isReadOnly_T,
           typename _details_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<SignerRuleResource, _resource_T>::value
                          && std::is_constructible<SignerRuleAction, _action_T>::value
                          && std::is_constructible<bool, _forbids_T>::value
                          && std::is_constructible<bool, _isDefault_T>::value
                          && std::is_constructible<bool, _isReadOnly_T>::value
                          && std::is_constructible<longstring, _details_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateSignerRuleData(_resource_T &&_resource,
                                _action_T &&_action,
                                _forbids_T &&_forbids,
                                _isDefault_T &&_isDefault,
                                _isReadOnly_T &&_isReadOnly,
                                _details_T &&_details,
                                _ext_T &&_ext)
    : resource(std::forward<_resource_T>(_resource)),
      action(std::forward<_action_T>(_action)),
      forbids(std::forward<_forbids_T>(_forbids)),
      isDefault(std::forward<_isDefault_T>(_isDefault)),
      isReadOnly(std::forward<_isReadOnly_T>(_isReadOnly)),
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

struct UpdateSignerRuleData  : xdr::xdr_abstract {
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
  SignerRuleResource resource{};
  SignerRuleAction action{};
  bool forbids{};
  bool isDefault{};
  longstring details{};
  _ext_t ext{};

  UpdateSignerRuleData() = default;
  template<typename _ruleID_T,
           typename _resource_T,
           typename _action_T,
           typename _forbids_T,
           typename _isDefault_T,
           typename _details_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _ruleID_T>::value
                          && std::is_constructible<SignerRuleResource, _resource_T>::value
                          && std::is_constructible<SignerRuleAction, _action_T>::value
                          && std::is_constructible<bool, _forbids_T>::value
                          && std::is_constructible<bool, _isDefault_T>::value
                          && std::is_constructible<longstring, _details_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit UpdateSignerRuleData(_ruleID_T &&_ruleID,
                                _resource_T &&_resource,
                                _action_T &&_action,
                                _forbids_T &&_forbids,
                                _isDefault_T &&_isDefault,
                                _details_T &&_details,
                                _ext_T &&_ext)
    : ruleID(std::forward<_ruleID_T>(_ruleID)),
      resource(std::forward<_resource_T>(_resource)),
      action(std::forward<_action_T>(_action)),
      forbids(std::forward<_forbids_T>(_forbids)),
      isDefault(std::forward<_isDefault_T>(_isDefault)),
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

struct RemoveSignerRuleData  : xdr::xdr_abstract {
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

  RemoveSignerRuleData() = default;
  template<typename _ruleID_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _ruleID_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit RemoveSignerRuleData(_ruleID_T &&_ruleID,
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

struct ManageSignerRuleOp  : xdr::xdr_abstract {
  struct _data_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<ManageSignerRuleAction>::case_type;
  private:
    _xdr_case_type action_;
    union {
      CreateSignerRuleData createData_;
      UpdateSignerRuleData updateData_;
      RemoveSignerRuleData removeData_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<ManageSignerRuleAction> &_xdr_case_values() {
      static const std::vector<ManageSignerRuleAction> _xdr_disc_vec {
        ManageSignerRuleAction::CREATE,
        ManageSignerRuleAction::UPDATE,
        ManageSignerRuleAction::REMOVE
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)ManageSignerRuleAction::CREATE ? 1
        : which == (int32_t)ManageSignerRuleAction::UPDATE ? 2
        : which == (int32_t)ManageSignerRuleAction::REMOVE ? 3
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)ManageSignerRuleAction::CREATE:
        _f(&_data_t::createData_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ManageSignerRuleAction::UPDATE:
        _f(&_data_t::updateData_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ManageSignerRuleAction::REMOVE:
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
        case (int32_t)ManageSignerRuleAction::CREATE:
new(&createData_) CreateSignerRuleData{};
break;
        case (int32_t)ManageSignerRuleAction::UPDATE:
new(&updateData_) UpdateSignerRuleData{};
break;
        case (int32_t)ManageSignerRuleAction::REMOVE:
new(&removeData_) RemoveSignerRuleData{};
break;
}

      }
      else
        action_ = which;
    }
    explicit _data_t(ManageSignerRuleAction which = ManageSignerRuleAction{}) : action_((int32_t)which) {
      switch (action_)
{
      case (int32_t)ManageSignerRuleAction::CREATE:
new(&createData_) CreateSignerRuleData{};
break;
      case (int32_t)ManageSignerRuleAction::UPDATE:
new(&updateData_) UpdateSignerRuleData{};
break;
      case (int32_t)ManageSignerRuleAction::REMOVE:
new(&removeData_) RemoveSignerRuleData{};
break;
}

    }
    _data_t(const _data_t &source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageSignerRuleAction::CREATE:
new(&createData_) CreateSignerRuleData(source.createData_);
break;
      case (int32_t)ManageSignerRuleAction::UPDATE:
new(&updateData_) UpdateSignerRuleData(source.updateData_);
break;
      case (int32_t)ManageSignerRuleAction::REMOVE:
new(&removeData_) RemoveSignerRuleData(source.removeData_);
break;
}

    }
    _data_t(_data_t &&source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageSignerRuleAction::CREATE:
new(&createData_) CreateSignerRuleData(std::move(source.createData_));
break;
      case (int32_t)ManageSignerRuleAction::UPDATE:
new(&updateData_) UpdateSignerRuleData(std::move(source.updateData_));
break;
      case (int32_t)ManageSignerRuleAction::REMOVE:
new(&removeData_) RemoveSignerRuleData(std::move(source.removeData_));
break;
}

    }
    ~_data_t() {
switch (action_)
{
    case (int32_t)ManageSignerRuleAction::CREATE:
createData_.~CreateSignerRuleData();
break;
    case (int32_t)ManageSignerRuleAction::UPDATE:
updateData_.~UpdateSignerRuleData();
break;
    case (int32_t)ManageSignerRuleAction::REMOVE:
removeData_.~RemoveSignerRuleData();
break;
}
}

    _data_t &operator=(const _data_t &source) {
      if (action_ == source.action_)
{
switch (action_)
{
      case (int32_t)ManageSignerRuleAction::CREATE:
createData_ = source.createData_;
break;
      case (int32_t)ManageSignerRuleAction::UPDATE:
updateData_ = source.updateData_;
break;
      case (int32_t)ManageSignerRuleAction::REMOVE:
removeData_ = source.removeData_;
break;
}
}
else {this->~_data_t();
      action_ = source.action_;
switch (action_)
{
      case (int32_t)ManageSignerRuleAction::CREATE:
new(&createData_) CreateSignerRuleData(source.createData_);
break;
      case (int32_t)ManageSignerRuleAction::UPDATE:
new(&updateData_) UpdateSignerRuleData(source.updateData_);
break;
      case (int32_t)ManageSignerRuleAction::REMOVE:
new(&removeData_) RemoveSignerRuleData(source.removeData_);
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
      case (int32_t)ManageSignerRuleAction::CREATE:
createData_ = std::move(source.createData_);
break;
      case (int32_t)ManageSignerRuleAction::UPDATE:
updateData_ = std::move(source.updateData_);
break;
      case (int32_t)ManageSignerRuleAction::REMOVE:
removeData_ = std::move(source.removeData_);
break;
}
}
else {this->~_data_t();
      action_ = std::move(source.action_);
switch (action_)
{
      case (int32_t)ManageSignerRuleAction::CREATE:
new(&createData_) CreateSignerRuleData(std::move(source.createData_));
break;
      case (int32_t)ManageSignerRuleAction::UPDATE:
new(&updateData_) UpdateSignerRuleData(std::move(source.updateData_));
break;
      case (int32_t)ManageSignerRuleAction::REMOVE:
new(&removeData_) RemoveSignerRuleData(std::move(source.removeData_));
break;
}
}
      return *this;
    }

    ManageSignerRuleAction action() const { return ManageSignerRuleAction(action_); }
    _data_t &action(ManageSignerRuleAction _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    CreateSignerRuleData &createData() {
      if (_xdr_field_number(action_) == 1)
        return createData_;
      throw xdr::xdr_wrong_union("_data_t: createData accessed when not selected");
    }
    const CreateSignerRuleData &createData() const {
      if (_xdr_field_number(action_) == 1)
        return createData_;
      throw xdr::xdr_wrong_union("_data_t: createData accessed when not selected");
    }
    UpdateSignerRuleData &updateData() {
      if (_xdr_field_number(action_) == 2)
        return updateData_;
      throw xdr::xdr_wrong_union("_data_t: updateData accessed when not selected");
    }
    const UpdateSignerRuleData &updateData() const {
      if (_xdr_field_number(action_) == 2)
        return updateData_;
      throw xdr::xdr_wrong_union("_data_t: updateData accessed when not selected");
    }
    RemoveSignerRuleData &removeData() {
      if (_xdr_field_number(action_) == 3)
        return removeData_;
      throw xdr::xdr_wrong_union("_data_t: removeData accessed when not selected");
    }
    const RemoveSignerRuleData &removeData() const {
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

  ManageSignerRuleOp() = default;
  template<typename _data_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<_data_t, _data_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ManageSignerRuleOp(_data_T &&_data,
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

enum class ManageSignerRuleResultCode : std::int32_t {
  SUCCESS = 0,
  NOT_FOUND = -1,
  RULE_IS_USED = -2,
  INVALID_DETAILS = -3,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageSignerRuleResultCode>
  : xdr_integral_base<::stellar::ManageSignerRuleResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageSignerRuleResultCode val) {
    switch (val) {
    case ::stellar::ManageSignerRuleResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::ManageSignerRuleResultCode::NOT_FOUND:
      return "NOT_FOUND";
    case ::stellar::ManageSignerRuleResultCode::RULE_IS_USED:
      return "RULE_IS_USED";
    case ::stellar::ManageSignerRuleResultCode::INVALID_DETAILS:
      return "INVALID_DETAILS";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageSignerRuleResultCode::SUCCESS,
      (int32_t)::stellar::ManageSignerRuleResultCode::NOT_FOUND,
      (int32_t)::stellar::ManageSignerRuleResultCode::RULE_IS_USED,
      (int32_t)::stellar::ManageSignerRuleResultCode::INVALID_DETAILS
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ManageSignerRuleResult : xdr::xdr_abstract {
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

  using _xdr_case_type = xdr::xdr_traits<ManageSignerRuleResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    _success_t success_;
    xdr::xvector<uint64> roleIDs_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<ManageSignerRuleResultCode> &_xdr_case_values() {
    static const std::vector<ManageSignerRuleResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)ManageSignerRuleResultCode::SUCCESS ? 1
      : which == (int32_t)ManageSignerRuleResultCode::RULE_IS_USED ? 2
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)ManageSignerRuleResultCode::SUCCESS:
      _f(&ManageSignerRuleResult::success_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)ManageSignerRuleResultCode::RULE_IS_USED:
      _f(&ManageSignerRuleResult::roleIDs_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in ManageSignerRuleResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~ManageSignerRuleResult();
      code_ = which;switch (code_)
{
      case (int32_t)ManageSignerRuleResultCode::SUCCESS:
new(&success_) _success_t{};
break;
      case (int32_t)ManageSignerRuleResultCode::RULE_IS_USED:
new(&roleIDs_) xdr::xvector<uint64>{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit ManageSignerRuleResult(ManageSignerRuleResultCode which = ManageSignerRuleResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)ManageSignerRuleResultCode::SUCCESS:
new(&success_) _success_t{};
break;
    case (int32_t)ManageSignerRuleResultCode::RULE_IS_USED:
new(&roleIDs_) xdr::xvector<uint64>{};
break;
    default:
      break;
}

  }
  ManageSignerRuleResult(const ManageSignerRuleResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManageSignerRuleResultCode::SUCCESS:
new(&success_) _success_t(source.success_);
break;
    case (int32_t)ManageSignerRuleResultCode::RULE_IS_USED:
new(&roleIDs_) xdr::xvector<uint64>(source.roleIDs_);
break;
    default:
      break;
}

  }
  ManageSignerRuleResult(ManageSignerRuleResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManageSignerRuleResultCode::SUCCESS:
new(&success_) _success_t(std::move(source.success_));
break;
    case (int32_t)ManageSignerRuleResultCode::RULE_IS_USED:
new(&roleIDs_) xdr::xvector<uint64>(std::move(source.roleIDs_));
break;
    default:
      break;
}

  }
  ~ManageSignerRuleResult() {
switch (code_)
{
  case (int32_t)ManageSignerRuleResultCode::SUCCESS:
success_.~_success_t();
break;
  case (int32_t)ManageSignerRuleResultCode::RULE_IS_USED:
roleIDs_.~xvector<uint64>();
break;
  default:
    break;
}
}

  ManageSignerRuleResult &operator=(const ManageSignerRuleResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManageSignerRuleResultCode::SUCCESS:
success_ = source.success_;
break;
    case (int32_t)ManageSignerRuleResultCode::RULE_IS_USED:
roleIDs_ = source.roleIDs_;
break;
    default:
      break;
}
}
else {this->~ManageSignerRuleResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)ManageSignerRuleResultCode::SUCCESS:
new(&success_) _success_t(source.success_);
break;
    case (int32_t)ManageSignerRuleResultCode::RULE_IS_USED:
new(&roleIDs_) xdr::xvector<uint64>(source.roleIDs_);
break;
    default:
      break;
}
}
    return *this;
  }
  ManageSignerRuleResult &operator=(ManageSignerRuleResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManageSignerRuleResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    case (int32_t)ManageSignerRuleResultCode::RULE_IS_USED:
roleIDs_ = std::move(source.roleIDs_);
break;
    default:
      break;
}
}
else {this->~ManageSignerRuleResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)ManageSignerRuleResultCode::SUCCESS:
new(&success_) _success_t(std::move(source.success_));
break;
    case (int32_t)ManageSignerRuleResultCode::RULE_IS_USED:
new(&roleIDs_) xdr::xvector<uint64>(std::move(source.roleIDs_));
break;
    default:
      break;
}
}
    return *this;
  }

  ManageSignerRuleResultCode code() const { return ManageSignerRuleResultCode(code_); }
  ManageSignerRuleResult &code(ManageSignerRuleResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  _success_t &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageSignerRuleResult: success accessed when not selected");
  }
  const _success_t &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageSignerRuleResult: success accessed when not selected");
  }
  xdr::xvector<uint64> &roleIDs() {
    if (_xdr_field_number(code_) == 2)
      return roleIDs_;
    throw xdr::xdr_wrong_union("ManageSignerRuleResult: roleIDs accessed when not selected");
  }
  const xdr::xvector<uint64> &roleIDs() const {
    if (_xdr_field_number(code_) == 2)
      return roleIDs_;
    throw xdr::xdr_wrong_union("ManageSignerRuleResult: roleIDs accessed when not selected");
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

#endif // !__XDR_OPERATION_MANAGE_SIGNER_RULE_H_INCLUDED__
