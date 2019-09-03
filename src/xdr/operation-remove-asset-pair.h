// -*- C++ -*-
// Automatically generated from operation-remove-asset-pair.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_REMOVE_ASSET_PAIR_H_INCLUDED__
#define __XDR_OPERATION_REMOVE_ASSET_PAIR_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/types.h"

namespace stellar {

struct RemoveAssetPairOp  : xdr::xdr_abstract {
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

  AssetCode base{};
  AssetCode quote{};
  _ext_t ext{};

  RemoveAssetPairOp() = default;
  template<typename _base_T,
           typename _quote_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<AssetCode, _base_T>::value
                          && std::is_constructible<AssetCode, _quote_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit RemoveAssetPairOp(_base_T &&_base,
                             _quote_T &&_quote,
                             _ext_T &&_ext)
    : base(std::forward<_base_T>(_base)),
      quote(std::forward<_quote_T>(_quote)),
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

enum class RemoveAssetPairResultCode : std::int32_t {
  SUCCESS = 0,
  NOT_FOUND = -1,
  HAS_ACTIVE_OFFERS = -2,
  HAS_ACTIVE_SALES = -3,
  INVALID_ASSET_CODE = -4,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::RemoveAssetPairResultCode>
  : xdr_integral_base<::stellar::RemoveAssetPairResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::RemoveAssetPairResultCode val) {
    switch (val) {
    case ::stellar::RemoveAssetPairResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::RemoveAssetPairResultCode::NOT_FOUND:
      return "NOT_FOUND";
    case ::stellar::RemoveAssetPairResultCode::HAS_ACTIVE_OFFERS:
      return "HAS_ACTIVE_OFFERS";
    case ::stellar::RemoveAssetPairResultCode::HAS_ACTIVE_SALES:
      return "HAS_ACTIVE_SALES";
    case ::stellar::RemoveAssetPairResultCode::INVALID_ASSET_CODE:
      return "INVALID_ASSET_CODE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::RemoveAssetPairResultCode::SUCCESS,
      (int32_t)::stellar::RemoveAssetPairResultCode::NOT_FOUND,
      (int32_t)::stellar::RemoveAssetPairResultCode::HAS_ACTIVE_OFFERS,
      (int32_t)::stellar::RemoveAssetPairResultCode::HAS_ACTIVE_SALES,
      (int32_t)::stellar::RemoveAssetPairResultCode::INVALID_ASSET_CODE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct RemoveAssetPairSuccess  : xdr::xdr_abstract {
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

  _ext_t ext{};

  RemoveAssetPairSuccess() = default;
  template<typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit RemoveAssetPairSuccess(_ext_T &&_ext)
    : ext(std::forward<_ext_T>(_ext)) {}
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

struct RemoveAssetPairResult : xdr::xdr_abstract {
  using _xdr_case_type = xdr::xdr_traits<RemoveAssetPairResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    RemoveAssetPairSuccess success_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<RemoveAssetPairResultCode> &_xdr_case_values() {
    static const std::vector<RemoveAssetPairResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)RemoveAssetPairResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)RemoveAssetPairResultCode::SUCCESS:
      _f(&RemoveAssetPairResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in RemoveAssetPairResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~RemoveAssetPairResult();
      code_ = which;switch (code_)
{
      case (int32_t)RemoveAssetPairResultCode::SUCCESS:
new(&success_) RemoveAssetPairSuccess{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit RemoveAssetPairResult(RemoveAssetPairResultCode which = RemoveAssetPairResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)RemoveAssetPairResultCode::SUCCESS:
new(&success_) RemoveAssetPairSuccess{};
break;
    default:
      break;
}

  }
  RemoveAssetPairResult(const RemoveAssetPairResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)RemoveAssetPairResultCode::SUCCESS:
new(&success_) RemoveAssetPairSuccess(source.success_);
break;
    default:
      break;
}

  }
  RemoveAssetPairResult(RemoveAssetPairResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)RemoveAssetPairResultCode::SUCCESS:
new(&success_) RemoveAssetPairSuccess(std::move(source.success_));
break;
    default:
      break;
}

  }
  ~RemoveAssetPairResult() {
switch (code_)
{
  case (int32_t)RemoveAssetPairResultCode::SUCCESS:
success_.~RemoveAssetPairSuccess();
break;
  default:
    break;
}
}

  RemoveAssetPairResult &operator=(const RemoveAssetPairResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)RemoveAssetPairResultCode::SUCCESS:
success_ = source.success_;
break;
    default:
      break;
}
}
else {this->~RemoveAssetPairResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)RemoveAssetPairResultCode::SUCCESS:
new(&success_) RemoveAssetPairSuccess(source.success_);
break;
    default:
      break;
}
}
    return *this;
  }
  RemoveAssetPairResult &operator=(RemoveAssetPairResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)RemoveAssetPairResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    default:
      break;
}
}
else {this->~RemoveAssetPairResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)RemoveAssetPairResultCode::SUCCESS:
new(&success_) RemoveAssetPairSuccess(std::move(source.success_));
break;
    default:
      break;
}
}
    return *this;
  }

  RemoveAssetPairResultCode code() const { return RemoveAssetPairResultCode(code_); }
  RemoveAssetPairResult &code(RemoveAssetPairResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  RemoveAssetPairSuccess &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("RemoveAssetPairResult: success accessed when not selected");
  }
  const RemoveAssetPairSuccess &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("RemoveAssetPairResult: success accessed when not selected");
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

#endif // !__XDR_OPERATION_REMOVE_ASSET_PAIR_H_INCLUDED__
