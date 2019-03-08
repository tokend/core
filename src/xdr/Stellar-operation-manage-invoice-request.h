// -*- C++ -*-
// Automatically generated from Stellar-operation-manage-invoice-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_OPERATION_MANAGE_INVOICE_REQUEST_H_INCLUDED__
#define __XDR_STELLAR_OPERATION_MANAGE_INVOICE_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-ledger-entries.h"

namespace stellar {

enum class ManageInvoiceRequestAction : std::int32_t {
  CREATE = 0,
  REMOVE = 1,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageInvoiceRequestAction>
  : xdr_integral_base<::stellar::ManageInvoiceRequestAction, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageInvoiceRequestAction val) {
    switch (val) {
    case ::stellar::ManageInvoiceRequestAction::CREATE:
      return "CREATE";
    case ::stellar::ManageInvoiceRequestAction::REMOVE:
      return "REMOVE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageInvoiceRequestAction::CREATE,
      (int32_t)::stellar::ManageInvoiceRequestAction::REMOVE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct InvoiceCreationRequest {
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

  AssetCode asset{};
  AccountID sender{};
  uint64 amount{};
  xdr::pointer<uint64> contractID{};
  longstring details{};
  xdr::pointer<uint32> allTasks{};
  _ext_t ext{};

  InvoiceCreationRequest() = default;
  template<typename _asset_T,
           typename _sender_T,
           typename _amount_T,
           typename _contractID_T,
           typename _details_T,
           typename _allTasks_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<AssetCode, _asset_T>::value
                          && std::is_constructible<AccountID, _sender_T>::value
                          && std::is_constructible<uint64, _amount_T>::value
                          && std::is_constructible<xdr::pointer<uint64>, _contractID_T>::value
                          && std::is_constructible<longstring, _details_T>::value
                          && std::is_constructible<xdr::pointer<uint32>, _allTasks_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit InvoiceCreationRequest(_asset_T &&_asset,
                                  _sender_T &&_sender,
                                  _amount_T &&_amount,
                                  _contractID_T &&_contractID,
                                  _details_T &&_details,
                                  _allTasks_T &&_allTasks,
                                  _ext_T &&_ext)
    : asset(std::forward<_asset_T>(_asset)),
      sender(std::forward<_sender_T>(_sender)),
      amount(std::forward<_amount_T>(_amount)),
      contractID(std::forward<_contractID_T>(_contractID)),
      details(std::forward<_details_T>(_details)),
      allTasks(std::forward<_allTasks_T>(_allTasks)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::InvoiceCreationRequest::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::InvoiceCreationRequest::_ext_t;
  using case_type = ::stellar::InvoiceCreationRequest::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::InvoiceCreationRequest::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::InvoiceCreationRequest::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::InvoiceCreationRequest::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::InvoiceCreationRequest>
  : xdr_struct_base<field_ptr<::stellar::InvoiceCreationRequest,
                              decltype(::stellar::InvoiceCreationRequest::asset),
                              &::stellar::InvoiceCreationRequest::asset>,
                    field_ptr<::stellar::InvoiceCreationRequest,
                              decltype(::stellar::InvoiceCreationRequest::sender),
                              &::stellar::InvoiceCreationRequest::sender>,
                    field_ptr<::stellar::InvoiceCreationRequest,
                              decltype(::stellar::InvoiceCreationRequest::amount),
                              &::stellar::InvoiceCreationRequest::amount>,
                    field_ptr<::stellar::InvoiceCreationRequest,
                              decltype(::stellar::InvoiceCreationRequest::contractID),
                              &::stellar::InvoiceCreationRequest::contractID>,
                    field_ptr<::stellar::InvoiceCreationRequest,
                              decltype(::stellar::InvoiceCreationRequest::details),
                              &::stellar::InvoiceCreationRequest::details>,
                    field_ptr<::stellar::InvoiceCreationRequest,
                              decltype(::stellar::InvoiceCreationRequest::allTasks),
                              &::stellar::InvoiceCreationRequest::allTasks>,
                    field_ptr<::stellar::InvoiceCreationRequest,
                              decltype(::stellar::InvoiceCreationRequest::ext),
                              &::stellar::InvoiceCreationRequest::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::InvoiceCreationRequest &obj) {
    archive(ar, obj.asset, "asset");
    archive(ar, obj.sender, "sender");
    archive(ar, obj.amount, "amount");
    archive(ar, obj.contractID, "contractID");
    archive(ar, obj.details, "details");
    archive(ar, obj.allTasks, "allTasks");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::InvoiceCreationRequest &obj) {
    archive(ar, obj.asset, "asset");
    archive(ar, obj.sender, "sender");
    archive(ar, obj.amount, "amount");
    archive(ar, obj.contractID, "contractID");
    archive(ar, obj.details, "details");
    archive(ar, obj.allTasks, "allTasks");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ManageInvoiceRequestOp {
  struct _details_t {
    using _xdr_case_type = xdr::xdr_traits<ManageInvoiceRequestAction>::case_type;
  private:
    _xdr_case_type action_;
    union {
      InvoiceCreationRequest invoiceRequest_;
      uint64 requestID_;
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<ManageInvoiceRequestAction> &_xdr_case_values() {
      static const std::vector<ManageInvoiceRequestAction> _xdr_disc_vec {
        ManageInvoiceRequestAction::CREATE,
        ManageInvoiceRequestAction::REMOVE
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == (int32_t)ManageInvoiceRequestAction::CREATE ? 1
        : which == (int32_t)ManageInvoiceRequestAction::REMOVE ? 2
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case (int32_t)ManageInvoiceRequestAction::CREATE:
        _f(&_details_t::invoiceRequest_, std::forward<_A>(_a)...);
        return true;
      case (int32_t)ManageInvoiceRequestAction::REMOVE:
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
    explicit _details_t(ManageInvoiceRequestAction which = ManageInvoiceRequestAction{}) : action_((int32_t)which) {
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

    ManageInvoiceRequestAction action() const { return ManageInvoiceRequestAction(action_); }
    _details_t &action(ManageInvoiceRequestAction _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }

    InvoiceCreationRequest &invoiceRequest() {
      if (_xdr_field_number(action_) == 1)
        return invoiceRequest_;
      throw xdr::xdr_wrong_union("_details_t: invoiceRequest accessed when not selected");
    }
    const InvoiceCreationRequest &invoiceRequest() const {
      if (_xdr_field_number(action_) == 1)
        return invoiceRequest_;
      throw xdr::xdr_wrong_union("_details_t: invoiceRequest accessed when not selected");
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

  ManageInvoiceRequestOp() = default;
  template<typename _details_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<_details_t, _details_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit ManageInvoiceRequestOp(_details_T &&_details,
                                  _ext_T &&_ext)
    : details(std::forward<_details_T>(_details)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageInvoiceRequestOp::_details_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageInvoiceRequestOp::_details_t;
  using case_type = ::stellar::ManageInvoiceRequestOp::_details_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().action());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "invoiceRequest";
    case 2:
      return "requestID";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageInvoiceRequestOp::_details_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of action in _details_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageInvoiceRequestOp::_details_t &obj) {
    xdr::archive(ar, obj.action(), "action");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.action(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of action in _details_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageInvoiceRequestOp::_details_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "action");
    obj.action(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.action(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageInvoiceRequestOp::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageInvoiceRequestOp::_ext_t;
  using case_type = ::stellar::ManageInvoiceRequestOp::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageInvoiceRequestOp::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageInvoiceRequestOp::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageInvoiceRequestOp::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageInvoiceRequestOp>
  : xdr_struct_base<field_ptr<::stellar::ManageInvoiceRequestOp,
                              decltype(::stellar::ManageInvoiceRequestOp::details),
                              &::stellar::ManageInvoiceRequestOp::details>,
                    field_ptr<::stellar::ManageInvoiceRequestOp,
                              decltype(::stellar::ManageInvoiceRequestOp::ext),
                              &::stellar::ManageInvoiceRequestOp::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageInvoiceRequestOp &obj) {
    archive(ar, obj.details, "details");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageInvoiceRequestOp &obj) {
    archive(ar, obj.details, "details");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum class ManageInvoiceRequestResultCode : std::int32_t {
  SUCCESS = 0,
  MALFORMED = -1,
  BALANCE_NOT_FOUND = -2,
  NOT_FOUND = -3,
  TOO_MANY_INVOICES = -4,
  DETAILS_TOO_LONG = -5,
  NOT_ALLOWED_TO_REMOVE = -6,
  CONTRACT_NOT_FOUND = -7,
  ONLY_CONTRACTOR_CAN_ATTACH_INVOICE_TO_CONTRACT = -8,
  SENDER_ACCOUNT_MISMATCHED = -9,
  INVOICE_IS_APPROVED = -10,
  INVOICE_TASKS_NOT_FOUND = -11,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageInvoiceRequestResultCode>
  : xdr_integral_base<::stellar::ManageInvoiceRequestResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageInvoiceRequestResultCode val) {
    switch (val) {
    case ::stellar::ManageInvoiceRequestResultCode::SUCCESS:
      return "SUCCESS";
    case ::stellar::ManageInvoiceRequestResultCode::MALFORMED:
      return "MALFORMED";
    case ::stellar::ManageInvoiceRequestResultCode::BALANCE_NOT_FOUND:
      return "BALANCE_NOT_FOUND";
    case ::stellar::ManageInvoiceRequestResultCode::NOT_FOUND:
      return "NOT_FOUND";
    case ::stellar::ManageInvoiceRequestResultCode::TOO_MANY_INVOICES:
      return "TOO_MANY_INVOICES";
    case ::stellar::ManageInvoiceRequestResultCode::DETAILS_TOO_LONG:
      return "DETAILS_TOO_LONG";
    case ::stellar::ManageInvoiceRequestResultCode::NOT_ALLOWED_TO_REMOVE:
      return "NOT_ALLOWED_TO_REMOVE";
    case ::stellar::ManageInvoiceRequestResultCode::CONTRACT_NOT_FOUND:
      return "CONTRACT_NOT_FOUND";
    case ::stellar::ManageInvoiceRequestResultCode::ONLY_CONTRACTOR_CAN_ATTACH_INVOICE_TO_CONTRACT:
      return "ONLY_CONTRACTOR_CAN_ATTACH_INVOICE_TO_CONTRACT";
    case ::stellar::ManageInvoiceRequestResultCode::SENDER_ACCOUNT_MISMATCHED:
      return "SENDER_ACCOUNT_MISMATCHED";
    case ::stellar::ManageInvoiceRequestResultCode::INVOICE_IS_APPROVED:
      return "INVOICE_IS_APPROVED";
    case ::stellar::ManageInvoiceRequestResultCode::INVOICE_TASKS_NOT_FOUND:
      return "INVOICE_TASKS_NOT_FOUND";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      (int32_t)::stellar::ManageInvoiceRequestResultCode::SUCCESS,
      (int32_t)::stellar::ManageInvoiceRequestResultCode::MALFORMED,
      (int32_t)::stellar::ManageInvoiceRequestResultCode::BALANCE_NOT_FOUND,
      (int32_t)::stellar::ManageInvoiceRequestResultCode::NOT_FOUND,
      (int32_t)::stellar::ManageInvoiceRequestResultCode::TOO_MANY_INVOICES,
      (int32_t)::stellar::ManageInvoiceRequestResultCode::DETAILS_TOO_LONG,
      (int32_t)::stellar::ManageInvoiceRequestResultCode::NOT_ALLOWED_TO_REMOVE,
      (int32_t)::stellar::ManageInvoiceRequestResultCode::CONTRACT_NOT_FOUND,
      (int32_t)::stellar::ManageInvoiceRequestResultCode::ONLY_CONTRACTOR_CAN_ATTACH_INVOICE_TO_CONTRACT,
      (int32_t)::stellar::ManageInvoiceRequestResultCode::SENDER_ACCOUNT_MISMATCHED,
      (int32_t)::stellar::ManageInvoiceRequestResultCode::INVOICE_IS_APPROVED,
      (int32_t)::stellar::ManageInvoiceRequestResultCode::INVOICE_TASKS_NOT_FOUND
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateInvoiceRequestResponse {
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

  BalanceID receiverBalance{};
  BalanceID senderBalance{};
  uint64 requestID{};
  _ext_t ext{};

  CreateInvoiceRequestResponse() = default;
  template<typename _receiverBalance_T,
           typename _senderBalance_T,
           typename _requestID_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<BalanceID, _receiverBalance_T>::value
                          && std::is_constructible<BalanceID, _senderBalance_T>::value
                          && std::is_constructible<uint64, _requestID_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit CreateInvoiceRequestResponse(_receiverBalance_T &&_receiverBalance,
                                        _senderBalance_T &&_senderBalance,
                                        _requestID_T &&_requestID,
                                        _ext_T &&_ext)
    : receiverBalance(std::forward<_receiverBalance_T>(_receiverBalance)),
      senderBalance(std::forward<_senderBalance_T>(_senderBalance)),
      requestID(std::forward<_requestID_T>(_requestID)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateInvoiceRequestResponse::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CreateInvoiceRequestResponse::_ext_t;
  using case_type = ::stellar::CreateInvoiceRequestResponse::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::CreateInvoiceRequestResponse::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateInvoiceRequestResponse::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateInvoiceRequestResponse::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::CreateInvoiceRequestResponse>
  : xdr_struct_base<field_ptr<::stellar::CreateInvoiceRequestResponse,
                              decltype(::stellar::CreateInvoiceRequestResponse::receiverBalance),
                              &::stellar::CreateInvoiceRequestResponse::receiverBalance>,
                    field_ptr<::stellar::CreateInvoiceRequestResponse,
                              decltype(::stellar::CreateInvoiceRequestResponse::senderBalance),
                              &::stellar::CreateInvoiceRequestResponse::senderBalance>,
                    field_ptr<::stellar::CreateInvoiceRequestResponse,
                              decltype(::stellar::CreateInvoiceRequestResponse::requestID),
                              &::stellar::CreateInvoiceRequestResponse::requestID>,
                    field_ptr<::stellar::CreateInvoiceRequestResponse,
                              decltype(::stellar::CreateInvoiceRequestResponse::ext),
                              &::stellar::CreateInvoiceRequestResponse::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateInvoiceRequestResponse &obj) {
    archive(ar, obj.receiverBalance, "receiverBalance");
    archive(ar, obj.senderBalance, "senderBalance");
    archive(ar, obj.requestID, "requestID");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateInvoiceRequestResponse &obj) {
    archive(ar, obj.receiverBalance, "receiverBalance");
    archive(ar, obj.senderBalance, "senderBalance");
    archive(ar, obj.requestID, "requestID");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ManageInvoiceRequestResult {
  struct _success_t {
    struct _details_t {
      using _xdr_case_type = xdr::xdr_traits<ManageInvoiceRequestAction>::case_type;
    private:
      _xdr_case_type action_;
      union {
        CreateInvoiceRequestResponse response_;
      };

    public:
      static Constexpr const bool _xdr_has_default_case = false;
      static const std::vector<ManageInvoiceRequestAction> &_xdr_case_values() {
        static const std::vector<ManageInvoiceRequestAction> _xdr_disc_vec {
          ManageInvoiceRequestAction::CREATE,
          ManageInvoiceRequestAction::REMOVE
        };
        return _xdr_disc_vec;
      }
      static Constexpr int _xdr_field_number(_xdr_case_type which) {
        return which == (int32_t)ManageInvoiceRequestAction::CREATE ? 1
          : which == (int32_t)ManageInvoiceRequestAction::REMOVE ? 0
          : -1;
      }
      template<typename _F, typename..._A> static bool
      _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
        switch (_which) {
        case (int32_t)ManageInvoiceRequestAction::CREATE:
          _f(&_details_t::response_, std::forward<_A>(_a)...);
          return true;
        case (int32_t)ManageInvoiceRequestAction::REMOVE:
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
      explicit _details_t(ManageInvoiceRequestAction which = ManageInvoiceRequestAction{}) : action_((int32_t)which) {
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

      ManageInvoiceRequestAction action() const { return ManageInvoiceRequestAction(action_); }
      _details_t &action(ManageInvoiceRequestAction _xdr_d, bool _xdr_validate = true) {
        _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
        return *this;
      }

      CreateInvoiceRequestResponse &response() {
        if (_xdr_field_number(action_) == 1)
          return response_;
        throw xdr::xdr_wrong_union("_details_t: response accessed when not selected");
      }
      const CreateInvoiceRequestResponse &response() const {
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

    bool fulfilled{};
    _details_t details{};
    _ext_t ext{};

    _success_t() = default;
    template<typename _fulfilled_T,
             typename _details_T,
             typename _ext_T,
             typename = typename
             std::enable_if<std::is_constructible<bool, _fulfilled_T>::value
                            && std::is_constructible<_details_t, _details_T>::value
                            && std::is_constructible<_ext_t, _ext_T>::value
                           >::type>
    explicit _success_t(_fulfilled_T &&_fulfilled,
                        _details_T &&_details,
                        _ext_T &&_ext)
      : fulfilled(std::forward<_fulfilled_T>(_fulfilled)),
        details(std::forward<_details_T>(_details)),
        ext(std::forward<_ext_T>(_ext)) {}
  };

  using _xdr_case_type = xdr::xdr_traits<ManageInvoiceRequestResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    _success_t success_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = true;
  static const std::vector<ManageInvoiceRequestResultCode> &_xdr_case_values() {
    static const std::vector<ManageInvoiceRequestResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == (int32_t)ManageInvoiceRequestResultCode::SUCCESS ? 1
      : 0;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case (int32_t)ManageInvoiceRequestResultCode::SUCCESS:
      _f(&ManageInvoiceRequestResult::success_, std::forward<_A>(_a)...);
      return true;
    default:
      return true;
    }
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in ManageInvoiceRequestResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~ManageInvoiceRequestResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit ManageInvoiceRequestResult(ManageInvoiceRequestResultCode which = ManageInvoiceRequestResultCode{}) : code_((int32_t)which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  ManageInvoiceRequestResult(const ManageInvoiceRequestResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  ManageInvoiceRequestResult(ManageInvoiceRequestResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~ManageInvoiceRequestResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  ManageInvoiceRequestResult &operator=(const ManageInvoiceRequestResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~ManageInvoiceRequestResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  ManageInvoiceRequestResult &operator=(ManageInvoiceRequestResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~ManageInvoiceRequestResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  ManageInvoiceRequestResultCode code() const { return ManageInvoiceRequestResultCode(code_); }
  ManageInvoiceRequestResult &code(ManageInvoiceRequestResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
    return *this;
  }

  _success_t &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageInvoiceRequestResult: success accessed when not selected");
  }
  const _success_t &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageInvoiceRequestResult: success accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageInvoiceRequestResult::_success_t::_details_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageInvoiceRequestResult::_success_t::_details_t;
  using case_type = ::stellar::ManageInvoiceRequestResult::_success_t::_details_t::_xdr_case_type;
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

  static std::size_t serial_size(const ::stellar::ManageInvoiceRequestResult::_success_t::_details_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of action in _details_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageInvoiceRequestResult::_success_t::_details_t &obj) {
    xdr::archive(ar, obj.action(), "action");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.action(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of action in _details_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageInvoiceRequestResult::_success_t::_details_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "action");
    obj.action(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.action(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageInvoiceRequestResult::_success_t::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageInvoiceRequestResult::_success_t::_ext_t;
  using case_type = ::stellar::ManageInvoiceRequestResult::_success_t::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageInvoiceRequestResult::_success_t::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageInvoiceRequestResult::_success_t::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageInvoiceRequestResult::_success_t::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.v(), ar, obj,
                          union_field_name((int32_t)which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageInvoiceRequestResult::_success_t>
  : xdr_struct_base<field_ptr<::stellar::ManageInvoiceRequestResult::_success_t,
                              decltype(::stellar::ManageInvoiceRequestResult::_success_t::fulfilled),
                              &::stellar::ManageInvoiceRequestResult::_success_t::fulfilled>,
                    field_ptr<::stellar::ManageInvoiceRequestResult::_success_t,
                              decltype(::stellar::ManageInvoiceRequestResult::_success_t::details),
                              &::stellar::ManageInvoiceRequestResult::_success_t::details>,
                    field_ptr<::stellar::ManageInvoiceRequestResult::_success_t,
                              decltype(::stellar::ManageInvoiceRequestResult::_success_t::ext),
                              &::stellar::ManageInvoiceRequestResult::_success_t::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageInvoiceRequestResult::_success_t &obj) {
    archive(ar, obj.fulfilled, "fulfilled");
    archive(ar, obj.details, "details");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageInvoiceRequestResult::_success_t &obj) {
    archive(ar, obj.fulfilled, "fulfilled");
    archive(ar, obj.details, "details");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageInvoiceRequestResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageInvoiceRequestResult;
  using case_type = ::stellar::ManageInvoiceRequestResult::_xdr_case_type;
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

  static std::size_t serial_size(const ::stellar::ManageInvoiceRequestResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in ManageInvoiceRequestResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageInvoiceRequestResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, (int32_t)obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in ManageInvoiceRequestResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageInvoiceRequestResult &obj) {
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

#endif // !__XDR_STELLAR_OPERATION_MANAGE_INVOICE_REQUEST_H_INCLUDED__
