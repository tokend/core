// -*- C++ -*-
// Automatically generated from operation-manage-invoice-request.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_OPERATION_MANAGE_INVOICE_REQUEST_H_INCLUDED__
#define __XDR_OPERATION_MANAGE_INVOICE_REQUEST_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/ledger-entries.h"

namespace stellar {

enum class ManageInvoiceRequestAction : std::int32_t {
  CREATE = 0,
  REMOVE = 1,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageInvoiceRequestAction>
  : xdr_integral_base<::stellar::ManageInvoiceRequestAction, std::uint32_t> {
  using case_type = std::int32_t;
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
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

struct InvoiceCreationRequest  : xdr::xdr_abstract {
  struct _ext_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
  private:
    _xdr_case_type v_;
    union {
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<LedgerVersion> &_xdr_case_values() {
      static const std::vector<LedgerVersion> _xdr_disc_vec {
        LedgerVersion::EMPTY_VERSION
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
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
        v_ = which;switch (v_)
{
        case (int32_t)LedgerVersion::EMPTY_VERSION:
          break;
}

      }
      else
        v_ = which;
    }
    explicit _ext_t(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}

    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}

    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}

    }
    ~_ext_t() {
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
      break;
}
}

    _ext_t &operator=(const _ext_t &source) {
      if (v_ == source.v_)
{
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
else {this->~_ext_t();
      v_ = source.v_;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
      return *this;
    }
    _ext_t &operator=(_ext_t &&source) {
      if (v_ == source.v_)
{
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
else {this->~_ext_t();
      v_ = std::move(source.v_);
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
      return *this;
    }

    LedgerVersion v() const { return LedgerVersion(v_); }
    _ext_t &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }
bool
operator==(xdr::xdr_abstract const& other) const override;
bool
operator<(xdr::xdr_abstract const& other) const override;
private:
    bool
from_bytes(xdr::unmarshaler& u) override;
bool
to_bytes(xdr::marshaler& m) const override;
void
count_size(xdr::measurer& m) const override;

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
  bool
operator==(xdr::xdr_abstract const& other) const override;bool
operator<(xdr::xdr_abstract const& other) const override;private:
  bool
from_bytes(xdr::unmarshaler& u) override;
bool
to_bytes(xdr::marshaler& m) const override;
void
count_size(xdr::measurer& m) const override;

};

struct ManageInvoiceRequestOp  : xdr::xdr_abstract {
  struct _details_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<ManageInvoiceRequestAction>::case_type;
  private:
    _xdr_case_type action_;
    union {
      InvoiceCreationRequest invoiceRequest_;
      uint64 requestID_;
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<ManageInvoiceRequestAction> &_xdr_case_values() {
      static const std::vector<ManageInvoiceRequestAction> _xdr_disc_vec {
        ManageInvoiceRequestAction::CREATE,
        ManageInvoiceRequestAction::REMOVE
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
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
        action_ = which;switch (action_)
{
        case (int32_t)ManageInvoiceRequestAction::CREATE:
new(&invoiceRequest_) InvoiceCreationRequest{};
break;
        case (int32_t)ManageInvoiceRequestAction::REMOVE:
new(&requestID_) uint64{};
break;
}

      }
      else
        action_ = which;
    }
    explicit _details_t(ManageInvoiceRequestAction which = ManageInvoiceRequestAction{}) : action_((int32_t)which) {
      switch (action_)
{
      case (int32_t)ManageInvoiceRequestAction::CREATE:
new(&invoiceRequest_) InvoiceCreationRequest{};
break;
      case (int32_t)ManageInvoiceRequestAction::REMOVE:
new(&requestID_) uint64{};
break;
}

    }
    _details_t(const _details_t &source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageInvoiceRequestAction::CREATE:
new(&invoiceRequest_) InvoiceCreationRequest(source.invoiceRequest_);
break;
      case (int32_t)ManageInvoiceRequestAction::REMOVE:
new(&requestID_) uint64(source.requestID_);
break;
}

    }
    _details_t(_details_t &&source) : action_(source.action_) {
      switch (action_)
{
      case (int32_t)ManageInvoiceRequestAction::CREATE:
new(&invoiceRequest_) InvoiceCreationRequest(std::move(source.invoiceRequest_));
break;
      case (int32_t)ManageInvoiceRequestAction::REMOVE:
new(&requestID_) uint64(std::move(source.requestID_));
break;
}

    }
    ~_details_t() {
switch (action_)
{
    case (int32_t)ManageInvoiceRequestAction::CREATE:
invoiceRequest_.~InvoiceCreationRequest();
break;
    case (int32_t)ManageInvoiceRequestAction::REMOVE:
requestID_.~uint64();
break;
}
}

    _details_t &operator=(const _details_t &source) {
      if (action_ == source.action_)
{
switch (action_)
{
      case (int32_t)ManageInvoiceRequestAction::CREATE:
invoiceRequest_ = source.invoiceRequest_;
break;
      case (int32_t)ManageInvoiceRequestAction::REMOVE:
requestID_ = source.requestID_;
break;
}
}
else {this->~_details_t();
      action_ = source.action_;
switch (action_)
{
      case (int32_t)ManageInvoiceRequestAction::CREATE:
new(&invoiceRequest_) InvoiceCreationRequest(source.invoiceRequest_);
break;
      case (int32_t)ManageInvoiceRequestAction::REMOVE:
new(&requestID_) uint64(source.requestID_);
break;
}
}
      return *this;
    }
    _details_t &operator=(_details_t &&source) {
      if (action_ == source.action_)
{
switch (action_)
{
      case (int32_t)ManageInvoiceRequestAction::CREATE:
invoiceRequest_ = std::move(source.invoiceRequest_);
break;
      case (int32_t)ManageInvoiceRequestAction::REMOVE:
requestID_ = std::move(source.requestID_);
break;
}
}
else {this->~_details_t();
      action_ = std::move(source.action_);
switch (action_)
{
      case (int32_t)ManageInvoiceRequestAction::CREATE:
new(&invoiceRequest_) InvoiceCreationRequest(std::move(source.invoiceRequest_));
break;
      case (int32_t)ManageInvoiceRequestAction::REMOVE:
new(&requestID_) uint64(std::move(source.requestID_));
break;
}
}
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
    }bool
operator==(xdr::xdr_abstract const& other) const override;
bool
operator<(xdr::xdr_abstract const& other) const override;
private:
    bool
from_bytes(xdr::unmarshaler& u) override;
bool
to_bytes(xdr::marshaler& m) const override;
void
count_size(xdr::measurer& m) const override;

  };
  struct _ext_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
  private:
    _xdr_case_type v_;
    union {
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<LedgerVersion> &_xdr_case_values() {
      static const std::vector<LedgerVersion> _xdr_disc_vec {
        LedgerVersion::EMPTY_VERSION
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
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
        v_ = which;switch (v_)
{
        case (int32_t)LedgerVersion::EMPTY_VERSION:
          break;
}

      }
      else
        v_ = which;
    }
    explicit _ext_t(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}

    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}

    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}

    }
    ~_ext_t() {
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
      break;
}
}

    _ext_t &operator=(const _ext_t &source) {
      if (v_ == source.v_)
{
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
else {this->~_ext_t();
      v_ = source.v_;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
      return *this;
    }
    _ext_t &operator=(_ext_t &&source) {
      if (v_ == source.v_)
{
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
else {this->~_ext_t();
      v_ = std::move(source.v_);
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
      return *this;
    }

    LedgerVersion v() const { return LedgerVersion(v_); }
    _ext_t &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }
bool
operator==(xdr::xdr_abstract const& other) const override;
bool
operator<(xdr::xdr_abstract const& other) const override;
private:
    bool
from_bytes(xdr::unmarshaler& u) override;
bool
to_bytes(xdr::marshaler& m) const override;
void
count_size(xdr::measurer& m) const override;

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
  bool
operator==(xdr::xdr_abstract const& other) const override;bool
operator<(xdr::xdr_abstract const& other) const override;private:
  bool
from_bytes(xdr::unmarshaler& u) override;
bool
to_bytes(xdr::marshaler& m) const override;
void
count_size(xdr::measurer& m) const override;

};

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
  static constexpr const bool is_enum = true;
  static constexpr const bool is_numeric = false;
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

struct CreateInvoiceRequestResponse  : xdr::xdr_abstract {
  struct _ext_t : xdr::xdr_abstract {
    using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
  private:
    _xdr_case_type v_;
    union {
    };

  public:
    static constexpr const bool _xdr_has_default_case = false;
    static const std::vector<LedgerVersion> &_xdr_case_values() {
      static const std::vector<LedgerVersion> _xdr_disc_vec {
        LedgerVersion::EMPTY_VERSION
      };
      return _xdr_disc_vec;
    }
    static constexpr int _xdr_field_number(_xdr_case_type which) {
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
        v_ = which;switch (v_)
{
        case (int32_t)LedgerVersion::EMPTY_VERSION:
          break;
}

      }
      else
        v_ = which;
    }
    explicit _ext_t(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}

    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}

    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}

    }
    ~_ext_t() {
switch (v_)
{
    case (int32_t)LedgerVersion::EMPTY_VERSION:
      break;
}
}

    _ext_t &operator=(const _ext_t &source) {
      if (v_ == source.v_)
{
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
else {this->~_ext_t();
      v_ = source.v_;
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
      return *this;
    }
    _ext_t &operator=(_ext_t &&source) {
      if (v_ == source.v_)
{
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
else {this->~_ext_t();
      v_ = std::move(source.v_);
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}
      return *this;
    }

    LedgerVersion v() const { return LedgerVersion(v_); }
    _ext_t &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
      return *this;
    }
bool
operator==(xdr::xdr_abstract const& other) const override;
bool
operator<(xdr::xdr_abstract const& other) const override;
private:
    bool
from_bytes(xdr::unmarshaler& u) override;
bool
to_bytes(xdr::marshaler& m) const override;
void
count_size(xdr::measurer& m) const override;

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
  bool
operator==(xdr::xdr_abstract const& other) const override;bool
operator<(xdr::xdr_abstract const& other) const override;private:
  bool
from_bytes(xdr::unmarshaler& u) override;
bool
to_bytes(xdr::marshaler& m) const override;
void
count_size(xdr::measurer& m) const override;

};

struct ManageInvoiceRequestResult : xdr::xdr_abstract {
  struct _success_t  : xdr::xdr_abstract {
    struct _details_t : xdr::xdr_abstract {
      using _xdr_case_type = xdr::xdr_traits<ManageInvoiceRequestAction>::case_type;
    private:
      _xdr_case_type action_;
      union {
        CreateInvoiceRequestResponse response_;
      };

    public:
      static constexpr const bool _xdr_has_default_case = false;
      static const std::vector<ManageInvoiceRequestAction> &_xdr_case_values() {
        static const std::vector<ManageInvoiceRequestAction> _xdr_disc_vec {
          ManageInvoiceRequestAction::CREATE,
          ManageInvoiceRequestAction::REMOVE
        };
        return _xdr_disc_vec;
      }
      static constexpr int _xdr_field_number(_xdr_case_type which) {
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
          action_ = which;switch (action_)
{
          case (int32_t)ManageInvoiceRequestAction::CREATE:
new(&response_) CreateInvoiceRequestResponse{};
break;
          case (int32_t)ManageInvoiceRequestAction::REMOVE:
            break;
}

        }
        else
          action_ = which;
      }
      explicit _details_t(ManageInvoiceRequestAction which = ManageInvoiceRequestAction{}) : action_((int32_t)which) {
        switch (action_)
{
        case (int32_t)ManageInvoiceRequestAction::CREATE:
new(&response_) CreateInvoiceRequestResponse{};
break;
        case (int32_t)ManageInvoiceRequestAction::REMOVE:
          break;
}

      }
      _details_t(const _details_t &source) : action_(source.action_) {
        switch (action_)
{
        case (int32_t)ManageInvoiceRequestAction::CREATE:
new(&response_) CreateInvoiceRequestResponse(source.response_);
break;
        case (int32_t)ManageInvoiceRequestAction::REMOVE:
          break;
}

      }
      _details_t(_details_t &&source) : action_(source.action_) {
        switch (action_)
{
        case (int32_t)ManageInvoiceRequestAction::CREATE:
new(&response_) CreateInvoiceRequestResponse(std::move(source.response_));
break;
        case (int32_t)ManageInvoiceRequestAction::REMOVE:
          break;
}

      }
      ~_details_t() {
switch (action_)
{
      case (int32_t)ManageInvoiceRequestAction::CREATE:
response_.~CreateInvoiceRequestResponse();
break;
      case (int32_t)ManageInvoiceRequestAction::REMOVE:
        break;
}
}

      _details_t &operator=(const _details_t &source) {
        if (action_ == source.action_)
{
switch (action_)
{
        case (int32_t)ManageInvoiceRequestAction::CREATE:
response_ = source.response_;
break;
        case (int32_t)ManageInvoiceRequestAction::REMOVE:
          break;
}
}
else {this->~_details_t();
        action_ = source.action_;
switch (action_)
{
        case (int32_t)ManageInvoiceRequestAction::CREATE:
new(&response_) CreateInvoiceRequestResponse(source.response_);
break;
        case (int32_t)ManageInvoiceRequestAction::REMOVE:
          break;
}
}
        return *this;
      }
      _details_t &operator=(_details_t &&source) {
        if (action_ == source.action_)
{
switch (action_)
{
        case (int32_t)ManageInvoiceRequestAction::CREATE:
response_ = std::move(source.response_);
break;
        case (int32_t)ManageInvoiceRequestAction::REMOVE:
          break;
}
}
else {this->~_details_t();
        action_ = std::move(source.action_);
switch (action_)
{
        case (int32_t)ManageInvoiceRequestAction::CREATE:
new(&response_) CreateInvoiceRequestResponse(std::move(source.response_));
break;
        case (int32_t)ManageInvoiceRequestAction::REMOVE:
          break;
}
}
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
      }bool
operator==(xdr::xdr_abstract const& other) const override;
bool
operator<(xdr::xdr_abstract const& other) const override;
private:
      bool
from_bytes(xdr::unmarshaler& u) override;
bool
to_bytes(xdr::marshaler& m) const override;
void
count_size(xdr::measurer& m) const override;

    };
    struct _ext_t : xdr::xdr_abstract {
      using _xdr_case_type = xdr::xdr_traits<LedgerVersion>::case_type;
    private:
      _xdr_case_type v_;
      union {
      };

    public:
      static constexpr const bool _xdr_has_default_case = false;
      static const std::vector<LedgerVersion> &_xdr_case_values() {
        static const std::vector<LedgerVersion> _xdr_disc_vec {
          LedgerVersion::EMPTY_VERSION
        };
        return _xdr_disc_vec;
      }
      static constexpr int _xdr_field_number(_xdr_case_type which) {
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
          v_ = which;switch (v_)
{
          case (int32_t)LedgerVersion::EMPTY_VERSION:
            break;
}

        }
        else
          v_ = which;
      }
      explicit _ext_t(LedgerVersion which = LedgerVersion{}) : v_((int32_t)which) {
        switch (v_)
{
        case (int32_t)LedgerVersion::EMPTY_VERSION:
          break;
}

      }
      _ext_t(const _ext_t &source) : v_(source.v_) {
        switch (v_)
{
        case (int32_t)LedgerVersion::EMPTY_VERSION:
          break;
}

      }
      _ext_t(_ext_t &&source) : v_(source.v_) {
        switch (v_)
{
        case (int32_t)LedgerVersion::EMPTY_VERSION:
          break;
}

      }
      ~_ext_t() {
switch (v_)
{
      case (int32_t)LedgerVersion::EMPTY_VERSION:
        break;
}
}

      _ext_t &operator=(const _ext_t &source) {
        if (v_ == source.v_)
{
switch (v_)
{
        case (int32_t)LedgerVersion::EMPTY_VERSION:
          break;
}
}
else {this->~_ext_t();
        v_ = source.v_;
switch (v_)
{
        case (int32_t)LedgerVersion::EMPTY_VERSION:
          break;
}
}
        return *this;
      }
      _ext_t &operator=(_ext_t &&source) {
        if (v_ == source.v_)
{
switch (v_)
{
        case (int32_t)LedgerVersion::EMPTY_VERSION:
          break;
}
}
else {this->~_ext_t();
        v_ = std::move(source.v_);
switch (v_)
{
        case (int32_t)LedgerVersion::EMPTY_VERSION:
          break;
}
}
        return *this;
      }

      LedgerVersion v() const { return LedgerVersion(v_); }
      _ext_t &v(LedgerVersion _xdr_d, bool _xdr_validate = true) {
        _xdr_discriminant((int32_t)_xdr_d, _xdr_validate);
        return *this;
      }
bool
operator==(xdr::xdr_abstract const& other) const override;
bool
operator<(xdr::xdr_abstract const& other) const override;
private:
      bool
from_bytes(xdr::unmarshaler& u) override;
bool
to_bytes(xdr::marshaler& m) const override;
void
count_size(xdr::measurer& m) const override;

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
    bool
operator==(xdr::xdr_abstract const& other) const override;bool
operator<(xdr::xdr_abstract const& other) const override;private:
    bool
from_bytes(xdr::unmarshaler& u) override;
bool
to_bytes(xdr::marshaler& m) const override;
void
count_size(xdr::measurer& m) const override;

  };

  using _xdr_case_type = xdr::xdr_traits<ManageInvoiceRequestResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    _success_t success_;
  };

