// -*- C++ -*-
// Automatically generated from Stellar-operation-manage-balance.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_OPERATION_MANAGE_BALANCE_H_INCLUDED__
#define __XDR_STELLAR_OPERATION_MANAGE_BALANCE_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-ledger-entries.h"

namespace stellar {

enum class ManageBalanceAction : std::int32_t {
  CREATE = 0,
  DELETE_BALANCE = 1,
  CREATE_UNIQUE = 2,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageBalanceAction>
  : xdr_integral_base<::stellar::ManageBalanceAction, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageBalanceAction val) {
    switch (val) {
    case ::stellar::ManageBalanceAction::CREATE:
      return "CREATE";
    case ::stellar::ManageBalanceAction::DELETE_BALANCE:
      return "DELETE_BALANCE";
    case ::stellar::ManageBalanceAction::CREATE_UNIQUE:
      return "CREATE_UNIQUE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageBalanceAction::CREATE,
      (int32_t)::stellar::ManageBalanceAction::DELETE_BALANCE,
      (int32_t)::stellar::ManageBalanceAction::CREATE_UNIQUE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ManageBalanceOp {
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

  ManageBalanceAction action{};
  AccountID destination{};
  AssetCode asset{};
  _ext_t ext{};

  ManageBalanceOp() = default;
  template<typename _action_T,
           typename _destination_T,
           typename _asset_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<ManageBalanceAction, _action_T>::value
                          && std::is_constructible<AccountID, _destination_T>::value
                          && std::is_constructible<AssetCode, _asset_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ManageBalanceOp(_action_T &&_action,
                           _destination_T &&_destination,
                           _asset_T &&_asset,
                           _ext_T &&_ext)
    : action(std::forward<_action_T>(_action)),
      destination(std::forward<_destination_T>(_destination)),
      asset(std::forward<_asset_T>(_asset)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageBalanceOp::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageBalanceOp::_ext_t;
  using case_type = ::stellar::ManageBalanceOp::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageBalanceOp::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageBalanceOp::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageBalanceOp::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageBalanceOp>
  : xdr_struct_base<field_ptr<::stellar::ManageBalanceOp,
                              decltype(::stellar::ManageBalanceOp::action),
                              &::stellar::ManageBalanceOp::action>,
                    field_ptr<::stellar::ManageBalanceOp,
                              decltype(::stellar::ManageBalanceOp::destination),
                              &::stellar::ManageBalanceOp::destination>,
                    field_ptr<::stellar::ManageBalanceOp,
                              decltype(::stellar::ManageBalanceOp::asset),
                              &::stellar::ManageBalanceOp::asset>,
                    field_ptr<::stellar::ManageBalanceOp,
                              decltype(::stellar::ManageBalanceOp::ext),
                              &::stellar::ManageBalanceOp::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageBalanceOp &obj) {
    archive(ar, obj.action, "action");
    archive(ar, obj.destination, "destination");
    archive(ar, obj.asset, "asset");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageBalanceOp &obj) {
    archive(ar, obj.action, "action");
    archive(ar, obj.destination, "destination");
    archive(ar, obj.asset, "asset");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum class ManageBalanceResultCode : std::int32_t {
  SUCCESS = 0,
  MALFORMED = -1,
  NOT_FOUND = -2,
  DESTINATION_NOT_FOUND = -3,
  ASSET_NOT_FOUND = -4,
  INVALID_ASSET = -5,
  BALANCE_ALREADY_EXISTS = -6,
  VERSION_IS_NOT_SUPPORTED_YET = -7,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageBalanceResultCode>
  : xdr_integral_base<::stellar::ManageBalanceResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageBalanceResultCode val) {
    switch (val) {
    case ::stellar::ManageBalanceResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::ManageBalanceResultCode::MALFORMED:
      return "MALFORMED";
    case ::stellar::ManageBalanceResultCode::NOT_FOUND:
      return "NOT_FOUND";
    case ::stellar::ManageBalanceResultCode::DESTINATION_NOT_FOUND:
      return "DESTINATION_NOT_FOUND";
    case ::stellar::ManageBalanceResultCode::ASSET_NOT_FOUND:
      return "ASSET_NOT_FOUND";
    case ::stellar::ManageBalanceResultCode::INVALID_ASSET:
      return "INVALID_ASSET";
    case ::stellar::ManageBalanceResultCode::BALANCE_ALREADY_EXISTS:
      return "BALANCE_ALREADY_EXISTS";
    case ::stellar::ManageBalanceResultCode::VERSION_IS_NOT_SUPPORTED_YET:
      return "VERSION_IS_NOT_SUPPORTED_YET";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageBalanceResultCode::SUCCESS,
      (int32_t)::stellar::ManageBalanceResultCode::MALFORMED,
      (int32_t)::stellar::ManageBalanceResultCode::NOT_FOUND,
      (int32_t)::stellar::ManageBalanceResultCode::DESTINATION_NOT_FOUND,
      (int32_t)::stellar::ManageBalanceResultCode::ASSET_NOT_FOUND,
      (int32_t)::stellar::ManageBalanceResultCode::INVALID_ASSET,
      (int32_t)::stellar::ManageBalanceResultCode::BALANCE_ALREADY_EXISTS,
      (int32_t)::stellar::ManageBalanceResultCode::VERSION_IS_NOT_SUPPORTED_YET
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ManageBalanceSuccess {
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

  BalanceID balanceID{};
  _ext_t ext{};

  ManageBalanceSuccess() = default;
  template<typename _balanceID_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<BalanceID, _balanceID_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ManageBalanceSuccess(_balanceID_T &&_balanceID,
                                _ext_T &&_ext)
    : balanceID(std::forward<_balanceID_T>(_balanceID)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageBalanceSuccess::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageBalanceSuccess::_ext_t;
  using case_type = ::stellar::ManageBalanceSuccess::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageBalanceSuccess::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageBalanceSuccess::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageBalanceSuccess::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageBalanceSuccess>
  : xdr_struct_base<field_ptr<::stellar::ManageBalanceSuccess,
                              decltype(::stellar::ManageBalanceSuccess::balanceID),
                              &::stellar::ManageBalanceSuccess::balanceID>,
                    field_ptr<::stellar::ManageBalanceSuccess,
                              decltype(::stellar::ManageBalanceSuccess::ext),
                              &::stellar::ManageBalanceSuccess::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageBalanceSuccess &obj) {
    archive(ar, obj.balanceID, "balanceID");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageBalanceSuccess &obj) {
    archive(ar, obj.balanceID, "balanceID");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ManageBalanceResult {
  using _xdr_case_type = xdr::xdr_traits<ManageBalanceResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    ManageBalanceSuccess success_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = true;
  static const std::vector<ManageBalanceResultCode> &_xdr_case_values() {
    static const std::vector<ManageBalanceResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)ManageBalanceResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)ManageBalanceResultCode::SUCCESS:
      _f(&ManageBalanceResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in ManageBalanceResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~ManageBalanceResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit ManageBalanceResult(ManageBalanceResultCode which = ManageBalanceResultCode{}) : code_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  ManageBalanceResult(const ManageBalanceResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  ManageBalanceResult(ManageBalanceResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~ManageBalanceResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  ManageBalanceResult &operator=(const ManageBalanceResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~ManageBalanceResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  ManageBalanceResult &operator=(ManageBalanceResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~ManageBalanceResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  ManageBalanceResultCode code() const { return ManageBalanceResultCode(code_); }
  ManageBalanceResult &code(ManageBalanceResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  ManageBalanceSuccess &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageBalanceResult: success accessed when not selected");
  }
  const ManageBalanceSuccess &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageBalanceResult: success accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageBalanceResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageBalanceResult;
  using case_type = ::stellar::ManageBalanceResult::_xdr_case_type;
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

  static std::size_t serial_size(const ::stellar::ManageBalanceResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in ManageBalanceResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageBalanceResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in ManageBalanceResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageBalanceResult &obj) {
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

#endif // !__XDR_STELLAR_OPERATION_MANAGE_BALANCE_H_INCLUDED__
