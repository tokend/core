// -*- C++ -*-
// Automatically generated from operation-manage-account-role.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_MANAGE_ACCOUNT_ROLE_H_INCLUDED__
#define __XDR_OPERATION_MANAGE_ACCOUNT_ROLE_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/ledger-entries.h"

namespace stellar {

enum class ManageAccountRoleAction : std::int32_t {
  CREATE = 0,
  UPDATE = 1,
  REMOVE = 2,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageAccountRoleAction>
  : xdr_integral_base<::stellar::ManageAccountRoleAction, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageAccountRoleAction val) {
    switch (val) {
    case ::stellar::ManageAccountRoleAction::CREATE:
      return "CREATE";
    case ::stellar::ManageAccountRoleAction::UPDATE:
      return "UPDATE";
    case ::stellar::ManageAccountRoleAction::REMOVE:
      return "REMOVE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageAccountRoleAction::CREATE,
      (int32_t)::stellar::ManageAccountRoleAction::UPDATE,
      (int32_t)::stellar::ManageAccountRoleAction::REMOVE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateAccountRoleData  : xdr::xdr_abstract {
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

  longstring details{};
  xdr::xvector<uint64> ruleIDs{};
  _ext_t ext{};

  CreateAccountRoleData() = default;
  template<typename _details_T,
           typename _ruleIDs_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<longstring, _details_T>::value
                          && std::is_constructible<xdr::xvector<uint64>, _ruleIDs_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateAccountRoleData(_details_T &&_details,
                                 _ruleIDs_T &&_ruleIDs,
                                 _ext_T &&_ext)
    : details(std::forward<_details_T>(_details)),
      ruleIDs(std::forward<_ruleIDs_T>(_ruleIDs)),
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

struct UpdateAccountRoleData  : xdr::xdr_abstract {
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

  uint64 roleID{};
  longstring details{};
  xdr::xvector<uint64> ruleIDs{};
  _ext_t ext{};

  UpdateAccountRoleData() = default;
  template<typename _roleID_T,
           typename _details_T,
           typename _ruleIDs_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _roleID_T>::value
                          && std::is_constructible<longstring, _details_T>::value
                          && std::is_constructible<xdr::xvector<uint64>, _ruleIDs_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit UpdateAccountRoleData(_roleID_T &&_roleID,
                                 _details_T &&_details,
                                 _ruleIDs_T &&_ruleIDs,
                                 _ext_T &&_ext)
    : roleID(std::forward<_roleID_T>(_roleID)),
      details(std::forward<_details_T>(_details)),
      ruleIDs(std::forward<_ruleIDs_T>(_ruleIDs)),
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

struct RemoveAccountRoleData  : xdr::xdr_abstract {
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

  uint64 roleID{};
  _ext_t ext{};

  RemoveAccountRoleData() = default;
  template<typename _roleID_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _roleID_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit RemoveAccountRoleData(_roleID_T &&_roleID,
                                 _ext_T &&_ext)
    : roleID(std::forward<_roleID_T>(_roleID)),
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

struct ManageAccountRoleOp  : xdr::xdr_abstract {
  struct _data_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<ManageAccountRoleAction>::case_type;
  private:
    _xdr_case_type action_;
    union {
      CreateAccountRoleData createData_;
      UpdateAccountRoleData updateData_;
      RemoveAccountRoleData removeData_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<ManageAccountRoleAction> &_xdr_case_values() {
      static const std::vector<ManageAccountRoleAction> _xdr_disc_vec {
        ManageAccountRoleAction::CREATE,
        ManageAccountRoleAction::UPDATE,
        ManageAccountRoleAction::REMOVE
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)ManageAccountRoleAction::CREATE ? 1
        : which == (int32_t)ManageAccountRoleAction::UPDATE ? 2
        : which == (int32_t)ManageAccountRoleAction::REMOVE ? 3
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)ManageAccountRoleAction::CREATE:
        _f(&_data_t::createData_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ManageAccountRoleAction::UPDATE:
        _f(&_data_t::updateData_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ManageAccountRoleAction::REMOVE:
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
        case (int32_t)ManageAccountRoleAction::CREATE:
new(&createData_) CreateAccountRoleData{};
break;
        case (int32_t)ManageAccountRoleAction::UPDATE:
new(&updateData_) UpdateAccountRoleData{};
break;
        case (int32_t)ManageAccountRoleAction::REMOVE:
new(&removeData_) RemoveAccountRoleData{};
break;
}

      }
      else
        action_ = which;
    }
    explicit _data_t(ManageAccountRoleAction which = ManageAccountRoleAction{}) : action_((int32_t)which) {
      switch (action_)
{
      case (int32_t)ManageAccountRoleAction::CREATE:
new(&createData_) CreateAccountRoleData{};
break;
      case (int32_t)ManageAccountRoleAction::UPDATE:
new(&updateData_) UpdateAccountRoleData{};
break;
      case (int32_t)ManageAccountRoleAction::REMOVE:
new(&removeData_) RemoveAccountRoleData{};
break;
}

    }
    _data_t(const _data_t &source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageAccountRoleAction::CREATE:
new(&createData_) CreateAccountRoleData(source.createData_);
break;
      case (int32_t)ManageAccountRoleAction::UPDATE:
new(&updateData_) UpdateAccountRoleData(source.updateData_);
break;
      case (int32_t)ManageAccountRoleAction::REMOVE:
new(&removeData_) RemoveAccountRoleData(source.removeData_);
break;
}

    }
    _data_t(_data_t &&source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageAccountRoleAction::CREATE:
new(&createData_) CreateAccountRoleData(std::move(source.createData_));
break;
      case (int32_t)ManageAccountRoleAction::UPDATE:
new(&updateData_) UpdateAccountRoleData(std::move(source.updateData_));
break;
      case (int32_t)ManageAccountRoleAction::REMOVE:
new(&removeData_) RemoveAccountRoleData(std::move(source.removeData_));
break;
}

    }
    ~_data_t() {
switch (action_)
{
    case (int32_t)ManageAccountRoleAction::CREATE:
createData_.~CreateAccountRoleData();
break;
    case (int32_t)ManageAccountRoleAction::UPDATE:
updateData_.~UpdateAccountRoleData();
break;
    case (int32_t)ManageAccountRoleAction::REMOVE:
removeData_.~RemoveAccountRoleData();
break;
}
}

    _data_t &operator=(const _data_t &source) {
      if (action_ == source.action_)
{
switch (action_)
{
      case (int32_t)ManageAccountRoleAction::CREATE:
createData_ = source.createData_;
break;
      case (int32_t)ManageAccountRoleAction::UPDATE:
updateData_ = source.updateData_;
break;
      case (int32_t)ManageAccountRoleAction::REMOVE:
removeData_ = source.removeData_;
break;
}
}
else {this->~_data_t();
      action_ = source.action_;
switch (action_)
{
      case (int32_t)ManageAccountRoleAction::CREATE:
new(&createData_) CreateAccountRoleData(source.createData_);
break;
      case (int32_t)ManageAccountRoleAction::UPDATE:
new(&updateData_) UpdateAccountRoleData(source.updateData_);
break;
      case (int32_t)ManageAccountRoleAction::REMOVE:
new(&removeData_) RemoveAccountRoleData(source.removeData_);
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
      case (int32_t)ManageAccountRoleAction::CREATE:
createData_ = std::move(source.createData_);
break;
      case (int32_t)ManageAccountRoleAction::UPDATE:
updateData_ = std::move(source.updateData_);
break;
      case (int32_t)ManageAccountRoleAction::REMOVE:
removeData_ = std::move(source.removeData_);
break;
}
}
else {this->~_data_t();
      action_ = std::move(source.action_);
switch (action_)
{
      case (int32_t)ManageAccountRoleAction::CREATE:
new(&createData_) CreateAccountRoleData(std::move(source.createData_));
break;
      case (int32_t)ManageAccountRoleAction::UPDATE:
new(&updateData_) UpdateAccountRoleData(std::move(source.updateData_));
break;
      case (int32_t)ManageAccountRoleAction::REMOVE:
new(&removeData_) RemoveAccountRoleData(std::move(source.removeData_));
break;
}
}
      return *this;
    }

    ManageAccountRoleAction action() const { return ManageAccountRoleAction(action_); }
    _data_t &action(ManageAccountRoleAction _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    CreateAccountRoleData &createData() {
      if (_xdr_field_number(action_) == 1)
        return createData_;
      throw xdr::xdr_wrong_union("_data_t: createData accessed when not selected");
    }
    const CreateAccountRoleData &createData() const {
      if (_xdr_field_number(action_) == 1)
        return createData_;
      throw xdr::xdr_wrong_union("_data_t: createData accessed when not selected");
    }
    UpdateAccountRoleData &updateData() {
      if (_xdr_field_number(action_) == 2)
        return updateData_;
      throw xdr::xdr_wrong_union("_data_t: updateData accessed when not selected");
    }
    const UpdateAccountRoleData &updateData() const {
      if (_xdr_field_number(action_) == 2)
        return updateData_;
      throw xdr::xdr_wrong_union("_data_t: updateData accessed when not selected");
    }
    RemoveAccountRoleData &removeData() {
      if (_xdr_field_number(action_) == 3)
        return removeData_;
      throw xdr::xdr_wrong_union("_data_t: removeData accessed when not selected");
    }
    const RemoveAccountRoleData &removeData() const {
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

  ManageAccountRoleOp() = default;
  template<typename _data_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<_data_t, _data_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ManageAccountRoleOp(_data_T &&_data,
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

enum class ManageAccountRoleResultCode : std::int32_t {
  SUCCESS = 0,
  NOT_FOUND = -1,
  ROLE_IS_USED = -2,
  INVALID_DETAILS = -3,
  NO_SUCH_RULE = -4,
  RULE_ID_DUPLICATION = -5,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageAccountRoleResultCode>
  : xdr_integral_base<::stellar::ManageAccountRoleResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageAccountRoleResultCode val) {
    switch (val) {
    case ::stellar::ManageAccountRoleResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::ManageAccountRoleResultCode::NOT_FOUND:
      return "NOT_FOUND";
    case ::stellar::ManageAccountRoleResultCode::ROLE_IS_USED:
      return "ROLE_IS_USED";
    case ::stellar::ManageAccountRoleResultCode::INVALID_DETAILS:
      return "INVALID_DETAILS";
    case ::stellar::ManageAccountRoleResultCode::NO_SUCH_RULE:
      return "NO_SUCH_RULE";
    case ::stellar::ManageAccountRoleResultCode::RULE_ID_DUPLICATION:
      return "RULE_ID_DUPLICATION";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageAccountRoleResultCode::SUCCESS,
      (int32_t)::stellar::ManageAccountRoleResultCode::NOT_FOUND,
      (int32_t)::stellar::ManageAccountRoleResultCode::ROLE_IS_USED,
      (int32_t)::stellar::ManageAccountRoleResultCode::INVALID_DETAILS,
      (int32_t)::stellar::ManageAccountRoleResultCode::NO_SUCH_RULE,
      (int32_t)::stellar::ManageAccountRoleResultCode::RULE_ID_DUPLICATION
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ManageAccountRoleResult : xdr::xdr_abstract {
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

    uint64 roleID{};
    _ext_t ext{};

    _success_t() = default;
    template<typename _roleID_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _roleID_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _success_t(_roleID_T &&_roleID,
                        _ext_T &&_ext)
      : roleID(std::forward<_roleID_T>(_roleID)),
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

  using _xdr_case_type = xdr::xdr_traits<ManageAccountRoleResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    _success_t success_;
    uint64 ruleID_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<ManageAccountRoleResultCode> &_xdr_case_values() {
    static const std::vector<ManageAccountRoleResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)ManageAccountRoleResultCode::SUCCESS ? 1
      : which == (int32_t)ManageAccountRoleResultCode::RULE_ID_DUPLICATION || which == (int32_t)ManageAccountRoleResultCode::NO_SUCH_RULE ? 2
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)ManageAccountRoleResultCode::SUCCESS:
      _f(&ManageAccountRoleResult::success_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)ManageAccountRoleResultCode::RULE_ID_DUPLICATION:
    case (int32_t)ManageAccountRoleResultCode::NO_SUCH_RULE:
      _f(&ManageAccountRoleResult::ruleID_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in ManageAccountRoleResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~ManageAccountRoleResult();
      code_ = which;switch (code_)
{
      case (int32_t)ManageAccountRoleResultCode::SUCCESS:
new(&success_) _success_t{};
break;
      case (int32_t)ManageAccountRoleResultCode::RULE_ID_DUPLICATION:
      case (int32_t)ManageAccountRoleResultCode::NO_SUCH_RULE:
new(&ruleID_) uint64{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit ManageAccountRoleResult(ManageAccountRoleResultCode which = ManageAccountRoleResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)ManageAccountRoleResultCode::SUCCESS:
new(&success_) _success_t{};
break;
    case (int32_t)ManageAccountRoleResultCode::RULE_ID_DUPLICATION:
    case (int32_t)ManageAccountRoleResultCode::NO_SUCH_RULE:
new(&ruleID_) uint64{};
break;
    default:
      break;
}

  }
  ManageAccountRoleResult(const ManageAccountRoleResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManageAccountRoleResultCode::SUCCESS:
new(&success_) _success_t(source.success_);
break;
    case (int32_t)ManageAccountRoleResultCode::RULE_ID_DUPLICATION:
    case (int32_t)ManageAccountRoleResultCode::NO_SUCH_RULE:
new(&ruleID_) uint64(source.ruleID_);
break;
    default:
      break;
}

  }
  ManageAccountRoleResult(ManageAccountRoleResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManageAccountRoleResultCode::SUCCESS:
new(&success_) _success_t(std::move(source.success_));
break;
    case (int32_t)ManageAccountRoleResultCode::RULE_ID_DUPLICATION:
    case (int32_t)ManageAccountRoleResultCode::NO_SUCH_RULE:
new(&ruleID_) uint64(std::move(source.ruleID_));
break;
    default:
      break;
}

  }
  ~ManageAccountRoleResult() {
switch (code_)
{
  case (int32_t)ManageAccountRoleResultCode::SUCCESS:
success_.~_success_t();
break;
  case (int32_t)ManageAccountRoleResultCode::RULE_ID_DUPLICATION:
  case (int32_t)ManageAccountRoleResultCode::NO_SUCH_RULE:
ruleID_.~uint64();
break;
  default:
    break;
}
}

  ManageAccountRoleResult &operator=(const ManageAccountRoleResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManageAccountRoleResultCode::SUCCESS:
success_ = source.success_;
break;
    case (int32_t)ManageAccountRoleResultCode::RULE_ID_DUPLICATION:
    case (int32_t)ManageAccountRoleResultCode::NO_SUCH_RULE:
ruleID_ = source.ruleID_;
break;
    default:
      break;
}
}
else {this->~ManageAccountRoleResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)ManageAccountRoleResultCode::SUCCESS:
new(&success_) _success_t(source.success_);
break;
    case (int32_t)ManageAccountRoleResultCode::RULE_ID_DUPLICATION:
    case (int32_t)ManageAccountRoleResultCode::NO_SUCH_RULE:
new(&ruleID_) uint64(source.ruleID_);
break;
    default:
      break;
}
}
    return *this;
  }
  ManageAccountRoleResult &operator=(ManageAccountRoleResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManageAccountRoleResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    case (int32_t)ManageAccountRoleResultCode::RULE_ID_DUPLICATION:
    case (int32_t)ManageAccountRoleResultCode::NO_SUCH_RULE:
ruleID_ = std::move(source.ruleID_);
break;
    default:
      break;
}
}
else {this->~ManageAccountRoleResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)ManageAccountRoleResultCode::SUCCESS:
new(&success_) _success_t(std::move(source.success_));
break;
    case (int32_t)ManageAccountRoleResultCode::RULE_ID_DUPLICATION:
    case (int32_t)ManageAccountRoleResultCode::NO_SUCH_RULE:
new(&ruleID_) uint64(std::move(source.ruleID_));
break;
    default:
      break;
}
}
    return *this;
  }

  ManageAccountRoleResultCode code() const { return ManageAccountRoleResultCode(code_); }
  ManageAccountRoleResult &code(ManageAccountRoleResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  _success_t &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageAccountRoleResult: success accessed when not selected");
  }
  const _success_t &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageAccountRoleResult: success accessed when not selected");
  }
  uint64 &ruleID() {
    if (_xdr_field_number(code_) == 2)
      return ruleID_;
    throw xdr::xdr_wrong_union("ManageAccountRoleResult: ruleID accessed when not selected");
  }
  const uint64 &ruleID() const {
    if (_xdr_field_number(code_) == 2)
      return ruleID_;
    throw xdr::xdr_wrong_union("ManageAccountRoleResult: ruleID accessed when not selected");
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

#endif // !__XDR_OPERATION_MANAGE_ACCOUNT_ROLE_H_INCLUDED__
