// -*- C++ -*-
// Automatically generated from Stellar-operation-create-aswap-bid-creation-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_OPERATION_CREATE_ASWAP_BID_CREATION_REQUEST_H_INCLUDED__
#define __XDR_STELLAR_OPERATION_CREATE_ASWAP_BID_CREATION_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-ledger-entries.h"
#include "xdr/Stellar-reviewable-request-atomic-swap-bid.h"

namespace stellar {

struct CreateASwapBidCreationRequestOp {
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

  ASwapBidCreationRequest request{};
  _ext_t ext{};

  CreateASwapBidCreationRequestOp() = default;
  template<typename _request_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<ASwapBidCreationRequest, _request_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateASwapBidCreationRequestOp(_request_T &&_request,
                                           _ext_T &&_ext)
    : request(std::forward<_request_T>(_request)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateASwapBidCreationRequestOp::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CreateASwapBidCreationRequestOp::_ext_t;
  using case_type = ::stellar::CreateASwapBidCreationRequestOp::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::CreateASwapBidCreationRequestOp::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateASwapBidCreationRequestOp::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateASwapBidCreationRequestOp::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::CreateASwapBidCreationRequestOp>
  : xdr_struct_base<field_ptr<::stellar::CreateASwapBidCreationRequestOp,
                              decltype(::stellar::CreateASwapBidCreationRequestOp::request),
                              &::stellar::CreateASwapBidCreationRequestOp::request>,
                    field_ptr<::stellar::CreateASwapBidCreationRequestOp,
                              decltype(::stellar::CreateASwapBidCreationRequestOp::ext),
                              &::stellar::CreateASwapBidCreationRequestOp::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateASwapBidCreationRequestOp &obj) {
    archive(ar, obj.request, "request");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateASwapBidCreationRequestOp &obj) {
    archive(ar, obj.request, "request");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum class CreateASwapBidCreationRequestResultCode : std::int32_t {
  SUCCESS = 0,
  INVALID_AMOUNT = -1,
  INVALID_PRICE = -2,
  INVALID_DETAILS = -3,
  ATOMIC_SWAP_BID_OVERFLOW = -4,
  BASE_ASSET_NOT_FOUND = -5,
  BASE_ASSET_CANNOT_BE_SWAPPED = -6,
  QUOTE_ASSET_NOT_FOUND = -7,
  QUOTE_ASSET_CANNOT_BE_SWAPPED = -8,
  BASE_BALANCE_NOT_FOUND = -9,
  ASSETS_ARE_EQUAL = -10,
  BASE_BALANCE_UNDERFUNDED = -11,
  INVALID_QUOTE_ASSET = -12,
  NOT_ALLOWED_BY_ASSET_POLICY = -13,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateASwapBidCreationRequestResultCode>
  : xdr_integral_base<::stellar::CreateASwapBidCreationRequestResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::CreateASwapBidCreationRequestResultCode val) {
    switch (val) {
    case ::stellar::CreateASwapBidCreationRequestResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::CreateASwapBidCreationRequestResultCode::INVALID_AMOUNT:
      return "INVALID_AMOUNT";
    case ::stellar::CreateASwapBidCreationRequestResultCode::INVALID_PRICE:
      return "INVALID_PRICE";
    case ::stellar::CreateASwapBidCreationRequestResultCode::INVALID_DETAILS:
      return "INVALID_DETAILS";
    case ::stellar::CreateASwapBidCreationRequestResultCode::ATOMIC_SWAP_BID_OVERFLOW:
      return "ATOMIC_SWAP_BID_OVERFLOW";
    case ::stellar::CreateASwapBidCreationRequestResultCode::BASE_ASSET_NOT_FOUND:
      return "BASE_ASSET_NOT_FOUND";
    case ::stellar::CreateASwapBidCreationRequestResultCode::BASE_ASSET_CANNOT_BE_SWAPPED:
      return "BASE_ASSET_CANNOT_BE_SWAPPED";
    case ::stellar::CreateASwapBidCreationRequestResultCode::QUOTE_ASSET_NOT_FOUND:
      return "QUOTE_ASSET_NOT_FOUND";
    case ::stellar::CreateASwapBidCreationRequestResultCode::QUOTE_ASSET_CANNOT_BE_SWAPPED:
      return "QUOTE_ASSET_CANNOT_BE_SWAPPED";
    case ::stellar::CreateASwapBidCreationRequestResultCode::BASE_BALANCE_NOT_FOUND:
      return "BASE_BALANCE_NOT_FOUND";
    case ::stellar::CreateASwapBidCreationRequestResultCode::ASSETS_ARE_EQUAL:
      return "ASSETS_ARE_EQUAL";
    case ::stellar::CreateASwapBidCreationRequestResultCode::BASE_BALANCE_UNDERFUNDED:
      return "BASE_BALANCE_UNDERFUNDED";
    case ::stellar::CreateASwapBidCreationRequestResultCode::INVALID_QUOTE_ASSET:
      return "INVALID_QUOTE_ASSET";
    case ::stellar::CreateASwapBidCreationRequestResultCode::NOT_ALLOWED_BY_ASSET_POLICY:
      return "NOT_ALLOWED_BY_ASSET_POLICY";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::CreateASwapBidCreationRequestResultCode::SUCCESS,
      (int32_t)::stellar::CreateASwapBidCreationRequestResultCode::INVALID_AMOUNT,
      (int32_t)::stellar::CreateASwapBidCreationRequestResultCode::INVALID_PRICE,
      (int32_t)::stellar::CreateASwapBidCreationRequestResultCode::INVALID_DETAILS,
      (int32_t)::stellar::CreateASwapBidCreationRequestResultCode::ATOMIC_SWAP_BID_OVERFLOW,
      (int32_t)::stellar::CreateASwapBidCreationRequestResultCode::BASE_ASSET_NOT_FOUND,
      (int32_t)::stellar::CreateASwapBidCreationRequestResultCode::BASE_ASSET_CANNOT_BE_SWAPPED,
      (int32_t)::stellar::CreateASwapBidCreationRequestResultCode::QUOTE_ASSET_NOT_FOUND,
      (int32_t)::stellar::CreateASwapBidCreationRequestResultCode::QUOTE_ASSET_CANNOT_BE_SWAPPED,
      (int32_t)::stellar::CreateASwapBidCreationRequestResultCode::BASE_BALANCE_NOT_FOUND,
      (int32_t)::stellar::CreateASwapBidCreationRequestResultCode::ASSETS_ARE_EQUAL,
      (int32_t)::stellar::CreateASwapBidCreationRequestResultCode::BASE_BALANCE_UNDERFUNDED,
      (int32_t)::stellar::CreateASwapBidCreationRequestResultCode::INVALID_QUOTE_ASSET,
      (int32_t)::stellar::CreateASwapBidCreationRequestResultCode::NOT_ALLOWED_BY_ASSET_POLICY
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateASwapBidCreationRequestSuccess {
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

  CreateASwapBidCreationRequestSuccess() = default;
  template<typename _requestID_T,
           typename _fulfilled_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<bool, _fulfilled_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateASwapBidCreationRequestSuccess(_requestID_T &&_requestID,
                                                _fulfilled_T &&_fulfilled,
                                                _ext_T &&_ext)
    : requestID(std::forward<_requestID_T>(_requestID)),
      fulfilled(std::forward<_fulfilled_T>(_fulfilled)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateASwapBidCreationRequestSuccess::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CreateASwapBidCreationRequestSuccess::_ext_t;
  using case_type = ::stellar::CreateASwapBidCreationRequestSuccess::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::CreateASwapBidCreationRequestSuccess::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateASwapBidCreationRequestSuccess::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateASwapBidCreationRequestSuccess::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::CreateASwapBidCreationRequestSuccess>
  : xdr_struct_base<field_ptr<::stellar::CreateASwapBidCreationRequestSuccess,
                              decltype(::stellar::CreateASwapBidCreationRequestSuccess::requestID),
                              &::stellar::CreateASwapBidCreationRequestSuccess::requestID>,
                    field_ptr<::stellar::CreateASwapBidCreationRequestSuccess,
                              decltype(::stellar::CreateASwapBidCreationRequestSuccess::fulfilled),
                              &::stellar::CreateASwapBidCreationRequestSuccess::fulfilled>,
                    field_ptr<::stellar::CreateASwapBidCreationRequestSuccess,
                              decltype(::stellar::CreateASwapBidCreationRequestSuccess::ext),
                              &::stellar::CreateASwapBidCreationRequestSuccess::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateASwapBidCreationRequestSuccess &obj) {
    archive(ar, obj.requestID, "requestID");
    archive(ar, obj.fulfilled, "fulfilled");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateASwapBidCreationRequestSuccess &obj) {
    archive(ar, obj.requestID, "requestID");
    archive(ar, obj.fulfilled, "fulfilled");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct CreateASwapBidCreationRequestResult {
  using _xdr_case_type = xdr::xdr_traits<CreateASwapBidCreationRequestResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    CreateASwapBidCreationRequestSuccess success_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = true;
  static const std::vector<CreateASwapBidCreationRequestResultCode> &_xdr_case_values() {
    static const std::vector<CreateASwapBidCreationRequestResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)CreateASwapBidCreationRequestResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)CreateASwapBidCreationRequestResultCode::SUCCESS:
      _f(&CreateASwapBidCreationRequestResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in CreateASwapBidCreationRequestResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~CreateASwapBidCreationRequestResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit CreateASwapBidCreationRequestResult(CreateASwapBidCreationRequestResultCode which = CreateASwapBidCreationRequestResultCode{}) : code_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  CreateASwapBidCreationRequestResult(const CreateASwapBidCreationRequestResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  CreateASwapBidCreationRequestResult(CreateASwapBidCreationRequestResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~CreateASwapBidCreationRequestResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  CreateASwapBidCreationRequestResult &operator=(const CreateASwapBidCreationRequestResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~CreateASwapBidCreationRequestResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  CreateASwapBidCreationRequestResult &operator=(CreateASwapBidCreationRequestResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~CreateASwapBidCreationRequestResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  CreateASwapBidCreationRequestResultCode code() const { return CreateASwapBidCreationRequestResultCode(code_); }
  CreateASwapBidCreationRequestResult &code(CreateASwapBidCreationRequestResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  CreateASwapBidCreationRequestSuccess &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateASwapBidCreationRequestResult: success accessed when not selected");
  }
  const CreateASwapBidCreationRequestSuccess &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateASwapBidCreationRequestResult: success accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateASwapBidCreationRequestResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CreateASwapBidCreationRequestResult;
  using case_type = ::stellar::CreateASwapBidCreationRequestResult::_xdr_case_type;
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

  static std::size_t serial_size(const ::stellar::CreateASwapBidCreationRequestResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in CreateASwapBidCreationRequestResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateASwapBidCreationRequestResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in CreateASwapBidCreationRequestResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateASwapBidCreationRequestResult &obj) {
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

#endif // !__XDR_STELLAR_OPERATION_CREATE_ASWAP_BID_CREATION_REQUEST_H_INCLUDED__
