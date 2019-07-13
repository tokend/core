// -*- C++ -*-
// Automatically generated from operation-manage-signer-role.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_MANAGE_SIGNER_ROLE_H_INCLUDED__
#define __XDR_OPERATION_MANAGE_SIGNER_ROLE_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/ledger-entries.h"
#include "xdr/resource-signer-rule.h"

namespace stellar {

enum class ManageSignerRoleAction : std::int32_t {
  CREATE = 0,
  UPDATE = 1,
  REMOVE = 2,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageSignerRoleAction>
  : xdr_integral_base<::stellar::ManageSignerRoleAction, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageSignerRoleAction val) {
    switch (val) {
    case ::stellar::ManageSignerRoleAction::CREATE:
      return "CREATE";
    case ::stellar::ManageSignerRoleAction::UPDATE:
      return "UPDATE";
    case ::stellar::ManageSignerRoleAction::REMOVE:
      return "REMOVE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageSignerRoleAction::CREATE,
      (int32_t)::stellar::ManageSignerRoleAction::UPDATE,
      (int32_t)::stellar::ManageSignerRoleAction::REMOVE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateSignerRoleData  : xdr::xdr_abstract {
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

  xdr::xvector<uint64> ruleIDs{};
  bool isReadOnly{};
  longstring details{};
  _ext_t ext{};

  CreateSignerRoleData() = default;
  template<typename _ruleIDs_T,
           typename _isReadOnly_T,
           typename _details_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xvector<uint64>, _ruleIDs_T>::value
                          && std::is_constructible<bool, _isReadOnly_T>::value
                          && std::is_constructible<longstring, _details_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateSignerRoleData(_ruleIDs_T &&_ruleIDs,
                                _isReadOnly_T &&_isReadOnly,
                                _details_T &&_details,
                                _ext_T &&_ext)
    : ruleIDs(std::forward<_ruleIDs_T>(_ruleIDs)),
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

struct UpdateSignerRoleData  : xdr::xdr_abstract {
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
  xdr::xvector<uint64> ruleIDs{};
  longstring details{};
  _ext_t ext{};

  UpdateSignerRoleData() = default;
  template<typename _roleID_T,
           typename _ruleIDs_T,
           typename _details_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _roleID_T>::value
                          && std::is_constructible<xdr::xvector<uint64>, _ruleIDs_T>::value
                          && std::is_constructible<longstring, _details_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit UpdateSignerRoleData(_roleID_T &&_roleID,
                                _ruleIDs_T &&_ruleIDs,
                                _details_T &&_details,
                                _ext_T &&_ext)
    : roleID(std::forward<_roleID_T>(_roleID)),
      ruleIDs(std::forward<_ruleIDs_T>(_ruleIDs)),
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

struct RemoveSignerRoleData  : xdr::xdr_abstract {
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

  RemoveSignerRoleData() = default;
  template<typename _roleID_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _roleID_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit RemoveSignerRoleData(_roleID_T &&_roleID,
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

struct ManageSignerRoleOp  : xdr::xdr_abstract {
  struct _data_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<ManageSignerRoleAction>::case_type;
  private:
    _xdr_case_type action_;
    union {
      CreateSignerRoleData createData_;
      UpdateSignerRoleData updateData_;
      RemoveSignerRoleData removeData_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<ManageSignerRoleAction> &_xdr_case_values() {
      static const std::vector<ManageSignerRoleAction> _xdr_disc_vec {
        ManageSignerRoleAction::CREATE,
        ManageSignerRoleAction::UPDATE,
        ManageSignerRoleAction::REMOVE
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)ManageSignerRoleAction::CREATE ? 1
        : which == (int32_t)ManageSignerRoleAction::UPDATE ? 2
        : which == (int32_t)ManageSignerRoleAction::REMOVE ? 3
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)ManageSignerRoleAction::CREATE:
        _f(&_data_t::createData_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ManageSignerRoleAction::UPDATE:
        _f(&_data_t::updateData_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ManageSignerRoleAction::REMOVE:
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
        case (int32_t)ManageSignerRoleAction::CREATE:
new(&createData_) CreateSignerRoleData{};
break;
        case (int32_t)ManageSignerRoleAction::UPDATE:
new(&updateData_) UpdateSignerRoleData{};
break;
        case (int32_t)ManageSignerRoleAction::REMOVE:
new(&removeData_) RemoveSignerRoleData{};
break;
}

      }
      else
        action_ = which;
    }
    explicit _data_t(ManageSignerRoleAction which = ManageSignerRoleAction{}) : action_((int32_t)which) {
      switch (action_)
{
      case (int32_t)ManageSignerRoleAction::CREATE:
new(&createData_) CreateSignerRoleData{};
break;
      case (int32_t)ManageSignerRoleAction::UPDATE:
new(&updateData_) UpdateSignerRoleData{};
break;
      case (int32_t)ManageSignerRoleAction::REMOVE:
new(&removeData_) RemoveSignerRoleData{};
break;
}

    }
    _data_t(const _data_t &source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageSignerRoleAction::CREATE:
new(&createData_) CreateSignerRoleData(source.createData_);
break;
      case (int32_t)ManageSignerRoleAction::UPDATE:
new(&updateData_) UpdateSignerRoleData(source.updateData_);
break;
      case (int32_t)ManageSignerRoleAction::REMOVE:
new(&removeData_) RemoveSignerRoleData(source.removeData_);
break;
}

    }
    _data_t(_data_t &&source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageSignerRoleAction::CREATE:
new(&createData_) CreateSignerRoleData(std::move(source.createData_));
break;
      case (int32_t)ManageSignerRoleAction::UPDATE:
new(&updateData_) UpdateSignerRoleData(std::move(source.updateData_));
break;
      case (int32_t)ManageSignerRoleAction::REMOVE:
new(&removeData_) RemoveSignerRoleData(std::move(source.removeData_));
break;
}

    }
    ~_data_t() {
switch (action_)
{
    case (int32_t)ManageSignerRoleAction::CREATE:
createData_.~CreateSignerRoleData();
break;
    case (int32_t)ManageSignerRoleAction::UPDATE:
updateData_.~UpdateSignerRoleData();
break;
    case (int32_t)ManageSignerRoleAction::REMOVE:
removeData_.~RemoveSignerRoleData();
break;
}
}

    _data_t &operator=(const _data_t &source) {
      if (action_ == source.action_)
{
switch (action_)
{
      case (int32_t)ManageSignerRoleAction::CREATE:
createData_ = source.createData_;
break;
      case (int32_t)ManageSignerRoleAction::UPDATE:
updateData_ = source.updateData_;
break;
      case (int32_t)ManageSignerRoleAction::REMOVE:
removeData_ = source.removeData_;
break;
}
}
else {this->~_data_t();
      action_ = source.action_;
switch (action_)
{
      case (int32_t)ManageSignerRoleAction::CREATE:
new(&createData_) CreateSignerRoleData(source.createData_);
break;
      case (int32_t)ManageSignerRoleAction::UPDATE:
new(&updateData_) UpdateSignerRoleData(source.updateData_);
break;
      case (int32_t)ManageSignerRoleAction::REMOVE:
new(&removeData_) RemoveSignerRoleData(source.removeData_);
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
      case (int32_t)ManageSignerRoleAction::CREATE:
createData_ = std::move(source.createData_);
break;
      case (int32_t)ManageSignerRoleAction::UPDATE:
updateData_ = std::move(source.updateData_);
break;
      case (int32_t)ManageSignerRoleAction::REMOVE:
removeData_ = std::move(source.removeData_);
break;
}
}
else {this->~_data_t();
      action_ = std::move(source.action_);
switch (action_)
{
      case (int32_t)ManageSignerRoleAction::CREATE:
new(&createData_) CreateSignerRoleData(std::move(source.createData_));
break;
      case (int32_t)ManageSignerRoleAction::UPDATE:
new(&updateData_) UpdateSignerRoleData(std::move(source.updateData_));
break;
      case (int32_t)ManageSignerRoleAction::REMOVE:
new(&removeData_) RemoveSignerRoleData(std::move(source.removeData_));
break;
}
}
      return *this;
    }

    ManageSignerRoleAction action() const { return ManageSignerRoleAction(action_); }
    _data_t &action(ManageSignerRoleAction _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    CreateSignerRoleData &createData() {
      if (_xdr_field_number(action_) == 1)
        return createData_;
      throw xdr::xdr_wrong_union("_data_t: createData accessed when not selected");
    }
    const CreateSignerRoleData &createData() const {
      if (_xdr_field_number(action_) == 1)
        return createData_;
      throw xdr::xdr_wrong_union("_data_t: createData accessed when not selected");
    }
    UpdateSignerRoleData &updateData() {
      if (_xdr_field_number(action_) == 2)
        return updateData_;
      throw xdr::xdr_wrong_union("_data_t: updateData accessed when not selected");
    }
    const UpdateSignerRoleData &updateData() const {
      if (_xdr_field_number(action_) == 2)
        return updateData_;
      throw xdr::xdr_wrong_union("_data_t: updateData accessed when not selected");
    }
    RemoveSignerRoleData &removeData() {
      if (_xdr_field_number(action_) == 3)
        return removeData_;
      throw xdr::xdr_wrong_union("_data_t: removeData accessed when not selected");
    }
    const RemoveSignerRoleData &removeData() const {
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

  ManageSignerRoleOp() = default;
  template<typename _data_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<_data_t, _data_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ManageSignerRoleOp(_data_T &&_data,
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

enum class ManageSignerRoleResultCode : std::int32_t {
  SUCCESS = 0,
  NOT_FOUND = -1,
  ROLE_IS_USED = -2,
  INVALID_DETAILS = -3,
  NO_SUCH_RULE = -4,
  RULE_ID_DUPLICATION = -5,
  DEFAULT_RULE_ID_DUPLICATION = -6,
  TOO_MANY_RULE_IDS = -7,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageSignerRoleResultCode>
  : xdr_integral_base<::stellar::ManageSignerRoleResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageSignerRoleResultCode val) {
    switch (val) {
    case ::stellar::ManageSignerRoleResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::ManageSignerRoleResultCode::NOT_FOUND:
      return "NOT_FOUND";
    case ::stellar::ManageSignerRoleResultCode::ROLE_IS_USED:
      return "ROLE_IS_USED";
    case ::stellar::ManageSignerRoleResultCode::INVALID_DETAILS:
      return "INVALID_DETAILS";
    case ::stellar::ManageSignerRoleResultCode::NO_SUCH_RULE:
      return "NO_SUCH_RULE";
    case ::stellar::ManageSignerRoleResultCode::RULE_ID_DUPLICATION:
      return "RULE_ID_DUPLICATION";
    case ::stellar::ManageSignerRoleResultCode::DEFAULT_RULE_ID_DUPLICATION:
      return "DEFAULT_RULE_ID_DUPLICATION";
    case ::stellar::ManageSignerRoleResultCode::TOO_MANY_RULE_IDS:
      return "TOO_MANY_RULE_IDS";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageSignerRoleResultCode::SUCCESS,
      (int32_t)::stellar::ManageSignerRoleResultCode::NOT_FOUND,
      (int32_t)::stellar::ManageSignerRoleResultCode::ROLE_IS_USED,
      (int32_t)::stellar::ManageSignerRoleResultCode::INVALID_DETAILS,
      (int32_t)::stellar::ManageSignerRoleResultCode::NO_SUCH_RULE,
      (int32_t)::stellar::ManageSignerRoleResultCode::RULE_ID_DUPLICATION,
      (int32_t)::stellar::ManageSignerRoleResultCode::DEFAULT_RULE_ID_DUPLICATION,
      (int32_t)::stellar::ManageSignerRoleResultCode::TOO_MANY_RULE_IDS
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ManageSignerRoleResult : xdr::xdr_abstract {
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

  using _xdr_case_type = xdr::xdr_traits<ManageSignerRoleResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    _success_t success_;
    uint64 ruleID_;
    uint64 maxRuleIDsCount_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<ManageSignerRoleResultCode> &_xdr_case_values() {
    static const std::vector<ManageSignerRoleResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)ManageSignerRoleResultCode::SUCCESS ? 1
      : which == (int32_t)ManageSignerRoleResultCode::RULE_ID_DUPLICATION || which == (int32_t)ManageSignerRoleResultCode::DEFAULT_RULE_ID_DUPLICATION || which == (int32_t)ManageSignerRoleResultCode::NO_SUCH_RULE ? 2
      : which == (int32_t)ManageSignerRoleResultCode::TOO_MANY_RULE_IDS ? 3
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)ManageSignerRoleResultCode::SUCCESS:
      _f(&ManageSignerRoleResult::success_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)ManageSignerRoleResultCode::RULE_ID_DUPLICATION:
    case (int32_t)ManageSignerRoleResultCode::DEFAULT_RULE_ID_DUPLICATION:
    case (int32_t)ManageSignerRoleResultCode::NO_SUCH_RULE:
      _f(&ManageSignerRoleResult::ruleID_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)ManageSignerRoleResultCode::TOO_MANY_RULE_IDS:
      _f(&ManageSignerRoleResult::maxRuleIDsCount_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in ManageSignerRoleResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~ManageSignerRoleResult();
      code_ = which;switch (code_)
{
      case (int32_t)ManageSignerRoleResultCode::SUCCESS:
new(&success_) _success_t{};
break;
      case (int32_t)ManageSignerRoleResultCode::RULE_ID_DUPLICATION:
      case (int32_t)ManageSignerRoleResultCode::DEFAULT_RULE_ID_DUPLICATION:
      case (int32_t)ManageSignerRoleResultCode::NO_SUCH_RULE:
new(&ruleID_) uint64{};
break;
      case (int32_t)ManageSignerRoleResultCode::TOO_MANY_RULE_IDS:
new(&maxRuleIDsCount_) uint64{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit ManageSignerRoleResult(ManageSignerRoleResultCode which = ManageSignerRoleResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)ManageSignerRoleResultCode::SUCCESS:
new(&success_) _success_t{};
break;
    case (int32_t)ManageSignerRoleResultCode::RULE_ID_DUPLICATION:
    case (int32_t)ManageSignerRoleResultCode::DEFAULT_RULE_ID_DUPLICATION:
    case (int32_t)ManageSignerRoleResultCode::NO_SUCH_RULE:
new(&ruleID_) uint64{};
break;
    case (int32_t)ManageSignerRoleResultCode::TOO_MANY_RULE_IDS:
new(&maxRuleIDsCount_) uint64{};
break;
    default:
      break;
}

  }
  ManageSignerRoleResult(const ManageSignerRoleResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManageSignerRoleResultCode::SUCCESS:
new(&success_) _success_t(source.success_);
break;
    case (int32_t)ManageSignerRoleResultCode::RULE_ID_DUPLICATION:
    case (int32_t)ManageSignerRoleResultCode::DEFAULT_RULE_ID_DUPLICATION:
    case (int32_t)ManageSignerRoleResultCode::NO_SUCH_RULE:
new(&ruleID_) uint64(source.ruleID_);
break;
    case (int32_t)ManageSignerRoleResultCode::TOO_MANY_RULE_IDS:
new(&maxRuleIDsCount_) uint64(source.maxRuleIDsCount_);
break;
    default:
      break;
}

  }
  ManageSignerRoleResult(ManageSignerRoleResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManageSignerRoleResultCode::SUCCESS:
new(&success_) _success_t(std::move(source.success_));
break;
    case (int32_t)ManageSignerRoleResultCode::RULE_ID_DUPLICATION:
    case (int32_t)ManageSignerRoleResultCode::DEFAULT_RULE_ID_DUPLICATION:
    case (int32_t)ManageSignerRoleResultCode::NO_SUCH_RULE:
new(&ruleID_) uint64(std::move(source.ruleID_));
break;
    case (int32_t)ManageSignerRoleResultCode::TOO_MANY_RULE_IDS:
new(&maxRuleIDsCount_) uint64(std::move(source.maxRuleIDsCount_));
break;
    default:
      break;
}

  }
  ~ManageSignerRoleResult() {
switch (code_)
{
  case (int32_t)ManageSignerRoleResultCode::SUCCESS:
success_.~_success_t();
break;
  case (int32_t)ManageSignerRoleResultCode::RULE_ID_DUPLICATION:
  case (int32_t)ManageSignerRoleResultCode::DEFAULT_RULE_ID_DUPLICATION:
  case (int32_t)ManageSignerRoleResultCode::NO_SUCH_RULE:
ruleID_.~uint64();
break;
  case (int32_t)ManageSignerRoleResultCode::TOO_MANY_RULE_IDS:
maxRuleIDsCount_.~uint64();
break;
  default:
    break;
}
}

  ManageSignerRoleResult &operator=(const ManageSignerRoleResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManageSignerRoleResultCode::SUCCESS:
success_ = source.success_;
break;
    case (int32_t)ManageSignerRoleResultCode::RULE_ID_DUPLICATION:
    case (int32_t)ManageSignerRoleResultCode::DEFAULT_RULE_ID_DUPLICATION:
    case (int32_t)ManageSignerRoleResultCode::NO_SUCH_RULE:
ruleID_ = source.ruleID_;
break;
    case (int32_t)ManageSignerRoleResultCode::TOO_MANY_RULE_IDS:
maxRuleIDsCount_ = source.maxRuleIDsCount_;
break;
    default:
      break;
}
}
else {this->~ManageSignerRoleResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)ManageSignerRoleResultCode::SUCCESS:
new(&success_) _success_t(source.success_);
break;
    case (int32_t)ManageSignerRoleResultCode::RULE_ID_DUPLICATION:
    case (int32_t)ManageSignerRoleResultCode::DEFAULT_RULE_ID_DUPLICATION:
    case (int32_t)ManageSignerRoleResultCode::NO_SUCH_RULE:
new(&ruleID_) uint64(source.ruleID_);
break;
    case (int32_t)ManageSignerRoleResultCode::TOO_MANY_RULE_IDS:
new(&maxRuleIDsCount_) uint64(source.maxRuleIDsCount_);
break;
    default:
      break;
}
}
    return *this;
  }
  ManageSignerRoleResult &operator=(ManageSignerRoleResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManageSignerRoleResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    case (int32_t)ManageSignerRoleResultCode::RULE_ID_DUPLICATION:
    case (int32_t)ManageSignerRoleResultCode::DEFAULT_RULE_ID_DUPLICATION:
    case (int32_t)ManageSignerRoleResultCode::NO_SUCH_RULE:
ruleID_ = std::move(source.ruleID_);
break;
    case (int32_t)ManageSignerRoleResultCode::TOO_MANY_RULE_IDS:
maxRuleIDsCount_ = std::move(source.maxRuleIDsCount_);
break;
    default:
      break;
}
}
else {this->~ManageSignerRoleResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)ManageSignerRoleResultCode::SUCCESS:
new(&success_) _success_t(std::move(source.success_));
break;
    case (int32_t)ManageSignerRoleResultCode::RULE_ID_DUPLICATION:
    case (int32_t)ManageSignerRoleResultCode::DEFAULT_RULE_ID_DUPLICATION:
    case (int32_t)ManageSignerRoleResultCode::NO_SUCH_RULE:
new(&ruleID_) uint64(std::move(source.ruleID_));
break;
    case (int32_t)ManageSignerRoleResultCode::TOO_MANY_RULE_IDS:
new(&maxRuleIDsCount_) uint64(std::move(source.maxRuleIDsCount_));
break;
    default:
      break;
}
}
    return *this;
  }

  ManageSignerRoleResultCode code() const { return ManageSignerRoleResultCode(code_); }
  ManageSignerRoleResult &code(ManageSignerRoleResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  _success_t &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageSignerRoleResult: success accessed when not selected");
  }
  const _success_t &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageSignerRoleResult: success accessed when not selected");
  }
  uint64 &ruleID() {
    if (_xdr_field_number(code_) == 2)
      return ruleID_;
    throw xdr::xdr_wrong_union("ManageSignerRoleResult: ruleID accessed when not selected");
  }
  const uint64 &ruleID() const {
    if (_xdr_field_number(code_) == 2)
      return ruleID_;
    throw xdr::xdr_wrong_union("ManageSignerRoleResult: ruleID accessed when not selected");
  }
  uint64 &maxRuleIDsCount() {
    if (_xdr_field_number(code_) == 3)
      return maxRuleIDsCount_;
    throw xdr::xdr_wrong_union("ManageSignerRoleResult: maxRuleIDsCount accessed when not selected");
  }
  const uint64 &maxRuleIDsCount() const {
    if (_xdr_field_number(code_) == 3)
      return maxRuleIDsCount_;
    throw xdr::xdr_wrong_union("ManageSignerRoleResult: maxRuleIDsCount accessed when not selected");
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

#endif // !__XDR_OPERATION_MANAGE_SIGNER_ROLE_H_INCLUDED__
