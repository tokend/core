// -*- C++ -*-
// Automatically generated from Stellar-operation-create-manage-limits-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_OPERATION_CREATE_MANAGE_LIMITS_REQUEST_H_INCLUDED__
#define __XDR_STELLAR_OPERATION_CREATE_MANAGE_LIMITS_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-ledger-entries.h"

namespace stellar {

struct CreateManageLimitsRequestOp {
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

  LimitsUpdateRequest manageLimitsRequest{};
  xdr::pointer<uint32> allTasks{};
  uint64 requestID{};
  _ext_t ext{};

  CreateManageLimitsRequestOp() = default;
  template<typename _manageLimitsRequest_T,
           typename _allTasks_T,
           typename _requestID_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<LimitsUpdateRequest, _manageLimitsRequest_T>::value
                          && std::is_constructible<xdr::pointer<uint32>, _allTasks_T>::value
                          && std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateManageLimitsRequestOp(_manageLimitsRequest_T &&_manageLimitsRequest,
                                       _allTasks_T &&_allTasks,
                                       _requestID_T &&_requestID,
                                       _ext_T &&_ext)
    : manageLimitsRequest(std::forward<_manageLimitsRequest_T>(_manageLimitsRequest)),
      allTasks(std::forward<_allTasks_T>(_allTasks)),
      requestID(std::forward<_requestID_T>(_requestID)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateManageLimitsRequestOp::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CreateManageLimitsRequestOp::_ext_t;
  using case_type = ::stellar::CreateManageLimitsRequestOp::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::CreateManageLimitsRequestOp::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateManageLimitsRequestOp::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateManageLimitsRequestOp::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::CreateManageLimitsRequestOp>
  : xdr_struct_base<field_ptr<::stellar::CreateManageLimitsRequestOp,
                              decltype(::stellar::CreateManageLimitsRequestOp::manageLimitsRequest),
                              &::stellar::CreateManageLimitsRequestOp::manageLimitsRequest>,
                    field_ptr<::stellar::CreateManageLimitsRequestOp,
                              decltype(::stellar::CreateManageLimitsRequestOp::allTasks),
                              &::stellar::CreateManageLimitsRequestOp::allTasks>,
                    field_ptr<::stellar::CreateManageLimitsRequestOp,
                              decltype(::stellar::CreateManageLimitsRequestOp::requestID),
                              &::stellar::CreateManageLimitsRequestOp::requestID>,
                    field_ptr<::stellar::CreateManageLimitsRequestOp,
                              decltype(::stellar::CreateManageLimitsRequestOp::ext),
                              &::stellar::CreateManageLimitsRequestOp::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateManageLimitsRequestOp &obj) {
    archive(ar, obj.manageLimitsRequest, "manageLimitsRequest");
    archive(ar, obj.allTasks, "allTasks");
    archive(ar, obj.requestID, "requestID");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateManageLimitsRequestOp &obj) {
    archive(ar, obj.manageLimitsRequest, "manageLimitsRequest");
    archive(ar, obj.allTasks, "allTasks");
    archive(ar, obj.requestID, "requestID");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum class CreateManageLimitsRequestResultCode : std::int32_t {
  SUCCESS = 0,
  MANAGE_LIMITS_REQUEST_REFERENCE_DUPLICATION = -1,
  MANAGE_LIMITS_REQUEST_NOT_FOUND = -2,
  INVALID_CREATOR_DETAILS = -3,
  LIMITS_UPDATE_TASKS_NOT_FOUND = -5,
  NOT_ALLOWED_TO_SET_TASKS_ON_UPDATE = -6,
  LIMITS_UPDATE_ZERO_TASKS_NOT_ALLOWED = -7,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateManageLimitsRequestResultCode>
  : xdr_integral_base<::stellar::CreateManageLimitsRequestResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::CreateManageLimitsRequestResultCode val) {
    switch (val) {
    case ::stellar::CreateManageLimitsRequestResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::CreateManageLimitsRequestResultCode::MANAGE_LIMITS_REQUEST_REFERENCE_DUPLICATION:
      return "MANAGE_LIMITS_REQUEST_REFERENCE_DUPLICATION";
    case ::stellar::CreateManageLimitsRequestResultCode::MANAGE_LIMITS_REQUEST_NOT_FOUND:
      return "MANAGE_LIMITS_REQUEST_NOT_FOUND";
    case ::stellar::CreateManageLimitsRequestResultCode::INVALID_CREATOR_DETAILS:
      return "INVALID_CREATOR_DETAILS";
    case ::stellar::CreateManageLimitsRequestResultCode::LIMITS_UPDATE_TASKS_NOT_FOUND:
      return "LIMITS_UPDATE_TASKS_NOT_FOUND";
    case ::stellar::CreateManageLimitsRequestResultCode::NOT_ALLOWED_TO_SET_TASKS_ON_UPDATE:
      return "NOT_ALLOWED_TO_SET_TASKS_ON_UPDATE";
    case ::stellar::CreateManageLimitsRequestResultCode::LIMITS_UPDATE_ZERO_TASKS_NOT_ALLOWED:
      return "LIMITS_UPDATE_ZERO_TASKS_NOT_ALLOWED";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::CreateManageLimitsRequestResultCode::SUCCESS,
      (int32_t)::stellar::CreateManageLimitsRequestResultCode::MANAGE_LIMITS_REQUEST_REFERENCE_DUPLICATION,
      (int32_t)::stellar::CreateManageLimitsRequestResultCode::MANAGE_LIMITS_REQUEST_NOT_FOUND,
      (int32_t)::stellar::CreateManageLimitsRequestResultCode::INVALID_CREATOR_DETAILS,
      (int32_t)::stellar::CreateManageLimitsRequestResultCode::LIMITS_UPDATE_TASKS_NOT_FOUND,
      (int32_t)::stellar::CreateManageLimitsRequestResultCode::NOT_ALLOWED_TO_SET_TASKS_ON_UPDATE,
      (int32_t)::stellar::CreateManageLimitsRequestResultCode::LIMITS_UPDATE_ZERO_TASKS_NOT_ALLOWED
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateManageLimitsRequestResult {
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

    uint64 manageLimitsRequestID{};
    bool fulfilled{};
    _ext_t ext{};

    _success_t() = default;
    template<typename _manageLimitsRequestID_T,
             typename _fulfilled_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _manageLimitsRequestID_T>::value
                            && std::is_constructible<bool, _fulfilled_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _success_t(_manageLimitsRequestID_T &&_manageLimitsRequestID,
                        _fulfilled_T &&_fulfilled,
                        _ext_T &&_ext)
      : manageLimitsRequestID(std::forward<_manageLimitsRequestID_T>(_manageLimitsRequestID)),
        fulfilled(std::forward<_fulfilled_T>(_fulfilled)),
        ext(std::forward<_ext_T>(_ext)) {}
  };

  using _xdr_case_type = xdr::xdr_traits<CreateManageLimitsRequestResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    _success_t success_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = true;
  static const std::vector<CreateManageLimitsRequestResultCode> &_xdr_case_values() {
    static const std::vector<CreateManageLimitsRequestResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)CreateManageLimitsRequestResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)CreateManageLimitsRequestResultCode::SUCCESS:
      _f(&CreateManageLimitsRequestResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in CreateManageLimitsRequestResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~CreateManageLimitsRequestResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit CreateManageLimitsRequestResult(CreateManageLimitsRequestResultCode which = CreateManageLimitsRequestResultCode{}) : code_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  CreateManageLimitsRequestResult(const CreateManageLimitsRequestResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  CreateManageLimitsRequestResult(CreateManageLimitsRequestResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~CreateManageLimitsRequestResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  CreateManageLimitsRequestResult &operator=(const CreateManageLimitsRequestResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~CreateManageLimitsRequestResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  CreateManageLimitsRequestResult &operator=(CreateManageLimitsRequestResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~CreateManageLimitsRequestResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  CreateManageLimitsRequestResultCode code() const { return CreateManageLimitsRequestResultCode(code_); }
  CreateManageLimitsRequestResult &code(CreateManageLimitsRequestResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  _success_t &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateManageLimitsRequestResult: success accessed when not selected");
  }
  const _success_t &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateManageLimitsRequestResult: success accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateManageLimitsRequestResult::_success_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CreateManageLimitsRequestResult::_success_t::_ext_t;
  using case_type = ::stellar::CreateManageLimitsRequestResult::_success_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::CreateManageLimitsRequestResult::_success_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateManageLimitsRequestResult::_success_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateManageLimitsRequestResult::_success_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::CreateManageLimitsRequestResult::_success_t>
  : xdr_struct_base<field_ptr<::stellar::CreateManageLimitsRequestResult::_success_t,
                              decltype(::stellar::CreateManageLimitsRequestResult::_success_t::manageLimitsRequestID),
                              &::stellar::CreateManageLimitsRequestResult::_success_t::manageLimitsRequestID>,
                    field_ptr<::stellar::CreateManageLimitsRequestResult::_success_t,
                              decltype(::stellar::CreateManageLimitsRequestResult::_success_t::fulfilled),
                              &::stellar::CreateManageLimitsRequestResult::_success_t::fulfilled>,
                    field_ptr<::stellar::CreateManageLimitsRequestResult::_success_t,
                              decltype(::stellar::CreateManageLimitsRequestResult::_success_t::ext),
                              &::stellar::CreateManageLimitsRequestResult::_success_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateManageLimitsRequestResult::_success_t &obj) {
    archive(ar, obj.manageLimitsRequestID, "manageLimitsRequestID");
    archive(ar, obj.fulfilled, "fulfilled");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateManageLimitsRequestResult::_success_t &obj) {
    archive(ar, obj.manageLimitsRequestID, "manageLimitsRequestID");
    archive(ar, obj.fulfilled, "fulfilled");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::CreateManageLimitsRequestResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CreateManageLimitsRequestResult;
  using case_type = ::stellar::CreateManageLimitsRequestResult::_xdr_case_type;
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

  static std::size_t serial_size(const ::stellar::CreateManageLimitsRequestResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in CreateManageLimitsRequestResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateManageLimitsRequestResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in CreateManageLimitsRequestResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateManageLimitsRequestResult &obj) {
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

#endif // !__XDR_STELLAR_OPERATION_CREATE_MANAGE_LIMITS_REQUEST_H_INCLUDED__
