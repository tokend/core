// -*- C++ -*-
// Automatically generated from Stellar-operation-set-fees.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_OPERATION_SET_FEES_H_INCLUDED__
#define __XDR_STELLAR_OPERATION_SET_FEES_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-ledger-entries.h"
#include "xdr/Stellar-ledger-entries-fee.h"

namespace stellar {

struct SetFeesOp {
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

  xdr::pointer<FeeEntry> fee{};
  bool isDelete{};
  _ext_t ext{};

  SetFeesOp() = default;
  template<typename _fee_T,
           typename _isDelete_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::pointer<FeeEntry>, _fee_T>::value
                          && std::is_constructible<bool, _isDelete_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit SetFeesOp(_fee_T &&_fee,
                     _isDelete_T &&_isDelete,
                     _ext_T &&_ext)
    : fee(std::forward<_fee_T>(_fee)),
      isDelete(std::forward<_isDelete_T>(_isDelete)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SetFeesOp::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::SetFeesOp::_ext_t;
  using case_type = ::stellar::SetFeesOp::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::SetFeesOp::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SetFeesOp::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SetFeesOp::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::SetFeesOp>
  : xdr_struct_base<field_ptr<::stellar::SetFeesOp,
                              decltype(::stellar::SetFeesOp::fee),
                              &::stellar::SetFeesOp::fee>,
                    field_ptr<::stellar::SetFeesOp,
                              decltype(::stellar::SetFeesOp::isDelete),
                              &::stellar::SetFeesOp::isDelete>,
                    field_ptr<::stellar::SetFeesOp,
                              decltype(::stellar::SetFeesOp::ext),
                              &::stellar::SetFeesOp::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SetFeesOp &obj) {
    archive(ar, obj.fee, "fee");
    archive(ar, obj.isDelete, "isDelete");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SetFeesOp &obj) {
    archive(ar, obj.fee, "fee");
    archive(ar, obj.isDelete, "isDelete");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum class SetFeesResultCode : std::int32_t {
  SUCCESS = 0,
  INVALID_AMOUNT = -1,
  INVALID_FEE_TYPE = -2,
  ASSET_NOT_FOUND = -3,
  INVALID_ASSET = -4,
  MALFORMED = -5,
  MALFORMED_RANGE = -6,
  RANGE_OVERLAP = -7,
  NOT_FOUND = -8,
  SUB_TYPE_NOT_EXIST = -9,
  INVALID_FEE_VERSION = -10,
  INVALID_FEE_ASSET = -11,
  FEE_ASSET_NOT_ALLOWED = -12,
  CROSS_ASSET_FEE_NOT_ALLOWED = -13,
  FEE_ASSET_NOT_FOUND = -14,
  ASSET_PAIR_NOT_FOUND = -15,
  INVALID_ASSET_PAIR_PRICE = -16,
  INVALID_FEE_HASH = -17,
  INVALID_AMOUNT_PRECISION = -18,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SetFeesResultCode>
  : xdr_integral_base<::stellar::SetFeesResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::SetFeesResultCode val) {
    switch (val) {
    case ::stellar::SetFeesResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::SetFeesResultCode::INVALID_AMOUNT:
      return "INVALID_AMOUNT";
    case ::stellar::SetFeesResultCode::INVALID_FEE_TYPE:
      return "INVALID_FEE_TYPE";
    case ::stellar::SetFeesResultCode::ASSET_NOT_FOUND:
      return "ASSET_NOT_FOUND";
    case ::stellar::SetFeesResultCode::INVALID_ASSET:
      return "INVALID_ASSET";
    case ::stellar::SetFeesResultCode::MALFORMED:
      return "MALFORMED";
    case ::stellar::SetFeesResultCode::MALFORMED_RANGE:
      return "MALFORMED_RANGE";
    case ::stellar::SetFeesResultCode::RANGE_OVERLAP:
      return "RANGE_OVERLAP";
    case ::stellar::SetFeesResultCode::NOT_FOUND:
      return "NOT_FOUND";
    case ::stellar::SetFeesResultCode::SUB_TYPE_NOT_EXIST:
      return "SUB_TYPE_NOT_EXIST";
    case ::stellar::SetFeesResultCode::INVALID_FEE_VERSION:
      return "INVALID_FEE_VERSION";
    case ::stellar::SetFeesResultCode::INVALID_FEE_ASSET:
      return "INVALID_FEE_ASSET";
    case ::stellar::SetFeesResultCode::FEE_ASSET_NOT_ALLOWED:
      return "FEE_ASSET_NOT_ALLOWED";
    case ::stellar::SetFeesResultCode::CROSS_ASSET_FEE_NOT_ALLOWED:
      return "CROSS_ASSET_FEE_NOT_ALLOWED";
    case ::stellar::SetFeesResultCode::FEE_ASSET_NOT_FOUND:
      return "FEE_ASSET_NOT_FOUND";
    case ::stellar::SetFeesResultCode::ASSET_PAIR_NOT_FOUND:
      return "ASSET_PAIR_NOT_FOUND";
    case ::stellar::SetFeesResultCode::INVALID_ASSET_PAIR_PRICE:
      return "INVALID_ASSET_PAIR_PRICE";
    case ::stellar::SetFeesResultCode::INVALID_FEE_HASH:
      return "INVALID_FEE_HASH";
    case ::stellar::SetFeesResultCode::INVALID_AMOUNT_PRECISION:
      return "INVALID_AMOUNT_PRECISION";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::SetFeesResultCode::SUCCESS,
      (int32_t)::stellar::SetFeesResultCode::INVALID_AMOUNT,
      (int32_t)::stellar::SetFeesResultCode::INVALID_FEE_TYPE,
      (int32_t)::stellar::SetFeesResultCode::ASSET_NOT_FOUND,
      (int32_t)::stellar::SetFeesResultCode::INVALID_ASSET,
      (int32_t)::stellar::SetFeesResultCode::MALFORMED,
      (int32_t)::stellar::SetFeesResultCode::MALFORMED_RANGE,
      (int32_t)::stellar::SetFeesResultCode::RANGE_OVERLAP,
      (int32_t)::stellar::SetFeesResultCode::NOT_FOUND,
      (int32_t)::stellar::SetFeesResultCode::SUB_TYPE_NOT_EXIST,
      (int32_t)::stellar::SetFeesResultCode::INVALID_FEE_VERSION,
      (int32_t)::stellar::SetFeesResultCode::INVALID_FEE_ASSET,
      (int32_t)::stellar::SetFeesResultCode::FEE_ASSET_NOT_ALLOWED,
      (int32_t)::stellar::SetFeesResultCode::CROSS_ASSET_FEE_NOT_ALLOWED,
      (int32_t)::stellar::SetFeesResultCode::FEE_ASSET_NOT_FOUND,
      (int32_t)::stellar::SetFeesResultCode::ASSET_PAIR_NOT_FOUND,
      (int32_t)::stellar::SetFeesResultCode::INVALID_ASSET_PAIR_PRICE,
      (int32_t)::stellar::SetFeesResultCode::INVALID_FEE_HASH,
      (int32_t)::stellar::SetFeesResultCode::INVALID_AMOUNT_PRECISION
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct SetFeesResult {
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

    _ext_t ext{};

    _success_t() = default;
    template<typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _success_t(_ext_T &&_ext)
      : ext(std::forward<_ext_T>(_ext)) {}
  };

  using _xdr_case_type = xdr::xdr_traits<SetFeesResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    _success_t success_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = true;
  static const std::vector<SetFeesResultCode> &_xdr_case_values() {
    static const std::vector<SetFeesResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)SetFeesResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)SetFeesResultCode::SUCCESS:
      _f(&SetFeesResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in SetFeesResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~SetFeesResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit SetFeesResult(SetFeesResultCode which = SetFeesResultCode{}) : code_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  SetFeesResult(const SetFeesResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  SetFeesResult(SetFeesResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~SetFeesResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  SetFeesResult &operator=(const SetFeesResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~SetFeesResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  SetFeesResult &operator=(SetFeesResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~SetFeesResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  SetFeesResultCode code() const { return SetFeesResultCode(code_); }
  SetFeesResult &code(SetFeesResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  _success_t &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("SetFeesResult: success accessed when not selected");
  }
  const _success_t &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("SetFeesResult: success accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SetFeesResult::_success_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::SetFeesResult::_success_t::_ext_t;
  using case_type = ::stellar::SetFeesResult::_success_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::SetFeesResult::_success_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SetFeesResult::_success_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SetFeesResult::_success_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::SetFeesResult::_success_t>
  : xdr_struct_base<field_ptr<::stellar::SetFeesResult::_success_t,
                              decltype(::stellar::SetFeesResult::_success_t::ext),
                              &::stellar::SetFeesResult::_success_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SetFeesResult::_success_t &obj) {
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SetFeesResult::_success_t &obj) {
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::SetFeesResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::SetFeesResult;
  using case_type = ::stellar::SetFeesResult::_xdr_case_type;
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

  static std::size_t serial_size(const ::stellar::SetFeesResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in SetFeesResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SetFeesResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in SetFeesResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SetFeesResult &obj) {
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

#endif // !__XDR_STELLAR_OPERATION_SET_FEES_H_INCLUDED__
