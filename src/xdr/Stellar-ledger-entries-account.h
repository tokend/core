// -*- C++ -*-
// Automatically generated from Stellar-ledger-entries-account.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_LEDGER_ENTRIES_ACCOUNT_H_INCLUDED__
#define __XDR_STELLAR_LEDGER_ENTRIES_ACCOUNT_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-types.h"

namespace stellar {

struct Limits {
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

  int64 dailyOut{};
  int64 weeklyOut{};
  int64 monthlyOut{};
  int64 annualOut{};
  _ext_t ext{};

  Limits() = default;
  template<typename _dailyOut_T,
           typename _weeklyOut_T,
           typename _monthlyOut_T,
           typename _annualOut_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<int64, _dailyOut_T>::value
                          && std::is_constructible<int64, _weeklyOut_T>::value
                          && std::is_constructible<int64, _monthlyOut_T>::value
                          && std::is_constructible<int64, _annualOut_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit Limits(_dailyOut_T &&_dailyOut,
                  _weeklyOut_T &&_weeklyOut,
                  _monthlyOut_T &&_monthlyOut,
                  _annualOut_T &&_annualOut,
                  _ext_T &&_ext)
    : dailyOut(std::forward<_dailyOut_T>(_dailyOut)),
      weeklyOut(std::forward<_weeklyOut_T>(_weeklyOut)),
      monthlyOut(std::forward<_monthlyOut_T>(_monthlyOut)),
      annualOut(std::forward<_annualOut_T>(_annualOut)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::Limits::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::Limits::_ext_t;
  using case_type = ::stellar::Limits::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::Limits::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::Limits::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::Limits::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::Limits>
  : xdr_struct_base<field_ptr<::stellar::Limits,
                              decltype(::stellar::Limits::dailyOut),
                              &::stellar::Limits::dailyOut>,
                    field_ptr<::stellar::Limits,
                              decltype(::stellar::Limits::weeklyOut),
                              &::stellar::Limits::weeklyOut>,
                    field_ptr<::stellar::Limits,
                              decltype(::stellar::Limits::monthlyOut),
                              &::stellar::Limits::monthlyOut>,
                    field_ptr<::stellar::Limits,
                              decltype(::stellar::Limits::annualOut),
                              &::stellar::Limits::annualOut>,
                    field_ptr<::stellar::Limits,
                              decltype(::stellar::Limits::ext),
                              &::stellar::Limits::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::Limits &obj) {
    archive(ar, obj.dailyOut, "dailyOut");
    archive(ar, obj.weeklyOut, "weeklyOut");
    archive(ar, obj.monthlyOut, "monthlyOut");
    archive(ar, obj.annualOut, "annualOut");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::Limits &obj) {
    archive(ar, obj.dailyOut, "dailyOut");
    archive(ar, obj.weeklyOut, "weeklyOut");
    archive(ar, obj.monthlyOut, "monthlyOut");
    archive(ar, obj.annualOut, "annualOut");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct AccountEntry {
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

  AccountID accountID{};
  xdr::pointer<AccountID> referrer{};
  uint64 sequentialID{};
  uint64 roleID{};
  _ext_t ext{};

  AccountEntry() = default;
  template<typename _accountID_T,
           typename _referrer_T,
           typename _sequentialID_T,
           typename _roleID_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<AccountID, _accountID_T>::value
                          && std::is_constructible<xdr::pointer<AccountID>, _referrer_T>::value
                          && std::is_constructible<uint64, _sequentialID_T>::value
                          && std::is_constructible<uint64, _roleID_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit AccountEntry(_accountID_T &&_accountID,
                        _referrer_T &&_referrer,
                        _sequentialID_T &&_sequentialID,
                        _roleID_T &&_roleID,
                        _ext_T &&_ext)
    : accountID(std::forward<_accountID_T>(_accountID)),
      referrer(std::forward<_referrer_T>(_referrer)),
      sequentialID(std::forward<_sequentialID_T>(_sequentialID)),
      roleID(std::forward<_roleID_T>(_roleID)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::AccountEntry::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::AccountEntry::_ext_t;
  using case_type = ::stellar::AccountEntry::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::AccountEntry::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::AccountEntry::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::AccountEntry::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::AccountEntry>
  : xdr_struct_base<field_ptr<::stellar::AccountEntry,
                              decltype(::stellar::AccountEntry::accountID),
                              &::stellar::AccountEntry::accountID>,
                    field_ptr<::stellar::AccountEntry,
                              decltype(::stellar::AccountEntry::referrer),
                              &::stellar::AccountEntry::referrer>,
                    field_ptr<::stellar::AccountEntry,
                              decltype(::stellar::AccountEntry::sequentialID),
                              &::stellar::AccountEntry::sequentialID>,
                    field_ptr<::stellar::AccountEntry,
                              decltype(::stellar::AccountEntry::roleID),
                              &::stellar::AccountEntry::roleID>,
                    field_ptr<::stellar::AccountEntry,
                              decltype(::stellar::AccountEntry::ext),
                              &::stellar::AccountEntry::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::AccountEntry &obj) {
    archive(ar, obj.accountID, "accountID");
    archive(ar, obj.referrer, "referrer");
    archive(ar, obj.sequentialID, "sequentialID");
    archive(ar, obj.roleID, "roleID");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::AccountEntry &obj) {
    archive(ar, obj.accountID, "accountID");
    archive(ar, obj.referrer, "referrer");
    archive(ar, obj.sequentialID, "sequentialID");
    archive(ar, obj.roleID, "roleID");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

}

#endif // !__XDR_STELLAR_LEDGER_ENTRIES_ACCOUNT_H_INCLUDED__
