// -*- C++ -*-
// Automatically generated from Stellar-operation-manage-external-system-id-pool-entry.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_OPERATION_MANAGE_EXTERNAL_SYSTEM_ID_POOL_ENTRY_H_INCLUDED__
#define __XDR_STELLAR_OPERATION_MANAGE_EXTERNAL_SYSTEM_ID_POOL_ENTRY_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-ledger-entries.h"

namespace stellar {

enum class ManageExternalSystemAccountIdPoolEntryAction : std::int32_t {
  CREATE = 0,
  REMOVE = 1,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageExternalSystemAccountIdPoolEntryAction>
  : xdr_integral_base<::stellar::ManageExternalSystemAccountIdPoolEntryAction, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
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

struct CreateExternalSystemAccountIdPoolEntryActionInput {
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateExternalSystemAccountIdPoolEntryActionInput::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CreateExternalSystemAccountIdPoolEntryActionInput::_ext_t;
  using case_type = ::stellar::CreateExternalSystemAccountIdPoolEntryActionInput::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::CreateExternalSystemAccountIdPoolEntryActionInput::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateExternalSystemAccountIdPoolEntryActionInput::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateExternalSystemAccountIdPoolEntryActionInput::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::CreateExternalSystemAccountIdPoolEntryActionInput>
  : xdr_struct_base<field_ptr<::stellar::CreateExternalSystemAccountIdPoolEntryActionInput,
                              decltype(::stellar::CreateExternalSystemAccountIdPoolEntryActionInput::externalSystemType),
                              &::stellar::CreateExternalSystemAccountIdPoolEntryActionInput::externalSystemType>,
                    field_ptr<::stellar::CreateExternalSystemAccountIdPoolEntryActionInput,
                              decltype(::stellar::CreateExternalSystemAccountIdPoolEntryActionInput::data),
                              &::stellar::CreateExternalSystemAccountIdPoolEntryActionInput::data>,
                    field_ptr<::stellar::CreateExternalSystemAccountIdPoolEntryActionInput,
                              decltype(::stellar::CreateExternalSystemAccountIdPoolEntryActionInput::parent),
                              &::stellar::CreateExternalSystemAccountIdPoolEntryActionInput::parent>,
                    field_ptr<::stellar::CreateExternalSystemAccountIdPoolEntryActionInput,
                              decltype(::stellar::CreateExternalSystemAccountIdPoolEntryActionInput::ext),
                              &::stellar::CreateExternalSystemAccountIdPoolEntryActionInput::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateExternalSystemAccountIdPoolEntryActionInput &obj) {
    archive(ar, obj.externalSystemType, "externalSystemType");
    archive(ar, obj.data, "data");
    archive(ar, obj.parent, "parent");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateExternalSystemAccountIdPoolEntryActionInput &obj) {
    archive(ar, obj.externalSystemType, "externalSystemType");
    archive(ar, obj.data, "data");
    archive(ar, obj.parent, "parent");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct DeleteExternalSystemAccountIdPoolEntryActionInput {
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::DeleteExternalSystemAccountIdPoolEntryActionInput::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::DeleteExternalSystemAccountIdPoolEntryActionInput::_ext_t;
  using case_type = ::stellar::DeleteExternalSystemAccountIdPoolEntryActionInput::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::DeleteExternalSystemAccountIdPoolEntryActionInput::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::DeleteExternalSystemAccountIdPoolEntryActionInput::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::DeleteExternalSystemAccountIdPoolEntryActionInput::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::DeleteExternalSystemAccountIdPoolEntryActionInput>
  : xdr_struct_base<field_ptr<::stellar::DeleteExternalSystemAccountIdPoolEntryActionInput,
                              decltype(::stellar::DeleteExternalSystemAccountIdPoolEntryActionInput::poolEntryID),
                              &::stellar::DeleteExternalSystemAccountIdPoolEntryActionInput::poolEntryID>,
                    field_ptr<::stellar::DeleteExternalSystemAccountIdPoolEntryActionInput,
                              decltype(::stellar::DeleteExternalSystemAccountIdPoolEntryActionInput::ext),
                              &::stellar::DeleteExternalSystemAccountIdPoolEntryActionInput::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::DeleteExternalSystemAccountIdPoolEntryActionInput &obj) {
    archive(ar, obj.poolEntryID, "poolEntryID");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::DeleteExternalSystemAccountIdPoolEntryActionInput &obj) {
    archive(ar, obj.poolEntryID, "poolEntryID");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ManageExternalSystemAccountIdPoolEntryOp {
  struct _actionInput_t {
    using _xdr_case_type = xdr::xdr_traits<ManageExternalSystemAccountIdPoolEntryAction>::case_type;
  private:
    _xdr_case_type action_;
    union {
      CreateExternalSystemAccountIdPoolEntryActionInput createExternalSystemAccountIdPoolEntryActionInput_;
      DeleteExternalSystemAccountIdPoolEntryActionInput deleteExternalSystemAccountIdPoolEntryActionInput_;
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<ManageExternalSystemAccountIdPoolEntryAction> &_xdr_case_values() {
      static const std::vector<ManageExternalSystemAccountIdPoolEntryAction> _xdr_disc_vec {
        ManageExternalSystemAccountIdPoolEntryAction::CREATE,
        ManageExternalSystemAccountIdPoolEntryAction::REMOVE
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
        action_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, action_, *this);
      }
      else
        action_ = which;
    }
    explicit _actionInput_t(ManageExternalSystemAccountIdPoolEntryAction which = ManageExternalSystemAccountIdPoolEntryAction{}) : action_((int32_t)which) {
      _xdr_with_mem_ptr(xdr::field_constructor, action_, *this);
    }
    _actionInput_t(const _actionInput_t &source) : action_(source.action_) {
      _xdr_with_mem_ptr(xdr::field_constructor, action_, *this, source);
    }
    _actionInput_t(_actionInput_t &&source) : action_(source.action_) {
      _xdr_with_mem_ptr(xdr::field_constructor, action_, *this,
                        std::move(source));
    }
    ~_actionInput_t() { _xdr_with_mem_ptr(xdr::field_destructor, action_, *this); }
    _actionInput_t &operator=(const _actionInput_t &source) {
      if (_xdr_field_number(action_)
          == _xdr_field_number(source.action_))
        _xdr_with_mem_ptr(xdr::field_assigner, action_, *this, source);
      else {
        this->~_actionInput_t();
        action_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.action_, *this, source);
      }
      action_ = source.action_;
      return *this;
    }
    _actionInput_t &operator=(_actionInput_t &&source) {
      if (_xdr_field_number(action_)
           == _xdr_field_number(source.action_))
        _xdr_with_mem_ptr(xdr::field_assigner, action_, *this,
                          std::move(source));
      else {
        this->~_actionInput_t();
        action_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.action_, *this,
                          std::move(source));
      }
      action_ = source.action_;
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageExternalSystemAccountIdPoolEntryOp::_actionInput_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageExternalSystemAccountIdPoolEntryOp::_actionInput_t;
  using case_type = ::stellar::ManageExternalSystemAccountIdPoolEntryOp::_actionInput_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().action());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "createExternalSystemAccountIdPoolEntryActionInput";
    case 2:
      return "deleteExternalSystemAccountIdPoolEntryActionInput";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageExternalSystemAccountIdPoolEntryOp::_actionInput_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of action in _actionInput_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageExternalSystemAccountIdPoolEntryOp::_actionInput_t &obj) {
    xdr::archive(ar, obj.action(), "action");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.action(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of action in _actionInput_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageExternalSystemAccountIdPoolEntryOp::_actionInput_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "action");
    obj.action(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.action(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageExternalSystemAccountIdPoolEntryOp::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageExternalSystemAccountIdPoolEntryOp::_ext_t;
  using case_type = ::stellar::ManageExternalSystemAccountIdPoolEntryOp::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageExternalSystemAccountIdPoolEntryOp::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageExternalSystemAccountIdPoolEntryOp::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageExternalSystemAccountIdPoolEntryOp::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageExternalSystemAccountIdPoolEntryOp>
  : xdr_struct_base<field_ptr<::stellar::ManageExternalSystemAccountIdPoolEntryOp,
                              decltype(::stellar::ManageExternalSystemAccountIdPoolEntryOp::actionInput),
                              &::stellar::ManageExternalSystemAccountIdPoolEntryOp::actionInput>,
                    field_ptr<::stellar::ManageExternalSystemAccountIdPoolEntryOp,
                              decltype(::stellar::ManageExternalSystemAccountIdPoolEntryOp::ext),
                              &::stellar::ManageExternalSystemAccountIdPoolEntryOp::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageExternalSystemAccountIdPoolEntryOp &obj) {
    archive(ar, obj.actionInput, "actionInput");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageExternalSystemAccountIdPoolEntryOp &obj) {
    archive(ar, obj.actionInput, "actionInput");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

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
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
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

struct ManageExternalSystemAccountIdPoolEntrySuccess {
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
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageExternalSystemAccountIdPoolEntrySuccess::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageExternalSystemAccountIdPoolEntrySuccess::_ext_t;
  using case_type = ::stellar::ManageExternalSystemAccountIdPoolEntrySuccess::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageExternalSystemAccountIdPoolEntrySuccess::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageExternalSystemAccountIdPoolEntrySuccess::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageExternalSystemAccountIdPoolEntrySuccess::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageExternalSystemAccountIdPoolEntrySuccess>
  : xdr_struct_base<field_ptr<::stellar::ManageExternalSystemAccountIdPoolEntrySuccess,
                              decltype(::stellar::ManageExternalSystemAccountIdPoolEntrySuccess::poolEntryID),
                              &::stellar::ManageExternalSystemAccountIdPoolEntrySuccess::poolEntryID>,
                    field_ptr<::stellar::ManageExternalSystemAccountIdPoolEntrySuccess,
                              decltype(::stellar::ManageExternalSystemAccountIdPoolEntrySuccess::ext),
                              &::stellar::ManageExternalSystemAccountIdPoolEntrySuccess::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageExternalSystemAccountIdPoolEntrySuccess &obj) {
    archive(ar, obj.poolEntryID, "poolEntryID");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageExternalSystemAccountIdPoolEntrySuccess &obj) {
    archive(ar, obj.poolEntryID, "poolEntryID");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ManageExternalSystemAccountIdPoolEntryResult {
  using _xdr_case_type = xdr::xdr_traits<ManageExternalSystemAccountIdPoolEntryResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    ManageExternalSystemAccountIdPoolEntrySuccess success_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = true;
  static const std::vector<ManageExternalSystemAccountIdPoolEntryResultCode> &_xdr_case_values() {
    static const std::vector<ManageExternalSystemAccountIdPoolEntryResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
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
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit ManageExternalSystemAccountIdPoolEntryResult(ManageExternalSystemAccountIdPoolEntryResultCode which = ManageExternalSystemAccountIdPoolEntryResultCode{}) : code_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  ManageExternalSystemAccountIdPoolEntryResult(const ManageExternalSystemAccountIdPoolEntryResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  ManageExternalSystemAccountIdPoolEntryResult(ManageExternalSystemAccountIdPoolEntryResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~ManageExternalSystemAccountIdPoolEntryResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  ManageExternalSystemAccountIdPoolEntryResult &operator=(const ManageExternalSystemAccountIdPoolEntryResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~ManageExternalSystemAccountIdPoolEntryResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  ManageExternalSystemAccountIdPoolEntryResult &operator=(ManageExternalSystemAccountIdPoolEntryResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~ManageExternalSystemAccountIdPoolEntryResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
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
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageExternalSystemAccountIdPoolEntryResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageExternalSystemAccountIdPoolEntryResult;
  using case_type = ::stellar::ManageExternalSystemAccountIdPoolEntryResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "success";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageExternalSystemAccountIdPoolEntryResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in ManageExternalSystemAccountIdPoolEntryResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageExternalSystemAccountIdPoolEntryResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in ManageExternalSystemAccountIdPoolEntryResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageExternalSystemAccountIdPoolEntryResult &obj) {
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

#endif // !__XDR_STELLAR_OPERATION_MANAGE_EXTERNAL_SYSTEM_ID_POOL_ENTRY_H_INCLUDED__
