// -*- C++ -*-
// Automatically generated from Stellar-operation-manage-asset-pair.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_OPERATION_MANAGE_ASSET_PAIR_H_INCLUDED__
#define __XDR_STELLAR_OPERATION_MANAGE_ASSET_PAIR_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-ledger-entries.h"

namespace stellar {

enum class ManageAssetPairAction : std::int32_t {
  CREATE = 0,
  UPDATE_PRICE = 1,
  UPDATE_POLICIES = 2,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageAssetPairAction>
  : xdr_integral_base<::stellar::ManageAssetPairAction, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageAssetPairAction val) {
    switch (val) {
    case ::stellar::ManageAssetPairAction::CREATE:
      return "CREATE";
    case ::stellar::ManageAssetPairAction::UPDATE_PRICE:
      return "UPDATE_PRICE";
    case ::stellar::ManageAssetPairAction::UPDATE_POLICIES:
      return "UPDATE_POLICIES";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageAssetPairAction::CREATE,
      (int32_t)::stellar::ManageAssetPairAction::UPDATE_PRICE,
      (int32_t)::stellar::ManageAssetPairAction::UPDATE_POLICIES
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ManageAssetPairOp {
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

  ManageAssetPairAction action{};
  AssetCode base{};
  AssetCode quote{};
  int64 physicalPrice{};
  int64 physicalPriceCorrection{};
  int64 maxPriceStep{};
  int32 policies{};
  _ext_t ext{};

  ManageAssetPairOp() = default;
  template<typename _action_T,
           typename _base_T,
           typename _quote_T,
           typename _physicalPrice_T,
           typename _physicalPriceCorrection_T,
           typename _maxPriceStep_T,
           typename _policies_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<ManageAssetPairAction, _action_T>::value
                          && std::is_constructible<AssetCode, _base_T>::value
                          && std::is_constructible<AssetCode, _quote_T>::value
                          && std::is_constructible<int64, _physicalPrice_T>::value
                          && std::is_constructible<int64, _physicalPriceCorrection_T>::value
                          && std::is_constructible<int64, _maxPriceStep_T>::value
                          && std::is_constructible<int32, _policies_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ManageAssetPairOp(_action_T &&_action,
                             _base_T &&_base,
                             _quote_T &&_quote,
                             _physicalPrice_T &&_physicalPrice,
                             _physicalPriceCorrection_T &&_physicalPriceCorrection,
                             _maxPriceStep_T &&_maxPriceStep,
                             _policies_T &&_policies,
                             _ext_T &&_ext)
    : action(std::forward<_action_T>(_action)),
      base(std::forward<_base_T>(_base)),
      quote(std::forward<_quote_T>(_quote)),
      physicalPrice(std::forward<_physicalPrice_T>(_physicalPrice)),
      physicalPriceCorrection(std::forward<_physicalPriceCorrection_T>(_physicalPriceCorrection)),
      maxPriceStep(std::forward<_maxPriceStep_T>(_maxPriceStep)),
      policies(std::forward<_policies_T>(_policies)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageAssetPairOp::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageAssetPairOp::_ext_t;
  using case_type = ::stellar::ManageAssetPairOp::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageAssetPairOp::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageAssetPairOp::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageAssetPairOp::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageAssetPairOp>
  : xdr_struct_base<field_ptr<::stellar::ManageAssetPairOp,
                              decltype(::stellar::ManageAssetPairOp::action),
                              &::stellar::ManageAssetPairOp::action>,
                    field_ptr<::stellar::ManageAssetPairOp,
                              decltype(::stellar::ManageAssetPairOp::base),
                              &::stellar::ManageAssetPairOp::base>,
                    field_ptr<::stellar::ManageAssetPairOp,
                              decltype(::stellar::ManageAssetPairOp::quote),
                              &::stellar::ManageAssetPairOp::quote>,
                    field_ptr<::stellar::ManageAssetPairOp,
                              decltype(::stellar::ManageAssetPairOp::physicalPrice),
                              &::stellar::ManageAssetPairOp::physicalPrice>,
                    field_ptr<::stellar::ManageAssetPairOp,
                              decltype(::stellar::ManageAssetPairOp::physicalPriceCorrection),
                              &::stellar::ManageAssetPairOp::physicalPriceCorrection>,
                    field_ptr<::stellar::ManageAssetPairOp,
                              decltype(::stellar::ManageAssetPairOp::maxPriceStep),
                              &::stellar::ManageAssetPairOp::maxPriceStep>,
                    field_ptr<::stellar::ManageAssetPairOp,
                              decltype(::stellar::ManageAssetPairOp::policies),
                              &::stellar::ManageAssetPairOp::policies>,
                    field_ptr<::stellar::ManageAssetPairOp,
                              decltype(::stellar::ManageAssetPairOp::ext),
                              &::stellar::ManageAssetPairOp::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageAssetPairOp &obj) {
    archive(ar, obj.action, "action");
    archive(ar, obj.base, "base");
    archive(ar, obj.quote, "quote");
    archive(ar, obj.physicalPrice, "physicalPrice");
    archive(ar, obj.physicalPriceCorrection, "physicalPriceCorrection");
    archive(ar, obj.maxPriceStep, "maxPriceStep");
    archive(ar, obj.policies, "policies");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageAssetPairOp &obj) {
    archive(ar, obj.action, "action");
    archive(ar, obj.base, "base");
    archive(ar, obj.quote, "quote");
    archive(ar, obj.physicalPrice, "physicalPrice");
    archive(ar, obj.physicalPriceCorrection, "physicalPriceCorrection");
    archive(ar, obj.maxPriceStep, "maxPriceStep");
    archive(ar, obj.policies, "policies");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum class ManageAssetPairResultCode : std::int32_t {
  SUCCESS = 0,
  NOT_FOUND = -1,
  ALREADY_EXISTS = -2,
  MALFORMED = -3,
  INVALID_ASSET = -4,
  INVALID_ACTION = -5,
  INVALID_POLICIES = -6,
  ASSET_NOT_FOUND = -7,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageAssetPairResultCode>
  : xdr_integral_base<::stellar::ManageAssetPairResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageAssetPairResultCode val) {
    switch (val) {
    case ::stellar::ManageAssetPairResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::ManageAssetPairResultCode::NOT_FOUND:
      return "NOT_FOUND";
    case ::stellar::ManageAssetPairResultCode::ALREADY_EXISTS:
      return "ALREADY_EXISTS";
    case ::stellar::ManageAssetPairResultCode::MALFORMED:
      return "MALFORMED";
    case ::stellar::ManageAssetPairResultCode::INVALID_ASSET:
      return "INVALID_ASSET";
    case ::stellar::ManageAssetPairResultCode::INVALID_ACTION:
      return "INVALID_ACTION";
    case ::stellar::ManageAssetPairResultCode::INVALID_POLICIES:
      return "INVALID_POLICIES";
    case ::stellar::ManageAssetPairResultCode::ASSET_NOT_FOUND:
      return "ASSET_NOT_FOUND";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageAssetPairResultCode::SUCCESS,
      (int32_t)::stellar::ManageAssetPairResultCode::NOT_FOUND,
      (int32_t)::stellar::ManageAssetPairResultCode::ALREADY_EXISTS,
      (int32_t)::stellar::ManageAssetPairResultCode::MALFORMED,
      (int32_t)::stellar::ManageAssetPairResultCode::INVALID_ASSET,
      (int32_t)::stellar::ManageAssetPairResultCode::INVALID_ACTION,
      (int32_t)::stellar::ManageAssetPairResultCode::INVALID_POLICIES,
      (int32_t)::stellar::ManageAssetPairResultCode::ASSET_NOT_FOUND
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ManageAssetPairSuccess {
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

  int64 currentPrice{};
  _ext_t ext{};

  ManageAssetPairSuccess() = default;
  template<typename _currentPrice_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<int64, _currentPrice_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ManageAssetPairSuccess(_currentPrice_T &&_currentPrice,
                                  _ext_T &&_ext)
    : currentPrice(std::forward<_currentPrice_T>(_currentPrice)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageAssetPairSuccess::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageAssetPairSuccess::_ext_t;
  using case_type = ::stellar::ManageAssetPairSuccess::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageAssetPairSuccess::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageAssetPairSuccess::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageAssetPairSuccess::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageAssetPairSuccess>
  : xdr_struct_base<field_ptr<::stellar::ManageAssetPairSuccess,
                              decltype(::stellar::ManageAssetPairSuccess::currentPrice),
                              &::stellar::ManageAssetPairSuccess::currentPrice>,
                    field_ptr<::stellar::ManageAssetPairSuccess,
                              decltype(::stellar::ManageAssetPairSuccess::ext),
                              &::stellar::ManageAssetPairSuccess::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageAssetPairSuccess &obj) {
    archive(ar, obj.currentPrice, "currentPrice");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageAssetPairSuccess &obj) {
    archive(ar, obj.currentPrice, "currentPrice");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ManageAssetPairResult {
  using _xdr_case_type = xdr::xdr_traits<ManageAssetPairResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    ManageAssetPairSuccess success_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = true;
  static const std::vector<ManageAssetPairResultCode> &_xdr_case_values() {
    static const std::vector<ManageAssetPairResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)ManageAssetPairResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)ManageAssetPairResultCode::SUCCESS:
      _f(&ManageAssetPairResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in ManageAssetPairResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~ManageAssetPairResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit ManageAssetPairResult(ManageAssetPairResultCode which = ManageAssetPairResultCode{}) : code_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  ManageAssetPairResult(const ManageAssetPairResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  ManageAssetPairResult(ManageAssetPairResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~ManageAssetPairResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  ManageAssetPairResult &operator=(const ManageAssetPairResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~ManageAssetPairResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  ManageAssetPairResult &operator=(ManageAssetPairResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~ManageAssetPairResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  ManageAssetPairResultCode code() const { return ManageAssetPairResultCode(code_); }
  ManageAssetPairResult &code(ManageAssetPairResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  ManageAssetPairSuccess &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageAssetPairResult: success accessed when not selected");
  }
  const ManageAssetPairSuccess &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageAssetPairResult: success accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageAssetPairResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageAssetPairResult;
  using case_type = ::stellar::ManageAssetPairResult::_xdr_case_type;
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

  static std::size_t serial_size(const ::stellar::ManageAssetPairResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in ManageAssetPairResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageAssetPairResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in ManageAssetPairResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageAssetPairResult &obj) {
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

#endif // !__XDR_STELLAR_OPERATION_MANAGE_ASSET_PAIR_H_INCLUDED__
