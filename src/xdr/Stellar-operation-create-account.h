// -*- C++ -*-
// Automatically generated from Stellar-operation-create-account.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_OPERATION_CREATE_ACCOUNT_H_INCLUDED__
#define __XDR_STELLAR_OPERATION_CREATE_ACCOUNT_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-types.h"
#include "xdr/Stellar-operation-manage-signer.h"

namespace stellar {

struct CreateAccountOp {
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

  AccountID destination{};
  xdr::pointer<AccountID> referrer{};
  uint64 roleID{};
  xdr::xvector<UpdateSignerData> signersData{};
  _ext_t ext{};

  CreateAccountOp() = default;
  template<typename _destination_T,
           typename _referrer_T,
           typename _roleID_T,
           typename _signersData_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<AccountID, _destination_T>::value
                          && std::is_constructible<xdr::pointer<AccountID>, _referrer_T>::value
                          && std::is_constructible<uint64, _roleID_T>::value
                          && std::is_constructible<xdr::xvector<UpdateSignerData>, _signersData_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateAccountOp(_destination_T &&_destination,
                           _referrer_T &&_referrer,
                           _roleID_T &&_roleID,
                           _signersData_T &&_signersData,
                           _ext_T &&_ext)
    : destination(std::forward<_destination_T>(_destination)),
      referrer(std::forward<_referrer_T>(_referrer)),
      roleID(std::forward<_roleID_T>(_roleID)),
      signersData(std::forward<_signersData_T>(_signersData)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateAccountOp::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CreateAccountOp::_ext_t;
  using case_type = ::stellar::CreateAccountOp::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::CreateAccountOp::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateAccountOp::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateAccountOp::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::CreateAccountOp>
  : xdr_struct_base<field_ptr<::stellar::CreateAccountOp,
                              decltype(::stellar::CreateAccountOp::destination),
                              &::stellar::CreateAccountOp::destination>,
                    field_ptr<::stellar::CreateAccountOp,
                              decltype(::stellar::CreateAccountOp::referrer),
                              &::stellar::CreateAccountOp::referrer>,
                    field_ptr<::stellar::CreateAccountOp,
                              decltype(::stellar::CreateAccountOp::roleID),
                              &::stellar::CreateAccountOp::roleID>,
                    field_ptr<::stellar::CreateAccountOp,
                              decltype(::stellar::CreateAccountOp::signersData),
                              &::stellar::CreateAccountOp::signersData>,
                    field_ptr<::stellar::CreateAccountOp,
                              decltype(::stellar::CreateAccountOp::ext),
                              &::stellar::CreateAccountOp::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateAccountOp &obj) {
    archive(ar, obj.destination, "destination");
    archive(ar, obj.referrer, "referrer");
    archive(ar, obj.roleID, "roleID");
    archive(ar, obj.signersData, "signersData");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateAccountOp &obj) {
    archive(ar, obj.destination, "destination");
    archive(ar, obj.referrer, "referrer");
    archive(ar, obj.roleID, "roleID");
    archive(ar, obj.signersData, "signersData");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum class CreateAccountResultCode : std::int32_t {
  SUCCESS = 0,
  INVALID_DESTINATION = -1,
  ALREADY_EXISTS = -2,
  INVALID_WEIGHT = -3,
  NO_SUCH_ROLE = -4,
  INVALID_SIGNER_DATA = -5,
  NO_SIGNER_DATA = -6,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateAccountResultCode>
  : xdr_integral_base<::stellar::CreateAccountResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::CreateAccountResultCode val) {
    switch (val) {
    case ::stellar::CreateAccountResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::CreateAccountResultCode::INVALID_DESTINATION:
      return "INVALID_DESTINATION";
    case ::stellar::CreateAccountResultCode::ALREADY_EXISTS:
      return "ALREADY_EXISTS";
    case ::stellar::CreateAccountResultCode::INVALID_WEIGHT:
      return "INVALID_WEIGHT";
    case ::stellar::CreateAccountResultCode::NO_SUCH_ROLE:
      return "NO_SUCH_ROLE";
    case ::stellar::CreateAccountResultCode::INVALID_SIGNER_DATA:
      return "INVALID_SIGNER_DATA";
    case ::stellar::CreateAccountResultCode::NO_SIGNER_DATA:
      return "NO_SIGNER_DATA";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::CreateAccountResultCode::SUCCESS,
      (int32_t)::stellar::CreateAccountResultCode::INVALID_DESTINATION,
      (int32_t)::stellar::CreateAccountResultCode::ALREADY_EXISTS,
      (int32_t)::stellar::CreateAccountResultCode::INVALID_WEIGHT,
      (int32_t)::stellar::CreateAccountResultCode::NO_SUCH_ROLE,
      (int32_t)::stellar::CreateAccountResultCode::INVALID_SIGNER_DATA,
      (int32_t)::stellar::CreateAccountResultCode::NO_SIGNER_DATA
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateAccountSuccess {
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

  uint64 sequentialID{};
  _ext_t ext{};

  CreateAccountSuccess() = default;
  template<typename _sequentialID_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _sequentialID_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateAccountSuccess(_sequentialID_T &&_sequentialID,
                                _ext_T &&_ext)
    : sequentialID(std::forward<_sequentialID_T>(_sequentialID)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateAccountSuccess::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CreateAccountSuccess::_ext_t;
  using case_type = ::stellar::CreateAccountSuccess::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::CreateAccountSuccess::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateAccountSuccess::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateAccountSuccess::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::CreateAccountSuccess>
  : xdr_struct_base<field_ptr<::stellar::CreateAccountSuccess,
                              decltype(::stellar::CreateAccountSuccess::sequentialID),
                              &::stellar::CreateAccountSuccess::sequentialID>,
                    field_ptr<::stellar::CreateAccountSuccess,
                              decltype(::stellar::CreateAccountSuccess::ext),
                              &::stellar::CreateAccountSuccess::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateAccountSuccess &obj) {
    archive(ar, obj.sequentialID, "sequentialID");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateAccountSuccess &obj) {
    archive(ar, obj.sequentialID, "sequentialID");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct CreateAccountResult {
  using _xdr_case_type = xdr::xdr_traits<CreateAccountResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    CreateAccountSuccess success_;
    ManageSignerResultCode createSignerErrorCode_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = true;
  static const std::vector<CreateAccountResultCode> &_xdr_case_values() {
    static const std::vector<CreateAccountResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)CreateAccountResultCode::SUCCESS ? 1
      : which == (int32_t)CreateAccountResultCode::INVALID_SIGNER_DATA ? 2
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)CreateAccountResultCode::SUCCESS:
      _f(&CreateAccountResult::success_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)CreateAccountResultCode::INVALID_SIGNER_DATA:
      _f(&CreateAccountResult::createSignerErrorCode_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in CreateAccountResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~CreateAccountResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit CreateAccountResult(CreateAccountResultCode which = CreateAccountResultCode{}) : code_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  CreateAccountResult(const CreateAccountResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  CreateAccountResult(CreateAccountResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~CreateAccountResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  CreateAccountResult &operator=(const CreateAccountResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~CreateAccountResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  CreateAccountResult &operator=(CreateAccountResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~CreateAccountResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  CreateAccountResultCode code() const { return CreateAccountResultCode(code_); }
  CreateAccountResult &code(CreateAccountResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  CreateAccountSuccess &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateAccountResult: success accessed when not selected");
  }
  const CreateAccountSuccess &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateAccountResult: success accessed when not selected");
  }
  ManageSignerResultCode &createSignerErrorCode() {
    if (_xdr_field_number(code_) == 2)
      return createSignerErrorCode_;
    throw xdr::xdr_wrong_union("CreateAccountResult: createSignerErrorCode accessed when not selected");
  }
  const ManageSignerResultCode &createSignerErrorCode() const {
    if (_xdr_field_number(code_) == 2)
      return createSignerErrorCode_;
    throw xdr::xdr_wrong_union("CreateAccountResult: createSignerErrorCode accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateAccountResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CreateAccountResult;
  using case_type = ::stellar::CreateAccountResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "success";
    case 2:
      return "createSignerErrorCode";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::CreateAccountResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in CreateAccountResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateAccountResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in CreateAccountResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateAccountResult &obj) {
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

#endif // !__XDR_STELLAR_OPERATION_CREATE_ACCOUNT_H_INCLUDED__
