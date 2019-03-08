// -*- C++ -*-
// Automatically generated from Stellar-operation-manage-signer-role.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_OPERATION_MANAGE_SIGNER_ROLE_H_INCLUDED__
#define __XDR_STELLAR_OPERATION_MANAGE_SIGNER_ROLE_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-ledger-entries.h"
#include "xdr/Stellar-resource-signer-rule.h"

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
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
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

struct CreateSignerRoleData {
  struct _ext_t {
    using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
  private:
    _xdr_case_type v_;
    union {
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<LedgerVersion> &_xdr_case_values() {
      static const std::vector<LedgerVersion> _xdr_disc_vec {
        LedgerVersion::EMPTY_VERSION
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
        v_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
      }
      else
        v_ = which;
    }
    explicit _ext_t(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                        std::move(source));
    }
    ~_ext_t() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
    _ext_t &operator=(const _ext_t &source) {
      if (_xdr_field_number(v_)
          == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
      }
      v_ = source.v_;
      return *this;
    }
    _ext_t &operator=(_ext_t &&source) {
      if (_xdr_field_number(v_)
           == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                          std::move(source));
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                          std::move(source));
      }
      v_ = source.v_;
      return *this;
    }

    LedgerVersion v() const { return LedgerVersion(v_); }
    _ext_t &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateSignerRoleData::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CreateSignerRoleData::_ext_t;
  using case_type = ::stellar::CreateSignerRoleData::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::CreateSignerRoleData::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateSignerRoleData::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateSignerRoleData::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::CreateSignerRoleData>
  : xdr_struct_base<field_ptr<::stellar::CreateSignerRoleData,
                              decltype(::stellar::CreateSignerRoleData::ruleIDs),
                              &::stellar::CreateSignerRoleData::ruleIDs>,
                    field_ptr<::stellar::CreateSignerRoleData,
                              decltype(::stellar::CreateSignerRoleData::isReadOnly),
                              &::stellar::CreateSignerRoleData::isReadOnly>,
                    field_ptr<::stellar::CreateSignerRoleData,
                              decltype(::stellar::CreateSignerRoleData::details),
                              &::stellar::CreateSignerRoleData::details>,
                    field_ptr<::stellar::CreateSignerRoleData,
                              decltype(::stellar::CreateSignerRoleData::ext),
                              &::stellar::CreateSignerRoleData::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateSignerRoleData &obj) {
    archive(ar, obj.ruleIDs, "ruleIDs");
    archive(ar, obj.isReadOnly, "isReadOnly");
    archive(ar, obj.details, "details");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateSignerRoleData &obj) {
    archive(ar, obj.ruleIDs, "ruleIDs");
    archive(ar, obj.isReadOnly, "isReadOnly");
    archive(ar, obj.details, "details");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct UpdateSignerRoleData {
  struct _ext_t {
    using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
  private:
    _xdr_case_type v_;
    union {
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<LedgerVersion> &_xdr_case_values() {
      static const std::vector<LedgerVersion> _xdr_disc_vec {
        LedgerVersion::EMPTY_VERSION
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
        v_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
      }
      else
        v_ = which;
    }
    explicit _ext_t(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                        std::move(source));
    }
    ~_ext_t() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
    _ext_t &operator=(const _ext_t &source) {
      if (_xdr_field_number(v_)
          == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
      }
      v_ = source.v_;
      return *this;
    }
    _ext_t &operator=(_ext_t &&source) {
      if (_xdr_field_number(v_)
           == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                          std::move(source));
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                          std::move(source));
      }
      v_ = source.v_;
      return *this;
    }

    LedgerVersion v() const { return LedgerVersion(v_); }
    _ext_t &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::UpdateSignerRoleData::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::UpdateSignerRoleData::_ext_t;
  using case_type = ::stellar::UpdateSignerRoleData::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::UpdateSignerRoleData::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::UpdateSignerRoleData::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::UpdateSignerRoleData::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::UpdateSignerRoleData>
  : xdr_struct_base<field_ptr<::stellar::UpdateSignerRoleData,
                              decltype(::stellar::UpdateSignerRoleData::roleID),
                              &::stellar::UpdateSignerRoleData::roleID>,
                    field_ptr<::stellar::UpdateSignerRoleData,
                              decltype(::stellar::UpdateSignerRoleData::ruleIDs),
                              &::stellar::UpdateSignerRoleData::ruleIDs>,
                    field_ptr<::stellar::UpdateSignerRoleData,
                              decltype(::stellar::UpdateSignerRoleData::details),
                              &::stellar::UpdateSignerRoleData::details>,
                    field_ptr<::stellar::UpdateSignerRoleData,
                              decltype(::stellar::UpdateSignerRoleData::ext),
                              &::stellar::UpdateSignerRoleData::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::UpdateSignerRoleData &obj) {
    archive(ar, obj.roleID, "roleID");
    archive(ar, obj.ruleIDs, "ruleIDs");
    archive(ar, obj.details, "details");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::UpdateSignerRoleData &obj) {
    archive(ar, obj.roleID, "roleID");
    archive(ar, obj.ruleIDs, "ruleIDs");
    archive(ar, obj.details, "details");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct RemoveSignerRoleData {
  struct _ext_t {
    using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
  private:
    _xdr_case_type v_;
    union {
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<LedgerVersion> &_xdr_case_values() {
      static const std::vector<LedgerVersion> _xdr_disc_vec {
        LedgerVersion::EMPTY_VERSION
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
        v_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
      }
      else
        v_ = which;
    }
    explicit _ext_t(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                        std::move(source));
    }
    ~_ext_t() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
    _ext_t &operator=(const _ext_t &source) {
      if (_xdr_field_number(v_)
          == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
      }
      v_ = source.v_;
      return *this;
    }
    _ext_t &operator=(_ext_t &&source) {
      if (_xdr_field_number(v_)
           == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                          std::move(source));
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                          std::move(source));
      }
      v_ = source.v_;
      return *this;
    }

    LedgerVersion v() const { return LedgerVersion(v_); }
    _ext_t &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::RemoveSignerRoleData::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::RemoveSignerRoleData::_ext_t;
  using case_type = ::stellar::RemoveSignerRoleData::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::RemoveSignerRoleData::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::RemoveSignerRoleData::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::RemoveSignerRoleData::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::RemoveSignerRoleData>
  : xdr_struct_base<field_ptr<::stellar::RemoveSignerRoleData,
                              decltype(::stellar::RemoveSignerRoleData::roleID),
                              &::stellar::RemoveSignerRoleData::roleID>,
                    field_ptr<::stellar::RemoveSignerRoleData,
                              decltype(::stellar::RemoveSignerRoleData::ext),
                              &::stellar::RemoveSignerRoleData::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::RemoveSignerRoleData &obj) {
    archive(ar, obj.roleID, "roleID");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::RemoveSignerRoleData &obj) {
    archive(ar, obj.roleID, "roleID");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ManageSignerRoleOp {
  struct _data_t {
    using _xdr_case_type = xdr::xdr_traits<ManageSignerRoleAction>::case_type;
  private:
    _xdr_case_type action_;
    union {
      CreateSignerRoleData createData_;
      UpdateSignerRoleData updateData_;
      RemoveSignerRoleData removeData_;
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<ManageSignerRoleAction> &_xdr_case_values() {
      static const std::vector<ManageSignerRoleAction> _xdr_disc_vec {
        ManageSignerRoleAction::CREATE,
        ManageSignerRoleAction::UPDATE,
        ManageSignerRoleAction::REMOVE
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
        action_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, action_, *this);
      }
      else
        action_ = which;
    }
    explicit _data_t(ManageSignerRoleAction which = ManageSignerRoleAction{}) : action_((int32_t)which) {
      _xdr_with_mem_ptr(xdr::field_constructor, action_, *this);
    }
    _data_t(const _data_t &source) : action_(source.action_) {
      _xdr_with_mem_ptr(xdr::field_constructor, action_, *this, source);
    }
    _data_t(_data_t &&source) : action_(source.action_) {
      _xdr_with_mem_ptr(xdr::field_constructor, action_, *this,
                        std::move(source));
    }
    ~_data_t() { _xdr_with_mem_ptr(xdr::field_destructor, action_, *this); }
    _data_t &operator=(const _data_t &source) {
      if (_xdr_field_number(action_)
          == _xdr_field_number(source.action_))
        _xdr_with_mem_ptr(xdr::field_assigner, action_, *this, source);
      else {
        this->~_data_t();
        action_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.action_, *this, source);
      }
      action_ = source.action_;
      return *this;
    }
    _data_t &operator=(_data_t &&source) {
      if (_xdr_field_number(action_)
           == _xdr_field_number(source.action_))
        _xdr_with_mem_ptr(xdr::field_assigner, action_, *this,
                          std::move(source));
      else {
        this->~_data_t();
        action_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.action_, *this,
                          std::move(source));
      }
      action_ = source.action_;
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
    }
  };
  struct _ext_t {
    using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
  private:
    _xdr_case_type v_;
    union {
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<LedgerVersion> &_xdr_case_values() {
      static const std::vector<LedgerVersion> _xdr_disc_vec {
        LedgerVersion::EMPTY_VERSION
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
        v_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
      }
      else
        v_ = which;
    }
    explicit _ext_t(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                        std::move(source));
    }
    ~_ext_t() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
    _ext_t &operator=(const _ext_t &source) {
      if (_xdr_field_number(v_)
          == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
      }
      v_ = source.v_;
      return *this;
    }
    _ext_t &operator=(_ext_t &&source) {
      if (_xdr_field_number(v_)
           == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                          std::move(source));
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                          std::move(source));
      }
      v_ = source.v_;
      return *this;
    }

    LedgerVersion v() const { return LedgerVersion(v_); }
    _ext_t &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageSignerRoleOp::_data_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageSignerRoleOp::_data_t;
  using case_type = ::stellar::ManageSignerRoleOp::_data_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().action());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "createData";
    case 2:
      return "updateData";
    case 3:
      return "removeData";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageSignerRoleOp::_data_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of action in _data_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageSignerRoleOp::_data_t &obj) {
    xdr::archive(ar, obj.action(), "action");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.action(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of action in _data_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageSignerRoleOp::_data_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "action");
    obj.action(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.action(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageSignerRoleOp::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageSignerRoleOp::_ext_t;
  using case_type = ::stellar::ManageSignerRoleOp::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageSignerRoleOp::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageSignerRoleOp::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageSignerRoleOp::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageSignerRoleOp>
  : xdr_struct_base<field_ptr<::stellar::ManageSignerRoleOp,
                              decltype(::stellar::ManageSignerRoleOp::data),
                              &::stellar::ManageSignerRoleOp::data>,
                    field_ptr<::stellar::ManageSignerRoleOp,
                              decltype(::stellar::ManageSignerRoleOp::ext),
                              &::stellar::ManageSignerRoleOp::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageSignerRoleOp &obj) {
    archive(ar, obj.data, "data");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageSignerRoleOp &obj) {
    archive(ar, obj.data, "data");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

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
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
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

struct ManageSignerRoleResult {
  struct _success_t {
    struct _ext_t {
      using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
    private:
      _xdr_case_type v_;
      union {
      };

    public:
      static Constexpr const bool _xdr_has_default_case = false;
      static const std::vector<LedgerVersion> &_xdr_case_values() {
        static const std::vector<LedgerVersion> _xdr_disc_vec {
          LedgerVersion::EMPTY_VERSION
        };
        return _xdr_disc_vec;
      }
      static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
          v_ = which;
          _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
        }
        else
          v_ = which;
      }
      explicit _ext_t(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
        _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
      }
      _ext_t(const _ext_t &source) : v_(source.v_) {
        _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
      }
      _ext_t(_ext_t &&source) : v_(source.v_) {
        _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                          std::move(source));
      }
      ~_ext_t() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
      _ext_t &operator=(const _ext_t &source) {
        if (_xdr_field_number(v_)
            == _xdr_field_number(source.v_))
          _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
        else {
          this->~_ext_t();
          v_ = std::numeric_limits<_xdr_case_type>::max();
          _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
        }
        v_ = source.v_;
        return *this;
      }
      _ext_t &operator=(_ext_t &&source) {
        if (_xdr_field_number(v_)
             == _xdr_field_number(source.v_))
          _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                            std::move(source));
        else {
          this->~_ext_t();
          v_ = std::numeric_limits<_xdr_case_type>::max();
          _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                            std::move(source));
        }
        v_ = source.v_;
        return *this;
      }

      LedgerVersion v() const { return LedgerVersion(v_); }
      _ext_t &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
        _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
        return *this;
      }

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
  static Constexpr const bool _xdr_has_default_case = true;
  static const std::vector<ManageSignerRoleResultCode> &_xdr_case_values() {
    static const std::vector<ManageSignerRoleResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit ManageSignerRoleResult(ManageSignerRoleResultCode which = ManageSignerRoleResultCode{}) : code_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  ManageSignerRoleResult(const ManageSignerRoleResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  ManageSignerRoleResult(ManageSignerRoleResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~ManageSignerRoleResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  ManageSignerRoleResult &operator=(const ManageSignerRoleResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~ManageSignerRoleResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  ManageSignerRoleResult &operator=(ManageSignerRoleResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~ManageSignerRoleResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
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
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageSignerRoleResult::_success_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageSignerRoleResult::_success_t::_ext_t;
  using case_type = ::stellar::ManageSignerRoleResult::_success_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageSignerRoleResult::_success_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageSignerRoleResult::_success_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageSignerRoleResult::_success_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageSignerRoleResult::_success_t>
  : xdr_struct_base<field_ptr<::stellar::ManageSignerRoleResult::_success_t,
                              decltype(::stellar::ManageSignerRoleResult::_success_t::roleID),
                              &::stellar::ManageSignerRoleResult::_success_t::roleID>,
                    field_ptr<::stellar::ManageSignerRoleResult::_success_t,
                              decltype(::stellar::ManageSignerRoleResult::_success_t::ext),
                              &::stellar::ManageSignerRoleResult::_success_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageSignerRoleResult::_success_t &obj) {
    archive(ar, obj.roleID, "roleID");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageSignerRoleResult::_success_t &obj) {
    archive(ar, obj.roleID, "roleID");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageSignerRoleResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageSignerRoleResult;
  using case_type = ::stellar::ManageSignerRoleResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "success";
    case 2:
      return "ruleID";
    case 3:
      return "maxRuleIDsCount";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageSignerRoleResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in ManageSignerRoleResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageSignerRoleResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in ManageSignerRoleResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageSignerRoleResult &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.code(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
} namespace stellar {

}

#endif // !__XDR_STELLAR_OPERATION_MANAGE_SIGNER_ROLE_H_INCLUDED__
