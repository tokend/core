// -*- C++ -*-
// Automatically generated from Stellar-operation-manage-contract.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_OPERATION_MANAGE_CONTRACT_H_INCLUDED__
#define __XDR_STELLAR_OPERATION_MANAGE_CONTRACT_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-ledger-entries.h"

namespace stellar {

enum class ManageContractAction : std::int32_t {
  ADD_DETAILS = 0,
  CONFIRM_COMPLETED = 1,
  START_DISPUTE = 2,
  RESOLVE_DISPUTE = 3,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageContractAction>
  : xdr_integral_base<::stellar::ManageContractAction, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageContractAction val) {
    switch (val) {
    case ::stellar::ManageContractAction::ADD_DETAILS:
      return "ADD_DETAILS";
    case ::stellar::ManageContractAction::CONFIRM_COMPLETED:
      return "CONFIRM_COMPLETED";
    case ::stellar::ManageContractAction::START_DISPUTE:
      return "START_DISPUTE";
    case ::stellar::ManageContractAction::RESOLVE_DISPUTE:
      return "RESOLVE_DISPUTE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageContractAction::ADD_DETAILS,
      (int32_t)::stellar::ManageContractAction::CONFIRM_COMPLETED,
      (int32_t)::stellar::ManageContractAction::START_DISPUTE,
      (int32_t)::stellar::ManageContractAction::RESOLVE_DISPUTE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ManageContractOp {
  struct _data_t {
    using _xdr_case_type = xdr::xdr_traits<ManageContractAction>::case_type;
  private:
    _xdr_case_type action_;
    union {
      longstring details_;
      longstring disputeReason_;
      bool isRevert_;
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<ManageContractAction> &_xdr_case_values() {
      static const std::vector<ManageContractAction> _xdr_disc_vec {
        ManageContractAction::ADD_DETAILS,
        ManageContractAction::CONFIRM_COMPLETED,
        ManageContractAction::START_DISPUTE,
        ManageContractAction::RESOLVE_DISPUTE
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)ManageContractAction::ADD_DETAILS ? 1
        : which == (int32_t)ManageContractAction::CONFIRM_COMPLETED ? 0
        : which == (int32_t)ManageContractAction::START_DISPUTE ? 2
        : which == (int32_t)ManageContractAction::RESOLVE_DISPUTE ? 3
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)ManageContractAction::ADD_DETAILS:
        _f(&_data_t::details_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ManageContractAction::CONFIRM_COMPLETED:
        return true;
      case (int32_t)ManageContractAction::START_DISPUTE:
        _f(&_data_t::disputeReason_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ManageContractAction::RESOLVE_DISPUTE:
        _f(&_data_t::isRevert_, std::forward<_A>(_a)...);
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return action_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of action in _data_t");
      if (fnum != _xdr_field_number(action_)) {
        this->~_data_t();
        action_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, action_, *this);
      }
      else
        action_ = which;
    }
    explicit _data_t(ManageContractAction which = ManageContractAction{}) : action_((int32_t)which) {
      _xdr_with_mem_ptr(xdr::field_constructor, action_, *this);
    }
    _data_t(const _data_t &source) : action_(source.action_) {
      _xdr_with_mem_ptr(xdr::field_constructor, action_, *this, source);
    }
    _data_t(_data_t &&source) : action_(source.action_) {
      _xdr_with_mem_ptr(xdr::field_constructor, action_, *this,
                        std::move(source));
    }
    ~_data_t() { _xdr_with_mem_ptr(xdr::field_destructor, action_, *this); }
    _data_t &operator=(const _data_t &source) {
      if (_xdr_field_number(action_)
          == _xdr_field_number(source.action_))
        _xdr_with_mem_ptr(xdr::field_assigner, action_, *this, source);
      else {
        this->~_data_t();
        action_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.action_, *this, source);
      }
      action_ = source.action_;
      return *this;
    }
    _data_t &operator=(_data_t &&source) {
      if (_xdr_field_number(action_)
           == _xdr_field_number(source.action_))
        _xdr_with_mem_ptr(xdr::field_assigner, action_, *this,
                          std::move(source));
      else {
        this->~_data_t();
        action_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.action_, *this,
                          std::move(source));
      }
      action_ = source.action_;
      return *this;
    }

    ManageContractAction action() const { return ManageContractAction(action_); }
    _data_t &action(ManageContractAction _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    longstring &details() {
      if (_xdr_field_number(action_) == 1)
        return details_;
      throw xdr::xdr_wrong_union("_data_t: details accessed when not selected");
    }
    const longstring &details() const {
      if (_xdr_field_number(action_) == 1)
        return details_;
      throw xdr::xdr_wrong_union("_data_t: details accessed when not selected");
    }
    longstring &disputeReason() {
      if (_xdr_field_number(action_) == 2)
        return disputeReason_;
      throw xdr::xdr_wrong_union("_data_t: disputeReason accessed when not selected");
    }
    const longstring &disputeReason() const {
      if (_xdr_field_number(action_) == 2)
        return disputeReason_;
      throw xdr::xdr_wrong_union("_data_t: disputeReason accessed when not selected");
    }
    bool &isRevert() {
      if (_xdr_field_number(action_) == 3)
        return isRevert_;
      throw xdr::xdr_wrong_union("_data_t: isRevert accessed when not selected");
    }
    const bool &isRevert() const {
      if (_xdr_field_number(action_) == 3)
        return isRevert_;
      throw xdr::xdr_wrong_union("_data_t: isRevert accessed when not selected");
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

  uint64 contractID{};
  _data_t data{};
  _ext_t ext{};

  ManageContractOp() = default;
  template<typename _contractID_T,
           typename _data_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _contractID_T>::value
                          && std::is_constructible<_data_t, _data_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ManageContractOp(_contractID_T &&_contractID,
                            _data_T &&_data,
                            _ext_T &&_ext)
    : contractID(std::forward<_contractID_T>(_contractID)),
      data(std::forward<_data_T>(_data)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageContractOp::_data_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageContractOp::_data_t;
  using case_type = ::stellar::ManageContractOp::_data_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().action());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "details";
    case 2:
      return "disputeReason";
    case 3:
      return "isRevert";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageContractOp::_data_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of action in _data_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageContractOp::_data_t &obj) {
    xdr::archive(ar, obj.action(), "action");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.action(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of action in _data_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageContractOp::_data_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "action");
    obj.action(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.action(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageContractOp::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageContractOp::_ext_t;
  using case_type = ::stellar::ManageContractOp::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageContractOp::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageContractOp::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageContractOp::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageContractOp>
  : xdr_struct_base<field_ptr<::stellar::ManageContractOp,
                              decltype(::stellar::ManageContractOp::contractID),
                              &::stellar::ManageContractOp::contractID>,
                    field_ptr<::stellar::ManageContractOp,
                              decltype(::stellar::ManageContractOp::data),
                              &::stellar::ManageContractOp::data>,
                    field_ptr<::stellar::ManageContractOp,
                              decltype(::stellar::ManageContractOp::ext),
                              &::stellar::ManageContractOp::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageContractOp &obj) {
    archive(ar, obj.contractID, "contractID");
    archive(ar, obj.data, "data");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageContractOp &obj) {
    archive(ar, obj.contractID, "contractID");
    archive(ar, obj.data, "data");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum class ManageContractResultCode : std::int32_t {
  SUCCESS = 0,
  MALFORMED = -1,
  NOT_FOUND = -2,
  NOT_ALLOWED = -3,
  DETAILS_TOO_LONG = -4,
  DISPUTE_REASON_TOO_LONG = -5,
  ALREADY_CONFIRMED = -6,
  INVOICE_NOT_APPROVED = -7,
  DISPUTE_ALREADY_STARTED = -8,
  CUSTOMER_BALANCE_OVERFLOW = -9,
  INCORRECT_PRECISION = -10,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageContractResultCode>
  : xdr_integral_base<::stellar::ManageContractResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageContractResultCode val) {
    switch (val) {
    case ::stellar::ManageContractResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::ManageContractResultCode::MALFORMED:
      return "MALFORMED";
    case ::stellar::ManageContractResultCode::NOT_FOUND:
      return "NOT_FOUND";
    case ::stellar::ManageContractResultCode::NOT_ALLOWED:
      return "NOT_ALLOWED";
    case ::stellar::ManageContractResultCode::DETAILS_TOO_LONG:
      return "DETAILS_TOO_LONG";
    case ::stellar::ManageContractResultCode::DISPUTE_REASON_TOO_LONG:
      return "DISPUTE_REASON_TOO_LONG";
    case ::stellar::ManageContractResultCode::ALREADY_CONFIRMED:
      return "ALREADY_CONFIRMED";
    case ::stellar::ManageContractResultCode::INVOICE_NOT_APPROVED:
      return "INVOICE_NOT_APPROVED";
    case ::stellar::ManageContractResultCode::DISPUTE_ALREADY_STARTED:
      return "DISPUTE_ALREADY_STARTED";
    case ::stellar::ManageContractResultCode::CUSTOMER_BALANCE_OVERFLOW:
      return "CUSTOMER_BALANCE_OVERFLOW";
    case ::stellar::ManageContractResultCode::INCORRECT_PRECISION:
      return "INCORRECT_PRECISION";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageContractResultCode::SUCCESS,
      (int32_t)::stellar::ManageContractResultCode::MALFORMED,
      (int32_t)::stellar::ManageContractResultCode::NOT_FOUND,
      (int32_t)::stellar::ManageContractResultCode::NOT_ALLOWED,
      (int32_t)::stellar::ManageContractResultCode::DETAILS_TOO_LONG,
      (int32_t)::stellar::ManageContractResultCode::DISPUTE_REASON_TOO_LONG,
      (int32_t)::stellar::ManageContractResultCode::ALREADY_CONFIRMED,
      (int32_t)::stellar::ManageContractResultCode::INVOICE_NOT_APPROVED,
      (int32_t)::stellar::ManageContractResultCode::DISPUTE_ALREADY_STARTED,
      (int32_t)::stellar::ManageContractResultCode::CUSTOMER_BALANCE_OVERFLOW,
      (int32_t)::stellar::ManageContractResultCode::INCORRECT_PRECISION
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ManageContractResponse {
  struct _data_t {
    using _xdr_case_type = xdr::xdr_traits<ManageContractAction>::case_type;
  private:
    _xdr_case_type action_;
    union {
      bool isCompleted_;
    };

  public:
    static Constexpr const bool _xdr_has_default_case = true;
    static const std::vector<ManageContractAction> &_xdr_case_values() {
      static const std::vector<ManageContractAction> _xdr_disc_vec {};
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)ManageContractAction::CONFIRM_COMPLETED ? 1
        : 0;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)ManageContractAction::CONFIRM_COMPLETED:
        _f(&_data_t::isCompleted_, std::forward<_A>(_a)...);
        return true;
      default:
        return true;
      }
    }

    _xdr_case_type _xdr_discriminant() const { return action_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of action in _data_t");
      if (fnum != _xdr_field_number(action_)) {
        this->~_data_t();
        action_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, action_, *this);
      }
      else
        action_ = which;
    }
    explicit _data_t(ManageContractAction which = ManageContractAction{}) : action_((int32_t)which) {
      _xdr_with_mem_ptr(xdr::field_constructor, action_, *this);
    }
    _data_t(const _data_t &source) : action_(source.action_) {
      _xdr_with_mem_ptr(xdr::field_constructor, action_, *this, source);
    }
    _data_t(_data_t &&source) : action_(source.action_) {
      _xdr_with_mem_ptr(xdr::field_constructor, action_, *this,
                        std::move(source));
    }
    ~_data_t() { _xdr_with_mem_ptr(xdr::field_destructor, action_, *this); }
    _data_t &operator=(const _data_t &source) {
      if (_xdr_field_number(action_)
          == _xdr_field_number(source.action_))
        _xdr_with_mem_ptr(xdr::field_assigner, action_, *this, source);
      else {
        this->~_data_t();
        action_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.action_, *this, source);
      }
      action_ = source.action_;
      return *this;
    }
    _data_t &operator=(_data_t &&source) {
      if (_xdr_field_number(action_)
           == _xdr_field_number(source.action_))
        _xdr_with_mem_ptr(xdr::field_assigner, action_, *this,
                          std::move(source));
      else {
        this->~_data_t();
        action_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.action_, *this,
                          std::move(source));
      }
      action_ = source.action_;
      return *this;
    }

    ManageContractAction action() const { return ManageContractAction(action_); }
    _data_t &action(ManageContractAction _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    bool &isCompleted() {
      if (_xdr_field_number(action_) == 1)
        return isCompleted_;
      throw xdr::xdr_wrong_union("_data_t: isCompleted accessed when not selected");
    }
    const bool &isCompleted() const {
      if (_xdr_field_number(action_) == 1)
        return isCompleted_;
      throw xdr::xdr_wrong_union("_data_t: isCompleted accessed when not selected");
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

  _data_t data{};
  _ext_t ext{};

  ManageContractResponse() = default;
  template<typename _data_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<_data_t, _data_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ManageContractResponse(_data_T &&_data,
                                  _ext_T &&_ext)
    : data(std::forward<_data_T>(_data)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageContractResponse::_data_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageContractResponse::_data_t;
  using case_type = ::stellar::ManageContractResponse::_data_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().action());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "isCompleted";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageContractResponse::_data_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of action in _data_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageContractResponse::_data_t &obj) {
    xdr::archive(ar, obj.action(), "action");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.action(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of action in _data_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageContractResponse::_data_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "action");
    obj.action(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.action(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageContractResponse::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageContractResponse::_ext_t;
  using case_type = ::stellar::ManageContractResponse::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageContractResponse::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageContractResponse::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageContractResponse::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageContractResponse>
  : xdr_struct_base<field_ptr<::stellar::ManageContractResponse,
                              decltype(::stellar::ManageContractResponse::data),
                              &::stellar::ManageContractResponse::data>,
                    field_ptr<::stellar::ManageContractResponse,
                              decltype(::stellar::ManageContractResponse::ext),
                              &::stellar::ManageContractResponse::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageContractResponse &obj) {
    archive(ar, obj.data, "data");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageContractResponse &obj) {
    archive(ar, obj.data, "data");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ManageContractResult {
  using _xdr_case_type = xdr::xdr_traits<ManageContractResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    ManageContractResponse response_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = true;
  static const std::vector<ManageContractResultCode> &_xdr_case_values() {
    static const std::vector<ManageContractResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)ManageContractResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)ManageContractResultCode::SUCCESS:
      _f(&ManageContractResult::response_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in ManageContractResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~ManageContractResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit ManageContractResult(ManageContractResultCode which = ManageContractResultCode{}) : code_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  ManageContractResult(const ManageContractResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  ManageContractResult(ManageContractResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~ManageContractResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  ManageContractResult &operator=(const ManageContractResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~ManageContractResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  ManageContractResult &operator=(ManageContractResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~ManageContractResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  ManageContractResultCode code() const { return ManageContractResultCode(code_); }
  ManageContractResult &code(ManageContractResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  ManageContractResponse &response() {
    if (_xdr_field_number(code_) == 1)
      return response_;
    throw xdr::xdr_wrong_union("ManageContractResult: response accessed when not selected");
  }
  const ManageContractResponse &response() const {
    if (_xdr_field_number(code_) == 1)
      return response_;
    throw xdr::xdr_wrong_union("ManageContractResult: response accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageContractResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageContractResult;
  using case_type = ::stellar::ManageContractResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

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

  static std::size_t serial_size(const ::stellar::ManageContractResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in ManageContractResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageContractResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in ManageContractResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageContractResult &obj) {
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

#endif // !__XDR_STELLAR_OPERATION_MANAGE_CONTRACT_H_INCLUDED__