public:
  static constexpr const bool _xdr_has_default_case = true;
  static const std::vector<ManageInvoiceRequestResultCode> &_xdr_case_values() {
    static const std::vector<ManageInvoiceRequestResultCode> _xdr_disc_vec {};
    return _xdr_disc_vec;
  }
  static constexpr int _xdr_field_number(_xdr_case_type which) {
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
      code_ = which;switch (code_)
{
      case (int32_t)ManageInvoiceRequestResultCode::SUCCESS:
new(&success_) _success_t{};
break;
      default:
        break;
}

    }
    else
      code_ = which;
  }
  explicit ManageInvoiceRequestResult(ManageInvoiceRequestResultCode which = ManageInvoiceRequestResultCode{}) : code_((int32_t)which) {
    switch (code_)
{
    case (int32_t)ManageInvoiceRequestResultCode::SUCCESS:
new(&success_) _success_t{};
break;
    default:
      break;
}

  }
  ManageInvoiceRequestResult(const ManageInvoiceRequestResult &source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManageInvoiceRequestResultCode::SUCCESS:
new(&success_) _success_t(source.success_);
break;
    default:
      break;
}

  }
  ManageInvoiceRequestResult(ManageInvoiceRequestResult &&source) : code_(source.code_) {
    switch (code_)
{
    case (int32_t)ManageInvoiceRequestResultCode::SUCCESS:
new(&success_) _success_t(std::move(source.success_));
break;
    default:
      break;
}

  }
  ~ManageInvoiceRequestResult() {
switch (code_)
{
  case (int32_t)ManageInvoiceRequestResultCode::SUCCESS:
success_.~_success_t();
break;
  default:
    break;
}
}

  ManageInvoiceRequestResult &operator=(const ManageInvoiceRequestResult &source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManageInvoiceRequestResultCode::SUCCESS:
success_ = source.success_;
break;
    default:
      break;
}
}
else {this->~ManageInvoiceRequestResult();
    code_ = source.code_;
switch (code_)
{
    case (int32_t)ManageInvoiceRequestResultCode::SUCCESS:
new(&success_) _success_t(source.success_);
break;
    default:
      break;
}
}
    return *this;
  }
  ManageInvoiceRequestResult &operator=(ManageInvoiceRequestResult &&source) {
    if (code_ == source.code_)
{
switch (code_)
{
    case (int32_t)ManageInvoiceRequestResultCode::SUCCESS:
success_ = std::move(source.success_);
break;
    default:
      break;
}
}
else {this->~ManageInvoiceRequestResult();
    code_ = std::move(source.code_);
switch (code_)
{
    case (int32_t)ManageInvoiceRequestResultCode::SUCCESS:
new(&success_) _success_t(std::move(source.success_));
break;
    default:
      break;
}
}
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
  }bool
operator==(xdr::xdr_abstract const& other) const override;
bool
operator<(xdr::xdr_abstract const& other) const override;
private:
  bool
from_bytes(xdr::unmarshaler& u) override;
bool
to_bytes(xdr::marshaler& m) const override;
void
count_size(xdr::measurer& m) const override;

};

}

#endif // !__XDR_OPERATION_MANAGE_INVOICE_REQUEST_H_INCLUDED__
