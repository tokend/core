// -*- C++ -*-
// Automatically generated from Stellar-operation-create-withdrawal-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_OPERATION_CREATE_WITHDRAWAL_REQUEST_H_INCLUDED__
#define __XDR_STELLAR_OPERATION_CREATE_WITHDRAWAL_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-ledger-entries.h"

namespace stellar {

struct CreateWithdrawalRequestOp {
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

  WithdrawalRequest request{};
  xdr::pointer<uint32> allTasks{};
  _ext_t ext{};

  CreateWithdrawalRequestOp() = default;
  template<typename _request_T,
           typename _allTasks_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<WithdrawalRequest, _request_T>::value
                          && std::is_constructible<xdr::pointer<uint32>, _allTasks_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateWithdrawalRequestOp(_request_T &&_request,
                                     _allTasks_T &&_allTasks,
                                     _ext_T &&_ext)
    : request(std::forward<_request_T>(_request)),
      allTasks(std::forward<_allTasks_T>(_allTasks)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateWithdrawalRequestOp::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CreateWithdrawalRequestOp::_ext_t;
  using case_type = ::stellar::CreateWithdrawalRequestOp::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::CreateWithdrawalRequestOp::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateWithdrawalRequestOp::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateWithdrawalRequestOp::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::CreateWithdrawalRequestOp>
  : xdr_struct_base<field_ptr<::stellar::CreateWithdrawalRequestOp,
                              decltype(::stellar::CreateWithdrawalRequestOp::request),
                              &::stellar::CreateWithdrawalRequestOp::request>,
                    field_ptr<::stellar::CreateWithdrawalRequestOp,
                              decltype(::stellar::CreateWithdrawalRequestOp::allTasks),
                              &::stellar::CreateWithdrawalRequestOp::allTasks>,
                    field_ptr<::stellar::CreateWithdrawalRequestOp,
                              decltype(::stellar::CreateWithdrawalRequestOp::ext),
                              &::stellar::CreateWithdrawalRequestOp::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateWithdrawalRequestOp &obj) {
    archive(ar, obj.request, "request");
    archive(ar, obj.allTasks, "allTasks");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateWithdrawalRequestOp &obj) {
    archive(ar, obj.request, "request");
    archive(ar, obj.allTasks, "allTasks");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum class CreateWithdrawalRequestResultCode : std::int32_t {
  SUCCESS = 0,
  INVALID_AMOUNT = -1,
  INVALID_CREATOR_DETAILS = -2,
  BALANCE_NOT_FOUND = -3,
  ASSET_IS_NOT_WITHDRAWABLE = -4,
  CONVERSION_PRICE_IS_NOT_AVAILABLE = -5,
  FEE_MISMATCHED = -6,
  CONVERSION_OVERFLOW = -7,
  CONVERTED_AMOUNT_MISMATCHED = -8,
  BALANCE_LOCK_OVERFLOW = -9,
  UNDERFUNDED = -10,
  INVALID_UNIVERSAL_AMOUNT = -11,
  STATS_OVERFLOW = -12,
  LIMITS_EXCEEDED = -13,
  INVALID_PRE_CONFIRMATION_DETAILS = -14,
  LOWER_BOUND_NOT_EXCEEDED = -15,
  WITHDRAWAL_TASKS_NOT_FOUND = -16,
  NOT_ALLOWED_TO_SET_WITHDRAWAL_TASKS = -17,
  WITHDRAWAL_ZERO_TASKS_NOT_ALLOWED = -18,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateWithdrawalRequestResultCode>
  : xdr_integral_base<::stellar::CreateWithdrawalRequestResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::CreateWithdrawalRequestResultCode val) {
    switch (val) {
    case ::stellar::CreateWithdrawalRequestResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::CreateWithdrawalRequestResultCode::INVALID_AMOUNT:
      return "INVALID_AMOUNT";
    case ::stellar::CreateWithdrawalRequestResultCode::INVALID_CREATOR_DETAILS:
      return "INVALID_CREATOR_DETAILS";
    case ::stellar::CreateWithdrawalRequestResultCode::BALANCE_NOT_FOUND:
      return "BALANCE_NOT_FOUND";
    case ::stellar::CreateWithdrawalRequestResultCode::ASSET_IS_NOT_WITHDRAWABLE:
      return "ASSET_IS_NOT_WITHDRAWABLE";
    case ::stellar::CreateWithdrawalRequestResultCode::CONVERSION_PRICE_IS_NOT_AVAILABLE:
      return "CONVERSION_PRICE_IS_NOT_AVAILABLE";
    case ::stellar::CreateWithdrawalRequestResultCode::FEE_MISMATCHED:
      return "FEE_MISMATCHED";
    case ::stellar::CreateWithdrawalRequestResultCode::CONVERSION_OVERFLOW:
      return "CONVERSION_OVERFLOW";
    case ::stellar::CreateWithdrawalRequestResultCode::CONVERTED_AMOUNT_MISMATCHED:
      return "CONVERTED_AMOUNT_MISMATCHED";
    case ::stellar::CreateWithdrawalRequestResultCode::BALANCE_LOCK_OVERFLOW:
      return "BALANCE_LOCK_OVERFLOW";
    case ::stellar::CreateWithdrawalRequestResultCode::UNDERFUNDED:
      return "UNDERFUNDED";
    case ::stellar::CreateWithdrawalRequestResultCode::INVALID_UNIVERSAL_AMOUNT:
      return "INVALID_UNIVERSAL_AMOUNT";
    case ::stellar::CreateWithdrawalRequestResultCode::STATS_OVERFLOW:
      return "STATS_OVERFLOW";
    case ::stellar::CreateWithdrawalRequestResultCode::LIMITS_EXCEEDED:
      return "LIMITS_EXCEEDED";
    case ::stellar::CreateWithdrawalRequestResultCode::INVALID_PRE_CONFIRMATION_DETAILS:
      return "INVALID_PRE_CONFIRMATION_DETAILS";
    case ::stellar::CreateWithdrawalRequestResultCode::LOWER_BOUND_NOT_EXCEEDED:
      return "LOWER_BOUND_NOT_EXCEEDED";
    case ::stellar::CreateWithdrawalRequestResultCode::WITHDRAWAL_TASKS_NOT_FOUND:
      return "WITHDRAWAL_TASKS_NOT_FOUND";
    case ::stellar::CreateWithdrawalRequestResultCode::NOT_ALLOWED_TO_SET_WITHDRAWAL_TASKS:
      return "NOT_ALLOWED_TO_SET_WITHDRAWAL_TASKS";
    case ::stellar::CreateWithdrawalRequestResultCode::WITHDRAWAL_ZERO_TASKS_NOT_ALLOWED:
      return "WITHDRAWAL_ZERO_TASKS_NOT_ALLOWED";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::CreateWithdrawalRequestResultCode::SUCCESS,
      (int32_t)::stellar::CreateWithdrawalRequestResultCode::INVALID_AMOUNT,
      (int32_t)::stellar::CreateWithdrawalRequestResultCode::INVALID_CREATOR_DETAILS,
      (int32_t)::stellar::CreateWithdrawalRequestResultCode::BALANCE_NOT_FOUND,
      (int32_t)::stellar::CreateWithdrawalRequestResultCode::ASSET_IS_NOT_WITHDRAWABLE,
      (int32_t)::stellar::CreateWithdrawalRequestResultCode::CONVERSION_PRICE_IS_NOT_AVAILABLE,
      (int32_t)::stellar::CreateWithdrawalRequestResultCode::FEE_MISMATCHED,
      (int32_t)::stellar::CreateWithdrawalRequestResultCode::CONVERSION_OVERFLOW,
      (int32_t)::stellar::CreateWithdrawalRequestResultCode::CONVERTED_AMOUNT_MISMATCHED,
      (int32_t)::stellar::CreateWithdrawalRequestResultCode::BALANCE_LOCK_OVERFLOW,
      (int32_t)::stellar::CreateWithdrawalRequestResultCode::UNDERFUNDED,
      (int32_t)::stellar::CreateWithdrawalRequestResultCode::INVALID_UNIVERSAL_AMOUNT,
      (int32_t)::stellar::CreateWithdrawalRequestResultCode::STATS_OVERFLOW,
      (int32_t)::stellar::CreateWithdrawalRequestResultCode::LIMITS_EXCEEDED,
      (int32_t)::stellar::CreateWithdrawalRequestResultCode::INVALID_PRE_CONFIRMATION_DETAILS,
      (int32_t)::stellar::CreateWithdrawalRequestResultCode::LOWER_BOUND_NOT_EXCEEDED,
      (int32_t)::stellar::CreateWithdrawalRequestResultCode::WITHDRAWAL_TASKS_NOT_FOUND,
      (int32_t)::stellar::CreateWithdrawalRequestResultCode::NOT_ALLOWED_TO_SET_WITHDRAWAL_TASKS,
      (int32_t)::stellar::CreateWithdrawalRequestResultCode::WITHDRAWAL_ZERO_TASKS_NOT_ALLOWED
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateWithdrawalSuccess {
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

  uint64 requestID{};
  bool fulfilled{};
  _ext_t ext{};

  CreateWithdrawalSuccess() = default;
  template<typename _requestID_T,
           typename _fulfilled_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<bool, _fulfilled_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateWithdrawalSuccess(_requestID_T &&_requestID,
                                   _fulfilled_T &&_fulfilled,
                                   _ext_T &&_ext)
    : requestID(std::forward<_requestID_T>(_requestID)),
      fulfilled(std::forward<_fulfilled_T>(_fulfilled)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateWithdrawalSuccess::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CreateWithdrawalSuccess::_ext_t;
  using case_type = ::stellar::CreateWithdrawalSuccess::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::CreateWithdrawalSuccess::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateWithdrawalSuccess::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateWithdrawalSuccess::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::CreateWithdrawalSuccess>
  : xdr_struct_base<field_ptr<::stellar::CreateWithdrawalSuccess,
                              decltype(::stellar::CreateWithdrawalSuccess::requestID),
                              &::stellar::CreateWithdrawalSuccess::requestID>,
                    field_ptr<::stellar::CreateWithdrawalSuccess,
                              decltype(::stellar::CreateWithdrawalSuccess::fulfilled),
                              &::stellar::CreateWithdrawalSuccess::fulfilled>,
                    field_ptr<::stellar::CreateWithdrawalSuccess,
                              decltype(::stellar::CreateWithdrawalSuccess::ext),
                              &::stellar::CreateWithdrawalSuccess::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateWithdrawalSuccess &obj) {
    archive(ar, obj.requestID, "requestID");
    archive(ar, obj.fulfilled, "fulfilled");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateWithdrawalSuccess &obj) {
    archive(ar, obj.requestID, "requestID");
    archive(ar, obj.fulfilled, "fulfilled");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct CreateWithdrawalRequestResult {
  using _xdr_case_type = xdr::xdr_traits<CreateWithdrawalRequestResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    CreateWithdrawalSuccess success_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = true;
  static const std::vector<CreateWithdrawalRequestResultCode> &_xdr_case_values() {
    static const std::vector<CreateWithdrawalRequestResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)CreateWithdrawalRequestResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)CreateWithdrawalRequestResultCode::SUCCESS:
      _f(&CreateWithdrawalRequestResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in CreateWithdrawalRequestResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~CreateWithdrawalRequestResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit CreateWithdrawalRequestResult(CreateWithdrawalRequestResultCode which = CreateWithdrawalRequestResultCode{}) : code_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  CreateWithdrawalRequestResult(const CreateWithdrawalRequestResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  CreateWithdrawalRequestResult(CreateWithdrawalRequestResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~CreateWithdrawalRequestResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  CreateWithdrawalRequestResult &operator=(const CreateWithdrawalRequestResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~CreateWithdrawalRequestResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  CreateWithdrawalRequestResult &operator=(CreateWithdrawalRequestResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~CreateWithdrawalRequestResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  CreateWithdrawalRequestResultCode code() const { return CreateWithdrawalRequestResultCode(code_); }
  CreateWithdrawalRequestResult &code(CreateWithdrawalRequestResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  CreateWithdrawalSuccess &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateWithdrawalRequestResult: success accessed when not selected");
  }
  const CreateWithdrawalSuccess &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateWithdrawalRequestResult: success accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateWithdrawalRequestResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CreateWithdrawalRequestResult;
  using case_type = ::stellar::CreateWithdrawalRequestResult::_xdr_case_type;
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

  static std::size_t serial_size(const ::stellar::CreateWithdrawalRequestResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in CreateWithdrawalRequestResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateWithdrawalRequestResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in CreateWithdrawalRequestResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateWithdrawalRequestResult &obj) {
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

#endif // !__XDR_STELLAR_OPERATION_CREATE_WITHDRAWAL_REQUEST_H_INCLUDED__
