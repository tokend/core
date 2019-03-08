// -*- C++ -*-
// Automatically generated from Stellar-operation-create-aswap-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_OPERATION_CREATE_ASWAP_REQUEST_H_INCLUDED__
#define __XDR_STELLAR_OPERATION_CREATE_ASWAP_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-ledger-entries.h"
#include "xdr/Stellar-reviewable-request-atomic-swap.h"

namespace stellar {

struct CreateASwapRequestOp {
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

  ASwapRequest request{};
  _ext_t ext{};

  CreateASwapRequestOp() = default;
  template<typename _request_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<ASwapRequest, _request_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateASwapRequestOp(_request_T &&_request,
                                _ext_T &&_ext)
    : request(std::forward<_request_T>(_request)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateASwapRequestOp::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CreateASwapRequestOp::_ext_t;
  using case_type = ::stellar::CreateASwapRequestOp::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::CreateASwapRequestOp::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateASwapRequestOp::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateASwapRequestOp::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::CreateASwapRequestOp>
  : xdr_struct_base<field_ptr<::stellar::CreateASwapRequestOp,
                              decltype(::stellar::CreateASwapRequestOp::request),
                              &::stellar::CreateASwapRequestOp::request>,
                    field_ptr<::stellar::CreateASwapRequestOp,
                              decltype(::stellar::CreateASwapRequestOp::ext),
                              &::stellar::CreateASwapRequestOp::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateASwapRequestOp &obj) {
    archive(ar, obj.request, "request");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateASwapRequestOp &obj) {
    archive(ar, obj.request, "request");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum class CreateASwapRequestResultCode : std::int32_t {
  SUCCESS = 0,
  INVALID_BASE_AMOUNT = -1,
  INVALID_QUOTE_ASSET = -2,
  BID_NOT_FOUND = -3,
  QUOTE_ASSET_NOT_FOUND = -4,
  BID_UNDERFUNDED = -5,
  ATOMIC_SWAP_TASKS_NOT_FOUND = -6,
  NOT_ALLOWED_BY_ASSET_POLICY = -7,
  BID_IS_CANCELLED = -8,
  CANNOT_CREATE_ASWAP_REQUEST_FOR_OWN_BID = -9,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateASwapRequestResultCode>
  : xdr_integral_base<::stellar::CreateASwapRequestResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::CreateASwapRequestResultCode val) {
    switch (val) {
    case ::stellar::CreateASwapRequestResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::CreateASwapRequestResultCode::INVALID_BASE_AMOUNT:
      return "INVALID_BASE_AMOUNT";
    case ::stellar::CreateASwapRequestResultCode::INVALID_QUOTE_ASSET:
      return "INVALID_QUOTE_ASSET";
    case ::stellar::CreateASwapRequestResultCode::BID_NOT_FOUND:
      return "BID_NOT_FOUND";
    case ::stellar::CreateASwapRequestResultCode::QUOTE_ASSET_NOT_FOUND:
      return "QUOTE_ASSET_NOT_FOUND";
    case ::stellar::CreateASwapRequestResultCode::BID_UNDERFUNDED:
      return "BID_UNDERFUNDED";
    case ::stellar::CreateASwapRequestResultCode::ATOMIC_SWAP_TASKS_NOT_FOUND:
      return "ATOMIC_SWAP_TASKS_NOT_FOUND";
    case ::stellar::CreateASwapRequestResultCode::NOT_ALLOWED_BY_ASSET_POLICY:
      return "NOT_ALLOWED_BY_ASSET_POLICY";
    case ::stellar::CreateASwapRequestResultCode::BID_IS_CANCELLED:
      return "BID_IS_CANCELLED";
    case ::stellar::CreateASwapRequestResultCode::CANNOT_CREATE_ASWAP_REQUEST_FOR_OWN_BID:
      return "CANNOT_CREATE_ASWAP_REQUEST_FOR_OWN_BID";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::CreateASwapRequestResultCode::SUCCESS,
      (int32_t)::stellar::CreateASwapRequestResultCode::INVALID_BASE_AMOUNT,
      (int32_t)::stellar::CreateASwapRequestResultCode::INVALID_QUOTE_ASSET,
      (int32_t)::stellar::CreateASwapRequestResultCode::BID_NOT_FOUND,
      (int32_t)::stellar::CreateASwapRequestResultCode::QUOTE_ASSET_NOT_FOUND,
      (int32_t)::stellar::CreateASwapRequestResultCode::BID_UNDERFUNDED,
      (int32_t)::stellar::CreateASwapRequestResultCode::ATOMIC_SWAP_TASKS_NOT_FOUND,
      (int32_t)::stellar::CreateASwapRequestResultCode::NOT_ALLOWED_BY_ASSET_POLICY,
      (int32_t)::stellar::CreateASwapRequestResultCode::BID_IS_CANCELLED,
      (int32_t)::stellar::CreateASwapRequestResultCode::CANNOT_CREATE_ASWAP_REQUEST_FOR_OWN_BID
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateASwapRequestSuccess {
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
  AccountID bidOwnerID{};
  _ext_t ext{};

  CreateASwapRequestSuccess() = default;
  template<typename _requestID_T,
           typename _bidOwnerID_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<AccountID, _bidOwnerID_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateASwapRequestSuccess(_requestID_T &&_requestID,
                                     _bidOwnerID_T &&_bidOwnerID,
                                     _ext_T &&_ext)
    : requestID(std::forward<_requestID_T>(_requestID)),
      bidOwnerID(std::forward<_bidOwnerID_T>(_bidOwnerID)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateASwapRequestSuccess::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CreateASwapRequestSuccess::_ext_t;
  using case_type = ::stellar::CreateASwapRequestSuccess::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::CreateASwapRequestSuccess::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateASwapRequestSuccess::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateASwapRequestSuccess::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::CreateASwapRequestSuccess>
  : xdr_struct_base<field_ptr<::stellar::CreateASwapRequestSuccess,
                              decltype(::stellar::CreateASwapRequestSuccess::requestID),
                              &::stellar::CreateASwapRequestSuccess::requestID>,
                    field_ptr<::stellar::CreateASwapRequestSuccess,
                              decltype(::stellar::CreateASwapRequestSuccess::bidOwnerID),
                              &::stellar::CreateASwapRequestSuccess::bidOwnerID>,
                    field_ptr<::stellar::CreateASwapRequestSuccess,
                              decltype(::stellar::CreateASwapRequestSuccess::ext),
                              &::stellar::CreateASwapRequestSuccess::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateASwapRequestSuccess &obj) {
    archive(ar, obj.requestID, "requestID");
    archive(ar, obj.bidOwnerID, "bidOwnerID");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateASwapRequestSuccess &obj) {
    archive(ar, obj.requestID, "requestID");
    archive(ar, obj.bidOwnerID, "bidOwnerID");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct CreateASwapRequestResult {
  using _xdr_case_type = xdr::xdr_traits<CreateASwapRequestResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    CreateASwapRequestSuccess success_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = true;
  static const std::vector<CreateASwapRequestResultCode> &_xdr_case_values() {
    static const std::vector<CreateASwapRequestResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)CreateASwapRequestResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)CreateASwapRequestResultCode::SUCCESS:
      _f(&CreateASwapRequestResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in CreateASwapRequestResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~CreateASwapRequestResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit CreateASwapRequestResult(CreateASwapRequestResultCode which = CreateASwapRequestResultCode{}) : code_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  CreateASwapRequestResult(const CreateASwapRequestResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  CreateASwapRequestResult(CreateASwapRequestResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~CreateASwapRequestResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  CreateASwapRequestResult &operator=(const CreateASwapRequestResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~CreateASwapRequestResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  CreateASwapRequestResult &operator=(CreateASwapRequestResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~CreateASwapRequestResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  CreateASwapRequestResultCode code() const { return CreateASwapRequestResultCode(code_); }
  CreateASwapRequestResult &code(CreateASwapRequestResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  CreateASwapRequestSuccess &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateASwapRequestResult: success accessed when not selected");
  }
  const CreateASwapRequestSuccess &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateASwapRequestResult: success accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateASwapRequestResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CreateASwapRequestResult;
  using case_type = ::stellar::CreateASwapRequestResult::_xdr_case_type;
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

  static std::size_t serial_size(const ::stellar::CreateASwapRequestResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in CreateASwapRequestResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateASwapRequestResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in CreateASwapRequestResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateASwapRequestResult &obj) {
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

#endif // !__XDR_STELLAR_OPERATION_CREATE_ASWAP_REQUEST_H_INCLUDED__
