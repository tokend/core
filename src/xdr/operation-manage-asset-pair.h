// -*- C++ -*-
// Automatically generated from operation-manage-asset-pair.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_MANAGE_ASSET_PAIR_H_INCLUDED__
#define __XDR_OPERATION_MANAGE_ASSET_PAIR_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/ledger-entries.h"

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
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
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

struct ManageAssetPairOp  : xdr::xdr_abstract {
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

enum class ManageAssetPairResultCode : std::int32_t {
  SUCCESS = 0,
  NOT_FOUND = -1,
  ALREADY_EXISTS = -2,
  MALFORMED = -3,
  INVALID_ASSET = -4,
  INVALID_ACTION = -5,
  INVALID_POLICIES = -6,
  ASSET_NOT_FOUND = -7,
  SAME_ASSET = -8,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageAssetPairResultCode>
  : xdr_integral_base<::stellar::ManageAssetPairResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
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
    case ::stellar::ManageAssetPairResultCode::SAME_ASSET:
      return "SAME_ASSET";
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
      (int32_t)::stellar::ManageAssetPairResultCode::ASSET_NOT_FOUND,
      (int32_t)::stellar::ManageAssetPairResultCode::SAME_ASSET
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ManageAssetPairSuccess  : xdr::xdr_abstract {
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

struct ManageAssetPairResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<ManageAssetPairResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    ManageAssetPairSuccess success_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<ManageAssetPairResultCode> &_xdr_case_values() {
    static const std::vector<ManageAssetPairResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
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
      code_ = which;switch (code_)
{
      case (int32_t)ManageAssetPairResultCode::SUCCESS:
new(&success_) ManageAssetPairSuccess{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit ManageAssetPairResult(ManageAssetPairResultCode which = ManageAssetPairResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)ManageAssetPairResultCode::SUCCESS:
new(&success_) ManageAssetPairSuccess{};
break;
    default:
      break;
}

  }
  ManageAssetPairResult(const ManageAssetPairResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManageAssetPairResultCode::SUCCESS:
new(&success_) ManageAssetPairSuccess(source.success_);
break;
    default:
      break;
}

  }
  ManageAssetPairResult(ManageAssetPairResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManageAssetPairResultCode::SUCCESS:
new(&success_) ManageAssetPairSuccess(std::move(source.success_));
break;
    default:
      break;
}

  }
  ~ManageAssetPairResult() {
switch (code_)
{
  case (int32_t)ManageAssetPairResultCode::SUCCESS:
success_.~ManageAssetPairSuccess();
break;
  default:
    break;
}
}

  ManageAssetPairResult &operator=(const ManageAssetPairResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManageAssetPairResultCode::SUCCESS:
success_ = source.success_;
break;
    default:
      break;
}
}
else {this->~ManageAssetPairResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)ManageAssetPairResultCode::SUCCESS:
new(&success_) ManageAssetPairSuccess(source.success_);
break;
    default:
      break;
}
}
    return *this;
  }
  ManageAssetPairResult &operator=(ManageAssetPairResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManageAssetPairResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    default:
      break;
}
}
else {this->~ManageAssetPairResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)ManageAssetPairResultCode::SUCCESS:
new(&success_) ManageAssetPairSuccess(std::move(source.success_));
break;
    default:
      break;
}
}
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

#endif // !__XDR_OPERATION_MANAGE_ASSET_PAIR_H_INCLUDED__
