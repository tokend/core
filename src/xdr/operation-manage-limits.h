// -*- C++ -*-
// Automatically generated from operation-manage-limits.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_MANAGE_LIMITS_H_INCLUDED__
#define __XDR_OPERATION_MANAGE_LIMITS_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/ledger-entries-limits-v2.h"

namespace stellar {

enum class ManageLimitsAction : std::int32_t {
  CREATE = 0,
  REMOVE = 1,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageLimitsAction>
  : xdr_integral_base<::stellar::ManageLimitsAction, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
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

struct LimitsCreateDetails  : xdr::xdr_abstract {
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

struct ManageLimitsOp  : xdr::xdr_abstract {
  struct _details_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<ManageLimitsAction>::case_type;
  private:
    _xdr_case_type action_;
    union {
      LimitsCreateDetails limitsCreateDetails_;
      uint64 id_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<ManageLimitsAction> &_xdr_case_values() {
      static const std::vector<ManageLimitsAction> _xdr_disc_vec {
        ManageLimitsAction::CREATE,
        ManageLimitsAction::REMOVE
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
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
        action_ = which;switch (action_)
{
        case (int32_t)ManageLimitsAction::CREATE:
new(&limitsCreateDetails_) LimitsCreateDetails{};
break;
        case (int32_t)ManageLimitsAction::REMOVE:
new(&id_) uint64{};
break;
}

      }
      else
        action_ = which;
    }
    explicit _details_t(ManageLimitsAction which = ManageLimitsAction{}) : action_((int32_t)which) {
      switch (action_)
{
      case (int32_t)ManageLimitsAction::CREATE:
new(&limitsCreateDetails_) LimitsCreateDetails{};
break;
      case (int32_t)ManageLimitsAction::REMOVE:
new(&id_) uint64{};
break;
}

    }
    _details_t(const _details_t &source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageLimitsAction::CREATE:
new(&limitsCreateDetails_) LimitsCreateDetails(source.limitsCreateDetails_);
break;
      case (int32_t)ManageLimitsAction::REMOVE:
new(&id_) uint64(source.id_);
break;
}

    }
    _details_t(_details_t &&source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageLimitsAction::CREATE:
new(&limitsCreateDetails_) LimitsCreateDetails(std::move(source.limitsCreateDetails_));
break;
      case (int32_t)ManageLimitsAction::REMOVE:
new(&id_) uint64(std::move(source.id_));
break;
}

    }
    ~_details_t() {
switch (action_)
{
    case (int32_t)ManageLimitsAction::CREATE:
limitsCreateDetails_.~LimitsCreateDetails();
break;
    case (int32_t)ManageLimitsAction::REMOVE:
id_.~uint64();
break;
}
}

