// -*- C++ -*-
// Automatically generated from Stellar-operation-create-sale-creation-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_OPERATION_CREATE_SALE_CREATION_REQUEST_H_INCLUDED__
#define __XDR_STELLAR_OPERATION_CREATE_SALE_CREATION_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-ledger-entries.h"
#include "xdr/Stellar-operation-review-request.h"

namespace stellar {

struct CreateSaleCreationRequestOp {
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
  SaleCreationRequest request{};
  xdr::pointer<uint32> allTasks{};
  _ext_t ext{};

  CreateSaleCreationRequestOp() = default;
  template<typename _requestID_T,
           typename _request_T,
           typename _allTasks_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<SaleCreationRequest, _request_T>::value
                          && std::is_constructible<xdr::pointer<uint32>, _allTasks_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateSaleCreationRequestOp(_requestID_T &&_requestID,
                                       _request_T &&_request,
                                       _allTasks_T &&_allTasks,
                                       _ext_T &&_ext)
    : requestID(std::forward<_requestID_T>(_requestID)),
      request(std::forward<_request_T>(_request)),
      allTasks(std::forward<_allTasks_T>(_allTasks)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateSaleCreationRequestOp::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CreateSaleCreationRequestOp::_ext_t;
  using case_type = ::stellar::CreateSaleCreationRequestOp::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::CreateSaleCreationRequestOp::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateSaleCreationRequestOp::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateSaleCreationRequestOp::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::CreateSaleCreationRequestOp>
  : xdr_struct_base<field_ptr<::stellar::CreateSaleCreationRequestOp,
                              decltype(::stellar::CreateSaleCreationRequestOp::requestID),
                              &::stellar::CreateSaleCreationRequestOp::requestID>,
                    field_ptr<::stellar::CreateSaleCreationRequestOp,
                              decltype(::stellar::CreateSaleCreationRequestOp::request),
                              &::stellar::CreateSaleCreationRequestOp::request>,
                    field_ptr<::stellar::CreateSaleCreationRequestOp,
                              decltype(::stellar::CreateSaleCreationRequestOp::allTasks),
                              &::stellar::CreateSaleCreationRequestOp::allTasks>,
                    field_ptr<::stellar::CreateSaleCreationRequestOp,
                              decltype(::stellar::CreateSaleCreationRequestOp::ext),
                              &::stellar::CreateSaleCreationRequestOp::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateSaleCreationRequestOp &obj) {
    archive(ar, obj.requestID, "requestID");
    archive(ar, obj.request, "request");
    archive(ar, obj.allTasks, "allTasks");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateSaleCreationRequestOp &obj) {
    archive(ar, obj.requestID, "requestID");
    archive(ar, obj.request, "request");
    archive(ar, obj.allTasks, "allTasks");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum class CreateSaleCreationRequestResultCode : std::int32_t {
  SUCCESS = 0,
  REQUEST_NOT_FOUND = -1,
  BASE_ASSET_OR_ASSET_REQUEST_NOT_FOUND = -2,
  QUOTE_ASSET_NOT_FOUND = -3,
  START_END_INVALID = -4,
  INVALID_END = -5,
  INVALID_PRICE = -6,
  INVALID_CAP = -7,
  INSUFFICIENT_MAX_ISSUANCE = -8,
  INVALID_ASSET_PAIR = -9,
  REQUEST_OR_SALE_ALREADY_EXISTS = -10,
  INSUFFICIENT_PREISSUED = -11,
  INVALID_CREATOR_DETAILS = -12,
  VERSION_IS_NOT_SUPPORTED_YET = -13,
  SALE_CREATE_TASKS_NOT_FOUND = -14,
  NOT_ALLOWED_TO_SET_TASKS_ON_UPDATE = -15,
  AUTO_REVIEW_FAILED = -16,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateSaleCreationRequestResultCode>
  : xdr_integral_base<::stellar::CreateSaleCreationRequestResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::CreateSaleCreationRequestResultCode val) {
    switch (val) {
    case ::stellar::CreateSaleCreationRequestResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::CreateSaleCreationRequestResultCode::REQUEST_NOT_FOUND:
      return "REQUEST_NOT_FOUND";
    case ::stellar::CreateSaleCreationRequestResultCode::BASE_ASSET_OR_ASSET_REQUEST_NOT_FOUND:
      return "BASE_ASSET_OR_ASSET_REQUEST_NOT_FOUND";
    case ::stellar::CreateSaleCreationRequestResultCode::QUOTE_ASSET_NOT_FOUND:
      return "QUOTE_ASSET_NOT_FOUND";
    case ::stellar::CreateSaleCreationRequestResultCode::START_END_INVALID:
      return "START_END_INVALID";
    case ::stellar::CreateSaleCreationRequestResultCode::INVALID_END:
      return "INVALID_END";
    case ::stellar::CreateSaleCreationRequestResultCode::INVALID_PRICE:
      return "INVALID_PRICE";
    case ::stellar::CreateSaleCreationRequestResultCode::INVALID_CAP:
      return "INVALID_CAP";
    case ::stellar::CreateSaleCreationRequestResultCode::INSUFFICIENT_MAX_ISSUANCE:
      return "INSUFFICIENT_MAX_ISSUANCE";
    case ::stellar::CreateSaleCreationRequestResultCode::INVALID_ASSET_PAIR:
      return "INVALID_ASSET_PAIR";
    case ::stellar::CreateSaleCreationRequestResultCode::REQUEST_OR_SALE_ALREADY_EXISTS:
      return "REQUEST_OR_SALE_ALREADY_EXISTS";
    case ::stellar::CreateSaleCreationRequestResultCode::INSUFFICIENT_PREISSUED:
      return "INSUFFICIENT_PREISSUED";
    case ::stellar::CreateSaleCreationRequestResultCode::INVALID_CREATOR_DETAILS:
      return "INVALID_CREATOR_DETAILS";
    case ::stellar::CreateSaleCreationRequestResultCode::VERSION_IS_NOT_SUPPORTED_YET:
      return "VERSION_IS_NOT_SUPPORTED_YET";
    case ::stellar::CreateSaleCreationRequestResultCode::SALE_CREATE_TASKS_NOT_FOUND:
      return "SALE_CREATE_TASKS_NOT_FOUND";
    case ::stellar::CreateSaleCreationRequestResultCode::NOT_ALLOWED_TO_SET_TASKS_ON_UPDATE:
      return "NOT_ALLOWED_TO_SET_TASKS_ON_UPDATE";
    case ::stellar::CreateSaleCreationRequestResultCode::AUTO_REVIEW_FAILED:
      return "AUTO_REVIEW_FAILED";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::SUCCESS,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::REQUEST_NOT_FOUND,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::BASE_ASSET_OR_ASSET_REQUEST_NOT_FOUND,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::QUOTE_ASSET_NOT_FOUND,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::START_END_INVALID,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::INVALID_END,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::INVALID_PRICE,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::INVALID_CAP,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::INSUFFICIENT_MAX_ISSUANCE,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::INVALID_ASSET_PAIR,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::REQUEST_OR_SALE_ALREADY_EXISTS,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::INSUFFICIENT_PREISSUED,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::INVALID_CREATOR_DETAILS,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::VERSION_IS_NOT_SUPPORTED_YET,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::SALE_CREATE_TASKS_NOT_FOUND,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::NOT_ALLOWED_TO_SET_TASKS_ON_UPDATE,
      (int32_t)::stellar::CreateSaleCreationRequestResultCode::AUTO_REVIEW_FAILED
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateSaleCreationSuccess {
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
  uint64 saleID{};
  bool fulfilled{};
  _ext_t ext{};

  CreateSaleCreationSuccess() = default;
  template<typename _requestID_T,
           typename _saleID_T,
           typename _fulfilled_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<uint64, _saleID_T>::value
                          && std::is_constructible<bool, _fulfilled_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateSaleCreationSuccess(_requestID_T &&_requestID,
                                     _saleID_T &&_saleID,
                                     _fulfilled_T &&_fulfilled,
                                     _ext_T &&_ext)
    : requestID(std::forward<_requestID_T>(_requestID)),
      saleID(std::forward<_saleID_T>(_saleID)),
      fulfilled(std::forward<_fulfilled_T>(_fulfilled)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateSaleCreationSuccess::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CreateSaleCreationSuccess::_ext_t;
  using case_type = ::stellar::CreateSaleCreationSuccess::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::CreateSaleCreationSuccess::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateSaleCreationSuccess::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateSaleCreationSuccess::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::CreateSaleCreationSuccess>
  : xdr_struct_base<field_ptr<::stellar::CreateSaleCreationSuccess,
                              decltype(::stellar::CreateSaleCreationSuccess::requestID),
                              &::stellar::CreateSaleCreationSuccess::requestID>,
                    field_ptr<::stellar::CreateSaleCreationSuccess,
                              decltype(::stellar::CreateSaleCreationSuccess::saleID),
                              &::stellar::CreateSaleCreationSuccess::saleID>,
                    field_ptr<::stellar::CreateSaleCreationSuccess,
                              decltype(::stellar::CreateSaleCreationSuccess::fulfilled),
                              &::stellar::CreateSaleCreationSuccess::fulfilled>,
                    field_ptr<::stellar::CreateSaleCreationSuccess,
                              decltype(::stellar::CreateSaleCreationSuccess::ext),
                              &::stellar::CreateSaleCreationSuccess::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateSaleCreationSuccess &obj) {
    archive(ar, obj.requestID, "requestID");
    archive(ar, obj.saleID, "saleID");
    archive(ar, obj.fulfilled, "fulfilled");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateSaleCreationSuccess &obj) {
    archive(ar, obj.requestID, "requestID");
    archive(ar, obj.saleID, "saleID");
    archive(ar, obj.fulfilled, "fulfilled");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct CreateSaleCreationAutoReviewFailed {
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

  ReviewRequestResult reviewRequestRequest{};
  _ext_t ext{};

  CreateSaleCreationAutoReviewFailed() = default;
  template<typename _reviewRequestRequest_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<ReviewRequestResult, _reviewRequestRequest_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateSaleCreationAutoReviewFailed(_reviewRequestRequest_T &&_reviewRequestRequest,
                                              _ext_T &&_ext)
    : reviewRequestRequest(std::forward<_reviewRequestRequest_T>(_reviewRequestRequest)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateSaleCreationAutoReviewFailed::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CreateSaleCreationAutoReviewFailed::_ext_t;
  using case_type = ::stellar::CreateSaleCreationAutoReviewFailed::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::CreateSaleCreationAutoReviewFailed::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateSaleCreationAutoReviewFailed::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateSaleCreationAutoReviewFailed::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::CreateSaleCreationAutoReviewFailed>
  : xdr_struct_base<field_ptr<::stellar::CreateSaleCreationAutoReviewFailed,
                              decltype(::stellar::CreateSaleCreationAutoReviewFailed::reviewRequestRequest),
                              &::stellar::CreateSaleCreationAutoReviewFailed::reviewRequestRequest>,
                    field_ptr<::stellar::CreateSaleCreationAutoReviewFailed,
                              decltype(::stellar::CreateSaleCreationAutoReviewFailed::ext),
                              &::stellar::CreateSaleCreationAutoReviewFailed::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateSaleCreationAutoReviewFailed &obj) {
    archive(ar, obj.reviewRequestRequest, "reviewRequestRequest");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateSaleCreationAutoReviewFailed &obj) {
    archive(ar, obj.reviewRequestRequest, "reviewRequestRequest");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct CreateSaleCreationRequestResult {
  using _xdr_case_type = xdr::xdr_traits<CreateSaleCreationRequestResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    CreateSaleCreationSuccess success_;
    CreateSaleCreationAutoReviewFailed autoReviewFailed_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = true;
  static const std::vector<CreateSaleCreationRequestResultCode> &_xdr_case_values() {
    static const std::vector<CreateSaleCreationRequestResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)CreateSaleCreationRequestResultCode::SUCCESS ? 1
      : which == (int32_t)CreateSaleCreationRequestResultCode::AUTO_REVIEW_FAILED ? 2
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)CreateSaleCreationRequestResultCode::SUCCESS:
      _f(&CreateSaleCreationRequestResult::success_, std::forward<_A>(_a)...);
      return true;
    case (int32_t)CreateSaleCreationRequestResultCode::AUTO_REVIEW_FAILED:
      _f(&CreateSaleCreationRequestResult::autoReviewFailed_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in CreateSaleCreationRequestResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~CreateSaleCreationRequestResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit CreateSaleCreationRequestResult(CreateSaleCreationRequestResultCode which = CreateSaleCreationRequestResultCode{}) : code_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  CreateSaleCreationRequestResult(const CreateSaleCreationRequestResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  CreateSaleCreationRequestResult(CreateSaleCreationRequestResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~CreateSaleCreationRequestResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  CreateSaleCreationRequestResult &operator=(const CreateSaleCreationRequestResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~CreateSaleCreationRequestResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  CreateSaleCreationRequestResult &operator=(CreateSaleCreationRequestResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~CreateSaleCreationRequestResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  CreateSaleCreationRequestResultCode code() const { return CreateSaleCreationRequestResultCode(code_); }
  CreateSaleCreationRequestResult &code(CreateSaleCreationRequestResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  CreateSaleCreationSuccess &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateSaleCreationRequestResult: success accessed when not selected");
  }
  const CreateSaleCreationSuccess &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateSaleCreationRequestResult: success accessed when not selected");
  }
  CreateSaleCreationAutoReviewFailed &autoReviewFailed() {
    if (_xdr_field_number(code_) == 2)
      return autoReviewFailed_;
    throw xdr::xdr_wrong_union("CreateSaleCreationRequestResult: autoReviewFailed accessed when not selected");
  }
  const CreateSaleCreationAutoReviewFailed &autoReviewFailed() const {
    if (_xdr_field_number(code_) == 2)
      return autoReviewFailed_;
    throw xdr::xdr_wrong_union("CreateSaleCreationRequestResult: autoReviewFailed accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateSaleCreationRequestResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CreateSaleCreationRequestResult;
  using case_type = ::stellar::CreateSaleCreationRequestResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "success";
    case 2:
      return "autoReviewFailed";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::CreateSaleCreationRequestResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in CreateSaleCreationRequestResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateSaleCreationRequestResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in CreateSaleCreationRequestResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateSaleCreationRequestResult &obj) {
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

#endif // !__XDR_STELLAR_OPERATION_CREATE_SALE_CREATION_REQUEST_H_INCLUDED__
