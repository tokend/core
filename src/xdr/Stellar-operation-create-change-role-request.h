// -*- C++ -*-
// Automatically generated from Stellar-operation-create-change-role-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_OPERATION_CREATE_CHANGE_ROLE_REQUEST_H_INCLUDED__
#define __XDR_STELLAR_OPERATION_CREATE_CHANGE_ROLE_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-types.h"

namespace stellar {

struct CreateChangeRoleRequestOp {
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
  AccountID destinationAccount{};
  uint64 accountRoleToSet{};
  longstring creatorDetails{};
  xdr::pointer<uint32> allTasks{};
  _ext_t ext{};

  CreateChangeRoleRequestOp() = default;
  template<typename _requestID_T,
           typename _destinationAccount_T,
           typename _accountRoleToSet_T,
           typename _creatorDetails_T,
           typename _allTasks_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<AccountID, _destinationAccount_T>::value
                          && std::is_constructible<uint64, _accountRoleToSet_T>::value
                          && std::is_constructible<longstring, _creatorDetails_T>::value
                          && std::is_constructible<xdr::pointer<uint32>, _allTasks_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateChangeRoleRequestOp(_requestID_T &&_requestID,
                                     _destinationAccount_T &&_destinationAccount,
                                     _accountRoleToSet_T &&_accountRoleToSet,
                                     _creatorDetails_T &&_creatorDetails,
                                     _allTasks_T &&_allTasks,
                                     _ext_T &&_ext)
    : requestID(std::forward<_requestID_T>(_requestID)),
      destinationAccount(std::forward<_destinationAccount_T>(_destinationAccount)),
      accountRoleToSet(std::forward<_accountRoleToSet_T>(_accountRoleToSet)),
      creatorDetails(std::forward<_creatorDetails_T>(_creatorDetails)),
      allTasks(std::forward<_allTasks_T>(_allTasks)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateChangeRoleRequestOp::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CreateChangeRoleRequestOp::_ext_t;
  using case_type = ::stellar::CreateChangeRoleRequestOp::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::CreateChangeRoleRequestOp::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateChangeRoleRequestOp::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateChangeRoleRequestOp::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::CreateChangeRoleRequestOp>
  : xdr_struct_base<field_ptr<::stellar::CreateChangeRoleRequestOp,
                              decltype(::stellar::CreateChangeRoleRequestOp::requestID),
                              &::stellar::CreateChangeRoleRequestOp::requestID>,
                    field_ptr<::stellar::CreateChangeRoleRequestOp,
                              decltype(::stellar::CreateChangeRoleRequestOp::destinationAccount),
                              &::stellar::CreateChangeRoleRequestOp::destinationAccount>,
                    field_ptr<::stellar::CreateChangeRoleRequestOp,
                              decltype(::stellar::CreateChangeRoleRequestOp::accountRoleToSet),
                              &::stellar::CreateChangeRoleRequestOp::accountRoleToSet>,
                    field_ptr<::stellar::CreateChangeRoleRequestOp,
                              decltype(::stellar::CreateChangeRoleRequestOp::creatorDetails),
                              &::stellar::CreateChangeRoleRequestOp::creatorDetails>,
                    field_ptr<::stellar::CreateChangeRoleRequestOp,
                              decltype(::stellar::CreateChangeRoleRequestOp::allTasks),
                              &::stellar::CreateChangeRoleRequestOp::allTasks>,
                    field_ptr<::stellar::CreateChangeRoleRequestOp,
                              decltype(::stellar::CreateChangeRoleRequestOp::ext),
                              &::stellar::CreateChangeRoleRequestOp::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateChangeRoleRequestOp &obj) {
    archive(ar, obj.requestID, "requestID");
    archive(ar, obj.destinationAccount, "destinationAccount");
    archive(ar, obj.accountRoleToSet, "accountRoleToSet");
    archive(ar, obj.creatorDetails, "creatorDetails");
    archive(ar, obj.allTasks, "allTasks");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateChangeRoleRequestOp &obj) {
    archive(ar, obj.requestID, "requestID");
    archive(ar, obj.destinationAccount, "destinationAccount");
    archive(ar, obj.accountRoleToSet, "accountRoleToSet");
    archive(ar, obj.creatorDetails, "creatorDetails");
    archive(ar, obj.allTasks, "allTasks");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum class CreateChangeRoleRequestResultCode : std::int32_t {
  SUCCESS = 0,
  ACC_TO_UPDATE_DOES_NOT_EXIST = -1,
  REQUEST_ALREADY_EXISTS = -2,
  SAME_ACC_TYPE_TO_SET = -3,
  REQUEST_DOES_NOT_EXIST = -4,
  NOT_ALLOWED_TO_UPDATE_REQUEST = -6,
  INVALID_CHANGE_ROLE_REQUEST_DATA = -7,
  INVALID_CREATOR_DETAILS = -8,
  CHANGE_ROLE_TASKS_NOT_FOUND = -9,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateChangeRoleRequestResultCode>
  : xdr_integral_base<::stellar::CreateChangeRoleRequestResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::CreateChangeRoleRequestResultCode val) {
    switch (val) {
    case ::stellar::CreateChangeRoleRequestResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::CreateChangeRoleRequestResultCode::ACC_TO_UPDATE_DOES_NOT_EXIST:
      return "ACC_TO_UPDATE_DOES_NOT_EXIST";
    case ::stellar::CreateChangeRoleRequestResultCode::REQUEST_ALREADY_EXISTS:
      return "REQUEST_ALREADY_EXISTS";
    case ::stellar::CreateChangeRoleRequestResultCode::SAME_ACC_TYPE_TO_SET:
      return "SAME_ACC_TYPE_TO_SET";
    case ::stellar::CreateChangeRoleRequestResultCode::REQUEST_DOES_NOT_EXIST:
      return "REQUEST_DOES_NOT_EXIST";
    case ::stellar::CreateChangeRoleRequestResultCode::NOT_ALLOWED_TO_UPDATE_REQUEST:
      return "NOT_ALLOWED_TO_UPDATE_REQUEST";
    case ::stellar::CreateChangeRoleRequestResultCode::INVALID_CHANGE_ROLE_REQUEST_DATA:
      return "INVALID_CHANGE_ROLE_REQUEST_DATA";
    case ::stellar::CreateChangeRoleRequestResultCode::INVALID_CREATOR_DETAILS:
      return "INVALID_CREATOR_DETAILS";
    case ::stellar::CreateChangeRoleRequestResultCode::CHANGE_ROLE_TASKS_NOT_FOUND:
      return "CHANGE_ROLE_TASKS_NOT_FOUND";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::CreateChangeRoleRequestResultCode::SUCCESS,
      (int32_t)::stellar::CreateChangeRoleRequestResultCode::ACC_TO_UPDATE_DOES_NOT_EXIST,
      (int32_t)::stellar::CreateChangeRoleRequestResultCode::REQUEST_ALREADY_EXISTS,
      (int32_t)::stellar::CreateChangeRoleRequestResultCode::SAME_ACC_TYPE_TO_SET,
      (int32_t)::stellar::CreateChangeRoleRequestResultCode::REQUEST_DOES_NOT_EXIST,
      (int32_t)::stellar::CreateChangeRoleRequestResultCode::NOT_ALLOWED_TO_UPDATE_REQUEST,
      (int32_t)::stellar::CreateChangeRoleRequestResultCode::INVALID_CHANGE_ROLE_REQUEST_DATA,
      (int32_t)::stellar::CreateChangeRoleRequestResultCode::INVALID_CREATOR_DETAILS,
      (int32_t)::stellar::CreateChangeRoleRequestResultCode::CHANGE_ROLE_TASKS_NOT_FOUND
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateChangeRoleRequestResult {
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

  using _xdr_case_type = xdr::xdr_traits<CreateChangeRoleRequestResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    _success_t success_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = true;
  static const std::vector<CreateChangeRoleRequestResultCode> &_xdr_case_values() {
    static const std::vector<CreateChangeRoleRequestResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)CreateChangeRoleRequestResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)CreateChangeRoleRequestResultCode::SUCCESS:
      _f(&CreateChangeRoleRequestResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in CreateChangeRoleRequestResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~CreateChangeRoleRequestResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit CreateChangeRoleRequestResult(CreateChangeRoleRequestResultCode which = CreateChangeRoleRequestResultCode{}) : code_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  CreateChangeRoleRequestResult(const CreateChangeRoleRequestResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  CreateChangeRoleRequestResult(CreateChangeRoleRequestResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~CreateChangeRoleRequestResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  CreateChangeRoleRequestResult &operator=(const CreateChangeRoleRequestResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~CreateChangeRoleRequestResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  CreateChangeRoleRequestResult &operator=(CreateChangeRoleRequestResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~CreateChangeRoleRequestResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  CreateChangeRoleRequestResultCode code() const { return CreateChangeRoleRequestResultCode(code_); }
  CreateChangeRoleRequestResult &code(CreateChangeRoleRequestResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  _success_t &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateChangeRoleRequestResult: success accessed when not selected");
  }
  const _success_t &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("CreateChangeRoleRequestResult: success accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateChangeRoleRequestResult::_success_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CreateChangeRoleRequestResult::_success_t::_ext_t;
  using case_type = ::stellar::CreateChangeRoleRequestResult::_success_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::CreateChangeRoleRequestResult::_success_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateChangeRoleRequestResult::_success_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateChangeRoleRequestResult::_success_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::CreateChangeRoleRequestResult::_success_t>
  : xdr_struct_base<field_ptr<::stellar::CreateChangeRoleRequestResult::_success_t,
                              decltype(::stellar::CreateChangeRoleRequestResult::_success_t::requestID),
                              &::stellar::CreateChangeRoleRequestResult::_success_t::requestID>,
                    field_ptr<::stellar::CreateChangeRoleRequestResult::_success_t,
                              decltype(::stellar::CreateChangeRoleRequestResult::_success_t::fulfilled),
                              &::stellar::CreateChangeRoleRequestResult::_success_t::fulfilled>,
                    field_ptr<::stellar::CreateChangeRoleRequestResult::_success_t,
                              decltype(::stellar::CreateChangeRoleRequestResult::_success_t::ext),
                              &::stellar::CreateChangeRoleRequestResult::_success_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateChangeRoleRequestResult::_success_t &obj) {
    archive(ar, obj.requestID, "requestID");
    archive(ar, obj.fulfilled, "fulfilled");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateChangeRoleRequestResult::_success_t &obj) {
    archive(ar, obj.requestID, "requestID");
    archive(ar, obj.fulfilled, "fulfilled");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::CreateChangeRoleRequestResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CreateChangeRoleRequestResult;
  using case_type = ::stellar::CreateChangeRoleRequestResult::_xdr_case_type;
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

  static std::size_t serial_size(const ::stellar::CreateChangeRoleRequestResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in CreateChangeRoleRequestResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateChangeRoleRequestResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in CreateChangeRoleRequestResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateChangeRoleRequestResult &obj) {
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

#endif // !__XDR_STELLAR_OPERATION_CREATE_CHANGE_ROLE_REQUEST_H_INCLUDED__
