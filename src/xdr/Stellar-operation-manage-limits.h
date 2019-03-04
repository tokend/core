// -*- C++ -*-
// Automatically generated from Stellar-operation-manage-limits.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_OPERATION_MANAGE_LIMITS_H_INCLUDED__
#define __XDR_STELLAR_OPERATION_MANAGE_LIMITS_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-ledger-entries-limits-v2.h"

namespace stellar {

enum class ManageLimitsAction : std::int32_t {
  CREATE = 0,
  REMOVE = 1,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageLimitsAction>
  : xdr_integral_base<::stellar::ManageLimitsAction, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageLimitsAction val) {
    switch (val) {
    case ::stellar::ManageLimitsAction::CREATE:
      return "CREATE";
    case ::stellar::ManageLimitsAction::REMOVE:
      return "REMOVE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageLimitsAction::CREATE,
      (int32_t)::stellar::ManageLimitsAction::REMOVE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct LimitsCreateDetails {
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

  xdr::pointer<uint64> accountRole{};
  xdr::pointer<AccountID> accountID{};
  StatsOpType statsOpType{};
  AssetCode assetCode{};
  bool isConvertNeeded{};
  uint64 dailyOut{};
  uint64 weeklyOut{};
  uint64 monthlyOut{};
  uint64 annualOut{};
  _ext_t ext{};

  LimitsCreateDetails() = default;
  template<typename _accountRole_T,
           typename _accountID_T,
           typename _statsOpType_T,
           typename _assetCode_T,
           typename _isConvertNeeded_T,
           typename _dailyOut_T,
           typename _weeklyOut_T,
           typename _monthlyOut_T,
           typename _annualOut_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::pointer<uint64>, _accountRole_T>::value
                          && std::is_constructible<xdr::pointer<AccountID>, _accountID_T>::value
                          && std::is_constructible<StatsOpType, _statsOpType_T>::value
                          && std::is_constructible<AssetCode, _assetCode_T>::value
                          && std::is_constructible<bool, _isConvertNeeded_T>::value
                          && std::is_constructible<uint64, _dailyOut_T>::value
                          && std::is_constructible<uint64, _weeklyOut_T>::value
                          && std::is_constructible<uint64, _monthlyOut_T>::value
                          && std::is_constructible<uint64, _annualOut_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit LimitsCreateDetails(_accountRole_T &&_accountRole,
                               _accountID_T &&_accountID,
                               _statsOpType_T &&_statsOpType,
                               _assetCode_T &&_assetCode,
                               _isConvertNeeded_T &&_isConvertNeeded,
                               _dailyOut_T &&_dailyOut,
                               _weeklyOut_T &&_weeklyOut,
                               _monthlyOut_T &&_monthlyOut,
                               _annualOut_T &&_annualOut,
                               _ext_T &&_ext)
    : accountRole(std::forward<_accountRole_T>(_accountRole)),
      accountID(std::forward<_accountID_T>(_accountID)),
      statsOpType(std::forward<_statsOpType_T>(_statsOpType)),
      assetCode(std::forward<_assetCode_T>(_assetCode)),
      isConvertNeeded(std::forward<_isConvertNeeded_T>(_isConvertNeeded)),
      dailyOut(std::forward<_dailyOut_T>(_dailyOut)),
      weeklyOut(std::forward<_weeklyOut_T>(_weeklyOut)),
      monthlyOut(std::forward<_monthlyOut_T>(_monthlyOut)),
      annualOut(std::forward<_annualOut_T>(_annualOut)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LimitsCreateDetails::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LimitsCreateDetails::_ext_t;
  using case_type = ::stellar::LimitsCreateDetails::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LimitsCreateDetails::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LimitsCreateDetails::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LimitsCreateDetails::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LimitsCreateDetails>
  : xdr_struct_base<field_ptr<::stellar::LimitsCreateDetails,
                              decltype(::stellar::LimitsCreateDetails::accountRole),
                              &::stellar::LimitsCreateDetails::accountRole>,
                    field_ptr<::stellar::LimitsCreateDetails,
                              decltype(::stellar::LimitsCreateDetails::accountID),
                              &::stellar::LimitsCreateDetails::accountID>,
                    field_ptr<::stellar::LimitsCreateDetails,
                              decltype(::stellar::LimitsCreateDetails::statsOpType),
                              &::stellar::LimitsCreateDetails::statsOpType>,
                    field_ptr<::stellar::LimitsCreateDetails,
                              decltype(::stellar::LimitsCreateDetails::assetCode),
                              &::stellar::LimitsCreateDetails::assetCode>,
                    field_ptr<::stellar::LimitsCreateDetails,
                              decltype(::stellar::LimitsCreateDetails::isConvertNeeded),
                              &::stellar::LimitsCreateDetails::isConvertNeeded>,
                    field_ptr<::stellar::LimitsCreateDetails,
                              decltype(::stellar::LimitsCreateDetails::dailyOut),
                              &::stellar::LimitsCreateDetails::dailyOut>,
                    field_ptr<::stellar::LimitsCreateDetails,
                              decltype(::stellar::LimitsCreateDetails::weeklyOut),
                              &::stellar::LimitsCreateDetails::weeklyOut>,
                    field_ptr<::stellar::LimitsCreateDetails,
                              decltype(::stellar::LimitsCreateDetails::monthlyOut),
                              &::stellar::LimitsCreateDetails::monthlyOut>,
                    field_ptr<::stellar::LimitsCreateDetails,
                              decltype(::stellar::LimitsCreateDetails::annualOut),
                              &::stellar::LimitsCreateDetails::annualOut>,
                    field_ptr<::stellar::LimitsCreateDetails,
                              decltype(::stellar::LimitsCreateDetails::ext),
                              &::stellar::LimitsCreateDetails::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LimitsCreateDetails &obj) {
    archive(ar, obj.accountRole, "accountRole");
    archive(ar, obj.accountID, "accountID");
    archive(ar, obj.statsOpType, "statsOpType");
    archive(ar, obj.assetCode, "assetCode");
    archive(ar, obj.isConvertNeeded, "isConvertNeeded");
    archive(ar, obj.dailyOut, "dailyOut");
    archive(ar, obj.weeklyOut, "weeklyOut");
    archive(ar, obj.monthlyOut, "monthlyOut");
    archive(ar, obj.annualOut, "annualOut");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LimitsCreateDetails &obj) {
    archive(ar, obj.accountRole, "accountRole");
    archive(ar, obj.accountID, "accountID");
    archive(ar, obj.statsOpType, "statsOpType");
    archive(ar, obj.assetCode, "assetCode");
    archive(ar, obj.isConvertNeeded, "isConvertNeeded");
    archive(ar, obj.dailyOut, "dailyOut");
    archive(ar, obj.weeklyOut, "weeklyOut");
    archive(ar, obj.monthlyOut, "monthlyOut");
    archive(ar, obj.annualOut, "annualOut");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ManageLimitsOp {
  struct _details_t {
    using _xdr_case_type = xdr::xdr_traits<ManageLimitsAction>::case_type;
  private:
    _xdr_case_type action_;
    union {
      LimitsCreateDetails limitsCreateDetails_;
      uint64 id_;
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<ManageLimitsAction> &_xdr_case_values() {
      static const std::vector<ManageLimitsAction> _xdr_disc_vec {
        ManageLimitsAction::CREATE,
        ManageLimitsAction::REMOVE
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)ManageLimitsAction::CREATE ? 1
        : which == (int32_t)ManageLimitsAction::REMOVE ? 2
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)ManageLimitsAction::CREATE:
        _f(&_details_t::limitsCreateDetails_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ManageLimitsAction::REMOVE:
        _f(&_details_t::id_, std::forward<_A>(_a)...);
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return action_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of action in _details_t");
      if (fnum != _xdr_field_number(action_)) {
        this->~_details_t();
        action_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, action_, *this);
      }
      else
        action_ = which;
    }
    explicit _details_t(ManageLimitsAction which = ManageLimitsAction{}) : action_((int32_t)which) {
      _xdr_with_mem_ptr(xdr::field_constructor, action_, *this);
    }
    _details_t(const _details_t &source) : action_(source.action_) {
      _xdr_with_mem_ptr(xdr::field_constructor, action_, *this, source);
    }
    _details_t(_details_t &&source) : action_(source.action_) {
      _xdr_with_mem_ptr(xdr::field_constructor, action_, *this,
                        std::move(source));
    }
    ~_details_t() { _xdr_with_mem_ptr(xdr::field_destructor, action_, *this); }
    _details_t &operator=(const _details_t &source) {
      if (_xdr_field_number(action_)
          == _xdr_field_number(source.action_))
        _xdr_with_mem_ptr(xdr::field_assigner, action_, *this, source);
      else {
        this->~_details_t();
        action_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.action_, *this, source);
      }
      action_ = source.action_;
      return *this;
    }
    _details_t &operator=(_details_t &&source) {
      if (_xdr_field_number(action_)
           == _xdr_field_number(source.action_))
        _xdr_with_mem_ptr(xdr::field_assigner, action_, *this,
                          std::move(source));
      else {
        this->~_details_t();
        action_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.action_, *this,
                          std::move(source));
      }
      action_ = source.action_;
      return *this;
    }

    ManageLimitsAction action() const { return ManageLimitsAction(action_); }
    _details_t &action(ManageLimitsAction _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    LimitsCreateDetails &limitsCreateDetails() {
      if (_xdr_field_number(action_) == 1)
        return limitsCreateDetails_;
      throw xdr::xdr_wrong_union("_details_t: limitsCreateDetails accessed when not selected");
    }
    const LimitsCreateDetails &limitsCreateDetails() const {
      if (_xdr_field_number(action_) == 1)
        return limitsCreateDetails_;
      throw xdr::xdr_wrong_union("_details_t: limitsCreateDetails accessed when not selected");
    }
    uint64 &id() {
      if (_xdr_field_number(action_) == 2)
        return id_;
      throw xdr::xdr_wrong_union("_details_t: id accessed when not selected");
    }
    const uint64 &id() const {
      if (_xdr_field_number(action_) == 2)
        return id_;
      throw xdr::xdr_wrong_union("_details_t: id accessed when not selected");
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

  _details_t details{};
  _ext_t ext{};

  ManageLimitsOp() = default;
  template<typename _details_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<_details_t, _details_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ManageLimitsOp(_details_T &&_details,
                          _ext_T &&_ext)
    : details(std::forward<_details_T>(_details)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageLimitsOp::_details_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageLimitsOp::_details_t;
  using case_type = ::stellar::ManageLimitsOp::_details_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().action());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "limitsCreateDetails";
    case 2:
      return "id";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageLimitsOp::_details_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of action in _details_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageLimitsOp::_details_t &obj) {
    xdr::archive(ar, obj.action(), "action");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.action(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of action in _details_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageLimitsOp::_details_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "action");
    obj.action(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.action(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageLimitsOp::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageLimitsOp::_ext_t;
  using case_type = ::stellar::ManageLimitsOp::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageLimitsOp::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageLimitsOp::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageLimitsOp::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageLimitsOp>
  : xdr_struct_base<field_ptr<::stellar::ManageLimitsOp,
                              decltype(::stellar::ManageLimitsOp::details),
                              &::stellar::ManageLimitsOp::details>,
                    field_ptr<::stellar::ManageLimitsOp,
                              decltype(::stellar::ManageLimitsOp::ext),
                              &::stellar::ManageLimitsOp::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageLimitsOp &obj) {
    archive(ar, obj.details, "details");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageLimitsOp &obj) {
    archive(ar, obj.details, "details");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum class ManageLimitsResultCode : std::int32_t {
  SUCCESS = 0,
  MALFORMED = -1,
  NOT_FOUND = -2,
  ALREADY_EXISTS = -3,
  CANNOT_CREATE_FOR_ACC_ID_AND_ACC_TYPE = -4,
  INVALID_LIMITS = -5,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageLimitsResultCode>
  : xdr_integral_base<::stellar::ManageLimitsResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageLimitsResultCode val) {
    switch (val) {
    case ::stellar::ManageLimitsResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::ManageLimitsResultCode::MALFORMED:
      return "MALFORMED";
    case ::stellar::ManageLimitsResultCode::NOT_FOUND:
      return "NOT_FOUND";
    case ::stellar::ManageLimitsResultCode::ALREADY_EXISTS:
      return "ALREADY_EXISTS";
    case ::stellar::ManageLimitsResultCode::CANNOT_CREATE_FOR_ACC_ID_AND_ACC_TYPE:
      return "CANNOT_CREATE_FOR_ACC_ID_AND_ACC_TYPE";
    case ::stellar::ManageLimitsResultCode::INVALID_LIMITS:
      return "INVALID_LIMITS";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageLimitsResultCode::SUCCESS,
      (int32_t)::stellar::ManageLimitsResultCode::MALFORMED,
      (int32_t)::stellar::ManageLimitsResultCode::NOT_FOUND,
      (int32_t)::stellar::ManageLimitsResultCode::ALREADY_EXISTS,
      (int32_t)::stellar::ManageLimitsResultCode::CANNOT_CREATE_FOR_ACC_ID_AND_ACC_TYPE,
      (int32_t)::stellar::ManageLimitsResultCode::INVALID_LIMITS
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ManageLimitsResult {
  struct _success_t {
    struct _details_t {
      using _xdr_case_type = xdr::xdr_traits<ManageLimitsAction>::case_type;
    private:
      _xdr_case_type action_;
      union {
        uint64 id_;
      };

    public:
      static Constexpr const bool _xdr_has_default_case = false;
      static const std::vector<ManageLimitsAction> &_xdr_case_values() {
        static const std::vector<ManageLimitsAction> _xdr_disc_vec {
          ManageLimitsAction::CREATE,
          ManageLimitsAction::REMOVE
        };
        return _xdr_disc_vec;
      }
      static Constexpr int _xdr_field_number(_xdr_case_type which) {
        return which == (int32_t)ManageLimitsAction::CREATE ? 1
          : which == (int32_t)ManageLimitsAction::REMOVE ? 0
          : -1;
      }
      template<typename _F, typename..._A> static bool
      _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
        switch (_which) {
        case (int32_t)ManageLimitsAction::CREATE:
          _f(&_details_t::id_, std::forward<_A>(_a)...);
          return true;
        case (int32_t)ManageLimitsAction::REMOVE:
          return true;
        }
        return false;
      }

      _xdr_case_type _xdr_discriminant() const { return action_; }
      void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
        int fnum = _xdr_field_number(which);
        if (fnum < 0 && validate)
          throw xdr::xdr_bad_discriminant("bad value of action in _details_t");
        if (fnum != _xdr_field_number(action_)) {
          this->~_details_t();
          action_ = which;
          _xdr_with_mem_ptr(xdr::field_constructor, action_, *this);
        }
        else
          action_ = which;
      }
      explicit _details_t(ManageLimitsAction which = ManageLimitsAction{}) : action_((int32_t)which) {
        _xdr_with_mem_ptr(xdr::field_constructor, action_, *this);
      }
      _details_t(const _details_t &source) : action_(source.action_) {
        _xdr_with_mem_ptr(xdr::field_constructor, action_, *this, source);
      }
      _details_t(_details_t &&source) : action_(source.action_) {
        _xdr_with_mem_ptr(xdr::field_constructor, action_, *this,
                          std::move(source));
      }
      ~_details_t() { _xdr_with_mem_ptr(xdr::field_destructor, action_, *this); }
      _details_t &operator=(const _details_t &source) {
        if (_xdr_field_number(action_)
            == _xdr_field_number(source.action_))
          _xdr_with_mem_ptr(xdr::field_assigner, action_, *this, source);
        else {
          this->~_details_t();
          action_ = std::numeric_limits<_xdr_case_type>::max();
          _xdr_with_mem_ptr(xdr::field_constructor, source.action_, *this, source);
        }
        action_ = source.action_;
        return *this;
      }
      _details_t &operator=(_details_t &&source) {
        if (_xdr_field_number(action_)
             == _xdr_field_number(source.action_))
          _xdr_with_mem_ptr(xdr::field_assigner, action_, *this,
                            std::move(source));
        else {
          this->~_details_t();
          action_ = std::numeric_limits<_xdr_case_type>::max();
          _xdr_with_mem_ptr(xdr::field_constructor, source.action_, *this,
                            std::move(source));
        }
        action_ = source.action_;
        return *this;
      }

      ManageLimitsAction action() const { return ManageLimitsAction(action_); }
      _details_t &action(ManageLimitsAction _xdr_d, bool _xdr_validate = true) {
        _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
        return *this;
      }

      uint64 &id() {
        if (_xdr_field_number(action_) == 1)
          return id_;
        throw xdr::xdr_wrong_union("_details_t: id accessed when not selected");
      }
      const uint64 &id() const {
        if (_xdr_field_number(action_) == 1)
          return id_;
        throw xdr::xdr_wrong_union("_details_t: id accessed when not selected");
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

    _details_t details{};
    _ext_t ext{};

    _success_t() = default;
    template<typename _details_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<_details_t, _details_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _success_t(_details_T &&_details,
                        _ext_T &&_ext)
      : details(std::forward<_details_T>(_details)),
        ext(std::forward<_ext_T>(_ext)) {}
  };

  using _xdr_case_type = xdr::xdr_traits<ManageLimitsResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    _success_t success_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = true;
  static const std::vector<ManageLimitsResultCode> &_xdr_case_values() {
    static const std::vector<ManageLimitsResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)ManageLimitsResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)ManageLimitsResultCode::SUCCESS:
      _f(&ManageLimitsResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in ManageLimitsResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~ManageLimitsResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit ManageLimitsResult(ManageLimitsResultCode which = ManageLimitsResultCode{}) : code_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  ManageLimitsResult(const ManageLimitsResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  ManageLimitsResult(ManageLimitsResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~ManageLimitsResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  ManageLimitsResult &operator=(const ManageLimitsResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~ManageLimitsResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  ManageLimitsResult &operator=(ManageLimitsResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~ManageLimitsResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  ManageLimitsResultCode code() const { return ManageLimitsResultCode(code_); }
  ManageLimitsResult &code(ManageLimitsResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  _success_t &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageLimitsResult: success accessed when not selected");
  }
  const _success_t &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageLimitsResult: success accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageLimitsResult::_success_t::_details_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageLimitsResult::_success_t::_details_t;
  using case_type = ::stellar::ManageLimitsResult::_success_t::_details_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().action());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "id";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageLimitsResult::_success_t::_details_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of action in _details_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageLimitsResult::_success_t::_details_t &obj) {
    xdr::archive(ar, obj.action(), "action");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.action(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of action in _details_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageLimitsResult::_success_t::_details_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "action");
    obj.action(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.action(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageLimitsResult::_success_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageLimitsResult::_success_t::_ext_t;
  using case_type = ::stellar::ManageLimitsResult::_success_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageLimitsResult::_success_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageLimitsResult::_success_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageLimitsResult::_success_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageLimitsResult::_success_t>
  : xdr_struct_base<field_ptr<::stellar::ManageLimitsResult::_success_t,
                              decltype(::stellar::ManageLimitsResult::_success_t::details),
                              &::stellar::ManageLimitsResult::_success_t::details>,
                    field_ptr<::stellar::ManageLimitsResult::_success_t,
                              decltype(::stellar::ManageLimitsResult::_success_t::ext),
                              &::stellar::ManageLimitsResult::_success_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageLimitsResult::_success_t &obj) {
    archive(ar, obj.details, "details");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageLimitsResult::_success_t &obj) {
    archive(ar, obj.details, "details");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageLimitsResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageLimitsResult;
  using case_type = ::stellar::ManageLimitsResult::_xdr_case_type;
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

  static std::size_t serial_size(const ::stellar::ManageLimitsResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in ManageLimitsResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageLimitsResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in ManageLimitsResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageLimitsResult &obj) {
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

#endif // !__XDR_STELLAR_OPERATION_MANAGE_LIMITS_H_INCLUDED__
