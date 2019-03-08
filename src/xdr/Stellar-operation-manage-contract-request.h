// -*- C++ -*-
// Automatically generated from Stellar-operation-manage-contract-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_OPERATION_MANAGE_CONTRACT_REQUEST_H_INCLUDED__
#define __XDR_STELLAR_OPERATION_MANAGE_CONTRACT_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-ledger-entries.h"

namespace stellar {

enum class ManageContractRequestAction : std::int32_t {
  CREATE = 0,
  REMOVE = 1,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageContractRequestAction>
  : xdr_integral_base<::stellar::ManageContractRequestAction, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageContractRequestAction val) {
    switch (val) {
    case ::stellar::ManageContractRequestAction::CREATE:
      return "CREATE";
    case ::stellar::ManageContractRequestAction::REMOVE:
      return "REMOVE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageContractRequestAction::CREATE,
      (int32_t)::stellar::ManageContractRequestAction::REMOVE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateContractRequest {
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

  ContractRequest contractRequest{};
  xdr::pointer<uint32> allTasks{};
  _ext_t ext{};

  CreateContractRequest() = default;
  template<typename _contractRequest_T,
           typename _allTasks_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<ContractRequest, _contractRequest_T>::value
                          && std::is_constructible<xdr::pointer<uint32>, _allTasks_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateContractRequest(_contractRequest_T &&_contractRequest,
                                 _allTasks_T &&_allTasks,
                                 _ext_T &&_ext)
    : contractRequest(std::forward<_contractRequest_T>(_contractRequest)),
      allTasks(std::forward<_allTasks_T>(_allTasks)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateContractRequest::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CreateContractRequest::_ext_t;
  using case_type = ::stellar::CreateContractRequest::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::CreateContractRequest::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateContractRequest::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateContractRequest::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::CreateContractRequest>
  : xdr_struct_base<field_ptr<::stellar::CreateContractRequest,
                              decltype(::stellar::CreateContractRequest::contractRequest),
                              &::stellar::CreateContractRequest::contractRequest>,
                    field_ptr<::stellar::CreateContractRequest,
                              decltype(::stellar::CreateContractRequest::allTasks),
                              &::stellar::CreateContractRequest::allTasks>,
                    field_ptr<::stellar::CreateContractRequest,
                              decltype(::stellar::CreateContractRequest::ext),
                              &::stellar::CreateContractRequest::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateContractRequest &obj) {
    archive(ar, obj.contractRequest, "contractRequest");
    archive(ar, obj.allTasks, "allTasks");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateContractRequest &obj) {
    archive(ar, obj.contractRequest, "contractRequest");
    archive(ar, obj.allTasks, "allTasks");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ManageContractRequestOp {
  struct _details_t {
    using _xdr_case_type = xdr::xdr_traits<ManageContractRequestAction>::case_type;
  private:
    _xdr_case_type action_;
    union {
      CreateContractRequest createContractRequest_;
      uint64 requestID_;
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<ManageContractRequestAction> &_xdr_case_values() {
      static const std::vector<ManageContractRequestAction> _xdr_disc_vec {
        ManageContractRequestAction::CREATE,
        ManageContractRequestAction::REMOVE
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)ManageContractRequestAction::CREATE ? 1
        : which == (int32_t)ManageContractRequestAction::REMOVE ? 2
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)ManageContractRequestAction::CREATE:
        _f(&_details_t::createContractRequest_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ManageContractRequestAction::REMOVE:
        _f(&_details_t::requestID_, std::forward<_A>(_a)...);
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return action_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of action in _details_t");
      if (fnum != _xdr_field_number(action_)) {
        this->~_details_t();
        action_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, action_, *this);
      }
      else
        action_ = which;
    }
    explicit _details_t(ManageContractRequestAction which = ManageContractRequestAction{}) : action_((int32_t)which) {
      _xdr_with_mem_ptr(xdr::field_constructor, action_, *this);
    }
    _details_t(const _details_t &source) : action_(source.action_) {
      _xdr_with_mem_ptr(xdr::field_constructor, action_, *this, source);
    }
    _details_t(_details_t &&source) : action_(source.action_) {
      _xdr_with_mem_ptr(xdr::field_constructor, action_, *this,
                        std::move(source));
    }
    ~_details_t() { _xdr_with_mem_ptr(xdr::field_destructor, action_, *this); }
    _details_t &operator=(const _details_t &source) {
      if (_xdr_field_number(action_)
          == _xdr_field_number(source.action_))
        _xdr_with_mem_ptr(xdr::field_assigner, action_, *this, source);
      else {
        this->~_details_t();
        action_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.action_, *this, source);
      }
      action_ = source.action_;
      return *this;
    }
    _details_t &operator=(_details_t &&source) {
      if (_xdr_field_number(action_)
           == _xdr_field_number(source.action_))
        _xdr_with_mem_ptr(xdr::field_assigner, action_, *this,
                          std::move(source));
      else {
        this->~_details_t();
        action_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.action_, *this,
                          std::move(source));
      }
      action_ = source.action_;
      return *this;
    }

    ManageContractRequestAction action() const { return ManageContractRequestAction(action_); }
    _details_t &action(ManageContractRequestAction _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    CreateContractRequest &createContractRequest() {
      if (_xdr_field_number(action_) == 1)
        return createContractRequest_;
      throw xdr::xdr_wrong_union("_details_t: createContractRequest accessed when not selected");
    }
    const CreateContractRequest &createContractRequest() const {
      if (_xdr_field_number(action_) == 1)
        return createContractRequest_;
      throw xdr::xdr_wrong_union("_details_t: createContractRequest accessed when not selected");
    }
    uint64 &requestID() {
      if (_xdr_field_number(action_) == 2)
        return requestID_;
      throw xdr::xdr_wrong_union("_details_t: requestID accessed when not selected");
    }
    const uint64 &requestID() const {
      if (_xdr_field_number(action_) == 2)
        return requestID_;
      throw xdr::xdr_wrong_union("_details_t: requestID accessed when not selected");
    }
  };
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

  _details_t details{};
  _ext_t ext{};

  ManageContractRequestOp() = default;
  template<typename _details_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<_details_t, _details_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ManageContractRequestOp(_details_T &&_details,
                                   _ext_T &&_ext)
    : details(std::forward<_details_T>(_details)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageContractRequestOp::_details_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageContractRequestOp::_details_t;
  using case_type = ::stellar::ManageContractRequestOp::_details_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().action());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "createContractRequest";
    case 2:
      return "requestID";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageContractRequestOp::_details_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of action in _details_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageContractRequestOp::_details_t &obj) {
    xdr::archive(ar, obj.action(), "action");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.action(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of action in _details_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageContractRequestOp::_details_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "action");
    obj.action(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.action(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageContractRequestOp::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageContractRequestOp::_ext_t;
  using case_type = ::stellar::ManageContractRequestOp::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageContractRequestOp::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageContractRequestOp::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageContractRequestOp::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageContractRequestOp>
  : xdr_struct_base<field_ptr<::stellar::ManageContractRequestOp,
                              decltype(::stellar::ManageContractRequestOp::details),
                              &::stellar::ManageContractRequestOp::details>,
                    field_ptr<::stellar::ManageContractRequestOp,
                              decltype(::stellar::ManageContractRequestOp::ext),
                              &::stellar::ManageContractRequestOp::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageContractRequestOp &obj) {
    archive(ar, obj.details, "details");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageContractRequestOp &obj) {
    archive(ar, obj.details, "details");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum class ManageContractRequestResultCode : std::int32_t {
  SUCCESS = 0,
  MALFORMED = -1,
  NOT_FOUND = -2,
  TOO_MANY_CONTRACTS = -3,
  NOT_ALLOWED_TO_REMOVE = -4,
  DETAILS_TOO_LONG = -5,
  CONTRACT_CREATE_TASKS_NOT_FOUND = -6,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageContractRequestResultCode>
  : xdr_integral_base<::stellar::ManageContractRequestResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageContractRequestResultCode val) {
    switch (val) {
    case ::stellar::ManageContractRequestResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::ManageContractRequestResultCode::MALFORMED:
      return "MALFORMED";
    case ::stellar::ManageContractRequestResultCode::NOT_FOUND:
      return "NOT_FOUND";
    case ::stellar::ManageContractRequestResultCode::TOO_MANY_CONTRACTS:
      return "TOO_MANY_CONTRACTS";
    case ::stellar::ManageContractRequestResultCode::NOT_ALLOWED_TO_REMOVE:
      return "NOT_ALLOWED_TO_REMOVE";
    case ::stellar::ManageContractRequestResultCode::DETAILS_TOO_LONG:
      return "DETAILS_TOO_LONG";
    case ::stellar::ManageContractRequestResultCode::CONTRACT_CREATE_TASKS_NOT_FOUND:
      return "CONTRACT_CREATE_TASKS_NOT_FOUND";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageContractRequestResultCode::SUCCESS,
      (int32_t)::stellar::ManageContractRequestResultCode::MALFORMED,
      (int32_t)::stellar::ManageContractRequestResultCode::NOT_FOUND,
      (int32_t)::stellar::ManageContractRequestResultCode::TOO_MANY_CONTRACTS,
      (int32_t)::stellar::ManageContractRequestResultCode::NOT_ALLOWED_TO_REMOVE,
      (int32_t)::stellar::ManageContractRequestResultCode::DETAILS_TOO_LONG,
      (int32_t)::stellar::ManageContractRequestResultCode::CONTRACT_CREATE_TASKS_NOT_FOUND
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateContractRequestResponse {
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

  CreateContractRequestResponse() = default;
  template<typename _requestID_T,
           typename _fulfilled_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<bool, _fulfilled_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateContractRequestResponse(_requestID_T &&_requestID,
                                         _fulfilled_T &&_fulfilled,
                                         _ext_T &&_ext)
    : requestID(std::forward<_requestID_T>(_requestID)),
      fulfilled(std::forward<_fulfilled_T>(_fulfilled)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateContractRequestResponse::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CreateContractRequestResponse::_ext_t;
  using case_type = ::stellar::CreateContractRequestResponse::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::CreateContractRequestResponse::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateContractRequestResponse::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateContractRequestResponse::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::CreateContractRequestResponse>
  : xdr_struct_base<field_ptr<::stellar::CreateContractRequestResponse,
                              decltype(::stellar::CreateContractRequestResponse::requestID),
                              &::stellar::CreateContractRequestResponse::requestID>,
                    field_ptr<::stellar::CreateContractRequestResponse,
                              decltype(::stellar::CreateContractRequestResponse::fulfilled),
                              &::stellar::CreateContractRequestResponse::fulfilled>,
                    field_ptr<::stellar::CreateContractRequestResponse,
                              decltype(::stellar::CreateContractRequestResponse::ext),
                              &::stellar::CreateContractRequestResponse::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateContractRequestResponse &obj) {
    archive(ar, obj.requestID, "requestID");
    archive(ar, obj.fulfilled, "fulfilled");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateContractRequestResponse &obj) {
    archive(ar, obj.requestID, "requestID");
    archive(ar, obj.fulfilled, "fulfilled");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ManageContractRequestResult {
  struct _success_t {
    struct _details_t {
      using _xdr_case_type = xdr::xdr_traits<ManageContractRequestAction>::case_type;
    private:
      _xdr_case_type action_;
      union {
        CreateContractRequestResponse response_;
      };

    public:
      static Constexpr const bool _xdr_has_default_case = false;
      static const std::vector<ManageContractRequestAction> &_xdr_case_values() {
        static const std::vector<ManageContractRequestAction> _xdr_disc_vec {
          ManageContractRequestAction::CREATE,
          ManageContractRequestAction::REMOVE
        };
        return _xdr_disc_vec;
      }
      static Constexpr int _xdr_field_number(_xdr_case_type which) {
        return which == (int32_t)ManageContractRequestAction::CREATE ? 1
          : which == (int32_t)ManageContractRequestAction::REMOVE ? 0
          : -1;
      }
      template<typename _F, typename..._A> static bool
      _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
        switch (_which) {
        case (int32_t)ManageContractRequestAction::CREATE:
          _f(&_details_t::response_, std::forward<_A>(_a)...);
          return true;
        case (int32_t)ManageContractRequestAction::REMOVE:
          return true;
        }
        return false;
      }

      _xdr_case_type _xdr_discriminant() const { return action_; }
      void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
        int fnum = _xdr_field_number(which);
        if (fnum < 0 && validate)
          throw xdr::xdr_bad_discriminant("bad value of action in _details_t");
        if (fnum != _xdr_field_number(action_)) {
          this->~_details_t();
          action_ = which;
          _xdr_with_mem_ptr(xdr::field_constructor, action_, *this);
        }
        else
          action_ = which;
      }
      explicit _details_t(ManageContractRequestAction which = ManageContractRequestAction{}) : action_((int32_t)which) {
        _xdr_with_mem_ptr(xdr::field_constructor, action_, *this);
      }
      _details_t(const _details_t &source) : action_(source.action_) {
        _xdr_with_mem_ptr(xdr::field_constructor, action_, *this, source);
      }
      _details_t(_details_t &&source) : action_(source.action_) {
        _xdr_with_mem_ptr(xdr::field_constructor, action_, *this,
                          std::move(source));
      }
      ~_details_t() { _xdr_with_mem_ptr(xdr::field_destructor, action_, *this); }
      _details_t &operator=(const _details_t &source) {
        if (_xdr_field_number(action_)
            == _xdr_field_number(source.action_))
          _xdr_with_mem_ptr(xdr::field_assigner, action_, *this, source);
        else {
          this->~_details_t();
          action_ = std::numeric_limits<_xdr_case_type>::max();
          _xdr_with_mem_ptr(xdr::field_constructor, source.action_, *this, source);
        }
        action_ = source.action_;
        return *this;
      }
      _details_t &operator=(_details_t &&source) {
        if (_xdr_field_number(action_)
             == _xdr_field_number(source.action_))
          _xdr_with_mem_ptr(xdr::field_assigner, action_, *this,
                            std::move(source));
        else {
          this->~_details_t();
          action_ = std::numeric_limits<_xdr_case_type>::max();
          _xdr_with_mem_ptr(xdr::field_constructor, source.action_, *this,
                            std::move(source));
        }
        action_ = source.action_;
        return *this;
      }

      ManageContractRequestAction action() const { return ManageContractRequestAction(action_); }
      _details_t &action(ManageContractRequestAction _xdr_d, bool _xdr_validate = true) {
        _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
        return *this;
      }

      CreateContractRequestResponse &response() {
        if (_xdr_field_number(action_) == 1)
          return response_;
        throw xdr::xdr_wrong_union("_details_t: response accessed when not selected");
      }
      const CreateContractRequestResponse &response() const {
        if (_xdr_field_number(action_) == 1)
          return response_;
        throw xdr::xdr_wrong_union("_details_t: response accessed when not selected");
      }
    };
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

    _details_t details{};
    _ext_t ext{};

    _success_t() = default;
    template<typename _details_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<_details_t, _details_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _success_t(_details_T &&_details,
                        _ext_T &&_ext)
      : details(std::forward<_details_T>(_details)),
        ext(std::forward<_ext_T>(_ext)) {}
  };

  using _xdr_case_type = xdr::xdr_traits<ManageContractRequestResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    _success_t success_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = true;
  static const std::vector<ManageContractRequestResultCode> &_xdr_case_values() {
    static const std::vector<ManageContractRequestResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)ManageContractRequestResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)ManageContractRequestResultCode::SUCCESS:
      _f(&ManageContractRequestResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in ManageContractRequestResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~ManageContractRequestResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit ManageContractRequestResult(ManageContractRequestResultCode which = ManageContractRequestResultCode{}) : code_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  ManageContractRequestResult(const ManageContractRequestResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  ManageContractRequestResult(ManageContractRequestResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~ManageContractRequestResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  ManageContractRequestResult &operator=(const ManageContractRequestResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~ManageContractRequestResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  ManageContractRequestResult &operator=(ManageContractRequestResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~ManageContractRequestResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  ManageContractRequestResultCode code() const { return ManageContractRequestResultCode(code_); }
  ManageContractRequestResult &code(ManageContractRequestResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  _success_t &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageContractRequestResult: success accessed when not selected");
  }
  const _success_t &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageContractRequestResult: success accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageContractRequestResult::_success_t::_details_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageContractRequestResult::_success_t::_details_t;
  using case_type = ::stellar::ManageContractRequestResult::_success_t::_details_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().action());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "response";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageContractRequestResult::_success_t::_details_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of action in _details_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageContractRequestResult::_success_t::_details_t &obj) {
    xdr::archive(ar, obj.action(), "action");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.action(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of action in _details_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageContractRequestResult::_success_t::_details_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "action");
    obj.action(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.action(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageContractRequestResult::_success_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageContractRequestResult::_success_t::_ext_t;
  using case_type = ::stellar::ManageContractRequestResult::_success_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageContractRequestResult::_success_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageContractRequestResult::_success_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageContractRequestResult::_success_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageContractRequestResult::_success_t>
  : xdr_struct_base<field_ptr<::stellar::ManageContractRequestResult::_success_t,
                              decltype(::stellar::ManageContractRequestResult::_success_t::details),
                              &::stellar::ManageContractRequestResult::_success_t::details>,
                    field_ptr<::stellar::ManageContractRequestResult::_success_t,
                              decltype(::stellar::ManageContractRequestResult::_success_t::ext),
                              &::stellar::ManageContractRequestResult::_success_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageContractRequestResult::_success_t &obj) {
    archive(ar, obj.details, "details");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageContractRequestResult::_success_t &obj) {
    archive(ar, obj.details, "details");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageContractRequestResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageContractRequestResult;
  using case_type = ::stellar::ManageContractRequestResult::_xdr_case_type;
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

  static std::size_t serial_size(const ::stellar::ManageContractRequestResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in ManageContractRequestResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageContractRequestResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in ManageContractRequestResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageContractRequestResult &obj) {
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

#endif // !__XDR_STELLAR_OPERATION_MANAGE_CONTRACT_REQUEST_H_INCLUDED__
