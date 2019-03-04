// -*- C++ -*-
// Automatically generated from Stellar-operation-create-preissuance-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_OPERATION_CREATE_PREISSUANCE_REQUEST_H_INCLUDED__
#define __XDR_STELLAR_OPERATION_CREATE_PREISSUANCE_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-ledger-entries.h"

namespace stellar {

struct CreatePreIssuanceRequestOp {
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

  PreIssuanceRequest request{};
  xdr::pointer<uint32> allTasks{};
  _ext_t ext{};

  CreatePreIssuanceRequestOp() = default;
  template<typename _request_T,
           typename _allTasks_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<PreIssuanceRequest, _request_T>::value
                          && std::is_constructible<xdr::pointer<uint32>, _allTasks_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreatePreIssuanceRequestOp(_request_T &&_request,
                                      _allTasks_T &&_allTasks,
                                      _ext_T &&_ext)
    : request(std::forward<_request_T>(_request)),
      allTasks(std::forward<_allTasks_T>(_allTasks)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreatePreIssuanceRequestOp::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CreatePreIssuanceRequestOp::_ext_t;
  using case_type = ::stellar::CreatePreIssuanceRequestOp::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::CreatePreIssuanceRequestOp::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreatePreIssuanceRequestOp::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreatePreIssuanceRequestOp::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::CreatePreIssuanceRequestOp>
  : xdr_struct_base<field_ptr<::stellar::CreatePreIssuanceRequestOp,
                              decltype(::stellar::CreatePreIssuanceRequestOp::request),
                              &::stellar::CreatePreIssuanceRequestOp::request>,
                    field_ptr<::stellar::CreatePreIssuanceRequestOp,
                              decltype(::stellar::CreatePreIssuanceRequestOp::allTasks),
                              &::stellar::CreatePreIssuanceRequestOp::allTasks>,
                    field_ptr<::stellar::CreatePreIssuanceRequestOp,
                              decltype(::stellar::CreatePreIssuanceRequestOp::ext),
                              &::stellar::CreatePreIssuanceRequestOp::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreatePreIssuanceRequestOp &obj) {
    archive(ar, obj.request, "request");
    archive(ar, obj.allTasks, "allTasks");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreatePreIssuanceRequestOp &obj) {
    archive(ar, obj.request, "request");
    archive(ar, obj.allTasks, "allTasks");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum class CreatePreIssuanceRequestResultCode : std::int32_t {
  SUCCESS = 0,
  ASSET_NOT_FOUND = -1,
  REFERENCE_DUPLICATION = -2,
  NOT_AUTHORIZED_UPLOAD = -3,
  INVALID_SIGNATURE = -4,
  EXCEEDED_MAX_AMOUNT = -5,
  INVALID_AMOUNT = -6,
  INVALID_REFERENCE = -7,
  INCORRECT_AMOUNT_PRECISION = -8,
  PREISSUANCE_TASKS_NOT_FOUND = -9,
  INVALID_CREATOR_DETAILS = -10,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreatePreIssuanceRequestResultCode>
  : xdr_integral_base<::stellar::CreatePreIssuanceRequestResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::CreatePreIssuanceRequestResultCode val) {
    switch (val) {
    case ::stellar::CreatePreIssuanceRequestResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::CreatePreIssuanceRequestResultCode::ASSET_NOT_FOUND:
      return "ASSET_NOT_FOUND";
    case ::stellar::CreatePreIssuanceRequestResultCode::REFERENCE_DUPLICATION:
      return "REFERENCE_DUPLICATION";
    case ::stellar::CreatePreIssuanceRequestResultCode::NOT_AUTHORIZED_UPLOAD:
      return "NOT_AUTHORIZED_UPLOAD";
    case ::stellar::CreatePreIssuanceRequestResultCode::INVALID_SIGNATURE:
      return "INVALID_SIGNATURE";
    case ::stellar::CreatePreIssuanceRequestResultCode::EXCEEDED_MAX_AMOUNT:
      return "EXCEEDED_MAX_AMOUNT";
    case ::stellar::CreatePreIssuanceRequestResultCode::INVALID_AMOUNT:
      return "INVALID_AMOUNT";
    case ::stellar::CreatePreIssuanceRequestResultCode::INVALID_REFERENCE:
      return "INVALID_REFERENCE";
    case ::stellar::CreatePreIssuanceRequestResultCode::INCORRECT_AMOUNT_PRECISION:
      return "INCORRECT_AMOUNT_PRECISION";
    case ::stellar::CreatePreIssuanceRequestResultCode::PREISSUANCE_TASKS_NOT_FOUND:
      return "PREISSUANCE_TASKS_NOT_FOUND";
    case ::stellar::CreatePreIssuanceRequestResultCode::INVALID_CREATOR_DETAILS:
      return "INVALID_CREATOR_DETAILS";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::CreatePreIssuanceRequestResultCode::SUCCESS,
      (int32_t)::stellar::CreatePreIssuanceRequestResultCode::ASSET_NOT_FOUND,
      (int32_t)::stellar::CreatePreIssuanceRequestResultCode::REFERENCE_DUPLICATION,
      (int32_t)::stellar::CreatePreIssuanceRequestResultCode::NOT_AUTHORIZED_UPLOAD,
      (int32_t)::stellar::CreatePreIssuanceRequestResultCode::INVALID_SIGNATURE,
      (int32_t)::stellar::CreatePreIssuanceRequestResultCode::EXCEEDED_MAX_AMOUNT,
      (int32_t)::stellar::CreatePreIssuanceRequestResultCode::INVALID_AMOUNT,
      (int32_t)::stellar::CreatePreIssuanceRequestResultCode::INVALID_REFERENCE,
      (int32_t)::stellar::CreatePreIssuanceRequestResultCode::INCORRECT_AMOUNT_PRECISION,
      (int32_t)::stellar::CreatePreIssuanceRequestResultCode::PREISSUANCE_TASKS_NOT_FOUND,
      (int32_t)::stellar::CreatePreIssuanceRequestResultCode::INVALID_CREATOR_DETAILS
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreatePreIssuanceRequestResult {
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

    uint64 requestID{};
    bool fulfilled{};
    _ext_t ext{};

    _success_t() = default;
    template<typename _requestID_T,
             typename _fulfilled_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                            && std::is_constructible<bool, _fulfilled_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _success_t(_requestID_T &&_requestID,
                        _fulfilled_T &&_fulfilled,
                        _ext_T &&_ext)
      : requestID(std::forward<_requestID_T>(_requestID)),
        fulfilled(std::forward<_fulfilled_T>(_fulfilled)),
        ext(std::forward<_ext_T>(_ext)) {}
  };

  using _xdr_case_type = xdr::xdr_traits<CreatePreIssuanceRequestResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    _success_t success_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = true;
  static const std::vector<CreatePreIssuanceRequestResultCode> &_xdr_case_values() {
    static const std::vector<CreatePreIssuanceRequestResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)CreatePreIssuanceRequestResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)CreatePreIssuanceRequestResultCode::SUCCESS:
      _f(&CreatePreIssuanceRequestResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in CreatePreIssuanceRequestResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~CreatePreIssuanceRequestResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit CreatePreIssuanceRequestResult(CreatePreIssuanceRequestResultCode which = CreatePreIssuanceRequestResultCode{}) : code_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  CreatePreIssuanceRequestResult(const CreatePreIssuanceRequestResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  CreatePreIssuanceRequestResult(CreatePreIssuanceRequestResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~CreatePreIssuanceRequestResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  CreatePreIssuanceRequestResult &operator=(const CreatePreIssuanceRequestResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~CreatePreIssuanceRequestResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  CreatePreIssuanceRequestResult &operator=(CreatePreIssuanceRequestResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~CreatePreIssuanceRequestResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  CreatePreIssuanceRequestResultCode code() const { return CreatePreIssuanceRequestResultCode(code_); }
  CreatePreIssuanceRequestResult &code(CreatePreIssuanceRequestResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  _success_t &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreatePreIssuanceRequestResult: success accessed when not selected");
  }
  const _success_t &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreatePreIssuanceRequestResult: success accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreatePreIssuanceRequestResult::_success_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CreatePreIssuanceRequestResult::_success_t::_ext_t;
  using case_type = ::stellar::CreatePreIssuanceRequestResult::_success_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::CreatePreIssuanceRequestResult::_success_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreatePreIssuanceRequestResult::_success_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreatePreIssuanceRequestResult::_success_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::CreatePreIssuanceRequestResult::_success_t>
  : xdr_struct_base<field_ptr<::stellar::CreatePreIssuanceRequestResult::_success_t,
                              decltype(::stellar::CreatePreIssuanceRequestResult::_success_t::requestID),
                              &::stellar::CreatePreIssuanceRequestResult::_success_t::requestID>,
                    field_ptr<::stellar::CreatePreIssuanceRequestResult::_success_t,
                              decltype(::stellar::CreatePreIssuanceRequestResult::_success_t::fulfilled),
                              &::stellar::CreatePreIssuanceRequestResult::_success_t::fulfilled>,
                    field_ptr<::stellar::CreatePreIssuanceRequestResult::_success_t,
                              decltype(::stellar::CreatePreIssuanceRequestResult::_success_t::ext),
                              &::stellar::CreatePreIssuanceRequestResult::_success_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreatePreIssuanceRequestResult::_success_t &obj) {
    archive(ar, obj.requestID, "requestID");
    archive(ar, obj.fulfilled, "fulfilled");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreatePreIssuanceRequestResult::_success_t &obj) {
    archive(ar, obj.requestID, "requestID");
    archive(ar, obj.fulfilled, "fulfilled");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::CreatePreIssuanceRequestResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CreatePreIssuanceRequestResult;
  using case_type = ::stellar::CreatePreIssuanceRequestResult::_xdr_case_type;
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

  static std::size_t serial_size(const ::stellar::CreatePreIssuanceRequestResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in CreatePreIssuanceRequestResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreatePreIssuanceRequestResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in CreatePreIssuanceRequestResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreatePreIssuanceRequestResult &obj) {
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

#endif // !__XDR_STELLAR_OPERATION_CREATE_PREISSUANCE_REQUEST_H_INCLUDED__