    _details_t &operator=(const _details_t &source) {
      if (action_ == source.action_)
{
switch (action_)
{
      case (int32_t)ManageLimitsAction::CREATE:
limitsCreateDetails_ = source.limitsCreateDetails_;
break;
      case (int32_t)ManageLimitsAction::REMOVE:
id_ = source.id_;
break;
}
}
else {this->~_details_t();
      action_ = source.action_;
switch (action_)
{
      case (int32_t)ManageLimitsAction::CREATE:
new(&limitsCreateDetails_) LimitsCreateDetails(source.limitsCreateDetails_);
break;
      case (int32_t)ManageLimitsAction::REMOVE:
new(&id_) uint64(source.id_);
break;
}
}
      return *this;
    }
    _details_t &operator=(_details_t &&source) {
      if (action_ == source.action_)
{
switch (action_)
{
      case (int32_t)ManageLimitsAction::CREATE:
limitsCreateDetails_ = std::move(source.limitsCreateDetails_);
break;
      case (int32_t)ManageLimitsAction::REMOVE:
id_ = std::move(source.id_);
break;
}
}
else {this->~_details_t();
      action_ = std::move(source.action_);
switch (action_)
{
      case (int32_t)ManageLimitsAction::CREATE:
new(&limitsCreateDetails_) LimitsCreateDetails(std::move(source.limitsCreateDetails_));
break;
      case (int32_t)ManageLimitsAction::REMOVE:
new(&id_) uint64(std::move(source.id_));
break;
}
}
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

enum class ManageLimitsResultCode : std::int32_t {
  SUCCESS = 0,
  ACCOUNT_NOT_FOUND = -1,
  NOT_FOUND = -2,
  ROLE_NOT_FOUND = -3,
  CANNOT_CREATE_FOR_ACC_ID_AND_ACC_TYPE = -4,
  INVALID_LIMITS = -5,
  ASSET_NOT_FOUND = -6,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageLimitsResultCode>
  : xdr_integral_base<::stellar::ManageLimitsResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageLimitsResultCode val) {
    switch (val) {
    case ::stellar::ManageLimitsResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::ManageLimitsResultCode::ACCOUNT_NOT_FOUND:
      return "ACCOUNT_NOT_FOUND";
    case ::stellar::ManageLimitsResultCode::NOT_FOUND:
      return "NOT_FOUND";
    case ::stellar::ManageLimitsResultCode::ROLE_NOT_FOUND:
      return "ROLE_NOT_FOUND";
    case ::stellar::ManageLimitsResultCode::CANNOT_CREATE_FOR_ACC_ID_AND_ACC_TYPE:
      return "CANNOT_CREATE_FOR_ACC_ID_AND_ACC_TYPE";
    case ::stellar::ManageLimitsResultCode::INVALID_LIMITS:
      return "INVALID_LIMITS";
    case ::stellar::ManageLimitsResultCode::ASSET_NOT_FOUND:
      return "ASSET_NOT_FOUND";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageLimitsResultCode::SUCCESS,
      (int32_t)::stellar::ManageLimitsResultCode::ACCOUNT_NOT_FOUND,
      (int32_t)::stellar::ManageLimitsResultCode::NOT_FOUND,
      (int32_t)::stellar::ManageLimitsResultCode::ROLE_NOT_FOUND,
      (int32_t)::stellar::ManageLimitsResultCode::CANNOT_CREATE_FOR_ACC_ID_AND_ACC_TYPE,
      (int32_t)::stellar::ManageLimitsResultCode::INVALID_LIMITS,
      (int32_t)::stellar::ManageLimitsResultCode::ASSET_NOT_FOUND
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ManageLimitsResult : xdr::xdr_abstract {
  struct _success_t  : xdr::xdr_abstract {
    struct _details_t : xdr::xdr_abstract {
      using _xdr_case_type = xdr::xdr_traits<ManageLimitsAction>::case_type;
    private:
      _xdr_case_type action_;
      union {
        uint64 id_;
      };

    public:
      static constexpr const bool _xdr_has_default_case = false;
      static const std::vector<ManageLimitsAction> &_xdr_case_values() {
        static const std::vector<ManageLimitsAction> _xdr_disc_vec {
          ManageLimitsAction::CREATE,
          ManageLimitsAction::REMOVE
        };
        return _xdr_disc_vec;
      }
      static constexpr int _xdr_field_number(_xdr_case_type which) {
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
          action_ = which;switch (action_)
{
          case (int32_t)ManageLimitsAction::CREATE:
new(&id_) uint64{};
break;
          case (int32_t)ManageLimitsAction::REMOVE:
            break;
}

        }
        else
          action_ = which;
      }
      explicit _details_t(ManageLimitsAction which = ManageLimitsAction{}) : action_((int32_t)which) {
        switch (action_)
{
        case (int32_t)ManageLimitsAction::CREATE:
new(&id_) uint64{};
break;
        case (int32_t)ManageLimitsAction::REMOVE:
          break;
}

      }
      _details_t(const _details_t &source) : action_(source.action_) {
        switch (action_)
{
        case (int32_t)ManageLimitsAction::CREATE:
new(&id_) uint64(source.id_);
break;
        case (int32_t)ManageLimitsAction::REMOVE:
          break;
}

      }
      _details_t(_details_t &&source) : action_(source.action_) {
        switch (action_)
{
        case (int32_t)ManageLimitsAction::CREATE:
new(&id_) uint64(std::move(source.id_));
break;
        case (int32_t)ManageLimitsAction::REMOVE:
          break;
}

      }
      ~_details_t() {
switch (action_)
{
      case (int32_t)ManageLimitsAction::CREATE:
id_.~uint64();
break;
      case (int32_t)ManageLimitsAction::REMOVE:
        break;
}
}

      _details_t &operator=(const _details_t &source) {
        if (action_ == source.action_)
{
switch (action_)
{
        case (int32_t)ManageLimitsAction::CREATE:
id_ = source.id_;
break;
        case (int32_t)ManageLimitsAction::REMOVE:
          break;
}
}
else {this->~_details_t();
        action_ = source.action_;
switch (action_)
{
        case (int32_t)ManageLimitsAction::CREATE:
new(&id_) uint64(source.id_);
break;
        case (int32_t)ManageLimitsAction::REMOVE:
          break;
}
}
        return *this;
      }
      _details_t &operator=(_details_t &&source) {
        if (action_ == source.action_)
{
switch (action_)
{
        case (int32_t)ManageLimitsAction::CREATE:
id_ = std::move(source.id_);
break;
        case (int32_t)ManageLimitsAction::REMOVE:
          break;
}
}
else {this->~_details_t();
        action_ = std::move(source.action_);
switch (action_)
{
        case (int32_t)ManageLimitsAction::CREATE:
new(&id_) uint64(std::move(source.id_));
break;
        case (int32_t)ManageLimitsAction::REMOVE:
          break;
}
}
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

  using _xdr_case_type = xdr::xdr_traits<ManageLimitsResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    _success_t success_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<ManageLimitsResultCode> &_xdr_case_values() {
    static const std::vector<ManageLimitsResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
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
      code_ = which;switch (code_)
{
      case (int32_t)ManageLimitsResultCode::SUCCESS:
new(&success_) _success_t{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit ManageLimitsResult(ManageLimitsResultCode which = ManageLimitsResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)ManageLimitsResultCode::SUCCESS:
new(&success_) _success_t{};
break;
    default:
      break;
}

  }
  ManageLimitsResult(const ManageLimitsResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManageLimitsResultCode::SUCCESS:
new(&success_) _success_t(source.success_);
break;
    default:
      break;
}

  }
  ManageLimitsResult(ManageLimitsResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManageLimitsResultCode::SUCCESS:
new(&success_) _success_t(std::move(source.success_));
break;
    default:
      break;
}

  }
  ~ManageLimitsResult() {
switch (code_)
{
  case (int32_t)ManageLimitsResultCode::SUCCESS:
success_.~_success_t();
break;
  default:
    break;
}
}

  ManageLimitsResult &operator=(const ManageLimitsResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManageLimitsResultCode::SUCCESS:
success_ = source.success_;
break;
    default:
      break;
}
}
else {this->~ManageLimitsResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)ManageLimitsResultCode::SUCCESS:
new(&success_) _success_t(source.success_);
break;
    default:
      break;
}
}
    return *this;
  }
  ManageLimitsResult &operator=(ManageLimitsResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManageLimitsResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    default:
      break;
}
}
else {this->~ManageLimitsResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)ManageLimitsResultCode::SUCCESS:
new(&success_) _success_t(std::move(source.success_));
break;
    default:
      break;
}
}
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

#endif // !__XDR_OPERATION_MANAGE_LIMITS_H_INCLUDED__
