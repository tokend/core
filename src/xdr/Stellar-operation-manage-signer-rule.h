// -*- C++ -*-
// Automatically generated from Stellar-operation-manage-signer-rule.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_OPERATION_MANAGE_SIGNER_RULE_H_INCLUDED__
#define __XDR_STELLAR_OPERATION_MANAGE_SIGNER_RULE_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-ledger-entries.h"
#include "xdr/Stellar-resource-signer-rule.h"

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
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
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

struct CreateSignerRuleData {
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateSignerRuleData::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CreateSignerRuleData::_ext_t;
  using case_type = ::stellar::CreateSignerRuleData::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::CreateSignerRuleData::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateSignerRuleData::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateSignerRuleData::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::CreateSignerRuleData>
  : xdr_struct_base<field_ptr<::stellar::CreateSignerRuleData,
                              decltype(::stellar::CreateSignerRuleData::resource),
                              &::stellar::CreateSignerRuleData::resource>,
                    field_ptr<::stellar::CreateSignerRuleData,
                              decltype(::stellar::CreateSignerRuleData::action),
                              &::stellar::CreateSignerRuleData::action>,
                    field_ptr<::stellar::CreateSignerRuleData,
                              decltype(::stellar::CreateSignerRuleData::forbids),
                              &::stellar::CreateSignerRuleData::forbids>,
                    field_ptr<::stellar::CreateSignerRuleData,
                              decltype(::stellar::CreateSignerRuleData::isDefault),
                              &::stellar::CreateSignerRuleData::isDefault>,
                    field_ptr<::stellar::CreateSignerRuleData,
                              decltype(::stellar::CreateSignerRuleData::isReadOnly),
                              &::stellar::CreateSignerRuleData::isReadOnly>,
                    field_ptr<::stellar::CreateSignerRuleData,
                              decltype(::stellar::CreateSignerRuleData::details),
                              &::stellar::CreateSignerRuleData::details>,
                    field_ptr<::stellar::CreateSignerRuleData,
                              decltype(::stellar::CreateSignerRuleData::ext),
                              &::stellar::CreateSignerRuleData::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateSignerRuleData &obj) {
    archive(ar, obj.resource, "resource");
    archive(ar, obj.action, "action");
    archive(ar, obj.forbids, "forbids");
    archive(ar, obj.isDefault, "isDefault");
    archive(ar, obj.isReadOnly, "isReadOnly");
    archive(ar, obj.details, "details");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateSignerRuleData &obj) {
    archive(ar, obj.resource, "resource");
    archive(ar, obj.action, "action");
    archive(ar, obj.forbids, "forbids");
    archive(ar, obj.isDefault, "isDefault");
    archive(ar, obj.isReadOnly, "isReadOnly");
    archive(ar, obj.details, "details");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct UpdateSignerRuleData {
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::UpdateSignerRuleData::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::UpdateSignerRuleData::_ext_t;
  using case_type = ::stellar::UpdateSignerRuleData::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::UpdateSignerRuleData::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::UpdateSignerRuleData::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::UpdateSignerRuleData::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::UpdateSignerRuleData>
  : xdr_struct_base<field_ptr<::stellar::UpdateSignerRuleData,
                              decltype(::stellar::UpdateSignerRuleData::ruleID),
                              &::stellar::UpdateSignerRuleData::ruleID>,
                    field_ptr<::stellar::UpdateSignerRuleData,
                              decltype(::stellar::UpdateSignerRuleData::resource),
                              &::stellar::UpdateSignerRuleData::resource>,
                    field_ptr<::stellar::UpdateSignerRuleData,
                              decltype(::stellar::UpdateSignerRuleData::action),
                              &::stellar::UpdateSignerRuleData::action>,
                    field_ptr<::stellar::UpdateSignerRuleData,
                              decltype(::stellar::UpdateSignerRuleData::forbids),
                              &::stellar::UpdateSignerRuleData::forbids>,
                    field_ptr<::stellar::UpdateSignerRuleData,
                              decltype(::stellar::UpdateSignerRuleData::isDefault),
                              &::stellar::UpdateSignerRuleData::isDefault>,
                    field_ptr<::stellar::UpdateSignerRuleData,
                              decltype(::stellar::UpdateSignerRuleData::details),
                              &::stellar::UpdateSignerRuleData::details>,
                    field_ptr<::stellar::UpdateSignerRuleData,
                              decltype(::stellar::UpdateSignerRuleData::ext),
                              &::stellar::UpdateSignerRuleData::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::UpdateSignerRuleData &obj) {
    archive(ar, obj.ruleID, "ruleID");
    archive(ar, obj.resource, "resource");
    archive(ar, obj.action, "action");
    archive(ar, obj.forbids, "forbids");
    archive(ar, obj.isDefault, "isDefault");
    archive(ar, obj.details, "details");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::UpdateSignerRuleData &obj) {
    archive(ar, obj.ruleID, "ruleID");
    archive(ar, obj.resource, "resource");
    archive(ar, obj.action, "action");
    archive(ar, obj.forbids, "forbids");
    archive(ar, obj.isDefault, "isDefault");
    archive(ar, obj.details, "details");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct RemoveSignerRuleData {
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::RemoveSignerRuleData::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::RemoveSignerRuleData::_ext_t;
  using case_type = ::stellar::RemoveSignerRuleData::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::RemoveSignerRuleData::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::RemoveSignerRuleData::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::RemoveSignerRuleData::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::RemoveSignerRuleData>
  : xdr_struct_base<field_ptr<::stellar::RemoveSignerRuleData,
                              decltype(::stellar::RemoveSignerRuleData::ruleID),
                              &::stellar::RemoveSignerRuleData::ruleID>,
                    field_ptr<::stellar::RemoveSignerRuleData,
                              decltype(::stellar::RemoveSignerRuleData::ext),
                              &::stellar::RemoveSignerRuleData::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::RemoveSignerRuleData &obj) {
    archive(ar, obj.ruleID, "ruleID");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::RemoveSignerRuleData &obj) {
    archive(ar, obj.ruleID, "ruleID");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ManageSignerRuleOp {
  struct _data_t {
    using _xdr_case_type = xdr::xdr_traits<ManageSignerRuleAction>::case_type;
  private:
    _xdr_case_type action_;
    union {
      CreateSignerRuleData createData_;
      UpdateSignerRuleData updateData_;
      RemoveSignerRuleData removeData_;
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<ManageSignerRuleAction> &_xdr_case_values() {
      static const std::vector<ManageSignerRuleAction> _xdr_disc_vec {
        ManageSignerRuleAction::CREATE,
        ManageSignerRuleAction::UPDATE,
        ManageSignerRuleAction::REMOVE
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
        action_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, action_, *this);
      }
      else
        action_ = which;
    }
    explicit _data_t(ManageSignerRuleAction which = ManageSignerRuleAction{}) : action_((int32_t)which) {
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageSignerRuleOp::_data_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageSignerRuleOp::_data_t;
  using case_type = ::stellar::ManageSignerRuleOp::_data_t::_xdr_case_type;
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

  static std::size_t serial_size(const ::stellar::ManageSignerRuleOp::_data_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of action in _data_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageSignerRuleOp::_data_t &obj) {
    xdr::archive(ar, obj.action(), "action");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.action(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of action in _data_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageSignerRuleOp::_data_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "action");
    obj.action(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.action(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageSignerRuleOp::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageSignerRuleOp::_ext_t;
  using case_type = ::stellar::ManageSignerRuleOp::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageSignerRuleOp::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageSignerRuleOp::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageSignerRuleOp::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageSignerRuleOp>
  : xdr_struct_base<field_ptr<::stellar::ManageSignerRuleOp,
                              decltype(::stellar::ManageSignerRuleOp::data),
                              &::stellar::ManageSignerRuleOp::data>,
                    field_ptr<::stellar::ManageSignerRuleOp,
                              decltype(::stellar::ManageSignerRuleOp::ext),
                              &::stellar::ManageSignerRuleOp::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageSignerRuleOp &obj) {
    archive(ar, obj.data, "data");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageSignerRuleOp &obj) {
    archive(ar, obj.data, "data");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

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
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
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

struct ManageSignerRuleResult {
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
  };

  using _xdr_case_type = xdr::xdr_traits<ManageSignerRuleResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    _success_t success_;
    xdr::xvector<uint64> roleIDs_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = true;
  static const std::vector<ManageSignerRuleResultCode> &_xdr_case_values() {
    static const std::vector<ManageSignerRuleResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit ManageSignerRuleResult(ManageSignerRuleResultCode which = ManageSignerRuleResultCode{}) : code_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  ManageSignerRuleResult(const ManageSignerRuleResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  ManageSignerRuleResult(ManageSignerRuleResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~ManageSignerRuleResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  ManageSignerRuleResult &operator=(const ManageSignerRuleResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~ManageSignerRuleResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  ManageSignerRuleResult &operator=(ManageSignerRuleResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~ManageSignerRuleResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
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
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageSignerRuleResult::_success_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageSignerRuleResult::_success_t::_ext_t;
  using case_type = ::stellar::ManageSignerRuleResult::_success_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageSignerRuleResult::_success_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageSignerRuleResult::_success_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageSignerRuleResult::_success_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageSignerRuleResult::_success_t>
  : xdr_struct_base<field_ptr<::stellar::ManageSignerRuleResult::_success_t,
                              decltype(::stellar::ManageSignerRuleResult::_success_t::ruleID),
                              &::stellar::ManageSignerRuleResult::_success_t::ruleID>,
                    field_ptr<::stellar::ManageSignerRuleResult::_success_t,
                              decltype(::stellar::ManageSignerRuleResult::_success_t::ext),
                              &::stellar::ManageSignerRuleResult::_success_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageSignerRuleResult::_success_t &obj) {
    archive(ar, obj.ruleID, "ruleID");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageSignerRuleResult::_success_t &obj) {
    archive(ar, obj.ruleID, "ruleID");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageSignerRuleResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageSignerRuleResult;
  using case_type = ::stellar::ManageSignerRuleResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "success";
    case 2:
      return "roleIDs";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageSignerRuleResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in ManageSignerRuleResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageSignerRuleResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in ManageSignerRuleResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageSignerRuleResult &obj) {
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

#endif // !__XDR_STELLAR_OPERATION_MANAGE_SIGNER_RULE_H_INCLUDED__
